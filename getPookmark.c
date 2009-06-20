/*
 * clip saver <<getPookmark>>
 *
 *      POOKMARK Airlines → OPML 変換出力プログラム
 *          written by H.Tsujimura  5 Oct 2006
 *
 * $Log: /comm/bookey/getPookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 13    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 12    07/01/19 18:25 Tsujimura543
 * コメントを修正
 * 
 * 11    07/01/19 17:11 Tsujimura543
 * _getPookmark() を導入、リファクタリングを実施
 * 
 * 10    07/01/18 0:10 Tsujimura543
 * (1) 英語モード対応
 * (2) コマンドライン版をビルドできるようにした
 * 
 * 9     06/12/11 19:24 Tsujimura543
 * 「公開フラグ」 (public/private) に対応 
 * 
 * 8     06/11/29 18:54 Tsujimura543
 * http://pookmark.jp/export が利用可能な場合は、そちらの方から
 * ブックマーク情報を取得するようにした
 * 
 * 7     06/11/27 16:04 Tsujimura543
 * コメントが空のブックマークの取得に失敗する不具合に対処
 * 
 * 6     06/11/16 16:41 Tsujimura543
 * 取得した「コメント」に改行が含まれる場合は、取り除くようにした
 * 
 * 5     06/10/27 0:57 Tsujimura543
 * typo 修正
 * 
 * 4     06/10/27 0:56 Tsujimura543
 * <wbr> を空白に置換する処理を追加
 * 
 * 3     06/10/27 0:33 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 2     06/10/27 0:27 Tsujimura543
 * POOKMARK Airlines のブックマーク一覧ページのフォーマットが変更され
 * たのに伴う修正を実施
 * 
 * 1     06/10/05 20:03 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getPookmark.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
getPookmarkWithCookie(
        char *cookie,       /* (I/O) クッキー                     */
        int  total,         /* (I) 当該ユーザのブックマークの総数 */
        int  *numOfClips    /* (O) 取得したブックマークの数       */
    )
{
    MyClip  *mp = NULL;
    int     num  = 0;
    char    *filename;

    if ( (total <= 0) || !cookie || !(*cookie) )
        return ( mp );

    filename = tempnam( ".", "exp" );
    if ( filename ) {
        FILE    *fp;
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_DESCRIPTION_LEN * 16 * total;

        response = (char *)malloc( sz );
        if ( !response )
            return ( mp );

        strcpy( url, "http://pookmark.jp/export" );
        setUpReceiveBuffer( response, sz );
        setTargetURL( url );
        http_getEx( url, response, cookie );
        fp = fopen( filename, "wb" );
        if ( fp ) {
            fputs( response, fp );
            fclose( fp );

            fp = fopen( filename, "rb" );
            if ( fp ) {
                mp = inputBookmarkHtml( &num, fp );
                fclose( fp );

                if ( mp && (num > 0) ) {
                    int     i;
                    char    *p;

                    for ( i = 0; i < num; i++ ) {
                        p = utf2sjis( mp[i].title );
                        if ( p )
                            strcpy( mp[i].title, p );

                        p = utf2sjis( mp[i].comment );
                        if ( p )
                            strcpy( mp[i].comment, p );

                        p = utf2sjis( mp[i].tags );
                        if ( p )
                            strcpy( mp[i].tags, p );
                    }
                }
            }
        }
        unlink( filename );
        free( filename );
        free( response );
    }

    *numOfClips = num;

    return ( mp );
}

int
_getPookmark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    int     page = 1;
    int     yy, mm, dd;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    sprintf( target, "http://pookmark.jp/user/%s", userName );
    strcpy( url, target );
    do {
        setUpReceiveBuffer( response, sz );
        setTargetURL( url );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) ||
             strstr( response, sjis2utf("指定したページはありません") ) )
            break;

        if ( *total == 0 ) {
            // 全部で何件あるか、前もって調べておく
            p = strstr( response, sjis2utf("件中") );
            if ( p ) {
                while ( *--p && ((*p >= '0') && (*p <= '9')) )
                    if ( p <= response )
                        break;
                if ( *++p ) {
                    if ( *p == '0' )
                        p++;
                    *total = atol( p );
                }
            }
        }

        // ブックマークを抜き出す
        p = strstr( response, "<ul class=\"bookmark\">" );
        if ( !p )
            break;
        p += 21;

        do {
            if ( mp ) {
                MyClip  *np;
                np = allocateMyClipIfNecessary( mp, unit, &cnt, num );
                if ( !np )
                    break;
                *mp = np;
            }
            if ( mpEx ) {
                MyClipEx    *np;
                np = allocateMyClipExIfNecessary( mpEx, unit, &cnt, num );
                if ( !np )
                    break;
                *mpEx = np;
            }

            q = strstr( p, " id=\"bookmark_" );
            s = strstr( p, "</li><!-- /bookmark_" );
            if ( !s )
                s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = q + 14;

            // URL
            q = strstr( p, "<a href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 9;
            q = strstr( p, "\" " );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // タイトル
            p = q + 2;
            q = strstr( p, "<span class=\"title\">" );
            if ( !q || (q > s) )
                break;
            p = q + 20;
            q = strstr( p, "</span>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( !r )
                utf2sjisEx( tmp );
            else
                strcpy( tmp, r );
            while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &#039; → ' に置換 */
            }
            while ( (r = strstr( tmp, "&quot;" )) != NULL ) {
                *r = '"';
                strcpy( r + 1, r + 6 ); /* &quot; → " に置換 */
            }
            while ( (r = strstr( tmp, "<wbr>" )) != NULL ) {
                *r = ' ';
                strcpy( r + 1, r + 5 ); /* <wbr> → 空白 に置換 */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // ハッシュ値
            r = p = q + 7;
            q = strstr( p, "<div class=\"user-count\">" );
            if ( !q )
                q = strstr( p, "<div class=\"user-count " );
            if ( q ) {
                p = strchr( q, '>' ) + 1;
                q = strstr( p, "<a href=\"/url/" );
                if ( q ) {
                    p = q + 14;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( tmp, p, q - p );
                        tmp[q - p] = NUL;
                        if ( mpEx )
                            strcpy( (*mpEx)[num].remarks, tmp );
                    }
                }
            }
            if ( !q )
                q = p - 7;

            // コメント
            p = r;
            q = strstr( p, "<p class=\"comment\">" );
            if ( !q )
                q = strstr( p, "<p class=\"comment " );
            if ( !q || (q > s) )
                q = p - 4; // コメント欄が空の場合
            else {
                p = strchr( q, '>' ) + 1;
                q = strstr( p, "</p>" );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                r = utf2sjis( tmp );
                if ( !r )
                    utf2sjisEx( tmp );
                else
                    strcpy( tmp, r );
                while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                    *r = '\'';
                    strcpy( r + 1, r + 6 ); /* &#039; → ' に置換 */
                }
                while ( (r = strstr( tmp, "&quot;" )) != NULL ) {
                    *r = '"';
                    strcpy( r + 1, r + 6 ); /* &quot; → " に置換 */
                }
                while ( (r = strstr( tmp, "<wbr>" )) != NULL ) {
                    *r = ' ';
                    strcpy( r + 1, r + 5 ); /* <wbr> → 空白 に置換 */
                }
                while ( ((r = strchr(tmp, '\r')) != NULL) ||
                        ((r = strchr(tmp, '\n')) != NULL)    )
                    strcpy( r, r + 1 );     /* 改行を取り除く */
                if ( mp )
                    strcpy( (*mp)[num].comment, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].comment, tmp );
            }

            // タグ
            p = q + 4;
            q = strstr( p, "<p class=\"tag\">" );
            if ( !q )
                q = strstr( p, "<li class=\"tag\">" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = strchr( q, '>' ) + 1;
                do {
                    q = strstr( p, "\" rel=\"tag\">" );
                    if ( !q )
                        q = strstr( p, "\" class=\"tag\">" );
                    if ( !q || (q > s) )
                        break;
                    p = strchr( q, '>' ) + 1;
                    q = strstr( p, "</a>" );
                    if ( !q )
                        break;

                    if ( tmp[0] == NUL )
                        len = 0;
                    else {
                        strcat( tmp, " " );
                        len = strlen( tmp );
                    }
                    strncat( tmp, p, q - p );
                    tmp[len + (q - p)] = NUL;

                    p = q + 4;
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( !r )
                        utf2sjisEx( tmp );
                    else
                        strcpy( tmp, r );
                    while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 6 ); /* &#039; → ' に置換 */
                    }
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // 年月日
            q = strstr( p, "<span class=\"datetime\">" );
            if ( !q || (q > s) )
                break;
            p = q + 23;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            yy = atol( p );

            skipToNextItemWithSeparator( p, '/', s );
            mm = atol( p );

            skipToNextItemWithSeparator( p, '/', s );
            dd = atol( p );

            if ( mp ) {
                (*mp)[num].yyyy = yy;
                (*mp)[num].mm   = mm;
                (*mp)[num].dd   = dd;
                (*mp)[num].HH   = 0;
                (*mp)[num].MM   = 0;
                (*mp)[num].SS   = 0;
            }

            // 公開フラグ
            q = strstr( p, "<span class=\"private\">" );
            if ( q && (q < s) )
                if ( mp )
                    (*mp)[num].publication = PUB_PRIVATE;

            // bookmark ID (削除用)
            q = strstr( p, "delete_confirm('" );
            if ( q && (q < s) ) {
                p = q + 16;
                q = strstr( p, "')" );
                if ( q ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                }
                if ( mpEx )
                    strcpy( (*mpEx)[num].entryID, tmp );
            }

            p = s + 5;
            num++;
            if ( (*total > 0) && (num >= *total) ) {
                cont = FALSE;
                break;
            }
        } while ( p && *p );

        // 次へ
        page++;
        sprintf( url, "%s?page=%d", target, page );
        Sleep( 1000 );
    } while ( cont );

    return ( num );
}

MyClip  *
getPookmark(
        const char *userName,   /* (I) JugemKey ID (JUGEMユーザ名)      */
        const char *password,   /* (I) パスワード (プライベートなブック */
                                /*     マークも取得する場合にのみ必要)  */
        int        *total,      /* (O) 当該ユーザのブックマークの総数   */
        int        *numOfClips  /* (O) 取得したブックマークの数         */
    )
{
    /*
     *  userName で指定されたユーザーのクリップを全件取得する
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    int     num  = 0;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0]   = NUL;
    response[0] = NUL;

    fd = fileno( stderr );
    if ( password && *password ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( !cookie ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "メモリの確保に失敗しました\n"
                        : "memory exhausted.\n",
                       stderr );
            free( response );
            return ( mp );
        }
        memset( cookie, 0x00, MAX_COOKIE_LEN );

        // jugemkey で login (cookie を取得)
        if ( !loginJugemkey( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "POOKMARK への login に失敗しました\n"
                        : "POOKMARK Airlines: login failed.\n",
                       stderr);
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // ブックマークを取得
    num = _getPookmark( userName, cookie, &mp, NULL, response, sz, total );
    if ( (*total > 0) && (num == 0) ) {
        // 上記の方法ではブックマーク情報が取得できなかった場合
        //  -- html ファイルの中身の構造が変更された、などの原因で取得でき
        //     なくなってしまった場合
        if ( cookie ) {
            // POOKMARK のエクスポート機能を使って、ブックマーク情報を取得
            //  -- 注意: この方法では「公開フラグ」の値が取得できない
            if ( mp )
                free( mp );
            mp = getPookmarkWithCookie( cookie, *total, &num );
        }
    }

    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_POOKMARK_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( username, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    if ( getLanguageCode() == 0x0411 ) {
        // 日本語
        fprintf( stderr,
                 "getPookmark: POOKMARK Airlines → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tPOOKMARK Airlinesから吸い出した内容を OPML ファイルとして"
                 "出力する\n" );
        fprintf( stderr,
                 "    getPookmark [-x] -u JugemKeyID -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getPookmark: get bookmarks from POOKMARK Airlines, and "
                 "output them as OPML\n" );
        fprintf( stderr,
                 "    getPookmark [-x] -u JugemKeyID -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* POOKMARK Airlines へ登録済みのブックマークを取得 */
    mp = getPookmark( username, password, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  POOKMARK Airlines のブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "POOKMARK Airlines", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_POOKMARK_EXE */

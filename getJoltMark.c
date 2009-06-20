/*
 * clip saver <<getJoltMark>>
 *
 *      JoltMark → OPML 変換出力プログラム
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/getJoltMark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 7     07/01/19 23:20 Tsujimura543
 * _getJoltMark() を導入、リファクタリングを実施
 * 
 * 6     07/01/17 22:58 Tsujimura543
 * (1) 英語モード対応
 * (2) コマンドライン版をビルドできるようにした
 * 
 * 5     07/01/12 22:33 Tsujimura543
 * (1) 「次のページ」の URL の末尾に余分な文字がつく現象に対処
 * (2) 「コメント」中に <br> が含まれる場合は除去するようにした
 * 
 * 4     06/12/22 18:53 Tsujimura543
 * 評価の取得に対応
 * 
 * 3     06/12/22 15:28 Tsujimura543
 * コメントの取得に対応 (評価の取得は依然として未対応)
 * 
 * 2     06/12/21 21:23 Tsujimura543
 * JoltMark のブックマーク情報の取得に対応 (コメントの取得は未対応)
 * 
 * 1     06/12/21 15:21 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getJoltMark.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20

int
_getJoltMark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    )
{
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    char    markNo[MAX_KEYLENGTH];
    char    ckString[MAX_KEYLENGTH];
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    ckString[0] = NUL;

    strcpy( target, "http://mark.jolt.jp/viewuser/search.do" );
    sprintf( url,
             "%s?s3=%s&s0=&s1=&s2=&s4=&so=&dateFrom=&dateTo=",
             target, userName );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) )
            break;

        // ブックマークを抜き出す
        p = strstr( response, sjis2utf("<!--マーク情報表示-->") );
        if ( !p )
            break;
        p = strstr( p, "-->" ) + 3;

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

            markNo[0] = NUL;
            q = strstr( p, "<div class=\"mark-result\">" );
            s = strstr( p, "<div class=\"mark-list-line-dot\">" );
            if ( !q || !s )
                break;
            p = q + 25;
 
            // タイトル
            q = strstr( p, "<a href=\"/pageDetail/" );
            if ( !q || (q > s) ) {
                q = strstr( p, "<a href=\"pageDetail.do?" );
                if ( q )
                    q += 9;
            }
            if ( !q || (q > s) )
                break;
            p = q + 21;

            //  -- markNo
            r = strchr( p, '"' );
            if ( r && (r < s) ) {
                strncpy( markNo, p, r - p );
                markNo[r - p] = NUL;
            }

            //  -- タイトル
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // 公開・非公開
            p = q + 4;
            q = strstr( p, " class=\"mark-result-noPublic\"" );
            if ( q && (q < s) ) {
                p = q + 29;
                q = strstr( p, sjis2utf("(非公開)") );
                if ( q && (q < s) )
                    if ( mp )
                        (*mp)[num].publication = PUB_PRIVATE;
                q = strstr( p, "</span>" );
                if ( q && (q < s) )
                    p = q + 7;
            }

            // 年月日時分秒
            q = strstr( p, sjis2utf("\">マーク数(") );
            if ( !q || (q > s) )
                break;
            p = strchr( q, ')<' );
            if ( !p || (p > s) )
                break;
            q = p + 2;
            while ( *q && ((*q <= '0') || (*q > '9')) )
                q++;
            p = q;
            if ( !p || (p > s) )
                break;

            q = strchr( p, '<' );
            if ( q && (q < s) ) {
                char    tmp[BUFSIZ];

                r = q--;
                strncpy( tmp, p, q - p );
                while ( (q > p) && isWhiteSpace(*(q - 1)) )
                    q--;
                tmp[q - p] = NUL;
                strcat( tmp, " +0900" );    /* {@@} */
                if ( mp )
                    getDateTimeFromDateString( tmp,
                                               &((*mp)[num].yyyy),
                                               &((*mp)[num].mm),
                                               &((*mp)[num].dd),
                                               &((*mp)[num].HH),
                                               &((*mp)[num].MM),
                                               &((*mp)[num].SS) );
                p = r;
            }

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

            // マークID
            p = q + 2;
            q = strstr( p, sjis2utf(">【削除】</a>") );
            if ( q && (q < s) ) {
                r = p;
                p = strstr( q, "</a>" ) + 4;
                while ( (q > r) && (strncmp( q, "markNo=", 7 ) != 0) )
                    q--;
                if ( !strncmp( q, "markNo=", 7 ) ) {
                    q += 7;
                    r = strchr( q, '&' );
                    if ( !r || (r > p) )
                        r = strchr( q, '"' );
                    if ( !r || (r > p) )
                        r = strchr( q, ' ' );
                    if ( r && (r < p) ) {
                        strncpy( tmp, q, r - q );
                        tmp[r - q] = NUL;
                        if ( mpEx )
                            strcpy( (*mpEx)[num].entryID, tmp );
                    }

                    r = strstr( q, "ckString=" );
                    if ( r && (r < p) ) {
                        q = r + 9;
                        r = strchr( q, '&' );
                        if ( !r || (r > p) )
                            r = strchr( q, '"' );
                        if ( !r || (r > p) )
                            r = strchr( q, ' ' );
                        if ( r && (r < p) ) {
                            strncpy( ckString, q, r - q );
                            ckString[r - q] = NUL;
                        }
                    }
                }
            }

            // タグ
            q = strstr( p, " class=\"mark-result-details-icon-tag\"" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 37;
                do {
                    r = "&dateTo=\">";
                    q = strstr( p, r );
                    if ( !q || (q > s) )
                        break;
                    p = q + strlen( r );
                    r = "</a>";
                    q = strstr( p, r );
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

                    p = q + strlen( r );
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // コメント
            q = strstr( p, "<div class=\"mark-result-details-note\"" );
            if ( q && (q < s) ) {
                p = q + 37;
                q = strchr( p, '>' );
                if ( q && (q < s) ) {
                    p = q + 1;
                    while ( isWhiteSpace( *p ) )
                        p++;
                    q = strstr( p, "</div>" );
                    while ( (q > p) && isWhiteSpace( *(q - 1) ) )
                        q--;
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    if ( tmp[0] ) {
                        r = utf2sjis( tmp );
                        if ( r )
                            strcpy( tmp, r );
                        while ((r = strstr(tmp, "<br>")) != NULL)
                            strcpy( r, r + 4 );
                    }
                    if ( mp )
                        strcpy( (*mp)[num].comment, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].comment, tmp );
                }
            }

            // 評価
            //   → 「編集ページ」から取ってくる必要がある
            //   → 自分の「評価」しか取得できない
            if ( mp ) {
                if ( cookie && markNo[0] ) {
                    char    response2[MAX_CONTENT_SIZE];
                    size_t  sz2 = MAX_CONTENT_SIZE;

                    sprintf( url,
                             "http://mark.jolt.jp/editMark.do?markNo=%s",
                             markNo );
                    setUpReceiveBuffer( response2, sz2 );
                    http_getEx( url, response2, cookie );
                    if ( response2[0] ) {
                        q = strstr( response2, "\" selected=\"selected\">" );
                        if ( q ) {
                            while ( (q > response2)              &&
                                    ((*q <= '0') || (*q >= '6'))    )
                                q--;
                            if ( (*q >= '1') && (*q <= '5') )
                                (*mp)[num].evaluation = (*q - '0');
                        }
                    }
                }
            }

            if ( mpEx )
                strcpy( (*mpEx)[num].remarks, ckString );

            p = s + 32;

            num++;
        } while ( p && *p );

        // 次へ
        cont = FALSE;
        p = strstr( response, sjis2utf("><div id=\"page-next\">次のページ") );
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( !q )
                    q = strchr( p, '>' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;

                    q = strchr( page, '>' );
                    if ( q )
                        *q = NUL;

                    sprintf( url, "%s%s", target, page );
                    cont = TRUE;
                    Sleep( 1000 );
                }
            }
        }
    } while ( cont );

    return ( num );
}

MyClip  *
getJoltMark(
        const char *userName,   /* (I) ユーザ名                       */
        const char *password,   /* (I) パスワード (非公開のブックマー */
                                /*     クも取得したい場合に必要)      */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    )
{
    /*
     *  userName で指定されたユーザのブックマーク(のうち、公開されて
     *  いるもの)を全件取得する(非公開のものも取得するには、userName
     *  のユーザの password の指定も必要)
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    int     num = 0;

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0] = NUL;

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

        // JoltMark にlogin (cookie を取得)
        if ( !loginJoltMark( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "JoltMark への login に失敗しました\n"
                        : "JoltMark: login failed.\n",
                       stderr );
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // ブックマークの取得
    num = _getJoltMark( userName, cookie, &mp, NULL, response, sz );
    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_JOLTMARK_EXE
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
                 "getJoltMark: JoltMark → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tJoltMark から吸い出した内容を OPML ファイルとして出力"
                 "する\n" );
        fprintf( stderr,
                 "    getJoltMark [-x] -u ユーザ名 -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getJoltMark: get bookmarks from JoltMark, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getJoltMark [-x] -u username -p password\n" );
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

    /* JoltMark へ登録済みのブックマークを取得 */
    mp = getJoltMark( username, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  JoltMark のブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "JoltMark", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_JOLTMARK_EXE */

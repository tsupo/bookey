/*
 * clip saver <<getEcNaviClip>>
 *
 *      Buzzurl → OPML 変換出力プログラム
 *          written by H.Tsujimura  30 Jun 2006 / 11 Jan 2007
 *
 * $Log: /comm/bookey/getEcNaviClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 25    07/10/05 3:03 Tsujimura543
 * BBAuth 経由でのログイン後も期待通りブックマークの取得ができることを確認
 * 
 * 24    07/10/05 2:45 Tsujimura543
 * BBAuth 経由でのアクセス対応 (ログインには成功するようになったが、その後
 * の処理がまだ不完全)
 * 
 * 23    07/09/19 21:38 Tsujimura543
 * getEcNaviClip() を修正。 *uID が NUL のときは target を空文字列のまま
 * にしておくようにした
 * 
 * 22    07/09/14 23:21 Tsujimura543
 * BBAuth 経由でのアクセス対応 (まだ途中)
 * 
 * 21    07/09/10 16:58 Tsujimura543
 * ソースコードを整理
 * 
 * 20    07/09/10 15:48 Tsujimura543
 * _getEcNaviClip() を修正。 Buzzurl の html フォーマットが変わった
 * のが原因でコメントとタグが取得できなくなってしまっていたため、修
 * 正を実施した
 * 
 * 19    07/08/24 1:38 Tsujimura543
 * Buzzurl のトップページのデザイン変更に伴う修正
 * 
 * 18    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 17    07/01/19 19:52 Tsujimura543
 * _getEcNaviClip() を導入、リファクタリングを実施
 * 
 * 16    07/01/17 21:45 Tsujimura543
 * (1) 英語モード対応
 * (2) コマンドライン版をビルドできるようにした
 * 
 * 15    07/01/11 17:17 Tsujimura543
 * 「コメント」に含まれる &nbsp; を除去するようにした
 * 
 * 14    07/01/11 15:47 Tsujimura543
 * (1) コメントの前に余分な空白が残らないように修正
 * (2) タイトルが文字化けすることがある現象に対処
 * 
 * 13    07/01/11 15:24 Tsujimura543
 * ポインタ計算処理の一部を修正
 * 
 * 12    07/01/11 15:06 Tsujimura543
 * 余分なコメントを削除
 * 
 * 11    07/01/11 15:04 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 10    06/12/07 16:44 Tsujimura543
 * getDateTimeFromDateString() を導入し、日時情報の解析を委ねることにする
 * 
 * 9     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 8     06/10/10 16:49 Tsujimura543
 * ECナビ人気ニュースの Webページの charSet が EUC-JP から UTF-8 に
 * 変更されたのに伴う修正を実施
 * 
 * 7     06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 6     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 5a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 5     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 4     06/08/18 14:10 Tsujimura543
 * getEcNaviClipUserID() の第3引数を追加 (cookie を呼び出し元でも参照可能
 * にするため)
 * 
 * 3     06/08/18 11:46 Tsujimura543
 * ECナビ人気ニュースの html ソースのフォーマット変更に伴う修正を実施
 * 
 * 2     06/07/21 20:51 Tsujimura543
 * ECナビ人気ニュースの取得処理の引数を追加(全何件あるか、取得できるように
 * した)
 * 
 * 1     06/06/30 19:42 Tsujimura543
 * 最初の版(動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getEcNaviClip.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif


/* Buzzurl の記者名を取得する */
char    *
getEcNaviClipUserID(
    const char *userName,
    const char *password,
    AUTH_TYPE  authType,
    char       *cookie,
    size_t     *cookieSize )
{
    Thread static char  userID[MAX_USERIDLEN];
    char                *response;
    char                url[MAX_URLLENGTH];
    size_t              sz  = MAX_CONTENT_SIZE * 20;
    int                 ret = 0;

    userID[0] = NUL;

    /* Buzzurl に login */
    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        // Yahoo! Japan ID で Buzzurl にログイン
        ret = loginEcNaviOnBBAuth( userName, password, cookie, cookieSize );
    }
    else {
        // Buzzurl にログイン
        ret = loginEcNavi( userName, password, cookie );
    }

    if ( !ret ) {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Buzzurl への login に失敗しました\n"
                    : "Buzzurl: login failed.\n",
                   stderr );
        return ( userID );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( userID );

    strcpy( url, "http://buzzurl.jp/" );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    /* Buzzurl トップページから記者名を取得 */
    if ( response && *response ) {
        char    *p = strstr( response, sjis2utf("\">マイページ</a>") );

        if ( !p ) {
            p = strstr(response, sjis2utf("<span>ようこそ<span><a href=\""));
            if ( p ) {
                p += 29;
                while ( *p && (*p != '"') )
                    p++;
                if ( *p && (*p == '"' ) )
                    p++;
                else
                    p = NULL;
            }
        }

        if ( p ) {
            while ( (p > response) && (*p != '/') )
                p--;
            if ( *p == '/' ) {
                if ( !strncmp( p - 3, "/yj/", 4 ) )
                    p -= 3;
                p++;
            }
            else
                p = NULL;
        }

        if ( p ) {
            char    *q = strchr( p, '"' );
            if ( q ) {
                strncpy( userID, p, q - p );
                userID[q - p] = NUL;
            }
        }
    }

    free( response );

    return ( userID );
}

int
_getEcNaviClip(
        const char *target,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    strcpy( url, target );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );
        if ( !response || !(response[0]) )
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
            else {
                char    tmp[BUFSIZ];

                sprintf( tmp, "<td><a href=\"%s\">", target + 21 );
                p = strstr( response, tmp );
                if ( p ) {
                    p += strlen( tmp );
                    *total = atol( p );
                }
            }
        }

        // ブックマークを抜き出す
        p = strstr( response, sjis2utf("<!-- ↓ -->") );
        if ( !p )
            break;
        p = strchr( p, '>' ) + 1;

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

            q = strstr( p, "<p class=\"num\">" );
            s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = q + 15;

            // URL
            q = strstr( p, "<a href=\"/entry/" );
            if ( !q || (q > s) )
                break;
            p = q + 16;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // entry_id
            p = q + 2;
            q = strstr( p, "action_delete('" );
            if ( q && (q < s) ) {
                p = q + 15;
                q = strchr( p, '\'' );
                if ( q ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    if ( mpEx )
                        strcpy( (*mpEx)[num].entryID, tmp );
                }
            }

            // thumbprint
            q = strstr( p, ", '" );
            if ( q && (q < s) ) {
                p = q + 3;
                q = strchr( p, '\'' );
                if ( q ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    if ( mpEx )
                        strcpy( (*mpEx)[num].remarks, tmp );
                }
            }

            // タイトル
            p = q + 1;
            q = strstr( p, "<a href=\"/entry/" );
            if ( !q || (q > s) )
                break;
            p = q + 16;
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjisEx( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( ( r = strstr( tmp, "&#39;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 5 ); /* &#39; → ' に置換 */
            }
            while ( ( r = strstr( tmp, "&quot;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &quot; → ' に置換 */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            q = strstr( p, "<div class=\"comment\">" );
            if ( !q )
                q = strstr( p, "<div class=\"comment\" " );
            if ( q && (q < s) ) {
                p = q + 21;
                q = strstr( p, "<p class=\"tag\">" );

                if ( q && (q < s) ) {
                    // キーワード (タグ)
                    int len;

                    tmp[0] = NUL;
                    p = q + 15;
                    do {
                        q = strstr( p, "[<a href=\"/user/" );
                        if ( !q || (q > s) )
                            break;
                        p = q + 16;
                        q = strstr( p, "\">" );
                        if ( !q )
                            break;
                        p = q + 2;
                        q = strstr( p, "</a>]" );
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

                        p = q + 5;
                    } while ( p < s );
                    if ( tmp[0] ) {
                        r = utf2sjisEx( tmp );
                        if ( r )
                            strcpy( tmp, r );
                    }
                    if ( mp )
                        strcpy( (*mp)[num].tags, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].tags, tmp );

                    q = strstr( p, "</p>" );
                    if ( q && (q < s) )
                        p = q;
                }

                q = strstr( p, "<p>" );
                if ( q && (q < s) ) {
                    // コメント

                    p = q + 4;
                    while ( isWhiteSpace(*p) )
                        p++;
                    r = strstr( p, "</p>" );
                    if ( r && (r < s) ) {
                        char    *pp = r + 4;
                        while ( (r > p) && isWhiteSpace( *(r - 1) ) )
                            r--;
                        if ( r > p ) {
                            strncpy( tmp, p, r - p );
                            tmp[r - p] = NUL;
                            deleteHtmlTags( tmp );
                            r = utf2sjisEx( tmp );
                            if ( r )
                                strcpy( tmp, r );
                            while ((r = strstr(tmp, "&nbsp;")) != NULL)
                                strcpy( r, r + 6 );
                            if ( mp )
                                strcpy( (*mp)[num].comment, tmp );
                            if ( mpEx )
                                strcpy( (*mpEx)[num].comment, tmp );
                        }
                        p = pp;
                    }
                }
            }

            // 年月日時分秒
            q = strstr( p, "<p class=\"permalink\">" );
            if ( !q || (q > s) )
                break;
            p = q + 21;
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            q = strchr( p, '<' );
            if ( q ) {
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
            }

            p = s + 5;

            num++;
        } while ( p && *p );

        // 次へ
        cont = FALSE;
        p = strstr( response, sjis2utf("\">次へ</a>") );
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;
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
getEcNaviClip(
        const char *userName,   /* (I) login時に使うメールアドレス    */
        const char *password,   /* (I) login時に使うパスワード        */
        const char *userName2,  /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char *password2,  /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE  authType,    /* (I) 認証タイプ                     */
        const char *userID,     /* (I) 記者名                         */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 取得したブックマークの数       */
    )
{
    /*
     *  userName で指定された記者のマイニュース、もしくは userID で指定さ
     *  れた記者のマイニュースを全件取得する(userName で指定する場合は、
     *  password の指定も必要。userID で指定する場合は、password は不要)
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    size_t  sz   = MAX_CONTENT_SIZE * 20;
    int     num  = 0;
    const char  *u = userName;
    const char  *p = password;

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        u = userName2;
        p = password2;
    }

    *total      = 0;
    *numOfClips = 0;
    target[0]   = NUL;
    if ( u && u[0] && p && p[0] ) {
        size_t  cookieSize = MAX_COOKIE_LEN;
        char    *cookie;
        char    *uID;

        cookie = (char *)malloc( cookieSize + 1 );
        if ( !cookie )
            return ( mp );
        memset( cookie, 0x00, cookieSize );

        uID = getEcNaviClipUserID( u, p, authType, cookie, &cookieSize );
        if ( uID && *uID )
            sprintf( target, "http://buzzurl.jp/user/%s/all", uID );
        free( cookie );
    }
    else if ( userID && userID[0] )
        sprintf( target, "http://buzzurl.jp/user/%s/all", userID );
    if ( target[0] == NUL )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // ブックマークの取得
    num = _getEcNaviClip( target, NULL, &mp, NULL, response, sz, total );
    *numOfClips = num;

    free( response );

    return ( mp );
}


#ifdef  GET_BUZZURL_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        AUTH_TYPE *authType,
        BOOL      *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'U':
                    *authType = AK_YAHOOJAPAN_BBAUTH;
                    /* fall into ... */
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
                 "getBuzzurl: Buzzurl → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tBuzzurl から吸い出した内容を OPML ファイルとして出力"
                 "する\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -u メールアドレス -p パスワード\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -U Yahoo!JapanID -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getBuzzurl: get bookmarks from Buzzurl, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -u mailaddress -p password\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -U Yahoo!JapanID -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL        useProxy = FALSE;
    char        username[MAX_USERIDLEN];
    char        password[MAX_PASSWDLEN];
    int         numOfClips = 0;
    int         total      = 0;
    MyClip      *mp = NULL;
    AUTH_TYPE   authType = AK_ORIGINAL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &authType, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* Buzzurl へ登録済みのブックマークを取得 */
    mp = getEcNaviClip( username, password,
                        username, password,
                        authType,
                        NULL, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Buzzurl のブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "Buzzurl", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BUZZURL_EXE */

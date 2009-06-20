/*
 * clip loader <<putNewsing>>
 *
 *      OPML → newsing 登録プログラム
 *          written by H.Tsujimura  29 Sep 2006
 *
 * History:
 * $Log: /comm/bookey/putNewsing.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     07/10/12 1:47 Tsujimura543
 * BBAuth 経由でのアクセスに対応
 * 
 * 6     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 5     07/01/23 19:45 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 4     07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 3     07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 2     06/09/30 0:54 Tsujimura543
 * タグの数を強制的に5個以内にしてから投稿するようにした
 * 
 * 1     06/09/29 23:43 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putNewsing.c 1     09/05/14 3:48 tsupo $";
#endif

BOOL
_putNewsing(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    int         status;
    const char  *p;
    char        url[MAX_URLLENGTH * 16];
    BOOL        ret = FALSE;

    errorString[0] = NUL;

    status = 0;

    /* まず、投稿用ダイアログを GET */
    /*  -- タイトル */
    p = euc2utf( mp->title );
    if ( !p )
        p = sjis2utf( mp->title );
    sprintf( url,
             "http://newsing.jp/add?title=%s&",
             encodeURL(p ? p : mp->title) );

    /*  -- URL */
    sprintf( url + strlen(url),
             "url=%s&",
             encodeURL(mp->url) );

    /*  -- コメント */
    p = euc2utf( mp->comment );
    if ( !p )
        p = sjis2utf( mp->comment );
    sprintf( url + strlen(url),
             "description=%s",
             encodeURL(p ? p : mp->comment) );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        const char  *q;

        p = strstr( response, sjis2euc("この記事をピックアップ") );
        q = strstr( response, sjis2euc("コメントをする") );
        if ( p )
            status = 1; // まだ誰も投稿していない
        else if ( q )
            status = 2; // すでに誰かが投稿している
        else
            status = 0;
    }

    if ( status ) {
        const char  *q;
        int         len;
        int         cnt;
        char        tags[BUFSIZ];

        memset( request,  0x00, MAX_CONTENT_SIZE );
        strcpy( url, "http://newsing.jp/index.php" );

        /* url */
        sprintf( request,
                 "action_%s=1&"
                 "url=%s&",
                 status == 1 ? "add" : "comment",
                 encodeURL(mp->url) );
        if ( status == 2 ) {
            /* submit */
            sprintf( request + strlen(request),
                     "submit=%s&",
                     "submit" );
        }

        if ( status == 1 ) {
            /* タイトル */
            p = utf2euc( mp->title );
            if ( !p )
                p = sjis2euc( mp->title );
            sprintf( request + strlen(request),
                     "title=%s&",
                     encodeURL(p ? p : mp->title) );
        }

        /* 評価 */
        sprintf( request + strlen(request),
                 "thumb=%d&",
                 (mp->affirmation == AFF_BAD) ? 0 : 1 );


        /* タグ (スペース区切り、5個まで) */
        q   = mp->tags;
        cnt = 0;
        tags[0] = NUL;
        do {
            p = strchr( q, ' ' );
            if ( p ) {
                len = tags[0] ? strlen( tags ) : 0;
                if ( len > 0 ) {
                    strcat( tags, " " );
                    len++;
                }
                strncat( tags, q, p - q );
                tags[len + (p - q)] = NUL;
                q = p + 1;
                cnt++;
            }
            else {
                if ( tags[0] )
                    strcat( tags, " " );
                strcat( tags, q );
                cnt++;
                break;
            }
        } while ( (cnt < 5) && *q );

        p = utf2euc( tags );
        if ( !p )
            p = sjis2euc( tags );
        sprintf( request + strlen(request),
                 "tag=%s&",
                 encodeURL(p ? p : tags) );

        /* 意見・要約 */
        p = utf2euc( mp->comment );
        if ( !p )
            p = sjis2euc( mp->comment );
        sprintf( request + strlen(request),
                 "%s=%s&",
                 status == 1 ? "description" : "comment",
                 encodeURL(p ? p : mp->comment) );

        if ( status == 1 ) {
            /* submit */
            sprintf( request + strlen(request),
                     "submit=%s",
                     encodeURL(sjis2euc("この記事をピックアップ")) );
        }
        else {
            /* fromcommentwindow */
            sprintf( request + strlen(request),
                     "fromcommentwindow=%s",
                     "true" );
        }

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            if ( strstr(response,
                        sjis2euc("要約・意見には全角30文字以上("
                                 "半角60文字以上)入力して下さい")) ) {
                strcpy( errorString,
                        getLanguageCode() == 0x0411
                         ? "コメントが短すぎます(全角30文字以上にしてください)。"
                         : "Your comment is too short.\r\n"
                           "You should write comment over 60 bytes long!");
                ret = TRUE; /* 登録失敗だが、このままリトライしても失敗 */
                            /* するだけなので登録成功扱いとする         */
            }
            else if ( strstr( response, mp->url )            ||
                      strstr( response, encodeURL(mp->url) )    )
                ret = TRUE; /* 登録成功 */
        }
    }

    return ( ret );
}

void
putNewsing(
        const char   *userName,
        const char   *password,
        const char   *userName2,  /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char   *password2,  /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE    authType,    /* (I) 認証タイプ                     */
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        // Yahoo! Japan ID で newsing にログイン
        ret = loginNewsingOnBBAuth(userName2, password2, cookie, &cookieSize);
    }
    else {
        /* newsing に login */
        ret = loginNewsing( userName, password, cookie );
    }
    if ( ret == 1 )
        putBookmarks( "newsing", mp, numOfClips, cookie, cookieSize, NULL,
                      _putNewsing );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "newsing への login に失敗しました\n"
                    : "newsing: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "newsing へのログインに失敗しました。  "
                         : "newsing: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_NEWSING_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        AUTH_TYPE *authType,
        BOOL      *useProxy,
        FILE      **fp
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
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;

                case 'i':
                    if ( argv[i][j + 1] ) {
                        FILE    *gp = fopen( &(argv[i][j + 1]), "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s が見つかりません\n"
                                      : "%s: Not found.\n",
                                     &(argv[i][j + 1]) );
                            exit( 255 );
                        }
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        FILE    *gp = fopen( argv[i + 1], "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s が見つかりません\n"
                                      : "%s: Not found.\n",
                                     argv[i + 1] );
                            exit( 255 );
                        }
                        i++;
                        j = strlen( argv[i] ) - 1;
                    }
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
                 "putNewsing: OPML → newsing 登録ツール\n" );
        fprintf( stderr,
                 "    putNewsing [-x] -u ユーザ名 -p パスワード\n"
                 "               [-i OPMLファイル名]\n" );
        fprintf( stderr,
                 "    putNewsing [-x] -U Yahoo!JapanID -p パスワード\n"
                 "               [-i OPMLファイル名]\n" );
        fprintf( stderr,
    "\t-x: proxy を使う\n"
    "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n\n"
    "  *注意: newsing は「コメント」が60バイト以下(全角30文字以下)だと登録\n"
    "         に失敗します。\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putNewsing: read bookmarks from OPML, and put them into newsing\n" );
        fprintf( stderr,
      "    putNewsing [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "    putNewsing [-x] -U Yahoo!JapanID -p password [-i OPMLfilename]\n");
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n\n"
      "    *Warning* :: If length of 'comment' is less than 60 bytes long,\n"
      "                 registration into newsing will be failed.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int         numOfClips = 0;
    char        username[MAX_USERIDLEN + 1];
    char        password[MAX_PASSWDLEN + 1];
    BOOL        useProxy = FALSE;
    FILE        *fp = stdin;
    MyClip      *mp = NULL;
    AUTH_TYPE   authType = AK_ORIGINAL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &authType, &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを newsing に登録 */
        putNewsing( username, password,
                    username, password,
                    authType,
                    mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_NEWSING_EXE */

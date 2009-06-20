/*
 * clip loader <<put1470net>>
 *
 *      OPML → 1470.netリニューアル版 登録プログラム
 *          written by H.Tsujimura  14 Jul 2006
 *
 * $Log: /comm/bookey/putMMmemo/put1470net.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 18    07/10/05 4:18 Tsujimura543
 * ソース整理
 * 
 * 17    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 16    07/07/02 16:35 Tsujimura543
 * 1470.net リニューアル版のデザイン変更に伴い、ブックマーク登録の
 * 成功・失敗判定条件を修正
 * 
 * 15    07/01/23 21:35 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 14    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 13    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 12    06/12/22 18:37 Tsujimura543
 * getEvaluation() を導入。title が MM/Memo 形式であれば、正規化してから
 * 登録するようにしてみた
 * 
 * 11    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 10    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 9a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 9     06/08/22 17:48 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 8     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 7     06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 6     06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 5     06/07/18 21:04 Tsujimura543
 * ログイン失敗時にエラーダイアログを出すようにした
 * 
 * 4     06/07/18 20:47 Tsujimura543
 * &raquo: 関連の処理を修正(はてなブックマークの挙動変更に伴うコードの見直
 * し)
 * 
 * 3     06/07/18 13:59 Tsujimura543
 * OPMLファイルからの評価(レート)、グループの取り込みに対応
 * 
 * 2     06/07/18 11:43 Tsujimura543
 * MONO の登録に対応した
 * 
 * 1     06/07/15 0:55 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putMMmemo/put1470net.c 1     09/05/14 3:48 tsupo $";
#endif

BOOL
_put1470net(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    char        url[1024];
    char        webpageID[16];
    char        asin[16];
    const char  *p;
    char        *q;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    memset( request, 0x00, MAX_CONTENT_SIZE );

    // メモ登録・更新フォームを GET
    strcpy( url, "http://1470.net/tools/memo/new" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        char    csrf[64];

        // _csrf を取得
        p = strstr( response, "name=\"_csrf\" value=\"" );
        if ( p ) {
            p += 20;
            q = strstr( p, "\" />" );
            if ( q ) {
                char    tmpTitle[2048];
                char    groupStr[8];
                long    rate = 0;

                strncpy( csrf, p, q - p );
                csrf[q - p] = NUL;

                groupStr[0] = NUL;
                p = sjis2utf(mp->title);
                strcpy( tmpTitle, p ? p : mp->title );

                // MM/Memo 形式の title を扱うための処理
                rate = getEvaluation( tmpTitle, UTF8 );
                q = tmpTitle;
                if ( rate == 0 )
                    if ( (mp->evaluation >= EVL_ONE)  &&
                         (mp->evaluation <= EVL_FIVE)    )
                        rate = mp->evaluation;

                sprintf( request,
                         "_csrf=%s&"
                         "title=%s&",
                         csrf, 
                         encodeURLex2( q ) );

                if ( (rate >= EVL_ONE) && (rate <= EVL_FIVE) )
                    sprintf( request + strlen(request),
                             "eval=%d&",
                             rate );
                else
                    strcat( request, "eval=&" );

                if ( groupStr[0] )
                    sprintf( request + strlen(request),
                             "group=%s&",
                             encodeURL( groupStr ) );
                else
                    strcat( request, "group=&" );

                p = sjis2utf(mp->tags);
                sprintf( request + strlen(request),
                         "tag=%s&",
                         encodeURL( p ? p : mp->tags ) );

                p = sjis2utf(mp->comment);
                sprintf( request + strlen(request),
                         "comment=%s&",
                         encodeURL( p ? p : mp->comment ) );

                sprintf( request + strlen(request),
                         "todoName=&"
                         "todoDate=&"
                         "newUri=%s&",
                         encodeURL( mp->url) );

                getASIN( mp->url, asin );
                if ( asin[0] )
                    sprintf( request + strlen(request),
                             "asins[]=%s&",
                             asin );
                strcat( request, "newAsin=&" );

                sprintf( request + strlen(request),
                         "searchDate_year=%d"
                         "searchDate_month=%d"
                         "searchDate_day=%d"
                         "locationQuery=&"
                         "_save=%s",
                         mp->yyyy,
                         mp->mm,
                         mp->dd,
                         encodeURL( sjis2utf("保存する") ) );

                // メモを投稿
                setUpReceiveBuffer( response, sz );
                http_postEx( url, "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response ) {
                    if ( (p = strstr( response, "resId=" )) != NULL ) {
                        q = strstr( p, sjis2utf("\">返信</a>") );
                        if ( !q )
                            q = strstr( p, sjis2utf("\">res</a>") );
                        if ( q ) {
                            strncpy( webpageID, p, q - p );
                            webpageID[q - p] = NUL;
                            ret = TRUE; // 投稿成功
                        }
                    }
                }
            }
        }
    }

    return ( ret );
}

void
put1470net(
        const char   *userName,  /* (I) 認証用ユーザ名         */
        const char   *password,  /* (I) 認証用パスワード       */
        const char   *userName2, /* (I) 認証用ユーザ名(予備)   */
        const char   *password2, /* (I) 認証用パスワード(予備) */
        AUTH_TYPE    authType,   /* (I) 認証タイプ             */
        const MyClip *mp,        /* (I) ブックマーク情報       */
        int          numOfClips  /* (I) ブックマーク数         */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    userID[32];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    memset( userID, 0x00, 32 );

    /* 1470.net にログイン */
    ret = login1470net( userName, password, userName2, password2, authType,
                        cookie, userID );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "1470.net", mp, numOfClips,
                      cookie, cookieSize, NULL,
                      _put1470net );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "1470.net への login に失敗しました\n"
                    : "1470.net: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "1470.netへのログインに失敗しました。  "
                         : "1470.net: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_1470NET_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        char      *username2,
        char      *password2,
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

                case 'U':
                    if ( argv[i][j + 1] ) {
                        strcpy( username2, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username2, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'P':
                    if ( argv[i][j + 1] ) {
                        strcpy( password2, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password2, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'a':
                    switch ( argv[i][j + 1] ) {
                    case 't':
                        *authType = AK_TYPEKEY;
                        if ( argv[i][j + 2] == 'h' ) {
                            *authType = AK_TYPEKEY_HATENA;
                            j++;
                        }
                        break;
                    case 'h':
                        *authType = AK_HATENA;
                        if ( argv[i][j + 2] == 't' ) {
                            *authType = AK_HATENA_TYPEKEY;
                            j++;
                        }
                        break;
                    case 'T':
                        *authType = AK_TYPEKEY_HATENA;
                        break;
                    case 'H':
                        *authType = AK_HATENA_TYPEKEY;
                        break;
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
             "put1470net: OPML → 1470.net リニューアル版 登録ツール\n" );
        fprintf( stderr,
             "    put1470net [-x] -u TypeKeyユーザ名 -p TypeKeyパスワード\n");
        fprintf( stderr,
             "    put1470net [-x] -U はてなID -P はてなパスワード\n" );
        fprintf( stderr,
       "    put1470net [-x] -a{T|H} -u TypeKeyユーザ名 -p TypeKeyパスワード\n"
       "               -U はてなID -P はてなパスワード\n" );
        fprintf( stderr,
       "\t-x: proxy を使う\n"
       "\t-aT: まず TypeKey 認証でのアクセスを試し、失敗した場合ははてな"
       "認証でのアクセスを試みる\n"
       "\t-aH: まずはてな認証でのアクセスを試し、失敗した場合は TypeKey "
       "認証でのアクセスを試みる\n"
       "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
        "put1470net: read bookmarks from OPML, and put them into 1470.net\n");
        fprintf( stderr,
             "    put1470net [-x] -u TypekeyID -p TypeKeyPassword\n" );
        fprintf( stderr,
             "    put1470net [-x] -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "    put1470net [-x] -a{T|H} -u TypekeyID -p TypeKeyPassword\n"
             "               -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "      TypekeyID: ID for TypeKey authentication\n"
             "      TypeKeyPassword: password for TypeKey authentication\n" );
        fprintf( stderr,
             "      hatenaID: ID for Hatena authentication\n"
             "      hatenaPassword: password for Hatena authentication\n" );
        fprintf( stderr,
         "\t-x: use http access via proxy server\n"
         "\t-aT: Use 'TypeKey' authentication first. If 'TypeKey' failure,"
         "\n\t\tthen try 'Hatena' authentication.\n"
         "\t-aH: Use 'Hatena' authentication first. If 'Hatena' falure,\n"
         "\t\tthen try 'TypeKey' authentication.\n"
         "\t-i: If this option is not specified, read from standard input\n"
         "\t    instead of OPML\n\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int         numOfClips = 0;
    char        username[MAX_USERIDLEN + 1];
    char        password[MAX_PASSWDLEN + 1];
    char        username2[MAX_USERIDLEN];
    char        password2[MAX_PASSWDLEN];
    AUTH_TYPE   authType = AK_TYPEKEY; /* default */
    BOOL        useProxy = FALSE;
    FILE        *fp = stdin;
    MyClip      *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username,  0x00, MAX_USERIDLEN );
    memset( password,  0x00, MAX_PASSWDLEN );
    memset( username2, 0x00, MAX_USERIDLEN );
    memset( password2, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username,  password,
                  username2, password2,
                  &authType, &useProxy,
                  &fp );

    if ( username[0]  && password[0]  &&
         username2[0] && password2[0]    ) {
        if ( (authType != AK_TYPEKEY_HATENA) &&
             (authType != AK_HATENA_TYPEKEY)    )
            authType = AK_TYPEKEY_HATENA;
    }
    else if ( username[0] && password[0] )
        authType = AK_TYPEKEY;
    else if ( username2[0] && password2[0] )
        authType = AK_HATENA;
    else
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを 1470.net に登録 */
        put1470net( username,  password,
                    username2, password2,
                    authType,
                    mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_1470NET_EXE */

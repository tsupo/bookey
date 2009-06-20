/*
 * clip loader <<putEcNaviClip>>
 *
 *      OPML → Buzzurl 登録プログラム
 *          written by H.Tsujimura  29 Jun 2006 / 11 Jan 2007
 *
 * History:
 * $Log: /comm/bookey/putEcNaviClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    07/10/10 1:51 Tsujimura543
 * BBAuth 経由でのブックマーク投稿時にキーワード(タグ)が設定されない
 * 不具合を修正
 * 
 * 23    07/10/05 4:19 Tsujimura543
 * putBuzzurl() から putBuzzurlOnBBAuth() を分離
 * 
 * 22    07/10/05 3:50 Tsujimura543
 * BBAuth 経由でのログインによるブックマークの登録が成功することを確認
 * 
 * 21    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 20    07/09/14 23:21 Tsujimura543
 * BBAuth 経由でのアクセス対応 (まだ途中)
 * 
 * 19    07/03/28 20:28 Tsujimura543
 * タグにマルチバイト文字が含まれる場合、投稿後のタグが最初の1個だけに
 * なってしまう不具合を修正 (投稿API対応時にエンバグ)
 * 
 * 18    07/03/20 0:15 Tsujimura543
 * 自分で設定したタイトルを使う場合は、login する必要がなくなった
 * 
 * 17    07/03/16 23:55 Tsujimura543
 * 不要になったコードを削除
 * 
 * 16    07/03/16 23:17 Tsujimura543
 * Buzzurl の投稿用APIを使用してみる版を試作。問題なく使えることを確認
 * 
 * 15    07/02/16 16:17 Tsujimura543
 * すでに登録されているタイトルと登録しようとしているタイトルが食い違う場
 * 合は、登録しようとしているタイトルで上書きするか、すでに登録されている
 * タイトルをそのまま流用するか、選択できるようにした
 * 
 * 14    07/01/23 20:40 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 13    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 12    07/01/19 19:49 Tsujimura543
 * (リニューアル以降)タグが登録されない不具合を修正
 * 
 * 11    07/01/18 22:46 Tsujimura543
 * (1) putEcNavi.c と putNiftyClip.c のそれぞれに配置してあった getValue()
 *    を分離、独立させた (getValue.c へ移動)
 * (2) putBookmarks() を導入、リファクタリングを実施
 * 
 * 10    07/01/11 16:02 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 9     06/11/14 15:48 Tsujimura543
 * 不要になったコードを削除
 * 
 * 8     06/10/10 16:49 Tsujimura543
 * ECナビ人気ニュースの Webページの charSet が EUC-JP から UTF-8 に
 * 変更されたのに伴う修正を実施
 * 
 * 7     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 6a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 6     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 5     06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 4     06/07/18 21:04 Tsujimura543
 * ログイン失敗時にエラーダイアログを出すようにした
 * 
 * 3     06/07/12 15:51 Tsujimura543
 * 64 → MAX_KEYLENGTH に置換
 * 
 * 2     06/06/29 21:29 Tsujimura543
 * ブックマーク投稿時の request 文字列から余分な文字を除去
 * 
 * 1     06/06/29 18:42 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putEcNaviClip.c 1     09/05/14 3:48 tsupo $";
#endif

/*
 * Buzzurlへの投稿API仕様
 * ・リクエストURI
 *     https://buzzurl.jp/posts/add/v1
 * 
 * ・文字エンコード
 *     UTF-8のみ
 * 
 * ・認証方法
 *     https+BasicAuthです。
 *     (httpでも利用可能ですがなるべくhttpsの利用をお願いします)
 *     Buzzurlへのログインメールアドレスとパスワードを利用します
 * 
 * ・method
 *     postのみ
 * 
 * ・リクエストパラメータ
 *     ・url
 *         ブックマークするURL(必須)
 *     ・title
 *         記事のタイトル(任意)
 *     ・comment
 *         記事へのコメント(任意)
 *     ・keyword
 *         キーワード(任意。8個まで指定可能)
 *     ・cb
 *         JSONP用のcallbackを指定(任意)
 * 
 * レスポンス
 *     ・status
 *         ブックマーク成功の可否。成功時 "success", 失敗時 "fail"を返します。
 *     ・reason
 *         失敗時のみ失敗理由を返します。
 *             ・認証失敗："401 authentication required."
 *             ・post以外のmethod："invalid_method"
 *             ・url未設定："need_url"
 *             ・不正なURLを設定："invalid_url"
 *             ・urlが255byte以上の場合："too_long_url"
 *             ・タイトルの自動取得が出来なく且つtitle未設定時："need_title"
 *             ・Buzzurl側のDBで何らかのエラーが発生："db_error"
 *         ・サンプルレスポンス
 *             ・成功時
 *                 {"status":"success"}
 *             ・失敗時
 *                 {"status":"fail","reason":"invalid_method"}
 */

typedef struct param_putBuzzurl {
    char        *username;  /* ユーザ名                       */
    char        *password;  /* パスワード                     */
    AUTH_TYPE   authType;   /* 認証タイプ                     */
    BOOL        useMyTitle; /* タイトルを独自に設定するか否か */
}   PARAM_PBZRL;


BOOL
putBuzzurlOnBBAuth(
        const MyClip *mp,
        const char   *title,
        PARAM_PBM    *args
    )
{
    BOOL        ret       = FALSE;
    char        *request  = args->request;
    char        *response = args->response;
    char        *cookie   = args->cookie;
    size_t      sz        = args->sz;
    char        url[MAX_URLLENGTH];
    const char  *p, *q;

    // 投稿ページを GET
    sprintf( url, "http://buzzurl.jp/config/add/confirm?url=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    if ( *response ) {
        char    thumbprint[MAX_KEYLENGTH];
        char    user_num[MAX_NAMELEN];
        char    already_exists[MAX_NAMELEN];
        char    default_title[MAX_DESCRIPTION_LEN];

        // thumbprint
        thumbprint[0] = NUL;
        p = strstr( response, "name=\"thumbprint\" value=\"" );
        if ( p ) {
            p += 25;
            q = strchr( p, '"' );
            strncpy( thumbprint, p, q - p );
            thumbprint[q - p] = NUL;
        }

        // user_num
        user_num[0] = NUL;
        p = strstr( response, "name=\"user_num\" value=\"" );
        if ( p ) {
            p += 23;
            q = strchr( p, '"' );
            strncpy( user_num, p, q - p );
            user_num[q - p] = NUL;
        }

        // already_exists
        already_exists[0] = NUL;
        p = strstr( response, "name=\"already_exists\" value=\"" );
        if ( p ) {
            p += 29;
            q = strchr( p, '"' );
            strncpy( already_exists, p, q - p );
            already_exists[q - p] = NUL;
        }

        // title
        default_title[0] = NUL;
        p = strstr( response, "name=\"title\" value=\"" );
        if ( p ) {
            p += 20;
            q = strchr( p, '"' );
            strncpy( default_title, p, q - p );
            default_title[q - p] = NUL;
        }

        // request を組み立てる
        //  -- thumbprint
        if ( thumbprint[0] )
            sprintf( request,
                     "thumbprint=%s&",
                     thumbprint );
        else
            strcpy( request, "thumbprint=&" );

        //  -- URL
        sprintf( request + strlen(request),
                 "url=%s&",
                 encodeURL( mp->url ) );

        // -- user_num
        if ( user_num[0] )
            sprintf( request + strlen(request),
                     "user_num=%s&",
                     user_num );
        else
            strcat( request, "user_num=&" );

        //  -- already_exists
        if ( already_exists[0] )
            sprintf( request + strlen(request),
                     "already_exists=%s&",
                     already_exists );
        else
            strcat( request, "already_exists=&" );

        //  -- タイトル
        if ( title[0] ) {
            p = any2utf( title );
            sprintf( request + strlen(request),
                     "title=%s&", encodeURL(p) );
        }
        else if ( default_title[0] ) {
            sprintf( request + strlen(request),
                     "title=%s&", encodeURL(default_title) );
        }
        else
            strcat( request, "title=&" );

        //  -- コメント
        if ( mp->comment[0] ) {
            p = any2utf( mp->comment );
            sprintf( request + strlen(request),
                     "comment=%s&", encodeURL(p) );
        }

        // キーワード(タグ)は最大8個まで
        if ( mp->tags[0] ) {
            int     i;
            char    tag[80];
            char    *r;
            char    *temp = NULL;
            BOOL    done  = FALSE;

            p = any2utf( mp->tags );
            if ( p ) {
                temp = (char *)malloc( strlen( p ) + 1 );
                if ( temp ) {
                    strcpy( temp, p );
                    p = temp;
                }
            }
            q = p ? p : mp->tags;
            i = 0;
            do {
                p = strchr( q, ' ' );
                if ( p ) {
                    strncpy( tag, q, p - q );
                    tag[p - q] = NUL;
                    q = p + 1;
                }
                else {
                    strcpy( tag, q );
                    done = TRUE;
                }
                i++;

                r = any2utf( tag );
                sprintf( request + strlen(request),
                         "keyword=%s&",
                         encodeURL( r ) );
            } while ( (done == FALSE) && (i < 8) && *q );

            if ( temp )
                free( temp );
        }

        sprintf( request + strlen(request),
                 "submit=%s",
                 encodeURL(sjis2utf(" ブックマークする ")) );
    }

    setUpReceiveBuffer( response, sz );
    http_postEx( "http://buzzurl.jp//config/add/execute",
                 "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, mp->url ) )
            ret = TRUE;
    }

    return ( ret );
}

BOOL
putBuzzurl(
        const MyClip *mp,
        const char   *peseudoTitle,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    BOOL        ret       = FALSE;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_PBZRL *param    = (PARAM_PBZRL *)args->args;
    char        title[MAX_DESCRIPTION_LEN];
    const char  *p, *q;

    if ( peseudoTitle && *peseudoTitle )
        strcpy( title, peseudoTitle );
    else
        strcpy( title, mp->title );

    if ( param->authType == AK_YAHOOJAPAN_BBAUTH ) {
        // BBAuth 経由でのアクセスの場合は API が使えない
        return ( putBuzzurlOnBBAuth( mp, title, args ) );
    }

    // API によるブックマーク登録実行
    //  -- URL
    if ( strlen( mp->url ) >= 256 ) {
        strcpy( errorString, "URL が長すぎます" );
        return ( ret );
    }
    sprintf( request,
             "url=%s&",
             encodeURL( mp->url ) );

    //  -- タイトル
    if ( title[0] ) {
        p = any2utf( title );
        sprintf( request + strlen(request),
                 "title=%s&", encodeURL(p) );
    }

    //  -- コメント
    if ( mp->comment[0] ) {
        p = any2utf( mp->comment );
        sprintf( request + strlen(request),
                 "comment=%s&", encodeURL(p) );
    }

    //  -- キーワード(タグ)は最大8個まで
    if ( mp->tags[0] ) {
        int     i;
        char    tag[80];
        char    *r;
        char    *temp = NULL;
        BOOL    done  = FALSE;

        p = any2utf( mp->tags );
        if ( p ) {
            temp = (char *)malloc( strlen( p ) + 1 );
            if ( temp ) {
                strcpy( temp, p );
                p = temp;
            }
        }
        q = p ? p : mp->tags;
        i = 0;
        do {
            p = strchr( q, ' ' );
            if ( p ) {
                strncpy( tag, q, p - q );
                tag[p - q] = NUL;
                q = p + 1;
            }
            else {
                strcpy( tag, q );
                done = TRUE;
            }
            i++;

            r = any2utf( tag );
            sprintf( request + strlen(request),
                     "keyword=%s&",
                     encodeURL( r ) );
        } while ( (done == FALSE) && (i < 8) && *q );

        if ( temp )
            free( temp );
    }

    sprintf( request + strlen(request),
             "cb=%s", "checkResult" );

    setUpReceiveBuffer( response, sz );
    http_postBASIC( "https://buzzurl.jp/posts/add/v1",
                    param->username, param->password,
                    "application/x-www-form-urlencoded",
                    request, response );
    if ( *response ) {
        if ( strstr( response, "\"success\"" ) )
            ret = TRUE;
        else {
            p = strstr( response, "\"reason\"" );
            if ( p ) {
                p += 9;
                q = strchr( p, '"' );
                if ( q ){
                    q++;
                    p = strchr( q, '"' );
                    if ( p ) {
                        strncpy( errorString, q, p - q );
                        errorString[p - q] = NUL;

                        if ( strstr( errorString, "authentication" ) )
                            strcpy( errorString,
                                    "ユーザ名またはパスワードが違います" );
                        else if ( !strcmp( errorString, "db_error" ) )
                            strcpy( errorString,
                                    "Buzzurl のデータベースで何らかのエラー"
                                    "が発生しました" );
                    }
                }
            }
        }
    }

    return ( ret );
}

BOOL
_putEcNaviClip(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie    = args->cookie;
    char    *response  = args->response;
    size_t  sz         = args->sz;
    BOOL    useMyTitle = ((PARAM_PBZRL *)(args->args))->useMyTitle;
    char    *p, *q;
    char    url[MAX_URLLENGTH * 4];
    char    title[MAX_DESCRIPTION_LEN];

    strcpy( title, mp->title );
    if ( useMyTitle == FALSE ) {
        /* すでに誰かによって登録済みのタイトル(が存在すれば)を採用 */
        sprintf( url, "http://buzzurl.jp/entry/%s",
                 encodeURLforHatena(mp->url) );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( *response ) {
            p = strstr( response, "<h2><a href=\"" );
            if ( p ) {
                /* すでに誰かによって登録済みのタイトルが存在する場合 */
                p += 13;
                q = strstr( p, "\">" );
                if ( q ) {
                    p = q + 2;
                    q = strstr( p, "</a>" );
                    if ( q ) {
                        strncpy( title, p, q - p );
                        title[q - p] = NUL;
                    }
                }
            }
        }
    }

    return ( putBuzzurl( mp, title, errorString, args ) );
}

void
putEcNaviClip(
        const char   *userName,  /* (I) ユーザ名                       */
        const char   *password,  /* (I) パスワード                     */
        const char   *username2,
        const char   *password2,
        AUTH_TYPE    authType,
        BOOL         useMyTitle, /* (I) タイトルを独自に設定するか否か */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    )
{
    char        cookie[MAX_COOKIE_LEN + 1];
    size_t      cookieSize = MAX_COOKIE_LEN;
    PARAM_PBZRL param;
    int         ret = 0;

    memset( cookie, 0x00, MAX_COOKIE_LEN );

    param.username   = (char *)userName;
    param.password   = (char *)password;
    param.authType   = authType;
    param.useMyTitle = useMyTitle;

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        // Yahoo! Japan ID で Buzzurl にログイン
        param.username = (char *)username2;
        param.password = (char *)password2;
        ret = loginEcNaviOnBBAuth(username2, password2, cookie, &cookieSize);
    }
    else if ( useMyTitle == FALSE ) {
        // Buzzurl にログイン
        ret = loginEcNavi( userName, password, cookie );
    }
    else {
        ret = 1;    // useMyTitle が TRUE のときは、login 不要になった
                    // (投稿用API実行時にBASIC認証する)
    }
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "Buzzurl", mp, numOfClips, cookie, cookieSize,
                      (void *)&param,
                      _putEcNaviClip );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Buzzurl への login に失敗しました\n"
                    : "Buzzurl: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Buzzurl へのログインに失敗しました。  "
                         : "Buzzurl: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_BUZZURL_EXE
#define BUFFER_SIZE_FOR_GETTITLE    2048

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
encodeURLforHatena( const char *url )
{
    Thread  static char url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *p;
    char                *q;

    strcpy( url2, url );
    while ( (p = strchr( url2, '#' )) != NULL ) {
        q = &url2[strlen(url2)];
        while ( q >= p + 1 ) {
            *(q + 2) = *q;
            q--;
        }
        *p++ = '%';
        *p++ = '2';
        *p   = '3';
    }

    return ( url2 );
}

void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        AUTH_TYPE *authType,
        BOOL      *useMyTitle,
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

                case 'F':
                    *useMyTitle = !(*useMyTitle);
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
                 "putBuzzurl: OPML → Buzzurl 登録ツール\n" );
        fprintf( stderr,
 "    putBuzzurl [-x] [-F] -u メールアドレス -p パスワード [-i OPMLファイル"
 "名]\n");
        fprintf( stderr,
 "    putBuzzurl [-x] [-F] -U Yahoo!JapanID -p パスワード [-i OPMLファイル"
 "名]\n");
        fprintf( stderr,
 "\t-x: proxy を使う\n"
 "\t-F: すでに登録されているタイトルと登録しようとしているタイトル\n"
 "\t    が食い違う場合は、登録しようとしているタイトルで上書きする\n"
 "\t    (Buzzurl では、タイトルは全員で共有しています。上書きするか\n"
 "\t     どうかは慎重に判断して決めてください)\n"
 "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putBuzzurl: read bookmarks from OPML, and put them into Buzzurl\n" );
        fprintf( stderr,
      "    putBuzzurl [-x] [-F] -u mailaddress -p password [-i OPMLfilename]"
      "\n" );
        fprintf( stderr,
      "    putBuzzurl [-x] [-F] -U Yahoo!JapanID -p password [-i OPMLfilename]"
      "\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-F: overwrite entry title, if original title was different from\n"
      "\t    your specified title\n"
      "\t    (Caution: entry title is shared by all users of Buzzurl)\n"
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
    BOOL        useProxy   = FALSE;
    BOOL        useMyTitle = FALSE;
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
                  &authType, &useMyTitle, &useProxy,
                  &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを Buzzurl に登録 */
        putEcNaviClip( username, password,
                       username, password,
                       authType,
                       useMyTitle, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_BUZZURL_EXE */

/*
 * clip loader <<putNiftyClip>>
 *
 *      OPML → ニフティクリップ 登録プログラム
 *          written by H.Tsujimura  29 Jun 2006
 *
 * History:
 * $Log: /comm/bookey/putNiftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 19    08/11/05 20:59 Tsujimura543
 * コマンドライン版から呼んでいる putNiftyClip() の引数を修正
 * (コマンドライン版では、APIキーは、まだ未対応)
 * 
 * 18    08/11/05 19:48 Tsujimura543
 * 「APIキーを使用して@niftyクリップへ登録する」処理を追加、動作確認した
 * 
 * 17    08/03/12 3:32 Tsujimura543
 * 登録失敗時に「失敗した原因」が取得可能な場合は取得するようにした
 * 
 * 16    08/03/12 1:14 Tsujimura543
 * 2008年3月11日の「@niftyクリップ」リニューアルに対応した
 * 
 * 15    07/10/05 4:18 Tsujimura543
 * ソース整理
 * 
 * 14    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 13    07/01/23 17:10 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 12    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 11    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 10    07/01/18 22:45 Tsujimura543
 * putEcNavi.c と putNiftyClip.c のそれぞれに配置してあった getValue() を
 * 分離、独立させた (getValue.c へ移動)
 * 
 * 9     06/12/11 20:47 Tsujimura543
 * 「公開フラグ」 (public/private) に対応
 * 
 * 8     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 7a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 7     06/08/31 16:38 Tsujimura543
 * 登録に成功したかどうか判断する条件を変更 (従来の条件では「登録失敗」と
 * 判定されてしまうようになったため)
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
 * 3     06/07/18 20:47 Tsujimura543
 * &raquo: 関連の処理を修正(はてなブックマークの挙動変更に伴うコードの見直
 * し)
 * 
 * 2     06/07/12 15:51 Tsujimura543
 * 64 → MAX_KEYLENGTH に置換
 * 
 * 1     06/06/29 21:26 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putNiftyClip.c 1     09/05/14 3:48 tsupo $";
#endif


BOOL
_putNiftyClipWithApiKey(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    *apiKey   = (char *)(args->args);
    char    *p, *q;
    char    tag[80];
    int     i;
    BOOL    ret = FALSE;

    errorString[0] = NUL;

    // APIキー + URL
    sprintf( request,
             "api_key=%s&"
             "url=%s&",
             apiKey,
             encodeURL( mp->url ) );

    // タイトル
    p = any2utf( mp->title );
    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( p ? p : mp->title ) );

    // タグは最大10個まで [最大100文字まで]
    p = any2utf( mp->tags );
    q = p ? p : mp->tags;
    i = 0;
    do {
        p = strchr( q, ' ' );
        if ( p ) {
            strncpy( tag, q, p - q );
            tag[p - q] = NUL;
            sprintf( request + strlen(request),
                     "tag=%s&",
                     encodeURL( tag ) );
            i++;
            q = p + 1;
        }
        else {
            sprintf( request + strlen(request),
                     "tag=%s&",
                     encodeURL( q ) );
            break;
        }
    } while ( (i < 10) && *q );

    // コメント
    p = any2utf( mp->comment );
    sprintf( request + strlen(request),
             "comment=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // 公開フラグ
    sprintf( request + strlen(request),
             "public_flag=%s&"
             "alt=xml",
             mp->publication != PUB_PRIVATE ? "1" : "0" );

    setUpReceiveBuffer( response, sz );
    http_post( "http://api.clip.nifty.com/api/v1/clip/create",
               "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        p = strstr( response, "Bad Request" );
        if ( p ) {
            Sleep( 1000 );
            setUpReceiveBuffer( response, sz );
            http_post( "http://api.clip.nifty.com/api/v1/clip/update",
                       "application/x-www-form-urlencoded",
                       request, response );
        }
    }

    if ( *response ) {
        p = strstr( response, "<message>OK</message>" );
        if ( p )
            ret = TRUE;
        else {
            p = strstr( response, "<message>" );
            if ( p ) {
                p += 9;
                q = strstr( p, "</message>" );
                if ( q ) {
                    char    tmp[BUFSIZ];

                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    strcpy( errorString, utf2sjisEx( tmp ) );
                }
            }
        }
    }

    return ( ret );
}


BOOL
_putNiftyClip(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    url[MAX_URLLENGTH * 4];
    char    *p, *q;
    char    token[MAX_KEYLENGTH];
    char    tag[80];
    int     i;
    BOOL    ret = FALSE;

    errorString[0] = NUL;

    /* token を取得 */
    token[0] = NUL;

    setUpReceiveBuffer( response, sz );
    http_getEx( "http://clip.nifty.com/create", response, cookie );
    if ( *response ) {
        p = getValue( response, "token" );
        if ( p ) {
            strcpy( token, p );

            /* ブックマークを POST */
            strcpy( url, "http://clip.nifty.com/create" );

            sprintf( request,
                     "token=%s&",
                     token );

            // タイトル
            p = any2utf( mp->title );
            sprintf( request + strlen(request),
                     "title=%s&",
                     encodeURLex2( p ? p : mp->title ) );

            // URL
            sprintf( request + strlen(request),
                     "url=%s&",
                     encodeURL( mp->url ) );

            // コメント
            p = any2utf( mp->comment );
            sprintf( request + strlen(request),
                     "comment=%s&",
                     encodeURLex( p ? p : mp->comment ) );

            // タグは最大10個まで [最大100文字まで]
            p = any2utf( mp->tags );
            q = p ? p : mp->tags;
            i = 0;
            do {
                p = strchr( q, ' ' );
                if ( p ) {
                    strncpy( tag, q, p - q );
                    tag[p - q] = NUL;
                    sprintf( request + strlen(request),
                             "%s%s",
                             i == 0 ? "suggesttags=" : "%20",
                             encodeURL( tag ) );
                    i++;
                    q = p + 1;
                }
                else {
                    sprintf( request + strlen(request),
                             "%s%s&",
                             i == 0 ? "suggesttags=" : "%20",
                             encodeURL( q ) );
                    break;
                }
            } while ( (i < 10) && *q );

            // 公開フラグ
            if ( mp->publication != PUB_PRIVATE )
                sprintf( request + strlen(request),
                         "public_flag=%s&",
                         "on" );

            // ジャンプ先
            sprintf( request + strlen(request),
                     "moveto=mylist" );

            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );
            if ( *response ) {
                if ( strstr( response, sjis2utf("クリップ一覧") ) )
                    ret = TRUE; /* 登録成功 */
                else {
                    p = strstr( response, "<h2>" );
                    if ( p ) {
                        p += 4;
                        q = strstr( p, "</h2>" );
                        if ( q ) {
                            char    tmp[BUFSIZ];
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;

                            p = utf2sjis( tmp );
                            if ( p )
                                strcpy( errorString, p );
                        }
                    }
                }
            }
        }
    }

    return ( ret );
}

void
putNiftyClip(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const char   *apiKey,    /* (I) APIキー          */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;
    LCID    l = getLanguageCode();

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    if ( apiKey != NULL && *apiKey != NUL ) {
        putBookmarks( l == 0x0411
                        ? "ニフティクリップ"
                        : "nifty clip",
                      mp, numOfClips, NULL, 0, (void *)apiKey,
                      _putNiftyClipWithApiKey );
    }
    else {
        // ニフティクリップにログイン
        ret = loginNiftyClip( userName, password, cookie );
        if ( ret == 1 ) /* login 成功 */
            putBookmarks( l == 0x0411
                            ? "ニフティクリップ"
                            : "nifty clip",
                          mp, numOfClips, cookie, cookieSize, NULL,
                          _putNiftyClip );
        else {
            int fd = fileno( stderr );

            if ( (fd >= 0) && isatty( fd ) )
                fputs( l == 0x0411
                        ? "ニフティクリップへの login に失敗しました\n"
                        : "nifty clip: login failed.\n",
                       stderr );
#ifdef  WIN32
            else {
                MessageBox(
                    NULL,
                    l == 0x0411
                        ? "ニフティクリップへのログインに失敗しました。  "
                        : "nifty clip: login failed.    ",
                    l == 0x0411
                        ? "ログイン失敗"
                        : "Login failure",
                    MB_OK|MB_ICONERROR );
            }
#endif
        }
    }
}


#ifdef  PUT_NIFTY_CLIP_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy,
        FILE **fp
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
                 "putNC: OPML → ニフティクリップ 登録ツール\n" );
        fprintf( stderr,
                 "    putNC [-x] -u ID -p パスワード [-i OPMLファイル名]\n" );
        fprintf( stderr,
    "      ID: @nifty ID または PLEASY ID\n"
    "\t-x: proxy を使う\n"
    "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putNC: read bookmarks from OPML, and put them into nifty clip\n" );
        fprintf( stderr,
      "    putNC [-x] -u ID -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "      ID: @nifty ID or PLEASY ID\n"
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを ニフティクリップ に登録 */
        putNiftyClip( username, password, NULL, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_NIFTY_CLIP_EXE */

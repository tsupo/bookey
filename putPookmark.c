/*
 * clip loader <<putPookmark>>
 *
 *      OPML → POOKMARK Airlines 登録プログラム
 *          written by H.Tsujimura  4 Oct 2006
 *
 * History:
 * $Log: /comm/bookey/putPookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    08/03/17 15:46 Tsujimura543
 * _putPookmark() を修正 (2008年3月15日辺りから登録できなくなってし
 * まった件の対応 / form が変わった[key が必要になった]のが原因)
 * 
 * 10    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 9     07/02/22 18:44 Tsujimura543
 * タイトルが長すぎて登録に失敗する場合に対処するため、必要に応じて
 * タイトルを短くするようにしてみた
 * 
 * 8     07/01/23 16:42 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 7     07/01/23 16:36 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 6     07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 5     07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 4     06/12/11 19:24 Tsujimura543
 * 「公開フラグ」 (public/private) に対応 
 * 
 * 3     06/11/14 15:54 Tsujimura543
 * chcode() の実体を myClip.c へ移動
 * 
 * 2     06/10/05 20:03 Tsujimura543
 * 文字コード変換処理絡みの修正を実施
 * 
 * 1     06/10/04 21:48 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putPookmark.c 1     09/05/14 3:48 tsupo $";
#endif


BOOL
_putPookmark(
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
    char    key[MAX_KEYLENGTH];
    char    origTitle[MAX_DESCRIPTION_LEN];
    char    *title, *temp;
    char    *p, *q;
    BOOL    ret = FALSE;

    /* key を get */
    key[0] = NUL;
    origTitle[0] = NUL;
    sprintf( url, "http://pookmark.jp/post?url=%s", encodeURL(mp->url) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "name=\"key\"" );
        if ( p ) {
            p += 10;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( key, p, q - p );
                    key[q - p] = NUL;
                }
            }
        }

        p = strstr( response, "name=\"original_title\"" );
        if ( p ) {
            p += 21;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( origTitle, p, q - p );
                    origTitle[q - p] = NUL;
                }
            }
        }

        if ( origTitle[0] == NUL )
            strcpy( origTitle, mp->url );
    }

    if ( key[0] == NUL ) {
        strcpy( errorString, "Cannot get 'key' for posting." );
        return ( ret );
    }

    /* ブックマークを POST */
    strcpy( url, "http://pookmark.jp/post" );

    // key, origURL
    sprintf( request,
             "key=%s&"
             "original_title=%s&",
             key,
             encodeURL( origTitle ) );

    // URL
    sprintf( request + strlen(request),
             "url=%s&",
             encodeURL( mp->url ) );

    // 公開フラグ
    sprintf( request + strlen(request),
             mp->publication == PUB_PRIVATE
                ? "private=on&"
                : "private=&"   );

    // タイトル
    //  -- POOKMARK Airlines は、UTF-8変換+パーセントエンコード後のタイトルの
    //     長さが256バイト以上だと登録に失敗するため、必要に応じてタイトルを
    //     短くするようにする
    temp  = NULL;
    title = chcode( (char *)(mp->title) );
    q = any2sjis( title );
    if ( q && *q && (strlen(q) >= 84) ) {
        temp  = (char *)malloc( BUFSIZ );
        strcpy( temp, justify( q, 80 ) );
        title = temp;
    }
    p = any2utf( title );
    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( p ? p : mp->title ) );
    if ( temp )
        free( temp );

    // コメント
    p = any2utf( chcode( (char *)(mp->comment) ) );
    sprintf( request + strlen(request),
             "comment=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // タグ (空白区切り)
    p = any2utf( chcode( (char *)(mp->tags) ) );
    sprintf( request + strlen(request),
             "tags=%s&",
             encodeURLex( p ? p : mp->tags ) );

    // 登録後のアクション
    sprintf( request + strlen(request),
             "jump=no" );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, sjis2utf("表示しています") ) )
            ret = TRUE; /* 登録成功 */
        else {
            p = strstr( response, "<div class=\"error\">" );
            if ( p ) {
                char    *q;

                p += 19;
                q = strstr( p, "</div>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString,
                                p );    // 課題: 英語モードのとき、そのまま
                    else                //       表示してしまってもいいか?
                        strcpy( errorString,
                        getLanguageCode() == 0x0411
                         ? "不明"
                         : "unknown error" );
                }
            }
        }
    }

    return ( ret );
}

void
putPookmark(
        const char   *userName,  /* (I) jugemkey         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    // jugemkey でログイン
    ret = loginJugemkey( userName, password, cookie );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "POOKMARK Airlines",
                      mp, numOfClips, cookie, cookieSize, NULL,
                      _putPookmark );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "POOKMARK への login に失敗しました\n"
                    : "POOKMARK: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "POOKMARK へのログインに失敗しました。  "
                         : "POOKMARK: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_POOKMARK_EXE
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
                 "putPookmark: OPML → POOKMARK Airlines 登録ツール\n" );
        fprintf( stderr,
    "    putPookmark [-x] -u JugemKeyID -p パスワード [-i OPMLファイル名]\n");
        fprintf( stderr,
    "\t-x: proxy を使う\n"
    "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putPookmark: read bookmarks from OPML, and put them into POOKMARK "
      "Airlines\n" );
        fprintf( stderr,
      "    putPookmark [-x] -u JugemKeyID -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
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
        /* ブックマークを POOKMARK に登録 */
        putPookmark( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_POOKMARK_EXE */

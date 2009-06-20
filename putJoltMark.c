/*
 * clip loader <<putJoltMark>>
 *
 *      OPML → JoltMark 登録プログラム
 *          written by H.Tsujimura  21 Dec 2006
 *
 * History:
 * $Log: /comm/bookey/putJoltMark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     08/11/25 15:12 Tsujimura543
 * ckString 抽出回りを修正
 * (2008年4月23日以降、登録できなくなっていた件に対処)
 * 
 * 7     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 6     07/01/23 20:16 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 5     07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 4     07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 3     06/12/22 18:39 Tsujimura543
 * 登録しようとしているブックマークに設定される「評価」が、いちばん最初の
 * ブックマークの「評価」になってしまう不具合に対処
 * ([誤] mp->evaluation → [正] mp[i].evaluation)
 * 
 * 2     06/12/21 18:07 Tsujimura543
 * 動作確認完了
 * 
 * 1     06/12/21 15:31 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putJoltMark.c 1     09/05/14 3:48 tsupo $";
#endif


typedef struct paramPutJM   {
    const char  *ckString;
}   PARAM_JM;

BOOL
_putJoltMark(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_JM    *param = (PARAM_JM *)(args->args);
    char        url[MAX_URLLENGTH * 4];
    char        tmpTitle[2048];
    char        *p, *q;
    long        rate;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    rate = 0;

    /* ブックマークを POST */
    strcpy( url, "https://mark.jolt.jp/registerMark.do" );

    p = any2utf( mp->title );
    strcpy( tmpTitle, p ? p : mp->title );

    // MM/Memo 形式の title を扱うための処理
    rate = getEvaluation( tmpTitle, UTF8 );
    q = tmpTitle;

    if ( rate == 0 )
        if ( (mp->evaluation >= EVL_ONE)  &&
             (mp->evaluation <= EVL_FIVE)    )
            rate = mp->evaluation;

    // タイトル
    sprintf( request,
             "title=%s&",   // 最大500バイト
             encodeURLex2( q ) );

    // URL
    sprintf( request + strlen(request),
             "url=%s&",     // 最大500バイト
             encodeURL( mp->url ) );

    // マーク名
    sprintf( request + strlen(request),
             "markName=%s&",// 最大500バイト
             encodeURLex2( q ) );
        // 暫定的に、マーク名はタイトルと同じものを使うことにする

    // 説明
    p = any2utf( mp->comment );
    sprintf( request + strlen(request),
             "note=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // 「評価」は必須 (デフォルトは「★3つ」)
    sprintf( request + strlen(request),
             "rate=%d&",
             (rate >= EVL_ONE) && (rate <= EVL_FIVE)
                ? rate
                : EVL_THREE );

    // 公開・非公開 (デフォルトは「公開」)
    sprintf( request + strlen(request),
             "publicMark=%s&",
             mp->publication == PUB_PRIVATE ? "false"
                                            : "true" );

    // 保存
    sprintf( request + strlen(request),
             "saveFlag=%s&",
             "false" ); // 暫定的に false にする

    // タグ (スペース区切りで最大1000バイトまで)
    p = any2utf( mp->tags );
    sprintf( request + strlen(request),
             "tags=%s&",
             encodeURL( p ? p : mp->tags ) );

    // 登録後表示
    sprintf( request + strlen(request),
             "jumpTo=%s&",
             "pageInfo" ); // マーク登録後、ページ情報を表示する

    // ckString
    sprintf( request + strlen(request),
             "ckString=%s&"
             "referer=&",
             param->ckString );

    sprintf( request + strlen(request),
             "regist=%s&",
             encodeURL( sjis2utf("マーク登録") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        p = strstr( response, sjis2utf("」のページ情報</title>") );
        if ( p )
            ret = TRUE; /* 登録成功 */
    }

    return ( ret );
}

void
putJoltMark(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    PARAM_JM    param;
    size_t      cookieSize = MAX_COOKIE_LEN;
    char        cookie[MAX_COOKIE_LEN + 1];
    int         ret;
    char        *response;
    char        url[MAX_URLLENGTH * 4];
    char        *p, *q;
    char        ckString[MAX_KEYLENGTH];
    size_t      sz;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* JoltMark に login */
    ret = loginJoltMark( userName, password, cookie );
    if ( !ret ) {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "JoltMark への login に失敗しました\n"
                    : "JoltMark: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "JoltMark へのログインに失敗しました。  "
                         : "JoltMark: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
        return;
    }

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response )
        return;

    /* ckString を取得 */
    ckString[0] = NUL;
    strcpy( url, "http://mark.jolt.jp/mark/entryForm.do" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        q = strstr( response, "<form name=\"entryMarkForm\"" );
        if ( !q )
            q = response;
        p = strstr( q, "name=\"ckString\" value=\"" );
        if ( p ) {
            p += 23;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( ckString, p, q - p );
                ckString[q - p] = NUL;      // 偽の ckString
            }

            p = strstr( q, "name=\"ckString\" value=\"" );
            if ( p ) {
                p += 23;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( ckString, p, q - p );
                    ckString[q - p] = NUL;  // 本物の ckString
                }
            }
        }
    }
    free( response );
    if ( !(ckString[0]) )
        return;

    /* JoltMark に登録 */
    param.ckString = ckString;
    putBookmarks( "JoltMark", mp, numOfClips, cookie, cookieSize, &param,
                  _putJoltMark );
}


#ifdef  PUT_JOLTMARK_EXE
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
                 "putJoltMark: OPML → JoltMark 登録ツール\n" );
        fprintf( stderr,
    "    putJoltMark [-x] -u ユーザ名 -p パスワード [-i OPMLファイル名]\n" );
        fprintf( stderr,
    "\t-x: proxy を使う\n"
    "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putJoltMark: read bookmarks from OPML, and put them into JoltMark\n" );
        fprintf( stderr,
      "    putJoltMark [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n\n" );
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
        /* ブックマークを JoltMark に登録 */
        putJoltMark( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_JOLTMARK_EXE */

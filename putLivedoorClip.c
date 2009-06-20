/*
 * clip loader <<putLivedoorClip>>
 *
 *      OPML → livedoorクリップ 登録プログラム
 *          written by H.Tsujimura  28 Jun 2006
 *
 * History:
 * $Log: /comm/bookey/putLivedoorClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 28    08/12/02 19:38 Tsujimura543
 * フォーマットストリング脆弱性関連のバグ修正
 * 
 * 27    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 26    07/02/05 20:04 Tsujimura543
 * editLivedoorClip() を追加。すでに登録済みのWebページを上書き登録できる
 * ようにした
 * 
 * 25    07/01/23 20:05 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 24    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 23    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 22    06/12/22 18:39 Tsujimura543
 * 登録しようとしているブックマークに設定される「評価」が、いちばん最初の
 * ブックマークの「評価」になってしまう不具合に対処
 * ([誤] mp->evaluation → [正] mp[i].evaluation)
 * 
 * 21    06/12/06 19:02 Tsujimura543
 * 「r18フラグ」は明示的に 0 を指定するようにした
 * 
 * 20    06/12/06 18:58 Tsujimura543
 * 「公開状態」を指定しての登録ができるようにしてみた
 * 
 * 19    06/11/17 19:38 Tsujimura543
 * getEvaluation() を導入。title が MM/Memo 形式であれば、正規化してから
 * 登録するようにしてみた
 * 
 * 18    06/11/14 15:47 Tsujimura543
 * any2utf() の実体を myClip.c へ移動
 * 
 * 17    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 16    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 15a   06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 15    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 14    06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 13    06/07/18 21:04 Tsujimura543
 * ログイン失敗時にエラーダイアログを出すようにした
 * 
 * 12    06/07/18 20:47 Tsujimura543
 * &raquo: 関連の処理を修正(はてなブックマークの挙動変更に伴うコードの見直
 * し)
 * 
 * 11    06/07/12 15:51 Tsujimura543
 * 64 → MAX_KEYLENGTH に置換
 * 
 * 10    06/07/11 19:43 Tsujimura543
 * 登録しようとしているページがすでに登録済みの場合は、その旨表示する
 * ようにした
 * 
 * 9     06/07/07 13:38 Tsujimura543
 * 「評価」の設定に対応 (MM/Memo から取得した評価付きブックマークの登録
 * 試験を実施し、動作確認を行なった)
 * 
 * 8     06/06/29 11:46 Tsujimura543
 * any2utf() にコメント(説明)を追加
 * 
 * 7     06/06/29 11:39 Tsujimura543
 * charset が ISO-2022-JP なページのクリップにも対応した
 * 
 * 6     06/06/29 11:33 Tsujimura543
 * 実際に投稿する前に、受信バッファをクリアする処理が抜けていたので、追加
 * 
 * 5     06/06/29 11:29 Tsujimura543
 * 少しだけリファクタリング
 * 
 * 4     06/06/29 11:25 Tsujimura543
 * タイトルとコメントのエンコード処理を encodeURL() から encodeURLex() に
 * 変更
 * 
 * 3     06/06/29 1:07 Tsujimura543
 * OPMLファイル(charset=UTF-8)から読み込んだ内容を登録するとき、文字化けが
 * 発生することがある不具合に対処
 * 
 * 2     06/06/29 0:43 Tsujimura543
 * 投稿失敗時の処理経路を整理
 * 
 * 1     06/06/29 0:40 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putLivedoorClip.c 1     09/05/14 3:48 tsupo $";
#endif


void
getHashWithPostkey(
        const char *username,
        const char *targetURL,
        char       *postkey,
        char       *hash,
        char       *cookie
    )
{
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response )
        return;

    sprintf( url, "http://clip.livedoor.com/clips/%s", username );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        char    *p, *q;
        char    clipURL[4096];

        // postkey
        p = strstr( response, "=\"postkey\" value=\"" );
        if ( p ) {
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( postkey, p, q - p );
                postkey[q - p] = NUL;
            }
        }

        // hash
        p = response;
        do {
            hash[0] = NUL;

            q = strstr( p, "<li class=\"clip\" " );
            if ( !q )
                break;
            p = q + 17;

            q = strstr( p, "<a id=\"hash_" );
            if ( !q )
                break;
            p = q + 12;

            q = strstr( p, "\" name=\"p_" );
            if ( !q )
                break;
            p = q + 10;

            q = strchr( p, '"' );
            if ( !q )
                break;
            strncpy( hash, p, q - p );
            hash[q - p] = NUL;

            // url
            p = q + 1;
            q = strstr( p, "<a href=\"" );
            if ( !q ) {
                hash[0] = NUL;
                break;
            }

            p = q + 9;
            q = strchr( p, '"' );
            if ( !q ) {
                hash[0] = NUL;
                break;
            }

            while ( isWhiteSpace(*p) )
                p++;
            while ( (q > p) && isWhiteSpace(*(q - 1)) )
                q--;
            strncpy( clipURL, p, q - p );
            clipURL[q - p] = NUL;
            while ( ( p = strstr( clipURL, "&amp;" ) ) != NULL )
                strcpy( p + 1, p + 5 );
            if ( !strcmp( clipURL, targetURL ) )
                break;  // hash 確定

            p = q + 1;
        } while ( *p );
    }

    free( response );
}

void
setRateOnLivedoorClip(
        const char *username,
        const char *targetURL,
        int        rate,
        char       *cookie
    )
{
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    hash[MAX_KEYLENGTH];
    char    postkey[MAX_KEYLENGTH];
    size_t  sz;

    hash[0]    = NUL;
    postkey[0] = NUL;
    getHashWithPostkey( username, targetURL, postkey, hash, cookie );
    if ( (hash[0] == NUL) || (postkey[0] == NUL) )
        return;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        free( cookie );
        return;
    }

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return;
    }

    strcpy( url, "http://clip.livedoor.com/clip/set_rate" );
    sprintf( request, "hash=%s&rate=%d&postkey=%s", hash, rate, postkey );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    free( response );
    free( request );
}


BOOL
editLivedoorClip(
        const MyClip *mp,
        long         rate,
        const char   *postkey,
        char         *cookie,
        char         *errorString
    )
{
    BOOL    ret = FALSE;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    char    *p;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    orig_title[MAX_DESCRIPTION_LEN];

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        free( cookie );
        return ( ret );
    }

    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return ( ret );
    }

    orig_title[0] = NUL;
    sprintf( url, "http://clip.livedoor.com/clip/edit?link=%s",
             encodeURL(mp->url) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "name=\"title\"" );
        if ( p ) {
            p += 12;
            p = strstr( p, "value=\"" );
            if ( p ) {
                char    *q;

                p += 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( orig_title, p, q - p );
                    orig_title[q - p] = NUL;
                }
            }
        }
    }
    if ( orig_title[0] == NUL ) {
        p = any2utf( mp->title );
        strcpy( orig_title, p ? p : mp->title );
    }

    strcpy( url, "http://clip.livedoor.com/clip/edit" );
    sprintf( request,
             "postkey=%s&"
             "title=%s&",
             postkey,
             encodeURLex2(orig_title) );
    sprintf( request + strlen(request),
             "link=%s&"
             "jump=myclip&",
             encodeURL(mp->url) );

    p = any2utf(mp->title);
    sprintf( request + strlen(request),
             "my_title=%s&"
             "rate=%d&",
             encodeURLex2( p ? p : mp->title ),
             rate );

    p = any2utf(mp->tags);
    sprintf( request + strlen(request),
             "tags=%s&",
             encodeURL( p ? p : mp->tags ) );

    p = any2utf(mp->comment);
    sprintf( request + strlen(request),
             "notes=%s&"
             "public=%s&",
             encodeURLex( p ? p : mp->comment ),
             mp->publication == PUB_PRIVATE ? "off" : "on" );

    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL(sjis2utf("クリップ！")) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        ret = TRUE;
        errorString[0] = NUL;
    }

    free( response );
    free( request );

    return ( ret );
}


typedef struct paramPutLC   {
    const char  *userName;
}   PARAM_LC;

BOOL
_putLivedoorClip(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_LC    *param = (PARAM_LC *)(args->args);
    char        url[MAX_URLLENGTH * 4];
    char        *p, *q;
    char        postkey[MAX_KEYLENGTH];
    char        tmpTitle[2048];
    long        rate;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    rate = 0;

    /* postkey を取得 */
    p = encodeURL( mp->url );
    sprintf( url,
             "http://clip.livedoor.com/clip/add?link=%s",
             p );
    sprintf( url + strlen(url),
             "&jump=%s",
             p );
    sprintf( url + strlen(url),
             "&title=%s",
             encodeURL( mp->title ) );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response,
                 "<input type=\"hidden\" name=\"postkey\" value=\"" );
        if ( p ) {
            p += 43;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( postkey, p, q - p );
                postkey[q - p] = NUL;

                /* ブックマークを POST */
                strcpy( url, "http://clip.livedoor.com/clip/add" );

                p = any2utf( mp->title );
                strcpy( tmpTitle, p ? p : mp->title );

                // MM/Memo 形式の title を扱うための処理
                rate = getEvaluation( tmpTitle, UTF8 );
                q = tmpTitle;
                if ( rate == 0 )
                    if ( (mp->evaluation >= EVL_ONE)  &&
                         (mp->evaluation <= EVL_FIVE)    )
                        rate = mp->evaluation;

                sprintf( request,
                         "title=%s&",
                         encodeURLex2( q ) );

                sprintf( request + strlen(request),
                         "postkey=%s&"
                         "link=%s&",
                         postkey,
                         encodeURL( mp->url ) );

                p = any2utf( mp->tags );
                sprintf( request + strlen(request),
                         "tags=%s&",
                         encodeURL( p ? p : mp->tags ) );

                p = any2utf( mp->comment );
                sprintf( request + strlen(request),
                         "notes=%s&"
                         "public=%s&"
                         "r18=0&",
                         encodeURLex( p ? p : mp->comment ),
                         mp->publication == PUB_PRIVATE ? "off"
                                                        : "on" );

                sprintf( request + strlen(request),
                         "submit=%s&",
                         encodeURL( sjis2utf("クリップ") ) );
                sprintf( request + strlen(request),
                         "jump=%s&"
                         "form=",
                         encodeURL( mp->url ) );

                setUpReceiveBuffer( response, sz );
                http_postEx( url, "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response ) {
                    p = strstr( response,
                                "<form action=\"/clip/delete\"" );
                    q = strstr( response,
                                sjis2utf("に登録済み</span>") );
                    if ( p && q && (p < q) ) {
#ifndef WIN32
# ifndef IDNO
#  define IDNO  FALSE
#  define IDYES TRUE
# endif /* !IDNO  */
#endif  /* !WIN32 */
                        int     r = IDNO;
                        int     fd = fileno( stderr );
                        LCID    l = getLanguageCode();

                        strcpy( errorString,
                                l == 0x0411
                                 ? "そのWebページは、すでにlivedoorクリップに"
                                   "登録済みです。"
                                 : "this web page was already registered by"
                                   " you." );
#ifdef  WIN32
                        if ( (fd >= 0) && isatty( fd ) )
                            r = IDNO;
                        else
                            r = MessageBox(
                                    NULL,
                                    l == 0x0411
                                     ? "当該Webページは既に登録済みです。    "
                                       "\r\n登録内容を上書きしますか?"
                                     : "This web page was already registered "
                                       "by you.    \r\n"
                                       "Overwrite this bookmark?",
                                    l == 0x0411
                                     ? "上書き確認 (livedoorクリップ)"
                                     : "Overwrite bookmark (livedoor clip)",
                                    MB_YESNO|MB_ICONQUESTION );
#endif
                        if ( r == IDYES )
                            editLivedoorClip( mp, rate, postkey, cookie,
                                              errorString );
                    }
                    else {
                        if ( rate > 0 )
                            setRateOnLivedoorClip( param->userName,
                                                   mp->url,
                                                   rate, cookie );
                    }

                    ret = TRUE; /* 登録成功 */
                }
            }
        }
    }

    return ( ret );
}

void
putLivedoorClip(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t      cookieSize = MAX_COOKIE_LEN;
    char        cookie[MAX_COOKIE_LEN + 1];
    int         ret;
    PARAM_LC    param;

    param.userName = userName;
    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* livedoor Clip に login */
    ret = loginLivedoorClip( userName, password, cookie );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "livedoorクリップ",
                      mp, numOfClips, cookie, cookieSize, &param,
                      _putLivedoorClip );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "livedoor への login に失敗しました\n"
                    : "livedoor clip: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "livedoor へのログインに失敗しました。  "
                         : "livedoor clip: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_LIVEDOOR_CLIP_EXE
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
                 "putLC: OPML → livedoorクリップ 登録ツール\n" );
        fprintf( stderr,
    "    putLC [-x] -u ユーザ名 -p パスワード [-i OPMLファイル名]\n" );
        fprintf( stderr,
    "\t-x: proxy を使う\n"
    "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putLC: read bookmarks from OPML, and put them into livedoor clip\n" );
        fprintf( stderr,
      "    putLC [-x] -u username -p password [-i OPMLfilename]\n" );
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
        /* ブックマークを livedoorクリップ に登録 */
        putLivedoorClip( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_LIVEDOOR_CLIP_EXE */

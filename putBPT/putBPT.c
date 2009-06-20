/*
 * clip loader <<putBPT>>
 *
 *      OPML → BlogPeople Tags 登録プログラム
 *          written by H.Tsujimura  17 Oct 2005
 *
 * $Log: /comm/bookey/putBPT/putBPT.c $
 * 
 * 1     09/05/14 4:31 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 34    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 33    07/09/04 22:05 Tsujimura543
 * setVerbose() の第2引数追加に伴う変更
 * 
 * 32    07/01/23 16:42 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 31    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 30    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 29    06/11/17 19:38 Tsujimura543
 * getEvaluation() を導入。title が MM/Memo 形式であれば、正規化してから
 * 登録するようにしてみた
 * 
 * 28    06/11/13 17:27 Tsujimura543
 * 2006年11月1日(もしくは2006年10月31日?)時点でのloginシーケンス変更に対応
 * 
 * 27    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 26    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 25a   06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 25    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 24    06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 23    06/05/22 16:49 Tsujimura543
 * Sleep() するタイミングを再調整
 * 
 * 22    06/05/22 15:30 Tsujimura543
 * (1) メモリオーバーラン対策を実施
 * (2) 登録実行時の Sleep() のタイミング、sleepする時間の長さを調整
 * 
 * 21    06/05/19 16:45 Tsujimura543
 * BlogPeople Tags の cookie 回りの扱いが変わった(2006年5月13日以降)
 * 影響でブックマークが登録できなくなっていたのを、登録できるように対処
 * した
 * 
 * 20    06/02/22 17:16 Tsujimura543
 * メモリ解放抜け対処
 * 
 * 19    06/02/22 17:14 Tsujimura543
 * &raquo; 対策を実施
 * 
 * 18    05/12/07 20:39 Tsujimura543
 * MM/Memo 形式の title かどうか判断する処理周りを改良
 * 
 * 17    05/12/07 20:03 Tsujimura543
 * ブックマーク対象のWebページのtitleに "『" と "』" が含まれる場合、
 * MM/Memo 形式の title だと誤認されてしまう可能性を極力減らすように
 * してみた
 * 
 * 16    05/11/11 1:13 Tsujimura543
 * 動作確認終了
 * 
 * 15    05/11/11 1:11 Tsujimura543
 * MM/Memo 互換形式の場合しか title が正しく取得できなくなっていた不具合
 * を修正
 * 
 * 14    05/11/02 16:26 Tsujimura543
 * MM/Memo の「評価」、「種類」を取り込めるようにした
 * 
 * 13    05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 12    05/10/29 1:12 Tsujimura543
 * ブックマーク登録時に使用する処理を各々見直した(動作確認済み)
 * 
 * 11    05/10/25 14:22 Tsujimura543
 * メッセージボックスのタイトルと本文の文言が逆になっていたのを修正
 * 
 * 10    05/10/25 14:12 Tsujimura543
 * 標準エラー出力が対話に利用可能かどうかを調査する方法を修正
 * 
 * 9     05/10/20 23:39 Tsujimura543
 * (1) format ストリング脆弱性バグを修正 (2件)
 * (2) ブックマーク登録失敗時のリトライ処理を追加
 * 
 * 8     05/10/20 21:13 Tsujimura543
 * 入力の文字コードが Shift_JIS, EUC-JP, UTF-8 のどれでもいいようにした
 * 
 * 7     05/10/20 16:06 Tsujimura543
 * usage() で表示する文言を再度修正 (修正し忘れた箇所が残っていた)
 * 
 * 6     05/10/19 17:28 Tsujimura543
 * putBlogPeopleTags() のリターン値を int から BOOL に変更
 * 
 * 5     05/10/18 14:31 Tsujimura543
 * putBPT() → putBPTags() に名称変更
 * 
 * 4     05/10/18 13:49 Tsujimura543
 * encodeURL( NULL ); を実行する場所を変更
 * 
 * 3     05/10/18 13:46 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 2     05/10/18 13:43 Tsujimura543
 * (1) loginBlogPeople() をファイル内から削除。blogPeople.c のものを参照する
 *     ようにした
 * (2) putBookmark() を putBlogPeopleTags() に名称変更
 * 
 * 1     05/10/18 0:38 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBPT/putBPT.c 1     09/05/14 4:31 tsupo $";
#endif

BOOL
_putBlogPeopleTags(
        char       *cookie,
        char       *request,
        char       *response,
        size_t     sz,
        const char *url,
        const char *title,
        const char *comment
    )
{
    BOOL    ret = FALSE;

    strcpy( request, "http://tags.blogpeople.net/tags_addlink.jsp" );
    sprintf( request + strlen( request ),
             "?u=%s&",
             encodeURL( url ) );
    sprintf( request + strlen( request ),
             "ti=%s&",
             encodeURLex4( title ) );
    sprintf( request + strlen( request ),
             "de=%s",
             encodeURL( comment ) );

    setUpReceiveBuffer( response, sz );
    http_getEx( request, response, cookie );
    if ( !response || !(response[0]) )
        encodeURL( NULL );
    else
        ret = TRUE;

    return ( ret );
}


typedef struct paramPutBPT  {
    const char  *userName;
    const char  *password;
}   PARAM_BPT;

BOOL
putBlogPeopleTags(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    PARAM_BPT   *param    = (PARAM_BPT *)(args->args);
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    const char  *userName = param->userName;
    const char  *password = param->password;
    char        url[1024];
    char        imgURL[MAX_URLLENGTH];
    char        tmpURL[BUFSIZ];
    char        tmpTitle[BUFSIZ];
    char        tmpTags[180];
    char        tmpComment[2048];
    char        category[8];
    char        calist[BUFSIZ];
    const char  *p, *q;
    char        cookie2[MAX_COOKIE_LEN];
    long        rate = 0;
    BOOL        ret  = FALSE;

    errorString[0] = NUL;
    category[0]    = NUL;
    request[0]     = NUL;

    strcpy( tmpURL, mp->url );

    // MM/Memo 形式の title を扱うための処理
    strcpy( tmpTitle, mp->title );
    rate = getEvaluation( tmpTitle, SJIS2UTF );
    if ( rate == 0 )
        if ( (mp->evaluation >= EVL_ONE) && (mp->evaluation <= EVL_FIVE) )
            rate = mp->evaluation;

    p = utf2sjis( mp->tags );
    if ( !p )
        p = euc2sjis( mp->tags );
    strcpy( tmpTags,    p ? p : mp->tags );

    p = utf2sjis( mp->comment );
    if ( !p )
        p = euc2sjis( mp->comment );
    strcpy( tmpComment, p ? p : mp->comment );

    ret = _putBlogPeopleTags( cookie, request, response, sz,
                              tmpURL, tmpTitle, tmpComment );
    if ( ret == FALSE )
        return ( ret );

    if ( strstr( response, "value=\"ログイン\"" ) ) {
        // BlogPeople にログイン
        ret = FALSE;
        memset( cookie2, 0x00, MAX_COOKIE_LEN );
        strcpy( url, "http://member.blogpeople.net/member/member_index.jsp" );
        sprintf( request,
                 "user_id=%s&passwd=%s&autologin=1&",
                 userName, password );
        sprintf( request + strlen( request ),
                 "Submit=%s&opt=1&url=",
                 encodeURL( "　ログイン　" ) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie2 );
        if ( !response || !(response[0]) ) {
            encodeURL( NULL );
            return ( ret );
        }

        imgURL[0] = NUL;
        p = strstr( response, "<img src=\"" );
        if ( p ) {
            p += 10;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( imgURL, p, q - p );
                imgURL[q - p] = NUL;
            }
        }

        if ( imgURL[0] ) {  // 2006年11月1日以降の新loginシーケンス対応
            memset( cookie2, 0x00, MAX_COOKIE_LEN );
            setUpReceiveBuffer( response, sz );
            http_getEx( imgURL, response, cookie2 );
            if ( !response || !(response[0]) ) {
                encodeURL( NULL );
                return ( ret );
            }
        }

        if ( cookie2[0] ) {
            strcpy( cookie, cookie2 );
            ret = _putBlogPeopleTags( cookie, request, response, sz,
                                      tmpURL, tmpTitle, tmpComment );
        }

        if ( ret == FALSE )
            return ( ret );
    }

    if ( category[0] )
        strcpy( calist, category );
    else {
        // calist 取得
        calist[0] = NUL;
        p = strstr( response, "<select name=\"calist\"" );
        if ( p ) {
            q = strstr( p + 21, "<option value=\"" );
            if ( q ) {
                p = q + 15;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( calist, p, q - p );
                    calist[q - p] = NUL;
                }
            }
        }
        if ( calist[0] == NUL )
            strcpy( calist, "bookey" ); /* 暫定 */
    }

    strcpy( url, "http://tags.blogpeople.net/tags_addlink.jsp" );
    sprintf( request,
             "calist=%s&",
             encodeURL( calist ) );
    sprintf( request + strlen( request ),
             "ca=%s&",
             encodeURL( calist ) );
    sprintf( request + strlen( request ),
             "u=%s&",
             encodeURL( tmpURL ) );
    sprintf( request + strlen( request ),
             "ti=%s&",
             encodeURLex4( tmpTitle ) );
    sprintf( request + strlen( request ),
             "tag=%s&",
             encodeURL( tmpTags ) );
    sprintf( request + strlen( request ),
             "desc=%s&"
             "myrate=%d&",
             encodeURL( tmpComment ),
             rate );
    sprintf( request + strlen( request ),
             "submit=%s",
             encodeURL( "追加" ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    ret = response && response[0] ? TRUE : FALSE;
    encodeURLex4( NULL );

    return ( ret );
}


void
putBPTags(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t      cookieSize = MAX_COOKIE_LEN;
    char        cookie[MAX_COOKIE_LEN + 1];
    PARAM_BPT   param;

    param.userName = userName;
    param.password = password;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    putBookmarks( "BlogPeople Tags",
                  mp, numOfClips, cookie, cookieSize, &param,
                  putBlogPeopleTags );
}



#ifdef  PUT_BLOGPEOPLE_TAGS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForHatena,
        char *passwordForHatene,
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
                        strcpy( usernameForHatena, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForHatena, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForHatene, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForHatene, argv[i] );
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
        fprintf( stderr, "putBPT: OPML → BlogPeople Tags 登録ツール\n" );
        fprintf( stderr,
                 "    putBPT [-x] -u BlogPeopleログイン用メールアドレス\n"
                 "                -p パスワード [-i OPMLファイル名]\n" );
        fprintf( stderr,
            "\t-x: proxy を使う\n"
            "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
     "putBPT: read bookmarks from OPML, and put them into BlogPeople Tags\n");
        fprintf( stderr,
     "    putBPT [-x] -u mailaddress -p password [-i OPMLfilename]\n" );
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

#ifdef  _DEBUG
    setVerbose( TRUE, stderr );
#endif
    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを BlogPeople Tags に登録 */
        putBPTags( username, password, mp, numOfClips );
        free( mp );
        encodeURL( NULL );      // 領域解放
        encodeURLex4( NULL );   // 領域解放
    }

    return ( 1 );
}
#endif  /* PUT_BLOGPEOPLE_TAGS_EXE */

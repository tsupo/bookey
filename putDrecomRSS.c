/*
 * clip loader <<putDrecomRSS>>
 *
 *      OPML → ドリコムRSS-Clip 登録プログラム
 *          written by H.Tsujimura  28 Mar 2006
 *
 * History:
 * $Log: /comm/bookey/putDrecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 23    07/02/15 0:29 Tsujimura543
 * getArticleIDbyURL() を getArticleIDbyURLonDrecomRSS() に名称変更
 * 
 * 22    07/02/08 16:52 Tsujimura543
 * コマンドライン版のビルド時は「上書き機能」を組み込まないようにする
 * 
 * 21    07/02/05 21:41 Tsujimura543
 * ソースを整理
 * 
 * 20    07/02/05 21:40 Tsujimura543
 * getArticleIDbyURL() の引数を追加。フォルダ番号がわかっている場合は
 * 記事IDの発見に要する時間を短縮できるようになった
 * 
 * 19    07/02/05 20:03 Tsujimura543
 * 上書き確認メッセージボックスのタイトルの文言を変更
 * 
 * 18    07/02/05 18:22 Tsujimura543
 * すでに登録済みのWebページを再度登録しようとしている場合は、
 * 上書きするかどうか質問した上で上書きを実行するようにした
 * 
 * 17    07/01/23 21:01 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 16    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 15    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 14    06/10/05 22:33 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 13    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 13a   06/09/03 20:17 tsupo
 * cookie まわりを修正
 * 
 * 12    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 11    06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 10    06/07/18 20:45 Tsujimura543
 * ログイン失敗時にエラーダイアログを出すようにした
 * 
 * 9     06/05/22 16:49 Tsujimura543
 * Sleep() するタイミングを再調整
 * 
 * 8     06/05/22 15:30 Tsujimura543
 * 登録実行時の Sleep() のタイミング、sleepする時間の長さを調整
 * 
 * 7     06/03/29 18:29 Tsujimura543
 * getFolderNumber() の返す値の default 値を 1 (Internet) とする
 * 
 * 6     06/03/28 17:05 Tsujimura543
 * loginDrecomRSS() を drecomRSS.c へ分離
 * 
 * 5     06/03/28 16:54 Tsujimura543
 * putDrecomRSS() を呼び出す前に、あらかじめ UTF-8 に変換されていることを前提
 * とする仕様に変更した (他のブックマークサービス用の putXXX() と仕様を合わせ
 * るため)
 * 
 * 4     06/03/28 15:59 Tsujimura543
 * 不要な処理を削除
 * 
 * 3     06/03/28 15:55 Tsujimura543
 * 動作確認完了
 * 
 * 2     06/03/28 15:46 Tsujimura543
 * http://rss.drecom.jp/shortcut/add_clip を GET する処理を実行する
 * 必要がないことを確認。削除した
 * 
 * 1     06/03/28 15:38 Tsujimura543
 * 最初の版
 */

#include "myClip.h"
#include "getDrecomRSS.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDrecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif


int
getFolderNumber( const char *folderName )
{
    int folderNumber = 1; /* default */

    if ( strstr( folderName, "Internet" ) )
        folderNumber = 1;
    else if ( strstr( folderName, "entertainment" ) )
        folderNumber = 2;
    else if ( strstr( folderName, "science" ) )
        folderNumber = 3;
    else if ( strstr( folderName, "region" ) )
        folderNumber = 4;
    else if ( strstr( folderName, "social" ) )
        folderNumber = 5;
    else if ( strstr( folderName, "column" ) )
        folderNumber = 6;
    else if ( strstr( folderName, "news-of-death" ) )
        folderNumber = 7;
    else if ( strstr( folderName, "culture" ) )
        folderNumber = 8;
    else if ( strstr( folderName, "blog" ) )
        folderNumber = 9;
    else if ( strstr( folderName, "economy" ) )
        folderNumber = 10;
    else if ( strstr( folderName, "politics" ) )
        folderNumber = 11;
    else if ( strstr( folderName, "sport" ) )
        folderNumber = 12;
    else if ( strstr( folderName, "book-review" ) )
        folderNumber = 13;
    else if ( strstr( folderName, "international" ) )
        folderNumber = 14;
    else if ( strstr( folderName, "technology" ) )
        folderNumber = 15;

    return ( folderNumber );
}


BOOL
_putDrecomRSS(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    url[MAX_URLLENGTH];
    int     folderNumber;
    BOOL    ret = FALSE;

    errorString[0] = NUL;
    folderNumber   = getFolderNumber(mp->tags);

    strcpy( url, "http://rss.drecom.jp/shortcut/add_clip_done" );
    sprintf( request,
             "clip_title=%s&",
             encodeURL(mp->title) );
    sprintf( request + strlen(request),
             "clip_url=%s&",
             encodeURL(mp->url) );
    sprintf( request + strlen(request),
             "clip_folder=%d&",
             folderNumber );
    sprintf( request + strlen(request),
             "clip_comment=%s&",
             encodeURL(mp->comment) );
    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL(sjis2utf("登録")) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr(response, sjis2utf("既に登録しているClipです")) ) {
#ifndef PUT_DRECOM_RSS_EXE
# ifndef WIN32
#  ifndef IDNO
#   define IDNO  FALSE
#   define IDYES TRUE
#  endif /* !IDNO  */
# endif  /* !WIN32 */
            int     r = IDNO;
            int     fd = fileno( stderr );
#endif  /* !PUT_DRECOM_RSS_EXE */
            LCID    l = getLanguageCode();

            strcpy( errorString,
                    l == 0x0411
                     ? "当該Webページは既に登録済みです"
                     : "this web page was already registered by you." );

#ifndef PUT_DRECOM_RSS_EXE
# ifdef  WIN32
            if ( (fd >= 0) && isatty( fd ) )
                r = IDNO;
            else
                r = MessageBox(
                        NULL,
                        l == 0x0411
                         ? "当該Webページは既に登録済みです。    \r\n"
                           "登録内容を上書きしますか?"
                         : "This web page was already registered by you."
                           "    \r\nOverwrite this bookmark?",
                        l == 0x0411
                         ? "上書き確認 (ドリコムRSS)"
                         : "Overwrite bookmark (Drecom RSS)",
                        MB_YESNO|MB_ICONQUESTION );
# endif

            if ( r == IDYES ) {
                char    articleID[64];

                articleID[0] = NUL;
                getArticleIDbyURLonDrecomRSS( mp->url, folderNumber, cookie,
                                              articleID );
                if ( articleID[0] ) {
                    /* ブックマーク登録内容の修正 */
                    errorString[0] = NUL;
                    editDrecomRSS( mp, articleID, cookie, errorString );
                }
            }
#endif  /* !PUT_DRECOM_RSS_EXE */
        }

        ret = TRUE;
    }

    return ( ret );
}

void
putDrecomRSS(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* ドリコムRSS に login */
    ret = loginDrecomRSS( userName, password, cookie );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( getLanguageCode() == 0x0411
                       ? "ドリコムRSS"
                       : "Drecom RSS",
                      mp, numOfClips, cookie, cookieSize, NULL,
                      _putDrecomRSS );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "ドリコムRSSへの login に失敗しました\n"
                    : "Drecom RSS: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "ドリコムRSSへのログインに失敗しました。  "
                         : "Drecom RSS: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_DRECOM_RSS_EXE
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
                 "putDRC: OPML → Drecom RSS の Clip! 登録ツール\n" );
        fprintf( stderr,
     "    putDRC [-x] -u メールアドレス -p パスワード [-i OPMLファイル名]\n");
        fprintf( stderr,
     "\t-x: proxy を使う\n"
     "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
  "putDRC: read bookmarks from OPML, and put them into Drecom RSS (Clip!)\n");
        fprintf( stderr,
      "    putDRC [-x] -u mailaddress -p password [-i OPMLfilename]\n" );
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
        /* ブックマークを Drecom RSS の Clip! に登録 */
        putDrecomRSS( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_DRECOM_RSS_EXE */

/*
 * clip loader <<putMMmemo>>
 *
 *      OPML → MM/Memo 登録プログラム
 *          written by H.Tsujimura  19 Oct 2005
 *
 * $Log: /comm/bookey/putMMmemo/putMMmemo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 32    07/11/12 21:55 Tsujimura543
 * adjustStringLength() を myClip.c へ移管
 * 
 * 31    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 30    07/09/04 22:05 Tsujimura543
 * setVerbose() の第2引数追加に伴う変更
 * 
 * 29    07/07/02 16:34 Tsujimura543
 * http://1470.net/mm/ → http://mmmemo.1470.net/mm/ に変更
 * (変更しないと登録に失敗する[登録しようとしているURLが無効、と表示
 *  される]ことが判明)
 * 
 * 28    07/01/23 16:42 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 27    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 26    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 25    06/11/17 19:38 Tsujimura543
 * getEvaluation() を導入。title が MM/Memo 形式であれば、正規化してから
 * 登録するようにしてみた
 * 
 * 24    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 23    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 22a   06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 22    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 21    06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 20    06/07/07 13:36 Tsujimura543
 * コメントを修正
 * 
 * 19    06/06/28 21:39 Tsujimura543
 * ブックマーク対象元WebページのcharsetがEUC-JPでかつタイトルが128バイト
 * より大きいとき、空のタイトルで登録しようとしてしまう不具合に対処
 * 
 * 18    06/06/05 22:10 Tsujimura543
 * MM/Memo のタグ(ジャンル)の最大許容バイト数(80バイト)を超える部分は
 * 除去・削除してから、登録を実行するようにした
 * 
 * 17    06/05/22 16:49 Tsujimura543
 * Sleep() するタイミングを再調整
 * 
 * 16    06/05/22 15:30 Tsujimura543
 * 登録実行時の Sleep() のタイミング、sleepする時間の長さを調整
 * 
 * 15    06/02/22 16:47 Tsujimura543
 * &raquo; 対策を実施
 * 
 * 14    05/12/07 20:39 Tsujimura543
 * MM/Memo 形式の title かどうか判断する処理周りを改良
 * 
 * 13    05/12/07 20:03 Tsujimura543
 * ブックマーク対象のWebページのtitleに "『" と "』" が含まれる場合、
 * MM/Memo 形式の title だと誤認されてしまう可能性を極力減らすように
 * してみた
 * 
 * 12    05/11/02 18:00 Tsujimura543
 * memo_kind が反映されない不具合を修正 (Date_Day=xx の直後の & が
 * 抜けていた)
 * 
 * 11    05/11/02 15:31 Tsujimura543
 * getStringImplanted() を getString.c へ分離、独立させた
 * 
 * 10    05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 9     05/10/29 1:12 Tsujimura543
 * ブックマーク登録時に使用する処理を各々見直した(動作確認済み)
 * 
 * 8     05/10/25 15:00 Tsujimura543
 * (1) アマゾンの商品個別ページのブックマークに失敗する不具合を修正
 * (2) ブックマーク対象のWebページが Shift_JIS または EUC-JP の場合、
 *     ブックマーク登録後のタイトルが期待通りのものにならないことがある
 *     不具合を修正
 * 
 * 7     05/10/25 14:22 Tsujimura543
 * メッセージボックスのタイトルと本文の文言が逆になっていたのを修正
 * 
 * 6     05/10/25 14:12 Tsujimura543
 * 標準エラー出力が対話に利用可能かどうかを調査する方法を修正
 * 
 * 5     05/10/24 20:37 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 4     05/10/24 20:34 Tsujimura543
 * タイトルが128バイトより大きい場合の対策を実施
 * 
 * 3     05/10/20 23:39 Tsujimura543
 * ブックマーク登録失敗時のリトライ処理を追加
 * 
 * 2     05/10/20 21:13 Tsujimura543
 * 入力の文字コードが Shift_JIS, EUC-JP, UTF-8 のどれでもいいようにした
 * 
 * 1     05/10/20 20:08 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putMMmemo/putMMmemo.c 1     09/05/14 3:48 tsupo $";
#endif


BOOL
_putMMmemo(
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
    char        checkKey[32 + 1];
    char        webpageID[16];
    char        asin[16];
    char        tmpTitle[BUFSIZ];
    char        tmpTags[180];
    char        tmpComment[2048];
    const char  *p;
    char        *q;
    BOOL        ret  = FALSE;
    int         rate = 0;
    int         len;

    errorString[0] = NUL;

    // check_key と webpageID もしくは asin を取得
    checkKey[0]  = NUL;
    webpageID[0] = NUL;
    asin[0]      = NUL;

    sprintf( url, "http://mmmemo.1470.net/mm/memo_form.html?url=%s",
             encodeURL( mp->url ) );

    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( !p || !(*p) )
        return ( ret );

    getStringImplanted( checkKey,  p, "name=\"check_key\" value=\"", "\"" );
    getStringImplanted( webpageID, p, "name=\"webpage\" value=\"",   "\"" );
    getStringImplanted( asin,      p, "name=\"asin\" value=\"",   "\"" );
    if ( !(checkKey[0]) || (!(webpageID[0]) && !(asin[0])) )
        return ( ret );

    // ブックマークを登録
    strcpy( url, "http://mmmemo.1470.net/mm/memo_form.html" );

    // MM/Memo 形式の title を扱うための処理
    strcpy( tmpTitle, mp->title );
    rate = getEvaluation( tmpTitle, EUC2UTF );
    p = tmpTitle;

    // MM/Memo の「タイトル」は128バイト以内にする必要あり
    len = strlen( p );
    if ( len > 128 ) {
        const char  *q;

        q = euc2sjis( p );
        if ( q )
            strcpy( tmpTitle, q );
        adjustStringLength( tmpTitle, 128 );
        p = sjis2euc( tmpTitle );
        if ( !p )
            p = tmpTitle;
    }

    sprintf( request,
             "memo=&"
             "check_key=%s&",
             checkKey );
    if ( webpageID[0] )
        sprintf( request + strlen( request ),
                 "webpage=%s&",
                 webpageID );
    else if ( asin[0] )
        sprintf( request + strlen( request ),
                 "asin=%s&",
                 asin );
    sprintf( request + strlen( request ),
             "memo_title=%s&"
             "Date_Year=%d&"
             "Date_Month=%d&"
             "Date_Day=%d&",
             encodeURLex3( p ),
             mp->yyyy, mp->mm, mp->dd );
    // -- memo_kind
    p = utf2euc( mp->title );
    if ( !p )
        p = sjis2euc( mp->title );
    strcpy( tmpTitle, p ? p : mp->title );
    if ( (tmpTitle[0] == '[') && (tmpTitle[3] == ']') )
        sprintf( request + strlen( request ),
                 "memo_kind=%%%02x%%%02x&",
                 tmpTitle[1] & 0xFF, tmpTitle[2] & 0xFF );
    else
        strcat( request, "memo_kind=&" );
    // -- memo_eval
    if ( rate > 0 )
        sprintf( request + strlen( request ),
                 "memo_eval=%d&",
                 rate );
    else if ( (mp->evaluation >= EVL_ONE) && (mp->evaluation <= EVL_FIVE) )
        sprintf( request + strlen( request ),
                 "memo_eval=%d&",
                 mp->evaluation );
    else
        strcat( request, "memo_eval=&" );
    // -- memo_genre
    p = utf2euc( mp->tags );
    if ( !p )
        p = sjis2euc( mp->tags );
    strcpy( tmpTags, p ? p : mp->tags );
    q = tmpTags;
    if ( *q ) {
        while ( *q ) {
            if ( *q == ' ' ) {
                *q = '|';

                /* 以下は bookey 0.04, 0.04a, 0.04b で getMMmemo() したブッ */
                /* クマークを putMMmemo() する場合の対策(なので、いずれは廃 */
                /* 止する)                                                  */
                while ( *(q + 1) == ' ' )
                    strcpy( q + 1, q + 2 );
            }
            q++;
        }

        // MM/Memo の「ジャンル」は80バイト以内にする必要あり
        while ( strlen( tmpTags ) > 80 ) {
            q = strrchr( tmpTags, '|' );
            if ( q )
                *q = NUL;
            else {
                adjustStringLength( tmpTags, 80 );
                break;
            }
        }

        sprintf( request + strlen( request ),
                 "memo_genre=%s&",
                 encodeURL( tmpTags ) );
    }
    else
        strcat( request, "memo_genre=&" );
    // -- memo_text
    p = utf2euc( mp->comment );
    if ( !p )
        p = sjis2euc( mp->comment );
    strcpy( tmpComment, p ? encodeURL( p ) : mp->comment );
    sprintf( request + strlen( request ),
             "memo_text=%s&"
             "memo_url=&"
             "submit_button=%s&"
             "save_copy=1",
             tmpComment, encodeURL(sjis2euc("保存する")) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    ret = response && response[0] ? TRUE : FALSE;
    encodeURLex3( NULL );

    return ( ret );
}


void
putMMmemo(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    userID[32];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    memset( userID, 0x00, 32 );

    /* MM/Memo にログイン */
    ret = loginMMmemo( userName, password, cookie, userID );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "MM/Memo", mp, numOfClips, cookie, cookieSize, NULL,
                      _putMMmemo );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "MM/Memo への login に失敗しました\n"
                    : "MM/Memo: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "MM/Memo へのログインに失敗しました。  "
                         : "MM/Memo: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}



#ifdef  PUT_MM_MEMO_EXE
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
        fprintf( stderr, "putMMmemo: OPML → MM/Memo 登録ツール\n" );
        fprintf( stderr,
                 "    putMMmemo [-x] -u TypeKey認証用ユーザ名\n"
                 "                   -p TypeKey認証用パスワード\n"
                 "                   [-i OPMLファイル名]\n" );
        fprintf( stderr,
        "\t-x: proxy を使う\n"
        "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putMMmemo: read bookmarks from OPML, and put them into MM/Memo\n" );
        fprintf( stderr,
      "    putMMmemo [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "      username: ID for TypeKey authentication\n"
      "      password: password for TypeKey authentication\n" );
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
        /* ブックマークを MM/Memo に登録 */
        putMMmemo( username, password, mp, numOfClips );
        free( mp );
        encodeURL( NULL );  // 領域解放
    }

    return ( 1 );
}
#endif  /* PUT_MM_MEMO_EXE */

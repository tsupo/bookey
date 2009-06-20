/*
 * clip loader <<putFlog>>
 *
 *      OPML → Flog 登録プログラム
 *          written by H.Tsujimura  31 May 2006
 *
 * History:
 * $Log: /comm/bookey/putFlog.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 19    08/12/02 19:37 Tsujimura543
 * メモリ解放忘れになる可能性のある箇所の修正
 * 
 * 18    07/11/12 20:55 Tsujimura543
 * any2sjisEx() を導入、Shift_JIS なのに EUC-JP だと誤認するケースに対処
 * 
 * 17    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 16    07/02/05 15:08 Tsujimura543
 * getCategoryNumber() の(Flog 独自カテゴリを使ってない場合、どの
 * カテゴリにマッピングするかに関する)仕様を変更
 * 
 * 15    07/01/23 20:28 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 14    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 13    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 12    07/01/17 22:25 Tsujimura543
 * 綴りミスを修正 oversea → overseas)
 * 
 * 11    07/01/16 15:20 Tsujimura543
 * 綴りミスを修正 (byke → bike)
 * 
 * 10    06/10/03 23:06 Tsujimura543
 * 綴りミスを修正 (catoon → cartoon) [facetさん、指摘感謝!]
 * 
 * 9     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 8a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 8     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 7     06/07/27 20:45 Tsujimura543
 * 受信電文格納領域のオーバーラン防止機能を組み込んだ
 * 
 * 6     06/07/18 21:04 Tsujimura543
 * ログイン失敗時にエラーダイアログを出すようにした
 * 
 * 5     06/06/22 18:58 Tsujimura543
 * すでに誰かが登録済みのWebページを登録しようとするとエラーになって
 * いたのを、正常に登録できるように対処した
 * 
 * 4     06/06/01 21:48 Tsujimura543
 * 登録失敗時、以降の登録を中断するかどうか尋ねるようにした
 * 
 * 3     06/05/31 21:48 Tsujimura543
 * 文字コードが Shift_JIS 以外のブックマーク(OPML)の取り込みにも
 * 対応した (というか、文字コードの問題を忘れていた)
 * 
 * 2     06/05/31 19:42 Tsujimura543
 * ジャンル(カテゴリ名)をタグで指定できるようにした
 * 
 * 1     06/05/31 19:02 Tsujimura543
 * 最初の版 (ジャンルを "1" 固定にした暫定版) [動作確認済み]
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putFlog.c 1     09/05/14 3:48 tsupo $";
#endif


int
getCategoryNumber( const char *categoryName )
{
    int cataegoryNumber = 0;

    /*
     * 1    コンピュータ
     * 2    ビジネス/政治
     * 3    ニュース
     * 4    日記
     * 5    芸能/アイドル
     * 6    ヘルス/ビューティ
     * 7    就職/転職
     * 8    グルメ
     * 9    音楽
     * 10   映画
     * 11   本/雑誌/新聞
     * 12   漫画/アニメ
     * 13   テレビ
     * 14   ゲーム
     * 15   ペット/動物
     * 16   趣味/スポーツ
     * 17   車/バイク
     * 18   くらし/家電
     * 19   旅行/地域情報
     * 20   芸術/デザイン
     * 21   教育/学問/資料
     * 22   動画/フラッシュ
     * 23   便利ツール
     * 24   まとめサイト
     * 25   ネタ/ジョーク
     * 26   恋愛
     * 27   ファッション/ブランド
     * 28   海外
     */
    /* Flog独自カテゴリ名 */
    if ( strstr( categoryName, "computer" ) )
        cataegoryNumber = 1;
    else if ( strstr( categoryName, "business" ) )
        cataegoryNumber = 2;
    else if ( strstr( categoryName, "news" ) )
        cataegoryNumber = 3;
    else if ( strstr( categoryName, "diary" ) )
        cataegoryNumber = 4;
    else if ( strstr( categoryName, "showbiz" ) )
        cataegoryNumber = 5;
    else if ( strstr( categoryName, "health" ) )
        cataegoryNumber = 6;
    else if ( strstr( categoryName, "employment" ) )
        cataegoryNumber = 7;
    else if ( strstr( categoryName, "gourmet" ) )
        cataegoryNumber = 8;
    else if ( strstr( categoryName, "music" ) )
        cataegoryNumber = 9;
    else if ( strstr( categoryName, "cinema" ) )
        cataegoryNumber = 10;
    else if ( strstr( categoryName, "print" ) )
        cataegoryNumber = 11;
    else if ( strstr( categoryName, "catoon" ) ||
              strstr( categoryName, "cartoon")    )
        cataegoryNumber = 12;
    else if ( strstr( categoryName, "tv" ) )
        cataegoryNumber = 13;
    else if ( strstr( categoryName, "game" ) )
        cataegoryNumber = 14;
    else if ( strstr( categoryName, "animal" ) )
        cataegoryNumber = 15;
    else if ( strstr( categoryName, "hobby" ) )
        cataegoryNumber = 16;
    else if ( strstr( categoryName, "car" ) )
        cataegoryNumber = 17;
    else if ( strstr( categoryName, "life" ) )
        cataegoryNumber = 18;
    else if ( strstr( categoryName, "travel" ) )
        cataegoryNumber = 19;
    else if ( strstr( categoryName, "art" ) )
        cataegoryNumber = 20;
    else if ( strstr( categoryName, "education" ) )
        cataegoryNumber = 21;
    else if ( strstr( categoryName, "movie" ) )
        cataegoryNumber = 22;
    else if ( strstr( categoryName, "tool" ) )
        cataegoryNumber = 23;
    else if ( strstr( categoryName, "summarySite" ) )
        cataegoryNumber = 24;
    else if ( strstr( categoryName, "neta" ) )
        cataegoryNumber = 25;
    else if ( strstr( categoryName, "love" ) )
        cataegoryNumber = 26;
    else if ( strstr( categoryName, "fashion" ) )
        cataegoryNumber = 27;
    else if ( strstr( categoryName, "overseas") ||
              strstr( categoryName, "oversea" )    )
        cataegoryNumber = 28;

    if ( cataegoryNumber == 0 ) {
        /* ドリコムRSS互換カテゴリ名 */
        if ( strstr( categoryName, "Internet" ) )
            cataegoryNumber = 1;    /* → コンピュータ   */
        else if ( strstr( categoryName, "entertainment" ) )
            cataegoryNumber = 3;    /* → ニュース       */
        else if ( strstr( categoryName, "science" ) )
            cataegoryNumber = 21;   /* → 教育/学問/資料 */
        else if ( strstr( categoryName, "region" ) )
            cataegoryNumber = 19;   /* → 旅行/地域情報  */
        else if ( strstr( categoryName, "social" ) )
            cataegoryNumber = 3;    /* → ニュース       */
        else if ( strstr( categoryName, "column" ) )
            cataegoryNumber = 21;   /* → 教育/学問/資料 */
        else if ( strstr( categoryName, "news-of-death" ) )
            cataegoryNumber = 3;    /* → ニュース       */
        else if ( strstr( categoryName, "culture" ) )
            cataegoryNumber = 8;    /* → 芸能/アイドル  */
        else if ( strstr( categoryName, "blog" ) )
            cataegoryNumber = 4;    /* → 日記           */
        else if ( strstr( categoryName, "economy" ) )
            cataegoryNumber = 2;    /* → ビジネス/政治  */
        else if ( strstr( categoryName, "politics" ) )
            cataegoryNumber = 2;    /* → ビジネス/政治  */
        else if ( strstr( categoryName, "sport" ) )
            cataegoryNumber = 16;   /* → 趣味/スポーツ  */
        else if ( strstr( categoryName, "book-review" ) )
            cataegoryNumber = 11;   /* → 本/雑誌/新聞   */
        else if ( strstr( categoryName, "international" ) )
            cataegoryNumber = 28;   /* → 海外           */
        else if ( strstr( categoryName, "technology" ) )
            cataegoryNumber = 21;   /* → 教育/学問/資料 */
    }

    if ( cataegoryNumber == 0 ) {
        /* その他 */
        if ( strstr( categoryName, "books" ) )
            cataegoryNumber = 11;   /* → 本/雑誌/新聞   */
        else if ( strstr( categoryName, "comics" ) )
            cataegoryNumber = 12;   /* → 漫画/アニメ    */
        else if ( strstr( categoryName, "anime" ) )
            cataegoryNumber = 12;   /* → 漫画/アニメ    */
        else if ( strstr( categoryName, "foods" ) )
            cataegoryNumber = 8;    /* → グルメ         */
        else if ( strstr( categoryName, "magazine" ) )
            cataegoryNumber = 11;   /* → 本/雑誌/新聞   */
        else if ( strstr( categoryName, "newspaper" ) )
            cataegoryNumber = 11;   /* → 本/雑誌/新聞   */
        else if ( strstr( categoryName, "bike" ) )
            cataegoryNumber = 17;   /* → 車/バイク      */
    }

    if ( cataegoryNumber == 0 )
        cataegoryNumber = 1;    /* default */;

    return ( cataegoryNumber );
}

BOOL
_putFlog(
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
    BOOL    ret = FALSE;

    errorString[0] = NUL;

    /* まず、URL を POST */
    strcpy( url, "http://www.flog.jp/post.php" );
    sprintf( request,
             "url_uri=%s&",
             encodeURL(mp->url) );
    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL("次へ") );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        const char  *p, *q;
        char        *buffer = (char *)malloc( MAX_CONTENT_SIZE );

        p = strstr( response, "ブックマークに投稿します" );
        if ( !p )
            p = strstr( response, "ブックマークを追加する" );
        if ( p ) {
            char    domain[80];
            char    name[80];
            char    tag[3][80];
            int     cnt = 0;
            int     i;

            p = mp->url;
            q = strchr( p + 8, '/' );
            if ( q ) {
                strncpy( domain, p, q - p );
                domain[q - p] = NUL;
            }
            else
                strcpy( domain, mp->url );

            p = strstr( cookie, "NAME=" );
            if ( p ) {
                p += 5;
                strcpy( name, p );
            }
            else
                name[0] = NUL;

            tag[0][0] = NUL;
            tag[1][0] = NUL;
            tag[2][0] = NUL;
            p = mp->tags;
            do {
                q = strchr( p, ' ' );
                if ( q ) {
                    strncpy( tag[cnt], p, q - p );
                    tag[cnt][q - p] = NUL;
                    cnt++;
                    if ( cnt >= 3 )
                        break;
                    p = q + 1;
                }
                else {
                    strcpy( tag[cnt], p );
                    break;
                }
            } while ( *p );

            memset( request,  0x00, MAX_CONTENT_SIZE );
            strcpy( url, "http://www.flog.jp/post.php" );
            sprintf( request,
                     "plot=1&"
                     "url_uri=%s&",
                     encodeURL(mp->url) );
            sprintf( request + strlen(request),
                     "url_domain=%s&",
                     encodeURL(domain) );

            /* 名前 */
            if ( name[0] )
                sprintf( request + strlen(request),
                         "url_postuser=%s&",
                         encodeURL(name) );
            else
                strcat( request, "url_postuser=&" );

            /* ジャンル */
            sprintf( request + strlen(request),
                     "url_category=%d&",
                     getCategoryNumber(mp->tags) );

            /* サイト名 */
            if ( buffer ) {
                buffer[0] = NUL;
                p = any2sjisEx( buffer, mp->title );
            }
            else {
                p = utf2sjis( mp->title );
                if ( !p )
                    p = euc2sjis( mp->title );
            }
            sprintf( request + strlen(request),
                     "url_title=%s&",
                     encodeURL(p ? p : mp->title) );

            /* キーワード (最大3個まで) */
            for ( i = 0; i <= 2; i++ ) {
                if ( tag[i] ) {
                    if ( buffer ) {
                        buffer[0] = NUL;
                        p = any2sjisEx( buffer, tag[i] );
                    }
                    else {
                        p = utf2sjis( tag[i] );
                        if ( !p )
                            p = euc2sjis( tag[i] );
                    }
                    sprintf( request + strlen(request),
                             "userpage_label%d=%s&",
                             i + 1,
                             encodeURL(p ? p : tag[i]) );
                }
                else
                    sprintf( request + strlen(request),
                             "userpage_label%d=&",
                             i + 1 );
            }

            /* コメント */
            if ( buffer ) {
                buffer[0] = NUL;
                p = any2sjisEx( buffer, mp->comment );
            }
            else {
                p = utf2sjis( mp->comment );
                if ( !p )
                    p = euc2sjis( mp->comment );
            }
            sprintf( request + strlen(request),
                     "url_comment=%s&",
                     encodeURL(p ? p : mp->comment) );

            sprintf( request + strlen(request),
                     "submit=%s&"
                     "posted=&"
                     "origin=",
                     encodeURL("ブックマークを投稿する") );

            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

            if ( *response ) {
                if ( strstr( response, "投稿が完了しました" ) )
                    ret = TRUE; /* 登録成功 */
            }
        }

        if ( buffer )
            free( buffer );
    }

    return ( ret );
}

void
putFlog(
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

    /* Flog に login */
    ret = loginFlog( userName, password, cookie );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "Flog", mp, numOfClips, cookie, cookieSize, NULL,
                      _putFlog );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Flogへの login に失敗しました\n"
                    : "Flog: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Flogへのログインに失敗しました。  "
                         : "Flog: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_FLOG_EXE
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
                 "putFlog: OPML → Flog 登録ツール\n" );
        fprintf( stderr,
    "    putFlog [-x] -u メールアドレス -p パスワード [-i OPMLファイル名]\n");
        fprintf( stderr,
    "\t-x: proxy を使う\n"
    "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putFlog: read bookmarks from OPML, and put them into Flog\n" );
        fprintf( stderr,
      "    putFlog [-x] -u mailaddress -p password [-i OPMLfilename]\n" );
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
        /* ブックマークを Flog に登録 */
        putFlog( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_FLOG_EXE */

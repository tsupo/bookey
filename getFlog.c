/*
 * clip saver <<getFlog>>
 *
 *      Flog → OPML 変換出力プログラム
 *          written by H.Tsujimura  23 Jun 2006
 *
 * $Log: /comm/bookey/getFlog.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    08/11/25 12:10 Tsujimura543
 * ブックマーク取得処理を更新
 * (いつの間にか、Flog のページのフォーマット、構成が変わっていたため、
 *  ブックマークの取得ができなくなっていた)
 * 
 * 14    08/02/14 19:40 Tsujimura543
 * replaceString() を myClip.c へ移動
 * 
 * 13    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 12    07/01/18 0:29 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 11    07/01/17 22:59 Tsujimura543
 * 英語モード対応
 * 
 * 10    07/01/17 22:25 Tsujimura543
 * 綴りミスを修正 oversea → overseas)
 * 
 * 9     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 8     06/10/03 23:06 Tsujimura543
 * 綴りミスを修正 (catoon → cartoon) [facetさん、指摘感謝!]
 * 
 * 7     06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 6     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 5a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 5     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 4     06/06/23 21:50 Tsujimura543
 * &raquo; 対策を追加
 * 
 * 3     06/06/23 21:48 Tsujimura543
 * (1) httpリクエストを連続送信する場合、1秒間 Sleep を入れるようにした
 * (2) 正しい「年」を取得するため、comment.php を取得するようにした
 * (3) OPML 書き出し時に XML 的に正しくないものが生成されてしまわないよ
 *     うにコメントやタイトルに特別扱いすべき文字が含まれる場合は適宜置
 *     換するような処理を追加した
 * 
 * 2     06/06/23 18:10 Tsujimura543
 * comment 中に含まれる改行や<br>を除去するようにした
 * 
 * 1     06/06/23 17:59 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getFlog.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/*
 *  Flog の場合、自分のブックマーク一覧は
 *    (1) Myブックマーク
 *    (2) 管理画面
 *  経由のどちらでも取得可能であり、(1) は 20件/ページ単位での取得、
 *  (2) は全件一気取得となる。ただ、ブックマークの数が増えてくると、
 *  (2) も1ページで全件取得できなくなる可能性がある(未確認)ため、
 *  現時点では (1) 経由でブックマーク一覧を取得することにする
 *
 *  また、ユーザIDがわかれば、http://www.flog.jp/m.php/ユーザID に
 *  アクセスすることで、そのユーザのブックマークが取得できる((1) と
 *  同じ形式で取得できるので、取得処理は共通化できる)。
 */

char    *
getFlogGategory( const char *catStr )
{
    const char  *tag = "computer";

    if ( !strcmp( catStr, "コンピュータ" ) )
        tag = "computer";
    else if ( !strcmp( catStr, "ビジネス/政治" ) )
        tag = "business";
    else if ( !strcmp( catStr, "ニュース" ) )
        tag = "news";
    else if ( !strcmp( catStr, "日記" ) )
        tag = "diary";
    else if ( !strcmp( catStr, "芸能/アイドル" ) )
        tag = "showbiz";
    else if ( !strcmp( catStr, "ヘルス/ビューティ" ) )
        tag = "health";
    else if ( !strcmp( catStr, "就職/転職" ) )
        tag = "employment";
    else if ( !strcmp( catStr, "グルメ" ) )
        tag = "gourmet";
    else if ( !strcmp( catStr, "音楽" ) )
        tag = "music";
    else if ( !strcmp( catStr, "映画" ) )
        tag = "cinema";
    else if ( !strcmp( catStr, "本/雑誌/新聞" ) )
        tag = "print";
    else if ( !strcmp( catStr, "漫画/アニメ" ) )
        tag = "cartoon";
    else if ( !strcmp( catStr, "テレビ" ) )
        tag = "tv";
    else if ( !strcmp( catStr, "ゲーム" ) )
        tag = "game";
    else if ( !strcmp( catStr, "ペット/動物" ) )
        tag = "animal";
    else if ( !strcmp( catStr, "趣味/スポーツ" ) )
        tag = "hobby";
    else if ( !strcmp( catStr, "車/バイク" ) )
        tag = "car";
    else if ( !strcmp( catStr, "くらし/家電" ) )
        tag = "life";
    else if ( !strcmp( catStr, "旅行/地域情報" ) )
        tag = "travel";
    else if ( !strcmp( catStr, "芸術/デザイン" ) )
        tag = "art";
    else if ( !strcmp( catStr, "教育/学問/資料" ) )
        tag = "education";
    else if ( !strcmp( catStr, "動画/フラッシュ" ) )
        tag = "movie";
    else if ( !strcmp( catStr, "便利ツール" ) )
        tag = "tool";
    else if ( !strcmp( catStr, "まとめサイト" ) )
        tag = "summarySite";
    else if ( !strcmp( catStr, "ネタ/ジョーク" ) )
        tag = "neta";
    else if ( !strcmp( catStr, "恋愛" ) )
        tag = "love";
    else if ( !strcmp( catStr, "ファッション/ブランド" ) )
        tag = "fashion";
    else if ( !strcmp( catStr, "海外" ) )
        tag = "overseas";

    return ( (char *)tag );
}


char    *
getFlogUserID( const char *userName, const char *password )
{
    Thread static char  userID[32];
    char                *cookie;
    char                *response;
    char                url[MAX_URLLENGTH];
    int                 fd;
    size_t              sz = MAX_CONTENT_SIZE * 20;

    userID[0] = NUL;

    fd = fileno( stderr );
    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "メモリの確保に失敗しました\n"
                    : "memory exhausted.\n",
                   stderr );
        return ( userID );
    }
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* Flog に login */
    if ( !loginFlog( userName, password, cookie ) ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Flogへの login に失敗しました\n"
                    : "Flog: login failed.\n",
                   stderr );
        free( cookie );
        return ( userID );
    }

    /* 「Myブックマーク」を取得 */
    response = (char *)malloc( sz );
    if ( !response ) {
        free( cookie );
        return ( userID );
    }

    strcpy( url, "http://www.flog.jp/my.php" );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    /* 「Myブックマーク」からユーザIDを取得 */
    if ( response && *response ) {
        char    *p = strstr( response, "<a href=\"/confirm.php/" );

        if ( p ) {
            char    *q;

            p += 22;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( userID, p, q - p );
                userID[q - p] = NUL;
            }
        }
    }

    free( response );
    free( cookie );

    return ( userID );
}

MyClip  *
getFlog(
        const char *userName,   /* (I) login時に使うユーザ名    */
        const char *password,   /* (I) login時に使うパスワード  */
        const char *userID,     /* (I) ユーザID                 */
        int        *numOfClips  /* (O) 取得したブックマークの数 */
    )
{
    /*
     *  userName で指定されたユーザのブックマーク、もしくは userID で指定さ
     *  れたユーザのブックマークを全件取得する(userName で指定する場合は、
     *  password の指定も必要。userID で指定する場合は、password は不要)
     */
    MyClip      *mp = NULL;
    char        target[MAX_URLLENGTH];
    char        url[MAX_URLLENGTH];
    char        commentURL[MAX_URLLENGTH];
    char        *response;
    char        *response2;
    BOOL        cont = TRUE;
    char        *p, *q, *r, *s;
    int         num  = 0;
    int         cnt  = 0;
    int         unit = 200;
    int         len;
    char        category[32];
    char        commentID[32];
    int         yy, mm, dd, HH, MM, SS;
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    size_t      sz  = MAX_CONTENT_SIZE * 20;

    yy = tm->tm_year + 1900;
    mm = tm->tm_mon + 1;
    dd = tm->tm_mday;
    HH = tm->tm_hour;
    MM = tm->tm_min;
    SS = tm->tm_sec;

    *numOfClips = 0;
    target[0]   = NUL;
    if ( userName && userName[0] && password && password[0] ) {
        char    *uID = getFlogUserID( userName, password );
        if ( uID )
            sprintf( target, "http://www.flog.jp/m.php/%s", uID );
    }
    else if ( userID && userID[0] )
        sprintf( target, "http://www.flog.jp/m.php/%s", userID );
    if ( target[0] == NUL )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );
    response2 = (char *)malloc( sz );
    if ( !response2 ) {
        free( response );
        return ( mp );
    }

    strcpy( url, target );
    do {
        MyClip  *newClip_p;

        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        http_get( url, response );

        if ( !response || !(response[0]) )
            break;

        newClip_p = allocateMyClipIfNecessary( &mp, unit, &cnt, num );
        if ( !newClip_p )
            break;
        mp = newClip_p;

        // ブックマークを抜き出す
     // p = strstr( response, "<td align=\"left\" class=\"txt\">" );
        p = strstr( response, " class=\"txt_b\">" );
        q = NULL;
        if ( p ) {
         // p += 30;
            p += 14;
            q = strstr( p, "</table><center><table " );
        }
        while ( p && q && (p < q) ) {
            s = strstr( p, "</table><a " );
            if ( !s )
                s = q;

            // URL
            r = strstr( p, "<a href=\"/comment.php/" );
            if ( !r || (r > s) )
                break;
            p = r + 22;
            r = strchr( p, '"' );
            if ( !r || (r > s) )
                r = strchr( p, ' ' );
            if ( !r || (r > s) )
                r = strchr( p, '>' );
            if ( !r || (r > s) )
                break;
            strncpy( commentURL, p, r - p );
            commentURL[r - p] = NUL;
            p = r + 1;

            // タイトル
            r = strchr( p, '>' );
            if ( !r || (r > s) )
                break;
            p = r + 1;
            r = strstr( p, "</a>" );
            if ( !r || (r > s) )
                break;
            strncpy( mp[num].title, p, r - p );
            mp[num].title[r - p] = NUL;

            replaceString( mp[num].title, "&raquo;-&raquo;", " - " );
            replaceString( mp[num].title, "&raquo;", "≫" );

            p = r + 4;

            // タグ
            mp[num].tags[0] = NUL;
            do {
                r = strstr( p, " class=\"txt_s\">[" );
                if ( !r || (r > s) )
                    break;
                p = r + 16;
                r = strstr( p, "]</a>" ); // 2byte 目が ']' な漢字があると罠に
                if ( !r || (r > s) )      // はまるので、"</a>" 付きで評価する
                    break;

                if ( mp[num].tags[0] )
                    strcat( mp[num].tags, " " );
                len = mp[num].tags[0] ? strlen( mp[num].tags ) : 0;
                strncat( mp[num].tags, p, r - p );
                mp[num].tags[len + (r - p)] = NUL;

                p = r + 5;
            } while ( r );
            if ( p > s )
                break;

            // コメントID
            commentID[0] = NUL;
            r = strstr( p, "<a href=\"/comment.php/" );
            if ( r && (r < s) ) {
                p = r + 22;
                r = strchr( p, '"' );
                if ( r && (r < s) ) {
                    strncpy( commentID, p, r - p );
                    commentID[r - p] = NUL;
                    p = r + 1;
                }
            }

            // コメント
            r = strstr( p, "<div class=\"comment\">" );
            if ( !r || (r > s) )
                break;
            p += 21;
            r = strstr( p, "\">&nbsp;" );
            if ( !r || (r > s) )
                break;
            p = r + 8;

            r = strstr( p, "&nbsp;(" );
            if ( !r || (r > s) )
                break;
            strncpy( mp[num].comment, p, r - p );
            mp[num].comment[r - p] = NUL;

            /* Flog のコメントには改行が含まれ得る */
            while ( ((p = strchr(mp[num].comment, '\r')) != NULL) ||
                    ((p = strchr(mp[num].comment, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* 改行を取り除く */
            /* Flog のコメントには <br> が含まれ得る */
            while ( (p = strstr( mp[num].comment, "<br>" )) != NULL ) 
                strcpy( p, p + 4 ); /* <br> を取り除く */

            if ( strchr( mp[num].comment, '&' ) ) {
                replaceString( mp[num].comment, "&quot;",  "\"" );
                replaceString( mp[num].comment, "&lt;",    "<" );
                replaceString( mp[num].comment, "&gt;",    ">" );
                replaceString( mp[num].comment, "&amp;",   "&" );
                replaceString( mp[num].comment, "&raquo;", "≫" );
            }
    
            replaceString( mp[num].comment, "&",  "&amp;" );
            replaceString( mp[num].comment, "\"", "&quot;" );
            replaceString( mp[num].comment, "<",  "&lt;" );
            replaceString( mp[num].comment, ">",  "&gt;" );

            p = r + 7;

            // カテゴリー
            r = strstr( p, "<a href=\"/cate.php/" );
            if ( !r || (r > s) )
                break;
            p = r + 19;
            r = strstr( p, "title=\"" );
            if ( !r || (r > s) )
                break;
            p = r + 7;
            r = strchr( p, '"' );
            if ( !r || (r > s) )
                break;
            strncpy( category, p, r - p );
            category[r - p] = NUL;

            if ( mp[num].tags[0] )
                strcat( mp[num].tags, " " );
            strcat( mp[num].tags, getFlogGategory( category ) );

            p = r + 1;

            // 月日 時分秒 (「年」の情報が含まれないので、補完する必要がある)
            //   ヒント: 「年」の情報は
            //               http://www.flog.jp/comment.php/ブックマークID
            //           経由で取得できる
            r = strstr( p, "<span class=\"txt_s\">" );
            if ( !r || (r > s) ) {
                mp[num].yyyy = yy;
                mp[num].mm   = mm;
                mp[num].dd   = dd;
                mp[num].HH   = HH;
                mp[num].MM   = MM;
                mp[num].SS   = SS;
            }
            else {
                p = r + 20;
                mm = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                dd = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                HH = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                MM = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                SS = (*p - '0') * 10 + (*(p + 1) - '0');

                mp[num].yyyy = yy; /* 暫定値 */
                mp[num].mm   = mm;
                mp[num].dd   = dd;
                mp[num].HH   = HH;
                mp[num].MM   = MM;
                mp[num].SS   = SS;

                // 年
                //   http://www.flog.jp/comment.php/ブックマークID を取得
                if ( commentID[0] ) {
                    Sleep( 1000 );

                    sprintf( url, "http://www.flog.jp/comment.php/%s",
                             commentID );
                    setTargetURL( url );
                    setUpReceiveBuffer( response2, sz );
                    http_get( url, response2 );

                    if ( response2 && *response2 ) {
                        char    *pp = strstr( response2,
                                              "<br><span class=\"txt_s\">" );
                        if ( pp ) {
                            pp += 24;
                            mp[num].yyyy = atol( pp );
                        }

                        pp = strstr( response2, "<a href=/j.php/" );
                        if ( pp ) {
                            char    *qq;

                            pp += 15;
                            qq = strchr( pp, ' ' );
                            if ( !qq )
                                qq = strchr( pp, '>' );
                            if ( qq ) {
                                strncpy( mp[num].url, pp, qq - pp );
                                mp[num].url[qq - pp] = NUL;
                            }
                        }
                    }
                } 

                p += 2;
            }

            num++;

            p = strstr( p, "</table>" );
            if ( p )
                p += 8;
        }

        // 次へ
        cont = FALSE;
        p = strstr( response, "\">&nbsp;&nbsp;次へ&gt;&gt;</a>" );
        if ( p ) {
            while ( (p >= response) && (*p != '/') )
                p--;
            if ( *p == '/' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;
                    sprintf( url, "%s%s", target, page );
                    cont = TRUE;
                    Sleep( 1000 );
                }
            }
        }
    } while ( cont );

    *numOfClips = num;
    free( response2 );
    free( response );

    return ( mp );
}


#ifdef  GET_FLOG_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy
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
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
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
                 "getFlog: Flog → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tFlogから吸い出した内容を OPML ファイルとして出力する\n" );
        fprintf( stderr,
                 "    getFlog [-x] -u メールアドレス -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getFlog: get bookmarks from Flog, and output them as "
                 "OPML\n" );
        fprintf( stderr,
                 "    getFlog [-x] -u mailaddress -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* Flog へ登録済みのブックマークを取得 */
    mp = getFlog( username, password, NULL, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Flog のブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "Flog", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_FLOG_EXE */

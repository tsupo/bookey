/*
 * clip saver <<getBlueDot>>
 *
 *      Blue Dot → OPML 変換出力プログラム
 *          written by H.Tsujimura  6 Oct 2006
 *
 * History:
 * $Log: /comm/bookey/getDelicious/getBlueDot.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 17    08/12/01 19:17 Tsujimura543
 * escapeAmpasand() → escapeAmpersand() に変更 (綴り誤りを修正)
 * 
 * 16    08/07/25 0:36 Tsujimura543
 * private saving に対応
 * 
 * 15    08/07/25 0:03 Tsujimura543
 * getBlueDot2() を変更、修正 (private対応、タグ抽出処理修正)
 * 
 * 14    08/02/25 16:48 Tsujimura543
 * コメントを修正
 * 
 * 13    08/02/25 16:40 Tsujimura543
 * bluedot.us → faves.com への移行に伴う修正を実施
 * (注意: この版では、公開範囲が Everyone のものしか取得できない)
 * 
 * 12    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 11    07/01/17 21:42 Tsujimura543
 * (1) deleteHtmlTags() を getBlueDot.c から分離、独立させた
 * (2) 英語モード対応
 * (3) コマンドライン版をビルドできるようにした
 * 
 * 10    07/01/11 20:23 Tsujimura543
 * getAllPostsOnBlueDot() でタイムアウトが発生しなくなったことを確認
 * (サーバ側で何らかの改善が行われた模様)
 * 
 * 9     07/01/11 20:17 Tsujimura543
 * 文字化けしたり、invalid な OPML になってしまったりすることがある
 * 不具合に可能な限り対処 
 * 
 * 8     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 7     06/10/18 19:41 Tsujimura543
 * 任意のユーザのブックマークを取得できるようにした
 * 
 * 6     06/10/07 7:21 Tsujimura543
 * タイトルに改行が含まれる場合、取り除くようにした
 * 
 * 5     06/10/07 5:32 Tsujimura543
 * 結局、My Dots (html ページ)を順番に取得して解析した結果を元に
 * ブックマーク情報を構成するようにすることで対応することにした
 * 
 * 4     06/10/07 2:20 Tsujimura543
 * いったん fix し、後日、別の手を考えることにする
 * 
 * 3     06/10/07 2:18 Tsujimura543
 * getListOfDatesOnBlueDot() を使う方法でも駄目だった
 *  → API を使わずに、My Dots な Web ページを取得して、html ファイルを
 *     解析していく手法を採用するしか手はないかも (API の存在意味なし)
 * 
 * 2     06/10/07 2:00 Tsujimura543
 * del.icio.us の場合は「http応答受信待ちタイムアウト時間」を長くすること
 * でブックマーク数が多い場合にも対応できたが、Blue Dot の場合は、処理に
 * 時間が(60秒以上?)かかりそうな場合はサーバの方から接続を切ってくること
 * が判明。別の方法で対処する必要がある (今後の課題)
 * 
 * 1     06/10/07 1:08 Tsujimura543
 * 新規作成
 */

#include "myClip.h"
#include "delicious.h"
#include "blueDot.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDelicious/getBlueDot.c 1     09/05/14 3:48 tsupo $";
#endif


char    *
escapeAmpersand( char *p )
{
    char    *s, *t, *u;

    s = strchr( p, '&' );
    while ( s ) {
        t = strchr( s, ';' );
        u = strchr( s, '&' );
        if ( !t || (u && (u < t)) ) {
            char    *pp = s + strlen( s );
            while ( pp > s ) {
                *(pp + 4) = *pp;
                pp--;
            }
            *++s = 'a';
            *++s = 'm';
            *++s = 'p';
            *++s = ';';

            s = strchr( s, '&' );
        }
        else
            break;
    }

    return ( p );
}


/* Blue Dot に sign in する */
int
loginBlueDot(
        const char *username,   // (I)   ユーザ名
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

 // strcpy( url, "https://secure.bluedot.us/signIn" );
    strcpy( url, "https://secure.faves.com/signIn" );
    setTargetURL( url );
    sprintf( request,
             "rUsername=%s&"
             "rPassword=%s&"
             "rememberMe=1&"
             "action=%s",
             username, password,
             encodeURL( "Sign In" ) );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( (strstr( response, "Sign Out" )   != NULL) ||
             (strstr( response, "My Account" ) != NULL)    )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }
    else
        ret = 0;        /* ログイン失敗 */

    free( response );
    free( request  );

    return ( ret );
}

MyClip  *
getBlueDot2(
        const char *userName,   /* (I) ユーザ名                 */
        const char *password,   /* (I) パスワード               */
        long       *numOfClips  /* (O) 取得したブックマークの数 */
    )
{
    /*
     *  userName で指定されたユーザの favesを全件取得する(公開範囲が
     *  Everyone 以外の faves を取得する場合は、password の指定も必要。
     *  Everyone のみの取得でいい場合は、password は不要)
     */
    MyClip      *mp = NULL;
    char        url[MAX_URLLENGTH];
    char        *request;
    char        *response;
    char        *cookie;
    char        *pi;
    char        *p, *q, *r, *s, *qq;
    BOOL        cont = TRUE;
    int         num  = 0;
    int         cnt  = 0;
    int         unit = 200;
    int         i;
    int         yy, mm, dd;
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    int         y0  = tm->tm_year + 1900;
    int         m0  = tm->tm_mon  + 1;
    int         d0  = tm->tm_mday;
    size_t      sz  = MAX_CONTENT_SIZE * 20;

    static char month[12][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    *numOfClips = 0;

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( mp );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    if ( password && *password ) {
        /* Blue Dot に login */
        if ( !loginBlueDot( userName, password, cookie ) ) {
            // login 失敗
            free( cookie );
            return ( mp );
        }
    }

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        free( cookie );
        return ( mp );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return ( mp );
    }
    pi = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !pi ) {
        free( response );
        free( request );
        free( cookie );
        return ( mp );
    }

 // sprintf( url, "http://bluedot.us/users/%s", userName );
    sprintf( url, "http://faves.com/users/%s", userName );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    do {
        if ( !response || !(response[0]) )
            break;

        // ブックマークを抜き出す
     // p = strstr( response, "<div class=\"dotList\">" );
        p = strstr( response, "<ul class=\"dotList" );
        if ( !p )
            break;
        p += 18;

        do {
            MyClip  *newClip_p;
            newClip_p = allocateMyClipIfNecessary( &mp, unit, &cnt, num );
            if ( !newClip_p )
                break;
            mp = newClip_p;

            q = strstr( p, "<div class=\"t\">" );
            s = strstr( p, "</a></div></li>" );
            if ( !q || !s )
                break;
            p = strchr( q, '>' ) + 1;

            // URL
            q = strstr( p, "<a name=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 10;
            q = strstr( p, " href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 7;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( mp[num].url, p, q - p );
            mp[num].url[q - p] = NUL;

            // タイトル
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( mp[num].title, p, q - p );
            mp[num].title[q - p] = NUL;
            r = utf2sjis( mp[num].title );
            if ( r )
                strcpy( mp[num].title, r );
            else
                utf2sjisEx( mp[num].title );
            /* Blue Dot のタイトルには改行が含まれ得る */
            while ( ((p = strchr(mp[num].title, '\r')) != NULL) ||
                    ((p = strchr(mp[num].title, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* 改行を取り除く */
            escapeAmpersand( mp[num].title );

            // private か否か
            mp[num].publication = PUB_EVERYONE;
            p = q + 4;
            q = strstr( p, "</em> - " );
            if ( q && (q < s) ) {
                // private
                r = strstr( p, "Not Shared" );
                if ( !r || (r > q) )
                    r = strstr( p, "(Private)" );
                if ( r && (r < q) )
                    mp[num].publication = PUB_PRIVATE;
                p = q + 8;
            }
            else {
                q = strstr( p, "</a> - " );
                if ( !q || (q > s) )
                    break;
                p = q + 7;
            }

            // 年月日
            if ( (*p >= '1') && (*p <= '9') ) {
                dd = atol( p );
                while ( (*p >= '0') && (*p <= '9') )
                    p++;
                if ( *p == ' ' )
                    p++;
                if ( !strncmp( p, "days ago", 8 ) ||
                     !strncmp( p, "day ago",  7 )    ) {
                    time_t      tt   = t - dd * 24 * 60 * 60;
                    struct tm   *ttm = localtime( &tt );

                    yy = ttm->tm_year + 1900;
                    mm = ttm->tm_mon  + 1;
                    dd = ttm->tm_mday;
                }
                else {
                    // 今日
                    yy = y0;
                    mm = m0;
                    dd = d0;
                }
            }
            else {
                // Aug 28 2006 形式
                yy = y0;    // 初期値 (暫定)
                mm = m0;    // 初期値 (暫定)
                dd = d0;    // 初期値 (暫定)

                for ( i = 0; i < 12; i++ ) {
                    if ( !strncmp( p, month[i], 3 ) ) {
                        mm = i + 1;
                        break;
                    }
                }

                while ( *p && ((*p <= '0') || (*p > '9')) )
                    p++;
                if ( (*p >= '1') && (*p <= '9') )
                    dd = atol( p );
                while ( (*p >= '0') && (*p <= '9') )
                    p++;
                while ( *p && ((*p <= '0') || (*p > '9')) )
                    p++;
                if ( (*p >= '1') && (*p <= '9') )
                    yy = atol( p );
            }

            mp[num].yyyy = yy;
            mp[num].mm   = mm;
            mp[num].dd   = dd;
            mp[num].HH   = 0;
            mp[num].MM   = 0;
            mp[num].SS   = 0;

            qq = strstr( p, "=tag%" );
            q = strstr( p, "/tag/" );
            r = strstr( p, "<div class=\"note\">" );
            if ( qq && q && r && (qq < q) && (qq < r) )
                q = qq;
            if ( q && r && (q < s) && (q < r) && (r < s) ) {
                // キーワード (タグ)
                int len;

                p = q + 5;
                do {
                    q = strstr( p, "\">" );
                    if ( !q || (q > r) )
                        break;
                    p = q + 2;
                    q = strstr( p, "</a>" );
                    if ( !q || (q > r) )
                        break;

                    if ( mp[num].tags[0] == NUL )
                        len = 0;
                    else {
                        strcat( mp[num].tags, " " );
                        len = strlen( mp[num].tags );
                    }
                    strncat( mp[num].tags, p, q - p );
                    mp[num].tags[len + (q - p)] = NUL;

                    p = q + 4;
                } while ( p < r );
                if ( mp[num].tags[0] ) {
                    r = utf2sjis( mp[num].tags );
                    if ( r )
                        strcpy( mp[num].tags, r );
                    else
                        utf2sjisEx( mp[num].tags );
                    escapeAmpersand( mp[num].tags );
                }
            }

            // コメント
            q = strstr( p, "<div class=\"note\">" );
            if ( !q || (q > s) )
                break;
            p = q + 18;
            q = strstr( p, "</div>" );
            if ( !q || (q > s) )
                break;
            strncpy( mp[num].comment, p, q - p );
            mp[num].comment[q - p] = NUL;
            deleteHtmlTags( mp[num].comment );
            r = utf2sjis( mp[num].comment );
            if ( r )
                strcpy( mp[num].comment, r );
            else
                utf2sjisEx( mp[num].comment );
            escapeAmpersand( mp[num].comment );

            p = s + 24;

            num++;
        } while ( p && *p );

        // 次へ
        cont = FALSE;
        p = strstr( response, "<input name=\"pi\"" );
        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( pi, p, q - p );
                    pi[q - p] = NUL;

                    Sleep( 1000 );

                    setTargetURL( url );
                    sprintf( request,
                             "pi=%s&",
                             encodeURL( pi ) );
                    sprintf( request + strlen( request ),
                             "n=%s",
                             encodeURL( "NEXT PAGE" ) );
                    setUpReceiveBuffer( response, sz );
                    http_postEx( url, "application/x-www-form-urlencoded",
                                 request, response, cookie );
                    cont = TRUE;
                }
            }
        }
    } while ( cont );

    *numOfClips = num;

    free( pi );
    free( response );
    free( request );
    free( cookie );

    return ( mp );
}


MyClip  *
getBlueDot(
        const char *username,   /* (I)   ユーザ名         */
        const char *password,   /* (I)   パスワード       */
        int        *numOfClips  /* (I/O) ブックマーク件数 */
    )
{
    long            n, num, numOfPosts = 0, i;
    DELICIOUS_POSTS *posts;
    MyClip          *mp = NULL;
    char            *s, *t;

    n = *numOfClips;
    *numOfClips = 0;

    /* Blue Dot のブックマークを取得 */
    if ( n == 0 )
        num = getNumberOfBookmarksOnBlueDot( username, password );
    else
        num = n;
    if ( num <= 0 )
        return ( mp );
    Sleep( 1000 );

    numOfPosts = num;
    posts = (DELICIOUS_POSTS *)
                malloc( sizeof ( DELICIOUS_POSTS ) * numOfPosts );
    if ( !posts )
        return ( mp );
    memset( posts, 0x00, sizeof ( DELICIOUS_POSTS ) * numOfPosts );

    n = 0;
    if ( password && *password ) {
#if 0
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT * (numOfPosts / 100) );
                        // ブックマーク総数に比例したタイムアウト時間を設定
#endif
        n = getAllPostsOnBlueDot( username, password,
                                  NULL,
                                  &numOfPosts, posts );
#if 0
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT ); // デフォルト値に戻しておく
#endif
    }
    if ( n <= 0 ) {
        // 別の方法でブックマーク取得を試みる
        mp = getBlueDot2( username, password, &n );
    }
    else {
        mp = (MyClip *)malloc( sizeof ( MyClip ) * n );
        if ( !mp ) {
            free( posts );
            return ( mp );
        }

        for ( i = 0; i < n; i++ ) {
            strcpy( mp[i].title,   posts[i].description );
            escapeAmpersand( mp[i].title );

            strcpy( mp[i].tags,    posts[i].tag );
            escapeAmpersand( mp[i].tags );

            strcpy( mp[i].url,     posts[i].href );
            strcpy( mp[i].comment, posts[i].extended );

            s = mp[i].comment;
            while ( ((t = strchr( s, '\n' )) != NULL) ||
                    ((t = strchr( s, '\r' )) != NULL)    ) {
                if ( (*(t + 1) == '\r') || (*(t + 1) == '\n') )
                    strcpy( t, t + 1 );
                *t = ' ';
            }
            escapeAmpersand( mp[i].comment );

            mp[i].yyyy = atol( posts[i].dateTime );
            mp[i].mm   = (posts[i].dateTime[5]  - '0') * 10 +
                            (posts[i].dateTime[6]  - '0');
            mp[i].dd   = (posts[i].dateTime[8]  - '0') * 10 +
                            (posts[i].dateTime[9]  - '0');
            mp[i].HH   = (posts[i].dateTime[11] - '0') * 10 +
                            (posts[i].dateTime[12] - '0');
            mp[i].MM   = (posts[i].dateTime[14] - '0') * 10 +
                            (posts[i].dateTime[15] - '0');
            mp[i].SS   = (posts[i].dateTime[17] - '0') * 10 +
                            (posts[i].dateTime[18] - '0');

            if ( posts[i].shared == FALSE )
                mp[i].publication = PUB_PRIVATE;
        }
    }
 
    *numOfClips = n;
    free( posts );

    return ( mp );
}

#ifdef  GET_BLUEDOT_EXE
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
        fprintf( stderr, "getBlueDot: Blue Dot → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "    getBlueDot [-x] -u Blue Dot ユーザ名 "
                 "-p Blue Dot パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getBlueDot: get bookmarks from Blue Dot, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getBlueDot [-x] -u username "
                 "-p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password, &useProxy );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* Blue Dot 登録済みのブックマークを取得 */
    mp = getBlueDot( username, password, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  Blue Dot 情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "Blue Dot", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLUEDOT_EXE */

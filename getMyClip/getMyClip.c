/*
 * clip saver <<getMyClip>>
 *
 *      MyClip! → OPML 変換出力プログラム
 *          written by H.Tsujimura  17 Jan 2005 / 28 Sep 2005
 *
 * $Log: /comm/bookey/getMyClip/getMyClip.c $
 * 
 * 1     09/05/14 4:27 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 16    06/09/04 15:56 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 15a   06/09/03 20:17 tsupo
 * cookie まわりを修正
 * 
 * 15    06/08/22 15:47 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 14    06/03/28 16:57 Tsujimura543
 * MyClip! サービス 終了直前 フィックス版
 * 
 * 13    06/03/28 16:54 Tsujimura543
 * putDrecomRSS() を呼び出す前に、あらかじめ UTF-8 に変換されていることを前提
 * とする仕様に変更した (他のブックマークサービス用の putXXX() と仕様を合わせ
 * るため)
 * 
 * 12    06/03/28 16:24 Tsujimura543
 * -i オプションを追加し、putDrecomRSS() を組み込んだ
 * 
 * 11    05/11/02 0:50 Tsujimura543
 * 暫定的なリファクタリングを実施
 * 
 * 10    05/10/20 16:09 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 9     05/09/30 17:41 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 8     05/09/28 20:18 Tsujimura543
 * getMyClip() の仕様(引数の数、戻り値の型)を変更
 * 
 * 7     05/09/28 13:21 Tsujimura543
 * コードの整理
 * 
 * 6     05/09/28 13:19 Tsujimura543
 * getMyClip() をブックマーク管理ツールから呼び出せるようにした
 * 
 * 5     05/09/28 11:57 Tsujimura543
 * コードの整理
 * 
 * 4     05/09/28 11:28 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備
 * 
 * 3     05/09/28 11:04 Tsujimura543
 * struct myClip を他のブックマーク吸出し処理と完全に同じものにする
 * 
 * 2     05/09/28 10:59 Tsujimura543
 * struct myClip の定義を他のブックマーク吸出し処理での定義に近づける
 * 
 * 1     05/09/28 10:43 Tsujimura543
 * 最初の版 (clipCOnverter.c を元にブックマーク吸出し～OPML出力までの処理を
 * 切り出し)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getMyClip/getMyClip.c 1     09/05/14 4:27 tsupo $";
#endif


static char *
cutBrCrLf( char *p )
{
    char    *r;

    while ( ( r = strstr( p, "<br />" ) ) != NULL ) {
        if ( *(r - 1) == ' ' )
            strcpy( r, r + 7 );
        else
            strcpy( r, r + 6 );
    }

    while ( ( ( r = strchr( p, '\r' ) ) != NULL ) ||
            ( ( r = strchr( p, '\n' ) ) != NULL )    ) {
        strcpy( r, r + 1 );
    }

    return ( p );
}


int
loginMyClip( const char *username,
             const char *password,
             char       *cookie )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];

    if ( !cookie )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( MAX_CONTENT_SIZE * 20 );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );
    memset( response, 0x00, MAX_CONTENT_SIZE * 20 );

    strcpy( url, "http://clip.myblog.jp/login" );
    setTargetURL( url );
    sprintf( request,
             "email=%s&"
             "password=%s&"
             "auto_login=true",
             username, password );

    p = http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

    if ( !p || !(*p) )
        ret = 0;        /* サーバとの通信失敗 */
    else if ( *response ) {
        if ( strstr( response, "/logout" ) != NULL )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }

    free( response );
    free( request  );

    return ( ret );
}


#define URL_CLIPLIST_MYBLOG "http://clip.myblog.jp/member/list?"

long
getNumOfMyClips( char *cookie, int yyyy, int mm )
{
    long    num = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    *p, *q, *buf;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( num );
    response = (char *)malloc( MAX_CONTENT_SIZE * 20 );
    if ( !response ) {
        free( request );
        return ( num );
    }

    do {
        memset( request,  0x00, MAX_CONTENT_SIZE );
        memset( response, 0x00, MAX_CONTENT_SIZE * 20 );
        sprintf( url,
                 URL_CLIPLIST_MYBLOG
                 "year=%d&month=%d&cid=0",
                 yyyy, mm );
        setTargetURL( url );
        p = http_getEx( url, response, cookie );
        buf = response;
        if ( buf ) {
            if ( strstr( buf, url + 21 ) != NULL ) {
                    /* ↑ 21 := "http://clip.myblog.jp" 分をスキップ */
                p = strstr( buf, sjis2euc("Page1 ：") );
                if ( p ) {
                    p += 8;
                    q = strchr( p, '/' );
                    if ( q ) {
                        while ( *q && ((*q < '0') || (*q > '9')) )
                            q++;
                        if ( *q )
                            num += atol( q );
                    }
                }
            }
        }

        mm--;
        if ( mm <= 0 ) {
            mm = 12;
            yyyy--;
        }
    } while ( (yyyy >= 2005) || (mm >= 3) ); /* 最古の MyClip! は 2004年3月 */

    free( response );
    free( request  );

    return ( num );
}

char    *
setTag( char *tag, const char *catStr )
{
    if ( !strcmp( catStr, "IT" ) )
        strcpy( tag, "Internet" );
    else if ( !strcmp( catStr, sjis2euc("社会") ) )
        strcpy( tag, "social" );
    else if ( !strcmp( catStr, sjis2euc("スポーツ") ) )
        strcpy( tag, "sport" );
    else if ( !strcmp( catStr, sjis2euc("経済・経営") ) )
        strcpy( tag, "economy" );
    else if ( !strcmp( catStr, sjis2euc("政治") ) )
        strcpy( tag, "politics" );
    else if ( !strcmp( catStr, sjis2euc("国際") ) )
        strcpy( tag, "international" );
    else if ( !strcmp( catStr, sjis2euc("サイエンス") ) )
        strcpy( tag, "science" );
    else if ( !strcmp( catStr, sjis2euc("文化・芸能") ) )
        strcpy( tag, "culture" );
    else if ( !strcmp( catStr, sjis2euc("地域") ) )
        strcpy( tag, "region" );
    else if ( !strcmp( catStr, sjis2euc("訃報") ) )
        strcpy( tag, "news-of-death" );
    else if ( !strcmp( catStr, sjis2euc("コラム") ) )
        strcpy( tag, "column" );
    else if ( !strcmp( catStr, sjis2euc("エンターテインメント") ) )
        strcpy( tag, "entertainment" );
    else if ( !strcmp( catStr, sjis2euc("ブックレビュー") ) )
        strcpy( tag, "book-review" );
    else if ( !strcmp( catStr, sjis2euc("テクノロジー") ) )
        strcpy( tag, "technology" );
    else if ( !strcmp( catStr, "blog" ) )
        strcpy( tag, "blog" );
    else
        strcpy( tag, "no-detail" );

    strcat( tag, " MyClip" );

    return ( tag );
}

MyClip  *
getMyClips( char *cookie, int *numOfClips )
{
    char        *request;
    char        *response;
    char        url[MAX_URLLENGTH];
    char        catStr[80];
    char        timestr[80];
    int         yyyy, mm;
    int         s_yyyy, s_mm;
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );
    char        *p, *q, *buf, *cur;
    long        num = 0, cnt = 0, preCnt = 0, page;
    const char  *aim  = "<td width=\"336\" valign=\"top\" class=\"tx12bh\">";
    const char  *aim2 = "<td width=\"336\" class=\"tx12bh\">";
    int         maxNum = 1000;  /* 暫定 */
    MyClip      *mp = NULL;

    s_yyyy = yyyy = tm->tm_year + 1900;
    s_mm   = mm   = tm->tm_mon + 1;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( mp );
    response = (char *)malloc( MAX_CONTENT_SIZE * 20 );
    if ( !response ) {
        free( request );
        return ( mp );
    }

    /* http://clip.myblog.jp/member/list?year=2005&month=1&cid=0 */

    /* 総Clip数 479 */
    /* タイトル ： WAY TO GO: WWW::Mixiでサイドバーにコミュニティ一覧を表示  
　   * 記事URL  ： http://www.kreis-net.jp/blog/archives/000035.html  
　   * カテゴリ ： IT, 社会, スポーツ, 経済・経営, 政治, 国際, サイエンス, 
     *             文化・芸能, 地域, 訃報, コラム, エンターテインメント,
     *             ブックレビュー, テクノロジー, blog
     * コメント ： 一部同意できないところもあるけど、概ね賛成。  
     */

    do {
        page = 0;
        do {
            preCnt = cnt;
            memset( request,  0x00, MAX_CONTENT_SIZE );
            memset( response, 0x00, MAX_CONTENT_SIZE * 20 );
            if ( page == 0 )
                sprintf( url,
                         URL_CLIPLIST_MYBLOG
                         "year=%d&month=%d&cid=0",
                         yyyy, mm );
            else
                sprintf( url,
                         URL_CLIPLIST_MYBLOG
                         "year=%d&month=%d&cid=0&page=%d",
                         yyyy, mm, page );
            setTargetURL( url );
            p = http_getEx( url, response, cookie );
            if ( !p || !(*p) || !(*response) ) 
                break;

            buf = response;
            if ( buf ) {
                if ( (page == 0) && (strstr( buf, url + 21 ) == NULL) ) {
                    goto next;          /* ↑ 21 := "http://clip.myblog.jp" */
                }                       /*    byte 分をスキップ             */

                if ( num == 0 ) {
                    p = strstr( buf, sjis2euc("総Clip数") );
                    if ( p ) {
                        p += 8;
                        while ( (*p < '0') || (*p > '9') )
                            p++;
                        num = atol( p );
                    }
                    else {
                        /* いつの間にか MyClip! 一覧画面の仕様が変わり、 */
                        /*「総Clip数」が表示されなくなっている           */
                        /*
                         * クリップ数を自力でカウント
                         */
                        num = getNumOfMyClips( cookie, yyyy, mm );
                    }

                    if ( num <= 0 )
                        num = maxNum;

                    mp = (MyClip *)malloc( sizeof ( MyClip ) * num );
                    if ( !mp )
                        break;
                }

                cur = buf;
                do {
                    if ( cnt == 0 )
                        p = strstr( cur,
                                    "<table width=\"450\" height=\"200\" "
                                    "valign=\"middle\"" );
                    else
                        p = strstr( cur,
                                    "<table width=\"420\" border=\"0\" "
                                    "cellspacing=\"0\" cellpadding=\"0\">" );
                    if ( !p )
                        break;
                    cur = strchr( p, '>' );
                    if ( !cur )
                        break;
                    cur++;

                    p = strstr( cur, sjis2euc("タイトル") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                        q--;
                    if ( q - cur > (512 - 1) )  /* {@@} */
                        break;                  /* {@@} */
                    strncpy( mp[cnt].title, cur, q - cur );
                    mp[cnt].title[q - cur] = NUL;
                    cur = p + 5;

                    p = strstr( cur, sjis2euc("記事URL") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;

                    if ( !strncmp( cur, "<a href=\"", 9 ) ) {
                        cur += 9;
                        q = strchr( cur, '"' );
                        if ( q ) {
                            strncpy( mp[cnt].url, cur, q - cur );
                            mp[cnt].url[q - cur] = NUL;
                        }

                        while( *cur && (*cur != '>') )
                            cur++;
                        cur++;
                        while( (*cur == ' ')  || (*cur == '\t') ||
                               (*cur == '\r') || (*cur == '\n')    )
                            cur++;
                        p = q = strstr( cur, "</a>" );
                    }
                    else
                        p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    cur = p + 5;

                    p = strstr( cur, sjis2euc("カテゴリ") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                        q--;
                    strncpy( catStr, cur, q - cur );
                    catStr[q - cur] = NUL;
                    cur = p + 5;
                    setTag( mp[cnt].tags, catStr );

                    p = strstr( cur, sjis2euc("コメント") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    if ( !strncmp( cur, "</td>", 5 ) )
                        mp[cnt].comment[0] = NUL;
                    else {
                        p = q = strstr( cur, "</td>" );
                        if ( !q )
                            break;
                        while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                            q--;
                        strncpy( mp[cnt].comment, cur, q - cur );
                        mp[cnt].comment[q - cur] = NUL;
                        cutBrCrLf( mp[cnt].comment );
                    }
                    cur = p + 5;

                    p = strstr( cur, sjis2euc("追加日時") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim2 );
                    if ( !p )
                        break;
                    cur = p += strlen( aim2 );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                        q--;
                    strncpy( timestr, cur, q - cur );
                    timestr[q - cur] = NUL;
                    q = euc2sjis( timestr );
                    if ( !q )
                        q = timestr;
                    mp[cnt].yyyy = atol( q );

                    q += 6;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].mm   = atol( q );

                    q = timestr + 10;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].dd   = atol( q );

                    q = timestr + 15;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].HH   = atol( q );

                    q = timestr + 19;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].MM   = atol( q );
                    cur = p + 5;

                    mp[cnt].SS   = 0;

                    cnt++;
                    if ( cnt >= num )
                        break;
                } while ( p );
            }

            page++;
        } while ( preCnt != cnt );

        if ( !mp )
            break;

      next:
        mm--;
        if ( mm <= 0 ) {
            mm = 12;
            yyyy--;
        }
    } while ( (yyyy >= 2005) || (mm >= 3) ); /* 最古の MyClip! は 2004年3月 */

    free( response );
    free( request  );

    *numOfClips = num;

    return ( mp );
}

MyClip  *
getMyClip( const char *userName, const char *password, int *numOfClips )
{
    int     ret;
    char    cookie[MAX_COOKIE_LEN];
    MyClip  *mp = NULL;

    /* MyClip へ login */
    memset( cookie, 0x00, MAX_COOKIE_LEN );
    ret = loginMyClip( userName, password, cookie );
    if ( ret == 1 ) {   /* login 成功 */
        /* MyClip へ登録済みの clip を取得 */
        mp = getMyClips( cookie, numOfClips );
    }

    return ( mp );
}


#ifdef  GET_MYCLIP_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForMyClip,
        char *passwordForMyClip,
        BOOL *useProxy,
        BOOL *useImport
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( usernameForMyClip, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForMyClip, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForMyClip, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForMyClip, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;

                case 'i':
                    *useImport = !(*useImport);
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    fprintf( stderr, "getMyClip: MyClip! → OPML 変換出力ツール\n" );
    fprintf( stderr,
             "    getMyClip [-x] [-i] [-u MyBlogListユーザ名] "
             "[-p MyBlogListパスワード]\n" );
    fprintf( stderr,
             "\t-x: proxy を使う\n"
             "\t-i: ドリコムRSS にインポートする\n" );
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy   = FALSE;
    BOOL    useImport  = FALSE;
    char    userName[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( userName,  0x00, MAX_USERIDLEN );
    memset( password,  0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  userName, password, &useProxy, &useImport );

    if ( !(userName[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* MyClip! へ登録済みのブックマークを取得 */
    mp = getMyClip( userName, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  MyClip 情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "MyClip!", EUC2UTF, stdout );

        if ( useImport ) {
            int     i;
            char    *p;

            for ( i = 0; i < numOfClips; i++ ) {
                p = euc2utf( mp[i].title );
                if ( p )
                    strcpy( mp[i].title, p );

                p = euc2utf( mp[i].tags );
                if ( p )
                    strcpy( mp[i].tags, p );

                p = euc2utf( mp[i].comment );
                if ( p )
                    strcpy( mp[i].comment, p );
            }

            putDrecomRSS( userName, password, mp, numOfClips );
        }

        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_MYCLIP_EXE */

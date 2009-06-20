/*
 * clip saver <<getDrecomRSS>>
 *
 *      ドリコムRSS-Clip → OPML 変換出力プログラム
 *          written by H.Tsujimura  12 Jul 2006
 *
 * $Log: /comm/bookey/getDrecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 18    08/12/02 19:30 Tsujimura543
 * nullポインタ参照が発生する可能性のある箇所の対処
 * 
 * 17    08/07/26 0:31 Tsujimura543
 * decodeContents() を decodeContents.c へ移管
 * 
 * 16    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 15    07/01/17 21:46 Tsujimura543
 * 英語モード対応
 * 
 * 14    06/12/07 20:14 Tsujimura543
 * getDateTimeFromDateString() を導入し、日時情報の解析を委ねることにする
 * 
 * 13    06/11/10 17:00 Tsujimura543
 * GET_DRECOM_RSS_EXE が有効な状態でコンパイルした場合、出力するOPML
 * ファイルの title 要素が BlogPeople Tags になってしまう不具合を修正
 * 
 * 12    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 11    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 10d   06/09/03 15:54 tsupo
 * cookie 格納領域をヒープからスタックに変更
 * 
 * 10c   06/09/03 7:23 tsupo
 * cookie の格納領域のサイズを元(4096バイト)に戻す
 * 
 * 10b   06/09/03 6:42 tsupo
 * 夏時間対策、fix
 * 
 * 10a   06/09/03 5:47 tsupo
 * (1) なぜか Visual Studio 2005 でビルドした版は日本時間であるにも関
 *     わらず夏時間になる(localtime() の返す struct tm の内容)ため、
 *     暫定的に1時間過去に戻すようにしてみた
 * (2) cookie 用に確保する領域サイズを増やす (暫定)
 * (3) JSONRPC リクエスト実行時に 0 バイトの応答が返ってくる件の対策
 *     (暫定)
 * (4) 同一ソースからコマンドライン版 (getDrecomRSS.exe)もビルドできる
 *     ようにしてみた
 * 
 * 10    06/09/01 19:06 Tsujimura543
 * さらにリファクタリング
 * 
 * 9     06/09/01 17:01 Tsujimura543
 * フォルダ一覧取得処理を getFolderList() として独立させた
 * 
 * 8     06/09/01 0:59 Tsujimura543
 * さらに少しリファクタリング
 * 
 * 7     06/08/31 17:01 Tsujimura543
 * 少しだけリファクタリング
 * 
 * 6     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 5     06/07/13 18:25 Tsujimura543
 * XML invalid な OPML を吐き出してしまう可能性を極力排除するようにした
 * 
 * 4     06/07/13 16:40 Tsujimura543
 * Sleep() を入れる
 * 
 * 3     06/07/13 16:37 Tsujimura543
 * 最初の版、完成 (動作確認完了)
 * 
 * 2     06/07/12 23:07 Tsujimura543
 * UCS-2 のデコード(UTF-8 への変換)回りを修正
 * 
 * 1     06/07/12 20:44 Tsujimura543
 * 新規作成 (サーバからクリップ一覧を取ってくるところまで作成)
 */

#include "myClip.h"
#include "getDrecomRSS.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDrecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif

#define skipToNextItem(p)   \
            while ( *(p) && ((*(p) >= '0') && (*(p) <= '9')) ) \
                (p)++; \
            while ( *(p) && ((*(p) <= '0') || (*(p) > '9')) ) \
                (p)++;

BOOL
setObjectID( char *objectID, char *cookie )
{
    BOOL        ret = FALSE;
    char        *p;
    char        url[MAX_URLLENGTH];
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    char        *request;
    char        *response;
    size_t      sz = MAX_CONTENT_SIZE * 20;
    int         retry = 5;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    if ( tm->tm_isdst == 1 ) {
        p = _tzname[0];
        if ( !strcmp( p, "JST" ) ) {
            /* なぜか日本時間であるにも関わらず、夏時間になっている場合 */
            long l = _daylight;

            if ( l == 1 ) {
                // 環境変数 TZ を設定している場合は、(Visual Studio 2005 の)
                // 「C ランタイム ライブラリは、夏時間 (DST: Daylight Saving
                // Time) 計算の実装については米国の規則を前提としています」と
                // いうことで、勝手に夏時間にされてしまうらしい
                // 日本時間には(少なくとも現時点では)夏時間はないのに……
                _daylight = 0;
                tm = localtime( &t );
            }
            else {
                tm->tm_isdst = 0;
                tm->tm_hour--;
                        // tm_hour が負の値になった場合は、自動的に前日になる
            }
        }
    }
    strcpy( objectID, asctime( tm ) );
    p = strrchr( objectID, ' ' );
    if ( p )
        sprintf( p, " UTC+0900 %04d", tm->tm_year + 1900 );

    // JSON RPC API 一覧取得 (objectID 登録を兼ねる)
    do {
        request[0]  = NUL;
        strcpy( url, "http://rss.drecom.jp/jsonrpc" );
        sprintf( request,
                 "{\"method\": \"system.listMethods\", \"params\": [], "
                 "\"objectID\": \"%s\"}",
                 objectID );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "text/plain",
                     request, response, cookie );
        if ( !(*response ) ) {
            retry--;
            if ( retry <= 0 )
                break;
            Sleep( 2000 );
        }
    } while ( !(*response) );

    if ( *response ) {
        if ( strstr( response, "\"error\":null" ) )
            ret = TRUE;     /* 取得成功 → objectID 登録成功 */
    }

    if ( ret == FALSE )
        *objectID = NUL;    /* 取得失敗 → objectID 登録失敗 */

    free( response );
    free( request );

    return ( ret );
}

char    *
getArticleList( int folderNumber, int year, int page,
                const char *objectID,
                char *response, size_t sz,
                char *cookie )
{
    char    url[MAX_URLLENGTH];
    char    request[BUFSIZ];

    strcpy( url, "http://rss.drecom.jp/jsonrpc" );
    sprintf( request,
             "{\"method\": \"clip.getClipArticleList\", \"params\": "
             "[\"m%d.%04d.00\", %d], "
             "\"objectID\": \"%s\"}",
             folderNumber + 1, year, page,
             objectID );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "text/plain",
                 request, response, cookie );

    return ( response );
}

char    *
getArticleDetail( const char *articleID, const char *objectID,
                  char *response, size_t sz,
                  char *cookie )
{
    char    url[MAX_URLLENGTH];
    char    request[BUFSIZ];

    strcpy( url, "http://rss.drecom.jp/jsonrpc" );
    sprintf( request,
             "{\"method\": \"clip.getClipArticleDetailHtml\", \"params\":"
             " [\"%s\"], \"objectID\": \"%s\"}",
             articleID,
             objectID );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "text/plain",
                 request, response, cookie );

    return ( response );
}

void
getTagByName( char *tag, const char *folderName )
{
    char    *p = utf2sjis( folderName );
    char    *q = p;

    if ( !p )
        q = p = (char *)folderName;

    if ( !strcmp( p, "IT" ) )
        q = "Internet";
    else if ( !strcmp( p, "エンターテイメント" ) )
        q = "entertainment";
    else if ( !strcmp( p, "サイエンス" ) )
        q = "science";
    else if ( !strcmp( p, "地域" ) )
        q = "region";
    else if ( !strcmp( p, "社会" ) )
        q = "social";
    else if ( !strcmp( p, "コラム" ) )
        q = "column";
    else if ( !strcmp( p, "訃報" ) )
        q = "news-of-death";
    else if ( !strcmp( p, "文化・芸能" ) )
        q = "culture";
    else if ( !strcmp( p, "blog" ) )
        q = "blog";
    else if ( !strcmp( p, "経済・経営" ) )
        q = "economy";
    else if ( !strcmp( p, "政治" ) )
        q = "politics";
    else if ( !strcmp( p, "スポーツ" ) )
        q = "sport";
    else if ( !strcmp( p, "ブックレビュー" ) )
        q = "book-review";
    else if ( !strcmp( p, "国際" ) )
        q = "international";
    else if ( !strcmp( p, "テクノロジー" ) )
        q = "technology";

    strcpy( tag, q );
}

FOLDER_LIST *
getFolderList( const char *htmlSrc, int *numOfFolders )
{
    char        *p;
    int         num = 0;
    FOLDER_LIST *list = NULL;

    p = strstr( htmlSrc, "<div id=\"broot.children\" class=\"tree\">" );
    if ( p ) {
        char    name[BUFSIZ];
        char    *q, *r;
        int     unit  = 15;
        int     cnt   = 1;

        r = strstr( p, "<div id=\"treePool\" style=\"display:none;\">" );
        if ( r ) {
            p += 38;
            do {
                sprintf( name, "<div id=\"m%d.name\" class=\"treeName\">",
                         num + 1 );
                q = strstr( p, name );
                if ( !q || (q > r) )
                    break;

                if ( !list )
                    list = (FOLDER_LIST *)
                                malloc( sizeof ( FOLDER_LIST ) * unit * cnt );
                else if ( num >= unit * cnt ) {
                    FOLDER_LIST *newList;
                    cnt++;
                    newList = (FOLDER_LIST *)
                                    realloc( list,
                                             sizeof ( FOLDER_LIST ) *
                                                            unit * cnt );
                    if ( !newList )
                        break;
                    list = newList;
                }
                if ( !list )
                    break;
                p = q + strlen( name );
                q = strstr( p, "</div>" );
                if ( !q || (q > r) )
                    break;
                strncpy( list[num].folderName, p, q - p );
                list[num].folderName[q - p] = NUL;
                list[num].folderNumber = num + 1;
                num++;
            } while ( p < r );
        }
    }

    *numOfFolders = num;

    return ( list );
}


void
getClipInfo( const char *htmlSrc,
             MyClip     **mp,
             const char *tag,
             int        year,
             const char *objectID,
             char       *cookie,
             int        *numOfClips )
{
    int                 unit = MAX_DRECOM_RSS_PER_BLOCK;
    Thread  static int  cnt  = 0;
    const char          *p, *q, *r;
    char                articleID[64];
    char                *response;
    char                title[1024];
    char                href[1024];
    char                summary[2048];
    int                 yyyy, mm, dd, HH, MM, SS;
    int                 num = 0;
    size_t              sz  = MAX_CONTENT_SIZE * 20;

    if ( !(*mp) )
        cnt = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    p = htmlSrc;
    do {
        // article ID
        q = strstr( p, "<div class=\"articleRow\" id=\"" );
        if ( !q )
            break;
        r = strstr( q, "</div>" );
        if ( !r )
            break;
        p = q + 28;
        q = strstr( p, "\">" );
        if ( !q || (q > r) )
            break;
        strncpy( articleID, p, q - p );
        articleID[q - p] = NUL;

        // title
        p = q + 2;
        q = strstr( p, " all=\"");
        if ( !q || (q > r) )
            break;
        p = q + 6;
        q = strstr( p, "\">" );
        if ( !q || (q > r) )
            break;
        strncpy( title, p, q - p );
        title[q - p] = NUL;

        // timestamp
        yyyy = year;
        mm   = 0;
        dd   = 0;
        HH   = 0;
        MM   = 0;
        SS   = 0;

        p = q + 2;
        q = strstr( p, ".articleTime\">" );
        if ( !q || (q > r) )
            break;
        p = q + 14;
        while ( isWhiteSpace(*p) )
            p++;
        q = strstr( p, "</span>" );
        if ( q ) {
            char    tmp[BUFSIZ];

            r = q;
            while ( (q > p) && isWhiteSpace(*(q - 1)) )
                q--;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            strcat( tmp, " +0900" );    /* {@@} */
            getDateTimeFromDateString( tmp, &yyyy, &mm, &dd, &HH, &MM, &SS );
            p = r + 1;
        }

        p = r + 6;

        getArticleDetail( articleID, objectID,
                          response, sz, cookie );
        if ( *response ) {
            char    *s, *t;
            MyClip  *pp;

            decodeContents( response );
            s = response;

            // url
            t = strstr( s, "<a href=\"" );
            if ( !t )
                continue;
            s = t + 9;
            t = strstr( s, "\" " );
            if ( !t )
                continue;
            strncpy( href, s, t - s );
            href[t - s] = NUL;

            // comment
            summary[0] = NUL;
            s = t + 2;
            t = strstr( s, "<td style=\"color:#666666;\">" );
            if ( t ) {
                s = t + 27;
                t = strstr( s, "</td>" );
                if ( t ) {
                    strncpy( summary, s, t - s );
                    summary[t - s] = NUL;
                }
            }

            while ( (s = strstr( title, "&#039;" )) != NULL ) {
                *s = '\'';
                strcpy( s + 1, s + 6 ); /* &#039; → ' に置換 */
            }

            /* ドリコムRSSのClip!のコメントには改行が含まれ得る */
            while ( ((s = strchr(summary, '\r')) != NULL) ||
                    ((s = strchr(summary, '\n')) != NULL)    )
                strcpy( s, s + 1 ); /* 改行を取り除く */
            /* ドリコムRSSのClip!のコメントには <br /> が含まれ得る */
            while ( (s = strstr( summary, "<br />" )) != NULL )
                strcpy( s, s + 6 ); /* <br /> を取り除く */
            while ( (s = strstr( summary, "&#039;" )) != NULL ) {
                *s = '\'';
                strcpy( s + 1, s + 6 ); /* &#039; → ' に置換 */
            }

            pp = allocateMyClipIfNecessary(mp, unit, &cnt, *numOfClips + num);
            if ( !pp )
                break;
            *mp = pp;

            pp = &((*mp)[*numOfClips + num]);
            strcpy( pp->title, utf2sjisEx(title) );
            if ( summary[0] )
                strcpy( pp->comment, utf2sjisEx(summary) );
            strcpy( pp->url,  href );
            strcpy( pp->tags, tag );
            pp->yyyy = yyyy;
            pp->mm   = mm;
            pp->dd   = dd;
            pp->HH   = HH;
            pp->MM   = MM;
            pp->SS   = SS;

            num++;
        }
    } while ( p && *p );

    if ( num > 0 )
        *numOfClips += num;

    free( response );
}

void
getDrecomRSSclip(
        MyClip     **mp,
        const char *objectID,
        const char *folderName,
        int        folderNumber,
        int        year,
        char       *cookie,
        int        *numOfClips )
{
    char    *p;
    char    tag[80];
    int     totalPages = 0;
    int     page = 1;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    // フォルダ名 → タグ
    getTagByName( tag, folderName );

    // 指定フォルダ・指定年のクリップ一覧(の1ページ目)を取得
    getArticleList( folderNumber, year, page, objectID,
                    response, sz, cookie );
    if ( *response ) {
        if ( !strstr( response, "\"error\":null" ) ) {
            free( response );
            return; /* 取得失敗 */
        }

        decodeContents( response );
        if ( !strstr( response, "<div class=\"articleRow\"" ) ) {
            free( response );
            return; /* 指定年のクリップデータなし */
        }

        p = strstr( response, "title=\"last page\">[" );
        if ( p ) {
            p += 19;
            totalPages = atol( p );
        }
        getClipInfo( response, mp, tag, year,
                     objectID, cookie, numOfClips );

        // 指定フォルダ・指定年のクリップ一覧(の2ページ目以降)を取得
        for ( ++page; page <= totalPages; page++ ) {
            Sleep( 1000 );  /* サーバへの負荷集中回避のため sleep */
            getArticleList( folderNumber, year, page, objectID,
                            response, sz, cookie );
            if ( !(*response) || !strstr( response, "\"error\":null" ) )
                break;      /* 取得失敗 */

            decodeContents( response );
            if ( !strstr( response, "<div class=\"articleRow\"" ) )
                continue;   /* クリップデータなし */

            getClipInfo( response, mp, tag, year,
                         objectID, cookie, numOfClips );
        }
    }

    free( response );
}

MyClip  *
getDrecomRSS(
        const char *userName,   /* (I) login時に使うメールアドレス */
        const char *password,   /* (I) login時に使うパスワード     */
        int        *numOfClips  /* (O) 取得したブックマークの数    */
    )
{
    MyClip  *mp = NULL;
    char    *response;
    char    url[MAX_URLLENGTH];
    int     fd;
    int     num = 0;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    char    cookie[MAX_COOKIE_LEN];

    fd = fileno( stderr );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    // ドリコムRSS に login
    if ( !loginDrecomRSS( userName, password, cookie ) ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "ドリコムRSSへの login に失敗しました\n"
                    : "Drecom RSS: login failed.\n",
                   stderr );
        return ( mp );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // クリップリーダー にアクセス
    strcpy( url, "http://rss.drecom.jp/clip" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        FOLDER_LIST *list = NULL;
        int         numOfFolders = 0;

        // フォルダ一覧を取得
        list = getFolderList( response, &numOfFolders );

        if ( list ) {
            char        objectID[64];
            int         i, y;
            time_t      t = time( NULL );
            struct tm   *tm = localtime( &t );
            int         yyyy = tm->tm_year + 1900;
            BOOL        b;

            // objectID を登録
            objectID[0] = NUL;
            b = setObjectID( objectID, cookie );
            if ( b ) {
                // 各フォルダについて、年ごとのクリップ一覧を取得
                for ( i = 0; i < numOfFolders; i++) {
                    for (y = yyyy; y > 2003; y--) // 最古のクリップは2004年3月
                        getDrecomRSSclip( &mp, objectID, list[i].folderName,
                                          i, y, cookie, &num );
                }
            }

            free( list );
        }
    }

    *numOfClips = num;

    free( response );

    return ( mp );
}

#ifdef  GET_DRECOM_RSS_EXE
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
                 "getDrecom: Drecom RSS の Clip! → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tDrecom RSS の Clip! から吸い出した内容を OPML ファイル"
                 "として出力する\n" );
        fprintf( stderr,
                 "    getDrecom [-x] -u メールアドレス -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getDrecom: get bookmarks from Drecom RSS (Clip!), and "
                 "output them as OPML\n" );
        fprintf( stderr,
                 "    getDrecom [-x] -u mailaddress -p password\n" );
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

    /* Drecom RSS の Clip! へ登録済みのブックマークを取得 */
    mp = getDrecomRSS( username, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Drecom RSS の Clip! 情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "Drecom RSS", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_DRECOM_RSS_EXE */

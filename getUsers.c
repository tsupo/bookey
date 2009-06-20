/*
 *  指定 Web ページのブックマーク登録者数を取得する
 *      written by H.Tsujimura  28 Jun 2006
 *
 * $Log: /comm/bookey/getUsers.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    08/11/04 12:36 Tsujimura543
 * getUsersOfNiftyClip() で 404 が返ってきた場合にも対応
 * 
 * 13    08/11/04 12:25 Tsujimura543
 * getUsersOfNiftyClip() を追加
 * 
 * 12    07/09/05 1:48 Tsujimura543
 * getUsersOfMMmemo() に第2引数を追加(stat1470netを引数化)
 * 
 * 11    07/07/09 18:35 Tsujimura543
 * getUsersOfDigg() を追加
 * 
 * 10    07/03/01 21:40 Tsujimura543
 * getUsersOfMMmemo() を改修、MM/Memo が応答しない場合は、以後、
 * MM/Memo の API を呼び出さないようにした
 * 
 * 9     07/03/01 21:38 Tsujimura543
 * (1) getUsersOfDelicious() を改修(URLが長いとメモリ破壊が発生する不具合)
 * (2) getUsersOfLivedoorClip() を追加
 * 
 * 8     07/01/11 17:01 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 7     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 6     06/10/11 17:47 Tsujimura543
 * bookmark.getTotalCount (特定サイトの被はてなブックマーク数を取得する
 * XML-RPC API)を使って、はてブ登録済みユーザ数を求めるようにしてみた
 * 
 * 5     06/10/11 16:53 Tsujimura543
 * はてブのエントリページのフォーマット変更により、ブックマーク登録者数が
 * 取得できなくなってしまったため、新しいフォーマットに合わせて修正を実施
 * 
 * 4     06/07/11 22:49 Tsujimura543
 * ECナビ人気ニュースのブックマーク登録者数も表示するようにした
 * (ブックマーク登録画面/EditBookmarkDialog)
 * 
 * 3     06/07/03 14:19 Tsujimura543
 * getUsersOfMMmemo() を修正 (MM/Memo のサーバから期待とは違う応答が
 * 返ってきた場合に対応)
 * 
 * 2     06/06/29 10:26 Tsujimura543
 * バッファオーバーラン対策を実施
 * (はてなブックマークのエントリページ取得処理)
 * 
 * 1     06/06/28 15:54 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getUsers.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *getUsersOfHatenaBookmark( const char *url )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char    apiURL[MAX_URLLENGTH];
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 16;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    /* XML-RPC API (bookmark.getTotalCount) を実行 */
    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( users );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( users );
    }

    strcpy( apiURL, "http://b.hatena.ne.jp/xmlrpc" );
    sprintf( request,
             XML_STATEMENT
             "<methodCall>\r\n"
             "<methodName>bookmark.getTotalCount</methodName>\r\n"
             "<params>\r\n"
             "<param>\r\n"
             "<value><string>%s</string></value>\r\n"
             "</param>\r\n"
             "</params>\r\n"
             "</methodCall>",
             url );
    setUpReceiveBuffer( response, sz );
    http_post( apiURL, NULL,
               request, response );
    if ( *response ) {
        char    *p, *q;

        p = strstr( response, "flerror" );
        if ( !p ) {
            // 正常応答
            p = strstr( response, "<value><int>" );
            if ( p ) {
                p += 12;
                q = strstr( p, "</int></value>" );
                if ( q ) {
                    long    num = atol( p );

                    if ( num >= 0 )
                        sprintf( users, "(%d)", num );
                }
            }
        }

        if ( strcmp( users, "(?)" ) != 0 ) {
            free( response );
            free( request );
            return ( users );
        }
    }

    /* Hatena exist API を実行 */
    sprintf( apiURL,
             "http://d.hatena.ne.jp/exist?mode=xml&%s",
             encodeURL( url ) );
    setUpReceiveBuffer( response, sz );
    http_get( apiURL, response );
    if ( *response ) {
        char    *p, *q, *r;

        p = strstr( response, "<count name=\"bookmark\">" );
        if ( p ) {
            p += 23;
            q = strchr( p, '<' );
            if ( q ) {
                char    tmp[32];

                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                sprintf( users, "(%s)", tmp );

                strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                saveURL[MAX_URLLENGTH - 1] = NUL;
            }
        }
        else {
            // エントリページを取得
            //  -- エントリページは getTitle() でも取得しているので、2回も
            //     取得しに行くのはよくない(が、とりあえず、取得しに行く)
            sprintf( apiURL,
                     "http://b.hatena.ne.jp/entry/%s",
                     encodeURLforHatena( url ) );
            setUpReceiveBuffer( response, sz );
            http_get( apiURL, response );
            if ( *response ) {
                p = strstr( response, "<a name=\"comments\"" );
                if ( p ) {
                    int num = 0;

                    p += 18;
                    q = strstr( p, "</a> (" );
                    if ( q ) {
                        p = q + 6;
                        q = strstr(p, "<span class=\"public-count\" title=");
                        if ( q ) {
                            q = strstr( q + 32, "\">" );
                            if ( q )
                                q += 2;
                        }
                        r = strstr( p, ") <a href=\"/entry/" );
                        if ( q && r && (q < r) )
                            num = atol( p ) + atol( q );
                        else if ( r )
                            num = atol( p );
                    }

                    if ( num > 0 ) {
                        sprintf( users, "(%d)", num );

                        strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                        saveURL[MAX_URLLENGTH - 1] = NUL;
                    }
                }
            }
        }
    }

    free( response );
    free( request );

    return ( users );
}

char    *getUsersOfDelicious( const char *url )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char    *p;
    char    *apiURL;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    /* del.icio.us のブックマークページを取得 */
    response = (char *)malloc( sz );
    if ( !response )
        return ( users );

    p = encodeURL( url );
    apiURL = (char *)malloc( strlen(p) + 80 );
    if ( !apiURL ) {
        free( response );
        return ( users );
    }

    sprintf( apiURL, "http://del.icio.us/url/check?url=%s", p );
    setUpReceiveBuffer( response, sz );
    http_get( apiURL, response );
    if ( *response ) {
        char    *p, *q, *r;

        p = strstr( response, "<h4 class=\"smaller nom\">" );
        if ( p ) {
            p += 24;
            q = strstr( p, "</h4>" );
            if ( q ) {
                r = strstr( p, "this url has been saved by " );
                if ( r && (r < q) ) {
                    int num = atol( r + 27 );

                    sprintf( users, "(%d)", num );

                    strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                    saveURL[MAX_URLLENGTH - 1] = NUL;
                }
            }
        }
    }

    free( apiURL );
    free( response );

    return ( users );
}

char    *getUsersOfMMmemo( const char *url, BOOL *stat1470net )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char        *request;
    char        *response;
    size_t      sz = MAX_CONTENT_SIZE;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    if ( *stat1470net == FALSE )
        return ( users );

    /* 1470.net exist API を実行 */
    request  = (char *)malloc( BUFSIZ );
    if ( !request )
        return ( users );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( users );
    }
    memset( request, 0x00, BUFSIZ );

    sprintf( request, "url=%s", encodeURL( url ) );
    setUpReceiveBuffer( response, sz );
    http_post( "http://1470.net/api/exists.php",
               "application/x-www-form-urlencoded",
               request, response );

    if ( *response ) {
        char    *p, *q;

        p = strchr( response, '\t' );
        if ( p ) {
            p++;
            q = strchr( p, '\t' );
            if ( q && (q - p < 32) ) {
                char    tmp[32];

                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                sprintf( users, "(%s)", tmp );

                strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                saveURL[MAX_URLLENGTH - 1] = NUL;
            }
        }
    }
    else
        *stat1470net = FALSE;

    free( response );
    free( request );

    return ( users );
}


char    *getUsersOfECnaviClip( const char *url )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char    apiURL[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    /* Buzzurl のブックマーク登録者数を取得 */
    response = (char *)malloc( sz );
    if ( !response )
        return ( users );

    sprintf( apiURL, "http://buzzurl.jp/api/counter/%s",
             encodeURLforHatena( url ) );
    setUpReceiveBuffer( response, sz );
    http_get( apiURL, response );

    if ( *response ) {
        char    *p;
        char    gifURL[MAX_URLLENGTH];

        gifURL[0] = NUL;
        getCurrentLocation( gifURL );
        if ( gifURL[0] ) {
            // gifURL は 登録者数に対応する GIF 画像の URL になる
            //   例: http://buzzurl.jp/static/image/api/number/017.gif
            p = strrchr( gifURL, '/' );
            if ( p ) {
                p++;
                while ( *p == '0' )
                    p++;
                if ( (*p >= '1') && (*p <= '9') )
                    sprintf( users, "(%d)", atol(p) );
                else if ( *p == '.' )
                    strcpy( users, "(0)" );

                strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                saveURL[MAX_URLLENGTH - 1] = NUL;
            }
        }
    }

    free( response );

    return ( users );
}


char    *getUsersOfLivedoorClip( const char *url )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char    apiURL[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    /* livedoorクリップのブックマーク登録者数を取得 */
    response = (char *)malloc( sz );
    if ( !response )
        return ( users );

    sprintf( apiURL, "http://image.clip.livedoor.com/counter/small/%s",
             encodeURLforHatena( url ) );
    setUpReceiveBuffer( response, sz );
    http_get( apiURL, response );

    if ( *response ) {
        char    *p;
        char    pngURL[MAX_URLLENGTH];

        pngURL[0] = NUL;
        getCurrentLocation( pngURL );
        if ( pngURL[0] ) {
            // pngURL は 登録者数に対応する PNG 画像の URL になる
            //   例: http://image.clip.livedoor.com/img/users/small/00005.png
            p = strrchr( pngURL, '/' );
            if ( p ) {
                p++;
                while ( *p == '0' )
                    p++;
                if ( (*p >= '1') && (*p <= '9') )
                    sprintf( users, "(%d)", atol(p) );
                else if ( *p == '.' )
                    strcpy( users, "(0)" );

                strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                saveURL[MAX_URLLENGTH - 1] = NUL;
            }
        }
    }

    free( response );

    return ( users );
}


char    *getUsersOfDigg( const char *url )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char        *request;
    char        *response;
    size_t      sz = MAX_CONTENT_SIZE;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    /* Digg API を実行 */
    request  = (char *)malloc( sz );
    if ( !request )
        return ( users );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( users );
    }
    memset( request, 0x00, BUFSIZ );

    sprintf( request,
             "http://services.digg.com/stories?link=%s",
             encodeURL( url ) );
    sprintf( request + strlen(request),
             "&appkey=%s",
        encodeURL("http://watcher.moe-nifty.com/memo/2005/10/bookey.html") );
                                                        // IDS_BOOKEY_WEB_URL
    setUpReceiveBuffer( response, sz );
    http_get( request, response );

    if ( *response ) {
        char    *p, *q, *r;

        p = strstr( response, "<story id=\"" );
        if ( p ) {
            p += 11;
            q = strstr( p, " diggs=\"" );
            r = strchr( p, '>' );
            if ( q && r && (q < r) ) {
                q += 8;
                sprintf( users, "(%d)", atol(q) );
                strncpy( saveURL, url, MAX_URLLENGTH - 1 );
                saveURL[MAX_URLLENGTH - 1] = NUL;
            }
        }
    }

    free( response );
    free( request );

    return ( users );
}


char    *getUsersOfNiftyClip( const char *url )
{
    Thread  static char users[32];
    Thread  static char saveURL[MAX_URLLENGTH * 8];
    char    apiURL[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( users[0] && (strcmp( users, "(?)" ) != 0 ) )
        if ( !strncmp( url, saveURL, MAX_URLLENGTH - 1 ) )
            return ( users );
    strcpy( users, "(?)" );

    /* livedoorクリップのブックマーク登録者数を取得 */
    response = (char *)malloc( sz );
    if ( !response )
        return ( users );

    sprintf( apiURL,
             "http://api.clip.nifty.com/api/v1/counter?url=%s",
             encodeURL( url ) );
    setUpReceiveBuffer( response, sz );
    http_get( apiURL, response );

    if ( *response ) {
        char    *p = strstr( response, "<count>" );

        if ( p ) {
            p += 7;

            while ( (*p == ' ')  || (*p == '\t') ||
                    (*p == '\r') || (*p == '\n')    )
                p++;
            while ( *p == '0' )
                p++;
            if ( (*p >= '1') && (*p <= '9') )
                sprintf( users, "(%d)", atol(p) );
            else if ( *p == '.' )
                strcpy( users, "(0)" );

            strncpy( saveURL, url, MAX_URLLENGTH - 1 );
            saveURL[MAX_URLLENGTH - 1] = NUL;
        }
        else {
            p = strstr( response, "<code>404</code>" );
            if ( p )
                strcpy( users, "(0)" );
        }
    }

    free( response );

    return ( users );
}

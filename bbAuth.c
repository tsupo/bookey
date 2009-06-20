/*
 *  bbAuth.c
 *      Yahoo! Japan の BBAuth による認証を実行する
 *
 *          written by H.Tsujimura  14 Sep 2007 / 24 Oct 2007
 *
 * $Log: /comm/bookey/bbAuth.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    08/12/02 19:25 Tsujimura543
 * (1) 意味のない処理の削除
 * (2) メモリ解放忘れ対処
 * 
 * 13    07/12/06 5:09 Tsujimura543
 * コンパイル時に wininet.h 中で出る warning C4201 を抑制するようにした
 * 
 * 12    07/11/05 20:49 Tsujimura543
 * 様子見バージョン
 * 
 * 11    07/10/13 3:30 Tsujimura543
 * Buzzurl へのアクセスと newsing へのアクセスを連続で行なおうとすると、
 * newsing へのアクセス時に延々と「パスワードの再確認」が出続ける現象
 * あり。両者のアクセスの間にある程度時間を置けばとりあえず大丈夫。
 * 何かうまい対策はないか模索中。
 * 
 * 10    07/10/13 2:45 Tsujimura543
 * Buzzurl, newsing からのログアウト後、クッキーを削除するようにした
 * 
 * 9     07/10/13 2:39 Tsujimura543
 * デバッグ用のコードを整理
 * 
 * 8     07/10/13 2:35 Tsujimura543
 * newsing も BBAuth経由でログインできるようになった(動作確認済み)
 * [あとでリファクタリングする]
 * 
 * 7     07/10/10 17:49 Tsujimura543
 * (1) doYahooStep1() 内のログアウトによるリカバリ処理を廃止
 * (2) 代わりに _loginEcNaviOnBBAuth() 内にログアウトを試みる処理を挿入
 * 
 * 6     07/10/10 1:58 Tsujimura543
 * _loginEcNaviOnBBAuth() を修正 (修正し忘れていたところがあった)
 * 
 * 5     07/10/10 1:55 Tsujimura543
 * (1) デバッグ情報出力処理を追加
 * (2) _loginEcNaviOnBBAuth() を修正、cookie が有効な場合は再利用するよう
 *     にした
 * (3) doYahooStep1() 内のリカバリ処理を修正、Yahoo! 以外に、ターゲットの
 *     方からもいったんログアウトするようにした
 * 
 * 4     07/10/05 23:08 Tsujimura543
 * リトライ処理(+ リカバリ処理)を強化
 * 
 * 3     07/10/05 15:19 Tsujimura543
 * 複数回連続して BBAuth 経由でログインしようとすると、ログインに失敗する
 * ことがあることが判明。doYahooStep1() を修正することで対処した
 * 
 * 2     07/10/05 4:39 Tsujimura543
 * InternetConnect() に proxy ユーザ名・パスワード を渡す条件を修正
 * 
 * 1     07/10/05 2:38 Tsujimura543
 * 認証に成功することを確認
 */

#include "xmlRPC.h"
#include "MD5.h"
#pragma warning ( disable : 4201 )
#include <wininet.h>
#pragma warning ( default : 4201 )
#ifdef  _DEBUG_BBAUTH
#include <time.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bbAuth.c 1     09/05/14 3:48 tsupo $";
#endif


struct proxyInfo    {
    int             useProxy;
    char            proxyServer[MAX_SERVERNAME];
    unsigned short  proxyPort;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];
}   proxyInfoForBBAuth;


char *
ToLower( char *p )
{
    char    *s = p;
    while ( *s ) {
        if ( (*s >= 'A') && (*s <= 'Z') )
            *s = (char)((*s - 'A') + 'a');
        s++;
    }

    return ( p );
}

BOOL
parseURL(
        const char *address,
        char       *host,
        char       *webPage,
        BOOL       *useHttps
    )
{
    BOOL        ret = FALSE;
    const char  *p, *q;

    if ( !strncmp( address, "https://", 8 ) )
        *useHttps = TRUE;
    p = strstr( address, "://" );
    if ( !p )
        return ( ret );

    p += 3;
    q = strchr( p, '/' );
    if ( !q ) {
        strcpy( host, address );
        strcpy( webPage, "/" );
    }
    else {
        strncpy( host, p, q - address );
        host[q - p] = NUL;
        if ( *(q + 1) )
            strcpy( webPage, q + 1 );
        else
            strcpy( webPage, "/" );
    }

    ret = TRUE;
    return ( ret );
}


#ifdef  _DEBUG
void
dump( char *buffer, size_t sz )
{
    unsigned int    i, c;
    unsigned char   buf[80];

    dputs( ">>|\n" );
    for ( i = 0; i < sz; i++ ) {
        if ( (i != 0) && (i % 16 == 0) ) {
            buf[16] = NUL;
            dprintf( "    %s\n", buf );
        }
        if ( i % 16 == 0 )
            dprintf( "%08x:", &buffer[i] );
        c = buffer[i] & 0xFF;
        if ( (c >= ' ') && (c <= 0x7E) )
            buf[i % 16] = (unsigned char)c;
        else
            buf[i % 16] = '.';
        dprintf( " %02x", c & 0xFF );
    }
    if ( i % 16 == 0 )
        buf[16] = NUL;
    else {
        buf[i % 16] = NUL;
        for ( i = i % 16; i < 16; i++ )
            dputs( "   " );
    }
    dprintf( "    %s\n|<<\n\n", buf );
}
#endif  /* _DEBUG */


void
_openConnectionIC(
        HINTERNET  *hInet,
        HINTERNET  *hConn,
        const char *host,
        BOOL       useHttps
    )
{
    char    proxyServer[MAX_SERVERNAME + MAX_KEYLENGTH];

    proxyServer[0] = NUL;
    if ( proxyInfoForBBAuth.useProxy )
        sprintf( proxyServer, "%s:%d",
                 proxyInfoForBBAuth.proxyServer,
                 proxyInfoForBBAuth.proxyPort );

    *hInet = InternetOpen( 
             // "httpAuth/1.0 (written by H.Tsujimura)", /* ← Buzzurl はこれでも OK */
                "Mozilla/4.0 (compatible; MSIE 6.0)",    /* ← newsing はこっちじゃないと通らない */
                proxyInfoForBBAuth.useProxy ? INTERNET_OPEN_TYPE_PROXY
                                            : INTERNET_OPEN_TYPE_PRECONFIG,
                proxyInfoForBBAuth.useProxy ? proxyServer
                                            : NULL,
                proxyInfoForBBAuth.useProxy ? "<local>"
                                            : NULL,
                0 );
    if ( *hInet == NULL )
        return;

    *hConn = InternetConnect(
                *hInet,
                host,
                (INTERNET_PORT)
                    (useHttps ? INTERNET_DEFAULT_HTTPS_PORT
                              : INTERNET_DEFAULT_HTTP_PORT),
                proxyInfoForBBAuth.useProxy &&
                proxyInfoForBBAuth.proxyUserName[0]
                                            ? proxyInfoForBBAuth.proxyUserName
                                            : NULL,
                proxyInfoForBBAuth.useProxy &&
                proxyInfoForBBAuth.proxyPassword[0]
                                            ? proxyInfoForBBAuth.proxyPassword
                                            : NULL,
                INTERNET_SERVICE_HTTP,
                0, 0 );
    if ( *hConn == NULL ) {
        dputs( "_openConnectionIC(): 失敗\n" );
        InternetCloseHandle( *hInet );
        *hInet = NULL;
    }
}

void
_closeConnectionIC(
        HINTERNET hInet,
        HINTERNET hConn
    )
{
    if ( hConn )
        InternetCloseHandle( hConn );
    if ( hInet )
        InternetCloseHandle( hInet );
}


char    *
_httpGetIC(
        const char *address,
        char       *buffer,
        BOOL       withHeader,
        BOOL       escapeURL
    )
{
    HINTERNET   hInet;
    HINTERNET   hConn;
    HINTERNET   hReq;
    char        szBuf[BUFSIZ * 2 + 1];
    DWORD       dwSize;
    DWORD       dwIndex;
    BOOL        bret;
    char        host[MAX_PATH];
    char        webPage[MAX_WEBPAGENAME];
    BOOL        useHttps = FALSE;
    char        *tail = buffer;

    if ( escapeURL == FALSE ) {
        // newsing 対策
        char    *p;
        char    *q;

        p = strstr( address, "&done=http%3A%2F%2F" );
        if ( p ) {
            while ( (q = strstr( p, "%3A" )) != NULL ) {
                *q = ':';
                strcpy( q + 1, q + 3 );
            }
            while ( (q = strstr( p, "%2F" )) != NULL ) {
                *q = '/';
                strcpy( q + 1, q + 3 );
            }
        }
    }

    *buffer  = NUL;
    *webPage = NUL;
    parseURL( address, host, webPage, &useHttps );
    if ( !webPage )
        return ( buffer );

    _openConnectionIC( &hInet, &hConn, host, useHttps );
    if ( !hInet || !hConn )
        return ( buffer );

    // GET 対象の URL を設定
    hReq = HttpOpenRequest(
                hConn,
                "GET",
                webPage,
                NULL, NULL, NULL,
                useHttps ? INTERNET_FLAG_SECURE : 0,
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS  );
    if ( hReq == NULL ) {
        dputs( "HttpOpenRequest(): 失敗\n" );
        _closeConnectionIC( hInet, hConn );
        return ( buffer );
    }
    dprintf( "_httpGetIC(): GET %s\n", address );

    // GET リクエストを送信
    if( HttpSendRequest( hReq, NULL, 0, NULL, 0 ) != TRUE ) {
        DWORD   err = GetLastError();

        // HttpOpenRequest() で
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS
        // を設定しているのに、なぜかエラーが発生することがある

        if ( (err != ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR) &&
             (err != ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR)    ) {
            MessageBox( NULL,
                        "httpリクエストの送信処理でエラーが発生しました  ",
                        "http GET メソッド", MB_ICONHAND|MB_OK );
            InternetCloseHandle( hReq );
            _closeConnectionIC( hInet, hConn );
            return ( buffer );
        }

        // http ステータスコードの値に対応する後始末を実行
        dwIndex = 0;
        dwSize  = sizeof( szBuf ) - 1;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = HttpQueryInfo( hReq, 
                              HTTP_QUERY_STATUS_CODE,
                              szBuf, &dwSize, &dwIndex );
        if ( bret == TRUE ) {
            int statusCode = atol( szBuf );
            switch ( statusCode ) {
            case 301:
            case 302:
                dwSize = sizeof( szBuf ) - 1;
                memset( szBuf, 0x00, sizeof( szBuf ) );
                bret = HttpQueryInfo( hReq, 
                                      HTTP_QUERY_LOCATION,
                                      szBuf, &dwSize, &dwIndex );
                if ( bret == TRUE ) {
                    InternetCloseHandle( hReq );
                    _closeConnectionIC( hInet, hConn );

                    // リダイレクトを実行
                    dprintf( "_httpGetIC(): %s へリダイレクト\n", szBuf );
                    _httpGetIC( szBuf, buffer, FALSE, escapeURL );
                    return ( buffer );
                }
                break;
            }
        }
    }

    // レスポンスヘッダを受信
    bret    = TRUE;
    dwIndex = 0;
    while ( bret == TRUE ) {
        dwSize = sizeof( szBuf ) - 1;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = HttpQueryInfo( hReq, 
                              HTTP_QUERY_RAW_HEADERS_CRLF |
                              HTTP_QUERY_FLAG_NUMBER,
                              szBuf, &dwSize, &dwIndex );
        dwIndex++;
        if ( bret ) {
            if ( withHeader ) {
                memcpy( tail, szBuf, dwSize + 1 );
                tail += dwSize;
            }
#ifdef  _DEBUG
            dump( szBuf, dwSize );
#endif
        }
    }

    // レスポンス本体を受信
    bret = TRUE;
    while ( bret == TRUE ) {
        dwSize = 0;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = InternetReadFile( hReq,
                                 szBuf, sizeof( szBuf ) - 1, &dwSize );
        if ( bret ) {
            memcpy( tail, szBuf, dwSize );
            tail += dwSize;
        }
        if ( dwSize == 0 ) {
            if ( szBuf[0] ) {
                strcpy( tail, szBuf );
                tail += strlen( szBuf );
            }
            else
                *tail = NUL;
#ifdef  _DEBUG
            dump( buffer, tail - buffer );
#endif
            break;
        }
    }

    InternetCloseHandle( hReq );
    _closeConnectionIC( hInet, hConn );

#ifdef  _DEBUG_BBAUTH
    {
        FILE    *fp;
        char    filename[MAX_PATH];

        sprintf( filename, "./Debug/bbAuth_%d.html", time( NULL ) );
        fp = fopen( filename, "w" );
        if ( fp ) {
            fprintf( fp, "GET %s\n\n", address );
            fputs( buffer, fp );
            fclose( fp );
        }
    }
#endif

    return ( buffer );
}


char    *
_httpPostIC(
        const char *address,
        const char *request,
        char       *buffer,
        BOOL       escapeURL
    )
{
    HINTERNET   hInet;
    HINTERNET   hConn;
    HINTERNET   hReq;
    char        szBuf[BUFSIZ * 2 + 1];
    DWORD       dwSize;
    DWORD       dwIndex;
    BOOL        bret;
    char        host[MAX_PATH];
    char        webPage[MAX_WEBPAGENAME];
    BOOL        useHttps = FALSE;
    char        *tail = buffer;
    const char  *contentType =
                    "Content-Type: application/x-www-form-urlencoded";

    *buffer  = NUL;
    *webPage = NUL;
    parseURL( address, host, webPage, &useHttps );
    if ( !webPage )
        return ( buffer );

    _openConnectionIC( &hInet, &hConn, host, useHttps );
    if ( !hInet || !hConn )
        return ( buffer );

    hReq = HttpOpenRequest(
                hConn,
                "POST",
                webPage,
                NULL, NULL, NULL,
                useHttps ? INTERNET_FLAG_SECURE : 0,
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS  );
    if ( hReq == NULL ) {
        dputs( "HttpOpenRequest(): 失敗\n" );
        _closeConnectionIC( hInet, hConn );
        return ( buffer );
    }
    dprintf( "_httpPostIC(): POST %s\n>>\n%s\n<<\n", address, request );

    // requestを送信する
    bret = HttpSendRequest( hReq,
                            contentType, strlen(contentType),
                            (void *)request, strlen(request) );
    if( bret != TRUE ) {
        DWORD   err = GetLastError();

        // HttpOpenRequest() で
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS
        // を設定しているのに、なぜかエラーが発生することがある

        if ( (err != ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR) &&
             (err != ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR)    ) {
            MessageBox( NULL,
                        "httpリクエストの送信処理でエラーが発生しました  ",
                        "http POST メソッド", MB_ICONHAND|MB_OK );
            InternetCloseHandle( hReq );
            _closeConnectionIC( hInet, hConn );
            return ( buffer );
        }

        // http ステータスコードの値に対応する後始末を実行
        dwIndex = 0;
        dwSize  = sizeof( szBuf ) - 1;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = HttpQueryInfo( hReq, 
                              HTTP_QUERY_STATUS_CODE,
                              szBuf, &dwSize, &dwIndex );
        if ( bret == TRUE ) {
            int statusCode = atol( szBuf );
            switch ( statusCode ) {
            case 301:
            case 302:
                dwSize = sizeof( szBuf ) - 1;
                memset( szBuf, 0x00, sizeof( szBuf ) );
                bret = HttpQueryInfo( hReq, 
                                      HTTP_QUERY_LOCATION,
                                      szBuf, &dwSize, &dwIndex );
                if ( bret == TRUE ) {
                    InternetCloseHandle( hReq );
                    _closeConnectionIC( hInet, hConn );

                    // リダイレクトを実行
                    dprintf( "_httpPostIC(): %s へリダイレクト\n", szBuf );
                    _httpGetIC( szBuf, buffer, FALSE, escapeURL );
                    return ( buffer );
                }
                break;
            }
        }
    }

    // レスポンス本体を受信
    bret = TRUE;
    while ( bret == TRUE ) {
        dwSize = 0;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = InternetReadFile( hReq,
                                 szBuf, sizeof( szBuf ) - 1, &dwSize );
        if ( bret ) {
            memcpy( tail, szBuf, dwSize );
            tail += dwSize;
        }
        if ( dwSize == 0 ) {
            if ( szBuf[0] ) {
                strcpy( tail, szBuf );
                tail += strlen( szBuf );
            }
            else
                *tail = NUL;
#ifdef  _DEBUG
            dump( buffer, tail - buffer );
#endif
            break;
        }
    }

    InternetCloseHandle( hReq );
    _closeConnectionIC( hInet, hConn );

#ifdef  _DEBUG_BBAUTH
    {
        FILE    *fp;
        char    filename[MAX_PATH];

        sprintf( filename, "./Debug/bbAuth_%d.html", time( NULL ) );
        fp = fopen( filename, "w" );
        if ( fp ) {
            fprintf( fp, "POST %s\n",   address );
            fprintf( fp, ">>   %s\n\n", request );
            fputs( buffer, fp );
            fclose( fp );
        }
    }
#endif

    return ( buffer );
}


void
doYahooStep2(
        char       *buffer,
        char       *request,
        const char *target,
        char       *cookie,
        size_t     *cookieSize
    )
{
    // 「同意する」ボタンを押す
    const char  *p, *q;
    char        url[BUFSIZ * 2];

    dputs( "doYahooStep2(): 実行開始\n" );

    p = strstr( buffer, "<form action=\"" );
    if ( p ) {
        p += 14;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( url, p, q - p );
            url[q - p] = NUL;
        }

        strcpy( request, "na=0" );
        _httpPostIC( url, request, buffer, TRUE );
        if ( *buffer )
            InternetGetCookie( target,
                               "external_session",
                               cookie,
                               (unsigned long *)cookieSize );
    }
}


BOOL
doYahooStep1b(
        char       *buffer,
        char       *request,
        const char *username,
        const char *password
    )
{
    char    *p, *q;
    char    src[MAX_NAMELEN];
    char    done[MAX_WEBPAGENAME];
    char    challenge[MAX_KEYLENGTH];
    char    u[MAX_USERIDLEN];
    char    passwd[BUFSIZ * 2];
    char    url[MAX_WEBPAGENAME];
    int     tries     = 2;
    BOOL    usePost   = FALSE;
    BOOL    ret       = FALSE;
    BOOL    escapeURL = TRUE;

    dputs( "doYahooStep1b(): 実行開始\n" );

    // パスワードの再確認
    src[0]       = NUL;
    done[0]      = NUL;
    challenge[0] = NUL;
    u[0]         = NUL;
    passwd[0]    = NUL;

    if ( strstr( buffer, "name=\"login_form\">" ) )
        usePost = TRUE;

    p = strstr( buffer, "name=\".tries\" value=\"" );
    if ( p ) {
        p += 21;
        q = strchr( p, '"' );
        if ( q ) {
            char    buf[BUFSIZ];

            strncpy( buf, p, q - p );
            buf[q - p] = NUL;
            tries = atol( buf );
        }
    }

    p = strstr( buffer, "name=\".src\" value=\"" );
    if ( p ) {
        p += 19;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( src, p, q - p );
            src[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".done\" value=\"" );
    if ( p ) {
        p += 20;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( done, p, q - p );
            done[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".challenge\" value=\"" );
    if ( p ) {
        p += 25;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( challenge, p, q - p );
            challenge[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".u\" value=\"" );
    if ( p ) {
        p += 17;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( u, p, q - p );
            u[q - p] = NUL;
        }
    }

    sprintf( passwd, "%s%s", ToLower(MD5(password)), challenge );
    strcpy( passwd, ToLower( MD5( passwd ) ) );

    if ( !strcmp( src, "ba_newsing" ) )
        escapeURL = FALSE;

    if ( escapeURL ) {
        strcpy( done, translateURL( done ) );
        p = strstr( done, "appdata" );
        if ( p ) {
            char    *r;
            p += 7;
            while ( ((q = strstr( p, "%3A" )) != NULL) ||
                    ((q = strstr( p, "%2F" )) != NULL) ||
                    ((q = strstr( p, "%2E" )) != NULL)    ) {
                r = p + strlen( p );
                while ( r > q ) {
                    *(r + 2) = *r;
                    r--;
                }
                *++q = '2';
                *++q = '5';
            }
        }
    }

    if ( strstr( buffer, "name=\"promo\" value=\"" ) ) {
        strcpy( url,
            usePost ? "https://login.yahoo.co.jp/config/login?"
                    : "http://login.yahoo.co.jp/config/login?" );
        sprintf( request,
                 ".tries=%d&"
                 ".src=%s&"
                 ".md5=&"
                 ".hash=&"
                 ".js=1&"
                 ".last=&"
                 "promo=&"
                 ".intl=jp&"
                 ".bypass=&"
                 ".partner=&"
                 ".u=%s&"
                 ".v=0&"
                 ".challenge=%s&"
                 ".yplus=&"
                 ".emailCode=&"
                 "pkg=&"
                 "stepid=&"
                 ".ev=&"
                 "hasMsgr=0&"
                 ".chkP=Y&"
                 ".done=%s&"
                 ".pd=&"
                 ".protoctl=&"
                 "login=%s&"
                 "passwd=%s&"
                 ".persistent=y&"
                 ".hash=1&"
                 ".md5=1",
                 tries,
                 src,
                 u,
                 challenge,
                 done,
                 username,
                 passwd );
    }
    else {
        strcpy( url, 
                usePost ? "https://login.yahoo.co.jp/config/login_verify2?"
                        : "http://login.yahoo.co.jp/config/login_verify2?" );
        sprintf( request,
                 usePost ? ".src=%s&"
                           ".tries=%d&"
                           ".done=%s&"
                           ".md5=&"
                           ".hash=&"
                           ".js=&"
                           ".partner=&"
                           ".slogin=%s&"
                           ".intl=jp&"
                           ".fUpdate=&"
                           ".prelog=&"
                           ".bid=&"
                           ".aucid=&"
                           ".challenge=%s&"
                           ".yplus=&"
                           ".chldID=&"
                           "pkg=&"
                           "hasMsgr=0&"
                           ".pd=&"
                           ".protoctl=&"
                           ".u=%s&"
                           "passwd=%s"
                         : ".src=%s&"
                           ".tries=%d&"
                           ".done=%s&"
                           ".md5=&"
                           ".hash=&"
                           ".js=1&"
                           ".partner=&"
                           ".slogin=%s&"
                           ".intl=jp&"
                           ".fUpdate=&"
                           ".prelog=&"
                           ".bid=&"
                           ".aucid=&"
                           ".challenge=%s&"
                           ".yplus=&"
                           ".chldID=&"
                           "pkg=&"
                           "hasMsgr=0&"
                           ".pd=&"
                           ".protoctl=&"
                           ".u=%s&"
                           "passwd=%s&"
                           ".hash=1&"
                           ".md5=1",
                 src,
                 tries,
                 done,
                 username,
                 challenge,
                 u,
                 usePost ? password : passwd );
    }
    if ( usePost ) {
        p = strstr( buffer, "<form method=\"post\" action=\"" );
        if ( p ) {
            p += 28;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( url, p, q - p );
                url[q - p] = NUL;
            }
        }

#ifdef  _DEBUG
        {
            FILE    *fp = fopen( "./bbauthPost.html", "w" );
            fputs( buffer, fp );
            fclose( fp );
        }
#endif

        _httpPostIC( url, request, buffer, escapeURL );

#ifdef  _DEBUG
        {
            FILE    *fp = fopen( "./bbauthPost2.html", "w" );
            fputs( buffer, fp );
            fclose( fp );
        }
#endif
    }
    else {
        strcat( url, request );
        _httpGetIC( url, buffer, FALSE, escapeURL );
    }
    if ( *buffer ) {
        if ( strstr( buffer, "<input type=\"submit\" class=\"fakebutton\"" ) )
            ret = TRUE;
    }

    return ( ret );
}

void
doYahooStep1a(
        char       *buffer,
        char       *request,
        const char *target,
        const char *username,
        const char *password,
        char       *cookie,
        size_t     *cookieSize
    )
{
    int retry = 5;

    while ( strstr( buffer, sjis2euc("パスワードの再確認") ) ) {
        Sleep( 2000 );
        doYahooStep1b( buffer, request, username, password );
        if ( strstr( buffer,
                     "<input type=\"submit\" class=\"fakebutton\"" ) )
            break;

        retry--;
        if ( retry <= 0 )
            break;
    }

    if ( strstr( buffer, "<input type=\"submit\" class=\"fakebutton\"" ) )
        doYahooStep2( buffer, request, target, cookie, cookieSize );
}


void
doYahooStep1(
        char       *buffer,
        const char *target,
        const char *username,
        const char *password,
        char       *cookie,
        size_t     *cookieSize
    )
{
    char    *request;
    char    *p, *q;
    char    src[MAX_NAMELEN];
    char    done[MAX_WEBPAGENAME];
    char    challenge[MAX_KEYLENGTH];
    char    u[MAX_USERIDLEN];
    char    passwd[BUFSIZ * 2];
    char    url[BUFSIZ * 2];
    int     tries     = 1;
    BOOL    escapeURL = TRUE;

    dputs( "doYahooStep1(): 実行開始\n" );

    // Yahoo! Japan にログイン
    request  = (char *)malloc( RCV_BUFFER_SIZE );
    if ( !request ) 
        return;

    src[0]       = NUL;
    done[0]      = NUL;
    challenge[0] = NUL;
    u[0]         = NUL;
    passwd[0]    = NUL;

    p = strstr( buffer, "name=\".tries\" value=\"" );
    if ( p ) {
        p += 21;
        q = strchr( p, '"' );
        if ( q ) {
            char    buf[BUFSIZ];

            strncpy( buf, p, q - p );
            buf[q - p] = NUL;
            tries = atol( buf );
        }
    }

    p = strstr( buffer, "name=\".src\" value=\"" );
    if ( p ) {
        p += 19;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( src, p, q - p );
            src[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".done\" value=\"" );
    if ( p ) {
        p += 20;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( done, p, q - p );
            done[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".challenge\" value=\"" );
    if ( p ) {
        p += 25;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( challenge, p, q - p );
            challenge[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".u\" value=\"" );
    if ( p ) {
        p += 17;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( u, p, q - p );
            u[q - p] = NUL;
        }
    }

    sprintf( passwd, "%s%s", ToLower(MD5(password)), challenge );
    strcpy( passwd, ToLower( MD5( passwd ) ) );

    strcpy( done, translateURL( done ) );
    p = strstr( done, "appdata" );
    if ( p ) {
        char    *r;
        p += 7;
        while ( ((q = strstr( p, "%3A" )) != NULL) ||
                ((q = strstr( p, "%2F" )) != NULL) ||
                ((q = strstr( p, "%2E" )) != NULL)    ) {
            r = p + strlen( p );
            while ( r > q ) {
                *(r + 2) = *r;
                r--;
            }
            *++q = '2';
            *++q = '5';
        }
    }

    strcpy( url, "http://login.yahoo.co.jp/config/login?" );
    sprintf( request,
             ".tries=%d&"
             ".src=%s&"
             ".md5=&"
             ".hash=&"
             ".js=1&"
             ".last=&"
             "promo=&"
             ".intl=jp&"
             ".bypass=&"
             ".partner=&"
             ".u=%s&"
             ".v=0&"
             ".challenge=%s&"
             ".yplus=&"
             ".emailCode=&"
             "pkg=&"
             "stepid=&"
             ".ev=&"
             "hasMsgr=0&"
             ".chkP=Y&"
             ".done=%s&"
             ".pd=&"
             ".protoctl=&"
             "login=%s&"
             "passwd=%s&"
             ".persistent=y&"
             ".hash=1&"
             ".md5=1",
             tries,
             src,
             u,
             challenge,
             done,
             username,
             passwd );
    strcat( url, request );

    if ( !strcmp( src, "ba_newsing" ) )
        escapeURL = FALSE;

    _httpGetIC( url, buffer, FALSE, escapeURL );
    if ( *buffer )
        doYahooStep1a( buffer, request, target,
                       username, password, cookie, cookieSize );

    free( request );
}


void
logoutYahooJapan( char *buffer )
{
    char    *p, *q;
    char    cookie[MAX_COOKIE_LEN + 1];

    _httpGetIC( "http://www.yahoo.co.jp/", buffer, FALSE, TRUE );
    p = strstr( buffer, sjis2euc("ログアウト</a>") );
    if ( p ) {
        while ( (p > buffer) && (strncmpi( p, " href=\"", 7 ) != 0) )
            p--;
        if ( !strncmpi( p, " href=\"", 7 ) ) {
            p += 7;
            q = strchr( p, '"' );
            if ( q ) {
                char    url[BUFSIZ * 2];

                strncpy( url, p, q - p );
                url[q - p] = NUL;
                if ( url[0] == '/' ) {
                    char    buf[BUFSIZ];

                    sprintf( buf, "http://www.yahoo.co.jp%s", url );
                    strcpy( url, buf );
                }

                // Yahoo! Japan からログアウトする
                _httpGetIC( url, buffer, FALSE, TRUE );

                // クッキーを削除
                cookie[0] = NUL;
                InternetSetCookie( "http://www.yahoo.co.jp/", NULL, cookie );

                _httpGetIC( "http://www.yahoo.co.jp/", buffer, FALSE, TRUE );
                p = strstr( buffer, sjis2euc("ログイン</a>") );
                if ( !p )
                    logoutYahooJapan( buffer );
            }
        }
    }
}


void
getLoginAddressOnYahooJapan(
        const char *target,
        char       *buffer,
        char       *address,
        BOOL       escapeURL
    )
{
    _httpGetIC( target, buffer, FALSE, escapeURL );
    if ( *buffer ) {
        char    *p, *q;

        p = strstr( buffer, "<a href=\"https://api.login.yahoo.co.jp/" );
        if ( p ) {
            p += 9;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( address, p, q - p );
                address[q - p] = NUL;

                while ( (p = strstr( address, "&amp;" ) ) != NULL )
                    strcpy( p + 1, p + 5 );
            }
        }
    }
}


BOOL
_loginEcNaviOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    )
{
    BOOL        ret     = FALSE;
    const char  *target = "http://buzzurl.jp/";
    char        address[MAX_WEBPAGENAME];
    char        *p;
    char        *buffer = (char *)malloc( MAX_CONTENT_SIZE * 16 );

    *cookie = NUL;
    if ( !buffer )
        return ( ret );

    // proxy 情報取得
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    proxyInfoForBBAuth.useProxy         = FALSE;
    proxyInfoForBBAuth.proxyServer[0]   = NUL;
    proxyInfoForBBAuth.proxyPort        = 0;
    proxyInfoForBBAuth.proxyUserName[0] = NUL;
    proxyInfoForBBAuth.proxyPassword[0] = NUL;
    getProxyInfo( &(proxyInfoForBBAuth.useProxy),
                  proxyInfoForBBAuth.proxyServer,
                  &(proxyInfoForBBAuth.proxyPort),
                  proxyInfoForBBAuth.proxyUserName,
                  proxyInfoForBBAuth.proxyPassword );

    // 複数ユーザで同一PCを使っている場合もあり得るので、ログイン状態であれば
    // 念のためにいったんログアウトしておく
    _httpGetIC( target, buffer, FALSE, TRUE );
    p = strstr( buffer, "/config/logout" );
    if ( p ) {
        // Buzzurl からログアウトする
        _httpGetIC( "http://buzzurl.jp/config/logout", buffer, FALSE, TRUE );

        // クッキーを削除
        cookie[0] = NUL;
        InternetSetCookie( target, NULL, cookie );
    }

    // Yahoo! Japan からログアウトする
    logoutYahooJapan( buffer );

    // Buzzurl向けBBAuth開始URLを取得
    getLoginAddressOnYahooJapan( "https://buzzurl.jp/config/login?"
                                 "done=http%3A%2F%2Fbuzzurl.jp%2F",
                                 buffer, address, TRUE );

    // BBAuth 開始
    _httpGetIC( address, buffer, FALSE, TRUE );
    if ( *buffer ) {
        doYahooStep1( buffer, target, username, password,
                      cookie, cookieSize );
        if ( *cookie )
            ret = TRUE;
    }
    translateURL( NULL );
    free( buffer );

    return ( ret );
}

BOOL
_loginNewsingOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    )
{
    BOOL        ret     = FALSE;
    const char  *target = "http://newsing.jp/";
    char        address[MAX_WEBPAGENAME];
    char        *p;
    char        *buffer = (char *)malloc( MAX_CONTENT_SIZE * 16 );
    BOOL        done    = FALSE;
    int         retry   = 5;

    *cookie = NUL;
    if ( !buffer )
        return ( ret );

    // proxy 情報取得
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    proxyInfoForBBAuth.useProxy         = FALSE;
    proxyInfoForBBAuth.proxyServer[0]   = NUL;
    proxyInfoForBBAuth.proxyPort        = 0;
    proxyInfoForBBAuth.proxyUserName[0] = NUL;
    proxyInfoForBBAuth.proxyPassword[0] = NUL;
    getProxyInfo( &(proxyInfoForBBAuth.useProxy),
                  proxyInfoForBBAuth.proxyServer,
                  &(proxyInfoForBBAuth.proxyPort),
                  proxyInfoForBBAuth.proxyUserName,
                  proxyInfoForBBAuth.proxyPassword );

    // 複数ユーザで同一PCを使っている場合もあり得るので、ログイン状態であれば
    // 念のためにいったんログアウトしておく
    _httpGetIC( target, buffer, FALSE, TRUE );
    p = strstr( buffer, "/logout\">" );
    if ( p ) {
        // newsing からログアウトする
        _httpGetIC( "http://newsing.jp/logout", buffer, FALSE, TRUE );

        // クッキーを削除
     // cookie[0] = NUL;
     // InternetSetCookie( target, NULL, cookie );
    }

    done = FALSE;
    do {
        // Yahoo! Japan からログアウトする
        logoutYahooJapan( buffer );
     // Sleep( 10000 );

        // newsing向けBBAuth開始URLを取得
        getLoginAddressOnYahooJapan( "http://newsing.jp/login",
                                     buffer, address, FALSE );

        // BBAuth 開始
        _httpGetIC( address, buffer, FALSE, FALSE );
        if ( strstr( buffer, sjis2euc("パスワードの再確認") ) ) {
            char    *request  = (char *)malloc( RCV_BUFFER_SIZE );
            if ( request ) {
                doYahooStep1a( buffer, request, target,
                               username, password, cookie, cookieSize );
                free( request );
                if ( *cookie )
                    break;
            }
            retry--;
            if ( retry <= 0 )
                break;
        }
        else
            done = TRUE;
    } while ( !done );

    if ( done )
        if ( !(*cookie) )
            doYahooStep1( buffer, target, username, password,
                          cookie, cookieSize );
    if ( *cookie )
        ret = TRUE;

    translateURL( NULL );
    free( buffer );

    return ( ret );
}

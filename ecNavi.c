/*
 *  ecNavi.c
 *      Buzzurl に login する
 *          written by H.Tsujimura  29 Jun 2006
 *
 * $Log: /comm/bookey/ecNavi.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    08/11/18 1:11 Tsujimura543
 * loginEcNavi() にもキャッシュを導入
 * 
 * 14    07/10/09 20:21 Tsujimura543
 * dputs() を導入
 * 
 * 13    07/10/05 23:08 Tsujimura543
 * リトライ処理(+ リカバリ処理)を強化
 * 
 * 12    07/10/05 3:02 Tsujimura543
 * loginEcNaviOnBBAuth() の cookie 設定処理を修正
 * 
 * 11    07/10/05 2:44 Tsujimura543
 * BBAuth 経由でのログイン成功を確認
 * 
 * 10    07/09/20 20:57 Tsujimura543
 * コメントを整理
 * 
 * 9     07/09/20 20:51 Tsujimura543
 * いったん、ソースコードを整理
 * 
 * 8     07/09/20 20:45 Tsujimura543
 * BBAuth 経由でのアクセス対応 (少し前進。まだ完成していない)
 * 
 * 7     07/09/19 21:39 Tsujimura543
 * BBAuth 経由でのアクセス対応 (つづき。まだ作業中)
 * 
 * 6     07/09/14 23:26 Tsujimura543
 * BBAuth 経由でのアクセス対応 (まだ途中)
 * 
 * 5     07/02/01 17:44 Tsujimura543
 * 2007年2月1日付で login 直後の html ページの内容が変わったため、
 * それにあわせて login に成功したかどうかのチェックの仕方を変更した
 * 
 * 4     07/01/11 11:35 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 3     06/10/18 19:42 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 2     06/10/10 16:49 Tsujimura543
 * ECナビ人気ニュースの Webページの charSet が EUC-JP から UTF-8 に
 * 変更されたのに伴う修正を実施
 * 
 * 1     06/06/29 18:28 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"
#include "MD5.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/ecNavi.c 1     09/05/14 3:48 tsupo $";
#endif


/* Buzzurl に login する */
int
loginEcNavi(
        const char *username,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    ) {
        /* キャッシュクリア */
        firstTime = 0;
        return ( ret );
    }

    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* キャッシュの有効時間を1時間とする */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        if ( saveCookie[0] )
            dputs( "loginEcNavi(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginEcNavi(): キャッシュを利用\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ログイン成功 */
        return ( ret );
    }

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

#ifdef  BEFORE_20070110
    strcpy( url, "https://ecnavi.jp/login/scripts/login.php" );
    setTargetURL( url );
    sprintf( request,
             "URL=%s&"
             "email=%s&"
             "passwd=%s&",
             encodeURL("http://news.ecnavi.jp/"),
             username, password );
    sprintf( request + strlen(request),
             "formSend=%s",
             encodeURL( sjis2utf("　ログイン　") ) );
#else
    strcpy( url, "https://buzzurl.jp/config/login/execute" );
    setTargetURL( url );
    sprintf( request,
             "done=%s&"
             "mail=%s&"
             "pass=%s&",
             encodeURL("http://buzzurl.jp/"),
             username, password );
    sprintf( request + strlen(request),
             "login_button=%s",
             encodeURL( sjis2utf("　ログイン　") ) );
#endif
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( (strstr(response, "/config/logout") != NULL) ||
             (strstr(cookie, "Apache=") != NULL)             )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }
    else
        ret = 0;        /* ログイン失敗 */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginEcNavi(): ログイン成功、キャッシュに保存\n" );
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
    }
    else {
        /* キャッシュを破棄 */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        firstTime       = 0;
    }

    return ( ret );
}



BOOL
_loginEcNaviOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    );

/* Yahoo! Japan ID で Buzzurl に login する */
int
loginEcNaviOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    )
{
    int             ret   = 0;
    int             retry = 5;
    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    ) {
        /* キャッシュクリア */
        firstTime = 0;
        return ( ret );
    }

    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* キャッシュの有効時間を1時間とする */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        if ( saveCookie[0] )
            dputs( "loginEcNaviOnBBAuth(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginEcNaviOnBBAuth(): キャッシュを利用\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ログイン成功 */
        return ( ret );
    }

    do {
        _loginEcNaviOnBBAuth( username, password, cookie, cookieSize );
        retry--;
        if ( retry <= 0 )
            break;
    } while ( !cookie || !(*cookie) );

    if ( cookie && *cookie ) {
        char        external_session[BUFSIZ];
        char        apache[BUFSIZ];
        const char  *p, *q;

        external_session[0] = NUL;
        apache[0]           = NUL;

        p = strstr( cookie, "external_session" );
        if ( p ) {
            q = strchr( p, ';' );
            if ( !q )
                q = p + strlen( p );
            strncpy( external_session, p, q - p );
            external_session[q - p] = NUL;
        }

        p = strstr( cookie, "Apache" );
        if ( p ) {
            q = strchr( p, ';' );
            if ( !q )
                q = p + strlen( p );
            strncpy( apache, p, q - p );
            apache[q - p] = NUL;
        }

        if ( external_session[0] && apache[0] )
            sprintf( cookie, "Cookie: %s; %s; SESSION\r\n",
                     external_session, apache );

        ret = 1;
    }

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginEcNaviOnBBAuth(): ログイン成功、キャッシュに保存\n" );
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
    }
    else {
        /* キャッシュを破棄 */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        firstTime       = 0;
    }

    return ( ret );
}

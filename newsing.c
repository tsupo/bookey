/*
 *  newsing.c
 *      newsing に login する
 *          written by H.Tsujimura  29 Sep 2006
 *
 * History:
 * $Log: /comm/bookey/newsing.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/11/18 1:08 Tsujimura543
 * loginNewsing() にもキャッシュを導入
 * 
 * 5     08/10/20 14:22 Tsujimura543
 * logiｎページからトップページへ遷移するまでの間に挿入される中間ページ
 * の内容が変更されたのに伴う修正を実施
 * 
 * 4     07/10/13 2:40 Tsujimura543
 * BBAuth 経由でのアクセスができることを確認
 * 
 * 3     07/10/12 13:56 Tsujimura543
 * BBAuth 経由でのアクセスに対応 (まだ、_loginNewsingOnBBAuth() が
 * 期待通り動いていないため、実際にはアクセスはできない状態)
 * 
 * 2     07/10/10 23:09 Tsujimura543
 * ログイン成功・失敗の判定条件を修正
 * 
 * 1     06/09/29 23:42 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/newsing.c 1     09/05/14 3:48 tsupo $";
#endif

/* newsing に login する */
int
loginNewsing(
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
            dputs( "loginNewsing(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginNewsing(): キャッシュを利用\n" );
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
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://newsing.jp/index.php" );
    sprintf( request,
             "address=%s&"
             "password=%s&"
             "autologin=1&",
             username, password );
    sprintf( request + strlen(request),
             "submit=%s&"
             "action_login=1&"
             "rurl=/login",
             encodeURL( sjis2euc("ログイン") ) );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        char    *p, *q;

        p = strstr(response, "<meta http-equiv=\"Refresh\" content=\"1;URL=");
        if ( p ) {
            p += 42;
            q = strchr( p, '"' );
            if ( q ) {
                int len = 0;
                url[0] = NUL;
                if ( strncmp( p, "http://", 7 ) != 0 ) {
                    strcpy( url, "http://newsing.jp" );
                    len = strlen( url );
                }
                strncat( url, p, q - p );
                url[len + (q - p)] = NUL;
                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );
            }
        }

        if ( *response ) {
            if ( strstr( response, "/logout\">" )   ||
                 strstr( cookie, "NewsingSESSID=" )    )
                ret = 1;    /* ログイン成功 */
            else
                ret = 0;    /* ログイン失敗 */
        }
    }
    else
        ret = 0;        /* ログイン失敗 */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginNewsing(): ログイン成功、キャッシュに保存\n" );
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
_loginNewsingOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    );

/* Yahoo! Japan ID で newsing に login する */
int
loginNewsingOnBBAuth(
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
            dputs( "loginNewsingOnBBAuth(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginNewsingOnBBAuth(): キャッシュを利用\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ログイン成功 */
        return ( ret );
    }

    do {
        _loginNewsingOnBBAuth( username, password, cookie, cookieSize );
        retry--;
        if ( retry <= 0 )
            break;
    } while ( !cookie || !(*cookie) );

    if ( cookie && *cookie ) {
        char        sessionID[BUFSIZ];
        const char  *p, *q;

        sessionID[0] = NUL;

        p = strstr( cookie, "NewsingSESSID" );
        if ( p ) {
            q = strchr( p, ';' );
            if ( !q )
                q = p + strlen( p );
            strncpy( sessionID, p, q - p );
            sessionID[q - p] = NUL;
        }

        if ( sessionID[0] )
            sprintf( cookie, "Cookie: %s\r\n",
                     sessionID );

        ret = 1;
    }

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginNewsingOnBBAuth(): ログイン成功、キャッシュに保存\n" );
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

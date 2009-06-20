/*
 *  digg.c
 *      digg に login する
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/digg.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/11/18 1:26 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 1     07/07/09 19:54 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/digg.c 1     09/05/14 3:48 tsupo $";
#endif

int
loginDigg(
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
            dputs( "loginDigg(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginDigg(): キャッシュを利用\n" );
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

    strcpy( url, "http://digg.com/login" );
    setTargetURL( url );
    sprintf( request,
             "side-username=%s&"
             "side-password=%s&"
             "side-persistent=1&",
             username, password );
    sprintf( request + strlen(request),
             "submit=%s&"
             "returnpage=/&"
             "processlogin=1",
             "Sign+In" );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( strstr( response, "/logout" ) != NULL )
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
        dputs( "loginDigg(): ログイン成功、キャッシュに保存\n" );
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


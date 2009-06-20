/*
 *  jugemkey.c
 *      jugemkey で login する
 *          written by H.Tsujimura  4 Oct 2006
 *
 * $Log: /comm/bookey/jugemkey.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/11/18 1:20 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 3     07/01/30 0:32 Tsujimura543
 * ログイン処理を再修正 (クッキーのフォーマットが変だったのは一時的な現象
 * らしい。サーバの負荷が重いとクッキーの払い出し処理が変になるのかも)
 * 
 * 2     07/01/30 0:01 Tsujimura543
 * login 処理を修正 (cookie のフォーマットが変更された)
 * 
 * 1     06/10/04 21:48 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/jugemkey.c 1     09/05/14 3:48 tsupo $";
#endif


/* jugemkey で login する */
int
loginJugemkey(
        const char *username,   // (I)   jugemkey
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 4;

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
            dputs( "loginJugemkey(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginJugemkey(): キャッシュを利用\n" );
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

    do {
        memset( request,  0x00, MAX_CONTENT_SIZE );
        setUpReceiveBuffer( response, sz );
        strcpy( url, "http://pookmark.jp/ajax/login" );
        setTargetURL( url );
        sprintf( request,
                 "username=%s&"
                 "password=%s&"
                 "cookie=on&"
                 "_=",
                 username, password );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response && *cookie ) {
            if ( (strstr( cookie, "username=" ) != NULL) &&
                 (strstr( cookie, "POOKMARK=" ) != NULL)    )
                ret = 1;    /* ログイン成功 */
            else
                ret = 0;    /* ログイン失敗 */
        }
        else
            ret = 0;        /* ログイン失敗 */

        if ( ret == 0 ) {
            retry--;
            if ( retry <= 0 )
                break;
            Sleep( 2000 );
        }
    } while ( ret == 0 );

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginJugemkey(): ログイン成功、キャッシュに保存\n" );
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

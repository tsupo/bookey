/*
 *  joltMark.c
 *      JoltMark に login する
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/joltMark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     08/11/18 1:20 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 1     06/12/21 16:53 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/joltMark.c 1     09/05/14 3:48 tsupo $";
#endif


/* JoltMark に login する */
int
loginJoltMark(
        const char *username,   // (I)   ユーザ名
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
            dputs( "loginJoltMark(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginJoltMark(): キャッシュを利用\n" );
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

        strcpy( url, "https://mark.jolt.jp/login.do" );
        setTargetURL( url );
        sprintf( request,
                 "userId=%s&"
                 "password=%s&"
                 "autoLogin=on&"
                 "login=%s",
                 username, password,
                 encodeURL(sjis2utf("ログイン")) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            char    *p, *q;

            p = strstr( response,
                        "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=" );
            if ( p ) {
                p += 42;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                    setUpReceiveBuffer( response, sz );
                    http_getEx( url, response, cookie );
                }
            }

            if ( *response ) {
                if ( strstr( response, sjis2utf("でログイン中") ) != NULL )
                    ret = 1;    /* ログイン成功 */
                else
                    ret = 0;    /* ログイン失敗 */
            }
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
        dputs( "loginJoltMark(): ログイン成功、キャッシュに保存\n" );
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

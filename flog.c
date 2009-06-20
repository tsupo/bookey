/*
 *  flog.c
 *      Flog に login する
 *          written by H.Tsujimura  31 May 2006
 *
 * $Log: /comm/bookey/flog.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/11/18 1:26 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 2     06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 1     06/05/31 17:42 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/flog.c 1     09/05/14 3:48 tsupo $";
#endif


/* Flog に login する */
int
loginFlog(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    )
{
    int     ret = 0;    /* 初期値は「login 失敗」 */
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !userName || !(*userName) ||
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
        else if ( ( strcmp( userName, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        if ( saveCookie[0] )
            dputs( "loginFlog(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginFlog(): キャッシュを利用\n" );
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

    strcpy( url, "http://www.flog.jp/login.php" );
    sprintf( request,
             "m=%s&"
             "p=%s&"
             "submit=%s",
             userName, password, encodeURL("ログイン") );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "ログインが完了しました" ) != NULL ) {
            if ( !(cookie[0]) ) {
                /*
                 * html ソースの中に、cookie をセットするための JavaScript が
                 * 記述されている。この記述を元に cookie を組み立てる
                 *
                 * 例)
                 *     document.cookie = 'MDMD=8317558c2959e8bdb7d774dd77c9b8
                 *     72 ; expires=Thu,05-Jan-30 00:00:01 GMT; path=/;';docu
                 *     ment.cookie = 'DMDM=' + 'tsupo@na.rim.or.jp' + ' ; exp
                 *     ires=Thu,05-Jan-30 00:00:01 GMT; path=/;';var name = e
                 *     scape("tsupo");document.cookie = "NAME =" + name +"; e
                 *     xpires=Thu,05-Jan-10 00:00:01 GMT; path=/";
                 *      ↓
                 *     MDMD=8317558c2959e8bdb7d774dd77c9b872; DMDM=tsupo@na.r
                 *     im.or.jp; NAME=tsupo
                 */
                char    *p, *q, *r;
                p = strstr( response, "document.cookie = '" );
                if ( p ) {
                    p += 19;
                    q = strchr( p, ';' );
                    if ( q ) {
                        r = q + 1;
                        while ( *(q - 1) == ' ' )
                            q--;
                        strcpy( cookie, "Cookie: " );
                        strncat( cookie, p, q - p );
                        cookie[8 + (q - p)] = NUL;
                        sprintf( cookie + strlen( cookie ),
                                 "; DMDM=%s; NAME=", userName );
                        p = strstr( r, "name = escape(\"" );
                        if ( p ) {
                            p += 15;
                            q = strchr( p, '"' );
                            if ( q ) {
                                int len = strlen( cookie );
                                strncat( cookie, p, q - p );
                                cookie[len + (q - p)] = NUL;
                                ret = 1;    /* login 成功 */
                            }
                        }
                    }
                }
            }
            else
                ret = 1;    /* login 成功 */
        }
        else
            ret = 0;        /* login 失敗 */
    }
    else
        ret = 0;            /* login 失敗 */

    free( response );
    free( request );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginFlog(): ログイン成功、キャッシュに保存\n" );
        strcpy( saveUserName, userName );
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

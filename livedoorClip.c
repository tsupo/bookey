/*
 *  livedoorClip.c
 *      livedoor クリップ に login する
 *          written by H.Tsujimura  28 Jun 2006
 *
 * $Log: /comm/bookey/livedoorClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     08/11/18 1:20 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 8     08/07/28 15:29 Tsujimura543
 * getApiKeyOnLivedoorClip() を追加
 * 
 * 7     08/03/10 14:58 Tsujimura543
 * 「ログイン直後に表示される Web ページ」の仕様変更(2008年3月8日に
 * 実施?)にあわせて、login処理を更新
 * 
 * 6     07/11/07 5:02 Tsujimura543
 * 2007年11月6日に実施された微妙な変更に対応 (ログイン成功/失敗判定条件
 * を改定) [livedoorクリップの Google Analytics 導入による変更の模様]
 * 
 * 5     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 4     06/07/31 17:43 Tsujimura543
 * コメントを修正
 * 
 * 3     06/07/31 17:42 Tsujimura543
 * (1) ログイン直後の Web ページのサイズが大きくなった(2006年7月31日未明
 *     以降)ため、バッファーオーバーランが発生し、bookeyが異常終了するよ
 *     うになってしまったため、受信電文格納領域サイズを増やし、さらにオー
 *     バーラン防止機能を組み込んだ
 * (2) login 失敗時、最大5回までリトライするようにした (たまに login に失
 *     敗することがあるため)
 * 
 * 2     06/06/29 17:04 Tsujimura543
 * コメントを修正
 * 
 * 1     06/06/29 0:02 Tsujimura543
 * 最初の版 (動作確認済み) [livedoor Blog への login 処理を元に作成]
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/livedoorClip.c 1     09/05/14 3:48 tsupo $";
#endif


/* livedoor クリップ に login する */
int
loginLivedoorClip(
        const char *username,   // (I)   ユーザ名 (livedoor ID)
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
            dputs( "loginLivedoorClip(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginLivedoorClip(): キャッシュを利用\n" );
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
        http_getEx( "http://clip.livedoor.com/",
                    response, cookie );

        strcpy( url, "http://member.livedoor.com/login/index" );
        setTargetURL( url );
        sprintf( request,
                 ".next=%s&"
                 ".sv=clip&"
                 "livedoor_id=%s&"
                 "password=%s&"
                 "auto_login=on\r\n",
                 encodeURL("http://clip.livedoor.com/register/"),
                 username, password );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            if ( strstr( response, "<a href=\"/logout\">" ) ||
                 strstr( response, "<a href=\"/logout\" " ) ||
                 strstr( response, "/logout\"" )            ||
                 strstr( response, "/logout\'" )               )
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
        dputs( "loginLivedoorClip(): ログイン成功、キャッシュに保存\n" );
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


char    *
getApiKeyOnLivedoorClip(
        const char *username,   // (I) ユーザ名 (livedoor ID)
        const char *password,   // (I) パスワード
        char       *apiKey      // (O) APIキー
    )
{
    char    cookie[MAX_COOKIE_LEN + 1];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( !apiKey )
        return ( NULL );

    *apiKey = NUL;
    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    if ( loginLivedoorClip( username, password, cookie ) ) {
        response = (char *)malloc( sz );
        if ( !response )
            return ( apiKey );

        setUpReceiveBuffer( response, sz );
        http_getEx( "http://clip.livedoor.com/config/api", response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"api-key-box\"" );
            if ( p ) {
                char    *q;

                p += 13;
                q = strchr( p, '>' );
                if ( q ) {
                    p = q + 1;
                    q = strchr( p, '<' );
                    if ( q && ((q - p) <= MAX_KEYLENGTH ) ) {
                        strncpy( apiKey, p, q - p );
                        apiKey[q - p] = NUL;
                    }
                }
            }
        }

        free( response );
    }

    return ( apiKey );
}

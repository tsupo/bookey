/*
 *  fc2bookmark.c
 *      FC2BOOKMARK に login する
 *          written by H.Tsujimura  29 Mar 2007
 *
 * $Log: /comm/bookey/fc2bookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/11/18 1:05 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 5     07/09/26 14:00 Tsujimura543
 * keep_login と Submit の順序を入れ替えた
 * 
 * 4     07/03/29 18:06 Tsujimura543
 * loginFC2Bookmark() の引数を2つ追加。uid と cc を取得するようにした
 * 
 * 3     07/03/29 17:25 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 2     07/03/29 17:24 Tsujimura543
 * 実装完了 (実際にログインできることを確認)
 * 
 * 1     07/03/29 15:06 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/fc2bookmark.c 1     09/05/14 3:48 tsupo $";
#endif


/* FC2BOOKMARK に login する */
int
loginFC2Bookmark(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        char       *uid,        // (O)   uid (FC2ID のユーザID)
        char       *cc          // (O)   cc  (FC2BOOKMARK のcc)
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
    static char     saveUserID[MAX_NAMELEN];
    static char     saveCC[MAX_KEYLENGTH];
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
            dputs( "loginFC2Bookmark(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveCC[0]       = NUL;
    }
    else {
        dputs( "loginFC2Bookmark(): キャッシュを利用\n" );
        strcpy( cookie, saveCookie );
        strcpy( uid,    saveUserID );
        strcpy( cc,     saveCC );
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

    strcpy( url, "https://secure.id.fc2.com/?mode=login" );
    setTargetURL( url );
    sprintf( request,
             "email=%s&"
             "pass=%s&",
             userName, password );
    sprintf( request + strlen(request),
             "Submit=%s&"
             "keep_login=1",
             encodeURL( sjis2utf("ログイン") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        char    *p = strstr(response,
                            "<META http-equiv=\"Refresh\" content=\"0; url=");
        if ( p ) {
            char    *q;

            p += 43;
            q = strstr( p, "\">" );
            if ( q ) {
                strncpy( url, p, q - p );
                url[q - p] = NUL;

                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );
            }
        }

        if ( *response && strstr( response, "logout" ) ) {
            char    *p = strstr( response,
                                 "http://bookmark.fc2.com/user/index?uid=" );
            if ( p ) {
                char    *q;

                p += 39;
                q = strchr( p, '&' );
                if ( q ) {
                    strncpy( uid, p, q - p );
                    uid[q - p] = NUL;

                    q++;
                    p = strstr( q, "cc=" );
                    if ( p ) {
                        p += 3;
                        q = strchr( q, '"' );
                        if ( !q )
                            q = strchr( q, '>' );
                        if ( !q )
                            q = strchr( q, ' ' );
                        if ( q ) {
                            strncpy( cc, p, q - p );
                            cc[q - p] = NUL;
                        }
                    }
                }
                /* uid は FC2ID が必要な全サービスで共通         */
                /* cc  は FC2ID が必要なサービスごとに存在する値 */
            }
            ret = 1;    /* ログイン成功 */
        }
        else
            ret = 0;    /* ログイン失敗 */
    }
    else
        ret = 0;        /* ログイン失敗 */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginFC2Bookmark(): ログイン成功、キャッシュに保存\n" );
        strcpy( saveUserName, userName );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
        strcpy( saveUserID, uid );
        strcpy( saveCC,     cc );
    }
    else {
        /* キャッシュを破棄 */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveCC[0]       = NUL;
        firstTime       = 0;
    }

    return ( ret );
}

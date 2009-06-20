/*
 *  niftyClip.c
 *      ニフティクリップ に login する
 *          written by H.Tsujimura  29 Jun 2006
 *
 * $Log: /comm/bookey/niftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/01/30 17:33 Tsujimura543
 * @nifty クリップの "settings" ページの内容変更に伴い、
 * APIキー取得処理を更新
 * 
 * 11    08/11/18 1:05 Tsujimura543
 * コメントを修正
 * 
 * 10    08/11/18 1:02 Tsujimura543
 * ログイン処理のキャッシュ回りを修正
 * 
 * 9     08/11/05 17:30 Tsujimura543
 * 「APIキー設定」ボタン押下時処理を修正
 * 
 * 8     08/11/04 16:45 Tsujimura543
 * getApiKeyOnNiftyClip() を追加
 * 
 * 7     08/11/04 11:56 Tsujimura543
 * ログイン処理を更新 (login ページを GET してから POST しないと
 * ログインできなくなった模様)
 * 
 * 6     08/04/02 17:32 Tsujimura543
 * login処理を更新 (2008年4月1日にログイン後に表示されるページの内容
 * が微妙に変更された。これに合わせてlogin成功判断条件を修正)
 * 
 * 5     08/03/17 18:08 Tsujimura543
 * キャッシュを導入。リクエストが発生する都度、ログインしなくてもいいよう
 * にしてみた
 * 
 * 4     08/03/17 16:46 Tsujimura543
 * login処理を更新 (2008年3月17日に仕様変更が実施された模様)
 * 
 * 3     06/10/19 13:58 Tsujimura543
 * コメントを修正
 * 
 * 2     06/10/19 13:57 Tsujimura543
 * (1) login 失敗時、リトライするようにした
 * (2) ただし、「ユーザIDまたはパスワードが違う」のが理由での login 失敗時
 *     はリトライを行なわない
 * (3) 受信バッファオーバーフロー対策を実施した
 * 
 * 1     06/06/29 21:26 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/niftyClip.c 1     09/05/14 3:48 tsupo $";
#endif


/* ニフティクリップ に login する */
int
loginNiftyClip(
        const char *username,   // (I)   ユーザ名 (@nifty ID または PLEASY ID)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    // キャッシュチェック
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
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        strcpy( cookie, saveCookie );
        ret = TRUE;     /* ログイン成功 */
        return ( ret );
    }

    // ログイン処理
    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }

    sz = MAX_CONTENT_SIZE * 2;
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }

    do {
        memset( request, 0x00, MAX_CONTENT_SIZE );
        setUpReceiveBuffer( response, sz );

        *cookie = NUL;
        http_getEx( "http://clip.nifty.com/login", response, cookie );
        if ( *response ) {
            setUpReceiveBuffer( response, sz );
            strcpy( url, "https://clip.nifty.com/login" );
            setTargetURL( url );
            sprintf( request,
                     "name=&"
                     "username=%s&"
                     "password=%s",
                     username, password );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

            if ( *response ) {
                if ( strstr( response, "<a href=\"/logout\">" )             ||
                     (strstr( response, "<meta http-equiv=\"Refresh\" "
                                        "content=\"0; url=" )          &&
                      strstr( response, "window.location.replace(" )      )    ) {
                    ret = 1;    /* ログイン成功 */
                    break;
                }
                else if ( strstr( response, "login-failure" ) ) {
                    /* 「ユーザIDまたはパスワードが違います。」 の場合 */
                    ret = 0;    /* ログイン失敗 */
                    break;
                }
            }
        }

        retry--;
        if ( retry <= 0 )
            break;
        Sleep( 2000 );
    } while ( ret == 0 );

    free( response );
    free( request  );

    // キャッシュを更新
    if ( ret == TRUE ) {
        /* キャッシュに保存 */
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie,   cookie );
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
_getApiKeyOnNiftyClip( const char *response, char *apiKey )
{
    const char  *p = response;
    const char  *q;

    q = strstr( p, "</button>" );
    if ( q ) {
        q += 9;
        while ( (*q == ' ')  || (*q == '\t') ||
                (*q == '\r') || (*q == '\n')    )
            q++;
        p = q;
        q = strstr( p, "</form>" );
        if ( q ) {
            while ( (*(q - 1) == ' ')  || (*(q - 1) == '\t') ||
                    (*(q - 1) == '\r') || (*(q - 1) == '\n')    )
                q--;

            if ( !strncmpi( p, "<input ", 7 ) ) {
                q = strstr( p, "value=\"" );
                if ( q ) {
                    p = q + 7;
                    q = strchr( p, '"' );
                    if ( !q )
                        q = p + MAX_KEYLENGTH;
                }
            }

            if ( ((q - p) <= MAX_KEYLENGTH ) ) {
                strncpy( apiKey, p, q - p );
                apiKey[q - p] = NUL;
            }
        }
    }

    return ( apiKey );
}

char    *
getApiKeyOnNiftyClip(
        const char *username,   // (I)   ユーザ名 (@nifty ID または PLEASY ID)
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
    if ( loginNiftyClip( username, password, cookie ) ) {
        response = (char *)malloc( sz );
        if ( !response )
            return ( apiKey );

        setUpReceiveBuffer( response, sz );
        http_getEx( "http://clip.nifty.com/settings", response, cookie );
        if ( *response ) {
            char    *p = strstr( response, sjis2utf("APIキー再発行") );
            if ( p ) {
                // すでに APIキー発行済みの場合
                _getApiKeyOnNiftyClip( p, apiKey );
            }
            else {
                // まだ APIキーが発行されていない場合
                char    request[BUFSIZ];
                sprintf( request, "submitAction=%s",
                         sjis2utf("APIキー発行") );
                setUpReceiveBuffer( response, sz );
                http_postEx( "http://clip.nifty.com/settings",
                             "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response ) {
                    p = strstr( response, "setAPIKey" );
                    if ( p )
                        _getApiKeyOnNiftyClip( p, apiKey );
                }
            }
        }

        free( response );
    }

    return ( apiKey );
}

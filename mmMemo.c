/*
 *  mmMemo.c
 *      MM/Memo に(TypeKey認証経由で) login する
 *          written by H.Tsujimura  18 Oct 2005
 *
 * $Log: /comm/bookey/mmMemo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 22    08/12/05 17:32 Tsujimura543
 * コメントを整理
 * 
 * 21    08/12/05 17:29 Tsujimura543
 * デバッグ用の処理を削除(し忘れていた)
 * 
 * 20    08/12/05 15:03 Tsujimura543
 * login1470netViaHatena() を修正 (はてな認証回りのログイン手順変更に対応)
 * 
 * 19    08/12/02 22:02 Tsujimura543
 * TypePad Connect 経由で MM/Memo へログインしようとしたときに
 * 何回リトライしても [RETRY] が返ってくるような状態に(MM/Memoが)
 * なっていることがあることが判明。その対策を実施した
 * 
 * 18    08/11/25 17:49 Tsujimura543
 * TypeKey 認証 → TypePad Connect 移行に伴う修正を実施
 * 
 * 17    08/11/18 1:05 Tsujimura543
 * コメントを修正
 * 
 * 16    08/11/18 1:02 Tsujimura543
 * ログイン処理のキャッシュ回りを修正
 * 
 * 15    07/06/29 22:24 Tsujimura543
 * ソースコードを整理
 * 
 * 14    07/06/29 22:22 Tsujimura543
 * (1) http://1470.net/mm/ → http://mmmemo.1470.net/mm/ へ変更
 * (2) TypeKey 認証まわりを修正 (いつの間にか認証に失敗するようになっていた)
 * 
 * 13    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 12a   06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 12    06/08/22 17:48 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 11    06/08/22 16:59 Tsujimura543
 * enum authenticationType の定義を myClip.h 内に移した
 * 
 * 10    06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 9     06/07/31 18:03 Tsujimura543
 * (1) 受信バッファオーバーラン防止機能を組み込んだ
 * (2) login1470net() の login 再試行間隔を 2秒 に変更
 * 
 * 8     06/07/24 19:23 Tsujimura543
 * login1470net() 中で、受信電文格納領域の掃除し忘れがあったのを修正
 * 
 * 7     06/07/18 20:47 Tsujimura543
 * コメントの修正
 * 
 * 6     06/07/18 15:26 Tsujimura543
 * MM/Memo と 1470.net リニューアル版への同時登録実行時、どちらか一方しか
 * 登録できないことがある件に対処した(login情報のキャッシュを破棄する機能
 * を追加することで対処)
 * 
 * 5     06/07/15 0:42 Tsujimura543
 * login1470net() を追加
 * 
 * 4     06/07/12 15:51 Tsujimura543
 * 64 → MAX_KEYLENGTH に置換
 * 
 * 3     06/06/19 20:42 Tsujimura543
 * インデント修正
 * 
 * 2     06/05/22 18:56 Tsujimura543
 * MM/Memo に対する操作のたびに TypeKey を取得し直すのを回避するため、
 * キャッシュを導入した
 * 
 * 1     05/10/19 16:46 Tsujimura543
 * getMMmemo.c から分離、独立させた
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/mmMemo.c 1     09/05/14 3:48 tsupo $";
#endif

/* MM/Memo にログインする */
int
_loginMMmemo( const char *username,     // (I)   TypeKeyユーザ名
              const char *password,     // (I)   TypeKeyパスワード
              char       *cookie,       // (I/O) クッキー
              char       *userID,       // (O)   MM/Memo ユーザID
              int        stackCount )   // (I)   
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];
    char    cookie2[MAX_COOKIE_LEN];
    char    key[MAX_KEYLENGTH];
    char    token[MAX_LOGICALLINELEN];
    size_t  sz;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static char     saveUserID[MAX_NAMELEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !username ) {
        /* キャッシュクリア */
        firstTime = 0;
        return ( ret );
    }
    login1470net( NULL, NULL, NULL, NULL, AK_ORIGINAL, NULL, NULL );
                                    /* login1470net()内のキャッシュをクリア */
    if ( !cookie )
        return ( ret );

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
        saveUserID[0]   = NUL;
    }
    else {
        strcpy( cookie, saveCookie );
        strcpy( userID, saveUserID );
        ret = 1;    /* ログイン成功 */
        return ( ret );
    }

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        firstTime = 0;
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( cookie2, 0x00, MAX_COOKIE_LEN );

    strcpy( url, "http://mmmemo.1470.net/mm/mylist.html" );
    setTargetURL( url );

    key[0]   = NUL;
    token[0] = NUL;
    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( !p || !(*p) ) {
        char    url2[MAX_URLLENGTH];
        char    *q, *r;

        getCurrentLocation( url2 );
        q = strstr( url2, "t=" );
        if ( !q ) {
            q = strstr( url2, "typekey_token=" );
            if ( q )
                q += 12; /* 12 (= 14 - 2) */
        }
        if ( q ) {
            q += 2;
            r = strchr( q, '&' );
            if ( r ) {
                strncpy( key, q, r - q );
                key[r - q] = NUL;
            }
        }
    }
    else {
        char    *q, *r;

        // MM/Memo の公開鍵を取得 (TypePad Connect 認証用 login ページの解析)
        key[0] = NUL;
        q = strstr( p, "<input type=\"hidden\" name=\"t\"" );
        if ( !q ) {
            q = strstr( p, "<input type=\"hidden\" name=\"typekey_token\"" );
            if ( q )
                q += 12; /* 12 (= 41 - 29) */
        }
        if ( q ) {
            q += 29;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( key, r, q - r );
                    key[q - r] = NUL;
                }
            }
        }

        p = response;
        token[0] = NUL;
        q = strstr( p,
              "<input type=\"hidden\" id=\"password-token\" name=\"token\"");
        if ( q ) {
            q += 53;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( token, r, q - r );
                    token[q - r] = NUL;
                }
            }
        }
    }
    if ( key[0] && token[0] ) {
        // TypePad Connect 認証
        strcpy( url, "https://www.typepad.com/secure/services/signin/save" );
        sprintf( request,
                 "token=%s&"
                 "resp=&"
                 "to=%s&"
                 "is_typekey=1&",
                 token,
                 encodeURL( "http://mmmemo.1470.net/login" ) );
        sprintf( request + strlen( request ),
                 "typekey_token=%s&"
                 "typekey_version=1.1&"
                 "username=%s&"
                 "password=%s&"
                 "remember=1",
                 key, username, password );
        setUpReceiveBuffer( response, sz );
        p = http_postEx2( url, "application/x-www-form-urlencoded",
                          request, response, cookie2,
                          "http://mmmemo.1470.net/", cookie );
        if ( !p || !(*p) )
            ret = 0;        /* サーバとの通信失敗 */
        else {
            // TypeKey 認証実行後の redirect 先の Web ページの内容を解析
            char        *q, *r;
            const char  *targetString = "<link rel=\"alternate\" "
                                        "type=\"application/rss+xml\" "
                                        "title=\"RSS\" href=\"http://";
            if ( strstr( p, "RETRY" ) != NULL ) {
                stackCount++;
                if ( stackCount >= 6 ) {
                    // スタックオーバーフロー(+ 無限ループ)防止
                    return ( ret );
                }

                Sleep( 5000 );  // 5秒待ってからリトライ
                firstTime = 0;
                memset( cookie, 0x00, MAX_COOKIE_LEN );
                ret = _loginMMmemo( username, password, cookie, userID,
                                    stackCount );
                stackCount--;
            }
            else if ( ( q = strstr( p, targetString ) ) != NULL ) {
                q += strlen( targetString );
                r = strstr( q, "mylist.html/" );
                if ( r )
                    q = r + 12;
                r = strchr( q, '?' );
                if ( r ) {
                    strncpy( userID, q, r - q );
                    userID[r - q] = NUL;
                }
                ret = 1;    /* ログイン成功 */
            }
            else
                ret = 0;    /* ログイン失敗 */
        }
    }
    else
        ret = 0;    /* ログイン失敗 */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
        strcpy( saveUserID, userID );
    }
    else {
        /* キャッシュを破棄 */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        firstTime       = 0;
    }

    return ( ret );
}

int
loginMMmemo( const char *username,  // (I)   TypeKeyユーザ名
             const char *password,  // (I)   TypeKeyパスワード
             char       *cookie,    // (I/O) クッキー
             char       *userID )   // (O)   MM/Memo ユーザID
{
    int stackCount = 0;

    return ( _loginMMmemo( username, password, cookie, userID, stackCount ) );
}

int
login1470netViaTypeKey(
        const char *username,   // (I)   TypeKeyユーザ名
        const char *password,   // (I)   TypeKeyパスワード
        char       *request,    // (I/O) request  格納領域
        char       *response,   // (I/O) response 格納領域
        size_t     sz,          // (I)   response 格納領域のサイズ
        char       *cookie,     // (I/O) クッキー
        char       *userID      // (O)   1470.netリニューアル版 ユーザ名
    )
{
    int     ret = 0;
    char    url[MAX_URLLENGTH];
    char    cookie2[MAX_COOKIE_LEN];
    char    *p;

    memset( cookie2, 0x00, MAX_COOKIE_LEN );

    strcpy( url, "http://1470.net/tools/" );
    setTargetURL( url );

    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( p && *p ) {
        char    key[MAX_KEYLENGTH];
        char    token[MAX_LOGICALLINELEN];
        char    *q, *r;

        // PHPSESSID=
        q = strstr( cookie, "; PHPSESSID=" );
        if ( q )
            strcpy( q, "\r\n" );

        key[0]   = NUL;
        token[0] = NUL;
        q = strstr(p, "<a href=\"https://www.typekey.com/t/typekey/login?t=");
        if ( q ) {
            p = q + 9;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( url, p, q - p );
                url[q - p] = NUL;

                q = strstr( url, "t=" );
                if ( !q ) {
                    q = strstr( url, "typekey_token=" );
                    if ( q )
                        q += 12; /* 12 (= 14 - 2) */
                }
                if ( q ) {
                    q += 2;
                    r = strchr( q, '&' );
                    if ( r ) {
                        strncpy( key, q, r - q );
                        key[r - q] = NUL;
                    }
                }

                setUpReceiveBuffer( response, sz );
                p = http_getEx( url, response, cookie2 );
                if ( !p )
                    return ( ret );
            }
        }

        // 1470.net の公開鍵を取得 (TypePad Connect 認証用 login ページの解析)
        p = response;
        q = strstr( p, "<input type=\"hidden\" name=\"typekey_token\"" );
        if ( q ) {
            q += 41;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( key, r, q - r );
                    key[q - r] = NUL;
                }
            }
        }

        p = response;
        q = strstr( p,
              "<input type=\"hidden\" id=\"password-token\" name=\"token\"");
        if ( q ) {
            q += 53;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( token, r, q - r );
                    token[q - r] = NUL;
                }
            }
        }

        // TypePad Connect 認証
        strcpy( url, "https://www.typepad.com/secure/services/signin/save" );
        sprintf( request,
                 "token=%s&"
                 "resp=&"
                 "to=%s&"
                 "is_typekey=1&",
                 token,
                 encodeURL( "http://1470.net/tools/" ) );
        sprintf( request + strlen( request ),
                 "typekey_token=%s&"
                 "typekey_version=1.1&"
                 "username=%s&"
                 "password=%s&"
                 "remember=1",
                 key,
                 username, password );
        setUpReceiveBuffer( response, sz );
        p = http_postEx2( url, "application/x-www-form-urlencoded",
                          request, response, cookie2,
                          "http://1470.net/", cookie );
        if ( !p || !(*p) )
            ret = 0;        /* サーバとの通信失敗 */
        else {
            // TypeKey 認証実行後の redirect 先の Web ページの内容を解析
            char    *q;
            int     retry = 0;
            if ( strstr( p, sjis2utf("ログインに成功しました") ) ) {
                const char  *targetString = "<meta http-equiv=\"refresh\" "
                                            "content=\"1; url=";
                url[0] = NUL;
                q = strstr( p, targetString );
                if ( q ) {
                    p = q + strlen( targetString );
                    q = strstr( p, "\">" );
                    if ( q ) {
                        strcpy( url, "http://1470.net" );
                        strncat( url, p, q - p );
                        url[15 + (q - p)] = NUL;
                        while ( (q = strstr( url, "&amp;" )) != NULL )
                            strcpy( q + 1, q + 5 );
                    }
                }

                do {
                    if ( url[0] == NUL )
                        strcpy( url, "http://1470.net/tools/" );
                    setTargetURL( url );
                    Sleep( 1000 );

                    setUpReceiveBuffer( response, sz );
                    p = http_getEx( url, response, cookie );
                            // 注意: なぜか、この url を2回 GET しないと
                            //       userID が得られるページへうまく redirect
                            //       されない
                    if ( p && *p ) {
                        q = strstr( p, "<a href=\"/user/" );
                        if ( q ) {
                            p = q + 15;
                            q = strstr( p, "/\">" );
                            if ( q ) {
                                strncpy( userID, p, q - p );
                                userID[q - p] = NUL;
                            }
                        }
                    }

                    if ( userID[0] )
                        ret = 1;    /* ログイン成功 */
                    else {
                        ret = 0;    /* ログイン失敗 */
                        retry++;
                        if ( retry > 5 )
                            break;
                        Sleep( 2000 );
                    }
                } while ( ret == 0 );
            }
            else
                ret = 0;    /* ログイン失敗 */
        }
    }
    else
        ret = 0;    /* ログイン失敗 */

    return ( ret );
}


int
login1470netViaHatena(
        const char *username,   // (I)   はてなID
        const char *password,   // (I)   はてなパスワード
        char       *request,    // (I/O) request  格納領域
        char       *response,   // (I/O) response 格納領域
        size_t     sz,          // (I)   response 格納領域のサイズ
        char       *cookie,     // (I/O) クッキー
        char       *userID      // (O)   1470.netリニューアル版 ユーザ名
    )
{
    int     ret = 0;
    char    url[MAX_URLLENGTH];
    char    targetURL[MAX_URLLENGTH];
    char    *p;

    strcpy( url, "http://1470.net/tools/" );
    setTargetURL( url );

    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( p && *p ) {
        char    api_key[MAX_KEYLENGTH];
        char    api_sig[MAX_KEYLENGTH];
        char    *q, *r;

        // 1470.net の api_key と api_sig を取得
        api_key[0] = NUL;
        api_sig[0] = NUL;
        q = strstr( p, "http://auth.hatena.ne.jp/auth?api_key=" );
        if ( q ) {
            q += 38;
            r = strstr( q, "&amp;api_sig=" );
            if ( r ) {
                strncpy( api_key, q, r - q );
                api_key[r - q] = NUL;

                q = r + 13;
                r = strstr( q, "\">" );
                if ( r ) {
                    strncpy( api_sig, q, r - q );
                    api_sig[r - q] = NUL;
                }
            }
        }

        sprintf( targetURL,
                 "http://auth.hatena.ne.jp/auth?api_key=%s&api_sig=%s",
                 api_key, api_sig );

        // はてな認証API
        strcpy( url, "https://www.hatena.ne.jp/login" );
        sprintf( request,
                 "name=%s&"
                 "password=%s&",
                 username, password );
        sprintf( request + strlen( request ),
                 "persistent=1&"
                 "location=%s&",
                 encodeURL( targetURL ) );

        setUpReceiveBuffer( response, sz );
        p = http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

        if ( !p || !(*p) )
            ret = 0;        /* サーバとの通信失敗 */
        else {
            // はてな認証実行後の redirect 先の Web ページの内容を解析
            char    *q;
            int     retry = 0;

            Sleep( 1000 );
            setUpReceiveBuffer( response, sz );
            p = http_getEx( targetURL, response, cookie );
            if ( p && strstr( p, sjis2utf("ログインに成功しました") ) ) {
                const char  *targetString = "<meta http-equiv=\"refresh\" "
                                            "content=\"1; url=";
                url[0] = NUL;
                q = strstr( p, targetString );
                if ( q ) {
                    p = q + strlen( targetString );
                    q = strstr( p, "\">" );
                    if ( q ) {
                        strcpy( url, "http://1470.net" );
                        strncat( url, p, q - p );
                        url[15 + (q - p)] = NUL;
                        while ( (q = strstr( url, "&amp;" )) != NULL )
                            strcpy( q + 1, q + 5 );
                    }
                }

                do {
                    if ( url[0] == NUL )
                        strcpy( url, "http://1470.net/tools/" );
                    setTargetURL( url );
                    Sleep( 1000 );

                    setUpReceiveBuffer( response, sz );
                    p = http_getEx( url, response, cookie );
                    if ( p && *p ) {
                        q = strstr( p, "<a href=\"/user/" );
                        if ( q ) {
                            p = q + 15;
                            q = strstr( p, "/\">" );
                            if ( q ) {
                                strncpy( userID, p, q - p );
                                userID[q - p] = NUL;
                            }
                        }
                    }

                    if ( userID[0] )
                        ret = 1;    /* ログイン成功 */
                    else {
                        ret = 0;    /* ログイン失敗 */
                        retry++;
                        if ( retry > 5 )
                            break;
                        Sleep( 2000 );
                    }
                } while ( ret == 0 );
            }
            else
                ret = 0;    /* ログイン失敗 */
        }
    }
    else
        ret = 0;    /* ログイン失敗 */

    return ( ret );
}

/* 1470.netリニューアル版 にログインする */
int
login1470net(
        const char *username,   // (I)   TypeKeyユーザ名
        const char *password,   // (I)   TypeKeyパスワード
        const char *username2,  // (I)   はてなID
        const char *password2,  // (I)   はてなパスワード
        AUTH_TYPE  authType,    // (I)   認証種別 (TypeKey, はてな認証API)
        char       *cookie,     // (I/O) クッキー
        char       *userID      // (O)   1470.netリニューアル版 ユーザ名
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    size_t  sz;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static char     saveUserID[MAX_NAMELEN];
    static int      saveAuthType = AK_ORIGINAL;
    static time_t   firstTime    = 0;
    BOOL            refresh = FALSE;

    if ( !username ) {
        /* キャッシュクリア */
        firstTime = 0;
        return ( ret );
    }
    loginMMmemo( NULL, NULL, NULL, NULL );
                                    /* loginMMmemo()内のキャッシュをクリア */

    if ( !cookie )
        return ( ret );

    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* キャッシュの有効時間を1時間とする */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 ) ||
                  ( authType != saveAuthType )                 )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveAuthType    = AK_ORIGINAL;
    }
    else {
        strcpy( cookie, saveCookie );
        strcpy( userID, saveUserID );
        ret = 1;    /* ログイン成功 */
        return ( ret );
    }

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        firstTime = 0;
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    userID[0] = NUL;

    if ( (authType == AK_TYPEKEY) || (authType == AK_TYPEKEY_HATENA) ) {
        ret = login1470netViaTypeKey( username, password, request, response,
                                      sz, cookie, userID );
    }
    if ( (ret == 0)                            &&
         ((authType == AK_HATENA)         ||
          (authType == AK_HATENA_TYPEKEY) ||
          (authType == AK_TYPEKEY_HATENA)    )    ) {
        memset( request, 0x00, MAX_CONTENT_SIZE );
        userID[0] = NUL;
        ret = login1470netViaHatena( username2, password2, request, response,
                                     sz, cookie, userID );
    }
    if ( (ret == 0) && (authType == AK_HATENA_TYPEKEY) ) {
        memset( request, 0x00, MAX_CONTENT_SIZE );
        userID[0] = NUL;
        ret = login1470netViaTypeKey( username, password, request, response,
                                      sz, cookie, userID );
    }

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
        strcpy( saveUserID, userID );
        saveAuthType = authType;
    }
    else {
        /* キャッシュを破棄 */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveAuthType    = AK_ORIGINAL;
        firstTime       = 0;
    }

    return ( ret );
}

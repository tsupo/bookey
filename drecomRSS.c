/*
 *  drecomRSS.c
 *      ドリコムRSS に login する
 *          written by H.Tsujimura  28 Mar 2006
 *
 * $Log: /comm/bookey/drecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    08/11/18 1:14 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 10    07/05/22 17:57 Tsujimura543
 * リファクタリング
 * 
 * 9     07/04/16 20:19 Tsujimura543
 * またまた、微妙にドリコムRSS(というかドリコムアカウント)の仕様が変わって
 * いることが判明、対応した
 * 
 * 8     07/04/12 15:25 Tsujimura543
 * 2007年4月12日のドリコムRSSリニューアルに対応
 * 
 * 7     07/02/15 15:54 Tsujimura543
 * __ticket__ はサーバ側で cookie に格納する仕様に変更された模様
 * (2007年1月17日に仕様変更された?)。念のため、cookie に __ticket__
 * が格納済みか確認し、格納されていない場合のみ、__ticket__取得、設
 * 定を行なうようにした (この処理自体、今後は不要かもしれない)
 * 
 * 6     07/01/17 17:54 Tsujimura543
 * 英語モード対応
 * 
 * 5     06/09/12 14:00 Tsujimura543
 * Visual C++ 6 / Visual C++ 2005 の両方で問題なくビルドできることを確認
 * 
 * 4a    06/09/12 5:17 tsupo
 * MessageBox() が ascii バージョン / wide char バージョンのどちらでも
 * warning なしでコンパイルできるようにした (for Visual Studio 2005)
 * 
 * 4     06/07/31 17:36 Tsujimura543
 * リトライ回数を5回にする
 * 
 * 3     06/07/25 18:26 Tsujimura543
 * ドリコムアカウント(2006年7月25日稼動開始)に対応
 * 
 * 2     06/07/18 21:40 Tsujimura543
 * login 失敗時、最大3回まで再試行するようにしてみた
 * 
 * 1     06/03/28 17:08 Tsujimura543
 * putDrecomRSS.c から分離、独立させた
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/drecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif


/* ドリコムRSS に login する */
int
loginDrecomRSS(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
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
            dputs( "loginDrecomRSS(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginDrecomRSS(): キャッシュを利用\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ログイン成功 */
        return ( ret );
    }

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }

    do {
        memset( request,  0x00, MAX_CONTENT_SIZE );
        setUpReceiveBuffer( response, sz );

        /* ログインページを取得 */
        strcpy( url, "http://rss.drecom.jp/logging/re" );
        cookie[0] = NUL;
        http_getEx( url, response, cookie );
        if ( *response ) {
            /* iframe で指示されている login form を GET */
            char    *p = strstr( response, "<iframe src=\"" );
            if ( p ) {
                char    *q;

                p += 13;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;

                    setUpReceiveBuffer( response, sz );
                    http_getEx( url, response, cookie );
                    if ( *response ) {
                        char    appKey[64];
                        char    sig[64];

                        /* applicationKey と signature を取得 */
                        appKey[0] = NUL;
                        sig[0]    = NUL;
                        p = strstr( response, " name=\"app_key\" " );
                        if ( p ) {
                            p += 16;
                            q = strstr( p, "value=\"" );
                            if ( q ) {
                                p = q + 7;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    strncpy( appKey, p, q - p );
                                    appKey[q - p] =  NUL;
                                }
                            }
                        }

                        p = strstr( p ? p : response, " name=\"sig\" " );
                        if ( p ) {
                            p += 12;
                            q = strstr( p, "value=\"" );
                            if ( q ) {
                                p = q + 7;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    strncpy( sig, p, q - p );
                                    sig[q - p] =  NUL;
                                }
                            }
                        }

                        if ( !(appKey[0]) || (!sig[0]) )
                            break;

                        /* ドリコムアカウントへサインイン */
                        sprintf( request,
                                 "app_key=%s&"
                                 "from=&"
                                 "method=frame_signin&"
                                 "sig=%s&"
                                 "account[name]=%s&"
                                 "account[password]=%s&"
                                 "account[remember]=1&"
                                 "commit=%s",
                                 appKey,
                                 sig,
                                 userName, password,
                                 "Click+Login" );
                        strcpy(url, "https://account.drecom.jp/frame/signin");
                        setUpReceiveBuffer( response, sz );
                        http_postEx( url,
                                     "application/x-www-form-urlencoded",
                                     request, response, cookie );
                        if ( *response ) {
                            /* ドリコムアカウントが有効になっているか */
                            /* どうかを確認                           */
                            if ( strstr( response,
                                         "https://account.drecom.jp/"
                                         "questionnaire" ) ) {
                                DWORD   langCode = getLanguageCode();

                                if ( langCode == 0x0411 ) {
                                    // 日本語
                                    MessageBox( NULL,
                                      (LPCTSTR)
                                      "ドリコムアカウントへの登録・移行手続"
                                      "きがまだ終わっていません。\r\n"
                                      "手続きを行なっておいてください。  ",
                                      (LPCTSTR)
                                      "ドリコムアカウントへの登録・移行をし"
                                      "てください",
                                                MB_OK|MB_ICONERROR );
                                }
                                else {
                                    // 英語
                                    MessageBox( NULL,
                                           "You should get a Drecom Account.",
                                                "Get your Drecom Account",
                                                MB_OK|MB_ICONERROR );
                                }
                                break;
                            }

                            if ( !strstr( cookie, "__ticket__" ) ) {
                                /* ticket を取得し、cookie に埋め込む */
                                p = strstr( response,
                                            "\"__ticket__\",\"=\",escape(\"" );
                                if ( p ) {
                                    char    ticket[64];

                                    p += 25;
                                    q = strchr( p, '"' );
                                    strncpy( ticket, p, q - p );
                                    ticket[q - p] = NUL;

                                    p = strchr( cookie, '\r' );
                                    if ( p )
                                        sprintf( p, "; __ticket__=%s\r\n",
                                                 ticket );
                                }
                            }

                            /* 最終的なログインページ(ログイン後のトップ */
                            /* ぺージ)を取得                             */
                            p = strstr( response,
                                        "parent.location.href = \"" );
                            if ( p ) {
                                p += 24;
                                q = strchr( p, '"' );
                                strncpy( url, p, q - p );
                                url[q - p] = NUL;

                                setUpReceiveBuffer( response, sz );
                                http_getEx( url, response, cookie );
                                if ( *response ) {
                                    if ( (strstr( response,
                                       "https://account.drecom.jp/signout"
                                               ) != NULL) ||
                                         (strstr( response, "/logging/out"
                                               ) != NULL)    ) {
                                        ret = 1;    /* login 成功 */
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        retry--;
        if ( retry <= 0 )
            break;
        Sleep( 2000 );
    } while ( ret == 0 );

    free( response );
    free( request );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginDrecomRSS(): ログイン成功、キャッシュに保存\n" );
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

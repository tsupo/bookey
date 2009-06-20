/*
 *  blogPet.c
 *      BlogPet 管理画面 に login する
 *          written by H.Tsujimura  12 Sep 2006 / 22 Dec 2006
 *
 * $Log: /comm/bookey/blogPet.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     08/11/18 1:04 Tsujimura543
 * ログイン処理にキャッシュを導入
 * 
 * 7     08/01/25 15:32 Tsujimura543
 * ユーザ名、パスワードにマルチバイト文字を使っている人がいるとのことで、
 * ユーザ名とパスワードを UTF-8に変換するようにしてみた
 * 
 * 6     07/07/13 2:01 Tsujimura543
 * 2007年7月12日に実施された BlogPet リニューアルに対応
 * 
 * 5     07/02/14 23:14 Tsujimura543
 * encodeURLe() のプロトタイプ宣言を blogPet.h へ移動
 * 
 * 4     07/02/13 21:43 Tsujimura543
 * encodeURLe() を getBlogPet.c から blogPet.c へ移動
 * 
 * 3     06/12/25 23:37 Tsujimura543
 * loginBlogPet() に第4引数を追加
 * 
 * 2     06/12/25 13:51 Tsujimura543
 * "jump=&" を追加
 * 
 * 1     06/12/22 21:38 Tsujimura543
 * 「ここうさぎ」用に作った処理を流用
 */

#include "xmlRPC.h"
#include "myClip.h"
#include "blogPet.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/blogPet.c 1     09/05/14 3:48 tsupo $";
#endif


/* BlogPet 管理画面 に login する */
int
loginBlogPet(
        const char *userName,   // (I)   ユーザ名
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        char       *userID      // (O)   ユーザID
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    _username[MAX_USERIDLEN];
    char    _password[MAX_PASSWDLEN];
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 4;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static char     saveUserID[MAX_NAMELEN];
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
            dputs( "loginBlogPet(): キャッシュを破棄\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
    }
    else {
        dputs( "loginBlogPet(): キャッシュを利用\n" );
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
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }

    strcpy( _username, userName );
    any2utf( _username );
    strcpy( _password, password );
    any2utf( _password );

    do {
        memset( request, 0x00, MAX_CONTENT_SIZE );

        strcpy( url, "https://www.blogpet.net/login" );
        setTargetURL( url );
        setUpReceiveBuffer( response, MAX_CONTENT_SIZE * 4 );
        sprintf( request,
                 "username=%s&",
                 encodeURL(_username) );
        sprintf( request + strlen(request),
                 "password=%s&"
                 "remember=1&"
                 "jump_url=%%2Fhome",
                 encodeURL(_password) );
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

        if ( ret == 0 ) {
            retry--;
            if ( retry <= 0 )
                break;
            Sleep( 2000 );
        }
    } while ( ret == 0 );

    if ( ret == 1 ) {
        setUpReceiveBuffer( response, sz );
        http_getEx( "http://www.blogpet.net/home", response, cookie );
        if ( *response ) {
            char    *p;

            p = strstr( response, "/profile/friends/" );
            if ( !p )
                p = strstr( response, "/profile/groups/" );
            if ( p ) {
                char    *q;

                p = strstr( p, "s/" ) + 2;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( userID, p, q - p );
                    userID[q - p] = NUL;
                }
            }
        }
    }

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* キャッシュに保存 */
        dputs( "loginBlogPet(): ログイン成功、キャッシュに保存\n" );
        strcpy( saveUserName, userName );
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

char    *
encodeURLe( const char *p )
{
    static char hex[] = "0123456789ABCDEF";
    static char temp[MAX_CONTENT_SIZE];
    char        *q = temp;

    while ( *p ) {
        if ( (unsigned char)(*p) < 0x80 )
            *q++ = *p++;
        else {
            *q++ = '%';
            *q++ = hex[(*p &0xF0) >> 4];
            *q++ = hex[*p & 0x0F];
            p++;
        }
    }
    *q = NUL;

    return ( temp );
}


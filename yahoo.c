/*
 *  yahoo.c
 *      Yahoo! に login する
 *          written by H.Tsujimura  18 Apr 2007
 *
 * $Log: /comm/bookey/yahoo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/04/18 21:32 Tsujimura543
 * コメントを修正
 * 
 * 1     07/04/18 21:31 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/yahoo.c 1     09/05/14 3:48 tsupo $";
#endif


/* Yahoo! に login する */
int
loginYahoo(
        const char *username,   // (I)   ユーザ名 (Yahoo! ID)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    challenge[MAX_KEYLENGTH];
    char    u[MAX_KEYLENGTH];
    char    pd[MAX_KEYLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    // http://bookmarks.yahoo.com/ を GET
    challenge[0] = NUL;
    u[0]         = NUL;
    pd[0]        = NUL;
    setUpReceiveBuffer( response, sz );
    http_get( "http://bookmarks.yahoo.com/", response );
    if ( *response ) {
        char    *p, *q;

        p = strstr( response, "name=\".challenge\" value=\"" );
        if ( p ) {
            p += 25;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( challenge, p, q - p );
                challenge[q - p] = NUL;
            }
        }

        p = strstr( response, "name=\".u\" value=\"" );
        if ( p ) {
            p += 17;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( u, p, q - p );
                u[q - p] = NUL;
            }
        }


        p = strstr( response, "name=\".pd\" value=\"" );
        if ( p ) {
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( pd, p, q - p );
                pd[q - p] = NUL;
            }
        }
    }

    if ( challenge[0] ) {
        do {
            memset( request,  0x00, MAX_CONTENT_SIZE );

            strcpy( url, "https://login.yahoo.com/config/login?" );
            setTargetURL( url );
            sprintf( request,
                     ".tries=1&"
                     ".src=bmk2&"
                     ".md5=&"
                     ".hash=&"
                     ".js=&"
                     ".last=&"
                     "promo=&"
                     ".intl=us&"
                     ".bypass=&"
                     ".partner=&" );
            if ( u[0] )
                sprintf( request + strlen( request ),
                         ".u=%s&",
                         u );
            else
                sprintf( request + strlen( request ),
                         ".u=&" );
            sprintf( request + strlen( request ),
                     ".v=0&"
                     ".challenge=%s&"
                     ".yplus=&"
                     ".emailCode=&"
                     "pkg=&"
                     "stepid=&"
                     ".ev=&"
                     "hasMsgr=0&"
                     ".chkP=Y&"
                     ".done=%s&",
                     challenge,
                     encodeURL( "http://bookmarks.yahoo.com/" ) );
            if ( pd[0] )
                sprintf( request + strlen( request ),
                         ".pd=%s&",
                         u );
            else
                sprintf( request + strlen( request ),
                         ".pd=&" );
            sprintf( request + strlen( request ),
                     "login=%s&"
                     "passwd=%s&"
                     ".persistent=Y&"
                     ".save=%s",
                     username, password,
                     encodeURL( "Sign In" ) );
            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

            if ( *response ) {
                char    *p, *q;

                p = strstr( response,
                            "<meta http-equiv=\"Refresh\" content=\"0; url=" );
                if ( p ) {
                    p += 43;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( url, p, q - p );
                        url[q - p] = NUL;
                        setUpReceiveBuffer( response, sz );
                        http_getEx( url, response, cookie );
                    }
                }

                if ( *response ) {
                    if ( strstr( response, "Sign out</a>" ) != NULL )
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
    }

    free( response );
    free( request  );

    return ( ret );
}

/*
 * hatena.c
 *
 *      指定ユーザのはてなブックマーク登録件数を取得する
 *          written by H.Tsujimura  3 Jul 2006
 *
 * $Log: /comm/bookey/hatena.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 1     06/07/03 13:34 Tsujimura543
 * 新規作成
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/hatena.c 1     09/05/14 3:48 tsupo $";
#endif

int
getNumberOfHatenaBookmark( const char *username, const char *password )
{
    int total = 0;

    if ( username[0] && password[0] )
        total = getNumberOfBookmarksOnHatena( username, password );
    else {
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 64;

        response = (char *)malloc( sz );
        if ( response ) {
            sprintf( url, "http://b.hatena.ne.jp/%s", username );
            setUpReceiveBuffer( response, sz );
            http_get( url, response );
            if ( *response ) {
                char    *p;

                p = strstr( response, "<li class=\"count\">(" );
                if ( p )
                    total = atol( p + 19 );
            }

            free( response );
        }
    }

    return ( total );
}

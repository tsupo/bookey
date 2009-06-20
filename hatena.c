/*
 * hatena.c
 *
 *      �w�胆�[�U�̂͂Ăȃu�b�N�}�[�N�o�^�������擾����
 *          written by H.Tsujimura  3 Jul 2006
 *
 * $Log: /comm/bookey/hatena.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 1     06/07/03 13:34 Tsujimura543
 * �V�K�쐬
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

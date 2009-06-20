/*
 *  inputDeliciousXML.c
 *      del.icio.us �� posts/all ����擾�\�Ȍ`����XML�t�@�C������u�b�N
 *      �}�[�N����荞��
 *          written by H.Tsujimura  16 Apr 2007
 *
 * $Log: /comm/bookey/inputDeliciousXML.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/04/16 16:42 Tsujimura543
 * inputDeliciousXML() �̓���m�F����
 * 
 * 1     07/04/16 15:44 Tsujimura543
 * �V�K�쐬
 */

#define  USE_DELICIOUS_POSTS
#include "myClip.h"
#include "deliciousApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputDeliciousXML.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
inputDeliciousXML( int *numOfClips, FILE *fp, size_t fileSize )
{
    MyClip  *mp = NULL;
    int     n   = 0;
    int     cnt = 0;
    char    *p, *q;
    char    *buf;

    *numOfClips = 0;
    buf = (char *)malloc( fileSize + 1 );
    if ( buf ) {
        memset( buf, 0x00, fileSize );
        fread( buf, 1, fileSize, fp );

        p = buf;
        while ( *p ) {
            q = strstr( p, "<post href" );
            if ( !q )
                break;
            n++;
            p = q + 10;
        }

        if ( n > 0 ) {
            DELICIOUS_POSTS *posts;
            long            numOfPosts = n;

            posts = (DELICIOUS_POSTS *)
                        malloc( sizeof ( DELICIOUS_POSTS ) * numOfPosts );
            if ( posts ) {
                memset(posts, 0x00, sizeof ( DELICIOUS_POSTS ) * numOfPosts);

                cnt = getAllPostsFromDeliciousXML( buf, &numOfPosts, posts );
                if ( cnt > 0 ) {
                    mp = deliciousPosts2MyClip( posts, cnt );
                    if ( mp )
                        *numOfClips = cnt;
                }
                free( posts );
            }
        }
        free( buf );
    }

    return ( mp );
}

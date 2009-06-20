/*
 *  getString.c
 *      2�̎w�蕶����ɋ��܂ꂽ�����̕�������擾����
 *          written by H.Tsujimura  19 Oct 2005 / 2 Nov 2005
 *
 * $Log: /comm/bookey/getString.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     05/11/02 15:30 Tsujimura543
 * putMMmemo.c ���番���A�Ɨ�������
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getString.c 1     09/05/14 3:48 tsupo $";
#endif

/*
 *  getStringImplanted()
 *      ������ src ����AstartString �� endString �ŋ��܂ꂽ������
 *      ������𒊏o(�������̂� dst �Ɋi�[)����
 */
char    *
getStringImplanted(
        char       *dst,
        const char *src,
        const char *startString,
        const char *endString
    )
{
    char    *p, *q;
    int     len = strlen( startString );

    *dst = NUL;
    p = strstr( src, startString );
    if ( p ) {
        p += len;
        if ( strlen( endString ) == 1 )
            q = strchr( p, *endString );
        else
            q = strstr( p, endString );
        if ( q ) {
            strncpy( dst, p, q - p );
            dst[q - p] = NUL;
        }
    }

    return ( dst );
}

/*
 * getValue.c
 *      �w�蕶����� id �����̒l�Ƃ��Ă���(input)�v�f�� value ������
 *      �l���擾����
 *          written by H.Tsujimura  29 Jun 2006 / 18 Jan 2007
 *
 * History:
 * $Log: /comm/bookey/getValue.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/01/19 0:11 Tsujimura543
 * �R�����g���C��
 * 
 * 2     07/01/19 0:09 Tsujimura543
 * id�����Ō�����Ȃ������ꍇ�́Aname�����ŒT���悤�ɂ���
 * (Buzzurl �� name�������g���Ă���) [putNiftyClip.c �� getValue()
 * �� putEcNavi.c  �� getValue() �̔����Ȏd�l�̈Ⴂ�������Ƃ��Ă���]
 * 
 * 1     07/01/18 22:45 Tsujimura543
 * putEcNavi.c �� putNiftyClip.c �̂��ꂼ��ɔz�u���Ă����� getValue() ��
 * �����A�Ɨ������� (getValue.c �ֈړ�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getValue.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char *
getValue( const char *p, const char *name )
{
    Thread  static char value[BUFSIZ];

    value[0] = NUL;
    if ( p && *p ) {
        char    target[BUFSIZ];
        char    *q, *r;

        sprintf( target, "id=\"%s\" value=\"", name );
        q = strstr( p, target );
        if ( !q ) {
            sprintf( target, "name=\"%s\" value=\"", name );
            q = strstr( p, target );
        }
        if ( q ) {
            q += strlen( target );
            r = strchr( q, '"' );
            if ( r ) {
                strncpy( value, q, r - q );
                value[r - q] = NUL;
            }
        }
    }

    return ( value );
}

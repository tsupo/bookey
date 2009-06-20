/*
 *  justify.c
 *      Shift_JIS ��������w��o�C�g���ȓ��Ɋۂ߂鏈��
 *          written by H.Tsujimura  22 Aug 2006 / 18 Jan 2007
 *
 * $Log: /comm/bookey/justify.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/01/18 15:12 Tsujimura543
 * justify() �� Delete1470net.cpp ���番���A�Ɨ�������
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/justify.c 1     09/05/14 3:48 tsupo $";
#endif

char    *
justify( char *s, size_t len )
{
    char    *p = s;

    if ( s && *s && (strlen( s ) > len) ) {
        BOOL    kanjiFlag = FALSE;
        size_t  i = 0;

        while ( *p ) {
            if ( ++i > len )
                break;
            if ( !kanjiFlag && iskanji1( *p ) )
                kanjiFlag = TRUE;
            else
                kanjiFlag = FALSE;
            *p++;
        }
        if ( kanjiFlag )
            *(p - 1) = NUL;
        else
            *p = NUL;

        strcat( s, getLanguageCode() == 0x0411 ? "�c�c" : "..." );
    }

    return ( s );
}

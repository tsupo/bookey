/*
 * clip saver <<getLocalOpml>>
 *
 *      ���[�J��OPML�t�@�C�� �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  26 Oct 2006
 *
 * $Log: /comm/bookey/getLocalOpml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     06/10/26 21:31 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getLocalOpml.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20

MyClip  *
getLocalOpml(
        const char *filename,   /* (I) ���[�J��OPML�t�@�C��           */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    )
{
    MyClip  *mp = NULL;
    FILE    *fp = fopen( filename, "r" );

    if ( fp ) {
        mp = inputOPML( numOfClips, fp );
        fclose( fp );
    }
    else
        *numOfClips = 0;

    return ( mp );
}

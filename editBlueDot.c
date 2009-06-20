/*
 *  editBlueDot.c
 *      �u�w�胆�[�U�� Blue Dot �Ŏg���Ă���^�O�̈ꗗ�v���擾����
 *          written by H.Tsujimura  26 Jan 2007 / 30 Jan 2007
 *
 * $Log: /comm/bookey/editBlueDot.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/01/30 18:47 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 1     07/01/30 18:33 Tsujimura543
 * getTagListOnBlueDot() �ɑ������鏈���� UserInfo.cpp ���番���A
 * �Ɨ�������
 */

#include "myClip.h"
#include "delicious.h"
#include "bluedot.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editBlueDot.c 1     09/05/14 3:48 tsupo $";
#endif


TagList *
getTagListOnBlueDot(
        const char *username,
        const char *password,
        int        *numOfTags )
{
    TagList         *p = NULL;
    DELICIOUS_TAGS  *tp;
    long            num = 0;

    *numOfTags = 0;

    num = getNumberOfTagsOnBlueDot( username, password );
    tp  = (DELICIOUS_TAGS *)malloc( sizeof ( DELICIOUS_TAGS ) * num );
    if ( tp ) {
        *numOfTags = getListOfTagsOnBlueDot( username, password, &num, tp );
        if ( *numOfTags > 0 ) {
            p = (TagList *)malloc( sizeof (TagList) * *numOfTags );
            if ( p ) {
                int             i;
                TagList         *q = p;
                DELICIOUS_TAGS  *r = tp;

                for ( i = 0; i < *numOfTags; i++, q++, r++ )
                    strcpy( q->tag, r->tag ); 
            }
        }
        free( tp );
    }

    return ( p );
}
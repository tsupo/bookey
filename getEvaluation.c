/*
 *  getEvaluation.c
 *      MM/Memo �`���́u�]���v
 *          written by H.Tsujimura  19 Oct 2005 / 17 Nov 2006
 *
 * $Log: /comm/bookey/getEvaluation.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     06/11/27 16:01 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 3     06/11/27 15:58 Tsujimura543
 * �u�]���v�̎w�肪���݂��Ȃ��ꍇ�� title �̕����R�[�h�ϊ����K�v�ł���
 * ���Ƃ�Y��Ă��� (��������)
 * 
 * 2     06/11/17 15:25 Tsujimura543
 * getEvaluation() �ɑ�2������ǉ�
 * 
 * 1     06/11/17 14:43 Tsujimura543
 * �V�K�쐬 (���܂Ŋe�֐������Ŋe�X�������Ă����̂��A���ʊ֐������Ă݂�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getEvaluation.c 1     09/05/14 3:48 tsupo $";
#endif

//  MM/Memo �`���́u�]���v(title �̐擪�ɖ��ߍ��܂�Ă���)���擾���A
//  title �𑼂̃\�[�V�����u�b�N�}�[�N�T�[�r�X�ւ��̂܂܃C���|�[�g��
//  ����`���ɕϊ�����
//
//      MM/Memo �� title �̗� (�ȉ��̂悤��3��ނ̃p�^�[��������)
//          �E��� + �]�� + �^�C�g��
//              [sw](3)�wDublin Core Metadata Initiative (DCMI)�x
//          �E�]�� + �^�C�g��
//              (3)�wDublin Core Metadata Initiative (DCMI)�x
//          �E�^�C�g��
//              �wDublin Core Metadata Initiative (DCMI)�x
int
getEvaluation( char *title, int changeCode )
{
    const char  *p, *q;
    BOOL        multiple = FALSE;
    int         rate = 0;
    char        temp[MAX_DESCRIPTION_LEN];
    char        tmpTitle[MAX_DESCRIPTION_LEN];

    temp[0] = NUL;

    // �������� Shift_JIS �ɕϊ����Ă����Ă���A������i�߂�
    p = utf2sjis( title );
    if ( !p )
        p = euc2sjis( title );
    strcpy( tmpTitle, p ? p : title );

    p = strstr( tmpTitle, "�w" );
    q = strstr( tmpTitle, "�x" );
    if ( q && *(q + 2) ) {
        const char  *r;
        do {
            r = strstr( q + 2, "�x" );
            if ( r ) {
                q = r;
                multiple = TRUE;
            }
        } while ( r );
    }
    if ( p && q && (p < q) && (*(q + 2) == NUL) &&
         ((p == tmpTitle)   ||
          (*(p - 1) == ')') ||
          (*(p - 1) == ']')    )                   ) {
        if ( multiple == FALSE )
            p = getStringImplanted( temp, tmpTitle, "�w", "�x" );
        else {
            // �w�x������q�\���ɂȂ��Ă���ꍇ
            ///  -- �����΂�O���́w�x���O��
            strcpy( temp, p + 2 );
            temp[strlen(temp) - 2] = NUL;
            p = temp;
        }
        if ( p && *p ) {
            if ( ((tmpTitle[0] == '(') && (tmpTitle[2] == ')')) ||
                 ((tmpTitle[4] == '(') && (tmpTitle[6] == ')'))    ) {
                // �u�]���v�� title ������o��
                rate = atol( (tmpTitle[0] == '(') && (tmpTitle[2] == ')')
                                 ? &(tmpTitle[1])
                                 : &(tmpTitle[5]) );
            }
        }
    }

    // title ����u��ށv�A�u�]���v(�����݂���ꍇ)����菜�������̂�
    // �V���� title �ɂ��� [����ɁA(�u�]���v�����݂��邩�ǂ����Ɋւ�
    // �炸�AShift_JIS ����)�I���W�i���̕����R�[�h�ɖ߂��Ă���]
    q = temp[0] ? temp : tmpTitle;
    if ( *q ) {
        switch ( changeCode ) {
        case EUC2UTF:
            p = sjis2euc( q );
            strcpy( title, p ? p : q );
            break;
        case SJIS2UTF:
            strcpy( title, q );
            break;
        case UTF8:
        default:
            p = any2utf( q );
            strcpy( title, p ? p : q );
            break;
        }
    }

    return ( rate );
}

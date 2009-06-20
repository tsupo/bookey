/*
 *  outputOpera6Adr.c
 *      �u�b�N�}�[�N�� opera6.adr �`���̃e�L�X�g�t�@�C���Ƃ��ďo�͂���
 *          written by H.Tsujimura  10 Nov 2006
 *
 * $Log: /comm/bookey/outputOpera6Adr.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     06/11/16 13:55 Tsujimura543
 * �^�O�̑��o�C�g��(�^�O�ƃ^�O����؂镶�����܂�)��512�o�C�g���傫���ƁA
 * �N���b�V������s��ɑΏ�
 * 
 * 2     06/11/14 19:16 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     06/11/10 19:39 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/outputOpera6Adr.c 1     09/05/14 3:48 tsupo $";
#endif

char    *regularize( char *p );


void
outputOpera6Adr(
        const MyClip *mp,
        int          numOfClips,
        const char   *title,
        int          codeChange,
        FILE         *fp
    )
{
    int     i;
    char    buf[BUFSIZ];
    char    tag[4096];
    char    comment[4096];
    char    *p;
    long    id = 1001;  /* �b�� */

    fputs( "Opera Hotlist version 2.0\n"
           "Options: encoding = utf8, version=3\n\n",
           fp );

    switch ( codeChange ) {
    case SJIS2UTF:
        p = sjis2utf( title );
        break;

    case EUC2UTF:
        p = euc2utf( title );
        break;

    case UTF8:
    default:
        p = NULL;
        break;
    }
    fprintf( fp, "#FOLDER\n\tID=%d\n\tNAME=%s\n\n",
             id++, p ? p : title );

    for ( i = 0; i < numOfClips; i++ ) {
        switch ( codeChange ) {
        case SJIS2UTF:
            p = sjis2utf( mp[i].title );
            strcpy( buf, p ? p : mp[i].title );
            p = sjis2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = sjis2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case EUC2UTF:
            p = euc2utf( mp[i].title );
            strcpy( buf, p ? p : mp[i].title );
            p = euc2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = euc2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case UTF8:
        default:
            strcpy( buf, mp[i].title );
            strcpy( tag, mp[i].tags );
            strcpy( comment, mp[i].comment );
            break;
        }

        regularize( buf );
        regularize( tag );
        regularize( comment );

        fprintf( fp, "#URL\n\tID=%d\n\tNAME=%s\n\tURL=%s\n",
                 id++, buf, mp[i].url );
        if ( comment[0] ) {
            if ( tag[0] )
                fprintf( fp, "\tDESCRIPTION=%s (tags: %s)\n", comment, tag );
            else
                fprintf( fp, "\tDESCRIPTION=%s\n", comment );
        }
        fputs( "\n", fp );
    }

    fputs( "-\n\n", fp );
}

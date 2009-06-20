/*
 *  �w�� URL ���� ASIN ���擾����
 *      written by H.Tsujimura  24 May 2006
 *
 * $Log: /comm/bookey/getASIN.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     06/09/11 11:32 Tsujimura543
 * 2006�N9��8���A9���ɏo�������V�����p�^�[���� URL �ɂ��Ή�
 * 
 * 4     06/09/04 22:29 Tsujimura543
 * �V�����p�^�[���� URL �ɑΉ�
 * 
 * 3     06/05/25 21:37 Tsujimura543
 * /tg/detail/-/ �Ɋւ��� books �ȊO���Ή� (����m�F�ς�)
 * 
 * 2     06/05/25 21:18 Tsujimura543
 * /tg/detail/-/books/ �ȃy�[�W(�ڍ׉���y�[�W)�ɂ��Ή�����
 * 
 * 1     06/05/24 17:13 Tsujimura543
 * �V�K�쐬
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getASIN.c 1     09/05/14 3:48 tsupo $";
#endif

/*
 *  getASIN()
 *      URL �Ɋ܂܂�� ASIN �����o��
 *      (amazon, �͂Ă� �� URL ���Ώ�)
 */
char    *
getASIN(
        const char *url,    /* (I) ��͑Ώ� URL */
        char       *asin    /* (O) ASIN ������  */
    )
{
    char    *p;
    char    *q;

    asin[0] = NUL;
    p = strstr( url, "/ASIN/" );
    if ( !p )
        p = strstr( url, "/asin/" );    /*�u�͂Ăȁv�̏ꍇ���܂� */
    if ( !p ) {
        p = strstr( url, "/gp/product/" );
        if ( p ) {
            p += 6;
            if ( !strncmp( p + 6, "images/", 7 ) )
                p += 7;
        }
    }
    if ( p )
        p += 6;

    if ( !p && strstr( url, "amazon" ) ) {
        p = strstr( url, "/detail/" );
        if ( p ) {
            /* �C���X�^���g�X�g�A (���̃p�^�[���̏ꍇ�͕K���A���O�� */
            /* associate ID �����݂���)                             */
            if ( (*(p - 1) >= '0') && (*(p - 1) <= '9') )
                p += 8;
            else
                p = NULL;
        }

        if ( !p ) {
            /* �������� (2006�N8��24�����납��o�����n�߂��`��) */
            p = strstr( url, "/dp/" );
            if ( p )
                p += 4;
        }
        if ( !p ) {
            /* 
             *  /tg/�C�ӂ̕�����/-/XXX/ ��
             *  /tg/�C�ӂ̕�����/�C�ӂ̕�����/-/XXX/ �̏ꍇ
             */
            p = strstr( url, "/tg/" );
            q = strstr( url, "/-/"  );
            if ( p && q && (p < q) )
                p = q + 3;
            else
                p = NULL;
        }
    }

    if ( p ) {
        if ( !strncmp( p, "list/", 5 ) )
            p += 5;
        q = strchr( p, '/' );
        if ( q ) {
            strncpy( asin, p, q - p );
            asin[q - p] = NUL;
        }
        else if ( strlen( p ) > 10 ) {
            strncpy( asin, p, 10 );
            asin[10] = NUL;
        }
        else
            strcpy( asin, p );
    }

    return ( asin );
}


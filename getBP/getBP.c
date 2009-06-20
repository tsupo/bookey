/*
 * clip saver <<getBP>>
 *
 *      BlogPeople IB �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  23 Jun 2005
 *
 * $Log: /comm/bookey/getBP/getBP.c $
 * 
 * 1     09/05/14 4:23 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 20    07/01/18 13:40 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 19    06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 18    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 17    05/11/02 13:09 Tsujimura543
 * BPIB �Ƃ����^�O�������I�ɕt������̂���߂�
 * 
 * 16    05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 15    05/09/30 17:42 Tsujimura543
 * outputOPML() �Ɉ�����ǉ�
 * 
 * 14    05/09/28 20:42 Tsujimura543
 * �O���ϐ��ւ̃A�N�Z�X��p�~
 * 
 * 13    05/09/28 13:53 Tsujimura543
 * getIB() ���u�b�N�}�[�N�Ǘ��c�[������Ăяo����悤�ɂ���
 * 
 * 12    05/09/27 18:29 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 11    05/09/26 20:50 Tsujimura543
 * outputOPML() �� getBPT �̂��̂Ɠ���
 * 
 * 10    05/09/26 20:36 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓������� (bug�C��)
 * 
 * 9     05/09/26 20:18 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓������� (�Â�)
 * 
 * 8     05/09/26 20:10 Tsujimura543
 * struct myClip �̃����o tag �� tags �ɖ��̕ύX
 * 
 * 7     05/09/26 20:04 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓�������
 * 
 * 6     05/09/26 19:53 Tsujimura543
 * struct myClip �̃����o catrgory �� tag �ɖ��̕ύX
 * 
 * 5     05/09/26 19:38 Tsujimura543
 * �ϊ����ʂ�W���G���[�o�͂ɕ\������̂̓f�o�b�O�r���h���݂̂ɂ���
 * 
 * 4     05/09/26 18:55 Tsujimura543
 * �����������t�@�N�^�����O (�܂��܂����t�@�N�^�����O�̗]�n����܂���)
 * 
 * 3     05/09/26 18:45 Tsujimura543
 * �������� OPML �t�@�C���� title �� BlogPeople Instant Bookmarks �ɂ���
 * 
 * 2     05/06/27 14:18 Tsujimura543
 * �{�c�[���� clcoo ��A�g�����āAdel.icio.us �ɃC���|�[�g�ł��邱�Ƃ��m�F
 * 
 * 1     05/06/23 19:52 Tsujimura543
 * �ŏ��̔�
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBP/getBP.c 1     09/05/14 4:23 tsupo $";
#endif

/* BlogPeople IB �ɓo�^�ς݂̃u�b�N�}�[�N���擾������@�́A
 * �ȉ��̂��̂�����
 *  (1) �Ǘ���ʂ� html �t�@�C������͂��ď��𒊏o
 *  (2) blog �\���p�� Javascript ���擾�A��͂��ď��𒊏o
 *  (3) RSS ���擾�A��͂��ď��𒊏o
 *  (4) OPML ���擾�A��͂��ď��𒊏o
 *  (5) PHP �ŃC���N���[�h�ł���`�� (���̂� html) ���擾�A��͂��ď��𒊏o
 *
 * �Ȃ��A
 *      (1) �̕��@�́A�u�b�N�}�[�N�o�^�������u��/�� ��:���v�̂��߁u�N�v���s��
 *      (3) �� RSS �t�@�C���ɂ́u���ށv(dc:subject) ���܂܂�Ȃ����Ƃƃ\�[�g��
 *      ��Ă��鏇���s��(�o�^�������ł��Ȃ����AURL �� abc ���ł��Ȃ�)
 *      (4) �� OPML �t�@�C���ɂ��u���ށv���܂܂�Ȃ����ƂƁA�\�[�g����Ă��鏇
 *      ���s��(�o�^�������ł��Ȃ����AURL �� abc ���ł��Ȃ�)
 *      (2) �` (5) �� URL �� BlogPeolpe �̃��_�C���N�^�o�R�̂��̂ɂȂ��Ă���
 * �Ƃ��������_������
 *
 *      �� (3)�A(4) �̃\�[�g���́A�܂��A�u���ށv�Ń\�[�g������A�o�^������(��
 *         �����̂���V�������̂ւ̏���)�Ń\�[�g����Ă���͗l (�Ǘ���ʂ����
 *         �ݒ�ɂ��A�t��(�V���̂��̂���Â����̂�)�Ƀ\�[�g���邱�Ƃ��\)
 * 
 * �ȏ�𓥂܂��A(5) �� html ���擾���A��́A��񒊏o����Ƃ������@���̗p����
 */


#define MAX_NUMBER_OF_IB    100 /* BlogPeople IB �͍ő�100�� */

MyClip  *
getIB( const char *ibID, int *numOfClips )
{
    char    *response;
    char    url[MAX_URLLENGTH];
    char    tmp[BUFSIZ * 2];
    char    *p, *q, *r;
    int     maxNum = MAX_NUMBER_OF_IB;
    int     yyyy, mm, dd, HH, MM, num;
    MyClip  *mp = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 20;

    *numOfClips = num = 0;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    sprintf( url, "http://www.blogpeople.net/display/usr/ib/%s.html", ibID );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    p = http_get( url, response );
    if ( !p || !(*p) || !(*response) ) {
        free( response );
        return ( mp );
    }

    mp = (MyClip *)malloc( sizeof ( MyClip ) * maxNum );
    if ( mp ) {
        char    tag[80];
        char    *t = sjis2utf( "title=\"�X�V��:" );
        int     tlen = strlen( t );

        memset( mp, 0x00, sizeof ( MyClip ) * maxNum );
        p = response;
        tag[0] = NUL;
        while ( *p ) {
            if ( !strncmp( p, "<span class=\"blogpeople-linklist\">", 34 ) ) {
                q = p + 34;
                r = strstr( q, "</span>" );
                if ( r ) {
                    strncpy( tag, q, r - q );
                    tag[r - q] = NUL;
                    p = r + 7;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p,
            "<a href=\"http://www.blogpeople.net/cgi-bin/ib_click.cgi?u=http",
                           62 ) ) {
                q = p + 58;
                r = strstr( q, "\" " );
                if ( r ) {
                    strncpy( tmp, q, r - q );
                    tmp[r - q] = NUL;
                    strcpy( mp[num].url, decodeURL( tmp ) );
                    p = r + 2;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p, t, tlen ) ) {
                q = p + tlen;
                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                yyyy = 2000 + (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                mm   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                dd   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                HH   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                MM   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                mp[num].yyyy = yyyy;
                mp[num].mm   = mm;
                mp[num].dd   = dd;
                mp[num].HH   = HH;
                mp[num].MM   = MM;
                mp[num].SS   = 0;

                p = q + 20;

                r = strchr( q, '>' );
                if ( r ) {
                    r++;
#ifdef  _DEBUG
                    if ( tag[0] ) {
                        if ( !strstr( tag, "BPIB" ) )
                            strcat( tag, " BPIB" );
                    }
                    else
                        strcpy( tag, "BPIB" );
#endif  /* _DEBUG */
                    strcpy( mp[num].tags, tag );

                    q = strstr( r, "</a>" );
                    if ( q ) {
                        strncpy( mp[num].title, r, q - r );
                        mp[num].title[q - r] = NUL;
                        p = q + 4;
                    }

                    num++;
                    if ( num >= maxNum )
                        break;
                }

                continue;
            }

            p++;
        }
    }

    free( response );
    *numOfClips = num;

    return ( mp );
}

#ifdef  GET_BLOGPEOPLE_IB_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *IBIDForBlogPeople,
        BOOL *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'd':
                    if ( argv[i][j + 1] ) {
                        strcpy( IBIDForBlogPeople, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( IBIDForBlogPeople, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    if ( getLanguageCode() == 0x0411 ) {
        // ���{��
        fprintf( stderr,
                 "getBP: BlogPeople IB �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tBlogPeople IB ����z���o�������e�� OPML �t�@�C���Ƃ���"
                 "�o�͂���\n" );
        fprintf( stderr,
                "    getBP [-x] -d 16�i16����ID\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
        fprintf( stderr,
                 "\t16�i16����ID: BlogPeople IB �́u��{�ݒ�v�́u11.�R�[�h"
                 "�̐����v\n\t��OPML�𐶐������Ƃ��� URL �Ɋ܂܂��16�i16��"
                 "�̕����񕔕��̂���\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getBP: get bookmarks from BlogPeople IB, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getBP [-x] -d hashcode\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
        fprintf( stderr,
                 "\thashcode: Visit the web page of BlogPeople IB - \"11. "
                 "Generate\n\t\tcode\" - \"Configure Base Settings\", "
                 "generate OPML code,\n\t\tand get hashcode as 16 columns of "
                 "HEX string from this OPML\n\t\tcode.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    ibID[MAX_USERIDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( ibID, 0x00, MAX_USERIDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, ibID, &useProxy );

    if ( !(ibID[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* BlogPeople IB �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getIB( ibID, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  BlogPeople IB ���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips,
                    "BlogPeople Instant Bookmarks", UTF8, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLOGPEOPLE_IB_EXE */

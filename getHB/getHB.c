/*
 * clip saver <<getHB>>
 *
 *      �͂Ăȃu�b�N�}�[�N �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  26 Sep 2005
 *
 * $Log: /comm/bookey/getHB/getHB.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    08/11/28 17:03 Tsujimura543
 * getHB() ���Ƀ��g���C������ǉ�
 * 
 * 14    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 13    07/01/17 22:59 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 12    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() �𓱓��BMyClip �\���̊i�[�̈�m�ۏ�����
 * ���ʊ֐������Ă݂�
 * 
 * 11    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 10    05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 9     05/10/25 14:10 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 8     05/10/03 23:06 Tsujimura543
 * NUM_OF_INFO_PER_HATENA_API �� #define �� myClip.h �Ɉڂ�
 * 
 * 7     05/10/03 22:54 Tsujimura543
 * ���t�@�N�^�����O�����{
 * 
 * 6     05/09/30 17:42 Tsujimura543
 * outputOPML() �Ɉ�����ǉ�
 * 
 * 5     05/09/28 22:22 Tsujimura543
 * �O���ϐ��ւ̃A�N�Z�X��p�~
 * 
 * 4     05/09/28 13:30 Tsujimura543
 * getHB() ���u�b�N�}�[�N�Ǘ��c�[������Ăяo����悤�ɂ���
 * 
 * 3     05/09/27 18:30 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 2     05/09/26 20:55 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓�������
 * 
 * 1     05/09/26 18:47 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getHB/getHB.c 1     09/05/14 3:48 tsupo $";
#endif


/* �͂Ăȃu�b�N�}�[�N �ɓo�^�ς݂̃u�b�N�}�[�N���擾������@�́A
 * �ȉ��̂��̂�����
 *  (1) http://b.hatena.ne.jp/���[�U�� ���擾�A��͂��ď��𒊏o
 *      (����ɉߋ��ɑk���ău�b�N�}�[�N���擾�E���o)
 *  (2) �͂Ăȃu�b�N�}�[�N Atom API (FeedURI �ւ� GET) ���g���Ď����̃u�b�N
 *      �}�[�N���擾
 *  (3) �͂Ăȃu�b�N�}�[�N REST API ���g���Ďw�胆�[�U�̃u�b�N�}�[�N���擾
 *
 * (2) �́u�ŋ߁v�̃u�b�N�}�[�N�����擾�ł��Ȃ����߁A�{�c�[���ł� (3) ���g��
 * ���Ƃɂ���B
 */

MyClip  *
getHB( const char *hatenaID, int *numOfClips )
{
    int             max    = 1000; /* �b�� */
    int             cnt    = 0;
    int             block  = 1;
    long            num    = NUM_OF_INFO_PER_HATENA_API, n;
    long            offset = 0;
    BOOL            more   = TRUE;
    HATENA_BOOKMARK posts[NUM_OF_INFO_PER_HATENA_API];
    MyClip          *mp    = NULL;
    int             retry  = 0;

    *numOfClips = 0;

    do {
        long    i;
        MyClip  *newClip_p;

        num = NUM_OF_INFO_PER_HATENA_API;
        n = getRecentPostsOnHatenaUser(hatenaID, offset, &num, posts, &more);
        if ( n <= 0 ) {
            if ( more == TRUE ) {
                retry++;
                if ( retry < 5 ) {
                    Sleep( 2000 );
                    continue;
                }
            }
            break;
        }
        retry = 0;

        for ( i = 0; i < n; i++ ) {
            newClip_p = allocateMyClipIfNecessary( &mp, max, &block, cnt );
            if ( !newClip_p ) {
                more = FALSE;
                break;
            }
            mp = newClip_p;

            strcpy( mp[cnt].comment, posts[i].summary );
            strcpy( mp[cnt].tags,    posts[i].tags );
            strcpy( mp[cnt].title,   posts[i].title );
            strcpy( mp[cnt].url,     posts[i].href );
            mp[cnt].yyyy = posts[i].yyyy;
            mp[cnt].mm   = posts[i].mm;
            mp[cnt].dd   = posts[i].dd;
            mp[cnt].HH   = posts[i].HH;
            mp[cnt].MM   = posts[i].MM;
            mp[cnt].SS   = posts[i].SS;

            cnt++;
        }
        offset += n;
    } while ( more == TRUE );

    *numOfClips = cnt;

    return ( mp );
}

#ifdef  GET_HATENA_BOOKMARK_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForHatena,
        BOOL *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( usernameForHatena, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForHatena, argv[i] );
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
                 "getHB: �͂Ăȃu�b�N�}�[�N �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\t�͂Ăȃu�b�N�}�[�N����z���o�������e�� OPML �t�@�C����"
                 "���ďo�͂���\n");
        fprintf( stderr,
                 "    getHB [-x] -u ���[�U��\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getHB: get bookmarks from 'Hatena Bookmark', and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getHB [-x] -u username\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    hatenaID[MAX_USERIDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( hatenaID, 0x00, MAX_USERIDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, hatenaID, &useProxy );

    if ( !(hatenaID[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* �͂Ăȃu�b�N�}�[�N�֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getHB( hatenaID, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  �͂Ăȃu�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "Hatena Bookmark", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_HATENA_BOOKMARK_EXE */

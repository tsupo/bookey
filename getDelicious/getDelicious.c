/*
 * clip saver <<getDelicious>>
 *
 *      del.icio.us �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  2 Jun 2005 / 27 Sep 2005
 *
 * History:
 * $Log: /comm/bookey/getDelicious/getDelicious.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 16    08/07/25 0:36 Tsujimura543
 * private saving �ɑΉ�
 * 
 * 15    07/04/16 16:44 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 14    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 13    07/01/17 21:46 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 12    06/10/07 1:57 Tsujimura543
 * http ������M�҂��^�C���A�E�g���Ԃ��u�b�N�}�[�N���ɔ�Ⴕ�Đݒ肷��
 * ���ƂŁA�u�b�N�}�[�N���������ꍇ�ł��S�u�b�N�}�[�N�̎擾�ɐ�������
 * �\�������߂Ă݂�
 * 
 * 11    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 10    06/07/20 19:02 Tsujimura543
 * del.icio.us ����́u�擾�v���A�擾�Ɏ��s�����ꍇ�A�S�������̉����܂ł�
 * �擾
 * �ɐ����������A�_�C�A���O�ŕ\������悤�ɂ���
 * 
 * 9     06/07/20 14:58 Tsujimura543
 * getDelicious() �̌Ăяo�����ŁA���炩���ߑS���ŉ������邩����������ŁA
 * getDelicious() ���Ăяo���悤�ȏ󋵂ɔ����āA��3������ (O) ���� (I/O)
 * �ɕύX����
 * 
 * 8     06/06/20 15:54 Tsujimura543
 * �u�R�����g�v���Ɋ܂܂����s(\r,\n)����菜���悤�ɂ���
 * 
 * 7     05/10/20 16:07 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 6     05/09/30 17:42 Tsujimura543
 * outputOPML() �Ɉ�����ǉ�
 * 
 * 5     05/09/28 21:06 Tsujimura543
 * �O���ϐ��ւ̃A�N�Z�X��p�~
 * 
 * 4     05/09/28 13:35 Tsujimura543
 * getDelicious() ���u�b�N�}�[�N�Ǘ��c�[������Ăяo����悤�ɂ���
 * 
 * 3     05/09/27 18:26 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 2     05/09/27 16:33 Tsujimura543
 * �ϊ����ʂ�W���G���[�o�͂ɕ\������̂̓f�o�b�O�r���h���݂̂ɂ���
 * 
 * 1     05/09/27 16:31 Tsujimura543
 * �ŏ��̔�(d2hb �̃\�[�X�����ɍ쐬�BAPI �𑼂̃u�b�N�}�[�N�擾�֐��ɍ��킹��)
 */

#define  USE_DELICIOUS_POSTS
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDelicious/getDelicious.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
deliciousPosts2MyClip( DELICIOUS_POSTS *posts, int numOfPosts )
{
    MyClip  *mp;
    int     i;
    char    *s, *t;

    mp = (MyClip *)malloc( sizeof ( MyClip ) * numOfPosts );
    if ( !mp )
        return ( mp );

    for ( i = 0; i < numOfPosts; i++ ) {
        strcpy( mp[i].title,   posts[i].description );
        strcpy( mp[i].tags,    posts[i].tag );
        strcpy( mp[i].url,     posts[i].href );
        strcpy( mp[i].comment, posts[i].extended );

        s = mp[i].comment;
        while ( ((t = strchr( s, '\n' )) != NULL) ||
                ((t = strchr( s, '\r' )) != NULL)    ) {
            if ( (*(t + 1) == '\r') || (*(t + 1) == '\n') )
                strcpy( t, t + 1 );
            *t = ' ';
        }

        getDateTimeFromDateString( posts[i].dateTime,
                                   &(mp[i].yyyy), &(mp[i].mm), &(mp[i].dd),
                                   &(mp[i].HH), &(mp[i].MM), &(mp[i].SS) );

        if ( posts[i].shared == FALSE )
            mp[i].publication = PUB_PRIVATE;
    }

    return ( mp );
}

MyClip  *
getDelicious(
        const char *usernameForDelicious,   /* (I)   ���[�U��         */
        const char *passwordForDelicious,   /* (I)   �p�X���[�h       */
        int        *numOfClips              /* (I/O) �u�b�N�}�[�N���� */
    )
{
    long            n, num, numOfPosts = 0;
    DELICIOUS_POSTS *posts;
    MyClip          *mp = NULL;

    n = *numOfClips;
    *numOfClips = 0;

    /* del.icio.us �̃u�b�N�}�[�N���擾 */
    if ( n == 0 )
        num = getNumberOfBookmarksOnDelicious( usernameForDelicious,
                                               passwordForDelicious );
    else
        num = n;
    if ( num <= 0 )
        return ( mp );
    Sleep( 1000 );

    numOfPosts = num;
    posts = (DELICIOUS_POSTS *)
                malloc( sizeof ( DELICIOUS_POSTS ) * numOfPosts );
    if ( !posts )
        return ( mp );
    memset( posts, 0x00, sizeof ( DELICIOUS_POSTS ) * numOfPosts );

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * (numOfPosts / 100) );
                        // �u�b�N�}�[�N�����ɔ�Ⴕ���^�C���A�E�g���Ԃ�ݒ�
    n = getAllPostsOnDelicious( usernameForDelicious,
                                passwordForDelicious,
                                NULL,
                                &numOfPosts,
                                posts );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT );    // �f�t�H���g�l�ɖ߂��Ă���
    if ( n <= 0 ) {
        free( posts );
        return ( mp );
    }

    mp = deliciousPosts2MyClip( posts, n );
    if ( mp )
        *numOfClips = n;
    free( posts );

    return ( mp );
}

#ifdef  GET_DELICIOUS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForDelicious,
        char *passwordForDelicious,
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
                        strcpy( usernameForDelicious, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForDelicious, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForDelicious, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForDelicious, argv[i] );
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
                 "getDelicious: del.icio.us �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "    getDelicious [-x] -u ���[�U�� -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getDelicious: get bookmarks from del.icio.us, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getDelicious [-x] -u username -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    usernameForDelicious[MAX_USERIDLEN + 1];
    char    passwordForDelicious[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( usernameForDelicious, 0x00, MAX_USERIDLEN );
    memset( passwordForDelicious, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  usernameForDelicious, passwordForDelicious, &useProxy );

    if ( !(usernameForDelicious[0]) || !(passwordForDelicious[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* del.icio.us�o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getDelicious( usernameForDelicious, passwordForDelicious,
                       &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  del.icio.us���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "del.icio.us", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_DELICIOUS_EXE */

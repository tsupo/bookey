/*
 * clip loader <<putDelicious>>
 *
 *      OPML �� del.icio.us �o�^�v���O����
 *          written by H.Tsujimura  17 Jan 2005 / 27 Sep 2005
 *
 * History:
 * $Log: /comm/bookey/putDelicious/putDelicious.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 17    08/07/25 0:37 Tsujimura543
 * private saving �ɑΉ�
 * 
 * 16    07/11/12 19:09 Tsujimura543
 * any2sjisEx() �𓱓��AShift_JIS �Ȃ̂� EUC-JP ���ƌ�F����P�[�X�ɑΏ�
 * 
 * 15    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 14    07/01/23 16:42 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 13    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 12    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 11    06/11/16 19:31 Tsujimura543
 * �f�o�b�O�p��(�f�o�b�O�r���h���̂ݗL����)�R�[�h���폜
 * 
 * 10    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 9     06/08/17 11:50 Tsujimura543
 * ���g���C���A�O�̂��߂� Sleep() �����Ă݂�
 * 
 * 8     05/10/25 14:22 Tsujimura543
 * ���b�Z�[�W�{�b�N�X�̃^�C�g���Ɩ{���̕������t�ɂȂ��Ă����̂��C��
 * 
 * 7     05/10/25 14:12 Tsujimura543
 * �W���G���[�o�͂��Θb�ɗ��p�\���ǂ����𒲍�������@���C��
 * 
 * 6     05/10/20 21:13 Tsujimura543
 * ���͂̕����R�[�h�� Shift_JIS, EUC-JP, UTF-8 �̂ǂ�ł������悤�ɂ���
 * 
 * 5     05/10/19 17:23 Tsujimura543
 * �u�b�N�}�[�N�o�^���s���́u���g���C���邩�ǂ����̎���v������ύX
 * 
 * 4     05/10/11 18:02 Tsujimura543
 * ��3������ const �C���q��t��
 * 
 * 3     05/09/28 23:09 Tsujimura543
 * usage() ���C��
 * 
 * 2     05/09/28 19:37 Tsujimura543
 * putDelicious() �̎d�l(�����̐��A�߂�l�̌^)��ύX
 * 
 * 1     05/09/28 18:30 Tsujimura543
 * clipConverter.c ���� del.icio.us �ւ̃C���|�[�g������؂�o��
 */

#include "myClip.h"
#include "delicious.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDelicious/putDelicious.c 1     09/05/14 3:48 tsupo $";
#endif

typedef struct paramPutDeli {
    const char  *userName;
    const char  *password;
}   PARAM_DELI;

BOOL
_putDelicious(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    PARAM_DELI      *param = (PARAM_DELI *)(args->args);
    DELICIOUS_ENTRY entry;
    BOOL            ret = FALSE;

    errorString[0] = NUL;

    if ( mp->url[0] == NUL )
        return ( ret ); // ����I������

    any2sjisEx( entry.description, mp->title );
    any2sjisEx( entry.extended,    mp->comment );
    any2sjisEx( entry.tag,         mp->tags );

    strcpy( entry.url,         mp->url );
    sprintf( entry.dateTime,
             "%04d-%02d-%02dT%02d:%02d:%02dZ",
             mp->yyyy, mp->mm, mp->dd,
             mp->HH, mp->MM, mp->SS );

    entry.shared = (mp->publication == PUB_PRIVATE) ? FALSE : TRUE;

    ret = postEntryOnDelicious( param->userName, param->password, &entry );

    return ( ret );
}

void
putDelicious(
        const char   *userName2,
        const char   *password2,
        const MyClip *mp,
        int          numOfClips
    )
{
    PARAM_DELI  param;

    param.userName = userName2;
    param.password = password2;

    putBookmarks( "del.icio.us", mp, numOfClips, NULL, 0, &param,
                  _putDelicious );
}

#ifdef  PUT_DELICIOUS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForDelicious,
        char *passwordForDelicious,
        BOOL *useProxy,
        FILE **fp
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

                case 'i':
                    if ( argv[i][j + 1] ) {
                        FILE    *gp = fopen( &(argv[i][j + 1]), "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s ��������܂���\n"
                                      : "%s: Not found.\n",
                                     &(argv[i][j + 1]) );
                        }
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        FILE    *gp = fopen( argv[i + 1], "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s ��������܂���\n"
                                      : "%s: Not found.\n",
                                     argv[i + 1] );
                            exit( 255 );
                        }
                        i++;
                        j = strlen( argv[i] ) - 1;
                    }
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
        fprintf( stderr, "putDelicious: OPML �� del.icio.us �o�^�c�[��\n" );
        fprintf( stderr,
     "    putDelicious [-x] -u ���[�U�� -p �p�X���[�h [-i OPML�t�@�C����]\n");
        fprintf( stderr,
     "\t-x: proxy ���g��\n"
     "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
   "putDelicious: read bookmarks from OPML, and put them into del.icio.us\n");
        fprintf( stderr,
   "    putDelicious [-x] [-u username] [-p password] [-i OPMLfilename]\n" );
        fprintf( stderr,
   "\t-x: use http access via proxy server\n"
   "\t-i: If this option is not specified, read from standard input\n"
   "\t    instead of OPML\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    usernameForDelicious[MAX_USERIDLEN + 1];
    char    passwordForDelicious[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( usernameForDelicious, 0x00, MAX_USERIDLEN );
    memset( passwordForDelicious, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  usernameForDelicious, passwordForDelicious,
                  &useProxy, &fp );

    if ( !(usernameForDelicious[0]) || !(passwordForDelicious[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� del.icio.us �ɓo�^ */
        putDelicious( usernameForDelicious, passwordForDelicious,
                      mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_DELICIOUS_EXE */

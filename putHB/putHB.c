/*
 * clip loader <<putHB>>
 *
 *      OPML �� �͂Ăȃu�b�N�}�[�N �o�^�v���O����
 *          written by H.Tsujimura  2 Jun 2005 / 28 Sep 2005
 *
 * History:
 * $Log: /comm/bookey/putHB/putHB.c $
 * 
 * 2     09/06/18 0:53 tsupo
 * 0.63b��
 * 
 * 19    09/06/16 21:46 Tsujimura543
 * �u�R���N�V�����v�̓o�^���̂݁Aprivate(����J)�œ��e�ł��邱�Ƃ��m�F
 * (�͂Ăȃu�b�N�}�[�N�v���X���g���Ă���ꍇ)
 * -- �ʏ�̃u�b�N�}�[�N�� API �ɂ�� private �w����@���s��(�s�\?)
 * -- �Ȃ��߁A����̉ۑ�Ƃ���
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 18    07/11/12 19:16 Tsujimura543
 * any2sjisEx() �𓱓��AShift_JIS �Ȃ̂� EUC-JP ���ƌ�F����P�[�X�ɑΏ�
 * 
 * 17    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 16    07/02/16 16:19 Tsujimura543
 * �R�����g���C��
 * 
 * 15    07/02/16 16:16 Tsujimura543
 * ���łɓo�^����Ă���^�C�g���Ɠo�^���悤�Ƃ��Ă���^�C�g�����H���Ⴄ��
 * ���́A�o�^���悤�Ƃ��Ă���^�C�g���ŏ㏑�����邩�A���łɓo�^����Ă���
 * �^�C�g�������̂܂ܗ��p���邩�A�I���ł���悤�ɂ���
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
 * 11    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 10    06/07/24 19:22 Tsujimura543
 * �o�^���悤�Ƃ��Ă���Web�y�[�W�� title �̐擪�����s�̏ꍇ�A���s������
 * �̂ĂāA�c��̕����� titile �Ƃ��č̗p����悤�ɂ���
 * 
 * 9     06/06/28 21:06 Tsujimura543
 * �R�����g�ɉ��s���܂܂��ꍇ�A��菜���Ă���o�^����悤�ɂ���
 * 
 * 8     06/05/22 15:30 Tsujimura543
 * �o�^���s���� Sleep() �̃^�C�~���O�Asleep���鎞�Ԃ̒����𒲐�
 * 
 * 7     06/04/06 22:16 Tsujimura543
 * �u�R���N�V�����v�̓o�^(�ǉ�)�ɑΉ�����
 * 
 * 6     05/10/25 14:22 Tsujimura543
 * ���b�Z�[�W�{�b�N�X�̃^�C�g���Ɩ{���̕������t�ɂȂ��Ă����̂��C��
 * 
 * 5     05/10/25 14:12 Tsujimura543
 * �W���G���[�o�͂��Θb�ɗ��p�\���ǂ����𒲍�������@���C��
 * 
 * 4     05/10/20 21:13 Tsujimura543
 * ���͂̕����R�[�h�� Shift_JIS, EUC-JP, UTF-8 �̂ǂ�ł������悤�ɂ���
 * 
 * 3     05/10/19 17:23 Tsujimura543
 * �u�b�N�}�[�N�o�^���s���́u���g���C���邩�ǂ����̎���v������ύX
 * 
 * 2     05/10/11 18:02 Tsujimura543
 * ��3������ const �C���q��t��
 * 
 * 1     05/09/28 23:44 Tsujimura543
 * �V�K�쐬(d2hb.c ����͂Ăȃu�b�N�}�[�N�ւ̓o�^������؂�o���A�ėp��)
 */

#include "myClip.h"
#include "hatenaAPI.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putHB/putHB.c 2     09/06/18 0:53 tsupo $";
#endif

typedef struct paramPutHB   {
    const char      *userName;
    const char      *password;
    HATENA_BOOKMARK *entries;
}   PARAM_HB;

BOOL
_putHB(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    BOOL            ret      = FALSE;
    PARAM_HB        *param   = (PARAM_HB *)(args->args);
    HATENA_BOOKMARK *entries = param->entries + args->index;
    char            *p;
    char            title[1024];

    errorString[0] = NUL;

    strcpy( entries->href, mp->url );

    p = any2sjisEx( entries->title, mp->title );
    while ( p && ((*p == '\r') || (*p == '\n')) )
        p++;
    strcpy( entries->title, p ? p : mp->title );

    p = any2sjisEx( entries->summary, mp->comment );
    while ( p && (((p = strchr(entries->summary, '\r')) != NULL) ||
                  ((p = strchr(entries->summary, '\n')) != NULL)   ) )
        strcpy( p, p + 1 ); /* ���s����菜�� */

    any2sjisEx( entries->tags, mp->tags );

    memset( title, 0x00, 1024 );
    entries->entryID[0] = NUL;

    if ( mp->asin )
        ret = postBookmarkWithCollectionOnHatena(
                    param->userName, param->password,
                    entries->href,
                    title,
                    entries->summary,
                    entries->tags,
                    mp->publication == PUB_PRIVATE ? TRUE : FALSE,
                    entries->entryID );
    else
        ret = postBookmarkOnHatena(
                    param->userName, param->password,
                    entries->href,
                    title,
                    entries->summary,
                    entries->tags,
                    mp->publication == PUB_PRIVATE ? TRUE : FALSE,
                    entries->entryID );

    if ( (ret == TRUE) &&
         title[0] && !strcmp( title, entries->title ) ) {
        strcpy( entries->entryID, "0" );    /* title ��o�^�������K�v�Ȃ� */
    }

    return ( ret );
}

void
putHB(
        const char   *userName,  /* (I) �͂Ă�ID                       */
        const char   *password,  /* (I) �p�X���[�h                     */
        BOOL         useMyTitle, /* (I) �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    )
{
    int             ret, i;
    int             n = numOfClips;
    HATENA_BOOKMARK *entries;
    PARAM_HB        param;

    entries = (HATENA_BOOKMARK *)malloc( sizeof ( HATENA_BOOKMARK ) * n );
    if ( !entries )
        return;
    memset( entries, 0x00, sizeof ( HATENA_BOOKMARK ) * n );

    /* �͂Ăȃu�b�N�}�[�N�ɓo�^ */
    param.entries  = entries;
    param.userName = userName;
    param.password = password;
    putBookmarks( getLanguageCode() == 0x0411
                   ? "�͂Ăȃu�b�N�}�[�N"
                   : "Hatena Bookmark",
                  mp, numOfClips, NULL, 0, &param, _putHB );

    if ( useMyTitle ) {
        /* �u�b�N�}�[�N�� title �v�f���I���W�i���ɍ��킹�� */
        for ( i = 0; i < n; i++ ) {
            if ( atol( entries[i].entryID ) == 0 )
                continue;
            Sleep( 2000 );
            ret = editBookmarkOnHatena(
                        userName, password,
                        entries[i].href,
                        entries[i].title,
                        entries[i].summary,
                        entries[i].tags,
                        entries[i].entryID );
        }
    }

    free( entries );
}


#ifdef  PUT_HATENA_BOOKMARK_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForHatena,
        char *passwordForHatene,
        BOOL *useMyTitle,
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
                        strcpy( usernameForHatena, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForHatena, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForHatene, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForHatene, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;

                case 'F':
                    *useMyTitle = !(*useMyTitle);
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
                            exit( 255 );
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
        fprintf( stderr, "putHB: OPML �� �͂Ăȃu�b�N�}�[�N �o�^�c�[��\n" );
        fprintf( stderr,
         "    putHB [-x] [-F] -u �͂Ă�ID -p �p�X���[�h [-i OPML�t�@�C����]"
         "\n" );
        fprintf( stderr,
         "\t-x: proxy ���g��\n"
         "\t-F: ���łɓo�^����Ă���^�C�g���Ɠo�^���悤�Ƃ��Ă���^�C�g��\n"
         "\t    ���H���Ⴄ�ꍇ�́A�o�^���悤�Ƃ��Ă���^�C�g���ŏ㏑������\n"
         "\t    (�͂Ăȃu�b�N�}�[�N�ł́A�^�C�g���͑S���ŋ��L���Ă��܂��B\n"
         "\t     �㏑�����邩�ǂ����͐T�d�ɔ��f���Č��߂Ă�������)\n"
         "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n");
    }
    else {
        // �p��
        fprintf( stderr,
      "putHB: read bookmarks from OPML, and put them into Hatena Bookmark\n" );
        fprintf( stderr,
      "    putHB [-x] [-F] -u hatenaID -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-F: overwrite entry title, if original title was different from\n"
      "\t    your specified title\n"
      "\t    (Caution: entry title is shared by all users of Hatena Bookmark)"
      "\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    usernameForHatena[MAX_USERIDLEN + 1];
    char    passwordForHatena[MAX_PASSWDLEN + 1];
    BOOL    useProxy   = FALSE;
    BOOL    useMyTitle = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( usernameForHatena, 0x00, MAX_USERIDLEN );
    memset( passwordForHatena, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  usernameForHatena, passwordForHatena,
                  &useMyTitle, &useProxy, &fp );

    if ( !(usernameForHatena[0]) || !(passwordForHatena[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� �͂Ăȃu�b�N�}�[�N �ɓo�^ */
        putHB( usernameForHatena, passwordForHatena, useMyTitle,
               mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_HATENA_BOOKMARK_EXE */

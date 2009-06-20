/*
 * clip loader <<putJoltMark>>
 *
 *      OPML �� JoltMark �o�^�v���O����
 *          written by H.Tsujimura  21 Dec 2006
 *
 * History:
 * $Log: /comm/bookey/putJoltMark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     08/11/25 15:12 Tsujimura543
 * ckString ���o�����C��
 * (2008�N4��23���ȍ~�A�o�^�ł��Ȃ��Ȃ��Ă������ɑΏ�)
 * 
 * 7     07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 6     07/01/23 20:16 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 5     07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 4     07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 3     06/12/22 18:39 Tsujimura543
 * �o�^���悤�Ƃ��Ă���u�b�N�}�[�N�ɐݒ肳���u�]���v���A�����΂�ŏ���
 * �u�b�N�}�[�N�́u�]���v�ɂȂ��Ă��܂��s��ɑΏ�
 * ([��] mp->evaluation �� [��] mp[i].evaluation)
 * 
 * 2     06/12/21 18:07 Tsujimura543
 * ����m�F����
 * 
 * 1     06/12/21 15:31 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putJoltMark.c 1     09/05/14 3:48 tsupo $";
#endif


typedef struct paramPutJM   {
    const char  *ckString;
}   PARAM_JM;

BOOL
_putJoltMark(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_JM    *param = (PARAM_JM *)(args->args);
    char        url[MAX_URLLENGTH * 4];
    char        tmpTitle[2048];
    char        *p, *q;
    long        rate;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    rate = 0;

    /* �u�b�N�}�[�N�� POST */
    strcpy( url, "https://mark.jolt.jp/registerMark.do" );

    p = any2utf( mp->title );
    strcpy( tmpTitle, p ? p : mp->title );

    // MM/Memo �`���� title ���������߂̏���
    rate = getEvaluation( tmpTitle, UTF8 );
    q = tmpTitle;

    if ( rate == 0 )
        if ( (mp->evaluation >= EVL_ONE)  &&
             (mp->evaluation <= EVL_FIVE)    )
            rate = mp->evaluation;

    // �^�C�g��
    sprintf( request,
             "title=%s&",   // �ő�500�o�C�g
             encodeURLex2( q ) );

    // URL
    sprintf( request + strlen(request),
             "url=%s&",     // �ő�500�o�C�g
             encodeURL( mp->url ) );

    // �}�[�N��
    sprintf( request + strlen(request),
             "markName=%s&",// �ő�500�o�C�g
             encodeURLex2( q ) );
        // �b��I�ɁA�}�[�N���̓^�C�g���Ɠ������̂��g�����Ƃɂ���

    // ����
    p = any2utf( mp->comment );
    sprintf( request + strlen(request),
             "note=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // �u�]���v�͕K�{ (�f�t�H���g�́u��3�v)
    sprintf( request + strlen(request),
             "rate=%d&",
             (rate >= EVL_ONE) && (rate <= EVL_FIVE)
                ? rate
                : EVL_THREE );

    // ���J�E����J (�f�t�H���g�́u���J�v)
    sprintf( request + strlen(request),
             "publicMark=%s&",
             mp->publication == PUB_PRIVATE ? "false"
                                            : "true" );

    // �ۑ�
    sprintf( request + strlen(request),
             "saveFlag=%s&",
             "false" ); // �b��I�� false �ɂ���

    // �^�O (�X�y�[�X��؂�ōő�1000�o�C�g�܂�)
    p = any2utf( mp->tags );
    sprintf( request + strlen(request),
             "tags=%s&",
             encodeURL( p ? p : mp->tags ) );

    // �o�^��\��
    sprintf( request + strlen(request),
             "jumpTo=%s&",
             "pageInfo" ); // �}�[�N�o�^��A�y�[�W����\������

    // ckString
    sprintf( request + strlen(request),
             "ckString=%s&"
             "referer=&",
             param->ckString );

    sprintf( request + strlen(request),
             "regist=%s&",
             encodeURL( sjis2utf("�}�[�N�o�^") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        p = strstr( response, sjis2utf("�v�̃y�[�W���</title>") );
        if ( p )
            ret = TRUE; /* �o�^���� */
    }

    return ( ret );
}

void
putJoltMark(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    PARAM_JM    param;
    size_t      cookieSize = MAX_COOKIE_LEN;
    char        cookie[MAX_COOKIE_LEN + 1];
    int         ret;
    char        *response;
    char        url[MAX_URLLENGTH * 4];
    char        *p, *q;
    char        ckString[MAX_KEYLENGTH];
    size_t      sz;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* JoltMark �� login */
    ret = loginJoltMark( userName, password, cookie );
    if ( !ret ) {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "JoltMark �ւ� login �Ɏ��s���܂���\n"
                    : "JoltMark: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "JoltMark �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "JoltMark: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
        return;
    }

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response )
        return;

    /* ckString ���擾 */
    ckString[0] = NUL;
    strcpy( url, "http://mark.jolt.jp/mark/entryForm.do" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        q = strstr( response, "<form name=\"entryMarkForm\"" );
        if ( !q )
            q = response;
        p = strstr( q, "name=\"ckString\" value=\"" );
        if ( p ) {
            p += 23;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( ckString, p, q - p );
                ckString[q - p] = NUL;      // �U�� ckString
            }

            p = strstr( q, "name=\"ckString\" value=\"" );
            if ( p ) {
                p += 23;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( ckString, p, q - p );
                    ckString[q - p] = NUL;  // �{���� ckString
                }
            }
        }
    }
    free( response );
    if ( !(ckString[0]) )
        return;

    /* JoltMark �ɓo�^ */
    param.ckString = ckString;
    putBookmarks( "JoltMark", mp, numOfClips, cookie, cookieSize, &param,
                  _putJoltMark );
}


#ifdef  PUT_JOLTMARK_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
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
                        strcpy( username, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
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
        fprintf( stderr,
                 "putJoltMark: OPML �� JoltMark �o�^�c�[��\n" );
        fprintf( stderr,
    "    putJoltMark [-x] -u ���[�U�� -p �p�X���[�h [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
    "\t-x: proxy ���g��\n"
    "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putJoltMark: read bookmarks from OPML, and put them into JoltMark\n" );
        fprintf( stderr,
      "    putJoltMark [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� JoltMark �ɓo�^ */
        putJoltMark( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_JOLTMARK_EXE */

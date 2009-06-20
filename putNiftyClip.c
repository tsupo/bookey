/*
 * clip loader <<putNiftyClip>>
 *
 *      OPML �� �j�t�e�B�N���b�v �o�^�v���O����
 *          written by H.Tsujimura  29 Jun 2006
 *
 * History:
 * $Log: /comm/bookey/putNiftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    08/11/05 20:59 Tsujimura543
 * �R�}���h���C���ł���Ă�ł��� putNiftyClip() �̈������C��
 * (�R�}���h���C���łł́AAPI�L�[�́A�܂����Ή�)
 * 
 * 18    08/11/05 19:48 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v�֓o�^����v������ǉ��A����m�F����
 * 
 * 17    08/03/12 3:32 Tsujimura543
 * �o�^���s���Ɂu���s���������v���擾�\�ȏꍇ�͎擾����悤�ɂ���
 * 
 * 16    08/03/12 1:14 Tsujimura543
 * 2008�N3��11���́u@nifty�N���b�v�v���j���[�A���ɑΉ�����
 * 
 * 15    07/10/05 4:18 Tsujimura543
 * �\�[�X����
 * 
 * 14    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 13    07/01/23 17:10 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 12    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 11    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 10    07/01/18 22:45 Tsujimura543
 * putEcNavi.c �� putNiftyClip.c �̂��ꂼ��ɔz�u���Ă����� getValue() ��
 * �����A�Ɨ������� (getValue.c �ֈړ�)
 * 
 * 9     06/12/11 20:47 Tsujimura543
 * �u���J�t���O�v (public/private) �ɑΉ�
 * 
 * 8     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 7a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 7     06/08/31 16:38 Tsujimura543
 * �o�^�ɐ����������ǂ������f���������ύX (�]���̏����ł́u�o�^���s�v��
 * ���肳��Ă��܂��悤�ɂȂ�������)
 * 
 * 6     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 5     06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 4     06/07/18 21:04 Tsujimura543
 * ���O�C�����s���ɃG���[�_�C�A���O���o���悤�ɂ���
 * 
 * 3     06/07/18 20:47 Tsujimura543
 * &raquo: �֘A�̏������C��(�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����R�[�h�̌���
 * ��)
 * 
 * 2     06/07/12 15:51 Tsujimura543
 * 64 �� MAX_KEYLENGTH �ɒu��
 * 
 * 1     06/06/29 21:26 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putNiftyClip.c 1     09/05/14 3:48 tsupo $";
#endif


BOOL
_putNiftyClipWithApiKey(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    *apiKey   = (char *)(args->args);
    char    *p, *q;
    char    tag[80];
    int     i;
    BOOL    ret = FALSE;

    errorString[0] = NUL;

    // API�L�[ + URL
    sprintf( request,
             "api_key=%s&"
             "url=%s&",
             apiKey,
             encodeURL( mp->url ) );

    // �^�C�g��
    p = any2utf( mp->title );
    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( p ? p : mp->title ) );

    // �^�O�͍ő�10�܂� [�ő�100�����܂�]
    p = any2utf( mp->tags );
    q = p ? p : mp->tags;
    i = 0;
    do {
        p = strchr( q, ' ' );
        if ( p ) {
            strncpy( tag, q, p - q );
            tag[p - q] = NUL;
            sprintf( request + strlen(request),
                     "tag=%s&",
                     encodeURL( tag ) );
            i++;
            q = p + 1;
        }
        else {
            sprintf( request + strlen(request),
                     "tag=%s&",
                     encodeURL( q ) );
            break;
        }
    } while ( (i < 10) && *q );

    // �R�����g
    p = any2utf( mp->comment );
    sprintf( request + strlen(request),
             "comment=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // ���J�t���O
    sprintf( request + strlen(request),
             "public_flag=%s&"
             "alt=xml",
             mp->publication != PUB_PRIVATE ? "1" : "0" );

    setUpReceiveBuffer( response, sz );
    http_post( "http://api.clip.nifty.com/api/v1/clip/create",
               "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        p = strstr( response, "Bad Request" );
        if ( p ) {
            Sleep( 1000 );
            setUpReceiveBuffer( response, sz );
            http_post( "http://api.clip.nifty.com/api/v1/clip/update",
                       "application/x-www-form-urlencoded",
                       request, response );
        }
    }

    if ( *response ) {
        p = strstr( response, "<message>OK</message>" );
        if ( p )
            ret = TRUE;
        else {
            p = strstr( response, "<message>" );
            if ( p ) {
                p += 9;
                q = strstr( p, "</message>" );
                if ( q ) {
                    char    tmp[BUFSIZ];

                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    strcpy( errorString, utf2sjisEx( tmp ) );
                }
            }
        }
    }

    return ( ret );
}


BOOL
_putNiftyClip(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    url[MAX_URLLENGTH * 4];
    char    *p, *q;
    char    token[MAX_KEYLENGTH];
    char    tag[80];
    int     i;
    BOOL    ret = FALSE;

    errorString[0] = NUL;

    /* token ���擾 */
    token[0] = NUL;

    setUpReceiveBuffer( response, sz );
    http_getEx( "http://clip.nifty.com/create", response, cookie );
    if ( *response ) {
        p = getValue( response, "token" );
        if ( p ) {
            strcpy( token, p );

            /* �u�b�N�}�[�N�� POST */
            strcpy( url, "http://clip.nifty.com/create" );

            sprintf( request,
                     "token=%s&",
                     token );

            // �^�C�g��
            p = any2utf( mp->title );
            sprintf( request + strlen(request),
                     "title=%s&",
                     encodeURLex2( p ? p : mp->title ) );

            // URL
            sprintf( request + strlen(request),
                     "url=%s&",
                     encodeURL( mp->url ) );

            // �R�����g
            p = any2utf( mp->comment );
            sprintf( request + strlen(request),
                     "comment=%s&",
                     encodeURLex( p ? p : mp->comment ) );

            // �^�O�͍ő�10�܂� [�ő�100�����܂�]
            p = any2utf( mp->tags );
            q = p ? p : mp->tags;
            i = 0;
            do {
                p = strchr( q, ' ' );
                if ( p ) {
                    strncpy( tag, q, p - q );
                    tag[p - q] = NUL;
                    sprintf( request + strlen(request),
                             "%s%s",
                             i == 0 ? "suggesttags=" : "%20",
                             encodeURL( tag ) );
                    i++;
                    q = p + 1;
                }
                else {
                    sprintf( request + strlen(request),
                             "%s%s&",
                             i == 0 ? "suggesttags=" : "%20",
                             encodeURL( q ) );
                    break;
                }
            } while ( (i < 10) && *q );

            // ���J�t���O
            if ( mp->publication != PUB_PRIVATE )
                sprintf( request + strlen(request),
                         "public_flag=%s&",
                         "on" );

            // �W�����v��
            sprintf( request + strlen(request),
                     "moveto=mylist" );

            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );
            if ( *response ) {
                if ( strstr( response, sjis2utf("�N���b�v�ꗗ") ) )
                    ret = TRUE; /* �o�^���� */
                else {
                    p = strstr( response, "<h2>" );
                    if ( p ) {
                        p += 4;
                        q = strstr( p, "</h2>" );
                        if ( q ) {
                            char    tmp[BUFSIZ];
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;

                            p = utf2sjis( tmp );
                            if ( p )
                                strcpy( errorString, p );
                        }
                    }
                }
            }
        }
    }

    return ( ret );
}

void
putNiftyClip(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const char   *apiKey,    /* (I) API�L�[          */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;
    LCID    l = getLanguageCode();

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    if ( apiKey != NULL && *apiKey != NUL ) {
        putBookmarks( l == 0x0411
                        ? "�j�t�e�B�N���b�v"
                        : "nifty clip",
                      mp, numOfClips, NULL, 0, (void *)apiKey,
                      _putNiftyClipWithApiKey );
    }
    else {
        // �j�t�e�B�N���b�v�Ƀ��O�C��
        ret = loginNiftyClip( userName, password, cookie );
        if ( ret == 1 ) /* login ���� */
            putBookmarks( l == 0x0411
                            ? "�j�t�e�B�N���b�v"
                            : "nifty clip",
                          mp, numOfClips, cookie, cookieSize, NULL,
                          _putNiftyClip );
        else {
            int fd = fileno( stderr );

            if ( (fd >= 0) && isatty( fd ) )
                fputs( l == 0x0411
                        ? "�j�t�e�B�N���b�v�ւ� login �Ɏ��s���܂���\n"
                        : "nifty clip: login failed.\n",
                       stderr );
#ifdef  WIN32
            else {
                MessageBox(
                    NULL,
                    l == 0x0411
                        ? "�j�t�e�B�N���b�v�ւ̃��O�C���Ɏ��s���܂����B  "
                        : "nifty clip: login failed.    ",
                    l == 0x0411
                        ? "���O�C�����s"
                        : "Login failure",
                    MB_OK|MB_ICONERROR );
            }
#endif
        }
    }
}


#ifdef  PUT_NIFTY_CLIP_EXE
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
                 "putNC: OPML �� �j�t�e�B�N���b�v �o�^�c�[��\n" );
        fprintf( stderr,
                 "    putNC [-x] -u ID -p �p�X���[�h [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
    "      ID: @nifty ID �܂��� PLEASY ID\n"
    "\t-x: proxy ���g��\n"
    "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putNC: read bookmarks from OPML, and put them into nifty clip\n" );
        fprintf( stderr,
      "    putNC [-x] -u ID -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "      ID: @nifty ID or PLEASY ID\n"
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n" );
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
        /* �u�b�N�}�[�N�� �j�t�e�B�N���b�v �ɓo�^ */
        putNiftyClip( username, password, NULL, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_NIFTY_CLIP_EXE */

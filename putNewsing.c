/*
 * clip loader <<putNewsing>>
 *
 *      OPML �� newsing �o�^�v���O����
 *          written by H.Tsujimura  29 Sep 2006
 *
 * History:
 * $Log: /comm/bookey/putNewsing.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     07/10/12 1:47 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�ɑΉ�
 * 
 * 6     07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 5     07/01/23 19:45 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 4     07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 3     07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 2     06/09/30 0:54 Tsujimura543
 * �^�O�̐��������I��5�ȓ��ɂ��Ă��瓊�e����悤�ɂ���
 * 
 * 1     06/09/29 23:43 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putNewsing.c 1     09/05/14 3:48 tsupo $";
#endif

BOOL
_putNewsing(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    int         status;
    const char  *p;
    char        url[MAX_URLLENGTH * 16];
    BOOL        ret = FALSE;

    errorString[0] = NUL;

    status = 0;

    /* �܂��A���e�p�_�C�A���O�� GET */
    /*  -- �^�C�g�� */
    p = euc2utf( mp->title );
    if ( !p )
        p = sjis2utf( mp->title );
    sprintf( url,
             "http://newsing.jp/add?title=%s&",
             encodeURL(p ? p : mp->title) );

    /*  -- URL */
    sprintf( url + strlen(url),
             "url=%s&",
             encodeURL(mp->url) );

    /*  -- �R�����g */
    p = euc2utf( mp->comment );
    if ( !p )
        p = sjis2utf( mp->comment );
    sprintf( url + strlen(url),
             "description=%s",
             encodeURL(p ? p : mp->comment) );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        const char  *q;

        p = strstr( response, sjis2euc("���̋L�����s�b�N�A�b�v") );
        q = strstr( response, sjis2euc("�R�����g������") );
        if ( p )
            status = 1; // �܂��N�����e���Ă��Ȃ�
        else if ( q )
            status = 2; // ���łɒN�������e���Ă���
        else
            status = 0;
    }

    if ( status ) {
        const char  *q;
        int         len;
        int         cnt;
        char        tags[BUFSIZ];

        memset( request,  0x00, MAX_CONTENT_SIZE );
        strcpy( url, "http://newsing.jp/index.php" );

        /* url */
        sprintf( request,
                 "action_%s=1&"
                 "url=%s&",
                 status == 1 ? "add" : "comment",
                 encodeURL(mp->url) );
        if ( status == 2 ) {
            /* submit */
            sprintf( request + strlen(request),
                     "submit=%s&",
                     "submit" );
        }

        if ( status == 1 ) {
            /* �^�C�g�� */
            p = utf2euc( mp->title );
            if ( !p )
                p = sjis2euc( mp->title );
            sprintf( request + strlen(request),
                     "title=%s&",
                     encodeURL(p ? p : mp->title) );
        }

        /* �]�� */
        sprintf( request + strlen(request),
                 "thumb=%d&",
                 (mp->affirmation == AFF_BAD) ? 0 : 1 );


        /* �^�O (�X�y�[�X��؂�A5�܂�) */
        q   = mp->tags;
        cnt = 0;
        tags[0] = NUL;
        do {
            p = strchr( q, ' ' );
            if ( p ) {
                len = tags[0] ? strlen( tags ) : 0;
                if ( len > 0 ) {
                    strcat( tags, " " );
                    len++;
                }
                strncat( tags, q, p - q );
                tags[len + (p - q)] = NUL;
                q = p + 1;
                cnt++;
            }
            else {
                if ( tags[0] )
                    strcat( tags, " " );
                strcat( tags, q );
                cnt++;
                break;
            }
        } while ( (cnt < 5) && *q );

        p = utf2euc( tags );
        if ( !p )
            p = sjis2euc( tags );
        sprintf( request + strlen(request),
                 "tag=%s&",
                 encodeURL(p ? p : tags) );

        /* �ӌ��E�v�� */
        p = utf2euc( mp->comment );
        if ( !p )
            p = sjis2euc( mp->comment );
        sprintf( request + strlen(request),
                 "%s=%s&",
                 status == 1 ? "description" : "comment",
                 encodeURL(p ? p : mp->comment) );

        if ( status == 1 ) {
            /* submit */
            sprintf( request + strlen(request),
                     "submit=%s",
                     encodeURL(sjis2euc("���̋L�����s�b�N�A�b�v")) );
        }
        else {
            /* fromcommentwindow */
            sprintf( request + strlen(request),
                     "fromcommentwindow=%s",
                     "true" );
        }

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            if ( strstr(response,
                        sjis2euc("�v��E�ӌ��ɂ͑S�p30�����ȏ�("
                                 "���p60�����ȏ�)���͂��ĉ�����")) ) {
                strcpy( errorString,
                        getLanguageCode() == 0x0411
                         ? "�R�����g���Z�����܂�(�S�p30�����ȏ�ɂ��Ă�������)�B"
                         : "Your comment is too short.\r\n"
                           "You should write comment over 60 bytes long!");
                ret = TRUE; /* �o�^���s�����A���̂܂܃��g���C���Ă����s */
                            /* ���邾���Ȃ̂œo�^���������Ƃ���         */
            }
            else if ( strstr( response, mp->url )            ||
                      strstr( response, encodeURL(mp->url) )    )
                ret = TRUE; /* �o�^���� */
        }
    }

    return ( ret );
}

void
putNewsing(
        const char   *userName,
        const char   *password,
        const char   *userName2,  /* (I) �F�ؗp���[�U��(Yahoo! Japan)   */
        const char   *password2,  /* (I) �F�ؗp�p�X���[�h(Yahoo! Japan) */
        AUTH_TYPE    authType,    /* (I) �F�؃^�C�v                     */
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        // Yahoo! Japan ID �� newsing �Ƀ��O�C��
        ret = loginNewsingOnBBAuth(userName2, password2, cookie, &cookieSize);
    }
    else {
        /* newsing �� login */
        ret = loginNewsing( userName, password, cookie );
    }
    if ( ret == 1 )
        putBookmarks( "newsing", mp, numOfClips, cookie, cookieSize, NULL,
                      _putNewsing );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "newsing �ւ� login �Ɏ��s���܂���\n"
                    : "newsing: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "newsing �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "newsing: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_NEWSING_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        AUTH_TYPE *authType,
        BOOL      *useProxy,
        FILE      **fp
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'U':
                    *authType = AK_YAHOOJAPAN_BBAUTH;
                    /* fall into ... */
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
                 "putNewsing: OPML �� newsing �o�^�c�[��\n" );
        fprintf( stderr,
                 "    putNewsing [-x] -u ���[�U�� -p �p�X���[�h\n"
                 "               [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
                 "    putNewsing [-x] -U Yahoo!JapanID -p �p�X���[�h\n"
                 "               [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
    "\t-x: proxy ���g��\n"
    "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n\n"
    "  *����: newsing �́u�R�����g�v��60�o�C�g�ȉ�(�S�p30�����ȉ�)���Ɠo�^\n"
    "         �Ɏ��s���܂��B\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putNewsing: read bookmarks from OPML, and put them into newsing\n" );
        fprintf( stderr,
      "    putNewsing [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "    putNewsing [-x] -U Yahoo!JapanID -p password [-i OPMLfilename]\n");
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n\n"
      "    *Warning* :: If length of 'comment' is less than 60 bytes long,\n"
      "                 registration into newsing will be failed.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int         numOfClips = 0;
    char        username[MAX_USERIDLEN + 1];
    char        password[MAX_PASSWDLEN + 1];
    BOOL        useProxy = FALSE;
    FILE        *fp = stdin;
    MyClip      *mp = NULL;
    AUTH_TYPE   authType = AK_ORIGINAL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &authType, &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� newsing �ɓo�^ */
        putNewsing( username, password,
                    username, password,
                    authType,
                    mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_NEWSING_EXE */

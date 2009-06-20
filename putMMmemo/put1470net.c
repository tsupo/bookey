/*
 * clip loader <<put1470net>>
 *
 *      OPML �� 1470.net���j���[�A���� �o�^�v���O����
 *          written by H.Tsujimura  14 Jul 2006
 *
 * $Log: /comm/bookey/putMMmemo/put1470net.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 18    07/10/05 4:18 Tsujimura543
 * �\�[�X����
 * 
 * 17    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 16    07/07/02 16:35 Tsujimura543
 * 1470.net ���j���[�A���ł̃f�U�C���ύX�ɔ����A�u�b�N�}�[�N�o�^��
 * �����E���s����������C��
 * 
 * 15    07/01/23 21:35 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 14    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 13    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 12    06/12/22 18:37 Tsujimura543
 * getEvaluation() �𓱓��Btitle �� MM/Memo �`���ł���΁A���K�����Ă���
 * �o�^����悤�ɂ��Ă݂�
 * 
 * 11    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 10    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 9a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 9     06/08/22 17:48 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 8     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 7     06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 6     06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 5     06/07/18 21:04 Tsujimura543
 * ���O�C�����s���ɃG���[�_�C�A���O���o���悤�ɂ���
 * 
 * 4     06/07/18 20:47 Tsujimura543
 * &raquo: �֘A�̏������C��(�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����R�[�h�̌���
 * ��)
 * 
 * 3     06/07/18 13:59 Tsujimura543
 * OPML�t�@�C������̕]��(���[�g)�A�O���[�v�̎�荞�݂ɑΉ�
 * 
 * 2     06/07/18 11:43 Tsujimura543
 * MONO �̓o�^�ɑΉ�����
 * 
 * 1     06/07/15 0:55 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putMMmemo/put1470net.c 1     09/05/14 3:48 tsupo $";
#endif

BOOL
_put1470net(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    char        url[1024];
    char        webpageID[16];
    char        asin[16];
    const char  *p;
    char        *q;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    memset( request, 0x00, MAX_CONTENT_SIZE );

    // �����o�^�E�X�V�t�H�[���� GET
    strcpy( url, "http://1470.net/tools/memo/new" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        char    csrf[64];

        // _csrf ���擾
        p = strstr( response, "name=\"_csrf\" value=\"" );
        if ( p ) {
            p += 20;
            q = strstr( p, "\" />" );
            if ( q ) {
                char    tmpTitle[2048];
                char    groupStr[8];
                long    rate = 0;

                strncpy( csrf, p, q - p );
                csrf[q - p] = NUL;

                groupStr[0] = NUL;
                p = sjis2utf(mp->title);
                strcpy( tmpTitle, p ? p : mp->title );

                // MM/Memo �`���� title ���������߂̏���
                rate = getEvaluation( tmpTitle, UTF8 );
                q = tmpTitle;
                if ( rate == 0 )
                    if ( (mp->evaluation >= EVL_ONE)  &&
                         (mp->evaluation <= EVL_FIVE)    )
                        rate = mp->evaluation;

                sprintf( request,
                         "_csrf=%s&"
                         "title=%s&",
                         csrf, 
                         encodeURLex2( q ) );

                if ( (rate >= EVL_ONE) && (rate <= EVL_FIVE) )
                    sprintf( request + strlen(request),
                             "eval=%d&",
                             rate );
                else
                    strcat( request, "eval=&" );

                if ( groupStr[0] )
                    sprintf( request + strlen(request),
                             "group=%s&",
                             encodeURL( groupStr ) );
                else
                    strcat( request, "group=&" );

                p = sjis2utf(mp->tags);
                sprintf( request + strlen(request),
                         "tag=%s&",
                         encodeURL( p ? p : mp->tags ) );

                p = sjis2utf(mp->comment);
                sprintf( request + strlen(request),
                         "comment=%s&",
                         encodeURL( p ? p : mp->comment ) );

                sprintf( request + strlen(request),
                         "todoName=&"
                         "todoDate=&"
                         "newUri=%s&",
                         encodeURL( mp->url) );

                getASIN( mp->url, asin );
                if ( asin[0] )
                    sprintf( request + strlen(request),
                             "asins[]=%s&",
                             asin );
                strcat( request, "newAsin=&" );

                sprintf( request + strlen(request),
                         "searchDate_year=%d"
                         "searchDate_month=%d"
                         "searchDate_day=%d"
                         "locationQuery=&"
                         "_save=%s",
                         mp->yyyy,
                         mp->mm,
                         mp->dd,
                         encodeURL( sjis2utf("�ۑ�����") ) );

                // �����𓊍e
                setUpReceiveBuffer( response, sz );
                http_postEx( url, "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response ) {
                    if ( (p = strstr( response, "resId=" )) != NULL ) {
                        q = strstr( p, sjis2utf("\">�ԐM</a>") );
                        if ( !q )
                            q = strstr( p, sjis2utf("\">res</a>") );
                        if ( q ) {
                            strncpy( webpageID, p, q - p );
                            webpageID[q - p] = NUL;
                            ret = TRUE; // ���e����
                        }
                    }
                }
            }
        }
    }

    return ( ret );
}

void
put1470net(
        const char   *userName,  /* (I) �F�ؗp���[�U��         */
        const char   *password,  /* (I) �F�ؗp�p�X���[�h       */
        const char   *userName2, /* (I) �F�ؗp���[�U��(�\��)   */
        const char   *password2, /* (I) �F�ؗp�p�X���[�h(�\��) */
        AUTH_TYPE    authType,   /* (I) �F�؃^�C�v             */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���       */
        int          numOfClips  /* (I) �u�b�N�}�[�N��         */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    userID[32];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    memset( userID, 0x00, 32 );

    /* 1470.net �Ƀ��O�C�� */
    ret = login1470net( userName, password, userName2, password2, authType,
                        cookie, userID );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( "1470.net", mp, numOfClips,
                      cookie, cookieSize, NULL,
                      _put1470net );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "1470.net �ւ� login �Ɏ��s���܂���\n"
                    : "1470.net: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "1470.net�ւ̃��O�C���Ɏ��s���܂����B  "
                         : "1470.net: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_1470NET_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        char      *username2,
        char      *password2,
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

                case 'U':
                    if ( argv[i][j + 1] ) {
                        strcpy( username2, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username2, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'P':
                    if ( argv[i][j + 1] ) {
                        strcpy( password2, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password2, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'a':
                    switch ( argv[i][j + 1] ) {
                    case 't':
                        *authType = AK_TYPEKEY;
                        if ( argv[i][j + 2] == 'h' ) {
                            *authType = AK_TYPEKEY_HATENA;
                            j++;
                        }
                        break;
                    case 'h':
                        *authType = AK_HATENA;
                        if ( argv[i][j + 2] == 't' ) {
                            *authType = AK_HATENA_TYPEKEY;
                            j++;
                        }
                        break;
                    case 'T':
                        *authType = AK_TYPEKEY_HATENA;
                        break;
                    case 'H':
                        *authType = AK_HATENA_TYPEKEY;
                        break;
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
             "put1470net: OPML �� 1470.net ���j���[�A���� �o�^�c�[��\n" );
        fprintf( stderr,
             "    put1470net [-x] -u TypeKey���[�U�� -p TypeKey�p�X���[�h\n");
        fprintf( stderr,
             "    put1470net [-x] -U �͂Ă�ID -P �͂Ăȃp�X���[�h\n" );
        fprintf( stderr,
       "    put1470net [-x] -a{T|H} -u TypeKey���[�U�� -p TypeKey�p�X���[�h\n"
       "               -U �͂Ă�ID -P �͂Ăȃp�X���[�h\n" );
        fprintf( stderr,
       "\t-x: proxy ���g��\n"
       "\t-aT: �܂� TypeKey �F�؂ł̃A�N�Z�X�������A���s�����ꍇ�͂͂Ă�"
       "�F�؂ł̃A�N�Z�X�����݂�\n"
       "\t-aH: �܂��͂ĂȔF�؂ł̃A�N�Z�X�������A���s�����ꍇ�� TypeKey "
       "�F�؂ł̃A�N�Z�X�����݂�\n"
       "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
        "put1470net: read bookmarks from OPML, and put them into 1470.net\n");
        fprintf( stderr,
             "    put1470net [-x] -u TypekeyID -p TypeKeyPassword\n" );
        fprintf( stderr,
             "    put1470net [-x] -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "    put1470net [-x] -a{T|H} -u TypekeyID -p TypeKeyPassword\n"
             "               -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "      TypekeyID: ID for TypeKey authentication\n"
             "      TypeKeyPassword: password for TypeKey authentication\n" );
        fprintf( stderr,
             "      hatenaID: ID for Hatena authentication\n"
             "      hatenaPassword: password for Hatena authentication\n" );
        fprintf( stderr,
         "\t-x: use http access via proxy server\n"
         "\t-aT: Use 'TypeKey' authentication first. If 'TypeKey' failure,"
         "\n\t\tthen try 'Hatena' authentication.\n"
         "\t-aH: Use 'Hatena' authentication first. If 'Hatena' falure,\n"
         "\t\tthen try 'TypeKey' authentication.\n"
         "\t-i: If this option is not specified, read from standard input\n"
         "\t    instead of OPML\n\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int         numOfClips = 0;
    char        username[MAX_USERIDLEN + 1];
    char        password[MAX_PASSWDLEN + 1];
    char        username2[MAX_USERIDLEN];
    char        password2[MAX_PASSWDLEN];
    AUTH_TYPE   authType = AK_TYPEKEY; /* default */
    BOOL        useProxy = FALSE;
    FILE        *fp = stdin;
    MyClip      *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username,  0x00, MAX_USERIDLEN );
    memset( password,  0x00, MAX_PASSWDLEN );
    memset( username2, 0x00, MAX_USERIDLEN );
    memset( password2, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username,  password,
                  username2, password2,
                  &authType, &useProxy,
                  &fp );

    if ( username[0]  && password[0]  &&
         username2[0] && password2[0]    ) {
        if ( (authType != AK_TYPEKEY_HATENA) &&
             (authType != AK_HATENA_TYPEKEY)    )
            authType = AK_TYPEKEY_HATENA;
    }
    else if ( username[0] && password[0] )
        authType = AK_TYPEKEY;
    else if ( username2[0] && password2[0] )
        authType = AK_HATENA;
    else
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� 1470.net �ɓo�^ */
        put1470net( username,  password,
                    username2, password2,
                    authType,
                    mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_1470NET_EXE */

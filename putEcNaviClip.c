/*
 * clip loader <<putEcNaviClip>>
 *
 *      OPML �� Buzzurl �o�^�v���O����
 *          written by H.Tsujimura  29 Jun 2006 / 11 Jan 2007
 *
 * History:
 * $Log: /comm/bookey/putEcNaviClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 24    07/10/10 1:51 Tsujimura543
 * BBAuth �o�R�ł̃u�b�N�}�[�N���e���ɃL�[���[�h(�^�O)���ݒ肳��Ȃ�
 * �s����C��
 * 
 * 23    07/10/05 4:19 Tsujimura543
 * putBuzzurl() ���� putBuzzurlOnBBAuth() �𕪗�
 * 
 * 22    07/10/05 3:50 Tsujimura543
 * BBAuth �o�R�ł̃��O�C���ɂ��u�b�N�}�[�N�̓o�^���������邱�Ƃ��m�F
 * 
 * 21    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 20    07/09/14 23:21 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�Ή� (�܂��r��)
 * 
 * 19    07/03/28 20:28 Tsujimura543
 * �^�O�Ƀ}���`�o�C�g�������܂܂��ꍇ�A���e��̃^�O���ŏ���1������
 * �Ȃ��Ă��܂��s����C�� (���eAPI�Ή����ɃG���o�O)
 * 
 * 18    07/03/20 0:15 Tsujimura543
 * �����Őݒ肵���^�C�g�����g���ꍇ�́Alogin ����K�v���Ȃ��Ȃ���
 * 
 * 17    07/03/16 23:55 Tsujimura543
 * �s�v�ɂȂ����R�[�h���폜
 * 
 * 16    07/03/16 23:17 Tsujimura543
 * Buzzurl �̓��e�pAPI���g�p���Ă݂�ł�����B���Ȃ��g���邱�Ƃ��m�F
 * 
 * 15    07/02/16 16:17 Tsujimura543
 * ���łɓo�^����Ă���^�C�g���Ɠo�^���悤�Ƃ��Ă���^�C�g�����H���Ⴄ��
 * ���́A�o�^���悤�Ƃ��Ă���^�C�g���ŏ㏑�����邩�A���łɓo�^����Ă���
 * �^�C�g�������̂܂ܗ��p���邩�A�I���ł���悤�ɂ���
 * 
 * 14    07/01/23 20:40 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 13    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 12    07/01/19 19:49 Tsujimura543
 * (���j���[�A���ȍ~)�^�O���o�^����Ȃ��s����C��
 * 
 * 11    07/01/18 22:46 Tsujimura543
 * (1) putEcNavi.c �� putNiftyClip.c �̂��ꂼ��ɔz�u���Ă����� getValue()
 *    �𕪗��A�Ɨ������� (getValue.c �ֈړ�)
 * (2) putBookmarks() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 10    07/01/11 16:02 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 9     06/11/14 15:48 Tsujimura543
 * �s�v�ɂȂ����R�[�h���폜
 * 
 * 8     06/10/10 16:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�� Web�y�[�W�� charSet �� EUC-JP ���� UTF-8 ��
 * �ύX���ꂽ�̂ɔ����C�������{
 * 
 * 7     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 6a    06/09/03 20:19 tsupo
 * cookie �܂����C��
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
 * 3     06/07/12 15:51 Tsujimura543
 * 64 �� MAX_KEYLENGTH �ɒu��
 * 
 * 2     06/06/29 21:29 Tsujimura543
 * �u�b�N�}�[�N���e���� request �����񂩂�]���ȕ���������
 * 
 * 1     06/06/29 18:42 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putEcNaviClip.c 1     09/05/14 3:48 tsupo $";
#endif

/*
 * Buzzurl�ւ̓��eAPI�d�l
 * �E���N�G�X�gURI
 *     https://buzzurl.jp/posts/add/v1
 * 
 * �E�����G���R�[�h
 *     UTF-8�̂�
 * 
 * �E�F�ؕ��@
 *     https+BasicAuth�ł��B
 *     (http�ł����p�\�ł����Ȃ�ׂ�https�̗��p�����肢���܂�)
 *     Buzzurl�ւ̃��O�C�����[���A�h���X�ƃp�X���[�h�𗘗p���܂�
 * 
 * �Emethod
 *     post�̂�
 * 
 * �E���N�G�X�g�p�����[�^
 *     �Eurl
 *         �u�b�N�}�[�N����URL(�K�{)
 *     �Etitle
 *         �L���̃^�C�g��(�C��)
 *     �Ecomment
 *         �L���ւ̃R�����g(�C��)
 *     �Ekeyword
 *         �L�[���[�h(�C�ӁB8�܂Ŏw��\)
 *     �Ecb
 *         JSONP�p��callback���w��(�C��)
 * 
 * ���X�|���X
 *     �Estatus
 *         �u�b�N�}�[�N�����̉ہB������ "success", ���s�� "fail"��Ԃ��܂��B
 *     �Ereason
 *         ���s���̂ݎ��s���R��Ԃ��܂��B
 *             �E�F�؎��s�F"401 authentication required."
 *             �Epost�ȊO��method�F"invalid_method"
 *             �Eurl���ݒ�F"need_url"
 *             �E�s����URL��ݒ�F"invalid_url"
 *             �Eurl��255byte�ȏ�̏ꍇ�F"too_long_url"
 *             �E�^�C�g���̎����擾���o���Ȃ�����title���ݒ莞�F"need_title"
 *             �EBuzzurl����DB�ŉ��炩�̃G���[�������F"db_error"
 *         �E�T���v�����X�|���X
 *             �E������
 *                 {"status":"success"}
 *             �E���s��
 *                 {"status":"fail","reason":"invalid_method"}
 */

typedef struct param_putBuzzurl {
    char        *username;  /* ���[�U��                       */
    char        *password;  /* �p�X���[�h                     */
    AUTH_TYPE   authType;   /* �F�؃^�C�v                     */
    BOOL        useMyTitle; /* �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
}   PARAM_PBZRL;


BOOL
putBuzzurlOnBBAuth(
        const MyClip *mp,
        const char   *title,
        PARAM_PBM    *args
    )
{
    BOOL        ret       = FALSE;
    char        *request  = args->request;
    char        *response = args->response;
    char        *cookie   = args->cookie;
    size_t      sz        = args->sz;
    char        url[MAX_URLLENGTH];
    const char  *p, *q;

    // ���e�y�[�W�� GET
    sprintf( url, "http://buzzurl.jp/config/add/confirm?url=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    if ( *response ) {
        char    thumbprint[MAX_KEYLENGTH];
        char    user_num[MAX_NAMELEN];
        char    already_exists[MAX_NAMELEN];
        char    default_title[MAX_DESCRIPTION_LEN];

        // thumbprint
        thumbprint[0] = NUL;
        p = strstr( response, "name=\"thumbprint\" value=\"" );
        if ( p ) {
            p += 25;
            q = strchr( p, '"' );
            strncpy( thumbprint, p, q - p );
            thumbprint[q - p] = NUL;
        }

        // user_num
        user_num[0] = NUL;
        p = strstr( response, "name=\"user_num\" value=\"" );
        if ( p ) {
            p += 23;
            q = strchr( p, '"' );
            strncpy( user_num, p, q - p );
            user_num[q - p] = NUL;
        }

        // already_exists
        already_exists[0] = NUL;
        p = strstr( response, "name=\"already_exists\" value=\"" );
        if ( p ) {
            p += 29;
            q = strchr( p, '"' );
            strncpy( already_exists, p, q - p );
            already_exists[q - p] = NUL;
        }

        // title
        default_title[0] = NUL;
        p = strstr( response, "name=\"title\" value=\"" );
        if ( p ) {
            p += 20;
            q = strchr( p, '"' );
            strncpy( default_title, p, q - p );
            default_title[q - p] = NUL;
        }

        // request ��g�ݗ��Ă�
        //  -- thumbprint
        if ( thumbprint[0] )
            sprintf( request,
                     "thumbprint=%s&",
                     thumbprint );
        else
            strcpy( request, "thumbprint=&" );

        //  -- URL
        sprintf( request + strlen(request),
                 "url=%s&",
                 encodeURL( mp->url ) );

        // -- user_num
        if ( user_num[0] )
            sprintf( request + strlen(request),
                     "user_num=%s&",
                     user_num );
        else
            strcat( request, "user_num=&" );

        //  -- already_exists
        if ( already_exists[0] )
            sprintf( request + strlen(request),
                     "already_exists=%s&",
                     already_exists );
        else
            strcat( request, "already_exists=&" );

        //  -- �^�C�g��
        if ( title[0] ) {
            p = any2utf( title );
            sprintf( request + strlen(request),
                     "title=%s&", encodeURL(p) );
        }
        else if ( default_title[0] ) {
            sprintf( request + strlen(request),
                     "title=%s&", encodeURL(default_title) );
        }
        else
            strcat( request, "title=&" );

        //  -- �R�����g
        if ( mp->comment[0] ) {
            p = any2utf( mp->comment );
            sprintf( request + strlen(request),
                     "comment=%s&", encodeURL(p) );
        }

        // �L�[���[�h(�^�O)�͍ő�8�܂�
        if ( mp->tags[0] ) {
            int     i;
            char    tag[80];
            char    *r;
            char    *temp = NULL;
            BOOL    done  = FALSE;

            p = any2utf( mp->tags );
            if ( p ) {
                temp = (char *)malloc( strlen( p ) + 1 );
                if ( temp ) {
                    strcpy( temp, p );
                    p = temp;
                }
            }
            q = p ? p : mp->tags;
            i = 0;
            do {
                p = strchr( q, ' ' );
                if ( p ) {
                    strncpy( tag, q, p - q );
                    tag[p - q] = NUL;
                    q = p + 1;
                }
                else {
                    strcpy( tag, q );
                    done = TRUE;
                }
                i++;

                r = any2utf( tag );
                sprintf( request + strlen(request),
                         "keyword=%s&",
                         encodeURL( r ) );
            } while ( (done == FALSE) && (i < 8) && *q );

            if ( temp )
                free( temp );
        }

        sprintf( request + strlen(request),
                 "submit=%s",
                 encodeURL(sjis2utf(" �u�b�N�}�[�N���� ")) );
    }

    setUpReceiveBuffer( response, sz );
    http_postEx( "http://buzzurl.jp//config/add/execute",
                 "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, mp->url ) )
            ret = TRUE;
    }

    return ( ret );
}

BOOL
putBuzzurl(
        const MyClip *mp,
        const char   *peseudoTitle,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    BOOL        ret       = FALSE;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_PBZRL *param    = (PARAM_PBZRL *)args->args;
    char        title[MAX_DESCRIPTION_LEN];
    const char  *p, *q;

    if ( peseudoTitle && *peseudoTitle )
        strcpy( title, peseudoTitle );
    else
        strcpy( title, mp->title );

    if ( param->authType == AK_YAHOOJAPAN_BBAUTH ) {
        // BBAuth �o�R�ł̃A�N�Z�X�̏ꍇ�� API ���g���Ȃ�
        return ( putBuzzurlOnBBAuth( mp, title, args ) );
    }

    // API �ɂ��u�b�N�}�[�N�o�^���s
    //  -- URL
    if ( strlen( mp->url ) >= 256 ) {
        strcpy( errorString, "URL ���������܂�" );
        return ( ret );
    }
    sprintf( request,
             "url=%s&",
             encodeURL( mp->url ) );

    //  -- �^�C�g��
    if ( title[0] ) {
        p = any2utf( title );
        sprintf( request + strlen(request),
                 "title=%s&", encodeURL(p) );
    }

    //  -- �R�����g
    if ( mp->comment[0] ) {
        p = any2utf( mp->comment );
        sprintf( request + strlen(request),
                 "comment=%s&", encodeURL(p) );
    }

    //  -- �L�[���[�h(�^�O)�͍ő�8�܂�
    if ( mp->tags[0] ) {
        int     i;
        char    tag[80];
        char    *r;
        char    *temp = NULL;
        BOOL    done  = FALSE;

        p = any2utf( mp->tags );
        if ( p ) {
            temp = (char *)malloc( strlen( p ) + 1 );
            if ( temp ) {
                strcpy( temp, p );
                p = temp;
            }
        }
        q = p ? p : mp->tags;
        i = 0;
        do {
            p = strchr( q, ' ' );
            if ( p ) {
                strncpy( tag, q, p - q );
                tag[p - q] = NUL;
                q = p + 1;
            }
            else {
                strcpy( tag, q );
                done = TRUE;
            }
            i++;

            r = any2utf( tag );
            sprintf( request + strlen(request),
                     "keyword=%s&",
                     encodeURL( r ) );
        } while ( (done == FALSE) && (i < 8) && *q );

        if ( temp )
            free( temp );
    }

    sprintf( request + strlen(request),
             "cb=%s", "checkResult" );

    setUpReceiveBuffer( response, sz );
    http_postBASIC( "https://buzzurl.jp/posts/add/v1",
                    param->username, param->password,
                    "application/x-www-form-urlencoded",
                    request, response );
    if ( *response ) {
        if ( strstr( response, "\"success\"" ) )
            ret = TRUE;
        else {
            p = strstr( response, "\"reason\"" );
            if ( p ) {
                p += 9;
                q = strchr( p, '"' );
                if ( q ){
                    q++;
                    p = strchr( q, '"' );
                    if ( p ) {
                        strncpy( errorString, q, p - q );
                        errorString[p - q] = NUL;

                        if ( strstr( errorString, "authentication" ) )
                            strcpy( errorString,
                                    "���[�U���܂��̓p�X���[�h���Ⴂ�܂�" );
                        else if ( !strcmp( errorString, "db_error" ) )
                            strcpy( errorString,
                                    "Buzzurl �̃f�[�^�x�[�X�ŉ��炩�̃G���["
                                    "���������܂���" );
                    }
                }
            }
        }
    }

    return ( ret );
}

BOOL
_putEcNaviClip(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie    = args->cookie;
    char    *response  = args->response;
    size_t  sz         = args->sz;
    BOOL    useMyTitle = ((PARAM_PBZRL *)(args->args))->useMyTitle;
    char    *p, *q;
    char    url[MAX_URLLENGTH * 4];
    char    title[MAX_DESCRIPTION_LEN];

    strcpy( title, mp->title );
    if ( useMyTitle == FALSE ) {
        /* ���łɒN���ɂ���ēo�^�ς݂̃^�C�g��(�����݂����)���̗p */
        sprintf( url, "http://buzzurl.jp/entry/%s",
                 encodeURLforHatena(mp->url) );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( *response ) {
            p = strstr( response, "<h2><a href=\"" );
            if ( p ) {
                /* ���łɒN���ɂ���ēo�^�ς݂̃^�C�g�������݂���ꍇ */
                p += 13;
                q = strstr( p, "\">" );
                if ( q ) {
                    p = q + 2;
                    q = strstr( p, "</a>" );
                    if ( q ) {
                        strncpy( title, p, q - p );
                        title[q - p] = NUL;
                    }
                }
            }
        }
    }

    return ( putBuzzurl( mp, title, errorString, args ) );
}

void
putEcNaviClip(
        const char   *userName,  /* (I) ���[�U��                       */
        const char   *password,  /* (I) �p�X���[�h                     */
        const char   *username2,
        const char   *password2,
        AUTH_TYPE    authType,
        BOOL         useMyTitle, /* (I) �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    )
{
    char        cookie[MAX_COOKIE_LEN + 1];
    size_t      cookieSize = MAX_COOKIE_LEN;
    PARAM_PBZRL param;
    int         ret = 0;

    memset( cookie, 0x00, MAX_COOKIE_LEN );

    param.username   = (char *)userName;
    param.password   = (char *)password;
    param.authType   = authType;
    param.useMyTitle = useMyTitle;

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        // Yahoo! Japan ID �� Buzzurl �Ƀ��O�C��
        param.username = (char *)username2;
        param.password = (char *)password2;
        ret = loginEcNaviOnBBAuth(username2, password2, cookie, &cookieSize);
    }
    else if ( useMyTitle == FALSE ) {
        // Buzzurl �Ƀ��O�C��
        ret = loginEcNavi( userName, password, cookie );
    }
    else {
        ret = 1;    // useMyTitle �� TRUE �̂Ƃ��́Alogin �s�v�ɂȂ���
                    // (���e�pAPI���s����BASIC�F�؂���)
    }
    if ( ret == 1 ) /* login ���� */
        putBookmarks( "Buzzurl", mp, numOfClips, cookie, cookieSize,
                      (void *)&param,
                      _putEcNaviClip );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Buzzurl �ւ� login �Ɏ��s���܂���\n"
                    : "Buzzurl: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Buzzurl �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "Buzzurl: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_BUZZURL_EXE
#define BUFFER_SIZE_FOR_GETTITLE    2048

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
encodeURLforHatena( const char *url )
{
    Thread  static char url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *p;
    char                *q;

    strcpy( url2, url );
    while ( (p = strchr( url2, '#' )) != NULL ) {
        q = &url2[strlen(url2)];
        while ( q >= p + 1 ) {
            *(q + 2) = *q;
            q--;
        }
        *p++ = '%';
        *p++ = '2';
        *p   = '3';
    }

    return ( url2 );
}

void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        AUTH_TYPE *authType,
        BOOL      *useMyTitle,
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
        fprintf( stderr,
                 "putBuzzurl: OPML �� Buzzurl �o�^�c�[��\n" );
        fprintf( stderr,
 "    putBuzzurl [-x] [-F] -u ���[���A�h���X -p �p�X���[�h [-i OPML�t�@�C��"
 "��]\n");
        fprintf( stderr,
 "    putBuzzurl [-x] [-F] -U Yahoo!JapanID -p �p�X���[�h [-i OPML�t�@�C��"
 "��]\n");
        fprintf( stderr,
 "\t-x: proxy ���g��\n"
 "\t-F: ���łɓo�^����Ă���^�C�g���Ɠo�^���悤�Ƃ��Ă���^�C�g��\n"
 "\t    ���H���Ⴄ�ꍇ�́A�o�^���悤�Ƃ��Ă���^�C�g���ŏ㏑������\n"
 "\t    (Buzzurl �ł́A�^�C�g���͑S���ŋ��L���Ă��܂��B�㏑�����邩\n"
 "\t     �ǂ����͐T�d�ɔ��f���Č��߂Ă�������)\n"
 "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putBuzzurl: read bookmarks from OPML, and put them into Buzzurl\n" );
        fprintf( stderr,
      "    putBuzzurl [-x] [-F] -u mailaddress -p password [-i OPMLfilename]"
      "\n" );
        fprintf( stderr,
      "    putBuzzurl [-x] [-F] -U Yahoo!JapanID -p password [-i OPMLfilename]"
      "\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-F: overwrite entry title, if original title was different from\n"
      "\t    your specified title\n"
      "\t    (Caution: entry title is shared by all users of Buzzurl)\n"
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
    BOOL        useProxy   = FALSE;
    BOOL        useMyTitle = FALSE;
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
                  &authType, &useMyTitle, &useProxy,
                  &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� Buzzurl �ɓo�^ */
        putEcNaviClip( username, password,
                       username, password,
                       authType,
                       useMyTitle, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_BUZZURL_EXE */

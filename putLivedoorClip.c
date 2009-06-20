/*
 * clip loader <<putLivedoorClip>>
 *
 *      OPML �� livedoor�N���b�v �o�^�v���O����
 *          written by H.Tsujimura  28 Jun 2006
 *
 * History:
 * $Log: /comm/bookey/putLivedoorClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 28    08/12/02 19:38 Tsujimura543
 * �t�H�[�}�b�g�X�g�����O�Ǝ㐫�֘A�̃o�O�C��
 * 
 * 27    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 26    07/02/05 20:04 Tsujimura543
 * editLivedoorClip() ��ǉ��B���łɓo�^�ς݂�Web�y�[�W���㏑���o�^�ł���
 * �悤�ɂ���
 * 
 * 25    07/01/23 20:05 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 24    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 23    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 22    06/12/22 18:39 Tsujimura543
 * �o�^���悤�Ƃ��Ă���u�b�N�}�[�N�ɐݒ肳���u�]���v���A�����΂�ŏ���
 * �u�b�N�}�[�N�́u�]���v�ɂȂ��Ă��܂��s��ɑΏ�
 * ([��] mp->evaluation �� [��] mp[i].evaluation)
 * 
 * 21    06/12/06 19:02 Tsujimura543
 * �ur18�t���O�v�͖����I�� 0 ���w�肷��悤�ɂ���
 * 
 * 20    06/12/06 18:58 Tsujimura543
 * �u���J��ԁv���w�肵�Ă̓o�^���ł���悤�ɂ��Ă݂�
 * 
 * 19    06/11/17 19:38 Tsujimura543
 * getEvaluation() �𓱓��Btitle �� MM/Memo �`���ł���΁A���K�����Ă���
 * �o�^����悤�ɂ��Ă݂�
 * 
 * 18    06/11/14 15:47 Tsujimura543
 * any2utf() �̎��̂� myClip.c �ֈړ�
 * 
 * 17    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 16    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 15a   06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 15    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 14    06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 13    06/07/18 21:04 Tsujimura543
 * ���O�C�����s���ɃG���[�_�C�A���O���o���悤�ɂ���
 * 
 * 12    06/07/18 20:47 Tsujimura543
 * &raquo: �֘A�̏������C��(�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����R�[�h�̌���
 * ��)
 * 
 * 11    06/07/12 15:51 Tsujimura543
 * 64 �� MAX_KEYLENGTH �ɒu��
 * 
 * 10    06/07/11 19:43 Tsujimura543
 * �o�^���悤�Ƃ��Ă���y�[�W�����łɓo�^�ς݂̏ꍇ�́A���̎|�\������
 * �悤�ɂ���
 * 
 * 9     06/07/07 13:38 Tsujimura543
 * �u�]���v�̐ݒ�ɑΉ� (MM/Memo ����擾�����]���t���u�b�N�}�[�N�̓o�^
 * ���������{���A����m�F���s�Ȃ���)
 * 
 * 8     06/06/29 11:46 Tsujimura543
 * any2utf() �ɃR�����g(����)��ǉ�
 * 
 * 7     06/06/29 11:39 Tsujimura543
 * charset �� ISO-2022-JP �ȃy�[�W�̃N���b�v�ɂ��Ή�����
 * 
 * 6     06/06/29 11:33 Tsujimura543
 * ���ۂɓ��e����O�ɁA��M�o�b�t�@���N���A���鏈���������Ă����̂ŁA�ǉ�
 * 
 * 5     06/06/29 11:29 Tsujimura543
 * �����������t�@�N�^�����O
 * 
 * 4     06/06/29 11:25 Tsujimura543
 * �^�C�g���ƃR�����g�̃G���R�[�h������ encodeURL() ���� encodeURLex() ��
 * �ύX
 * 
 * 3     06/06/29 1:07 Tsujimura543
 * OPML�t�@�C��(charset=UTF-8)����ǂݍ��񂾓��e��o�^����Ƃ��A����������
 * �������邱�Ƃ�����s��ɑΏ�
 * 
 * 2     06/06/29 0:43 Tsujimura543
 * ���e���s���̏����o�H�𐮗�
 * 
 * 1     06/06/29 0:40 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putLivedoorClip.c 1     09/05/14 3:48 tsupo $";
#endif


void
getHashWithPostkey(
        const char *username,
        const char *targetURL,
        char       *postkey,
        char       *hash,
        char       *cookie
    )
{
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response )
        return;

    sprintf( url, "http://clip.livedoor.com/clips/%s", username );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        char    *p, *q;
        char    clipURL[4096];

        // postkey
        p = strstr( response, "=\"postkey\" value=\"" );
        if ( p ) {
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( postkey, p, q - p );
                postkey[q - p] = NUL;
            }
        }

        // hash
        p = response;
        do {
            hash[0] = NUL;

            q = strstr( p, "<li class=\"clip\" " );
            if ( !q )
                break;
            p = q + 17;

            q = strstr( p, "<a id=\"hash_" );
            if ( !q )
                break;
            p = q + 12;

            q = strstr( p, "\" name=\"p_" );
            if ( !q )
                break;
            p = q + 10;

            q = strchr( p, '"' );
            if ( !q )
                break;
            strncpy( hash, p, q - p );
            hash[q - p] = NUL;

            // url
            p = q + 1;
            q = strstr( p, "<a href=\"" );
            if ( !q ) {
                hash[0] = NUL;
                break;
            }

            p = q + 9;
            q = strchr( p, '"' );
            if ( !q ) {
                hash[0] = NUL;
                break;
            }

            while ( isWhiteSpace(*p) )
                p++;
            while ( (q > p) && isWhiteSpace(*(q - 1)) )
                q--;
            strncpy( clipURL, p, q - p );
            clipURL[q - p] = NUL;
            while ( ( p = strstr( clipURL, "&amp;" ) ) != NULL )
                strcpy( p + 1, p + 5 );
            if ( !strcmp( clipURL, targetURL ) )
                break;  // hash �m��

            p = q + 1;
        } while ( *p );
    }

    free( response );
}

void
setRateOnLivedoorClip(
        const char *username,
        const char *targetURL,
        int        rate,
        char       *cookie
    )
{
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    hash[MAX_KEYLENGTH];
    char    postkey[MAX_KEYLENGTH];
    size_t  sz;

    hash[0]    = NUL;
    postkey[0] = NUL;
    getHashWithPostkey( username, targetURL, postkey, hash, cookie );
    if ( (hash[0] == NUL) || (postkey[0] == NUL) )
        return;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        free( cookie );
        return;
    }

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return;
    }

    strcpy( url, "http://clip.livedoor.com/clip/set_rate" );
    sprintf( request, "hash=%s&rate=%d&postkey=%s", hash, rate, postkey );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    free( response );
    free( request );
}


BOOL
editLivedoorClip(
        const MyClip *mp,
        long         rate,
        const char   *postkey,
        char         *cookie,
        char         *errorString
    )
{
    BOOL    ret = FALSE;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    char    *p;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    orig_title[MAX_DESCRIPTION_LEN];

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        free( cookie );
        return ( ret );
    }

    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return ( ret );
    }

    orig_title[0] = NUL;
    sprintf( url, "http://clip.livedoor.com/clip/edit?link=%s",
             encodeURL(mp->url) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "name=\"title\"" );
        if ( p ) {
            p += 12;
            p = strstr( p, "value=\"" );
            if ( p ) {
                char    *q;

                p += 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( orig_title, p, q - p );
                    orig_title[q - p] = NUL;
                }
            }
        }
    }
    if ( orig_title[0] == NUL ) {
        p = any2utf( mp->title );
        strcpy( orig_title, p ? p : mp->title );
    }

    strcpy( url, "http://clip.livedoor.com/clip/edit" );
    sprintf( request,
             "postkey=%s&"
             "title=%s&",
             postkey,
             encodeURLex2(orig_title) );
    sprintf( request + strlen(request),
             "link=%s&"
             "jump=myclip&",
             encodeURL(mp->url) );

    p = any2utf(mp->title);
    sprintf( request + strlen(request),
             "my_title=%s&"
             "rate=%d&",
             encodeURLex2( p ? p : mp->title ),
             rate );

    p = any2utf(mp->tags);
    sprintf( request + strlen(request),
             "tags=%s&",
             encodeURL( p ? p : mp->tags ) );

    p = any2utf(mp->comment);
    sprintf( request + strlen(request),
             "notes=%s&"
             "public=%s&",
             encodeURLex( p ? p : mp->comment ),
             mp->publication == PUB_PRIVATE ? "off" : "on" );

    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL(sjis2utf("�N���b�v�I")) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        ret = TRUE;
        errorString[0] = NUL;
    }

    free( response );
    free( request );

    return ( ret );
}


typedef struct paramPutLC   {
    const char  *userName;
}   PARAM_LC;

BOOL
_putLivedoorClip(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_LC    *param = (PARAM_LC *)(args->args);
    char        url[MAX_URLLENGTH * 4];
    char        *p, *q;
    char        postkey[MAX_KEYLENGTH];
    char        tmpTitle[2048];
    long        rate;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    rate = 0;

    /* postkey ���擾 */
    p = encodeURL( mp->url );
    sprintf( url,
             "http://clip.livedoor.com/clip/add?link=%s",
             p );
    sprintf( url + strlen(url),
             "&jump=%s",
             p );
    sprintf( url + strlen(url),
             "&title=%s",
             encodeURL( mp->title ) );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response,
                 "<input type=\"hidden\" name=\"postkey\" value=\"" );
        if ( p ) {
            p += 43;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( postkey, p, q - p );
                postkey[q - p] = NUL;

                /* �u�b�N�}�[�N�� POST */
                strcpy( url, "http://clip.livedoor.com/clip/add" );

                p = any2utf( mp->title );
                strcpy( tmpTitle, p ? p : mp->title );

                // MM/Memo �`���� title ���������߂̏���
                rate = getEvaluation( tmpTitle, UTF8 );
                q = tmpTitle;
                if ( rate == 0 )
                    if ( (mp->evaluation >= EVL_ONE)  &&
                         (mp->evaluation <= EVL_FIVE)    )
                        rate = mp->evaluation;

                sprintf( request,
                         "title=%s&",
                         encodeURLex2( q ) );

                sprintf( request + strlen(request),
                         "postkey=%s&"
                         "link=%s&",
                         postkey,
                         encodeURL( mp->url ) );

                p = any2utf( mp->tags );
                sprintf( request + strlen(request),
                         "tags=%s&",
                         encodeURL( p ? p : mp->tags ) );

                p = any2utf( mp->comment );
                sprintf( request + strlen(request),
                         "notes=%s&"
                         "public=%s&"
                         "r18=0&",
                         encodeURLex( p ? p : mp->comment ),
                         mp->publication == PUB_PRIVATE ? "off"
                                                        : "on" );

                sprintf( request + strlen(request),
                         "submit=%s&",
                         encodeURL( sjis2utf("�N���b�v") ) );
                sprintf( request + strlen(request),
                         "jump=%s&"
                         "form=",
                         encodeURL( mp->url ) );

                setUpReceiveBuffer( response, sz );
                http_postEx( url, "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response ) {
                    p = strstr( response,
                                "<form action=\"/clip/delete\"" );
                    q = strstr( response,
                                sjis2utf("�ɓo�^�ς�</span>") );
                    if ( p && q && (p < q) ) {
#ifndef WIN32
# ifndef IDNO
#  define IDNO  FALSE
#  define IDYES TRUE
# endif /* !IDNO  */
#endif  /* !WIN32 */
                        int     r = IDNO;
                        int     fd = fileno( stderr );
                        LCID    l = getLanguageCode();

                        strcpy( errorString,
                                l == 0x0411
                                 ? "����Web�y�[�W�́A���ł�livedoor�N���b�v��"
                                   "�o�^�ς݂ł��B"
                                 : "this web page was already registered by"
                                   " you." );
#ifdef  WIN32
                        if ( (fd >= 0) && isatty( fd ) )
                            r = IDNO;
                        else
                            r = MessageBox(
                                    NULL,
                                    l == 0x0411
                                     ? "���YWeb�y�[�W�͊��ɓo�^�ς݂ł��B    "
                                       "\r\n�o�^���e���㏑�����܂���?"
                                     : "This web page was already registered "
                                       "by you.    \r\n"
                                       "Overwrite this bookmark?",
                                    l == 0x0411
                                     ? "�㏑���m�F (livedoor�N���b�v)"
                                     : "Overwrite bookmark (livedoor clip)",
                                    MB_YESNO|MB_ICONQUESTION );
#endif
                        if ( r == IDYES )
                            editLivedoorClip( mp, rate, postkey, cookie,
                                              errorString );
                    }
                    else {
                        if ( rate > 0 )
                            setRateOnLivedoorClip( param->userName,
                                                   mp->url,
                                                   rate, cookie );
                    }

                    ret = TRUE; /* �o�^���� */
                }
            }
        }
    }

    return ( ret );
}

void
putLivedoorClip(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t      cookieSize = MAX_COOKIE_LEN;
    char        cookie[MAX_COOKIE_LEN + 1];
    int         ret;
    PARAM_LC    param;

    param.userName = userName;
    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* livedoor Clip �� login */
    ret = loginLivedoorClip( userName, password, cookie );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( "livedoor�N���b�v",
                      mp, numOfClips, cookie, cookieSize, &param,
                      _putLivedoorClip );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "livedoor �ւ� login �Ɏ��s���܂���\n"
                    : "livedoor clip: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "livedoor �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "livedoor clip: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_LIVEDOOR_CLIP_EXE
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
                 "putLC: OPML �� livedoor�N���b�v �o�^�c�[��\n" );
        fprintf( stderr,
    "    putLC [-x] -u ���[�U�� -p �p�X���[�h [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
    "\t-x: proxy ���g��\n"
    "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putLC: read bookmarks from OPML, and put them into livedoor clip\n" );
        fprintf( stderr,
      "    putLC [-x] -u username -p password [-i OPMLfilename]\n" );
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
        /* �u�b�N�}�[�N�� livedoor�N���b�v �ɓo�^ */
        putLivedoorClip( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_LIVEDOOR_CLIP_EXE */

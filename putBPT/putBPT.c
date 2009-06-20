/*
 * clip loader <<putBPT>>
 *
 *      OPML �� BlogPeople Tags �o�^�v���O����
 *          written by H.Tsujimura  17 Oct 2005
 *
 * $Log: /comm/bookey/putBPT/putBPT.c $
 * 
 * 1     09/05/14 4:31 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 34    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 33    07/09/04 22:05 Tsujimura543
 * setVerbose() �̑�2�����ǉ��ɔ����ύX
 * 
 * 32    07/01/23 16:42 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 31    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 30    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 29    06/11/17 19:38 Tsujimura543
 * getEvaluation() �𓱓��Btitle �� MM/Memo �`���ł���΁A���K�����Ă���
 * �o�^����悤�ɂ��Ă݂�
 * 
 * 28    06/11/13 17:27 Tsujimura543
 * 2006�N11��1��(��������2006�N10��31��?)���_�ł�login�V�[�P���X�ύX�ɑΉ�
 * 
 * 27    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 26    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 25a   06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 25    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 24    06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 23    06/05/22 16:49 Tsujimura543
 * Sleep() ����^�C�~���O���Ē���
 * 
 * 22    06/05/22 15:30 Tsujimura543
 * (1) �������I�[�o�[�����΍�����{
 * (2) �o�^���s���� Sleep() �̃^�C�~���O�Asleep���鎞�Ԃ̒����𒲐�
 * 
 * 21    06/05/19 16:45 Tsujimura543
 * BlogPeople Tags �� cookie ���̈������ς����(2006�N5��13���ȍ~)
 * �e���Ńu�b�N�}�[�N���o�^�ł��Ȃ��Ȃ��Ă����̂��A�o�^�ł���悤�ɑΏ�
 * ����
 * 
 * 20    06/02/22 17:16 Tsujimura543
 * ��������������Ώ�
 * 
 * 19    06/02/22 17:14 Tsujimura543
 * &raquo; �΍�����{
 * 
 * 18    05/12/07 20:39 Tsujimura543
 * MM/Memo �`���� title ���ǂ������f���鏈�����������
 * 
 * 17    05/12/07 20:03 Tsujimura543
 * �u�b�N�}�[�N�Ώۂ�Web�y�[�W��title�� "�w" �� "�x" ���܂܂��ꍇ�A
 * MM/Memo �`���� title ���ƌ�F����Ă��܂��\�����ɗ͌��炷�悤��
 * ���Ă݂�
 * 
 * 16    05/11/11 1:13 Tsujimura543
 * ����m�F�I��
 * 
 * 15    05/11/11 1:11 Tsujimura543
 * MM/Memo �݊��`���̏ꍇ���� title ���������擾�ł��Ȃ��Ȃ��Ă����s�
 * ���C��
 * 
 * 14    05/11/02 16:26 Tsujimura543
 * MM/Memo �́u�]���v�A�u��ށv����荞�߂�悤�ɂ���
 * 
 * 13    05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 12    05/10/29 1:12 Tsujimura543
 * �u�b�N�}�[�N�o�^���Ɏg�p���鏈�����e�X��������(����m�F�ς�)
 * 
 * 11    05/10/25 14:22 Tsujimura543
 * ���b�Z�[�W�{�b�N�X�̃^�C�g���Ɩ{���̕������t�ɂȂ��Ă����̂��C��
 * 
 * 10    05/10/25 14:12 Tsujimura543
 * �W���G���[�o�͂��Θb�ɗ��p�\���ǂ����𒲍�������@���C��
 * 
 * 9     05/10/20 23:39 Tsujimura543
 * (1) format �X�g�����O�Ǝ㐫�o�O���C�� (2��)
 * (2) �u�b�N�}�[�N�o�^���s���̃��g���C������ǉ�
 * 
 * 8     05/10/20 21:13 Tsujimura543
 * ���͂̕����R�[�h�� Shift_JIS, EUC-JP, UTF-8 �̂ǂ�ł������悤�ɂ���
 * 
 * 7     05/10/20 16:06 Tsujimura543
 * usage() �ŕ\�����镶�����ēx�C�� (�C�����Y�ꂽ�ӏ����c���Ă���)
 * 
 * 6     05/10/19 17:28 Tsujimura543
 * putBlogPeopleTags() �̃��^�[���l�� int ���� BOOL �ɕύX
 * 
 * 5     05/10/18 14:31 Tsujimura543
 * putBPT() �� putBPTags() �ɖ��̕ύX
 * 
 * 4     05/10/18 13:49 Tsujimura543
 * encodeURL( NULL ); �����s����ꏊ��ύX
 * 
 * 3     05/10/18 13:46 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 2     05/10/18 13:43 Tsujimura543
 * (1) loginBlogPeople() ���t�@�C��������폜�BblogPeople.c �̂��̂��Q�Ƃ���
 *     �悤�ɂ���
 * (2) putBookmark() �� putBlogPeopleTags() �ɖ��̕ύX
 * 
 * 1     05/10/18 0:38 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBPT/putBPT.c 1     09/05/14 4:31 tsupo $";
#endif

BOOL
_putBlogPeopleTags(
        char       *cookie,
        char       *request,
        char       *response,
        size_t     sz,
        const char *url,
        const char *title,
        const char *comment
    )
{
    BOOL    ret = FALSE;

    strcpy( request, "http://tags.blogpeople.net/tags_addlink.jsp" );
    sprintf( request + strlen( request ),
             "?u=%s&",
             encodeURL( url ) );
    sprintf( request + strlen( request ),
             "ti=%s&",
             encodeURLex4( title ) );
    sprintf( request + strlen( request ),
             "de=%s",
             encodeURL( comment ) );

    setUpReceiveBuffer( response, sz );
    http_getEx( request, response, cookie );
    if ( !response || !(response[0]) )
        encodeURL( NULL );
    else
        ret = TRUE;

    return ( ret );
}


typedef struct paramPutBPT  {
    const char  *userName;
    const char  *password;
}   PARAM_BPT;

BOOL
putBlogPeopleTags(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    PARAM_BPT   *param    = (PARAM_BPT *)(args->args);
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    const char  *userName = param->userName;
    const char  *password = param->password;
    char        url[1024];
    char        imgURL[MAX_URLLENGTH];
    char        tmpURL[BUFSIZ];
    char        tmpTitle[BUFSIZ];
    char        tmpTags[180];
    char        tmpComment[2048];
    char        category[8];
    char        calist[BUFSIZ];
    const char  *p, *q;
    char        cookie2[MAX_COOKIE_LEN];
    long        rate = 0;
    BOOL        ret  = FALSE;

    errorString[0] = NUL;
    category[0]    = NUL;
    request[0]     = NUL;

    strcpy( tmpURL, mp->url );

    // MM/Memo �`���� title ���������߂̏���
    strcpy( tmpTitle, mp->title );
    rate = getEvaluation( tmpTitle, SJIS2UTF );
    if ( rate == 0 )
        if ( (mp->evaluation >= EVL_ONE) && (mp->evaluation <= EVL_FIVE) )
            rate = mp->evaluation;

    p = utf2sjis( mp->tags );
    if ( !p )
        p = euc2sjis( mp->tags );
    strcpy( tmpTags,    p ? p : mp->tags );

    p = utf2sjis( mp->comment );
    if ( !p )
        p = euc2sjis( mp->comment );
    strcpy( tmpComment, p ? p : mp->comment );

    ret = _putBlogPeopleTags( cookie, request, response, sz,
                              tmpURL, tmpTitle, tmpComment );
    if ( ret == FALSE )
        return ( ret );

    if ( strstr( response, "value=\"���O�C��\"" ) ) {
        // BlogPeople �Ƀ��O�C��
        ret = FALSE;
        memset( cookie2, 0x00, MAX_COOKIE_LEN );
        strcpy( url, "http://member.blogpeople.net/member/member_index.jsp" );
        sprintf( request,
                 "user_id=%s&passwd=%s&autologin=1&",
                 userName, password );
        sprintf( request + strlen( request ),
                 "Submit=%s&opt=1&url=",
                 encodeURL( "�@���O�C���@" ) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie2 );
        if ( !response || !(response[0]) ) {
            encodeURL( NULL );
            return ( ret );
        }

        imgURL[0] = NUL;
        p = strstr( response, "<img src=\"" );
        if ( p ) {
            p += 10;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( imgURL, p, q - p );
                imgURL[q - p] = NUL;
            }
        }

        if ( imgURL[0] ) {  // 2006�N11��1���ȍ~�̐Vlogin�V�[�P���X�Ή�
            memset( cookie2, 0x00, MAX_COOKIE_LEN );
            setUpReceiveBuffer( response, sz );
            http_getEx( imgURL, response, cookie2 );
            if ( !response || !(response[0]) ) {
                encodeURL( NULL );
                return ( ret );
            }
        }

        if ( cookie2[0] ) {
            strcpy( cookie, cookie2 );
            ret = _putBlogPeopleTags( cookie, request, response, sz,
                                      tmpURL, tmpTitle, tmpComment );
        }

        if ( ret == FALSE )
            return ( ret );
    }

    if ( category[0] )
        strcpy( calist, category );
    else {
        // calist �擾
        calist[0] = NUL;
        p = strstr( response, "<select name=\"calist\"" );
        if ( p ) {
            q = strstr( p + 21, "<option value=\"" );
            if ( q ) {
                p = q + 15;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( calist, p, q - p );
                    calist[q - p] = NUL;
                }
            }
        }
        if ( calist[0] == NUL )
            strcpy( calist, "bookey" ); /* �b�� */
    }

    strcpy( url, "http://tags.blogpeople.net/tags_addlink.jsp" );
    sprintf( request,
             "calist=%s&",
             encodeURL( calist ) );
    sprintf( request + strlen( request ),
             "ca=%s&",
             encodeURL( calist ) );
    sprintf( request + strlen( request ),
             "u=%s&",
             encodeURL( tmpURL ) );
    sprintf( request + strlen( request ),
             "ti=%s&",
             encodeURLex4( tmpTitle ) );
    sprintf( request + strlen( request ),
             "tag=%s&",
             encodeURL( tmpTags ) );
    sprintf( request + strlen( request ),
             "desc=%s&"
             "myrate=%d&",
             encodeURL( tmpComment ),
             rate );
    sprintf( request + strlen( request ),
             "submit=%s",
             encodeURL( "�ǉ�" ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    ret = response && response[0] ? TRUE : FALSE;
    encodeURLex4( NULL );

    return ( ret );
}


void
putBPTags(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t      cookieSize = MAX_COOKIE_LEN;
    char        cookie[MAX_COOKIE_LEN + 1];
    PARAM_BPT   param;

    param.userName = userName;
    param.password = password;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    putBookmarks( "BlogPeople Tags",
                  mp, numOfClips, cookie, cookieSize, &param,
                  putBlogPeopleTags );
}



#ifdef  PUT_BLOGPEOPLE_TAGS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForHatena,
        char *passwordForHatene,
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
        fprintf( stderr, "putBPT: OPML �� BlogPeople Tags �o�^�c�[��\n" );
        fprintf( stderr,
                 "    putBPT [-x] -u BlogPeople���O�C���p���[���A�h���X\n"
                 "                -p �p�X���[�h [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
            "\t-x: proxy ���g��\n"
            "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
     "putBPT: read bookmarks from OPML, and put them into BlogPeople Tags\n");
        fprintf( stderr,
     "    putBPT [-x] -u mailaddress -p password [-i OPMLfilename]\n" );
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

#ifdef  _DEBUG
    setVerbose( TRUE, stderr );
#endif
    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� BlogPeople Tags �ɓo�^ */
        putBPTags( username, password, mp, numOfClips );
        free( mp );
        encodeURL( NULL );      // �̈���
        encodeURLex4( NULL );   // �̈���
    }

    return ( 1 );
}
#endif  /* PUT_BLOGPEOPLE_TAGS_EXE */

/*
 * clip loader <<putDrecomRSS>>
 *
 *      OPML �� �h���R��RSS-Clip �o�^�v���O����
 *          written by H.Tsujimura  28 Mar 2006
 *
 * History:
 * $Log: /comm/bookey/putDrecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 24    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 23    07/02/15 0:29 Tsujimura543
 * getArticleIDbyURL() �� getArticleIDbyURLonDrecomRSS() �ɖ��̕ύX
 * 
 * 22    07/02/08 16:52 Tsujimura543
 * �R�}���h���C���ł̃r���h���́u�㏑���@�\�v��g�ݍ��܂Ȃ��悤�ɂ���
 * 
 * 21    07/02/05 21:41 Tsujimura543
 * �\�[�X�𐮗�
 * 
 * 20    07/02/05 21:40 Tsujimura543
 * getArticleIDbyURL() �̈�����ǉ��B�t�H���_�ԍ����킩���Ă���ꍇ��
 * �L��ID�̔����ɗv���鎞�Ԃ�Z�k�ł���悤�ɂȂ���
 * 
 * 19    07/02/05 20:03 Tsujimura543
 * �㏑���m�F���b�Z�[�W�{�b�N�X�̃^�C�g���̕�����ύX
 * 
 * 18    07/02/05 18:22 Tsujimura543
 * ���łɓo�^�ς݂�Web�y�[�W���ēx�o�^���悤�Ƃ��Ă���ꍇ�́A
 * �㏑�����邩�ǂ������₵����ŏ㏑�������s����悤�ɂ���
 * 
 * 17    07/01/23 21:01 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 16    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 15    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 14    06/10/05 22:33 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 13    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 13a   06/09/03 20:17 tsupo
 * cookie �܂����C��
 * 
 * 12    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 11    06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 10    06/07/18 20:45 Tsujimura543
 * ���O�C�����s���ɃG���[�_�C�A���O���o���悤�ɂ���
 * 
 * 9     06/05/22 16:49 Tsujimura543
 * Sleep() ����^�C�~���O���Ē���
 * 
 * 8     06/05/22 15:30 Tsujimura543
 * �o�^���s���� Sleep() �̃^�C�~���O�Asleep���鎞�Ԃ̒����𒲐�
 * 
 * 7     06/03/29 18:29 Tsujimura543
 * getFolderNumber() �̕Ԃ��l�� default �l�� 1 (Internet) �Ƃ���
 * 
 * 6     06/03/28 17:05 Tsujimura543
 * loginDrecomRSS() �� drecomRSS.c �֕���
 * 
 * 5     06/03/28 16:54 Tsujimura543
 * putDrecomRSS() ���Ăяo���O�ɁA���炩���� UTF-8 �ɕϊ�����Ă��邱�Ƃ�O��
 * �Ƃ���d�l�ɕύX���� (���̃u�b�N�}�[�N�T�[�r�X�p�� putXXX() �Ǝd�l�����킹
 * �邽��)
 * 
 * 4     06/03/28 15:59 Tsujimura543
 * �s�v�ȏ������폜
 * 
 * 3     06/03/28 15:55 Tsujimura543
 * ����m�F����
 * 
 * 2     06/03/28 15:46 Tsujimura543
 * http://rss.drecom.jp/shortcut/add_clip �� GET ���鏈�������s����
 * �K�v���Ȃ����Ƃ��m�F�B�폜����
 * 
 * 1     06/03/28 15:38 Tsujimura543
 * �ŏ��̔�
 */

#include "myClip.h"
#include "getDrecomRSS.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDrecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif


int
getFolderNumber( const char *folderName )
{
    int folderNumber = 1; /* default */

    if ( strstr( folderName, "Internet" ) )
        folderNumber = 1;
    else if ( strstr( folderName, "entertainment" ) )
        folderNumber = 2;
    else if ( strstr( folderName, "science" ) )
        folderNumber = 3;
    else if ( strstr( folderName, "region" ) )
        folderNumber = 4;
    else if ( strstr( folderName, "social" ) )
        folderNumber = 5;
    else if ( strstr( folderName, "column" ) )
        folderNumber = 6;
    else if ( strstr( folderName, "news-of-death" ) )
        folderNumber = 7;
    else if ( strstr( folderName, "culture" ) )
        folderNumber = 8;
    else if ( strstr( folderName, "blog" ) )
        folderNumber = 9;
    else if ( strstr( folderName, "economy" ) )
        folderNumber = 10;
    else if ( strstr( folderName, "politics" ) )
        folderNumber = 11;
    else if ( strstr( folderName, "sport" ) )
        folderNumber = 12;
    else if ( strstr( folderName, "book-review" ) )
        folderNumber = 13;
    else if ( strstr( folderName, "international" ) )
        folderNumber = 14;
    else if ( strstr( folderName, "technology" ) )
        folderNumber = 15;

    return ( folderNumber );
}


BOOL
_putDrecomRSS(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    url[MAX_URLLENGTH];
    int     folderNumber;
    BOOL    ret = FALSE;

    errorString[0] = NUL;
    folderNumber   = getFolderNumber(mp->tags);

    strcpy( url, "http://rss.drecom.jp/shortcut/add_clip_done" );
    sprintf( request,
             "clip_title=%s&",
             encodeURL(mp->title) );
    sprintf( request + strlen(request),
             "clip_url=%s&",
             encodeURL(mp->url) );
    sprintf( request + strlen(request),
             "clip_folder=%d&",
             folderNumber );
    sprintf( request + strlen(request),
             "clip_comment=%s&",
             encodeURL(mp->comment) );
    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL(sjis2utf("�o�^")) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr(response, sjis2utf("���ɓo�^���Ă���Clip�ł�")) ) {
#ifndef PUT_DRECOM_RSS_EXE
# ifndef WIN32
#  ifndef IDNO
#   define IDNO  FALSE
#   define IDYES TRUE
#  endif /* !IDNO  */
# endif  /* !WIN32 */
            int     r = IDNO;
            int     fd = fileno( stderr );
#endif  /* !PUT_DRECOM_RSS_EXE */
            LCID    l = getLanguageCode();

            strcpy( errorString,
                    l == 0x0411
                     ? "���YWeb�y�[�W�͊��ɓo�^�ς݂ł�"
                     : "this web page was already registered by you." );

#ifndef PUT_DRECOM_RSS_EXE
# ifdef  WIN32
            if ( (fd >= 0) && isatty( fd ) )
                r = IDNO;
            else
                r = MessageBox(
                        NULL,
                        l == 0x0411
                         ? "���YWeb�y�[�W�͊��ɓo�^�ς݂ł��B    \r\n"
                           "�o�^���e���㏑�����܂���?"
                         : "This web page was already registered by you."
                           "    \r\nOverwrite this bookmark?",
                        l == 0x0411
                         ? "�㏑���m�F (�h���R��RSS)"
                         : "Overwrite bookmark (Drecom RSS)",
                        MB_YESNO|MB_ICONQUESTION );
# endif

            if ( r == IDYES ) {
                char    articleID[64];

                articleID[0] = NUL;
                getArticleIDbyURLonDrecomRSS( mp->url, folderNumber, cookie,
                                              articleID );
                if ( articleID[0] ) {
                    /* �u�b�N�}�[�N�o�^���e�̏C�� */
                    errorString[0] = NUL;
                    editDrecomRSS( mp, articleID, cookie, errorString );
                }
            }
#endif  /* !PUT_DRECOM_RSS_EXE */
        }

        ret = TRUE;
    }

    return ( ret );
}

void
putDrecomRSS(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* �h���R��RSS �� login */
    ret = loginDrecomRSS( userName, password, cookie );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( getLanguageCode() == 0x0411
                       ? "�h���R��RSS"
                       : "Drecom RSS",
                      mp, numOfClips, cookie, cookieSize, NULL,
                      _putDrecomRSS );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "�h���R��RSS�ւ� login �Ɏ��s���܂���\n"
                    : "Drecom RSS: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "�h���R��RSS�ւ̃��O�C���Ɏ��s���܂����B  "
                         : "Drecom RSS: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_DRECOM_RSS_EXE
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
                 "putDRC: OPML �� Drecom RSS �� Clip! �o�^�c�[��\n" );
        fprintf( stderr,
     "    putDRC [-x] -u ���[���A�h���X -p �p�X���[�h [-i OPML�t�@�C����]\n");
        fprintf( stderr,
     "\t-x: proxy ���g��\n"
     "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
  "putDRC: read bookmarks from OPML, and put them into Drecom RSS (Clip!)\n");
        fprintf( stderr,
      "    putDRC [-x] -u mailaddress -p password [-i OPMLfilename]\n" );
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
        /* �u�b�N�}�[�N�� Drecom RSS �� Clip! �ɓo�^ */
        putDrecomRSS( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_DRECOM_RSS_EXE */

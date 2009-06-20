/*
 * clip loader <<putFlog>>
 *
 *      OPML �� Flog �o�^�v���O����
 *          written by H.Tsujimura  31 May 2006
 *
 * History:
 * $Log: /comm/bookey/putFlog.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    08/12/02 19:37 Tsujimura543
 * ����������Y��ɂȂ�\���̂���ӏ��̏C��
 * 
 * 18    07/11/12 20:55 Tsujimura543
 * any2sjisEx() �𓱓��AShift_JIS �Ȃ̂� EUC-JP ���ƌ�F����P�[�X�ɑΏ�
 * 
 * 17    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 16    07/02/05 15:08 Tsujimura543
 * getCategoryNumber() ��(Flog �Ǝ��J�e�S�����g���ĂȂ��ꍇ�A�ǂ�
 * �J�e�S���Ƀ}�b�s���O���邩�Ɋւ���)�d�l��ύX
 * 
 * 15    07/01/23 20:28 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 14    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 13    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 12    07/01/17 22:25 Tsujimura543
 * �Ԃ�~�X���C�� oversea �� overseas)
 * 
 * 11    07/01/16 15:20 Tsujimura543
 * �Ԃ�~�X���C�� (byke �� bike)
 * 
 * 10    06/10/03 23:06 Tsujimura543
 * �Ԃ�~�X���C�� (catoon �� cartoon) [facet����A�w�E����!]
 * 
 * 9     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 8a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 8     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 7     06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 6     06/07/18 21:04 Tsujimura543
 * ���O�C�����s���ɃG���[�_�C�A���O���o���悤�ɂ���
 * 
 * 5     06/06/22 18:58 Tsujimura543
 * ���łɒN�����o�^�ς݂�Web�y�[�W��o�^���悤�Ƃ���ƃG���[�ɂȂ���
 * �����̂��A����ɓo�^�ł���悤�ɑΏ�����
 * 
 * 4     06/06/01 21:48 Tsujimura543
 * �o�^���s���A�ȍ~�̓o�^�𒆒f���邩�ǂ����q�˂�悤�ɂ���
 * 
 * 3     06/05/31 21:48 Tsujimura543
 * �����R�[�h�� Shift_JIS �ȊO�̃u�b�N�}�[�N(OPML)�̎�荞�݂ɂ�
 * �Ή����� (�Ƃ������A�����R�[�h�̖���Y��Ă���)
 * 
 * 2     06/05/31 19:42 Tsujimura543
 * �W������(�J�e�S����)���^�O�Ŏw��ł���悤�ɂ���
 * 
 * 1     06/05/31 19:02 Tsujimura543
 * �ŏ��̔� (�W�������� "1" �Œ�ɂ����b���) [����m�F�ς�]
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putFlog.c 1     09/05/14 3:48 tsupo $";
#endif


int
getCategoryNumber( const char *categoryName )
{
    int cataegoryNumber = 0;

    /*
     * 1    �R���s���[�^
     * 2    �r�W�l�X/����
     * 3    �j���[�X
     * 4    ���L
     * 5    �|�\/�A�C�h��
     * 6    �w���X/�r���[�e�B
     * 7    �A�E/�]�E
     * 8    �O����
     * 9    ���y
     * 10   �f��
     * 11   �{/�G��/�V��
     * 12   ����/�A�j��
     * 13   �e���r
     * 14   �Q�[��
     * 15   �y�b�g/����
     * 16   �/�X�|�[�c
     * 17   ��/�o�C�N
     * 18   ���炵/�Ɠd
     * 19   ���s/�n����
     * 20   �|�p/�f�U�C��
     * 21   ����/�w��/����
     * 22   ����/�t���b�V��
     * 23   �֗��c�[��
     * 24   �܂Ƃ߃T�C�g
     * 25   �l�^/�W���[�N
     * 26   ����
     * 27   �t�@�b�V����/�u�����h
     * 28   �C�O
     */
    /* Flog�Ǝ��J�e�S���� */
    if ( strstr( categoryName, "computer" ) )
        cataegoryNumber = 1;
    else if ( strstr( categoryName, "business" ) )
        cataegoryNumber = 2;
    else if ( strstr( categoryName, "news" ) )
        cataegoryNumber = 3;
    else if ( strstr( categoryName, "diary" ) )
        cataegoryNumber = 4;
    else if ( strstr( categoryName, "showbiz" ) )
        cataegoryNumber = 5;
    else if ( strstr( categoryName, "health" ) )
        cataegoryNumber = 6;
    else if ( strstr( categoryName, "employment" ) )
        cataegoryNumber = 7;
    else if ( strstr( categoryName, "gourmet" ) )
        cataegoryNumber = 8;
    else if ( strstr( categoryName, "music" ) )
        cataegoryNumber = 9;
    else if ( strstr( categoryName, "cinema" ) )
        cataegoryNumber = 10;
    else if ( strstr( categoryName, "print" ) )
        cataegoryNumber = 11;
    else if ( strstr( categoryName, "catoon" ) ||
              strstr( categoryName, "cartoon")    )
        cataegoryNumber = 12;
    else if ( strstr( categoryName, "tv" ) )
        cataegoryNumber = 13;
    else if ( strstr( categoryName, "game" ) )
        cataegoryNumber = 14;
    else if ( strstr( categoryName, "animal" ) )
        cataegoryNumber = 15;
    else if ( strstr( categoryName, "hobby" ) )
        cataegoryNumber = 16;
    else if ( strstr( categoryName, "car" ) )
        cataegoryNumber = 17;
    else if ( strstr( categoryName, "life" ) )
        cataegoryNumber = 18;
    else if ( strstr( categoryName, "travel" ) )
        cataegoryNumber = 19;
    else if ( strstr( categoryName, "art" ) )
        cataegoryNumber = 20;
    else if ( strstr( categoryName, "education" ) )
        cataegoryNumber = 21;
    else if ( strstr( categoryName, "movie" ) )
        cataegoryNumber = 22;
    else if ( strstr( categoryName, "tool" ) )
        cataegoryNumber = 23;
    else if ( strstr( categoryName, "summarySite" ) )
        cataegoryNumber = 24;
    else if ( strstr( categoryName, "neta" ) )
        cataegoryNumber = 25;
    else if ( strstr( categoryName, "love" ) )
        cataegoryNumber = 26;
    else if ( strstr( categoryName, "fashion" ) )
        cataegoryNumber = 27;
    else if ( strstr( categoryName, "overseas") ||
              strstr( categoryName, "oversea" )    )
        cataegoryNumber = 28;

    if ( cataegoryNumber == 0 ) {
        /* �h���R��RSS�݊��J�e�S���� */
        if ( strstr( categoryName, "Internet" ) )
            cataegoryNumber = 1;    /* �� �R���s���[�^   */
        else if ( strstr( categoryName, "entertainment" ) )
            cataegoryNumber = 3;    /* �� �j���[�X       */
        else if ( strstr( categoryName, "science" ) )
            cataegoryNumber = 21;   /* �� ����/�w��/���� */
        else if ( strstr( categoryName, "region" ) )
            cataegoryNumber = 19;   /* �� ���s/�n����  */
        else if ( strstr( categoryName, "social" ) )
            cataegoryNumber = 3;    /* �� �j���[�X       */
        else if ( strstr( categoryName, "column" ) )
            cataegoryNumber = 21;   /* �� ����/�w��/���� */
        else if ( strstr( categoryName, "news-of-death" ) )
            cataegoryNumber = 3;    /* �� �j���[�X       */
        else if ( strstr( categoryName, "culture" ) )
            cataegoryNumber = 8;    /* �� �|�\/�A�C�h��  */
        else if ( strstr( categoryName, "blog" ) )
            cataegoryNumber = 4;    /* �� ���L           */
        else if ( strstr( categoryName, "economy" ) )
            cataegoryNumber = 2;    /* �� �r�W�l�X/����  */
        else if ( strstr( categoryName, "politics" ) )
            cataegoryNumber = 2;    /* �� �r�W�l�X/����  */
        else if ( strstr( categoryName, "sport" ) )
            cataegoryNumber = 16;   /* �� �/�X�|�[�c  */
        else if ( strstr( categoryName, "book-review" ) )
            cataegoryNumber = 11;   /* �� �{/�G��/�V��   */
        else if ( strstr( categoryName, "international" ) )
            cataegoryNumber = 28;   /* �� �C�O           */
        else if ( strstr( categoryName, "technology" ) )
            cataegoryNumber = 21;   /* �� ����/�w��/���� */
    }

    if ( cataegoryNumber == 0 ) {
        /* ���̑� */
        if ( strstr( categoryName, "books" ) )
            cataegoryNumber = 11;   /* �� �{/�G��/�V��   */
        else if ( strstr( categoryName, "comics" ) )
            cataegoryNumber = 12;   /* �� ����/�A�j��    */
        else if ( strstr( categoryName, "anime" ) )
            cataegoryNumber = 12;   /* �� ����/�A�j��    */
        else if ( strstr( categoryName, "foods" ) )
            cataegoryNumber = 8;    /* �� �O����         */
        else if ( strstr( categoryName, "magazine" ) )
            cataegoryNumber = 11;   /* �� �{/�G��/�V��   */
        else if ( strstr( categoryName, "newspaper" ) )
            cataegoryNumber = 11;   /* �� �{/�G��/�V��   */
        else if ( strstr( categoryName, "bike" ) )
            cataegoryNumber = 17;   /* �� ��/�o�C�N      */
    }

    if ( cataegoryNumber == 0 )
        cataegoryNumber = 1;    /* default */;

    return ( cataegoryNumber );
}

BOOL
_putFlog(
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
    BOOL    ret = FALSE;

    errorString[0] = NUL;

    /* �܂��AURL �� POST */
    strcpy( url, "http://www.flog.jp/post.php" );
    sprintf( request,
             "url_uri=%s&",
             encodeURL(mp->url) );
    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL("����") );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        const char  *p, *q;
        char        *buffer = (char *)malloc( MAX_CONTENT_SIZE );

        p = strstr( response, "�u�b�N�}�[�N�ɓ��e���܂�" );
        if ( !p )
            p = strstr( response, "�u�b�N�}�[�N��ǉ�����" );
        if ( p ) {
            char    domain[80];
            char    name[80];
            char    tag[3][80];
            int     cnt = 0;
            int     i;

            p = mp->url;
            q = strchr( p + 8, '/' );
            if ( q ) {
                strncpy( domain, p, q - p );
                domain[q - p] = NUL;
            }
            else
                strcpy( domain, mp->url );

            p = strstr( cookie, "NAME=" );
            if ( p ) {
                p += 5;
                strcpy( name, p );
            }
            else
                name[0] = NUL;

            tag[0][0] = NUL;
            tag[1][0] = NUL;
            tag[2][0] = NUL;
            p = mp->tags;
            do {
                q = strchr( p, ' ' );
                if ( q ) {
                    strncpy( tag[cnt], p, q - p );
                    tag[cnt][q - p] = NUL;
                    cnt++;
                    if ( cnt >= 3 )
                        break;
                    p = q + 1;
                }
                else {
                    strcpy( tag[cnt], p );
                    break;
                }
            } while ( *p );

            memset( request,  0x00, MAX_CONTENT_SIZE );
            strcpy( url, "http://www.flog.jp/post.php" );
            sprintf( request,
                     "plot=1&"
                     "url_uri=%s&",
                     encodeURL(mp->url) );
            sprintf( request + strlen(request),
                     "url_domain=%s&",
                     encodeURL(domain) );

            /* ���O */
            if ( name[0] )
                sprintf( request + strlen(request),
                         "url_postuser=%s&",
                         encodeURL(name) );
            else
                strcat( request, "url_postuser=&" );

            /* �W������ */
            sprintf( request + strlen(request),
                     "url_category=%d&",
                     getCategoryNumber(mp->tags) );

            /* �T�C�g�� */
            if ( buffer ) {
                buffer[0] = NUL;
                p = any2sjisEx( buffer, mp->title );
            }
            else {
                p = utf2sjis( mp->title );
                if ( !p )
                    p = euc2sjis( mp->title );
            }
            sprintf( request + strlen(request),
                     "url_title=%s&",
                     encodeURL(p ? p : mp->title) );

            /* �L�[���[�h (�ő�3�܂�) */
            for ( i = 0; i <= 2; i++ ) {
                if ( tag[i] ) {
                    if ( buffer ) {
                        buffer[0] = NUL;
                        p = any2sjisEx( buffer, tag[i] );
                    }
                    else {
                        p = utf2sjis( tag[i] );
                        if ( !p )
                            p = euc2sjis( tag[i] );
                    }
                    sprintf( request + strlen(request),
                             "userpage_label%d=%s&",
                             i + 1,
                             encodeURL(p ? p : tag[i]) );
                }
                else
                    sprintf( request + strlen(request),
                             "userpage_label%d=&",
                             i + 1 );
            }

            /* �R�����g */
            if ( buffer ) {
                buffer[0] = NUL;
                p = any2sjisEx( buffer, mp->comment );
            }
            else {
                p = utf2sjis( mp->comment );
                if ( !p )
                    p = euc2sjis( mp->comment );
            }
            sprintf( request + strlen(request),
                     "url_comment=%s&",
                     encodeURL(p ? p : mp->comment) );

            sprintf( request + strlen(request),
                     "submit=%s&"
                     "posted=&"
                     "origin=",
                     encodeURL("�u�b�N�}�[�N�𓊍e����") );

            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

            if ( *response ) {
                if ( strstr( response, "���e���������܂���" ) )
                    ret = TRUE; /* �o�^���� */
            }
        }

        if ( buffer )
            free( buffer );
    }

    return ( ret );
}

void
putFlog(
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

    /* Flog �� login */
    ret = loginFlog( userName, password, cookie );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( "Flog", mp, numOfClips, cookie, cookieSize, NULL,
                      _putFlog );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Flog�ւ� login �Ɏ��s���܂���\n"
                    : "Flog: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Flog�ւ̃��O�C���Ɏ��s���܂����B  "
                         : "Flog: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_FLOG_EXE
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
                 "putFlog: OPML �� Flog �o�^�c�[��\n" );
        fprintf( stderr,
    "    putFlog [-x] -u ���[���A�h���X -p �p�X���[�h [-i OPML�t�@�C����]\n");
        fprintf( stderr,
    "\t-x: proxy ���g��\n"
    "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putFlog: read bookmarks from OPML, and put them into Flog\n" );
        fprintf( stderr,
      "    putFlog [-x] -u mailaddress -p password [-i OPMLfilename]\n" );
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
        /* �u�b�N�}�[�N�� Flog �ɓo�^ */
        putFlog( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_FLOG_EXE */

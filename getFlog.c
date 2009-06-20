/*
 * clip saver <<getFlog>>
 *
 *      Flog �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  23 Jun 2006
 *
 * $Log: /comm/bookey/getFlog.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    08/11/25 12:10 Tsujimura543
 * �u�b�N�}�[�N�擾�������X�V
 * (���̊Ԃɂ��AFlog �̃y�[�W�̃t�H�[�}�b�g�A�\�����ς���Ă������߁A
 *  �u�b�N�}�[�N�̎擾���ł��Ȃ��Ȃ��Ă���)
 * 
 * 14    08/02/14 19:40 Tsujimura543
 * replaceString() �� myClip.c �ֈړ�
 * 
 * 13    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 12    07/01/18 0:29 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 11    07/01/17 22:59 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 10    07/01/17 22:25 Tsujimura543
 * �Ԃ�~�X���C�� oversea �� overseas)
 * 
 * 9     06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 8     06/10/03 23:06 Tsujimura543
 * �Ԃ�~�X���C�� (catoon �� cartoon) [facet����A�w�E����!]
 * 
 * 7     06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() �𓱓��BMyClip �\���̊i�[�̈�m�ۏ�����
 * ���ʊ֐������Ă݂�
 * 
 * 6     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 5a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 5     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 4     06/06/23 21:50 Tsujimura543
 * &raquo; �΍��ǉ�
 * 
 * 3     06/06/23 21:48 Tsujimura543
 * (1) http���N�G�X�g��A�����M����ꍇ�A1�b�� Sleep ������悤�ɂ���
 * (2) �������u�N�v���擾���邽�߁Acomment.php ���擾����悤�ɂ���
 * (3) OPML �����o������ XML �I�ɐ������Ȃ����̂���������Ă��܂�Ȃ���
 *     ���ɃR�����g��^�C�g���ɓ��ʈ������ׂ��������܂܂��ꍇ�͓K�X�u
 *     ������悤�ȏ�����ǉ�����
 * 
 * 2     06/06/23 18:10 Tsujimura543
 * comment ���Ɋ܂܂����s��<br>����������悤�ɂ���
 * 
 * 1     06/06/23 17:59 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getFlog.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/*
 *  Flog �̏ꍇ�A�����̃u�b�N�}�[�N�ꗗ��
 *    (1) My�u�b�N�}�[�N
 *    (2) �Ǘ����
 *  �o�R�̂ǂ���ł��擾�\�ł���A(1) �� 20��/�y�[�W�P�ʂł̎擾�A
 *  (2) �͑S����C�擾�ƂȂ�B�����A�u�b�N�}�[�N�̐��������Ă���ƁA
 *  (2) ��1�y�[�W�őS���擾�ł��Ȃ��Ȃ�\��������(���m�F)���߁A
 *  �����_�ł� (1) �o�R�Ńu�b�N�}�[�N�ꗗ���擾���邱�Ƃɂ���
 *
 *  �܂��A���[�UID���킩��΁Ahttp://www.flog.jp/m.php/���[�UID ��
 *  �A�N�Z�X���邱�ƂŁA���̃��[�U�̃u�b�N�}�[�N���擾�ł���((1) ��
 *  �����`���Ŏ擾�ł���̂ŁA�擾�����͋��ʉ��ł���)�B
 */

char    *
getFlogGategory( const char *catStr )
{
    const char  *tag = "computer";

    if ( !strcmp( catStr, "�R���s���[�^" ) )
        tag = "computer";
    else if ( !strcmp( catStr, "�r�W�l�X/����" ) )
        tag = "business";
    else if ( !strcmp( catStr, "�j���[�X" ) )
        tag = "news";
    else if ( !strcmp( catStr, "���L" ) )
        tag = "diary";
    else if ( !strcmp( catStr, "�|�\/�A�C�h��" ) )
        tag = "showbiz";
    else if ( !strcmp( catStr, "�w���X/�r���[�e�B" ) )
        tag = "health";
    else if ( !strcmp( catStr, "�A�E/�]�E" ) )
        tag = "employment";
    else if ( !strcmp( catStr, "�O����" ) )
        tag = "gourmet";
    else if ( !strcmp( catStr, "���y" ) )
        tag = "music";
    else if ( !strcmp( catStr, "�f��" ) )
        tag = "cinema";
    else if ( !strcmp( catStr, "�{/�G��/�V��" ) )
        tag = "print";
    else if ( !strcmp( catStr, "����/�A�j��" ) )
        tag = "cartoon";
    else if ( !strcmp( catStr, "�e���r" ) )
        tag = "tv";
    else if ( !strcmp( catStr, "�Q�[��" ) )
        tag = "game";
    else if ( !strcmp( catStr, "�y�b�g/����" ) )
        tag = "animal";
    else if ( !strcmp( catStr, "�/�X�|�[�c" ) )
        tag = "hobby";
    else if ( !strcmp( catStr, "��/�o�C�N" ) )
        tag = "car";
    else if ( !strcmp( catStr, "���炵/�Ɠd" ) )
        tag = "life";
    else if ( !strcmp( catStr, "���s/�n����" ) )
        tag = "travel";
    else if ( !strcmp( catStr, "�|�p/�f�U�C��" ) )
        tag = "art";
    else if ( !strcmp( catStr, "����/�w��/����" ) )
        tag = "education";
    else if ( !strcmp( catStr, "����/�t���b�V��" ) )
        tag = "movie";
    else if ( !strcmp( catStr, "�֗��c�[��" ) )
        tag = "tool";
    else if ( !strcmp( catStr, "�܂Ƃ߃T�C�g" ) )
        tag = "summarySite";
    else if ( !strcmp( catStr, "�l�^/�W���[�N" ) )
        tag = "neta";
    else if ( !strcmp( catStr, "����" ) )
        tag = "love";
    else if ( !strcmp( catStr, "�t�@�b�V����/�u�����h" ) )
        tag = "fashion";
    else if ( !strcmp( catStr, "�C�O" ) )
        tag = "overseas";

    return ( (char *)tag );
}


char    *
getFlogUserID( const char *userName, const char *password )
{
    Thread static char  userID[32];
    char                *cookie;
    char                *response;
    char                url[MAX_URLLENGTH];
    int                 fd;
    size_t              sz = MAX_CONTENT_SIZE * 20;

    userID[0] = NUL;

    fd = fileno( stderr );
    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "�������̊m�ۂɎ��s���܂���\n"
                    : "memory exhausted.\n",
                   stderr );
        return ( userID );
    }
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* Flog �� login */
    if ( !loginFlog( userName, password, cookie ) ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Flog�ւ� login �Ɏ��s���܂���\n"
                    : "Flog: login failed.\n",
                   stderr );
        free( cookie );
        return ( userID );
    }

    /* �uMy�u�b�N�}�[�N�v���擾 */
    response = (char *)malloc( sz );
    if ( !response ) {
        free( cookie );
        return ( userID );
    }

    strcpy( url, "http://www.flog.jp/my.php" );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    /* �uMy�u�b�N�}�[�N�v���烆�[�UID���擾 */
    if ( response && *response ) {
        char    *p = strstr( response, "<a href=\"/confirm.php/" );

        if ( p ) {
            char    *q;

            p += 22;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( userID, p, q - p );
                userID[q - p] = NUL;
            }
        }
    }

    free( response );
    free( cookie );

    return ( userID );
}

MyClip  *
getFlog(
        const char *userName,   /* (I) login���Ɏg�����[�U��    */
        const char *password,   /* (I) login���Ɏg���p�X���[�h  */
        const char *userID,     /* (I) ���[�UID                 */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�̃u�b�N�}�[�N�A�������� userID �Ŏw�肳
     *  �ꂽ���[�U�̃u�b�N�}�[�N��S���擾����(userName �Ŏw�肷��ꍇ�́A
     *  password �̎w����K�v�BuserID �Ŏw�肷��ꍇ�́Apassword �͕s�v)
     */
    MyClip      *mp = NULL;
    char        target[MAX_URLLENGTH];
    char        url[MAX_URLLENGTH];
    char        commentURL[MAX_URLLENGTH];
    char        *response;
    char        *response2;
    BOOL        cont = TRUE;
    char        *p, *q, *r, *s;
    int         num  = 0;
    int         cnt  = 0;
    int         unit = 200;
    int         len;
    char        category[32];
    char        commentID[32];
    int         yy, mm, dd, HH, MM, SS;
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    size_t      sz  = MAX_CONTENT_SIZE * 20;

    yy = tm->tm_year + 1900;
    mm = tm->tm_mon + 1;
    dd = tm->tm_mday;
    HH = tm->tm_hour;
    MM = tm->tm_min;
    SS = tm->tm_sec;

    *numOfClips = 0;
    target[0]   = NUL;
    if ( userName && userName[0] && password && password[0] ) {
        char    *uID = getFlogUserID( userName, password );
        if ( uID )
            sprintf( target, "http://www.flog.jp/m.php/%s", uID );
    }
    else if ( userID && userID[0] )
        sprintf( target, "http://www.flog.jp/m.php/%s", userID );
    if ( target[0] == NUL )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );
    response2 = (char *)malloc( sz );
    if ( !response2 ) {
        free( response );
        return ( mp );
    }

    strcpy( url, target );
    do {
        MyClip  *newClip_p;

        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        http_get( url, response );

        if ( !response || !(response[0]) )
            break;

        newClip_p = allocateMyClipIfNecessary( &mp, unit, &cnt, num );
        if ( !newClip_p )
            break;
        mp = newClip_p;

        // �u�b�N�}�[�N�𔲂��o��
     // p = strstr( response, "<td align=\"left\" class=\"txt\">" );
        p = strstr( response, " class=\"txt_b\">" );
        q = NULL;
        if ( p ) {
         // p += 30;
            p += 14;
            q = strstr( p, "</table><center><table " );
        }
        while ( p && q && (p < q) ) {
            s = strstr( p, "</table><a " );
            if ( !s )
                s = q;

            // URL
            r = strstr( p, "<a href=\"/comment.php/" );
            if ( !r || (r > s) )
                break;
            p = r + 22;
            r = strchr( p, '"' );
            if ( !r || (r > s) )
                r = strchr( p, ' ' );
            if ( !r || (r > s) )
                r = strchr( p, '>' );
            if ( !r || (r > s) )
                break;
            strncpy( commentURL, p, r - p );
            commentURL[r - p] = NUL;
            p = r + 1;

            // �^�C�g��
            r = strchr( p, '>' );
            if ( !r || (r > s) )
                break;
            p = r + 1;
            r = strstr( p, "</a>" );
            if ( !r || (r > s) )
                break;
            strncpy( mp[num].title, p, r - p );
            mp[num].title[r - p] = NUL;

            replaceString( mp[num].title, "&raquo;-&raquo;", " - " );
            replaceString( mp[num].title, "&raquo;", "��" );

            p = r + 4;

            // �^�O
            mp[num].tags[0] = NUL;
            do {
                r = strstr( p, " class=\"txt_s\">[" );
                if ( !r || (r > s) )
                    break;
                p = r + 16;
                r = strstr( p, "]</a>" ); // 2byte �ڂ� ']' �Ȋ����������㩂�
                if ( !r || (r > s) )      // �͂܂�̂ŁA"</a>" �t���ŕ]������
                    break;

                if ( mp[num].tags[0] )
                    strcat( mp[num].tags, " " );
                len = mp[num].tags[0] ? strlen( mp[num].tags ) : 0;
                strncat( mp[num].tags, p, r - p );
                mp[num].tags[len + (r - p)] = NUL;

                p = r + 5;
            } while ( r );
            if ( p > s )
                break;

            // �R�����gID
            commentID[0] = NUL;
            r = strstr( p, "<a href=\"/comment.php/" );
            if ( r && (r < s) ) {
                p = r + 22;
                r = strchr( p, '"' );
                if ( r && (r < s) ) {
                    strncpy( commentID, p, r - p );
                    commentID[r - p] = NUL;
                    p = r + 1;
                }
            }

            // �R�����g
            r = strstr( p, "<div class=\"comment\">" );
            if ( !r || (r > s) )
                break;
            p += 21;
            r = strstr( p, "\">&nbsp;" );
            if ( !r || (r > s) )
                break;
            p = r + 8;

            r = strstr( p, "&nbsp;(" );
            if ( !r || (r > s) )
                break;
            strncpy( mp[num].comment, p, r - p );
            mp[num].comment[r - p] = NUL;

            /* Flog �̃R�����g�ɂ͉��s���܂܂꓾�� */
            while ( ((p = strchr(mp[num].comment, '\r')) != NULL) ||
                    ((p = strchr(mp[num].comment, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* ���s����菜�� */
            /* Flog �̃R�����g�ɂ� <br> ���܂܂꓾�� */
            while ( (p = strstr( mp[num].comment, "<br>" )) != NULL ) 
                strcpy( p, p + 4 ); /* <br> ����菜�� */

            if ( strchr( mp[num].comment, '&' ) ) {
                replaceString( mp[num].comment, "&quot;",  "\"" );
                replaceString( mp[num].comment, "&lt;",    "<" );
                replaceString( mp[num].comment, "&gt;",    ">" );
                replaceString( mp[num].comment, "&amp;",   "&" );
                replaceString( mp[num].comment, "&raquo;", "��" );
            }
    
            replaceString( mp[num].comment, "&",  "&amp;" );
            replaceString( mp[num].comment, "\"", "&quot;" );
            replaceString( mp[num].comment, "<",  "&lt;" );
            replaceString( mp[num].comment, ">",  "&gt;" );

            p = r + 7;

            // �J�e�S���[
            r = strstr( p, "<a href=\"/cate.php/" );
            if ( !r || (r > s) )
                break;
            p = r + 19;
            r = strstr( p, "title=\"" );
            if ( !r || (r > s) )
                break;
            p = r + 7;
            r = strchr( p, '"' );
            if ( !r || (r > s) )
                break;
            strncpy( category, p, r - p );
            category[r - p] = NUL;

            if ( mp[num].tags[0] )
                strcat( mp[num].tags, " " );
            strcat( mp[num].tags, getFlogGategory( category ) );

            p = r + 1;

            // ���� �����b (�u�N�v�̏�񂪊܂܂�Ȃ��̂ŁA�⊮����K�v������)
            //   �q���g: �u�N�v�̏���
            //               http://www.flog.jp/comment.php/�u�b�N�}�[�NID
            //           �o�R�Ŏ擾�ł���
            r = strstr( p, "<span class=\"txt_s\">" );
            if ( !r || (r > s) ) {
                mp[num].yyyy = yy;
                mp[num].mm   = mm;
                mp[num].dd   = dd;
                mp[num].HH   = HH;
                mp[num].MM   = MM;
                mp[num].SS   = SS;
            }
            else {
                p = r + 20;
                mm = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                dd = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                HH = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                MM = (*p - '0') * 10 + (*(p + 1) - '0');
                p += 3;
                SS = (*p - '0') * 10 + (*(p + 1) - '0');

                mp[num].yyyy = yy; /* �b��l */
                mp[num].mm   = mm;
                mp[num].dd   = dd;
                mp[num].HH   = HH;
                mp[num].MM   = MM;
                mp[num].SS   = SS;

                // �N
                //   http://www.flog.jp/comment.php/�u�b�N�}�[�NID ���擾
                if ( commentID[0] ) {
                    Sleep( 1000 );

                    sprintf( url, "http://www.flog.jp/comment.php/%s",
                             commentID );
                    setTargetURL( url );
                    setUpReceiveBuffer( response2, sz );
                    http_get( url, response2 );

                    if ( response2 && *response2 ) {
                        char    *pp = strstr( response2,
                                              "<br><span class=\"txt_s\">" );
                        if ( pp ) {
                            pp += 24;
                            mp[num].yyyy = atol( pp );
                        }

                        pp = strstr( response2, "<a href=/j.php/" );
                        if ( pp ) {
                            char    *qq;

                            pp += 15;
                            qq = strchr( pp, ' ' );
                            if ( !qq )
                                qq = strchr( pp, '>' );
                            if ( qq ) {
                                strncpy( mp[num].url, pp, qq - pp );
                                mp[num].url[qq - pp] = NUL;
                            }
                        }
                    }
                } 

                p += 2;
            }

            num++;

            p = strstr( p, "</table>" );
            if ( p )
                p += 8;
        }

        // ����
        cont = FALSE;
        p = strstr( response, "\">&nbsp;&nbsp;����&gt;&gt;</a>" );
        if ( p ) {
            while ( (p >= response) && (*p != '/') )
                p--;
            if ( *p == '/' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;
                    sprintf( url, "%s%s", target, page );
                    cont = TRUE;
                    Sleep( 1000 );
                }
            }
        }
    } while ( cont );

    *numOfClips = num;
    free( response2 );
    free( response );

    return ( mp );
}


#ifdef  GET_FLOG_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy
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
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
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
                 "getFlog: Flog �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tFlog����z���o�������e�� OPML �t�@�C���Ƃ��ďo�͂���\n" );
        fprintf( stderr,
                 "    getFlog [-x] -u ���[���A�h���X -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getFlog: get bookmarks from Flog, and output them as "
                 "OPML\n" );
        fprintf( stderr,
                 "    getFlog [-x] -u mailaddress -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* Flog �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getFlog( username, password, NULL, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Flog �̃u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "Flog", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_FLOG_EXE */

/*
 * clip saver <<getBlueDot>>
 *
 *      Blue Dot �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  6 Oct 2006
 *
 * History:
 * $Log: /comm/bookey/getDelicious/getBlueDot.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 17    08/12/01 19:17 Tsujimura543
 * escapeAmpasand() �� escapeAmpersand() �ɕύX (�Ԃ�����C��)
 * 
 * 16    08/07/25 0:36 Tsujimura543
 * private saving �ɑΉ�
 * 
 * 15    08/07/25 0:03 Tsujimura543
 * getBlueDot2() ��ύX�A�C�� (private�Ή��A�^�O���o�����C��)
 * 
 * 14    08/02/25 16:48 Tsujimura543
 * �R�����g���C��
 * 
 * 13    08/02/25 16:40 Tsujimura543
 * bluedot.us �� faves.com �ւ̈ڍs�ɔ����C�������{
 * (����: ���̔łł́A���J�͈͂� Everyone �̂��̂����擾�ł��Ȃ�)
 * 
 * 12    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 11    07/01/17 21:42 Tsujimura543
 * (1) deleteHtmlTags() �� getBlueDot.c ���番���A�Ɨ�������
 * (2) �p�ꃂ�[�h�Ή�
 * (3) �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 10    07/01/11 20:23 Tsujimura543
 * getAllPostsOnBlueDot() �Ń^�C���A�E�g���������Ȃ��Ȃ������Ƃ��m�F
 * (�T�[�o���ŉ��炩�̉��P���s��ꂽ�͗l)
 * 
 * 9     07/01/11 20:17 Tsujimura543
 * ��������������Ainvalid �� OPML �ɂȂ��Ă��܂����肷�邱�Ƃ�����
 * �s��ɉ\�Ȍ���Ώ� 
 * 
 * 8     06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 7     06/10/18 19:41 Tsujimura543
 * �C�ӂ̃��[�U�̃u�b�N�}�[�N���擾�ł���悤�ɂ���
 * 
 * 6     06/10/07 7:21 Tsujimura543
 * �^�C�g���ɉ��s���܂܂��ꍇ�A��菜���悤�ɂ���
 * 
 * 5     06/10/07 5:32 Tsujimura543
 * ���ǁAMy Dots (html �y�[�W)�����ԂɎ擾���ĉ�͂������ʂ�����
 * �u�b�N�}�[�N�����\������悤�ɂ��邱�ƂőΉ����邱�Ƃɂ���
 * 
 * 4     06/10/07 2:20 Tsujimura543
 * �������� fix ���A����A�ʂ̎���l���邱�Ƃɂ���
 * 
 * 3     06/10/07 2:18 Tsujimura543
 * getListOfDatesOnBlueDot() ���g�����@�ł��ʖڂ�����
 *  �� API ���g�킸�ɁAMy Dots �� Web �y�[�W���擾���āAhtml �t�@�C����
 *     ��͂��Ă�����@���̗p���邵����͂Ȃ����� (API �̑��݈Ӗ��Ȃ�)
 * 
 * 2     06/10/07 2:00 Tsujimura543
 * del.icio.us �̏ꍇ�́uhttp������M�҂��^�C���A�E�g���ԁv�𒷂����邱��
 * �Ńu�b�N�}�[�N���������ꍇ�ɂ��Ή��ł������ABlue Dot �̏ꍇ�́A������
 * ���Ԃ�(60�b�ȏ�?)�����肻���ȏꍇ�̓T�[�o�̕�����ڑ���؂��Ă��邱��
 * �������B�ʂ̕��@�őΏ�����K�v������ (����̉ۑ�)
 * 
 * 1     06/10/07 1:08 Tsujimura543
 * �V�K�쐬
 */

#include "myClip.h"
#include "delicious.h"
#include "blueDot.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDelicious/getBlueDot.c 1     09/05/14 3:48 tsupo $";
#endif


char    *
escapeAmpersand( char *p )
{
    char    *s, *t, *u;

    s = strchr( p, '&' );
    while ( s ) {
        t = strchr( s, ';' );
        u = strchr( s, '&' );
        if ( !t || (u && (u < t)) ) {
            char    *pp = s + strlen( s );
            while ( pp > s ) {
                *(pp + 4) = *pp;
                pp--;
            }
            *++s = 'a';
            *++s = 'm';
            *++s = 'p';
            *++s = ';';

            s = strchr( s, '&' );
        }
        else
            break;
    }

    return ( p );
}


/* Blue Dot �� sign in ���� */
int
loginBlueDot(
        const char *username,   // (I)   ���[�U��
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

 // strcpy( url, "https://secure.bluedot.us/signIn" );
    strcpy( url, "https://secure.faves.com/signIn" );
    setTargetURL( url );
    sprintf( request,
             "rUsername=%s&"
             "rPassword=%s&"
             "rememberMe=1&"
             "action=%s",
             username, password,
             encodeURL( "Sign In" ) );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( (strstr( response, "Sign Out" )   != NULL) ||
             (strstr( response, "My Account" ) != NULL)    )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }
    else
        ret = 0;        /* ���O�C�����s */

    free( response );
    free( request  );

    return ( ret );
}

MyClip  *
getBlueDot2(
        const char *userName,   /* (I) ���[�U��                 */
        const char *password,   /* (I) �p�X���[�h               */
        long       *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�� faves��S���擾����(���J�͈͂�
     *  Everyone �ȊO�� faves ���擾����ꍇ�́Apassword �̎w����K�v�B
     *  Everyone �݂̂̎擾�ł����ꍇ�́Apassword �͕s�v)
     */
    MyClip      *mp = NULL;
    char        url[MAX_URLLENGTH];
    char        *request;
    char        *response;
    char        *cookie;
    char        *pi;
    char        *p, *q, *r, *s, *qq;
    BOOL        cont = TRUE;
    int         num  = 0;
    int         cnt  = 0;
    int         unit = 200;
    int         i;
    int         yy, mm, dd;
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    int         y0  = tm->tm_year + 1900;
    int         m0  = tm->tm_mon  + 1;
    int         d0  = tm->tm_mday;
    size_t      sz  = MAX_CONTENT_SIZE * 20;

    static char month[12][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    *numOfClips = 0;

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( mp );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    if ( password && *password ) {
        /* Blue Dot �� login */
        if ( !loginBlueDot( userName, password, cookie ) ) {
            // login ���s
            free( cookie );
            return ( mp );
        }
    }

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        free( cookie );
        return ( mp );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return ( mp );
    }
    pi = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !pi ) {
        free( response );
        free( request );
        free( cookie );
        return ( mp );
    }

 // sprintf( url, "http://bluedot.us/users/%s", userName );
    sprintf( url, "http://faves.com/users/%s", userName );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    do {
        if ( !response || !(response[0]) )
            break;

        // �u�b�N�}�[�N�𔲂��o��
     // p = strstr( response, "<div class=\"dotList\">" );
        p = strstr( response, "<ul class=\"dotList" );
        if ( !p )
            break;
        p += 18;

        do {
            MyClip  *newClip_p;
            newClip_p = allocateMyClipIfNecessary( &mp, unit, &cnt, num );
            if ( !newClip_p )
                break;
            mp = newClip_p;

            q = strstr( p, "<div class=\"t\">" );
            s = strstr( p, "</a></div></li>" );
            if ( !q || !s )
                break;
            p = strchr( q, '>' ) + 1;

            // URL
            q = strstr( p, "<a name=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 10;
            q = strstr( p, " href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 7;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( mp[num].url, p, q - p );
            mp[num].url[q - p] = NUL;

            // �^�C�g��
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( mp[num].title, p, q - p );
            mp[num].title[q - p] = NUL;
            r = utf2sjis( mp[num].title );
            if ( r )
                strcpy( mp[num].title, r );
            else
                utf2sjisEx( mp[num].title );
            /* Blue Dot �̃^�C�g���ɂ͉��s���܂܂꓾�� */
            while ( ((p = strchr(mp[num].title, '\r')) != NULL) ||
                    ((p = strchr(mp[num].title, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* ���s����菜�� */
            escapeAmpersand( mp[num].title );

            // private ���ۂ�
            mp[num].publication = PUB_EVERYONE;
            p = q + 4;
            q = strstr( p, "</em> - " );
            if ( q && (q < s) ) {
                // private
                r = strstr( p, "Not Shared" );
                if ( !r || (r > q) )
                    r = strstr( p, "(Private)" );
                if ( r && (r < q) )
                    mp[num].publication = PUB_PRIVATE;
                p = q + 8;
            }
            else {
                q = strstr( p, "</a> - " );
                if ( !q || (q > s) )
                    break;
                p = q + 7;
            }

            // �N����
            if ( (*p >= '1') && (*p <= '9') ) {
                dd = atol( p );
                while ( (*p >= '0') && (*p <= '9') )
                    p++;
                if ( *p == ' ' )
                    p++;
                if ( !strncmp( p, "days ago", 8 ) ||
                     !strncmp( p, "day ago",  7 )    ) {
                    time_t      tt   = t - dd * 24 * 60 * 60;
                    struct tm   *ttm = localtime( &tt );

                    yy = ttm->tm_year + 1900;
                    mm = ttm->tm_mon  + 1;
                    dd = ttm->tm_mday;
                }
                else {
                    // ����
                    yy = y0;
                    mm = m0;
                    dd = d0;
                }
            }
            else {
                // Aug 28 2006 �`��
                yy = y0;    // �����l (�b��)
                mm = m0;    // �����l (�b��)
                dd = d0;    // �����l (�b��)

                for ( i = 0; i < 12; i++ ) {
                    if ( !strncmp( p, month[i], 3 ) ) {
                        mm = i + 1;
                        break;
                    }
                }

                while ( *p && ((*p <= '0') || (*p > '9')) )
                    p++;
                if ( (*p >= '1') && (*p <= '9') )
                    dd = atol( p );
                while ( (*p >= '0') && (*p <= '9') )
                    p++;
                while ( *p && ((*p <= '0') || (*p > '9')) )
                    p++;
                if ( (*p >= '1') && (*p <= '9') )
                    yy = atol( p );
            }

            mp[num].yyyy = yy;
            mp[num].mm   = mm;
            mp[num].dd   = dd;
            mp[num].HH   = 0;
            mp[num].MM   = 0;
            mp[num].SS   = 0;

            qq = strstr( p, "=tag%" );
            q = strstr( p, "/tag/" );
            r = strstr( p, "<div class=\"note\">" );
            if ( qq && q && r && (qq < q) && (qq < r) )
                q = qq;
            if ( q && r && (q < s) && (q < r) && (r < s) ) {
                // �L�[���[�h (�^�O)
                int len;

                p = q + 5;
                do {
                    q = strstr( p, "\">" );
                    if ( !q || (q > r) )
                        break;
                    p = q + 2;
                    q = strstr( p, "</a>" );
                    if ( !q || (q > r) )
                        break;

                    if ( mp[num].tags[0] == NUL )
                        len = 0;
                    else {
                        strcat( mp[num].tags, " " );
                        len = strlen( mp[num].tags );
                    }
                    strncat( mp[num].tags, p, q - p );
                    mp[num].tags[len + (q - p)] = NUL;

                    p = q + 4;
                } while ( p < r );
                if ( mp[num].tags[0] ) {
                    r = utf2sjis( mp[num].tags );
                    if ( r )
                        strcpy( mp[num].tags, r );
                    else
                        utf2sjisEx( mp[num].tags );
                    escapeAmpersand( mp[num].tags );
                }
            }

            // �R�����g
            q = strstr( p, "<div class=\"note\">" );
            if ( !q || (q > s) )
                break;
            p = q + 18;
            q = strstr( p, "</div>" );
            if ( !q || (q > s) )
                break;
            strncpy( mp[num].comment, p, q - p );
            mp[num].comment[q - p] = NUL;
            deleteHtmlTags( mp[num].comment );
            r = utf2sjis( mp[num].comment );
            if ( r )
                strcpy( mp[num].comment, r );
            else
                utf2sjisEx( mp[num].comment );
            escapeAmpersand( mp[num].comment );

            p = s + 24;

            num++;
        } while ( p && *p );

        // ����
        cont = FALSE;
        p = strstr( response, "<input name=\"pi\"" );
        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( pi, p, q - p );
                    pi[q - p] = NUL;

                    Sleep( 1000 );

                    setTargetURL( url );
                    sprintf( request,
                             "pi=%s&",
                             encodeURL( pi ) );
                    sprintf( request + strlen( request ),
                             "n=%s",
                             encodeURL( "NEXT PAGE" ) );
                    setUpReceiveBuffer( response, sz );
                    http_postEx( url, "application/x-www-form-urlencoded",
                                 request, response, cookie );
                    cont = TRUE;
                }
            }
        }
    } while ( cont );

    *numOfClips = num;

    free( pi );
    free( response );
    free( request );
    free( cookie );

    return ( mp );
}


MyClip  *
getBlueDot(
        const char *username,   /* (I)   ���[�U��         */
        const char *password,   /* (I)   �p�X���[�h       */
        int        *numOfClips  /* (I/O) �u�b�N�}�[�N���� */
    )
{
    long            n, num, numOfPosts = 0, i;
    DELICIOUS_POSTS *posts;
    MyClip          *mp = NULL;
    char            *s, *t;

    n = *numOfClips;
    *numOfClips = 0;

    /* Blue Dot �̃u�b�N�}�[�N���擾 */
    if ( n == 0 )
        num = getNumberOfBookmarksOnBlueDot( username, password );
    else
        num = n;
    if ( num <= 0 )
        return ( mp );
    Sleep( 1000 );

    numOfPosts = num;
    posts = (DELICIOUS_POSTS *)
                malloc( sizeof ( DELICIOUS_POSTS ) * numOfPosts );
    if ( !posts )
        return ( mp );
    memset( posts, 0x00, sizeof ( DELICIOUS_POSTS ) * numOfPosts );

    n = 0;
    if ( password && *password ) {
#if 0
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT * (numOfPosts / 100) );
                        // �u�b�N�}�[�N�����ɔ�Ⴕ���^�C���A�E�g���Ԃ�ݒ�
#endif
        n = getAllPostsOnBlueDot( username, password,
                                  NULL,
                                  &numOfPosts, posts );
#if 0
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT ); // �f�t�H���g�l�ɖ߂��Ă���
#endif
    }
    if ( n <= 0 ) {
        // �ʂ̕��@�Ńu�b�N�}�[�N�擾�����݂�
        mp = getBlueDot2( username, password, &n );
    }
    else {
        mp = (MyClip *)malloc( sizeof ( MyClip ) * n );
        if ( !mp ) {
            free( posts );
            return ( mp );
        }

        for ( i = 0; i < n; i++ ) {
            strcpy( mp[i].title,   posts[i].description );
            escapeAmpersand( mp[i].title );

            strcpy( mp[i].tags,    posts[i].tag );
            escapeAmpersand( mp[i].tags );

            strcpy( mp[i].url,     posts[i].href );
            strcpy( mp[i].comment, posts[i].extended );

            s = mp[i].comment;
            while ( ((t = strchr( s, '\n' )) != NULL) ||
                    ((t = strchr( s, '\r' )) != NULL)    ) {
                if ( (*(t + 1) == '\r') || (*(t + 1) == '\n') )
                    strcpy( t, t + 1 );
                *t = ' ';
            }
            escapeAmpersand( mp[i].comment );

            mp[i].yyyy = atol( posts[i].dateTime );
            mp[i].mm   = (posts[i].dateTime[5]  - '0') * 10 +
                            (posts[i].dateTime[6]  - '0');
            mp[i].dd   = (posts[i].dateTime[8]  - '0') * 10 +
                            (posts[i].dateTime[9]  - '0');
            mp[i].HH   = (posts[i].dateTime[11] - '0') * 10 +
                            (posts[i].dateTime[12] - '0');
            mp[i].MM   = (posts[i].dateTime[14] - '0') * 10 +
                            (posts[i].dateTime[15] - '0');
            mp[i].SS   = (posts[i].dateTime[17] - '0') * 10 +
                            (posts[i].dateTime[18] - '0');

            if ( posts[i].shared == FALSE )
                mp[i].publication = PUB_PRIVATE;
        }
    }
 
    *numOfClips = n;
    free( posts );

    return ( mp );
}

#ifdef  GET_BLUEDOT_EXE
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
        fprintf( stderr, "getBlueDot: Blue Dot �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "    getBlueDot [-x] -u Blue Dot ���[�U�� "
                 "-p Blue Dot �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getBlueDot: get bookmarks from Blue Dot, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getBlueDot [-x] -u username "
                 "-p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password, &useProxy );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* Blue Dot �o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getBlueDot( username, password, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  Blue Dot ���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "Blue Dot", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLUEDOT_EXE */

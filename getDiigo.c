/*
 * clip saver <<getDiigo>>
 *
 *      Diigo �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  25 Jul 2008
 *
 * $Log: /comm/bookey/getDiigo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/12/02 19:14 Tsujimura543
 * �g���Ă��Ȃ��ϐ����R�����g�A�E�g
 * 
 * 3     08/07/26 0:36 Tsujimura543
 * �\�[�X�𐮗�
 * 
 * 2     08/07/26 0:18 Tsujimura543
 * �^�O�� decodeContents() ����悤�ɂ���
 * 
 * 1     08/07/25 21:22 Tsujimura543
 * �V�K�쐬 (�b��ŁB����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDiigo.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   100


char    *skipInnerComment( char *t, const char *itemName )
{
    int     cnt = 0;
    int     len = strlen( itemName );
    char    *u = t;

    t += len;
    if ( *t == '[' ) {
        cnt++;
        t++;
        while ( *t ) {
            if ( *t == '[' )
                cnt++;
            else if ( *t == ']' ) {
                cnt--;
                if ( cnt == 0 ) {
                    t++;
                    if ( *t == ',' )
                        t++;
                    strcpy( u, t );
                    t = u;
                    break;
                }
            }

            t++;
        }
    }

    return ( t );
}

char    *deleteInnerComment( char *s )
{
    char    *t = s;

    while ( *t ) {
        if ( *t == '"' ) {
            if ( !strncmp( t, "\"comments\":", 11 ) )
                skipInnerComment( t, "\"comments\":" );
            else if ( !strncmp( t, "\"annotations\":", 14 ) )
                skipInnerComment( t, "\"annotations\":" );
        }

        t++;
    }

    return ( s );
}

int
_getDiigo(
        const char *userName,
        const char *password,
        MyClip     **mp,
        char       *response,
        size_t     sz
    )
{
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s, *t, *u;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    strcpy( target, "http://api2.diigo.com/bookmarks" );
    sprintf( url,
             "%s?users=%s&filter=all&start=%d&rows=%d",
             target, userName, cnt, NUM_OF_CLIPS_PER_PAGE );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        http_getBASIC( url, userName, password, response );

        if ( !response || !(response[0]) )
            break;

        // �������ȒP�ɂ��邽�߁Acomment �� anotation ���̂Ă�
        deleteInnerComment( response );

        // �u�b�N�}�[�N�𔲂��o��
        p = strchr( response, '[' );
        if ( !p )
            break;
        p++;

        do {
            if ( mp ) {
                MyClip  *np;
                np = allocateMyClipIfNecessary( mp, unit, &cnt, num );
                if ( !np )
                    break;
                *mp = np;
            }

            q = strchr( p, '{' );
            if ( !q )
                break;
            p = q + 1;

            s = strstr( p, "}," );
            if ( !s )
                s = strchr( p, '}' );
            if ( !s )
                break;
 
            // �^�C�g��
            q = strstr( p, "\"title\":\"" );
            if ( !q || (q > s) )
                break;
            q += 9;
            r = strchr( q, '"' );
            if ( !r || (r > s) )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;
            decodeContents( tmp );
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );
            if ( mp )
                strcpy( (*mp)[num].title, tmp );

            // URL
            q = strstr( p, "\"url\":\"" );
            if ( !q || (q > s) )
                break;
            q += 7;
            r = strchr( q, '"' );
            if ( !r || (r > s) )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
            while ( ( r = strstr( tmp, "\\/" ) ) != NULL )
                strcpy( r, r + 1 );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );

            // ����
            q = strstr( p, "\"desc\":\"" );
            if ( !q || (q > s) )
                break;
            q += 8;
            r = strchr( q, '"' );
            if ( !r || (r > s) )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;
            decodeContents( tmp );
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( ((r = strchr(tmp, '\r')) != NULL) ||
                    ((r = strchr(tmp, '\n')) != NULL)    )
                strcpy( r, r + 1 ); /* ���s����菜�� */
            if ( mp )
                strcpy( (*mp)[num].comment, tmp );

            // �^�O
            q = strstr( p, "\"tags\":\"" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                q += 8;
                u = strchr( q, '"' );
                if ( u && (u < s) ) {
                    do {
                        t = strchr( q, ',' );
                        if ( !t || (t > u) ) {
                            if ( tmp[0] == NUL )
                                len = 0;
                            else {
                                strcat( tmp, " " );
                                len = strlen( tmp );
                            }
                            strncat( tmp, q, u - q );
                            tmp[len + (u - q)] = NUL;
                            break;
                        }

                        if ( tmp[0] == NUL )
                            len = 0;
                        else {
                            strcat( tmp, " " );
                            len = strlen( tmp );
                        }
                        strncat( tmp, q, t - q );
                        tmp[len + (t - q)] = NUL;

                        q = t + 1;
                    } while ( q < u );

                    if ( tmp[0] ) {
                        decodeContents( tmp );
                        r = utf2sjis( tmp );
                        if ( r )
                            strcpy( tmp, r );
                    }
                    if ( mp )
                        strcpy( (*mp)[num].tags, tmp );
                }
            }

            // ���J�E����J
            q = strstr( p, "\"shared\":\"" );
            if ( q && (q < s) ) {
                q += 10;
                r = strchr( q, '"' );
                if ( r && (r < s) ) {
                    strncpy( tmp, q, r - q );
                    tmp[r - q] = NUL;
                    if ( strcmpi( tmp, "yes" ) != 0 )
                        if ( mp )
                            (*mp)[num].publication = PUB_PRIVATE;
                }
            }

            // �N���������b
            q = strstr( p, "\"created_at\":\"" );
            if ( !q || (q > s) )
                q = strstr( p, "\"updated_at\":\"" );
            if ( !q || (q > s) )
                break;
            q += 14;
            r = strchr( q, '"' );
            if ( !r || (r > s) )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;

            if ( mp )
                getDateTimeFromDateString( tmp,
                                           &((*mp)[num].yyyy),
                                           &((*mp)[num].mm),
                                           &((*mp)[num].dd),
                                           &((*mp)[num].HH),
                                           &((*mp)[num].MM),
                                           &((*mp)[num].SS) );

            // �R�����g
            // �A�m�e�[�V����


            p = s + 1;
            num++;
        } while ( p && *p );

        // ����
        cont = FALSE;
        if ( num == NUM_OF_CLIPS_PER_PAGE ) {
            cont = TRUE;
            cnt++;
            sprintf( url,
                     "%s?users=%s&filter=all&start=%d&rows=%d",
                     target, userName, num, NUM_OF_CLIPS_PER_PAGE );
            Sleep( 1000 );
        }
    } while ( cont );

    return ( num );
}

MyClip  *
getDiigo(
        const char *userName,   /* (I) ���[�U��                       */
        const char *password,   /* (I) �p�X���[�h                     */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�̃u�b�N�}�[�N��S���擾����
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
 // int     fd;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    int     num = 0;

    *numOfClips = 0;

    if ( !password || !(*password) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0] = NUL;

 // fd = fileno( stderr );

    // �u�b�N�}�[�N�̎擾
    num = _getDiigo( userName, password, &mp, response, sz );
    *numOfClips = num;

    free( response );

    return ( mp );
}


#ifdef  GET_DIIGO_EXE
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
                 "getDiigo: Diigo �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tDiigo ����z���o�������e�� OPML �t�@�C���Ƃ��ďo��"
                 "����\n" );
        fprintf( stderr,
                 "    getDiigo [-x] -u ���[�U�� -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getDiigo: get bookmarks from Diigo, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getDiigo [-x] -u username -p password\n" );
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

    /* Diigo �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getDiigo( username, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Diigo �̃u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "JoltMark", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_DIIGO_EXE */

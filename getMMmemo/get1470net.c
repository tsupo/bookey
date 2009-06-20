/*
 * clip saver <<get1470net>>
 *
 *      1470.net���j���[�A���� �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  25 Aug 2006
 *
 * $Log: /comm/bookey/getMMmemo/get1470net.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 12    08/12/02 19:28 Tsujimura543
 * ����������Y��Ώ�
 * 
 * 11    08/11/25 19:26 Tsujimura543
 * �u�b�N�}�[�N�̎擾���ł��Ȃ��Ȃ��Ă������Ƃ������������߁A�Ώ�����
 * 
 * 10    07/07/02 17:28 Tsujimura543
 * getFeedOn1470net() �� void ���� BOOL �ɕύX
 * 
 * 9     07/06/29 22:27 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 8     07/06/29 22:26 Tsujimura543
 * (1) 1470.net �̃f�U�C���ύX�ɑΉ� (�X�N���C�s���O���������܂������Ȃ�
 *     �Ȃ��Ă��܂��Ă���)
 * (2) �����擾API �� 404 Not Found ��Ԃ��Ă���ꍇ�́A�����ɏ�����ł�
 *     �؂�悤�ɂ���
 * 
 * 7     07/01/18 15:15 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 6     07/01/17 17:54 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 5     06/11/17 14:03 Tsujimura543
 *  �u�]���v�� title �ɖ��ߍ���ŋL�^�������(MM/Memo�݊�����)����߁A
 * MyClip �\���̂� evaluation �ɋL����������Ɉڍs
 * 
 * 4     06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() �𓱓��BMyClip �\���̊i�[�̈�m�ۏ�����
 * ���ʊ֐������Ă݂�
 * 
 * 3     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 2a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 2     06/08/26 0:06 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     06/08/25 19:48 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getMMmemo/get1470net.c 1     09/05/14 3:48 tsupo $";
#endif

#define MAX_1470NET_MEMO_PER_BLOCK  200

BOOL
getFeedOn1470net(
        const char *userID,
        const char *url,
        MyClip     **mp,
        int        *num,
        int        *cnt,
        int        unit
    )
{
    char        entryListURL[MAX_URLLENGTH];
    char        entryID[32];
    const char  *p, *q, *r;
    char        *response;
    int         sz = MAX_CONTENT_SIZE * 20;
    int         yyyy, mm, dd, HH, MM, SS;
    BOOL        ret = FALSE;

    entryListURL[0] = NUL;
    p = strstr( url, "/2" );
    if ( p ) {
        int yyyy = 0, mm = 0, dd = 0;

        yyyy = atol( ++p );
        if ( yyyy >= 1970 ) {
            while ( *p && (*p != '/') )
                p++;
            if ( *p == '/' ) {
                if ( *++p == '0' )
                    p++;
                mm = atol( p );
            }
            while ( *p && (*p != '/') )
                p++;
            if ( *p == '/' ) {
                if ( *++p == '0' )
                    p++;
                dd = atol( p );
            }
        }

        if ( (yyyy > 0) && (mm > 0) && (dd > 0) )
            sprintf( entryListURL,
                     "http://1470.net/api/memo/daily?"
                     "userName=%s&"
                     "day=%04d-%02d-%02d",
                     userID, yyyy, mm, dd );
    }
    if ( !(entryListURL[0]) )
        sprintf( entryListURL,
                 "http://1470.net/api/memo/daily?"
                 "userName=%s",
                 userID );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    // ���Y�N�����̃G���g��(����)�ꗗ���擾
    Sleep( 2000 );
    setUpReceiveBuffer( response, sz );
    http_get( entryListURL, response );
    if ( *response ) {
        // �e�����̏������Ɏ擾
        char    entryURL[MAX_URLLENGTH];
        char    *response2;
        int     len;
        int     eval;

        if ( strstr(response,
                    "<html><head>\n<title>404 Not Found</title>\n</head>") ) {
            free( response );
            return ( ret );
        }

        response2 = (char *)malloc( sz );
        if ( !response2 ) {
            free( response );
            return ( ret );
        }

        p = response;
        if ( strchr( p, '{' ) )
            ret = TRUE;
        while ( *p ) {
            q = strstr( p, "{\"id\" : " );
            if ( !q )
                break;
            q += 8;
            r = strchr( q, ',' );
            if ( !r )
                break;

            strncpy( entryID, q, r - q );
            entryID[r - q] = NUL;

            // ���Y�������擾
            Sleep( 2000 );
            sprintf( entryURL,
                     "http://1470.net/api/memo/%s",
                     entryID );
            setUpReceiveBuffer( response2, sz );
            http_get( entryURL, response2 );
            if ( *response2 ) {
                char    *s, *t, *u;
                MyClip  *newClip_p;

                newClip_p = allocateMyClipIfNecessary( mp, unit, cnt, *num );
                if ( !newClip_p )
                    break;
                *mp = newClip_p;

                // �^�C�g��
                s = response2;
                t = strstr( s, "\"title\" : \"" );
                if ( !t )
                    break;
                s = t + 11;
                t = strstr( s, "\"," );
                if ( !t )
                    break;
                strncpy( ((*mp)[*num]).title, s, t - s );
                ((*mp)[*num]).title[t - s] = NUL;
                s = utf2sjis( ((*mp)[*num]).title );
                if ( s )
                    strcpy( ((*mp)[*num]).title, decodeString( s ) );

                s = t + 2;

                // �R�����g
                ((*mp)[*num]).comment[0] = NUL;
                t = strstr( s, "\"comment\" : \"" );
                if ( t ) {
                    s = t + 11;
                    t = strstr( s, "\"," );
                    if ( t ) {
                        len = t - s;
                        if ( len >= MAX_DESCRIPTION_LEN ) {
                            /* ���ӂꂽ����؂�̂Ă� */
                            char    *temp = (char *)malloc( len + 1 );
                            if ( temp ) {
                                strncpy( temp, s, len );
                                temp[len] = NUL;

                                strcpy( ((*mp)[*num]).comment,
                                        justify( temp,
                                                 MAX_DESCRIPTION_LEN - 2 ) );

                                free( temp );
                            }
                        }
                        else if ( len > 0 ) {
                            strncpy( ((*mp)[*num]).comment, s, len );
                            ((*mp)[*num]).comment[len] = NUL;
                        }

                        if ( len > 0 ) {
                            /* 1470.net���j���[�A���ł̃R�����g�ɂ� <br /> */
                            /* ���܂܂꓾��                                */
                            while ( (u = strstr( ((*mp)[*num]).comment,
                                                 "<br />"         )) != NULL )
                                strcpy( u, u + 6 ); /* <br /> ����菜�� */

                            s = utf2sjis( ((*mp)[*num]).comment );
                            if ( s )
                                strcpy( ((*mp)[*num]).comment,
                                        decodeString( s ) );
                        }

                        s = t + 2;
                    }
                }

                // �]��
                eval = 0;
                t = strstr( s, "\"eval\" : " );
                if ( t ) {
                    t += 9;
                    if ( (*t >= '0') && (*t <= '9') ) {
                        eval = atol( t );
                        if ( eval > 0 ) {
#ifdef  OLD_FASHIONED
                            // �^�C�g���̓��ɕ]���𖄂ߍ���
                            char    tmp[4096];

                            sprintf( tmp,
                                     "(%d)�w%s�x",
                                     eval, ((*mp)[*num]).title );
                            strcpy( ((*mp)[*num]).title, tmp );
#else
                            // �u�]���v�� ((*mp)[*num]).evaluation �Ɋi�[����
                            ((*mp)[*num]).evaluation = eval;
#endif
                        }
                    }

                    s = t + 1;
                }

                // �^�O
                ((*mp)[*num]).tags[0] = NUL;
                t = strstr( s, "\"tags\" : [" );
                if ( t ) {
                    s = t + 10;
                    t = strstr( s, "]," );
                    if ( t ) {
                        strncpy( ((*mp)[*num]).tags, s, t - s );
                        ((*mp)[*num]).tags[t - s] = NUL;
                        while ( (u = strstr( ((*mp)[*num]).tags,
                                             "\", \"")           ) != NULL ) {
                            *u = ' ';
                            strcpy( u + 1, u + 4 );
                        }
                        u = ((*mp)[*num]).tags;
                        strcpy( u, u + 1 );
                        u[strlen(u) - 1] = NUL;
                        s = utf2sjis( ((*mp)[*num]).tags );
                        if ( s )
                            strcpy( ((*mp)[*num]).tags, decodeString( s ) );

                        s = t + 2;
                    }
                }

                // URL
                t = strstr( s, "\"uri\" : [{\"url\" : \"" );
                if ( !t )
                    break;
                s = t + 19;
                t = strstr( s, "\"," );
                if ( !t )
                    break;
                strncpy( ((*mp)[*num]).url, s, t - s );
                ((*mp)[*num]).url[t - s] = NUL;

                s = t + 2;

                // �^�C���X�^���v (�o�^�����ƍŏI�ύX���������邪�A�o�^������
                // �����擾����)
                t = strstr( s, "\"rgdt\" : \"" );
                if ( !t )
                    break;
                t += 10;

                yyyy = mm = dd = HH = MM = SS = 0;
                yyyy = atol( t );
                if ( yyyy >= 1970 ) {
                    while ( *t && (*t != '-') )
                        t++;
                    if ( *t == '-' ) {
                        if ( *++t == '0' )
                            t++;
                        mm = atol( t );
                    }
                    while ( *t && (*t != '-') )
                        t++;
                    if ( *t == '-' ) {
                        if ( *++t == '0' )
                            t++;
                        dd = atol( t );
                    }
                    while ( *t && (*t != ' ') )
                        t++;
                    if ( *t == ' ' ) {
                        if ( *++t == '0' )
                            t++;
                        HH = atol( t );
                    }
                    while ( *t && (*t != ':') )
                        t++;
                    if ( *t == ':' ) {
                        if ( *++t == '0' )
                            t++;
                        MM = atol( t );
                    }
                    while ( *t && (*t != ':') )
                        t++;
                    if ( *t == ':' ) {
                        if ( *++t == '0' )
                            t++;
                        SS = atol( t );
                    }
                }

                ((*mp)[*num]).yyyy = yyyy;
                ((*mp)[*num]).mm   = mm;
                ((*mp)[*num]).dd   = dd;
                ((*mp)[*num]).HH   = HH;
                ((*mp)[*num]).MM   = MM;
                ((*mp)[*num]).SS   = SS;

                (*num)++;
                ret = TRUE;
            }

            p = r + 1;
        }

        free( response2 );
    }
    free( response );

    return ( ret );
}


MyClip  *
get1470net(
        const char *username,   /* (I) TypeKey�F�ؗp���[�U��   */
        const char *password,   /* (I) TypeKey�F�ؗp�p�X���[�h */
        const char *username2,  /* (I) �͂ĂȔF�ؗp���[�U��    */
        const char *password2,  /* (I) �͂ĂȔF�ؗp�p�X���[�h  */
        AUTH_TYPE  authType,    /* (I) �F�؃^�C�v              */
        int        *numOfClips  /* (O) �u�b�N�}�[�N��          */
    )
{
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    char    url2[MAX_URLLENGTH];
    char    userID[32];
    char    *response;
    char    *p, *q, *r;
    char    *pp;
    int     num     = 0;
    int     cnt     = 0;
    int     unit    = MAX_1470NET_MEMO_PER_BLOCK;
    int     sz      = MAX_CONTENT_SIZE * 20;
    char    *cookie = NULL;
    int     fd;
    int     ret;

    *numOfClips = 0;
    target[0]   = NUL;
    userID[0]   = NUL;

    fd = fileno( stderr );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "�������̊m�ۂɎ��s���܂���\n"
                    : "memory exhausted.\n",
                   stderr );
        return ( mp );
    }
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* 1470.net �Ƀ��O�C�� */
    ret = login1470net( username, password, username2, password2, authType,
                        cookie, userID );
    if ( ret == 0 ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "1470.net �ւ� login �Ɏ��s���܂���\n"
                    : "1470.net: login failed.\n",
                   stderr );
        free( cookie );
        return ( mp );  // ���O�C�����s
    }

    response = (char *)malloc( sz );
    if ( !response ) {
        free( cookie );
        return ( mp );
    }

    // �}�C�y�[�W(�������� Feed ���擾)
    //  http://1470.net/redirect/user/index (�� http://1470.net/user/���[�U��)
    strcpy( url, "http://1470.net/redirect/user/index" );
    do {
        Sleep( 2000 );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( !(*response) )
            break;

        // API �o�R�œ��Y�N�����̃G���g���ꗗ���擾
        if ( !getFeedOn1470net( userID, url, &mp, &num, &cnt, unit ) )
            break;

        // ���� (�ߋ������֑k��)
        p = strstr( response, "<div class=\"pageNavigationArea\">" );
        if ( !p )
            break;
        p += 32;
        pp = strstr( p, "<div class=\"pageNavigationArea\">" );
        if ( pp )
            p = pp + 32;
        else {
            pp = strstr( p, "</div>" );
            if ( pp ) {
                while ( pp > p ) {
                    if ( *pp == '<' ) {
                        if ( !strncmp( pp + 1, "a href=\"", 8 ) ) {
                            p = pp;
                            break;
                        }
                    }
                    pp--;
                }
            }
        }

        q = strstr( p, "<a href=\"" );
        r = strchr( p, '|' );
        if ( !r )
            r = strchr( p, '"' );
        if ( !q || (q > r) )
            break;
        q += 9;
        r = strchr( q, '"' );
        if ( !r )
            break;
        strcpy( url2, "http://1470.net" );
        strncat( url2, q, r - q );
        url2[15 + (r - q)] = NUL;

        if ( !strcmp( url2, url ) )
            break;
        strcpy( url, url2 );
    } while ( *response );

    *numOfClips = num;
    free( response );
    free( cookie );

    return ( mp );
}

#ifdef  GET_1470NET_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        char      *username2,
        char      *password2,
        AUTH_TYPE *authType,
        BOOL      *useProxy
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
        fprintf( stderr, "get1470net: 1470net �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
          "\t1470.net ����z���o�������e�� OPML �t�@�C���Ƃ��ďo�͂���\n");
        fprintf( stderr,
             "    get1470net [-x] -u TypeKey���[�U�� -p TypeKey�p�X���[�h\n");
        fprintf( stderr,
             "    get1470net [-x] -U �͂Ă�ID -P �͂Ăȃp�X���[�h\n" );
        fprintf( stderr,
             "    get1470net [-x] -a{T|H} -u TypeKey���[�U�� -p TypeKey�p�X"
             "���[�h\n               -U �͂Ă�ID -P �͂Ăȃp�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
        fprintf( stderr,
            "\t-aT: �܂� TypeKey �F�؂ł̃A�N�Z�X�������A���s�����ꍇ�͂͂Ă�"
            "�F�؂ł̃A�N�Z�X�����݂�\n" );
        fprintf( stderr,
            "\t-aH: �܂��͂ĂȔF�؂ł̃A�N�Z�X�������A���s�����ꍇ�� TypeKey "
            "�F�؂ł̃A�N�Z�X�����݂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "get1470net: get bookmarks from 1470.net, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    get1470net [-x] -u TypekeyID -p TypeKeyPassword\n" );
        fprintf( stderr,
             "    get1470net [-x] -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "    get1470net [-x] -a{T|H} -u TypekeyID -p TypeKeyPassword\n"
             "               -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "      TypekeyID: ID for TypeKey authentication\n"
             "      TypeKeyPassword: password for TypeKey authentication\n" );
        fprintf( stderr,
             "      hatenaID: ID for Hatena authentication\n"
             "      hatenaPassword: password for Hatena authentication\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
        fprintf( stderr,
            "\t-aT: Use 'TypeKey' authentication first. If 'TypeKey' failure,"
            "\n\t\tthen try 'Hatena' authentication.\n" );
        fprintf( stderr,
            "\t-aH: Use 'Hatena' authentication first. If 'Hatena' falure,\n"
            "\t\tthen try 'TypeKey' authentication.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL        useProxy = FALSE;
    char        username[MAX_USERIDLEN];
    char        password[MAX_PASSWDLEN];
    char        username2[MAX_USERIDLEN];
    char        password2[MAX_PASSWDLEN];
    AUTH_TYPE   authType = AK_TYPEKEY; /* default */
    int         numOfClips = 0;
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
                  &authType, &useProxy );

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

    /* 1470.net �ɓo�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = get1470net( username,  password,
                     username2, password2,
                     authType,
                     &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "1470.net", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_1470NET_EXE */

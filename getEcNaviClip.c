/*
 * clip saver <<getEcNaviClip>>
 *
 *      Buzzurl �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  30 Jun 2006 / 11 Jan 2007
 *
 * $Log: /comm/bookey/getEcNaviClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 25    07/10/05 3:03 Tsujimura543
 * BBAuth �o�R�ł̃��O�C��������Ғʂ�u�b�N�}�[�N�̎擾���ł��邱�Ƃ��m�F
 * 
 * 24    07/10/05 2:45 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�Ή� (���O�C���ɂ͐�������悤�ɂȂ������A���̌�
 * �̏������܂��s���S)
 * 
 * 23    07/09/19 21:38 Tsujimura543
 * getEcNaviClip() ���C���B *uID �� NUL �̂Ƃ��� target ���󕶎���̂܂�
 * �ɂ��Ă����悤�ɂ���
 * 
 * 22    07/09/14 23:21 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�Ή� (�܂��r��)
 * 
 * 21    07/09/10 16:58 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 20    07/09/10 15:48 Tsujimura543
 * _getEcNaviClip() ���C���B Buzzurl �� html �t�H�[�}�b�g���ς����
 * �̂������ŃR�����g�ƃ^�O���擾�ł��Ȃ��Ȃ��Ă��܂��Ă������߁A�C
 * �������{����
 * 
 * 19    07/08/24 1:38 Tsujimura543
 * Buzzurl �̃g�b�v�y�[�W�̃f�U�C���ύX�ɔ����C��
 * 
 * 18    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 17    07/01/19 19:52 Tsujimura543
 * _getEcNaviClip() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 16    07/01/17 21:45 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή�
 * (2) �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 15    07/01/11 17:17 Tsujimura543
 * �u�R�����g�v�Ɋ܂܂�� &nbsp; ����������悤�ɂ���
 * 
 * 14    07/01/11 15:47 Tsujimura543
 * (1) �R�����g�̑O�ɗ]���ȋ󔒂��c��Ȃ��悤�ɏC��
 * (2) �^�C�g���������������邱�Ƃ����錻�ۂɑΏ�
 * 
 * 13    07/01/11 15:24 Tsujimura543
 * �|�C���^�v�Z�����̈ꕔ���C��
 * 
 * 12    07/01/11 15:06 Tsujimura543
 * �]���ȃR�����g���폜
 * 
 * 11    07/01/11 15:04 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 10    06/12/07 16:44 Tsujimura543
 * getDateTimeFromDateString() �𓱓����A�������̉�͂��ς˂邱�Ƃɂ���
 * 
 * 9     06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 8     06/10/10 16:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�� Web�y�[�W�� charSet �� EUC-JP ���� UTF-8 ��
 * �ύX���ꂽ�̂ɔ����C�������{
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
 * 4     06/08/18 14:10 Tsujimura543
 * getEcNaviClipUserID() �̑�3������ǉ� (cookie ���Ăяo�����ł��Q�Ɖ\
 * �ɂ��邽��)
 * 
 * 3     06/08/18 11:46 Tsujimura543
 * EC�i�r�l�C�j���[�X�� html �\�[�X�̃t�H�[�}�b�g�ύX�ɔ����C�������{
 * 
 * 2     06/07/21 20:51 Tsujimura543
 * EC�i�r�l�C�j���[�X�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤��
 * ����)
 * 
 * 1     06/06/30 19:42 Tsujimura543
 * �ŏ��̔�(����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getEcNaviClip.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif


/* Buzzurl �̋L�Җ����擾���� */
char    *
getEcNaviClipUserID(
    const char *userName,
    const char *password,
    AUTH_TYPE  authType,
    char       *cookie,
    size_t     *cookieSize )
{
    Thread static char  userID[MAX_USERIDLEN];
    char                *response;
    char                url[MAX_URLLENGTH];
    size_t              sz  = MAX_CONTENT_SIZE * 20;
    int                 ret = 0;

    userID[0] = NUL;

    /* Buzzurl �� login */
    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        // Yahoo! Japan ID �� Buzzurl �Ƀ��O�C��
        ret = loginEcNaviOnBBAuth( userName, password, cookie, cookieSize );
    }
    else {
        // Buzzurl �Ƀ��O�C��
        ret = loginEcNavi( userName, password, cookie );
    }

    if ( !ret ) {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Buzzurl �ւ� login �Ɏ��s���܂���\n"
                    : "Buzzurl: login failed.\n",
                   stderr );
        return ( userID );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( userID );

    strcpy( url, "http://buzzurl.jp/" );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    /* Buzzurl �g�b�v�y�[�W����L�Җ����擾 */
    if ( response && *response ) {
        char    *p = strstr( response, sjis2utf("\">�}�C�y�[�W</a>") );

        if ( !p ) {
            p = strstr(response, sjis2utf("<span>�悤����<span><a href=\""));
            if ( p ) {
                p += 29;
                while ( *p && (*p != '"') )
                    p++;
                if ( *p && (*p == '"' ) )
                    p++;
                else
                    p = NULL;
            }
        }

        if ( p ) {
            while ( (p > response) && (*p != '/') )
                p--;
            if ( *p == '/' ) {
                if ( !strncmp( p - 3, "/yj/", 4 ) )
                    p -= 3;
                p++;
            }
            else
                p = NULL;
        }

        if ( p ) {
            char    *q = strchr( p, '"' );
            if ( q ) {
                strncpy( userID, p, q - p );
                userID[q - p] = NUL;
            }
        }
    }

    free( response );

    return ( userID );
}

int
_getEcNaviClip(
        const char *target,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    strcpy( url, target );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );
        if ( !response || !(response[0]) )
            break;

        if ( *total == 0 ) {
            // �S���ŉ������邩�A�O�����Ē��ׂĂ���
            p = strstr( response, sjis2utf("����") );
            if ( p ) {
                while ( *--p && ((*p >= '0') && (*p <= '9')) )
                    if ( p <= response )
                        break;
                if ( *++p ) {
                    if ( *p == '0' )
                        p++;
                    *total = atol( p );
                }
            }
            else {
                char    tmp[BUFSIZ];

                sprintf( tmp, "<td><a href=\"%s\">", target + 21 );
                p = strstr( response, tmp );
                if ( p ) {
                    p += strlen( tmp );
                    *total = atol( p );
                }
            }
        }

        // �u�b�N�}�[�N�𔲂��o��
        p = strstr( response, sjis2utf("<!-- �� -->") );
        if ( !p )
            break;
        p = strchr( p, '>' ) + 1;

        do {
            if ( mp ) {
                MyClip  *np;
                np = allocateMyClipIfNecessary( mp, unit, &cnt, num );
                if ( !np )
                    break;
                *mp = np;
            }
            if ( mpEx ) {
                MyClipEx    *np;
                np = allocateMyClipExIfNecessary( mpEx, unit, &cnt, num );
                if ( !np )
                    break;
                *mpEx = np;
            }

            q = strstr( p, "<p class=\"num\">" );
            s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = q + 15;

            // URL
            q = strstr( p, "<a href=\"/entry/" );
            if ( !q || (q > s) )
                break;
            p = q + 16;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // entry_id
            p = q + 2;
            q = strstr( p, "action_delete('" );
            if ( q && (q < s) ) {
                p = q + 15;
                q = strchr( p, '\'' );
                if ( q ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    if ( mpEx )
                        strcpy( (*mpEx)[num].entryID, tmp );
                }
            }

            // thumbprint
            q = strstr( p, ", '" );
            if ( q && (q < s) ) {
                p = q + 3;
                q = strchr( p, '\'' );
                if ( q ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    if ( mpEx )
                        strcpy( (*mpEx)[num].remarks, tmp );
                }
            }

            // �^�C�g��
            p = q + 1;
            q = strstr( p, "<a href=\"/entry/" );
            if ( !q || (q > s) )
                break;
            p = q + 16;
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjisEx( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( ( r = strstr( tmp, "&#39;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 5 ); /* &#39; �� ' �ɒu�� */
            }
            while ( ( r = strstr( tmp, "&quot;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &quot; �� ' �ɒu�� */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            q = strstr( p, "<div class=\"comment\">" );
            if ( !q )
                q = strstr( p, "<div class=\"comment\" " );
            if ( q && (q < s) ) {
                p = q + 21;
                q = strstr( p, "<p class=\"tag\">" );

                if ( q && (q < s) ) {
                    // �L�[���[�h (�^�O)
                    int len;

                    tmp[0] = NUL;
                    p = q + 15;
                    do {
                        q = strstr( p, "[<a href=\"/user/" );
                        if ( !q || (q > s) )
                            break;
                        p = q + 16;
                        q = strstr( p, "\">" );
                        if ( !q )
                            break;
                        p = q + 2;
                        q = strstr( p, "</a>]" );
                        if ( !q )
                            break;

                        if ( tmp[0] == NUL )
                            len = 0;
                        else {
                            strcat( tmp, " " );
                            len = strlen( tmp );
                        }
                        strncat( tmp, p, q - p );
                        tmp[len + (q - p)] = NUL;

                        p = q + 5;
                    } while ( p < s );
                    if ( tmp[0] ) {
                        r = utf2sjisEx( tmp );
                        if ( r )
                            strcpy( tmp, r );
                    }
                    if ( mp )
                        strcpy( (*mp)[num].tags, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].tags, tmp );

                    q = strstr( p, "</p>" );
                    if ( q && (q < s) )
                        p = q;
                }

                q = strstr( p, "<p>" );
                if ( q && (q < s) ) {
                    // �R�����g

                    p = q + 4;
                    while ( isWhiteSpace(*p) )
                        p++;
                    r = strstr( p, "</p>" );
                    if ( r && (r < s) ) {
                        char    *pp = r + 4;
                        while ( (r > p) && isWhiteSpace( *(r - 1) ) )
                            r--;
                        if ( r > p ) {
                            strncpy( tmp, p, r - p );
                            tmp[r - p] = NUL;
                            deleteHtmlTags( tmp );
                            r = utf2sjisEx( tmp );
                            if ( r )
                                strcpy( tmp, r );
                            while ((r = strstr(tmp, "&nbsp;")) != NULL)
                                strcpy( r, r + 6 );
                            if ( mp )
                                strcpy( (*mp)[num].comment, tmp );
                            if ( mpEx )
                                strcpy( (*mpEx)[num].comment, tmp );
                        }
                        p = pp;
                    }
                }
            }

            // �N���������b
            q = strstr( p, "<p class=\"permalink\">" );
            if ( !q || (q > s) )
                break;
            p = q + 21;
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            q = strchr( p, '<' );
            if ( q ) {
                strncpy( tmp, p, q - p );
                while ( (q > p) && isWhiteSpace(*(q - 1)) )
                    q--;
                tmp[q - p] = NUL;
                strcat( tmp, " +0900" );    /* {@@} */
                if ( mp )
                    getDateTimeFromDateString( tmp,
                                               &((*mp)[num].yyyy),
                                               &((*mp)[num].mm),
                                               &((*mp)[num].dd),
                                               &((*mp)[num].HH),
                                               &((*mp)[num].MM),
                                               &((*mp)[num].SS) );
            }

            p = s + 5;

            num++;
        } while ( p && *p );

        // ����
        cont = FALSE;
        p = strstr( response, sjis2utf("\">����</a>") );
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
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

    return ( num );
}

MyClip  *
getEcNaviClip(
        const char *userName,   /* (I) login���Ɏg�����[���A�h���X    */
        const char *password,   /* (I) login���Ɏg���p�X���[�h        */
        const char *userName2,  /* (I) �F�ؗp���[�U��(Yahoo! Japan)   */
        const char *password2,  /* (I) �F�ؗp�p�X���[�h(Yahoo! Japan) */
        AUTH_TYPE  authType,    /* (I) �F�؃^�C�v                     */
        const char *userID,     /* (I) �L�Җ�                         */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�       */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ�L�҂̃}�C�j���[�X�A�������� userID �Ŏw�肳
     *  �ꂽ�L�҂̃}�C�j���[�X��S���擾����(userName �Ŏw�肷��ꍇ�́A
     *  password �̎w����K�v�BuserID �Ŏw�肷��ꍇ�́Apassword �͕s�v)
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    size_t  sz   = MAX_CONTENT_SIZE * 20;
    int     num  = 0;
    const char  *u = userName;
    const char  *p = password;

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        u = userName2;
        p = password2;
    }

    *total      = 0;
    *numOfClips = 0;
    target[0]   = NUL;
    if ( u && u[0] && p && p[0] ) {
        size_t  cookieSize = MAX_COOKIE_LEN;
        char    *cookie;
        char    *uID;

        cookie = (char *)malloc( cookieSize + 1 );
        if ( !cookie )
            return ( mp );
        memset( cookie, 0x00, cookieSize );

        uID = getEcNaviClipUserID( u, p, authType, cookie, &cookieSize );
        if ( uID && *uID )
            sprintf( target, "http://buzzurl.jp/user/%s/all", uID );
        free( cookie );
    }
    else if ( userID && userID[0] )
        sprintf( target, "http://buzzurl.jp/user/%s/all", userID );
    if ( target[0] == NUL )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �u�b�N�}�[�N�̎擾
    num = _getEcNaviClip( target, NULL, &mp, NULL, response, sz, total );
    *numOfClips = num;

    free( response );

    return ( mp );
}


#ifdef  GET_BUZZURL_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        AUTH_TYPE *authType,
        BOOL      *useProxy
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
                 "getBuzzurl: Buzzurl �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tBuzzurl ����z���o�������e�� OPML �t�@�C���Ƃ��ďo��"
                 "����\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -u ���[���A�h���X -p �p�X���[�h\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -U Yahoo!JapanID -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getBuzzurl: get bookmarks from Buzzurl, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -u mailaddress -p password\n" );
        fprintf( stderr,
                 "    getBuzzurl [-x] -U Yahoo!JapanID -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL        useProxy = FALSE;
    char        username[MAX_USERIDLEN];
    char        password[MAX_PASSWDLEN];
    int         numOfClips = 0;
    int         total      = 0;
    MyClip      *mp = NULL;
    AUTH_TYPE   authType = AK_ORIGINAL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &authType, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* Buzzurl �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getEcNaviClip( username, password,
                        username, password,
                        authType,
                        NULL, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Buzzurl �̃u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "Buzzurl", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BUZZURL_EXE */

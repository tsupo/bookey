/*
 * clip saver <<getJoltMark>>
 *
 *      JoltMark �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/getJoltMark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 7     07/01/19 23:20 Tsujimura543
 * _getJoltMark() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 6     07/01/17 22:58 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή�
 * (2) �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 5     07/01/12 22:33 Tsujimura543
 * (1) �u���̃y�[�W�v�� URL �̖����ɗ]���ȕ����������ۂɑΏ�
 * (2) �u�R�����g�v���� <br> ���܂܂��ꍇ�͏�������悤�ɂ���
 * 
 * 4     06/12/22 18:53 Tsujimura543
 * �]���̎擾�ɑΉ�
 * 
 * 3     06/12/22 15:28 Tsujimura543
 * �R�����g�̎擾�ɑΉ� (�]���̎擾�͈ˑR�Ƃ��Ė��Ή�)
 * 
 * 2     06/12/21 21:23 Tsujimura543
 * JoltMark �̃u�b�N�}�[�N���̎擾�ɑΉ� (�R�����g�̎擾�͖��Ή�)
 * 
 * 1     06/12/21 15:21 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getJoltMark.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20

int
_getJoltMark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    )
{
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    char    markNo[MAX_KEYLENGTH];
    char    ckString[MAX_KEYLENGTH];
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    ckString[0] = NUL;

    strcpy( target, "http://mark.jolt.jp/viewuser/search.do" );
    sprintf( url,
             "%s?s3=%s&s0=&s1=&s2=&s4=&so=&dateFrom=&dateTo=",
             target, userName );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) )
            break;

        // �u�b�N�}�[�N�𔲂��o��
        p = strstr( response, sjis2utf("<!--�}�[�N���\��-->") );
        if ( !p )
            break;
        p = strstr( p, "-->" ) + 3;

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

            markNo[0] = NUL;
            q = strstr( p, "<div class=\"mark-result\">" );
            s = strstr( p, "<div class=\"mark-list-line-dot\">" );
            if ( !q || !s )
                break;
            p = q + 25;
 
            // �^�C�g��
            q = strstr( p, "<a href=\"/pageDetail/" );
            if ( !q || (q > s) ) {
                q = strstr( p, "<a href=\"pageDetail.do?" );
                if ( q )
                    q += 9;
            }
            if ( !q || (q > s) )
                break;
            p = q + 21;

            //  -- markNo
            r = strchr( p, '"' );
            if ( r && (r < s) ) {
                strncpy( markNo, p, r - p );
                markNo[r - p] = NUL;
            }

            //  -- �^�C�g��
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // ���J�E����J
            p = q + 4;
            q = strstr( p, " class=\"mark-result-noPublic\"" );
            if ( q && (q < s) ) {
                p = q + 29;
                q = strstr( p, sjis2utf("(����J)") );
                if ( q && (q < s) )
                    if ( mp )
                        (*mp)[num].publication = PUB_PRIVATE;
                q = strstr( p, "</span>" );
                if ( q && (q < s) )
                    p = q + 7;
            }

            // �N���������b
            q = strstr( p, sjis2utf("\">�}�[�N��(") );
            if ( !q || (q > s) )
                break;
            p = strchr( q, ')<' );
            if ( !p || (p > s) )
                break;
            q = p + 2;
            while ( *q && ((*q <= '0') || (*q > '9')) )
                q++;
            p = q;
            if ( !p || (p > s) )
                break;

            q = strchr( p, '<' );
            if ( q && (q < s) ) {
                char    tmp[BUFSIZ];

                r = q--;
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
                p = r;
            }

            // URL
            q = strstr( p, "<a href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 9;
            q = strstr( p, "\" " );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // �}�[�NID
            p = q + 2;
            q = strstr( p, sjis2utf(">�y�폜�z</a>") );
            if ( q && (q < s) ) {
                r = p;
                p = strstr( q, "</a>" ) + 4;
                while ( (q > r) && (strncmp( q, "markNo=", 7 ) != 0) )
                    q--;
                if ( !strncmp( q, "markNo=", 7 ) ) {
                    q += 7;
                    r = strchr( q, '&' );
                    if ( !r || (r > p) )
                        r = strchr( q, '"' );
                    if ( !r || (r > p) )
                        r = strchr( q, ' ' );
                    if ( r && (r < p) ) {
                        strncpy( tmp, q, r - q );
                        tmp[r - q] = NUL;
                        if ( mpEx )
                            strcpy( (*mpEx)[num].entryID, tmp );
                    }

                    r = strstr( q, "ckString=" );
                    if ( r && (r < p) ) {
                        q = r + 9;
                        r = strchr( q, '&' );
                        if ( !r || (r > p) )
                            r = strchr( q, '"' );
                        if ( !r || (r > p) )
                            r = strchr( q, ' ' );
                        if ( r && (r < p) ) {
                            strncpy( ckString, q, r - q );
                            ckString[r - q] = NUL;
                        }
                    }
                }
            }

            // �^�O
            q = strstr( p, " class=\"mark-result-details-icon-tag\"" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 37;
                do {
                    r = "&dateTo=\">";
                    q = strstr( p, r );
                    if ( !q || (q > s) )
                        break;
                    p = q + strlen( r );
                    r = "</a>";
                    q = strstr( p, r );
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

                    p = q + strlen( r );
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // �R�����g
            q = strstr( p, "<div class=\"mark-result-details-note\"" );
            if ( q && (q < s) ) {
                p = q + 37;
                q = strchr( p, '>' );
                if ( q && (q < s) ) {
                    p = q + 1;
                    while ( isWhiteSpace( *p ) )
                        p++;
                    q = strstr( p, "</div>" );
                    while ( (q > p) && isWhiteSpace( *(q - 1) ) )
                        q--;
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    if ( tmp[0] ) {
                        r = utf2sjis( tmp );
                        if ( r )
                            strcpy( tmp, r );
                        while ((r = strstr(tmp, "<br>")) != NULL)
                            strcpy( r, r + 4 );
                    }
                    if ( mp )
                        strcpy( (*mp)[num].comment, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].comment, tmp );
                }
            }

            // �]��
            //   �� �u�ҏW�y�[�W�v�������Ă���K�v������
            //   �� �����́u�]���v�����擾�ł��Ȃ�
            if ( mp ) {
                if ( cookie && markNo[0] ) {
                    char    response2[MAX_CONTENT_SIZE];
                    size_t  sz2 = MAX_CONTENT_SIZE;

                    sprintf( url,
                             "http://mark.jolt.jp/editMark.do?markNo=%s",
                             markNo );
                    setUpReceiveBuffer( response2, sz2 );
                    http_getEx( url, response2, cookie );
                    if ( response2[0] ) {
                        q = strstr( response2, "\" selected=\"selected\">" );
                        if ( q ) {
                            while ( (q > response2)              &&
                                    ((*q <= '0') || (*q >= '6'))    )
                                q--;
                            if ( (*q >= '1') && (*q <= '5') )
                                (*mp)[num].evaluation = (*q - '0');
                        }
                    }
                }
            }

            if ( mpEx )
                strcpy( (*mpEx)[num].remarks, ckString );

            p = s + 32;

            num++;
        } while ( p && *p );

        // ����
        cont = FALSE;
        p = strstr( response, sjis2utf("><div id=\"page-next\">���̃y�[�W") );
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( !q )
                    q = strchr( p, '>' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;

                    q = strchr( page, '>' );
                    if ( q )
                        *q = NUL;

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
getJoltMark(
        const char *userName,   /* (I) ���[�U��                       */
        const char *password,   /* (I) �p�X���[�h (����J�̃u�b�N�}�[ */
                                /*     �N���擾�������ꍇ�ɕK�v)      */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�̃u�b�N�}�[�N(�̂����A���J�����
     *  �������)��S���擾����(����J�̂��̂��擾����ɂ́AuserName
     *  �̃��[�U�� password �̎w����K�v)
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    int     num = 0;

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0] = NUL;

    fd = fileno( stderr );
    if ( password && *password ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( !cookie ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "�������̊m�ۂɎ��s���܂���\n"
                        : "memory exhausted.\n",
                       stderr );
            free( response );
            return ( mp );
        }
        memset( cookie, 0x00, MAX_COOKIE_LEN );

        // JoltMark ��login (cookie ���擾)
        if ( !loginJoltMark( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "JoltMark �ւ� login �Ɏ��s���܂���\n"
                        : "JoltMark: login failed.\n",
                       stderr );
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // �u�b�N�}�[�N�̎擾
    num = _getJoltMark( userName, cookie, &mp, NULL, response, sz );
    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_JOLTMARK_EXE
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
                 "getJoltMark: JoltMark �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tJoltMark ����z���o�������e�� OPML �t�@�C���Ƃ��ďo��"
                 "����\n" );
        fprintf( stderr,
                 "    getJoltMark [-x] -u ���[�U�� -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getJoltMark: get bookmarks from JoltMark, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getJoltMark [-x] -u username -p password\n" );
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

    /* JoltMark �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getJoltMark( username, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  JoltMark �̃u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "JoltMark", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_JOLTMARK_EXE */

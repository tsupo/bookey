/*
 * clip saver <<getBlogPet>>
 *
 *      �uBlogPet�u�b�N�}�[�N�v �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/getBlogPet.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 13    08/12/02 19:29 Tsujimura543
 * null �|�C���^�Q�Ƃ���������\���̂���ӏ��̑Ώ�
 * 
 * 12    08/02/19 22:35 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 11    08/02/19 22:33 Tsujimura543
 * _getBlogPet() ���C���A�ύX
 *     (1) �^�C�g���̐擪�Ɩ����� white space �����݂���ꍇ�͍폜����
 *         �悤�ɂ���
 *     (2) �^�C�g���ɉ��s���܂܂��ꍇ�͍폜����悤�ɂ���
 *     (3) �R�����g����̂Ƃ��A�u(�R�����g������܂���)�v���R�����g��
 *         �Ȃ��Ă��܂����ɑΏ�
 * 
 * 10    08/02/19 21:58 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v �� �uBlogPet�u�b�N�}�[�N�v�ɖ��̕ύX
 * 
 * 9     07/07/13 2:01 Tsujimura543
 * 2007�N7��12���Ɏ��{���ꂽ BlogPet ���j���[�A���ɑΉ�
 * 
 * 8     07/02/14 23:16 Tsujimura543
 * _getBlogPet() �̃v���g�^�C�v�錾�� blogPet.h �ֈړ�
 * 
 * 7     07/02/13 21:43 Tsujimura543
 * encodeURLe() �� getBlogPet.c ���� blogPet.c �ֈړ�
 * 
 * 6     07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 5     07/01/19 15:43 Tsujimura543
 * html �̎擾�E��͏����𕪗����A_getBlogPet() ���쐬
 * 
 * 4     07/01/17 21:45 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή�
 * (2) �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 3     06/12/25 23:37 Tsujimura543
 * loginBlogPet() �ɑ�4������ǉ�
 * 
 * 2     06/12/25 23:22 Tsujimura543
 * �b����� (����m�F�ς�)
 * 
 * 1     06/12/22 21:58 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"
#include "blogPet.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBlogPet.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20


int
_getBlogPet(
        const char *userID,
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
    int     page = 1;
    char    bmNumber[MAX_KEYLENGTH];
    char    tmp[MAX_DESCRIPTION_LEN * 2];

 // if ( cookie )
        sprintf( target,
                 "http://www.blogpet.net/profile/bookmarks/%s",
                 userID );
 // else
 //     strcpy( target, "http://www.blogpet.net/bookmark/my" );
 //        -- http://www.blogpet.net/bookmark/my �̕��͍ő�10�y�[�W������
 //           �ߋ������ɑk��Ȃ����߁A
 //           http://www.blogpet.net/profile/bookmarks/xxxxxx �̕����擾
 //           ����
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

        // �u�b�N�}�[�N�𔲂��o��
        p = strstr( response, "<div class=\"bookmarks\">" );
        if ( !p )
            break;
        p += 23;

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

            q = strstr( p, "<li class=\"clearfix\">" );
            if ( !q )
                q = strstr( p, "<li>" );
            s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = strchr( q, '>' ) + 1;

            // URL
            q = strstr( p, "<a href=\"/view_url?url=" );
            if ( !q || (q > s) )
                break;
            p = q + 23;
            q = strstr( p, "\" " );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            strcpy( tmp, encodeURLe( decodeURL( tmp ) ) );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );
 
            // �^�C�g��
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

            while ( ((r = strchr(tmp, '\r')) != NULL) ||
                    ((r = strchr(tmp, '\n')) != NULL)    )
                strcpy( r, r + 1 ); /* ���s����菜�� */

            r = &(tmp[strlen(tmp) - 1]);
            while ( (r > tmp) && ((*r == ' ') || (*r == '\t')) )
                *r-- = NUL;

            r = tmp;
            while ( ((*r == ' ') || (*r == '\t')) )
                r++;

            if ( mp )
                strcpy( (*mp)[num].title, r );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, r );

            // �u�b�N�}�[�N�ԍ�
            bmNumber[0] = NUL;
            p = q + 4;
            q = strstr( p, "<a href=\"/bookmark/view/" );
            if ( q && (q < s) ) {
                p = q + 24;
                if ( (*p >= '1') && (*p <= '9') )
                    sprintf( bmNumber, "%d", atol( p ) );
            }

            // �^�O
            p = q + 2;
            q = strstr( p, "<dd class=\"keywords\">" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 21;
                do {
                    r = "<a href=\"/bookmark/search?keyword=";
                    q = strstr( p, r );
                    if ( !q || (q > s) ) {
                        r = "<a href=\"/bookmark/search?tag=";
                        q = strstr( p, r );
                        if ( !q || (q > s) )
                            break;
                    }
                    p = q + strlen( r );
                    q = strstr( p, "\">" );
                    if ( q && (q < s) ) {
                        q += 2;
                        r = strstr( q, "</a>" );
                        if ( !r || (r > s) )
                            break;

                        if ( tmp[0] == NUL )
                            len = 0;
                        else {
                            strcat( tmp, " " );
                            len = strlen( tmp );
                        }
                        strncat( tmp, q, r - q );
                        tmp[len + (r - q)] = NUL;
                        p = q + 4;
                    }
                    else
                        break;
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

            //   -- �R�����g
            q = strstr( p, "<dd class=\"comment\">" );
            if ( q && (q < s) ) {
                p = q + 20;
                q = strstr( p, "&nbsp;</dd>" );
                if ( !q || (q > s) )
                    q = strstr( p, "</dd>" );
                if ( q && (q < s) ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    deleteHtmlTags( tmp );
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );

                    if ( strstr( tmp, ">(�R�����g������܂���)</span>" ) )
                        tmp[0] = NUL;

                    if ( mp )
                        strcpy( (*mp)[num].comment, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].comment, tmp );
                }
            }

            if ( mp ) {
                //   -- �o�^����
                tmp[0] = NUL;
                q = strstr( p, "<div class=\"bookmarkFooter\">" );
                if ( q && (q < s) ) {
                    p = q + 28;
                    q = strstr( p, "<br />" );
                    if ( q && (q < s) ) {
                        while ( isWhiteSpace( *p ) && (p < q) )
                            p++;
                        if ( p < q ) {
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;
                        }
                    }
                }
                else {
                    q = strstr( p, "<dd class=\"date\">" );
                    if ( q && (q < s) ) {
                        p = q + 17;
                        q = strstr( p, "</dd>" );
                        if ( q && (q < s) ) {
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;
                        }
                    }
                }
                if ( tmp[0] ) {
                    strcat( tmp, " +0900" );
                    getDateTimeFromDateString(
                            tmp,
                            &((*mp)[num].yyyy),
                            &((*mp)[num].mm),
                            &((*mp)[num].dd),
                            &((*mp)[num].HH),
                            &((*mp)[num].MM),
                            &((*mp)[num].SS) );
                }

                //   -- ���J���x��
                q = strstr( p, sjis2utf("���J���x���F<em>") );
                if ( q && (q < s) ) {
                    q = strstr( p, "<em>" ) + 4;
                    r = strstr( q, "</em>" );
                    if ( q && r && !strncmp( q, sjis2utf("���J"), r - q ) )
                        (*mp)[num].publication = PUB_EVERYONE;
                    else
                        (*mp)[num].publication = PUB_PRIVATE;
                }
            }
            p = s + 5;

            if ( bmNumber[0] ) {
                if ( mpEx )
                    strcpy( (*mpEx)[num].entryID, bmNumber );
                num++;
            }
        } while ( p && *p );

        // ����
        cont = FALSE;
        p = strstr( response, "<div class=\"pagingNext\">" );
        if ( p ) {
            page++;
            sprintf( url, "%s/%d", target, page );
            cont = TRUE;
            Sleep( 1000 );
        }
    } while ( cont );

    return ( num );
}

MyClip  *
getBlogPet(
        const char *userName,   /* (I) ���[�U��                       */
        const char *password,   /* (I) �p�X���[�h (����J�̃u�b�N�}�[ */
                                /*     �N���擾�������ꍇ�ɕK�v)      */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  (1) userName �Ń��[�U�����w�肵���ꍇ�́A���̃��[�U(�������g��z��)
     *      �̃u�b�N�}�[�N���擾���� (password �̎w����K�v)
     *        �� http://www.blogpet.net/bookmark/my
     *           �������̃u�b�N�}�[�N�̈ꗗ�̃g�b�v�y�[�W�A
     *           http://www.blogpet.net/bookmark/my/n
     *           �������̃u�b�N�}�[�N�̈ꗗ�� n �y�[�W�ڂɂȂ�
     *  (2) userName �Łu�n�b�V�������ꂽID�v���w�肵���ꍇ�́A���̃��[�U��
     *      �u�b�N�}�[�N(�̂����A���J����Ă������)��S���擾����(password
     *      �͕s�v)
     *        -- ���Y���[�U�̃v���t�B�[���y�[�W�� URL
     *             http://www.blogpet.net/profile/view/XXXXXX
     *           �� XXXXXX ����(32����)���u�n�b�V�������ꂽID�v�ɑ�������
     *        �� http://www.blogpet.net/profile/bookmarks/XXXXXX
     *           �����Y���[�U�́u���J����Ă���v�u�b�N�}�[�N�̈ꗗ�̃g�b�v
     *           �y�[�W�A
     *           http://www.blogpet.net/profile/bookmarks/XXXXXX/n
     *           �����Y���[�U�́u���J����Ă���v�u�b�N�}�[�N�̈ꗗ�� n �y�[
     *           �W�ڂɂȂ�
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;
    char    userID[MAX_KEYLENGTH];

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0] = NUL;
    userID[0] = NUL;

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

        // BlogPet �Ǘ���� ��login (cookie ���擾)
        if ( !loginBlogPet( userName, password, cookie, userID ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "BlogPet�Ǘ���ʂւ� login �Ɏ��s���܂���\n"
                        : "BlogPet: login failed.\n",
                       stderr );
            free( cookie );
            free( response );
            return ( mp );
        }
    }
    else
        strcpy( userID, userName );

    if ( !(userID[0]) ) {
        if ( cookie )
            free( cookie );
        free( response );
        return ( mp );
    }

    *numOfClips = _getBlogPet( userID, cookie, &mp, NULL, response, sz );

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_BLOGPET_EXE
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
        fprintf( stderr,
             "getBlogPet: BlogPet�u�b�N�}�[�N �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "    getBlogPet [-x] -u BlogPet���[�U�� "
                 "-p BlogPet�p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getBlogPet: get bookmarks from 'BlogPet bookmarks',"
                 " and output them as OPML\n" );
        fprintf( stderr,
                 "    getBlogPet [-x] -u username -p password\n" );
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

    /* �uBlogPet�u�b�N�}�[�N�v�o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getBlogPet( username, password, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "BlogPet", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLOGPET_EXE */

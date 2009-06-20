/*
 * clip saver <<getPookmark>>
 *
 *      POOKMARK Airlines �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  5 Oct 2006
 *
 * $Log: /comm/bookey/getPookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 13    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 12    07/01/19 18:25 Tsujimura543
 * �R�����g���C��
 * 
 * 11    07/01/19 17:11 Tsujimura543
 * _getPookmark() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 10    07/01/18 0:10 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή�
 * (2) �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 9     06/12/11 19:24 Tsujimura543
 * �u���J�t���O�v (public/private) �ɑΉ� 
 * 
 * 8     06/11/29 18:54 Tsujimura543
 * http://pookmark.jp/export �����p�\�ȏꍇ�́A������̕�����
 * �u�b�N�}�[�N�����擾����悤�ɂ���
 * 
 * 7     06/11/27 16:04 Tsujimura543
 * �R�����g����̃u�b�N�}�[�N�̎擾�Ɏ��s����s��ɑΏ�
 * 
 * 6     06/11/16 16:41 Tsujimura543
 * �擾�����u�R�����g�v�ɉ��s���܂܂��ꍇ�́A��菜���悤�ɂ���
 * 
 * 5     06/10/27 0:57 Tsujimura543
 * typo �C��
 * 
 * 4     06/10/27 0:56 Tsujimura543
 * <wbr> ���󔒂ɒu�����鏈����ǉ�
 * 
 * 3     06/10/27 0:33 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 2     06/10/27 0:27 Tsujimura543
 * POOKMARK Airlines �̃u�b�N�}�[�N�ꗗ�y�[�W�̃t�H�[�}�b�g���ύX����
 * ���̂ɔ����C�������{
 * 
 * 1     06/10/05 20:03 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getPookmark.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
getPookmarkWithCookie(
        char *cookie,       /* (I/O) �N�b�L�[                     */
        int  total,         /* (I) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int  *numOfClips    /* (O) �擾�����u�b�N�}�[�N�̐�       */
    )
{
    MyClip  *mp = NULL;
    int     num  = 0;
    char    *filename;

    if ( (total <= 0) || !cookie || !(*cookie) )
        return ( mp );

    filename = tempnam( ".", "exp" );
    if ( filename ) {
        FILE    *fp;
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_DESCRIPTION_LEN * 16 * total;

        response = (char *)malloc( sz );
        if ( !response )
            return ( mp );

        strcpy( url, "http://pookmark.jp/export" );
        setUpReceiveBuffer( response, sz );
        setTargetURL( url );
        http_getEx( url, response, cookie );
        fp = fopen( filename, "wb" );
        if ( fp ) {
            fputs( response, fp );
            fclose( fp );

            fp = fopen( filename, "rb" );
            if ( fp ) {
                mp = inputBookmarkHtml( &num, fp );
                fclose( fp );

                if ( mp && (num > 0) ) {
                    int     i;
                    char    *p;

                    for ( i = 0; i < num; i++ ) {
                        p = utf2sjis( mp[i].title );
                        if ( p )
                            strcpy( mp[i].title, p );

                        p = utf2sjis( mp[i].comment );
                        if ( p )
                            strcpy( mp[i].comment, p );

                        p = utf2sjis( mp[i].tags );
                        if ( p )
                            strcpy( mp[i].tags, p );
                    }
                }
            }
        }
        unlink( filename );
        free( filename );
        free( response );
    }

    *numOfClips = num;

    return ( mp );
}

int
_getPookmark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
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
    int     yy, mm, dd;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    sprintf( target, "http://pookmark.jp/user/%s", userName );
    strcpy( url, target );
    do {
        setUpReceiveBuffer( response, sz );
        setTargetURL( url );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) ||
             strstr( response, sjis2utf("�w�肵���y�[�W�͂���܂���") ) )
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
        }

        // �u�b�N�}�[�N�𔲂��o��
        p = strstr( response, "<ul class=\"bookmark\">" );
        if ( !p )
            break;
        p += 21;

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

            q = strstr( p, " id=\"bookmark_" );
            s = strstr( p, "</li><!-- /bookmark_" );
            if ( !s )
                s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = q + 14;

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

            // �^�C�g��
            p = q + 2;
            q = strstr( p, "<span class=\"title\">" );
            if ( !q || (q > s) )
                break;
            p = q + 20;
            q = strstr( p, "</span>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( !r )
                utf2sjisEx( tmp );
            else
                strcpy( tmp, r );
            while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &#039; �� ' �ɒu�� */
            }
            while ( (r = strstr( tmp, "&quot;" )) != NULL ) {
                *r = '"';
                strcpy( r + 1, r + 6 ); /* &quot; �� " �ɒu�� */
            }
            while ( (r = strstr( tmp, "<wbr>" )) != NULL ) {
                *r = ' ';
                strcpy( r + 1, r + 5 ); /* <wbr> �� �� �ɒu�� */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // �n�b�V���l
            r = p = q + 7;
            q = strstr( p, "<div class=\"user-count\">" );
            if ( !q )
                q = strstr( p, "<div class=\"user-count " );
            if ( q ) {
                p = strchr( q, '>' ) + 1;
                q = strstr( p, "<a href=\"/url/" );
                if ( q ) {
                    p = q + 14;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( tmp, p, q - p );
                        tmp[q - p] = NUL;
                        if ( mpEx )
                            strcpy( (*mpEx)[num].remarks, tmp );
                    }
                }
            }
            if ( !q )
                q = p - 7;

            // �R�����g
            p = r;
            q = strstr( p, "<p class=\"comment\">" );
            if ( !q )
                q = strstr( p, "<p class=\"comment " );
            if ( !q || (q > s) )
                q = p - 4; // �R�����g������̏ꍇ
            else {
                p = strchr( q, '>' ) + 1;
                q = strstr( p, "</p>" );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                r = utf2sjis( tmp );
                if ( !r )
                    utf2sjisEx( tmp );
                else
                    strcpy( tmp, r );
                while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                    *r = '\'';
                    strcpy( r + 1, r + 6 ); /* &#039; �� ' �ɒu�� */
                }
                while ( (r = strstr( tmp, "&quot;" )) != NULL ) {
                    *r = '"';
                    strcpy( r + 1, r + 6 ); /* &quot; �� " �ɒu�� */
                }
                while ( (r = strstr( tmp, "<wbr>" )) != NULL ) {
                    *r = ' ';
                    strcpy( r + 1, r + 5 ); /* <wbr> �� �� �ɒu�� */
                }
                while ( ((r = strchr(tmp, '\r')) != NULL) ||
                        ((r = strchr(tmp, '\n')) != NULL)    )
                    strcpy( r, r + 1 );     /* ���s����菜�� */
                if ( mp )
                    strcpy( (*mp)[num].comment, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].comment, tmp );
            }

            // �^�O
            p = q + 4;
            q = strstr( p, "<p class=\"tag\">" );
            if ( !q )
                q = strstr( p, "<li class=\"tag\">" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = strchr( q, '>' ) + 1;
                do {
                    q = strstr( p, "\" rel=\"tag\">" );
                    if ( !q )
                        q = strstr( p, "\" class=\"tag\">" );
                    if ( !q || (q > s) )
                        break;
                    p = strchr( q, '>' ) + 1;
                    q = strstr( p, "</a>" );
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

                    p = q + 4;
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( !r )
                        utf2sjisEx( tmp );
                    else
                        strcpy( tmp, r );
                    while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 6 ); /* &#039; �� ' �ɒu�� */
                    }
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // �N����
            q = strstr( p, "<span class=\"datetime\">" );
            if ( !q || (q > s) )
                break;
            p = q + 23;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            yy = atol( p );

            skipToNextItemWithSeparator( p, '/', s );
            mm = atol( p );

            skipToNextItemWithSeparator( p, '/', s );
            dd = atol( p );

            if ( mp ) {
                (*mp)[num].yyyy = yy;
                (*mp)[num].mm   = mm;
                (*mp)[num].dd   = dd;
                (*mp)[num].HH   = 0;
                (*mp)[num].MM   = 0;
                (*mp)[num].SS   = 0;
            }

            // ���J�t���O
            q = strstr( p, "<span class=\"private\">" );
            if ( q && (q < s) )
                if ( mp )
                    (*mp)[num].publication = PUB_PRIVATE;

            // bookmark ID (�폜�p)
            q = strstr( p, "delete_confirm('" );
            if ( q && (q < s) ) {
                p = q + 16;
                q = strstr( p, "')" );
                if ( q ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                }
                if ( mpEx )
                    strcpy( (*mpEx)[num].entryID, tmp );
            }

            p = s + 5;
            num++;
            if ( (*total > 0) && (num >= *total) ) {
                cont = FALSE;
                break;
            }
        } while ( p && *p );

        // ����
        page++;
        sprintf( url, "%s?page=%d", target, page );
        Sleep( 1000 );
    } while ( cont );

    return ( num );
}

MyClip  *
getPookmark(
        const char *userName,   /* (I) JugemKey ID (JUGEM���[�U��)      */
        const char *password,   /* (I) �p�X���[�h (�v���C�x�[�g�ȃu�b�N */
                                /*     �}�[�N���擾����ꍇ�ɂ̂ݕK�v)  */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑���   */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�         */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�[�̃N���b�v��S���擾����
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    int     num  = 0;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0]   = NUL;
    response[0] = NUL;

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

        // jugemkey �� login (cookie ���擾)
        if ( !loginJugemkey( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "POOKMARK �ւ� login �Ɏ��s���܂���\n"
                        : "POOKMARK Airlines: login failed.\n",
                       stderr);
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // �u�b�N�}�[�N���擾
    num = _getPookmark( userName, cookie, &mp, NULL, response, sz, total );
    if ( (*total > 0) && (num == 0) ) {
        // ��L�̕��@�ł̓u�b�N�}�[�N��񂪎擾�ł��Ȃ������ꍇ
        //  -- html �t�@�C���̒��g�̍\�����ύX���ꂽ�A�Ȃǂ̌����Ŏ擾�ł�
        //     �Ȃ��Ȃ��Ă��܂����ꍇ
        if ( cookie ) {
            // POOKMARK �̃G�N�X�|�[�g�@�\���g���āA�u�b�N�}�[�N�����擾
            //  -- ����: ���̕��@�ł́u���J�t���O�v�̒l���擾�ł��Ȃ�
            if ( mp )
                free( mp );
            mp = getPookmarkWithCookie( cookie, *total, &num );
        }
    }

    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_POOKMARK_EXE
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
                 "getPookmark: POOKMARK Airlines �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tPOOKMARK Airlines����z���o�������e�� OPML �t�@�C���Ƃ���"
                 "�o�͂���\n" );
        fprintf( stderr,
                 "    getPookmark [-x] -u JugemKeyID -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getPookmark: get bookmarks from POOKMARK Airlines, and "
                 "output them as OPML\n" );
        fprintf( stderr,
                 "    getPookmark [-x] -u JugemKeyID -p password\n" );
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

    /* POOKMARK Airlines �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getPookmark( username, password, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  POOKMARK Airlines �̃u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "POOKMARK Airlines", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_POOKMARK_EXE */

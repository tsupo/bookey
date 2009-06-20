/*
 * clip saver <<getYahooBookmarks>>
 *
 *      Yahoo! Bookmarks �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  20 Apr 2007
 *
 * $Log: /comm/bookey/getYahooBookmarks.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     08/12/02 19:33 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 2     07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks �� Yahoo! �u�b�N�}�[�N�́u�폜�v�ɑΉ�
 * 
 * 1     07/04/20 20:30 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getYahooBookmarks.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
getYBookmarksFromHtml(
        const char *endPointForExport,/* (I) �G�N�X�|�[�g URI               */
        char       *cookie,           /* (I/O) �N�b�L�[                     */
        int        total,             /* (I) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips        /* (O) �擾�����u�b�N�}�[�N�̐�       */
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

        strcpy( url, endPointForExport );
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

                if ( mp && (num > 0) )
                    qsort( mp, num, sizeof ( MyClip ), compareMyClip );
            }
        }
        unlink( filename );
        free( filename );
        free( response );
    }

    *numOfClips = num;

    return ( mp );
}


MyClip  *
getYahooBookmarksFromHtml(
        char *cookie,       /* (I/O) �N�b�L�[                     */
        int  total,         /* (I) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int  *numOfClips    /* (O) �擾�����u�b�N�}�[�N�̐�       */
    )
{
    return ( getYBookmarksFromHtml(
                "http://bookmarks.yahoo.com/tools/export?expformat=ie",
                cookie,
                total,
                numOfClips ) );
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
int
_getYahooBookmarks(
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
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    strcpy( target, "http://bookmarks.yahoo.com/" );
    strcpy( url, target );
    do {
        setUpReceiveBuffer( response, sz );
        setTargetURL( url );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !(*response) )
            break;

        if ( *total == 0 ) {
            // �S���ŉ������邩�A�O�����Ē��ׂĂ���
            p = strstr( response, "<strong id=\"infototal\">" );
            if ( p )
                *total = atol( p + 23 );
        }

        // �u�b�N�}�[�N�𔲂��o��
        p = strstr( response, "<div id=\"visiblebms\">" );
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

            q = strstr( p, "<div class=\"saveitem\"" );
            s = strstr( p, "<div class=\"clr\"></div>" );
            if ( !s )
                s = strstr( p, "<div class=\"selectarea\">" );
            if ( !q || !s )
                break;
            p = q + 21;

            // ID
            q = strstr( p, " id=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 5;
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            if ( !strncmp( p, "fakenode", 8 ) )
                break;
            if ( mpEx ) {
                strncpy( (*mpEx)[num].entryID, p, q - p );
                (*mpEx)[num].entryID[q - p] = NUL;
            }
            p = q + 2;

            // URL
            q = strstr( p, "<h4 class=\"title\"><a href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 27;
            if ( !strncmp( p, "http://us.lrd.yahoo.com/_ylt=", 29 ) ) {
                q = strstr( p, "/**" );
                if ( !q || (q > s) )
                    break;
                p = q + 3;
            }
            q = strstr( p, "\" " );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "%3A" ) ) != NULL ) {
                *r = ':';
                strcpy( r + 1, r + 3 );
            }
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );
            p = q + 2;

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
            if ( !r )
                utf2sjisEx( tmp );
            else
                strcpy( tmp, r );
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );
            p = q + 4;

            // �R�����g
            q = strstr( p, "<div class=\"desc\">" );
            if ( q && (q < s) ) {
                // �R�����g�����݂���ꍇ
                p = q + 18;
                q = strstr( p, "</div>" );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                r = utf2sjis( tmp );
                if ( !r )
                    utf2sjisEx( tmp );
                else
                    strcpy( tmp, r );
                if ( mp )
                    strcpy( (*mp)[num].comment, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].comment, tmp );
                p = q + 6;
            }

            // �^�O
            q = strstr( p, " class=\"tags\">" );
            if ( q && (q < s) ) {
                // �^�O�����݂���ꍇ
                int len;

                p = q + 14;

                tmp[0] = NUL;
                p = strchr( q, '>' ) + 1;
                do {
                    q = strstr( p, "<a href=\"/tags/" );
                    if ( !q || (q > s) )
                        break;
                    q += 15;
                    p = strchr( q, '>' );
                    if ( !p )
                        break;
                    p++;
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
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // �N���������b�͎擾�ł��Ȃ�
            if ( mp ) {
                // �Ƃ肠�����A���ݎ��������Ă���
                time_t      t = time( NULL );
                struct tm   *tm = localtime( &t );

                (*mp)[num].yyyy = tm->tm_year + 1900;
                (*mp)[num].mm   = tm->tm_mon + 1;
                (*mp)[num].dd   = tm->tm_mday;
                (*mp)[num].HH   = tm->tm_hour;
                (*mp)[num].MM   = tm->tm_min;
                (*mp)[num].SS   = tm->tm_sec;
            }

            // ���J�E����J (�����_�ł́A���ׂĔ���J)
            if ( mp )
                (*mp)[num].publication = PUB_PRIVATE;

            p = strchr( s, '>' );
            num++;
            if ( (*total > 0) && (num >= *total) ) {
                cont = FALSE;
                break;
            }
        } while ( p && *p );

        if ( cont ) {
            // ����
            cont = FALSE;
            if ( strstr( response, "<span>Next</span></a>" ) ) {
                page++;
                sprintf( url,
                         "%s?orderby=ctime&b=%d&sort=DESC",
                         target, page );
                cont = TRUE;
                Sleep( 1000 );
            }
        }
    } while ( cont );

    return ( num );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif


MyClip  *
getYahooBookmarks(
        const char *userName,   /* (I) Yahoo! ID                      */
        const char *password,   /* (I) �p�X���[�h                     */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�       */
    )
{
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    int     num  = 0;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    *numOfClips = 0;
    if ( !password || !(*password) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0]   = NUL;
    response[0] = NUL;

    fd = fileno( stderr );
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

    if ( !loginYahoo( userName, password, cookie ) ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Yahoo! �ւ� login �Ɏ��s���܂���\n"
                    : "Yahoo!: login failed.\n",
                   stderr);
        free( response );
        free( cookie );
        return ( mp );
    }

    // �u�b�N�}�[�N���擾
    num = _getYahooBookmarks( userName, cookie, &mp, NULL,
                              response, sz, total );
    if ( num > 0 ) {
        // �^�C���X�^���v���擾�A�㏑��
        int     num2 = 0;
        MyClip  *mp2 = getYahooBookmarksFromHtml( cookie, num, &num2 );

        if ( mp2 ) {
            if ( num2 > 0 ) {
                int i, j, k, l;

                for ( i = 0; i < num; i++ ) {
                    for ( j = 0; j < num2; j++ ) {
                        l = (i + j) % num2;
                        k = (num2 - l) - 1;
                        if ( !strcmp( mp[i].url, mp2[k].url ) ) {
                            mp[i].yyyy = mp2[k].yyyy;
                            mp[i].mm   = mp2[k].mm;
                            mp[i].dd   = mp2[k].dd;
                            mp[i].HH   = mp2[k].HH;
                            mp[i].MM   = mp2[k].MM;
                            mp[i].SS   = mp2[k].SS;
                            break;
                        }
                    }
                }
            }

            free( mp2 );
        }
    }
    *numOfClips = num;

    free( cookie );
    free( response );

    return ( mp );
}

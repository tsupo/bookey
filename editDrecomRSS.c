/*
 *  editDrecomRSS.c
 *      �w��URL�̋L�����h���R��RSS(��Clip!)�ɏ㏑���o�^����
 *          written by H.Tsujimura  5 Feb 2007
 *
 * $Log: /comm/bookey/editDrecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/07/26 0:44 Tsujimura543
 * encodeContents() �� encodeContents.c �ֈڊ�
 * 
 * 4     07/02/15 0:29 Tsujimura543
 * getArticleIDbyURL() �� getArticleIDbyURLonDrecomRSS() �ɖ��̕ύX
 * 
 * 3     07/02/05 22:07 Tsujimura543
 * �\�[�X�̐���
 * 
 * 2     07/02/05 21:40 Tsujimura543
 * getArticleIDbyURL() �̈�����ǉ��B�t�H���_�ԍ����킩���Ă���ꍇ��
 * �L��ID�̔����ɗv���鎞�Ԃ�Z�k�ł���悤�ɂȂ���
 * 
 * 1     07/02/05 17:55 Tsujimura543
 * getArticleIDbyURL() �� editDrecomRSS() ������ (����m�F�ς�)
 */

#include "myClip.h"
#include "getDrecomRSS.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editDrecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif


void
getClipInfoByURL(
        const char *htmlSrc,
        MyClip     **mp,
        const char *tag,
        int        year,
        const char *objectID,
        char       *cookie,
        int        *numOfClips,
        const char *url,        /* (I)   �����Ώ�URL */
        char       *articleID   /* (O)   �L��ID      */
    )
{
    int                 unit = MAX_DRECOM_RSS_PER_BLOCK;
    Thread  static int  cnt  = 0;
    const char          *p, *q, *r;
    char                _articleID[64];
    char                *response;
    char                title[1024];
    char                href[1024];
    char                summary[2048];
    int                 yyyy, mm, dd, HH, MM, SS;
    int                 num = 0;
    size_t              sz  = MAX_CONTENT_SIZE * 20;

    if ( !(*mp) )
        cnt = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    p = htmlSrc;
    do {
        // article ID
        q = strstr( p, "<div class=\"articleRow\" id=\"" );
        if ( !q )
            break;
        r = strstr( q, "</div>" );
        if ( !r )
            break;
        p = q + 28;
        q = strstr( p, "\">" );
        if ( !q || (q > r) )
            break;
        strncpy( _articleID, p, q - p );
        _articleID[q - p] = NUL;

        // title
        p = q + 2;
        q = strstr( p, " all=\"");
        if ( !q || (q > r) )
            break;
        p = q + 6;
        q = strstr( p, "\">" );
        if ( !q || (q > r) )
            break;
        strncpy( title, p, q - p );
        title[q - p] = NUL;

        // timestamp
        yyyy = year;
        mm   = 0;
        dd   = 0;
        HH   = 0;
        MM   = 0;
        SS   = 0;

        p = q + 2;
        q = strstr( p, ".articleTime\">" );
        if ( !q || (q > r) )
            break;
        p = q + 14;
        while ( isWhiteSpace(*p) )
            p++;
        q = strstr( p, "</span>" );
        if ( q ) {
            char    tmp[BUFSIZ];

            r = q;
            while ( (q > p) && isWhiteSpace(*(q - 1)) )
                q--;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            strcat( tmp, " +0900" );    /* {@@} */
            getDateTimeFromDateString( tmp, &yyyy, &mm, &dd, &HH, &MM, &SS );
            p = r + 1;
        }

        p = r + 6;

        getArticleDetail( _articleID, objectID,
                          response, sz, cookie );
        if ( *response ) {
            char    *s, *t;
            MyClip  *pp;

            decodeContents( response );
            s = response;

            // url
            t = strstr( s, "<a href=\"" );
            if ( !t )
                continue;
            s = t + 9;
            t = strstr( s, "\" " );
            if ( !t )
                continue;
            strncpy( href, s, t - s );
            href[t - s] = NUL;

            // comment
            summary[0] = NUL;
            s = t + 2;
            t = strstr( s, "<td style=\"color:#666666;\">" );
            if ( t ) {
                s = t + 27;
                t = strstr( s, "</td>" );
                if ( t ) {
                    strncpy( summary, s, t - s );
                    summary[t - s] = NUL;
                }
            }

            while ( (s = strstr( title, "&#039;" )) != NULL ) {
                *s = '\'';
                strcpy( s + 1, s + 6 ); /* &#039; �� ' �ɒu�� */
            }

            /* �h���R��RSS��Clip!�̃R�����g�ɂ͉��s���܂܂꓾�� */
            while ( ((s = strchr(summary, '\r')) != NULL) ||
                    ((s = strchr(summary, '\n')) != NULL)    )
                strcpy( s, s + 1 ); /* ���s����菜�� */
            /* �h���R��RSS��Clip!�̃R�����g�ɂ� <br /> ���܂܂꓾�� */
            while ( (s = strstr( summary, "<br />" )) != NULL )
                strcpy( s, s + 6 ); /* <br /> ����菜�� */
            while ( (s = strstr( summary, "&#039;" )) != NULL ) {
                *s = '\'';
                strcpy( s + 1, s + 6 ); /* &#039; �� ' �ɒu�� */
            }

            pp = allocateMyClipIfNecessary(mp, unit, &cnt, *numOfClips + num);
            if ( !pp )
                break;
            *mp = pp;

            pp = &((*mp)[*numOfClips + num]);
            strcpy( pp->title, utf2sjisEx(title) );
            if ( summary[0] )
                strcpy( pp->comment, utf2sjisEx(summary) );
            strcpy( pp->url,  href );
            strcpy( pp->tags, tag );
            pp->yyyy = yyyy;
            pp->mm   = mm;
            pp->dd   = dd;
            pp->HH   = HH;
            pp->MM   = MM;
            pp->SS   = SS;

            if ( !strcmp( url, pp->url ) ) {
                strcpy( articleID, _articleID );
                break;
            }

            num++;
        }
    } while ( p && *p );

    if ( num > 0 )
        *numOfClips += num;

    free( response );
}

void
getDrecomRSSclipByURL(
        MyClip     **mp,
        const char *objectID,
        const char *folderName,
        int        folderNumber,
        int        year,
        char       *cookie,
        int        *numOfClips,
        const char *url,        /* (I)   �����Ώ�URL */
        char       *articleID   /* (O)   �L��ID      */
    )
{
    char    *p;
    char    tag[80];
    int     totalPages = 0;
    int     page = 1;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    // �t�H���_�� �� �^�O
    getTagByName( tag, folderName );

    // �w��t�H���_�E�w��N�̃N���b�v�ꗗ(��1�y�[�W��)���擾
    getArticleList( folderNumber, year, page, objectID,
                    response, sz, cookie );
    if ( *response ) {
        if ( !strstr( response, "\"error\":null" ) ) {
            free( response );
            return; /* �擾���s */
        }

        decodeContents( response );
        if ( !strstr( response, "<div class=\"articleRow\"" ) ) {
            free( response );
            return; /* �w��N�̃N���b�v�f�[�^�Ȃ� */
        }

        p = strstr( response, "title=\"last page\">[" );
        if ( p ) {
            p += 19;
            totalPages = atol( p );
        }
        getClipInfoByURL( response, mp, tag, year,
                          objectID, cookie, numOfClips,
                          url, articleID );

        // �w��t�H���_�E�w��N�̃N���b�v�ꗗ(��2�y�[�W�ڈȍ~)���擾
        for ( ++page; page <= totalPages; page++ ) {
            if ( articleID[0] )
                break;
            Sleep( 1000 );  /* �T�[�o�ւ̕��׏W������̂��� sleep */
            getArticleList( folderNumber, year, page, objectID,
                            response, sz, cookie );
            if ( !(*response) || !strstr( response, "\"error\":null" ) )
                break;      /* �擾���s */

            decodeContents( response );
            if ( !strstr( response, "<div class=\"articleRow\"" ) )
                continue;   /* �N���b�v�f�[�^�Ȃ� */

            getClipInfoByURL( response, mp, tag, year,
                              objectID, cookie, numOfClips,
                              url, articleID );
        }
    }

    free( response );
}


/* �w�肳�ꂽURL�̃h���R��RSS�̃N���b�v���[�_�[���L��ID���擾���� */
BOOL
getArticleIDbyURLonDrecomRSS(
        const char *url,            /* (I)   �����Ώ�URL */
        long       folderNumber,    /* (I) �t�H���_�ԍ�  */
        char       *cookie,         /* (I/O) �N�b�L�[    */
        char       *articleID       /* (O)   �L��ID      */
    )
{
    BOOL        ret   = FALSE;
    MyClip      *mp   = NULL;
    FOLDER_LIST *list = NULL;
    int         numOfFolders = 0;
    char        *response;
    int         num = 0;
    size_t      sz  = MAX_CONTENT_SIZE * 20;

    articleID[0] = NUL;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    // �t�H���_�ꗗ���擾
    // �N���b�v���[�_�[ �ɃA�N�Z�X
    setUpReceiveBuffer( response, sz );
    http_getEx( "http://rss.drecom.jp/clip", response, cookie );
    if ( *response )
        list = getFolderList( response, &numOfFolders );

    if ( list ) {
        char        objectID[64];
        int         i, y;
        time_t      t = time( NULL );
        struct tm   *tm = localtime( &t );
        int         yyyy = tm->tm_year + 1900;
        BOOL        b;

        // objectID ��o�^
        objectID[0] = NUL;
        b = setObjectID( objectID, cookie );
        if ( b ) {
            if ( folderNumber > 0 ) {
                folderNumber--;
                for (y = yyyy; y > 2003; y--) { // �ŌẪN���b�v��2004�N3��
                    getDrecomRSSclipByURL( &mp, objectID,
                                           list[folderNumber].folderName,
                                           folderNumber, y, cookie, &num,
                                           url, articleID );
                    if ( articleID[0] ) {
                        ret = TRUE;
                        break;
                    }
                }
            }
            else {
                // �e�t�H���_�ɂ��āA�N���Ƃ̃N���b�v�ꗗ���擾
                for ( i = 0; i < numOfFolders; i++ ) {
                    for (y = yyyy; y > 2003; y--) {//�ŌẪN���b�v��2004�N3��
                        getDrecomRSSclipByURL( &mp, objectID,
                                               list[i].folderName,
                                               i, y, cookie, &num,
                                               url, articleID );
                        if ( articleID[0] ) {
                            i = numOfFolders;
                            ret = TRUE;
                            break;
                        }
                    }
                }
            }
        }

        free( list );
    }

    free( response );

    return ( ret );
}


BOOL
editDrecomRSS(
        const MyClip *mp,
        const char   *articleID,
        char         *cookie,
        char         *errorString
    )
{
    BOOL    ret = FALSE;
    char    objectID[64];
    BOOL    b;

    // objectID ��o�^
    objectID[0] = NUL;
    b = setObjectID( objectID, cookie );
    if ( b ) {
        char    url[MAX_URLLENGTH];
        char    *request;
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 20;

        request = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request )
            return ( ret );
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            return ( ret );
        }

        strcpy( url, "http://rss.drecom.jp/jsonrpc" );
        sprintf( request,
                 "{\"method\": \"clip.editClip\", \"params\": "
                 "[\"%s\", \"%s\", ",
                 articleID,
                 encodeContents(sjis2utf(mp->title)) );
        sprintf( request + strlen(request),
                 "\"%s\"], "
                 "\"objectID\": \"%s\"}",
                 encodeContents(sjis2utf(mp->comment)),
                 objectID );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "text/plain",
                     request, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"error\":null" );
            if ( p )
                ret = TRUE;
            else {
                p = strstr( response, "\"error\":" );
                if ( p ) {
                    char    *q;

                    p += 8;
                    q = strchr( p, '}' );
                    if ( q ) {
                        strncpy( errorString, p, q - p );
                        errorString[q - p] = NUL;
                        p = utf2sjisEx( errorString );
                        if ( !p )
                            errorString[0] = NUL;
                    }
                }
            }
        }

        free( response );
        free( request );
    }

    return ( ret );
}


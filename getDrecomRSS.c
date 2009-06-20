/*
 * clip saver <<getDrecomRSS>>
 *
 *      �h���R��RSS-Clip �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  12 Jul 2006
 *
 * $Log: /comm/bookey/getDrecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 18    08/12/02 19:30 Tsujimura543
 * null�|�C���^�Q�Ƃ���������\���̂���ӏ��̑Ώ�
 * 
 * 17    08/07/26 0:31 Tsujimura543
 * decodeContents() �� decodeContents.c �ֈڊ�
 * 
 * 16    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 15    07/01/17 21:46 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 14    06/12/07 20:14 Tsujimura543
 * getDateTimeFromDateString() �𓱓����A�������̉�͂��ς˂邱�Ƃɂ���
 * 
 * 13    06/11/10 17:00 Tsujimura543
 * GET_DRECOM_RSS_EXE ���L���ȏ�ԂŃR���p�C�������ꍇ�A�o�͂���OPML
 * �t�@�C���� title �v�f�� BlogPeople Tags �ɂȂ��Ă��܂��s����C��
 * 
 * 12    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() �𓱓��BMyClip �\���̊i�[�̈�m�ۏ�����
 * ���ʊ֐������Ă݂�
 * 
 * 11    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 10d   06/09/03 15:54 tsupo
 * cookie �i�[�̈���q�[�v����X�^�b�N�ɕύX
 * 
 * 10c   06/09/03 7:23 tsupo
 * cookie �̊i�[�̈�̃T�C�Y����(4096�o�C�g)�ɖ߂�
 * 
 * 10b   06/09/03 6:42 tsupo
 * �Ď��ԑ΍�Afix
 * 
 * 10a   06/09/03 5:47 tsupo
 * (1) �Ȃ��� Visual Studio 2005 �Ńr���h�����ł͓��{���Ԃł���ɂ���
 *     ��炸�Ď��ԂɂȂ�(localtime() �̕Ԃ� struct tm �̓��e)���߁A
 *     �b��I��1���ԉߋ��ɖ߂��悤�ɂ��Ă݂�
 * (2) cookie �p�Ɋm�ۂ���̈�T�C�Y�𑝂₷ (�b��)
 * (3) JSONRPC ���N�G�X�g���s���� 0 �o�C�g�̉������Ԃ��Ă��錏�̑΍�
 *     (�b��)
 * (4) ����\�[�X����R�}���h���C���� (getDrecomRSS.exe)���r���h�ł���
 *     �悤�ɂ��Ă݂�
 * 
 * 10    06/09/01 19:06 Tsujimura543
 * ����Ƀ��t�@�N�^�����O
 * 
 * 9     06/09/01 17:01 Tsujimura543
 * �t�H���_�ꗗ�擾������ getFolderList() �Ƃ��ēƗ�������
 * 
 * 8     06/09/01 0:59 Tsujimura543
 * ����ɏ������t�@�N�^�����O
 * 
 * 7     06/08/31 17:01 Tsujimura543
 * �����������t�@�N�^�����O
 * 
 * 6     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 5     06/07/13 18:25 Tsujimura543
 * XML invalid �� OPML ��f���o���Ă��܂��\�����ɗ͔r������悤�ɂ���
 * 
 * 4     06/07/13 16:40 Tsujimura543
 * Sleep() ������
 * 
 * 3     06/07/13 16:37 Tsujimura543
 * �ŏ��̔ŁA���� (����m�F����)
 * 
 * 2     06/07/12 23:07 Tsujimura543
 * UCS-2 �̃f�R�[�h(UTF-8 �ւ̕ϊ�)�����C��
 * 
 * 1     06/07/12 20:44 Tsujimura543
 * �V�K�쐬 (�T�[�o����N���b�v�ꗗ������Ă���Ƃ���܂ō쐬)
 */

#include "myClip.h"
#include "getDrecomRSS.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDrecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif

#define skipToNextItem(p)   \
            while ( *(p) && ((*(p) >= '0') && (*(p) <= '9')) ) \
                (p)++; \
            while ( *(p) && ((*(p) <= '0') || (*(p) > '9')) ) \
                (p)++;

BOOL
setObjectID( char *objectID, char *cookie )
{
    BOOL        ret = FALSE;
    char        *p;
    char        url[MAX_URLLENGTH];
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    char        *request;
    char        *response;
    size_t      sz = MAX_CONTENT_SIZE * 20;
    int         retry = 5;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    if ( tm->tm_isdst == 1 ) {
        p = _tzname[0];
        if ( !strcmp( p, "JST" ) ) {
            /* �Ȃ������{���Ԃł���ɂ��ւ�炸�A�Ď��ԂɂȂ��Ă���ꍇ */
            long l = _daylight;

            if ( l == 1 ) {
                // ���ϐ� TZ ��ݒ肵�Ă���ꍇ�́A(Visual Studio 2005 ��)
                // �uC �����^�C�� ���C�u�����́A�Ď��� (DST: Daylight Saving
                // Time) �v�Z�̎����ɂ��Ă͕č��̋K����O��Ƃ��Ă��܂��v��
                // �������ƂŁA����ɉĎ��Ԃɂ���Ă��܂��炵��
                // ���{���Ԃɂ�(���Ȃ��Ƃ������_�ł�)�Ď��Ԃ͂Ȃ��̂Ɂc�c
                _daylight = 0;
                tm = localtime( &t );
            }
            else {
                tm->tm_isdst = 0;
                tm->tm_hour--;
                        // tm_hour �����̒l�ɂȂ����ꍇ�́A�����I�ɑO���ɂȂ�
            }
        }
    }
    strcpy( objectID, asctime( tm ) );
    p = strrchr( objectID, ' ' );
    if ( p )
        sprintf( p, " UTC+0900 %04d", tm->tm_year + 1900 );

    // JSON RPC API �ꗗ�擾 (objectID �o�^�����˂�)
    do {
        request[0]  = NUL;
        strcpy( url, "http://rss.drecom.jp/jsonrpc" );
        sprintf( request,
                 "{\"method\": \"system.listMethods\", \"params\": [], "
                 "\"objectID\": \"%s\"}",
                 objectID );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "text/plain",
                     request, response, cookie );
        if ( !(*response ) ) {
            retry--;
            if ( retry <= 0 )
                break;
            Sleep( 2000 );
        }
    } while ( !(*response) );

    if ( *response ) {
        if ( strstr( response, "\"error\":null" ) )
            ret = TRUE;     /* �擾���� �� objectID �o�^���� */
    }

    if ( ret == FALSE )
        *objectID = NUL;    /* �擾���s �� objectID �o�^���s */

    free( response );
    free( request );

    return ( ret );
}

char    *
getArticleList( int folderNumber, int year, int page,
                const char *objectID,
                char *response, size_t sz,
                char *cookie )
{
    char    url[MAX_URLLENGTH];
    char    request[BUFSIZ];

    strcpy( url, "http://rss.drecom.jp/jsonrpc" );
    sprintf( request,
             "{\"method\": \"clip.getClipArticleList\", \"params\": "
             "[\"m%d.%04d.00\", %d], "
             "\"objectID\": \"%s\"}",
             folderNumber + 1, year, page,
             objectID );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "text/plain",
                 request, response, cookie );

    return ( response );
}

char    *
getArticleDetail( const char *articleID, const char *objectID,
                  char *response, size_t sz,
                  char *cookie )
{
    char    url[MAX_URLLENGTH];
    char    request[BUFSIZ];

    strcpy( url, "http://rss.drecom.jp/jsonrpc" );
    sprintf( request,
             "{\"method\": \"clip.getClipArticleDetailHtml\", \"params\":"
             " [\"%s\"], \"objectID\": \"%s\"}",
             articleID,
             objectID );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "text/plain",
                 request, response, cookie );

    return ( response );
}

void
getTagByName( char *tag, const char *folderName )
{
    char    *p = utf2sjis( folderName );
    char    *q = p;

    if ( !p )
        q = p = (char *)folderName;

    if ( !strcmp( p, "IT" ) )
        q = "Internet";
    else if ( !strcmp( p, "�G���^�[�e�C�����g" ) )
        q = "entertainment";
    else if ( !strcmp( p, "�T�C�G���X" ) )
        q = "science";
    else if ( !strcmp( p, "�n��" ) )
        q = "region";
    else if ( !strcmp( p, "�Љ�" ) )
        q = "social";
    else if ( !strcmp( p, "�R����" ) )
        q = "column";
    else if ( !strcmp( p, "�]��" ) )
        q = "news-of-death";
    else if ( !strcmp( p, "�����E�|�\" ) )
        q = "culture";
    else if ( !strcmp( p, "blog" ) )
        q = "blog";
    else if ( !strcmp( p, "�o�ρE�o�c" ) )
        q = "economy";
    else if ( !strcmp( p, "����" ) )
        q = "politics";
    else if ( !strcmp( p, "�X�|�[�c" ) )
        q = "sport";
    else if ( !strcmp( p, "�u�b�N���r���[" ) )
        q = "book-review";
    else if ( !strcmp( p, "����" ) )
        q = "international";
    else if ( !strcmp( p, "�e�N�m���W�[" ) )
        q = "technology";

    strcpy( tag, q );
}

FOLDER_LIST *
getFolderList( const char *htmlSrc, int *numOfFolders )
{
    char        *p;
    int         num = 0;
    FOLDER_LIST *list = NULL;

    p = strstr( htmlSrc, "<div id=\"broot.children\" class=\"tree\">" );
    if ( p ) {
        char    name[BUFSIZ];
        char    *q, *r;
        int     unit  = 15;
        int     cnt   = 1;

        r = strstr( p, "<div id=\"treePool\" style=\"display:none;\">" );
        if ( r ) {
            p += 38;
            do {
                sprintf( name, "<div id=\"m%d.name\" class=\"treeName\">",
                         num + 1 );
                q = strstr( p, name );
                if ( !q || (q > r) )
                    break;

                if ( !list )
                    list = (FOLDER_LIST *)
                                malloc( sizeof ( FOLDER_LIST ) * unit * cnt );
                else if ( num >= unit * cnt ) {
                    FOLDER_LIST *newList;
                    cnt++;
                    newList = (FOLDER_LIST *)
                                    realloc( list,
                                             sizeof ( FOLDER_LIST ) *
                                                            unit * cnt );
                    if ( !newList )
                        break;
                    list = newList;
                }
                if ( !list )
                    break;
                p = q + strlen( name );
                q = strstr( p, "</div>" );
                if ( !q || (q > r) )
                    break;
                strncpy( list[num].folderName, p, q - p );
                list[num].folderName[q - p] = NUL;
                list[num].folderNumber = num + 1;
                num++;
            } while ( p < r );
        }
    }

    *numOfFolders = num;

    return ( list );
}


void
getClipInfo( const char *htmlSrc,
             MyClip     **mp,
             const char *tag,
             int        year,
             const char *objectID,
             char       *cookie,
             int        *numOfClips )
{
    int                 unit = MAX_DRECOM_RSS_PER_BLOCK;
    Thread  static int  cnt  = 0;
    const char          *p, *q, *r;
    char                articleID[64];
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
        strncpy( articleID, p, q - p );
        articleID[q - p] = NUL;

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

        getArticleDetail( articleID, objectID,
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

            num++;
        }
    } while ( p && *p );

    if ( num > 0 )
        *numOfClips += num;

    free( response );
}

void
getDrecomRSSclip(
        MyClip     **mp,
        const char *objectID,
        const char *folderName,
        int        folderNumber,
        int        year,
        char       *cookie,
        int        *numOfClips )
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
        getClipInfo( response, mp, tag, year,
                     objectID, cookie, numOfClips );

        // �w��t�H���_�E�w��N�̃N���b�v�ꗗ(��2�y�[�W�ڈȍ~)���擾
        for ( ++page; page <= totalPages; page++ ) {
            Sleep( 1000 );  /* �T�[�o�ւ̕��׏W������̂��� sleep */
            getArticleList( folderNumber, year, page, objectID,
                            response, sz, cookie );
            if ( !(*response) || !strstr( response, "\"error\":null" ) )
                break;      /* �擾���s */

            decodeContents( response );
            if ( !strstr( response, "<div class=\"articleRow\"" ) )
                continue;   /* �N���b�v�f�[�^�Ȃ� */

            getClipInfo( response, mp, tag, year,
                         objectID, cookie, numOfClips );
        }
    }

    free( response );
}

MyClip  *
getDrecomRSS(
        const char *userName,   /* (I) login���Ɏg�����[���A�h���X */
        const char *password,   /* (I) login���Ɏg���p�X���[�h     */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�    */
    )
{
    MyClip  *mp = NULL;
    char    *response;
    char    url[MAX_URLLENGTH];
    int     fd;
    int     num = 0;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    char    cookie[MAX_COOKIE_LEN];

    fd = fileno( stderr );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    // �h���R��RSS �� login
    if ( !loginDrecomRSS( userName, password, cookie ) ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "�h���R��RSS�ւ� login �Ɏ��s���܂���\n"
                    : "Drecom RSS: login failed.\n",
                   stderr );
        return ( mp );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �N���b�v���[�_�[ �ɃA�N�Z�X
    strcpy( url, "http://rss.drecom.jp/clip" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        FOLDER_LIST *list = NULL;
        int         numOfFolders = 0;

        // �t�H���_�ꗗ���擾
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
                // �e�t�H���_�ɂ��āA�N���Ƃ̃N���b�v�ꗗ���擾
                for ( i = 0; i < numOfFolders; i++) {
                    for (y = yyyy; y > 2003; y--) // �ŌẪN���b�v��2004�N3��
                        getDrecomRSSclip( &mp, objectID, list[i].folderName,
                                          i, y, cookie, &num );
                }
            }

            free( list );
        }
    }

    *numOfClips = num;

    free( response );

    return ( mp );
}

#ifdef  GET_DRECOM_RSS_EXE
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
                 "getDrecom: Drecom RSS �� Clip! �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tDrecom RSS �� Clip! ����z���o�������e�� OPML �t�@�C��"
                 "�Ƃ��ďo�͂���\n" );
        fprintf( stderr,
                 "    getDrecom [-x] -u ���[���A�h���X -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getDrecom: get bookmarks from Drecom RSS (Clip!), and "
                 "output them as OPML\n" );
        fprintf( stderr,
                 "    getDrecom [-x] -u mailaddress -p password\n" );
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

    /* Drecom RSS �� Clip! �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getDrecomRSS( username, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  Drecom RSS �� Clip! ���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "Drecom RSS", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_DRECOM_RSS_EXE */

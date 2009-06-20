/*
 *  DeleteDrecomRSS.cpp
 *      �h���R��RSS(Clip!) �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  22 Aug 2006
 *
 * $Log: /comm/bookey/DeleteDrecomRSS.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 16    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 15    07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 14    07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 13    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 12    06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() �𓱓��BMyClipEx �\���̊i�[�̈�m��
 * ���������ʊ֐������Ă݂�
 * 
 * 11    06/09/04 15:20 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 10    06/09/02 2:14 Tsujimura543
 * ����ς��Ē������邽�߁A�u�i�s�󋵃_�C�A���O�v�����ɖ߂�
 * (�� Visual Studio 2005 �ł��r���h���ē���m�F�����Ă݂��Ƃ���Acookie
 *     �i�[�̈�̃������I�[�o�[�����ɂ��A�X�^�b�N�t���[�����j�󂳂��
 *     ����̂������ŁA���X�̌��ۂ��������Ă��邱�Ƃ������Bcookie �܂��
 *     �̏����̉��C�ɂāA���ۂ��������Ȃ��Ȃ������Ƃ��m�F)
 * 
 * 9     06/09/02 2:12 Tsujimura543
 * ��������`�F�b�N�C��(�u�i�s�󋵁v�_�C�A���O�̕\������߂�ƁA���x��
 * �X�^�b�N�I�[�o�[�t���[�ŗ�����B���܂Ō����ĂȂ��������������ގ肪
 * ���肩?)
 * 
 * 8     06/09/01 19:07 Tsujimura543
 * ����Ƀ��t�@�N�^�����O (�܂��A�����킩�炸)
 * 
 * 7     06/09/01 1:27 Tsujimura543
 * �����ǋ������₷�����邽�߁A�������t�@�N�^�����O
 * 
 * 6     06/09/01 1:01 Tsujimura543
 * �Ƃ肠�����A�����͏��������ǁA�_�C�A���O�̃t�H�[�J�X���ς��Ƃ���ŕs
 * ���ȃ������Q�Ƃ��������ė������肪�c���Ă��� (���̂Ƃ���A�����s��)
 * 
 * 5     06/08/26 1:53 Tsujimura543
 * ���͂�C���N���[�h�s�v�ɂȂ����w�b�_�t�@�C���̃C���N���[�h����߂�
 * 
 * 4     06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 3     06/08/25 22:20 Tsujimura543
 * ���ۂɃu�b�N�}�[�N���擾���āA�폜���鏈���ȊO�̍�荞�݁A�I��
 * 
 * 2     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() �𓱓����A(�폜�p)�u�b�N�}�[�N���擾������
 * �ʃX���b�h������
 * 
 * 1     06/08/22 20:05 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"
#include "getDrecomRSS.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteDrecomRSS.cpp 1     09/05/14 3:48 tsupo $";
#endif

void
getClipInfo2( const char *htmlSrc,
              MyClipEx   **mp,
              const char *tag,
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

        p = r + 6;

        getArticleDetail( articleID, objectID,
                          response, sz, cookie );
        if ( *response ) {
            char        *s, *t;
            MyClipEx    *pp;

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

            pp = allocateMyClipExIfNecessary( mp, unit, &cnt,
                                              *numOfClips + num );
            if ( !pp )
                break;
            *mp = pp;

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

            pp = &((*mp)[*numOfClips + num]);
            strcpy( pp->title, utf2sjisEx(title) );
            if ( summary[0] )
                strcpy( pp->comment, utf2sjisEx(summary) );
            else
                pp->comment[0] = NUL;

            strcpy( pp->url,  href );
            strcpy( pp->tags, tag );

            strcpy( pp->entryID, articleID );
            strcpy( pp->remarks, objectID );

            num++;
        }
    } while ( p && *p );

    if ( num > 0 )
        *numOfClips += num;

    free( response );
}

void
getDrecomRSSclip2(
        MyClipEx   **mp,
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
        int     page = 1;

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
        getClipInfo2( response, mp, tag,
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

            getClipInfo2( response, mp, tag,
                          objectID, cookie, numOfClips );
        }
    }

    free( response );
}

MyClipEx    *
getDrecomRSS2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        *response;
    char        url[MAX_URLLENGTH];
    int         num = 0;
    size_t      sz  = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_DRECOM_RSS );

    // �h���R��RSS �� login
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginDrecomRSS( username, password, cookie ) ) {
        // login ���s
        return ( mp );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �N���b�v���[�_�[ �ɃA�N�Z�X
    text.LoadString(IDS_TXT_CONTINUE_GETTING_FOLDER);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �t�H���_�ꗗ�擾�� �c�c
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
            b = setObjectID( objectID, cookie );
            if ( b ) {
                CString text;
                text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
                pdlg->ChangeDialogText( bookmarkName,
                                        text ); // �u�b�N�}�[�N���擾�� �c�c

                // �e�t�H���_�ɂ��āA�N���Ƃ̃N���b�v�ꗗ���擾
                for ( i = 0; i < numOfFolders; i++ ) {
                    for (y = yyyy; y > 2003; y--) // �ŌẪN���b�v��2004�N3��
                        getDrecomRSSclip2( &mp, objectID, list[i].folderName,
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

BOOL
deleteEntryOnDrecomRSS( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    sprintf( request,
             "{\"method\": \"clip.deleteClip\", \"params\": "
             "[[\"%s\"]], \"objectID\": \"%s\"}",
             mp->entryID, mp->remarks );
    strcpy( url, "http://rss.drecom.jp/jsonrpc" );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "text/plain",
                 request, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}

/*
 *  DeleteMMmemo.cpp
 *      MM/Memo �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  1 Nov 2005
 *
 * $Log: /comm/bookey/DeleteMMmemo.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 26    07/06/29 13:49 Tsujimura543
 * http://1470.net/mm/ �� http://mmmemo.1470.net/mm/ �֕ύX
 * 
 * 25    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 24    07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 23    07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 22    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 21    06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 20    06/09/25 16:12 Tsujimura543
 * allocateMyClipExIfNecessary() �𓱓�(���t�@�N�^�����O�����{)
 * 
 * 19    06/08/26 1:53 Tsujimura543
 * ���͂�C���N���[�h�s�v�ɂȂ����w�b�_�t�@�C���̃C���N���[�h����߂�
 * 
 * 18    06/08/26 1:42 Tsujimura543
 * �C����̍폜������m�F (���Ȃ�)
 * 
 * 17    06/08/26 1:40 Tsujimura543
 * (1) deleteEntryOnMMmemo() ���Ŏ�M�o�b�t�@�I�[�o�[��������s����C��
 *     (�o�b�t�@�I�[�o�[�����h�~�@�\��g�ݍ���)
 * (2) ��L�C������A�폜�Ɏ��s����(delete_key ���擾�ł��Ȃ�)�s��𔭌��B
 *     �C�������{ (��M�o�b�t�@�T�C�Y�𑝂₵��)
 * 
 * 16    06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 15    06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() �𓱓����A(�폜�p)�u�b�N�}�[�N���擾������
 * �ʃX���b�h������
 * 
 * 14    06/08/22 17:21 Tsujimura543
 * �Ǝ��̍\���̂�p�~���AMyClipEx �𓱓�
 * 
 * 13    06/07/19 13:47 Tsujimura543
 * FEATURE_NOT_AVAILABLE �ȕ������폜 (1470.net���j���[�A���ł̓o���
 * MM/Memo ���̂� API �����̉\���͂Ȃ��Ȃ�������)
 * 
 * 12    06/07/03 15:15 Tsujimura543
 * ProceedingDialog ���݂̉��C (ProceedingDialog �� delete���ɗ�O��
 * �������邱�Ƃ����錏�̑΍���{)
 * 
 * 11    06/06/20 16:29 Tsujimura543
 * isWhiteSpace() �� myClip.h �ֈړ�
 * 
 * 10    06/06/19 20:31 Tsujimura543
 * m_pDlg->DestroyWindow(); ���R�����g�A�E�g
 * 
 * 9     06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 8     05/11/30 14:30 Tsujimura543
 * MAX_DESCRIPTION_LEN �̒�`�𓝈ꂵ�AxmlRPC.h �Ɉړ�
 * 
 * 7     05/11/11 13:19 Tsujimura543
 * �����������t�@�N�^�����O
 * 
 * 6     05/11/11 0:03 Tsujimura543
 * �u�u�b�N�}�[�N�폜���v�̕\����ǉ�
 * 
 * 5     05/11/10 21:21 Tsujimura543
 * �i�s�󋵕\���_�C�A���O���g���悤�ɂ���
 * 
 * 4     05/11/09 23:52 Tsujimura543
 * �]���ȃR�����g���폜
 * 
 * 3     05/11/09 23:48 Tsujimura543
 * �폜�����̎��������A����m�F�ς�
 * 
 * 2     05/11/09 21:24 Tsujimura543
 * getMMmemo2() ������ (�폜�������̂��͖̂�����)
 * 
 * 1     05/11/01 18:20 Tsujimura543
 * �ŏ��̔� (���ۂɍ폜���钼�O�܂Ŏ��s���A�폜���̂͂܂����s�����ɏI����
 * ���)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteMMmemo.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define skipWhiteSpace( p ) \
            while ( isWhiteSpace(*(p)) ) \
                (p)++;
#define skipNumber( p ) \
            while ( (*(p) >= '0') && (*(p) <= '9') ) \
                (p)++;
#define skipNonNumber( p ) \
            while ( (*(p) < '0') || (*(p) > '9') ) \
                (p)++;
#define skipToNextNumber( p ) \
            skipNumber(p); \
            skipNonNumber(p); \
            if ( *(p) == '0' ) \
                (p)++;

#define MAX_MEMO_PER_PAGE   50

long
getPostsOnMMmemo(
        const char *response,
        long       *numOfPosts,
        MyClipEx   *posts
    )
{
    long        num = 0;
    const char  *p = response, *q, *r, *s, *t;
    char        temp[MAX_DESCRIPTION_LEN];
    int         yyyy, mm, dd;
    int         preYyyy = 0, preMm = 0, preDd = 0;

    while ( *p ) {
        yyyy = 0;
        mm   = 0;
        dd   = 0;
        q = strstr( p, "<h2><span class=\"date\">" );
        r = strstr( p, "<h3>" );
        if ( !r )
            break;
        if ( q && r && (q < r) ) {
            // �N����
            s = strstr( q, "?date=" );
            if ( s && (s < r) ) {
                s += 6;
                yyyy = atol( s );

                skipToNextNumber(s);
                mm = atol( s );

                skipToNextNumber(s);
                dd = atol( s );
            }
        }
        if ( num > 0 ) {
            if ( yyyy == 0 ) {
                yyyy = preYyyy;
                mm   = preMm;
                dd   = preDd;
            }
        }
        preYyyy = yyyy;
        preMm   = mm;
        preDd   = dd;
        sprintf( posts[num].remarks, "%04d%02d%02d", yyyy, mm, dd );

        // genre
        p = r + 4;
        q = r;
        t = strstr( p, "</h3>" );
        if ( !t )
            break;
        posts[num].tags[0] = NUL;
        memset( temp, NUL, MAX_DESCRIPTION_LEN );
        while ( p < t ) {
            q = strstr( p, "?genre=" );
            if ( !q || (q > t) )
                break;
            q += 7;
            r = strstr( q, ">[" );
            if ( !r || (r > t) )
                break;
            r += 2;
            s = strstr( r, "]<" );
            if ( !s || (s > t) )
                break;
            if ( temp[0] )
                strcat( temp, " " );
            strncat( temp, r, s - r );
            p = s + 2;
        }
        if ( temp[0] ) {
            q = euc2sjis( temp );
            strcpy( posts[num].tags, q ? q : temp );
        }

        // href �� title
        q = strstr( p, sjis2euc( "�w" ) );
        if ( !q )
            break;
        p = q + 2;
        q = strstr( p, sjis2euc( "�x" ) );
        if ( !q )
            break;

        r = strstr( p, "<a href=\"" );
        if ( !r )
            break;
        r += 9;
        s = strchr( r, '"' );
        if ( !s )
            break;
        strncpy( posts[num].url, r, s - r );
        posts[num].url[s - r] = NUL;

        p = s + 1;
        s = strchr( p, '>' );
        if ( !s )
            break;
        s++;
        r = strstr( s, "</a>" );
        if ( !r )
            break;
        strncpy( temp, s, r - s );
        temp[r - s] = NUL;
        s = euc2sjis( temp );
        if ( s )
            strcpy( posts[num].title, s );
        else
            strcpy( posts[num].title, temp );
        p = q + 2;

        // ����ID
        q = strstr( p, "?memo=" );
        if ( !q )
            break;
        q += 6;
        r = strchr( q, '"' );
        if ( !r )
            break;
        strncpy( posts[num].entryID, q , r - q );
        posts[num].entryID[r - q] = NUL;
        p = r + 1;

        // �R�����g
        if ( p > t )
            break;
        p = t + 5;
        q = strstr( p, "<p>" );
        t = strstr( p, "<div class=\"" );
        if ( q && t && (q < t) ) {
            q += 4;
            skipWhiteSpace(q);
            r = strstr( q, "</p>" );
            if ( !r )
                break;
            p = r + 5;
            while ( isWhiteSpace(*(r - 1)) )
                r--;
            strncpy( temp, q, r - q );
            temp[r - q] = NUL;
            q = euc2sjis( temp );
            strcpy( posts[num].comment, q ? q : temp );
        }
        else
            posts[num].comment[0] = NUL;

        num++;
        if ( num >= *numOfPosts )
            break;
    }

    *numOfPosts = num;

    return ( num );
}

long
getRecentPostsOnMMmemo(
        const char       *username,     /* (I) ���[�U��                     */
        const char       *password,     /* (I) �p�X���[�h                   */
        char             *userID,       /* (I/O) ���[�UID                   */
        long             offset,        /* (I) �擾�J�n�ʒu(�y�[�W�ԍ�)     */
        long             *numOfPosts,   /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        MyClipEx         *posts,        /* (O) �擾�����u�b�N�}�[�N         */
        BOOL             *more,         /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
        char             *cookie,       /* (I/O) �N�b�L�[                   */
        ProceedingDialog *pdlg
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         (offset < 0) || !more )
        return ( num );

    sz = MAX_CONTENT_SIZE * 2;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    CString text;
    CString bookmarkName;
    bookmarkName.LoadString( IDS_TGT_MMMEMO );

    if ( offset == 0 ) {
        // MM/Memo �փ��O�C��
        text.LoadString(IDS_TXT_CONTINUE_CHECKING_TYPEKEY);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // TypeKey �F�ؒ� �c�c
        res = loginMMmemo( username, password, cookie, userID );
        if ( res == 0 ) {
            // ���O�C�����s
            free( response );
            return ( num );
        }

        // http://1470.net/mm/mylist.html �� GET
        //  -- http://1470.net/mm/ �� http://mmmemo.1470.net/mm/
        sprintf( url, "http://mmmemo.1470.net/mm/mylist.html/%s", userID );
    }
    else {
        // http://1470.net/mm/mylist.html/���[�UID?limit=50&page=�y�[�W�ԍ�
        // �� GET
        sprintf( url, "http://mmmemo.1470.net/mm/mylist.html/%s?limit=%d&page=%d",
                 userID, MAX_MEMO_PER_PAGE, offset + 1 );
    }

    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( response[0] != NUL ) {
        char    *p;

        p = response;
        if ( strstr( p, "-&gt;</a>" ) )
            *more = TRUE;
        else
            *more = FALSE;

        // �T�[�o����Ԃ��Ă��� html ����͂��āA�u�b�N�}�[�N�̃��X�g�𐶐�
        num = getPostsOnMMmemo( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}


/* MM/Memo �̑S�������擾 */
MyClipEx    *
getMMmemo2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp            = NULL;
    int         offset         = 0;
    int         total          = 0;
    BOOL        more           = TRUE;
    long        num            = MAX_MEMO_PER_PAGE;
    long        numOfBookmarks = 0;
    char        userID[32];

    do {
        MyClipEx    *newClip_p;

        total = *numOfClips;
        newClip_p = allocateMyClipExIfNecessary( &mp, num, &offset, total );
        if ( !newClip_p ) {
            more = FALSE;
            break;
        }
        mp = newClip_p;

        numOfBookmarks = getRecentPostsOnMMmemo( username, password, userID,
                                                 offset - 1, &num,
                                                 &(mp[num * (offset - 1)]),
                                                 &more,
                                                 cookie,
                                                 pdlg );
        *numOfClips += numOfBookmarks;
        num = MAX_MEMO_PER_PAGE;
    } while ( more == TRUE );

    return ( mp );
}

BOOL
deleteEntryOnMMmemo(
        char           *cookie,
        const MyClipEx *mp
    )
{
    BOOL    ret = FALSE;
    char    url[MAX_URLLENGTH];
    char    *request;
    char    *response;
    size_t  sz  = MAX_CONTENT_SIZE * 20;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    // http://1470.net/mm/memo_form.html?memo=����ID&delete=true �� GET
    setUpReceiveBuffer( response, sz );
    sprintf( url,
             "http://mmmemo.1470.net/mm/memo_form.html?memo=%s&delete=true",
             mp->entryID );
    http_getEx( url, response, cookie );
    if ( response[0] != NUL ) {
        char    *p, *q;
        char    checkKey[MAX_BLOGIDLENGTH + 1];
        char    deleteKey[MAX_BLOGIDLENGTH + 1];
        char    webpage[MAX_BLOGIDLENGTH + 1];

        checkKey[0]  = NUL;
        deleteKey[0] = NUL;
        webpage[0]   = NUL;

        // check_key ���擾
        p = strstr( response, "name=\"check_key\" value=\"" );
        if ( p ) {
            p += 24;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( checkKey, p, q - p );
                checkKey[q - p] = NUL;
            }
        }

        // delete_key ���擾
        p = strstr( response, "name=\"delete_key\" value=\"" );
        if ( p ) {
            p += 25;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( deleteKey, p, q - p );
                deleteKey[q - p] = NUL;
            }
        }

        // webpage ���擾
        p = strstr( response, "name=\"webpage\" value=\"" );
        if ( p ) {
            p += 22;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( webpage, p, q - p );
                webpage[q - p] = NUL;
            }
        }

        if ( checkKey[0] && deleteKey[0] && webpage[0] ) {
            // �폜���s
            setUpReceiveBuffer( response, sz );
            strcpy( url, "http://mmmemo.1470.net/mm/memo_form.html" );
            sprintf( request,
                     "memo=%s&"
                     "check_key=%s&"
                     "webpage=%s&",
                     mp->entryID, checkKey, webpage );
            sprintf( request + strlen( request ),
                     "delete=%s&"
                     "delete_key=%s",
                     sjis2euc( "�폜����" ), deleteKey );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );
            if ( response[0] )
                ret = TRUE;
        }
    }

    free( response );
    free( request );

    return ( ret );
}


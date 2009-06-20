/*
 *  DeleteNiftyClip.cpp
 *      �j�t�e�B�N���b�v �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  12 Jul 2006
 *
 * $Log: /comm/bookey/DeleteNiftyClip.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    08/11/11 17:18 Tsujimura543
 * NUM_OF_INFO_PER_NIFTY_API �̒�`�� niftyClip.h �ֈړ�
 * 
 * 18    08/11/11 16:16 Tsujimura543
 * GetNiftyClipWithApiKey() �� _getNiftyClipWithApiKey() �ɕύX���A
 * getNiftyClip.c �ֈڊ�
 * 
 * 17    08/11/11 15:10 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v����폜����v������ǉ��A����m�F����
 * 
 * 16    08/03/17 18:10 Tsujimura543
 * getScreenNameOnNiftyClip() �𓱓��B�\�[�X�𐮗�����
 * 
 * 15    08/03/12 5:05 Tsujimura543
 * 2008�N3��11���́u@nifty�N���b�v�v���j���[�A���ɑΉ�����
 * 
 * 14    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 13    07/01/19 18:25 Tsujimura543
 * _getNiftyClip() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 12    07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 11    07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 10    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 9     06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 8     06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() �𓱓��BMyClipEx �\���̊i�[�̈�m��
 * ���������ʊ֐������Ă݂�
 * 
 * 7     06/08/26 1:53 Tsujimura543
 * ���͂�C���N���[�h�s�v�ɂȂ����w�b�_�t�@�C���̃C���N���[�h����߂�
 * 
 * 6     06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 5     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() �𓱓����A(�폜�p)�u�b�N�}�[�N���擾������
 * �ʃX���b�h������
 * 
 * 4     06/08/22 17:21 Tsujimura543
 * �Ǝ��̍\���̂�p�~���AMyClipEx �𓱓�
 * 
 * 3     06/07/12 15:05 Tsujimura543
 * �]���ȏ������폜
 * 
 * 2     06/07/12 12:09 Tsujimura543
 * deleteEntryOnNiftyClip() ���� response ��������Y��Ă���
 * 
 * 1     06/07/12 12:02 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"
#include "niftyClip.h"
#include "DeleteBookmarkDialog4.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteNiftyClip.cpp 1     09/05/14 3:48 tsupo $";
#endif


/*
 *  API�L�[���g��Ȃ��폜����
 */

#define MAX_NIFTYCLIP_PER_BLOCK 200

MyClipEx    *
getNiftyClip2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        *response;
    long        num = 0;
    char        target[MAX_URLLENGTH];
    size_t      sz = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;
    int         total = 0;
    char        screenname[80];

    screenname[0] = NUL;
    *numOfClips   = 0;
    bookmarkName.LoadString( IDS_TGT_NIFTY_CLIP );

    // �j�t�e�B�N���b�v �փ��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginNiftyClip( username, password, cookie ) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �j�t�e�B�N���b�v�̃g�b�v�y�[�W���擾���A�u�b�N�}�[�N���[�U�����m�肷��
    // [��: �j�t�e�B�N���b�v�ł́A���O�C�����[�U��(@nifty ID �܂��� PLEASY ID)
    //      �Ƃ͕ʂɁA�u�b�N�}�[�N���[�U��(screenname)��ݒ�ł���]
    target[0] = NUL;
    getScreenNameOnNiftyClip( screenname, target,
                              response, sz, cookie );
    if ( target[0] == NUL ) {
        free( response );
        return ( mp );
    }

    // �u�b�N�}�[�N���擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    num = _getNiftyClip( target,
                         screenname[0] ? screenname : username,
                         cookie,
                         NULL, &mp, response, sz, &total );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnNiftyClip( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url, "http://clip.nifty.com/delete?bookmarkId=%s", mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}



/*
 *  API�L�[���g���폜����
 */

BOOL
deleteBookmarkOnNiftyClip(
        const char *apiKey, /* (I) API�L�[     */
        const char *url     /* (I) �폜�Ώ�URL */
    )
{
    BOOL    ret = FALSE;
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *request;
    char    *response;

    request  = (char *)malloc( strlen( url ) * 6 + BUFSIZ );
    if ( !request )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    // API�L�[ + URL
    sprintf( request,
             "api_key=%s&"
             "url=%s&"
             "alt=xml",
             apiKey,
             encodeURL( url ) );

    setUpReceiveBuffer( response, sz );
    http_post( "http://api.clip.nifty.com/api/v1/clip/delete",
               "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        char    *p = strstr( response, "<message>OK</message>" );
        if ( p )
            ret = TRUE;
    }

    free( response );
    free( request );

    return ( ret );
}

void
DeleteNiftyClip(
        const char       *apiKey,
        bool             withQuery /* = true */,
        ProceedingDialog *dlg      /* = NULL */
    )
{
    CString title;
    CString text;

    if ( withQuery == false ) {
        title.LoadString(IDS_TTL_DELETE_ALL_BOOKMARKS);
        text.LoadString( IDS_TXT_DELETE_ALL_BOOKMARKS);
        int r = MessageBox( NULL,
                            text,   // �{���Ƀu�b�N�}�[�N��S���폜���Ă��܂��Ă��\��Ȃ���ł���?
                            title,  // �u�b�N�}�[�N�폜�m�F
                            MB_YESNO|MB_ICONQUESTION );
        if ( r == IDNO )
            return;
    }

    CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
    long                num, n, nn;
    long                offset;
    BOOL                more = TRUE;
    BOOL                ret;
    bool                executeDelete;
    ProceedingDialog    *pdlg;
    MyClip              *posts   = new MyClip[NUM_OF_INFO_PER_NIFTY_API];
    BOOL                *deleted = new BOOL[NUM_OF_INFO_PER_NIFTY_API];
    CString             bookmarkName;

    if ( !posts || !deleted ) {
        if ( posts )
            delete [] posts;
        if ( deleted )
            delete [] deleted;
        return;
    }

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }
    bookmarkName.LoadString( IDS_TGT_NIFTY_CLIP );

    offset = 0;
    do {
        // �u�b�N�}�[�N�����擾
        text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
        pdlg->ShowWindow( SW_SHOWNORMAL );
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // �u�b�N�}�[�N���擾�� �c�c

        num = NUM_OF_INFO_PER_NIFTY_API;
        nn  = 0;
        memset( posts, 0x00, sizeof ( MyClip ) * num );

        n = _getNiftyClipWithApiKey( apiKey, offset, &num, posts, &more );
        if ( n <= 0 )
            break;

        // �u�b�N�}�[�N��1���Â폜
        int     i;
        for ( i = 0; i < n; i++ )
            deleted[i] = FALSE;
        for ( i = 0; i < n; i++ ) {
            if ( deleted[i] == TRUE )
                continue;
            if ( withQuery ) {
                pdlg->ShowWindow( SW_HIDE );

                // �u�b�N�}�[�N����\��
                DeleteBookmarkDialog4   d;

                d.m_url     = posts[i].url;
                d.m_title   = posts[i].title;
                d.m_comment = posts[i].comment;
                d.m_tags    = posts[i].tags;
                d.m_enableToBackward = (i == 0) ? false : true;
                d.m_backToPrevious   = false;

                if ( i > 0 ) {
                    int j = i - 1;
                    while ( (j >= 0) && deleted[j] )
                        j--;
                    if ( j < 0 )
                        d.m_enableToBackward = false;
                }

                int r = d.DoModal();
                if ( r == IDCANCEL ) {
                    more = FALSE;
                    executeDelete = false;
                    break;
                }
                if ( d.m_backToPrevious ) {
                    int j = i;
                    while ( (--i > 0) && deleted[i] )
                        ;
                    if ( deleted[i] == FALSE ) {
                        i--;
                        continue;
                    }
                    i = j;
                }
                if ( d.m_executeWithoutQuery == true ) {
                    title.LoadString(IDS_TTL_DELETE_ALL);
                    text.LoadString( IDS_TXT_DELETE_ALL);
                    r = MessageBox( NULL,
                                    text,   // �c��̃u�b�N�}�[�N��S����C�ɍ폜���Ă��܂��Ă��\��Ȃ��ł���?
                                    title,  // �u�b�N�}�[�N�ꊇ�폜�m�F
                                    MB_YESNO|MB_ICONQUESTION );
                    if ( r == IDYES )
                        withQuery = false;
                }
                if ( d.m_execute == false )
                    continue;
                executeDelete = d.m_execute;

                pdlg->ShowWindow( SW_SHOWNORMAL );
            }
            else
                executeDelete = true;

            // �폜�����s
            if ( executeDelete ) {
                text.LoadString(IDS_TXT_CONTINUE_DELETING);
                pdlg->ChangeDialogText( bookmarkName,
                                        text ); // �u�b�N�}�[�N�폜�� �c�c
                ret = deleteBookmarkOnNiftyClip( apiKey, posts[i].url );
                if ( ret == FALSE ) {
                    int r;

                    title.LoadString(IDS_TTL_FAILURE_DELETE_BOOKMARKS);
                    text.LoadString( IDS_TXT_FAILURE_DELETE_BOOKMARKS);
                    r = MessageBox( NULL,
                                    text,   // �u�b�N�}�[�N�̍폜�Ɏ��s���܂���    \r\n�����𑱍s���܂���?
                                    title,  // �u�b�N�}�[�N�폜���s
                                    MB_YESNO|MB_ICONWARNING );
                    if ( r == IDYES )
                        continue;
                    break;
                }
                nn++;
                deleted[i] = TRUE;
            }
        }

        offset += (n - nn);
    } while ( more == TRUE );

    if ( !dlg )
        delete pdlg;
    delete [] deleted;
    delete [] posts;
}

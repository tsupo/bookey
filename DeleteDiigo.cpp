/*
 *  DeleteDiigo.cpp
 *      Diigo �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  25 Jul 2008
 *
 * $Log: /comm/bookey/DeleteDiigo.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     08/07/26 0:17 Tsujimura543
 * �V�K�쐬 (���̂Ƃ���A�폜�ɐ������Ă��Ȃ�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog4.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
char    *encodeURLforJSON( const char *url );
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteDiigo.cpp 1     09/05/14 3:48 tsupo $";
#endif


/*
 *  Diigo ����w��u�b�N�}�[�N���폜����
 */

BOOL
deleteEntryOnDiigo(
        const char *username,   /* (I) ���[�U��                        */
        const char *password,   /* (I) �p�X���[�h                      */
        const char *url )       /* (I) �폜�Ώۃu�b�N�}�[�N(�Ώۂ�URL) */
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    targetUrl[MAX_URLLENGTH];
    int     sz = MAX_CONTENT_SIZE * 20;
    char    *URLforJSON = NUL;
    char    *urls  = NUL;
    char    *p;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    strcpy( targetUrl, "http://api2.diigo.com/bookmarks" );

    // URL
    URLforJSON = encodeURLforJSON( url );
#if 1
    sprintf( request,
             "[{\"url\":\"%s\"}]",
             URLforJSON );
    /* �� deleted: 0 bookmark ���Ԃ��Ă��� (�폜�ł��Ȃ�) */
#else
    sprintf( request,
             "[{\"%s\"}]",
             URLforJSON );
    /* �� API �d�l���ɏ����Ă�������ʂ�(�̂͂�)
          �Ȃ��� 400 Bad Request �ɂȂ�            */
#endif

    urls = (char *)malloc( strlen( request ) * 8 + 1 );
    if ( urls ) {
        sprintf( urls, "urls=%s", encodeURL(request) );

        setUpReceiveBuffer( response, sz );
        http_deleteBASIC( targetUrl, username, password,
                          "application/x-www-form-urlencoded",
                          urls, response );
        if ( *response ) {
            p = strstr( response, "deleted" );
            if ( p )
                ret = TRUE; /* �폜���� */
        }

        free( urls );
    }

    if ( URLforJSON )
        free( URLforJSON );

    free( response );
    free( request );

    return ( ret );
}


/*
 *  Diigo ����o�^�ς݃u�b�N�}�[�N���폜����
 */

void
DeleteDiigo(
        const char       *username,
        const char       *password,
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
    BOOL                ret;
    char                cookie[MAX_COOKIE_LEN];
    CBookeyApp          *pp = (CBookeyApp *)AfxGetApp();
    ProceedingDialog    *pdlg;
    CString             bookmarkName;

    bookmarkName.LoadString( IDS_TGT_DIIGO );
    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }

    cookie[0] = NUL;
    if ( (pp->m_bookmarkGotten == false)                   ||
         !(pp->m_myClip)                                   ||
         (pp->m_bookmarkName.Compare( bookmarkName ) != 0)    ) {
        // �u�b�N�}�[�N�����܂��擾���Ă��Ȃ��ꍇ
        text.LoadString(IDS_TXT_GET_BOOKMARKS);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // �u�b�N�}�[�N�擾������ �c�c
        if ( pp->m_myClip ) {
            pp->m_bookmarkGotten = false;
            pp->m_bookmarkName   = "";
            free( pp->m_myClip );
            pp->m_myClip = NULL;
        }
        pdlg->ShowWindow( SW_HIDE );

        /// �u�b�N�}�[�N�����擾
        pp->m_myClip = pp->m_diigo.GetBookmarks( pp->m_numOfClips,
                                                 username, password );
        if ( !(pp->m_myClip) ) {
            title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS);
            text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS);
            MessageBox( NULL,
                        text,   // �u�b�N�}�[�N�����擾�ł��܂���ł���
                        title,  // �u�b�N�}�[�N�擾���s
                        MB_OK|MB_ICONWARNING );
            if ( !dlg )
                delete pdlg;
            return;
        }

        pdlg->ShowWindow( SW_SHOWNORMAL );
        pp->m_bookmarkGotten = true;
        pp->m_bookmarkName   = bookmarkName;
    }

    // �u�b�N�}�[�N��1���Â폜
    BOOL    *deleted = new BOOL[pp->m_numOfClips];
    int     i;
    for ( i = 0; i < pp->m_numOfClips; i++ )
        deleted[i] = FALSE;
    for ( i = 0; i < pp->m_numOfClips; i++ ) {
        if ( deleted[i] == TRUE )
            continue;
        if ( withQuery ) {
            pdlg->ShowWindow( SW_HIDE );

            // �u�b�N�}�[�N����\��
            DeleteBookmarkDialog4   d;

            d.m_url     = pp->m_myClip[i].url;
            d.m_title   = pp->m_myClip[i].title;
            d.m_comment = pp->m_myClip[i].comment;
            d.m_tags    = pp->m_myClip[i].tags;
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
            if ( r == IDCANCEL )
                break;
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

            pdlg->ShowWindow( SW_SHOWNORMAL );
        }

        text.LoadString(IDS_TXT_CONTINUE_DELETING);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // �u�b�N�}�[�N�폜�� �c�c
        ret = deleteEntryOnDiigo( username, password, pp->m_myClip[i].url );
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
        deleted[i] = TRUE;
    }

    // �u�b�N�}�[�N����j��
    delete [] deleted;
    pp->m_bookmarkGotten = false;
    pp->m_bookmarkName   = "";
    free( pp->m_myClip );
    pp->m_myClip = NULL;

    if ( !dlg )
        delete pdlg;
}

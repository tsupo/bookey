/*
 *  DeleteLocalOpml.cpp
 *      ���[�J��OPML�t�@�C�� �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  26 Oct 2006
 *
 * $Log: /comm/bookey/DeleteLocalOpml.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     08/07/25 1:30 Tsujimura543
 * �u�b�N�}�[�N�폜��A�O���ɖ��폜�̃u�b�N�}�[�N���c���Ă��Ȃ��Ƃ�
 * �ł��A�u1�O�ɖ߂�v�{�^�����L���Ȃ܂܂ɂȂ��Ă��܂��s����C��
 * 
 * 7     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 6     07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 5     07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 4     07/01/04 18:54 Tsujimura543
 * ShowWindow() �̈������C��
 * 
 * 3     06/10/26 23:53 Tsujimura543
 * �R�����g���C��
 * 
 * 2     06/10/26 23:51 Tsujimura543
 * �u1�O�ɖ߂�v�Ŗ߂肷���Ă��܂����Ƃ�����(�������͂��̃u�b�N�}�[�N��
 * �\�������)�s��ɑΏ�
 * 
 * 1     06/10/26 22:37 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog4.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteLocalOpml.cpp 1     09/05/14 3:48 tsupo $";
#endif


/*
 *  ���[�J��OPML�t�@�C�� ����w��u�b�N�}�[�N���폜����
 */

BOOL
deleteEntryOnLocalOpml(
        const char *filename,   /* (I) ���[�J��OPML�t�@�C����          */
        const char *url         /* (I) �폜�Ώۃu�b�N�}�[�N(�Ώۂ�URL) */
    )
{
    BOOL    ret  = FALSE;
    BOOL    done = FALSE;
    FILE    *fp, *gp;

    fp = fopen( filename, "r" );
    if ( fp ) {
        gp = tmpfile();
        if ( gp ) {
            char    *p, *q;
            char    buf[MAX_CONTENT_SIZE];

            while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
                q = strstr( p, url );
                if ( q && (*(q - 1) == '"') && (*(q + strlen(url)) == '"') )
                    continue;
                fputs( p, gp );
            }

            done = TRUE;
        }

        fclose( fp );

        if ( gp ) {
            if ( done ) {
                fp = fopen( filename, "w" );
                if ( fp ) {
                    char    *p;
                    char    buf[BUFSIZ];

                    rewind( gp );
                    while ( ( p = fgets( buf, BUFSIZ - 1, gp ) ) != NULL )
                        fputs( p, fp );

                    fclose( fp );
                    ret = TRUE;
                }
            }

            fclose( gp );
        }
    }

    return ( ret );
}


/*
 *  ���[�J��OPML�t�@�C�� ����o�^�ς݃u�b�N�}�[�N���폜����
 */

void
DeleteLocalOpml(
        const char       *filename,
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
        if ( r == IDYES )
            unlink( filename );
        return;
    }

    CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
    BOOL                ret;
    CBookeyApp          *pp = (CBookeyApp *)AfxGetApp();
    ProceedingDialog    *pdlg;
    CString             bookmarkName;

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }
    bookmarkName.LoadString( IDS_TGT_LOCAL_OPML );

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
    pp->m_myClip = pp->m_localOpml.GetBookmarks( pp->m_numOfClips );
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
            char                    *p;

            d.m_url     = pp->m_myClip[i].url;

            p = utf2sjis( pp->m_myClip[i].title );
            d.m_title   = p ? p : pp->m_myClip[i].title;

            p = utf2sjis( pp->m_myClip[i].comment );
            d.m_comment = p ? p : pp->m_myClip[i].comment;

            p = utf2sjis( pp->m_myClip[i].tags );
            d.m_tags    = p ? p : pp->m_myClip[i].tags;

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
        ret = deleteEntryOnLocalOpml( filename, pp->m_myClip[i].url );
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

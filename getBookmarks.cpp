/*
 * getBookmarks.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      (�u�b�N�}�[�N�폜�p)�u�b�N�}�[�N���擾�X���b�h
 *          written by H.Tsujimura  25 Aug 2006
 *
 * $Log: /comm/bookey/getBookmarks.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    07/10/05 2:41 Tsujimura543
 * getEcNaviClip2() �̈����ǉ��ɔ����ύX
 * 
 * 14    07/09/13 22:30 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 13    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks �� Yahoo! �u�b�N�}�[�N�́u�폜�v�ɑΉ�
 * 
 * 12    07/03/30 14:09 Tsujimura543
 * FC2BOOKMARK �́u�폜�v�ɑΉ�
 * 
 * 11    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 10    07/02/16 16:35 Tsujimura543
 * �R�����g���C��
 * 
 * 9     06/12/25 23:23 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 8     06/12/21 22:31 Tsujimura543
 * JoltMark �Ή�
 * 
 * 7     06/10/05 22:30 Tsujimura543
 * POOKMARK Airlines �́u�폜�v�ɑΉ�
 * 
 * 6     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 5a    06/09/03 22:03 tsupo
 * �ĕ`��̂��߂̃��b�Z�[�W���[�v�𓖏��̂���(revision 2 ���_)�ɖ߂�
 * (�߂��Ă������Ȃ��Ȃ������Ƃ��m�F)
 * 
 * 5     06/09/03 5:54 tsupo
 * GetBookmarksForDelete() ����(revision 3 ���_)�ɖ߂�
 * (xmlRPC.dll �� cookie ���̏C���ɂĖ�肪������������)
 * 
 * 4     06/09/02 1:32 Tsujimura543
 * http �ʐM���ɂ� SetFocus() ���Ȃ��悤�ɂ�������A�܂�������(���Ƃ�����B
 * ���܂�100%�����Ă����̂��A�����Ȃ��Ȃ邱�Ƃ�����A���x�ɉ��P���ꂽ����
 * �������B���{�I�Ȍ�������������܂ŁA���炩�̎b��Ώ����K�v)
 * 
 * 3     06/09/02 1:17 Tsujimura543
 * �h���R��RSS(Clip!)�̎擾���� SetFocus() �ŗ����錏�́A�󋵏؋��ɂ��A
 * http �ʐM���s���� SetFocus() ����̂��܂����炵�����Ƃ������Bhttp �ʐM
 * ���s���łȂ��ꍇ�̂݁A���b�Z�[�W���[�v�������������s����悤�ɂ���
 * 
 * 2     06/08/25 19:25 Tsujimura543
 * �\�[�X�𐮌`
 *
 * 1     06/08/25 19:21 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "deleteBookmark.h"
#include <process.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBookmarks.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// (�폜�p)�u�b�N�}�[�N���̎擾
UINT
DeleteBookmarkSub( LPVOID pParam )
{
    // (�폜�p)�u�b�N�}�[�N���擾�X���b�h
    UINT        ret = 0;
    DBSparam_t  *p  = (DBSparam_t *)pParam;

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_MM_MEMO:
        // MM/Memo ����u�b�N�}�[�N�����擾
        p->myBookmark = getMMmemo2( p->u.username, p->u.password,
                                    p->cookie,
                                    &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_DRECOM_RSS:
        // �h���R��RSS ����u�b�N�}�[�N�����擾
        p->myBookmark = getDrecomRSS2( p->u.username, p->u.password,
                                       p->cookie,
                                       &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_FLOG:
        // Flog ����u�b�N�}�[�N�����擾
        p->myBookmark = getFlog2( p->u.username, p->u.password,
                                  p->cookie,
                                  &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP:
        // livedoor�N���b�v ����u�b�N�}�[�N�����擾
        p->myBookmark = getLivedoorClip2( p->u.username, p->u.password,
                                          p->cookie,
                                          &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_ECNAVI_CLIP:
        // Buzzurl ����u�b�N�}�[�N�����擾
        p->myBookmark = getEcNaviClip2( p->u.username,  p->u.password,
                                        p->u.username2, p->u.password2,
                                        p->u.authType,  p->cookie,
                                        &(p->cookieSize),
                                        &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_NIFTY_CLIP:
        // �j�t�e�B�N���b�v ����u�b�N�}�[�N�����擾
        p->myBookmark = getNiftyClip2( p->u.username, p->u.password,
                                       p->cookie,
                                       &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_1470NET:
        // 1470.net���j���[�A���� ����u�b�N�}�[�N�����擾
        p->myBookmark = get1470net2( p->u.username,  p->u.password,
                                     p->u.username2, p->u.password2,
                                     p->u.authType,  p->cookie,
                                     &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_POOKMARK:
        // POOKMARK Airlines ����u�b�N�}�[�N�����擾
        p->myBookmark = getPookmark2( p->u.username, p->u.password,
                                      p->cookie,
                                      &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_JOLTMARK:
        // JoltMark ����u�b�N�}�[�N�����擾
        p->myBookmark = getJoltMark2( p->u.username, p->u.password,
                                      p->cookie,
                                      &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_BLOGPET:
        // BlogPet �C�ɂȂ�L�� ����u�b�N�}�[�N�����擾
        p->myBookmark = getBlogPet2( p->u.username, p->u.password,
                                     p->cookie,
                                     &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_FC2BOOKMARK:
        // FC2BOOKMARK ����u�b�N�}�[�N�����擾
        p->myBookmark = getFC2bookmark2( p->u.username, p->u.password,
                                         p->cookie,
                                         &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_YJ_BOOKMARK:
        // Yahoo! �u�b�N�}�[�N ����u�b�N�}�[�N�����擾
        p->myBookmark = getYJbookmark2( p->u.username, p->u.password,
                                        p->cookie,
                                        &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_YAHOO_BOOKMARKS:
        // Yahoo! Bookmarks ����u�b�N�}�[�N�����擾
        p->myBookmark = getYahooBookmarks2( p->u.username, p->u.password,
                                            p->cookie,
                                            &(p->numOfBookmarks), p->dlg );
        break;

    default:
        // �͂Ăȃu�b�N�}�[�N�Adel.icio.us�ABlogPeople tags ��(�ʏ��)�u�b�N
        // �}�[�N�擾�������g�p���邽�߁A�{�X���b�h�𗘗p���邱�Ƃ͂Ȃ�
        break;
    }

    return ( ret );
}

MyClipEx  *
GetBookmarksForDelete( DBSparam_t *param,
                       int        &numOfMyBookmarks )
{
    MyClipEx    *p = NULL;
    CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

    // �u�b�N�}�[�N�擾�X���b�h���N��
    CWinThread  *tp = AfxBeginThread( DeleteBookmarkSub,
                                      (void *)param );
    if ( tp ) {
        DWORD       exitCode  = 0;
        int         status;
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

        // �u�b�N�}�[�N�擾�X���b�h���I������̂�҂�
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView �������� CBookeyDlg �̍ĕ`��
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog �̍ĕ`��
                param->dlg->SetFocus();
                param->dlg->UpdateWindow();

                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        if ( param->myBookmark ) {
            if ( param->numOfBookmarks > 0 ) {
                p = param->myBookmark;
                numOfMyBookmarks = param->numOfBookmarks;
            }
            else
                free( param->myBookmark );
        }

        delete tp;
    }

    return ( p );
}

/*
 * MainFrm.cpp : ソーシャルブックマーク管理プログラム
 *      CMainFrame クラスの動作の定義
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/MainFrm.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     09/01/19 23:55 Tsujimura543
 * ツールバーの右クリックメニューに「ブックマーク管理ツール起動」と
 * 「設定」を追加 (最小化状態からも起動できるようにした)
 * 
 * 8     08/10/22 13:35 Tsujimura543
 * タイトルバーを右クリックしたときに表示されるメニューに、「サポート」、
 * 「コミュニティ」、「バージョン情報」を追加
 * 
 * 7     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 6     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 5     05/10/25 19:20 Tsujimura543
 * メイン画面から「無題」の表示を削除
 * 
 * 4     05/10/24 21:42 Tsujimura543
 * クリップボードにテキストが入っていないときは、paste を disable
 * にするようにした
 * 
 * 3     05/10/20 23:48 Tsujimura543
 * 最大化ボタンを disable にする
 * 
 * 2     05/10/14 15:01 Tsujimura543
 * Window サイズを固定にする
 * 
 * 1     05/10/14 14:37 Tsujimura543
 * 新規作成 (ドラッグ・アンド・ドロップ機能サポート用)
 */

#include "bookey.h"
#include "MainFrm.h"
#include "AboutDlg.h"

#include "bookeyDoc.h"
#include "bookeyView.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/MainFrm.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    CMenu   *c;
    c = GetSystemMenu( FALSE );
    if ( c ) {
        c->AppendMenu(MF_SEPARATOR);
        CString strAboutMenu0;

        strAboutMenu0.LoadString(IDS_MANAGE_BOOKMARKS);
		c->AppendMenu(MF_STRING, IDM_MANAGE_BOOKMARKS, strAboutMenu0);
        strAboutMenu0.LoadString(IDS_EDIT_SETTING);
        c->AppendMenu(MF_STRING, IDM_EDIT_SETTING, strAboutMenu0);

        c->AppendMenu(MF_SEPARATOR);

		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT);
		c->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT2);
		c->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT2, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY);
		c->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY2);
		c->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY2, strAboutMenu0);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			c->AppendMenu(MF_SEPARATOR);
			c->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
    }

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~WS_SIZEBOX;    // Window サイズ変更禁止
    cs.style &= ~WS_MAXIMIZEBOX;// 最大化ボタンなし
    cs.style &= ~FWS_ADDTOTITLE;// 「無題」を消す

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ


void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        pCmdUI->Enable( FALSE );
    else
        pCmdUI->Enable( TRUE );
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CString cmd = "";

    switch (nID & 0xFFF0) {
    case IDM_ABOUTBOX:
        switch (nID) {
        case IDM_ABOUTBOX: {
            CAboutDlg dlgAbout;
            dlgAbout.DoModal(); }
            break;

        case IDM_ABOUT_SUPPORT:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_WEB_URL );
            /* fall into ... */
        case IDM_ABOUT_SUPPORT2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_SUPPORT );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_COMMUNITY );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_COMMUNITY2 );
            ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
            break;

        case IDM_MANAGE_BOOKMARKS: {
            CBookeyView *pView = (CBookeyView *)GetActiveView();
            if ( pView ) {
                pView->ManagementBookmark();
            } }
            break;
        case IDM_EDIT_SETTING: {
            CBookeyView *pView = (CBookeyView *)GetActiveView();
            if ( pView ) {
                pView->EditSetting();
            } }
            break;
        }
        break;

    default:
    	CFrameWnd::OnSysCommand(nID, lParam);
        break;
    }
}

/*
 * ProceedingDialog.cpp : ソーシャルブックマーク管理プログラム
 *      進行状況表示ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  10 Nov 2005
 *
 * $Log: /comm/bookey/ProceedingDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     07/09/05 11:56 Tsujimura543
 * ダイアログのタイトル、文言の変更のタイミングでログを出力するようにする
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 7     07/01/30 21:44 Tsujimura543
 * コメントを修正
 * 
 * 6     07/01/17 23:57 Tsujimura543
 * 英語モード対応
 * 
 * 5     07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 4     06/07/11 18:15 Tsujimura543
 * コメントを修正
 * 
 * 3     06/07/11 18:14 Tsujimura543
 * SetFocus() 絡みの修正を実施 (「実行中」ダイアログに focus が当たるよう
 * に調整した)
 * 
 * 2     06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 1     05/11/10 21:17 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "ProceedingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/ProceedingDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog ダイアログ

ProceedingDialog::ProceedingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ProceedingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ProceedingDialog)
	//}}AFX_DATA_INIT
}


void ProceedingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProceedingDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProceedingDialog, CDialog)
	//{{AFX_MSG_MAP(ProceedingDialog)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog 追加メソッド

void    ProceedingDialog::ChangeDialogText(
                const char *title,
                const char *message
            )
{
    SetWindowText( title );

    CStatic *sp = (CStatic *)GetDlgItem( IDC_STATIC_PROCEED_STRING );
    sp->SetWindowText( message );

    SetFocus();

    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
    if ( bp->m_verboseFp && (bp->m_verboseFp != stdout) )
        fprintf( bp->m_verboseFp, ">>> %s: %s\n", title, message );
}

void    ProceedingDialog::ResetDialogText()
{
    CString text;
    text.LoadString(IDS_TXT_CONTINUE_PROCEEDING);
    ChangeDialogText( text, text );
}

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog メッセージ ハンドラ

void ProceedingDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CButton *bp = (CButton *)GetDlgItem( IDCANCEL );
        bp->ShowWindow( SW_HIDE );
    }
}

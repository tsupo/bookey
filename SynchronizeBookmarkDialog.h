/*
 * SynchronizeBookmarkDialog.h  : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その1 ヘッダーファイル
 *          written by H.Tsujimura  11 Oct 2005
 *
 * $Log: /comm/bookey/SynchronizeBookmarkDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 5     06/02/08 19:20 Tsujimura543
 * 4つのブックマークのうちの任意の2つの間の同期を取ることを指示できるよう
 * にした
 * 
 * 4     05/10/14 17:01 Tsujimura543
 * コメントを修正
 * 
 * 3     05/10/11 17:16 Tsujimura543
 * ファイル名を変更 (Syncronize… → Synchronize…)
 * 
 * 2     05/10/11 17:06 Tsujimura543
 * ブックマーク同期処理の実装開始
 */

#if !defined(AFX_SYNCHRONIZEBOOKMARKDIALOG_H__62AC5641_D301_497A_B5FD_589763E07167__INCLUDED_)
#define AFX_SYNCHRONIZEBOOKMARKDIALOG_H__62AC5641_D301_497A_B5FD_589763E07167__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// SynchronizeBookmarkDialog ダイアログ

class SynchronizeBookmarkDialog : public CDialog
{
// コンストラクション
public:
	SynchronizeBookmarkDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

    enum    {
        fromBM1toBM2 = 0,
        fromBM2toBM1,
        both
    }       m_direction;

// ダイアログ データ
	//{{AFX_DATA(SynchronizeBookmarkDialog)
	enum { IDD = IDD_SYNC_DIALOG };
	CComboBox	m_bookmarkList2;
	CComboBox	m_bookmarkList1;
	CButton	m_description;
	CString	m_bookmark1;
	CString	m_bookmark2;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SynchronizeBookmarkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    ChangeButtons( const char *bookmark1 /* = NULL */,
                           const char *bookmark2 /* = NULL */  );

	// メッセージマップ関数
	//{{AFX_MSG(SynchronizeBookmarkDialog)
	afx_msg void OnButtonSync1();
	afx_msg void OnButtonSync2();
	afx_msg void OnButtonSync3();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeBm1();
	afx_msg void OnSelchangeBm2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SynchronizeBookmarkDialog( SynchronizeBookmarkDialog &dlg );
    SynchronizeBookmarkDialog   operator = ( SynchronizeBookmarkDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SYNCHRONIZEBOOKMARKDIALOG_H__62AC5641_D301_497A_B5FD_589763E07167__INCLUDED_)

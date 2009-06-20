/*
 * DeleteBookmarkDialog4.h  : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その4 ヘッダーファイル
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog4.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 4     06/09/04 18:15 Tsujimura543
 * 「1個前へ戻る」機能を追加
 * 
 * 3     05/10/11 19:07 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 2     05/10/03 22:17 Tsujimura543
 * del.icio.us のブックマークを削除する処理を実装
 */

#if !defined(AFX_DELETEBOOKMARKDIALOG4_H__4E5F3A1F_3D38_4AB4_AE28_AB3149996690__INCLUDED_)
#define AFX_DELETEBOOKMARKDIALOG4_H__4E5F3A1F_3D38_4AB4_AE28_AB3149996690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog4 ダイアログ

class DeleteBookmarkDialog4 : public CDialog
{
// コンストラクション
public:
	DeleteBookmarkDialog4(CWnd* pParent = NULL);   // 標準のコンストラクタ

    bool    m_execute;
    bool    m_executeWithoutQuery;
    bool    m_enableToBackward;
    bool    m_backToPrevious;
    CString m_messageOnQuery;
    CString m_windowTextExtra;

// ダイアログ データ
	//{{AFX_DATA(DeleteBookmarkDialog4)
	enum { IDD = IDD_DELETE_DIALOG4 };
	CString	m_url;
	CString	m_title;
	CString	m_tags;
	CString	m_comment;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(DeleteBookmarkDialog4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(DeleteBookmarkDialog4)
	afx_msg void OnButtonDeleteYes();
	afx_msg void OnButtonDeleteNo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonDeleteForcely();
	afx_msg void OnButtonBackword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    DeleteBookmarkDialog4( DeleteBookmarkDialog4 &dlg );
    DeleteBookmarkDialog4   operator = ( DeleteBookmarkDialog4 &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETEBOOKMARKDIALOG4_H__4E5F3A1F_3D38_4AB4_AE28_AB3149996690__INCLUDED_)

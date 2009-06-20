/*
 * DeleteBookmarkDialog3.h  : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その3 ヘッダーファイル
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog3.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 10    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 9     06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 8     06/06/01 19:04 Tsujimura543
 * ブックマーク種別を示す enum 値を、enum CUserInfo::bookmarkType に
 * 一本化した
 * 
 * 7     06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 6     06/03/29 18:30 Tsujimura543
 * ドリコムRSSへのブックマーク(Clip)登録に対応した
 * 
 * 5     05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 4     05/10/21 18:44 Tsujimura543
 * MM/Memo と BlogPeople に対応
 * 
 * 3     05/10/11 16:56 Tsujimura543
 * ブックマーク同期処理の実装開始
 * 
 * 2     05/10/03 18:56 Tsujimura543
 * ブックマーク削除実行時に使う「ユーザ名、パスワード入力画面」を作成
 */

#if !defined(AFX_DELETEBOOKMARKDIALOG3_H__9980C414_4753_4BA3_A0EB_63A14C625B7D__INCLUDED_)
#define AFX_DELETEBOOKMARKDIALOG3_H__9980C414_4753_4BA3_A0EB_63A14C625B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog3 ダイアログ

class DeleteBookmarkDialog3 : public CDialog
{
// コンストラクション
public:
    DeleteBookmarkDialog3(CWnd* pParent = NULL);   // 標準のコンストラクタ

    enum CUserInfo::bookmarkType    m_targetBookmark;
    CString                         m_messageOnCancel;

// ダイアログ データ
	//{{AFX_DATA(DeleteBookmarkDialog3)
	enum { IDD = IDD_DELETE_DIALOG3 };
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(DeleteBookmarkDialog3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(DeleteBookmarkDialog3)
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    DeleteBookmarkDialog3( DeleteBookmarkDialog3 &dlg );
    DeleteBookmarkDialog3   operator = ( DeleteBookmarkDialog3 &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETEBOOKMARKDIALOG3_H__9980C414_4753_4BA3_A0EB_63A14C625B7D__INCLUDED_)

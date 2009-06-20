/*
 * DeleteBookmarkDialog.h  : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その1 ヘッダーファイル
 *          written by H.Tsujimura  30 Sep 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 14    08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 13    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 12    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks と Yahoo! ブックマークの「削除」に対応
 * 
 * 11    07/01/12 22:45 Tsujimura543
 * 英語モード対応
 * 
 * 10    06/08/22 11:43 Tsujimura543
 * DeleteBookmarkDialog と DeleteBookmarkDialog2 を1個のダイアログに
 * まとめた (DeleteBookmarkDialog2 は廃止)
 * 
 * 9     06/07/12 9:33 Tsujimura543
 * livedoorクリップ、ECナビ人気ニュース、ニフティクリップの削除ボタンを追
 * 加
 * 
 * 8     06/06/27 15:24 Tsujimura543
 * Flog の削除に対応
 * 
 * 7     06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 6     06/06/01 19:04 Tsujimura543
 * ブックマーク種別を示す enum 値を、enum CUserInfo::bookmarkType に
 * 一本化した
 * 
 * 5     05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 4     05/10/31 21:42 Tsujimura543
 * MM/Memo と BlogPeople Tags の削除に対応
 * 
 * 3     05/10/11 17:01 Tsujimura543
 * 初版のタイムスタンプ表記ミスを修正 (コメントのみの修正。動作に影響なし)
 * 
 * 2     05/09/30 23:57 Tsujimura543
 * ブックマークの取得、登録機能の動作確認完了
 */

#if !defined(AFX_DELETEBOOKMARKDIALOG_H__21477E33_8E0E_45CF_9E6F_024EB274E64E__INCLUDED_)
#define AFX_DELETEBOOKMARKDIALOG_H__21477E33_8E0E_45CF_9E6F_024EB274E64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog ダイアログ

class DeleteBookmarkDialog : public CDialog
{
// コンストラクション
public:
	DeleteBookmarkDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

    enum CUserInfo::bookmarkType    m_targetBookmark;
    bool                            m_deleteAll;
    bool                            m_deleteInteractive;

// ダイアログ データ
	//{{AFX_DATA(DeleteBookmarkDialog)
	enum { IDD = IDD_DELETE_DIALOG };
	CComboBox	m_bookmark;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(DeleteBookmarkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_blogPet;
    CString m_tgt_fc2Bookmark;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_diigo;
    CString m_tgt_localOPML;

	// メッセージマップ関数
	//{{AFX_MSG(DeleteBookmarkDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonDeleteInteractive();
	afx_msg void OnButtonDeleteAll();
	afx_msg void OnSelchangeComboDeleteList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    DeleteBookmarkDialog( DeleteBookmarkDialog &dlg );
    DeleteBookmarkDialog    operator = ( DeleteBookmarkDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETEBOOKMARKDIALOG_H__21477E33_8E0E_45CF_9E6F_024EB274E64E__INCLUDED_)

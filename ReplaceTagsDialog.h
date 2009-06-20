/*
 * ReplaceTagsDialog.h  : ソーシャルブックマーク管理プログラム
 *      タグ置換ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  24 Jan 2006
 *
 * $Log: /comm/bookey/ReplaceTagsDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 4     08/07/25 18:44 Tsujimura543
 * Diigo 対応準備
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/01/29 18:04 Tsujimura543
 * ユーザインターフェースの細部を詰める必要が残っているが、とりあえず、
 * 使えるものが完成
 * 
 * 1     07/01/24 21:01 Tsujimura543
 * 新規作成 (スケルトン)
 */

#if !defined(AFX_REPLACETAGSDIALOG_H__7DECEF52_ED77_4E69_A834_DE2F53423A0D__INCLUDED_)
#define AFX_REPLACETAGSDIALOG_H__7DECEF52_ED77_4E69_A834_DE2F53423A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReplaceTagsDialog ダイアログ

class CReplaceTagsDialog : public CDialog
{
// コンストラクション
public:
	CReplaceTagsDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CReplaceTagsDialog)
	enum { IDD = IDD_REPLACE_TAGS_DIALOG };
	CComboBox	m_bookmarkList;
	CComboBox	m_tagList;
	CString	m_newTag;
	CString	m_oldTag;
	CString	m_bookmarkName;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CReplaceTagsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    int                             m_tagIndex;
    int                             m_numOfTags;
    enum CUserInfo::bookmarkType    m_targetBookmark;

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
    CString m_tgt_diigo;
    CString m_tgt_localOPML;

	// メッセージマップ関数
	//{{AFX_MSG(CReplaceTagsDialog)
	afx_msg void OnButtonGetTags();
	afx_msg void OnReplaceTags();
	afx_msg void OnSelchangeComboDeleteTaglist();
	afx_msg void OnSelchangeComboDeletelistTags();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillfocusEditNewTag();
	afx_msg void OnUpdateEditNewTag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CReplaceTagsDialog( CReplaceTagsDialog &dlg );
    CReplaceTagsDialog  operator = ( CReplaceTagsDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_REPLACETAGSDIALOG_H__7DECEF52_ED77_4E69_A834_DE2F53423A0D__INCLUDED_)

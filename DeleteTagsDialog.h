/*
 * DeleteTagsDialog.h  : ソーシャルブックマーク管理プログラム
 *      タグ削除ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  24 Jan 2006
 *
 * $Log: /comm/bookey/DeleteTagsDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 4     08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/01/29 17:53 Tsujimura543
 * ユーザインターフェースの細部を詰める必要が残っているが、とりあえず、
 * 使えるものが完成
 * 
 * 1     07/01/24 21:01 Tsujimura543
 * 新規作成 (スケルトン)
 */

#if !defined(AFX_DELETETAGSDIALOG_H__8E7F715D_4E8D_4ACA_A71B_3F0306CD1C09__INCLUDED_)
#define AFX_DELETETAGSDIALOG_H__8E7F715D_4E8D_4ACA_A71B_3F0306CD1C09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDeleteTagsDialog ダイアログ

class CDeleteTagsDialog : public CDialog
{
// コンストラクション
public:
	CDeleteTagsDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDeleteTagsDialog)
	enum { IDD = IDD_DELETE_TAGS_DIALOG };
	CComboBox	m_bookmarkList;
	CComboBox	m_tagList;
	CString	m_bookmarkName;
	CString	m_tag;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CDeleteTagsDialog)
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
	//{{AFX_MSG(CDeleteTagsDialog)
	afx_msg void OnButtonGetTags();
	afx_msg void OnDeleteTags();
	afx_msg void OnSelchangeComboDeleteTaglist();
	afx_msg void OnSelchangeComboDeletelistTags();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDeleteTagsDialog( CDeleteTagsDialog &dlg );
    CDeleteTagsDialog   operator = ( CDeleteTagsDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETETAGSDIALOG_H__8E7F715D_4E8D_4ACA_A71B_3F0306CD1C09__INCLUDED_)

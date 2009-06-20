/*
 * bookeyDlg.h  : ソーシャルブックマーク管理プログラム
 *      メインダイアログ ヘッダーファイル
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookeyDlg.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 35    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 34    08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 33    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 32    07/04/20 20:34 Tsujimura543
 * Yahoo! ブックマーク、Yahoo! Bookmarks のインポートとエクスポートに対応
 * 
 * 31    07/04/16 18:23 Tsujimura543
 * コメントを修正
 * 
 * 30    07/04/16 17:59 Tsujimura543
 * del.icio.us の posts/all 形式の XML ファイルのインポートとエクスポート
 * に対応した
 * 
 * 29    07/03/29 15:18 Tsujimura543
 * FC2BOOKMARK に対応した
 * 
 * 28    07/01/24 20:55 Tsujimura543
 * 「タグの削除」と「タグの置換」ボタンを各々追加
 * 
 * 27    07/01/12 23:34 Tsujimura543
 * 英語モード対応
 * 
 * 26    06/11/16 16:43 Tsujimura543
 * CUserInfo 導入によるリファクタリング第16段階、終了
 * 
 * 25    06/11/16 14:06 Tsujimura543
 * CBookeyDlg クラス内のメンバ変数のうち、もはや不要になったものを削除
 * 
 * 24    06/11/16 14:02 Tsujimura543
 * CUserInfo 導入によるリファクタリング第15段階、終了
 * 
 * 23    06/11/10 19:26 Tsujimura543
 * ブラウザのブックマークを取り込む/ブラウザに取り込める形式のブックマーク
 * ファイルを生成する機能をサポートするための準備
 * 
 * 22    06/08/23 22:10 Tsujimura543
 * 1470.netリニューアル版の「削除」時にユーザ情報を設定した場合、
 * その設定内容を初期設定ファイルに反映できるようにした
 * 
 * 21    06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 20    06/06/15 12:51 Tsujimura543
 * EnableButton() を追加
 * 
 * 19    06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 18    06/06/06 22:23 Tsujimura543
 * CUserInfo 導入によるリファクタリング第2段階、終了
 * 
 * 17    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 16    06/06/01 20:28 Tsujimura543
 * CBookeyDlg 内のユーザ名、パスワードを CUserInfo を使って管理する
 * ように変更した
 * 
 * 15    06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 14    06/03/29 18:30 Tsujimura543
 * ドリコムRSSへのブックマーク(Clip)登録に対応した
 * 
 * 13    06/02/17 18:11 Tsujimura543
 * ImportFromAnotherToMMmemo() と ImportFromAnotherToBPtags() を追加
 * 
 * 12    06/02/17 18:07 Tsujimura543
 * ブックマークの同期を、はてなブックマークとdel.icio.us以外にも容易に対応
 * 可能にするため、処理の抽象化を進めた
 * 
 * 11    05/11/10 22:25 Tsujimura543
 * 進行状況表示ダイアログを使うようにした
 * 
 * 10    05/10/28 14:45 Tsujimura543
 * DeleteBlogPeopleTags(), DeleteMMmemoBookmark() を追加
 * 
 * 9     05/10/21 18:57 Tsujimura543
 * MM/Memo と BlogPeople のユーザ名、パスワードも bookeyView から
 * 受け取れるようにした
 * 
 * 8     05/10/15 0:41 Tsujimura543
 * はてなとdel.icio.usのユーザ名、パスワードを bookeyView から受け取れる
 * ようにした
 * 
 * 7     05/10/11 19:07 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 6     05/10/11 16:56 Tsujimura543
 * ブックマーク同期処理の実装開始
 * 
 * 5     05/10/03 22:59 Tsujimura543
 * はてなブックマークを削除する処理を実装
 * 
 * 4     05/10/03 22:17 Tsujimura543
 * del.icio.us のブックマークを削除する処理を実装
 * 
 * 3     05/10/03 21:02 Tsujimura543
 * ブックマーク削除処理の実装開始
 * 
 * 2     05/09/30 23:57 Tsujimura543
 * ブックマークの取得、登録機能の動作確認完了
 */

#if !defined(AFX_BOOKEYDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)
#define AFX_BOOKEYDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#ifdef __cplusplus
}
#endif

#include "ProceedingDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg ダイアログ

class CBookeyDlg : public CDialog
{
// 構築
public:
	CBookeyDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CBookeyDlg)
	enum { IDD = IDD_BOOKEY_DIALOG };
	CComboBox	m_bookmarkList2;
	CComboBox	m_bookmarkList1;
	CString	m_bookmark1;
	CString	m_bookmark2;
	CString	m_password1;
	CString	m_password2;
	CString	m_username1;
	CString	m_username2;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBookeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
    bool    m_needToSave;

protected:
	HICON   m_hIcon;

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
    CString m_tgt_fc2bookmark;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_diigo;
    CString m_tgt_opml;
    CString m_tgt_netscape1;
    CString m_tgt_opera6;
    CString m_tgt_hatenaFeed;
    CString m_tgt_livedoorFeed;
    CString m_tgt_deliciousXML;

    void    ChangeButtonGet();
    void    ChangeButtonPut();
    void    EnableButton( bool enable );

	// メッセージマップ関数
	//{{AFX_MSG(CBookeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonPut();
	afx_msg void OnButtonSync();
	afx_msg void OnSelchangeComboBookmark1();
	afx_msg void OnSelchangeComboBookmark2();
	afx_msg void OnKillfocusEditPassword1();
	afx_msg void OnKillfocusEditPassword2();
	afx_msg void OnKillfocusEditUsername1();
	afx_msg void OnKillfocusEditUsername2();
	afx_msg void OnUpdateEditUsername1();
	afx_msg void OnUpdateEditPassword1();
	afx_msg void OnUpdateEditUsername2();
	afx_msg void OnUpdateEditPassword2();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonEditTags();
	afx_msg void OnButtonDeleteTags();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CBookeyDlg( CBookeyDlg &dlg );
    CBookeyDlg  operator = ( CBookeyDlg &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEYDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)

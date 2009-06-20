/*
 * AboutDlg.h  : ソーシャルブックマーク管理プログラム
 *      版数(バージョン番号)表示ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/AboutDlg.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     09/02/24 16:40 Tsujimura543
 * 「Yahoo! Japan Web サービス」のクレジット表示を追加
 * 
 * 5     09/01/19 23:55 Tsujimura543
 * ツールバーの右クリックメニューに「ブックマーク管理ツール起動」と
 * 「設定」を追加 (最小化状態からも起動できるようにした)
 * 
 * 4     08/10/22 13:33 Tsujimura543
 * IDM_ABOUT_SUPPORT, IDM_ABOUT_SUPPORT2,
 * IDM_ABOUT_COMMUNITY, IDM_ABOUT_COMMUNITY2
 * の定義を bookeyDlg.cpp から移管
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     06/06/27 12:07 Tsujimura543
 * blog の URL、メールアドレスをクリックすると、ブラウザ、メーラを立ち上げ
 * るようにした
 * 
 * 1     05/10/14 14:11 Tsujimura543
 * bookey.cpp および bookeyDlg.cpp から分離、独立させた
 */

#if !defined(AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)
#define AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	~CAboutDlg();

    HCURSOR m_hCursor;
    CFont   m_cFont;

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnBookeyMailAddr();
	afx_msg void OnBookeyWebUrl();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCreditYahooJapan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CAboutDlg( CAboutDlg &dlg );
    CAboutDlg   operator = ( CAboutDlg &dlg );
};

#define IDM_ABOUT_SUPPORT       (IDM_ABOUTBOX + 1)
#define IDM_ABOUT_SUPPORT2      (IDM_ABOUTBOX + 2)
#define IDM_ABOUT_COMMUNITY     (IDM_ABOUTBOX + 3)
#define IDM_ABOUT_COMMUNITY2    (IDM_ABOUTBOX + 4)

#define IDM_MANAGE_BOOKMARKS    (IDM_ABOUTBOX + 9)
#define IDM_EDIT_SETTING        (IDM_ABOUTBOX + 10)

#endif  // AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

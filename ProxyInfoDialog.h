/*
 * ProxyInfoDialog.h  : ソーシャルブックマーク管理プログラム
 *      proxy情報設定ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/ProxyInfoDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/03/14 16:17 Tsujimura543
 * 「ブログクライアント BloGolEe」用に書いたソースを取り込む
 * =======================================================================
 * 2     07/03/10 5:22 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応してみた
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_)
#define AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog ダイアログ

class CProxyInfoDialog : public CDialog
{
// コンストラクション
public:
	CProxyInfoDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CProxyInfoDialog)
	enum { IDD = IDD_DIALOG_PROXY_INFO };
	CString	m_proxyServerName;
	UINT	m_proxyPortNumber;
	CString	m_proxyUserName;
	CString	m_proxyPassword;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CProxyInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    switchOK();

	// メッセージマップ関数
	//{{AFX_MSG(CProxyInfoDialog)
	afx_msg void OnUpdateEditProxyPortNumber();
	afx_msg void OnUpdateEditProxyServerName();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateEditProxyUserName();
	afx_msg void OnUpdateEditProxyPassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CProxyInfoDialog( CProxyInfoDialog &dlg );
    CProxyInfoDialog    operator = ( CProxyInfoDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_)

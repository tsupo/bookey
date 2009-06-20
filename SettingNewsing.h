/*
 * SettingNewsing.h  : ソーシャルブックマーク管理プログラム
 *      SettingNewsing クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingNewsing.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/10/11 19:31 Tsujimura543
 * Yahoo! Japan の ID で newsing を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 1     06/09/29 18:41 Tsujimura543
 * 新規作成 (newsing 対応)
 */

#if !defined(AFX_SETTINGNEWSING_H__084A0DEF_37B8_4E9B_A605_F12385D5E316__INCLUDED_)
#define AFX_SETTINGNEWSING_H__084A0DEF_37B8_4E9B_A605_F12385D5E316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingNewsing ダイアログ

class SettingNewsing : public CTabDialog
{
// コンストラクション
public:
	SettingNewsing(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得
    void    SetAuthType();

// ダイアログ データ
	//{{AFX_DATA(SettingNewsing)
	enum { IDD = IDD_TAB_NEWSING };
	CString	m_yahooJapanID;
	CString	m_yahooJapanPassword;
	//}}AFX_DATA

    AUTH_TYPE   m_auth;     // 認証方法 (default は AK_ORIGINAL)

// オーバーライド
	//{{AFX_VIRTUAL(SettingNewsing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingNewsing)
	afx_msg void OnRadioUseNewsing();
	afx_msg void OnRadioUseYj();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingNewsing( SettingNewsing &dlg );
    SettingNewsing  operator = ( SettingNewsing &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGNEWSING_H__084A0DEF_37B8_4E9B_A605_F12385D5E316__INCLUDED_)

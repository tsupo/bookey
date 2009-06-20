/*
 * SettingTumblr.h  : ソーシャルブックマーク管理プログラム
 *      SettingTumblr クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  31 Oct 2007
 *
 * $Log: /comm/bookey/SettingTumblr.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 2     09/05/29 0:23 Tsujimura543
 * 投稿先 tumbleblog を(プライマリ以外からも)選択可能にした
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/10/31 16:50 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGTUMBLR_H__E423AC98_FC72_4E34_877A_7B45B0E895D1__INCLUDED_)
#define AFX_SETTINGTUMBLR_H__E423AC98_FC72_4E34_877A_7B45B0E895D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

#define MAX_BLOGS       30  /* 暫定値 */

/////////////////////////////////////////////////////////////////////////////
// SettingTumblr ダイアログ

class SettingTumblr : public CTabDialog
{
// コンストラクション
public:
	SettingTumblr(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

    CString m_blogID;

// ダイアログ データ
	//{{AFX_DATA(SettingTumblr)
	enum { IDD = IDD_TAB_TUMBLR };
	CString	m_blogName;
	//}}AFX_DATA

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(SettingTumblr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(SettingTumblr)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonSelectTarget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingTumblr( SettingTumblr &dlg );
    SettingTumblr  operator = ( SettingTumblr &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTUMBLR_H__E423AC98_FC72_4E34_877A_7B45B0E895D1__INCLUDED_)

/*
 * SettingDigg.h  : ソーシャルブックマーク管理プログラム
 *      SettingDigg クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/SettingDigg.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 1     07/07/09 19:11 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGDIGG_H__60D32F03_A07D_466F_9E24_CE37BBA8DD3A__INCLUDED_)
#define AFX_SETTINGDIGG_H__60D32F03_A07D_466F_9E24_CE37BBA8DD3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDigg ダイアログ

class SettingDigg : public CTabDialog
{
// コンストラクション
public:
	SettingDigg(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingDigg)
	enum { IDD = IDD_TAB_DIGG };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingDigg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingDigg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDigg( SettingDigg &dlg );
    SettingDigg operator = ( SettingDigg &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIGG_H__60D32F03_A07D_466F_9E24_CE37BBA8DD3A__INCLUDED_)

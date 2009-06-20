/*
 * SettingDiigo.h  : ソーシャルブックマーク管理プログラム
 *      SettingDiigo クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  25 Jul 2008
 *
 * $Log: /comm/bookey/SettingDiigo.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/07/25 17:33 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGDIIGO_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)
#define AFX_SETTINGDIIGO_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDiigo ダイアログ

class SettingDiigo : public CTabDialog
{
// コンストラクション
public:
	SettingDiigo(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingDiigo)
	enum { IDD = IDD_TAB_DIIGO };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingDiigo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingDiigo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDiigo( SettingDiigo &dlg );
    SettingDiigo  operator = ( SettingDiigo &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIIGO_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)

/*
 * SettingPookmark.h  : ソーシャルブックマーク管理プログラム
 *      SettingPookmark クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  4 Oct 2006
 *
 * $Log: /comm/bookey/SettingPookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 1     06/10/04 20:22 Tsujimura543
 * 新規作成 (pookmark 対応)
 */

#if !defined(AFX_SETTINGPOOKMARK_H__068DC3C0_E5E6_4120_8F8A_202C6E1A42BC__INCLUDED_)
#define AFX_SETTINGPOOKMARK_H__068DC3C0_E5E6_4120_8F8A_202C6E1A42BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingPookmark ダイアログ

class SettingPookmark : public CTabDialog
{
// コンストラクション
public:
	SettingPookmark(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();   // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingPookmark)
	enum { IDD = IDD_TAB_POOKMARK };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingPookmark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingPookmark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingPookmark( SettingPookmark &dlg );
    SettingPookmark operator = ( SettingPookmark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGPOOKMARK_H__068DC3C0_E5E6_4120_8F8A_202C6E1A42BC__INCLUDED_)

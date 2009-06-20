/*
 * SettingYJbookmark.h  : ソーシャルブックマーク管理プログラム
 *      SettingYJbookmark クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  16 Apr 2007
 *
 * $Log: /comm/bookey/SettingYJbookmark.h $
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
 * 1     07/04/16 20:38 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGYJBOOKMARK_H__617DDF3B_62E2_45F2_A219_6657C6E2F93F__INCLUDED_)
#define AFX_SETTINGYJBOOKMARK_H__617DDF3B_62E2_45F2_A219_6657C6E2F93F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingYJbookmark ダイアログ

class SettingYJbookmark : public CTabDialog
{
// コンストラクション
public:
	SettingYJbookmark(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingYJbookmark)
	enum { IDD = IDD_TAB_YJ_BOOKMARK };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingYJbookmark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingYJbookmark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingYJbookmark( SettingYJbookmark &dlg );
    SettingYJbookmark   operator = ( SettingYJbookmark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGYJBOOKMARK_H__617DDF3B_62E2_45F2_A219_6657C6E2F93F__INCLUDED_)

/*
 * SettingYahooBookmarks.h  : ソーシャルブックマーク管理プログラム
 *      SettingYahooBookmarks クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  18 Apr 2007
 *
 * $Log: /comm/bookey/SettingYahooBookmarks.h $
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
 * 1     07/04/18 21:34 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_SETTINGYAHOOBOOKMARKS_H__AA8DC0E1_7C0C_46D4_A35B_32E22BB13916__INCLUDED_)
#define AFX_SETTINGYAHOOBOOKMARKS_H__AA8DC0E1_7C0C_46D4_A35B_32E22BB13916__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingYahooBookmarks ダイアログ

class SettingYahooBookmarks : public CTabDialog
{
// コンストラクション
public:
	SettingYahooBookmarks(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingYahooBookmarks)
	enum { IDD = IDD_TAB_YAHOO_BOOKMARKS };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingYahooBookmarks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingYahooBookmarks)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingYahooBookmarks( SettingYahooBookmarks &dlg );
    SettingYahooBookmarks   operator = ( SettingYahooBookmarks &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGYAHOOBOOKMARKS_H__AA8DC0E1_7C0C_46D4_A35B_32E22BB13916__INCLUDED_)

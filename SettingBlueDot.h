/*
 * SettingBlueDot.h  : ソーシャルブックマーク管理プログラム
 *      SettingBlueDot クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  6 Oct 2006
 *
 * $Log: /comm/bookey/SettingBlueDot.h $
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
 * 1     06/10/07 1:07 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_SETTINGBLUEDOT_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)
#define AFX_SETTINGBLUEDOT_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingBlueDot ダイアログ

class SettingBlueDot : public CTabDialog
{
// コンストラクション
public:
	SettingBlueDot(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingBlueDot)
	enum { IDD = IDD_TAB_BLUEDOT };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingBlueDot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingBlueDot)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingBlueDot( SettingBlueDot &dlg );
    SettingBlueDot  operator = ( SettingBlueDot &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGBLUEDOT_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)

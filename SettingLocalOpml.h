/*
 * SettingLocalOpml.h  : ソーシャルブックマーク管理プログラム
 *      SettingLocalOpml クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  26 Jul 2006
 *
 * $Log: /comm/bookey/SettingLocalOpml.h $
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
 * 1     06/10/26 21:00 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#if !defined(AFX_SETTINGLOCALOPML_H__927B0DA2_E19D_4BF9_9641_D0D75EAF0B3F__INCLUDED_)
#define AFX_SETTINGLOCALOPML_H__927B0DA2_E19D_4BF9_9641_D0D75EAF0B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingLocalOpml ダイアログ

class SettingLocalOpml : public CTabDialog
{
// コンストラクション
public:
	SettingLocalOpml(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingLocalOpml)
	enum { IDD = IDD_TAB_LOCALOPML };
	CString	m_filename;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingLocalOpml)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingLocalOpml)
	afx_msg void OnButtonFileopen();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingLocalOpml( SettingLocalOpml &dlg );
    SettingLocalOpml    operator = ( SettingLocalOpml &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGLOCALOPML_H__927B0DA2_E19D_4BF9_9641_D0D75EAF0B3F__INCLUDED_)

/*
 * SettingLivedoor.h  : ソーシャルブックマーク管理プログラム
 *      SettingLivedoor クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingLivedoor.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     08/07/28 17:06 Tsujimura543
 * 設定したはずの apiKey が bookey の再起動時に消えてしまう
 * 不具合を修正
 * 
 * 6     08/07/28 15:29 Tsujimura543
 * 「APIキー」関連、追加
 * 
 * 5     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 4     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 3     06/07/31 17:14 Tsujimura543
 * ソースの整理 (コメント追加、余分な改行・空白の削除、など)
 * 
 * 2     06/07/31 17:03 Tsujimura543
 * 設定ダイアログを OK ボタン押下で終了すると、それまでにタブをクリックして
 * いなかったブックマークサービスの設定内容が破壊されてしまう不具合に対処
 * 
 * 1     06/07/28 23:00 Tsujimura543
 * 新規作成 (タブ切り替え式の「設定ダイアログ」を作成、導入した)
 */

#if !defined(AFX_SETTINGLIVEDOOR_H__839E7C30_41A1_4E2A_BD43_FE429130BE44__INCLUDED_)
#define AFX_SETTINGLIVEDOOR_H__839E7C30_41A1_4E2A_BD43_FE429130BE44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingLivedoor ダイアログ

class SettingLivedoor : public CTabDialog
{
// コンストラクション
public:
	SettingLivedoor(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingLivedoor)
	enum { IDD = IDD_TAB_LIVEDOOR };
	CString	m_apiKey;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingLivedoor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingLivedoor)
	afx_msg void OnButtonApiKey();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingLivedoor( SettingLivedoor &dlg );
    SettingLivedoor operator = ( SettingLivedoor &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGLIVEDOOR_H__839E7C30_41A1_4E2A_BD43_FE429130BE44__INCLUDED_)

/*
 * Setting1470net.h  : ソーシャルブックマーク管理プログラム
 *      Setting1470net クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/Setting1470net.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 5     06/08/22 17:53 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 4     06/08/22 17:00 Tsujimura543
 * enum authenticationType の定義を myClip.h 内に移した
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

#if !defined(AFX_SETTING1470NET_H__989E9351_8196_41E0_A8E2_C82A1FE44451__INCLUDED_)
#define AFX_SETTING1470NET_H__989E9351_8196_41E0_A8E2_C82A1FE44451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// Setting1470net ダイアログ

class Setting1470net : public CTabDialog
{
// コンストラクション
public:
	Setting1470net(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();   // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得
    void    SetAuthType();

// ダイアログ データ
	//{{AFX_DATA(Setting1470net)
	enum { IDD = IDD_TAB_1470NET };
	CString	m_hatena_password;
	CString	m_hatena_username;
	//}}AFX_DATA

    AUTH_TYPE   m_authType; // 認証種別

// オーバーライド
	//{{AFX_VIRTUAL(Setting1470net)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(Setting1470net)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioHatena();
	afx_msg void OnRadioHatenaTypekey();
	afx_msg void OnRadioTypekey();
	afx_msg void OnRadioTypekeyHatena();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    Setting1470net( Setting1470net &dlg );
    Setting1470net  operator = ( Setting1470net &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTING1470NET_H__989E9351_8196_41E0_A8E2_C82A1FE44451__INCLUDED_)

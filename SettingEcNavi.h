/*
 * SettingEcNavi.h  : ソーシャルブックマーク管理プログラム
 *      SettingEcNavi クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingEcNavi.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/09/13 22:29 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
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

#if !defined(AFX_SETTINGECNAVI_H__827D5B3E_2F46_4E23_8202_DD6C4C096BAC__INCLUDED_)
#define AFX_SETTINGECNAVI_H__827D5B3E_2F46_4E23_8202_DD6C4C096BAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingEcNavi ダイアログ

class SettingEcNavi : public CTabDialog
{
// コンストラクション
public:
	SettingEcNavi(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得
    void    SetUseMyTitle();
    void    SetAuthType();

// ダイアログ データ
	//{{AFX_DATA(SettingEcNavi)
	enum { IDD = IDD_TAB_ECNAVI };
	CString	m_yahooJapanID;
	CString	m_yahooJapanPassword;
	//}}AFX_DATA

    bool    m_useMyTitle;   // ブックマーク登録時、自分で設定しようとしている
                            // タイトルを優先的に適用するか否か (他者によって
                            // 設定済みのタイトルを受け入れるか否か)

    AUTH_TYPE   m_auth;     // 認証方法 (default は AK_ORIGINAL)

// オーバーライド
	//{{AFX_VIRTUAL(SettingEcNavi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingEcNavi)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioNochange();
	afx_msg void OnRadioChange();
	afx_msg void OnRadioUseEcnavi();
	afx_msg void OnRadioUseYj();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingEcNavi( SettingEcNavi &dlg );
    SettingEcNavi   operator = ( SettingEcNavi &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGECNAVI_H__827D5B3E_2F46_4E23_8202_DD6C4C096BAC__INCLUDED_)

/*
 * SettingNifty.h  : ソーシャルブックマーク管理プログラム
 *      SettingNifty クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingNifty.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     08/11/13 13:25 Tsujimura543
 * 「Powered by @nifty クリップ」に下線が引かれていなかったのを修正
 * 
 * 8     08/11/04 16:46 Tsujimura543
 * 「APIキー設定」ボタンを追加
 * 
 * 7     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 5     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 4     07/02/16 13:56 Tsujimura543
 * ニフティクリップに登録したブックマークのタイトルは共有ではなく、各自が
 * 独自のものを設定可能なことが判明したため、常に「独自のタイトルで上書き
 * する」ように処理自体と関連する設定画面を作り直した
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

#if !defined(AFX_SETTINGNIFTY_H__A5EE6969_B2BF_45C3_A8EC_13273CB33489__INCLUDED_)
#define AFX_SETTINGNIFTY_H__A5EE6969_B2BF_45C3_A8EC_13273CB33489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingNifty ダイアログ

class SettingNifty : public CTabDialog
{
// コンストラクション
public:
	SettingNifty(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~SettingNifty();

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

    HCURSOR m_hCursor;
    CFont   m_cFont;

// ダイアログ データ
	//{{AFX_DATA(SettingNifty)
	enum { IDD = IDD_TAB_NIFTY };
	CString	m_apiKey;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingNifty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingNifty)
	afx_msg void OnButtonApikey();
	afx_msg void OnPoweredByNiftyclip();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingNifty( SettingNifty &dlg );
    SettingNifty    operator = ( SettingNifty &dlg );

    bool    m_initialized2;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGNIFTY_H__A5EE6969_B2BF_45C3_A8EC_13273CB33489__INCLUDED_)

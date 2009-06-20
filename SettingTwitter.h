/*
 * SettingTwitter.h  : ソーシャルブックマーク管理プログラム
 *      SettingTwitter クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  10 Apr 2007
 *
 * $Log: /comm/bookey/SettingTwitter.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 1     07/04/10 18:46 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGTWITTER_H__B2A5A9BA_1158_425F_946A_E150A6B5B132__INCLUDED_)
#define AFX_SETTINGTWITTER_H__B2A5A9BA_1158_425F_946A_E150A6B5B132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingTwitter ダイアログ

class SettingTwitter : public CTabDialog
{
// コンストラクション
public:
	SettingTwitter(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingTwitter)
	enum { IDD = IDD_TAB_TWITTER };
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingTwitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

    AUTH_TYPE   m_auth;     // 認証方法 (default は AK_ORIGINAL)
    CString     m_oauthToken;
    CString     m_oauthTokenSecret;

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingTwitter)
	afx_msg void OnButtonGetToken();
	afx_msg void OnRadioOauth();
	afx_msg void OnRadioBasic();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    void    ShowCurrentStatus();
    bool    GetAccessToken(
                    const char *consumerKey,
                    const char *consumerSecret
                );
    bool    GetRequestToken(
                    const char *consumerKey,
                    const char *consumerSecret,
                    CString    &oauthToken,
                    CString    &oauthTokenSecret
                );
    bool    GetToken(
                    const char *response,
                    CString    &oauthToken,
                    CString    &oauthTokenSecret
                );

    SettingTwitter( SettingTwitter &dlg );
    SettingTwitter  operator = ( SettingTwitter &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTWITTER_H__B2A5A9BA_1158_425F_946A_E150A6B5B132__INCLUDED_)

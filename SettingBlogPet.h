/*
 * SettingBlogPet.h  : ソーシャルブックマーク管理プログラム
 *      SettingBlogPet クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/SettingBlogPet.h $
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
 * 1     06/12/22 22:16 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGBLOGPET_H__50BB79F5_C78C_4436_B618_3D6E49AE0C7D__INCLUDED_)
#define AFX_SETTINGBLOGPET_H__50BB79F5_C78C_4436_B618_3D6E49AE0C7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingBlogPet ダイアログ

class SettingBlogPet : public CTabDialog
{
// コンストラクション
public:
	SettingBlogPet(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得
    void    SetUseMyTitle();

// ダイアログ データ
	//{{AFX_DATA(SettingBlogPet)
	enum { IDD = IDD_TAB_BLOGPET };
	//}}AFX_DATA

    bool    m_useMyTitle;   // ブックマーク登録時、自分で設定しようとしている
                            // タイトルを優先的に適用するか否か (他者によって
                            // 設定済みのタイトルを受け入れるか否か)

// オーバーライド
	//{{AFX_VIRTUAL(SettingBlogPet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingBlogPet)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioChange();
	afx_msg void OnRadioNochange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingBlogPet( SettingBlogPet &dlg );
    SettingBlogPet  operator = ( SettingBlogPet &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGBLOGPET_H__50BB79F5_C78C_4436_B618_3D6E49AE0C7D__INCLUDED_)

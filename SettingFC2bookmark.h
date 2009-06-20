/*
 * SettingFC2bookmark.h  : ソーシャルブックマーク管理プログラム
 *      SettingFC2bookmark クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  30 Mar 2007
 *
 * $Log: /comm/bookey/SettingFC2bookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/05/07 19:20 Tsujimura543
 * 本ダイアログを抜けた後、m_isTarget の値が設定ファイルに反映されない
 * 不具合に対処
 * (m_isTarget は当クラス内のものではなく、親クラス CTabDialog のもの
 *  を使う必要あり。初歩的なミス)
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 1     07/03/30 16:02 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_SETTINGFC2BOOKMARK_H__19C7F532_AD49_4BDA_B892_1BAE817E4F58__INCLUDED_)
#define AFX_SETTINGFC2BOOKMARK_H__19C7F532_AD49_4BDA_B892_1BAE817E4F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingFC2bookmark ダイアログ

class SettingFC2bookmark : public CTabDialog
{
// コンストラクション
public:
	SettingFC2bookmark(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingFC2bookmark)
	enum { IDD = IDD_TAB_FC2BOOKMARK };
	//}}AFX_DATA

 // bool    m_isTarget; // 登録対象とするか否か

// オーバーライド
	//{{AFX_VIRTUAL(SettingFC2bookmark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingFC2bookmark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingFC2bookmark( SettingFC2bookmark &dlg );
    SettingFC2bookmark  operator = ( SettingFC2bookmark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGFC2BOOKMARK_H__19C7F532_AD49_4BDA_B892_1BAE817E4F58__INCLUDED_)

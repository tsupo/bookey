/*
 * SettingFlog.h  : ソーシャルブックマーク管理プログラム
 *      SettingFlog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingFlog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/05/07 19:20 Tsujimura543
 * 本ダイアログを抜けた後、m_isTarget の値が設定ファイルに反映されない
 * 不具合に対処
 * (m_isTarget は当クラス内のものではなく、親クラス CTabDialog のもの
 *  を使う必要あり。初歩的なミス)
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

#if !defined(AFX_SETTINGFLOG_H__B9073D75_4E7D_4C01_959E_F817E8C366D9__INCLUDED_)
#define AFX_SETTINGFLOG_H__B9073D75_4E7D_4C01_959E_F817E8C366D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingFlog ダイアログ

class SettingFlog : public CTabDialog
{
// コンストラクション
public:
	SettingFlog(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();       // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingFlog)
	enum { IDD = IDD_TAB_FLOG };
	//}}AFX_DATA

 // bool    m_isTarget; // 登録対象とするか否か

// オーバーライド
	//{{AFX_VIRTUAL(SettingFlog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingFlog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingFlog( SettingFlog &dlg );
    SettingFlog operator = ( SettingFlog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGFLOG_H__B9073D75_4E7D_4C01_959E_F817E8C366D9__INCLUDED_)

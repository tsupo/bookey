/*
 * SettingJoltMark.h  : ソーシャルブックマーク管理プログラム
 *      SettingJoltMark クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/SettingJoltMark.h $
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
 * 1     06/12/21 16:37 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_SETTINGJOLTMARK_H__09926F6A_3870_4867_9876_90DDDF410EE3__INCLUDED_)
#define AFX_SETTINGJOLTMARK_H__09926F6A_3870_4867_9876_90DDDF410EE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingJoltMark ダイアログ

class SettingJoltMark : public CTabDialog
{
// コンストラクション
public:
	SettingJoltMark(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    Accept();   // 「設定ダイアログ」での「適用」ボタン押下時処理
    void    LoadSetting();  // 現在の「設定」を取得

// ダイアログ データ
	//{{AFX_DATA(SettingJoltMark)
	enum { IDD = IDD_TAB_JOLTMARK };
	//}}AFX_DATA

 // bool    m_isTarget; // 登録対象とするか否か

// オーバーライド
	//{{AFX_VIRTUAL(SettingJoltMark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(SettingJoltMark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingJoltMark( SettingJoltMark &dlg );
    SettingJoltMark operator = ( SettingJoltMark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGJOLTMARK_H__09926F6A_3870_4867_9876_90DDDF410EE3__INCLUDED_)

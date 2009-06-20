/*
 * InputPinDialog.h  : ソーシャルブックマーク管理プログラム
 *      (OAuth の) PIN 入力ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  11 Jun 2009
 *
 * $Log: /comm/bookey/InputPinDialog.h $
 * 
 * 1     09/06/18 0:43 tsupo
 * VSSサーバ拠点を変更
 * 
 * 1     09/06/11 17:49 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_INPUTPINDIALOG_H__28B8D63A_5699_4BBC_90D0_6971132E1B1E__INCLUDED_)
#define AFX_INPUTPINDIALOG_H__28B8D63A_5699_4BBC_90D0_6971132E1B1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// InputPinDialog ダイアログ

class InputPinDialog : public CDialog
{
// コンストラクション
public:
	InputPinDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(InputPinDialog)
	enum { IDD = IDD_INPUT_PIN };
	CString	m_pin;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(InputPinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(InputPinDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_INPUTPINDIALOG_H__28B8D63A_5699_4BBC_90D0_6971132E1B1E__INCLUDED_)

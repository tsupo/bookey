/*
 * TabDialog.h : ソーシャルブックマーク管理プログラム
 *      CTabDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006 / 8 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/TabDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/09/06 18:05 Tsujimura543
 * ソースコードを整理
 * 
 * 2     07/06/08 19:21 Tsujimura543
 * コメントを修正
 * 
 * 1     07/06/08 19:20 Tsujimura543
 * 新規作成 (今まで各ソーシャルブックマークサービスごとに設定画面に関する
 * 処理を書いていたのを、共通化できる部分を CTabDialogクラスに集約してみた)
 */

#ifndef __TAB_DIALOG_H__
#define __TAB_DIALOG_H__

/////////////////////////////////////////////////////////////////////////////
// CTabDialog ダイアログ

class CTabDialog : public CDialog
{
public:
    CTabDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL );

    // 「設定ダイアログ」での「適用」ボタン押下時処理
    virtual void    Accept() = 0;

    // 「登録対象」にする
    void            SetIsTarget();
    bool            m_isTarget; // 登録対象とするか否か

    // 現在の「設定」を取得
    virtual void    LoadSetting() = 0;

// ダイアログ データ
	//{{AFX_DATA(CTabDialog)
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CTabDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    bool    m_initialized;

	// メッセージマップ関数
	//{{AFX_MSG(CTabDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioTarget();
	afx_msg void OnRadioNontarget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif  /* __TAB_DIALOG_H__ */

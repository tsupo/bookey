/*
 * CaptchaDialog.h  : ソーシャルブックマーク管理プログラム
 *      CCaptchaDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/CaptchaDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/10/10 22:38 Tsujimura543
 * 画像を取得するのに cookie が必要な場合(今のところ、diggのみ)に対応
 * 
 * 5     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 4     07/07/10 19:34 Tsujimura543
 * inputCaptchaString() の引数追加とそれに伴う各種変更(その2)
 * 
 * 3     07/07/10 1:01 Tsujimura543
 * inputCaptchaString() の引数追加とそれに伴う各種変更
 * 
 * 2     07/07/09 21:50 Tsujimura543
 * Topic の選択を追加
 * 
 * 1     07/07/09 17:37 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_CAPTCHADIALOG_H__4E7FD97B_511D_4312_AB0B_884DB031773E__INCLUDED_)
#define AFX_CAPTCHADIALOG_H__4E7FD97B_511D_4312_AB0B_884DB031773E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCaptchaDialog ダイアログ

class CCaptchaDialog : public CDialog
{
// コンストラクション
public:
	CCaptchaDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~CCaptchaDialog();

    CString     m_captchaImageURL;  // CAPTCHA 画像 URL
    CString     m_cookie;
    CString     m_topic;
    HBITMAP     m_bitmap;
    CAP_MODE    m_mode;

// ダイアログ データ
	//{{AFX_DATA(CCaptchaDialog)
	enum { IDD = IDD_CAPTCHA_DIALOG };
	CComboBox	m_topicList;
	CString	m_captcha;
	CString	m_title;
	CString	m_comment;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(CCaptchaDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージマップ関数
	//{{AFX_MSG(CCaptchaDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeComboTopic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CCaptchaDialog( CCaptchaDialog &dlg );
    CCaptchaDialog  operator = ( CCaptchaDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CAPTCHADIALOG_H__4E7FD97B_511D_4312_AB0B_884DB031773E__INCLUDED_)

/*
 * SettingNewsing.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(newsing) インプリメンテーション ファイル
 *          written by H.Tsujimura  29 Sep 2006
 *
 * $Log: /comm/bookey/SettingNewsing.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     07/10/11 22:24 Tsujimura543
 * Yahoo! Japan ID, パスワード関連部分を修正
 * 
 * 7     07/10/11 19:31 Tsujimura543
 * Yahoo! Japan の ID で newsing を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 5     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 4     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 3     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 1     06/09/29 18:41 Tsujimura543
 * 新規作成 (newsing 対応)
 */

#include "bookey.h"
#include "SettingNewsing.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingNewsing.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingNewsing ダイアログ

SettingNewsing::SettingNewsing(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingNewsing::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingNewsing)
	m_yahooJapanID = _T("");
	m_yahooJapanPassword = _T("");
	//}}AFX_DATA_INIT

    m_auth = AK_ORIGINAL;
}

void SettingNewsing::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingNewsing)
	DDX_Text(pDX, IDC_EDIT_YJ_USERNAME, m_yahooJapanID);
	DDV_MaxChars(pDX, m_yahooJapanID, 80);
	DDX_Text(pDX, IDC_EDIT_YJ_PASSWORD, m_yahooJapanPassword);
	DDV_MaxChars(pDX, m_yahooJapanPassword, 32);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingNewsing::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_newsing.m_username  = m_username;
        pp->m_newsing.m_password  = m_password;
        pp->m_newsing.m_username2 = m_yahooJapanID;
        pp->m_newsing.m_password2 = m_yahooJapanPassword;
        pp->m_newsing.SetAuthType( m_auth );
        pp->m_newsing = m_isTarget;
    }
}

void SettingNewsing::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username           = pp->m_newsing.m_username;
        m_password           = pp->m_newsing.m_password;
        m_yahooJapanID       = pp->m_yjBookmark.m_username;
        m_yahooJapanPassword = pp->m_yjBookmark.m_password;
        m_auth     = pp->m_newsing.GetAuthType();
        m_isTarget = (bool)(pp->m_newsing);
    }
}

void SettingNewsing::SetAuthType()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_USE_NEWSING );
    q->SetCheck( m_auth == AK_ORIGINAL ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_USE_YJ );
    q->SetCheck( m_auth == AK_YAHOOJAPAN_BBAUTH ? 1 : 0 );
}

BEGIN_MESSAGE_MAP(SettingNewsing, CTabDialog)
	//{{AFX_MSG_MAP(SettingNewsing)
	ON_BN_CLICKED(IDC_RADIO_USE_NEWSING, OnRadioUseNewsing)
	ON_BN_CLICKED(IDC_RADIO_USE_YJ, OnRadioUseYj)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingNewsing メッセージ ハンドラ

void SettingNewsing::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->SetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->SetWindowText( m_yahooJapanPassword );

        SetAuthType();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->GetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->GetWindowText( m_yahooJapanPassword );
    }
}

void SettingNewsing::OnRadioUseNewsing() 
{
    m_auth = AK_ORIGINAL;
    SetAuthType();	
}

void SettingNewsing::OnRadioUseYj() 
{
    m_auth = AK_YAHOOJAPAN_BBAUTH;
    SetAuthType();
}

/*
 * SettingEcNavi.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(Buzzurl) インプリメンテーション ファイル
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingEcNavi.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    07/09/13 22:30 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 10    07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 9     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 8     07/02/16 16:20 Tsujimura543
 * m_useMyTitle 関連の処理を修正
 * 
 * 7     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 6     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 5     07/01/11 17:03 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正 (コメントのみ)
 * 
 * 4     06/09/29 18:57 Tsujimura543
 * RCS(VSS)の Header 情報を埋め込み忘れていたので、改めて埋め込んでみた
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

#include "bookey.h"
#include "SettingEcNavi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingEcNavi.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingEcNavi ダイアログ

SettingEcNavi::SettingEcNavi(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingEcNavi::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingEcNavi)
	m_yahooJapanID = _T("");
	m_yahooJapanPassword = _T("");
	//}}AFX_DATA_INIT

    m_useMyTitle = false;
    m_auth       = AK_ORIGINAL;
}

void SettingEcNavi::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingEcNavi)
	DDX_Text(pDX, IDC_EDIT_YJ_USERNAME, m_yahooJapanID);
	DDV_MaxChars(pDX, m_yahooJapanID, 32);
	DDX_Text(pDX, IDC_EDIT_YJ_PASSWORD, m_yahooJapanPassword);
	DDV_MaxChars(pDX, m_yahooJapanPassword, 80);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingEcNavi::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_ecNaviClip.m_username   = m_username;
        pp->m_ecNaviClip.m_password   = m_password;
        pp->m_ecNaviClip.m_username2  = m_yahooJapanID;
        pp->m_ecNaviClip.m_password2  = m_yahooJapanPassword;
        pp->m_ecNaviClip.m_useMyTitle = m_useMyTitle;
        pp->m_ecNaviClip.SetAuthType( m_auth );
        pp->m_ecNaviClip = m_isTarget;
    }
}

void    SettingEcNavi::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username           = pp->m_ecNaviClip.m_username;
        m_password           = pp->m_ecNaviClip.m_password;
        m_yahooJapanID       = pp->m_yjBookmark.m_username;
        m_yahooJapanPassword = pp->m_yjBookmark.m_password;
        m_auth       = pp->m_ecNaviClip.GetAuthType();
        m_isTarget   = (bool)(pp->m_ecNaviClip);
        m_useMyTitle = pp->m_ecNaviClip.m_useMyTitle;
    }
}

void SettingEcNavi::SetUseMyTitle()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_CHANGE );
    q->SetCheck( m_useMyTitle ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_NOCHANGE );
    q->SetCheck( m_useMyTitle ? 0 : 1 );
}

void SettingEcNavi::SetAuthType()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_USE_ECNAVI );
    q->SetCheck( m_auth == AK_ORIGINAL ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_USE_YJ );
    q->SetCheck( m_auth == AK_YAHOOJAPAN_BBAUTH ? 1 : 0 );
}

BEGIN_MESSAGE_MAP(SettingEcNavi, CTabDialog)
	//{{AFX_MSG_MAP(SettingEcNavi)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_NOCHANGE, OnRadioNochange)
	ON_BN_CLICKED(IDC_RADIO_CHANGE, OnRadioChange)
	ON_BN_CLICKED(IDC_RADIO_USE_ECNAVI, OnRadioUseEcnavi)
	ON_BN_CLICKED(IDC_RADIO_USE_YJ, OnRadioUseYj)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingEcNavi メッセージ ハンドラ

void SettingEcNavi::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->SetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->SetWindowText( m_yahooJapanPassword );

        SetAuthType();
        SetUseMyTitle();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->GetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->GetWindowText( m_yahooJapanPassword );
    }
}

void SettingEcNavi::OnRadioChange() 
{
    m_useMyTitle = true;
    SetUseMyTitle();
}

void SettingEcNavi::OnRadioNochange() 
{
    m_useMyTitle = false;
    SetUseMyTitle();
}

void SettingEcNavi::OnRadioUseEcnavi() 
{
    m_auth = AK_ORIGINAL;
    SetAuthType();	
}

void SettingEcNavi::OnRadioUseYj() 
{
    m_auth = AK_YAHOOJAPAN_BBAUTH;
    SetAuthType();
}

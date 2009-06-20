/*
 * SettingBlogPet.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(BlogPet 気になる記事) インプリメンテーション ファイル
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/SettingBlogPet.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 5     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 4     07/02/16 16:20 Tsujimura543
 * m_useMyTitle 関連の処理を修正
 * 
 * 3     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 1     06/12/22 22:16 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "SettingBlogPet.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingBlogPet.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingBlogPet ダイアログ

SettingBlogPet::SettingBlogPet(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingBlogPet::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingBlogPet)
	//}}AFX_DATA_INIT

    m_useMyTitle  = false;
}

void SettingBlogPet::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingBlogPet)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingBlogPet::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_blogPet.m_username   = m_username;
        pp->m_blogPet.m_password   = m_password;
        pp->m_blogPet.m_useMyTitle = m_useMyTitle;
        pp->m_blogPet = m_isTarget;
    }
}

void SettingBlogPet::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username   = pp->m_blogPet.m_username;
        m_password   = pp->m_blogPet.m_password;
        m_isTarget   = (bool)(pp->m_blogPet);
        m_useMyTitle = pp->m_blogPet.m_useMyTitle;
    }
}

void SettingBlogPet::SetUseMyTitle()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_CHANGE );
    q->SetCheck( m_useMyTitle ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_NOCHANGE );
    q->SetCheck( m_useMyTitle ? 0 : 1 );
}

BEGIN_MESSAGE_MAP(SettingBlogPet, CTabDialog)
	//{{AFX_MSG_MAP(SettingBlogPet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_CHANGE, OnRadioChange)
	ON_BN_CLICKED(IDC_RADIO_NOCHANGE, OnRadioNochange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingBlogPet メッセージ ハンドラ

void SettingBlogPet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow )
        SetUseMyTitle();
}

void SettingBlogPet::OnRadioChange() 
{
    m_useMyTitle = true;
    SetUseMyTitle();
}

void SettingBlogPet::OnRadioNochange() 
{
    m_useMyTitle = false;
    SetUseMyTitle();
}

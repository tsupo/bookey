/*
 * SettingDigg.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(digg) インプリメンテーション ファイル
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/SettingDigg.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/07/09 19:11 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "SettingDigg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingDigg.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDigg ダイアログ

SettingDigg::SettingDigg(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingDigg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDigg)
	//}}AFX_DATA_INIT
}

void SettingDigg::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDigg)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingDigg::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_digg.m_username = m_username;
        pp->m_digg.m_password = m_password;
        pp->m_digg = m_isTarget;
    }
}

void SettingDigg::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_digg.m_username;
        m_password = pp->m_digg.m_password;
        m_isTarget = (bool)(pp->m_digg);
    }
}

BEGIN_MESSAGE_MAP(SettingDigg, CTabDialog)
	//{{AFX_MSG_MAP(SettingDigg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

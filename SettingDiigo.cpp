/*
 * SettingDiigo.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(Diigo) インプリメンテーション ファイル
 *          written by H.Tsujimura  25 Jul 2008
 *
 * $Log: /comm/bookey/SettingDiigo.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/07/25 17:33 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "SettingDiigo.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingDiigo.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDiigo ダイアログ


SettingDiigo::SettingDiigo(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingDiigo::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDiigo)
	//}}AFX_DATA_INIT
}

void SettingDiigo::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDiigo)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingDiigo::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_diigo.m_username = m_username;
        pp->m_diigo.m_password = m_password;
        pp->m_diigo = m_isTarget;
    }
}

void SettingDiigo::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_diigo.m_username;
        m_password = pp->m_diigo.m_password;
        m_isTarget = (bool)(pp->m_diigo);
    }
}

BEGIN_MESSAGE_MAP(SettingDiigo, CTabDialog)
	//{{AFX_MSG_MAP(SettingDiigo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

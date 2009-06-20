/*
 * SettingTimelog.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(Timelog) インプリメンテーション ファイル
 *          written by H.Tsujimura  23 May 2007
 *
 * $Log: /comm/bookey/SettingTimelog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 2     07/05/23 16:00 Tsujimura543
 * コメントを修正
 * 
 * 1     07/05/23 15:59 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "SettingTimelog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingTimelog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingTimelog ダイアログ

SettingTimelog::SettingTimelog(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingTimelog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingTimelog)
	//}}AFX_DATA_INIT
}

void SettingTimelog::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingTimelog)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingTimelog::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_timelog.m_username = m_username;
        pp->m_timelog.m_password = m_password;
        pp->m_timelog = m_isTarget;
    }
}

void SettingTimelog::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_timelog.m_username;
        m_password = pp->m_timelog.m_password;
        m_isTarget = (bool)(pp->m_timelog);
    }
}

BEGIN_MESSAGE_MAP(SettingTimelog, CTabDialog)
	//{{AFX_MSG_MAP(SettingTimelog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

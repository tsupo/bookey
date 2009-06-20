/*
 * SettingYJbookmark.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(Yahoo! ブックマーク) インプリメンテーション ファイル
 *          written by H.Tsujimura  16 Apr 2007
 *
 * $Log: /comm/bookey/SettingYJbookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 1     07/04/16 20:38 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "SettingYJbookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingYJbookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingYJbookmark ダイアログ

SettingYJbookmark::SettingYJbookmark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingYJbookmark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingYJbookmark)
	//}}AFX_DATA_INIT
}

void SettingYJbookmark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingYJbookmark)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingYJbookmark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_yjBookmark.m_username = m_username;
        pp->m_yjBookmark.m_password = m_password;
        pp->m_yjBookmark = m_isTarget;
    }
}

void SettingYJbookmark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_yjBookmark.m_username;
        m_password = pp->m_yjBookmark.m_password;
        m_isTarget = (bool)(pp->m_yjBookmark);
    }
}

BEGIN_MESSAGE_MAP(SettingYJbookmark, CTabDialog)
	//{{AFX_MSG_MAP(SettingYJbookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

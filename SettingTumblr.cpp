/*
 * SettingTumblr.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(tumblr) インプリメンテーション ファイル
 *          written by H.Tsujimura  31 Oct 2007
 *
 * $Log: /comm/bookey/SettingTumblr.cpp $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 4     09/05/29 0:33 Tsujimura543
 * 動作確認終了
 * 
 * 3     09/05/29 0:32 Tsujimura543
 * 砂時計カーソルを表示しつつ、getBlogIDsTumblr() を実行するようにした
 * 
 * 2     09/05/29 0:23 Tsujimura543
 * 投稿先 tumbleblog を(プライマリ以外からも)選択可能にした
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/10/31 16:50 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "tumblr.h"
#include "SettingTumblr.h"
#include "BlogIDSelectDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingTumblr.cpp 2     09/05/29 8:43 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingTumblr ダイアログ

SettingTumblr::SettingTumblr(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingTumblr::IDD, pParent)
{
    m_blogID = _T("");

	//{{AFX_DATA_INIT(SettingTumblr)
	m_blogName = _T("");
	//}}AFX_DATA_INIT
}

void SettingTumblr::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingTumblr)
	DDX_Text(pDX, IDC_EDIT_BLOGNAME, m_blogName);
	DDV_MaxChars(pDX, m_blogName, 256);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingTumblr::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_tumblr.m_username = m_username;
        pp->m_tumblr.m_password = m_password;
        if ( m_blogID.GetLength() > 0 ) {
            pp->m_tumblr.m_blogID   = m_blogID;
            pp->m_tumblr.m_blogName = m_blogName;
        }
        pp->m_tumblr = m_isTarget;
    }
}

void SettingTumblr::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_tumblr.m_username;
        m_password = pp->m_tumblr.m_password;
        m_blogID   = pp->m_tumblr.m_blogID;
        m_blogName = pp->m_tumblr.m_blogName;
        m_isTarget = (bool)(pp->m_tumblr);
    }
}

BEGIN_MESSAGE_MAP(SettingTumblr, CTabDialog)
	//{{AFX_MSG_MAP(SettingTumblr)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_TARGET, OnButtonSelectTarget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void SettingTumblr::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        if ( m_blogID.GetLength() == 0 )
            m_blogName.LoadString(IDS_DEFAULT_TARGET);

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
        p->SetWindowText( m_blogName );
    }
}

void SettingTumblr::OnButtonSelectTarget() 
{
    CBlogIDSelectDlg    dlg;
    int                 r;
    BLOGINF             blogInfo[MAX_BLOGS];
    int                 numOfBlogs = MAX_BLOGS;

    CWaitCursor cur;    // マウスカーソルを砂時計表示
    r = getBlogIDsTumblr( m_username, m_password,
                          &numOfBlogs, blogInfo );
    if ( r <= 0 )
        return;

    m_blogID   = blogInfo[0].blogID;    // primary Blog
    m_blogName = blogInfo[0].blogName;  // primary Blog

    if ( r > 1 ) {
        dlg.initialize( blogInfo, numOfBlogs );
        int res = dlg.DoModal();
        if ( (res == IDOK) && (dlg.m_blogIDlistIndex != -1) ) {
            if ( (dlg.m_blogIDlistIndex >= 0)         &&
                 (dlg.m_blogIDlistIndex < numOfBlogs)    ) {
                r = dlg.m_blogIDlistIndex;

                m_blogID   = blogInfo[r].blogID;
                m_blogName = blogInfo[r].blogName;
            }
        }
    }

    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
    p->SetWindowText( m_blogName );
}

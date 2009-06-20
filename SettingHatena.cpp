/*
 * SettingHatena.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(はてなブックマーク) インプリメンテーション ファイル
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingHatena.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 7     07/02/16 16:20 Tsujimura543
 * m_useMyTitle 関連の処理を修正
 * 
 * 6     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 5     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
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
#include "SettingHatena.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingHatena.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingHatena ダイアログ

SettingHatena::SettingHatena(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingHatena::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingHatena)
	//}}AFX_DATA_INIT

    m_useMyTitle  = false;
}

void SettingHatena::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingHatena)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingHatena::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_hatena.m_username   = m_username;
        pp->m_hatena.m_password   = m_password;
        pp->m_hatena.m_useMyTitle = m_useMyTitle;
        pp->m_hatena = m_isTarget;
    }
}

void SettingHatena::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username   = pp->m_hatena.m_username;
        m_password   = pp->m_hatena.m_password;
        m_isTarget   = (bool)(pp->m_hatena);
        m_useMyTitle = pp->m_hatena.m_useMyTitle;
    }
}

void SettingHatena::SetUseMyTitle()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_CHANGE );
    q->SetCheck( m_useMyTitle ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_NOCHANGE );
    q->SetCheck( m_useMyTitle ? 0 : 1 );
}

BEGIN_MESSAGE_MAP(SettingHatena, CTabDialog)
	//{{AFX_MSG_MAP(SettingHatena)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_NOCHANGE, OnRadioNochange)
	ON_BN_CLICKED(IDC_RADIO_CHANGE, OnRadioChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingHatena メッセージ ハンドラ

void SettingHatena::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow )
        SetUseMyTitle();
}

void SettingHatena::OnRadioChange() 
{
    m_useMyTitle = true;
    SetUseMyTitle();
}

void SettingHatena::OnRadioNochange() 
{
    m_useMyTitle = false;
    SetUseMyTitle();
}

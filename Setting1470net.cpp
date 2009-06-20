/*
 * Setting1470net.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(1470.net) インプリメンテーション ファイル
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/Setting1470net.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 10    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 9     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 8     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 7     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 6     06/09/29 18:57 Tsujimura543
 * RCS(VSS)の Header 情報を埋め込み忘れていたので、改めて埋め込んでみた
 * 
 * 5     06/08/22 16:59 Tsujimura543
 * enum authenticationType の定義を myClip.h 内に移した
 * 
 * 4     06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
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
#include "Setting1470net.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/Setting1470net.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Setting1470net ダイアログ

Setting1470net::Setting1470net(CWnd* pParent /*=NULL*/)
	: CTabDialog(Setting1470net::IDD, pParent)
{
	//{{AFX_DATA_INIT(Setting1470net)
	//}}AFX_DATA_INIT
}

void Setting1470net::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Setting1470net)
	DDX_Text(pDX, IDC_EDIT_HATENA_PASSWORD, m_hatena_password);
	DDV_MaxChars(pDX, m_hatena_password, 32);
	DDX_Text(pDX, IDC_EDIT_HATENA_USERNAME, m_hatena_username);
	DDV_MaxChars(pDX, m_hatena_username, 32);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void Setting1470net::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_next1470net.m_username  = m_username;
        pp->m_next1470net.m_password  = m_password;
        pp->m_next1470net.m_username2 = m_hatena_username;
        pp->m_next1470net.m_password2 = m_hatena_password;
        pp->m_next1470net = m_isTarget;
        pp->m_next1470net.SetAuthType( m_authType );
    }
}

void Setting1470net::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_next1470net.m_username;
        m_password = pp->m_next1470net.m_password;
        m_isTarget = (bool)(pp->m_next1470net);
        m_authType = pp->m_next1470net.GetAuthType();

        m_hatena_username = pp->m_hatena.m_username;
        m_hatena_password = pp->m_hatena.m_password;
    }
}

void Setting1470net::SetAuthType()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_HATENA );
    q->SetCheck( m_authType == AK_HATENA ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_HATENA_TYPEKEY );
    q->SetCheck( m_authType == AK_HATENA_TYPEKEY ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_TYPEKEY );
    q->SetCheck( m_authType == AK_TYPEKEY ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_TYPEKEY_HATENA );
    q->SetCheck( m_authType == AK_TYPEKEY_HATENA ? 1 : 0 );
}

BEGIN_MESSAGE_MAP(Setting1470net, CTabDialog)
	//{{AFX_MSG_MAP(Setting1470net)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_HATENA, OnRadioHatena)
	ON_BN_CLICKED(IDC_RADIO_HATENA_TYPEKEY, OnRadioHatenaTypekey)
	ON_BN_CLICKED(IDC_RADIO_TYPEKEY, OnRadioTypekey)
	ON_BN_CLICKED(IDC_RADIO_TYPEKEY_HATENA, OnRadioTypekeyHatena)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Setting1470net メッセージ ハンドラ

void Setting1470net::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_HATENA_USERNAME);
        p->SetWindowText( m_hatena_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_HATENA_PASSWORD);
        p->SetWindowText( m_hatena_password );

        SetAuthType();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_HATENA_USERNAME);
        p->GetWindowText( m_hatena_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_HATENA_PASSWORD);
        p->GetWindowText( m_hatena_password );
    }
}

void Setting1470net::OnRadioHatena() 
{
    m_authType = AK_HATENA;
    SetAuthType();
}

void Setting1470net::OnRadioHatenaTypekey() 
{
    m_authType = AK_HATENA_TYPEKEY;
    SetAuthType();
}

void Setting1470net::OnRadioTypekey() 
{
    m_authType = AK_TYPEKEY;
    SetAuthType();
}

void Setting1470net::OnRadioTypekeyHatena() 
{
    m_authType = AK_TYPEKEY_HATENA;
    SetAuthType();
}

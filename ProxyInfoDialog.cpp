/*
 * ProxyInfoDialog.cpp : ソーシャルブックマーク管理プログラム
 *      proxy情報設定ダイアログ
 *
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/ProxyInfoDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 1     07/03/14 16:17 Tsujimura543
 * 「ブログクライアント BloGolEe」用に書いたソースを取り込む
 * =======================================================================
 * 2     07/03/10 5:22 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応してみた
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "ProxyInfoDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/ProxyInfoDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog ダイアログ

CProxyInfoDialog::CProxyInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProxyInfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProxyInfoDialog)
	m_proxyServerName = _T("");
	m_proxyPortNumber = 0;
	m_proxyUserName = _T("");
	m_proxyPassword = _T("");
	//}}AFX_DATA_INIT
}

void CProxyInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProxyInfoDialog)
	DDX_Text(pDX, IDC_EDIT_PROXY_SERVER_NAME, m_proxyServerName);
	DDV_MaxChars(pDX, m_proxyServerName, 384);
	DDX_Text(pDX, IDC_EDIT_PROXY_PORT_NUMBER, m_proxyPortNumber);
	DDV_MinMaxUInt(pDX, m_proxyPortNumber, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PROXY_USER_NAME, m_proxyUserName);
	DDV_MaxChars(pDX, m_proxyUserName, 32);
	DDX_Text(pDX, IDC_EDIT_PROXY_PASSWORD, m_proxyPassword);
	DDV_MaxChars(pDX, m_proxyPassword, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProxyInfoDialog, CDialog)
	//{{AFX_MSG_MAP(CProxyInfoDialog)
	ON_EN_UPDATE(IDC_EDIT_PROXY_PORT_NUMBER, OnUpdateEditProxyPortNumber)
	ON_EN_UPDATE(IDC_EDIT_PROXY_SERVER_NAME, OnUpdateEditProxyServerName)
	ON_WM_SHOWWINDOW()
	ON_EN_UPDATE(IDC_EDIT_PROXY_USER_NAME, OnUpdateEditProxyUserName)
	ON_EN_UPDATE(IDC_EDIT_PROXY_PASSWORD, OnUpdateEditProxyPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog 追加メソッド

void    CProxyInfoDialog::switchOK()
{
    CButton *q = (CButton *)GetDlgItem( IDOK );
    if ( (m_proxyServerName.GetLength() > 0) && (m_proxyPortNumber > 0) )
        q->EnableWindow( TRUE );
    else
        q->EnableWindow( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog メッセージ ハンドラ

void CProxyInfoDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        if ( m_proxyServerName.GetLength() > 0 ) {
            CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_SERVER_NAME );
            p->SetWindowText( m_proxyServerName );

            char    portNumberString[16];
            sprintf( portNumberString, "%d", m_proxyPortNumber );
            p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_PORT_NUMBER );
            p->SetWindowText( portNumberString );

            if ( m_proxyUserName.GetLength() > 0 ) {
                p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_USER_NAME );
                p->SetWindowText( m_proxyUserName );

                if ( m_proxyPassword.GetLength() > 0 ) {
                    p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_PASSWORD );
                    p->SetWindowText( m_proxyPassword );
                }
            }
        }
        switchOK();	
    }
}

void CProxyInfoDialog::OnUpdateEditProxyServerName() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_SERVER_NAME );
    p->GetWindowText( m_proxyServerName );
    switchOK();
}

void CProxyInfoDialog::OnUpdateEditProxyPortNumber() 
{
    CString portNumberString;
    long    portNumber;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_PORT_NUMBER );
    p->GetWindowText( portNumberString );
	
    if ( portNumberString.GetLength() > 0 ) {
        portNumber = atol( (const char *)portNumberString );
        if ( portNumber > 0 ) {
            m_proxyPortNumber = portNumber;
            switchOK();
        }
    }
}

void CProxyInfoDialog::OnUpdateEditProxyUserName() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_USER_NAME );
    p->GetWindowText( m_proxyUserName );
}

void CProxyInfoDialog::OnUpdateEditProxyPassword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_PASSWORD );
    p->GetWindowText( m_proxyPassword );
}

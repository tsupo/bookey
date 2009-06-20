/*
 * AboutDlg.cpp : ソーシャルブックマーク管理プログラム
 *      版数(バージョン番号)表示
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/AboutDlg.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    09/02/24 16:40 Tsujimura543
 * 「Yahoo! Japan Web サービス」のクレジット表示を追加
 * 
 * 10    08/11/27 15:12 Tsujimura543
 * OpenSSL と iconv の版数を表示するようにした
 * 
 * 9     08/10/21 22:05 Tsujimura543
 * 「ヘルプ」メニューに「サポート」(2件)、「コミュニティ」(2件)を追加
 * 
 * 8     07/07/02 16:44 Tsujimura543
 * Visual Studio 2005 でビルドした場合でも、期待通り「指カーソル」が
 * 表示されるように修正
 * 
 * 7     07/04/11 17:03 Tsujimura543
 * 版数情報はリソースファイルから持ってきたのを表示するようにしてみた
 * 
 * 6     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 5     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 4     06/06/27 12:33 Tsujimura543
 * IDS_BOOKEY_MAIL_ADDR, IDS_BOOKEY_WEB_URL を導入
 * 
 * 3     06/06/27 12:16 Tsujimura543
 * コメントを追加
 * 
 * 2     06/06/27 12:07 Tsujimura543
 * blog の URL、メールアドレスをクリックすると、ブラウザ、メーラを立ち上げ
 * るようにした
 * 
 * 1     05/10/14 14:08 Tsujimura543
 * bookey.cpp および bookeyDlg.cpp から分離、独立させた
 */

#include "bookey.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/AboutDlg.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

CAboutDlg::~CAboutDlg()
{
    m_cFont.DeleteObject();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BOOKEY_MAIL_ADDR, OnBookeyMailAddr)
	ON_BN_CLICKED(IDC_BOOKEY_WEB_URL, OnBookeyWebUrl)
	ON_WM_SETCURSOR()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CREDIT_YAHOOJAPAN, OnCreditYahooJapan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CBookeyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CAboutDlg::OnBookeyMailAddr() 
{
	CString cmd;
	cmd.LoadString( IDS_BOOKEY_MAIL_ADDR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CAboutDlg::OnBookeyWebUrl() 
{
	CString cmd;
	cmd.LoadString( IDS_BOOKEY_WEB_URL );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CAboutDlg::OnCreditYahooJapan() 
{
	CString cmd;
	cmd.LoadString( IDS_CREDIT_YAHOOJAPAN_URL );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );	
}

BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // Web の URLかメールアドレスにマウスポインタが来たら、
        // 指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_BOOKEY_MAIL_ADDR );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        s = (CStatic *)GetDlgItem( IDC_BOOKEY_WEB_URL );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        s = (CStatic *)GetDlgItem( IDC_CREDIT_YAHOOJAPAN );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        // Web の URLとメールアドレスを下線付きで表示する
        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        CStatic *s = (CStatic *)GetDlgItem( IDC_BOOKEY_MAIL_ADDR );
        s->SetFont( &m_cFont, TRUE );

        s = (CStatic *)GetDlgItem( IDC_BOOKEY_WEB_URL );
        s->SetFont( &m_cFont, TRUE );

        CString str;
        str.LoadString( IDS_BOOKEY_VERSION );
        str = "bookey Version " + str;
        s = (CStatic *)GetDlgItem( IDC_BOOKEY_VERSION );
        s->SetWindowText( str );

        // OpenSSL 版数表示
        char    buf[BUFSIZ];
        size_t  sz = BUFSIZ;

        s = (CStatic *)GetDlgItem( IDC_OPENSSL );
        s->SetWindowText( getOpenSSLversion( buf, sz ) );

        // iconv 版数表示
        s = (CStatic *)GetDlgItem( IDC_ICONV );
        s->SetWindowText( getIconvVersion( buf, sz ) );

        // Yahoo! Japan Webサービス クレジット表示
        s = (CStatic *)GetDlgItem( IDC_CREDIT_YAHOOJAPAN );
        s->SetFont( &m_cFont, TRUE );
    }
}

void CBookeyApp::OnAppSupport()
{
	CString cmd;
    cmd.LoadString( IDS_BOOKEY_WEB_URL );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CBookeyApp::OnAppSupport2()
{
	CString cmd;
    cmd.LoadString( IDS_BOOKEY_SUPPORT );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CBookeyApp::OnAppCommunity()
{
	CString cmd;
    cmd.LoadString( IDS_BOOKEY_COMMUNITY );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CBookeyApp::OnAppCommunity2()
{
	CString cmd;
    cmd.LoadString( IDS_BOOKEY_COMMUNITY2 );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

/*
 * AboutDlg.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �Ő�(�o�[�W�����ԍ�)�\��
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/AboutDlg.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    09/02/24 16:40 Tsujimura543
 * �uYahoo! Japan Web �T�[�r�X�v�̃N���W�b�g�\����ǉ�
 * 
 * 10    08/11/27 15:12 Tsujimura543
 * OpenSSL �� iconv �̔Ő���\������悤�ɂ���
 * 
 * 9     08/10/21 22:05 Tsujimura543
 * �u�w���v�v���j���[�Ɂu�T�|�[�g�v(2��)�A�u�R�~���j�e�B�v(2��)��ǉ�
 * 
 * 8     07/07/02 16:44 Tsujimura543
 * Visual Studio 2005 �Ńr���h�����ꍇ�ł��A���Ғʂ�u�w�J�[�\���v��
 * �\�������悤�ɏC��
 * 
 * 7     07/04/11 17:03 Tsujimura543
 * �Ő����̓��\�[�X�t�@�C�����玝���Ă����̂�\������悤�ɂ��Ă݂�
 * 
 * 6     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 5     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 4     06/06/27 12:33 Tsujimura543
 * IDS_BOOKEY_MAIL_ADDR, IDS_BOOKEY_WEB_URL �𓱓�
 * 
 * 3     06/06/27 12:16 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 2     06/06/27 12:07 Tsujimura543
 * blog �� URL�A���[���A�h���X���N���b�N����ƁA�u���E�U�A���[���𗧂��グ
 * ��悤�ɂ���
 * 
 * 1     05/10/14 14:08 Tsujimura543
 * bookey.cpp ����� bookeyDlg.cpp ���番���A�Ɨ�������
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
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

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

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
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
        // Web �� URL�����[���A�h���X�Ƀ}�E�X�|�C���^��������A
        // �w�J�[�\����\������
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
        // Web �� URL�ƃ��[���A�h���X�������t���ŕ\������
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

        // OpenSSL �Ő��\��
        char    buf[BUFSIZ];
        size_t  sz = BUFSIZ;

        s = (CStatic *)GetDlgItem( IDC_OPENSSL );
        s->SetWindowText( getOpenSSLversion( buf, sz ) );

        // iconv �Ő��\��
        s = (CStatic *)GetDlgItem( IDC_ICONV );
        s->SetWindowText( getIconvVersion( buf, sz ) );

        // Yahoo! Japan Web�T�[�r�X �N���W�b�g�\��
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

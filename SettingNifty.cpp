/*
 * SettingNifty.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(�j�t�e�B�N���b�v) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingNifty.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 14    08/11/13 13:25 Tsujimura543
 * �uPowered by @nifty �N���b�v�v�ɉ�����������Ă��Ȃ������̂��C��
 * 
 * 13    08/11/05 17:30 Tsujimura543
 * �uAPI�L�[�ݒ�v�{�^���������������C��
 * 
 * 12    08/11/05 17:29 Tsujimura543
 * ���̃T�[�r�X�̐ݒ��ʂ�@nifty�N���b�v�̐ݒ��ʂ��s�����藈���肷��
 * �ƃA�v���P�[�V�����G���[�ŗ�����s����C��
 * 
 * 11    08/11/04 16:46 Tsujimura543
 * �uAPI�L�[�ݒ�v�{�^����ǉ�
 * 
 * 10    07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 9     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 8     07/02/16 13:57 Tsujimura543
 * �R�����g���C��
 * 
 * 7     07/02/16 13:56 Tsujimura543
 * �j�t�e�B�N���b�v�ɓo�^�����u�b�N�}�[�N�̃^�C�g���͋��L�ł͂Ȃ��A�e����
 * �Ǝ��̂��̂�ݒ�\�Ȃ��Ƃ������������߁A��Ɂu�Ǝ��̃^�C�g���ŏ㏑��
 * ����v�悤�ɏ������̂Ɗ֘A����ݒ��ʂ���蒼����
 * 
 * 6     07/02/16 9:49 Tsujimura543
 * �u�K�p�v�{�^�������������ɕ����̃^�u���s�����藈���肷��ƁA�ȑO���͂�
 * �����e�������Ă��܂�(������Ԃɖ߂��Ă���)�s����C��
 * 
 * 5     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 4     06/09/29 18:57 Tsujimura543
 * RCS(VSS)�� Header ���𖄂ߍ��ݖY��Ă����̂ŁA���߂Ė��ߍ���ł݂�
 * 
 * 3     06/07/31 17:14 Tsujimura543
 * �\�[�X�̐��� (�R�����g�ǉ��A�]���ȉ��s�E�󔒂̍폜�A�Ȃ�)
 * 
 * 2     06/07/31 17:03 Tsujimura543
 * �ݒ�_�C�A���O�� OK �{�^�������ŏI������ƁA����܂łɃ^�u���N���b�N����
 * ���Ȃ������u�b�N�}�[�N�T�[�r�X�̐ݒ���e���j�󂳂�Ă��܂��s��ɑΏ�
 * 
 * 1     06/07/28 23:00 Tsujimura543
 * �V�K�쐬 (�^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�A��������)
 */

#include "bookey.h"
#include "SettingNifty.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingNifty.cpp 1     09/05/14 3:48 tsupo $";
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
// SettingNifty �_�C�A���O

SettingNifty::SettingNifty(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingNifty::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingNifty)
	m_apiKey = _T("");
	//}}AFX_DATA_INIT

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
    m_initialized2 = false;
}

SettingNifty::~SettingNifty()
{
    m_cFont.DeleteObject();
}

void SettingNifty::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingNifty)
	DDX_Text(pDX, IDC_EDIT_APIKEY, m_apiKey);
	DDV_MaxChars(pDX, m_apiKey, 64);
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingNifty::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_niftyClip.m_username = m_username;
        pp->m_niftyClip.m_password = m_password;
        if ( m_apiKey.GetLength() > 0)
            pp->m_niftyClip.m_apiKey = m_apiKey;
        pp->m_niftyClip = m_isTarget;
    }
}

void SettingNifty::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_niftyClip.m_username;
        m_password = pp->m_niftyClip.m_password;
        if ( pp->m_niftyClip.m_apiKey.GetLength() > 0 )
            m_apiKey = pp->m_niftyClip.m_apiKey;
        m_isTarget = (bool)(pp->m_niftyClip);
    }
}

BEGIN_MESSAGE_MAP(SettingNifty, CTabDialog)
	//{{AFX_MSG_MAP(SettingNifty)
	ON_BN_CLICKED(IDC_BUTTON_APIKEY, OnButtonApikey)
	ON_BN_CLICKED(IDC_POWEREDBY_NIFTYCLIP, OnPoweredByNiftyclip)
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingNitty ���b�Z�[�W �n���h��

void SettingNifty::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
    if ( bShow ) {
        p->SetWindowText( m_apiKey );

        if ( !m_initialized2 ) {
            // �uPowered by @nifty �N���b�v�v�������t���ŕ\������
            LOGFONT tLogFont;
            CFont   *cWndFont;

            cWndFont = GetFont(); 
            cWndFont->GetLogFont( &tLogFont );
            tLogFont.lfUnderline = 1;
            m_cFont.CreateFontIndirect( &tLogFont );

            CStatic *s = (CStatic *)GetDlgItem( IDC_POWEREDBY_NIFTYCLIP );
            s->SetFont( &m_cFont, TRUE );

            m_initialized2 = true;
        }
    }
    else
        p->GetWindowText( m_apiKey );
}

BOOL SettingNifty::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // �uPowered by @nifty �N���b�v�v�Ƀ}�E�X�|�C���^��������A
        // �w�J�[�\����\������
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_POWEREDBY_NIFTYCLIP );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

	return CTabDialog::OnSetCursor(pWnd, nHitTest, message);
}

void SettingNifty::OnButtonApikey() 
{
    if ( (m_username.GetLength() > 0) && (m_password.GetLength() > 0)) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        char        apiKey[MAX_KEYLENGTH];

        apiKey[0] = NUL;
        getApiKeyOnNiftyClip( m_username, m_password, apiKey );
        if ( apiKey[0] ) {
            m_apiKey = apiKey;

            CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
            p->SetWindowText( m_apiKey );
        }
    }
}

void SettingNifty::OnPoweredByNiftyclip() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_NIFTYCLIP );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

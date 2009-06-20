/*
 * SettingEcNavi.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(Buzzurl) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingEcNavi.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    07/09/13 22:30 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 10    07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 9     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 8     07/02/16 16:20 Tsujimura543
 * m_useMyTitle �֘A�̏������C��
 * 
 * 7     07/02/16 9:49 Tsujimura543
 * �u�K�p�v�{�^�������������ɕ����̃^�u���s�����藈���肷��ƁA�ȑO���͂�
 * �����e�������Ă��܂�(������Ԃɖ߂��Ă���)�s����C��
 * 
 * 6     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 5     07/01/11 17:03 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C�� (�R�����g�̂�)
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
#include "SettingEcNavi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingEcNavi.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingEcNavi �_�C�A���O

SettingEcNavi::SettingEcNavi(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingEcNavi::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingEcNavi)
	m_yahooJapanID = _T("");
	m_yahooJapanPassword = _T("");
	//}}AFX_DATA_INIT

    m_useMyTitle = false;
    m_auth       = AK_ORIGINAL;
}

void SettingEcNavi::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingEcNavi)
	DDX_Text(pDX, IDC_EDIT_YJ_USERNAME, m_yahooJapanID);
	DDV_MaxChars(pDX, m_yahooJapanID, 32);
	DDX_Text(pDX, IDC_EDIT_YJ_PASSWORD, m_yahooJapanPassword);
	DDV_MaxChars(pDX, m_yahooJapanPassword, 80);
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingEcNavi::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_ecNaviClip.m_username   = m_username;
        pp->m_ecNaviClip.m_password   = m_password;
        pp->m_ecNaviClip.m_username2  = m_yahooJapanID;
        pp->m_ecNaviClip.m_password2  = m_yahooJapanPassword;
        pp->m_ecNaviClip.m_useMyTitle = m_useMyTitle;
        pp->m_ecNaviClip.SetAuthType( m_auth );
        pp->m_ecNaviClip = m_isTarget;
    }
}

void    SettingEcNavi::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username           = pp->m_ecNaviClip.m_username;
        m_password           = pp->m_ecNaviClip.m_password;
        m_yahooJapanID       = pp->m_yjBookmark.m_username;
        m_yahooJapanPassword = pp->m_yjBookmark.m_password;
        m_auth       = pp->m_ecNaviClip.GetAuthType();
        m_isTarget   = (bool)(pp->m_ecNaviClip);
        m_useMyTitle = pp->m_ecNaviClip.m_useMyTitle;
    }
}

void SettingEcNavi::SetUseMyTitle()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_CHANGE );
    q->SetCheck( m_useMyTitle ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_NOCHANGE );
    q->SetCheck( m_useMyTitle ? 0 : 1 );
}

void SettingEcNavi::SetAuthType()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_USE_ECNAVI );
    q->SetCheck( m_auth == AK_ORIGINAL ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_USE_YJ );
    q->SetCheck( m_auth == AK_YAHOOJAPAN_BBAUTH ? 1 : 0 );
}

BEGIN_MESSAGE_MAP(SettingEcNavi, CTabDialog)
	//{{AFX_MSG_MAP(SettingEcNavi)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_NOCHANGE, OnRadioNochange)
	ON_BN_CLICKED(IDC_RADIO_CHANGE, OnRadioChange)
	ON_BN_CLICKED(IDC_RADIO_USE_ECNAVI, OnRadioUseEcnavi)
	ON_BN_CLICKED(IDC_RADIO_USE_YJ, OnRadioUseYj)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingEcNavi ���b�Z�[�W �n���h��

void SettingEcNavi::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->SetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->SetWindowText( m_yahooJapanPassword );

        SetAuthType();
        SetUseMyTitle();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->GetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->GetWindowText( m_yahooJapanPassword );
    }
}

void SettingEcNavi::OnRadioChange() 
{
    m_useMyTitle = true;
    SetUseMyTitle();
}

void SettingEcNavi::OnRadioNochange() 
{
    m_useMyTitle = false;
    SetUseMyTitle();
}

void SettingEcNavi::OnRadioUseEcnavi() 
{
    m_auth = AK_ORIGINAL;
    SetAuthType();	
}

void SettingEcNavi::OnRadioUseYj() 
{
    m_auth = AK_YAHOOJAPAN_BBAUTH;
    SetAuthType();
}

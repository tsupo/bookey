/*
 * SettingNewsing.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(newsing) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  29 Sep 2006
 *
 * $Log: /comm/bookey/SettingNewsing.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     07/10/11 22:24 Tsujimura543
 * Yahoo! Japan ID, �p�X���[�h�֘A�������C��
 * 
 * 7     07/10/11 19:31 Tsujimura543
 * Yahoo! Japan �� ID �� newsing �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 5     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 4     07/02/16 13:57 Tsujimura543
 * �R�����g���C��
 * 
 * 3     07/02/16 9:49 Tsujimura543
 * �u�K�p�v�{�^�������������ɕ����̃^�u���s�����藈���肷��ƁA�ȑO���͂�
 * �����e�������Ă��܂�(������Ԃɖ߂��Ă���)�s����C��
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 1     06/09/29 18:41 Tsujimura543
 * �V�K�쐬 (newsing �Ή�)
 */

#include "bookey.h"
#include "SettingNewsing.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingNewsing.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingNewsing �_�C�A���O

SettingNewsing::SettingNewsing(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingNewsing::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingNewsing)
	m_yahooJapanID = _T("");
	m_yahooJapanPassword = _T("");
	//}}AFX_DATA_INIT

    m_auth = AK_ORIGINAL;
}

void SettingNewsing::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingNewsing)
	DDX_Text(pDX, IDC_EDIT_YJ_USERNAME, m_yahooJapanID);
	DDV_MaxChars(pDX, m_yahooJapanID, 80);
	DDX_Text(pDX, IDC_EDIT_YJ_PASSWORD, m_yahooJapanPassword);
	DDV_MaxChars(pDX, m_yahooJapanPassword, 32);
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingNewsing::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_newsing.m_username  = m_username;
        pp->m_newsing.m_password  = m_password;
        pp->m_newsing.m_username2 = m_yahooJapanID;
        pp->m_newsing.m_password2 = m_yahooJapanPassword;
        pp->m_newsing.SetAuthType( m_auth );
        pp->m_newsing = m_isTarget;
    }
}

void SettingNewsing::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username           = pp->m_newsing.m_username;
        m_password           = pp->m_newsing.m_password;
        m_yahooJapanID       = pp->m_yjBookmark.m_username;
        m_yahooJapanPassword = pp->m_yjBookmark.m_password;
        m_auth     = pp->m_newsing.GetAuthType();
        m_isTarget = (bool)(pp->m_newsing);
    }
}

void SettingNewsing::SetAuthType()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_USE_NEWSING );
    q->SetCheck( m_auth == AK_ORIGINAL ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_USE_YJ );
    q->SetCheck( m_auth == AK_YAHOOJAPAN_BBAUTH ? 1 : 0 );
}

BEGIN_MESSAGE_MAP(SettingNewsing, CTabDialog)
	//{{AFX_MSG_MAP(SettingNewsing)
	ON_BN_CLICKED(IDC_RADIO_USE_NEWSING, OnRadioUseNewsing)
	ON_BN_CLICKED(IDC_RADIO_USE_YJ, OnRadioUseYj)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingNewsing ���b�Z�[�W �n���h��

void SettingNewsing::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->SetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->SetWindowText( m_yahooJapanPassword );

        SetAuthType();
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_USERNAME);
        p->GetWindowText( m_yahooJapanID );

        p = (CEdit *)GetDlgItem(IDC_EDIT_YJ_PASSWORD);
        p->GetWindowText( m_yahooJapanPassword );
    }
}

void SettingNewsing::OnRadioUseNewsing() 
{
    m_auth = AK_ORIGINAL;
    SetAuthType();	
}

void SettingNewsing::OnRadioUseYj() 
{
    m_auth = AK_YAHOOJAPAN_BBAUTH;
    SetAuthType();
}

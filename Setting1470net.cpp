/*
 * Setting1470net.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(1470.net) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/Setting1470net.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 10    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 9     07/02/16 13:57 Tsujimura543
 * �R�����g���C��
 * 
 * 8     07/02/16 9:49 Tsujimura543
 * �u�K�p�v�{�^�������������ɕ����̃^�u���s�����藈���肷��ƁA�ȑO���͂�
 * �����e�������Ă��܂�(������Ԃɖ߂��Ă���)�s����C��
 * 
 * 7     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 6     06/09/29 18:57 Tsujimura543
 * RCS(VSS)�� Header ���𖄂ߍ��ݖY��Ă����̂ŁA���߂Ė��ߍ���ł݂�
 * 
 * 5     06/08/22 16:59 Tsujimura543
 * enum authenticationType �̒�`�� myClip.h ���Ɉڂ���
 * 
 * 4     06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
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
// Setting1470net �_�C�A���O

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

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
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
// Setting1470net ���b�Z�[�W �n���h��

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

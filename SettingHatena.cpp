/*
 * SettingHatena.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(�͂Ăȃu�b�N�}�[�N) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingHatena.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 7     07/02/16 16:20 Tsujimura543
 * m_useMyTitle �֘A�̏������C��
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
// SettingHatena �_�C�A���O

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

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
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
// SettingHatena ���b�Z�[�W �n���h��

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

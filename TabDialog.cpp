/*
 * TabDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(�^�u�\��t����������) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006 / 8 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/TabDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/06/08 19:21 Tsujimura543
 * �R�����g���C��
 * 
 * 1     07/06/08 19:20 Tsujimura543
 * �V�K�쐬 (���܂Ŋe�\�[�V�����u�b�N�}�[�N�T�[�r�X���Ƃɐݒ��ʂɊւ���
 * �����������Ă����̂��A���ʉ��ł��镔���� CTabDialog�N���X�ɏW�񂵂Ă݂�)
 */

#include "bookey.h"
#include "TabDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/TabDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDialog �_�C�A���O

CTabDialog::CTabDialog( UINT nIDTemplate, CWnd* pParentWnd )
	: CDialog(nIDTemplate, pParentWnd)
{
	//{{AFX_DATA_INIT(CTabDialog)
	m_username = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT

    m_initialized = false;
}

void CTabDialog::SetIsTarget()
{
    CButton *q = (CButton *)GetDlgItem( IDC_RADIO_TARGET );
    q->SetCheck( m_isTarget ? 1 : 0 );

    q = (CButton *)GetDlgItem( IDC_RADIO_NONTARGET );
    q->SetCheck( m_isTarget ? 0 : 1 );
}

void CTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDialog)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTabDialog, CDialog)
	//{{AFX_MSG_MAP(CTabDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_TARGET, OnRadioTarget)
	ON_BN_CLICKED(IDC_RADIO_NONTARGET, OnRadioNontarget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDialog ���b�Z�[�W �n���h��

void CTabDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        LoadSetting();

        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->SetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->SetWindowText( m_password );

        SetIsTarget();

        m_initialized = true;
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
        p->GetWindowText( m_username );

        p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
        p->GetWindowText( m_password );
    }
}

void CTabDialog::OnRadioTarget() 
{
    m_isTarget = true;
    SetIsTarget();
}

void CTabDialog::OnRadioNontarget() 
{
    m_isTarget = false;
    SetIsTarget();
}

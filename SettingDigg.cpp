/*
 * SettingDigg.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(digg) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/SettingDigg.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/07/09 19:11 Tsujimura543
 * �V�K�쐬
 */

#include "bookey.h"
#include "SettingDigg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingDigg.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDigg �_�C�A���O

SettingDigg::SettingDigg(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingDigg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDigg)
	//}}AFX_DATA_INIT
}

void SettingDigg::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDigg)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingDigg::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_digg.m_username = m_username;
        pp->m_digg.m_password = m_password;
        pp->m_digg = m_isTarget;
    }
}

void SettingDigg::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_digg.m_username;
        m_password = pp->m_digg.m_password;
        m_isTarget = (bool)(pp->m_digg);
    }
}

BEGIN_MESSAGE_MAP(SettingDigg, CTabDialog)
	//{{AFX_MSG_MAP(SettingDigg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

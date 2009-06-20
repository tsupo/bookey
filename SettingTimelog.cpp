/*
 * SettingTimelog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(Timelog) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  23 May 2007
 *
 * $Log: /comm/bookey/SettingTimelog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 2     07/05/23 16:00 Tsujimura543
 * �R�����g���C��
 * 
 * 1     07/05/23 15:59 Tsujimura543
 * �V�K�쐬
 */

#include "bookey.h"
#include "SettingTimelog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingTimelog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingTimelog �_�C�A���O

SettingTimelog::SettingTimelog(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingTimelog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingTimelog)
	//}}AFX_DATA_INIT
}

void SettingTimelog::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingTimelog)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingTimelog::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_timelog.m_username = m_username;
        pp->m_timelog.m_password = m_password;
        pp->m_timelog = m_isTarget;
    }
}

void SettingTimelog::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_timelog.m_username;
        m_password = pp->m_timelog.m_password;
        m_isTarget = (bool)(pp->m_timelog);
    }
}

BEGIN_MESSAGE_MAP(SettingTimelog, CTabDialog)
	//{{AFX_MSG_MAP(SettingTimelog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

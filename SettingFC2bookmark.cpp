/*
 * SettingFC2bookmark.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(FC2BOOKMARK) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  30 Mar 2007
 *
 * $Log: /comm/bookey/SettingFC2bookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     07/03/30 16:02 Tsujimura543
 * �V�K�쐬
 */

#include "bookey.h"
#include "SettingFC2bookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingFC2bookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingFC2bookmark �_�C�A���O

SettingFC2bookmark::SettingFC2bookmark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingFC2bookmark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingFC2bookmark)
	//}}AFX_DATA_INIT
}

void SettingFC2bookmark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingFC2bookmark)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingFC2bookmark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_fc2bookmark.m_username = m_username;
        pp->m_fc2bookmark.m_password = m_password;
        pp->m_fc2bookmark = m_isTarget;
    }
}

void SettingFC2bookmark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_fc2bookmark.m_username;
        m_password = pp->m_fc2bookmark.m_password;
        m_isTarget = (bool)(pp->m_fc2bookmark);
    }
}

BEGIN_MESSAGE_MAP(SettingFC2bookmark, CTabDialog)
	//{{AFX_MSG_MAP(SettingFC2bookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

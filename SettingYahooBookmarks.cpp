/*
 * SettingYahooBookmarks.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(Yahoo! Bookmarks) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  18 Apr 2007
 *
 * $Log: /comm/bookey/SettingYahooBookmarks.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     07/04/18 21:34 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "SettingYahooBookmarks.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingYahooBookmarks.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingYahooBookmarks �_�C�A���O

SettingYahooBookmarks::SettingYahooBookmarks(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingYahooBookmarks::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingYahooBookmarks)
	//}}AFX_DATA_INIT
}

void SettingYahooBookmarks::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingYahooBookmarks)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingYahooBookmarks::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_yahooBookmarks.m_username = m_username;
        pp->m_yahooBookmarks.m_password = m_password;
        pp->m_yahooBookmarks = m_isTarget;
    }
}

void SettingYahooBookmarks::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_yahooBookmarks.m_username;
        m_password = pp->m_yahooBookmarks.m_password;
        m_isTarget = (bool)(pp->m_yahooBookmarks);
    }
}

BEGIN_MESSAGE_MAP(SettingYahooBookmarks, CTabDialog)
	//{{AFX_MSG_MAP(SettingYahooBookmarks)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

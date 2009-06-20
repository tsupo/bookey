/*
 * SettingYJbookmark.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(Yahoo! �u�b�N�}�[�N) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  16 Apr 2007
 *
 * $Log: /comm/bookey/SettingYJbookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     07/04/16 20:38 Tsujimura543
 * �V�K�쐬
 */

#include "bookey.h"
#include "SettingYJbookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingYJbookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingYJbookmark �_�C�A���O

SettingYJbookmark::SettingYJbookmark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingYJbookmark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingYJbookmark)
	//}}AFX_DATA_INIT
}

void SettingYJbookmark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingYJbookmark)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingYJbookmark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_yjBookmark.m_username = m_username;
        pp->m_yjBookmark.m_password = m_password;
        pp->m_yjBookmark = m_isTarget;
    }
}

void SettingYJbookmark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_yjBookmark.m_username;
        m_password = pp->m_yjBookmark.m_password;
        m_isTarget = (bool)(pp->m_yjBookmark);
    }
}

BEGIN_MESSAGE_MAP(SettingYJbookmark, CTabDialog)
	//{{AFX_MSG_MAP(SettingYJbookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

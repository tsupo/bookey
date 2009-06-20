/*
 * SettingPookmark.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(pookmark) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  4 Oct 2006
 *
 * $Log: /comm/bookey/SettingPookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 5     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 4     07/02/16 16:15 Tsujimura543
 * �R�����g���C��
 * 
 * 3     07/02/16 9:49 Tsujimura543
 * �u�K�p�v�{�^�������������ɕ����̃^�u���s�����藈���肷��ƁA�ȑO���͂�
 * �����e�������Ă��܂�(������Ԃɖ߂��Ă���)�s����C��
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 1     06/10/04 20:22 Tsujimura543
 * �V�K�쐬 (pookmark �Ή�)
 */

#include "bookey.h"
#include "SettingPookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingPookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingPookmark �_�C�A���O

SettingPookmark::SettingPookmark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingPookmark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingPookmark)
	//}}AFX_DATA_INIT
}

void SettingPookmark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingPookmark)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingPookmark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_pookmark.m_username = m_username;
        pp->m_pookmark.m_password = m_password;
        pp->m_pookmark = m_isTarget;
    }
}

void SettingPookmark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_pookmark.m_username;
        m_password = pp->m_pookmark.m_password;
        m_isTarget = (bool)(pp->m_pookmark);
    }
}

BEGIN_MESSAGE_MAP(SettingPookmark, CTabDialog)
	//{{AFX_MSG_MAP(SettingPookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
 * SettingBlueDot.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(Blue Dot) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  6 Oct 2006
 *
 * $Log: /comm/bookey/SettingBlueDot.cpp $
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
 * 1     06/10/07 1:07 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "SettingBlueDot.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingBlueDot.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingBlueDot �_�C�A���O


SettingBlueDot::SettingBlueDot(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingBlueDot::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingBlueDot)
	//}}AFX_DATA_INIT
}

void SettingBlueDot::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingBlueDot)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingBlueDot::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_blueDot.m_username = m_username;
        pp->m_blueDot.m_password = m_password;
        pp->m_blueDot = m_isTarget;
    }
}

void SettingBlueDot::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_blueDot.m_username;
        m_password = pp->m_blueDot.m_password;
        m_isTarget = (bool)(pp->m_blueDot);
    }
}

BEGIN_MESSAGE_MAP(SettingBlueDot, CTabDialog)
	//{{AFX_MSG_MAP(SettingBlueDot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

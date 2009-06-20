/*
 * SettingJoltMark.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(JoltMark) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/SettingJoltMark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 6     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 5     07/02/16 13:57 Tsujimura543
 * �R�����g���C��
 * 
 * 4     07/02/16 9:49 Tsujimura543
 * �u�K�p�v�{�^�������������ɕ����̃^�u���s�����藈���肷��ƁA�ȑO���͂�
 * �����e�������Ă��܂�(������Ԃɖ߂��Ă���)�s����C��
 * 
 * 3     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 2     06/12/22 22:12 Tsujimura543
 * �Ő��Ǘ��p������𖄂ߍ���
 * 
 * 1     06/12/21 16:37 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "SettingJoltMark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingJoltMark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingJoltMark �_�C�A���O

SettingJoltMark::SettingJoltMark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingJoltMark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingJoltMark)
	//}}AFX_DATA_INIT
}

void SettingJoltMark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingJoltMark)
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingJoltMark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_joltMark.m_username = m_username;
        pp->m_joltMark.m_password = m_password;
        pp->m_joltMark = m_isTarget;
    }
}

void SettingJoltMark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_joltMark.m_username;
        m_password = pp->m_joltMark.m_password;
        m_isTarget = (bool)(pp->m_joltMark);
    }
}

BEGIN_MESSAGE_MAP(SettingJoltMark, CTabDialog)
	//{{AFX_MSG_MAP(SettingJoltMark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

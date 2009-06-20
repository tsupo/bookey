/*
 * SettingLivedoor.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(livedoor�N���b�v) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingLivedoor.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 12    08/07/28 17:06 Tsujimura543
 * �ݒ肵���͂��� apiKey �� bookey �̍ċN�����ɏ����Ă��܂�
 * �s����C��
 * 
 * 11    08/07/28 15:37 Tsujimura543
 * OnButtonApiKey() ���s���͍����v�J�[�\����\������悤�ɂ���
 * 
 * 10    08/07/28 15:29 Tsujimura543
 * �uAPI�L�[�v�֘A�A�ǉ�
 * 
 * 9     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 7     07/02/16 13:57 Tsujimura543
 * �R�����g���C��
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
#include "SettingLivedoor.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingLivedoor.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingLivedoor �_�C�A���O

SettingLivedoor::SettingLivedoor(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingLivedoor::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingLivedoor)
	m_apiKey = _T("");
	//}}AFX_DATA_INIT
}

void SettingLivedoor::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingLivedoor)
	DDX_Text(pDX, IDC_EDIT_APIKEY, m_apiKey);
	DDV_MaxChars(pDX, m_apiKey, 64);
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingLivedoor::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_livedoorClip.m_username = m_username;
        pp->m_livedoorClip.m_password = m_password;
        if ( m_apiKey.GetLength() > 0)
            pp->m_livedoorClip.m_apiKey = m_apiKey;
        pp->m_livedoorClip = m_isTarget;
    }
}

void SettingLivedoor::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_livedoorClip.m_username;
        m_password = pp->m_livedoorClip.m_password;
        if ( pp->m_livedoorClip.m_apiKey.GetLength() > 0 )
            m_apiKey = pp->m_livedoorClip.m_apiKey;
        m_isTarget = (bool)(pp->m_livedoorClip);
    }
}

BEGIN_MESSAGE_MAP(SettingLivedoor, CTabDialog)
	//{{AFX_MSG_MAP(SettingLivedoor)
	ON_BN_CLICKED(IDC_BUTTON_APIKEY, OnButtonApiKey)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingLivedoor ���b�Z�[�W �n���h��

void SettingLivedoor::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
    if ( bShow )
        p->SetWindowText( m_apiKey );
    else
        p->GetWindowText( m_apiKey );
}

void SettingLivedoor::OnButtonApiKey() 
{
    if ( (m_username.GetLength() > 0) && (m_password.GetLength() > 0)) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        char        apiKey[MAX_KEYLENGTH];

        apiKey[0] = NUL;
        getApiKeyOnLivedoorClip( m_username, m_password, apiKey );
        if ( apiKey[0] ) {
            m_apiKey = apiKey;

            CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
            p->SetWindowText( m_apiKey );
        }
    }
}

/*
 * SettingLocalOpml.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(���[�J��OPML�t�@�C��) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  26 Sep 2006
 *
 * $Log: /comm/bookey/SettingLocalOpml.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 7     07/04/10 19:57 Tsujimura543
 * �R���X�g���N�^�� m_initialized ������������̂�Y��Ă���
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
 * 2     07/01/12 23:50 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 1     06/10/26 21:00 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "bookey.h"
#include "SettingLocalOpml.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingLocalOpml.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingLocalOpml �_�C�A���O

SettingLocalOpml::SettingLocalOpml(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingLocalOpml::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingLocalOpml)
	m_filename = _T("");
	//}}AFX_DATA_INIT
}

void SettingLocalOpml::DoDataExchange(CDataExchange* pDX)
{
    // �� CTabDialog �ł͂Ȃ��ACDialog �ɂ��Ă���̂́A SettingLocalOpml �ɂ�
    // �� m_username, m_pasword ����͂��邽�߂� CEdit �R���g���[�������݂���
    // �� ������
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingLocalOpml)
	DDX_Text(pDX, IDC_EDIT_LOCALOPML_FILENAME, m_filename);
	DDV_MaxChars(pDX, m_filename, 384);
	//}}AFX_DATA_MAP
}

// �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
void SettingLocalOpml::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_localOpml.m_username     = "";
        pp->m_localOpml.m_password     = "";
        pp->m_localOpml.m_opmlFilename = m_filename;
        pp->m_localOpml = m_isTarget;
    }
}

void SettingLocalOpml::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_filename = pp->m_localOpml.m_opmlFilename;
        m_isTarget = (bool)(pp->m_localOpml);
    }
}

// CTabDialog::OnRadioTarget(), CTabDialog::OnRadioNontarget() ���g�������̂�
// CTabDialog ���w�肵�Ă���         ��
BEGIN_MESSAGE_MAP(SettingLocalOpml, CTabDialog)
	//{{AFX_MSG_MAP(SettingLocalOpml)
	ON_BN_CLICKED(IDC_BUTTON_FILEOPEN, OnButtonFileopen)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingLocalOpml ���b�Z�[�W �n���h��

void SettingLocalOpml::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
    // �� CTabDialog �ł͂Ȃ��ACDialog �ɂ��Ă���̂́A SettingLocalOpml �ɂ�
    // �� m_username, m_pasword ����͂��邽�߂� CEdit �R���g���[�������݂���
    // �� ������

    if ( bShow ) {
        LoadSetting();

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_LOCALOPML_FILENAME );
        p->SetWindowText( m_filename );

        SetIsTarget();

        m_initialized = true;
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_LOCALOPML_FILENAME );
        p->GetWindowText( m_filename );
    }
}

void SettingLocalOpml::OnButtonFileopen() 
{
    // �t�@�C���I���_�C�A���O��\���AOPML�t�@�C����I��
    CFileDialog *fileDlg;
    CString     fileType;

    fileType.LoadString( IDS_FILETYPE_OPML );
    fileDlg = new CFileDialog( TRUE, "opml", m_filename,
                               OFN_EXPLORER,
                               fileType );
    if ( fileDlg->DoModal() == IDOK )
        m_filename = fileDlg->GetPathName();
    else
        m_filename = _T("");

    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_LOCALOPML_FILENAME );
    p->SetWindowText( m_filename );

    delete fileDlg;
}

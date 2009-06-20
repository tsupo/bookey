/*
 * InputPinDialog.cpp  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      (OAuth ��) PIN ���̓_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  11 Jun 2009
 *
 * $Log: /comm/bookey/InputPinDialog.cpp $
 * 
 * 1     09/06/18 0:43 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 3     09/06/16 1:18 Tsujimura543
 * PIN �� 0 �Ŏn�܂�6���̐����̏ꍇ�ɂ��Ή�
 * 
 * 2     09/06/11 18:26 Tsujimura543
 * �R�����g���� typo �C��
 * 
 * 1     09/06/11 17:49 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "InputPinDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/InputPinDialog.cpp 1     09/06/18 0:43 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InputPinDialog �_�C�A���O

InputPinDialog::InputPinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputPinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputPinDialog)
	m_pin = _T("");
	//}}AFX_DATA_INIT
}

void InputPinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputPinDialog)
	DDX_Text(pDX, IDC_EDIT_PIN, m_pin);
	DDV_MaxChars(pDX, m_pin, 12);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(InputPinDialog, CDialog)
	//{{AFX_MSG_MAP(InputPinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputPinDialog ���b�Z�[�W �n���h��

void InputPinDialog::OnOK() 
{
    long    num = 0;
    CString str = "";
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PIN );
    p->GetWindowText( str );
    if ( str.GetLength() > 0 )
        num = atol( str );
    if ( str.GetLength() < 6 ) {
        // ��: 0 �Ŏn�܂�6���̐��������蓾��(���Ƃ��킩����)
        CString ttl = _T("");
        CString msg = _T("");

        ttl.LoadString(IDS_TTL_INPUT_PIN);
        msg.LoadString(IDS_TXT_INPUT_PIN);
        MessageBox( msg, ttl, MB_OK|MB_ICONWARNING );
        return;
    }

    char    buf[64];
    m_pin  = _T("00000");
    m_pin += ltoa( num, buf, 10 );
    m_pin  = m_pin.Right(6);

	CDialog::OnOK();
}

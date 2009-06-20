/*
 * SynchronizeBookmarkDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�����_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  11 Oct 2005
 *
 * $Log: /comm/bookey/SynchronizeBookmarkDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 6     07/01/23 22:30 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 5     07/01/16 0:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 4     06/02/08 19:20 Tsujimura543
 * 4�̃u�b�N�}�[�N�̂����̔C�ӂ�2�̊Ԃ̓�������邱�Ƃ��w���ł���悤
 * �ɂ���
 * 
 * 3     05/10/11 17:16 Tsujimura543
 * �t�@�C������ύX (Syncronize�c �� Synchronize�c)
 * 
 * 2     05/10/11 17:06 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 */

#include "bookey.h"
#include "SynchronizeBookmarkDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SynchronizeBookmarkDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SynchronizeBookmarkDialog �_�C�A���O


SynchronizeBookmarkDialog::SynchronizeBookmarkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SynchronizeBookmarkDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SynchronizeBookmarkDialog)
	m_bookmark1 = _T("");
	m_bookmark2 = _T("");
	//}}AFX_DATA_INIT
}


void SynchronizeBookmarkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SynchronizeBookmarkDialog)
	DDX_Control(pDX, IDC_BM2, m_bookmarkList2);
	DDX_Control(pDX, IDC_BM1, m_bookmarkList1);
	DDX_Control(pDX, IDC_BMNAMES, m_description);
	DDX_CBString(pDX, IDC_BM1, m_bookmark1);
	DDX_CBString(pDX, IDC_BM2, m_bookmark2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SynchronizeBookmarkDialog, CDialog)
	//{{AFX_MSG_MAP(SynchronizeBookmarkDialog)
	ON_BN_CLICKED(IDC_BUTTON_SYNC1, OnButtonSync1)
	ON_BN_CLICKED(IDC_BUTTON_SYNC2, OnButtonSync2)
	ON_BN_CLICKED(IDC_BUTTON_SYNC3, OnButtonSync3)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_BM1, OnSelchangeBm1)
	ON_CBN_SELCHANGE(IDC_BM2, OnSelchangeBm2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SynchronizeBookmarkDialog �ǉ����\�b�h

void
SynchronizeBookmarkDialog::ChangeButtons( const char *bookmark1 = NULL,
                                          const char *bookmark2 = NULL )
{
    if ( bookmark1 == NULL ) {
        int location = m_bookmarkList1.GetCurSel();
        m_bookmarkList1.GetLBText( location, m_bookmark1 );
    }
    if ( bookmark2 == NULL ) {
        int location = m_bookmarkList2.GetCurSel();
        m_bookmarkList2.GetLBText( location, m_bookmark2 );
    }

    CString dir;
    dir.LoadString(IDS_DOUBLE_DIRECTION);

    CStatic *p = (CStatic *)GetDlgItem( IDC_BMNAMES );
    CString text = m_bookmark1 + dir + m_bookmark2;
    p->SetWindowText( text );

    char        txt[BUFSIZ * 2];
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    CButton     *bp = (CButton *)GetDlgItem( IDC_BUTTON_SYNC1 );
    text.LoadString(IDS_BTN_IMPORT_A);
    if ( pp->m_langCode == 0x0411 )
        sprintf( txt, text,
                 (const char *)m_bookmark1,
                 (const char *)m_bookmark2 );   // ���{��
    else
        sprintf( txt, text,
                 (const char *)m_bookmark2,
                 (const char *)m_bookmark1 );   // �p��
    bp->SetWindowText( txt );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_SYNC2 );
    if ( pp->m_langCode == 0x0411 )
        sprintf( txt, text,
                 (const char *)m_bookmark2,
                 (const char *)m_bookmark1 );   // ���{��
    else
        sprintf( txt, text,
                 (const char *)m_bookmark1,
                 (const char *)m_bookmark2 );   // �p��
    bp->SetWindowText( txt );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_SYNC3 );
    text.LoadString(IDS_BTN_IMPORT_AB);
    if ( pp->m_langCode == 0x0411 )
        sprintf( txt, text,
                 (const char *)m_bookmark1,
                 (const char *)m_bookmark2 );   // ���{��
    else
        sprintf( txt, text,
                 (const char *)m_bookmark2,
                 (const char *)m_bookmark1,
                 (const char *)m_bookmark1,
                 (const char *)m_bookmark2 );   // �p��
    bp->SetWindowText( txt );
}

/////////////////////////////////////////////////////////////////////////////
// SynchronizeBookmarkDialog ���b�Z�[�W �n���h��

void SynchronizeBookmarkDialog::OnButtonSync1() 
{
    int location = m_bookmarkList1.GetCurSel();
	m_bookmarkList1.GetLBText( location, m_bookmark1 );

    location = m_bookmarkList2.GetCurSel();
	m_bookmarkList2.GetLBText( location, m_bookmark2 );

    m_direction = fromBM1toBM2;
	OnOK();
}

void SynchronizeBookmarkDialog::OnButtonSync2() 
{
    int location = m_bookmarkList1.GetCurSel();
	m_bookmarkList1.GetLBText( location, m_bookmark1 );

    location = m_bookmarkList2.GetCurSel();
	m_bookmarkList2.GetLBText( location, m_bookmark2 );

    m_direction = fromBM2toBM1;
	OnOK();
}

void SynchronizeBookmarkDialog::OnButtonSync3() 
{
    int location = m_bookmarkList1.GetCurSel();
	m_bookmarkList1.GetLBText( location, m_bookmark1 );

    location = m_bookmarkList2.GetCurSel();
	m_bookmarkList2.GetLBText( location, m_bookmark2 );

    m_direction = both;
	OnOK();
}

void SynchronizeBookmarkDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        m_bookmarkList1.SetCurSel( 0 );
        m_bookmarkList2.SetCurSel( 1 );
        ChangeButtons();
    }
}

void SynchronizeBookmarkDialog::OnSelchangeBm1() 
{
    int location = m_bookmarkList1.GetCurSel();
	m_bookmarkList1.GetLBText( location, m_bookmark1 );

    location = m_bookmarkList2.GetCurSel();
	m_bookmarkList2.GetLBText( location, m_bookmark2 );

    if ( m_bookmark1.Compare( m_bookmark2 ) == 0 ) {
        location = ((location + 1) % m_bookmarkList2.GetCount());
        m_bookmarkList2.SetCurSel( location );
    	m_bookmarkList2.GetLBText( location, m_bookmark2 );
    }

    ChangeButtons( m_bookmark1, m_bookmark2 );
}

void SynchronizeBookmarkDialog::OnSelchangeBm2() 
{
    int location = m_bookmarkList1.GetCurSel();
	m_bookmarkList1.GetLBText( location, m_bookmark1 );

    location = m_bookmarkList2.GetCurSel();
	m_bookmarkList2.GetLBText( location, m_bookmark2 );

    if ( m_bookmark1.Compare( m_bookmark2 ) == 0 ) {
        location = ((location + 1) % m_bookmarkList2.GetCount());
        m_bookmarkList2.SetCurSel( location );
    	m_bookmarkList2.GetLBText( location, m_bookmark2 );
    }

    ChangeButtons( m_bookmark1, m_bookmark2 );
}

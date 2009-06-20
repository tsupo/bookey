/*
 * SettingDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �ݒ�_�C�A���O(����) �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 26    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 25    08/07/25 17:39 Tsujimura543
 * Diigo �ɑΉ�
 * 
 * 24    08/02/27 1:13 Tsujimura543
 * (1) �����̋��E�l�� 720px �� 800px �ɕύX (���ۂ� 780px �ő��v�����ǁA
 *     �]�T�����āA800px �ɂ��Ă���)
 * (2) �ɗ́A�\�[�X�R�[�h���̃}�W�b�N�i���o�[�����炷�悤�ɂ��Ă݂�
 * 
 * 23    08/02/20 23:21 Tsujimura543
 * �f�B�X�v���C�̏c�����̑傫��(����)�� 720px �ȉ��̏ꍇ�́A�\������
 * �_�C�A���O�̑傫�����c�����ɏ���������悤�ɂ��Ă݂�
 * 
 * 22    07/10/31 16:58 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 21    07/07/09 19:15 Tsujimura543
 * digg �ɑΉ�
 * 
 * 20    07/06/08 22:29 Tsujimura543
 * CTabDialog �̓����ɂ�� OnButtonAccept() ���R���p�N�g��
 * 
 * 19    07/05/23 16:01 Tsujimura543
 * Timelog �ɑΉ�
 * 
 * 18    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 17    07/04/16 20:45 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �Ή�
 * 
 * 16    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 15    07/03/30 16:12 Tsujimura543
 * FC2BOOKMARK �ɑΉ�
 * 
 * 14    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 13    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 12    06/12/22 22:33 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�Ή�
 * 
 * 11    06/12/21 16:37 Tsujimura543
 * JoltMark �Ή�
 * 
 * 10    06/10/26 21:01 Tsujimura543
 * �u���[�J��OPML�t�@�C���v�ɑΉ�
 * 
 * 9     06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 8     06/10/04 20:24 Tsujimura543
 * pookmark �Ή�
 * 
 * 7     06/09/29 18:45 Tsujimura543
 * �R�����g���C��
 * 
 * 6     06/09/29 18:44 Tsujimura543
 * newsing �Ή�
 * 
 * 5     06/08/23 21:35 Tsujimura543
 * �u1470.net���j���[�A���ł̃��[�U��񖢐ݒ�̂܂܁A�폜�����s���悤�Ƃ�
 * ���Ƃ��v�̃��[�U���ݒ�p�_�C�A���O�\��������������
 * 
 * 4     06/07/31 17:15 Tsujimura543
 * warning #4100 �� disable �ɂ���
 * 
 * 3     06/07/28 23:58 Tsujimura543
 * �f�[�^�̐��������`�F�b�N���鏈����ǉ�
 * 
 * 2     06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 */

#include "bookey.h"
#include "SettingDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDialog �_�C�A���O

#define DISPLAY_HEIGHT_LIMIT    800

SettingDialog::SettingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SettingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDialog)
	//}}AFX_DATA_INIT

    m_dlg[0]  = &m_dlg00;
    m_dlg[1]  = &m_dlg01;
    m_dlg[2]  = &m_dlg02;
    m_dlg[3]  = &m_dlg03;
    m_dlg[4]  = &m_dlg04;
    m_dlg[5]  = &m_dlg05;
    m_dlg[6]  = &m_dlg06;
    m_dlg[7]  = &m_dlg07;
    m_dlg[8]  = &m_dlg08;
    m_dlg[9]  = &m_dlg09;
    m_dlg[10] = &m_dlg10;
    m_dlg[11] = &m_dlg11;
    m_dlg[12] = &m_dlg12;
    m_dlg[13] = &m_dlg13;
    m_dlg[14] = &m_dlg14;
    m_dlg[15] = &m_dlg15;
    m_dlg[16] = &m_dlg16;
    m_dlg[17] = &m_dlg17;
    m_dlg[18] = &m_dlg18;
    m_dlg[19] = &m_dlg19;
    m_dlg[20] = &m_dlg20;
    m_dlg[21] = &m_dlg21;
    m_dlg[22] = &m_dlg22;

    m_1470net     = false;
    m_numOfTabs   = 0;
    m_width       = 0;
    m_height      = 0;
    m_base        = 0;
    m_dialogWidth = 0;
    m_resized     = false;
}


void SettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDialog)
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
	//}}AFX_DATA_MAP
}

BOOL SettingDialog::CheckDlgData()
{
    return ( m_dlg[m_activePage]->UpdateData() );
}

int SettingDialog::DispCurrentTab( int activeTab /* = 0 */ )
{
    if ( activeTab != 0 )
        m_tabSetting.SetCurSel( activeTab );

    m_activePage = m_tabSetting.GetCurSel();
    int nPages   = m_tabSetting.GetItemCount();

    for ( int i = 0; i < nPages; i++ )
        if ( i != m_activePage )
            m_dlg[i]->ShowWindow( SW_HIDE );

    m_dlg[m_activePage]->ShowWindow( SW_SHOW );

    if ( (m_height <= DISPLAY_HEIGHT_LIMIT) && !m_resized ) {
        // �������T�C�Y�̃_�C�A���O��\������
        CRect   rcClient;
        int     tabSettingDiffY = 160;  // �^�u�̌��ˑ��ŕύX����K�v������
        int     clientDiffY     = tabSettingDiffY + 20; // 20 = �{�^���̌���(20px)

        GetClientRect( &rcClient );
        rcClient.bottom -= tabSettingDiffY;
        MoveWindow( &rcClient );

        m_tabSetting.GetWindowRect( &rcClient );
        rcClient.bottom -= clientDiffY;
        m_tabSetting.MoveWindow( &rcClient );

        m_resized = true;
    }

    return ( m_activePage );
}

BEGIN_MESSAGE_MAP(SettingDialog, CDialog)
	//{{AFX_MSG_MAP(SettingDialog)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, OnButtonAccept)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingDialog ���b�Z�[�W �n���h��

BOOL SettingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

    if ( m_height <= DISPLAY_HEIGHT_LIMIT ) {
        int     height      = 0;
        int     width       = 0;
        int     buttonDiffX = 4;    // �{�^���ƃ{�^���̊�(������)�� 4px �󂯂�

        CRect   rectM;
        CButton *bp = (CButton *)GetDlgItem( IDOK );
     // if ( bp->GetSafeHwnd() && bp->IsWindowEnabled() ) {
            bp->GetWindowRect( &rectM );
            height = rectM.bottom - rectM.top;
            width  = rectM.right  - rectM.left;
            buttonDiffX += width;

            rectM.top    = m_base + 2;
            rectM.bottom = rectM.top + height;
            rectM.left   = (m_dialogWidth - (buttonDiffX * 3)) / 2 + 2;
            rectM.right  = rectM.left + width;
            bp->MoveWindow( rectM );
            bp->EnableWindow();

     // }

        CRect   rectM2;
        bp = (CButton *)GetDlgItem( IDCANCEL );
     // if ( bp->GetSafeHwnd() && bp->IsWindowEnabled() ) {
            bp->GetWindowRect( &rectM2 );
            height = rectM2.bottom - rectM2.top;
            width  = rectM2.right  - rectM2.left;
            rectM2.top    = rectM.top;
            rectM2.bottom = rectM2.top  + height;
            rectM2.left   = rectM.left  + buttonDiffX;
            rectM2.right  = rectM2.left + width;
            bp->MoveWindow( rectM2 );
            bp->EnableWindow();
     // }

        CRect   rectM3;
        bp = (CButton *)GetDlgItem( IDC_BUTTON_ACCEPT );
     // if ( bp->GetSafeHwnd() && bp->IsWindowEnabled() ) {
            bp->GetWindowRect( &rectM3 );
            height = rectM3.bottom - rectM3.top;
            width  = rectM3.right  - rectM3.left;
            rectM3.top    = rectM2.top;
            rectM3.bottom = rectM3.top  + height;
            rectM3.left   = rectM2.left + buttonDiffX;
            rectM3.right  = rectM3.left + width;
            bp->MoveWindow( rectM3 );
            bp->EnableWindow();
     // }
    }

    return TRUE;
}

void SettingDialog::OnButtonAccept() 
{
    if ( CheckDlgData() == FALSE )
        return;

    ((CTabDialog *)m_dlg[m_activePage])->Accept();
}

void SettingDialog::OnOK() 
{
    int nPages = m_tabSetting.GetItemCount();

    for ( int i = 0; i < nPages; i++ ) {
        m_activePage = i;
        if ( CheckDlgData() == FALSE )
            return;
        OnButtonAccept();
    }
	CDialog::OnOK();
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
BOOL SettingDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
    LPNMHDR pNMHDR      = (LPNMHDR)lParam;
    int     nActivePage = -1;

    switch ( pNMHDR->code ) {
    case TCN_SELCHANGE:
        nActivePage = DispCurrentTab();
        break;
    }

    return ( TRUE );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void SettingDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

    CRect   rcClient;
    GetClientRect( &rcClient );
    m_tabSetting.MoveWindow( &rcClient );

    CRect   rcTabCtrl;
    m_tabSetting.GetClientRect( &rcTabCtrl );

    int nPages = m_tabSetting.GetItemCount();
    int nRow   = m_tabSetting.GetRowCount();

    CRect   rcTabZero;
    m_tabSetting.GetItemRect( 0, &rcTabZero );

    int         iTabHeight = rcTabZero.Size().cy;
    const int   border     = 5;

    CRect   rcTabDisp;
    rcTabDisp.top    = iTabHeight * nRow + border;
    rcTabDisp.left   = border;
    rcTabDisp.right  = rcTabCtrl.right  - border;
    rcTabDisp.bottom = rcTabCtrl.bottom - border - 30;
    m_base           = rcTabDisp.bottom;
    m_dialogWidth    = rcTabCtrl.right - rcTabCtrl.left;

    for ( int i = 0; i < nPages; i++ )
        m_dlg[i]->MoveWindow( &rcTabDisp );
}

int SettingDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

    m_width  = GetSystemMetrics(SM_CXSCREEN);
    m_height = GetSystemMetrics(SM_CYSCREEN);

    BOOL    bResult;
    if ( m_height <= DISPLAY_HEIGHT_LIMIT )
        bResult = m_tabSetting.Create( WS_CHILD | WS_VISIBLE,
                                       CRect(0, 0, 0, 0), this,
                                       IDD_SETTING_DIALOG );
    else
        bResult = m_tabSetting.Create( WS_CHILD | WS_VISIBLE | TCS_MULTILINE,
                                       CRect(0, 0, 0, 0), this,
                                       IDD_SETTING_DIALOG );
    if ( bResult == FALSE )
		return -1;

    // �e�^�u�̕����̐ݒ�
    TCITEM      tc;
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_hatena);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_delicious);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_mmMemo);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_drecomRss);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_flog);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_livedoorClip);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_ecNaviClip);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_niftyClip);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_next1470net);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_newsing);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_pookmark);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_blueDot);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_joltMark);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_blogPet);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_fc2bookmark);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_twitter);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_yjBookmark);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_yahooBookmarks);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_timelog);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_digg);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_tumblr);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_diigo);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    tc.mask = TCIF_TEXT;
    tc.pszText = (char *)((const char*)pp->m_localOpml);
    m_tabSetting.InsertItem( m_numOfTabs++, &tc );

    ASSERT( m_numOfTabs == NUM_OF_TABS );

    // �f�t�H���g�̃^�u��I��
    m_tabSetting.SetCurSel( 0 );

    // �e�^�u�ɓ\��t����_�C�A���O�� Create
    LPCTSTR idd[] = {
        (LPCTSTR)IDD_TAB_HATENA,
        (LPCTSTR)IDD_TAB_DELICIOUS,
        (LPCTSTR)IDD_TAB_MMMEMO,
        (LPCTSTR)IDD_TAB_DRECOM,
        (LPCTSTR)IDD_TAB_FLOG,
        (LPCTSTR)IDD_TAB_LIVEDOOR,
        (LPCTSTR)IDD_TAB_ECNAVI,
        (LPCTSTR)IDD_TAB_NIFTY,
        (LPCTSTR)IDD_TAB_1470NET,
        (LPCTSTR)IDD_TAB_NEWSING,
        (LPCTSTR)IDD_TAB_POOKMARK,
        (LPCTSTR)IDD_TAB_BLUEDOT,
        (LPCTSTR)IDD_TAB_JOLTMARK,
        (LPCTSTR)IDD_TAB_BLOGPET,
        (LPCTSTR)IDD_TAB_FC2BOOKMARK,
        (LPCTSTR)IDD_TAB_TWITTER,
        (LPCTSTR)IDD_TAB_YJ_BOOKMARK,
        (LPCTSTR)IDD_TAB_YAHOO_BOOKMARKS,
        (LPCTSTR)IDD_TAB_TIMELOG,
        (LPCTSTR)IDD_TAB_DIGG,
        (LPCTSTR)IDD_TAB_TUMBLR,
        (LPCTSTR)IDD_TAB_DIIGO,
        (LPCTSTR)IDD_TAB_LOCALOPML
    };

    for ( int i = 0; i < m_numOfTabs; i++ ) {
        bResult = m_dlg[i]->Create( idd[i], this );
        if ( bResult == FALSE )
    		return -1;
    }

    // �f�t�H���g�̃^�u��\��
    if ( m_1470net )
        m_activePage = 8;
    else
        m_activePage = 0;
    DispCurrentTab( m_activePage );

	return 0;
}

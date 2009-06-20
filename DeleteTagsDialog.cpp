/*
 * DeleteTagsDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �^�O�폜�_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  24 Jan 2007
 *
 * $Log: /comm/bookey/DeleteTagsDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 6     08/07/25 22:17 Tsujimura543
 * Diigo �Ή�����
 * 
 * 5     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 4     07/01/30 0:53 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 3     07/01/29 22:01 Tsujimura543
 * ���[�U�C���^�[�t�F�[�X�̃��W�b�N�����A�t�B�b�N�X
 * 
 * 2     07/01/29 17:53 Tsujimura543
 * ���[�U�C���^�[�t�F�[�X�̍ו����l�߂�K�v���c���Ă��邪�A�Ƃ肠�����A
 * �g������̂�����
 * 
 * 1     07/01/24 21:01 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "bookey.h"
#include "DeleteTagsDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteTagsDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteTagsDialog �_�C�A���O

CDeleteTagsDialog::CDeleteTagsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteTagsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteTagsDialog)
	m_bookmarkName = _T("");
	m_tag = _T("");
	//}}AFX_DATA_INIT

    m_numOfTags = 0;
    m_tagIndex  = -1;

    m_tgt_hatenaBookmark.LoadString( IDS_TGT_HATENA_BOOKMARK );
    m_tgt_delicious.LoadString( IDS_TGT_DELICIOUS );
    m_tgt_mmMemo.LoadString( IDS_TGT_MMMEMO );
    m_tgt_drecomRSS.LoadString( IDS_TGT_DRECOM_RSS );
    m_tgt_flog.LoadString( IDS_TGT_FLOG );
    m_tgt_livedoorClip.LoadString( IDS_TGT_LIVEDOOR_CLIP );
    m_tgt_ecNaviClip.LoadString( IDS_TGT_ECNAVI_CLIP );
    m_tgt_niftyClip.LoadString( IDS_TGT_NIFTY_CLIP );
    m_tgt_1470net.LoadString( IDS_TGT_1470NET );
    m_tgt_pookmark.LoadString( IDS_TGT_POOKMARK );
    m_tgt_blueDot.LoadString( IDS_TGT_BLUEDOT );
    m_tgt_joltMark.LoadString( IDS_TGT_JOLTMARK );
    m_tgt_blogPet.LoadString( IDS_TGT_BLOGPET );
    m_tgt_fc2Bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_localOPML.LoadString( IDS_TGT_LOCAL_OPML );
}

void CDeleteTagsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteTagsDialog)
	DDX_Control(pDX, IDC_COMBO_DELETELIST_TAGS, m_bookmarkList);
	DDX_Control(pDX, IDC_COMBO_DELETE_TAGLIST, m_tagList);
	DDX_CBString(pDX, IDC_COMBO_DELETELIST_TAGS, m_bookmarkName);
	DDV_MaxChars(pDX, m_bookmarkName, 96);
	DDX_CBString(pDX, IDC_COMBO_DELETE_TAGLIST, m_tag);
	DDV_MaxChars(pDX, m_tag, 512);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDeleteTagsDialog, CDialog)
	//{{AFX_MSG_MAP(CDeleteTagsDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_TAGS, OnButtonGetTags)
	ON_BN_CLICKED(IDOK, OnDeleteTags)
	ON_CBN_SELCHANGE(IDC_COMBO_DELETE_TAGLIST, OnSelchangeComboDeleteTaglist)
	ON_CBN_SELCHANGE(IDC_COMBO_DELETELIST_TAGS, OnSelchangeComboDeletelistTags)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteTagsDialog ���b�Z�[�W �n���h��

void CDeleteTagsDialog::OnButtonGetTags() 
{
    if ( m_targetBookmark != CUserInfo::BK_UNKNOWN ) {
        // �^�O�̈ꗗ���擾
        CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
        ProceedingDialog    dlg;

        CString title;
        CString text;

        title.LoadString(IDS_TTL_CONTINUE_GET_TAG_LIST);
        text.LoadString( IDS_TXT_CONTINUE_GET_TAG_LIST);

        dlg.Create( IDD_PROCEEDING_DIALOG );
        dlg.ChangeDialogText( title,    // �^�O�ꗗ�擾
                              text );   // �^�O�ꗗ�擾���c�c

        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        TagList     *p  = pp->GetTagList( m_targetBookmark, m_numOfTags );

        if ( p && (m_numOfTags > 0) ) {
            // �^�O�̈ꗗ��I�����Ƃ��ēo�^
            if ( m_tagList.GetCount() > 0 )
                m_tagList.ResetContent();
            m_tagList.InitStorage( m_numOfTags,
                                   BUFSIZ * m_numOfTags );

            int     i;
            char    *q;
            TagList *qq = p;
            for ( i = 0; i < m_numOfTags; i++, qq++ ) {
                q = utf2sjisEx( qq->tag );
                m_tagList.AddString( q ? q : qq->tag );
            }
        }

        if ( p )
            free( p );
    }
}

void CDeleteTagsDialog::OnDeleteTags() 
{
    if ( (m_targetBookmark != CUserInfo::BK_UNKNOWN) &&
         (m_tag.GetLength() > 0)                        ) {
        CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
        ProceedingDialog    dlg;

        CString title;
        CString text;

        title.LoadString(IDS_TTL_CONTINUE_DELETE_TAGS);
        text.LoadString( IDS_TXT_CONTINUE_DELETE_TAGS);

        dlg.Create( IDD_PROCEEDING_DIALOG );
        dlg.ChangeDialogText( title,    // �w�肳�ꂽ�^�O�̍폜
                              text );   // �w�肳�ꂽ�^�O�̍폜���c�c

        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        pp->DeleteTag( m_targetBookmark, m_tag );

        m_tagList.DeleteString( m_tagIndex );
        m_numOfTags--;
        if ( m_numOfTags <= 0 ) {
            m_targetBookmark = CUserInfo::BK_UNKNOWN;
            m_tagList.ResetContent();
        }
        m_tag      = "";
        m_tagIndex = -1;

        CButton *p = (CButton *)GetDlgItem( IDOK );
        p->EnableWindow( FALSE );

        if ( pp->m_langCode == 0x0411 ) {
            p = (CButton *)GetDlgItem( IDCANCEL );
            p->SetWindowText( "�I��" );
        }
    }
}

void CDeleteTagsDialog::OnSelchangeComboDeleteTaglist() 
{
    int     location = m_tagList.GetCurSel();
    CButton *p = (CButton *)GetDlgItem( IDOK );

    if ( location == LB_ERR ) {
        p->EnableWindow( FALSE );
        return;
    }

	m_tagList.GetLBText( location, m_tag );
    m_tagIndex = location;

    p->EnableWindow( TRUE );
}

void CDeleteTagsDialog::OnSelchangeComboDeletelistTags() 
{
    int     location = m_bookmarkList.GetCurSel();
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET_TAGS );

    if ( location == LB_ERR ) {
        p->EnableWindow( FALSE );
        return;
    }

    CString bookmarkName = m_bookmarkName;

	m_bookmarkList.GetLBText( location, m_bookmarkName );
    if ( m_bookmarkName.Compare( bookmarkName ) == 0 )
        return; // �ω��Ȃ�

    m_targetBookmark = CUserInfo::BK_UNKNOWN;

    if ( m_tagList.GetCount() > 0 ) {
        m_numOfTags = 0;
        m_tagList.ResetContent();

        CButton *q = (CButton *)GetDlgItem( IDOK );
        q->EnableWindow( FALSE );
    }

    if ( m_bookmarkName.Compare( m_tgt_hatenaBookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_HATENA;
    else
    if ( m_bookmarkName.Compare( m_tgt_delicious ) == 0 )
        m_targetBookmark = CUserInfo::BK_DELICIOUS;
    else
    if ( m_bookmarkName.Compare( m_tgt_mmMemo ) == 0 )
        m_targetBookmark = CUserInfo::BK_MM_MEMO;
    else
    if ( m_bookmarkName.Compare( m_tgt_drecomRSS ) == 0 )
        m_targetBookmark = CUserInfo::BK_DRECOM_RSS;
    else
    if ( m_bookmarkName.Compare( m_tgt_flog ) == 0 )
        m_targetBookmark = CUserInfo::BK_FLOG;
    else
    if ( m_bookmarkName.Compare( m_tgt_livedoorClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_LIVEDOOR_CLIP;
    else
    if ( m_bookmarkName.Compare( m_tgt_ecNaviClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_ECNAVI_CLIP;
    else
    if ( m_bookmarkName.Compare( m_tgt_niftyClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_NIFTY_CLIP;
    else
    if ( m_bookmarkName.Compare( m_tgt_1470net ) == 0 )
        m_targetBookmark = CUserInfo::BK_1470NET;
    else
    if ( m_bookmarkName.Compare( m_tgt_pookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_POOKMARK;
    else
    if ( m_bookmarkName.Compare( m_tgt_blueDot ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLUEDOT;
    else
    if ( m_bookmarkName.Compare( m_tgt_joltMark ) == 0 )
        m_targetBookmark = CUserInfo::BK_JOLTMARK;
    else
    if ( m_bookmarkName.Compare( m_tgt_blogPet ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLOGPET;
    else
    if ( m_bookmarkName.Compare( m_tgt_fc2Bookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_FC2BOOKMARK;
    else
    if ( m_bookmarkName.Compare( m_tgt_diigo ) == 0 )
        m_targetBookmark = CUserInfo::BK_DIIGO;
    else
    if ( m_bookmarkName.Compare( m_tgt_localOPML ) == 0 )
        m_targetBookmark = CUserInfo::BK_LOCAL_OPML;

    p->EnableWindow( TRUE );
}

void CDeleteTagsDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET_TAGS );
        p->EnableWindow( FALSE );

        p = (CButton *)GetDlgItem( IDOK );
        p->EnableWindow( FALSE );
    }
}

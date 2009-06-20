/*
 * DeleteBookmarkDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�폜�_�C�A���O ����1 �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  30 Sep 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 24    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 23    08/07/25 22:17 Tsujimura543
 * Diigo �Ή�����
 * 
 * 22    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks �� Yahoo! �u�b�N�}�[�N�́u�폜�v�ɑΉ�
 * 
 * 21    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 20    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 19    07/01/12 22:45 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 18    07/01/11 17:01 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 17    06/12/22 21:47 Tsujimura543
 * �R�����g�C��
 * 
 * 16    06/12/21 21:18 Tsujimura543
 * JoltMark�AFC2BOOKMARK�A�uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 15    06/10/26 22:38 Tsujimura543
 * �u���[�J��OPML�v�ɑΉ�
 * 
 * 14    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 13    06/10/05 22:30 Tsujimura543
 * POOKMARK Airlines �́u�폜�v�ɑΉ�
 * 
 * 12    06/08/22 11:46 Tsujimura543
 * �s�v�ɂȂ����������폜
 * 
 * 11    06/08/22 11:43 Tsujimura543
 * DeleteBookmarkDialog �� DeleteBookmarkDialog2 ��1�̃_�C�A���O��
 * �܂Ƃ߂� (DeleteBookmarkDialog2 �͔p�~)
 * 
 * 10    06/07/12 9:33 Tsujimura543
 * livedoor�N���b�v�AEC�i�r�l�C�j���[�X�A�j�t�e�B�N���b�v�̍폜�{�^�����
 * ��
 * 
 * 9     06/06/27 15:24 Tsujimura543
 * Flog �̍폜�ɑΉ�
 * 
 * 8     06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 7     06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 6     06/06/01 19:04 Tsujimura543
 * �u�b�N�}�[�N��ʂ����� enum �l���Aenum CUserInfo::bookmarkType ��
 * ��{������
 * 
 * 5     05/11/01 16:50 Tsujimura543
 * (1) �����������t�@�N�^�����O
 * (2) MM/Memo �̍폜�֘A�������쐬
 * 
 * 4     05/10/31 21:42 Tsujimura543
 * MM/Memo �� BlogPeople Tags �̍폜�ɑΉ�
 * 
 * 3     05/10/11 17:01 Tsujimura543
 * ���ł̃^�C���X�^���v�\�L�~�X���C�� (�R�����g�݂̂̏C���B����ɉe���Ȃ�)
 * 
 * 2     05/10/01 0:00 Tsujimura543
 * �u�b�N�}�[�N�̎擾�A�o�^�@�\�̓���m�F����
 */

#include "bookey.h"
#include "DeleteBookmarkDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteBookmarkDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog �_�C�A���O


DeleteBookmarkDialog::DeleteBookmarkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DeleteBookmarkDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(DeleteBookmarkDialog)
	//}}AFX_DATA_INIT

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
    m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
    m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_localOPML.LoadString( IDS_TGT_LOCAL_OPML );
}


void DeleteBookmarkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeleteBookmarkDialog)
	DDX_Control(pDX, IDC_COMBO_DELETELIST, m_bookmark);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DeleteBookmarkDialog, CDialog)
	//{{AFX_MSG_MAP(DeleteBookmarkDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_DELETE_INTERACTIVE, OnButtonDeleteInteractive)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL, OnButtonDeleteAll)
	ON_CBN_SELCHANGE(IDC_COMBO_DELETELIST, OnSelchangeComboDeleteList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog ���b�Z�[�W �n���h��

void DeleteBookmarkDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        m_targetBookmark    = CUserInfo::BK_UNKNOWN;
    	m_deleteAll         = false;
    	m_deleteInteractive = false;
    }
}

void DeleteBookmarkDialog::OnButtonDeleteInteractive() 
{
	m_deleteInteractive = true;
    if ( m_targetBookmark != CUserInfo::BK_UNKNOWN )
        OnOK();
}

void DeleteBookmarkDialog::OnButtonDeleteAll() 
{
	m_deleteAll = true;
    if ( m_targetBookmark != CUserInfo::BK_UNKNOWN )
        OnOK();
}

void DeleteBookmarkDialog::OnSelchangeComboDeleteList() 
{
    CString     bookmarkName;
    int         location = m_bookmark.GetCurSel();

	m_bookmark.GetLBText( location, bookmarkName );
    if ( bookmarkName.Compare( m_tgt_hatenaBookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_HATENA;
    else
    if ( bookmarkName.Compare( m_tgt_delicious ) == 0 )
        m_targetBookmark = CUserInfo::BK_DELICIOUS;
    else
    if ( bookmarkName.Compare( m_tgt_mmMemo ) == 0 )
        m_targetBookmark = CUserInfo::BK_MM_MEMO;
    else
    if ( bookmarkName.Compare( m_tgt_drecomRSS ) == 0 )
        m_targetBookmark = CUserInfo::BK_DRECOM_RSS;
    else
    if ( bookmarkName.Compare( m_tgt_flog ) == 0 )
        m_targetBookmark = CUserInfo::BK_FLOG;
    else
    if ( bookmarkName.Compare( m_tgt_livedoorClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_LIVEDOOR_CLIP;
    else
    if ( bookmarkName.Compare( m_tgt_ecNaviClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_ECNAVI_CLIP;
    else
    if ( bookmarkName.Compare( m_tgt_niftyClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_NIFTY_CLIP;
    else
    if ( bookmarkName.Compare( m_tgt_1470net ) == 0 )
        m_targetBookmark = CUserInfo::BK_1470NET;
    else
    if ( bookmarkName.Compare( m_tgt_pookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_POOKMARK;
    else
    if ( bookmarkName.Compare( m_tgt_blueDot ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLUEDOT;
    else
    if ( bookmarkName.Compare( m_tgt_joltMark ) == 0 )
        m_targetBookmark = CUserInfo::BK_JOLTMARK;
    else
    if ( bookmarkName.Compare( m_tgt_blogPet ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLOGPET;
    else
    if ( bookmarkName.Compare( m_tgt_fc2Bookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_FC2BOOKMARK;
    else
    if ( bookmarkName.Compare( m_tgt_yjBookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_YJ_BOOKMARK;
    else
    if ( bookmarkName.Compare( m_tgt_yahooBookmarks ) == 0 )
        m_targetBookmark = CUserInfo::BK_YAHOO_BOOKMARKS;
    else
    if ( bookmarkName.Compare( m_tgt_diigo ) == 0 )
        m_targetBookmark = CUserInfo::BK_DIIGO;
    else
    if ( bookmarkName.Compare( m_tgt_localOPML ) == 0 )
        m_targetBookmark = CUserInfo::BK_LOCAL_OPML;
}

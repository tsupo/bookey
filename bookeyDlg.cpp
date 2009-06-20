/*
 * bookeyDlg.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      ���C���_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookeyDlg.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 84    08/10/22 13:34 Tsujimura543
 * �R�����g���C��
 * 
 * 83    08/10/22 13:33 Tsujimura543
 * IDM_ABOUT_SUPPORT, IDM_ABOUT_SUPPORT2,
 * IDM_ABOUT_COMMUNITY, IDM_ABOUT_COMMUNITY2
 * �̒�`�� AboutDlg.h �ֈڊ�
 * 
 * 82    08/10/21 22:04 Tsujimura543
 * ABOUT_SUPPORT2 ��ǉ�
 * 
 * 81    08/10/21 21:24 Tsujimura543
 * ABOUT_SUPPORT, ABOUT_COMMUNITY, ABOUT_COMMUNITY2 �ǉ�
 * 
 * 80    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 79    08/07/25 22:16 Tsujimura543
 * Diigo �Ή�
 * 
 * 78    07/04/20 20:34 Tsujimura543
 * Yahoo! �u�b�N�}�[�N�AYahoo! Bookmarks �̃C���|�[�g�ƃG�N�X�|�[�g�ɑΉ�
 * 
 * 77    07/04/16 18:23 Tsujimura543
 * �R�����g���C��
 * 
 * 76    07/04/16 17:59 Tsujimura543
 * del.icio.us �� posts/all �`���� XML �t�@�C���̃C���|�[�g�ƃG�N�X�|�[�g
 * �ɑΉ�����
 * 
 * 75    07/04/11 17:03 Tsujimura543
 * �Ő����̓��\�[�X�t�@�C�����玝���Ă����̂�\������悤�ɂ��Ă݂�
 * 
 * 74    07/03/29 15:18 Tsujimura543
 * FC2BOOKMARK �ɑΉ�����
 * 
 * 73    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 72    07/01/30 0:33 Tsujimura543
 * EnableButton() ��ύX���A�u�^�O�̍폜�v�A�u�^�O�̒u���v�{�^���̐���ɂ�
 * �Ή�����
 * 
 * 71    07/01/24 20:55 Tsujimura543
 * �u�^�O�̍폜�v�Ɓu�^�O�̒u���v�{�^�����e�X�ǉ�
 * 
 * 70    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 69    07/01/15 22:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 68    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 67    07/01/11 17:01 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 66    06/12/22 21:44 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�Ή�
 * 
 * 65    06/12/21 19:18 Tsujimura543
 * JoltMark �Ή�
 * 
 * 64    06/12/06 19:48 Tsujimura543
 * �R�����g���C��
 * 
 * 63    06/12/06 19:46 Tsujimura543
 * livedoor Clip �̃G�N�X�|�[�g�t�@�C��(RSS 2.0 �`��)���C���|�[�g����@�\
 * ��ǉ�����
 * 
 * 62    06/11/27 16:03 Tsujimura543
 * POOKMARK Airlines ����̃u�b�N�}�[�N�擾�Ɋւ��āA�p�X���[�h�w��Ȃ�
 * �̏ꍇ��(���J����Ă�����̂Ɍ�����)�擾�ł���悤�ɂ���
 * 
 * 61    06/11/16 16:43 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��16�i�K�A�I��
 * 
 * 60    06/11/16 14:06 Tsujimura543
 * CBookeyDlg �N���X���̃����o�ϐ��̂����A���͂�s�v�ɂȂ������̂��폜
 * 
 * 59    06/11/16 14:02 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��15�i�K�A�I��
 * 
 * 58    06/11/15 20:59 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̃G�N�X�|�[�g�`���̂����ARSS/Atom�t�B�[�h�`����
 * �t�@�C������̃u�b�N�}�[�N���̃C���|�[�g�ɂ��Ή����� (html�`����
 * �t�@�C���͂��łɑΉ��ς�)
 * 
 * 57    06/11/14 19:18 Tsujimura543
 * opera6.adr �`���̃t�@�C����ǂݏ�������Ƃ��̃t�@�C���_�C�A���O��
 * �\������t�@�C����ʂ��uOpera �u�b�N�}�[�N�t�@�C���v�ɕύX
 * 
 * 56    06/11/10 19:26 Tsujimura543
 * �u���E�U�̃u�b�N�}�[�N����荞��/�u���E�U�Ɏ�荞�߂�`���̃u�b�N�}�[�N
 * �t�@�C���𐶐�����@�\���T�|�[�g���邽�߂̏���
 * 
 * 55    06/10/18 19:41 Tsujimura543
 * BlueDot �Ɋւ��āA�C�ӂ̃��[�U�̃u�b�N�}�[�N���擾�ł���悤�ɂ���
 * 
 * 54    06/10/10 16:52 Tsujimura543
 * OnButtonPut() ���� title �� Shift_JIS ���� UTF-8 �ɕϊ����鏈�����폜
 * (outputOpml() ���ł��ϊ����Ă��邽�߁A��d�ɕϊ����Ă��܂��ĕ�������
 * ���������邱�Ƃ����邱�Ƃ������������߁A�C�������{)
 * 
 * 53    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 52    06/10/05 20:01 Tsujimura543
 * POOKMARK Airlines �ɑΉ�
 * 
 * 51    06/08/26 0:30 Tsujimura543
 * �R�����g���C��
 * 
 * 50    06/08/26 0:10 Tsujimura543
 * 1470.net���j���[�A���ł́u�擾�v�A�u�����v�ɑΉ�
 * (1470.net���j���[�A���łɊւ��Ă� OPML �`���ȊO�ł̏o�͂ɑΉ����邱�Ƃ�
 * �������BOPML �`���ł͑S�Ă̏���ۑ����؂�Ȃ�����)
 * 
 * 49    06/08/23 22:19 Tsujimura543
 * 1470.net���j���[�A���ł́u�����v���Ƀ��[�U����ݒ肵���ꍇ���A
 * ���̐ݒ���e�������ݒ�t�@�C���ɔ��f�ł���悤�ɂ���
 * 
 * 48    06/08/23 22:10 Tsujimura543
 * 1470.net���j���[�A���ł́u�폜�v���Ƀ��[�U����ݒ肵���ꍇ�A
 * ���̐ݒ���e�������ݒ�t�@�C���ɔ��f�ł���悤�ɂ���
 * 
 * 47    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 46    06/08/22 11:43 Tsujimura543
 * DeleteBookmarkDialog �� DeleteBookmarkDialog2 ��1�̃_�C�A���O��
 * �܂Ƃ߂� (DeleteBookmarkDialog2 �͔p�~)
 * 
 * 45    06/07/19 14:19 Tsujimura543
 * MyClip! �֌W�̏������폜 (2006�N6�����ŃT�[�r�X�I���̂���)
 * 
 * 44    06/07/15 0:56 Tsujimura543
 * 1470.net���j���[�A���łւ́u�o�^�v�ɑΉ�
 * 
 * 43    06/07/12 17:34 Tsujimura543
 * �h���R��RSS(��Clip!)�̎擾�A�����ɑΉ�
 * 
 * 42    06/07/07 19:34 Tsujimura543
 * �j�t�e�B�N���b�v�̎擾�A�����ɑΉ�
 * 
 * 41    06/07/06 19:53 Tsujimura543
 * livedoor�N���b�v�̎擾�A�����ɑΉ�
 * 
 * 40    06/06/30 19:43 Tsujimura543
 * EC�i�r�l�C�j���[�X�̎擾�A�����ɑΉ�
 * 
 * 39    06/06/29 18:47 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 38    06/06/29 0:51 Tsujimura543
 * livedoor�N���b�v�ւ̓o�^�����悤�Ƃ��Ă��A�o�^�{�^���� disable �̂܂�
 * �ω����Ȃ��s��ɑΏ�
 * 
 * 37    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 36    06/06/23 21:50 Tsujimura543
 * Flog �̎擾�A�����ɑΉ�����
 * 
 * 35    06/06/22 21:21 Tsujimura543
 * inquery �� inquiry �ɏC��(�Ԃ�~�X)
 * 
 * 34    06/06/20 14:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��9�i�K�A�I��
 * 
 * 33    06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 32    06/06/15 12:51 Tsujimura543
 * EnableButton() ��ǉ�
 * 
 * 31    06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 30    06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 29    06/06/06 22:23 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��
 * 
 * 28    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 27    06/06/01 22:20 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��1�i�K�A�I��
 * 
 * 26    06/06/01 20:28 Tsujimura543
 * CBookeyDlg ���̃��[�U���A�p�X���[�h�� CUserInfo ���g���ĊǗ�����
 * �悤�ɕύX����
 * 
 * 25    06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 24    06/06/01 19:04 Tsujimura543
 * �u�b�N�}�[�N��ʂ����� enum �l���Aenum CUserInfo::bookmarkType ��
 * ��{������
 * 
 * 23    06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 22    06/05/23 17:22 Tsujimura543
 * �\�[�X���������`
 * 
 * 21    06/05/22 19:31 Tsujimura543
 * �u�����v�Ώۂ̃u�b�N�}�[�N�擾�Ɏ��s�����ꍇ�́A�ēx�擾�����݂邩�ǂ�
 * ���u���悤�ɂ���
 * 
 * 20    06/04/07 14:01 Tsujimura543
 * �h���R��RSS(�� Clip!)�ւ̃u�b�N�}�[�N�̓o�^(�C���|�[�g)�ɑΉ�����
 * 
 * 19    06/03/13 16:48 Tsujimura543
 * CBookeyDlg::OnButtonSync() ���C�� (MM/Memo �� ���̃u�b�N�}�[�N �R�s�[��
 * �ɕ�����������s��ɑΏ�)
 * 
 * 18    06/02/17 22:02 Tsujimura543
 * 4�̃u�b�N�}�[�N�T�[�r�X�̂����A�C�ӂ�2�ҊԂœ���������悤�ɂ���
 * 
 * 17    06/02/17 18:07 Tsujimura543
 * �u�b�N�}�[�N�̓������A�͂Ăȃu�b�N�}�[�N��del.icio.us�ȊO�ɂ��e�ՂɑΉ�
 * �\�ɂ��邽�߁A�����̒��ۉ���i�߂�
 * 
 * 16    06/02/08 19:29 Tsujimura543
 * �u�b�N�}�[�N�ԓ����w���_�C�A���O�Ƃ̊Ԃ̃C���^�[�t�F�[�X��ύX
 * 
 * 15    05/11/10 22:25 Tsujimura543
 * �i�s�󋵕\���_�C�A���O���g���悤�ɂ���
 * 
 * 14    05/11/01 16:50 Tsujimura543
 * (1) �����������t�@�N�^�����O
 * (2) MM/Memo �̍폜�֘A�������쐬
 * 
 * 13    05/10/31 22:11 Tsujimura543
 * BlogPeople Tags �̍폜���T�|�[�g (����m�F�ς�)
 * 
 * 12    05/10/21 18:57 Tsujimura543
 * MM/Memo �� BlogPeople �̃��[�U���A�p�X���[�h�� bookeyView ����
 * �󂯎���悤�ɂ���
 * 
 * 11    05/10/20 23:41 Tsujimura543
 * (1) MM/Memo ����̃u�b�N�}�[�N�̋z�o��(�擾)�ɑΉ�
 * (2) MM/Memo, BlogPeople Tags �ւ̃u�b�N�}�[�N�̓o�^�ɑΉ�
 * 
 * 10    05/10/15 0:41 Tsujimura543
 * �͂ĂȂ�del.icio.us�̃��[�U���A�p�X���[�h�� bookeyView ����󂯎���
 * �悤�ɂ���
 * 
 * 9     05/10/14 14:20 Tsujimura543
 * CAboutDlg ��ʃt�@�C���֕����A�Ɨ�������
 * 
 * 8     05/10/11 19:08 Tsujimura543
 * �u�b�N�}�[�N�����@�\������ (����m�F�ς�)
 * 
 * 7     05/10/11 16:56 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 * 
 * 6     05/10/03 22:59 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N���폜���鏈��������
 * 
 * 5     05/10/03 22:17 Tsujimura543
 * del.icio.us �̃u�b�N�}�[�N���폜���鏈��������
 * 
 * 4     05/10/03 21:02 Tsujimura543
 * �u�b�N�}�[�N�폜�����̎����J�n
 * 
 * 3     05/10/03 12:34 Tsujimura543
 * OPML�t�@�C���̏o�͎��Atitle�v�f����ɂȂ��Ă��܂����Ƃ�����s����C��
 * 
 * 2     05/10/01 0:00 Tsujimura543
 * �u�b�N�}�[�N�̎擾�A�o�^�@�\�̓���m�F����
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "AboutDlg.h"
#include "DeleteBookmarkDialog.h"
#include "DeleteBookmarkDialog3.h"
#include "SynchronizeBookmarkDialog.h"
#include "exportBookmark.h"
#include "DeleteTagsDialog.h"
#include "ReplaceTagsDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookeyDlg.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg �_�C�A���O

CBookeyDlg::CBookeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBookeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBookeyDlg)
	m_bookmark1 = _T("");
	m_bookmark2 = _T("");
	m_password1 = _T("");
	m_password2 = _T("");
	m_username1 = _T("");
	m_username2 = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_needToSave = false;

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
    m_tgt_fc2bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
    m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
    m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_opml.LoadString( IDS_TGT_OPML );
    m_tgt_netscape1.LoadString( IDS_TGT_NETSCAPE_1 );
    m_tgt_opera6.LoadString( IDS_TGT_OPERA_6 );
    m_tgt_hatenaFeed.LoadString( IDS_TGT_HATENA_FEED );
    m_tgt_livedoorFeed.LoadString( IDS_TGT_LIVEDOOR_FEED );
    m_tgt_deliciousXML.LoadString( IDS_TGT_DELICIOUS_XML );
}

void CBookeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookeyDlg)
	DDX_Control(pDX, IDC_COMBO_BOOKMARK2, m_bookmarkList2);
	DDX_Control(pDX, IDC_COMBO_BOOKMARK1, m_bookmarkList1);
	DDX_CBString(pDX, IDC_COMBO_BOOKMARK1, m_bookmark1);
	DDV_MaxChars(pDX, m_bookmark1, 32);
	DDX_CBString(pDX, IDC_COMBO_BOOKMARK2, m_bookmark2);
	DDV_MaxChars(pDX, m_bookmark2, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD1, m_password1);
	DDV_MaxChars(pDX, m_password1, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD2, m_password2);
	DDV_MaxChars(pDX, m_password2, 32);
	DDX_Text(pDX, IDC_EDIT_USERNAME1, m_username1);
	DDV_MaxChars(pDX, m_username1, 32);
	DDX_Text(pDX, IDC_EDIT_USERNAME2, m_username2);
	DDV_MaxChars(pDX, m_username2, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBookeyDlg, CDialog)
	//{{AFX_MSG_MAP(CBookeyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_PUT, OnButtonPut)
	ON_BN_CLICKED(IDC_BUTTON_SYNC, OnButtonSync)
	ON_CBN_SELCHANGE(IDC_COMBO_BOOKMARK1, OnSelchangeComboBookmark1)
	ON_CBN_SELCHANGE(IDC_COMBO_BOOKMARK2, OnSelchangeComboBookmark2)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD1, OnKillfocusEditPassword1)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD2, OnKillfocusEditPassword2)
	ON_EN_KILLFOCUS(IDC_EDIT_USERNAME1, OnKillfocusEditUsername1)
	ON_EN_KILLFOCUS(IDC_EDIT_USERNAME2, OnKillfocusEditUsername2)
	ON_EN_UPDATE(IDC_EDIT_USERNAME1, OnUpdateEditUsername1)
	ON_EN_UPDATE(IDC_EDIT_PASSWORD1, OnUpdateEditPassword1)
	ON_EN_UPDATE(IDC_EDIT_USERNAME2, OnUpdateEditUsername2)
	ON_EN_UPDATE(IDC_EDIT_PASSWORD2, OnUpdateEditPassword2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_TAGS, OnButtonEditTags)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_TAGS, OnButtonDeleteTags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg �ǉ����\�b�h

void    CBookeyDlg::ChangeButtonGet()
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET );

    if ( !m_bookmark1.Compare( m_tgt_opml )                         ||
         !m_bookmark1.Compare( m_tgt_netscape1 )                    ||
         !m_bookmark1.Compare( m_tgt_opera6 )                       ||
         !m_bookmark1.Compare( m_tgt_hatenaFeed )                   ||
         !m_bookmark1.Compare( m_tgt_livedoorFeed )                 ||
         !m_bookmark1.Compare( m_tgt_deliciousXML )                 ||
         ( (m_username1.GetLength() > 0)                       &&
           ( !m_bookmark1.Compare( m_tgt_hatenaBookmark ) ||
             !m_bookmark1.Compare( m_tgt_flog )           ||
             !m_bookmark1.Compare( m_tgt_livedoorClip )   ||
             !m_bookmark1.Compare( m_tgt_ecNaviClip )     ||
             !m_bookmark1.Compare( m_tgt_niftyClip )      ||
             !m_bookmark1.Compare( m_tgt_pookmark )       ||
             !m_bookmark1.Compare( m_tgt_blueDot )        ||
             !m_bookmark1.Compare( m_tgt_joltMark )       ||
             !m_bookmark1.Compare( m_tgt_blogPet )        ||
             !m_bookmark1.Compare( m_tgt_fc2bookmark )    ||
             !m_bookmark1.Compare( m_tgt_yjBookmark )     ||
             !m_bookmark1.Compare( m_tgt_yahooBookmarks ) ||
             !m_bookmark1.Compare( m_tgt_diigo )          ||
             (m_password1.GetLength() > 0)                   )    )    )
        p->EnableWindow( TRUE );
    else
        p->EnableWindow( FALSE );
}

void    CBookeyDlg::ChangeButtonPut()
{
    CButton     *p  = (CButton *)GetDlgItem( IDC_BUTTON_PUT );
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    if ( (pp->m_bookmarkGotten || pp->m_myClip)            &&
         ( !m_bookmark2.Compare( m_tgt_opml )         ||
           !m_bookmark2.Compare( m_tgt_netscape1 )    ||
           !m_bookmark2.Compare( m_tgt_opera6 )       ||
           !m_bookmark2.Compare( m_tgt_deliciousXML ) ||
           ( (m_username2.GetLength() > 0) && 
             (m_password2.GetLength() > 0)    )          )    )
        p->EnableWindow( TRUE );
    else
        p->EnableWindow( FALSE );
}

void    CBookeyDlg::EnableButton( bool enable )
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET );
    if ( enable == false )
        p->EnableWindow( FALSE );
    else
        ChangeButtonGet();

    p = (CButton *)GetDlgItem( IDC_BUTTON_PUT );
    if ( enable == false )
        p->EnableWindow( FALSE );
    else
        ChangeButtonPut();

    p = (CButton *)GetDlgItem( IDC_BUTTON_SYNC );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_EDIT_TAGS );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_TAGS );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDOK );
    p->EnableWindow( enable ? TRUE : FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg ���b�Z�[�W �n���h��

BOOL CBookeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
        pSysMenu->AppendMenu(MF_SEPARATOR);
        CString strAboutMenu0;
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT2);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT2, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY2);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY2, strAboutMenu0);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);     // �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);    // �������A�C�R����ݒ�
	
    ChangeButtonGet();
    ChangeButtonPut();

    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME1 );
    p->EnableWindow( FALSE );
    p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD1 );
    p->EnableWindow( FALSE );
	
    p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME2 );
    p->EnableWindow( FALSE );
    p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD2 );
    p->EnableWindow( FALSE );

    CString str;
    CStatic *s;
    str.LoadString( IDS_BOOKEY_VERSION );
    str = "bookey Ver " + str;
    s = (CStatic *)GetDlgItem( IDC_BOOKEY_VERSION );
    s->SetWindowText( str );

    return TRUE;
}

void CBookeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CString cmd = "";

    switch (nID & 0xFFF0) {
    case IDM_ABOUTBOX:
        switch (nID) {
        case IDM_ABOUTBOX: {
            CAboutDlg dlgAbout;
            dlgAbout.DoModal(); }
            break;

        case IDM_ABOUT_SUPPORT:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_WEB_URL );
            /* fall into ... */
        case IDM_ABOUT_SUPPORT2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_SUPPORT );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_COMMUNITY );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_COMMUNITY2 );
            ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
            break;
        }
        break;

    default:
		CDialog::OnSysCommand(nID, lParam);
        break;
    }
}

void CBookeyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width()  - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CBookeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBookeyDlg::OnButtonGet() 
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    /* �u�b�N�}�[�N�̎擾 */
    if ( !m_bookmark1.Compare( m_tgt_opml )         ||
         !m_bookmark1.Compare( m_tgt_netscape1 )    ||
         !m_bookmark1.Compare( m_tgt_opera6 )       ||
         !m_bookmark1.Compare( m_tgt_hatenaFeed )   ||
         !m_bookmark1.Compare( m_tgt_livedoorFeed ) ||
         !m_bookmark1.Compare( m_tgt_deliciousXML )    ) {
        EnableButton( false );
        bool    ret = pp->GetBookmarks( m_bookmark1 );
        EnableButton( true );

        if ( ret == false )
            return;
    }
    else {
        if ( m_username1.GetLength() == 0 )
            return;
        if ( (m_password1.GetLength() == 0)                 &&
             ( !m_bookmark1.Compare( m_tgt_delicious ) ||
               !m_bookmark1.Compare( m_tgt_mmMemo )    ||
               !m_bookmark1.Compare( m_tgt_drecomRSS )    )    )
            return;
        if ( strchr( m_username1, '@' )                      &&
             (m_password1.GetLength() == 0)                  &&
             ( !m_bookmark1.Compare( m_tgt_flog )       ||
               !m_bookmark1.Compare( m_tgt_ecNaviClip )    )    )
            return;

        EnableButton( false );
        pp->GetBookmarks( m_bookmark1, m_username1, m_password1 );
        EnableButton( true );
    }

    if ( pp->m_myClip )
        ChangeButtonPut();
    else {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS);
        text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS);
        MessageBox( text,   // �u�b�N�}�[�N�����擾�ł��܂���ł���
                    title,  // �u�b�N�}�[�N�擾���s
                    MB_OK|MB_ICONWARNING );
    }
}

void CBookeyDlg::OnButtonPut() 
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    if ( !(pp->m_myClip) )
        return;

    /* �u�b�N�}�[�N�̓o�^ */
    EnableButton( false );
    if ( !m_bookmark2.Compare( m_tgt_opml )         ||
         !m_bookmark2.Compare( m_tgt_netscape1 )    ||
         !m_bookmark2.Compare( m_tgt_opera6 )       ||
      /* !m_bookmark2.Compare( m_tgt_hatenaFeed )   || */
         !m_bookmark2.Compare( m_tgt_deliciousXML )    )
        pp->PutBookmarks( m_bookmark2, m_bookmark1 );
    else
        pp->PutBookmarks( m_bookmark2, m_username2, m_password2 );
    EnableButton( true );
}

void CBookeyDlg::OnButtonSync() 
{
    EnableButton( false );

    SynchronizeBookmarkDialog   dlg;
    int ret = dlg.DoModal();
    if ( ret != IDOK ) {
        EnableButton( true );
        return;
    }

    MyClip      *myBookmark1 = NULL;
    MyClip      *myBookmark2 = NULL;
    int         numOfBookmark1 = 0;
    int         numOfBookmark2 = 0;
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    bool        cont;

    m_needToSave = false;
    if ( ((dlg.m_bookmark1.Compare(m_tgt_1470net) == 0) ||
          (dlg.m_bookmark2.Compare(m_tgt_1470net) == 0)   ) &&
         (pp->m_next1470net.m_username.GetLength() == 0)       )
        m_needToSave = true;

    /* ���[�U���A�p�X���[�h�̎擾 */
    CString txt;
    txt.LoadString( IDS_SYNCHRONIZE );  // ����
    cont = pp->InquiryUserInfo( dlg.m_bookmark1, dlg.m_bookmark2, txt );
    if ( cont == false ) {
        m_needToSave = false;
        EnableButton( true );
        return;
    }

    /* �u�b�N�}�[�N�̑S�擾 */
    cont = pp->ExportFromAnother( dlg.m_bookmark1, dlg.m_bookmark2,
                                  &myBookmark1,    &myBookmark2,
                                  &numOfBookmark1, &numOfBookmark2 );
    if ( cont == false ) {
        m_needToSave = false;
        EnableButton( true );
        return;
    }

    /* �u�b�N�}�[�N�̓o�^ */
    pp->ImportFromAnotherToOne( dlg.m_bookmark1, dlg.m_bookmark2,
                                myBookmark1,     myBookmark2,
                                numOfBookmark1,  numOfBookmark2,
                                dlg.m_direction );

    if ( m_needToSave ) {
        if (((dlg.m_bookmark1.Compare(m_tgt_1470net) == 0) ||
             (dlg.m_bookmark2.Compare(m_tgt_1470net) == 0)   ) &&
            (pp->m_next1470net.m_username.GetLength() == 0)       )
            m_needToSave = false;
    }

    EnableButton( true );
}

void CBookeyDlg::OnButtonDelete() 
{
    EnableButton( false );

	DeleteBookmarkDialog    dlg;
    dlg.DoModal();
    if ( dlg.m_targetBookmark == CUserInfo::BK_UNKNOWN ) {
        EnableButton( true );
        return;
    }

    if ( (dlg.m_deleteAll == false)         && 
         (dlg.m_deleteInteractive == false)    ) {
        EnableButton( true );
        return;
    }

    /* �u�b�N�}�[�N�̍폜 */
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    m_needToSave = false;
    if ( (dlg.m_targetBookmark == CUserInfo::BK_1470NET) &&
         (pp->m_next1470net.m_username.GetLength() == 0)    )
        m_needToSave = true;

    pp->DeleteBookmarks( dlg.m_targetBookmark,
                         dlg.m_deleteAll, dlg.m_deleteInteractive );
    if ( m_needToSave ) {
        if ( (dlg.m_targetBookmark == CUserInfo::BK_1470NET) &&
             (pp->m_next1470net.m_username.GetLength() == 0)    )
            m_needToSave = false;
    }

    EnableButton( true );
}


/* �u�u�b�N�}�[�N�擾�v�� */
void CBookeyDlg::OnSelchangeComboBookmark1() 
{
    CString     bookmarkName;
    int         location = m_bookmarkList1.GetCurSel();

	m_bookmarkList1.GetLBText( location, bookmarkName );
    if ( m_bookmark1.Compare( bookmarkName ) != 0 ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username1 = "";
        m_password1 = "";
        m_bookmark1 = bookmarkName;
        pp->m_bookmarkGotten = false;
        pp->m_bookmarkName   = "";

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME1 );
        CEdit   *q = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD1 );
        p->SetWindowText( m_username1 );
        q->SetWindowText( m_password1 );

        if ( m_bookmark1.GetLength() > 0 ) {
            if ( !m_bookmark1.Compare( m_tgt_hatenaBookmark ) )
                pp->SetWindowText( m_bookmark1, m_username1, p, q );
            else if ( !m_bookmark1.Compare( m_tgt_delicious )      ||
                      !m_bookmark1.Compare( m_tgt_blueDot )        ||
                      !m_bookmark1.Compare( m_tgt_mmMemo )         ||
                      !m_bookmark1.Compare( m_tgt_drecomRSS )      ||
                      !m_bookmark1.Compare( m_tgt_flog )           ||
                      !m_bookmark1.Compare( m_tgt_livedoorClip )   ||
                      !m_bookmark1.Compare( m_tgt_ecNaviClip )     ||
                      !m_bookmark1.Compare( m_tgt_niftyClip )      ||
                      !m_bookmark1.Compare( m_tgt_1470net )        ||
                      !m_bookmark1.Compare( m_tgt_pookmark )       ||
                      !m_bookmark1.Compare( m_tgt_joltMark )       ||
                      !m_bookmark1.Compare( m_tgt_blogPet )        ||
                      !m_bookmark1.Compare( m_tgt_fc2bookmark )    ||
                      !m_bookmark1.Compare( m_tgt_yjBookmark )     ||
                      !m_bookmark1.Compare( m_tgt_yahooBookmarks ) ||
                      !m_bookmark1.Compare( m_tgt_diigo )             )
                pp->SetWindowText( m_bookmark1, m_username1, m_password1,
                                   p, q );
            else if (!m_bookmark1.Compare( m_tgt_opml )         ||
                     !m_bookmark1.Compare( m_tgt_netscape1 )    ||
                     !m_bookmark1.Compare( m_tgt_opera6 )       ||
                     !m_bookmark1.Compare( m_tgt_hatenaFeed )   ||
                     !m_bookmark1.Compare( m_tgt_livedoorFeed ) ||
                     !m_bookmark1.Compare( m_tgt_deliciousXML )    ) {
                p->EnableWindow( FALSE );
                q->EnableWindow( FALSE );
            }
        }

        ChangeButtonGet();
        ChangeButtonPut();
    }
}

void CBookeyDlg::OnKillfocusEditUsername1() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME1 );
    p->GetWindowText( m_username1 );

    ChangeButtonGet();
}

void CBookeyDlg::OnKillfocusEditPassword1() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD1 );
    p->GetWindowText( m_password1 );

    ChangeButtonGet();
}

void CBookeyDlg::OnUpdateEditUsername1() 
{
    OnKillfocusEditUsername1();
}

void CBookeyDlg::OnUpdateEditPassword1() 
{
    OnKillfocusEditPassword1();
}


/* �u�u�b�N�}�[�N�o�^�v�� */
void CBookeyDlg::OnSelchangeComboBookmark2() 
{
    CString     bookmarkName;
    int         location = m_bookmarkList2.GetCurSel();

	m_bookmarkList2.GetLBText( location, bookmarkName );

    if ( m_bookmark2.Compare( bookmarkName ) != 0 ) {
        m_username2 = "";
        m_password2 = "";
        m_bookmark2 = bookmarkName;

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME2 );
        CEdit   *q = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD2 );
        p->SetWindowText( m_username2 );
        q->SetWindowText( m_password2 );

        if ( m_bookmark2.GetLength() > 0 ) {
            CString text;
            CButton *r = (CButton *)GetDlgItem( IDC_BUTTON_PUT );

           if ( !m_bookmark2.Compare( m_tgt_hatenaBookmark ) ||
                !m_bookmark2.Compare( m_tgt_delicious )      ||
                !m_bookmark2.Compare( m_tgt_blueDot )        ||
                !m_bookmark2.Compare( m_tgt_mmMemo )         ||
                !m_bookmark2.Compare( m_tgt_drecomRSS )      ||
                !m_bookmark2.Compare( m_tgt_flog )           ||
                !m_bookmark2.Compare( m_tgt_livedoorClip )   ||
                !m_bookmark2.Compare( m_tgt_ecNaviClip )     ||
                !m_bookmark2.Compare( m_tgt_niftyClip )      ||
                !m_bookmark2.Compare( m_tgt_1470net )        ||
                !m_bookmark2.Compare( m_tgt_pookmark )       ||
                !m_bookmark2.Compare( m_tgt_joltMark )       ||
                !m_bookmark2.Compare( m_tgt_blogPet )        ||
                !m_bookmark2.Compare( m_tgt_fc2bookmark )    ||
                !m_bookmark2.Compare( m_tgt_yjBookmark )     ||
                !m_bookmark2.Compare( m_tgt_yahooBookmarks ) ||
                !m_bookmark2.Compare( m_tgt_diigo )             ) {
                CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
                text.LoadString(IDS_BTN_PUT_BOOKMARKS);
                pp->SetWindowText( m_bookmark2, m_username2, m_password2,
                                   p, q, r,
                                   text );  // �u�b�N�}�[�N�o�^
            }
            else if ( !m_bookmark2.Compare( m_tgt_opml )         ||
                      !m_bookmark2.Compare( m_tgt_netscape1 )    ||
                      !m_bookmark2.Compare( m_tgt_opera6 )       ||
                      !m_bookmark2.Compare( m_tgt_deliciousXML )    ) {
                p->EnableWindow( FALSE );
                q->EnableWindow( FALSE );
                text.LoadString(IDS_BTN_SAVE_BOOKMARKS);
                r->SetWindowText( text );   // �u�b�N�}�[�N�ۑ�
            }
        }

        ChangeButtonPut();
    }
}

void CBookeyDlg::OnKillfocusEditUsername2() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME2 );
    p->GetWindowText( m_username2 );
    
    ChangeButtonPut();
}

void CBookeyDlg::OnKillfocusEditPassword2() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD2 );
    p->GetWindowText( m_password2 );

    ChangeButtonPut();
}

void CBookeyDlg::OnUpdateEditUsername2() 
{
    OnKillfocusEditUsername2();
}

void CBookeyDlg::OnUpdateEditPassword2() 
{
    OnKillfocusEditPassword2();
}

void CBookeyDlg::OnButtonEditTags() 
{
    EnableButton( false );

	CReplaceTagsDialog  dlg;
    dlg.DoModal();

    EnableButton( true );
}

void CBookeyDlg::OnButtonDeleteTags() 
{
    EnableButton( false );

	CDeleteTagsDialog   dlg;
    dlg.DoModal();

    EnableButton( true );
}

/*
 * EditBookmarkDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�ҏW�_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  14 Oct 2005
 *
 * $Log: /comm/bookey/EditBookmarkDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 74    08/11/04 12:48 Tsujimura543
 * @nifty Clip �o�^�Ґ����\������悤�ɂ���
 * 
 * 73    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 72    08/07/25 22:33 Tsujimura543
 * Diigo �Ή� (����m�F�ς�)
 * 
 * 71    07/10/31 17:13 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 70    07/09/05 2:19 Tsujimura543
 * SetUsers() �𓱓����A�\�[�X�𐮗�
 * 
 * 69    07/09/05 2:02 Tsujimura543
 * �u�b�N�}�[�N���������ʂ��ُ�l(����������)�̏ꍇ�ɁA�{�_�C�A���O����
 * �����邱�Ƃ��ł��Ȃ��Ȃ�s��ɑΏ�
 * 
 * 68    07/08/28 23:32 Tsujimura543
 * �������e�ΏۂɂȂ��Ă���u�b�N�}�[�N�̃A�C�R����"���ڂ�"�\������
 * �悤�ɂ��Ă݂�
 * 
 * 67    07/08/27 21:55 Tsujimura543
 * �u�͂ĂȃX�^�[�v�ɑΉ�
 * 
 * 66    07/07/27 1:14 Tsujimura543
 * �uOFF �� �ꎞ�I�� ON�v�؂�ւ��@�\������
 * 
 * 65    07/07/12 11:59 Tsujimura543
 * OnContextMenu() �� digg ���u�ꎞ�I�� off �ɂ���v����uon�v�ɖ߂��Ȃ�
 * �s������錏�ɑΏ�
 * 
 * 64    07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 63    07/07/02 16:44 Tsujimura543
 * Visual Studio 2005 �Ńr���h�����ꍇ�ł��A���Ғʂ�u�w�J�[�\���v��
 * �\�������悤�ɏC��
 * 
 * 62    07/06/29 13:49 Tsujimura543
 * http://1470.net/mm/ �� http://mmmemo.1470.net/mm/ �֕ύX
 * 
 * 61    07/05/23 16:02 Tsujimura543
 * Timelog �Ή�
 * 
 * 60    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 59    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 58    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 57    07/03/30 16:24 Tsujimura543
 * FC2BOOKMARK �ɑΉ�
 * 
 * 56    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 55    07/03/01 21:45 Tsujimura543
 * �R�����g���C��
 * 
 * 54    07/03/01 21:44 Tsujimura543
 * (1) livedoor�N���b�v�ɓo�^���Ă���l�̐���\������悤�ɂ���
 * (2) �j�t�e�B�N���b�v�̃A�C�R�����N���b�N����ƁA�G���g���y�[�W���u���E
 *     �U�ŕ\���ł���悤�ɂ���
 * 
 * 53    07/02/23 2:04 Tsujimura543
 * GetCatNumberOfDrecom(CString&), GetCatNumberOfFlog(CString&) ��
 * �������ׂ��J�e�S���������ł��Ȃ������Ƃ��Ƀ������Q�ƃG���[�ŗ�����
 * �s����C��
 * 
 * 52    07/02/08 21:35 Tsujimura543
 * �u�h���R��RSS��Flog�̃J�e�S�����������v�����s���������ύX
 * 
 * 51    07/02/05 16:17 Tsujimura543
 * �h���R��RSS��Flog�̃J�e�S�������������ďC��
 * 
 * 50    07/02/05 14:52 Tsujimura543
 * �h���R��RSS��Flog�̃J�e�S�������������C��
 * 
 * 49    07/02/02 23:56 Tsujimura543
 * ���C�����̓���m�F����
 * 
 * 48    07/02/02 23:40 Tsujimura543
 * �ēo�^���悤�Ƃ��Ă���ꍇ�̈�A�̏������C���B�h���R��RSS��Flog�̃J�e�S
 * ���������ł���悤�ɂ���
 * 
 * 47    07/02/02 20:59 Tsujimura543
 * ���łɁu�͂Ăȃu�b�N�}�[�N�v�ɓo�^�ς݂̃u�b�N�}�[�N�����߂ēo�^������
 * ���Ƃ��Ă���ꍇ�́A�ȑO�ɓo�^�����R�����g�A�^�O���擾���āA�ҏW������
 * ��悤�ɂ���
 * 
 * 46    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 45    07/01/17 22:26 Tsujimura543
 * �p�ꃂ�[�h�Ή� (�b��)
 * 
 * 44    07/01/16 22:50 Tsujimura543
 * �p�ꃂ�[�h�Ή����� ����3
 * 
 * 43    07/01/16 21:04 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή����� ����2
 * (2) IsInner() ��ǉ����A���t�@�N�^�����O
 * 
 * 42    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 41    07/01/11 17:01 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 40    06/12/27 17:37 Tsujimura543
 * �u�b�N�}�[�N���e�_�C�A���O�ŉE�N���b�N���j���[���g����悤�ɂ���
 * 
 * 39    06/12/25 23:23 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 38    06/12/21 19:11 Tsujimura543
 * JoltMark �Ή�
 * 
 * 37    06/12/07 19:26 Tsujimura543
 * �u���J��ԁv���W�I�{�^���Q�̏�����Ԃ�ύX
 * 
 * 36    06/12/06 18:59 Tsujimura543
 * �u���J��ԁv�̐ݒ�ɑΉ�
 * 
 * 35    06/10/18 19:40 Tsujimura543
 * �u�b�N�}�[�N�擾�����Ńo�b�t�@�I�[�o�[��������������\�������邱�Ƃ�
 * ���������̂ŁA�΍�����{
 * 
 * 34    06/10/07 9:17 Tsujimura543
 * Blue Dot �ɑΉ�����
 * 
 * 33    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline �ɑΉ�
 * 
 * 32    06/10/03 23:06 Tsujimura543
 * �Ԃ�~�X���C�� (catoon �� cartoon) [facet����A�w�E����!]
 * 
 * 31    06/09/30 0:55 Tsujimura543
 * ���~�{�^���������̓�����C�� (�L�����Z���\�ɂ���)
 * 
 * 30    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 29    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 28    06/07/27 23:55 Tsujimura543
 * newsing �Ή�����
 * 
 * 27    06/07/14 20:50 Tsujimura543
 * 1470.net���j���[�A���łɑΉ�
 * 
 * 26    06/07/11 22:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�̃u�b�N�}�[�N�o�^�Ґ����\������悤�ɂ���
 * (�u�b�N�}�[�N�o�^���/EditBookmarkDialog)
 * 
 * 25    06/06/30 11:37 Tsujimura543
 * livedoor�N���b�v�AEC�i�r�l�C�j���[�X�̃A�C�R�����N���b�N�����Ƃ����A
 * �e�u�b�N�}�[�N�̃G���g���y�[�W��(�u���E�U�o�R��)�\������悤�ɂ���
 * 
 * 24    06/06/29 18:47 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 23    06/06/29 10:47 Tsujimura543
 * �u�o�^�v�{�^�������������ł��Am_tags �̒��ɘA������󔒕�����1��
 * �󔒕����ɐ������鏈�������s����悤�ɂ���
 * 
 * 22    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 21    06/06/28 15:54 Tsujimura543
 * �u�b�N�}�[�N�o�^�Ґ��𒲂ׂĕ\������@�\��ǉ�
 * 
 * 20    06/06/26 16:27 Tsujimura543
 * OnSetCursor() ��ǉ� (�w�J�[�\���\���@�\)
 * 
 * 19    06/06/20 16:25 Tsujimura543
 * iskanji1(), iskanji2() �� myClip.h �ֈړ�
 * 
 * 18    06/06/19 13:42 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�Adel.icio.us�AMM/Memo �̃A�C�R�����N���b�N�����Ƃ��A
 * �e�u�b�N�}�[�N�̃G���g���y�[�W��(�u���E�U�o�R��)�\������悤�ɂ���
 * 
 * 17    06/06/06 22:23 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��
 * 
 * 16    06/06/06 15:17 Tsujimura543
 * �ǂ̃\�[�V�����u�b�N�}�[�N�ւ̓o�^���L��(�������͖���)�ɂȂ��Ă���̂�
 * �A�C�R���ƃc�[���`�b�v���g���ĕ\������悤�ɂ���
 * 
 * 15    06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 14    06/05/23 12:30 Tsujimura543
 * �R�����g���C��
 * 
 * 13    06/05/23 11:41 Tsujimura543
 * m_category �̍ő�o�C�g���� 16 ���� 18 �ɕύX
 * (�u�G���^�[�e�C�����g�v��I������Ɓu16�����ȉ��ɂ��Ă��������v
 *  �_�C�A���O���o�Ă��܂��Ƃ����s���������)
 * 
 * 12    06/04/06 22:16 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�́u�R���N�V�����v�ւ̒ǉ��ɑΉ�
 * 
 * 11    06/03/29 21:23 Tsujimura543
 * �h���R��RSS�́u�t�H���_�v(�J�e�S��)���w��ł���悤�ɂ���
 * 
 * 10    06/03/27 17:14 Tsujimura543
 * OnUpdateEditBmComment() �������S�Ă� OnUpdateEditBmXXX() ��p�~
 * 
 * 9     06/03/24 18:02 Tsujimura543
 * ���łɃu�b�N�}�[�N�ς݂� item ���ēx�u�b�N�}�[�N���悤�Ƃ����Ƃ�
 * �Ƀu�b�N�}�[�N�̕ҏW���[�h�ɓ��邱�Ƃ��ł���悤�ɂ��邽�߂̏���
 * �����{
 * 
 * 8     06/03/24 15:48 Tsujimura543
 * OnUpdateEditBmUrl() ���폜 [�����ɍċA����������s���������]
 * 
 * 7     05/12/01 15:44 Tsujimura543
 * �ȉ��̑Ώ������{����
 * (1) �^�O�w�藓�ɋ󔒕�����2�ȏ�A�����đ��݂���ꍇ��1�ɂ܂Ƃ߂�
 * (2) �^�O�w�藓�̃t�H�[�J�X���\�������s���ɔ��ł��܂��̂�h�~����
 * 
 * 6     05/12/01 0:02 Tsujimura543
 * �^�O���\���E���͋@�\������
 * 
 * 5     05/11/30 14:33 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̃^�O��3�܂Ł�10�܂ŁA�R�����g��50�����܂Ł�
 * 100�����܂łɊe�X�ύX���ꂽ�̂ɔ����C�������{
 * 
 * 4     05/10/24 17:37 Tsujimura543
 * �͂Ăȓ����K�ɑΉ�����
 * 
 * 3     05/10/14 20:38 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�Ή���Ɗ���
 * 
 * 2     05/10/14 17:02 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O������
 */

#include "bookey.h"
#include "EditBookmarkDialog.h"
extern "C" {
#include "twitStar.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/EditBookmarkDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// EditBookmarkDialog �_�C�A���O

EditBookmarkDialog::EditBookmarkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(EditBookmarkDialog::IDD, pParent)
{
    m_enableTipJar = false;
    m_useCategory  = false;
    m_enableCollection   = false;
    m_registerCollection = false;
	//{{AFX_DATA_INIT(EditBookmarkDialog)
	m_counterString = _T("");
	m_comment = _T("");
	m_tags = _T("");
	m_title = _T("");
	m_url = _T("");
	m_sendTipJar = FALSE;
	m_tag001 = _T("");
	m_tag002 = _T("");
	m_tag003 = _T("");
	m_tag004 = _T("");
	m_tag005 = _T("");
	m_tag006 = _T("");
	m_tag007 = _T("");
	m_tag008 = _T("");
	m_tag009 = _T("");
	m_tag010 = _T("");
	m_tag011 = _T("");
	m_tag012 = _T("");
	m_tag013 = _T("");
	m_tag014 = _T("");
	m_tag015 = _T("");
	m_tag016 = _T("");
	m_tag017 = _T("");
	m_tag018 = _T("");
	m_tag019 = _T("");
	m_tag020 = _T("");
	m_category = _T("");
	m_category2 = _T("");
	m_hbUsers = _T("");
	m_deliciousUsers = _T("");
	m_mmUsers = _T("");
	m_ecNaviUsers = _T("");
	m_livedoorClipUsers = _T("");
	m_diggUsers = _T("");
	m_hatenaStarUsers = _T("");
	m_niftyClipUsers = _T("");
	//}}AFX_DATA_INIT

    m_tag[0]  = &m_tag001;
    m_tag[1]  = &m_tag002;
    m_tag[2]  = &m_tag003;
    m_tag[3]  = &m_tag004;
    m_tag[4]  = &m_tag005;
    m_tag[5]  = &m_tag006;
    m_tag[6]  = &m_tag007;
    m_tag[7]  = &m_tag008;
    m_tag[8]  = &m_tag009;
    m_tag[9]  = &m_tag010;
    m_tag[10] = &m_tag011;
    m_tag[11] = &m_tag012;
    m_tag[12] = &m_tag013;
    m_tag[13] = &m_tag014;
    m_tag[14] = &m_tag015;
    m_tag[15] = &m_tag016;
    m_tag[16] = &m_tag017;
    m_tag[17] = &m_tag018;
    m_tag[18] = &m_tag019;
    m_tag[19] = &m_tag020;

    m_evaluation  = EVL_NONE;
    m_rating      = RAT_NONE;
    m_affirmation = AFF_NONE;

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );

    m_tgt_hatenaBookmark.LoadString( IDS_TGT_HATENA_BOOKMARK );
    m_tgt_delicious.LoadString( IDS_TGT_DELICIOUS );
    m_tgt_mmMemo.LoadString( IDS_TGT_MMMEMO );
    m_tgt_drecomRSS.LoadString( IDS_TGT_DRECOM_RSS );
    m_tgt_flog.LoadString( IDS_TGT_FLOG );
    m_tgt_livedoorClip.LoadString( IDS_TGT_LIVEDOOR_CLIP );
    m_tgt_ecNaviClip.LoadString( IDS_TGT_ECNAVI_CLIP );
    m_tgt_niftyClip.LoadString( IDS_TGT_NIFTY_CLIP );
    m_tgt_1470net.LoadString( IDS_TGT_1470NET );
    m_tgt_newsing.LoadString( IDS_TGT_NEWSING );
    m_tgt_pookmark.LoadString( IDS_TGT_POOKMARK );
    m_tgt_blueDot.LoadString( IDS_TGT_BLUEDOT );
    m_tgt_joltMark.LoadString( IDS_TGT_JOLTMARK );
    m_tgt_blogPet.LoadString( IDS_TGT_BLOGPET );
    m_tgt_fc2bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
    m_tgt_twitter.LoadString( IDS_TGT_TWITTER );
    m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
    m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
    m_tgt_timelog.LoadString( IDS_TGT_TIMELOG );
    m_tgt_digg.LoadString( IDS_TGT_DIGG );
    m_tgt_tumblr.LoadString( IDS_TGT_TUMBLR );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_hatenaStar.LoadString( IDS_TGT_HATENA_STAR );
}

void EditBookmarkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditBookmarkDialog)
	DDX_Control(pDX, IDC_COMBO_CATEGORY2, m_categoryList2);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_categoryList);
	DDX_Text(pDX, IDC_COUNTER, m_counterString);
	DDV_MaxChars(pDX, m_counterString, 12);
	DDX_Text(pDX, IDC_EDIT_BM_COMMENT, m_comment);
	DDV_MaxChars(pDX, m_comment, 512);
	DDX_Text(pDX, IDC_EDIT_BM_TAGS, m_tags);
	DDV_MaxChars(pDX, m_tags, 256);
	DDX_Text(pDX, IDC_EDIT_BM_TITLE, m_title);
	DDV_MaxChars(pDX, m_title, 512);
	DDX_Text(pDX, IDC_EDIT_BM_URL, m_url);
	DDV_MaxChars(pDX, m_url, 384);
	DDX_Check(pDX, IDC_CHECK_TIPJAR, m_sendTipJar);
	DDX_Text(pDX, IDC_TAG001, m_tag001);
	DDV_MaxChars(pDX, m_tag001, 20);
	DDX_Text(pDX, IDC_TAG002, m_tag002);
	DDV_MaxChars(pDX, m_tag002, 20);
	DDX_Text(pDX, IDC_TAG003, m_tag003);
	DDV_MaxChars(pDX, m_tag003, 20);
	DDX_Text(pDX, IDC_TAG004, m_tag004);
	DDV_MaxChars(pDX, m_tag004, 20);
	DDX_Text(pDX, IDC_TAG005, m_tag005);
	DDV_MaxChars(pDX, m_tag005, 20);
	DDX_Text(pDX, IDC_TAG006, m_tag006);
	DDV_MaxChars(pDX, m_tag006, 20);
	DDX_Text(pDX, IDC_TAG007, m_tag007);
	DDV_MaxChars(pDX, m_tag007, 20);
	DDX_Text(pDX, IDC_TAG008, m_tag008);
	DDV_MaxChars(pDX, m_tag008, 20);
	DDX_Text(pDX, IDC_TAG009, m_tag009);
	DDV_MaxChars(pDX, m_tag009, 20);
	DDX_Text(pDX, IDC_TAG010, m_tag010);
	DDV_MaxChars(pDX, m_tag010, 20);
	DDX_Text(pDX, IDC_TAG011, m_tag011);
	DDV_MaxChars(pDX, m_tag011, 20);
	DDX_Text(pDX, IDC_TAG012, m_tag012);
	DDV_MaxChars(pDX, m_tag012, 20);
	DDX_Text(pDX, IDC_TAG013, m_tag013);
	DDV_MaxChars(pDX, m_tag013, 20);
	DDX_Text(pDX, IDC_TAG014, m_tag014);
	DDV_MaxChars(pDX, m_tag014, 20);
	DDX_Text(pDX, IDC_TAG015, m_tag015);
	DDV_MaxChars(pDX, m_tag015, 20);
	DDX_Text(pDX, IDC_TAG016, m_tag016);
	DDV_MaxChars(pDX, m_tag016, 20);
	DDX_Text(pDX, IDC_TAG017, m_tag017);
	DDV_MaxChars(pDX, m_tag017, 20);
	DDX_Text(pDX, IDC_TAG018, m_tag018);
	DDV_MaxChars(pDX, m_tag018, 20);
	DDX_Text(pDX, IDC_TAG019, m_tag019);
	DDV_MaxChars(pDX, m_tag019, 20);
	DDX_Text(pDX, IDC_TAG020, m_tag020);
	DDV_MaxChars(pDX, m_tag020, 20);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_category);
	DDV_MaxChars(pDX, m_category, 24);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY2, m_category2);
	DDV_MaxChars(pDX, m_category2, 36);
	DDX_Text(pDX, IDC_HB_USERS, m_hbUsers);
	DDV_MaxChars(pDX, m_hbUsers, 8);
	DDX_Text(pDX, IDC_DELICIOUS_USERS, m_deliciousUsers);
	DDV_MaxChars(pDX, m_deliciousUsers, 8);
	DDX_Text(pDX, IDC_MM_USERS, m_mmUsers);
	DDV_MaxChars(pDX, m_mmUsers, 8);
	DDX_Text(pDX, IDC_ECNAVI_USERS, m_ecNaviUsers);
	DDV_MaxChars(pDX, m_ecNaviUsers, 8);
	DDX_Text(pDX, IDC_LIVEDOORCLIP_USERS, m_livedoorClipUsers);
	DDV_MaxChars(pDX, m_livedoorClipUsers, 8);
	DDX_Text(pDX, IDC_DIGG_USERS, m_diggUsers);
	DDV_MaxChars(pDX, m_diggUsers, 8);
	DDX_Text(pDX, IDC_HATENA_STAR_USERS, m_hatenaStarUsers);
	DDV_MaxChars(pDX, m_hatenaStarUsers, 10);
	DDX_Text(pDX, IDC_NIFTYCLIP_USERS, m_niftyClipUsers);
	DDV_MaxChars(pDX, m_niftyClipUsers, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditBookmarkDialog, CDialog)
	//{{AFX_MSG_MAP(EditBookmarkDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_BM_URL, OnKillfocusEditBmUrl)
	ON_EN_KILLFOCUS(IDC_EDIT_BM_TITLE, OnKillfocusEditBmTitle)
	ON_EN_KILLFOCUS(IDC_EDIT_BM_COMMENT, OnKillfocusEditBmComment)
	ON_EN_KILLFOCUS(IDC_EDIT_BM_TAGS, OnKillfocusEditBmTags)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK_TIPJAR, OnCheckTipjar)
	ON_BN_CLICKED(IDC_TAG001, OnTag001)
	ON_BN_CLICKED(IDC_TAG002, OnTag002)
	ON_BN_CLICKED(IDC_TAG003, OnTag003)
	ON_BN_CLICKED(IDC_TAG004, OnTag004)
	ON_BN_CLICKED(IDC_TAG005, OnTag005)
	ON_BN_CLICKED(IDC_TAG006, OnTag006)
	ON_BN_CLICKED(IDC_TAG007, OnTag007)
	ON_BN_CLICKED(IDC_TAG008, OnTag008)
	ON_BN_CLICKED(IDC_TAG009, OnTag009)
	ON_BN_CLICKED(IDC_TAG010, OnTag010)
	ON_BN_CLICKED(IDC_TAG011, OnTag011)
	ON_BN_CLICKED(IDC_TAG012, OnTag012)
	ON_BN_CLICKED(IDC_TAG013, OnTag013)
	ON_BN_CLICKED(IDC_TAG014, OnTag014)
	ON_BN_CLICKED(IDC_TAG015, OnTag015)
	ON_BN_CLICKED(IDC_TAG016, OnTag016)
	ON_BN_CLICKED(IDC_TAG017, OnTag017)
	ON_BN_CLICKED(IDC_TAG018, OnTag018)
	ON_BN_CLICKED(IDC_TAG019, OnTag019)
	ON_BN_CLICKED(IDC_TAG020, OnTag020)
	ON_EN_UPDATE(IDC_EDIT_BM_COMMENT, OnUpdateEditBmComment)
	ON_CBN_SELCHANGE(IDC_COMBO_CATEGORY, OnSelchangeComboCategory)
	ON_CBN_SELCHANGE(IDC_COMBO_CATEGORY2, OnSelchangeComboCategory2)
    ON_NOTIFY(TTN_NEEDTEXT, 0, OnDisplayToolTip)
	ON_BN_CLICKED(IDC_ICON_HATENA_BOOKMARK, OnIconHatenaBookmark)
	ON_BN_CLICKED(IDC_ICON_DELICIOUS, OnIconDelicious)
	ON_BN_CLICKED(IDC_ICON_MM_MEMO, OnIconMmMemo)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_HB_USERS, OnHbUsers)
	ON_BN_CLICKED(IDC_DELICIOUS_USERS, OnDeliciousUsers)
	ON_BN_CLICKED(IDC_MM_USERS, OnMmUsers)
	ON_BN_CLICKED(IDC_ICON_LIVEDOOR, OnIconLivedoor)
	ON_BN_CLICKED(IDC_ICON_ECNAVI_CLIP, OnIconEcnaviClip)
	ON_BN_CLICKED(IDC_ECNAVI_USERS, OnEcnaviUsers)
	ON_BN_CLICKED(IDC_ICON_1470NET, OnIcon1470net)
	ON_BN_CLICKED(IDC_NEWS_GOOD, OnNewsGood)
	ON_BN_CLICKED(IDC_NEWS_BAD, OnNewsBad)
	ON_BN_CLICKED(IDC_RADIO_EVAL00, OnRadioEval00)
	ON_BN_CLICKED(IDC_RADIO_EVAL01, OnRadioEval01)
	ON_BN_CLICKED(IDC_RADIO_EVAL02, OnRadioEval02)
	ON_BN_CLICKED(IDC_RADIO_EVAL03, OnRadioEval03)
	ON_BN_CLICKED(IDC_RADIO_EVAL04, OnRadioEval04)
	ON_BN_CLICKED(IDC_RADIO_EVAL05, OnRadioEval05)
	ON_BN_CLICKED(IDC_ICON_NEWSING, OnIconNewsing)
	ON_BN_CLICKED(IDC_RADIO_PUBLIC, OnRadioPublic)
	ON_BN_CLICKED(IDC_RADIO_FRIENDS, OnRadioFriends)
	ON_BN_CLICKED(IDC_RADIO_PRIVATE, OnRadioPrivate)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_ICON_NIFTY_CLIP, OnIconNiftyClip)
	ON_BN_CLICKED(IDC_LIVEDOORCLIP_USERS, OnLivedoorclipUsers)
	ON_BN_CLICKED(IDC_ICON_DIGG, OnIconDigg)
	ON_BN_CLICKED(IDC_DIGG_USERS, OnDiggUsers)
	ON_BN_CLICKED(IDC_ICON_HATENA_STAR, OnIconHatenaStar)
	ON_BN_CLICKED(IDC_HATENA_STAR_USERS, OnHatenaStarUsers)
	ON_BN_CLICKED(IDC_NIFTYCLIP_USERS, OnNiftyclipUsers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditBookmarkDialog �ǉ����\�b�h

void    EditBookmarkDialog::RedrawCounter( const char *comment )
{
    int         count = 0;
    char        counter[16];
    const char  *p = comment;
    bool        kanjiFlag = false;
    bool        continous = false;

    while ( *p ) {
        if ( (kanjiFlag == false) && iskanji1( *p ) ) {
            continous = false;
            kanjiFlag = true;
            p++;
            continue;
        }
        else if ( kanjiFlag == true ) {
            continous = false;
            kanjiFlag = false;
        }
        else {
            if ( continous == true ) {
                continous = false;
                p++;
                continue;
            }
            continous = true;
        }

        count++;
        p++;
    }

    sprintf( counter, "%d/100", count );
    m_counterString = counter;

    CStatic *q = (CStatic *)GetDlgItem( IDC_COUNTER );
    q->SetWindowText( m_counterString );
}

void    EditBookmarkDialog::SetTag( int tagID )
{
    int     index = tagID - IDC_TAG001;
    CStatic *p = (CStatic *)GetDlgItem( tagID );
    p->GetWindowText( *(m_tag[index]) );

    if ( (*(m_tag[index])).GetLength() > 0 ) {
        CEdit   *q = (CEdit *)GetDlgItem( IDC_EDIT_BM_TAGS );
        q->GetWindowText( m_tags );
        if ( m_tags.GetLength() > 0 ) {
            m_tags.TrimRight();
            m_tags += " ";
            m_tags += *(m_tag[index]);
        }
        else {
            m_tags = *(m_tag[index]);
        }
        q->SetWindowText( m_tags );
        q->SetSel( 0, -1 );
        q->SetSel( -1, -1 );
    }
}

void    EditBookmarkDialog::DisplayToolTip(
            bool        isTarget,
            BOOL        onOff,
            TOOLTIPTEXT *tp )
{
    strcat( tp->szText, ": " );
    if ( isTarget ) {
        if ( onOff )
            strcat( tp->szText, "ON" );
        else {
            CString text;
            text.LoadString(IDS_TXT_TEMPORARY_OFF);
            strcat( tp->szText, text ); // �ꎞ�I�� OFF
        }
    }
    else {
        if ( onOff ) {
            CString text;
            text.LoadString(IDS_TXT_TEMPORARY_ON);
            strcat( tp->szText, text ); // �ꎞ�I�� ON
        }
        else
            strcat( tp->szText, "OFF" );
    }
}

bool    EditBookmarkDialog::IsInner( int id, WORD wX, WORD wY )
{
    CRect   rcClient;
    CStatic *s = (CStatic *)GetDlgItem( id );
    bool    ret = false;

    s->GetWindowRect( &rcClient );
    if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
         (wY >= rcClient.top)  && (wY <= rcClient.bottom)    )
        ret = true;

    return ( ret );
}


int
EditBookmarkDialog::GetCatNumberOfDrecom( const char *tag )
{
    int     folderNumber = -1;

    if ( !strcmp( tag, "Internet" ) )
        folderNumber = 1;
    else if ( !strcmp( tag, "entertainment" ) )
        folderNumber = 2;
    else if ( !strcmp( tag, "science" ) )
        folderNumber = 3;
    else if ( !strcmp( tag, "region" ) )
        folderNumber = 4;
    else if ( !strcmp( tag, "social" ) )
        folderNumber = 5;
    else if ( !strcmp( tag, "column" ) )
        folderNumber = 6;
    else if ( !strcmp( tag, "news-of-death" ) )
        folderNumber = 7;
    else if ( !strcmp( tag, "culture" ) )
        folderNumber = 8;
    else if ( !strcmp( tag, "blog" ) )
        folderNumber = 9;
    else if ( !strcmp( tag, "economy" ) )
        folderNumber = 10;
    else if ( !strcmp( tag, "politics" ) )
        folderNumber = 11;
    else if ( !strcmp( tag, "sport" ) )
        folderNumber = 12;
    else if ( !strcmp( tag, "book-review" ) )
        folderNumber = 13;
    else if ( !strcmp( tag, "international" ) )
        folderNumber = 14;
    else if ( !strcmp( tag, "technology" ) )
        folderNumber = 15;

    return ( folderNumber );
}

int
EditBookmarkDialog::GetCatNumberOfDrecom( CString& tags )
{
    int     folderNumber = -1;
    int     len = tags.GetLength();

    if ( len == 0 )
        return ( folderNumber );

    char    *temp = new char[len + 2];
    char    *p, *q;

    len = 0;
    strcpy( temp, (const char*)tags );
    len = strlen( temp );
    p   = temp;
    q   = temp + (len - 1);
    while ( *p ) {
        q = strchr( p, ' ' );
        if ( q )
            *q = NUL;
        folderNumber = GetCatNumberOfDrecom( p );
        if ( folderNumber >= 0 )
            break;
        if ( !q || (q >= p + len) )
            break;
        p = q + 1;
    }

    if ( folderNumber >= 0 ) {
        ASSERT( p && *p );
        strcpy( temp, (const char*)tags );
        strcpy( p, q ? q + 1 : p + strlen(p) );
        tags = temp;
    }

    delete [] temp;

    return ( folderNumber );
}


int
EditBookmarkDialog::GetCatNumberOfFlog( const char *tag )
{
    int     cataegoryNumber = -1;

    if ( !strcmp( tag, "computer" ) )
        cataegoryNumber = 1;
    else if ( !strcmp( tag, "business" ) )
        cataegoryNumber = 2;
    else if ( !strcmp( tag, "news" ) )
        cataegoryNumber = 3;
    else if ( !strcmp( tag, "diary" ) )
        cataegoryNumber = 4;
    else if ( !strcmp( tag, "showbiz" ) )
        cataegoryNumber = 5;
    else if ( !strcmp( tag, "health" ) )
        cataegoryNumber = 6;
    else if ( !strcmp( tag, "employment" ) )
        cataegoryNumber = 7;
    else if ( !strcmp( tag, "gourmet" ) )
        cataegoryNumber = 8;
    else if ( !strcmp( tag, "music" ) )
        cataegoryNumber = 9;
    else if ( !strcmp( tag, "cinema" ) )
        cataegoryNumber = 10;
    else if ( !strcmp( tag, "print" ) )
        cataegoryNumber = 11;
    else if ( !strcmp( tag, "catoon" ) ||
              !strcmp( tag, "cartoon")    )
        cataegoryNumber = 12;
    else if ( !strcmp( tag, "tv" ) ) 
        cataegoryNumber = 13;
    else if ( !strcmp( tag, "game" ) )
        cataegoryNumber = 14;
    else if ( !strcmp( tag, "animal" ) )
        cataegoryNumber = 15;
    else if ( !strcmp( tag, "hobby" ) )
        cataegoryNumber = 16;
    else if ( !strcmp( tag, "car" ) )
        cataegoryNumber = 17;
    else if ( !strcmp( tag, "life" ) )
        cataegoryNumber = 18;
    else if ( !strcmp( tag, "travel" ) )
        cataegoryNumber = 19;
    else if ( !strcmp( tag, "art" ) )
        cataegoryNumber = 20;
    else if ( !strcmp( tag, "education" ) )
        cataegoryNumber = 21;
    else if ( !strcmp( tag, "movie" ) )
        cataegoryNumber = 22;
    else if ( !strcmp( tag, "tool" ) )
        cataegoryNumber = 23;
    else if ( !strcmp( tag, "summarySite" ) )
        cataegoryNumber = 24;
    else if ( !strcmp( tag, "neta" ) )
        cataegoryNumber = 25;
    else if ( !strcmp( tag, "love" ) )
        cataegoryNumber = 26;
    else if ( !strcmp( tag, "fashion" ) )
        cataegoryNumber = 27;
    else if ( !strcmp( tag, "overseas") ||
              !strcmp( tag, "oversea" )    )
        cataegoryNumber = 28;

    return ( cataegoryNumber );
}

int
EditBookmarkDialog::GetCatNumberOfFlog( CString& tags )
{
    int     cataegoryNumber = -1;
    int     len = tags.GetLength();

    if ( len == 0 )
        return ( cataegoryNumber );

    char    *temp = new char[len + 2];
    char    *p, *q;

    len = 0;
    strcpy( temp, (const char*)tags );
    len = strlen( temp );
    p   = temp;
    q   = temp + (len - 1);
    while ( *p ) {
        q = strchr( p, ' ' );
        if ( q )
            *q = NUL;
        cataegoryNumber = GetCatNumberOfFlog( p );
        if ( cataegoryNumber >= 0 )
            break;
        if ( !q || (q >= p + len) )
            break;
        p = q + 1;
    }

    if ( cataegoryNumber >= 0 ) {
        ASSERT( p && *p );
        strcpy( temp, (const char*)tags );
        strcpy( p, q ? q + 1 : p + strlen(p) );
        tags = temp;
    }

    delete [] temp;

    return ( cataegoryNumber );
}

void EditBookmarkDialog::SetStaticEdge( int idx, BOOL status )
{
    CStatic *sp = (CStatic *)GetDlgItem( idx );

    if ( status ) {
        // "���ڂ�"��Ԃɂ���
        sp->ModifyStyleEx( 0, WS_EX_STATICEDGE, SWP_DRAWFRAME );
    }
    else {
        // "���ڂ�"��Ԃ���������
        sp->ModifyStyleEx( WS_EX_STATICEDGE, 0, SWP_DRAWFRAME );

        // "���ڂ�"��� �� ���ڂ�łȂ���Ԃ̕ω���A�A�C�R���̉����̕\����
        // �����̂ŁA�ĕ`�悵�Ă���
        sp->RedrawWindow();
    }
}

void EditBookmarkDialog::SetUsers(
            CString &users,
            int     idx,
            long    maxLength /* = 8 */ )
{
    CStatic *s = (CStatic *)GetDlgItem( idx );

    if ( (users == "") || (users.GetLength() >= maxLength) )
        users = _T("(?)");
    s->SetWindowText( users );
}

/////////////////////////////////////////////////////////////////////////////
// EditBookmarkDialog ���b�Z�[�W �n���h��

void EditBookmarkDialog::OnKillfocusEditBmUrl() 
{
    CString newUrl;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BM_URL );
    p->GetWindowText( newUrl );
    if ( (newUrl.GetLength() > 0) && (newUrl.Compare( m_url ) != 0) )
        m_url = newUrl;
    p->SetWindowText( m_url );
}

void EditBookmarkDialog::OnKillfocusEditBmTitle() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BM_TITLE );
    p->GetWindowText( m_title );
}

void EditBookmarkDialog::OnKillfocusEditBmComment() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BM_COMMENT );
    p->GetWindowText( m_comment );
    RedrawCounter( m_comment );
}

void EditBookmarkDialog::OnUpdateEditBmComment() 
{
    OnKillfocusEditBmComment();
}

void EditBookmarkDialog::OnKillfocusEditBmTags() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BM_TAGS );
    p->GetWindowText( m_tags );

    bool        changed = false;
    const char  *s;
    if ( ( s = strstr( m_tags, "  " ) ) != NULL ) {
        char    temp[MAX_DESCRIPTION_LEN];
        strcpy( temp, m_tags );
        while ( ( s = strstr( temp, "  " ) ) != NULL )
            strcpy( (char *)s, s + 1 );
        m_tags  = temp;
        changed = true;
    }

    if ( changed ) {
        p->SetWindowText( m_tags );
        p->SetSel(  0, -1 );
        p->SetSel( -1, -1 );
    }
}

void EditBookmarkDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CEdit   *p;
        CStatic *s;

        if ( m_title.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_BM_TITLE );
            p->SetWindowText( m_title );
        }

        if ( m_comment.GetLength() > 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_BM_COMMENT );
            p->SetWindowText( m_comment );
        }

        if ( m_tags.GetLength() > 0 ) {
            if ( m_useCategory ) {
                int catNumber = GetCatNumberOfDrecom( m_tags );
                if ( catNumber > 0 )
                    m_categoryList.SetCurSel( catNumber - 1 );

                catNumber = GetCatNumberOfFlog( m_tags );
                if ( catNumber > 0 )
                    m_categoryList2.SetCurSel( catNumber - 1 );
            }

            p = (CEdit *)GetDlgItem( IDC_EDIT_BM_TAGS );
            p->SetWindowText( m_tags );
        }

        for ( int i = 0; i < 20; i++ ) {
            s = (CStatic *)GetDlgItem( IDC_TAG001 + i );
            s->SetWindowText( *(m_tag[i]) );
        }

        CButton *q;
        q = (CButton *)GetDlgItem( IDC_CHECK_TIPJAR );
        q->EnableWindow( (m_enableTipJar || m_enableCollection)
                                                    ? TRUE : FALSE );
        if ( m_enableTipJar == false ) {
            if ( m_enableCollection ) {
                CString text;
                text.LoadString(IDS_TXT_ADD_COLLECTON);
                q->SetWindowText( text );   // ���̏��i���R���N�V�����ɉ�����
                q->SetCheck( TRUE );
                m_registerCollection = true;
            }
            else
                q->ShowWindow( SW_HIDE );
        }

        CComboBox   *r;
        r = (CComboBox *)GetDlgItem( IDC_COMBO_CATEGORY );
        r->EnableWindow( m_useCategory ? TRUE : FALSE );
        if ( m_useCategory == false ) {
            r->ShowWindow( SW_HIDE );

            s = (CStatic *)GetDlgItem( IDC_STATIC_DRECOM );
            s->ShowWindow( SW_HIDE );
        }

        r = (CComboBox *)GetDlgItem( IDC_COMBO_CATEGORY2 );
        r->EnableWindow( m_useCategory ? TRUE : FALSE );
        if ( m_useCategory == false ) {
            r->ShowWindow( SW_HIDE );

            s = (CStatic *)GetDlgItem( IDC_STATIC_FLOG );
            s->ShowWindow( SW_HIDE );
        }

        q = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
        q->EnableWindow( m_evaluation == EVL_REQUESTED ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_EVAL01 );
        q->EnableWindow( m_evaluation == EVL_REQUESTED ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_EVAL02 );
        q->EnableWindow( m_evaluation == EVL_REQUESTED ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_EVAL03 );
        q->EnableWindow( m_evaluation == EVL_REQUESTED ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_EVAL04 );
        q->EnableWindow( m_evaluation == EVL_REQUESTED ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_EVAL05 );
        q->EnableWindow( m_evaluation == EVL_REQUESTED ? TRUE : FALSE );

        if ( m_evaluation == EVL_REQUESTED ) {
            q = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
            q->SetCheck( 0 );
            m_evaluation = EVL_NONE;
        }

        q = (CButton *)GetDlgItem( IDC_NEWS_GOOD );
        q->EnableWindow( m_affirmation == AFF_REQUESTED ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_NEWS_BAD );
        q->EnableWindow( m_affirmation == AFF_REQUESTED ? TRUE : FALSE );

        q = (CButton *)GetDlgItem( IDC_RADIO_FRIENDS );
        q->EnableWindow( m_public == PUB_REQUESTED2 ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_PRIVATE );
        q->EnableWindow( (m_public == PUB_REQUESTED)  ||
                         (m_public == PUB_REQUESTED2)    ? TRUE : FALSE );
        q = (CButton *)GetDlgItem( IDC_RADIO_PUBLIC );
        q->SetCheck( 1 );
        q->EnableWindow( TRUE );
        m_public = PUB_EVERYONE;

        SetStaticEdge( IDC_ICON_HATENA_BOOKMARK, m_param.hatena.isTarget );
        SetStaticEdge( IDC_ICON_DELICIOUS, m_param.delicious.isTarget );
        SetStaticEdge( IDC_ICON_MM_MEMO, m_param.mmMemo.isTarget );
        SetStaticEdge( IDC_ICON_DRECOM_RSS, m_param.drecomRss.isTarget );
        SetStaticEdge( IDC_ICON_FLOG, m_param.flog.isTarget );
        SetStaticEdge( IDC_ICON_LIVEDOOR, m_param.livedoorClip.isTarget );
        SetStaticEdge( IDC_ICON_ECNAVI_CLIP, m_param.ecNaviClip.isTarget );
        SetStaticEdge( IDC_ICON_NIFTY_CLIP, m_param.niftyClip.isTarget );
        SetStaticEdge( IDC_ICON_1470NET, m_param.next1470net.isTarget );
        SetStaticEdge( IDC_ICON_NEWSING, m_param.newsing.isTarget );
        SetStaticEdge( IDC_ICON_POOKMARK, m_param.pookmark.isTarget );
        SetStaticEdge( IDC_ICON_BLUEDOT, m_param.blueDot.isTarget );
        SetStaticEdge( IDC_ICON_JOLTMARK, m_param.joltMark.isTarget );
        SetStaticEdge( IDC_ICON_BLOGPET, m_param.blogPet.isTarget );
        SetStaticEdge( IDC_ICON_FC2BOOKMARK, m_param.fc2bookmark.isTarget );
        SetStaticEdge( IDC_ICON_TWITTER, m_param.twitter.isTarget );
        SetStaticEdge( IDC_ICON_YJBOOKMARK, m_param.yjBookmark.isTarget );
        SetStaticEdge( IDC_ICON_YAHOO_BOOKMARKS,
                       m_param.yahooBookmarks.isTarget );
        SetStaticEdge( IDC_ICON_TIMELOG, m_param.timelog.isTarget );
        SetStaticEdge( IDC_ICON_DIGG, m_param.digg.isTarget );
        SetStaticEdge( IDC_ICON_TUMBLR, m_param.tumblr.isTarget );
        SetStaticEdge( IDC_ICON_DIIGO, m_param.diigo.isTarget );

        SetUsers( m_hbUsers, IDC_HB_USERS );
        SetUsers( m_deliciousUsers, IDC_DELICIOUS_USERS );
        SetUsers( m_mmUsers, IDC_MM_USERS );
        SetUsers( m_ecNaviUsers, IDC_ECNAVI_USERS );
        SetUsers( m_livedoorClipUsers, IDC_LIVEDOORCLIP_USERS );
        SetUsers( m_niftyClipUsers, IDC_NIFTYCLIP_USERS );
        SetUsers( m_diggUsers, IDC_DIGG_USERS );
        SetUsers( m_hatenaStarUsers, IDC_HATENA_STAR_USERS, 10 );
    }
}

void EditBookmarkDialog::OnCheckTipjar() 
{
    if ( m_enableTipJar || m_enableCollection ) {
        CButton *p = (CButton *)GetDlgItem( IDC_CHECK_TIPJAR );
        if ( m_enableTipJar )
            m_sendTipJar = p->GetCheck() ? TRUE : FALSE;
        else
            m_registerCollection = p->GetCheck() ? true : false;
    }
}

void EditBookmarkDialog::OnTag001() 
{
    SetTag( IDC_TAG001 );
}

void EditBookmarkDialog::OnTag002() 
{
    SetTag( IDC_TAG002 );
}

void EditBookmarkDialog::OnTag003() 
{
    SetTag( IDC_TAG003 );
}

void EditBookmarkDialog::OnTag004() 
{
    SetTag( IDC_TAG004 );
}

void EditBookmarkDialog::OnTag005() 
{
    SetTag( IDC_TAG005 );
}

void EditBookmarkDialog::OnTag006() 
{
    SetTag( IDC_TAG006 );
}

void EditBookmarkDialog::OnTag007() 
{
    SetTag( IDC_TAG007 );
}

void EditBookmarkDialog::OnTag008() 
{
    SetTag( IDC_TAG008 );
}

void EditBookmarkDialog::OnTag009() 
{
    SetTag( IDC_TAG009 );
}

void EditBookmarkDialog::OnTag010() 
{
    SetTag( IDC_TAG010 );
}

void EditBookmarkDialog::OnTag011() 
{
    SetTag( IDC_TAG011 );
}

void EditBookmarkDialog::OnTag012() 
{
    SetTag( IDC_TAG012 );
}

void EditBookmarkDialog::OnTag013() 
{
    SetTag( IDC_TAG013 );
}

void EditBookmarkDialog::OnTag014() 
{
    SetTag( IDC_TAG014 );
}

void EditBookmarkDialog::OnTag015() 
{
    SetTag( IDC_TAG015 );
}

void EditBookmarkDialog::OnTag016() 
{
    SetTag( IDC_TAG016 );
}

void EditBookmarkDialog::OnTag017() 
{
    SetTag( IDC_TAG017 );
}

void EditBookmarkDialog::OnTag018() 
{
    SetTag( IDC_TAG018 );
}

void EditBookmarkDialog::OnTag019() 
{
    SetTag( IDC_TAG019 );
}

void EditBookmarkDialog::OnTag020() 
{
    SetTag( IDC_TAG020 );
}

void EditBookmarkDialog::OnSelchangeComboCategory() 
{
    int     location = m_categoryList.GetCurSel();
	m_categoryList.GetLBText( location, m_category );
}

void EditBookmarkDialog::OnSelchangeComboCategory2() 
{
    int     location = m_categoryList2.GetCurSel();
	m_categoryList2.GetLBText( location, m_category2 );
}

void EditBookmarkDialog::OnOK() 
{
	CDialog::OnOK();

    if ( m_category.GetLength() > 0 ) {
        if ( m_tags.GetLength() > 0 )
            m_tags += " ";
        if ( !(m_category.Compare( "IT" )) )
            m_tags += "Internet";
        else if ( !(m_category.Compare( "�G���^�[�e�C�����g" )) ||
                  !(m_category.Compare( "Entertainment" ))         )
            m_tags += "entertainment";
        else if ( !(m_category.Compare( "�T�C�G���X" )) ||
                  !(m_category.Compare( "Science" ))       )
            m_tags += "science";
        else if ( !(m_category.Compare( "�n��" ))   ||
                  !(m_category.Compare( "Region" ))    )
            m_tags += "region";
        else if ( !(m_category.Compare( "�Љ�" ))   ||
                  !(m_category.Compare( "Social" ))    )
            m_tags += "social";
        else if ( !(m_category.Compare( "�R����" )) ||
                  !(m_category.Compare( "Column" ))    )
            m_tags += "column";
        else if ( !(m_category.Compare( "�]��" ))          ||
                  !(m_category.Compare( "News of death" ))    )
            m_tags += "news-of-death";
        else if ( !(m_category.Compare( "�����E�|�\" ))        ||
                  !(m_category.Compare( "Culture / Showbiz" ))    )
            m_tags += "culture";
        else if ( !(m_category.Compare( "blog" )) ||
                  !(m_category.Compare( "Blog" ))    )
            m_tags += "blog";
        else if ( !(m_category.Compare( "�o�ρE�o�c" ))           ||
                  !(m_category.Compare( "Economy / Management" ))    )
            m_tags += "economy";
        else if ( !(m_category.Compare( "����" ))     ||
                  !(m_category.Compare( "Politics" ))    )
            m_tags += "politics";
        else if ( !(m_category.Compare( "�X�|�[�c" )) ||
                  !(m_category.Compare( "Sports" ))      )
            m_tags += "sport";
        else if ( !(m_category.Compare( "�u�b�N���r���[" )) ||
                  !(m_category.Compare( "Book review" ))       )
            m_tags += "book-review";
        else if ( !(m_category.Compare( "����" ))          ||
                  !(m_category.Compare( "International" ))    )
            m_tags += "international";
        else if ( !(m_category.Compare( "�e�N�m���W�[" )) ||
                  !(m_category.Compare( "Technology" ))      )
            m_tags += "technology";
    }

    if ( m_category2.GetLength() > 0 ) {
        if ( m_tags.GetLength() > 0 )
            m_tags += " ";
        if ( !(m_category2.Compare( "�R���s���[�^" )) ||
             !(m_category2.Compare( "Computer" ))        )
            m_tags += "computer";
        else if ( !(m_category2.Compare( "�r�W�l�X/����" ))       ||
                  !(m_category2.Compare( "Business / Politics" ))    )
            m_tags += "business";
        else if ( !(m_category2.Compare( "�j���[�X" )) ||
                  !(m_category2.Compare( "News" ))        )
            m_tags += "news";
        else if ( !(m_category2.Compare( "���L" ))  ||
                  !(m_category2.Compare( "Diary" ))    )
            m_tags += "diary";
        else if ( !(m_category2.Compare( "�|�\/�A�C�h��" ))  ||
                  !(m_category2.Compare( "Showbiz / Idol" ))    )
            m_tags += "showbiz";
        else if ( !(m_category2.Compare( "�w���X/�r���[�e�B" )) ||
                  !(m_category2.Compare( "Health / Beauty" ))      )
            m_tags += "health";
        else if ( !(m_category2.Compare( "�A�E/�]�E" ))       ||
                  !(m_category2.Compare( "Find Employment" ))    )
            m_tags += "employment";
        else if ( !(m_category2.Compare( "�O����" ))  ||
                  !(m_category2.Compare( "Gourmet" ))    )
            m_tags += "gourmet";
        else if ( !(m_category2.Compare( "���y" ))  ||
                  !(m_category2.Compare( "Music" ))    )
            m_tags += "music";
        else if ( !(m_category2.Compare( "�f��" ))  ||
                  !(m_category2.Compare( "Movie" ))    )
            m_tags += "cinema";
        else if ( !(m_category2.Compare( "�{/�G��/�V��" ))       ||
                  !(m_category2.Compare( "Books / Newspapers" ))    )
            m_tags += "print";
        else if ( !(m_category2.Compare( "����/�A�j��" ))     ||
                  !(m_category2.Compare( "Comics / Animes" ))    )
            m_tags += "cartoon";
        else if ( !(m_category2.Compare( "�e���r" )) ||
                  !(m_category2.Compare( "TV" ))        )
            m_tags += "tv";
        else if ( !(m_category2.Compare( "�Q�[��" )) ||
                  !(m_category2.Compare( "Game" ))      )
            m_tags += "game";
        else if ( !(m_category2.Compare( "�y�b�g/����" ))    ||
                  !(m_category2.Compare( "Pets / Animals" ))    )
            m_tags += "animal";
        else if ( !(m_category2.Compare( "�/�X�|�[�c" ))  ||
                  !(m_category2.Compare( "Hobby / Sports" ))    )
            m_tags += "hobby";
        else if ( !(m_category2.Compare( "��/�o�C�N" ))  ||
                  !(m_category2.Compare( "Car / Bike" ))    )
            m_tags += "car";
        else if ( !(m_category2.Compare( "���炵/�Ɠd" ))                 ||
                  !(m_category2.Compare( "Life / Consumer Electronics" ))    )
            m_tags += "life";
        else if ( !(m_category2.Compare( "���s/�n����" ))          ||
                  !(m_category2.Compare( "Travel / Regional Info" ))    )
            m_tags += "travel";
        else if ( !(m_category2.Compare( "�|�p/�f�U�C��" )) ||
                  !(m_category2.Compare( "Arts / Design" ))    )
            m_tags += "art";
        else if ( !(m_category2.Compare( "����/�w��/����" ))         ||
                  !(m_category2.Compare( "Education / References" ))    )
            m_tags += "education";
        else if ( !(m_category2.Compare( "����/�t���b�V��" ))    ||
                  !(m_category2.Compare( "Animations / Flash" ))    )
            m_tags += "movie";
        else if ( !(m_category2.Compare( "�֗��c�[��" )) ||
                  !(m_category2.Compare( "Tools" ))         )
            m_tags += "tool";
        else if ( !(m_category2.Compare( "�܂Ƃ߃T�C�g" )) ||
                  !(m_category2.Compare( "Summary Site" ))    )
            m_tags += "summarySite";
        else if ( !(m_category2.Compare( "�l�^/�W���[�N" )) ||
                  !(m_category2.Compare( "Jokes" ))            )
            m_tags += "neta";
        else if ( !(m_category2.Compare( "����" )) ||
                  !(m_category2.Compare( "Love" ))    )
            m_tags += "love";
        else if ( !(m_category2.Compare( "�t�@�b�V����/�u�����h" )) ||
                  !(m_category2.Compare( "Fashion / Brand" ))          )
            m_tags += "fashion";
        else if ( !(m_category2.Compare( "�C�O" ))      ||
                  !(m_category2.Compare( "Ovearseas" ))    )
            m_tags += "overseas";
    }

    const char  *s;
    if ( ( s = strstr( m_tags, "  " ) ) != NULL ) {
        char    temp[MAX_DESCRIPTION_LEN];
        strcpy( temp, m_tags );
        while ( ( s = strstr( temp, "  " ) ) != NULL )
            strcpy( (char *)s, s + 1 );
        m_tags  = temp;
    }

    if ( (m_sendTipJar == TRUE) && (m_enableTipJar == false) )
        m_sendTipJar = FALSE;

    if ( (m_public == PUB_REQUESTED)  ||
         (m_public == PUB_REQUESTED2)    )
        m_public = PUB_EVERYONE;
}

BOOL EditBookmarkDialog::OnInitDialog() 
{
    CDialog::OnInitDialog();

    EnableToolTips(TRUE);

    return TRUE;
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void EditBookmarkDialog::OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult)
{
    TOOLTIPTEXT *tp = (TOOLTIPTEXT *)pNMHDR;
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    if ( (tp->uFlags & TTF_IDISHWND) == TTF_IDISHWND ) {
        int id = ::GetDlgCtrlID( (HWND)tp->hdr.idFrom );

        switch ( id ) {
        case IDC_ICON_HATENA_BOOKMARK:
            strcpy( tp->szText, m_tgt_hatenaBookmark );
            DisplayToolTip( pp->m_hatena, m_param.hatena.isTarget, tp );
            break;
        case IDC_ICON_DELICIOUS:
            strcpy( tp->szText, m_tgt_delicious );
            DisplayToolTip( pp->m_delicious, m_param.delicious.isTarget, tp );
            break;
        case IDC_ICON_MM_MEMO:
            strcpy( tp->szText, m_tgt_mmMemo );
            DisplayToolTip( pp->m_mmMemo, m_param.mmMemo.isTarget, tp );
            break;
        case IDC_ICON_DRECOM_RSS:
            strcpy( tp->szText, m_tgt_drecomRSS );
            DisplayToolTip( pp->m_drecomRss, m_param.drecomRss.isTarget, tp );
            break;
        case IDC_ICON_FLOG:
            strcpy( tp->szText, m_tgt_flog );
            DisplayToolTip( pp->m_flog, m_param.flog.isTarget, tp );
            break;
        case IDC_ICON_LIVEDOOR:
            strcpy( tp->szText, m_tgt_livedoorClip );
            DisplayToolTip( pp->m_livedoorClip,
                            m_param.livedoorClip.isTarget, tp );
            break;
        case IDC_ICON_ECNAVI_CLIP:
            strcpy( tp->szText, m_tgt_ecNaviClip );
            DisplayToolTip(pp->m_ecNaviClip, m_param.ecNaviClip.isTarget, tp);
            break;
        case IDC_ICON_NIFTY_CLIP:
            strcpy( tp->szText, m_tgt_niftyClip );
            DisplayToolTip( pp->m_niftyClip, m_param.niftyClip.isTarget, tp );
            break;
        case IDC_ICON_1470NET:
            strcpy( tp->szText, m_tgt_1470net );
            DisplayToolTip(pp->m_next1470net,m_param.next1470net.isTarget,tp);
            break;
        case IDC_ICON_NEWSING:
            strcpy( tp->szText, m_tgt_newsing );
            DisplayToolTip( pp->m_newsing, m_param.newsing.isTarget, tp );
            break;
        case IDC_ICON_POOKMARK:
            strcpy( tp->szText, m_tgt_pookmark );
            DisplayToolTip( pp->m_pookmark, m_param.pookmark.isTarget, tp );
            break;
        case IDC_ICON_BLUEDOT:
            strcpy( tp->szText, m_tgt_blueDot );
            DisplayToolTip( pp->m_blueDot, m_param.blueDot.isTarget, tp );
            break;
        case IDC_ICON_JOLTMARK:
            strcpy( tp->szText, m_tgt_joltMark );
            DisplayToolTip( pp->m_joltMark, m_param.joltMark.isTarget, tp );
            break;
        case IDC_ICON_BLOGPET:
            strcpy( tp->szText, m_tgt_blogPet );
            DisplayToolTip( pp->m_blogPet, m_param.blogPet.isTarget, tp );
            break;
        case IDC_ICON_FC2BOOKMARK:
            strcpy( tp->szText, m_tgt_fc2bookmark );
            DisplayToolTip( pp->m_fc2bookmark, m_param.fc2bookmark.isTarget, tp );
            break;
        case IDC_ICON_TWITTER:
            strcpy( tp->szText, m_tgt_twitter );
            DisplayToolTip( pp->m_twitter, m_param.twitter.isTarget, tp );
            break;
        case IDC_ICON_YJBOOKMARK:
            strcpy( tp->szText, m_tgt_yjBookmark );
            DisplayToolTip( pp->m_yjBookmark, m_param.yjBookmark.isTarget, tp );
            break;
        case IDC_ICON_YAHOO_BOOKMARKS:
            strcpy( tp->szText, m_tgt_yahooBookmarks );
            DisplayToolTip( pp->m_yahooBookmarks,
                            m_param.yahooBookmarks.isTarget, tp );
            break;
        case IDC_ICON_TIMELOG:
            strcpy( tp->szText, m_tgt_timelog );
            DisplayToolTip( pp->m_timelog, m_param.timelog.isTarget, tp );
            break;
        case IDC_ICON_DIGG:
            strcpy( tp->szText, m_tgt_digg );
            DisplayToolTip( pp->m_digg, m_param.digg.isTarget, tp );
            break;
        case IDC_ICON_TUMBLR:
            strcpy( tp->szText, m_tgt_tumblr );
            DisplayToolTip( pp->m_tumblr, m_param.tumblr.isTarget, tp );
            break;
        case IDC_ICON_DIIGO:
            strcpy( tp->szText, m_tgt_diigo );
            DisplayToolTip( pp->m_diigo, m_param.diigo.isTarget, tp );
            break;
        case IDC_ICON_HATENA_STAR:
        case IDC_HATENA_STAR_USERS:
            strcpy( tp->szText, m_tgt_hatenaStar );
            break;
        }
    }
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void EditBookmarkDialog::OnIconHatenaBookmark() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://b.hatena.ne.jp/entry/%s",
             encodeURLforHatena( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconDelicious() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://del.icio.us/url/check?url=%s",
             encodeURL( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconMmMemo() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://mmmemo.1470.net/mm/related?url=%s",
             encodeURL( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconLivedoor() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://clip.livedoor.com/page/%s",
             encodeURLforHatena( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconEcnaviClip() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://buzzurl.jp/entry/%s",
             encodeURLforHatena( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIcon1470net() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://1470.net/uri/%s",
             encodeURLforHatena( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconNewsing() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://newsing.jp/entry?url=%s",
             encodeURL( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconNiftyClip() 
{
    char    cmd[BUFSIZ];

    sprintf( cmd, "http://clip.nifty.com/entry/?url=%s",
             encodeURL( (const char *)m_url ) );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void EditBookmarkDialog::OnIconDigg() 
{
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    /* Digg API �����s */
    request  = (char *)malloc( sz );
    if ( !request )
        return;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return;
    }
    memset( request, 0x00, BUFSIZ );

    sprintf( request,
             "http://services.digg.com/stories?link=%s",
             encodeURL( m_url ) );
    sprintf( request + strlen(request),
             "&appkey=%s",
        encodeURL("http://watcher.moe-nifty.com/memo/2005/10/bookey.html") );
                                                        // IDS_BOOKEY_WEB_URL
    setUpReceiveBuffer( response, sz );
    http_get( request, response );

    if ( *response ) {
        char    *p, *q, *r;

        p = strstr( response, "<story id=\"" );
        if ( p ) {
            p += 11;
            q = strstr( p, " href=\"" );
            r = strchr( p, '>' );
            if ( q && r && (q < r) ) {
                q += 7;
                r = strchr( q, '"' );
                if ( r ) {
                    char    diggURL[MAX_URLLENGTH];

                    strncpy( diggURL, q, r - q );
                    diggURL[r - q] = NULL;
                    ShellExecute( NULL, "open", diggURL, NULL, NULL,
                                  SW_SHOWNORMAL );
                }
            }
        }
    }

    free( response );
    free( request );
}

void EditBookmarkDialog::OnIconHatenaStar() 
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    if ( (m_url.GetLength() > 0)                   &&
         (pp->m_hatena.m_username.GetLength() > 0) &&
         (pp->m_hatena.m_password.GetLength() > 0)    ) {
        // �� ������
        BOOL    b = setHatenaStar( m_url,
                                   pp->m_hatena.m_username,
                                   pp->m_hatena.m_password );
        if ( b ) {
            // �� �̐���\��������
            char    buf[64];
            long    numOfHatenaStar =
                                atol( (const char *)m_hatenaStarUsers + 1 );
            numOfHatenaStar++;
            m_hatenaStarUsers = _T("(");
            m_hatenaStarUsers += ltoa( numOfHatenaStar, buf, 10 );
            m_hatenaStarUsers += _T(")");

            CStatic *s = (CStatic *)GetDlgItem( IDC_HATENA_STAR_USERS );
            s->SetWindowText( m_hatenaStarUsers );
        }
    }
}

void EditBookmarkDialog::OnHbUsers() 
{
    OnIconHatenaBookmark();
}

void EditBookmarkDialog::OnDeliciousUsers() 
{
    OnIconDelicious();
}

void EditBookmarkDialog::OnMmUsers() 
{
    OnIconMmMemo();
}

void EditBookmarkDialog::OnEcnaviUsers() 
{
    OnIconEcnaviClip();
}

void EditBookmarkDialog::OnLivedoorclipUsers() 
{
    OnIconLivedoor();
}

void EditBookmarkDialog::OnNiftyclipUsers() 
{
    OnIconNiftyClip();
}

void EditBookmarkDialog::OnDiggUsers() 
{
    OnIconDigg();
}

void EditBookmarkDialog::OnHatenaStarUsers() 
{
    OnIconHatenaStar();
}

BOOL EditBookmarkDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if ( nHitTest == HTCLIENT ) {
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );

        if ( IsInner( IDC_ICON_HATENA_BOOKMARK, wX, wY ) ||
             IsInner( IDC_HB_USERS, wX, wY )                ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_DELICIOUS, wX, wY )  ||
             IsInner( IDC_DELICIOUS_USERS, wX, wY )    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_MM_MEMO, wX, wY ) ||
             IsInner( IDC_MM_USERS, wX, wY )        ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_LIVEDOOR, wX, wY )      ||
             IsInner( IDC_LIVEDOORCLIP_USERS, wX, wY )    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_ECNAVI_CLIP, wX, wY ) ||
             IsInner( IDC_ECNAVI_USERS, wX, wY )        ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_NIFTY_CLIP, wX, wY ) ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_1470NET, wX, wY ) ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_NEWSING, wX, wY ) ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_DIGG, wX, wY )  ||
             IsInner( IDC_DIGG_USERS, wX, wY )    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        if ( IsInner( IDC_ICON_HATENA_STAR, wX, wY )  ||
             IsInner( IDC_HATENA_STAR_USERS, wX, wY )    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        for ( int i = 0; i < 20; i++ ) {
            if ( IsInner( IDC_TAG001 + i, wX, wY ) ) {
			    SetCursor( m_hCursor );
                return TRUE;
            }
        }
	}
	
    return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void EditBookmarkDialog::OnNewsGood() 
{
    CButton *p = (CButton *)GetDlgItem( IDC_NEWS_GOOD );

    if ( m_affirmation == AFF_GOOD ) {
        p->SetCheck( 0 );
    	m_affirmation = AFF_NONE;
    }
    else {
    	m_affirmation = AFF_GOOD;

        p = (CButton *)GetDlgItem( IDC_NEWS_BAD );
        p->SetCheck( 0 );
    }
}

void EditBookmarkDialog::OnNewsBad() 
{
    CButton *p = (CButton *)GetDlgItem( IDC_NEWS_BAD );

    if ( m_affirmation == AFF_BAD ) {
        p->SetCheck( 0 );
    	m_affirmation = AFF_NONE;
    }
    else {
	    m_affirmation = AFF_BAD;

        p = (CButton *)GetDlgItem( IDC_NEWS_GOOD );
        p->SetCheck( 0 );
    }
}

void EditBookmarkDialog::OnRadioEval00() 
{
    m_evaluation = EVL_NONE;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_EVAL01 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL02 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL03 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL04 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL05 );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioEval01() 
{
    m_evaluation = EVL_ONE;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL02 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL03 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL04 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL05 );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioEval02() 
{
    m_evaluation = EVL_TWO;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL01 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL03 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL04 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL05 );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioEval03() 
{
    m_evaluation = EVL_THREE;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL01 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL02 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL04 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL05 );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioEval04() 
{
    m_evaluation = EVL_FOUR;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL01 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL02 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL03 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL05 );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioEval05() 
{
    m_evaluation = EVL_FIVE;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_EVAL00 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL01 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL02 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL03 );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_EVAL04 );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioPublic() 
{
    m_public = PUB_EVERYONE;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_FRIENDS );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_PRIVATE );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioFriends() 
{
    m_public = PUB_FRIENDS;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_PUBLIC );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_PRIVATE );
    p->SetCheck( 0 );
}

void EditBookmarkDialog::OnRadioPrivate() 
{
    m_public = PUB_PRIVATE;

    CButton *p = (CButton *)GetDlgItem( IDC_RADIO_PUBLIC );
    p->SetCheck( 0 );

    p = (CButton *)GetDlgItem( IDC_RADIO_FRIENDS );
    p->SetCheck( 0 );
}


#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void EditBookmarkDialog::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    DWORD       dwPos = GetMessagePos();
    WORD        wX    = LOWORD( dwPos );
    WORD        wY    = HIWORD( dwPos );
    bool        onOff = true;
    bool        offOn = false;
    int         targetIDC = 0;
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_HATENA_BOOKMARK, wX, wY ) ||
             IsInner( IDC_HB_USERS, wX, wY )                ) {
            if ( (bool)pp->m_hatena ) {
                targetIDC = IDC_ICON_HATENA_BOOKMARK;
                onOff = m_param.hatena.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_hatena) != NULL)     &&
                     (((const char *)(pp->m_hatena))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_HATENA_BOOKMARK;
                    onOff = m_param.hatena.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_DELICIOUS, wX, wY )  ||
             IsInner( IDC_DELICIOUS_USERS, wX, wY )    ) {
            if ( (bool)pp->m_delicious ) {
                targetIDC = IDC_ICON_DELICIOUS;
                onOff = m_param.delicious.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_delicious) != NULL)     &&
                     (((const char *)(pp->m_delicious))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_DELICIOUS;
                    onOff = m_param.delicious.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_MM_MEMO, wX, wY ) ||
             IsInner( IDC_MM_USERS, wX, wY )        ) {
            if ( (bool)pp->m_mmMemo ) {
                targetIDC = IDC_ICON_MM_MEMO;
                onOff = m_param.mmMemo.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_mmMemo) != NULL)     &&
                     (((const char *)(pp->m_mmMemo))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_MM_MEMO;
                    onOff = m_param.mmMemo.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_DRECOM_RSS, wX, wY ) ) {
            if ( (bool)pp->m_drecomRss ) {
                targetIDC = IDC_ICON_DRECOM_RSS;
                onOff = m_param.drecomRss.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_drecomRss) != NULL)     &&
                     (((const char *)(pp->m_drecomRss))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_DRECOM_RSS;
                    onOff = m_param.drecomRss.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_FLOG, wX, wY ) ) {
            if ( (bool)pp->m_flog ) {
                targetIDC = IDC_ICON_FLOG;
                onOff = m_param.flog.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_flog) != NULL)     &&
                     (((const char *)(pp->m_flog))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_FLOG;
                    onOff = m_param.flog.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_LIVEDOOR, wX, wY )      ||
             IsInner( IDC_LIVEDOORCLIP_USERS, wX, wY )    ) {
            if ( (bool)pp->m_livedoorClip ) {
                targetIDC = IDC_ICON_LIVEDOOR;
                onOff = m_param.livedoorClip.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_livedoorClip) != NULL)     &&
                     (((const char *)(pp->m_livedoorClip))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_LIVEDOOR;
                    onOff = m_param.livedoorClip.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_ECNAVI_CLIP, wX, wY ) ||
             IsInner( IDC_ECNAVI_USERS, wX, wY )        ) {
            if ( (bool)pp->m_ecNaviClip ) {
                targetIDC = IDC_ICON_ECNAVI_CLIP;
                onOff = m_param.ecNaviClip.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_ecNaviClip) != NULL)     &&
                     (((const char *)(pp->m_ecNaviClip))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_ECNAVI_CLIP;
                    onOff = m_param.ecNaviClip.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_NIFTY_CLIP, wX, wY ) ) {
            if ( (bool)pp->m_niftyClip ) {
                targetIDC = IDC_ICON_NIFTY_CLIP;
                onOff = m_param.niftyClip.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_niftyClip) != NULL)     &&
                     (((const char *)(pp->m_niftyClip))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_NIFTY_CLIP;
                    onOff = m_param.niftyClip.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_1470NET, wX, wY ) ) {
            if ( (bool)pp->m_next1470net ) {
                targetIDC = IDC_ICON_1470NET;
                onOff = m_param.next1470net.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_next1470net) != NULL)     &&
                     (((const char *)(pp->m_next1470net))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_1470NET;
                    onOff = m_param.next1470net.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_NEWSING, wX, wY ) ) {
            if ( (bool)pp->m_newsing ) {
                targetIDC = IDC_ICON_NEWSING;
                onOff = m_param.newsing.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_newsing) != NULL)     &&
                     (((const char *)(pp->m_newsing))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_NEWSING;
                    onOff = m_param.newsing.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_POOKMARK, wX, wY ) ) {
            if ( (bool)pp->m_pookmark ) {
                targetIDC = IDC_ICON_POOKMARK;
                onOff = m_param.pookmark.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_pookmark) != NULL)     &&
                     (((const char *)(pp->m_pookmark))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_POOKMARK;
                    onOff = m_param.pookmark.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_BLUEDOT, wX, wY ) ) {
            if ( (bool)pp->m_blueDot ) {
                targetIDC = IDC_ICON_BLUEDOT;
                onOff = m_param.blueDot.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_blueDot) != NULL)     &&
                     (((const char *)(pp->m_blueDot))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_BLUEDOT;
                    onOff = m_param.blueDot.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_JOLTMARK, wX, wY ) ) {
            if ( (bool)pp->m_joltMark ) {
                targetIDC = IDC_ICON_JOLTMARK;
                onOff = m_param.joltMark.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_joltMark) != NULL)     &&
                     (((const char *)(pp->m_joltMark))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_JOLTMARK;
                    onOff = m_param.joltMark.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_BLOGPET, wX, wY ) ) {
            if ( (bool)pp->m_blogPet ) {
                targetIDC = IDC_ICON_BLOGPET;
                onOff = m_param.blogPet.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_blogPet) != NULL)     &&
                     (((const char *)(pp->m_blogPet))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_BLOGPET;
                    onOff = m_param.blogPet.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_FC2BOOKMARK, wX, wY ) ) {
            if ( (bool)pp->m_fc2bookmark ) {
                targetIDC = IDC_ICON_FC2BOOKMARK;
                onOff = m_param.fc2bookmark.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_fc2bookmark) != NULL)     &&
                     (((const char *)(pp->m_fc2bookmark))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_FC2BOOKMARK;
                    onOff = m_param.fc2bookmark.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_TWITTER, wX, wY ) ) {
            if ( (bool)pp->m_twitter ) {
                targetIDC = IDC_ICON_TWITTER;
                onOff = m_param.twitter.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_twitter) != NULL)     &&
                     (((const char *)(pp->m_twitter))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_TWITTER;
                    onOff = m_param.twitter.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_YJBOOKMARK, wX, wY ) ) {
            if ( (bool)pp->m_yjBookmark ) {
                targetIDC = IDC_ICON_YJBOOKMARK;
                onOff = m_param.yjBookmark.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_yjBookmark) != NULL)     &&
                     (((const char *)(pp->m_yjBookmark))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_YJBOOKMARK;
                    onOff = m_param.yjBookmark.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_YAHOO_BOOKMARKS, wX, wY ) ) {
            if ( (bool)pp->m_yahooBookmarks ) {
                targetIDC = IDC_ICON_YAHOO_BOOKMARKS;
                onOff = m_param.yahooBookmarks.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_yahooBookmarks) != NULL)     &&
                     (((const char *)(pp->m_yahooBookmarks))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_YAHOO_BOOKMARKS;
                    onOff = m_param.yahooBookmarks.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_TIMELOG, wX, wY ) ) {
            if ( (bool)pp->m_timelog ) {
                targetIDC = IDC_ICON_TIMELOG;
                onOff = m_param.timelog.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_timelog) != NULL)     &&
                     (((const char *)(pp->m_timelog))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_TIMELOG;
                    onOff = m_param.timelog.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_DIGG, wX, wY )      ||
             IsInner( IDC_DIGG_USERS, wX, wY )    ) {
            if ( (bool)pp->m_digg ) {
                targetIDC = IDC_ICON_DIGG;
                onOff = m_param.digg.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_digg) != NULL)     &&
                     (((const char *)(pp->m_digg))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_DIGG;
                    onOff = m_param.digg.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_TUMBLR, wX, wY ) ) {
            if ( (bool)pp->m_tumblr ) {
                targetIDC = IDC_ICON_TUMBLR;
                onOff = m_param.tumblr.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_tumblr) != NULL)     &&
                     (((const char *)(pp->m_tumblr))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_TUMBLR;
                    onOff = m_param.tumblr.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 ) {
        if ( IsInner( IDC_ICON_DIIGO, wX, wY ) ) {
            if ( (bool)pp->m_diigo ) {
                targetIDC = IDC_ICON_DIIGO;
                onOff = m_param.diigo.isTarget ? true : false;
            }
            else {
                if ( ((const char *)(pp->m_diigo) != NULL)     &&
                     (((const char *)(pp->m_diigo))[0] != NUL)    ) {
                    targetIDC = IDC_ICON_DIIGO;
                    onOff = m_param.diigo.isTarget ? true : false;
                    offOn = true;
                }
            }
        }
    }

    if ( targetIDC == 0 )
        return;

    CPoint  cMenuPt;
    GetCursorPos( &cMenuPt );

#define IDC_MENU_SWITCH_ON      1
#define IDC_MENU_SWITCH_OFF     2
#define IDC_MENU_SWITCH_ON2     3
#define IDC_MENU_SWITCH_OFF2    4
    CMenu   menu;
    CString text;
    menu.CreatePopupMenu();
    if ( !offOn ) {
        text.LoadString(IDS_MENU_TURN_ON);
        menu.AppendMenu( MF_STRING, IDC_MENU_SWITCH_ON,
                         text );    // ON �ɖ߂�(&A)
        text.LoadString(IDS_MENU_TURN_OFF);
        menu.AppendMenu( MF_STRING, IDC_MENU_SWITCH_OFF,
                         text );    // �ꎞ�I�� OFF �ɂ���(&Z)

        if ( onOff )
            menu.EnableMenuItem( IDC_MENU_SWITCH_ON, MF_GRAYED );
        if ( !onOff )
            menu.EnableMenuItem( IDC_MENU_SWITCH_OFF, MF_GRAYED );
    }
    else {
        text.LoadString(IDS_MENU_TURN_ON2);
        menu.AppendMenu( MF_STRING, IDC_MENU_SWITCH_ON2,
                         text );    // �ꎞ�I�� ON �ɂ���(&A)
        text.LoadString(IDS_MENU_TURN_OFF2);
        menu.AppendMenu( MF_STRING, IDC_MENU_SWITCH_OFF2,
                         text );    // OFF �ɖ߂�(&Z)

        if ( onOff )
            menu.EnableMenuItem( IDC_MENU_SWITCH_ON2, MF_GRAYED );
        if ( !onOff )
            menu.EnableMenuItem( IDC_MENU_SWITCH_OFF2, MF_GRAYED );
    }

    int iCommand =
        menu.TrackPopupMenu(
            TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
            cMenuPt.x, cMenuPt.y, this, NULL );

    if ( (iCommand == IDC_MENU_SWITCH_ON)   ||
         (iCommand == IDC_MENU_SWITCH_OFF)  ||
         (iCommand == IDC_MENU_SWITCH_ON2)  ||
         (iCommand == IDC_MENU_SWITCH_OFF2)    ) {
        switch ( targetIDC ) {
        case IDC_ICON_HATENA_BOOKMARK:
            m_param.hatena.isTarget = !(m_param.hatena.isTarget);
            SetStaticEdge( targetIDC, m_param.hatena.isTarget );
            break;
        case IDC_ICON_DELICIOUS:
            m_param.delicious.isTarget = !(m_param.delicious.isTarget);
            SetStaticEdge( targetIDC, m_param.delicious.isTarget );
            break;
        case IDC_ICON_MM_MEMO:
            m_param.mmMemo.isTarget = !(m_param.mmMemo.isTarget);
            SetStaticEdge( targetIDC, m_param.mmMemo.isTarget );
            break;
        case IDC_ICON_DRECOM_RSS:
            m_param.drecomRss.isTarget = !(m_param.drecomRss.isTarget);
            SetStaticEdge( targetIDC, m_param.drecomRss.isTarget );
            break;
        case IDC_ICON_FLOG:
            m_param.flog.isTarget = !(m_param.flog.isTarget);
            SetStaticEdge( targetIDC, m_param.flog.isTarget );
            break;
        case IDC_ICON_LIVEDOOR:
            m_param.livedoorClip.isTarget = !(m_param.livedoorClip.isTarget);
            SetStaticEdge( targetIDC, m_param.livedoorClip.isTarget );
            break;
        case IDC_ICON_ECNAVI_CLIP:
            m_param.ecNaviClip.isTarget = !(m_param.ecNaviClip.isTarget);
            SetStaticEdge( targetIDC, m_param.ecNaviClip.isTarget );
            break;
        case IDC_ICON_NIFTY_CLIP:
            m_param.niftyClip.isTarget = !(m_param.niftyClip.isTarget);
            SetStaticEdge( targetIDC, m_param.niftyClip.isTarget );
            break;
        case IDC_ICON_1470NET:
            m_param.next1470net.isTarget = !(m_param.next1470net.isTarget);
            SetStaticEdge( targetIDC, m_param.next1470net.isTarget );
            break;
        case IDC_ICON_NEWSING:
            m_param.newsing.isTarget = !(m_param.newsing.isTarget);
            SetStaticEdge( targetIDC, m_param.newsing.isTarget );
            break;
        case IDC_ICON_POOKMARK:
            m_param.pookmark.isTarget = !(m_param.pookmark.isTarget);
            SetStaticEdge( targetIDC, m_param.pookmark.isTarget );
            break;
        case IDC_ICON_BLUEDOT:
            m_param.blueDot.isTarget = !(m_param.blueDot.isTarget);
            SetStaticEdge( targetIDC, m_param.blueDot.isTarget );
            break;
        case IDC_ICON_JOLTMARK:
            m_param.joltMark.isTarget = !(m_param.joltMark.isTarget);
            SetStaticEdge( targetIDC, m_param.joltMark.isTarget );
            break;
        case IDC_ICON_BLOGPET:
            m_param.blogPet.isTarget = !(m_param.blogPet.isTarget);
            SetStaticEdge( targetIDC, m_param.blogPet.isTarget );
            break;
        case IDC_ICON_FC2BOOKMARK:
            m_param.fc2bookmark.isTarget = !(m_param.fc2bookmark.isTarget);
            SetStaticEdge( targetIDC, m_param.fc2bookmark.isTarget );
            break;
        case IDC_ICON_TWITTER:
            m_param.twitter.isTarget = !(m_param.twitter.isTarget);
            SetStaticEdge( targetIDC, m_param.twitter.isTarget );
            break;
        case IDC_ICON_YJBOOKMARK:
            m_param.yjBookmark.isTarget = !(m_param.yjBookmark.isTarget);
            SetStaticEdge( targetIDC, m_param.yjBookmark.isTarget );
            break;
        case IDC_ICON_YAHOO_BOOKMARKS:
            m_param.yahooBookmarks.isTarget = !(m_param.yahooBookmarks.isTarget);
            SetStaticEdge( targetIDC, m_param.yahooBookmarks.isTarget );
            break;
        case IDC_ICON_TIMELOG:
            m_param.timelog.isTarget = !(m_param.timelog.isTarget);
            SetStaticEdge( targetIDC, m_param.timelog.isTarget );
            break;
        case IDC_ICON_DIGG:
            m_param.digg.isTarget = !(m_param.digg.isTarget);
            SetStaticEdge( targetIDC, m_param.digg.isTarget );
            break;
        case IDC_ICON_TUMBLR:
            m_param.tumblr.isTarget = !(m_param.tumblr.isTarget);
            SetStaticEdge( targetIDC, m_param.tumblr.isTarget );
            break;
        case IDC_ICON_DIIGO:
            m_param.diigo.isTarget = !(m_param.diigo.isTarget);
            SetStaticEdge( targetIDC, m_param.diigo.isTarget );
            break;
        }
    }

    menu.DestroyMenu();	
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif


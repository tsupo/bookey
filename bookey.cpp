/*
 * bookey.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �A�v���P�[�V���� ���C��
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookey.cpp $
 * 
 * 3     09/06/22 22:31 tsupo
 * 0.63c��
 * 
 * 85    09/06/22 17:56 Tsujimura543
 * ���{�ꃂ�[�h�����p�ꃂ�[�h�ؑ֊֘A�A�C��
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 84    09/05/27 17:08 Tsujimura543
 * setSigInfo() �̈�����ǉ�
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 83    09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 82    08/10/21 22:05 Tsujimura543
 * �u�w���v�v���j���[�Ɂu�T�|�[�g�v(2��)�A�u�R�~���j�e�B�v(2��)��ǉ�
 * 
 * 81    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 80    08/07/25 22:16 Tsujimura543
 * Diigo �Ή�
 * 
 * 79    07/10/31 17:14 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 78    07/10/05 2:42 Tsujimura543
 * BBAuth �Ή��֘A�̊e��C�������{
 * 
 * 77    07/09/06 18:01 Tsujimura543
 * CUserInfo�N���X�̃R�s�[�R���X�g���N�^�A������Z�q���g���Ă���������
 * CUserInfo�N���X���Ɉڊ� (PutBookmarks)
 * 
 * 76    07/09/04 23:31 Tsujimura543
 * m_verboseFp �����ꏊ�� CBookeyView �̃f�X�g���N�^�Ɉړ�
 * 
 * 75    07/09/04 22:43 Tsujimura543
 * m_verboseFp �𓱓�
 * 
 * 74    07/09/04 22:30 Tsujimura543
 * m_verbose �𓱓�
 * 
 * 73    07/07/27 1:14 Tsujimura543
 * �uOFF �� �ꎞ�I�� ON�v�؂�ւ��@�\������
 * 
 * 72    07/07/12 11:57 Tsujimura543
 * ResetUserInfo() �� digg �֘A�̏����̈����w������C��
 * 
 * 71    07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 70    07/05/23 16:11 Tsujimura543
 * Timelog �ւ̓o�^(����)�ɑΉ�
 * 
 * 69    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 68    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 67    07/04/16 17:59 Tsujimura543
 * del.icio.us �� posts/all �`���� XML �t�@�C���̃C���|�[�g�ƃG�N�X�|�[�g
 * �ɑΉ�����
 * 
 * 66    07/04/11 15:02 Tsujimura543
 * �R�����g�ƃR�[�h�̓��e���H������Ă��܂��Ă����ӏ����C��
 * (�R�����g���C��)
 * 
 * 65    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 64    07/03/14 17:07 Tsujimura543
 * (1) StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * (2) proxy�֘A�̂������̏C���A�ǉ� (BloGolEe �̐��ʂ���荞��)
 * 
 * 63    07/02/16 16:35 Tsujimura543
 * �R�����g���C��
 * 
 * 62    07/01/29 23:59 Tsujimura543
 * UserInfo() ���C��
 * 
 * 61    07/01/29 17:51 Tsujimura543
 * �^�O�ꗗ�̎擾�A�^�O�̍폜�A�^�O�̒u���̊e������ǉ�
 * 
 * 60    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 59    07/01/17 21:44 Tsujimura543
 * �R�����g���C��
 * 
 * 58    07/01/17 21:43 Tsujimura543
 * �u����v���̎擾�A�ݒ菈���� xmlRPC.dll ���ɗp�ӂ������̂��g���悤
 * �ɕύX
 * 
 * 57    07/01/13 1:42 Tsujimura543
 * CBookeyApp::CBookeyApp() �̒����� CString#LoadString() �����
 * assertion failed ���邱�Ƃ������B�΍�����{ (�p�ꃂ�[�h�Ή��ɂ�������
 * ����������Q)
 * 
 * 56    07/01/12 20:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 55    07/01/12 13:21 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 54    07/01/04 18:54 Tsujimura543
 * ShowWindow() �̈������C��
 * 
 * 53    06/12/22 21:41 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�Ή�
 * 
 * 52    06/12/21 19:13 Tsujimura543
 * (1) JoltMark �ɑΉ�
 * (2) FC2BOOKMARK�A�uBlogPet �C�ɂȂ�L���v�Ή�����
 * 
 * 51    06/12/06 19:48 Tsujimura543
 * �R�����g���C��
 * 
 * 50    06/12/06 19:46 Tsujimura543
 * livedoor Clip �̃G�N�X�|�[�g�t�@�C��(RSS 2.0 �`��)���C���|�[�g����@�\
 * ��ǉ�����
 * 
 * 49    06/12/06 18:59 Tsujimura543
 * �u���J��ԁv�̐ݒ�ɑΉ�
 * 
 * 48    06/11/16 16:43 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��16�i�K�A�I��
 * 
 * 47    06/11/16 14:02 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��15�i�K�A�I��
 * 
 * 46    06/11/06 16:42 Tsujimura543
 * ResetUserInfo() �Ɏb��I�ȑΏ������{(�u���[�J��OPML�v�t�@�C�����̎b��I
 * �ȏC��������ǉ�)
 * 
 * 45    06/10/28 1:37 Tsujimura543
 * CBookeyApp::PutBookmarks() [��2�ڂ̕�] �� u �� delete ���Y��Ă���
 * 
 * 44    06/10/28 1:14 Tsujimura543
 * �u���[�J��OPML�v�֓o�^�ł��Ȃ����Ƃ�����s��ɑΏ�
 * 
 * 43    06/10/26 22:54 Tsujimura543
 * �u���[�J��OPML�v�ɑΉ�
 * 
 * 42    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 41    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline �ɑΉ�
 * 
 * 40    06/09/30 0:25 Tsujimura543
 * newsing �ɑΉ�
 * 
 * 39    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 38    06/09/05 11:14 Tsujimura543
 * Visual C++ 2005 �Ńr���h����ꍇ�ɔ����āAResetDayLightSaving()
 * ��ǉ� (���݃����[�X���Ă��� bookey �� Visual C++ 6 �ɂăr���h����
 * ����)
 * 
 * 37    06/08/22 17:48 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 36    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 35    06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 34    06/07/31 17:56 Tsujimura543
 * �R�����g���C���A�ǉ�
 * 
 * 33    06/07/31 17:51 Tsujimura543
 * �h���b�O�A���h�h���b�v�ɂ��u�b�N�}�[�N�o�^���́A1470.net (MM/Memo) ��
 * login �������̃L���b�V������ɃN���A����悤�ɂ��� (bookie �ȊO�̃A�v��
 * �P�[�V����(�Ⴆ�΁AWeb�u���E�U)�ɂ��A�N�Z�X�ɂ��A�L���b�V�����Ă���
 * cookie [�̂����ATypeKey �ƕR�t�����Ă������]�������ɂȂ��Ă���\��
 * �����邽�߁A�L���b�V�����N���A���āA���̓s�x login �������悤�ɂ���)
 * -- �Ȃ��A���̃u�b�N�}�[�N�T�[�r�X��OPML�t�@�C������̃C���|�[�g���A�擾
 * -- ���A�������͍��܂Œʂ�A�L���b�V����L���Ȃ܂܂Ƃ��Ă���
 * 
 * 32    06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 * 
 * 31    06/07/27 20:44 Tsujimura543
 * EC�i�r�l�C�j���[�X�A�j�t�e�B�N���b�v�A1470.net���j���[�A���łɁu�o�^�v
 * �ł��Ȃ����Ƃ�����(�Ȃ��������p�̊��ł́u�o�^�v�ł��Ă����̂ŋC�Â�
 * �̂��x�ꂽ)�s��ɑΏ�
 * 
 * 30    06/07/19 14:19 Tsujimura543
 * MyClip! �֌W�̏������폜 (2006�N6�����ŃT�[�r�X�I���̂���)
 * 
 * 29    06/07/14 20:50 Tsujimura543
 * 1470.net���j���[�A���łɑΉ�
 * 
 * 28    06/07/05 18:19 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��13�i�K�A�I��
 * 
 * 27    06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 26    06/07/03 23:37 Tsujimura543
 * ProceedingDialog �� DestroyWindow() ���ɗ�O���������邱�Ƃ����錏��
 * �b��Ώ������{ (�f�o�b�O�łł����������Ȃ�?)
 * 
 * 25    06/07/03 15:15 Tsujimura543
 * ProceedingDialog ���݂̉��C (ProceedingDialog �� delete���ɗ�O��
 * �������邱�Ƃ����錏�̑΍���{)
 * 
 * 24    06/06/29 18:46 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 23    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 22    06/06/22 21:21 Tsujimura543
 * inquery �� inquiry �ɏC��(�Ԃ�~�X)
 * 
 * 21    06/06/21 21:14 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��11�i�K�A�I��
 * 
 * 20    06/06/20 14:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��9�i�K�A�I��
 * 
 * 19    06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 18    06/06/14 22:40 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��7�i�K�A�I��
 * 
 * 17    06/06/14 12:06 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��6�i�K�A�I��
 * 
 * 16    06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 15    06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 14    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 13    06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 12    06/05/31 16:29 Tsujimura543
 * warning #4100 �� disable �ɂ���
 * 
 * 11    06/05/08 14:33 Tsujimura543
 * F1�L�[�������Ɂu�󋵈ˑ��w���v�v��\�����悤�Ƃ���̂�}������悤�ɂ�
 * ��
 * 
 * 10    05/11/10 21:20 Tsujimura543
 * (1) �i�s�󋵕\���_�C�A���O�̏����p�ɒǉ������ϐ��A�������폜
 * (2) ��L�ɔ����A�C�x���g���u��d�N���`�F�b�N�v�p�r��p�ɕύX
 * 
 * 9     05/11/10 14:13 Tsujimura543
 * m_proceedTitle ��ǉ�
 * 
 * 8     05/11/10 13:58 Tsujimura543
 * �i�s�󋵕\���_�C�A���O�Ή������Ƃ��āA�C�x���g�𓱓�
 * 
 * 7     05/11/10 12:06 Tsujimura543
 * �h�L�������g�e���v���[�g�֘A�̏������R�����g�A�E�g�����B����Ń��W�X�g
 * ����m��Ȃ��Ԃɏ��������Ă��܂��\�����r���ł����͂��B
 * 
 * 6     05/10/14 14:20 Tsujimura543
 * CAboutDlg ��ʃt�@�C���֕����A�Ɨ�������
 * 
 * 5     05/10/14 13:25 Tsujimura543
 * �ʓr�쐬�����h���b�O�E�A���h�E�h���b�v�Ή������v���O�����̐��ʂ���荞
 * ��
 * 
 * 4     05/10/14 11:07 Tsujimura543
 * 0.02 �� (�h���b�O�E�A���h�E�h���b�v���Ή���)
 * 
 * 3     05/10/11 17:04 Tsujimura543
 * ���ł̃^�C���X�^���v�\�L�~�X���C�� (�R�����g�݂̂̏C���B����ɉe���Ȃ�)
 * 
 * 2     05/09/30 23:52 Tsujimura543
 * �u�b�N�}�[�N�̎擾�A�o�^�@�\�̓���m�F����
 */

#include "bookey.h"

#include "MainFrm.h"
#include "bookeyDoc.h"
#include "bookeyView.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookey.cpp 3     09/06/22 22:31 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp

BEGIN_MESSAGE_MAP(CBookeyApp, CWinApp)
	//{{AFX_MSG_MAP(CBookeyApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(IDS_ABOUT_SUPPORT, OnAppSupport)
    ON_COMMAND(IDS_ABOUT_SUPPORT2, OnAppSupport2)
    ON_COMMAND(IDS_ABOUT_COMMUNITY, OnAppCommunity)
    ON_COMMAND(IDS_ABOUT_COMMUNITY2, OnAppCommunity2)
	//}}AFX_MSG
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp �N���X�̍\�z

CBookeyApp::CBookeyApp()
{
    m_proceed   = NULL;
    m_verbose   = false;
    m_verboseFp = NULL;

    LCID    langCode;
    m_langCode = langCode = getLanguageCode();
    if ( m_langCode != 0x0411 ) {
        m_langCode = 0x0409;  // �u���{��v�ȊO�̏ꍇ�͋����I�Ɂu�p��v�ɂ���
        if ( langCode != m_langCode )
            setLanguageCode( m_langCode );
    }

    int i = 0;
    m_userInfoList[i++] = &m_hatena;        // [0]  �͂Ăȃu�b�N�}�[�N
    m_userInfoList[i++] = &m_delicious;     // [1]  del.icio.us
    m_userInfoList[i++] = &m_mmMemo;        // [2]  MM/memo
    m_userInfoList[i++] = &m_drecomRss;     // [3]  �h���R��RSS
    m_userInfoList[i++] = &m_flog;          // [4]  Flog
    m_userInfoList[i++] = &m_livedoorClip;  // [5]  livedoor �N���b�v
    m_userInfoList[i++] = &m_ecNaviClip;    // [6]  Buzzurl
    m_userInfoList[i++] = &m_niftyClip;     // [7]  �j�t�e�B�N���b�v
    m_userInfoList[i++] = &m_next1470net;   // [8]  1470.net���j���[�A����
    m_userInfoList[i++] = &m_newsing;       // [9 ] newsing
    m_userInfoList[i++] = &m_pookmark;      // [10] POOKMARK Airlines
    m_userInfoList[i++] = &m_blueDot;       // [11] Blue Dot
    m_userInfoList[i++] = &m_joltMark;      // [12] JoltMark
    m_userInfoList[i++] = &m_fc2bookmark;   // [13] FC2BOOKMARK
    m_userInfoList[i++] = &m_blogPet;       // [14] BlogPet �C�ɂȂ�L��
    m_userInfoList[i++] = &m_twitter;       // [15] Twitter
    m_userInfoList[i++] = &m_yjBookmark;    // [16] Yahoo! Japan �u�b�N�}�[�N
    m_userInfoList[i++] = &m_yahooBookmarks;// [17] Yahoo! Bookmarks
    m_userInfoList[i++] = &m_timelog;       // [18] Timelog
    m_userInfoList[i++] = &m_digg;          // [19] digg
    m_userInfoList[i++] = &m_tumblr;        // [20] tumblr
    m_userInfoList[i++] = &m_diigo;         // [21] Diigo
    m_userInfoList[i++] = &m_localOpml;     // [22] ���[�J��OPML

    m_bookmarkGotten = false;

    m_proxyType      = autoDetect;  // �����ł͂Ƃ肠�����A�b��I�ȏ���������
    m_useProxy       = false;       // �Ă����ACBookeyView::OnInitialUpdate()
    m_proxyServer    = "";          // �ɂĎ��ۂ̒l��ݒ肷��
    m_proxyPort      = 0;
    m_proxyUsername  = "";
    m_proxyPassword  = "";

    m_myClip         = NULL;
    m_numOfClips     = 0;
    m_bookmarkName   = "";

    m_tcKey          = _T("");
    m_tcSecret       = _T("");
}

void CBookeyApp::Initialize()
{
    /*
     * �ȉ��̏����� InitInstance() �ł͌Ăяo���Ȃ����߁A����ɖ{���\�b�h
     * �ɂČĂяo��
     */
    m_hatena.Init( CUserInfo::BK_HATENA );
    m_delicious.Init( CUserInfo::BK_DELICIOUS );
    m_mmMemo.Init( CUserInfo::BK_MM_MEMO );
    m_drecomRss.Init( CUserInfo::BK_DRECOM_RSS );
    m_flog.Init( CUserInfo::BK_FLOG );
    m_livedoorClip.Init( CUserInfo::BK_LIVEDOOR_CLIP );
    m_ecNaviClip.Init( CUserInfo::BK_ECNAVI_CLIP );
    m_niftyClip.Init( CUserInfo::BK_NIFTY_CLIP );
    m_next1470net.Init( CUserInfo::BK_1470NET );
    m_newsing.Init( CUserInfo::BK_NEWSING );
    m_pookmark.Init( CUserInfo::BK_POOKMARK );
    m_blueDot.Init( CUserInfo::BK_BLUEDOT );
    m_joltMark.Init( CUserInfo::BK_JOLTMARK );
    m_fc2bookmark.Init( CUserInfo::BK_FC2BOOKMARK );
    m_blogPet.Init( CUserInfo::BK_BLOGPET );
    m_twitter.Init( CUserInfo::BK_TWITTER );
    m_yjBookmark.Init( CUserInfo::BK_YJ_BOOKMARK );
    m_yahooBookmarks.Init( CUserInfo::BK_YAHOO_BOOKMARKS );
    m_timelog.Init( CUserInfo::BK_TIMELOG );
    m_digg.Init( CUserInfo::BK_DIGG );
    m_tumblr.Init( CUserInfo::BK_TUMBLR );
    m_diigo.Init( CUserInfo::BK_DIIGO );
    m_localOpml.Init( CUserInfo::BK_LOCAL_OPML );

    CString sigHead = _T("");
    CString sigTail = _T("");
    sigHead.LoadString( IDS_TWITTER_OA001 );
    sigTail.LoadString( IDS_TWITTER_OA002 );
    SetSigInfo( m_tcKey, m_tcSecret, sigHead, sigTail );
}

void    CBookeyApp::ReInitialize()
{
    m_hatena.ReInit();
    m_delicious.ReInit();
    m_mmMemo.ReInit();
    m_drecomRss.ReInit();
    m_flog.ReInit();
    m_livedoorClip.ReInit();
    m_ecNaviClip.ReInit();
    m_niftyClip.ReInit();
    m_next1470net.ReInit();
    m_newsing.ReInit();
    m_pookmark.ReInit();
    m_blueDot.ReInit();
    m_joltMark.ReInit();
    m_fc2bookmark.ReInit();
    m_blogPet.ReInit();
    m_twitter.ReInit();
    m_yjBookmark.ReInit();
    m_yahooBookmarks.ReInit();
    m_timelog.ReInit();
    m_digg.ReInit();
    m_tumblr.ReInit();
    m_diigo.ReInit();
    m_localOpml.ReInit();
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CBookeyApp �I�u�W�F�N�g

CBookeyApp theApp;

// ���� ID �͂��̃A�v���P�[�V���������v�I�Ƀ��j�[�N�ɂȂ�悤�ɐ�������܂����B
// �����A���ʂ� ID ���w�肵�����Ȃ�΁A�ύX���Ă����܂��܂���B

// {2DDC3A1A-72B9-47A1-88F6-D2CF12788473}
static const CLSID clsid =
{ 0x2ddc3a1a, 0x72b9, 0x47a1, { 0x88, 0xf6, 0xd2, 0xcf, 0x12, 0x78, 0x84, 0x73 } };

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp �N���X�̏�����

BOOL CBookeyApp::InitInstance()
{
	// OLE ���C�u�����̏�����
	if (!AfxOleInit()) {
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

    m_proceed = new CEvent( FALSE, TRUE, BOOKEY_EVENT_PROCEED, NULL );
    if ( !m_proceed || (GetLastError() == ERROR_ALREADY_EXISTS) )
        return FALSE;

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
                IDR_MAINFRAME,
                RUNTIME_CLASS(CBookeyDoc),
                RUNTIME_CLASS(CMainFrame),  // ���C�� SDI �t���[�� �E�B���h�E
                RUNTIME_CLASS(CBookeyView));
	AddDocTemplate(pDocTemplate);

    ResetDayLightSaving();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated) {
		COleTemplateServer::RegisterAll();
		return TRUE;
	}

    Initialize();

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/*
 *  �Đݒ�
 */
void    CBookeyApp::ResetUserInfo( bool &needToSave )
{
    int i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ )
        m_userInfoList[i]->ResetUserInfo( needToSave );
}

void    CBookeyApp::ResetUserInfo( bool      &needToSave,
                                   RBparam_t &param )
{
    m_hatena.ResetUserInfo( needToSave,
                            param.hatena.isTarget,
                            param.hatena.username,
                            param.hatena.password );
    m_delicious.ResetUserInfo( needToSave,
                               param.delicious.isTarget,
                               param.delicious.username,
                               param.delicious.password );
    m_mmMemo.ResetUserInfo( needToSave,
                            param.mmMemo.isTarget,
                            param.mmMemo.username,
                            param.mmMemo.password );
    m_drecomRss.ResetUserInfo( needToSave,
                               param.drecomRss.isTarget,
                               param.drecomRss.username,
                               param.drecomRss.password );
    m_flog.ResetUserInfo( needToSave,
                          param.flog.isTarget,
                          param.flog.username,
                          param.flog.password );
    m_livedoorClip.ResetUserInfo( needToSave,
                                  param.livedoorClip.isTarget,
                                  param.livedoorClip.username,
                                  param.livedoorClip.password );
    m_ecNaviClip.ResetUserInfo( needToSave,
                                param.ecNaviClip.isTarget,
                                param.ecNaviClip.username,
                                param.ecNaviClip.password );
    m_niftyClip.ResetUserInfo( needToSave,
                               param.niftyClip.isTarget,
                               param.niftyClip.username,
                               param.niftyClip.password );
    m_next1470net.ResetUserInfo( needToSave,
                                 param.next1470net.isTarget,
                                 param.next1470net.username,
                                 param.next1470net.password );
    m_newsing.ResetUserInfo( needToSave,
                             param.newsing.isTarget,
                             param.newsing.username,
                             param.newsing.password );
    m_pookmark.ResetUserInfo( needToSave,
                              param.pookmark.isTarget,
                              param.pookmark.username,
                              param.pookmark.password );
    m_blueDot.ResetUserInfo( needToSave,
                             param.blueDot.isTarget,
                             param.blueDot.username,
                             param.blueDot.password );
    m_joltMark.ResetUserInfo( needToSave,
                              param.joltMark.isTarget,
                              param.joltMark.username,
                              param.joltMark.password );
    m_fc2bookmark.ResetUserInfo( needToSave,
                                 param.fc2bookmark.isTarget,
                                 param.fc2bookmark.username,
                                 param.fc2bookmark.password );
    m_blogPet.ResetUserInfo( needToSave,
                             param.blogPet.isTarget,
                             param.blogPet.username,
                             param.blogPet.password );
    m_twitter.ResetUserInfo( needToSave,
                             param.twitter.isTarget,
                             param.twitter.username,
                             param.twitter.password );
    m_yjBookmark.ResetUserInfo( needToSave,
                                param.yjBookmark.isTarget,
                                param.yjBookmark.username,
                                param.yjBookmark.password );
    m_yahooBookmarks.ResetUserInfo( needToSave,
                                    param.yahooBookmarks.isTarget,
                                    param.yahooBookmarks.username,
                                    param.yahooBookmarks.password );
    m_timelog.ResetUserInfo( needToSave,
                             param.timelog.isTarget,
                             param.timelog.username,
                             param.timelog.password );
    m_digg.ResetUserInfo( needToSave,
                          param.digg.isTarget,
                          param.digg.username,
                          param.digg.password );
    m_tumblr.ResetUserInfo( needToSave,
                            param.tumblr.isTarget,
                            param.tumblr.username,
                            param.tumblr.password );
    m_diigo.ResetUserInfo( needToSave,
                           param.diigo.isTarget,
                           param.diigo.username,
                           param.diigo.password );
    m_localOpml.ResetUserInfo( needToSave,
                               param.localOpml.isTarget,
                               param.localOpml.filename );
}

/*
 *  ���[�U���\��
 */

void    CBookeyApp::SetWindowText( CString bookmarkName,
                                   CString &username,
                                   CString &password,
                                   CEdit   *editUsername,
                                   CEdit   *editPassword,
                                   CButton *executeButton,
                                   CString txt )
{
    SetWindowText( bookmarkName, username, password,
                   editUsername, editPassword );
    executeButton->SetWindowText( txt );
}

void    CBookeyApp::SetWindowText( CString bookmarkName,
                                   CString &username,
                                   CString &password,
                                   CEdit   *editUsername,
                                   CEdit   *editPassword )
{
    if ( bookmarkName.Compare( m_localOpml ) != 0 ) {
        CUserInfo   *u = UserInfoEx( bookmarkName );

        if ( u )
            u->SetWindowText( username, password,
                              editUsername, editPassword );
    }

    editUsername->EnableWindow( TRUE );
    editPassword->EnableWindow( TRUE );
}

void    CBookeyApp::SetWindowText( CString bookmarkName,
                                   CString &username,
                                   CEdit   *editUsername,
                                   CEdit   *editPassword )
{
    if ( bookmarkName.Compare( m_localOpml ) != 0 ) {
        CUserInfo   *u = UserInfoEx( bookmarkName );

        if ( u )
            u->SetWindowText( username, editUsername );
    }

    editUsername->EnableWindow( TRUE );
    editPassword->EnableWindow( FALSE );
}

/*
 *  �e��₢���킹
 */

bool    CBookeyApp::InquiryUserInfo( CString bookmark1, CString bookmark2,
                                     CString txt )
{
    int     i;
    bool    cont = false;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        cont = m_userInfoList[i]->InquiryUserInfo(bookmark1, bookmark2, txt);
        if ( cont == false )
            break;
    }

    return ( cont );
}

/*
 *  �u�b�N�}�[�N�̃C���|�[�g(�o�^)
 */

void    CBookeyApp::ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction )
{
    int     i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        m_userInfoList[i]->ImportFromAnotherToOne(
                                bookmark1,      bookmark2,
                                myBookmark1,    myBookmark2,
                                numOfBookmark1, numOfBookmark2,
                                direction );
    }

    if ( myBookmark1 ) {
        free( myBookmark1 );
        myBookmark1 = NULL;
    }
    if ( myBookmark2 ) {
        free( myBookmark2 );
        myBookmark2 = NULL;
    }
}

/*
 *  �u�b�N�}�[�N�̃G�N�X�|�[�g(�擾)
 */

bool    CBookeyApp::ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2 )
{
    int     i;
    bool    cont = false;
    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        cont = m_userInfoList[i]->ExportFromAnother(
                                    bookmark1,      bookmark2,
                                    myBookmark1,    myBookmark2,
                                    numOfBookmark1, numOfBookmark2 );
        if ( cont == false )
            break;
    }

    if ( cont == false ) {
        if ( myBookmark1 && *myBookmark1 ) {
            free( *myBookmark1 );
            *myBookmark1 = NULL;
        }
        if ( myBookmark2 && *myBookmark2 ) {
            free( *myBookmark2 );
            *myBookmark2 = NULL;
        }
    }

    return ( cont );
}


/*
 *  �u�b�N�}�[�N�̍폜
 */

void    CBookeyApp::DeleteBookmarks(
            enum CUserInfo::bookmarkType bmType,
            bool                         deleteAll,
            bool                         deleteInteractive )
{
    CUserInfo   *u = UserInfo( bmType );

    if ( u )
        u->DeleteBookmarks( deleteAll, deleteInteractive );
}


/*
 *  �u�b�N�}�[�N�̓o�^
 */

void    CBookeyApp::PutBookmarks( const RBparam_t    *p,
                                  const char         *accountName,
                                  EditBookmarkDialog *editDlg,
                                  ProceedingDialog   *procDlg )
{
    MyClip  myBookmark;

    strcpy( myBookmark.url, (const char *)editDlg->m_url );
    if ( editDlg->m_title.GetLength() > 0 )
        strcpy( myBookmark.title, (const char *)(editDlg->m_title) );
    else
        strcpy( myBookmark.title, editDlg->m_url );
    if ( editDlg->m_comment.GetLength() > 0 )
        strcpy( myBookmark.comment, (const char *)(editDlg->m_comment) );
    else
        myBookmark.comment[0] = NUL;
    if ( editDlg->m_tags.GetLength() > 0 )
        strcpy( myBookmark.tags, (const char *)(editDlg->m_tags) );
    else
        myBookmark.tags[0] = NUL;

    time_t      t   = time( NULL );
    struct tm   *tm = gmtime( &t ); /* GMT */
    myBookmark.yyyy = tm->tm_year + 1900;
    myBookmark.mm   = tm->tm_mon  + 1;
    myBookmark.dd   = tm->tm_mday;
    myBookmark.HH   = tm->tm_hour;
    myBookmark.MM   = tm->tm_min;
    myBookmark.SS   = tm->tm_sec;

    myBookmark.evaluation  = editDlg->m_evaluation;
    myBookmark.rating      = editDlg->m_rating;
    myBookmark.affirmation = editDlg->m_affirmation;
    myBookmark.publication = editDlg->m_public;

    // �͂Ăȓ����K���M
    if ( editDlg->m_sendTipJar ) {
        char    cmd[BUFSIZ];
        sprintf( cmd, "https://www.hatena.ne.jp/sendpoint?name=%s",
                 accountName );
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }

    procDlg->ResetDialogText();
    procDlg->ShowWindow( SW_SHOWNORMAL );

    // ���[�J��OPML�t�@�C���ɓo�^
    if ( p->localOpml.isTarget && m_localOpml.m_opmlFilename[0] )
        m_localOpml.PutBookmarks( &myBookmark, procDlg );

    // �͂Ăȃu�b�N�}�[�N�ɓo�^
    if ( editDlg->m_param.hatena.isTarget && m_hatena.m_username[0] ) {
        myBookmark.asin = editDlg->m_registerCollection ? TRUE : FALSE;
        m_hatena.PutBookmarks( &myBookmark, procDlg );
    }

    // del.icio.us �ɓo�^
    if ( editDlg->m_param.delicious.isTarget && m_delicious.m_username[0] )
        m_delicious.PutBookmarks( &myBookmark, procDlg );

    // MM/Memo �ɓo�^
    if ( editDlg->m_param.mmMemo.isTarget && m_mmMemo.m_username[0] ) {
        loginMMmemo( NULL, NULL, NULL, NULL );  // �L���b�V�����N���A
        m_mmMemo.PutBookmarks( &myBookmark, procDlg );
    }

    // �h���R��RSS �ɓo�^
    if ( editDlg->m_param.drecomRss.isTarget && m_drecomRss.m_username[0] )
        m_drecomRss.PutBookmarks( &myBookmark, procDlg );

    // Flog �ɓo�^
    if ( editDlg->m_param.flog.isTarget && m_flog.m_username[0] )
        m_flog.PutBookmarks( &myBookmark, procDlg );

    // livedoor �N���b�v �ɓo�^
    if ( editDlg->m_param.livedoorClip.isTarget &&
         m_livedoorClip.m_username[0]              )
        m_livedoorClip.PutBookmarks( &myBookmark, procDlg );

    // Buzzurl �ɓo�^
    if ( editDlg->m_param.ecNaviClip.isTarget && m_ecNaviClip.m_username[0] )
        m_ecNaviClip.PutBookmarks( &myBookmark, procDlg );

    // �j�t�e�B�N���b�v �ɓo�^
    if ( editDlg->m_param.niftyClip.isTarget && m_niftyClip.m_username[0] )
        m_niftyClip.PutBookmarks( &myBookmark, procDlg );

    // 1470.net���j���[�A���� �ɓo�^
    if (editDlg->m_param.next1470net.isTarget && m_next1470net.m_username[0]) {
        login1470net( NULL, NULL, NULL, NULL, AK_ORIGINAL, NULL, NULL );
                                                        // �L���b�V�����N���A
        m_next1470net.PutBookmarks( &myBookmark, procDlg );
    }

    // newsing �ɓo�^
    if ( editDlg->m_param.newsing.isTarget          &&
         m_newsing.m_username[0]                    &&
         ((myBookmark.affirmation == AFF_GOOD) ||
          (myBookmark.affirmation == AFF_BAD)     )    )
        m_newsing.PutBookmarks( &myBookmark, procDlg );

    // pookmark �ɓo�^
    if ( editDlg->m_param.pookmark.isTarget && m_pookmark.m_username[0] )
        m_pookmark.PutBookmarks( &myBookmark, procDlg );

    // Blue Dot �ɓo�^
    if ( editDlg->m_param.blueDot.isTarget && m_blueDot.m_username[0] )
        m_blueDot.PutBookmarks( &myBookmark, procDlg );

    // JoltMark �ɓo�^
    if ( editDlg->m_param.joltMark.isTarget && m_joltMark.m_username[0] )
        m_joltMark.PutBookmarks( &myBookmark, procDlg );

    // FC2BOOKMARK �ɓo�^
    if (editDlg->m_param.fc2bookmark.isTarget && m_fc2bookmark.m_username[0])
        m_fc2bookmark.PutBookmarks( &myBookmark, procDlg );

    // BlogPet �C�ɂȂ�L�� �ɓo�^
    if ( editDlg->m_param.blogPet.isTarget && m_blogPet.m_username[0] )
        m_blogPet.PutBookmarks( &myBookmark, procDlg );

    // Yahoo! �u�b�N�}�[�N �ɓo�^
    if ( editDlg->m_param.yjBookmark.isTarget && m_yjBookmark.m_username[0] )
        m_yjBookmark.PutBookmarks( &myBookmark, procDlg );

    // Yahoo! Bookmarks �ɓo�^
    if ( editDlg->m_param.yahooBookmarks.isTarget &&
         m_yahooBookmarks.m_username[0]              )
        m_yahooBookmarks.PutBookmarks( &myBookmark, procDlg );

    // Twitter �Ŕ���
    if ( editDlg->m_param.twitter.isTarget && m_twitter.m_username[0] )
        m_twitter.PutBookmarks( &myBookmark, procDlg );

    // Timelog �Ŕ���
    if ( editDlg->m_param.timelog.isTarget && m_timelog.m_username[0] )
        m_timelog.PutBookmarks( &myBookmark, procDlg );

    // digg �ɓo�^
    if ( editDlg->m_param.digg.isTarget && m_digg.m_username[0] )
        m_digg.PutBookmarks( &myBookmark, procDlg );

    // tumblr �ɓo�^
    if ( editDlg->m_param.tumblr.isTarget && m_tumblr.m_username[0] )
        m_tumblr.PutBookmarks( &myBookmark, procDlg );

    // Diigo �ɓo�^
    if ( editDlg->m_param.diigo.isTarget && m_diigo.m_username[0] )
        m_diigo.PutBookmarks( &myBookmark, procDlg );
}

void    CBookeyApp::PutBookmarks(
            CString bookmarkName,
            CString username,
            CString password )
{
    CUserInfo   *orig = UserInfo( bookmarkName );
    if ( orig ) {
        orig->PutBookmarks( true,
                            m_myClip, m_numOfClips,
                            (const char *)username,
                            (const char *)password );
    }
}

bool    CBookeyApp::PutBookmarks(
            CString bookmarkNameAsExport,
            CString bookmarkNameAsImport )
{
    CUserInfo   uInfo;
    bool        result = false;
    CString     bookmarkName001;
    CString     bookmarkName002;
    CString     bookmarkName003;
    CString     bookmarkName004;
    CString     bookmarkName005;
    CString     bookmarkName006;

    bookmarkName001.LoadString( IDS_TGT_OPML );
	bookmarkName002.LoadString( IDS_TGT_NETSCAPE_1 );
	bookmarkName003.LoadString( IDS_TGT_OPERA_6 );
	bookmarkName004.LoadString( IDS_TGT_HATENA_FEED );
	bookmarkName005.LoadString( IDS_TGT_LIVEDOOR_FEED );
	bookmarkName006.LoadString( IDS_TGT_DELICIOUS_XML );

    if ( !bookmarkNameAsExport.Compare( bookmarkName001 ) )
        uInfo.Init( CUserInfo::BK_LOCAL_OPML );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName002 ) )
        uInfo.Init( CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1 );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName003 ) )
        uInfo.Init( CUserInfo::BK_OPERA6_ADR );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName004 ) )
        uInfo.Init( CUserInfo::BK_HATENA_BOOKMARK_ATOM );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName005 ) )
        uInfo.Init( CUserInfo::BK_LIVEDOOR_CLIP_RSS );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName006 ) )
        uInfo.Init( CUserInfo::BK_DELICIOUS_XML );
    else
        return ( result );

    uInfo.PutBookmarks(m_myClip, m_numOfClips, bookmarkNameAsImport, result);

    return ( result );
}


/*
 *  �u�b�N�}�[�N�̎擾
 */

void    CBookeyApp::GetBookmarks(
            CString bookmarkName,
            CString username,
            CString password )
{
    if ( m_myClip ) {
        free( m_myClip );
        m_myClip = NULL;
        m_bookmarkGotten = false;
        m_bookmarkName   = "";
    }

    CUserInfo   *u = UserInfo( bookmarkName );
    if ( u )
        m_myClip = u->GetBookmarks( m_numOfClips,
                                    (const char *)username,
                                    (const char *)password );

    if ( m_myClip ) {
        m_bookmarkGotten = true;
        m_bookmarkName   = bookmarkName;
    }
}

bool    CBookeyApp::GetBookmarks( CString bookmarkName )
{
    bool        ret = false;
    CUserInfo   uInfo;

    if ( m_myClip ) {
        free( m_myClip );
        m_myClip = NULL;
        m_bookmarkGotten = false;
        m_bookmarkName   = "";
    }

    CString bookmarkName001;
    CString bookmarkName002;
    CString bookmarkName003;
    CString bookmarkName004;
    CString bookmarkName005;
    CString bookmarkName006;

	bookmarkName001.LoadString( IDS_TGT_OPML );
	bookmarkName002.LoadString( IDS_TGT_NETSCAPE_1 );
	bookmarkName003.LoadString( IDS_TGT_OPERA_6 );
	bookmarkName004.LoadString( IDS_TGT_HATENA_FEED );
	bookmarkName005.LoadString( IDS_TGT_LIVEDOOR_FEED );
	bookmarkName006.LoadString( IDS_TGT_DELICIOUS_XML );

    if ( !bookmarkName.Compare( bookmarkName001 ) ) {
        uInfo.Init( CUserInfo::BK_LOCAL_OPML );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName002 ) ) {
        uInfo.Init( CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1 );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName003 ) ) {
        uInfo.Init( CUserInfo::BK_OPERA6_ADR );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName004 ) ) {
        uInfo.Init( CUserInfo::BK_HATENA_BOOKMARK_ATOM );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName005 ) ) {
        uInfo.Init( CUserInfo::BK_LIVEDOOR_CLIP_RSS );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName006 ) ) {
        uInfo.Init( CUserInfo::BK_DELICIOUS_XML );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }

    if ( m_myClip ) {
        m_bookmarkGotten = true;
        m_bookmarkName   = bookmarkName;
    }

    return ( ret );
}


/* �^�O�ꗗ�̎擾 */
TagList *CBookeyApp::GetTagList(
            enum CUserInfo::bookmarkType bmType,
            int                          &numOfTags )
{
    TagList     *p = NULL;
    CUserInfo   *u = UserInfo( bmType );

    numOfTags = 0;
    if ( u )
        p = u->GetTagList( numOfTags );

    return ( p );
}

/* �^�O�̍폜 */
void    CBookeyApp::DeleteTag(
            enum CUserInfo::bookmarkType bmType,
            const char                   *tag )
{
    CUserInfo   *u = UserInfo( bmType );

    if ( u )
        u->DeleteTag( tag );
}

/* �^�O�̒u�� */
void    CBookeyApp::ReplaceTag(
            enum CUserInfo::bookmarkType bmType,
            const char                   *oldTag,
            const char                   *newTag )
{
    CUserInfo   *u = UserInfo( bmType );

    if ( u )
        u->ReplaceTag( oldTag, newTag );
}


/* bookmarkName �ɑΉ����� CUserInfo �̎擾 */
CUserInfo   *CBookeyApp::UserInfo( CString bookmarkName, CUserInfo *userInfo )
{
    CUserInfo   *p = NULL;

    if ( !bookmarkName.Compare( *userInfo ) )
        p = userInfo;

    return ( p );
}

CUserInfo   *CBookeyApp::UserInfo( CString bookmarkName )
{
    CUserInfo   *p = NULL;
    int         i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        p = UserInfo( bookmarkName, m_userInfoList[i] );
        if ( p )
            break;
    }

    return ( p );
}

CUserInfo   *CBookeyApp::UserInfoEx( CString bookmarkName )
{
    CUserInfo   *p = UserInfo( bookmarkName );
    return ( p );
}

CUserInfo   *CBookeyApp::UserInfo( enum CUserInfo::bookmarkType bmType )
{
    CUserInfo   *p = NULL;

    switch ( bmType ) {
    case CUserInfo::BK_HATENA:
        p = &m_hatena;
        break;
    case CUserInfo::BK_DELICIOUS:
        p = &m_delicious;
        break;
    case CUserInfo::BK_MM_MEMO:
        p = &m_mmMemo;
        break;
    case CUserInfo::BK_DRECOM_RSS:
        p = &m_drecomRss;
        break;
    case CUserInfo::BK_FLOG:
        p = &m_flog;
        break;
    case CUserInfo::BK_LIVEDOOR_CLIP:
        p = &m_livedoorClip;
        break;
    case CUserInfo::BK_ECNAVI_CLIP:
        p = &m_ecNaviClip;
        break;
    case CUserInfo::BK_NIFTY_CLIP:
        p = &m_niftyClip;
        break;
    case CUserInfo::BK_1470NET:
        p = &m_next1470net;
        break;
    case CUserInfo::BK_NEWSING:
        p = &m_newsing;
        break;
    case CUserInfo::BK_POOKMARK:
        p = &m_pookmark;
        break;
    case CUserInfo::BK_BLUEDOT:
        p = &m_blueDot;
        break;
    case CUserInfo::BK_JOLTMARK:
        p = &m_joltMark;
        break;
    case CUserInfo::BK_FC2BOOKMARK:
        p = &m_fc2bookmark;
        break;
    case CUserInfo::BK_BLOGPET:
        p = &m_blogPet;
        break;
    case CUserInfo::BK_TWITTER:
        p = &m_twitter;
        break;
    case CUserInfo::BK_YJ_BOOKMARK:
        p = &m_yjBookmark;
        break;
    case CUserInfo::BK_YAHOO_BOOKMARKS:
        p = &m_yahooBookmarks;
        break;
    case CUserInfo::BK_TIMELOG:
        p = &m_timelog;
        break;
    case CUserInfo::BK_DIGG:
        p = &m_digg;
        break;
    case CUserInfo::BK_TUMBLR:
        p = &m_tumblr;
        break;
    case CUserInfo::BK_DIIGO:
        p = &m_diigo;
        break;
    case CUserInfo::BK_LOCAL_OPML:
        p = &m_localOpml;
        break;
    }

    return ( p );
}

/* proxy���t�@�C���̐��� (for BBAuth) */
#define FILE_CONFIG_PROXY   "proxy.txt" // proxy�T�[�o���ݒ�t�@�C��

void
CBookeyApp::MakeProxyText()
{
    if ( m_useProxy ) {
        char    filename[MAX_PATH];

        if ( __argv && __argv[0] && __argv[0][0] ) {
            char    *p;

            strcpy( filename, __argv[0] );
            p = strrchr( filename, '\\' );
            if ( p )
                *p = NUL;
            else {
                p = strrchr( filename, '/' );
                if ( p )
                    *p = NUL;
            }
            strcat( filename, "/" );
        }
        else
            strcpy( filename, "./" );
        strcat( filename, FILE_CONFIG_PROXY );

        FILE    *fp = fopen( filename, "w" );
        if ( fp ) {
            fprintf( fp, "%s\n", m_proxyServer );
            fprintf( fp, "%d\n", m_proxyPort );

            if ( m_proxyUsername.GetLength() > 0 ) {
                fprintf( fp, "%s\n", (const char *)m_proxyUsername );

                if ( m_proxyPassword.GetLength() > 0 )
                    fprintf( fp, "%s\n", (const char *)m_proxyPassword );
            }

            fclose( fp );
        }
    }
}

/*
 *  �����ݒ�t�@�C���֘A
 */

bool    CBookeyApp::EvalKeys(
            const char          *p,
            const unsigned char *rsaString )
{
    int     i;
    bool    cont = false;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        if ( m_userInfoList[i]->EvalKeys( p, rsaString ) ) {
            cont = true;
            break;
        }
    }

    return ( cont );
}

bool    CBookeyApp::CheckKeys(
            const char          *p,
            const unsigned char *rsaString,
            bool                &ret )
{
    int     i;
    bool    cont = false;
    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        if ( m_userInfoList[i]->CheckKeys( p, rsaString, ret ) ) {
            cont = true;
            break;
        }
    }

    return ( cont );
}

void    CBookeyApp::WriteKeys(
            FILE          *fp,      // (I/O) �����o����
            char          *key,     // (I)   ���J��
            unsigned char **secret, // (I/O) �����ɕK�v�ȏ��(�閧��)
            bool          &done )   // (O)   �Í����������s�ς݂��ۂ�
{
    int i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ )
        m_userInfoList[i]->WriteKeys( fp, key, secret, done );
}

/* for Visual C++ 2005 runtime */
bool    CBookeyApp::ResetDayLightSaving()
{
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    bool        ret = false;

    if ( tm->tm_isdst == 1 ) {
        char    *p = _tzname[0];
        if ( !strcmp( p, "JST" ) ) {
            /* �Ȃ������{���Ԃł���ɂ��ւ�炸�A�Ď��ԂɂȂ��Ă���ꍇ */
            long l = _daylight;

            if ( l == 1 ) {
                // ���ϐ� TZ ��ݒ肵�Ă���ꍇ�́A(Visual Studio 2005 ��)
                // �uC �����^�C�� ���C�u�����́A�Ď��� (DST: Daylight Saving
                // Time) �v�Z�̎����ɂ��Ă͕č��̋K����O��Ƃ��Ă��܂��v��
                // �������ƂŁA����ɉĎ��Ԃɂ���Ă��܂��炵��
                // ���{���Ԃɂ�(���Ȃ��Ƃ������_�ł�)�Ď��Ԃ͂Ȃ��̂Ɂc�c
                _daylight = 0;
                tm = localtime( &t );
            }
            else {
                tm->tm_isdst = 0;
                tm->tm_hour--;
                        // tm_hour �����̒l�ɂȂ����ꍇ�́A�����I�ɑO���ɂȂ�
            }

            ret = true;
        }
        // �Ƃ肠�����A���{���Ԃ̂ݍl���������A�{���́A���̉Ď��Ԗ��������E
        // �n���A�����J�ƉĎ��Ԃ̊J�n�E�I���������قȂ鍑�E�n��ɑ΂���z
        // �����K�v
        // �Ȃ��AVisual C++ 6 �̃����^�C���ł́ATZ=JST-9 �Ɛݒ肵�Ă���ꍇ
        // �ł��A���{���Ԃ��Ď��Ԃ���Ɣ��肳��Ă��܂��悤�Ȃ��Ƃ͂Ȃ��B��
        // ���܂ł� Visual C++ 2005 �̃����^�C���̖��ł���(Visual C++.NET
        // 2002/2003 �Ɋւ��Ă͖��m�F)
    }

    return ( ret );
}

/* ���̑� */
bool
CBookeyApp::SetSigInfo( CString &sKey,    CString &sSecret,
                        const char *sig1, const char *sig2 )
{
    char    key[BUFSIZ];
    char    secret[BUFSIZ];
    BOOL    ret;

    ret = setSigInfo( key, secret, sig1, sig2, "-ts", "ey-" );
    if ( ret ) {
        sKey    = key;
        sSecret = secret;
    }

    return ( ret ? true : false );
}

#ifdef __cplusplus
extern "C" {
#endif
char    *
TwitterOAuthConsumerKey()
{
    static char tcKey[MAX_KEYLENGTH + 1];

    if ( tcKey[0] == NUL ) {
        CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
        strcpy( tcKey, bp->m_tcKey );
    }

    return ( tcKey );
}

char    *
TwitterOAuthConsumerSecret()
{
    static char tcSecret[MAX_KEYLENGTH + 1];

    if ( tcSecret[0] == NUL ) {
        CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
        strcpy( tcSecret, bp->m_tcSecret );
    }

    return ( tcSecret );
}
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp ���b�Z�[�W �n���h��

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBookeyApp::WinHelp(DWORD dwData, UINT nCmd) 
{
 // CWinApp::WinHelp(dwData, nCmd);
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

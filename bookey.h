/*
 * bookey.h : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �A�v���P�[�V���� ���C�� �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookey.h $
 * 
 * 2     09/06/22 22:31 tsupo
 * 0.63c��
 * 
 * 71    09/06/22 17:56 Tsujimura543
 * ���{�ꃂ�[�h�����p�ꃂ�[�h�ؑ֊֘A�A�C��
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 70    09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 69    08/10/21 22:05 Tsujimura543
 * �u�w���v�v���j���[�Ɂu�T�|�[�g�v(2��)�A�u�R�~���j�e�B�v(2��)��ǉ�
 * 
 * 68    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 67    08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 66    08/05/07 19:17 Tsujimura543
 * MAX_NUM_OF_USERINFO �̒l���C��
 * (�܂��A���[�J��OPML�̐ݒ肪�ۑ��ł��Ȃ��s����������Ă���
 *  [tumblr �Ή����̏C���R��])
 * 
 * 65    07/10/31 16:58 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 64    07/10/17 23:09 Tsujimura543
 * �]���ȃv���v���Z�b�T���䕶���폜
 * 
 * 63    07/10/05 2:42 Tsujimura543
 * BBAuth �Ή��֘A�̊e��C�������{
 * 
 * 62    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 61    07/09/04 22:43 Tsujimura543
 * m_verboseFp �𓱓�
 * 
 * 60    07/09/04 22:38 Tsujimura543
 * BOOKEY_LOG_FILE ��ǉ�
 * 
 * 59    07/09/04 22:30 Tsujimura543
 * m_verbose �𓱓�
 * 
 * 58    07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 57    07/06/06 22:14 Tsujimura543
 * MAX_NUM_OF_USERINFO �̒l���C��
 * (���[�J��OPML�̐ݒ肪�ۑ��ł��Ȃ��s����������Ă���)
 * 
 * 56    07/05/25 23:02 Tsujimura543
 * MS_THREAD_REGISTERBOOKMARK �̒l�� 500 ���� 400 �ɕύX���Ă݂�
 * 
 * 55    07/05/23 16:11 Tsujimura543
 * Timelog �ւ̓o�^(����)�ɑΉ�
 * 
 * 54    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 53    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 52    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 51    07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 50    07/03/14 17:52 Tsujimura543
 * m_proxyPort �̌^�� int ���� long �ɕύX
 * 
 * 49    07/03/14 17:07 Tsujimura543
 * (1) StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * (2) proxy�֘A�̂������̏C���A�ǉ� (BloGolEe �̐��ʂ���荞��)
 * 
 * 48    07/02/16 16:35 Tsujimura543
 * �R�����g���C��
 * 
 * 47    07/01/29 23:59 Tsujimura543
 * UserInfo() ���C��
 * 
 * 46    07/01/29 17:51 Tsujimura543
 * �^�O�ꗗ�̎擾�A�^�O�̍폜�A�^�O�̒u���̊e������ǉ�
 * 
 * 45    07/01/13 1:42 Tsujimura543
 * CBookeyApp::CBookeyApp() �̒����� CString#LoadString() �����
 * assertion failed ���邱�Ƃ������B�΍�����{ (�p�ꃂ�[�h�Ή��ɂ�������
 * ����������Q)
 * 
 * 44    07/01/12 13:21 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 43    06/12/27 11:47 Tsujimura543
 * RBparam �\���̂̒�`�� bookey.h ���番���Ɨ������� RBparam.h �Ƃ���
 * 
 * 42    06/12/22 21:41 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�Ή�
 * 
 * 41    06/12/21 19:13 Tsujimura543
 * (1) JoltMark �ɑΉ�
 * (2) FC2BOOKMARK�A�uBlogPet �C�ɂȂ�L���v�Ή�����
 * 
 * 40    06/11/16 16:43 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��16�i�K�A�I��
 * 
 * 39    06/11/16 14:02 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��15�i�K�A�I��
 * 
 * 38    06/10/28 1:14 Tsujimura543
 * �u���[�J��OPML�v�֓o�^�ł��Ȃ����Ƃ�����s��ɑΏ�
 * 
 * 37    06/10/26 22:54 Tsujimura543
 * �u���[�J��OPML�v�ɑΉ�
 * 
 * 36    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 35    06/10/04 21:11 Tsujimura543
 * POOKMARK Airline �� POOKMARK Airlines �ɏC��
 * 
 * 34    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline �ɑΉ�
 * 
 * 33    06/09/29 23:49 Tsujimura543
 * newsing �ɑΉ�
 * 
 * 32    06/09/05 11:14 Tsujimura543
 * Visual C++ 2005 �Ńr���h����ꍇ�ɔ����āAResetDayLightSaving()
 * ��ǉ� (���݃����[�X���Ă��� bookey �� Visual C++ 6 �ɂăr���h����
 * ����)
 * 
 * 31    06/08/22 17:48 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 30    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 29    06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 28    06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 * 
 * 27    06/07/14 20:50 Tsujimura543
 * 1470.net���j���[�A���łɑΉ�
 * 
 * 26    06/07/05 18:19 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��13�i�K�A�I��
 * 
 * 25    06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 24    06/07/03 23:37 Tsujimura543
 * ProceedingDialog �� DestroyWindow() ���ɗ�O���������邱�Ƃ����錏��
 * �b��Ώ������{ (�f�o�b�O�łł����������Ȃ�?)
 * 
 * 23    06/06/29 18:46 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 22    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 21    06/06/28 15:54 Tsujimura543
 * �u�b�N�}�[�N�o�^�Ґ��𒲂ׂĕ\������@�\��ǉ�
 * 
 * 20    06/06/22 21:21 Tsujimura543
 * inquery �� inquiry �ɏC��(�Ԃ�~�X)
 * 
 * 19    06/06/21 21:14 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��11�i�K�A�I��
 * 
 * 18    06/06/20 14:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��9�i�K�A�I��
 * 
 * 17    06/06/19 20:25 Tsujimura543
 * getBPhash() �̃v���g�^�C�v�錾�� bookey.h ���� myClip.h �ֈڂ�
 * 
 * 16    06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 15    06/06/14 12:06 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��6�i�K�A�I��
 * 
 * 14    06/06/14 11:44 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��5�i�K�A�I��
 * 
 * 13    06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 12    06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 11    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 10    06/05/08 14:33 Tsujimura543
 * F1�L�[�������Ɂu�󋵈ˑ��w���v�v��\�����悤�Ƃ���̂�}������悤�ɂ�
 * ��
 * 
 * 9     05/11/10 21:20 Tsujimura543
 * (1) �i�s�󋵕\���_�C�A���O�̏����p�ɒǉ������ϐ��A�������폜
 * (2) ��L�ɔ����A�C�x���g���u��d�N���`�F�b�N�v�p�r��p�ɕύX
 * 
 * 8     05/11/10 14:13 Tsujimura543
 * m_proceedTitle ��ǉ�
 * 
 * 7     05/11/10 13:58 Tsujimura543
 * �i�s�󋵕\���_�C�A���O�Ή������Ƃ��āA�C�x���g�𓱓�
 * 
 * 6     05/11/10 12:06 Tsujimura543
 * �h�L�������g�e���v���[�g�֘A�̏������R�����g�A�E�g�����B����Ń��W�X�g
 * ����m��Ȃ��Ԃɏ��������Ă��܂��\�����r���ł����͂��B
 * 
 * 5     05/10/14 13:11 Tsujimura543
 * �ʓr�쐬�����h���b�O�E�A���h�E�h���b�v�Ή������v���O�����̐��ʂ���荞
 * ��
 * 
 * 4     05/10/14 11:07 Tsujimura543
 * 0.02 �� (�h���b�O�E�A���h�E�h���b�v���Ή���)
 * 
 * 3     05/10/11 17:04 Tsujimura543
 * ���ł̃^�C���X�^���v�\�L�~�X���C�� (�R�����g�݂̂̏C���B����ɉe���Ȃ�)
 * 
 * 2     05/09/30 23:57 Tsujimura543
 * �u�b�N�}�[�N�̎擾�A�o�^�@�\�̓���m�F����
 */

#if !defined(AFX_BOOKEY_H__958A686C_2250_4067_BFE4_13EA86CC7F61__INCLUDED_)
#define AFX_BOOKEY_H__958A686C_2250_4067_BFE4_13EA86CC7F61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__

#define VC_EXTRALEAN        // Windows �w�b�_�[����w�ǎg�p����Ȃ��X�^�b�t�����O���܂��B

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������
#include <afxdisp.h>        // MFC �̃I�[�g���[�V���� �N���X
#include <afxdtctl.h>       // MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif  // _AFX_NO_AFXCMN_SUPPORT
#endif  // !__AFXWIN_H__

#include <afxole.h>
#include <afxmt.h>
#include "resource.h"		// ���C�� �V���{��
#include "UserInfo.h"
#include "RBparam.h"
#include "EditBookmarkDialog.h"

// �u�b�N�}�[�N�o�^�X���b�h�ɓn���p�����[�^�i�[�p�\����
#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#include "encryptRSA.h"
#ifdef __cplusplus
}
#endif

// �e��ݒ�
#define BOOKEY_INF_FILE     "bookey.inf"    // �ݒ�t�@�C��
#define BOOKEY_DEFAULT_OPML "bookey.opml"   // ���[�J��OPML�t�@�C����(default)
#define BOOKEY_LOG_FILE     "bookey.log"    // �����p���O�t�@�C��
#define ID_THREAD_REGISTERBOOKMARK  0xCAFEBEAF
#define MS_THREAD_REGISTERBOOKMARK  400

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp   �A�v���P�[�V���� ���C��

class CBookeyApp : public CWinApp
{
public:
	CBookeyApp();

    ~CBookeyApp()
    {
        if ( m_proceed )
            delete m_proceed;
        if ( m_myClip ) {
            free( m_myClip );
            m_myClip = NULL;
            m_bookmarkGotten = false;
        }
    }

#define MAX_NUM_OF_USERINFO 23
    CUserInfo   m_hatena;           // [0]  �͂Ăȃu�b�N�}�[�N
    CUserInfo   m_delicious;        // [1]  del.icio.us
    CUserInfo   m_mmMemo;           // [2]  MM/memo
    CUserInfo   m_drecomRss;        // [3]  �h���R��RSS
    CUserInfo   m_flog;             // [4]  Flog
    CUserInfo   m_livedoorClip;     // [5]  livedoor �N���b�v
    CUserInfo   m_ecNaviClip;       // [6]  Buzzurl
    CUserInfo   m_niftyClip;        // [7]  �j�t�e�B�N���b�v
    CUserInfo   m_next1470net;      // [8]  1470.net���j���[�A����
    CUserInfo   m_newsing;          // [9]  newsing
    CUserInfo   m_pookmark;         // [10] POOKMARK Airlines
    CUserInfo   m_blueDot;          // [11] Blue Dot
    CUserInfo   m_joltMark;         // [12] JoltMark
    CUserInfo   m_fc2bookmark;      // [13] FC2BOOKMARK
    CUserInfo   m_blogPet;          // [14] BlogPet �C�ɂȂ�L��
    CUserInfo   m_twitter;          // [15] Twitter
    CUserInfo   m_yjBookmark;       // [16] Yahoo! Japan �u�b�N�}�[�N
    CUserInfo   m_yahooBookmarks;   // [17] Yahoo! Bookmarks
    CUserInfo   m_timelog;          // [18] Timelog
    CUserInfo   m_digg;             // [19] digg
    CUserInfo   m_tumblr;           // [20] tumblr
    CUserInfo   m_diigo;            // [21] Blue Dot
    CUserInfo   m_localOpml;        // [22] ���[�J��OPML�t�@�C��

    CUserInfo   *m_userInfoList[MAX_NUM_OF_USERINFO];

    bool        m_bookmarkGotten;   // �u�b�N�}�[�N���擾�ς݂��ۂ�

    volatile enum proxyType {
        autoDetect,     // proxy �g�p�󋵎����擾 (default)
        manualSetting,  // proxy �g�p�󋵎蓮�ݒ�A�ݒ�t�@�C������擾
        specialSetting, // proxy �g�p�󋵎蓮�ݒ�(���[�U���g�ɂ���Đݒ�ς�)
        notUsed         // proxy �͎g�p���Ȃ�    (���[�U���g�ɂ���Đݒ�ς�)
    }           m_proxyType;        // proxy �g�p�󋵎擾���@
    bool        m_useProxy;         // proxy ���g�����ۂ�
    CString     m_proxyServer;      // proxy�T�[�o URL (�܂��� IP�A�h���X)
    long        m_proxyPort;        // proxy�T�[�o �|�[�g�ԍ�
    CString     m_proxyUsername;    // proxy�T�[�o ���[�U��   (�K�v�ȏꍇ)
    CString     m_proxyPassword;    // proxy�T�[�o �p�X���[�h (�K�v�ȏꍇ)

    MyClip      *m_myClip;          // (�擾����)�u�b�N�}�[�N���
    int         m_numOfClips;       // �u�b�N�}�[�N���Ɋi�[����Ă���
                                    // �u�b�N�}�[�N�̐�
    CString     m_bookmarkName;     // �u�b�N�}�[�N���Ɋi�[����Ă���
                                    // �u�b�N�}�[�N�̃T�[�r�X��
    bool        m_verbose;          // ���O���o�͂��邩�ۂ�
    FILE        *m_verboseFp;       // �����p���O�t�@�C���̃t�@�C���|�C���^

    CString     m_tcKey;
    CString     m_tcSecret;

    /* �u�b�N�}�[�N�o�^�@�\���g���������ł��Ă��邩�ۂ� */
    bool    IsReady() {
        bool    ret = true;

        if ( (m_hatena         == false) &&
             (m_delicious      == false) &&
             (m_mmMemo         == false) &&
             (m_drecomRss      == false) &&
             (m_flog           == false) &&
             (m_livedoorClip   == false) &&
             (m_ecNaviClip     == false) &&
             (m_niftyClip      == false) &&
             (m_next1470net    == false) &&
             (m_newsing        == false) &&
             (m_pookmark       == false) &&
             (m_blueDot        == false) &&
             (m_joltMark       == false) &&
             (m_fc2bookmark    == false) &&
             (m_blogPet        == false) &&
             (m_twitter        == false) &&
             (m_yjBookmark     == false) &&
             (m_yahooBookmarks == false) &&
             (m_timelog        == false) &&
             (m_digg           == false) &&
             (m_tumblr         == false) &&
             (m_diigo          == false) &&
             (m_localOpml      == false)    )
            ret = false;

        return ( ret );
    }

    // ������ (InitInstance() ����Ăяo���Ȃ��������AInitInstance()
    // �ɑ����ČĂяo��)
    void    Initialize();
    void    ReInitialize();

    /* �Đݒ� */
    void    ResetUserInfo( bool &needToSave );
    void    ResetUserInfo( bool &needToSave, RBparam_t &param );

    /* ���[�U���\�� */
    void    SetWindowText( CString bookmarkName,
                           CString &username,
                           CString &password,
                           CEdit   *editUsername,
                           CEdit   *editPassword,
                           CButton *executeButton,
                           CString txt );
    void    SetWindowText( CString bookmarkName,
                           CString &username,
                           CString &password,
                           CEdit   *editUsername,
                           CEdit   *editPassword );
    void    SetWindowText( CString bookmarkName,
                           CString &username,
                           CEdit   *editUsername,
                           CEdit   *editPassword );

    /* �₢���킹 */
    bool    InquiryUserInfo( CString bookmark1, CString bookmark2,
                             CString txt);

    /* �u�b�N�}�[�N�̃C���|�[�g */
    void    ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction );

    /* �u�b�N�}�[�N�̃G�N�X�|�[�g */
    bool    ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2 );

    /* �u�b�N�}�[�N�̍폜 */
    void    DeleteBookmarks(
                enum CUserInfo::bookmarkType targetBookmark,
                bool                         deleteAll,
                bool                         deleteInteractive );

    /* �u�b�N�}�[�N�̓o�^ */
    void    PutBookmarks( const RBparam_t    *p,
                          const char         *accountName,
                          EditBookmarkDialog *editDlg,
                          ProceedingDialog   *procDlg );
    void    PutBookmarks( CString bookmarkName,
                          CString username,
                          CString password );
    bool    PutBookmarks( CString bookmarkNameAsExport,
                          CString bookmarkNameAsImport );

    /* �u�b�N�}�[�N�̎擾 */
    void    GetBookmarks( CString bookmarkName,
                          CString username,
                          CString password );
    bool    GetBookmarks( CString bookmarkName );

    /* �^�O�ꗗ�̎擾 */
    TagList *GetTagList( enum CUserInfo::bookmarkType bmType,
                         int                          &numOfTags );

    /* �^�O�̍폜 */
    void    DeleteTag( enum CUserInfo::bookmarkType bmType,
                       const char                   *tag );

    /* �^�O�̒u�� */
    void    ReplaceTag( enum CUserInfo::bookmarkType bmType,
                        const char                   *oldTag,
                        const char                   *newTag );

    /* proxy���t�@�C���̐��� (for BBAuth) */
    void    MakeProxyText();


    /* �����ݒ�t�@�C���֘A */
    bool    EvalKeys(
                const char          *p,      // (I) �ݒ�f�[�^�擾�Ώە�����
                const unsigned char *secret);// (I) �����ɕK�v�ȏ��(�閧��)
    bool    CheckKeys(
                const char          *p,      // (I) �ݒ�f�[�^�擾�Ώە�����
                const unsigned char *secret, // (I) �����ɕK�v�ȏ��(�閧��)
                bool                &ret );  // (O) �����ۏ؉�
    void    WriteKeys(
                FILE          *fp,      // (I/O) �����o����
                char          *key,     // (I)   ���J��
                unsigned char **secret, // (I/O) �����ɕK�v�ȏ��(�閧��)
                bool          &done );  // (O)   �Í����������s�ς݂��ۂ�

    /* bookmarkName �ɑΉ����� CUserInfo �̎擾 */
    CUserInfo   *UserInfo( CString bookmarkName, CUserInfo *userInfo );
    CUserInfo   *UserInfo( CString bookmarkName );
    CUserInfo   *UserInfo( enum CUserInfo::bookmarkType bmType );
    CUserInfo   *UserInfoEx( CString bookmarkName );

    /* (���{���ԂɊւ���)�Ď��ԃt���O���Z�b�g */
    bool    ResetDayLightSaving();      // for Visual Studio 2005 runtime

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CBookeyApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
#define BOOKEY_EVENT_PROCEED "__bookey_958A686C_2250_4067_BFE4_13EA86CC7F61__"
    CEvent  *m_proceed; // ��d�N���`�F�b�N�p
    LCID    m_langCode; // ����(0x0409: �p��(�A�����J), 0x0411: ���{��, �c�c)

	//{{AFX_MSG(CBookeyApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppSupport();
	afx_msg void OnAppSupport2();
	afx_msg void OnAppCommunity();
	afx_msg void OnAppCommunity2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CBookeyApp( CBookeyApp &obj );
    CBookeyApp  operator = ( CBookeyApp &obj );

    /* ���̑� */
    bool    SetSigInfo( CString &sKey,    CString &sSecret,
                        const char *sig1, const char *sig2 );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEY_H__958A686C_2250_4067_BFE4_13EA86CC7F61__INCLUDED_)

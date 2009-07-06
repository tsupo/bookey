/*
 * SettingDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingDialog �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingDialog.h $
 * 
 * 2     09/07/07 2:15 tsupo
 * 0.63c��
 * 
 * 24    09/06/22 18:04 Tsujimura543
 * �^�u�̈ʒu�����(���E��)����E��(�c�E��)�ɕύX
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 23    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 22    08/07/25 17:39 Tsujimura543
 * Diigo �ɑΉ�
 * 
 * 21    08/02/27 1:11 Tsujimura543
 * m_dialogWidth ��ǉ�
 * 
 * 20    08/02/20 23:21 Tsujimura543
 * �f�B�X�v���C�̏c�����̑傫��(����)�� 720px �ȉ��̏ꍇ�́A�\������
 * �_�C�A���O�̑傫�����c�����ɏ���������悤�ɂ��Ă݂�
 * 
 * 19    07/10/31 16:58 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 18    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 17    07/07/09 19:15 Tsujimura543
 * digg �ɑΉ�
 * 
 * 16    07/06/07 1:06 Tsujimura543
 * �R�����g���C��
 * 
 * 15    07/05/23 16:01 Tsujimura543
 * Timelog �ɑΉ�
 * 
 * 14    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 13    07/04/16 20:45 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �Ή�
 * 
 * 12    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 11    07/03/30 16:12 Tsujimura543
 * FC2BOOKMARK �ɑΉ�
 * 
 * 10    06/12/22 22:33 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�Ή�
 * 
 * 9     06/12/21 16:37 Tsujimura543
 * JoltMark �Ή�
 * 
 * 8     06/10/26 21:01 Tsujimura543
 * �u���[�J��OPML�t�@�C���v�ɑΉ�
 * 
 * 7     06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 6     06/10/04 20:24 Tsujimura543
 * pookmark �Ή�
 * 
 * 5     06/09/29 18:44 Tsujimura543
 * newsing �Ή�
 * 
 * 4     06/08/23 21:35 Tsujimura543
 * �u1470.net���j���[�A���ł̃��[�U��񖢐ݒ�̂܂܁A�폜�����s���悤�Ƃ�
 * ���Ƃ��v�̃��[�U���ݒ�p�_�C�A���O�\��������������
 * 
 * 3     06/07/28 23:58 Tsujimura543
 * �f�[�^�̐��������`�F�b�N���鏈����ǉ�
 * 
 * 2     06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 */

#if !defined(AFX_SETTINGDIALOG_H__5FD2347F_366A_42E4_AFD9_5E5B9F98840A__INCLUDED_)
#define AFX_SETTINGDIALOG_H__5FD2347F_366A_42E4_AFD9_5E5B9F98840A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SettingHatena.h"
#include "SettingDelicious.h"
#include "SettingMMmemo.h"
#include "SettingDrecom.h"
#include "SettingFlog.h"
#include "SettingLivedoor.h"
#include "SettingEcNavi.h"
#include "SettingNifty.h"
#include "Setting1470net.h"
#include "SettingNewsing.h"
#include "SettingPookmark.h"
#include "SettingBlueDot.h"
#include "SettingJoltMark.h"
#include "SettingBlogPet.h"
#include "SettingFC2bookmark.h"
#include "SettingTwitter.h"
#include "SettingYJbookmark.h"
#include "SettingYahooBookmarks.h"
#include "SettingTimelog.h"
#include "SettingDigg.h"
#include "SettingTumblr.h"
#include "SettingDiigo.h"
#include "SettingLocalOpml.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDialog �_�C�A���O

class SettingDialog : public CDialog
{
// �R���X�g���N�V����
public:
	SettingDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingDialog)
	enum { IDD = IDD_SETTING_DIALOG };
	CTabCtrl	m_tabSetting;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingDialog)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
#define NUM_OF_TABS     23                  // �^�u�̑���
    int                 m_numOfTabs;        // �^�u�̑���

    CDialog             *m_dlg[NUM_OF_TABS];// �e�^�u�ɓ\��t���Ă���_�C�A���O
    int                 m_activePage;       // �I������Ă���^�u
    bool                m_1470net;          // for 1470.net���j���[�A����

    // �_�C�A���O����
    SettingHatena           m_dlg00;
    SettingDelicious        m_dlg01;
    SettingMMmemo           m_dlg02;
    SettingDrecom           m_dlg03;
    SettingFlog             m_dlg04;
    SettingLivedoor         m_dlg05;
    SettingEcNavi           m_dlg06;
    SettingNifty            m_dlg07;
    Setting1470net          m_dlg08;
    SettingNewsing          m_dlg09;
    SettingPookmark         m_dlg10;
    SettingBlueDot          m_dlg11;
    SettingJoltMark         m_dlg12;
    SettingBlogPet          m_dlg13;
    SettingFC2bookmark      m_dlg14;
    SettingTwitter          m_dlg15;
    SettingYJbookmark       m_dlg16;
    SettingYahooBookmarks   m_dlg17;
    SettingTimelog          m_dlg18;
    SettingDigg             m_dlg19;
    SettingTumblr           m_dlg20;
    SettingDiigo            m_dlg21;
    SettingLocalOpml        m_dlg22;

    // �^�u�؂�ւ�
    int     DispCurrentTab( int activeTab = 0 );

protected:
    // �f�[�^�̐������`�F�b�N
    BOOL    CheckDlgData();

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingDialog)
	afx_msg void OnButtonAccept();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDialog( SettingDialog &dlg );
    SettingDialog   operator = ( SettingDialog &dlg );

 // int     m_width;
 // int     m_height;
    int     m_base;
    int     m_dialogWidth;
    bool    m_resized;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIALOG_H__5FD2347F_366A_42E4_AFD9_5E5B9F98840A__INCLUDED_)

/*
 * bookeyDlg.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      ���C���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookeyDlg.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 35    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 34    08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 33    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 32    07/04/20 20:34 Tsujimura543
 * Yahoo! �u�b�N�}�[�N�AYahoo! Bookmarks �̃C���|�[�g�ƃG�N�X�|�[�g�ɑΉ�
 * 
 * 31    07/04/16 18:23 Tsujimura543
 * �R�����g���C��
 * 
 * 30    07/04/16 17:59 Tsujimura543
 * del.icio.us �� posts/all �`���� XML �t�@�C���̃C���|�[�g�ƃG�N�X�|�[�g
 * �ɑΉ�����
 * 
 * 29    07/03/29 15:18 Tsujimura543
 * FC2BOOKMARK �ɑΉ�����
 * 
 * 28    07/01/24 20:55 Tsujimura543
 * �u�^�O�̍폜�v�Ɓu�^�O�̒u���v�{�^�����e�X�ǉ�
 * 
 * 27    07/01/12 23:34 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 26    06/11/16 16:43 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��16�i�K�A�I��
 * 
 * 25    06/11/16 14:06 Tsujimura543
 * CBookeyDlg �N���X���̃����o�ϐ��̂����A���͂�s�v�ɂȂ������̂��폜
 * 
 * 24    06/11/16 14:02 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��15�i�K�A�I��
 * 
 * 23    06/11/10 19:26 Tsujimura543
 * �u���E�U�̃u�b�N�}�[�N����荞��/�u���E�U�Ɏ�荞�߂�`���̃u�b�N�}�[�N
 * �t�@�C���𐶐�����@�\���T�|�[�g���邽�߂̏���
 * 
 * 22    06/08/23 22:10 Tsujimura543
 * 1470.net���j���[�A���ł́u�폜�v���Ƀ��[�U����ݒ肵���ꍇ�A
 * ���̐ݒ���e�������ݒ�t�@�C���ɔ��f�ł���悤�ɂ���
 * 
 * 21    06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 20    06/06/15 12:51 Tsujimura543
 * EnableButton() ��ǉ�
 * 
 * 19    06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 18    06/06/06 22:23 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��
 * 
 * 17    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 16    06/06/01 20:28 Tsujimura543
 * CBookeyDlg ���̃��[�U���A�p�X���[�h�� CUserInfo ���g���ĊǗ�����
 * �悤�ɕύX����
 * 
 * 15    06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 14    06/03/29 18:30 Tsujimura543
 * �h���R��RSS�ւ̃u�b�N�}�[�N(Clip)�o�^�ɑΉ�����
 * 
 * 13    06/02/17 18:11 Tsujimura543
 * ImportFromAnotherToMMmemo() �� ImportFromAnotherToBPtags() ��ǉ�
 * 
 * 12    06/02/17 18:07 Tsujimura543
 * �u�b�N�}�[�N�̓������A�͂Ăȃu�b�N�}�[�N��del.icio.us�ȊO�ɂ��e�ՂɑΉ�
 * �\�ɂ��邽�߁A�����̒��ۉ���i�߂�
 * 
 * 11    05/11/10 22:25 Tsujimura543
 * �i�s�󋵕\���_�C�A���O���g���悤�ɂ���
 * 
 * 10    05/10/28 14:45 Tsujimura543
 * DeleteBlogPeopleTags(), DeleteMMmemoBookmark() ��ǉ�
 * 
 * 9     05/10/21 18:57 Tsujimura543
 * MM/Memo �� BlogPeople �̃��[�U���A�p�X���[�h�� bookeyView ����
 * �󂯎���悤�ɂ���
 * 
 * 8     05/10/15 0:41 Tsujimura543
 * �͂ĂȂ�del.icio.us�̃��[�U���A�p�X���[�h�� bookeyView ����󂯎���
 * �悤�ɂ���
 * 
 * 7     05/10/11 19:07 Tsujimura543
 * �u�b�N�}�[�N�����@�\������ (����m�F�ς�)
 * 
 * 6     05/10/11 16:56 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 * 
 * 5     05/10/03 22:59 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N���폜���鏈��������
 * 
 * 4     05/10/03 22:17 Tsujimura543
 * del.icio.us �̃u�b�N�}�[�N���폜���鏈��������
 * 
 * 3     05/10/03 21:02 Tsujimura543
 * �u�b�N�}�[�N�폜�����̎����J�n
 * 
 * 2     05/09/30 23:57 Tsujimura543
 * �u�b�N�}�[�N�̎擾�A�o�^�@�\�̓���m�F����
 */

#if !defined(AFX_BOOKEYDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)
#define AFX_BOOKEYDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#ifdef __cplusplus
}
#endif

#include "ProceedingDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg �_�C�A���O

class CBookeyDlg : public CDialog
{
// �\�z
public:
	CBookeyDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBookeyDlg)
	enum { IDD = IDD_BOOKEY_DIALOG };
	CComboBox	m_bookmarkList2;
	CComboBox	m_bookmarkList1;
	CString	m_bookmark1;
	CString	m_bookmark2;
	CString	m_password1;
	CString	m_password2;
	CString	m_username1;
	CString	m_username2;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBookeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
    bool    m_needToSave;

protected:
	HICON   m_hIcon;

    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_blogPet;
    CString m_tgt_fc2bookmark;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_diigo;
    CString m_tgt_opml;
    CString m_tgt_netscape1;
    CString m_tgt_opera6;
    CString m_tgt_hatenaFeed;
    CString m_tgt_livedoorFeed;
    CString m_tgt_deliciousXML;

    void    ChangeButtonGet();
    void    ChangeButtonPut();
    void    EnableButton( bool enable );

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(CBookeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonPut();
	afx_msg void OnButtonSync();
	afx_msg void OnSelchangeComboBookmark1();
	afx_msg void OnSelchangeComboBookmark2();
	afx_msg void OnKillfocusEditPassword1();
	afx_msg void OnKillfocusEditPassword2();
	afx_msg void OnKillfocusEditUsername1();
	afx_msg void OnKillfocusEditUsername2();
	afx_msg void OnUpdateEditUsername1();
	afx_msg void OnUpdateEditPassword1();
	afx_msg void OnUpdateEditUsername2();
	afx_msg void OnUpdateEditPassword2();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonEditTags();
	afx_msg void OnButtonDeleteTags();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CBookeyDlg( CBookeyDlg &dlg );
    CBookeyDlg  operator = ( CBookeyDlg &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEYDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)

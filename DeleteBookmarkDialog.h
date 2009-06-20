/*
 * DeleteBookmarkDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�폜�_�C�A���O ����1 �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  30 Sep 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 14    08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 13    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 12    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks �� Yahoo! �u�b�N�}�[�N�́u�폜�v�ɑΉ�
 * 
 * 11    07/01/12 22:45 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 10    06/08/22 11:43 Tsujimura543
 * DeleteBookmarkDialog �� DeleteBookmarkDialog2 ��1�̃_�C�A���O��
 * �܂Ƃ߂� (DeleteBookmarkDialog2 �͔p�~)
 * 
 * 9     06/07/12 9:33 Tsujimura543
 * livedoor�N���b�v�AEC�i�r�l�C�j���[�X�A�j�t�e�B�N���b�v�̍폜�{�^�����
 * ��
 * 
 * 8     06/06/27 15:24 Tsujimura543
 * Flog �̍폜�ɑΉ�
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
 * 2     05/09/30 23:57 Tsujimura543
 * �u�b�N�}�[�N�̎擾�A�o�^�@�\�̓���m�F����
 */

#if !defined(AFX_DELETEBOOKMARKDIALOG_H__21477E33_8E0E_45CF_9E6F_024EB274E64E__INCLUDED_)
#define AFX_DELETEBOOKMARKDIALOG_H__21477E33_8E0E_45CF_9E6F_024EB274E64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog �_�C�A���O

class DeleteBookmarkDialog : public CDialog
{
// �R���X�g���N�V����
public:
	DeleteBookmarkDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    enum CUserInfo::bookmarkType    m_targetBookmark;
    bool                            m_deleteAll;
    bool                            m_deleteInteractive;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DeleteBookmarkDialog)
	enum { IDD = IDD_DELETE_DIALOG };
	CComboBox	m_bookmark;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(DeleteBookmarkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
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
    CString m_tgt_fc2Bookmark;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_diigo;
    CString m_tgt_localOPML;

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(DeleteBookmarkDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonDeleteInteractive();
	afx_msg void OnButtonDeleteAll();
	afx_msg void OnSelchangeComboDeleteList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    DeleteBookmarkDialog( DeleteBookmarkDialog &dlg );
    DeleteBookmarkDialog    operator = ( DeleteBookmarkDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETEBOOKMARKDIALOG_H__21477E33_8E0E_45CF_9E6F_024EB274E64E__INCLUDED_)

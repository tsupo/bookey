/*
 * DeleteBookmarkDialog3.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�폜�_�C�A���O ����3 �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog3.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 10    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 9     06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 8     06/06/01 19:04 Tsujimura543
 * �u�b�N�}�[�N��ʂ����� enum �l���Aenum CUserInfo::bookmarkType ��
 * ��{������
 * 
 * 7     06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 6     06/03/29 18:30 Tsujimura543
 * �h���R��RSS�ւ̃u�b�N�}�[�N(Clip)�o�^�ɑΉ�����
 * 
 * 5     05/11/01 16:50 Tsujimura543
 * (1) �����������t�@�N�^�����O
 * (2) MM/Memo �̍폜�֘A�������쐬
 * 
 * 4     05/10/21 18:44 Tsujimura543
 * MM/Memo �� BlogPeople �ɑΉ�
 * 
 * 3     05/10/11 16:56 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 * 
 * 2     05/10/03 18:56 Tsujimura543
 * �u�b�N�}�[�N�폜���s���Ɏg���u���[�U���A�p�X���[�h���͉�ʁv���쐬
 */

#if !defined(AFX_DELETEBOOKMARKDIALOG3_H__9980C414_4753_4BA3_A0EB_63A14C625B7D__INCLUDED_)
#define AFX_DELETEBOOKMARKDIALOG3_H__9980C414_4753_4BA3_A0EB_63A14C625B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog3 �_�C�A���O

class DeleteBookmarkDialog3 : public CDialog
{
// �R���X�g���N�V����
public:
    DeleteBookmarkDialog3(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    enum CUserInfo::bookmarkType    m_targetBookmark;
    CString                         m_messageOnCancel;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DeleteBookmarkDialog3)
	enum { IDD = IDD_DELETE_DIALOG3 };
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(DeleteBookmarkDialog3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(DeleteBookmarkDialog3)
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    DeleteBookmarkDialog3( DeleteBookmarkDialog3 &dlg );
    DeleteBookmarkDialog3   operator = ( DeleteBookmarkDialog3 &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETEBOOKMARKDIALOG3_H__9980C414_4753_4BA3_A0EB_63A14C625B7D__INCLUDED_)

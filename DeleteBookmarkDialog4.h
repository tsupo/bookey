/*
 * DeleteBookmarkDialog4.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�폜�_�C�A���O ����4 �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog4.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 4     06/09/04 18:15 Tsujimura543
 * �u1�O�֖߂�v�@�\��ǉ�
 * 
 * 3     05/10/11 19:07 Tsujimura543
 * �u�b�N�}�[�N�����@�\������ (����m�F�ς�)
 * 
 * 2     05/10/03 22:17 Tsujimura543
 * del.icio.us �̃u�b�N�}�[�N���폜���鏈��������
 */

#if !defined(AFX_DELETEBOOKMARKDIALOG4_H__4E5F3A1F_3D38_4AB4_AE28_AB3149996690__INCLUDED_)
#define AFX_DELETEBOOKMARKDIALOG4_H__4E5F3A1F_3D38_4AB4_AE28_AB3149996690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog4 �_�C�A���O

class DeleteBookmarkDialog4 : public CDialog
{
// �R���X�g���N�V����
public:
	DeleteBookmarkDialog4(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    bool    m_execute;
    bool    m_executeWithoutQuery;
    bool    m_enableToBackward;
    bool    m_backToPrevious;
    CString m_messageOnQuery;
    CString m_windowTextExtra;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DeleteBookmarkDialog4)
	enum { IDD = IDD_DELETE_DIALOG4 };
	CString	m_url;
	CString	m_title;
	CString	m_tags;
	CString	m_comment;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(DeleteBookmarkDialog4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(DeleteBookmarkDialog4)
	afx_msg void OnButtonDeleteYes();
	afx_msg void OnButtonDeleteNo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonDeleteForcely();
	afx_msg void OnButtonBackword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    DeleteBookmarkDialog4( DeleteBookmarkDialog4 &dlg );
    DeleteBookmarkDialog4   operator = ( DeleteBookmarkDialog4 &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DELETEBOOKMARKDIALOG4_H__4E5F3A1F_3D38_4AB4_AE28_AB3149996690__INCLUDED_)

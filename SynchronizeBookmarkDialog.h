/*
 * SynchronizeBookmarkDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�폜�_�C�A���O ����1 �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  11 Oct 2005
 *
 * $Log: /comm/bookey/SynchronizeBookmarkDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 5     06/02/08 19:20 Tsujimura543
 * 4�̃u�b�N�}�[�N�̂����̔C�ӂ�2�̊Ԃ̓�������邱�Ƃ��w���ł���悤
 * �ɂ���
 * 
 * 4     05/10/14 17:01 Tsujimura543
 * �R�����g���C��
 * 
 * 3     05/10/11 17:16 Tsujimura543
 * �t�@�C������ύX (Syncronize�c �� Synchronize�c)
 * 
 * 2     05/10/11 17:06 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 */

#if !defined(AFX_SYNCHRONIZEBOOKMARKDIALOG_H__62AC5641_D301_497A_B5FD_589763E07167__INCLUDED_)
#define AFX_SYNCHRONIZEBOOKMARKDIALOG_H__62AC5641_D301_497A_B5FD_589763E07167__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// SynchronizeBookmarkDialog �_�C�A���O

class SynchronizeBookmarkDialog : public CDialog
{
// �R���X�g���N�V����
public:
	SynchronizeBookmarkDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    enum    {
        fromBM1toBM2 = 0,
        fromBM2toBM1,
        both
    }       m_direction;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SynchronizeBookmarkDialog)
	enum { IDD = IDD_SYNC_DIALOG };
	CComboBox	m_bookmarkList2;
	CComboBox	m_bookmarkList1;
	CButton	m_description;
	CString	m_bookmark1;
	CString	m_bookmark2;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SynchronizeBookmarkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    void    ChangeButtons( const char *bookmark1 /* = NULL */,
                           const char *bookmark2 /* = NULL */  );

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SynchronizeBookmarkDialog)
	afx_msg void OnButtonSync1();
	afx_msg void OnButtonSync2();
	afx_msg void OnButtonSync3();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeBm1();
	afx_msg void OnSelchangeBm2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SynchronizeBookmarkDialog( SynchronizeBookmarkDialog &dlg );
    SynchronizeBookmarkDialog   operator = ( SynchronizeBookmarkDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SYNCHRONIZEBOOKMARKDIALOG_H__62AC5641_D301_497A_B5FD_589763E07167__INCLUDED_)

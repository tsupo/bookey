/*
 * ProceedingDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �i�s�󋵕\���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  10 Nov 2005
 *
 * $Log: /comm/bookey/ProceedingDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     06/07/03 23:37 Tsujimura543
 * ProceedingDialog �� DestroyWindow() ���ɗ�O���������邱�Ƃ����錏��
 * �b��Ώ������{ (�f�o�b�O�łł����������Ȃ�?)
 * 
 * 1     05/11/10 21:17 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_)
#define AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog �_�C�A���O

class ProceedingDialog : public CDialog
{
// �R���X�g���N�V����
public:
	ProceedingDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
    void    ChangeDialogText( const char *title, const char *message );
    void    ResetDialogText();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(ProceedingDialog)
	enum { IDD = IDD_PROCEEDING_DIALOG };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(ProceedingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(ProceedingDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    ProceedingDialog( ProceedingDialog &dlg );
    ProceedingDialog    operator = ( ProceedingDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_)

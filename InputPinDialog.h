/*
 * InputPinDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      (OAuth ��) PIN ���̓_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  11 Jun 2009
 *
 * $Log: /comm/bookey/InputPinDialog.h $
 * 
 * 1     09/06/18 0:43 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 1     09/06/11 17:49 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#if !defined(AFX_INPUTPINDIALOG_H__28B8D63A_5699_4BBC_90D0_6971132E1B1E__INCLUDED_)
#define AFX_INPUTPINDIALOG_H__28B8D63A_5699_4BBC_90D0_6971132E1B1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// InputPinDialog �_�C�A���O

class InputPinDialog : public CDialog
{
// �R���X�g���N�V����
public:
	InputPinDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(InputPinDialog)
	enum { IDD = IDD_INPUT_PIN };
	CString	m_pin;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(InputPinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(InputPinDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_INPUTPINDIALOG_H__28B8D63A_5699_4BBC_90D0_6971132E1B1E__INCLUDED_)

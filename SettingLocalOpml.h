/*
 * SettingLocalOpml.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingLocalOpml �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  26 Jul 2006
 *
 * $Log: /comm/bookey/SettingLocalOpml.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     06/10/26 21:00 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#if !defined(AFX_SETTINGLOCALOPML_H__927B0DA2_E19D_4BF9_9641_D0D75EAF0B3F__INCLUDED_)
#define AFX_SETTINGLOCALOPML_H__927B0DA2_E19D_4BF9_9641_D0D75EAF0B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingLocalOpml �_�C�A���O

class SettingLocalOpml : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingLocalOpml(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingLocalOpml)
	enum { IDD = IDD_TAB_LOCALOPML };
	CString	m_filename;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingLocalOpml)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingLocalOpml)
	afx_msg void OnButtonFileopen();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingLocalOpml( SettingLocalOpml &dlg );
    SettingLocalOpml    operator = ( SettingLocalOpml &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGLOCALOPML_H__927B0DA2_E19D_4BF9_9641_D0D75EAF0B3F__INCLUDED_)

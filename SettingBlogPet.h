/*
 * SettingBlogPet.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingBlogPet �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/SettingBlogPet.h $
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
 * 1     06/12/22 22:16 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_SETTINGBLOGPET_H__50BB79F5_C78C_4436_B618_3D6E49AE0C7D__INCLUDED_)
#define AFX_SETTINGBLOGPET_H__50BB79F5_C78C_4436_B618_3D6E49AE0C7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingBlogPet �_�C�A���O

class SettingBlogPet : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingBlogPet(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾
    void    SetUseMyTitle();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingBlogPet)
	enum { IDD = IDD_TAB_BLOGPET };
	//}}AFX_DATA

    bool    m_useMyTitle;   // �u�b�N�}�[�N�o�^���A�����Őݒ肵�悤�Ƃ��Ă���
                            // �^�C�g����D��I�ɓK�p���邩�ۂ� (���҂ɂ����
                            // �ݒ�ς݂̃^�C�g�����󂯓���邩�ۂ�)

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingBlogPet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingBlogPet)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioChange();
	afx_msg void OnRadioNochange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingBlogPet( SettingBlogPet &dlg );
    SettingBlogPet  operator = ( SettingBlogPet &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGBLOGPET_H__50BB79F5_C78C_4436_B618_3D6E49AE0C7D__INCLUDED_)

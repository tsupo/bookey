/*
 * SettingDiigo.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingDiigo �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  25 Jul 2008
 *
 * $Log: /comm/bookey/SettingDiigo.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     08/07/25 17:33 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_SETTINGDIIGO_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)
#define AFX_SETTINGDIIGO_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDiigo �_�C�A���O

class SettingDiigo : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingDiigo(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingDiigo)
	enum { IDD = IDD_TAB_DIIGO };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingDiigo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingDiigo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDiigo( SettingDiigo &dlg );
    SettingDiigo  operator = ( SettingDiigo &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIIGO_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)

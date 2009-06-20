/*
 * SettingBlueDot.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingBlueDot �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  6 Oct 2006
 *
 * $Log: /comm/bookey/SettingBlueDot.h $
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
 * 1     06/10/07 1:07 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#if !defined(AFX_SETTINGBLUEDOT_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)
#define AFX_SETTINGBLUEDOT_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingBlueDot �_�C�A���O

class SettingBlueDot : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingBlueDot(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingBlueDot)
	enum { IDD = IDD_TAB_BLUEDOT };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingBlueDot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingBlueDot)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingBlueDot( SettingBlueDot &dlg );
    SettingBlueDot  operator = ( SettingBlueDot &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGBLUEDOT_H__2ED10682_DACB_4771_918F_9EB5975B8A23__INCLUDED_)

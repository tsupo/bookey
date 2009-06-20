/*
 * SettingDelicious.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingBlogPeople �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingDelicious.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 4     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 3     06/07/31 17:14 Tsujimura543
 * �\�[�X�̐��� (�R�����g�ǉ��A�]���ȉ��s�E�󔒂̍폜�A�Ȃ�)
 * 
 * 2     06/07/31 17:03 Tsujimura543
 * �ݒ�_�C�A���O�� OK �{�^�������ŏI������ƁA����܂łɃ^�u���N���b�N����
 * ���Ȃ������u�b�N�}�[�N�T�[�r�X�̐ݒ���e���j�󂳂�Ă��܂��s��ɑΏ�
 * 
 * 1     06/07/28 23:00 Tsujimura543
 * �V�K�쐬 (�^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�A��������)
 */

#if !defined(AFX_SETTINGDELICIOUS_H__567A1F32_54BB_4F2D_A0A6_6A4295591F29__INCLUDED_)
#define AFX_SETTINGDELICIOUS_H__567A1F32_54BB_4F2D_A0A6_6A4295591F29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDelicious �_�C�A���O

class SettingDelicious : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingDelicious(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingDelicious)
	enum { IDD = IDD_TAB_DELICIOUS };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingDelicious)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingDelicious)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDelicious( SettingDelicious &dlg );
    SettingDelicious    operator = ( SettingDelicious &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDELICIOUS_H__567A1F32_54BB_4F2D_A0A6_6A4295591F29__INCLUDED_)

/*
 * SettingPookmark.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingPookmark �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  4 Oct 2006
 *
 * $Log: /comm/bookey/SettingPookmark.h $
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
 * 1     06/10/04 20:22 Tsujimura543
 * �V�K�쐬 (pookmark �Ή�)
 */

#if !defined(AFX_SETTINGPOOKMARK_H__068DC3C0_E5E6_4120_8F8A_202C6E1A42BC__INCLUDED_)
#define AFX_SETTINGPOOKMARK_H__068DC3C0_E5E6_4120_8F8A_202C6E1A42BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingPookmark �_�C�A���O

class SettingPookmark : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingPookmark(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();   // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingPookmark)
	enum { IDD = IDD_TAB_POOKMARK };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingPookmark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingPookmark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingPookmark( SettingPookmark &dlg );
    SettingPookmark operator = ( SettingPookmark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGPOOKMARK_H__068DC3C0_E5E6_4120_8F8A_202C6E1A42BC__INCLUDED_)

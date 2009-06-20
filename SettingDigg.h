/*
 * SettingDigg.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingDigg �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/SettingDigg.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 1     07/07/09 19:11 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_SETTINGDIGG_H__60D32F03_A07D_466F_9E24_CE37BBA8DD3A__INCLUDED_)
#define AFX_SETTINGDIGG_H__60D32F03_A07D_466F_9E24_CE37BBA8DD3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDigg �_�C�A���O

class SettingDigg : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingDigg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingDigg)
	enum { IDD = IDD_TAB_DIGG };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingDigg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingDigg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDigg( SettingDigg &dlg );
    SettingDigg operator = ( SettingDigg &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIGG_H__60D32F03_A07D_466F_9E24_CE37BBA8DD3A__INCLUDED_)

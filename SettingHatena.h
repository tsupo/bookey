/*
 * SettingHatena.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingHatena �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingHatena.h $
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

#if !defined(AFX_SETTINGHATENA_H__88239AF2_A260_493E_A0CF_97AAE39D0985__INCLUDED_)
#define AFX_SETTINGHATENA_H__88239AF2_A260_493E_A0CF_97AAE39D0985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingHatena �_�C�A���O

class SettingHatena : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingHatena(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾
    void    SetUseMyTitle();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingHatena)
	enum { IDD = IDD_TAB_HATENA };
	//}}AFX_DATA

    bool    m_useMyTitle;   // �u�b�N�}�[�N�o�^���A�����Őݒ肵�悤�Ƃ��Ă���
                            // �^�C�g����D��I�ɓK�p���邩�ۂ� (���҂ɂ����
                            // �ݒ�ς݂̃^�C�g�����󂯓���邩�ۂ�)

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingHatena)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingHatena)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioNochange();
	afx_msg void OnRadioChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingHatena( SettingHatena &dlg );
    SettingHatena   operator = ( SettingHatena &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGHATENA_H__88239AF2_A260_493E_A0CF_97AAE39D0985__INCLUDED_)

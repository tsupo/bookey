/*
 * Setting1470net.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      Setting1470net �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/Setting1470net.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 5     06/08/22 17:53 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 4     06/08/22 17:00 Tsujimura543
 * enum authenticationType �̒�`�� myClip.h ���Ɉڂ���
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

#if !defined(AFX_SETTING1470NET_H__989E9351_8196_41E0_A8E2_C82A1FE44451__INCLUDED_)
#define AFX_SETTING1470NET_H__989E9351_8196_41E0_A8E2_C82A1FE44451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// Setting1470net �_�C�A���O

class Setting1470net : public CTabDialog
{
// �R���X�g���N�V����
public:
	Setting1470net(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();   // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾
    void    SetAuthType();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(Setting1470net)
	enum { IDD = IDD_TAB_1470NET };
	CString	m_hatena_password;
	CString	m_hatena_username;
	//}}AFX_DATA

    AUTH_TYPE   m_authType; // �F�؎��

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(Setting1470net)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(Setting1470net)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioHatena();
	afx_msg void OnRadioHatenaTypekey();
	afx_msg void OnRadioTypekey();
	afx_msg void OnRadioTypekeyHatena();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    Setting1470net( Setting1470net &dlg );
    Setting1470net  operator = ( Setting1470net &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTING1470NET_H__989E9351_8196_41E0_A8E2_C82A1FE44451__INCLUDED_)

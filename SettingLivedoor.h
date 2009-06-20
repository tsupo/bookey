/*
 * SettingLivedoor.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingLivedoor �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingLivedoor.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     08/07/28 17:06 Tsujimura543
 * �ݒ肵���͂��� apiKey �� bookey �̍ċN�����ɏ����Ă��܂�
 * �s����C��
 * 
 * 6     08/07/28 15:29 Tsujimura543
 * �uAPI�L�[�v�֘A�A�ǉ�
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

#if !defined(AFX_SETTINGLIVEDOOR_H__839E7C30_41A1_4E2A_BD43_FE429130BE44__INCLUDED_)
#define AFX_SETTINGLIVEDOOR_H__839E7C30_41A1_4E2A_BD43_FE429130BE44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingLivedoor �_�C�A���O

class SettingLivedoor : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingLivedoor(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingLivedoor)
	enum { IDD = IDD_TAB_LIVEDOOR };
	CString	m_apiKey;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingLivedoor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingLivedoor)
	afx_msg void OnButtonApiKey();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingLivedoor( SettingLivedoor &dlg );
    SettingLivedoor operator = ( SettingLivedoor &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGLIVEDOOR_H__839E7C30_41A1_4E2A_BD43_FE429130BE44__INCLUDED_)

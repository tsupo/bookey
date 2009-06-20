/*
 * SettingEcNavi.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingEcNavi �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingEcNavi.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/09/13 22:29 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
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

#if !defined(AFX_SETTINGECNAVI_H__827D5B3E_2F46_4E23_8202_DD6C4C096BAC__INCLUDED_)
#define AFX_SETTINGECNAVI_H__827D5B3E_2F46_4E23_8202_DD6C4C096BAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingEcNavi �_�C�A���O

class SettingEcNavi : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingEcNavi(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾
    void    SetUseMyTitle();
    void    SetAuthType();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingEcNavi)
	enum { IDD = IDD_TAB_ECNAVI };
	CString	m_yahooJapanID;
	CString	m_yahooJapanPassword;
	//}}AFX_DATA

    bool    m_useMyTitle;   // �u�b�N�}�[�N�o�^���A�����Őݒ肵�悤�Ƃ��Ă���
                            // �^�C�g����D��I�ɓK�p���邩�ۂ� (���҂ɂ����
                            // �ݒ�ς݂̃^�C�g�����󂯓���邩�ۂ�)

    AUTH_TYPE   m_auth;     // �F�ؕ��@ (default �� AK_ORIGINAL)

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingEcNavi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingEcNavi)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioNochange();
	afx_msg void OnRadioChange();
	afx_msg void OnRadioUseEcnavi();
	afx_msg void OnRadioUseYj();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingEcNavi( SettingEcNavi &dlg );
    SettingEcNavi   operator = ( SettingEcNavi &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGECNAVI_H__827D5B3E_2F46_4E23_8202_DD6C4C096BAC__INCLUDED_)

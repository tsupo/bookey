/*
 * SettingNewsing.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingNewsing �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingNewsing.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/10/11 19:31 Tsujimura543
 * Yahoo! Japan �� ID �� newsing �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     06/09/29 18:41 Tsujimura543
 * �V�K�쐬 (newsing �Ή�)
 */

#if !defined(AFX_SETTINGNEWSING_H__084A0DEF_37B8_4E9B_A605_F12385D5E316__INCLUDED_)
#define AFX_SETTINGNEWSING_H__084A0DEF_37B8_4E9B_A605_F12385D5E316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingNewsing �_�C�A���O

class SettingNewsing : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingNewsing(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾
    void    SetAuthType();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingNewsing)
	enum { IDD = IDD_TAB_NEWSING };
	CString	m_yahooJapanID;
	CString	m_yahooJapanPassword;
	//}}AFX_DATA

    AUTH_TYPE   m_auth;     // �F�ؕ��@ (default �� AK_ORIGINAL)

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingNewsing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingNewsing)
	afx_msg void OnRadioUseNewsing();
	afx_msg void OnRadioUseYj();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingNewsing( SettingNewsing &dlg );
    SettingNewsing  operator = ( SettingNewsing &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGNEWSING_H__084A0DEF_37B8_4E9B_A605_F12385D5E316__INCLUDED_)

/*
 * SettingTwitter.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingTwitter �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  10 Apr 2007
 *
 * $Log: /comm/bookey/SettingTwitter.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     07/04/10 18:46 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_SETTINGTWITTER_H__B2A5A9BA_1158_425F_946A_E150A6B5B132__INCLUDED_)
#define AFX_SETTINGTWITTER_H__B2A5A9BA_1158_425F_946A_E150A6B5B132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingTwitter �_�C�A���O

class SettingTwitter : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingTwitter(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingTwitter)
	enum { IDD = IDD_TAB_TWITTER };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingTwitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

    AUTH_TYPE   m_auth;     // �F�ؕ��@ (default �� AK_ORIGINAL)
    CString     m_oauthToken;
    CString     m_oauthTokenSecret;

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingTwitter)
	afx_msg void OnButtonGetToken();
	afx_msg void OnRadioOauth();
	afx_msg void OnRadioBasic();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    void    ShowCurrentStatus();
    bool    GetAccessToken(
                    const char *consumerKey,
                    const char *consumerSecret
                );
    bool    GetRequestToken(
                    const char *consumerKey,
                    const char *consumerSecret,
                    CString    &oauthToken,
                    CString    &oauthTokenSecret
                );
    bool    GetToken(
                    const char *response,
                    CString    &oauthToken,
                    CString    &oauthTokenSecret
                );

    SettingTwitter( SettingTwitter &dlg );
    SettingTwitter  operator = ( SettingTwitter &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTWITTER_H__B2A5A9BA_1158_425F_946A_E150A6B5B132__INCLUDED_)

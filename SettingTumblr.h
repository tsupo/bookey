/*
 * SettingTumblr.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingTumblr �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  31 Oct 2007
 *
 * $Log: /comm/bookey/SettingTumblr.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 2     09/05/29 0:23 Tsujimura543
 * ���e�� tumbleblog ��(�v���C�}���ȊO�����)�I���\�ɂ���
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/10/31 16:50 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_SETTINGTUMBLR_H__E423AC98_FC72_4E34_877A_7B45B0E895D1__INCLUDED_)
#define AFX_SETTINGTUMBLR_H__E423AC98_FC72_4E34_877A_7B45B0E895D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

#define MAX_BLOGS       30  /* �b��l */

/////////////////////////////////////////////////////////////////////////////
// SettingTumblr �_�C�A���O

class SettingTumblr : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingTumblr(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

    CString m_blogID;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingTumblr)
	enum { IDD = IDD_TAB_TUMBLR };
	CString	m_blogName;
	//}}AFX_DATA

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(SettingTumblr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(SettingTumblr)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonSelectTarget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingTumblr( SettingTumblr &dlg );
    SettingTumblr  operator = ( SettingTumblr &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGTUMBLR_H__E423AC98_FC72_4E34_877A_7B45B0E895D1__INCLUDED_)

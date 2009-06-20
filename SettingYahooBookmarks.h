/*
 * SettingYahooBookmarks.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingYahooBookmarks �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  18 Apr 2007
 *
 * $Log: /comm/bookey/SettingYahooBookmarks.h $
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
 * 1     07/04/18 21:34 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#if !defined(AFX_SETTINGYAHOOBOOKMARKS_H__AA8DC0E1_7C0C_46D4_A35B_32E22BB13916__INCLUDED_)
#define AFX_SETTINGYAHOOBOOKMARKS_H__AA8DC0E1_7C0C_46D4_A35B_32E22BB13916__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingYahooBookmarks �_�C�A���O

class SettingYahooBookmarks : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingYahooBookmarks(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingYahooBookmarks)
	enum { IDD = IDD_TAB_YAHOO_BOOKMARKS };
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingYahooBookmarks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingYahooBookmarks)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingYahooBookmarks( SettingYahooBookmarks &dlg );
    SettingYahooBookmarks   operator = ( SettingYahooBookmarks &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGYAHOOBOOKMARKS_H__AA8DC0E1_7C0C_46D4_A35B_32E22BB13916__INCLUDED_)

/*
 * SettingFC2bookmark.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingFC2bookmark �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  30 Mar 2007
 *
 * $Log: /comm/bookey/SettingFC2bookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/05/07 19:20 Tsujimura543
 * �{�_�C�A���O�𔲂�����Am_isTarget �̒l���ݒ�t�@�C���ɔ��f����Ȃ�
 * �s��ɑΏ�
 * (m_isTarget �͓��N���X���̂��̂ł͂Ȃ��A�e�N���X CTabDialog �̂���
 *  ���g���K�v����B�����I�ȃ~�X)
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 1     07/03/30 16:02 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_SETTINGFC2BOOKMARK_H__19C7F532_AD49_4BDA_B892_1BAE817E4F58__INCLUDED_)
#define AFX_SETTINGFC2BOOKMARK_H__19C7F532_AD49_4BDA_B892_1BAE817E4F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingFC2bookmark �_�C�A���O

class SettingFC2bookmark : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingFC2bookmark(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingFC2bookmark)
	enum { IDD = IDD_TAB_FC2BOOKMARK };
	//}}AFX_DATA

 // bool    m_isTarget; // �o�^�ΏۂƂ��邩�ۂ�

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingFC2bookmark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingFC2bookmark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingFC2bookmark( SettingFC2bookmark &dlg );
    SettingFC2bookmark  operator = ( SettingFC2bookmark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGFC2BOOKMARK_H__19C7F532_AD49_4BDA_B892_1BAE817E4F58__INCLUDED_)

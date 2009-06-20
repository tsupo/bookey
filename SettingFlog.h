/*
 * SettingFlog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingFlog �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingFlog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     08/05/07 19:20 Tsujimura543
 * �{�_�C�A���O�𔲂�����Am_isTarget �̒l���ݒ�t�@�C���ɔ��f����Ȃ�
 * �s��ɑΏ�
 * (m_isTarget �͓��N���X���̂��̂ł͂Ȃ��A�e�N���X CTabDialog �̂���
 *  ���g���K�v����B�����I�ȃ~�X)
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

#if !defined(AFX_SETTINGFLOG_H__B9073D75_4E7D_4C01_959E_F817E8C366D9__INCLUDED_)
#define AFX_SETTINGFLOG_H__B9073D75_4E7D_4C01_959E_F817E8C366D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingFlog �_�C�A���O

class SettingFlog : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingFlog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingFlog)
	enum { IDD = IDD_TAB_FLOG };
	//}}AFX_DATA

 // bool    m_isTarget; // �o�^�ΏۂƂ��邩�ۂ�

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingFlog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingFlog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingFlog( SettingFlog &dlg );
    SettingFlog operator = ( SettingFlog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGFLOG_H__B9073D75_4E7D_4C01_959E_F817E8C366D9__INCLUDED_)

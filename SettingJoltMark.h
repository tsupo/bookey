/*
 * SettingJoltMark.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingJoltMark �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/SettingJoltMark.h $
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
 * 1     06/12/21 16:37 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#if !defined(AFX_SETTINGJOLTMARK_H__09926F6A_3870_4867_9876_90DDDF410EE3__INCLUDED_)
#define AFX_SETTINGJOLTMARK_H__09926F6A_3870_4867_9876_90DDDF410EE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingJoltMark �_�C�A���O

class SettingJoltMark : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingJoltMark(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    Accept();   // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingJoltMark)
	enum { IDD = IDD_TAB_JOLTMARK };
	//}}AFX_DATA

 // bool    m_isTarget; // �o�^�ΏۂƂ��邩�ۂ�

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingJoltMark)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingJoltMark)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingJoltMark( SettingJoltMark &dlg );
    SettingJoltMark operator = ( SettingJoltMark &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGJOLTMARK_H__09926F6A_3870_4867_9876_90DDDF410EE3__INCLUDED_)

/*
 * SettingNifty.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      SettingNifty �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingNifty.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     08/11/13 13:25 Tsujimura543
 * �uPowered by @nifty �N���b�v�v�ɉ�����������Ă��Ȃ������̂��C��
 * 
 * 8     08/11/04 16:46 Tsujimura543
 * �uAPI�L�[�ݒ�v�{�^����ǉ�
 * 
 * 7     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog �N���X�𓱓����A�e�^�u�̋��ʏ������W�񂵂�
 * 
 * 5     07/02/16 13:57 Tsujimura543
 * �R�����g���C��
 * 
 * 4     07/02/16 13:56 Tsujimura543
 * �j�t�e�B�N���b�v�ɓo�^�����u�b�N�}�[�N�̃^�C�g���͋��L�ł͂Ȃ��A�e����
 * �Ǝ��̂��̂�ݒ�\�Ȃ��Ƃ������������߁A��Ɂu�Ǝ��̃^�C�g���ŏ㏑��
 * ����v�悤�ɏ������̂Ɗ֘A����ݒ��ʂ���蒼����
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

#if !defined(AFX_SETTINGNIFTY_H__A5EE6969_B2BF_45C3_A8EC_13273CB33489__INCLUDED_)
#define AFX_SETTINGNIFTY_H__A5EE6969_B2BF_45C3_A8EC_13273CB33489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// SettingNifty �_�C�A���O

class SettingNifty : public CTabDialog
{
// �R���X�g���N�V����
public:
	SettingNifty(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
    ~SettingNifty();

    void    Accept();       // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    void    LoadSetting();  // ���݂́u�ݒ�v���擾

    HCURSOR m_hCursor;
    CFont   m_cFont;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(SettingNifty)
	enum { IDD = IDD_TAB_NIFTY };
	CString	m_apiKey;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(SettingNifty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(SettingNifty)
	afx_msg void OnButtonApikey();
	afx_msg void OnPoweredByNiftyclip();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingNifty( SettingNifty &dlg );
    SettingNifty    operator = ( SettingNifty &dlg );

    bool    m_initialized2;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGNIFTY_H__A5EE6969_B2BF_45C3_A8EC_13273CB33489__INCLUDED_)

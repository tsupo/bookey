/*
 * TabDialog.h : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CTabDialog �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  28 Jul 2006 / 8 Jun 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/TabDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/09/06 18:05 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 2     07/06/08 19:21 Tsujimura543
 * �R�����g���C��
 * 
 * 1     07/06/08 19:20 Tsujimura543
 * �V�K�쐬 (���܂Ŋe�\�[�V�����u�b�N�}�[�N�T�[�r�X���Ƃɐݒ��ʂɊւ���
 * �����������Ă����̂��A���ʉ��ł��镔���� CTabDialog�N���X�ɏW�񂵂Ă݂�)
 */

#ifndef __TAB_DIALOG_H__
#define __TAB_DIALOG_H__

/////////////////////////////////////////////////////////////////////////////
// CTabDialog �_�C�A���O

class CTabDialog : public CDialog
{
public:
    CTabDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL );

    // �u�ݒ�_�C�A���O�v�ł́u�K�p�v�{�^������������
    virtual void    Accept() = 0;

    // �u�o�^�Ώہv�ɂ���
    void            SetIsTarget();
    bool            m_isTarget; // �o�^�ΏۂƂ��邩�ۂ�

    // ���݂́u�ݒ�v���擾
    virtual void    LoadSetting() = 0;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CTabDialog)
	CString	m_username;
	CString	m_password;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CTabDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    bool    m_initialized;

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(CTabDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioTarget();
	afx_msg void OnRadioNontarget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif  /* __TAB_DIALOG_H__ */

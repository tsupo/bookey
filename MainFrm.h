/*
 * MainFrm.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CMainFrame �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/MainFrm.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/10/22 13:35 Tsujimura543
 * �^�C�g���o�[���E�N���b�N�����Ƃ��ɕ\������郁�j���[�ɁA�u�T�|�[�g�v�A
 * �u�R�~���j�e�B�v�A�u�o�[�W�������v��ǉ�
 * 
 * 4     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 3     05/10/24 21:42 Tsujimura543
 * �N���b�v�{�[�h�Ƀe�L�X�g�������Ă��Ȃ��Ƃ��́Apaste �� disable
 * �ɂ���悤�ɂ���
 * 
 * 2     05/10/14 20:38 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�Ή���Ɗ���
 * 
 * 1     05/10/14 14:28 Tsujimura543
 * �V�K�쐬 (�h���b�O�E�A���h�E�h���b�v�@�\��g���ނ��߁ACFormView �𓱓�)
 */

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ���i

#if !defined(AFX_MAINFRM_H__B438C2A6_D364_46DC_AE75_5468DFB03DF4__INCLUDED_)
#define AFX_MAINFRM_H__B438C2A6_D364_46DC_AE75_5468DFB03DF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���b�Z�[�W�}�b�v�֐�
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CMainFrame( CMainFrame &obj );
    CMainFrame  operator = ( CMainFrame &obj );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MAINFRM_H__B438C2A6_D364_46DC_AE75_5468DFB03DF4__INCLUDED_)

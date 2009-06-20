/*
 * AboutDlg.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �Ő�(�o�[�W�����ԍ�)�\���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/AboutDlg.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     09/02/24 16:40 Tsujimura543
 * �uYahoo! Japan Web �T�[�r�X�v�̃N���W�b�g�\����ǉ�
 * 
 * 5     09/01/19 23:55 Tsujimura543
 * �c�[���o�[�̉E�N���b�N���j���[�Ɂu�u�b�N�}�[�N�Ǘ��c�[���N���v��
 * �u�ݒ�v��ǉ� (�ŏ�����Ԃ�����N���ł���悤�ɂ���)
 * 
 * 4     08/10/22 13:33 Tsujimura543
 * IDM_ABOUT_SUPPORT, IDM_ABOUT_SUPPORT2,
 * IDM_ABOUT_COMMUNITY, IDM_ABOUT_COMMUNITY2
 * �̒�`�� bookeyDlg.cpp ����ڊ�
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     06/06/27 12:07 Tsujimura543
 * blog �� URL�A���[���A�h���X���N���b�N����ƁA�u���E�U�A���[���𗧂��グ
 * ��悤�ɂ���
 * 
 * 1     05/10/14 14:11 Tsujimura543
 * bookey.cpp ����� bookeyDlg.cpp ���番���A�Ɨ�������
 */

#if !defined(AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_)
#define AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	~CAboutDlg();

    HCURSOR m_hCursor;
    CFont   m_cFont;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnBookeyMailAddr();
	afx_msg void OnBookeyWebUrl();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCreditYahooJapan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CAboutDlg( CAboutDlg &dlg );
    CAboutDlg   operator = ( CAboutDlg &dlg );
};

#define IDM_ABOUT_SUPPORT       (IDM_ABOUTBOX + 1)
#define IDM_ABOUT_SUPPORT2      (IDM_ABOUTBOX + 2)
#define IDM_ABOUT_COMMUNITY     (IDM_ABOUTBOX + 3)
#define IDM_ABOUT_COMMUNITY2    (IDM_ABOUTBOX + 4)

#define IDM_MANAGE_BOOKMARKS    (IDM_ABOUTBOX + 9)
#define IDM_EDIT_SETTING        (IDM_ABOUTBOX + 10)

#endif  // AFX_ABOUTDLG_H__D2A6332F_A8AD_4DA8_8E75_58DE708ABB2B__INCLUDED_

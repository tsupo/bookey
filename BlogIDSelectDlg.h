/*
 * BlogIDSelectDlg.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      Blog ID �I���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007 / 28 May 2009
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�A�uBloGolEe�v�Ŏg���Ă���\�[�X�R�[�h�𗬗p
 *
 * $Log: /comm/bookey/BlogIDSelectDlg.h $
 * 
 * 1     09/05/29 8:31 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 1     09/05/28 23:22 Tsujimura543
 * bookey �����̍ŏ��̔�
 */

#if !defined(AFX_BLOGIDSELECTDLG_H__A3DAE02A_55C2_49FD_BA9F_EF76780D1C7E__INCLUDED_)
#define AFX_BLOGIDSELECTDLG_H__A3DAE02A_55C2_49FD_BA9F_EF76780D1C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#ifdef __cplusplus
}
#endif

#define MAX_BLOG_NAME_LENGTH    MAX_BLOGNAMELENGTH

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg �_�C�A���O

class CBlogIDSelectDlg : public CDialog
{
// �R���X�g���N�V����
private:
    BLOGINF *m_blogList;
    int     m_numOfBlogs;

    void    initBlogList( void );

public:
	CBlogIDSelectDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    ~CBlogIDSelectDlg() {
        if ( m_blogList )
            delete [] m_blogList;
    }

    void    initialize( BLOGINF *blogList, int numOfBlogs );

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBlogIDSelectDlg)
	enum { IDD = IDD_BLOGID_DIALOG };
	CListBox	m_blogIDlist;
	int		m_blogIDlistIndex;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CBlogIDSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(CBlogIDSelectDlg)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeListBlogid();
	afx_msg void OnDblclkListBlogID();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BLOGIDSELECTDLG_H__A3DAE02A_55C2_49FD_BA9F_EF76780D1C7E__INCLUDED_)

/*
 * ReplaceTagsDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �^�O�u���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  24 Jan 2006
 *
 * $Log: /comm/bookey/ReplaceTagsDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 4     08/07/25 18:44 Tsujimura543
 * Diigo �Ή�����
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     07/01/29 18:04 Tsujimura543
 * ���[�U�C���^�[�t�F�[�X�̍ו����l�߂�K�v���c���Ă��邪�A�Ƃ肠�����A
 * �g������̂�����
 * 
 * 1     07/01/24 21:01 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#if !defined(AFX_REPLACETAGSDIALOG_H__7DECEF52_ED77_4E69_A834_DE2F53423A0D__INCLUDED_)
#define AFX_REPLACETAGSDIALOG_H__7DECEF52_ED77_4E69_A834_DE2F53423A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReplaceTagsDialog �_�C�A���O

class CReplaceTagsDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CReplaceTagsDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CReplaceTagsDialog)
	enum { IDD = IDD_REPLACE_TAGS_DIALOG };
	CComboBox	m_bookmarkList;
	CComboBox	m_tagList;
	CString	m_newTag;
	CString	m_oldTag;
	CString	m_bookmarkName;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CReplaceTagsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    int                             m_tagIndex;
    int                             m_numOfTags;
    enum CUserInfo::bookmarkType    m_targetBookmark;

    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_blogPet;
    CString m_tgt_fc2Bookmark;
    CString m_tgt_diigo;
    CString m_tgt_localOPML;

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(CReplaceTagsDialog)
	afx_msg void OnButtonGetTags();
	afx_msg void OnReplaceTags();
	afx_msg void OnSelchangeComboDeleteTaglist();
	afx_msg void OnSelchangeComboDeletelistTags();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillfocusEditNewTag();
	afx_msg void OnUpdateEditNewTag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CReplaceTagsDialog( CReplaceTagsDialog &dlg );
    CReplaceTagsDialog  operator = ( CReplaceTagsDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_REPLACETAGSDIALOG_H__7DECEF52_ED77_4E69_A834_DE2F53423A0D__INCLUDED_)

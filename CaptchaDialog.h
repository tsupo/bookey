/*
 * CaptchaDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CCaptchaDialog �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/CaptchaDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/10/10 22:38 Tsujimura543
 * �摜���擾����̂� cookie ���K�v�ȏꍇ(���̂Ƃ���Adigg�̂�)�ɑΉ�
 * 
 * 5     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 4     07/07/10 19:34 Tsujimura543
 * inputCaptchaString() �̈����ǉ��Ƃ���ɔ����e��ύX(����2)
 * 
 * 3     07/07/10 1:01 Tsujimura543
 * inputCaptchaString() �̈����ǉ��Ƃ���ɔ����e��ύX
 * 
 * 2     07/07/09 21:50 Tsujimura543
 * Topic �̑I����ǉ�
 * 
 * 1     07/07/09 17:37 Tsujimura543
 * �V�K�쐬
 */

#if !defined(AFX_CAPTCHADIALOG_H__4E7FD97B_511D_4312_AB0B_884DB031773E__INCLUDED_)
#define AFX_CAPTCHADIALOG_H__4E7FD97B_511D_4312_AB0B_884DB031773E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCaptchaDialog �_�C�A���O

class CCaptchaDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CCaptchaDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
    ~CCaptchaDialog();

    CString     m_captchaImageURL;  // CAPTCHA �摜 URL
    CString     m_cookie;
    CString     m_topic;
    HBITMAP     m_bitmap;
    CAP_MODE    m_mode;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCaptchaDialog)
	enum { IDD = IDD_CAPTCHA_DIALOG };
	CComboBox	m_topicList;
	CString	m_captcha;
	CString	m_title;
	CString	m_comment;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CCaptchaDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(CCaptchaDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeComboTopic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CCaptchaDialog( CCaptchaDialog &dlg );
    CCaptchaDialog  operator = ( CCaptchaDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CAPTCHADIALOG_H__4E7FD97B_511D_4312_AB0B_884DB031773E__INCLUDED_)

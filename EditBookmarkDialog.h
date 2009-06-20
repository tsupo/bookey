/*
 * EditBookmarkDialog.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�ҏW�_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  14 Oct 2005
 *
 * $Log: /comm/bookey/EditBookmarkDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 42    08/11/04 12:48 Tsujimura543
 * @nifty Clip �o�^�Ґ����\������悤�ɂ���
 * 
 * 41    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 40    08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 39    07/10/31 17:13 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 38    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 37    07/09/05 2:19 Tsujimura543
 * SetUsers() �𓱓����A�\�[�X�𐮗�
 * 
 * 36    07/08/28 18:52 Tsujimura543
 * SetStaticEdge() �̑�2�����̌^�� bool ���� BOOL �ɕύX
 * 
 * 35    07/08/28 18:45 Tsujimura543
 * SetStaticEdge() ��ǉ�
 * 
 * 34    07/08/27 21:55 Tsujimura543
 * �u�͂ĂȃX�^�[�v�ɑΉ�
 * 
 * 33    07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 32    07/05/23 16:02 Tsujimura543
 * Timelog �Ή�
 * 
 * 31    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 30    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 29    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 28    07/03/30 16:24 Tsujimura543
 * FC2BOOKMARK �ɑΉ�
 * 
 * 27    07/03/01 21:45 Tsujimura543
 * �R�����g���C��
 * 
 * 26    07/03/01 21:44 Tsujimura543
 * (1) livedoor�N���b�v�ɓo�^���Ă���l�̐���\������悤�ɂ���
 * (2) �j�t�e�B�N���b�v�̃A�C�R�����N���b�N����ƁA�G���g���y�[�W���u���E
 *     �U�ŕ\���ł���悤�ɂ���
 * 
 * 25    07/02/05 14:52 Tsujimura543
 * �h���R��RSS��Flog�̃J�e�S�������������C��
 * 
 * 24    07/02/02 23:56 Tsujimura543
 * ���C�����̓���m�F����
 * 
 * 23    07/02/02 23:40 Tsujimura543
 * �ēo�^���悤�Ƃ��Ă���ꍇ�̈�A�̏������C���B�h���R��RSS��Flog�̃J�e�S
 * ���������ł���悤�ɂ���
 * 
 * 22    07/01/16 21:03 Tsujimura543
 * IsInner() ��ǉ�
 * 
 * 21    07/01/12 23:34 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 20    06/12/27 17:37 Tsujimura543
 * �u�b�N�}�[�N���e�_�C�A���O�ŉE�N���b�N���j���[���g����悤�ɂ���
 * 
 * 19    06/12/06 18:57 Tsujimura543
 * �u���J��ԁv�̐ݒ�ɑΉ�
 * 
 * 18    06/09/30 0:55 Tsujimura543
 * ���~�{�^���������̓�����C�� (�L�����Z���\�ɂ���)
 * 
 * 17    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 16    06/07/14 20:50 Tsujimura543
 * 1470.net���j���[�A���łɑΉ�
 * 
 * 15    06/07/11 22:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�̃u�b�N�}�[�N�o�^�Ґ����\������悤�ɂ���
 * (�u�b�N�}�[�N�o�^���/EditBookmarkDialog)
 * 
 * 14    06/06/30 11:37 Tsujimura543
 * livedoor�N���b�v�AEC�i�r�l�C�j���[�X�̃A�C�R�����N���b�N�����Ƃ����A
 * �e�u�b�N�}�[�N�̃G���g���y�[�W��(�u���E�U�o�R��)�\������悤�ɂ���
 * 
 * 13    06/06/28 15:54 Tsujimura543
 * �u�b�N�}�[�N�o�^�Ґ��𒲂ׂĕ\������@�\��ǉ�
 * 
 * 12    06/06/26 16:27 Tsujimura543
 * OnSetCursor() ��ǉ� (�w�J�[�\���\���@�\)
 * 
 * 11    06/06/19 13:42 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�Adel.icio.us�AMM/Memo �̃A�C�R�����N���b�N�����Ƃ��A
 * �e�u�b�N�}�[�N�̃G���g���y�[�W��(�u���E�U�o�R��)�\������悤�ɂ���
 * 
 * 10    06/06/06 15:17 Tsujimura543
 * �ǂ̃\�[�V�����u�b�N�}�[�N�ւ̓o�^���L��(�������͖���)�ɂȂ��Ă���̂�
 * �A�C�R���ƃc�[���`�b�v���g���ĕ\������悤�ɂ���
 * 
 * 9     06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 8     06/04/06 22:16 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�́u�R���N�V�����v�ւ̒ǉ��ɑΉ�
 * 
 * 7     06/03/29 21:23 Tsujimura543
 * �h���R��RSS�́u�t�H���_�v(�J�e�S��)���w��ł���悤�ɂ���
 * 
 * 6     06/03/27 17:16 Tsujimura543
 * OnUpdateEditBmComment() �������S�Ă� OnUpdateEditBmXXX() ��p�~
 * 
 * 5     06/03/24 15:48 Tsujimura543
 * OnUpdateEditBmUrl() ���폜 [�����ɍċA����������s���������]
 * 
 * 4     05/12/01 0:02 Tsujimura543
 * �^�O���\���E���͋@�\������
 * 
 * 3     05/10/24 17:37 Tsujimura543
 * �͂Ăȓ����K�ɑΉ�����
 * 
 * 2     05/10/14 17:02 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O������
 */

#if !defined(AFX_EDITBOOKMARKDIALOG_H__3EDC0EC9_0CED_4E9A_B89F_53E3E42275E4__INCLUDED_)
#define AFX_EDITBOOKMARKDIALOG_H__3EDC0EC9_0CED_4E9A_B89F_53E3E42275E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// EditBookmarkDialog �_�C�A���O

class EditBookmarkDialog : public CDialog
{
// �R���X�g���N�V����
public:
	EditBookmarkDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    void    RedrawCounter( const char *comment );
    void    SetTag( int tagID );

    bool    m_enableTipJar; // ���Y�G���g���[�̃I�[�i�[�ɑ΂��Ă͂Ăȃ|�C���g
                            // ���M�\���ۂ�
    bool    m_useCategory;  // (�h���R��RSS ��)�J�e�S�����g�����ۂ�
    bool    m_enableCollection;     // �͂Ăȃu�b�N�}�[�N�́u�R���N�V�����v��
                                    // �o�^�\���ۂ�
    bool    m_registerCollection;   // �͂Ăȃu�b�N�}�[�N�́u�R���N�V�����v��
                                    // �o�^���邩�ۂ�
    CString *m_tag[20];
    int     m_evaluation;  // �]��#1 (5�i�K + ���]��)
    int     m_rating;      // �]��#2 (3�i�K)
    int     m_affirmation; // �]��#3 (�m��/�ے�)
    int     m_public;      // ���J��� (EVERYONE/FRIENDS/PRIVATE)
    RBparam_t   m_param;   // �o�^���邩�ۂ��̐ݒ���ꎞ�I�ɕύX����ړI�Ŏg�p
    HCURSOR m_hCursor;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(EditBookmarkDialog)
	enum { IDD = IDD_EDIT_BOOKMARK_DIALOG };
	CComboBox	m_categoryList2;
	CComboBox	m_categoryList;
	CString	m_counterString;
	CString	m_comment;
	CString	m_tags;
	CString	m_title;
	CString	m_url;
	BOOL	m_sendTipJar;
	CString	m_tag001;
	CString	m_tag002;
	CString	m_tag003;
	CString	m_tag004;
	CString	m_tag005;
	CString	m_tag006;
	CString	m_tag007;
	CString	m_tag008;
	CString	m_tag009;
	CString	m_tag010;
	CString	m_tag011;
	CString	m_tag012;
	CString	m_tag013;
	CString	m_tag014;
	CString	m_tag015;
	CString	m_tag016;
	CString	m_tag017;
	CString	m_tag018;
	CString	m_tag019;
	CString	m_tag020;
	CString	m_category;
	CString	m_category2;
	CString	m_hbUsers;
	CString	m_deliciousUsers;
	CString	m_mmUsers;
	CString	m_ecNaviUsers;
	CString	m_livedoorClipUsers;
	CString	m_diggUsers;
	CString	m_hatenaStarUsers;
	CString	m_niftyClipUsers;
	//}}AFX_DATA

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(EditBookmarkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    void    DisplayToolTip( bool isTarget, BOOL onOff, TOOLTIPTEXT *tp );
    bool    IsInner( int id, WORD wX, WORD wY );
    void    SetStaticEdge( int idx, BOOL status );
    void    SetUsers( CString &users, int idx, long maxLength = 8 );

    int     GetCatNumberOfDrecom( const char *tag );
    int     GetCatNumberOfDrecom( CString& tags );

    int     GetCatNumberOfFlog( const char *tag );
    int     GetCatNumberOfFlog( CString& tags );

    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_newsing;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_blogPet;
    CString m_tgt_fc2bookmark;
    CString m_tgt_twitter;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_timelog;
    CString m_tgt_digg;
    CString m_tgt_tumblr;
    CString m_tgt_diigo;
    CString m_tgt_hatenaStar;

	// ���b�Z�[�W�}�b�v�֐�
	//{{AFX_MSG(EditBookmarkDialog)
	afx_msg void OnKillfocusEditBmUrl();
	afx_msg void OnKillfocusEditBmTitle();
	afx_msg void OnKillfocusEditBmComment();
	afx_msg void OnKillfocusEditBmTags();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheckTipjar();
	afx_msg void OnTag001();
	afx_msg void OnTag002();
	afx_msg void OnTag003();
	afx_msg void OnTag004();
	afx_msg void OnTag005();
	afx_msg void OnTag006();
	afx_msg void OnTag007();
	afx_msg void OnTag008();
	afx_msg void OnTag009();
	afx_msg void OnTag010();
	afx_msg void OnTag011();
	afx_msg void OnTag012();
	afx_msg void OnTag013();
	afx_msg void OnTag014();
	afx_msg void OnTag015();
	afx_msg void OnTag016();
	afx_msg void OnTag017();
	afx_msg void OnTag018();
	afx_msg void OnTag019();
	afx_msg void OnTag020();
	afx_msg void OnUpdateEditBmComment();
	afx_msg void OnSelchangeComboCategory();
	virtual void OnOK();
	afx_msg void OnSelchangeComboCategory2();
	virtual BOOL OnInitDialog();
    afx_msg void OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnIconHatenaBookmark();
	afx_msg void OnIconDelicious();
	afx_msg void OnIconMmMemo();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnHbUsers();
	afx_msg void OnDeliciousUsers();
	afx_msg void OnMmUsers();
	afx_msg void OnIconLivedoor();
	afx_msg void OnIconEcnaviClip();
	afx_msg void OnEcnaviUsers();
	afx_msg void OnIcon1470net();
	afx_msg void OnNewsGood();
	afx_msg void OnNewsBad();
	afx_msg void OnRadioEval00();
	afx_msg void OnRadioEval01();
	afx_msg void OnRadioEval02();
	afx_msg void OnRadioEval03();
	afx_msg void OnRadioEval04();
	afx_msg void OnRadioEval05();
	afx_msg void OnIconNewsing();
	afx_msg void OnRadioPublic();
	afx_msg void OnRadioFriends();
	afx_msg void OnRadioPrivate();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnIconNiftyClip();
	afx_msg void OnLivedoorclipUsers();
	afx_msg void OnIconDigg();
	afx_msg void OnDiggUsers();
	afx_msg void OnIconHatenaStar();
	afx_msg void OnHatenaStarUsers();
	afx_msg void OnNiftyclipUsers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    EditBookmarkDialog( EditBookmarkDialog &dlg );
    EditBookmarkDialog  operator = ( EditBookmarkDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_EDITBOOKMARKDIALOG_H__3EDC0EC9_0CED_4E9A_B89F_53E3E42275E4__INCLUDED_)

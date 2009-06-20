/*
 * bookeyView.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CBookeyView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyView.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 36    09/01/19 23:55 Tsujimura543
 * �c�[���o�[�̉E�N���b�N���j���[�Ɂu�u�b�N�}�[�N�Ǘ��c�[���N���v��
 * �u�ݒ�v��ǉ� (�ŏ�����Ԃ�����N���ł���悤�ɂ���)
 * 
 * 35    07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 34    07/07/09 18:38 Tsujimura543
 * ���{�ꃂ�[�h�Ɖp�ꃂ�[�h��؂�ւ���@�\��ǉ�
 * (�����_�ł́A���̋@�\�́A�f�o�b�O�r���h���̂ݗL���ƂȂ�)
 * 
 * 33    07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 32    07/03/16 23:03 Tsujimura543
 * SetProxyInfo() �̎d�l��ύX�B�����ۑ����[�h��p�ӂ���
 * 
 * 31    07/03/16 1:03 Tsujimura543
 * proxy�T�[�o�o�R�łȂ��ƃC���^�[�l�b�g�A�N�Z�X�ł��Ȃ��̂ɁAproxy�T�[�o
 * ���g��Ȃ��ݒ�ɂȂ��Ă���ꍇ�̑΍��ǉ�
 * 
 * 30    07/03/14 23:32 Tsujimura543
 * URL �L���[�C���O�@�\������
 * 
 * 29    06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 * 
 * 28    06/07/05 18:19 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��13�i�K�A�I��
 * 
 * 27    06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 26    06/07/04 23:48 Tsujimura543
 * encodeParameter() �� decodeParameter() �� CBookeyView �N���X�O�ֈړ�
 * 
 * 25    06/07/04 21:46 Tsujimura543
 * LoadSetting(), SaveSetting(), CheckEncodedPassword() �����t�@�N�^�����O
 * 
 * 24    06/07/03 23:37 Tsujimura543
 * ProceedingDialog �� DestroyWindow() ���ɗ�O���������邱�Ƃ����錏��
 * �b��Ώ������{ (�f�o�b�O�łł����������Ȃ�?)
 * 
 * 23    06/06/28 15:54 Tsujimura543
 * �u�b�N�}�[�N�o�^�Ґ��𒲂ׂĕ\������@�\��ǉ�
 * 
 * 22    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() �����s���Ă��A�ݒ肪�ύX�ł��Ȃ��Ȃ���
 * ���܂��Ă���(�G���o�O)�̂��C���B�ύX�ł���悤�ɂ���
 * 
 * 21    06/06/14 11:44 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��5�i�K�A�I��
 * 
 * 20    06/06/13 21:11 Tsujimura543
 * �u�b�N�}�[�N�o�^���ł���ʍĕ`��ł���悤�ɂ��Ă݂�
 * 
 * 19    06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 18    06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 17    06/06/06 22:23 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��
 * 
 * 16    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 15    06/06/01 20:28 Tsujimura543
 * CBookeyDlg ���̃��[�U���A�p�X���[�h�� CUserInfo ���g���ĊǗ�����
 * �悤�ɕύX����
 * 
 * 14    06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 13    06/06/01 18:49 Tsujimura543
 * enum bookmarkType �̒�`�� CBookeyView ���� CUserInfo �Ɉڂ���
 * 
 * 12    06/06/01 17:19 Tsujimura543
 * CUserInfo �N���X�𓱓�
 * 
 * 11    06/06/01 15:13 Tsujimura543
 * struct RBparam �� RBuser_t ���g���Ē�`��������
 * 
 * 10    06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 9     06/03/29 18:30 Tsujimura543
 * �h���R��RSS�ւ̃u�b�N�}�[�N(Clip)�o�^�ɑΉ�����
 * 
 * 8     06/03/13 20:56 Tsujimura543
 * �^�O���̕\���� ON/OFF �ł���悤�ɂ���
 * 
 * 7     06/03/09 15:16 Tsujimura543
 * CheckEncodedPassword() ��ǉ�
 * 
 * 6     05/11/01 16:50 Tsujimura543
 * (1) �����������t�@�N�^�����O
 * (2) MM/Memo �̍폜�֘A�������쐬
 * 
 * 5     05/10/24 14:45 Tsujimura543
 * �R���e�L�X�g���j���[������ǉ�
 * 
 * 4     05/10/21 19:56 Tsujimura543
 * MM/Memo �� BlogPeople �̓����u�b�N�}�[�N�o�^�ɂ��Ή�
 * 
 * 3     05/10/15 0:07 Tsujimura543
 * ���[�U���ƃp�X���[�h��ݒ�t�@�C���ɕۑ�����悤�ɂ���
 * 
 * 2     05/10/14 20:38 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�Ή���Ɗ���
 * 
 * 1     05/10/14 14:28 Tsujimura543
 * �V�K�쐬 (�h���b�O�E�A���h�E�h���b�v�@�\��g���ނ��߁ACFormView �𓱓�)
 */

/////////////////////////////////////////////////////////////////////////////
// CBookeyView ���i

#if !defined(AFX_BOOKEYVIEW_H__60864F83_A9BE_4622_8AED_48C0A5F33DBB__INCLUDED_)
#define AFX_BOOKEYVIEW_H__60864F83_A9BE_4622_8AED_48C0A5F33DBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CBookeyView �N���X
class CBookeyView : public CFormView
{
protected:
	CBookeyView();
	DECLARE_DYNCREATE(CBookeyView)

public:
	//{{AFX_DATA(CBookeyView)
	enum { IDD = IDD_BOOKEY_FORM };
	BOOL	m_useTagSuggestion;
	BOOL	m_useUsers;
	//}}AFX_DATA

// �A�g���r���[�g
public:
    CBookeyDoc* GetDocument();

    char        m_path[MAX_PATH];   // bookey.exe �̑��݂���f�B���N�g����

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CBookeyView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo�����
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CBookeyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    COleDropTarget      m_dropTarget;   //  OLE DnD �̃h���b�v�^�[�Q�b�g
#if 0
    bool                m_useProxy;
#endif
    bool                m_procCreated;
    ProceedingDialog    m_procDialog;
    CWinThread          *m_registerBookmarkThread;
    RBparam_t           m_param;

    void    LoadSetting();  // �ݒ���ǂݍ���
    void    SaveSetting();  // �ݒ��񏑂��o��
    void    SetProxyInfo( bool saveForcely = false );

    void    PutBookmark( const char *url );

    void    ManagementBookmark();
    void    EditSetting();

private:
    CRITICAL_SECTION    m_cs_bookey;    // �X���b�h�Ԃł̔r������p

#define MAX_WAITING_NUM 64
    CString             m_waitingURLs[MAX_WAITING_NUM]; // �o�^�҂� URL
    long                m_numOfWaiting;                 // �o�^�҂� URL ����
    long                m_waitingHead;                  // �o�^�҂� URL �L���[�擪
    long                m_waitingTail;                  // �o�^�҂� URL �L���[����

    void    putBookmark( const char *url );
    long    putWaiting( const char *url );
    CString getWaiting();

    bool    CheckEncodedPassword();
    void    EnableButton( bool enable );

// ���b�Z�[�W�}�b�v�֐�
protected:
	//{{AFX_MSG(CBookeyView)
	afx_msg void OnButtonTool();
	afx_msg void OnButtonSetting();
	afx_msg void OnButtonFinish();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEditPaste();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCheckTagSuggestion();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckUsers();
	afx_msg void OnButtonProxy();
	afx_msg void OnCheckLanguage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CBookeyView( CBookeyView &obj );
    CBookeyView operator = ( CBookeyView &obj );
};

#ifndef _DEBUG  // bookeyView.cpp �t�@�C�����f�o�b�O���̎��g�p�����
inline CBookeyDoc* CBookeyView::GetDocument()
   { return (CBookeyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEYVIEW_H__60864F83_A9BE_4622_8AED_48C0A5F33DBB__INCLUDED_)

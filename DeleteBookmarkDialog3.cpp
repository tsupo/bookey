/*
 * DeleteBookmarkDialog3.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�폜�_�C�A���O ����3 �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog3.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 31    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 30    08/07/25 22:17 Tsujimura543
 * Diigo �Ή�����
 * 
 * 29    07/10/31 17:08 Tsujimura543
 * digg �� tumblr �ɑΉ�
 * 
 * 28    07/05/23 16:03 Tsujimura543
 * Timelog �Ή�
 * 
 * 27    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 26    07/04/16 18:49 Tsujimura543
 * Twitter �� Yahoo! �u�b�N�}�[�N �ɑΉ�
 * 
 * 25    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 24    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 23    07/01/16 21:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 22    07/01/15 22:37 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 21    07/01/11 17:01 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 20    06/12/22 21:47 Tsujimura543
 * �R�����g�C��
 * 
 * 19    06/12/21 21:18 Tsujimura543
 * JoltMark�AFC2BOOKMARK�A�uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 18    06/10/26 22:52 Tsujimura543
 * �R�����g���C��
 * 
 * 17    06/10/26 22:51 Tsujimura543
 * POOKMARK Airlines �� Blue Dot �p�̕�����p�ӂ���
 * 
 * 16    06/08/23 21:33 Tsujimura543
 * �u1470.net���j���[�A���Łv�̂Ƃ��̕�����ύX
 * 
 * 15    06/07/14 20:50 Tsujimura543
 * 1470.net���j���[�A���łɑΉ�
 * 
 * 14    06/06/30 20:17 Tsujimura543
 * livedoor�N���b�v�AEC�i�r�l�C�j���[�X�A�j�t�e�B�N���b�v�p�̕�����p�ӂ���
 * 
 * 13    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 12    06/06/01 19:20 Tsujimura543
 * break; ����(1�ӏ�)�A�C��
 * 
 * 11    06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 10    06/06/01 19:04 Tsujimura543
 * �u�b�N�}�[�N��ʂ����� enum �l���Aenum CUserInfo::bookmarkType ��
 * ��{������
 * 
 * 9     06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 8     06/03/29 18:30 Tsujimura543
 * �h���R��RSS�ւ̃u�b�N�}�[�N(Clip)�o�^�ɑΉ�����
 * 
 * 7     05/11/01 16:50 Tsujimura543
 * (1) �����������t�@�N�^�����O
 * (2) MM/Memo �̍폜�֘A�������쐬
 * 
 * 6     05/10/21 18:44 Tsujimura543
 * MM/Memo �� BlogPeople �ɑΉ�
 * 
 * 5     05/10/14 20:38 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�Ή���Ɗ���
 * 
 * 4     05/10/14 15:35 Tsujimura543
 * OnCancel() �ŕ\�����镶���̃o���G�[�V������ǉ�
 * 
 * 3     05/10/11 16:56 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 * 
 * 2     05/10/03 18:56 Tsujimura543
 * �u�b�N�}�[�N�폜���s���Ɏg���u���[�U���A�p�X���[�h���͉�ʁv���쐬
 */

#include "bookey.h"
#include "DeleteBookmarkDialog3.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteBookmarkDialog3.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog3 �_�C�A���O

DeleteBookmarkDialog3::DeleteBookmarkDialog3(CWnd* pParent /*=NULL*/)
	: CDialog(DeleteBookmarkDialog3::IDD, pParent)
{
    m_targetBookmark  = CUserInfo::BK_UNKNOWN;
    m_messageOnCancel = "";

	//{{AFX_DATA_INIT(DeleteBookmarkDialog3)
	m_username = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
}

void DeleteBookmarkDialog3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeleteBookmarkDialog3)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DeleteBookmarkDialog3, CDialog)
	//{{AFX_MSG_MAP(DeleteBookmarkDialog3)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog3 ���b�Z�[�W �n���h��

void DeleteBookmarkDialog3::OnCancel() 
{
    int     ret;
    char    message1[BUFSIZ];
    char    message2[BUFSIZ];
    CString title;
    CString text;

    if ( m_messageOnCancel == "**" ) {
        title.LoadString(IDS_TTL_CANCEL_LOGIN_INFO);
        text.LoadString( IDS_TXT_CANCEL_LOGIN_INFO);
        strcpy( message1, text ); // ���[�U���A�p�X���[�h�̐ݒ�𒆎~���܂���?
        strcpy( message2, title );// ���O�C�����ݒ蒆�~
    }
    else {
        CString action;
        title.LoadString(IDS_TTL_CANCEL_LOGIN_INFO);
        text.LoadString( IDS_TXT_CANCEL_LOGIN_INFO);

        action.LoadString( IDS_DELETE );
        title.LoadString(IDS_TTL_CANCEL_PROCEDURE);
        text.LoadString( IDS_TXT_CANCEL_PROCEDURE);

        sprintf( message1,
                 text,  // �u�b�N�}�[�N��%s�𒆎~���܂���?
                 m_messageOnCancel == "" ? action   // �폜
                                         : (const char *)m_messageOnCancel );
        sprintf( message2,
                 title, // %s���s���~
                 m_messageOnCancel == "" ? action   // �폜
                                         : (const char *)m_messageOnCancel );
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        if ( pp->m_langCode != 0x0411 )
            message2[0] += ('A' - 'a');
    }
    ret = MessageBox( message1, message2, MB_YESNO|MB_ICONQUESTION );
    if ( ret == IDYES ) {
    	m_username = _T("");
	    m_password = _T("");
        CDialog::OnCancel();
    }
}

void DeleteBookmarkDialog3::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CStatic *p   = (CStatic *)GetDlgItem( IDC_DESCRIPTION );
        CString text = "";

        switch ( m_targetBookmark ) {
        case CUserInfo::BK_HATENA:
            text.LoadString(IDS_DSC_HATENA_BOOKMARK);
            break;
        case CUserInfo::BK_DELICIOUS:
            text.LoadString(IDS_DSC_DELICIOUS);
            break;
        case CUserInfo::BK_MM_MEMO:
            text.LoadString(IDS_DSC_MMMEMO);
            break;
        case CUserInfo::BK_DRECOM_RSS:
            text.LoadString(IDS_DSC_DRECOM_RSS);
            break;
        case CUserInfo::BK_FLOG:
            text.LoadString(IDS_DSC_FLOG);
            break;
        case CUserInfo::BK_LIVEDOOR_CLIP:
            text.LoadString(IDS_DSC_LIVEDOOR_CLIP);
            break;
        case CUserInfo::BK_ECNAVI_CLIP:
            text.LoadString(IDS_DSC_ECNAVI_CLIP);
            break;
        case CUserInfo::BK_NIFTY_CLIP:
            text.LoadString(IDS_DSC_NIFTY_CLIP);
            break;
        case CUserInfo::BK_1470NET:
            text.LoadString(IDS_DSC_1470NET);
            break;
        case CUserInfo::BK_POOKMARK:
            text.LoadString(IDS_DSC_POOKMARK);
            break;
        case CUserInfo::BK_BLUEDOT:
            text.LoadString(IDS_DSC_BLUEDOT);
            break;
        case CUserInfo::BK_JOLTMARK:
            text.LoadString(IDS_DSC_JOLTMARK);
            break;
        case CUserInfo::BK_FC2BOOKMARK:
            text.LoadString(IDS_DSC_FC2_BOOKMARK);
            break;
        case CUserInfo::BK_BLOGPET:
            text.LoadString(IDS_DSC_BLOGPET);
            break;
        case CUserInfo::BK_TWITTER:
            text.LoadString(IDS_DSC_TWITTER);
            break;
        case CUserInfo::BK_YJ_BOOKMARK:
            text.LoadString(IDS_DSC_YJBOOKMARK);
            break;
        case CUserInfo::BK_YAHOO_BOOKMARKS:
            text.LoadString(IDS_DSC_YAHOO_BOOKMARKS);
            break;
        case CUserInfo::BK_TIMELOG:
            text.LoadString(IDS_DSC_TIMELOG);
            break;
        case CUserInfo::BK_DIGG:
            text.LoadString(IDS_DSC_DIGG);
            break;
        case CUserInfo::BK_TUMBLR:
            text.LoadString(IDS_DSC_TUMBLR);
            break;
        case CUserInfo::BK_DIIGO:
            text.LoadString(IDS_DSC_DIIGO);
            break;
        }

        if ( text.GetLength() > 0 )
            p->SetWindowText( text );

        CEdit   *q;
        if ( m_username.GetLength() > 0 ) {
            q = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME );
            q->SetWindowText( m_username );
        }
        if ( m_password.GetLength() > 0 ) {
            q = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD );
            q->SetWindowText( m_password );
        }
    }
}

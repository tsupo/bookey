/*
 * CaptchaDialog.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CAPTCHA ���̓_�C�A���O �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  9 Jul 2007
 *
 * $Log: /comm/bookey/CaptchaDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     07/10/10 22:38 Tsujimura543
 * �摜���擾����̂� cookie ���K�v�ȏꍇ(���̂Ƃ���Adigg�̂�)�ɑΉ�
 * 
 * 6     07/07/10 19:34 Tsujimura543
 * inputCaptchaString() �̈����ǉ��Ƃ���ɔ����e��ύX(����2)
 * 
 * 5     07/07/10 1:01 Tsujimura543
 * inputCaptchaString() �̈����ǉ��Ƃ���ɔ����e��ύX
 * 
 * 4     07/07/09 22:20 Tsujimura543
 * OnShowWindow() ���C��
 * 
 * 3     07/07/09 21:50 Tsujimura543
 * (1) Topic �̑I����ǉ�
 * (2) inputCaptchaString() �̈�����ǉ�
 * 
 * 2     07/07/09 20:01 Tsujimura543
 * inputCaptchaString() ��ǉ�
 * 
 * 1     07/07/09 17:37 Tsujimura543
 * �V�K�쐬
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "CaptchaDialog.h"
#include "CImage.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/CaptchaDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptchaDialog �_�C�A���O

CCaptchaDialog::CCaptchaDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptchaDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaptchaDialog)
	m_captcha = _T("");
	m_title = _T("");
	m_comment = _T("");
	//}}AFX_DATA_INIT

    m_captchaImageURL = _T("");
    m_topic           = _T("");
    m_bitmap          = NULL;
    m_mode            = CAP_MAKE_STORY;
}

CCaptchaDialog::~CCaptchaDialog()
{
    if ( m_bitmap ) {
        DeleteObject( m_bitmap );
        m_bitmap = NULL;
    }
}

void CCaptchaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaptchaDialog)
	DDX_Control(pDX, IDC_COMBO_TOPIC, m_topicList);
	DDX_Text(pDX, IDC_EDIT_CAPTCHA, m_captcha);
	DDV_MaxChars(pDX, m_captcha, 128);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	DDV_MaxChars(pDX, m_title, 75);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_comment);
	DDV_MaxChars(pDX, m_comment, 256);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCaptchaDialog, CDialog)
	//{{AFX_MSG_MAP(CCaptchaDialog)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_TOPIC, OnSelchangeComboTopic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptchaDialog ���b�Z�[�W �n���h��

void CCaptchaDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        if ( m_captchaImageURL.GetLength() > 0 ) {
            CImage  img;

            m_bitmap = img.HttpOpen( m_captchaImageURL, m_cookie );
            if ( m_bitmap ) {
                CStatic *sp;
                sp = (CStatic *)GetDlgItem( IDC_BITMAP_CAPTCHA );
                sp->SetBitmap( m_bitmap );
            }
        }

        if ( m_mode == CAP_POST_COMMENT ) {
            CEdit   *ep = (CEdit *)GetDlgItem( IDC_EDIT_TITLE );
            ep->SetReadOnly( TRUE );

            m_topicList.EnableWindow( FALSE );
            int location = m_topicList.FindString( -1, m_topic );
            if ( location != CB_ERR )
                m_topicList.SetCurSel( location );
            else {
                m_topicList.AddString( m_topic );
                location = m_topicList.FindString( -1, m_topic );
                if ( location != CB_ERR )
                    m_topicList.SetCurSel( location );
            }
        }
    }
}

void CCaptchaDialog::OnSelchangeComboTopic() 
{
    int location = m_topicList.GetCurSel();
    if ( location >= 0 )
    	m_topicList.GetLBText( location, m_topic );
}

/////////////////////////////////////////////////////////////////////////////
// CCaptchaDialog ���p�֐�

char    *
inputCaptchaString( const char *url,
                    char       *cookie,
                    char       *captcha,
                    char       *title,
                    char       *comment,
                    char       *topic,
                    CAP_MODE   mode )
{
    int             ret;
    char            *p = captcha;
    CCaptchaDialog  dlg;

    dlg.m_captchaImageURL = url;
    dlg.m_cookie          = cookie;
    dlg.m_topic           = topic[0]   ? topic   : _T("");
    dlg.m_title           = title[0]   ? title   : _T("");
    dlg.m_comment         = comment[0] ? comment : _T("");
    dlg.m_mode            = mode;
    ret = dlg.DoModal();
    if ( ret == IDOK ) {
        if ( dlg.m_captcha.GetLength() > 0 )
            strcpy( captcha, dlg.m_captcha );
        if ( dlg.m_topic.GetLength() > 0 )
            strcpy( topic, dlg.m_topic );
        if ( dlg.m_title.GetLength() > 0 )
            strcpy( title, dlg.m_title );
        if ( dlg.m_comment.GetLength() > 0 )
            strcpy( comment, dlg.m_comment );
    }

    return ( p );
}

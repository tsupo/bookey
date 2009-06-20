/*
 * DeleteBookmarkDialog4.cpp : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その4 インプリメンテーション ファイル
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog4.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 10    08/04/15 15:07 Tsujimura543
 * コメントを修正
 * 
 * 9     08/04/15 15:05 Tsujimura543
 * title要素に &lt;, &gt;, &quot; が含まれる場合、デコードして表示する
 * ように変更
 * 
 * 8     07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks と Yahoo! ブックマークの「削除」に対応
 * 
 * 7     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 6     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 5     07/01/15 22:38 Tsujimura543
 * 英語モード対応
 * 
 * 4     06/09/04 18:15 Tsujimura543
 * 「1個前へ戻る」機能を追加
 * 
 * 3     05/10/11 19:08 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 2     05/10/03 22:17 Tsujimura543
 * del.icio.us のブックマークを削除する処理を実装
 */

#include "bookey.h"
#include "DeleteBookmarkDialog4.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteBookmarkDialog4.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog4 ダイアログ


DeleteBookmarkDialog4::DeleteBookmarkDialog4(CWnd* pParent /*=NULL*/)
	: CDialog(DeleteBookmarkDialog4::IDD, pParent)
{
	m_execute             = false;
	m_executeWithoutQuery = false;
    m_enableToBackward    = false;
    m_backToPrevious      = false;
    m_messageOnQuery      = "";
    m_windowTextExtra     = "";

	//{{AFX_DATA_INIT(DeleteBookmarkDialog4)
	m_url = _T("");
	m_title = _T("");
	m_tags = _T("");
	m_comment = _T("");
	//}}AFX_DATA_INIT
}


void DeleteBookmarkDialog4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeleteBookmarkDialog4)
	DDX_Text(pDX, IDC_EDIT_BM_URL, m_url);
	DDV_MaxChars(pDX, m_url, 512);
	DDX_Text(pDX, IDC_EDIT_BM_TITLE, m_title);
	DDV_MaxChars(pDX, m_title, 2048);
	DDX_Text(pDX, IDC_EDIT_BM_TAGS, m_tags);
	DDV_MaxChars(pDX, m_tags, 2048);
	DDX_Text(pDX, IDC_EDIT_BM_COMMENT, m_comment);
	DDV_MaxChars(pDX, m_comment, 2048);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DeleteBookmarkDialog4, CDialog)
	//{{AFX_MSG_MAP(DeleteBookmarkDialog4)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_YES, OnButtonDeleteYes)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_NO, OnButtonDeleteNo)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_DELETE_FORCELY, OnButtonDeleteForcely)
	ON_BN_CLICKED(IDC_BUTTON_BACKWORD, OnButtonBackword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog4 メッセージ ハンドラ

void DeleteBookmarkDialog4::OnButtonDeleteYes() 
{
	m_execute             = true;
	m_executeWithoutQuery = false;
    m_backToPrevious      = false;
    OnOK();
}

void DeleteBookmarkDialog4::OnButtonDeleteForcely() 
{
	m_execute             = true;
	m_executeWithoutQuery = true;
    m_backToPrevious      = false;
    OnOK();
}

void DeleteBookmarkDialog4::OnButtonDeleteNo() 
{
	m_execute        = false;
    m_backToPrevious = false;
    OnOK();
}

void DeleteBookmarkDialog4::OnButtonBackword() 
{
	m_execute        = false;
    m_backToPrevious = true;
    OnOK();
}

void DeleteBookmarkDialog4::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        if ( m_messageOnQuery != "" ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            char        tmp[BUFSIZ];
            CString     title;
            CString     text;
            CEdit       *p = (CEdit *)GetDlgItem( IDC_QUERY_MESSAGE );
            text.LoadString(IDS_TXT_EXECUTE_PROCEDURE);
            sprintf( tmp, text, (const char *)m_messageOnQuery );
            p->SetWindowText( tmp );    // このブックマークを%sしますか?

            CButton *q = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_YES );
            text.LoadString(IDS_BTN_EXECUTE_PROCEDURE); // %sする
            sprintf( tmp, text, (const char *)m_messageOnQuery );
            if ( pp->m_langCode != 0x0411 )
                tmp[0] += ('A' - 'a');
            q->SetWindowText( tmp );

            q = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_FORCELY );
            text.LoadString(IDS_BTN_EXECUTE_PROCEDURE_ALL); // 一気に%sする
            sprintf( tmp, text, (const char *)m_messageOnQuery );
            if ( pp->m_langCode != 0x0411 )
                tmp[0] += ('A' - 'a');
            q->SetWindowText( tmp );

            q = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_NO );
            text.LoadString(IDS_BTN_SKIP_PROCEDURE);    // %sしない
            if ( !strstr( text, "%s" ) )
                strcpy( tmp, text );
            else
                sprintf( tmp, text, (const char *)m_messageOnQuery );
            q->SetWindowText( tmp );

            q = (CButton *)GetDlgItem( IDCANCEL );
            text.LoadString(IDS_BTN_CANCEL_PROCEDURE);  // %s作業中止
            if ( !strstr( text, "%s" ) )
                strcpy( tmp, text );
            else
                sprintf( tmp, text, (const char *)m_messageOnQuery );
            q->SetWindowText( tmp );

            text.LoadString(IDS_TTL_EXECUTE_PROCEDURE); // ブックマークの%s
            sprintf( tmp, text, (const char *)m_messageOnQuery );
            if ( pp->m_langCode != 0x0411 )
                tmp[0] += ('A' - 'a');

            if ( m_windowTextExtra != "" )
                title = m_windowTextExtra + " " + tmp;
            else
                title = tmp;
            this->SetWindowText( title );

            if ( strchr( m_title, '&' ) ) {
                char    *ttl = new char[m_title.GetLength() + 1];
                strcpy( ttl, m_title );

                char    *pp = ttl;
                char    *qq;
                while ( ( qq = strstr( pp, "&lt;" ) ) != NULL ) {
                    *qq = '<';
                    strcpy( qq + 1, qq + 4 );
                }
                while ( ( qq = strstr( pp, "&gt;" ) ) != NULL ) {
                    *qq = '>';
                    strcpy( qq + 1, qq + 4 );
                }
                while ( ( qq = strstr( pp, "&quot;" ) ) != NULL ) {
                    *qq = '"';
                    strcpy( qq + 1, qq + 6 );
                }
                while ( ( qq = strstr( pp, "&amp;" ) ) != NULL )
                    strcpy( qq + 1, qq + 5 );

                m_title = ttl;

                CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BM_TITLE );
                p->SetWindowText( m_title );

                delete [] ttl;
            }
        }

        CButton *q = (CButton *)GetDlgItem( IDC_BUTTON_BACKWORD );
        q->EnableWindow( m_enableToBackward ? TRUE : FALSE );
    }
}

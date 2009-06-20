/*
 * DeleteBookmarkDialog3.cpp : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その3 インプリメンテーション ファイル
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog3.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 31    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 30    08/07/25 22:17 Tsujimura543
 * Diigo 対応準備
 * 
 * 29    07/10/31 17:08 Tsujimura543
 * digg と tumblr に対応
 * 
 * 28    07/05/23 16:03 Tsujimura543
 * Timelog 対応
 * 
 * 27    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 26    07/04/16 18:49 Tsujimura543
 * Twitter と Yahoo! ブックマーク に対応
 * 
 * 25    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 24    07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 23    07/01/16 21:35 Tsujimura543
 * 英語モード対応
 * 
 * 22    07/01/15 22:37 Tsujimura543
 * 英語モード対応準備
 * 
 * 21    07/01/11 17:01 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 20    06/12/22 21:47 Tsujimura543
 * コメント修正
 * 
 * 19    06/12/21 21:18 Tsujimura543
 * JoltMark、FC2BOOKMARK、「BlogPet 気になる記事」に対応
 * 
 * 18    06/10/26 22:52 Tsujimura543
 * コメントを修正
 * 
 * 17    06/10/26 22:51 Tsujimura543
 * POOKMARK Airlines と Blue Dot 用の文言を用意した
 * 
 * 16    06/08/23 21:33 Tsujimura543
 * 「1470.netリニューアル版」のときの文言を変更
 * 
 * 15    06/07/14 20:50 Tsujimura543
 * 1470.netリニューアル版に対応
 * 
 * 14    06/06/30 20:17 Tsujimura543
 * livedoorクリップ、ECナビ人気ニュース、ニフティクリップ用の文言を用意した
 * 
 * 13    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 12    06/06/01 19:20 Tsujimura543
 * break; 抜け(1箇所)、修正
 * 
 * 11    06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 10    06/06/01 19:04 Tsujimura543
 * ブックマーク種別を示す enum 値を、enum CUserInfo::bookmarkType に
 * 一本化した
 * 
 * 9     06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 8     06/03/29 18:30 Tsujimura543
 * ドリコムRSSへのブックマーク(Clip)登録に対応した
 * 
 * 7     05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 6     05/10/21 18:44 Tsujimura543
 * MM/Memo と BlogPeople に対応
 * 
 * 5     05/10/14 20:38 Tsujimura543
 * ドラッグ・アンド・ドロップ対応作業完了
 * 
 * 4     05/10/14 15:35 Tsujimura543
 * OnCancel() で表示する文言のバリエーションを追加
 * 
 * 3     05/10/11 16:56 Tsujimura543
 * ブックマーク同期処理の実装開始
 * 
 * 2     05/10/03 18:56 Tsujimura543
 * ブックマーク削除実行時に使う「ユーザ名、パスワード入力画面」を作成
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
// DeleteBookmarkDialog3 ダイアログ

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
// DeleteBookmarkDialog3 メッセージ ハンドラ

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
        strcpy( message1, text ); // ユーザ名、パスワードの設定を中止しますか?
        strcpy( message2, title );// ログイン情報設定中止
    }
    else {
        CString action;
        title.LoadString(IDS_TTL_CANCEL_LOGIN_INFO);
        text.LoadString( IDS_TXT_CANCEL_LOGIN_INFO);

        action.LoadString( IDS_DELETE );
        title.LoadString(IDS_TTL_CANCEL_PROCEDURE);
        text.LoadString( IDS_TXT_CANCEL_PROCEDURE);

        sprintf( message1,
                 text,  // ブックマークの%sを中止しますか?
                 m_messageOnCancel == "" ? action   // 削除
                                         : (const char *)m_messageOnCancel );
        sprintf( message2,
                 title, // %s実行中止
                 m_messageOnCancel == "" ? action   // 削除
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

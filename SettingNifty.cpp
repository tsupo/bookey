/*
 * SettingNifty.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(ニフティクリップ) インプリメンテーション ファイル
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingNifty.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    08/11/13 13:25 Tsujimura543
 * 「Powered by @nifty クリップ」に下線が引かれていなかったのを修正
 * 
 * 13    08/11/05 17:30 Tsujimura543
 * 「APIキー設定」ボタン押下時処理を修正
 * 
 * 12    08/11/05 17:29 Tsujimura543
 * 他のサービスの設定画面と@niftyクリップの設定画面を行ったり来たりする
 * とアプリケーションエラーで落ちる不具合を修正
 * 
 * 11    08/11/04 16:46 Tsujimura543
 * 「APIキー設定」ボタンを追加
 * 
 * 10    07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 9     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 8     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 7     07/02/16 13:56 Tsujimura543
 * ニフティクリップに登録したブックマークのタイトルは共有ではなく、各自が
 * 独自のものを設定可能なことが判明したため、常に「独自のタイトルで上書き
 * する」ように処理自体と関連する設定画面を作り直した
 * 
 * 6     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 5     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 4     06/09/29 18:57 Tsujimura543
 * RCS(VSS)の Header 情報を埋め込み忘れていたので、改めて埋め込んでみた
 * 
 * 3     06/07/31 17:14 Tsujimura543
 * ソースの整理 (コメント追加、余分な改行・空白の削除、など)
 * 
 * 2     06/07/31 17:03 Tsujimura543
 * 設定ダイアログを OK ボタン押下で終了すると、それまでにタブをクリックして
 * いなかったブックマークサービスの設定内容が破壊されてしまう不具合に対処
 * 
 * 1     06/07/28 23:00 Tsujimura543
 * 新規作成 (タブ切り替え式の「設定ダイアログ」を作成、導入した)
 */

#include "bookey.h"
#include "SettingNifty.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingNifty.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// SettingNifty ダイアログ

SettingNifty::SettingNifty(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingNifty::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingNifty)
	m_apiKey = _T("");
	//}}AFX_DATA_INIT

    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
    m_initialized2 = false;
}

SettingNifty::~SettingNifty()
{
    m_cFont.DeleteObject();
}

void SettingNifty::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingNifty)
	DDX_Text(pDX, IDC_EDIT_APIKEY, m_apiKey);
	DDV_MaxChars(pDX, m_apiKey, 64);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingNifty::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_niftyClip.m_username = m_username;
        pp->m_niftyClip.m_password = m_password;
        if ( m_apiKey.GetLength() > 0)
            pp->m_niftyClip.m_apiKey = m_apiKey;
        pp->m_niftyClip = m_isTarget;
    }
}

void SettingNifty::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_niftyClip.m_username;
        m_password = pp->m_niftyClip.m_password;
        if ( pp->m_niftyClip.m_apiKey.GetLength() > 0 )
            m_apiKey = pp->m_niftyClip.m_apiKey;
        m_isTarget = (bool)(pp->m_niftyClip);
    }
}

BEGIN_MESSAGE_MAP(SettingNifty, CTabDialog)
	//{{AFX_MSG_MAP(SettingNifty)
	ON_BN_CLICKED(IDC_BUTTON_APIKEY, OnButtonApikey)
	ON_BN_CLICKED(IDC_POWEREDBY_NIFTYCLIP, OnPoweredByNiftyclip)
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingNitty メッセージ ハンドラ

void SettingNifty::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
    if ( bShow ) {
        p->SetWindowText( m_apiKey );

        if ( !m_initialized2 ) {
            // 「Powered by @nifty クリップ」を下線付きで表示する
            LOGFONT tLogFont;
            CFont   *cWndFont;

            cWndFont = GetFont(); 
            cWndFont->GetLogFont( &tLogFont );
            tLogFont.lfUnderline = 1;
            m_cFont.CreateFontIndirect( &tLogFont );

            CStatic *s = (CStatic *)GetDlgItem( IDC_POWEREDBY_NIFTYCLIP );
            s->SetFont( &m_cFont, TRUE );

            m_initialized2 = true;
        }
    }
    else
        p->GetWindowText( m_apiKey );
}

BOOL SettingNifty::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // 「Powered by @nifty クリップ」にマウスポインタが来たら、
        // 指カーソルを表示する
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_POWEREDBY_NIFTYCLIP );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

	return CTabDialog::OnSetCursor(pWnd, nHitTest, message);
}

void SettingNifty::OnButtonApikey() 
{
    if ( (m_username.GetLength() > 0) && (m_password.GetLength() > 0)) {
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        char        apiKey[MAX_KEYLENGTH];

        apiKey[0] = NUL;
        getApiKeyOnNiftyClip( m_username, m_password, apiKey );
        if ( apiKey[0] ) {
            m_apiKey = apiKey;

            CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
            p->SetWindowText( m_apiKey );
        }
    }
}

void SettingNifty::OnPoweredByNiftyclip() 
{
	CString cmd;
	cmd.LoadString( IDS_URL_NIFTYCLIP );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

/*
 * SettingLivedoor.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(livedoorクリップ) インプリメンテーション ファイル
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingLivedoor.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    08/07/28 17:06 Tsujimura543
 * 設定したはずの apiKey が bookey の再起動時に消えてしまう
 * 不具合を修正
 * 
 * 11    08/07/28 15:37 Tsujimura543
 * OnButtonApiKey() 実行中は砂時計カーソルを表示するようにした
 * 
 * 10    08/07/28 15:29 Tsujimura543
 * 「APIキー」関連、追加
 * 
 * 9     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 7     07/02/16 13:57 Tsujimura543
 * コメントを修正
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
#include "SettingLivedoor.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingLivedoor.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingLivedoor ダイアログ

SettingLivedoor::SettingLivedoor(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingLivedoor::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingLivedoor)
	m_apiKey = _T("");
	//}}AFX_DATA_INIT
}

void SettingLivedoor::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingLivedoor)
	DDX_Text(pDX, IDC_EDIT_APIKEY, m_apiKey);
	DDV_MaxChars(pDX, m_apiKey, 64);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingLivedoor::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_livedoorClip.m_username = m_username;
        pp->m_livedoorClip.m_password = m_password;
        if ( m_apiKey.GetLength() > 0)
            pp->m_livedoorClip.m_apiKey = m_apiKey;
        pp->m_livedoorClip = m_isTarget;
    }
}

void SettingLivedoor::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_livedoorClip.m_username;
        m_password = pp->m_livedoorClip.m_password;
        if ( pp->m_livedoorClip.m_apiKey.GetLength() > 0 )
            m_apiKey = pp->m_livedoorClip.m_apiKey;
        m_isTarget = (bool)(pp->m_livedoorClip);
    }
}

BEGIN_MESSAGE_MAP(SettingLivedoor, CTabDialog)
	//{{AFX_MSG_MAP(SettingLivedoor)
	ON_BN_CLICKED(IDC_BUTTON_APIKEY, OnButtonApiKey)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingLivedoor メッセージ ハンドラ

void SettingLivedoor::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
    if ( bShow )
        p->SetWindowText( m_apiKey );
    else
        p->GetWindowText( m_apiKey );
}

void SettingLivedoor::OnButtonApiKey() 
{
    if ( (m_username.GetLength() > 0) && (m_password.GetLength() > 0)) {
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        char        apiKey[MAX_KEYLENGTH];

        apiKey[0] = NUL;
        getApiKeyOnLivedoorClip( m_username, m_password, apiKey );
        if ( apiKey[0] ) {
            m_apiKey = apiKey;

            CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_APIKEY);
            p->SetWindowText( m_apiKey );
        }
    }
}

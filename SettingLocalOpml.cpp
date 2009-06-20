/*
 * SettingLocalOpml.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(ローカルOPMLファイル) インプリメンテーション ファイル
 *          written by H.Tsujimura  26 Sep 2006
 *
 * $Log: /comm/bookey/SettingLocalOpml.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 7     07/04/10 19:57 Tsujimura543
 * コンストラクタで m_initialized を初期化するのを忘れていた
 * 
 * 6     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 5     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 4     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 3     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 2     07/01/12 23:50 Tsujimura543
 * 英語モード対応
 * 
 * 1     06/10/26 21:00 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "bookey.h"
#include "SettingLocalOpml.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingLocalOpml.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingLocalOpml ダイアログ

SettingLocalOpml::SettingLocalOpml(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingLocalOpml::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingLocalOpml)
	m_filename = _T("");
	//}}AFX_DATA_INIT
}

void SettingLocalOpml::DoDataExchange(CDataExchange* pDX)
{
    // ↓ CTabDialog ではなく、CDialog にしているのは、 SettingLocalOpml には
    // ↓ m_username, m_pasword を入力するための CEdit コントロールが存在しな
    // ↓ いため
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingLocalOpml)
	DDX_Text(pDX, IDC_EDIT_LOCALOPML_FILENAME, m_filename);
	DDV_MaxChars(pDX, m_filename, 384);
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingLocalOpml::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_localOpml.m_username     = "";
        pp->m_localOpml.m_password     = "";
        pp->m_localOpml.m_opmlFilename = m_filename;
        pp->m_localOpml = m_isTarget;
    }
}

void SettingLocalOpml::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_filename = pp->m_localOpml.m_opmlFilename;
        m_isTarget = (bool)(pp->m_localOpml);
    }
}

// CTabDialog::OnRadioTarget(), CTabDialog::OnRadioNontarget() を使いたいので
// CTabDialog を指定している         ↓
BEGIN_MESSAGE_MAP(SettingLocalOpml, CTabDialog)
	//{{AFX_MSG_MAP(SettingLocalOpml)
	ON_BN_CLICKED(IDC_BUTTON_FILEOPEN, OnButtonFileopen)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingLocalOpml メッセージ ハンドラ

void SettingLocalOpml::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
    // ↑ CTabDialog ではなく、CDialog にしているのは、 SettingLocalOpml には
    // ↑ m_username, m_pasword を入力するための CEdit コントロールが存在しな
    // ↑ いため

    if ( bShow ) {
        LoadSetting();

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_LOCALOPML_FILENAME );
        p->SetWindowText( m_filename );

        SetIsTarget();

        m_initialized = true;
    }
    else {
        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_LOCALOPML_FILENAME );
        p->GetWindowText( m_filename );
    }
}

void SettingLocalOpml::OnButtonFileopen() 
{
    // ファイル選択ダイアログを表示、OPMLファイルを選択
    CFileDialog *fileDlg;
    CString     fileType;

    fileType.LoadString( IDS_FILETYPE_OPML );
    fileDlg = new CFileDialog( TRUE, "opml", m_filename,
                               OFN_EXPLORER,
                               fileType );
    if ( fileDlg->DoModal() == IDOK )
        m_filename = fileDlg->GetPathName();
    else
        m_filename = _T("");

    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_LOCALOPML_FILENAME );
    p->SetWindowText( m_filename );

    delete fileDlg;
}

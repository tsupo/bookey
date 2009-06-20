/*
 * bookeyDlg.cpp : ソーシャルブックマーク管理プログラム
 *      メインダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookeyDlg.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 84    08/10/22 13:34 Tsujimura543
 * コメントを修正
 * 
 * 83    08/10/22 13:33 Tsujimura543
 * IDM_ABOUT_SUPPORT, IDM_ABOUT_SUPPORT2,
 * IDM_ABOUT_COMMUNITY, IDM_ABOUT_COMMUNITY2
 * の定義を AboutDlg.h へ移管
 * 
 * 82    08/10/21 22:04 Tsujimura543
 * ABOUT_SUPPORT2 を追加
 * 
 * 81    08/10/21 21:24 Tsujimura543
 * ABOUT_SUPPORT, ABOUT_COMMUNITY, ABOUT_COMMUNITY2 追加
 * 
 * 80    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 79    08/07/25 22:16 Tsujimura543
 * Diigo 対応
 * 
 * 78    07/04/20 20:34 Tsujimura543
 * Yahoo! ブックマーク、Yahoo! Bookmarks のインポートとエクスポートに対応
 * 
 * 77    07/04/16 18:23 Tsujimura543
 * コメントを修正
 * 
 * 76    07/04/16 17:59 Tsujimura543
 * del.icio.us の posts/all 形式の XML ファイルのインポートとエクスポート
 * に対応した
 * 
 * 75    07/04/11 17:03 Tsujimura543
 * 版数情報はリソースファイルから持ってきたのを表示するようにしてみた
 * 
 * 74    07/03/29 15:18 Tsujimura543
 * FC2BOOKMARK に対応した
 * 
 * 73    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 72    07/01/30 0:33 Tsujimura543
 * EnableButton() を変更し、「タグの削除」、「タグの置換」ボタンの制御にも
 * 対応した
 * 
 * 71    07/01/24 20:55 Tsujimura543
 * 「タグの削除」と「タグの置換」ボタンを各々追加
 * 
 * 70    07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 69    07/01/15 22:35 Tsujimura543
 * 英語モード対応
 * 
 * 68    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 67    07/01/11 17:01 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 66    06/12/22 21:44 Tsujimura543
 * 「BlogPet 気になる記事」対応
 * 
 * 65    06/12/21 19:18 Tsujimura543
 * JoltMark 対応
 * 
 * 64    06/12/06 19:48 Tsujimura543
 * コメントを修正
 * 
 * 63    06/12/06 19:46 Tsujimura543
 * livedoor Clip のエクスポートファイル(RSS 2.0 形式)をインポートする機能
 * を追加した
 * 
 * 62    06/11/27 16:03 Tsujimura543
 * POOKMARK Airlines からのブックマーク取得に関して、パスワード指定なし
 * の場合も(公開されているものに限って)取得できるようにする
 * 
 * 61    06/11/16 16:43 Tsujimura543
 * CUserInfo 導入によるリファクタリング第16段階、終了
 * 
 * 60    06/11/16 14:06 Tsujimura543
 * CBookeyDlg クラス内のメンバ変数のうち、もはや不要になったものを削除
 * 
 * 59    06/11/16 14:02 Tsujimura543
 * CUserInfo 導入によるリファクタリング第15段階、終了
 * 
 * 58    06/11/15 20:59 Tsujimura543
 * はてなブックマークのエクスポート形式のうち、RSS/Atomフィード形式の
 * ファイルからのブックマーク情報のインポートにも対応した (html形式の
 * ファイルはすでに対応済み)
 * 
 * 57    06/11/14 19:18 Tsujimura543
 * opera6.adr 形式のファイルを読み書きするときのファイルダイアログで
 * 表示するファイル種別を「Opera ブックマークファイル」に変更
 * 
 * 56    06/11/10 19:26 Tsujimura543
 * ブラウザのブックマークを取り込む/ブラウザに取り込める形式のブックマーク
 * ファイルを生成する機能をサポートするための準備
 * 
 * 55    06/10/18 19:41 Tsujimura543
 * BlueDot に関して、任意のユーザのブックマークを取得できるようにした
 * 
 * 54    06/10/10 16:52 Tsujimura543
 * OnButtonPut() 内で title を Shift_JIS から UTF-8 に変換する処理を削除
 * (outputOpml() 内でも変換しているため、二重に変換してしまって文字化け
 * が発生することがあることが判明したため、修正を実施)
 * 
 * 53    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 52    06/10/05 20:01 Tsujimura543
 * POOKMARK Airlines に対応
 * 
 * 51    06/08/26 0:30 Tsujimura543
 * コメントを修正
 * 
 * 50    06/08/26 0:10 Tsujimura543
 * 1470.netリニューアル版の「取得」、「同期」に対応
 * (1470.netリニューアル版に関しては OPML 形式以外での出力に対応することも
 * 検討中。OPML 形式では全ての情報を保存し切れないため)
 * 
 * 49    06/08/23 22:19 Tsujimura543
 * 1470.netリニューアル版の「同期」時にユーザ情報を設定した場合も、
 * その設定内容を初期設定ファイルに反映できるようにした
 * 
 * 48    06/08/23 22:10 Tsujimura543
 * 1470.netリニューアル版の「削除」時にユーザ情報を設定した場合、
 * その設定内容を初期設定ファイルに反映できるようにした
 * 
 * 47    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 46    06/08/22 11:43 Tsujimura543
 * DeleteBookmarkDialog と DeleteBookmarkDialog2 を1個のダイアログに
 * まとめた (DeleteBookmarkDialog2 は廃止)
 * 
 * 45    06/07/19 14:19 Tsujimura543
 * MyClip! 関係の処理を削除 (2006年6月末でサービス終了のため)
 * 
 * 44    06/07/15 0:56 Tsujimura543
 * 1470.netリニューアル版への「登録」に対応
 * 
 * 43    06/07/12 17:34 Tsujimura543
 * ドリコムRSS(のClip!)の取得、同期に対応
 * 
 * 42    06/07/07 19:34 Tsujimura543
 * ニフティクリップの取得、同期に対応
 * 
 * 41    06/07/06 19:53 Tsujimura543
 * livedoorクリップの取得、同期に対応
 * 
 * 40    06/06/30 19:43 Tsujimura543
 * ECナビ人気ニュースの取得、同期に対応
 * 
 * 39    06/06/29 18:47 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 38    06/06/29 0:51 Tsujimura543
 * livedoorクリップへの登録をしようとしても、登録ボタンが disable のまま
 * 変化しない不具合に対処
 * 
 * 37    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 36    06/06/23 21:50 Tsujimura543
 * Flog の取得、同期に対応した
 * 
 * 35    06/06/22 21:21 Tsujimura543
 * inquery → inquiry に修正(綴りミス)
 * 
 * 34    06/06/20 14:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第9段階、終了
 * 
 * 33    06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 32    06/06/15 12:51 Tsujimura543
 * EnableButton() を追加
 * 
 * 31    06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 30    06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 29    06/06/06 22:23 Tsujimura543
 * CUserInfo 導入によるリファクタリング第2段階、終了
 * 
 * 28    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 27    06/06/01 22:20 Tsujimura543
 * CUserInfo 導入によるリファクタリング第1段階、終了
 * 
 * 26    06/06/01 20:28 Tsujimura543
 * CBookeyDlg 内のユーザ名、パスワードを CUserInfo を使って管理する
 * ように変更した
 * 
 * 25    06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 24    06/06/01 19:04 Tsujimura543
 * ブックマーク種別を示す enum 値を、enum CUserInfo::bookmarkType に
 * 一本化した
 * 
 * 23    06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 22    06/05/23 17:22 Tsujimura543
 * ソースを少し整形
 * 
 * 21    06/05/22 19:31 Tsujimura543
 * 「同期」対象のブックマーク取得に失敗した場合は、再度取得を試みるかどう
 * か訊くようにした
 * 
 * 20    06/04/07 14:01 Tsujimura543
 * ドリコムRSS(の Clip!)へのブックマークの登録(インポート)に対応した
 * 
 * 19    06/03/13 16:48 Tsujimura543
 * CBookeyDlg::OnButtonSync() を修正 (MM/Memo → 他のブックマーク コピー時
 * に文字化けする不具合に対処)
 * 
 * 18    06/02/17 22:02 Tsujimura543
 * 4つのブックマークサービスのうち、任意の2者間で同期が取れるようにした
 * 
 * 17    06/02/17 18:07 Tsujimura543
 * ブックマークの同期を、はてなブックマークとdel.icio.us以外にも容易に対応
 * 可能にするため、処理の抽象化を進めた
 * 
 * 16    06/02/08 19:29 Tsujimura543
 * ブックマーク間同期指示ダイアログとの間のインターフェースを変更
 * 
 * 15    05/11/10 22:25 Tsujimura543
 * 進行状況表示ダイアログを使うようにした
 * 
 * 14    05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 13    05/10/31 22:11 Tsujimura543
 * BlogPeople Tags の削除をサポート (動作確認済み)
 * 
 * 12    05/10/21 18:57 Tsujimura543
 * MM/Memo と BlogPeople のユーザ名、パスワードも bookeyView から
 * 受け取れるようにした
 * 
 * 11    05/10/20 23:41 Tsujimura543
 * (1) MM/Memo からのブックマークの吸出し(取得)に対応
 * (2) MM/Memo, BlogPeople Tags へのブックマークの登録に対応
 * 
 * 10    05/10/15 0:41 Tsujimura543
 * はてなとdel.icio.usのユーザ名、パスワードを bookeyView から受け取れる
 * ようにした
 * 
 * 9     05/10/14 14:20 Tsujimura543
 * CAboutDlg を別ファイルへ分離、独立させた
 * 
 * 8     05/10/11 19:08 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 7     05/10/11 16:56 Tsujimura543
 * ブックマーク同期処理の実装開始
 * 
 * 6     05/10/03 22:59 Tsujimura543
 * はてなブックマークを削除する処理を実装
 * 
 * 5     05/10/03 22:17 Tsujimura543
 * del.icio.us のブックマークを削除する処理を実装
 * 
 * 4     05/10/03 21:02 Tsujimura543
 * ブックマーク削除処理の実装開始
 * 
 * 3     05/10/03 12:34 Tsujimura543
 * OPMLファイルの出力時、title要素が空になってしまうことがある不具合を修正
 * 
 * 2     05/10/01 0:00 Tsujimura543
 * ブックマークの取得、登録機能の動作確認完了
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "AboutDlg.h"
#include "DeleteBookmarkDialog.h"
#include "DeleteBookmarkDialog3.h"
#include "SynchronizeBookmarkDialog.h"
#include "exportBookmark.h"
#include "DeleteTagsDialog.h"
#include "ReplaceTagsDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookeyDlg.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg ダイアログ

CBookeyDlg::CBookeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBookeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBookeyDlg)
	m_bookmark1 = _T("");
	m_bookmark2 = _T("");
	m_password1 = _T("");
	m_password2 = _T("");
	m_username1 = _T("");
	m_username2 = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_needToSave = false;

    m_tgt_hatenaBookmark.LoadString( IDS_TGT_HATENA_BOOKMARK );
    m_tgt_delicious.LoadString( IDS_TGT_DELICIOUS );
    m_tgt_mmMemo.LoadString( IDS_TGT_MMMEMO );
    m_tgt_drecomRSS.LoadString( IDS_TGT_DRECOM_RSS );
    m_tgt_flog.LoadString( IDS_TGT_FLOG );
    m_tgt_livedoorClip.LoadString( IDS_TGT_LIVEDOOR_CLIP );
    m_tgt_ecNaviClip.LoadString( IDS_TGT_ECNAVI_CLIP );
    m_tgt_niftyClip.LoadString( IDS_TGT_NIFTY_CLIP );
    m_tgt_1470net.LoadString( IDS_TGT_1470NET );
    m_tgt_pookmark.LoadString( IDS_TGT_POOKMARK );
    m_tgt_blueDot.LoadString( IDS_TGT_BLUEDOT );
    m_tgt_joltMark.LoadString( IDS_TGT_JOLTMARK );
    m_tgt_blogPet.LoadString( IDS_TGT_BLOGPET );
    m_tgt_fc2bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
    m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
    m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_opml.LoadString( IDS_TGT_OPML );
    m_tgt_netscape1.LoadString( IDS_TGT_NETSCAPE_1 );
    m_tgt_opera6.LoadString( IDS_TGT_OPERA_6 );
    m_tgt_hatenaFeed.LoadString( IDS_TGT_HATENA_FEED );
    m_tgt_livedoorFeed.LoadString( IDS_TGT_LIVEDOOR_FEED );
    m_tgt_deliciousXML.LoadString( IDS_TGT_DELICIOUS_XML );
}

void CBookeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookeyDlg)
	DDX_Control(pDX, IDC_COMBO_BOOKMARK2, m_bookmarkList2);
	DDX_Control(pDX, IDC_COMBO_BOOKMARK1, m_bookmarkList1);
	DDX_CBString(pDX, IDC_COMBO_BOOKMARK1, m_bookmark1);
	DDV_MaxChars(pDX, m_bookmark1, 32);
	DDX_CBString(pDX, IDC_COMBO_BOOKMARK2, m_bookmark2);
	DDV_MaxChars(pDX, m_bookmark2, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD1, m_password1);
	DDV_MaxChars(pDX, m_password1, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD2, m_password2);
	DDV_MaxChars(pDX, m_password2, 32);
	DDX_Text(pDX, IDC_EDIT_USERNAME1, m_username1);
	DDV_MaxChars(pDX, m_username1, 32);
	DDX_Text(pDX, IDC_EDIT_USERNAME2, m_username2);
	DDV_MaxChars(pDX, m_username2, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBookeyDlg, CDialog)
	//{{AFX_MSG_MAP(CBookeyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_PUT, OnButtonPut)
	ON_BN_CLICKED(IDC_BUTTON_SYNC, OnButtonSync)
	ON_CBN_SELCHANGE(IDC_COMBO_BOOKMARK1, OnSelchangeComboBookmark1)
	ON_CBN_SELCHANGE(IDC_COMBO_BOOKMARK2, OnSelchangeComboBookmark2)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD1, OnKillfocusEditPassword1)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD2, OnKillfocusEditPassword2)
	ON_EN_KILLFOCUS(IDC_EDIT_USERNAME1, OnKillfocusEditUsername1)
	ON_EN_KILLFOCUS(IDC_EDIT_USERNAME2, OnKillfocusEditUsername2)
	ON_EN_UPDATE(IDC_EDIT_USERNAME1, OnUpdateEditUsername1)
	ON_EN_UPDATE(IDC_EDIT_PASSWORD1, OnUpdateEditPassword1)
	ON_EN_UPDATE(IDC_EDIT_USERNAME2, OnUpdateEditUsername2)
	ON_EN_UPDATE(IDC_EDIT_PASSWORD2, OnUpdateEditPassword2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_TAGS, OnButtonEditTags)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_TAGS, OnButtonDeleteTags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg 追加メソッド

void    CBookeyDlg::ChangeButtonGet()
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET );

    if ( !m_bookmark1.Compare( m_tgt_opml )                         ||
         !m_bookmark1.Compare( m_tgt_netscape1 )                    ||
         !m_bookmark1.Compare( m_tgt_opera6 )                       ||
         !m_bookmark1.Compare( m_tgt_hatenaFeed )                   ||
         !m_bookmark1.Compare( m_tgt_livedoorFeed )                 ||
         !m_bookmark1.Compare( m_tgt_deliciousXML )                 ||
         ( (m_username1.GetLength() > 0)                       &&
           ( !m_bookmark1.Compare( m_tgt_hatenaBookmark ) ||
             !m_bookmark1.Compare( m_tgt_flog )           ||
             !m_bookmark1.Compare( m_tgt_livedoorClip )   ||
             !m_bookmark1.Compare( m_tgt_ecNaviClip )     ||
             !m_bookmark1.Compare( m_tgt_niftyClip )      ||
             !m_bookmark1.Compare( m_tgt_pookmark )       ||
             !m_bookmark1.Compare( m_tgt_blueDot )        ||
             !m_bookmark1.Compare( m_tgt_joltMark )       ||
             !m_bookmark1.Compare( m_tgt_blogPet )        ||
             !m_bookmark1.Compare( m_tgt_fc2bookmark )    ||
             !m_bookmark1.Compare( m_tgt_yjBookmark )     ||
             !m_bookmark1.Compare( m_tgt_yahooBookmarks ) ||
             !m_bookmark1.Compare( m_tgt_diigo )          ||
             (m_password1.GetLength() > 0)                   )    )    )
        p->EnableWindow( TRUE );
    else
        p->EnableWindow( FALSE );
}

void    CBookeyDlg::ChangeButtonPut()
{
    CButton     *p  = (CButton *)GetDlgItem( IDC_BUTTON_PUT );
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    if ( (pp->m_bookmarkGotten || pp->m_myClip)            &&
         ( !m_bookmark2.Compare( m_tgt_opml )         ||
           !m_bookmark2.Compare( m_tgt_netscape1 )    ||
           !m_bookmark2.Compare( m_tgt_opera6 )       ||
           !m_bookmark2.Compare( m_tgt_deliciousXML ) ||
           ( (m_username2.GetLength() > 0) && 
             (m_password2.GetLength() > 0)    )          )    )
        p->EnableWindow( TRUE );
    else
        p->EnableWindow( FALSE );
}

void    CBookeyDlg::EnableButton( bool enable )
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET );
    if ( enable == false )
        p->EnableWindow( FALSE );
    else
        ChangeButtonGet();

    p = (CButton *)GetDlgItem( IDC_BUTTON_PUT );
    if ( enable == false )
        p->EnableWindow( FALSE );
    else
        ChangeButtonPut();

    p = (CButton *)GetDlgItem( IDC_BUTTON_SYNC );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_EDIT_TAGS );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_TAGS );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDOK );
    p->EnableWindow( enable ? TRUE : FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyDlg メッセージ ハンドラ

BOOL CBookeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
        pSysMenu->AppendMenu(MF_SEPARATOR);
        CString strAboutMenu0;
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_SUPPORT2);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_SUPPORT2, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY, strAboutMenu0);
		strAboutMenu0.LoadString(IDS_ABOUT_COMMUNITY2);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_COMMUNITY2, strAboutMenu0);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);     // 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);    // 小さいアイコンを設定
	
    ChangeButtonGet();
    ChangeButtonPut();

    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME1 );
    p->EnableWindow( FALSE );
    p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD1 );
    p->EnableWindow( FALSE );
	
    p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME2 );
    p->EnableWindow( FALSE );
    p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD2 );
    p->EnableWindow( FALSE );

    CString str;
    CStatic *s;
    str.LoadString( IDS_BOOKEY_VERSION );
    str = "bookey Ver " + str;
    s = (CStatic *)GetDlgItem( IDC_BOOKEY_VERSION );
    s->SetWindowText( str );

    return TRUE;
}

void CBookeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CString cmd = "";

    switch (nID & 0xFFF0) {
    case IDM_ABOUTBOX:
        switch (nID) {
        case IDM_ABOUTBOX: {
            CAboutDlg dlgAbout;
            dlgAbout.DoModal(); }
            break;

        case IDM_ABOUT_SUPPORT:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_WEB_URL );
            /* fall into ... */
        case IDM_ABOUT_SUPPORT2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_SUPPORT );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_COMMUNITY );
            /* fall into ... */
        case IDM_ABOUT_COMMUNITY2:
            if (cmd.IsEmpty())
    	        cmd.LoadString( IDS_BOOKEY_COMMUNITY2 );
            ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
            break;
        }
        break;

    default:
		CDialog::OnSysCommand(nID, lParam);
        break;
    }
}

void CBookeyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width()  - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CBookeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBookeyDlg::OnButtonGet() 
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    /* ブックマークの取得 */
    if ( !m_bookmark1.Compare( m_tgt_opml )         ||
         !m_bookmark1.Compare( m_tgt_netscape1 )    ||
         !m_bookmark1.Compare( m_tgt_opera6 )       ||
         !m_bookmark1.Compare( m_tgt_hatenaFeed )   ||
         !m_bookmark1.Compare( m_tgt_livedoorFeed ) ||
         !m_bookmark1.Compare( m_tgt_deliciousXML )    ) {
        EnableButton( false );
        bool    ret = pp->GetBookmarks( m_bookmark1 );
        EnableButton( true );

        if ( ret == false )
            return;
    }
    else {
        if ( m_username1.GetLength() == 0 )
            return;
        if ( (m_password1.GetLength() == 0)                 &&
             ( !m_bookmark1.Compare( m_tgt_delicious ) ||
               !m_bookmark1.Compare( m_tgt_mmMemo )    ||
               !m_bookmark1.Compare( m_tgt_drecomRSS )    )    )
            return;
        if ( strchr( m_username1, '@' )                      &&
             (m_password1.GetLength() == 0)                  &&
             ( !m_bookmark1.Compare( m_tgt_flog )       ||
               !m_bookmark1.Compare( m_tgt_ecNaviClip )    )    )
            return;

        EnableButton( false );
        pp->GetBookmarks( m_bookmark1, m_username1, m_password1 );
        EnableButton( true );
    }

    if ( pp->m_myClip )
        ChangeButtonPut();
    else {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS);
        text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS);
        MessageBox( text,   // ブックマーク情報を取得できませんでした
                    title,  // ブックマーク取得失敗
                    MB_OK|MB_ICONWARNING );
    }
}

void CBookeyDlg::OnButtonPut() 
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    if ( !(pp->m_myClip) )
        return;

    /* ブックマークの登録 */
    EnableButton( false );
    if ( !m_bookmark2.Compare( m_tgt_opml )         ||
         !m_bookmark2.Compare( m_tgt_netscape1 )    ||
         !m_bookmark2.Compare( m_tgt_opera6 )       ||
      /* !m_bookmark2.Compare( m_tgt_hatenaFeed )   || */
         !m_bookmark2.Compare( m_tgt_deliciousXML )    )
        pp->PutBookmarks( m_bookmark2, m_bookmark1 );
    else
        pp->PutBookmarks( m_bookmark2, m_username2, m_password2 );
    EnableButton( true );
}

void CBookeyDlg::OnButtonSync() 
{
    EnableButton( false );

    SynchronizeBookmarkDialog   dlg;
    int ret = dlg.DoModal();
    if ( ret != IDOK ) {
        EnableButton( true );
        return;
    }

    MyClip      *myBookmark1 = NULL;
    MyClip      *myBookmark2 = NULL;
    int         numOfBookmark1 = 0;
    int         numOfBookmark2 = 0;
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    bool        cont;

    m_needToSave = false;
    if ( ((dlg.m_bookmark1.Compare(m_tgt_1470net) == 0) ||
          (dlg.m_bookmark2.Compare(m_tgt_1470net) == 0)   ) &&
         (pp->m_next1470net.m_username.GetLength() == 0)       )
        m_needToSave = true;

    /* ユーザ名、パスワードの取得 */
    CString txt;
    txt.LoadString( IDS_SYNCHRONIZE );  // 同期
    cont = pp->InquiryUserInfo( dlg.m_bookmark1, dlg.m_bookmark2, txt );
    if ( cont == false ) {
        m_needToSave = false;
        EnableButton( true );
        return;
    }

    /* ブックマークの全取得 */
    cont = pp->ExportFromAnother( dlg.m_bookmark1, dlg.m_bookmark2,
                                  &myBookmark1,    &myBookmark2,
                                  &numOfBookmark1, &numOfBookmark2 );
    if ( cont == false ) {
        m_needToSave = false;
        EnableButton( true );
        return;
    }

    /* ブックマークの登録 */
    pp->ImportFromAnotherToOne( dlg.m_bookmark1, dlg.m_bookmark2,
                                myBookmark1,     myBookmark2,
                                numOfBookmark1,  numOfBookmark2,
                                dlg.m_direction );

    if ( m_needToSave ) {
        if (((dlg.m_bookmark1.Compare(m_tgt_1470net) == 0) ||
             (dlg.m_bookmark2.Compare(m_tgt_1470net) == 0)   ) &&
            (pp->m_next1470net.m_username.GetLength() == 0)       )
            m_needToSave = false;
    }

    EnableButton( true );
}

void CBookeyDlg::OnButtonDelete() 
{
    EnableButton( false );

	DeleteBookmarkDialog    dlg;
    dlg.DoModal();
    if ( dlg.m_targetBookmark == CUserInfo::BK_UNKNOWN ) {
        EnableButton( true );
        return;
    }

    if ( (dlg.m_deleteAll == false)         && 
         (dlg.m_deleteInteractive == false)    ) {
        EnableButton( true );
        return;
    }

    /* ブックマークの削除 */
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

    m_needToSave = false;
    if ( (dlg.m_targetBookmark == CUserInfo::BK_1470NET) &&
         (pp->m_next1470net.m_username.GetLength() == 0)    )
        m_needToSave = true;

    pp->DeleteBookmarks( dlg.m_targetBookmark,
                         dlg.m_deleteAll, dlg.m_deleteInteractive );
    if ( m_needToSave ) {
        if ( (dlg.m_targetBookmark == CUserInfo::BK_1470NET) &&
             (pp->m_next1470net.m_username.GetLength() == 0)    )
            m_needToSave = false;
    }

    EnableButton( true );
}


/* 「ブックマーク取得」側 */
void CBookeyDlg::OnSelchangeComboBookmark1() 
{
    CString     bookmarkName;
    int         location = m_bookmarkList1.GetCurSel();

	m_bookmarkList1.GetLBText( location, bookmarkName );
    if ( m_bookmark1.Compare( bookmarkName ) != 0 ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username1 = "";
        m_password1 = "";
        m_bookmark1 = bookmarkName;
        pp->m_bookmarkGotten = false;
        pp->m_bookmarkName   = "";

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME1 );
        CEdit   *q = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD1 );
        p->SetWindowText( m_username1 );
        q->SetWindowText( m_password1 );

        if ( m_bookmark1.GetLength() > 0 ) {
            if ( !m_bookmark1.Compare( m_tgt_hatenaBookmark ) )
                pp->SetWindowText( m_bookmark1, m_username1, p, q );
            else if ( !m_bookmark1.Compare( m_tgt_delicious )      ||
                      !m_bookmark1.Compare( m_tgt_blueDot )        ||
                      !m_bookmark1.Compare( m_tgt_mmMemo )         ||
                      !m_bookmark1.Compare( m_tgt_drecomRSS )      ||
                      !m_bookmark1.Compare( m_tgt_flog )           ||
                      !m_bookmark1.Compare( m_tgt_livedoorClip )   ||
                      !m_bookmark1.Compare( m_tgt_ecNaviClip )     ||
                      !m_bookmark1.Compare( m_tgt_niftyClip )      ||
                      !m_bookmark1.Compare( m_tgt_1470net )        ||
                      !m_bookmark1.Compare( m_tgt_pookmark )       ||
                      !m_bookmark1.Compare( m_tgt_joltMark )       ||
                      !m_bookmark1.Compare( m_tgt_blogPet )        ||
                      !m_bookmark1.Compare( m_tgt_fc2bookmark )    ||
                      !m_bookmark1.Compare( m_tgt_yjBookmark )     ||
                      !m_bookmark1.Compare( m_tgt_yahooBookmarks ) ||
                      !m_bookmark1.Compare( m_tgt_diigo )             )
                pp->SetWindowText( m_bookmark1, m_username1, m_password1,
                                   p, q );
            else if (!m_bookmark1.Compare( m_tgt_opml )         ||
                     !m_bookmark1.Compare( m_tgt_netscape1 )    ||
                     !m_bookmark1.Compare( m_tgt_opera6 )       ||
                     !m_bookmark1.Compare( m_tgt_hatenaFeed )   ||
                     !m_bookmark1.Compare( m_tgt_livedoorFeed ) ||
                     !m_bookmark1.Compare( m_tgt_deliciousXML )    ) {
                p->EnableWindow( FALSE );
                q->EnableWindow( FALSE );
            }
        }

        ChangeButtonGet();
        ChangeButtonPut();
    }
}

void CBookeyDlg::OnKillfocusEditUsername1() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME1 );
    p->GetWindowText( m_username1 );

    ChangeButtonGet();
}

void CBookeyDlg::OnKillfocusEditPassword1() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD1 );
    p->GetWindowText( m_password1 );

    ChangeButtonGet();
}

void CBookeyDlg::OnUpdateEditUsername1() 
{
    OnKillfocusEditUsername1();
}

void CBookeyDlg::OnUpdateEditPassword1() 
{
    OnKillfocusEditPassword1();
}


/* 「ブックマーク登録」側 */
void CBookeyDlg::OnSelchangeComboBookmark2() 
{
    CString     bookmarkName;
    int         location = m_bookmarkList2.GetCurSel();

	m_bookmarkList2.GetLBText( location, bookmarkName );

    if ( m_bookmark2.Compare( bookmarkName ) != 0 ) {
        m_username2 = "";
        m_password2 = "";
        m_bookmark2 = bookmarkName;

        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME2 );
        CEdit   *q = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD2 );
        p->SetWindowText( m_username2 );
        q->SetWindowText( m_password2 );

        if ( m_bookmark2.GetLength() > 0 ) {
            CString text;
            CButton *r = (CButton *)GetDlgItem( IDC_BUTTON_PUT );

           if ( !m_bookmark2.Compare( m_tgt_hatenaBookmark ) ||
                !m_bookmark2.Compare( m_tgt_delicious )      ||
                !m_bookmark2.Compare( m_tgt_blueDot )        ||
                !m_bookmark2.Compare( m_tgt_mmMemo )         ||
                !m_bookmark2.Compare( m_tgt_drecomRSS )      ||
                !m_bookmark2.Compare( m_tgt_flog )           ||
                !m_bookmark2.Compare( m_tgt_livedoorClip )   ||
                !m_bookmark2.Compare( m_tgt_ecNaviClip )     ||
                !m_bookmark2.Compare( m_tgt_niftyClip )      ||
                !m_bookmark2.Compare( m_tgt_1470net )        ||
                !m_bookmark2.Compare( m_tgt_pookmark )       ||
                !m_bookmark2.Compare( m_tgt_joltMark )       ||
                !m_bookmark2.Compare( m_tgt_blogPet )        ||
                !m_bookmark2.Compare( m_tgt_fc2bookmark )    ||
                !m_bookmark2.Compare( m_tgt_yjBookmark )     ||
                !m_bookmark2.Compare( m_tgt_yahooBookmarks ) ||
                !m_bookmark2.Compare( m_tgt_diigo )             ) {
                CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
                text.LoadString(IDS_BTN_PUT_BOOKMARKS);
                pp->SetWindowText( m_bookmark2, m_username2, m_password2,
                                   p, q, r,
                                   text );  // ブックマーク登録
            }
            else if ( !m_bookmark2.Compare( m_tgt_opml )         ||
                      !m_bookmark2.Compare( m_tgt_netscape1 )    ||
                      !m_bookmark2.Compare( m_tgt_opera6 )       ||
                      !m_bookmark2.Compare( m_tgt_deliciousXML )    ) {
                p->EnableWindow( FALSE );
                q->EnableWindow( FALSE );
                text.LoadString(IDS_BTN_SAVE_BOOKMARKS);
                r->SetWindowText( text );   // ブックマーク保存
            }
        }

        ChangeButtonPut();
    }
}

void CBookeyDlg::OnKillfocusEditUsername2() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_USERNAME2 );
    p->GetWindowText( m_username2 );
    
    ChangeButtonPut();
}

void CBookeyDlg::OnKillfocusEditPassword2() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PASSWORD2 );
    p->GetWindowText( m_password2 );

    ChangeButtonPut();
}

void CBookeyDlg::OnUpdateEditUsername2() 
{
    OnKillfocusEditUsername2();
}

void CBookeyDlg::OnUpdateEditPassword2() 
{
    OnKillfocusEditPassword2();
}

void CBookeyDlg::OnButtonEditTags() 
{
    EnableButton( false );

	CReplaceTagsDialog  dlg;
    dlg.DoModal();

    EnableButton( true );
}

void CBookeyDlg::OnButtonDeleteTags() 
{
    EnableButton( false );

	CDeleteTagsDialog   dlg;
    dlg.DoModal();

    EnableButton( true );
}

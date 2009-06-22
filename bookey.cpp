/*
 * bookey.cpp : ソーシャルブックマーク管理プログラム
 *      アプリケーション メイン
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookey.cpp $
 * 
 * 3     09/06/22 22:31 tsupo
 * 0.63c版
 * 
 * 85    09/06/22 17:56 Tsujimura543
 * 日本語モード←→英語モード切替関連、修正
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 84    09/05/27 17:08 Tsujimura543
 * setSigInfo() の引数を追加
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 83    09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 82    08/10/21 22:05 Tsujimura543
 * 「ヘルプ」メニューに「サポート」(2件)、「コミュニティ」(2件)を追加
 * 
 * 81    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 80    08/07/25 22:16 Tsujimura543
 * Diigo 対応
 * 
 * 79    07/10/31 17:14 Tsujimura543
 * tumblr に対応
 * 
 * 78    07/10/05 2:42 Tsujimura543
 * BBAuth 対応関連の各種修正を実施
 * 
 * 77    07/09/06 18:01 Tsujimura543
 * CUserInfoクラスのコピーコンストラクタ、代入演算子を使っていた部分を
 * CUserInfoクラス内に移管 (PutBookmarks)
 * 
 * 76    07/09/04 23:31 Tsujimura543
 * m_verboseFp を閉じる場所を CBookeyView のデストラクタに移動
 * 
 * 75    07/09/04 22:43 Tsujimura543
 * m_verboseFp を導入
 * 
 * 74    07/09/04 22:30 Tsujimura543
 * m_verbose を導入
 * 
 * 73    07/07/27 1:14 Tsujimura543
 * 「OFF → 一時的に ON」切り替え機能を実装
 * 
 * 72    07/07/12 11:57 Tsujimura543
 * ResetUserInfo() の digg 関連の処理の引数指定誤りを修正
 * 
 * 71    07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 70    07/05/23 16:11 Tsujimura543
 * Timelog への登録(発言)に対応
 * 
 * 69    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 68    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 67    07/04/16 17:59 Tsujimura543
 * del.icio.us の posts/all 形式の XML ファイルのインポートとエクスポート
 * に対応した
 * 
 * 66    07/04/11 15:02 Tsujimura543
 * コメントとコードの内容が食い違ってしまっていた箇所を修正
 * (コメントを修正)
 * 
 * 65    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 64    07/03/14 17:07 Tsujimura543
 * (1) StdAfx.h をインクルードしなくてもいいようにした
 * (2) proxy関連のもろもろの修正、追加 (BloGolEe の成果を取り込む)
 * 
 * 63    07/02/16 16:35 Tsujimura543
 * コメントを修正
 * 
 * 62    07/01/29 23:59 Tsujimura543
 * UserInfo() を修正
 * 
 * 61    07/01/29 17:51 Tsujimura543
 * タグ一覧の取得、タグの削除、タグの置換の各処理を追加
 * 
 * 60    07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 59    07/01/17 21:44 Tsujimura543
 * コメントを修正
 * 
 * 58    07/01/17 21:43 Tsujimura543
 * 「言語」情報の取得、設定処理を xmlRPC.dll 内に用意したものを使うよう
 * に変更
 * 
 * 57    07/01/13 1:42 Tsujimura543
 * CBookeyApp::CBookeyApp() の中から CString#LoadString() すると
 * assertion failed することが判明。対策を実施 (英語モード対応にあたって
 * 発生した障害)
 * 
 * 56    07/01/12 20:35 Tsujimura543
 * 英語モード対応
 * 
 * 55    07/01/12 13:21 Tsujimura543
 * 英語モード対応準備
 * 
 * 54    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 53    06/12/22 21:41 Tsujimura543
 * 「BlogPet 気になる記事」対応
 * 
 * 52    06/12/21 19:13 Tsujimura543
 * (1) JoltMark に対応
 * (2) FC2BOOKMARK、「BlogPet 気になる記事」対応準備
 * 
 * 51    06/12/06 19:48 Tsujimura543
 * コメントを修正
 * 
 * 50    06/12/06 19:46 Tsujimura543
 * livedoor Clip のエクスポートファイル(RSS 2.0 形式)をインポートする機能
 * を追加した
 * 
 * 49    06/12/06 18:59 Tsujimura543
 * 「公開状態」の設定に対応
 * 
 * 48    06/11/16 16:43 Tsujimura543
 * CUserInfo 導入によるリファクタリング第16段階、終了
 * 
 * 47    06/11/16 14:02 Tsujimura543
 * CUserInfo 導入によるリファクタリング第15段階、終了
 * 
 * 46    06/11/06 16:42 Tsujimura543
 * ResetUserInfo() に暫定的な対処を実施(「ローカルOPML」ファイル名の暫定的
 * な修復処理を追加)
 * 
 * 45    06/10/28 1:37 Tsujimura543
 * CBookeyApp::PutBookmarks() [の2つ目の方] で u を delete し忘れていた
 * 
 * 44    06/10/28 1:14 Tsujimura543
 * 「ローカルOPML」へ登録できないことがある不具合に対処
 * 
 * 43    06/10/26 22:54 Tsujimura543
 * 「ローカルOPML」に対応
 * 
 * 42    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 41    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline に対応
 * 
 * 40    06/09/30 0:25 Tsujimura543
 * newsing に対応
 * 
 * 39    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 38    06/09/05 11:14 Tsujimura543
 * Visual C++ 2005 でビルドする場合に備えて、ResetDayLightSaving()
 * を追加 (現在リリースしている bookey は Visual C++ 6 にてビルドして
 * いる)
 * 
 * 37    06/08/22 17:48 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 36    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 35    06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 34    06/07/31 17:56 Tsujimura543
 * コメントを修正、追加
 * 
 * 33    06/07/31 17:51 Tsujimura543
 * ドラッグアンドドロップによるブックマーク登録時は、1470.net (MM/Memo) の
 * login 処理内のキャッシュを常にクリアするようにした (bookie 以外のアプリ
 * ケーション(例えば、Webブラウザ)によるアクセスにより、キャッシュしている
 * cookie [のうち、TypeKey と紐付けられているもの]が無効になっている可能性
 * があるため、キャッシュをクリアして、その都度 login し直すようにした)
 * -- なお、他のブックマークサービスやOPMLファイルからのインポート時、取得
 * -- 時、同期時は今まで通り、キャッシュを有効なままとしてある
 * 
 * 32    06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 * 
 * 31    06/07/27 20:44 Tsujimura543
 * ECナビ人気ニュース、ニフティクリップ、1470.netリニューアル版に「登録」
 * できないことがある(なぜか試験用の環境では「登録」できていたので気づく
 * のが遅れた)不具合に対処
 * 
 * 30    06/07/19 14:19 Tsujimura543
 * MyClip! 関係の処理を削除 (2006年6月末でサービス終了のため)
 * 
 * 29    06/07/14 20:50 Tsujimura543
 * 1470.netリニューアル版に対応
 * 
 * 28    06/07/05 18:19 Tsujimura543
 * CUserInfo 導入によるリファクタリング第13段階、終了
 * 
 * 27    06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 26    06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 25    06/07/03 15:15 Tsujimura543
 * ProceedingDialog 絡みの改修 (ProceedingDialog の delete時に例外が
 * 発生することがある件の対策実施)
 * 
 * 24    06/06/29 18:46 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 23    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 22    06/06/22 21:21 Tsujimura543
 * inquery → inquiry に修正(綴りミス)
 * 
 * 21    06/06/21 21:14 Tsujimura543
 * CUserInfo 導入によるリファクタリング第11段階、終了
 * 
 * 20    06/06/20 14:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第9段階、終了
 * 
 * 19    06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 18    06/06/14 22:40 Tsujimura543
 * CUserInfo 導入によるリファクタリング第7段階、終了
 * 
 * 17    06/06/14 12:06 Tsujimura543
 * CUserInfo 導入によるリファクタリング第6段階、終了
 * 
 * 16    06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 15    06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 14    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 13    06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 12    06/05/31 16:29 Tsujimura543
 * warning #4100 を disable にする
 * 
 * 11    06/05/08 14:33 Tsujimura543
 * F1キー押下時に「状況依存ヘルプ」を表示しようとするのを抑制するようにし
 * た
 * 
 * 10    05/11/10 21:20 Tsujimura543
 * (1) 進行状況表示ダイアログの準備用に追加した変数、処理を削除
 * (2) 上記に伴い、イベントを「二重起動チェック」用途専用に変更
 * 
 * 9     05/11/10 14:13 Tsujimura543
 * m_proceedTitle を追加
 * 
 * 8     05/11/10 13:58 Tsujimura543
 * 進行状況表示ダイアログ対応準備として、イベントを導入
 * 
 * 7     05/11/10 12:06 Tsujimura543
 * ドキュメントテンプレート関連の処理をコメントアウトした。これでレジスト
 * リを知らない間に書き換えてしまう可能性も排除できたはず。
 * 
 * 6     05/10/14 14:20 Tsujimura543
 * CAboutDlg を別ファイルへ分離、独立させた
 * 
 * 5     05/10/14 13:25 Tsujimura543
 * 別途作成したドラッグ・アンド・ドロップ対応試験プログラムの成果を取り込
 * む
 * 
 * 4     05/10/14 11:07 Tsujimura543
 * 0.02 版 (ドラッグ・アンド・ドロップ未対応版)
 * 
 * 3     05/10/11 17:04 Tsujimura543
 * 初版のタイムスタンプ表記ミスを修正 (コメントのみの修正。動作に影響なし)
 * 
 * 2     05/09/30 23:52 Tsujimura543
 * ブックマークの取得、登録機能の動作確認完了
 */

#include "bookey.h"

#include "MainFrm.h"
#include "bookeyDoc.h"
#include "bookeyView.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookey.cpp 3     09/06/22 22:31 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp

BEGIN_MESSAGE_MAP(CBookeyApp, CWinApp)
	//{{AFX_MSG_MAP(CBookeyApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(IDS_ABOUT_SUPPORT, OnAppSupport)
    ON_COMMAND(IDS_ABOUT_SUPPORT2, OnAppSupport2)
    ON_COMMAND(IDS_ABOUT_COMMUNITY, OnAppCommunity)
    ON_COMMAND(IDS_ABOUT_COMMUNITY2, OnAppCommunity2)
	//}}AFX_MSG
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp クラスの構築

CBookeyApp::CBookeyApp()
{
    m_proceed   = NULL;
    m_verbose   = false;
    m_verboseFp = NULL;

    LCID    langCode;
    m_langCode = langCode = getLanguageCode();
    if ( m_langCode != 0x0411 ) {
        m_langCode = 0x0409;  // 「日本語」以外の場合は強制的に「英語」にする
        if ( langCode != m_langCode )
            setLanguageCode( m_langCode );
    }

    int i = 0;
    m_userInfoList[i++] = &m_hatena;        // [0]  はてなブックマーク
    m_userInfoList[i++] = &m_delicious;     // [1]  del.icio.us
    m_userInfoList[i++] = &m_mmMemo;        // [2]  MM/memo
    m_userInfoList[i++] = &m_drecomRss;     // [3]  ドリコムRSS
    m_userInfoList[i++] = &m_flog;          // [4]  Flog
    m_userInfoList[i++] = &m_livedoorClip;  // [5]  livedoor クリップ
    m_userInfoList[i++] = &m_ecNaviClip;    // [6]  Buzzurl
    m_userInfoList[i++] = &m_niftyClip;     // [7]  ニフティクリップ
    m_userInfoList[i++] = &m_next1470net;   // [8]  1470.netリニューアル版
    m_userInfoList[i++] = &m_newsing;       // [9 ] newsing
    m_userInfoList[i++] = &m_pookmark;      // [10] POOKMARK Airlines
    m_userInfoList[i++] = &m_blueDot;       // [11] Blue Dot
    m_userInfoList[i++] = &m_joltMark;      // [12] JoltMark
    m_userInfoList[i++] = &m_fc2bookmark;   // [13] FC2BOOKMARK
    m_userInfoList[i++] = &m_blogPet;       // [14] BlogPet 気になる記事
    m_userInfoList[i++] = &m_twitter;       // [15] Twitter
    m_userInfoList[i++] = &m_yjBookmark;    // [16] Yahoo! Japan ブックマーク
    m_userInfoList[i++] = &m_yahooBookmarks;// [17] Yahoo! Bookmarks
    m_userInfoList[i++] = &m_timelog;       // [18] Timelog
    m_userInfoList[i++] = &m_digg;          // [19] digg
    m_userInfoList[i++] = &m_tumblr;        // [20] tumblr
    m_userInfoList[i++] = &m_diigo;         // [21] Diigo
    m_userInfoList[i++] = &m_localOpml;     // [22] ローカルOPML

    m_bookmarkGotten = false;

    m_proxyType      = autoDetect;  // ここではとりあえず、暫定的な初期化をし
    m_useProxy       = false;       // ておき、CBookeyView::OnInitialUpdate()
    m_proxyServer    = "";          // にて実際の値を設定する
    m_proxyPort      = 0;
    m_proxyUsername  = "";
    m_proxyPassword  = "";

    m_myClip         = NULL;
    m_numOfClips     = 0;
    m_bookmarkName   = "";

    m_tcKey          = _T("");
    m_tcSecret       = _T("");
}

void CBookeyApp::Initialize()
{
    /*
     * 以下の処理は InitInstance() では呼び出せないため、代わりに本メソッド
     * にて呼び出す
     */
    m_hatena.Init( CUserInfo::BK_HATENA );
    m_delicious.Init( CUserInfo::BK_DELICIOUS );
    m_mmMemo.Init( CUserInfo::BK_MM_MEMO );
    m_drecomRss.Init( CUserInfo::BK_DRECOM_RSS );
    m_flog.Init( CUserInfo::BK_FLOG );
    m_livedoorClip.Init( CUserInfo::BK_LIVEDOOR_CLIP );
    m_ecNaviClip.Init( CUserInfo::BK_ECNAVI_CLIP );
    m_niftyClip.Init( CUserInfo::BK_NIFTY_CLIP );
    m_next1470net.Init( CUserInfo::BK_1470NET );
    m_newsing.Init( CUserInfo::BK_NEWSING );
    m_pookmark.Init( CUserInfo::BK_POOKMARK );
    m_blueDot.Init( CUserInfo::BK_BLUEDOT );
    m_joltMark.Init( CUserInfo::BK_JOLTMARK );
    m_fc2bookmark.Init( CUserInfo::BK_FC2BOOKMARK );
    m_blogPet.Init( CUserInfo::BK_BLOGPET );
    m_twitter.Init( CUserInfo::BK_TWITTER );
    m_yjBookmark.Init( CUserInfo::BK_YJ_BOOKMARK );
    m_yahooBookmarks.Init( CUserInfo::BK_YAHOO_BOOKMARKS );
    m_timelog.Init( CUserInfo::BK_TIMELOG );
    m_digg.Init( CUserInfo::BK_DIGG );
    m_tumblr.Init( CUserInfo::BK_TUMBLR );
    m_diigo.Init( CUserInfo::BK_DIIGO );
    m_localOpml.Init( CUserInfo::BK_LOCAL_OPML );

    CString sigHead = _T("");
    CString sigTail = _T("");
    sigHead.LoadString( IDS_TWITTER_OA001 );
    sigTail.LoadString( IDS_TWITTER_OA002 );
    SetSigInfo( m_tcKey, m_tcSecret, sigHead, sigTail );
}

void    CBookeyApp::ReInitialize()
{
    m_hatena.ReInit();
    m_delicious.ReInit();
    m_mmMemo.ReInit();
    m_drecomRss.ReInit();
    m_flog.ReInit();
    m_livedoorClip.ReInit();
    m_ecNaviClip.ReInit();
    m_niftyClip.ReInit();
    m_next1470net.ReInit();
    m_newsing.ReInit();
    m_pookmark.ReInit();
    m_blueDot.ReInit();
    m_joltMark.ReInit();
    m_fc2bookmark.ReInit();
    m_blogPet.ReInit();
    m_twitter.ReInit();
    m_yjBookmark.ReInit();
    m_yahooBookmarks.ReInit();
    m_timelog.ReInit();
    m_digg.ReInit();
    m_tumblr.ReInit();
    m_diigo.ReInit();
    m_localOpml.ReInit();
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CBookeyApp オブジェクト

CBookeyApp theApp;

// この ID はこのアプリケーションが統計的にユニークになるように生成されました。
// もし、特別な ID を指定したいならば、変更してもかまいません。

// {2DDC3A1A-72B9-47A1-88F6-D2CF12788473}
static const CLSID clsid =
{ 0x2ddc3a1a, 0x72b9, 0x47a1, { 0x88, 0xf6, 0xd2, 0xcf, 0x12, 0x78, 0x84, 0x73 } };

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp クラスの初期化

BOOL CBookeyApp::InitInstance()
{
	// OLE ライブラリの初期化
	if (!AfxOleInit()) {
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

    m_proceed = new CEvent( FALSE, TRUE, BOOKEY_EVENT_PROCEED, NULL );
    if ( !m_proceed || (GetLastError() == ERROR_ALREADY_EXISTS) )
        return FALSE;

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
                IDR_MAINFRAME,
                RUNTIME_CLASS(CBookeyDoc),
                RUNTIME_CLASS(CMainFrame),  // メイン SDI フレーム ウィンドウ
                RUNTIME_CLASS(CBookeyView));
	AddDocTemplate(pDocTemplate);

    ResetDayLightSaving();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated) {
		COleTemplateServer::RegisterAll();
		return TRUE;
	}

    Initialize();

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/*
 *  再設定
 */
void    CBookeyApp::ResetUserInfo( bool &needToSave )
{
    int i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ )
        m_userInfoList[i]->ResetUserInfo( needToSave );
}

void    CBookeyApp::ResetUserInfo( bool      &needToSave,
                                   RBparam_t &param )
{
    m_hatena.ResetUserInfo( needToSave,
                            param.hatena.isTarget,
                            param.hatena.username,
                            param.hatena.password );
    m_delicious.ResetUserInfo( needToSave,
                               param.delicious.isTarget,
                               param.delicious.username,
                               param.delicious.password );
    m_mmMemo.ResetUserInfo( needToSave,
                            param.mmMemo.isTarget,
                            param.mmMemo.username,
                            param.mmMemo.password );
    m_drecomRss.ResetUserInfo( needToSave,
                               param.drecomRss.isTarget,
                               param.drecomRss.username,
                               param.drecomRss.password );
    m_flog.ResetUserInfo( needToSave,
                          param.flog.isTarget,
                          param.flog.username,
                          param.flog.password );
    m_livedoorClip.ResetUserInfo( needToSave,
                                  param.livedoorClip.isTarget,
                                  param.livedoorClip.username,
                                  param.livedoorClip.password );
    m_ecNaviClip.ResetUserInfo( needToSave,
                                param.ecNaviClip.isTarget,
                                param.ecNaviClip.username,
                                param.ecNaviClip.password );
    m_niftyClip.ResetUserInfo( needToSave,
                               param.niftyClip.isTarget,
                               param.niftyClip.username,
                               param.niftyClip.password );
    m_next1470net.ResetUserInfo( needToSave,
                                 param.next1470net.isTarget,
                                 param.next1470net.username,
                                 param.next1470net.password );
    m_newsing.ResetUserInfo( needToSave,
                             param.newsing.isTarget,
                             param.newsing.username,
                             param.newsing.password );
    m_pookmark.ResetUserInfo( needToSave,
                              param.pookmark.isTarget,
                              param.pookmark.username,
                              param.pookmark.password );
    m_blueDot.ResetUserInfo( needToSave,
                             param.blueDot.isTarget,
                             param.blueDot.username,
                             param.blueDot.password );
    m_joltMark.ResetUserInfo( needToSave,
                              param.joltMark.isTarget,
                              param.joltMark.username,
                              param.joltMark.password );
    m_fc2bookmark.ResetUserInfo( needToSave,
                                 param.fc2bookmark.isTarget,
                                 param.fc2bookmark.username,
                                 param.fc2bookmark.password );
    m_blogPet.ResetUserInfo( needToSave,
                             param.blogPet.isTarget,
                             param.blogPet.username,
                             param.blogPet.password );
    m_twitter.ResetUserInfo( needToSave,
                             param.twitter.isTarget,
                             param.twitter.username,
                             param.twitter.password );
    m_yjBookmark.ResetUserInfo( needToSave,
                                param.yjBookmark.isTarget,
                                param.yjBookmark.username,
                                param.yjBookmark.password );
    m_yahooBookmarks.ResetUserInfo( needToSave,
                                    param.yahooBookmarks.isTarget,
                                    param.yahooBookmarks.username,
                                    param.yahooBookmarks.password );
    m_timelog.ResetUserInfo( needToSave,
                             param.timelog.isTarget,
                             param.timelog.username,
                             param.timelog.password );
    m_digg.ResetUserInfo( needToSave,
                          param.digg.isTarget,
                          param.digg.username,
                          param.digg.password );
    m_tumblr.ResetUserInfo( needToSave,
                            param.tumblr.isTarget,
                            param.tumblr.username,
                            param.tumblr.password );
    m_diigo.ResetUserInfo( needToSave,
                           param.diigo.isTarget,
                           param.diigo.username,
                           param.diigo.password );
    m_localOpml.ResetUserInfo( needToSave,
                               param.localOpml.isTarget,
                               param.localOpml.filename );
}

/*
 *  ユーザ情報表示
 */

void    CBookeyApp::SetWindowText( CString bookmarkName,
                                   CString &username,
                                   CString &password,
                                   CEdit   *editUsername,
                                   CEdit   *editPassword,
                                   CButton *executeButton,
                                   CString txt )
{
    SetWindowText( bookmarkName, username, password,
                   editUsername, editPassword );
    executeButton->SetWindowText( txt );
}

void    CBookeyApp::SetWindowText( CString bookmarkName,
                                   CString &username,
                                   CString &password,
                                   CEdit   *editUsername,
                                   CEdit   *editPassword )
{
    if ( bookmarkName.Compare( m_localOpml ) != 0 ) {
        CUserInfo   *u = UserInfoEx( bookmarkName );

        if ( u )
            u->SetWindowText( username, password,
                              editUsername, editPassword );
    }

    editUsername->EnableWindow( TRUE );
    editPassword->EnableWindow( TRUE );
}

void    CBookeyApp::SetWindowText( CString bookmarkName,
                                   CString &username,
                                   CEdit   *editUsername,
                                   CEdit   *editPassword )
{
    if ( bookmarkName.Compare( m_localOpml ) != 0 ) {
        CUserInfo   *u = UserInfoEx( bookmarkName );

        if ( u )
            u->SetWindowText( username, editUsername );
    }

    editUsername->EnableWindow( TRUE );
    editPassword->EnableWindow( FALSE );
}

/*
 *  各種問い合わせ
 */

bool    CBookeyApp::InquiryUserInfo( CString bookmark1, CString bookmark2,
                                     CString txt )
{
    int     i;
    bool    cont = false;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        cont = m_userInfoList[i]->InquiryUserInfo(bookmark1, bookmark2, txt);
        if ( cont == false )
            break;
    }

    return ( cont );
}

/*
 *  ブックマークのインポート(登録)
 */

void    CBookeyApp::ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction )
{
    int     i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        m_userInfoList[i]->ImportFromAnotherToOne(
                                bookmark1,      bookmark2,
                                myBookmark1,    myBookmark2,
                                numOfBookmark1, numOfBookmark2,
                                direction );
    }

    if ( myBookmark1 ) {
        free( myBookmark1 );
        myBookmark1 = NULL;
    }
    if ( myBookmark2 ) {
        free( myBookmark2 );
        myBookmark2 = NULL;
    }
}

/*
 *  ブックマークのエクスポート(取得)
 */

bool    CBookeyApp::ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2 )
{
    int     i;
    bool    cont = false;
    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        cont = m_userInfoList[i]->ExportFromAnother(
                                    bookmark1,      bookmark2,
                                    myBookmark1,    myBookmark2,
                                    numOfBookmark1, numOfBookmark2 );
        if ( cont == false )
            break;
    }

    if ( cont == false ) {
        if ( myBookmark1 && *myBookmark1 ) {
            free( *myBookmark1 );
            *myBookmark1 = NULL;
        }
        if ( myBookmark2 && *myBookmark2 ) {
            free( *myBookmark2 );
            *myBookmark2 = NULL;
        }
    }

    return ( cont );
}


/*
 *  ブックマークの削除
 */

void    CBookeyApp::DeleteBookmarks(
            enum CUserInfo::bookmarkType bmType,
            bool                         deleteAll,
            bool                         deleteInteractive )
{
    CUserInfo   *u = UserInfo( bmType );

    if ( u )
        u->DeleteBookmarks( deleteAll, deleteInteractive );
}


/*
 *  ブックマークの登録
 */

void    CBookeyApp::PutBookmarks( const RBparam_t    *p,
                                  const char         *accountName,
                                  EditBookmarkDialog *editDlg,
                                  ProceedingDialog   *procDlg )
{
    MyClip  myBookmark;

    strcpy( myBookmark.url, (const char *)editDlg->m_url );
    if ( editDlg->m_title.GetLength() > 0 )
        strcpy( myBookmark.title, (const char *)(editDlg->m_title) );
    else
        strcpy( myBookmark.title, editDlg->m_url );
    if ( editDlg->m_comment.GetLength() > 0 )
        strcpy( myBookmark.comment, (const char *)(editDlg->m_comment) );
    else
        myBookmark.comment[0] = NUL;
    if ( editDlg->m_tags.GetLength() > 0 )
        strcpy( myBookmark.tags, (const char *)(editDlg->m_tags) );
    else
        myBookmark.tags[0] = NUL;

    time_t      t   = time( NULL );
    struct tm   *tm = gmtime( &t ); /* GMT */
    myBookmark.yyyy = tm->tm_year + 1900;
    myBookmark.mm   = tm->tm_mon  + 1;
    myBookmark.dd   = tm->tm_mday;
    myBookmark.HH   = tm->tm_hour;
    myBookmark.MM   = tm->tm_min;
    myBookmark.SS   = tm->tm_sec;

    myBookmark.evaluation  = editDlg->m_evaluation;
    myBookmark.rating      = editDlg->m_rating;
    myBookmark.affirmation = editDlg->m_affirmation;
    myBookmark.publication = editDlg->m_public;

    // はてな投げ銭送信
    if ( editDlg->m_sendTipJar ) {
        char    cmd[BUFSIZ];
        sprintf( cmd, "https://www.hatena.ne.jp/sendpoint?name=%s",
                 accountName );
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }

    procDlg->ResetDialogText();
    procDlg->ShowWindow( SW_SHOWNORMAL );

    // ローカルOPMLファイルに登録
    if ( p->localOpml.isTarget && m_localOpml.m_opmlFilename[0] )
        m_localOpml.PutBookmarks( &myBookmark, procDlg );

    // はてなブックマークに登録
    if ( editDlg->m_param.hatena.isTarget && m_hatena.m_username[0] ) {
        myBookmark.asin = editDlg->m_registerCollection ? TRUE : FALSE;
        m_hatena.PutBookmarks( &myBookmark, procDlg );
    }

    // del.icio.us に登録
    if ( editDlg->m_param.delicious.isTarget && m_delicious.m_username[0] )
        m_delicious.PutBookmarks( &myBookmark, procDlg );

    // MM/Memo に登録
    if ( editDlg->m_param.mmMemo.isTarget && m_mmMemo.m_username[0] ) {
        loginMMmemo( NULL, NULL, NULL, NULL );  // キャッシュをクリア
        m_mmMemo.PutBookmarks( &myBookmark, procDlg );
    }

    // ドリコムRSS に登録
    if ( editDlg->m_param.drecomRss.isTarget && m_drecomRss.m_username[0] )
        m_drecomRss.PutBookmarks( &myBookmark, procDlg );

    // Flog に登録
    if ( editDlg->m_param.flog.isTarget && m_flog.m_username[0] )
        m_flog.PutBookmarks( &myBookmark, procDlg );

    // livedoor クリップ に登録
    if ( editDlg->m_param.livedoorClip.isTarget &&
         m_livedoorClip.m_username[0]              )
        m_livedoorClip.PutBookmarks( &myBookmark, procDlg );

    // Buzzurl に登録
    if ( editDlg->m_param.ecNaviClip.isTarget && m_ecNaviClip.m_username[0] )
        m_ecNaviClip.PutBookmarks( &myBookmark, procDlg );

    // ニフティクリップ に登録
    if ( editDlg->m_param.niftyClip.isTarget && m_niftyClip.m_username[0] )
        m_niftyClip.PutBookmarks( &myBookmark, procDlg );

    // 1470.netリニューアル版 に登録
    if (editDlg->m_param.next1470net.isTarget && m_next1470net.m_username[0]) {
        login1470net( NULL, NULL, NULL, NULL, AK_ORIGINAL, NULL, NULL );
                                                        // キャッシュをクリア
        m_next1470net.PutBookmarks( &myBookmark, procDlg );
    }

    // newsing に登録
    if ( editDlg->m_param.newsing.isTarget          &&
         m_newsing.m_username[0]                    &&
         ((myBookmark.affirmation == AFF_GOOD) ||
          (myBookmark.affirmation == AFF_BAD)     )    )
        m_newsing.PutBookmarks( &myBookmark, procDlg );

    // pookmark に登録
    if ( editDlg->m_param.pookmark.isTarget && m_pookmark.m_username[0] )
        m_pookmark.PutBookmarks( &myBookmark, procDlg );

    // Blue Dot に登録
    if ( editDlg->m_param.blueDot.isTarget && m_blueDot.m_username[0] )
        m_blueDot.PutBookmarks( &myBookmark, procDlg );

    // JoltMark に登録
    if ( editDlg->m_param.joltMark.isTarget && m_joltMark.m_username[0] )
        m_joltMark.PutBookmarks( &myBookmark, procDlg );

    // FC2BOOKMARK に登録
    if (editDlg->m_param.fc2bookmark.isTarget && m_fc2bookmark.m_username[0])
        m_fc2bookmark.PutBookmarks( &myBookmark, procDlg );

    // BlogPet 気になる記事 に登録
    if ( editDlg->m_param.blogPet.isTarget && m_blogPet.m_username[0] )
        m_blogPet.PutBookmarks( &myBookmark, procDlg );

    // Yahoo! ブックマーク に登録
    if ( editDlg->m_param.yjBookmark.isTarget && m_yjBookmark.m_username[0] )
        m_yjBookmark.PutBookmarks( &myBookmark, procDlg );

    // Yahoo! Bookmarks に登録
    if ( editDlg->m_param.yahooBookmarks.isTarget &&
         m_yahooBookmarks.m_username[0]              )
        m_yahooBookmarks.PutBookmarks( &myBookmark, procDlg );

    // Twitter で発言
    if ( editDlg->m_param.twitter.isTarget && m_twitter.m_username[0] )
        m_twitter.PutBookmarks( &myBookmark, procDlg );

    // Timelog で発言
    if ( editDlg->m_param.timelog.isTarget && m_timelog.m_username[0] )
        m_timelog.PutBookmarks( &myBookmark, procDlg );

    // digg に登録
    if ( editDlg->m_param.digg.isTarget && m_digg.m_username[0] )
        m_digg.PutBookmarks( &myBookmark, procDlg );

    // tumblr に登録
    if ( editDlg->m_param.tumblr.isTarget && m_tumblr.m_username[0] )
        m_tumblr.PutBookmarks( &myBookmark, procDlg );

    // Diigo に登録
    if ( editDlg->m_param.diigo.isTarget && m_diigo.m_username[0] )
        m_diigo.PutBookmarks( &myBookmark, procDlg );
}

void    CBookeyApp::PutBookmarks(
            CString bookmarkName,
            CString username,
            CString password )
{
    CUserInfo   *orig = UserInfo( bookmarkName );
    if ( orig ) {
        orig->PutBookmarks( true,
                            m_myClip, m_numOfClips,
                            (const char *)username,
                            (const char *)password );
    }
}

bool    CBookeyApp::PutBookmarks(
            CString bookmarkNameAsExport,
            CString bookmarkNameAsImport )
{
    CUserInfo   uInfo;
    bool        result = false;
    CString     bookmarkName001;
    CString     bookmarkName002;
    CString     bookmarkName003;
    CString     bookmarkName004;
    CString     bookmarkName005;
    CString     bookmarkName006;

    bookmarkName001.LoadString( IDS_TGT_OPML );
	bookmarkName002.LoadString( IDS_TGT_NETSCAPE_1 );
	bookmarkName003.LoadString( IDS_TGT_OPERA_6 );
	bookmarkName004.LoadString( IDS_TGT_HATENA_FEED );
	bookmarkName005.LoadString( IDS_TGT_LIVEDOOR_FEED );
	bookmarkName006.LoadString( IDS_TGT_DELICIOUS_XML );

    if ( !bookmarkNameAsExport.Compare( bookmarkName001 ) )
        uInfo.Init( CUserInfo::BK_LOCAL_OPML );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName002 ) )
        uInfo.Init( CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1 );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName003 ) )
        uInfo.Init( CUserInfo::BK_OPERA6_ADR );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName004 ) )
        uInfo.Init( CUserInfo::BK_HATENA_BOOKMARK_ATOM );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName005 ) )
        uInfo.Init( CUserInfo::BK_LIVEDOOR_CLIP_RSS );
    else if ( !bookmarkNameAsExport.Compare( bookmarkName006 ) )
        uInfo.Init( CUserInfo::BK_DELICIOUS_XML );
    else
        return ( result );

    uInfo.PutBookmarks(m_myClip, m_numOfClips, bookmarkNameAsImport, result);

    return ( result );
}


/*
 *  ブックマークの取得
 */

void    CBookeyApp::GetBookmarks(
            CString bookmarkName,
            CString username,
            CString password )
{
    if ( m_myClip ) {
        free( m_myClip );
        m_myClip = NULL;
        m_bookmarkGotten = false;
        m_bookmarkName   = "";
    }

    CUserInfo   *u = UserInfo( bookmarkName );
    if ( u )
        m_myClip = u->GetBookmarks( m_numOfClips,
                                    (const char *)username,
                                    (const char *)password );

    if ( m_myClip ) {
        m_bookmarkGotten = true;
        m_bookmarkName   = bookmarkName;
    }
}

bool    CBookeyApp::GetBookmarks( CString bookmarkName )
{
    bool        ret = false;
    CUserInfo   uInfo;

    if ( m_myClip ) {
        free( m_myClip );
        m_myClip = NULL;
        m_bookmarkGotten = false;
        m_bookmarkName   = "";
    }

    CString bookmarkName001;
    CString bookmarkName002;
    CString bookmarkName003;
    CString bookmarkName004;
    CString bookmarkName005;
    CString bookmarkName006;

	bookmarkName001.LoadString( IDS_TGT_OPML );
	bookmarkName002.LoadString( IDS_TGT_NETSCAPE_1 );
	bookmarkName003.LoadString( IDS_TGT_OPERA_6 );
	bookmarkName004.LoadString( IDS_TGT_HATENA_FEED );
	bookmarkName005.LoadString( IDS_TGT_LIVEDOOR_FEED );
	bookmarkName006.LoadString( IDS_TGT_DELICIOUS_XML );

    if ( !bookmarkName.Compare( bookmarkName001 ) ) {
        uInfo.Init( CUserInfo::BK_LOCAL_OPML );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName002 ) ) {
        uInfo.Init( CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1 );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName003 ) ) {
        uInfo.Init( CUserInfo::BK_OPERA6_ADR );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName004 ) ) {
        uInfo.Init( CUserInfo::BK_HATENA_BOOKMARK_ATOM );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName005 ) ) {
        uInfo.Init( CUserInfo::BK_LIVEDOOR_CLIP_RSS );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }
    else if ( !bookmarkName.Compare( bookmarkName006 ) ) {
        uInfo.Init( CUserInfo::BK_DELICIOUS_XML );
        m_myClip = uInfo.GetBookmarks( m_numOfClips, ret );
    }

    if ( m_myClip ) {
        m_bookmarkGotten = true;
        m_bookmarkName   = bookmarkName;
    }

    return ( ret );
}


/* タグ一覧の取得 */
TagList *CBookeyApp::GetTagList(
            enum CUserInfo::bookmarkType bmType,
            int                          &numOfTags )
{
    TagList     *p = NULL;
    CUserInfo   *u = UserInfo( bmType );

    numOfTags = 0;
    if ( u )
        p = u->GetTagList( numOfTags );

    return ( p );
}

/* タグの削除 */
void    CBookeyApp::DeleteTag(
            enum CUserInfo::bookmarkType bmType,
            const char                   *tag )
{
    CUserInfo   *u = UserInfo( bmType );

    if ( u )
        u->DeleteTag( tag );
}

/* タグの置換 */
void    CBookeyApp::ReplaceTag(
            enum CUserInfo::bookmarkType bmType,
            const char                   *oldTag,
            const char                   *newTag )
{
    CUserInfo   *u = UserInfo( bmType );

    if ( u )
        u->ReplaceTag( oldTag, newTag );
}


/* bookmarkName に対応する CUserInfo の取得 */
CUserInfo   *CBookeyApp::UserInfo( CString bookmarkName, CUserInfo *userInfo )
{
    CUserInfo   *p = NULL;

    if ( !bookmarkName.Compare( *userInfo ) )
        p = userInfo;

    return ( p );
}

CUserInfo   *CBookeyApp::UserInfo( CString bookmarkName )
{
    CUserInfo   *p = NULL;
    int         i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        p = UserInfo( bookmarkName, m_userInfoList[i] );
        if ( p )
            break;
    }

    return ( p );
}

CUserInfo   *CBookeyApp::UserInfoEx( CString bookmarkName )
{
    CUserInfo   *p = UserInfo( bookmarkName );
    return ( p );
}

CUserInfo   *CBookeyApp::UserInfo( enum CUserInfo::bookmarkType bmType )
{
    CUserInfo   *p = NULL;

    switch ( bmType ) {
    case CUserInfo::BK_HATENA:
        p = &m_hatena;
        break;
    case CUserInfo::BK_DELICIOUS:
        p = &m_delicious;
        break;
    case CUserInfo::BK_MM_MEMO:
        p = &m_mmMemo;
        break;
    case CUserInfo::BK_DRECOM_RSS:
        p = &m_drecomRss;
        break;
    case CUserInfo::BK_FLOG:
        p = &m_flog;
        break;
    case CUserInfo::BK_LIVEDOOR_CLIP:
        p = &m_livedoorClip;
        break;
    case CUserInfo::BK_ECNAVI_CLIP:
        p = &m_ecNaviClip;
        break;
    case CUserInfo::BK_NIFTY_CLIP:
        p = &m_niftyClip;
        break;
    case CUserInfo::BK_1470NET:
        p = &m_next1470net;
        break;
    case CUserInfo::BK_NEWSING:
        p = &m_newsing;
        break;
    case CUserInfo::BK_POOKMARK:
        p = &m_pookmark;
        break;
    case CUserInfo::BK_BLUEDOT:
        p = &m_blueDot;
        break;
    case CUserInfo::BK_JOLTMARK:
        p = &m_joltMark;
        break;
    case CUserInfo::BK_FC2BOOKMARK:
        p = &m_fc2bookmark;
        break;
    case CUserInfo::BK_BLOGPET:
        p = &m_blogPet;
        break;
    case CUserInfo::BK_TWITTER:
        p = &m_twitter;
        break;
    case CUserInfo::BK_YJ_BOOKMARK:
        p = &m_yjBookmark;
        break;
    case CUserInfo::BK_YAHOO_BOOKMARKS:
        p = &m_yahooBookmarks;
        break;
    case CUserInfo::BK_TIMELOG:
        p = &m_timelog;
        break;
    case CUserInfo::BK_DIGG:
        p = &m_digg;
        break;
    case CUserInfo::BK_TUMBLR:
        p = &m_tumblr;
        break;
    case CUserInfo::BK_DIIGO:
        p = &m_diigo;
        break;
    case CUserInfo::BK_LOCAL_OPML:
        p = &m_localOpml;
        break;
    }

    return ( p );
}

/* proxy情報ファイルの生成 (for BBAuth) */
#define FILE_CONFIG_PROXY   "proxy.txt" // proxyサーバ情報設定ファイル

void
CBookeyApp::MakeProxyText()
{
    if ( m_useProxy ) {
        char    filename[MAX_PATH];

        if ( __argv && __argv[0] && __argv[0][0] ) {
            char    *p;

            strcpy( filename, __argv[0] );
            p = strrchr( filename, '\\' );
            if ( p )
                *p = NUL;
            else {
                p = strrchr( filename, '/' );
                if ( p )
                    *p = NUL;
            }
            strcat( filename, "/" );
        }
        else
            strcpy( filename, "./" );
        strcat( filename, FILE_CONFIG_PROXY );

        FILE    *fp = fopen( filename, "w" );
        if ( fp ) {
            fprintf( fp, "%s\n", m_proxyServer );
            fprintf( fp, "%d\n", m_proxyPort );

            if ( m_proxyUsername.GetLength() > 0 ) {
                fprintf( fp, "%s\n", (const char *)m_proxyUsername );

                if ( m_proxyPassword.GetLength() > 0 )
                    fprintf( fp, "%s\n", (const char *)m_proxyPassword );
            }

            fclose( fp );
        }
    }
}

/*
 *  初期設定ファイル関連
 */

bool    CBookeyApp::EvalKeys(
            const char          *p,
            const unsigned char *rsaString )
{
    int     i;
    bool    cont = false;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        if ( m_userInfoList[i]->EvalKeys( p, rsaString ) ) {
            cont = true;
            break;
        }
    }

    return ( cont );
}

bool    CBookeyApp::CheckKeys(
            const char          *p,
            const unsigned char *rsaString,
            bool                &ret )
{
    int     i;
    bool    cont = false;
    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ ) {
        if ( m_userInfoList[i]->CheckKeys( p, rsaString, ret ) ) {
            cont = true;
            break;
        }
    }

    return ( cont );
}

void    CBookeyApp::WriteKeys(
            FILE          *fp,      // (I/O) 書き出し先
            char          *key,     // (I)   公開鍵
            unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
            bool          &done )   // (O)   暗号化処理実行済みか否か
{
    int i;

    for ( i = 0; i < MAX_NUM_OF_USERINFO; i++ )
        m_userInfoList[i]->WriteKeys( fp, key, secret, done );
}

/* for Visual C++ 2005 runtime */
bool    CBookeyApp::ResetDayLightSaving()
{
    time_t      t   = time( NULL );
    struct tm   *tm = localtime( &t );
    bool        ret = false;

    if ( tm->tm_isdst == 1 ) {
        char    *p = _tzname[0];
        if ( !strcmp( p, "JST" ) ) {
            /* なぜか日本時間であるにも関わらず、夏時間になっている場合 */
            long l = _daylight;

            if ( l == 1 ) {
                // 環境変数 TZ を設定している場合は、(Visual Studio 2005 の)
                // 「C ランタイム ライブラリは、夏時間 (DST: Daylight Saving
                // Time) 計算の実装については米国の規則を前提としています」と
                // いうことで、勝手に夏時間にされてしまうらしい
                // 日本時間には(少なくとも現時点では)夏時間はないのに……
                _daylight = 0;
                tm = localtime( &t );
            }
            else {
                tm->tm_isdst = 0;
                tm->tm_hour--;
                        // tm_hour が負の値になった場合は、自動的に前日になる
            }

            ret = true;
        }
        // とりあえず、日本時間のみ考慮したが、本当は、他の夏時間未導入国・
        // 地域やアメリカと夏時間の開始・終了時期が異なる国・地域に対する配
        // 慮も必要
        // なお、Visual C++ 6 のランタイムでは、TZ=JST-9 と設定している場合
        // でも、日本時間が夏時間ありと判定されてしまうようなことはない。あ
        // くまでも Visual C++ 2005 のランタイムの問題である(Visual C++.NET
        // 2002/2003 に関しては未確認)
    }

    return ( ret );
}

/* その他 */
bool
CBookeyApp::SetSigInfo( CString &sKey,    CString &sSecret,
                        const char *sig1, const char *sig2 )
{
    char    key[BUFSIZ];
    char    secret[BUFSIZ];
    BOOL    ret;

    ret = setSigInfo( key, secret, sig1, sig2, "-ts", "ey-" );
    if ( ret ) {
        sKey    = key;
        sSecret = secret;
    }

    return ( ret ? true : false );
}

#ifdef __cplusplus
extern "C" {
#endif
char    *
TwitterOAuthConsumerKey()
{
    static char tcKey[MAX_KEYLENGTH + 1];

    if ( tcKey[0] == NUL ) {
        CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
        strcpy( tcKey, bp->m_tcKey );
    }

    return ( tcKey );
}

char    *
TwitterOAuthConsumerSecret()
{
    static char tcSecret[MAX_KEYLENGTH + 1];

    if ( tcSecret[0] == NUL ) {
        CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
        strcpy( tcSecret, bp->m_tcSecret );
    }

    return ( tcSecret );
}
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp メッセージ ハンドラ

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBookeyApp::WinHelp(DWORD dwData, UINT nCmd) 
{
 // CWinApp::WinHelp(dwData, nCmd);
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

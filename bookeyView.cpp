/*
 * bookeyView.cpp : ソーシャルブックマーク管理プログラム
 *      CBookeyView クラスの動作の定義
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyView.cpp $
 * 
 * 3     09/06/22 22:31 tsupo
 * 0.63c版
 * 
 * 123   09/06/22 17:56 Tsujimura543
 * 日本語モード←→英語モード切替関連、修正
 * 
 * 2     09/06/18 0:53 tsupo
 * 0.63b版
 * 
 * 122   09/06/16 22:02 Tsujimura543
 * 登録しようとしている URL の長さが MAX_URLLENGTH 以上のとき
 * にバッファオーバーランが起きる不具合を修正
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 121   09/01/19 23:55 Tsujimura543
 * ツールバーの右クリックメニューに「ブックマーク管理ツール起動」と
 * 「設定」を追加 (最小化状態からも起動できるようにした)
 * 
 * 120   08/12/05 18:19 Tsujimura543
 * ログファイルが 2GBより大きいときにも、期待通りログ退避処理が
 * 動くように修正
 * 
 * 119   08/12/03 15:35 Tsujimura543
 * (bookey起動時に)ログファイルが 64MB より大きくなっていたら、
 * ファイル名を変更し、退避するようにした
 * 
 * 118   08/10/22 18:20 Tsujimura543
 * OnButtonProxy() 実行中も「閉じる」ボタンを disable にするようにした
 * 
 * 117   08/10/22 17:13 Tsujimura543
 * 『「閉じる」ボタンを enable/disable にする』処理を修正、復活させた
 * 
 * 116   07/12/05 23:17 Tsujimura543
 * unbase64() の引数追加に伴う修正を実施
 * 
 * 115   07/11/13 23:08 Tsujimura543
 * リファクタリング
 * 
 * 114   07/09/05 2:35 Tsujimura543
 * Debugビルド版は setDump() するようにした
 * 
 * 113   07/09/05 0:52 Tsujimura543
 * OnInitialUpdate() が Releaseビルド時にコンパイルエラーになってしまって
 * たのを修正
 * 
 * 112   07/09/05 0:29 Tsujimura543
 * m_verboseFp を閉じる直前に、タイムスタンプを書くようにした
 * 
 * 111   07/09/04 23:31 Tsujimura543
 * m_verboseFp を閉じる場所を CBookeyView のデストラクタに移動
 * 
 * 110   07/07/09 18:38 Tsujimura543
 * 日本語モードと英語モードを切り替える機能を追加
 * (現時点では、この機能は、デバッグビルド時のみ有効となる)
 * 
 * 109   07/06/08 21:36 Tsujimura543
 * 「specialSetting 時に setProxyInfo() を呼んでいない不具合」を修正
 * 
 * 108   07/04/11 15:01 Tsujimura543
 * bookey 起動直後の proxy 設定関連の処理をいったん fix
 * 
 * 107   07/04/10 23:13 Tsujimura543
 * 「proxy設定を何度も繰り返し質問してしまう現象」に対する対策を追加
 * 
 * 106   07/04/09 16:58 Tsujimura543
 * proxy設定を何度も繰り返し質問してしまう現象に対処
 * 
 * 105   07/03/28 20:29 Tsujimura543
 * ブックマーク登録処理中は「プロキシサーバ設定」ボタンを disable にする
 * ようにした
 * 
 * 104   07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 103   07/03/26 23:16 Tsujimura543
 * ローカルOPML登録時にメモリ破壊が発生する可能性のある箇所を発見、
 * 修正を実施
 * 
 * 102   07/03/20 0:17 Tsujimura543
 * コメントを修正
 * 
 * 101   07/03/20 0:17 Tsujimura543
 * SetProxyInfo() を修正。一度設定がうまくいった後で、設定が書き換わってし
 * まう可能性を排除
 * 
 * 100   07/03/16 23:03 Tsujimura543
 * SetProxyInfo() の仕様を変更。強制保存モードを用意した
 * 
 * 99    07/03/16 1:03 Tsujimura543
 * proxyサーバ経由でないとインターネットアクセスできないのに、proxyサーバ
 * を使わない設定になっている場合の対策を追加
 * 
 * 98    07/03/15 22:43 Tsujimura543
 * ソースコードを整理
 * 
 * 97    07/03/15 22:35 Tsujimura543
 * proxy設定確認ダイアログが表示された場合、初期設定ファイル(bookey.inf)
 * からユーザ名、パスワード等の情報が消えてしまう不具合に対処
 * [OnInitialUpdate() より OnShowWindow() の方が先に動き出すことを失念して
 * いた]
 * 
 * 96    07/03/14 23:35 Tsujimura543
 * 不要になったコードを削除
 * 
 * 95    07/03/14 23:32 Tsujimura543
 * URL キューイング機能を実装
 * 
 * 94    07/03/14 20:10 Tsujimura543
 * (1) StdAfx.h をインクルードしなくてもいいようにした
 * (2) proxy関連のもろもろの修正、追加 (BloGolEe の成果を取り込む)
 * (3) 上記の修正に合わせて、設定ファイルの読み書き処理をアップデート
 * 
 * 93    07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 92    07/01/16 23:14 Tsujimura543
 * 英語モード対応
 * 
 * 91    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 90    07/01/04 18:42 Tsujimura543
 * 各ブックマークサービスへの登録処理終了後も「ブックマーク登録中」
 * ダイアログが消えずに残ることがある現象に対処した
 * 
 * 89    06/08/23 22:10 Tsujimura543
 * 1470.netリニューアル版の「削除」時にユーザ情報を設定した場合、
 * その設定内容を初期設定ファイルに反映できるようにした
 * 
 * 88    06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 * 
 * 87    06/07/18 21:35 Tsujimura543
 * デストラクタに encodeURL2() 内メモリ領域解放処理を追加
 * 
 * 86    06/07/11 18:21 Tsujimura543
 * コメントの修正、整理
 * 
 * 85    06/07/11 18:14 Tsujimura543
 * SetFocus() 絡みの修正を実施 (「実行中」ダイアログに focus が当たらるよう
 * に調整した)
 * 
 * 84    06/07/05 18:19 Tsujimura543
 * CUserInfo 導入によるリファクタリング第13段階、終了
 * 
 * 83    06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 82    06/07/05 13:09 Tsujimura543
 * 初期設定ファイルから読み取った内容を解析、格納、照合する処理、
 * 初期設定ファイルへ書き出す処理を parameter.{h,cpp} として分離独
 * 立させた
 * 
 * 81    06/07/05 11:23 Tsujimura543
 * 「ブックマーク登録スレッド」関連部分を bookeyView.cpp から分離独立させ、
 * registerBookmark.cpp を作成した
 * 
 * 80    06/07/04 23:48 Tsujimura543
 * CheckEncodedPassword() をリファクタリング
 * 
 * 79    06/07/04 22:36 Tsujimura543
 * LoadSetting() をさらにリファクタリング
 * 
 * 78    06/07/04 21:46 Tsujimura543
 * LoadSetting(), SaveSetting(), CheckEncodedPassword() をリファクタリング
 * 
 * 77    06/07/04 10:51 Tsujimura543
 * 時間のかかる処理の実行中は「閉じる」ボタンを disable にしようと試みる
 * (が、うまくいかない)
 * 
 * 76    06/07/04 10:34 Tsujimura543
 * 砂時計カーソル関連、修正
 * 
 * 75    06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 74    06/07/03 14:36 Tsujimura543
 * ソースコードを整理
 * 
 * 73    06/07/03 14:23 Tsujimura543
 * (1) ProceedingDialog 絡みの改修 (ProceedingDialog が後ろに隠れてしまう
 *     ことがある件の対策実施、ProceedingDialog の delete時に例外が発生す
 *     ることがある件の対策実施)
 * (2) http://cgi.itmedia.co.jp/rss/ のリダイレクタに対応
 * 
 * 72    06/06/29 21:27 Tsujimura543
 * ニフティクリップのパスワード読み込み処理にバグがあったのを修正
 * 
 * 71    06/06/29 18:47 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 70    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 69    06/06/28 15:54 Tsujimura543
 * ブックマーク登録者数を調べて表示する機能を追加
 * 
 * 68    06/06/22 21:21 Tsujimura543
 * inquery → inquiry に修正(綴りミス)
 * 
 * 67    06/06/22 21:20 Tsujimura543
 * SetBookeyInfo() を修正(キャンセルボタン押下時は userInfo.Init(false);
 * する必要はない)
 * 
 * 66    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() を実行しても、設定が変更できなくなって
 * しまっていた(エンバグ)のを修正。変更できるようにした
 * 
 * 65    06/06/22 14:53 Tsujimura543
 * Webページ情報取得処理を別スレッド化した
 * 
 * 64    06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 63    06/06/15 12:55 Tsujimura543
 * 「管理ツール起動」や「設定」時にも EnableButton() するようにした
 * 
 * 62    06/06/14 12:06 Tsujimura543
 * CUserInfo 導入によるリファクタリング第6段階、終了
 * 
 * 61    06/06/14 11:44 Tsujimura543
 * CUserInfo 導入によるリファクタリング第5段階、終了
 * 
 * 60    06/06/13 22:11 Tsujimura543
 * RegisterBookmark() をリファクタリング
 * 
 * 59    06/06/13 21:40 Tsujimura543
 * タイトル取得中、タグ候補抽出中の進行状況ダイアログを表示するようにした
 * 
 * 58    06/06/13 21:11 Tsujimura543
 * ブックマーク登録中でも画面再描画できるようにしてみた
 * 
 * 57    06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 56    06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 55    06/06/06 22:23 Tsujimura543
 * CUserInfo 導入によるリファクタリング第2段階、終了
 * 
 * 54    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 53    06/06/05 22:12 Tsujimura543
 * スレッド間で競合する虞のある領域へのアクセスに関して、念のために
 * critical section を導入してみた(が、特に今までと変わっていない)
 * 
 * 52    06/06/01 23:10 Tsujimura543
 * CUserInfo 導入によるリファクタリング第1段階、終了
 * 
 * 51    06/06/01 20:28 Tsujimura543
 * CBookeyDlg 内のユーザ名、パスワードを CUserInfo を使って管理する
 * ように変更した
 * 
 * 50    06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 49    06/06/01 19:04 Tsujimura543
 * ブックマーク種別を示す enum 値を、enum CUserInfo::bookmarkType に
 * 一本化した
 * 
 * 48    06/06/01 18:49 Tsujimura543
 * enum bookmarkType の定義を CBookeyView から CUserInfo に移した
 * 
 * 47    06/06/01 18:28 Tsujimura543
 * RegisterBookmark() 内でいったん RBparam_t な領域をコピーしてから
 * 使うように変更
 * 
 * 46    06/06/01 17:19 Tsujimura543
 * CUserInfo クラスを導入
 * 
 * 45    06/06/01 15:13 Tsujimura543
 * struct RBparam を RBuser_t を使って定義し直した
 * 
 * 44    06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 43    06/05/29 17:15 Tsujimura543
 * http://markezine.jp/ のリダイレクタに対応
 * 
 * 42    06/05/29 17:03 Tsujimura543
 * http://codezine.jp/ のリダイレクタ(というより、最終的に移動したいURLに
 * 強制的に飛ばす)に対応
 * 
 * 41    06/05/26 15:33 Tsujimura543
 * ?fr=rdf を削除対象に追加 (ThinkIT)
 * 
 * 40    06/05/25 20:16 Tsujimura543
 * ?topic=1 を削除対象に追加 (japan.linux.com)
 * 
 * 39    06/05/25 19:20 Tsujimura543
 * http://www.pheedo.jp/ と http://www.neowing.co.jp/ のリダイレクタに対応
 * 
 * 38    06/05/25 17:12 Tsujimura543
 * &from=rss を削除対象に追加 (スラッシュドット ジャパン)
 * 
 * 37    06/05/25 17:08 Tsujimura543
 * ?from=top を削除対象に追加 (読売新聞)
 * 
 * 36    06/05/25 16:55 Tsujimura543
 * feedburner.jp と google.com のリダイレクタに対応した
 * 
 * 35    06/05/23 14:04 Tsujimura543
 * getTitle() と extractTags() の連携による「はてなブックマーク」からの
 * タグ候補取得をサポート
 * 
 * 34    06/05/11 16:43 Tsujimura543
 * ?in=rssw (MSN毎日新聞) を削除対象に追加
 * 
 * 33    06/04/06 22:16 Tsujimura543
 * はてなブックマークの「コレクション」への追加に対応
 * 
 * 32    06/04/04 12:08 Tsujimura543
 * ?fr=RSS を削除対象に追加
 * 
 * 31    06/03/29 21:42 Tsujimura543
 * ブックマーク登録時の ProceedingDialog の表示の on/off を切り替える回数
 * を抑制
 * 
 * 30    06/03/29 18:30 Tsujimura543
 * ドリコムRSSへのブックマーク(Clip)登録に対応した
 * 
 * 29    06/03/27 17:21 Tsujimura543
 * RegisterBookmarkDialog を使っていた痕跡を削除
 * 
 * 28    06/03/27 17:13 Tsujimura543
 * RegisterBookmarkDialog の代わりに ProceedingDialog を使うようにした
 * 
 * 27    06/03/13 20:56 Tsujimura543
 * タグ候補の表示を ON/OFF できるようにした
 * 
 * 26    06/03/13 16:51 Tsujimura543
 * FeedBurner もしくは Yahoo! Japan のリダイレクタを経由するWebページは
 * リダイレクト先の URL をブックマーク対象の URL とみなすようにした 
 * 
 * 25    06/03/10 19:11 Tsujimura543
 * デコード失敗時のリカバリ処理が無限ループになるのを予防する処理を
 * 追加 (無限ループになることはないはずだが、念のため)
 * 
 * 24    06/03/09 16:19 Tsujimura543
 * SaveSetting() を修正
 * 
 * 23    06/03/09 15:55 Tsujimura543
 * CheckEncodedPassword() を追加、パスワードデコード失敗時の対策を実現
 * 
 * 22    06/02/06 17:11 Tsujimura543
 * パスワードの中身が破壊されている場合に再設定を促す処理を追加
 * 
 * 21    05/11/30 23:43 Tsujimura543
 * extractTags() の第3引数を (I) から (I/O) へ変更
 * 
 * 20    05/11/30 23:28 Tsujimura543
 * タグ候補抽出処理を追加
 * 
 * 19    05/11/02 18:47 Tsujimura543
 * ref=atom なども削除対象に追加
 * 
 * 18    05/11/02 12:04 Tsujimura543
 * ?from=RSS というパターンにも対応
 * 
 * 17    05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 16    05/11/01 18:37 Tsujimura543
 * 登録対象の URL の末尾に ?{ref|from}=rss が付いている場合は削除するよう
 * にした
 * 
 * 15    05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 14    05/10/29 1:11 Tsujimura543
 * 設定ファイル保存処理を修正 (利用するブックマークサービスを減らすような
 * 設定変更時に保存内容がおかしくなる不具合があった)
 * 
 * 13    05/10/28 21:14 Tsujimura543
 * 領域解放処理追加
 * 
 * 12    05/10/24 20:36 Tsujimura543
 * (1) はてな投げ銭対応
 * (2) ブックマーク登録中ダイアログを新設
 * (3) 各種バグ修正
 * 
 * 11    05/10/24 14:46 Tsujimura543
 * (1) コンテキストメニュー処理を追加
 * (2) 同時ブックマーク登録ダイアログで中止を押すというのを何回か繰り返す
 *     と、そのうち落ちる現象の原因が判明(クリップボードからのコピー時の
 *     メモリ解放誤りだった)。修正 + 動作確認済み。
 * 
 * 10    05/10/24 11:10 Tsujimura543
 * 設定したはずの BlogPeople のパスワードが次回起動時に消えてしまう
 * 不具合に対処
 * 
 * 9     05/10/21 19:56 Tsujimura543
 * MM/Memo と BlogPeople の同時ブックマーク登録にも対応
 * 
 * 8     05/10/21 18:03 Tsujimura543
 * クリップボード経由での「ブックマーク対象URL」の取得に対応
 * 
 * 7     05/10/21 16:36 Tsujimura543
 * ファイルのドラッグアンドドロップにも対応
 * 
 * 6     05/10/20 21:22 Tsujimura543
 * ~CBookeyView() に領域解放処理を追加
 * 
 * 5     05/10/15 1:02 Tsujimura543
 * ユーザ名とパスワードを bookDlg に渡せるようにした
 * 
 * 4     05/10/15 0:07 Tsujimura543
 * ユーザ名とパスワードを設定ファイルに保存するようにした
 * 
 * 3     05/10/14 20:38 Tsujimura543
 * ドラッグ・アンド・ドロップ対応作業完了
 * 
 * 2     05/10/14 15:04 Tsujimura543
 * ドラッグ・アンド・ドロップ機能(正確にはドロップのみ)対応完了
 * 
 * 1     05/10/14 14:37 Tsujimura543
 * 新規作成 (ドラッグ・アンド・ドロップ機能サポート用)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "bookeyDoc.h"
#include "bookeyView.h"
#include "SettingDialog.h"
#include "confirmProxy.h"

#include "parameter.h"
#include <process.h>
#include <sys/stat.h>
#ifdef _INTEGRAL_MAX_BITS
#if _INTEGRAL_MAX_BITS >= 64
#define USE_STAT_64
#endif
#endif  /* _INTEGRAL_MAX_BITS */

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookeyView.cpp 3     09/06/22 22:31 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyView

IMPLEMENT_DYNCREATE(CBookeyView, CFormView)

BEGIN_MESSAGE_MAP(CBookeyView, CFormView)
	//{{AFX_MSG_MAP(CBookeyView)
	ON_BN_CLICKED(IDC_BUTTON_TOOL, OnButtonTool)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, OnButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_FINISH, OnButtonFinish)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_CHECK_TAG_SUGGESTION, OnCheckTagSuggestion)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_USERS, OnCheckUsers)
	ON_BN_CLICKED(IDC_BUTTON_PROXY, OnButtonProxy)
	ON_BN_CLICKED(IDC_CHECK_LANGUAGE, OnCheckLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyView クラスの構築/消滅

CBookeyView::CBookeyView()
	: CFormView(CBookeyView::IDD)
{
	//{{AFX_DATA_INIT(CBookeyView)
	m_useTagSuggestion = FALSE;
	m_useUsers = FALSE;
	//}}AFX_DATA_INIT

    m_registerBookmarkThread = NULL;
    m_param.active           = FALSE;
    m_procCreated            = false;

    char *p = __argv[0];
    strcpy( m_path, p );
    p = m_path;
    char *q = strrchr( p, '/' );
    if ( !q )
        q = strrchr( p, '\\' );
    if ( q && (q - 1 > p) && (*(q - 1) != ':') )
        *q = NUL;

    m_numOfWaiting = 0;
    m_waitingHead  = -1;
    m_waitingTail  = -1;

    InitializeCriticalSection( &m_cs_bookey );
}

CBookeyView::~CBookeyView()
{
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();

    if ( checkProxyInfo() ) {
        // proxy関連の設定に誤りがあると思われる場合、次回起動時に再設定可能と
        // するため、いまの設定をいったん破棄する
        bp->m_proxyType = CBookeyApp::autoDetect;
        SaveSetting();
    }

    // 領域解放
    DeleteCriticalSection( &m_cs_bookey );
    encodeURL( NULL );
    encodeURL2( NULL );
    encodeURLex( NULL );
    base64( NULL, 0 );

    if ( m_procCreated )
        m_procDialog.DestroyWindow();

    if ( bp->m_verboseFp ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );
        fprintf( bp->m_verboseFp,
                 "\n*** logging end:   %d/%02d/%02d %02d:%02d:%02d ***\n",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
        fclose( bp->m_verboseFp );
        bp->m_verboseFp = NULL;
    }
}

void CBookeyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookeyView)
	DDX_Check(pDX, IDC_CHECK_TAG_SUGGESTION, m_useTagSuggestion);
	DDX_Check(pDX, IDC_CHECK_USERS, m_useUsers);
	//}}AFX_DATA_MAP
}

BOOL CBookeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CBookeyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

    LoadSetting();
    SetProxyInfo();

    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_TAG_SUGGESTION );
    p->SetCheck( m_useTagSuggestion ? 1 : 0 );

    p = (CButton *)GetDlgItem( IDC_CHECK_USERS );
    p->SetCheck( m_useUsers ? 1 : 0 );

    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
#ifdef  _DEBUG
    LCID        l   = getLanguageCode();

    p = (CButton *)GetDlgItem( IDC_CHECK_LANGUAGE );
    p->SetCheck( l != bp->m_langCode ? 1 : 0 );
    setLanguageCode( bp->m_langCode );
    bp->ReInitialize();
#endif

    CStatic *sp = (CStatic *)GetDlgItem( IDC_WAITING );
    sp->ShowWindow( SW_HIDE );

    if ( bp->m_verbose ) {
        char            filename[MAX_PATH];
#ifdef  USE_STAT_64
        struct _stati64 s;
#else
        struct stat     s;
#endif  /* USE_STAT_64 */

        sprintf( filename, "%s/" BOOKEY_LOG_FILE, m_path );
#ifdef  USE_STAT_64
        if ( !_stati64( filename, &s ) ) {
            if ( s.st_size > (__int64)(1024 * 1024 * 64) ) {
#else   /* !USE_STAT_64 */
        if ( !stat( filename, &s ) ) {
            if ( (unsigned long)s.st_size > 1024 * 1024 * 64 ) {
#endif  /* !USE_STAT_64 */
                char        backup[MAX_PATH];
                time_t      t = time( NULL );
                struct tm   *tm = localtime( &t );

                sprintf( backup,
                         "%s/" BOOKEY_LOG_FILE ".%04d%02d%02d%02d%02d%02d",
                         m_path,
                         tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                         tm->tm_hour, tm->tm_min, tm->tm_sec );
                rename( filename, backup );
            }
        }

        bp->m_verboseFp = fopen( filename, "a" );
        if ( bp->m_verboseFp ) {
            time_t      t   = time( NULL );
            struct tm   *tm = localtime( &t );
            fprintf( bp->m_verboseFp,
                   "\n\n*** logging start: %d/%02d/%02d %02d:%02d:%02d ***\n",
                     tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                     tm->tm_hour, tm->tm_min, tm->tm_sec );
#ifdef  _DEBUG
            setDump( TRUE, bp->m_verboseFp );
#endif
        }
        setVerbose( bp->m_verbose, bp->m_verboseFp );
    }
}

void CBookeyView::SetProxyInfo( bool saveForcely /* = false */ )
{
    CBookeyApp              *bp = (CBookeyApp *)AfxGetApp();
    CBookeyApp::proxyType   saveProxyType = bp->m_proxyType;

    if ( bp->m_proxyType == CBookeyApp::autoDetect ) {
#if 0
        setConfirmProxyInfoFunc( confirmProxyInfo );
#else
        setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
#endif
        bp->m_useProxy = isUsedProxy() == TRUE ? true : false;
    }
    if ( (bp->m_proxyType == CBookeyApp::manualSetting)  ||
         (bp->m_proxyType == CBookeyApp::specialSetting)    ) {
        if ( bp->m_useProxy ) {
            setProxyInfo( bp->m_proxyServer,
                          (unsigned short)(bp->m_proxyPort),
                          bp->m_proxyUsername,
                          bp->m_proxyPassword );
        }
    }
    setUseProxy( bp->m_useProxy );

    if ( saveForcely || (saveProxyType != bp->m_proxyType) )
        SaveSetting();
    if ( saveForcely )
        setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
}

/////////////////////////////////////////////////////////////////////////////
// CBokeyView クラスの診断

#ifdef _DEBUG
void CBookeyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBookeyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CBookeyDoc* CBookeyView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBookeyDoc)));
	return (CBookeyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBookeyView クラス 登録待ちURLキュー関連処理

long    CBookeyView::putWaiting( const char *url )
{
    long    ret = -1;
    long    num = -1;
    char    tmp[BUFSIZ];

    if ( !url || !(*url) )
        return ( ret );

    EnterCriticalSection( &m_cs_bookey );
    num = m_numOfWaiting;
    LeaveCriticalSection( &m_cs_bookey );

    if ( num >= MAX_WAITING_NUM ) {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_BUSY_GETTING);
        text.LoadString( IDS_TXT_BUSY_GETTING);
        MessageBox( text,   // まだ前のブックマーク登録作業中です。
                            // あとでやり直してください。
                    title,  // 登録作業中
                    MB_OK|MB_ICONWARNING );
        return ( ret );
    }

    EnterCriticalSection( &m_cs_bookey );

    if ( m_waitingHead == m_waitingTail )
        m_waitingHead = m_waitingTail = 0;

    m_waitingURLs[m_waitingHead] = url;
    m_waitingHead = (m_waitingHead + 1) % MAX_WAITING_NUM;

    ret = ++m_numOfWaiting;

    LeaveCriticalSection( &m_cs_bookey );

    LCID    l = getLanguageCode();
    sprintf( tmp,
             l == 0x0411 ?
               "登録待ち: %d件"  :
             ret == 1 ?
               "Waiting: %d URL" :
               "Waiting: %d URLs",
             ret );
    CStatic *sp = (CStatic *)GetDlgItem( IDC_WAITING );
    sp->SetWindowText( tmp );
    sp->ShowWindow( SW_SHOW );

    return ( ret );
}

CString CBookeyView::getWaiting()
{
    CString s = "";
    char    tmp[BUFSIZ];
    long    num = -1;

    EnterCriticalSection( &m_cs_bookey );
    num = m_numOfWaiting;
    LeaveCriticalSection( &m_cs_bookey );

    if ( num == 0 )
        return ( s );

    EnterCriticalSection( &m_cs_bookey );

    s = m_waitingURLs[m_waitingTail];
    m_waitingTail = (m_waitingTail + 1) % MAX_WAITING_NUM;
    if ( m_waitingHead == m_waitingTail )
        m_waitingHead = m_waitingTail = 0;

    num = --m_numOfWaiting;

    LeaveCriticalSection( &m_cs_bookey );

    LCID    l   = getLanguageCode();
    CStatic *sp = (CStatic *)GetDlgItem( IDC_WAITING );
    if ( num > 0 ) {
        sprintf( tmp,
                 l == 0x0411 ?
                   "登録待ち: %d件"  :
                 num == 1 ?
                   "Waiting: %d URL" :
                   "Waiting: %d URLs",
                 num );
        sp->SetWindowText( tmp );
        sp->ShowWindow( SW_SHOW );
    }
    else
        sp->ShowWindow( SW_HIDE );

    return ( s );
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyView クラスの追加処理

// 設定情報読み込み
void    CBookeyView::LoadSetting()
{
    char            filename[MAX_PATH];
    FILE            *fp;
    char            key[BUFSIZ];
    char            buf[BUFSIZ];
    char            tmp[BUFSIZ];
    unsigned char   rsaString[BUFSIZ];
    char            *p;
    size_t          l   = 0;
    CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

    key[0]       = NUL;
    rsaString[0] = NUL;

    sprintf( filename, "%s/" BOOKEY_INF_FILE, m_path );
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p                      &&
                    ((l = strlen( p )) > 0) &&
                    (p[l - 1] == '\n')         )
                p[l - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( evalKey( p, "useTagSuggestion", m_useTagSuggestion ) )
                continue;
            if ( evalKey( p, "useUsers", m_useUsers ) )
                continue;
#ifdef  _DEBUG
            if ( evalKey( p, "langCode", pp->m_langCode ) )
                continue;
#endif
            if ( evalKey( p, "verbose", pp->m_verbose ) )
                continue;

            if ( evalKey( p, "proxyType", tmp ) ) {
                if ( !strcmp( tmp, "notUsed" ) ) {
                    pp->m_proxyType = CBookeyApp::notUsed;
                    pp->m_useProxy  = false;
                }
                else if ( !strcmp( tmp, "specialSetting" ) )
                    pp->m_proxyType = CBookeyApp::specialSetting;
                else if ( !strcmp( tmp, "manualSetting" ) )
                    pp->m_proxyType = CBookeyApp::manualSetting;
                else
                    pp->m_proxyType = CBookeyApp::autoDetect;
                continue;
            }

            if ( (pp->m_proxyType == CBookeyApp::specialSetting) ||
                 (pp->m_proxyType == CBookeyApp::manualSetting)     ) {
                if ( evalKey( p, "useProxy", pp->m_useProxy ) )
                    continue;
                if ( evalKey( p, "proxyServer", pp->m_proxyServer ) )
                    continue;
                if ( evalKey( p, "proxyPort", pp->m_proxyPort ) )
                    continue;
                if ( evalKey( p, "proxyUsername", pp->m_proxyUsername ) )
                    continue;
                if ( evalKey( p, "proxyPassword", pp->m_proxyPassword ) )
                    continue;
            }

            if ( key[0] == NUL ) {
                if ( evalKey( p, "encryptedKey", key ) ) {
                    size_t  sz = 0;

                    unbase64( (unsigned char *)key,
                              (unsigned char *)rsaString,
                              &sz );
                    rewind( fp );
                }
                continue;
            }

            if ( pp->EvalKeys( p, rsaString ) )
                continue;
        }
        fclose( fp );
    }

    /* 必要があれば、パスワードの再設定を行なう */
    bool    needToSave = false;

    pp->ResetUserInfo( needToSave );
    if ( needToSave )
        SaveSetting();
}

// 設定情報書き出し
void    CBookeyView::SaveSetting()
{
    char            filename[MAX_PATH];
    FILE            *fp;
    char            key[BUFSIZ];
    unsigned char   *rsaString;
    bool            encrypted;
    bool            done = false;
    int             retryCount = 0;
    CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

    do {
        key[0]    = NUL;
        rsaString = NULL;
        encrypted = false;

        sprintf( filename, "%s/" BOOKEY_INF_FILE, m_path );
        if ( ( fp = fopen( filename, "w" ) ) != NULL ) {
            fputs( "[bookmark target]\n", fp );
            pp->WriteKeys( fp,  key, &rsaString, encrypted );
            if ( encrypted && key[0] ) {
                writeKey( fp, "encryptedKey", key );
                freeRSAkey( rsaString );
            }

            fputs( "[bookey options]\n", fp );
            writeKey( fp, "useTagSuggestion", m_useTagSuggestion );
            writeKey( fp, "useUsers", m_useUsers );
#ifdef  _DEBUG
            writeKey( fp, "langCode", pp->m_langCode );
#endif
            if ( pp->m_verbose )
                writeKey( fp, "verbose", pp->m_verbose );

            fputs( "[proxy setting]\n", fp );
            if ( (pp->m_proxyType == CBookeyApp::specialSetting) ||
                 (pp->m_proxyType == CBookeyApp::manualSetting)     ) {
                writeKey( fp, "proxyType",
                          pp->m_proxyType == CBookeyApp::specialSetting
                            ? "specialSetting"
                            : "manualSetting" );
                writeKey( fp, "useProxy", pp->m_useProxy );
                if ( pp->m_useProxy ) {
                    writeKey( fp, "proxyServer", pp->m_proxyServer );
                    writeKey( fp, "proxyPort", pp->m_proxyPort );

                    if ( pp->m_proxyUsername.GetLength() > 0 ) {
                        writeKey( fp, "proxyUsername", pp->m_proxyUsername );
                        if ( pp->m_proxyPassword.GetLength() > 0 )
                            writeKey( fp, "proxyPassword",
                                      pp->m_proxyPassword );
                    }
                }
            }
            else if ( pp->m_proxyType == CBookeyApp::notUsed )
                writeKey( fp, "proxyType", "notUsed" );
            else
                writeKey( fp, "proxyType", "autoDetect" );

            fclose( fp );
        }

        /* パスワードが decode できることを確認 */
        if ( encrypted && key[0] )
            done = CheckEncodedPassword();
        else
            done = true;

        if ( done == false ) {
            retryCount++;
            if ( retryCount >= 27 )
                break;
        }
    } while ( done == false );
}

// ブックマークの登録
void    CBookeyView::putBookmark( const char *url )
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    bool        needToSave = false;

    // ブックマーク登録スレッドを生成
    EnterCriticalSection( &m_cs_bookey );
    strcpy( m_param.url, url );
    m_param.procDialog = &m_procDialog;

    /*
     * パスワード未設定、もしくはパスワードが壊れている場合は、
     * パスワードを(再)設定する
     */
    pp->ResetUserInfo( needToSave, m_param );

    m_param.useTagSuggestion = m_useTagSuggestion;
    m_param.useUsers         = m_useUsers;
    LeaveCriticalSection( &m_cs_bookey );

    if ( needToSave )
        SaveSetting();

    EnterCriticalSection( &m_cs_bookey );
    m_param.active = TRUE;

    if ( m_procCreated == false ) {
        m_procDialog.Create( IDD_PROCEEDING_DIALOG );
        m_procCreated = true;
    }
    else
        m_procDialog.ResetDialogText();
    m_procDialog.ShowWindow( SW_HIDE );

    m_registerBookmarkThread = AfxBeginThread( RegisterBookmark,
                                               (void *)&m_param );
    if ( m_registerBookmarkThread ) {
        m_registerBookmarkThread->m_bAutoDelete = FALSE;
        SetTimer( ID_THREAD_REGISTERBOOKMARK,
                  MS_THREAD_REGISTERBOOKMARK,
                  NULL );
        EnableButton( false );
    }
    LeaveCriticalSection( &m_cs_bookey );
    // 説明: なぜわざわざ別スレッドを立てて処理するかというと、
    //       この OnDrop() を抜けるまでドラッグ側のプロセス(Web
    //       ブラウザ)もロックされたままとなるため。OnDrop() と
    //       は独立したスレッドを用意することで、登録作業実行前
    //       に OnDrop() を脱出し、ブックマーク登録ダイアログと
    //       ブラウザの間を行ったり来たりできるようになる。
    //       (ブラウザから文字列をコピー&ペーストしたり、登録対
    //        象 Web を再度読み直したりしたいですよね?)
}

void    CBookeyView::PutBookmark( const char *url )
{
    bool        continous = true;
    char        targetURL[MAX_URLLENGTH + 1];
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    CString     title;
    CString     text;

    if ( !strncmp( url, "ttp:",  4 ) ||
         !strncmp( url, "ttps:", 5 )    )
        sprintf( targetURL, "h%s", url );
    else
        strcpy( targetURL, url );

    if ( (strncmp( targetURL, "http://",  7 ) != 0) &&
         (strncmp( targetURL, "https://", 8 ) != 0)    ) {
        title.LoadString(IDS_TTL_URL_CHECK_RESULT);
        text.LoadString( IDS_TXT_INVALID_URL);
        text += url;
        MessageBox( text, title, MB_OK|MB_ICONWARNING );
        continous = false;
    }
    else if ( pp->IsReady() == false ) {
        OnButtonSetting();
        if ( pp->IsReady() == false ) {
            title.LoadString(IDS_TTL_UNSETTING);
            text.LoadString( IDS_TXT_UNSETTING);
            MessageBox( text, title, MB_OK|MB_ICONWARNING );
            continous = false;
        }
    }

    if ( continous ) {
        BOOL    b;

        EnterCriticalSection( &m_cs_bookey );
        b = m_param.active;
        LeaveCriticalSection( &m_cs_bookey );

        if ( b )
            putWaiting( targetURL );
        else
            putBookmark( targetURL );
    }
}

// ボタンの有効/無効切り替え
void    CBookeyView::EnableButton( bool enable )
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_FINISH );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_TOOL );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_SETTING );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_CHECK_TAG_SUGGESTION );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_CHECK_USERS );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_PROXY );
    p->EnableWindow( enable ? TRUE : FALSE );

    // 「閉じる」ボタンを enable/disable にする
    CWnd    *wnd = AfxGetApp()->m_pMainWnd;
    if ( wnd ) {
        CMenu   *c = wnd->GetSystemMenu( FALSE );
        if ( c )
            c->EnableMenuItem(SC_CLOSE,
                              MF_BYCOMMAND | enable ? MF_ENABLED : MF_GRAYED);
    }
}

/* エンコード済みパスワードが本当にデコードできるのかどうか事前に */
/* 確認しておく (decodeByRSA() がデコードに失敗することがあること */
/* が判明、このメソッドを用意することで[暫定的な]対策とする)      */
bool
CBookeyView::CheckEncodedPassword()
{
    bool            ret = true;
    char            filename[MAX_PATH];
    FILE            *fp;
    char            key[BUFSIZ];
    char            buf[BUFSIZ];
    char            *p;
    unsigned char   rsaString[BUFSIZ];
    size_t          l   = 0;
    CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

    key[0]       = NUL;
    rsaString[0] = NUL;
    sprintf( filename, "%s/" BOOKEY_INF_FILE, m_path );
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p                      &&
                    ((l = strlen( p )) > 0) &&
                    (p[l - 1] == '\n')         )
                p[l - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( key[0] == NUL ) {
                if ( evalKey( p, "encryptedKey", key ) ) {
                    size_t  sz = 0;

                    unbase64( (unsigned char *)key,
                              (unsigned char *)rsaString,
                              &sz );
                    rewind( fp );
                }
                continue;
            }

            pp->CheckKeys( p, rsaString, ret );
        }
        fclose( fp );
    }

    return ( ret ); /* true: デコード成功, false: デコード失敗 */
}

void
CBookeyView::ManagementBookmark()
{
    EnableButton( false );

    CBookeyDlg  dlg;
    dlg.m_needToSave = false;
    dlg.DoModal();
    if ( dlg.m_needToSave )
        SaveSetting();

    EnableButton( true );
}

void
CBookeyView::EditSetting()
{
    EnableButton( false );

    SettingDialog   dlg;
    dlg.DoModal();

    SaveSetting();

    EnableButton( true );
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyView クラスのメッセージ ハンドラ

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBookeyView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    UpdateData( FALSE );	
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CBookeyView::OnButtonTool()
{
    ManagementBookmark();
}

void CBookeyView::OnButtonSetting()
{
    EditSetting();
}

void CBookeyView::OnButtonFinish()
{
    AfxGetMainWnd()->PostMessage( WM_CLOSE );
}

int CBookeyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    if( m_dropTarget.Register( this ) ) {   // ドロップターゲットへの登録
        DragAcceptFiles( TRUE );
        return 0;
    }
    return -1;
}

DROPEFFECT CBookeyView::OnDragEnter(
            COleDataObject* pDataObject,
            DWORD           dwKeyState,
            CPoint          point )
{
    if( pDataObject->IsDataAvailable(CF_TEXT)  ||
        pDataObject->IsDataAvailable(CF_HDROP)    ) {
        return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
                            //  コントロールの状態により、コピーかどうかを通知
    }

	return CFormView::OnDragEnter(pDataObject, dwKeyState, point);
}

void CBookeyView::OnDragLeave()
{
	CFormView::OnDragLeave();
}

DROPEFFECT CBookeyView::OnDragOver(
            COleDataObject* pDataObject,
            DWORD           dwKeyState,
            CPoint          point )
{
    if( pDataObject->IsDataAvailable(CF_TEXT)  ||
        pDataObject->IsDataAvailable(CF_HDROP)    ) {
        return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
    }

	return CFormView::OnDragOver(pDataObject, dwKeyState, point);
}

BOOL CBookeyView::OnDrop(
            COleDataObject* pDataObject,
            DROPEFFECT      dropEffect,
            CPoint          point )
{
    if( pDataObject->IsDataAvailable(CF_TEXT) ) {
        // ドロップされたデータを取得
        HGLOBAL     hData = pDataObject->GetGlobalData(CF_TEXT);
        ASSERT(hData);
        const char  *ptr  = (const char *)GlobalLock(hData);
        char        url[MAX_URLLENGTH + 2];

        // URL を取り出す
        memset( url, 0x00, MAX_URLLENGTH + 1 );
        strncpy( url, ptr, MAX_URLLENGTH );
        GlobalUnlock(hData);
        GlobalFree(hData);

        // ブックマークを登録
        PutBookmark( url );

        return TRUE;
    }

    if( pDataObject->IsDataAvailable(CF_HDROP) ) {
        /* ドロップされたものが「ファイル」の場合 */
        HDROP   hdrop;
        char    filename[MAX_PATH];
        int     num;

        HGLOBAL     hData = pDataObject->GetGlobalData(CF_HDROP);
        ASSERT(hData);
        const char  *ptr  = (const char *)GlobalLock(hData);
        size_t      sz    = MAX_PATH;

        hdrop = (HDROP)ptr;
        /* ドロップされたファイルの個数を得る */
        num = DragQueryFile( hdrop, (UINT)0xFFFFFFFF, NULL, 0 );
        /* ファイルを処理 */
        for ( int i = 0; i < num; i++ ) {
            filename[0] = NUL;
            DragQueryFile( hdrop, i, filename, sz );
            if ( filename[0] ) {
                FILE    *fp;
                char    buf[BUFSIZ];
                char    *p;
                BOOL    flag = FALSE;

                if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                    // URL を取り出す
                    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
                        if ( (flag == FALSE) &&
                             !strncmp( p, "[InternetShortcut]", 18 ) ) {
                            flag = TRUE;
                            continue;
                        }
                        else if ( (flag == TRUE) &&
                                  !strncmp( p, "URL=", 4 ) ) {
                            char    *q;

                            p += 4;
                            q = p + (strlen( p ) - 1);
                            while ((q > p) && ((*q == '\r') || (*q == '\n')))
                                *q-- = NUL;

                            // ブックマークを登録
                            PutBookmark( p );
                            break;
                        }
                        flag = FALSE;
                    }
                    fclose( fp );
                }
            }
        }
        GlobalUnlock(hData);
        GlobalFree(hData);

        return TRUE;
    }

	return CFormView::OnDrop(pDataObject, dropEffect, point);
}

void CBookeyView::OnEditPaste()
{
    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        return;

    HGLOBAL     hData;
    const char  *ptr;
    char        url[MAX_URLLENGTH + 1];

    // クリップボードから URL を取り出す
    OpenClipboard();
    hData = (HGLOBAL)GetClipboardData(CF_TEXT);
    ASSERT(hData);
    ptr = (const char *)GlobalLock(hData);
    memset( url, 0x00, MAX_URLLENGTH + 1 );
    strncpy( url, ptr, MAX_URLLENGTH );
    GlobalUnlock(hData);
 // GlobalFree(hData); ← ここで free してはいけない! (ヒープが不整合を起こす)
    CloseClipboard(); // ← free は CloseClipboard() の中でやっている

    // ブックマークを登録
    PutBookmark( url );
}

void CBookeyView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFormView::OnShowWindow(bShow, nStatus);
	
    if ( bShow == FALSE ) {
        BOOL    b;

        EnterCriticalSection( &m_cs_bookey );
        b = m_param.active;
        LeaveCriticalSection( &m_cs_bookey );

        if ( b ) {
            CString title;
            CString text;

            title.LoadString(IDS_TTL_BUSY_GETTING);
            text.LoadString( IDS_TXT_BUSY_BUSY);
            MessageBox( text,   // まだ前のブックマーク登録作業が終了していま
                                // せん。もうしばらくお待ちください。どれだけ
                                // 待っても終わらない場合は、申し訳ありません
                                // が bookey を強制終了させてください。
                        title,  // 登録作業中
                        MB_OK|MB_ICONWARNING );
        }
    }
#ifdef  _DEBUG
    else {
        CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_LANGUAGE );
        bp->EnableWindow( TRUE );
        bp->ShowWindow( SW_SHOW );
    }
#endif
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBookeyView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPoint  cMenuPt;
	GetCursorPos( &cMenuPt );

#define IDC_MENU_COPY   1
    CMenu   menu;
    CString text;

    text.LoadString(IDS_MENU_PASTE);
    menu.CreatePopupMenu();
    menu.AppendMenu( MF_STRING, IDC_MENU_COPY, text );  // 貼り付け(&P)

    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        menu.EnableMenuItem( IDC_MENU_COPY, MF_GRAYED );

    int iCommand;
	iCommand = menu.TrackPopupMenu(
                TPM_LEFTALIGN | TPM_BOTTOMALIGN  |
                TPM_RETURNCMD | TPM_LEFTBUTTON,
                cMenuPt.x, cMenuPt.y, this, NULL );

    if ( iCommand == IDC_MENU_COPY )
	    OnEditPaste();

    menu.DestroyMenu();
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CBookeyView::OnCheckTagSuggestion()
{
    m_useTagSuggestion = !m_useTagSuggestion;

    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_TAG_SUGGESTION );
    if ( m_useTagSuggestion == TRUE )
        p->SetCheck( 1 );
    else
        p->SetCheck( 0 );
    SaveSetting();
}

void CBookeyView::OnCheckUsers()
{
    m_useUsers = !m_useUsers;

    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_USERS );
    if ( m_useUsers == TRUE )
        p->SetCheck( 1 );
    else
        p->SetCheck( 0 );
    SaveSetting();
}

void CBookeyView::OnTimer(UINT nIDEvent)
{
    if ( nIDEvent == ID_THREAD_REGISTERBOOKMARK ) {
        CWinThread  *p;

        KillTimer( nIDEvent );
        EnterCriticalSection( &m_cs_bookey );
        p = m_registerBookmarkThread;
        LeaveCriticalSection( &m_cs_bookey );
        if ( p ) {
            DWORD   exitCode = 0;
            int     status;
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            EnterCriticalSection( &m_cs_bookey );
            status = GetExitCodeThread( p->m_hThread, &exitCode );
            LeaveCriticalSection( &m_cs_bookey );
            if ( (status != FALSE) && (exitCode == STILL_ACTIVE) ) {
             // SetFocus();
                UpdateWindow(); // CBookeyView の再描画
                SetTimer( nIDEvent, MS_THREAD_REGISTERBOOKMARK, NULL );
            }
            else {
                long    num = 0;

                EnterCriticalSection( &m_cs_bookey );
                delete m_registerBookmarkThread;
                m_registerBookmarkThread = NULL;
                m_param.active = FALSE;
                m_procDialog.DestroyWindow();
                m_procCreated = false;
                num = m_numOfWaiting;
                LeaveCriticalSection( &m_cs_bookey );

                if ( checkProxyInfo() ) {
                    // proxy関連の設定に誤りがあると思われる場合、次回起動時に
                    // 再設定可能とするため、いまの設定をいったん破棄する
                    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();

                    bp->m_proxyType = CBookeyApp::autoDetect;
                    SetProxyInfo( true );
                }

                if ( num > 0 ) {
                    CString s = getWaiting();
                    if ( s.GetLength() > 0 ) {
                        putBookmark( s );
                        return;
                    }
                }
                EnableButton( true );
            }
        }
        return;
    }
	
	CFormView::OnTimer(nIDEvent);
}

void CBookeyView::OnButtonProxy() 
{
    CBookeyApp      *bp = (CBookeyApp *)AfxGetApp();
    int             useProxy = bp->m_useProxy;
    char            proxyServer[MAX_SERVERNAME];
    unsigned short  proxyPort;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];

    EnableButton( false );

    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    proxyServer[0]   = NUL;
    proxyPort        = 0;
    proxyUserName[0] = NUL;
    proxyPassword[0] = NUL;
    initProxyInfo();
    if ( bp->m_proxyServer.GetLength() == 0 ) {
        useProxy = FALSE;
        getProxyInfo( &useProxy, proxyServer, &proxyPort,
                      proxyUserName, proxyPassword );
    }
    else {
        strcpy( proxyServer, bp->m_proxyServer );
        proxyPort = (unsigned short)(bp->m_proxyPort);
        strcpy( proxyUserName, bp->m_proxyUsername );
        strcpy( proxyPassword, bp->m_proxyPassword );
    }
    confirmProxyInfo( &useProxy, proxyServer, &proxyPort,
                      proxyUserName, proxyPassword );

    if ( useProxy == FALSE ) {
        bp->m_proxyType = CBookeyApp::notUsed;
        bp->m_useProxy  = false;
    }
    else if ( bp->m_proxyType == CBookeyApp::manualSetting ) {
        bp->m_proxyType = CBookeyApp::specialSetting;
        if ( bp->m_useProxy ) {
            setProxyInfo( bp->m_proxyServer,
                          (unsigned short)(bp->m_proxyPort),
                          bp->m_proxyUsername,
                          bp->m_proxyPassword );
        }
    }
    setUseProxy( bp->m_useProxy );
    syncProxyInfo();
    SaveSetting();

    EnableButton( true );
}

void CBookeyView::OnCheckLanguage() 
{
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
    bp->m_langCode = getLanguageCode();
    if ( bp->m_langCode == 0x0409 ) {
        bp->m_langCode = 0x0411;
    }
    else {
        bp->m_langCode = 0x0409;
    } 
    setLanguageCode( bp->m_langCode );
    SaveSetting();
    bp->ReInitialize();
}

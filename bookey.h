/*
 * bookey.h : ソーシャルブックマーク管理プログラム
 *      アプリケーション メイン ヘッダーファイル
 *          written by H.Tsujimura  29 Sep 2005
 *
 * $Log: /comm/bookey/bookey.h $
 * 
 * 2     09/06/22 22:31 tsupo
 * 0.63c版
 * 
 * 71    09/06/22 17:56 Tsujimura543
 * 日本語モード←→英語モード切替関連、修正
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 70    09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 69    08/10/21 22:05 Tsujimura543
 * 「ヘルプ」メニューに「サポート」(2件)、「コミュニティ」(2件)を追加
 * 
 * 68    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 67    08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 66    08/05/07 19:17 Tsujimura543
 * MAX_NUM_OF_USERINFO の値を修正
 * (また、ローカルOPMLの設定が保存できない不具合が発生していた
 *  [tumblr 対応時の修正漏れ])
 * 
 * 65    07/10/31 16:58 Tsujimura543
 * tumblr に対応
 * 
 * 64    07/10/17 23:09 Tsujimura543
 * 余分なプリプロセッサ制御文を削除
 * 
 * 63    07/10/05 2:42 Tsujimura543
 * BBAuth 対応関連の各種修正を実施
 * 
 * 62    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 61    07/09/04 22:43 Tsujimura543
 * m_verboseFp を導入
 * 
 * 60    07/09/04 22:38 Tsujimura543
 * BOOKEY_LOG_FILE を追加
 * 
 * 59    07/09/04 22:30 Tsujimura543
 * m_verbose を導入
 * 
 * 58    07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 57    07/06/06 22:14 Tsujimura543
 * MAX_NUM_OF_USERINFO の値を修正
 * (ローカルOPMLの設定が保存できない不具合が発生していた)
 * 
 * 56    07/05/25 23:02 Tsujimura543
 * MS_THREAD_REGISTERBOOKMARK の値を 500 から 400 に変更してみた
 * 
 * 55    07/05/23 16:11 Tsujimura543
 * Timelog への登録(発言)に対応
 * 
 * 54    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 53    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 52    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 51    07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 50    07/03/14 17:52 Tsujimura543
 * m_proxyPort の型を int から long に変更
 * 
 * 49    07/03/14 17:07 Tsujimura543
 * (1) StdAfx.h をインクルードしなくてもいいようにした
 * (2) proxy関連のもろもろの修正、追加 (BloGolEe の成果を取り込む)
 * 
 * 48    07/02/16 16:35 Tsujimura543
 * コメントを修正
 * 
 * 47    07/01/29 23:59 Tsujimura543
 * UserInfo() を修正
 * 
 * 46    07/01/29 17:51 Tsujimura543
 * タグ一覧の取得、タグの削除、タグの置換の各処理を追加
 * 
 * 45    07/01/13 1:42 Tsujimura543
 * CBookeyApp::CBookeyApp() の中から CString#LoadString() すると
 * assertion failed することが判明。対策を実施 (英語モード対応にあたって
 * 発生した障害)
 * 
 * 44    07/01/12 13:21 Tsujimura543
 * 英語モード対応準備
 * 
 * 43    06/12/27 11:47 Tsujimura543
 * RBparam 構造体の定義を bookey.h から分離独立させて RBparam.h とする
 * 
 * 42    06/12/22 21:41 Tsujimura543
 * 「BlogPet 気になる記事」対応
 * 
 * 41    06/12/21 19:13 Tsujimura543
 * (1) JoltMark に対応
 * (2) FC2BOOKMARK、「BlogPet 気になる記事」対応準備
 * 
 * 40    06/11/16 16:43 Tsujimura543
 * CUserInfo 導入によるリファクタリング第16段階、終了
 * 
 * 39    06/11/16 14:02 Tsujimura543
 * CUserInfo 導入によるリファクタリング第15段階、終了
 * 
 * 38    06/10/28 1:14 Tsujimura543
 * 「ローカルOPML」へ登録できないことがある不具合に対処
 * 
 * 37    06/10/26 22:54 Tsujimura543
 * 「ローカルOPML」に対応
 * 
 * 36    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 35    06/10/04 21:11 Tsujimura543
 * POOKMARK Airline → POOKMARK Airlines に修正
 * 
 * 34    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline に対応
 * 
 * 33    06/09/29 23:49 Tsujimura543
 * newsing に対応
 * 
 * 32    06/09/05 11:14 Tsujimura543
 * Visual C++ 2005 でビルドする場合に備えて、ResetDayLightSaving()
 * を追加 (現在リリースしている bookey は Visual C++ 6 にてビルドして
 * いる)
 * 
 * 31    06/08/22 17:48 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 30    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 29    06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 28    06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 * 
 * 27    06/07/14 20:50 Tsujimura543
 * 1470.netリニューアル版に対応
 * 
 * 26    06/07/05 18:19 Tsujimura543
 * CUserInfo 導入によるリファクタリング第13段階、終了
 * 
 * 25    06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 24    06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 23    06/06/29 18:46 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 22    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 21    06/06/28 15:54 Tsujimura543
 * ブックマーク登録者数を調べて表示する機能を追加
 * 
 * 20    06/06/22 21:21 Tsujimura543
 * inquery → inquiry に修正(綴りミス)
 * 
 * 19    06/06/21 21:14 Tsujimura543
 * CUserInfo 導入によるリファクタリング第11段階、終了
 * 
 * 18    06/06/20 14:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第9段階、終了
 * 
 * 17    06/06/19 20:25 Tsujimura543
 * getBPhash() のプロトタイプ宣言を bookey.h から myClip.h へ移す
 * 
 * 16    06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 15    06/06/14 12:06 Tsujimura543
 * CUserInfo 導入によるリファクタリング第6段階、終了
 * 
 * 14    06/06/14 11:44 Tsujimura543
 * CUserInfo 導入によるリファクタリング第5段階、終了
 * 
 * 13    06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 12    06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 11    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 10    06/05/08 14:33 Tsujimura543
 * F1キー押下時に「状況依存ヘルプ」を表示しようとするのを抑制するようにし
 * た
 * 
 * 9     05/11/10 21:20 Tsujimura543
 * (1) 進行状況表示ダイアログの準備用に追加した変数、処理を削除
 * (2) 上記に伴い、イベントを「二重起動チェック」用途専用に変更
 * 
 * 8     05/11/10 14:13 Tsujimura543
 * m_proceedTitle を追加
 * 
 * 7     05/11/10 13:58 Tsujimura543
 * 進行状況表示ダイアログ対応準備として、イベントを導入
 * 
 * 6     05/11/10 12:06 Tsujimura543
 * ドキュメントテンプレート関連の処理をコメントアウトした。これでレジスト
 * リを知らない間に書き換えてしまう可能性も排除できたはず。
 * 
 * 5     05/10/14 13:11 Tsujimura543
 * 別途作成したドラッグ・アンド・ドロップ対応試験プログラムの成果を取り込
 * む
 * 
 * 4     05/10/14 11:07 Tsujimura543
 * 0.02 版 (ドラッグ・アンド・ドロップ未対応版)
 * 
 * 3     05/10/11 17:04 Tsujimura543
 * 初版のタイムスタンプ表記ミスを修正 (コメントのみの修正。動作に影響なし)
 * 
 * 2     05/09/30 23:57 Tsujimura543
 * ブックマークの取得、登録機能の動作確認完了
 */

#if !defined(AFX_BOOKEY_H__958A686C_2250_4067_BFE4_13EA86CC7F61__INCLUDED_)
#define AFX_BOOKEY_H__958A686C_2250_4067_BFE4_13EA86CC7F61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__

#define VC_EXTRALEAN        // Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>       // MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC の Windows コモン コントロール サポート
#endif  // _AFX_NO_AFXCMN_SUPPORT
#endif  // !__AFXWIN_H__

#include <afxole.h>
#include <afxmt.h>
#include "resource.h"		// メイン シンボル
#include "UserInfo.h"
#include "RBparam.h"
#include "EditBookmarkDialog.h"

// ブックマーク登録スレッドに渡すパラメータ格納用構造体
#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#include "encryptRSA.h"
#ifdef __cplusplus
}
#endif

// 各種設定
#define BOOKEY_INF_FILE     "bookey.inf"    // 設定ファイル
#define BOOKEY_DEFAULT_OPML "bookey.opml"   // ローカルOPMLファイル名(default)
#define BOOKEY_LOG_FILE     "bookey.log"    // 調査用ログファイル
#define ID_THREAD_REGISTERBOOKMARK  0xCAFEBEAF
#define MS_THREAD_REGISTERBOOKMARK  400

/////////////////////////////////////////////////////////////////////////////
// CBookeyApp   アプリケーション メイン

class CBookeyApp : public CWinApp
{
public:
	CBookeyApp();

    ~CBookeyApp()
    {
        if ( m_proceed )
            delete m_proceed;
        if ( m_myClip ) {
            free( m_myClip );
            m_myClip = NULL;
            m_bookmarkGotten = false;
        }
    }

#define MAX_NUM_OF_USERINFO 23
    CUserInfo   m_hatena;           // [0]  はてなブックマーク
    CUserInfo   m_delicious;        // [1]  del.icio.us
    CUserInfo   m_mmMemo;           // [2]  MM/memo
    CUserInfo   m_drecomRss;        // [3]  ドリコムRSS
    CUserInfo   m_flog;             // [4]  Flog
    CUserInfo   m_livedoorClip;     // [5]  livedoor クリップ
    CUserInfo   m_ecNaviClip;       // [6]  Buzzurl
    CUserInfo   m_niftyClip;        // [7]  ニフティクリップ
    CUserInfo   m_next1470net;      // [8]  1470.netリニューアル版
    CUserInfo   m_newsing;          // [9]  newsing
    CUserInfo   m_pookmark;         // [10] POOKMARK Airlines
    CUserInfo   m_blueDot;          // [11] Blue Dot
    CUserInfo   m_joltMark;         // [12] JoltMark
    CUserInfo   m_fc2bookmark;      // [13] FC2BOOKMARK
    CUserInfo   m_blogPet;          // [14] BlogPet 気になる記事
    CUserInfo   m_twitter;          // [15] Twitter
    CUserInfo   m_yjBookmark;       // [16] Yahoo! Japan ブックマーク
    CUserInfo   m_yahooBookmarks;   // [17] Yahoo! Bookmarks
    CUserInfo   m_timelog;          // [18] Timelog
    CUserInfo   m_digg;             // [19] digg
    CUserInfo   m_tumblr;           // [20] tumblr
    CUserInfo   m_diigo;            // [21] Blue Dot
    CUserInfo   m_localOpml;        // [22] ローカルOPMLファイル

    CUserInfo   *m_userInfoList[MAX_NUM_OF_USERINFO];

    bool        m_bookmarkGotten;   // ブックマーク情報取得済みか否か

    volatile enum proxyType {
        autoDetect,     // proxy 使用状況自動取得 (default)
        manualSetting,  // proxy 使用状況手動設定、設定ファイルから取得
        specialSetting, // proxy 使用状況手動設定(ユーザ自身によって設定済み)
        notUsed         // proxy は使用しない    (ユーザ自身によって設定済み)
    }           m_proxyType;        // proxy 使用状況取得方法
    bool        m_useProxy;         // proxy を使うか否か
    CString     m_proxyServer;      // proxyサーバ URL (または IPアドレス)
    long        m_proxyPort;        // proxyサーバ ポート番号
    CString     m_proxyUsername;    // proxyサーバ ユーザ名   (必要な場合)
    CString     m_proxyPassword;    // proxyサーバ パスワード (必要な場合)

    MyClip      *m_myClip;          // (取得した)ブックマーク情報
    int         m_numOfClips;       // ブックマーク情報に格納されている
                                    // ブックマークの数
    CString     m_bookmarkName;     // ブックマーク情報に格納されている
                                    // ブックマークのサービス名
    bool        m_verbose;          // ログを出力するか否か
    FILE        *m_verboseFp;       // 調査用ログファイルのファイルポインタ

    CString     m_tcKey;
    CString     m_tcSecret;

    /* ブックマーク登録機能を使う準備ができているか否か */
    bool    IsReady() {
        bool    ret = true;

        if ( (m_hatena         == false) &&
             (m_delicious      == false) &&
             (m_mmMemo         == false) &&
             (m_drecomRss      == false) &&
             (m_flog           == false) &&
             (m_livedoorClip   == false) &&
             (m_ecNaviClip     == false) &&
             (m_niftyClip      == false) &&
             (m_next1470net    == false) &&
             (m_newsing        == false) &&
             (m_pookmark       == false) &&
             (m_blueDot        == false) &&
             (m_joltMark       == false) &&
             (m_fc2bookmark    == false) &&
             (m_blogPet        == false) &&
             (m_twitter        == false) &&
             (m_yjBookmark     == false) &&
             (m_yahooBookmarks == false) &&
             (m_timelog        == false) &&
             (m_digg           == false) &&
             (m_tumblr         == false) &&
             (m_diigo          == false) &&
             (m_localOpml      == false)    )
            ret = false;

        return ( ret );
    }

    // 初期化 (InitInstance() から呼び出せない処理を、InitInstance()
    // に代わって呼び出す)
    void    Initialize();
    void    ReInitialize();

    /* 再設定 */
    void    ResetUserInfo( bool &needToSave );
    void    ResetUserInfo( bool &needToSave, RBparam_t &param );

    /* ユーザ情報表示 */
    void    SetWindowText( CString bookmarkName,
                           CString &username,
                           CString &password,
                           CEdit   *editUsername,
                           CEdit   *editPassword,
                           CButton *executeButton,
                           CString txt );
    void    SetWindowText( CString bookmarkName,
                           CString &username,
                           CString &password,
                           CEdit   *editUsername,
                           CEdit   *editPassword );
    void    SetWindowText( CString bookmarkName,
                           CString &username,
                           CEdit   *editUsername,
                           CEdit   *editPassword );

    /* 問い合わせ */
    bool    InquiryUserInfo( CString bookmark1, CString bookmark2,
                             CString txt);

    /* ブックマークのインポート */
    void    ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction );

    /* ブックマークのエクスポート */
    bool    ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2 );

    /* ブックマークの削除 */
    void    DeleteBookmarks(
                enum CUserInfo::bookmarkType targetBookmark,
                bool                         deleteAll,
                bool                         deleteInteractive );

    /* ブックマークの登録 */
    void    PutBookmarks( const RBparam_t    *p,
                          const char         *accountName,
                          EditBookmarkDialog *editDlg,
                          ProceedingDialog   *procDlg );
    void    PutBookmarks( CString bookmarkName,
                          CString username,
                          CString password );
    bool    PutBookmarks( CString bookmarkNameAsExport,
                          CString bookmarkNameAsImport );

    /* ブックマークの取得 */
    void    GetBookmarks( CString bookmarkName,
                          CString username,
                          CString password );
    bool    GetBookmarks( CString bookmarkName );

    /* タグ一覧の取得 */
    TagList *GetTagList( enum CUserInfo::bookmarkType bmType,
                         int                          &numOfTags );

    /* タグの削除 */
    void    DeleteTag( enum CUserInfo::bookmarkType bmType,
                       const char                   *tag );

    /* タグの置換 */
    void    ReplaceTag( enum CUserInfo::bookmarkType bmType,
                        const char                   *oldTag,
                        const char                   *newTag );

    /* proxy情報ファイルの生成 (for BBAuth) */
    void    MakeProxyText();


    /* 初期設定ファイル関連 */
    bool    EvalKeys(
                const char          *p,      // (I) 設定データ取得対象文字列
                const unsigned char *secret);// (I) 復号に必要な情報(秘密鍵)
    bool    CheckKeys(
                const char          *p,      // (I) 設定データ取得対象文字列
                const unsigned char *secret, // (I) 復号に必要な情報(秘密鍵)
                bool                &ret );  // (O) 復号保証可否
    void    WriteKeys(
                FILE          *fp,      // (I/O) 書き出し先
                char          *key,     // (I)   公開鍵
                unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
                bool          &done );  // (O)   暗号化処理実行済みか否か

    /* bookmarkName に対応する CUserInfo の取得 */
    CUserInfo   *UserInfo( CString bookmarkName, CUserInfo *userInfo );
    CUserInfo   *UserInfo( CString bookmarkName );
    CUserInfo   *UserInfo( enum CUserInfo::bookmarkType bmType );
    CUserInfo   *UserInfoEx( CString bookmarkName );

    /* (日本時間に関して)夏時間フラグリセット */
    bool    ResetDayLightSaving();      // for Visual Studio 2005 runtime

// オーバーライド
	//{{AFX_VIRTUAL(CBookeyApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション
#define BOOKEY_EVENT_PROCEED "__bookey_958A686C_2250_4067_BFE4_13EA86CC7F61__"
    CEvent  *m_proceed; // 二重起動チェック用
    LCID    m_langCode; // 言語(0x0409: 英語(アメリカ), 0x0411: 日本語, ……)

	//{{AFX_MSG(CBookeyApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppSupport();
	afx_msg void OnAppSupport2();
	afx_msg void OnAppCommunity();
	afx_msg void OnAppCommunity2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CBookeyApp( CBookeyApp &obj );
    CBookeyApp  operator = ( CBookeyApp &obj );

    /* その他 */
    bool    SetSigInfo( CString &sKey,    CString &sSecret,
                        const char *sig1, const char *sig2 );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEY_H__958A686C_2250_4067_BFE4_13EA86CC7F61__INCLUDED_)

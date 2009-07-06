/*
 * SettingDialog.h  : ソーシャルブックマーク管理プログラム
 *      SettingDialog クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingDialog.h $
 * 
 * 2     09/07/07 2:15 tsupo
 * 0.63c版
 * 
 * 24    09/06/22 18:04 Tsujimura543
 * タブの位置を上辺(横・上)から右辺(縦・下)に変更
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 23    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 22    08/07/25 17:39 Tsujimura543
 * Diigo に対応
 * 
 * 21    08/02/27 1:11 Tsujimura543
 * m_dialogWidth を追加
 * 
 * 20    08/02/20 23:21 Tsujimura543
 * ディスプレイの縦方向の大きさ(高さ)が 720px 以下の場合は、表示する
 * ダイアログの大きさを縦方向に小さくするようにしてみた
 * 
 * 19    07/10/31 16:58 Tsujimura543
 * tumblr に対応
 * 
 * 18    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 17    07/07/09 19:15 Tsujimura543
 * digg に対応
 * 
 * 16    07/06/07 1:06 Tsujimura543
 * コメントを修正
 * 
 * 15    07/05/23 16:01 Tsujimura543
 * Timelog に対応
 * 
 * 14    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 13    07/04/16 20:45 Tsujimura543
 * Yahoo! ブックマーク 対応
 * 
 * 12    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 11    07/03/30 16:12 Tsujimura543
 * FC2BOOKMARK に対応
 * 
 * 10    06/12/22 22:33 Tsujimura543
 * 「BlogPet 気になる記事」対応
 * 
 * 9     06/12/21 16:37 Tsujimura543
 * JoltMark 対応
 * 
 * 8     06/10/26 21:01 Tsujimura543
 * 「ローカルOPMLファイル」に対応
 * 
 * 7     06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 6     06/10/04 20:24 Tsujimura543
 * pookmark 対応
 * 
 * 5     06/09/29 18:44 Tsujimura543
 * newsing 対応
 * 
 * 4     06/08/23 21:35 Tsujimura543
 * 「1470.netリニューアル版のユーザ情報未設定のまま、削除を実行しようとし
 * たとき」のユーザ情報設定用ダイアログ表示処理回りを実装
 * 
 * 3     06/07/28 23:58 Tsujimura543
 * データの正当性をチェックする処理を追加
 * 
 * 2     06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 */

#if !defined(AFX_SETTINGDIALOG_H__5FD2347F_366A_42E4_AFD9_5E5B9F98840A__INCLUDED_)
#define AFX_SETTINGDIALOG_H__5FD2347F_366A_42E4_AFD9_5E5B9F98840A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SettingHatena.h"
#include "SettingDelicious.h"
#include "SettingMMmemo.h"
#include "SettingDrecom.h"
#include "SettingFlog.h"
#include "SettingLivedoor.h"
#include "SettingEcNavi.h"
#include "SettingNifty.h"
#include "Setting1470net.h"
#include "SettingNewsing.h"
#include "SettingPookmark.h"
#include "SettingBlueDot.h"
#include "SettingJoltMark.h"
#include "SettingBlogPet.h"
#include "SettingFC2bookmark.h"
#include "SettingTwitter.h"
#include "SettingYJbookmark.h"
#include "SettingYahooBookmarks.h"
#include "SettingTimelog.h"
#include "SettingDigg.h"
#include "SettingTumblr.h"
#include "SettingDiigo.h"
#include "SettingLocalOpml.h"

/////////////////////////////////////////////////////////////////////////////
// SettingDialog ダイアログ

class SettingDialog : public CDialog
{
// コンストラクション
public:
	SettingDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(SettingDialog)
	enum { IDD = IDD_SETTING_DIALOG };
	CTabCtrl	m_tabSetting;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(SettingDialog)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
#define NUM_OF_TABS     23                  // タブの総数
    int                 m_numOfTabs;        // タブの総数

    CDialog             *m_dlg[NUM_OF_TABS];// 各タブに貼り付いているダイアログ
    int                 m_activePage;       // 選択されているタブ
    bool                m_1470net;          // for 1470.netリニューアル版

    // ダイアログ実体
    SettingHatena           m_dlg00;
    SettingDelicious        m_dlg01;
    SettingMMmemo           m_dlg02;
    SettingDrecom           m_dlg03;
    SettingFlog             m_dlg04;
    SettingLivedoor         m_dlg05;
    SettingEcNavi           m_dlg06;
    SettingNifty            m_dlg07;
    Setting1470net          m_dlg08;
    SettingNewsing          m_dlg09;
    SettingPookmark         m_dlg10;
    SettingBlueDot          m_dlg11;
    SettingJoltMark         m_dlg12;
    SettingBlogPet          m_dlg13;
    SettingFC2bookmark      m_dlg14;
    SettingTwitter          m_dlg15;
    SettingYJbookmark       m_dlg16;
    SettingYahooBookmarks   m_dlg17;
    SettingTimelog          m_dlg18;
    SettingDigg             m_dlg19;
    SettingTumblr           m_dlg20;
    SettingDiigo            m_dlg21;
    SettingLocalOpml        m_dlg22;

    // タブ切り替え
    int     DispCurrentTab( int activeTab = 0 );

protected:
    // データの正当性チェック
    BOOL    CheckDlgData();

	// メッセージマップ関数
	//{{AFX_MSG(SettingDialog)
	afx_msg void OnButtonAccept();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    SettingDialog( SettingDialog &dlg );
    SettingDialog   operator = ( SettingDialog &dlg );

 // int     m_width;
 // int     m_height;
    int     m_base;
    int     m_dialogWidth;
    bool    m_resized;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_SETTINGDIALOG_H__5FD2347F_366A_42E4_AFD9_5E5B9F98840A__INCLUDED_)

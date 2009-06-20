/*
 * DeleteBookmarkDialog.cpp : ソーシャルブックマーク管理プログラム
 *      ブックマーク削除ダイアログ その1 インプリメンテーション ファイル
 *          written by H.Tsujimura  30 Sep 2005
 *
 * $Log: /comm/bookey/DeleteBookmarkDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 23    08/07/25 22:17 Tsujimura543
 * Diigo 対応準備
 * 
 * 22    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks と Yahoo! ブックマークの「削除」に対応
 * 
 * 21    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 20    07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 19    07/01/12 22:45 Tsujimura543
 * 英語モード対応
 * 
 * 18    07/01/11 17:01 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 17    06/12/22 21:47 Tsujimura543
 * コメント修正
 * 
 * 16    06/12/21 21:18 Tsujimura543
 * JoltMark、FC2BOOKMARK、「BlogPet 気になる記事」に対応
 * 
 * 15    06/10/26 22:38 Tsujimura543
 * 「ローカルOPML」に対応
 * 
 * 14    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 13    06/10/05 22:30 Tsujimura543
 * POOKMARK Airlines の「削除」に対応
 * 
 * 12    06/08/22 11:46 Tsujimura543
 * 不要になった処理を削除
 * 
 * 11    06/08/22 11:43 Tsujimura543
 * DeleteBookmarkDialog と DeleteBookmarkDialog2 を1個のダイアログに
 * まとめた (DeleteBookmarkDialog2 は廃止)
 * 
 * 10    06/07/12 9:33 Tsujimura543
 * livedoorクリップ、ECナビ人気ニュース、ニフティクリップの削除ボタンを追
 * 加
 * 
 * 9     06/06/27 15:24 Tsujimura543
 * Flog の削除に対応
 * 
 * 8     06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 7     06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 6     06/06/01 19:04 Tsujimura543
 * ブックマーク種別を示す enum 値を、enum CUserInfo::bookmarkType に
 * 一本化した
 * 
 * 5     05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 4     05/10/31 21:42 Tsujimura543
 * MM/Memo と BlogPeople Tags の削除に対応
 * 
 * 3     05/10/11 17:01 Tsujimura543
 * 初版のタイムスタンプ表記ミスを修正 (コメントのみの修正。動作に影響なし)
 * 
 * 2     05/10/01 0:00 Tsujimura543
 * ブックマークの取得、登録機能の動作確認完了
 */

#include "bookey.h"
#include "DeleteBookmarkDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteBookmarkDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog ダイアログ


DeleteBookmarkDialog::DeleteBookmarkDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DeleteBookmarkDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(DeleteBookmarkDialog)
	//}}AFX_DATA_INIT

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
    m_tgt_fc2Bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
    m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
    m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_localOPML.LoadString( IDS_TGT_LOCAL_OPML );
}


void DeleteBookmarkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeleteBookmarkDialog)
	DDX_Control(pDX, IDC_COMBO_DELETELIST, m_bookmark);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DeleteBookmarkDialog, CDialog)
	//{{AFX_MSG_MAP(DeleteBookmarkDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_DELETE_INTERACTIVE, OnButtonDeleteInteractive)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL, OnButtonDeleteAll)
	ON_CBN_SELCHANGE(IDC_COMBO_DELETELIST, OnSelchangeComboDeleteList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeleteBookmarkDialog メッセージ ハンドラ

void DeleteBookmarkDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        m_targetBookmark    = CUserInfo::BK_UNKNOWN;
    	m_deleteAll         = false;
    	m_deleteInteractive = false;
    }
}

void DeleteBookmarkDialog::OnButtonDeleteInteractive() 
{
	m_deleteInteractive = true;
    if ( m_targetBookmark != CUserInfo::BK_UNKNOWN )
        OnOK();
}

void DeleteBookmarkDialog::OnButtonDeleteAll() 
{
	m_deleteAll = true;
    if ( m_targetBookmark != CUserInfo::BK_UNKNOWN )
        OnOK();
}

void DeleteBookmarkDialog::OnSelchangeComboDeleteList() 
{
    CString     bookmarkName;
    int         location = m_bookmark.GetCurSel();

	m_bookmark.GetLBText( location, bookmarkName );
    if ( bookmarkName.Compare( m_tgt_hatenaBookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_HATENA;
    else
    if ( bookmarkName.Compare( m_tgt_delicious ) == 0 )
        m_targetBookmark = CUserInfo::BK_DELICIOUS;
    else
    if ( bookmarkName.Compare( m_tgt_mmMemo ) == 0 )
        m_targetBookmark = CUserInfo::BK_MM_MEMO;
    else
    if ( bookmarkName.Compare( m_tgt_drecomRSS ) == 0 )
        m_targetBookmark = CUserInfo::BK_DRECOM_RSS;
    else
    if ( bookmarkName.Compare( m_tgt_flog ) == 0 )
        m_targetBookmark = CUserInfo::BK_FLOG;
    else
    if ( bookmarkName.Compare( m_tgt_livedoorClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_LIVEDOOR_CLIP;
    else
    if ( bookmarkName.Compare( m_tgt_ecNaviClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_ECNAVI_CLIP;
    else
    if ( bookmarkName.Compare( m_tgt_niftyClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_NIFTY_CLIP;
    else
    if ( bookmarkName.Compare( m_tgt_1470net ) == 0 )
        m_targetBookmark = CUserInfo::BK_1470NET;
    else
    if ( bookmarkName.Compare( m_tgt_pookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_POOKMARK;
    else
    if ( bookmarkName.Compare( m_tgt_blueDot ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLUEDOT;
    else
    if ( bookmarkName.Compare( m_tgt_joltMark ) == 0 )
        m_targetBookmark = CUserInfo::BK_JOLTMARK;
    else
    if ( bookmarkName.Compare( m_tgt_blogPet ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLOGPET;
    else
    if ( bookmarkName.Compare( m_tgt_fc2Bookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_FC2BOOKMARK;
    else
    if ( bookmarkName.Compare( m_tgt_yjBookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_YJ_BOOKMARK;
    else
    if ( bookmarkName.Compare( m_tgt_yahooBookmarks ) == 0 )
        m_targetBookmark = CUserInfo::BK_YAHOO_BOOKMARKS;
    else
    if ( bookmarkName.Compare( m_tgt_diigo ) == 0 )
        m_targetBookmark = CUserInfo::BK_DIIGO;
    else
    if ( bookmarkName.Compare( m_tgt_localOPML ) == 0 )
        m_targetBookmark = CUserInfo::BK_LOCAL_OPML;
}

/*
 * EditBookmarkDialog.h  : ソーシャルブックマーク管理プログラム
 *      ブックマーク編集ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  14 Oct 2005
 *
 * $Log: /comm/bookey/EditBookmarkDialog.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 42    08/11/04 12:48 Tsujimura543
 * @nifty Clip 登録者数も表示するようにした
 * 
 * 41    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 40    08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 39    07/10/31 17:13 Tsujimura543
 * tumblr に対応
 * 
 * 38    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 37    07/09/05 2:19 Tsujimura543
 * SetUsers() を導入し、ソースを整理
 * 
 * 36    07/08/28 18:52 Tsujimura543
 * SetStaticEdge() の第2引数の型を bool から BOOL に変更
 * 
 * 35    07/08/28 18:45 Tsujimura543
 * SetStaticEdge() を追加
 * 
 * 34    07/08/27 21:55 Tsujimura543
 * 「はてなスター」に対応
 * 
 * 33    07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 32    07/05/23 16:02 Tsujimura543
 * Timelog 対応
 * 
 * 31    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 30    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 29    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 28    07/03/30 16:24 Tsujimura543
 * FC2BOOKMARK に対応
 * 
 * 27    07/03/01 21:45 Tsujimura543
 * コメントを修正
 * 
 * 26    07/03/01 21:44 Tsujimura543
 * (1) livedoorクリップに登録している人の数を表示するようにした
 * (2) ニフティクリップのアイコンをクリックすると、エントリページをブラウ
 *     ザで表示できるようにした
 * 
 * 25    07/02/05 14:52 Tsujimura543
 * ドリコムRSSとFlogのカテゴリ復元処理を修正
 * 
 * 24    07/02/02 23:56 Tsujimura543
 * 改修部分の動作確認完了
 * 
 * 23    07/02/02 23:40 Tsujimura543
 * 再登録しようとしている場合の一連の処理を修正。ドリコムRSSやFlogのカテゴ
 * リも復元できるようにした
 * 
 * 22    07/01/16 21:03 Tsujimura543
 * IsInner() を追加
 * 
 * 21    07/01/12 23:34 Tsujimura543
 * 英語モード対応
 * 
 * 20    06/12/27 17:37 Tsujimura543
 * ブックマーク投稿ダイアログで右クリックメニューが使えるようにした
 * 
 * 19    06/12/06 18:57 Tsujimura543
 * 「公開状態」の設定に対応
 * 
 * 18    06/09/30 0:55 Tsujimura543
 * ○×ボタン押下時の動作を修正 (キャンセル可能にした)
 * 
 * 17    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 16    06/07/14 20:50 Tsujimura543
 * 1470.netリニューアル版に対応
 * 
 * 15    06/07/11 22:49 Tsujimura543
 * ECナビ人気ニュースのブックマーク登録者数も表示するようにした
 * (ブックマーク登録画面/EditBookmarkDialog)
 * 
 * 14    06/06/30 11:37 Tsujimura543
 * livedoorクリップ、ECナビ人気ニュースのアイコンをクリックしたときも、
 * 各ブックマークのエントリページを(ブラウザ経由で)表示するようにした
 * 
 * 13    06/06/28 15:54 Tsujimura543
 * ブックマーク登録者数を調べて表示する機能を追加
 * 
 * 12    06/06/26 16:27 Tsujimura543
 * OnSetCursor() を追加 (指カーソル表示機能)
 * 
 * 11    06/06/19 13:42 Tsujimura543
 * はてなブックマーク、del.icio.us、MM/Memo のアイコンをクリックしたとき、
 * 各ブックマークのエントリページを(ブラウザ経由で)表示するようにした
 * 
 * 10    06/06/06 15:17 Tsujimura543
 * どのソーシャルブックマークへの登録が有効(もしくは無効)になっているのか
 * アイコンとツールチップを使って表示するようにした
 * 
 * 9     06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 8     06/04/06 22:16 Tsujimura543
 * はてなブックマークの「コレクション」への追加に対応
 * 
 * 7     06/03/29 21:23 Tsujimura543
 * ドリコムRSSの「フォルダ」(カテゴリ)を指定できるようにした
 * 
 * 6     06/03/27 17:16 Tsujimura543
 * OnUpdateEditBmComment() を除く全ての OnUpdateEditBmXXX() を廃止
 * 
 * 5     06/03/24 15:48 Tsujimura543
 * OnUpdateEditBmUrl() を削除 [無限に再帰が発生する不具合があった]
 * 
 * 4     05/12/01 0:02 Tsujimura543
 * タグ候補表示・入力機能を実装
 * 
 * 3     05/10/24 17:37 Tsujimura543
 * はてな投げ銭に対応した
 * 
 * 2     05/10/14 17:02 Tsujimura543
 * ブックマーク編集ダイアログを実装
 */

#if !defined(AFX_EDITBOOKMARKDIALOG_H__3EDC0EC9_0CED_4E9A_B89F_53E3E42275E4__INCLUDED_)
#define AFX_EDITBOOKMARKDIALOG_H__3EDC0EC9_0CED_4E9A_B89F_53E3E42275E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// EditBookmarkDialog ダイアログ

class EditBookmarkDialog : public CDialog
{
// コンストラクション
public:
	EditBookmarkDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

    void    RedrawCounter( const char *comment );
    void    SetTag( int tagID );

    bool    m_enableTipJar; // 当該エントリーのオーナーに対してはてなポイント
                            // 送信可能か否か
    bool    m_useCategory;  // (ドリコムRSS の)カテゴリを使うか否か
    bool    m_enableCollection;     // はてなブックマークの「コレクション」に
                                    // 登録可能か否か
    bool    m_registerCollection;   // はてなブックマークの「コレクション」に
                                    // 登録するか否か
    CString *m_tag[20];
    int     m_evaluation;  // 評価#1 (5段階 + 未評価)
    int     m_rating;      // 評価#2 (3段階)
    int     m_affirmation; // 評価#3 (肯定/否定)
    int     m_public;      // 公開状態 (EVERYONE/FRIENDS/PRIVATE)
    RBparam_t   m_param;   // 登録するか否かの設定を一時的に変更する目的で使用
    HCURSOR m_hCursor;

// ダイアログ データ
	//{{AFX_DATA(EditBookmarkDialog)
	enum { IDD = IDD_EDIT_BOOKMARK_DIALOG };
	CComboBox	m_categoryList2;
	CComboBox	m_categoryList;
	CString	m_counterString;
	CString	m_comment;
	CString	m_tags;
	CString	m_title;
	CString	m_url;
	BOOL	m_sendTipJar;
	CString	m_tag001;
	CString	m_tag002;
	CString	m_tag003;
	CString	m_tag004;
	CString	m_tag005;
	CString	m_tag006;
	CString	m_tag007;
	CString	m_tag008;
	CString	m_tag009;
	CString	m_tag010;
	CString	m_tag011;
	CString	m_tag012;
	CString	m_tag013;
	CString	m_tag014;
	CString	m_tag015;
	CString	m_tag016;
	CString	m_tag017;
	CString	m_tag018;
	CString	m_tag019;
	CString	m_tag020;
	CString	m_category;
	CString	m_category2;
	CString	m_hbUsers;
	CString	m_deliciousUsers;
	CString	m_mmUsers;
	CString	m_ecNaviUsers;
	CString	m_livedoorClipUsers;
	CString	m_diggUsers;
	CString	m_hatenaStarUsers;
	CString	m_niftyClipUsers;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(EditBookmarkDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    DisplayToolTip( bool isTarget, BOOL onOff, TOOLTIPTEXT *tp );
    bool    IsInner( int id, WORD wX, WORD wY );
    void    SetStaticEdge( int idx, BOOL status );
    void    SetUsers( CString &users, int idx, long maxLength = 8 );

    int     GetCatNumberOfDrecom( const char *tag );
    int     GetCatNumberOfDrecom( CString& tags );

    int     GetCatNumberOfFlog( const char *tag );
    int     GetCatNumberOfFlog( CString& tags );

    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_newsing;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_blogPet;
    CString m_tgt_fc2bookmark;
    CString m_tgt_twitter;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_timelog;
    CString m_tgt_digg;
    CString m_tgt_tumblr;
    CString m_tgt_diigo;
    CString m_tgt_hatenaStar;

	// メッセージマップ関数
	//{{AFX_MSG(EditBookmarkDialog)
	afx_msg void OnKillfocusEditBmUrl();
	afx_msg void OnKillfocusEditBmTitle();
	afx_msg void OnKillfocusEditBmComment();
	afx_msg void OnKillfocusEditBmTags();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheckTipjar();
	afx_msg void OnTag001();
	afx_msg void OnTag002();
	afx_msg void OnTag003();
	afx_msg void OnTag004();
	afx_msg void OnTag005();
	afx_msg void OnTag006();
	afx_msg void OnTag007();
	afx_msg void OnTag008();
	afx_msg void OnTag009();
	afx_msg void OnTag010();
	afx_msg void OnTag011();
	afx_msg void OnTag012();
	afx_msg void OnTag013();
	afx_msg void OnTag014();
	afx_msg void OnTag015();
	afx_msg void OnTag016();
	afx_msg void OnTag017();
	afx_msg void OnTag018();
	afx_msg void OnTag019();
	afx_msg void OnTag020();
	afx_msg void OnUpdateEditBmComment();
	afx_msg void OnSelchangeComboCategory();
	virtual void OnOK();
	afx_msg void OnSelchangeComboCategory2();
	virtual BOOL OnInitDialog();
    afx_msg void OnDisplayToolTip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnIconHatenaBookmark();
	afx_msg void OnIconDelicious();
	afx_msg void OnIconMmMemo();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnHbUsers();
	afx_msg void OnDeliciousUsers();
	afx_msg void OnMmUsers();
	afx_msg void OnIconLivedoor();
	afx_msg void OnIconEcnaviClip();
	afx_msg void OnEcnaviUsers();
	afx_msg void OnIcon1470net();
	afx_msg void OnNewsGood();
	afx_msg void OnNewsBad();
	afx_msg void OnRadioEval00();
	afx_msg void OnRadioEval01();
	afx_msg void OnRadioEval02();
	afx_msg void OnRadioEval03();
	afx_msg void OnRadioEval04();
	afx_msg void OnRadioEval05();
	afx_msg void OnIconNewsing();
	afx_msg void OnRadioPublic();
	afx_msg void OnRadioFriends();
	afx_msg void OnRadioPrivate();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnIconNiftyClip();
	afx_msg void OnLivedoorclipUsers();
	afx_msg void OnIconDigg();
	afx_msg void OnDiggUsers();
	afx_msg void OnIconHatenaStar();
	afx_msg void OnHatenaStarUsers();
	afx_msg void OnNiftyclipUsers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    EditBookmarkDialog( EditBookmarkDialog &dlg );
    EditBookmarkDialog  operator = ( EditBookmarkDialog &dlg );
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_EDITBOOKMARKDIALOG_H__3EDC0EC9_0CED_4E9A_B89F_53E3E42275E4__INCLUDED_)

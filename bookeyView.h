/*
 * bookeyView.h  : ソーシャルブックマーク管理プログラム
 *      CBookeyView クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyView.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 36    09/01/19 23:55 Tsujimura543
 * ツールバーの右クリックメニューに「ブックマーク管理ツール起動」と
 * 「設定」を追加 (最小化状態からも起動できるようにした)
 * 
 * 35    07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 34    07/07/09 18:38 Tsujimura543
 * 日本語モードと英語モードを切り替える機能を追加
 * (現時点では、この機能は、デバッグビルド時のみ有効となる)
 * 
 * 33    07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 32    07/03/16 23:03 Tsujimura543
 * SetProxyInfo() の仕様を変更。強制保存モードを用意した
 * 
 * 31    07/03/16 1:03 Tsujimura543
 * proxyサーバ経由でないとインターネットアクセスできないのに、proxyサーバ
 * を使わない設定になっている場合の対策を追加
 * 
 * 30    07/03/14 23:32 Tsujimura543
 * URL キューイング機能を実装
 * 
 * 29    06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 * 
 * 28    06/07/05 18:19 Tsujimura543
 * CUserInfo 導入によるリファクタリング第13段階、終了
 * 
 * 27    06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 26    06/07/04 23:48 Tsujimura543
 * encodeParameter() と decodeParameter() を CBookeyView クラス外へ移動
 * 
 * 25    06/07/04 21:46 Tsujimura543
 * LoadSetting(), SaveSetting(), CheckEncodedPassword() をリファクタリング
 * 
 * 24    06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 23    06/06/28 15:54 Tsujimura543
 * ブックマーク登録者数を調べて表示する機能を追加
 * 
 * 22    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() を実行しても、設定が変更できなくなって
 * しまっていた(エンバグ)のを修正。変更できるようにした
 * 
 * 21    06/06/14 11:44 Tsujimura543
 * CUserInfo 導入によるリファクタリング第5段階、終了
 * 
 * 20    06/06/13 21:11 Tsujimura543
 * ブックマーク登録中でも画面再描画できるようにしてみた
 * 
 * 19    06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 18    06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 17    06/06/06 22:23 Tsujimura543
 * CUserInfo 導入によるリファクタリング第2段階、終了
 * 
 * 16    06/06/06 15:18 Tsujimura543
 * CUserInfo を CBookeyApp 内に移した
 * 
 * 15    06/06/01 20:28 Tsujimura543
 * CBookeyDlg 内のユーザ名、パスワードを CUserInfo を使って管理する
 * ように変更した
 * 
 * 14    06/06/01 19:14 Tsujimura543
 * CUserInfo を bookeyView.h から UserInfo.h に移したのに伴う修正を実施
 * 
 * 13    06/06/01 18:49 Tsujimura543
 * enum bookmarkType の定義を CBookeyView から CUserInfo に移した
 * 
 * 12    06/06/01 17:19 Tsujimura543
 * CUserInfo クラスを導入
 * 
 * 11    06/06/01 15:13 Tsujimura543
 * struct RBparam を RBuser_t を使って定義し直した
 * 
 * 10    06/05/31 21:48 Tsujimura543
 * Flog の「登録」に対応した
 * 
 * 9     06/03/29 18:30 Tsujimura543
 * ドリコムRSSへのブックマーク(Clip)登録に対応した
 * 
 * 8     06/03/13 20:56 Tsujimura543
 * タグ候補の表示を ON/OFF できるようにした
 * 
 * 7     06/03/09 15:16 Tsujimura543
 * CheckEncodedPassword() を追加
 * 
 * 6     05/11/01 16:50 Tsujimura543
 * (1) 少しだけリファクタリング
 * (2) MM/Memo の削除関連処理を作成
 * 
 * 5     05/10/24 14:45 Tsujimura543
 * コンテキストメニュー処理を追加
 * 
 * 4     05/10/21 19:56 Tsujimura543
 * MM/Memo と BlogPeople の同時ブックマーク登録にも対応
 * 
 * 3     05/10/15 0:07 Tsujimura543
 * ユーザ名とパスワードを設定ファイルに保存するようにした
 * 
 * 2     05/10/14 20:38 Tsujimura543
 * ドラッグ・アンド・ドロップ対応作業完了
 * 
 * 1     05/10/14 14:28 Tsujimura543
 * 新規作成 (ドラッグ・アンド・ドロップ機能を組込むため、CFormView を導入)
 */

/////////////////////////////////////////////////////////////////////////////
// CBookeyView 部品

#if !defined(AFX_BOOKEYVIEW_H__60864F83_A9BE_4622_8AED_48C0A5F33DBB__INCLUDED_)
#define AFX_BOOKEYVIEW_H__60864F83_A9BE_4622_8AED_48C0A5F33DBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CBookeyView クラス
class CBookeyView : public CFormView
{
protected:
	CBookeyView();
	DECLARE_DYNCREATE(CBookeyView)

public:
	//{{AFX_DATA(CBookeyView)
	enum { IDD = IDD_BOOKEY_FORM };
	BOOL	m_useTagSuggestion;
	BOOL	m_useUsers;
	//}}AFX_DATA

// アトリビュート
public:
    CBookeyDoc* GetDocument();

    char        m_path[MAX_PATH];   // bookey.exe の存在するディレクトリ名

// オペレーション
public:

// オーバーライド
	//{{AFX_VIRTUAL(CBookeyView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	virtual void OnInitialUpdate(); // 構築後の最初の１度だけ呼び出される
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CBookeyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    COleDropTarget      m_dropTarget;   //  OLE DnD のドロップターゲット
#if 0
    bool                m_useProxy;
#endif
    bool                m_procCreated;
    ProceedingDialog    m_procDialog;
    CWinThread          *m_registerBookmarkThread;
    RBparam_t           m_param;

    void    LoadSetting();  // 設定情報読み込み
    void    SaveSetting();  // 設定情報書き出し
    void    SetProxyInfo( bool saveForcely = false );

    void    PutBookmark( const char *url );

    void    ManagementBookmark();
    void    EditSetting();

private:
    CRITICAL_SECTION    m_cs_bookey;    // スレッド間での排他制御用

#define MAX_WAITING_NUM 64
    CString             m_waitingURLs[MAX_WAITING_NUM]; // 登録待ち URL
    long                m_numOfWaiting;                 // 登録待ち URL 件数
    long                m_waitingHead;                  // 登録待ち URL キュー先頭
    long                m_waitingTail;                  // 登録待ち URL キュー末尾

    void    putBookmark( const char *url );
    long    putWaiting( const char *url );
    CString getWaiting();

    bool    CheckEncodedPassword();
    void    EnableButton( bool enable );

// メッセージマップ関数
protected:
	//{{AFX_MSG(CBookeyView)
	afx_msg void OnButtonTool();
	afx_msg void OnButtonSetting();
	afx_msg void OnButtonFinish();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEditPaste();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCheckTagSuggestion();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckUsers();
	afx_msg void OnButtonProxy();
	afx_msg void OnCheckLanguage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CBookeyView( CBookeyView &obj );
    CBookeyView operator = ( CBookeyView &obj );
};

#ifndef _DEBUG  // bookeyView.cpp ファイルがデバッグ環境の時使用される
inline CBookeyDoc* CBookeyView::GetDocument()
   { return (CBookeyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEYVIEW_H__60864F83_A9BE_4622_8AED_48C0A5F33DBB__INCLUDED_)

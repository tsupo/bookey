/*
 * MainFrm.h  : ソーシャルブックマーク管理プログラム
 *      CMainFrame クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/MainFrm.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/10/22 13:35 Tsujimura543
 * タイトルバーを右クリックしたときに表示されるメニューに、「サポート」、
 * 「コミュニティ」、「バージョン情報」を追加
 * 
 * 4     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 3     05/10/24 21:42 Tsujimura543
 * クリップボードにテキストが入っていないときは、paste を disable
 * にするようにした
 * 
 * 2     05/10/14 20:38 Tsujimura543
 * ドラッグ・アンド・ドロップ対応作業完了
 * 
 * 1     05/10/14 14:28 Tsujimura543
 * 新規作成 (ドラッグ・アンド・ドロップ機能を組込むため、CFormView を導入)
 */

/////////////////////////////////////////////////////////////////////////////
// CMainFrame 部品

#if !defined(AFX_MAINFRM_H__B438C2A6_D364_46DC_AE75_5468DFB03DF4__INCLUDED_)
#define AFX_MAINFRM_H__B438C2A6_D364_46DC_AE75_5468DFB03DF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// アトリビュート
public:

// オペレーション
public:
// オーバーライド
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// メッセージマップ関数
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CMainFrame( CMainFrame &obj );
    CMainFrame  operator = ( CMainFrame &obj );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MAINFRM_H__B438C2A6_D364_46DC_AE75_5468DFB03DF4__INCLUDED_)

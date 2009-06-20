/*
 * bookeyDoc.h  : ソーシャルブックマーク管理プログラム
 *      CBookeyDoc クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyDoc.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     05/10/14 20:38 Tsujimura543
 * ドラッグ・アンド・ドロップ対応作業完了
 * 
 * 1     05/10/14 14:28 Tsujimura543
 * 新規作成 (ドラッグ・アンド・ドロップ機能を組込むため、CFormView を導入)
 */

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc 部品

#if !defined(AFX_BOOKRYDOC_H__BA2570F9_2971_4D74_B442_91DA7CC1465C__INCLUDED_)
#define AFX_BOOKEYDOC_H__BA2570F9_2971_4D74_B442_91DA7CC1465C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBookeyDoc : public CDocument
{
protected:
	CBookeyDoc();
	DECLARE_DYNCREATE(CBookeyDoc)

// アトリビュート
public:

// オペレーション
public:
// オーバーライド
	//{{AFX_VIRTUAL(CBookeyDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CBookeyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// メッセージマップ関数
protected:
	//{{AFX_MSG(CBookeyDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// OLE ディスパッチマップ関数
	//{{AFX_DISPATCH(CBookeyDoc)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
    CBookeyDoc( CBookeyDoc &obj );
    CBookeyDoc  operator = ( CBookeyDoc &obj );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_BOOKEYDOC_H__BA2570F9_2971_4D74_B442_91DA7CC1465C__INCLUDED_)

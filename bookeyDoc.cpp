/*
 * bookeyDoc.cpp : ソーシャルブックマーク管理プログラム
 *      CBookeyDoc クラスの動作の定義
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyDoc.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 1     05/10/14 14:37 Tsujimura543
 * 新規作成 (ドラッグ・アンド・ドロップ機能サポート用)
 */

#include "bookey.h"
#include "bookeyDoc.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookeyDoc.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc

IMPLEMENT_DYNCREATE(CBookeyDoc, CDocument)

BEGIN_MESSAGE_MAP(CBookeyDoc, CDocument)
	//{{AFX_MSG_MAP(CBookeyDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBookeyDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CBookeyDoc)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {950411A3-DEB5-4C17-B899-76FB75292533}
static const IID IID_IBookey =
{ 0x950411a3, 0xdeb5, 0x4c17, { 0xb8, 0x99, 0x76, 0xfb, 0x75, 0x29, 0x25, 0x33 } };

BEGIN_INTERFACE_MAP(CBookeyDoc, CDocument)
	INTERFACE_PART(CBookeyDoc, IID_IBookey, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc クラスの構築/消滅

CBookeyDoc::CBookeyDoc()
{
	EnableAutomation();

	AfxOleLockApp();
}

CBookeyDoc::~CBookeyDoc()
{
	AfxOleUnlockApp();
}

BOOL CBookeyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc シリアライゼーション

void CBookeyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
	}
	else {
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc クラスの診断

#ifdef _DEBUG
void CBookeyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBookeyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc コマンド

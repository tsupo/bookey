/*
 * bookeyDoc.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CBookeyDoc �N���X�̓���̒�`
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyDoc.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 1     05/10/14 14:37 Tsujimura543
 * �V�K�쐬 (�h���b�O�E�A���h�E�h���b�v�@�\�T�|�[�g�p)
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
// CBookeyDoc �N���X�̍\�z/����

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
// CBookeyDoc �V���A���C�[�[�V����

void CBookeyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
	}
	else {
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc �N���X�̐f�f

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
// CBookeyDoc �R�}���h

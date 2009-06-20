/*
 * bookeyDoc.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CBookeyDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyDoc.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     05/10/14 20:38 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�Ή���Ɗ���
 * 
 * 1     05/10/14 14:28 Tsujimura543
 * �V�K�쐬 (�h���b�O�E�A���h�E�h���b�v�@�\��g���ނ��߁ACFormView �𓱓�)
 */

/////////////////////////////////////////////////////////////////////////////
// CBookeyDoc ���i

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

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CBookeyDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CBookeyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���b�Z�[�W�}�b�v�֐�
protected:
	//{{AFX_MSG(CBookeyDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// OLE �f�B�X�p�b�`�}�b�v�֐�
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

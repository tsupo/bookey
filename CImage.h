/*
 * CImage.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CImage �N���X�̒�`
 *          written by H.Tsujimura  4 Apr 2007 / 9 Jul 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/CImage.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/10/10 22:38 Tsujimura543
 * �摜���擾����̂� cookie ���K�v�ȏꍇ(���̂Ƃ���Adigg�̂�)�ɑΉ�
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * �_�~�[�̃R�s�[�R���X�g���N�^�A������Z�q�� private �Ƃ��ē����B
 * �m��Ȃ������Ƀ������m��(�Ɖ�����Y��)����������\����r���B
 * 
 * 2     07/07/10 21:04 Tsujimura543
 * �f�X�g���N�^��ǉ�
 * 
 * 1     07/07/09 17:36 Tsujimura543
 * Chirrup �p�ɍ쐬�����\�[�X���� Bookey �ɕK�v�ȋ@�\�����c�������̂�
 * �p�ӂ���
 */

#if !defined(AFX_CJIMAGE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_)
#define AFX_CJIMAGE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CImage
{
public:
    CImage() {}
    ~CImage();

    HBITMAP LoadImageFile( CString filename );

    HBITMAP LoadBmpFile( CString filename );
	HBITMAP SimpleOpen( CString filename );
    HBITMAP HttpOpen( CString url, CString cookie );

private:
    CImage( CImage &img );
    CImage  operator = ( CImage &img );
};

#endif // !defined(AFX_CJIMAGE_H__A07B8677_638F_45CA_8C84_9324D00DA47B__INCLUDED_)

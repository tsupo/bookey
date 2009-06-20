/*
 * CImage.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CImage �N���X�̒�`
 *          written by H.Tsujimura  23 Feb 2007 / 5 Apr 2007 / 9 Jul 2007
 *
 * $Log: /comm/bookey/CImage.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/10/10 22:38 Tsujimura543
 * �摜���擾����̂� cookie ���K�v�ȏꍇ(���̂Ƃ���Adigg�̂�)�ɑΉ�
 * 
 * 2     07/07/10 21:04 Tsujimura543
 * �f�X�g���N�^��ǉ�
 * 
 * 1     07/07/09 17:36 Tsujimura543
 * Chirrup �p�ɍ쐬�����\�[�X���� Bookey �ɕK�v�ȋ@�\�����c�������̂�
 * �p�ӂ���
 */

/*
 * �ŏ��́A
 *    http://www.dinop.com/vc/read_jpeg_idg.html
 * ���Q�l�ɁAlibjpeg �𗘗p���� jpg �摜���r�b�g�}�b�v�ɕϊ����鏈����
 * �������悤�Ƃ��Ă������A����
 *    http://hp.vector.co.jp/authors/VA007941/program/no2124.html
 * ������ OleLoadPictureFile() ���g�����ƂŁAjpg �ȊO�� gif �ɂ��Ή���
 * ���邱�Ƃ������Blibjpeg ���g���̂͂�߂āAOleLoadPictureFile() ���g
 * �����Ƃɂ����B
 */

#include <afx.h>
#include "CImage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <afxctl.h>
#include <sys/stat.h>

extern "C" {
#include "xmlRPC.h"
}

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/CImage.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImage::~CImage()
{
    CString fileName = "tmp.img";
    unlink( fileName );
}

HBITMAP CImage::LoadImageFile( CString csFileName )
{
    HBITMAP hBmp = LoadBmpFile( csFileName );

    return ( hBmp );
}

HBITMAP CImage::LoadBmpFile( CString csFileName )
{
    // �l�^��: http://hp.vector.co.jp/authors/VA007941/program/no2124.html
    // bmp, jpg, gif �ɂ͑Ή����Ă��邪 png �� tif �ɂ͑Ή����Ă��Ȃ�
	LPDISPATCH	    pDispatch;
	COleVariant	    oleFileName(csFileName);	
	OLE_HANDLE	    holeHandle;
	short		    type;
	CPictureHolder	PictureHolder;
    HBITMAP         hBmp = NULL;

	// �摜�t�@�C�������[�h
	if ( OleLoadPictureFile( oleFileName, &pDispatch ) >= 0 ) {		
		PictureHolder.SetPictureDispatch( (LPPICTUREDISP)pDispatch );	
		if ( PictureHolder.m_pPict != NULL ) {
			PictureHolder.m_pPict->get_Type( &type );
			if ((type == PICTYPE_BITMAP)                                &&
                (PictureHolder.m_pPict->get_Handle( &holeHandle ) >= 0)   ) {
                hBmp = (HBITMAP)holeHandle;
			}
		}
	}

	return ( hBmp );
}

HBITMAP CImage::SimpleOpen( CString filename )
{
    // �w�肳�ꂽ�t�@�C�����̉摜�t�@�C����ǂ݁A�r�b�g�}�b�v�𐶐�����
    return LoadImageFile( filename );
}

HBITMAP CImage::HttpOpen( CString url, CString cookie )
{
    // �w�肳�ꂽ URL �̉摜�t�@�C����ǂ݁A�r�b�g�}�b�v�𐶐�����
    char    *response;
    char    *cookieString;
    size_t  sz  = 65536 * 256;
    HBITMAP ret = NULL;

    response = new char[sz];
    if ( !response )
        return ret;
    cookieString = new char[MAX_COOKIE_LEN + 2];
    if ( !cookieString ) {
        delete [] response;
        return ret;
    }
    strcpy( cookieString, cookie );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookieString );
    if ( *response ) {
        size_t  sz = getBinSize();
        if ( sz > 0 ) {
            CString fileName = "tmp.img";
            FILE    *fp      = fopen( fileName, "wb" );
            if ( fp ) {
                fwrite( response, sz, 1, fp );
                fclose( fp );
                ret = LoadImageFile( fileName );
            }
        }
    }

    delete [] cookieString;
    delete [] response;
    encodeURL( NULL );

    return ret;
}

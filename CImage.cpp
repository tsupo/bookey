/*
 * CImage.cpp : ソーシャルブックマーク管理プログラム
 *      CImage クラスの定義
 *          written by H.Tsujimura  23 Feb 2007 / 5 Apr 2007 / 9 Jul 2007
 *
 * $Log: /comm/bookey/CImage.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/10/10 22:38 Tsujimura543
 * 画像を取得するのに cookie が必要な場合(今のところ、diggのみ)に対応
 * 
 * 2     07/07/10 21:04 Tsujimura543
 * デストラクタを追加
 * 
 * 1     07/07/09 17:36 Tsujimura543
 * Chirrup 用に作成したソースから Bookey に必要な機能だけ残したものを
 * 用意した
 */

/*
 * 最初は、
 *    http://www.dinop.com/vc/read_jpeg_idg.html
 * を参考に、libjpeg を利用して jpg 画像をビットマップに変換する処理を
 * 実装しようとしていたが、結局
 *    http://hp.vector.co.jp/authors/VA007941/program/no2124.html
 * を見て OleLoadPictureFile() を使うことで、jpg 以外に gif にも対応で
 * きることが判明。libjpeg を使うのはやめて、OleLoadPictureFile() を使
 * うことにした。
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
    // ネタ元: http://hp.vector.co.jp/authors/VA007941/program/no2124.html
    // bmp, jpg, gif には対応しているが png や tif には対応していない
	LPDISPATCH	    pDispatch;
	COleVariant	    oleFileName(csFileName);	
	OLE_HANDLE	    holeHandle;
	short		    type;
	CPictureHolder	PictureHolder;
    HBITMAP         hBmp = NULL;

	// 画像ファイルをロード
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
    // 指定されたファイル名の画像ファイルを読み、ビットマップを生成する
    return LoadImageFile( filename );
}

HBITMAP CImage::HttpOpen( CString url, CString cookie )
{
    // 指定された URL の画像ファイルを読み、ビットマップを生成する
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

/*
 * CImage.h  : ソーシャルブックマーク管理プログラム
 *      CImage クラスの定義
 *          written by H.Tsujimura  4 Apr 2007 / 9 Jul 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/CImage.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/10/10 22:38 Tsujimura543
 * 画像を取得するのに cookie が必要な場合(今のところ、diggのみ)に対応
 * 
 * 3     07/09/06 18:08 Tsujimura543
 * ダミーのコピーコンストラクタ、代入演算子を private として導入。
 * 知らないうちにメモリ確保(と解放し忘れ)が発生する可能性を排除。
 * 
 * 2     07/07/10 21:04 Tsujimura543
 * デストラクタを追加
 * 
 * 1     07/07/09 17:36 Tsujimura543
 * Chirrup 用に作成したソースから Bookey に必要な機能だけ残したものを
 * 用意した
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

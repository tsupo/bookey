/*
 * encodeContents.c
 *      JSON 関連ライブラリ (UTF-8 → Unicode 変換処理)
 *          written by H.Tsujimura  5 Feb 2007 / 26 Jul 2008
 *
 * $Log: /comm/bookey/encodeContents.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/07/26 0:43 Tsujimura543
 * editDrecomRSS.c から encodeContents() を分離独立させた
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/encodeContents.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif


/* UTF-8 (xxyyzz) → Unicode(UCS-2BE) (%uXXXX) 変換 */
unsigned long
convUTF8( const unsigned char *code )
{
    unsigned long   a, b, c, d;
    unsigned long   l = 0;

    if ( code[0] >= (unsigned char)0xF0 ) {
        a = code[0] & 0x07;
        b = code[1] & 0x3F;
        c = code[2] & 0x3F;
        d = code[3] & 0x3F;
        l = ((a << 18) | (b << 12) | (c << 6) | d) & 0x00FFFFFF;
    }
    else if ( code[0] >= (unsigned char)0xE0 ) {
        a = code[0] & 0x0F;
        b = code[1] & 0x3F;
        c = code[2] & 0x3F;
        l = ((a << 12) | (b << 6) | c) & 0x0000FFFF;
    }
    else if ( code[0] >= (unsigned char)0xC0 ) {
        a = code[0] & 0x1F;
        b = code[1] & 0x3F;
        l = ((a << 6) | b) & 0x0000FFFF;
    }
    else
        l = code[0] & 0x7F;

    return ( l );
}

char    *
encodeContents( const char *contents )
{
    unsigned char       *p = (unsigned char *)contents;
    unsigned char       *q;
    unsigned long       ucs2;
    Thread  static char buf[MAX_CONTENT_SIZE * 3];

    q = (unsigned char *)buf;
    while ( p && *p ) {
        if ( *p <= 0x7f )
            *q++ = *p++;
        else {
            *q++ = '\\';
            *q++ = 'u';
            ucs2 = convUTF8( p );
            if ( ucs2 >= 0x00010000 ) {
                sprintf( (char *)q, "%06x", ucs2 );
                q += 6;
                p += 4;
            }
            else if ( ucs2 >= 0x00000800 ) {
                sprintf( (char *)q, "%04x", ucs2 );
                q += 4;
                p += 3;
            }
            else if ( ucs2 >= 0x00000080 ) {
                sprintf( (char *)q, "%04x", ucs2 );
                q += 4;
                p += 2;
            }
            else {
                sprintf( (char *)q, "%02x", ucs2 );
                q += 2;
                p += 1;
            }
        }
    }
    *q = NUL;

    return ( buf );
}

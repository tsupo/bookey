/*
 *  getString.c
 *      2つの指定文字列に挟まれた部分の文字列を取得する
 *          written by H.Tsujimura  19 Oct 2005 / 2 Nov 2005
 *
 * $Log: /comm/bookey/getString.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     05/11/02 15:30 Tsujimura543
 * putMMmemo.c から分離、独立させた
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getString.c 1     09/05/14 3:48 tsupo $";
#endif

/*
 *  getStringImplanted()
 *      文字列 src から、startString と endString で挟まれた部分の
 *      文字列を抽出(したものを dst に格納)する
 */
char    *
getStringImplanted(
        char       *dst,
        const char *src,
        const char *startString,
        const char *endString
    )
{
    char    *p, *q;
    int     len = strlen( startString );

    *dst = NUL;
    p = strstr( src, startString );
    if ( p ) {
        p += len;
        if ( strlen( endString ) == 1 )
            q = strchr( p, *endString );
        else
            q = strstr( p, endString );
        if ( q ) {
            strncpy( dst, p, q - p );
            dst[q - p] = NUL;
        }
    }

    return ( dst );
}

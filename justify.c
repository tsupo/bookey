/*
 *  justify.c
 *      Shift_JIS 文字列を指定バイト数以内に丸める処理
 *          written by H.Tsujimura  22 Aug 2006 / 18 Jan 2007
 *
 * $Log: /comm/bookey/justify.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/01/18 15:12 Tsujimura543
 * justify() を Delete1470net.cpp から分離、独立させた
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/justify.c 1     09/05/14 3:48 tsupo $";
#endif

char    *
justify( char *s, size_t len )
{
    char    *p = s;

    if ( s && *s && (strlen( s ) > len) ) {
        BOOL    kanjiFlag = FALSE;
        size_t  i = 0;

        while ( *p ) {
            if ( ++i > len )
                break;
            if ( !kanjiFlag && iskanji1( *p ) )
                kanjiFlag = TRUE;
            else
                kanjiFlag = FALSE;
            *p++;
        }
        if ( kanjiFlag )
            *(p - 1) = NUL;
        else
            *p = NUL;

        strcat( s, getLanguageCode() == 0x0411 ? "……" : "..." );
    }

    return ( s );
}

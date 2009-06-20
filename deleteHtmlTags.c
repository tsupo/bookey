/*
 *  指定された文字列中に含まれる html タグを取り除く
 *      written by H.Tsujimura  6 Oct 2006 / 17 Jan 2007
 *
 * $Log: /comm/bookey/deleteHtmlTags.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/01/17 21:41 Tsujimura543
 * deleteHtmlTags() を getBlueDot.c から分離、独立させた
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/deleteHtmlTags.c 1     09/05/14 3:48 tsupo $";
#endif

char    *
deleteHtmlTags( char *text )
{
    char    *p = text;
    char    *tmp, *q;
    int     innerBlockquote = 0;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* この関数の処理内容               */
    /*   (1) 改行を取り除く             */
    /*   (2) <br /> を取り除く          */
    /*   (3) <p>, <img>, <a> を取り除く */
    /*   (4) <blockquote> を取り除く    */
    /*   (5) </blockquote> を取り除く   */

    while ( *p ) {
        if ( (*p == '\r') || (*p == '\n') ) {
            /* (1) 改行を取り除く */
            p++;
        }
        else if ( !strncmp( p, "<br />", 6 ) ) {
            /* (2) <br /> を取り除く */
            p += 6;
        }
        else if ( !strncmp( p, "<br>", 4 ) ) {
            /* (2') <br> を取り除く */
            p += 4;
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (3a1) <p> を取り除く */
            p += 3;
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (3a2) </p> を取り除く */
            p += 4;
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (3b1) <cite> を取り除く */
            p += 6;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (3b2) </cite> を取り除く */
            p += 7;
        }
        else if ( !strncmp( p, "<a ", 3 ) ) {
            /* (3c1) <a> を取り除く */
            p += 3;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "</a>", 4 ) ) {
            /* (3c2) </a> を取り除く */
            p += 4;
        }
        else if ( !strncmp( p, "<img ", 5 ) ) {
            /* (3c1) <img> を取り除く */
            p += 5;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "<blockquote>", 12 ) ) {
            /* (4a) <blockquote> を取り除く */
            innerBlockquote = 1;
            p += 12;
        }
        else if ( !strncmp( p, "</blockquote>", 13 ) ) {
            /* (4b) </blockquote> を取り除く */
            innerBlockquote = 0;
            p += 13;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    if ( tmp ) {
        strcpy( text, tmp );
        free( tmp );
    }

    return ( text );
}

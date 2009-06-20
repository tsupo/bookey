/*
 *  指定 URL から ASIN を取得する
 *      written by H.Tsujimura  24 May 2006
 *
 * $Log: /comm/bookey/getASIN.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     06/09/11 11:32 Tsujimura543
 * 2006年9月8日、9日に出現した新しいパターンの URL にも対応
 * 
 * 4     06/09/04 22:29 Tsujimura543
 * 新しいパターンの URL に対応
 * 
 * 3     06/05/25 21:37 Tsujimura543
 * /tg/detail/-/ に関して books 以外も対応 (動作確認済み)
 * 
 * 2     06/05/25 21:18 Tsujimura543
 * /tg/detail/-/books/ なページ(詳細解説ページ)にも対応した
 * 
 * 1     06/05/24 17:13 Tsujimura543
 * 新規作成
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getASIN.c 1     09/05/14 3:48 tsupo $";
#endif

/*
 *  getASIN()
 *      URL に含まれる ASIN を取り出す
 *      (amazon, はてな の URL が対象)
 */
char    *
getASIN(
        const char *url,    /* (I) 解析対象 URL */
        char       *asin    /* (O) ASIN 文字列  */
    )
{
    char    *p;
    char    *q;

    asin[0] = NUL;
    p = strstr( url, "/ASIN/" );
    if ( !p )
        p = strstr( url, "/asin/" );    /*「はてな」の場合を含む */
    if ( !p ) {
        p = strstr( url, "/gp/product/" );
        if ( p ) {
            p += 6;
            if ( !strncmp( p + 6, "images/", 7 ) )
                p += 7;
        }
    }
    if ( p )
        p += 6;

    if ( !p && strstr( url, "amazon" ) ) {
        p = strstr( url, "/detail/" );
        if ( p ) {
            /* インスタントストア (このパターンの場合は必ず、直前に */
            /* associate ID が存在する)                             */
            if ( (*(p - 1) >= '0') && (*(p - 1) <= '9') )
                p += 8;
            else
                p = NULL;
        }

        if ( !p ) {
            /* 検索結果 (2006年8月24日ごろから出現し始めた形式) */
            p = strstr( url, "/dp/" );
            if ( p )
                p += 4;
        }
        if ( !p ) {
            /* 
             *  /tg/任意の文字列/-/XXX/ や
             *  /tg/任意の文字列/任意の文字列/-/XXX/ の場合
             */
            p = strstr( url, "/tg/" );
            q = strstr( url, "/-/"  );
            if ( p && q && (p < q) )
                p = q + 3;
            else
                p = NULL;
        }
    }

    if ( p ) {
        if ( !strncmp( p, "list/", 5 ) )
            p += 5;
        q = strchr( p, '/' );
        if ( q ) {
            strncpy( asin, p, q - p );
            asin[q - p] = NUL;
        }
        else if ( strlen( p ) > 10 ) {
            strncpy( asin, p, 10 );
            asin[10] = NUL;
        }
        else
            strcpy( asin, p );
    }

    return ( asin );
}


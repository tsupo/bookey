/*
 *  editDelicious.c
 *      「指定ユーザが del.icio.us で使っているタグの一覧」を取得する
 *          written by H.Tsujimura  26 Jan 2007 / 30 Jan 2007
 *
 * $Log: /comm/bookey/editDelicious.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/01/30 18:47 Tsujimura543
 * コードを整理
 * 
 * 1     07/01/30 18:24 Tsujimura543
 * getTagListOnDelicious() に相当する処理を UserInfo.cpp から分離、
 * 独立させた
 */

#include "myClip.h"
#include "delicious.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editDelicious.c 1     09/05/14 3:48 tsupo $";
#endif


TagList *
getTagListOnDelicious(
        const char *username,
        const char *password,
        int        *numOfTags )
{
    TagList         *p = NULL;
    DELICIOUS_TAGS  *tp;
    long            num = 0;

    *numOfTags = 0;

    num = getNumberOfTagsOnDelicious( username, password );
    tp  = (DELICIOUS_TAGS *)malloc( sizeof ( DELICIOUS_TAGS ) * num );
    if ( tp ) {
        *numOfTags = getListOfTagsOnDelicious( username, password, &num, tp );
        if ( *numOfTags > 0 ) {
            p = (TagList *)malloc( sizeof (TagList) * *numOfTags );
            if ( p ) {
                int             i;
                TagList         *q = p;
                DELICIOUS_TAGS  *r = tp;

                for ( i = 0; i < *numOfTags; i++, q++, r++ )
                    strcpy( q->tag, r->tag ); 
            }
        }
        free( tp );
    }

    return ( p );
}

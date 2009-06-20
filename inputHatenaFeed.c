/*
 *  inputHatenaFeed.c
 *      はてなブックマークの RSS/Atom フィード形式のXMLファイルから
 *      ブックマークを取り込む
 *          written by H.Tsujimura  10 Nov 2006
 *
 * $Log: /comm/bookey/inputHatenaFeed.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     06/12/06 18:56 Tsujimura543
 * 「公開状態」の値を暫定値から myClip.h で定義したものに移行した
 * 
 * 3     06/11/27 16:33 Tsujimura543
 * publication や asin フラグの値を明示的に初期化するようにしてみた
 * 
 * 2     06/11/15 20:55 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     06/11/10 19:35 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputHatenaFeed.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
inputHatenaFeed( int *numOfClips, FILE *fp )
{
    MyClip          *mp = NULL, *pp;
    long            num;
    long            numOfPosts = 0;
    HATENA_BOOKMARK *posts     = NULL, *hp;
    int             i;

    num = getPostsFromHatenaFeed( fp, &posts, &numOfPosts );
    if ( posts ) {
        if ( numOfPosts > 0 ) {
            mp = (MyClip *)malloc( sizeof( MyClip ) * numOfPosts );
            if ( mp ) {
                *numOfClips = numOfPosts;
                pp = &(mp[0]);
                hp = &(posts[0]);
                for ( i = 0; i < numOfPosts; i++, pp++, hp++ ) {
                    /* HATENA_BOOKMARK → MyClip 変換 */
                    strcpy( pp->comment, hp->summary );
                    strcpy( pp->tags,    hp->tags );
                    strcpy( pp->title,   hp->title );
                    strcpy( pp->url,     hp->href );
                    pp->yyyy = hp->yyyy;
                    pp->mm   = hp->mm;
                    pp->dd   = hp->dd;
                    pp->HH   = hp->HH;
                    pp->MM   = hp->MM;
                    pp->SS   = hp->SS;
                    pp->asin        = FALSE;
                    pp->publication = PUB_EVERYONE;
                    pp->evaluation  = 0;
                    pp->rating      = 0;
                    pp->affirmation = 0;
                }
            }
        }
        freePostsFromHatenaFeed( posts );
    }

    return ( mp );
}

/*
 * clip saver <<getLocalOpml>>
 *
 *      ローカルOPMLファイル → OPML 変換出力プログラム
 *          written by H.Tsujimura  26 Oct 2006
 *
 * $Log: /comm/bookey/getLocalOpml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     06/10/26 21:31 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getLocalOpml.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20

MyClip  *
getLocalOpml(
        const char *filename,   /* (I) ローカルOPMLファイル           */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    )
{
    MyClip  *mp = NULL;
    FILE    *fp = fopen( filename, "r" );

    if ( fp ) {
        mp = inputOPML( numOfClips, fp );
        fclose( fp );
    }
    else
        *numOfClips = 0;

    return ( mp );
}

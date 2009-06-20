/*
 * clip loader <<putLocalOpml>>
 *
 *      OPML → ローカルOPMLファイル 登録プログラム
 *          written by H.Tsujimura  26 Oct 2006
 *
 * History:
 * $Log: /comm/bookey/putLocalOpml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     07/11/12 21:55 Tsujimura543
 * adjustStringLength() を myClip.c へ移管
 * 
 * 4     07/03/26 23:16 Tsujimura543
 * ローカルOPML登録時にメモリ破壊が発生する可能性のある箇所を発見、
 * 修正を実施
 * 
 * 3     07/01/22 20:13 Tsujimura543
 * 英語モード対応
 * 
 * 2     06/11/14 15:54 Tsujimura543
 * chcode() の実体を myClip.c へ移動
 * 
 * 1     06/10/26 21:31 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putLocalOpml.c 1     09/05/14 3:48 tsupo $";
#endif

void
putLocalOpml(
        const char   *filename,
        const MyClip *mp,
        int          numOfClips
    )
{
    FILE    *fp;
    int     num = 0;
    MyClip  *pp = getLocalOpml( filename, &num );
    MyClip  *qq = (MyClip *)malloc( sizeof ( MyClip ) * (numOfClips + num) );

    if ( qq ) {
        char    *p;
        int     i, j;
        size_t  len;
        char    temp[MAX_DESCRIPTION_LEN];

        for ( i = 0; i < numOfClips; i++ ) {
            memcpy( &(qq[i]), &(mp[i]), sizeof ( MyClip ) );

            p = any2utf( chcode( (char *)(mp[i].title) ) );
            if ( p ) {
                len = strlen( p );
                if ( len < MAX_DESCRIPTION_LEN - 1 )
                    strcpy( qq[i].title, p );
                else {  /* @@ */
                    p = any2sjis( mp[i].title );
                    adjustStringLength( p, (MAX_DESCRIPTION_LEN * 2 / 3) );
                    strcpy( temp, p );
                    p = any2utf( temp );
                    strncpy( qq[i].title, p, MAX_DESCRIPTION_LEN - 2 );
                    qq[i].title[MAX_DESCRIPTION_LEN - 1] = NUL;
                }       /* @@ */
            }

            p = any2utf( chcode( (char *)(mp[i].comment) ) );
            if ( p ) {
                len = strlen( p );
                if ( len < MAX_DESCRIPTION_LEN - 1 )
                    strcpy( qq[i].comment, p );
                else {  /* @@ */
                    p = any2sjis( mp[i].comment );
                    adjustStringLength( p, (MAX_DESCRIPTION_LEN * 2 / 3) );
                    strcpy( temp, p );
                    p = any2utf( temp );
                    strncpy( qq[i].comment, p, MAX_DESCRIPTION_LEN - 2 );
                    qq[i].comment[MAX_DESCRIPTION_LEN - 1] = NUL;
                }       /* @@ */
            }

            p = any2utf( chcode( (char *)(mp[i].tags) ) );
            if ( p ) {
                len = strlen( p );
                if ( len < MAX_DESCRIPTION_LEN - 1 )
                    strcpy( qq[i].tags, p );
                else {  /* @@ */
                    p = any2sjis( mp[i].tags );
                    adjustStringLength( p, (MAX_DESCRIPTION_LEN * 2 / 3) );
                    strcpy( temp, p );
                    p = any2utf( temp );
                    strncpy( qq[i].tags, p, MAX_DESCRIPTION_LEN - 2 );
                    qq[i].tags[MAX_DESCRIPTION_LEN - 1] = NUL;
                }       /* @@ */
            }
        }

        if ( pp ) {
            for ( j = 0; i < numOfClips + num; i++, j++ )
                memcpy( &(qq[i]), &(pp[j]), sizeof ( MyClip ) );

            free( pp );
        }

        pp = qq;
    }
    else {
        if ( pp ) {
            free( pp );
            num = 0;
        }
        pp = (MyClip *)mp;
    }

    num = numOfClips + num;
    fp = fopen( filename, "w" );
    if ( fp ) {
        int     changeCode = UTF8;
        char    title[BUFSIZ];

        strcpy( title,
                getLanguageCode() == 0x0411
                 ? sjis2utf("ローカルOPMLファイル")
                 : "Local OPML" );
        outputOPML( pp, num,
                    title, changeCode, fp );
        fclose( fp );
    }

    if ( qq )
        free( qq );
}

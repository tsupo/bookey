/*
 *  outputOpera6Adr.c
 *      ブックマークを opera6.adr 形式のテキストファイルとして出力する
 *          written by H.Tsujimura  10 Nov 2006
 *
 * $Log: /comm/bookey/outputOpera6Adr.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     06/11/16 13:55 Tsujimura543
 * タグの総バイト数(タグとタグを区切る文字を含む)が512バイトより大きいと、
 * クラッシュする不具合に対処
 * 
 * 2     06/11/14 19:16 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     06/11/10 19:39 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/outputOpera6Adr.c 1     09/05/14 3:48 tsupo $";
#endif

char    *regularize( char *p );


void
outputOpera6Adr(
        const MyClip *mp,
        int          numOfClips,
        const char   *title,
        int          codeChange,
        FILE         *fp
    )
{
    int     i;
    char    buf[BUFSIZ];
    char    tag[4096];
    char    comment[4096];
    char    *p;
    long    id = 1001;  /* 暫定 */

    fputs( "Opera Hotlist version 2.0\n"
           "Options: encoding = utf8, version=3\n\n",
           fp );

    switch ( codeChange ) {
    case SJIS2UTF:
        p = sjis2utf( title );
        break;

    case EUC2UTF:
        p = euc2utf( title );
        break;

    case UTF8:
    default:
        p = NULL;
        break;
    }
    fprintf( fp, "#FOLDER\n\tID=%d\n\tNAME=%s\n\n",
             id++, p ? p : title );

    for ( i = 0; i < numOfClips; i++ ) {
        switch ( codeChange ) {
        case SJIS2UTF:
            p = sjis2utf( mp[i].title );
            strcpy( buf, p ? p : mp[i].title );
            p = sjis2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = sjis2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case EUC2UTF:
            p = euc2utf( mp[i].title );
            strcpy( buf, p ? p : mp[i].title );
            p = euc2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = euc2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case UTF8:
        default:
            strcpy( buf, mp[i].title );
            strcpy( tag, mp[i].tags );
            strcpy( comment, mp[i].comment );
            break;
        }

        regularize( buf );
        regularize( tag );
        regularize( comment );

        fprintf( fp, "#URL\n\tID=%d\n\tNAME=%s\n\tURL=%s\n",
                 id++, buf, mp[i].url );
        if ( comment[0] ) {
            if ( tag[0] )
                fprintf( fp, "\tDESCRIPTION=%s (tags: %s)\n", comment, tag );
            else
                fprintf( fp, "\tDESCRIPTION=%s\n", comment );
        }
        fputs( "\n", fp );
    }

    fputs( "-\n\n", fp );
}

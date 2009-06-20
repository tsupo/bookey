/*
 *  inputBookmarkHtml.c
 *      NETSCAPE-Bookmark-file-1 形式の htmlファイルからブックマークを取り込む
 *          written by H.Tsujimura  10 Nov 2006
 *
 * $Log: /comm/bookey/inputBookmarkHtml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/12/02 19:34 Tsujimura543
 * バッファオーバーフローが発生する可能性のある箇所の対処
 * 
 * 4     06/11/14 15:45 Tsujimura543
 * unescapeURL() の実体を myClip.c へ移動
 * 
 * 3     06/11/14 15:29 Tsujimura543
 * 日時情報の取り扱い方法を修正 (ローカル時間で保持する)
 * 
 * 2     06/11/13 22:25 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     06/11/10 19:35 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputBookmarkHtml.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
inputBookmarkHtml( int *numOfClips, FILE *fp )
{
    MyClip  *mp = NULL;
    MyClip  *newClip_p;
    char    *p, *q, *r;
    char    buf[MAX_CONTENT_SIZE];
    BOOL    found = FALSE;
    char    tags[BUFSIZ * 2];
    char    tmp[65536];
    char    date[16];
    int     num = 1000; /* 暫定 */
    int     cnt = 0, block = 1;

    *numOfClips = 0;
    while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
        while ( isWhiteSpace(*p) )
            p++;
        if ( !strncmp( p, "<!DOCTYPE ", 10 ) ) {
            if ( strstr( p + 10, "NETSCAPE-Bookmark-file-1" ) )
                found = TRUE;
            break;
        }
        if ( !strncmpi( p, "</body>", 7 ) || !strncmpi( p, "</html>", 7 ) )
            break;
    }

    if ( found ) {
        int len;
        int tmpSz = BUFSIZ * 2 - 1;

        while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
          next:
            while ( isWhiteSpace(*p) )
                p++;

            if ( !strncmpi( p, "<DT><H3 ", 8 ) ) {
                p += 8;

                tags[0] = NUL;
                q = strstr( p, "\">" );
                if ( q ) {
                    p = q + 2;
                    while ( isWhiteSpace(*p) )
                        p++;
                    q = strstr( p, "</" );
                    if ( q && !strncmpi( q + 2, "H3>", 3 ) ) {
                        while ( isWhiteSpace(*(q - 1)) )
                            q--;
                        len = min( tmpSz, q - p );
                        strncpy( tags, p, len );
                        tags[len] = NUL;
                    }
                }
            }
            else if ( !strncmpi( p, "<DT><A ", 7 ) ) {
                time_t  t = 0;

                newClip_p = allocateMyClipIfNecessary(&mp, num, &block, cnt);
                if ( !newClip_p )
                    break;
                mp = newClip_p;

                p += 7;

                // href
                q = strstr( p, "HREF=\"" );
                if ( !q )
                    q = strstr( p, "href=\"" );
                if ( q ) {
                    q += 6;
                    r = strchr( q, '"' );
                    if ( r ) {
                        len = min( tmpSz, r - q );
                        strncpy( tmp, q, len );
                        tmp[len] = NUL;
                        strcpy( mp[cnt].url, unescapeURL( tmp ) );
                    }
                }

                // add_date
                q = strstr( p, "ADD_DATE=\"" );
                if ( !q )
                    q = strstr( p, "add_date=\"" );
                if ( q ) {
                    q += 10;
                    r = strchr( q, '"' );
                    if ( r ) {
                        len = min( tmpSz, r - q );
                        strncpy( date, q, tmpSz );
                        date[tmpSz] = NUL;
                        t = atol( date );
                    }
                }
                else
                    t = time( NULL );
                if ( t > 0 ) {
                    struct tm   *tt = localtime( &t );

                    mp[cnt].yyyy = tt->tm_year + 1900;
                    mp[cnt].mm   = tt->tm_mon  + 1;
                    mp[cnt].dd   = tt->tm_mday;
                    mp[cnt].HH   = tt->tm_hour;
                    mp[cnt].MM   = tt->tm_min;
                    mp[cnt].SS   = tt->tm_sec;
                }

                // tags (del.icio.us, pookmark, はてなブックマーク)
                mp[cnt].tags[0] = NUL;
                q = strstr( p, "TAGS=\"" );
                if ( !q )
                    q = strstr( p, "tags=\"" );
                if ( q ) {
                    q += 6;
                    r = strchr( q, '"' );
                    if ( r ) {
                        len = min( tmpSz, r - q );
                        strncpy( tmp, q, len );
                        tmp[len] = NUL;

                        r = tmp;
                        while ( *r ) {
                            if ( *r == ',' )
                                *r = ' ';
                            r++;
                        }

                        r = any2utf( tmp );
                        strcpy( mp[cnt].tags, r ? r : tmp );
                    }
                }

                // title
                q = strstr( p, "\">" );
                if ( q ) {
                    p = q + 2;
                    while ( isWhiteSpace(*p) )
                        p++;
                    q = strstr( p, "</" );
                    if ( q && !strncmpi( q + 2, "A>", 2 ) ) {
                        while ( isWhiteSpace(*(q - 1)) )
                            q--;
                        len = min( tmpSz, q - p );
                        strncpy( tmp, p, tmpSz );
                        tmp[tmpSz] = NUL;
                        r = any2utf( tmp );
                        strcpy( mp[cnt].title, r ? r : tmp );
                    }

                    if ( (!mp[cnt].tags[0]) && tags[0] ) {
                        r = any2utf( tags );
                        strcpy( mp[cnt].tags, r ? r : tags );
                    }

                    cnt++;
                    if ((p = fgets(buf, MAX_CONTENT_SIZE - 1, fp)) != NULL) {
                        while ( isWhiteSpace(*p) )
                            p++;
                        if ( !strncmpi( p, "<DD>", 4 ) ) {
                            p += 4;
                            q = strstr( p, "</DD>" );
                            if ( !q )
                                q = strstr( p, "</dd>" );
                            if ( !q )
                                q = strchr( p, '\r' );
                            if ( !q )
                                q = strchr( p, '\n' );

                            if ( q ) {
                                len = min( tmpSz, q - p );
                                strncpy( tmp, p, len );
                                tmp[len] = NUL;
                                r = any2utf( tmp );
                                strcpy( mp[cnt - 1].comment, r ? r : tmp );
                            }
                        }
                        else
                            goto next;
                    }
                    else
                        break;
                }
            }
        }
    }
    *numOfClips = cnt;

    return ( mp );
}

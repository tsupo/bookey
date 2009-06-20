/*
 *  inputLivedoorFeed.c
 *      livedoor Clip の RSS フィード形式のXMLファイルからブックマークを
 *      取り込む
 *          written by H.Tsujimura  6 Dec 2006
 *
 * $Log: /comm/bookey/inputLivedoorFeed.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     06/12/07 15:57 Tsujimura543
 * getDateTimeFromDateString() を inputLivedoorFeed.c から
 * myClip.c へ移す
 * 
 * 1     06/12/07 15:13 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputLivedoorFeed.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
inputLivedoorFeed( int *numOfClips, FILE *fp )
{
    MyClip  *mp = NULL;
    MyClip  *newClip_p;
    long    numOfPosts = 0;
    long    total      = 0;
    char    *buf, *temp;
    char    *p, *q, *pp, *qq;
    int     num = 1000; /* 暫定 */
    int     block = 1;
    int     len;

    buf = (char *)malloc( MAX_CONTENT_SIZE * 16 );
    if ( !buf )
        return ( mp );
    temp = (char *)malloc( MAX_CONTENT_SIZE * 16 );
    if ( !temp ) {
        free( buf );
        return ( mp );
    }

    while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
        if ( total == 0 ) {
            // total
            q = strstr( p, "<opensearch:totalResults>" );
            if ( q ) {
                q += 25;
                total = atol( q );
                p = q + 1;
            }

            continue;
        }

        while ( isWhiteSpace(*p) )
            p++;

        // item
        if ( !strncmp( p, "<item>", 6 ) ) {
            newClip_p = allocateMyClipIfNecessary( &mp, num, &block,
                                                   numOfPosts );
            if ( !newClip_p )
                break;
            mp = newClip_p;

            continue;
        }

        //  -- title                  題名
        if ( !strncmp( p, "<title>", 7 ) ) {
            p += 7;
            q = strstr( p, "</title>" );
            while ( !q ) {
                len = strlen( buf );
                qq = buf + len;
                pp = fgets( qq,
                        min(MAX_CONTENT_SIZE - 1, MAX_CONTENT_SIZE * 1 - len),
                            fp );
                if ( !pp || !(*pp) )
                    break;
                if ( len + strlen( pp ) >= MAX_CONTENT_SIZE * 16 )
                    break;
                q = strstr( p, "</title>" );
            }
            if ( q ) {
                while ( isWhiteSpace(*p) )
                    p++;
                strncpy( temp, p, q - p );
                temp[q - p] = NUL;
                p = q + 8;
                q = any2utf( decodeURL( temp ) );
                strcpy( mp[numOfPosts].title, q ? q : temp );

                while (((q = strchr(mp[numOfPosts].title, '\r')) != NULL) ||
                       ((q = strchr(mp[numOfPosts].title, '\n')) != NULL)   )
                    strcpy( q, q + 1 ); /* 改行を取り除く */
            }

            continue;
        }

        //  -- link                   URL
        if ( !strncmp( p, "<link>", 6 ) ) {
            p += 6;
            q = strstr( p, "</link>" );
            if ( q ) {
                strncpy( mp[numOfPosts].url, p, q - p );
                mp[numOfPosts].url[q - p] = NUL;
                p = q + 7;
            }

            continue;
        }

        //  -- description            コメント
        if ( !strncmp( p, "<description>", 13 ) ) {
            p += 13;
            q = strstr( p, "</description>" );
            while ( !q ) {
                len = strlen( buf );
                qq = buf + len;
                pp = fgets( qq,
                        min(MAX_CONTENT_SIZE - 1, MAX_CONTENT_SIZE * 1 - len),
                            fp );
                if ( !pp || !(*pp) )
                    break;
                if ( len + strlen( pp ) >= MAX_CONTENT_SIZE * 16 )
                    break;
                q = strstr( p, "</description>" );
            }
            if ( q ) {
                strncpy( temp, p, q - p );
                temp[q - p] = NUL;
                p = q + 14;
                q = any2utf(temp);
                if ( q )
                    strcpy( mp[numOfPosts].comment, q );

                while (((q = strchr(mp[numOfPosts].comment, '\r')) != NULL)||
                       ((q = strchr(mp[numOfPosts].comment, '\n')) != NULL)  )
                    strcpy( q, q + 1 ); /* 改行を取り除く */
            }

            continue;
        }

        //  -- pubDate (RFC 822形式)  登録日時
        if ( !strncmp( p, "<pubDate>", 9 ) ) {
            p += 9;
            getDateTimeFromDateString( p,
                                       &(mp[numOfPosts].yyyy),
                                       &(mp[numOfPosts].mm),
                                       &(mp[numOfPosts].dd),
                                       &(mp[numOfPosts].HH),
                                       &(mp[numOfPosts].MM),
                                       &(mp[numOfPosts].SS) );
            q = strstr( p, "</pubDate>" );
            if ( q )
                p = q + 10;

            continue;
        }

        //  -- author                 登録者
        if ( !strncmp( p, "<author>", 8 ) ) {
            p += 13;
            q = strstr( p, "</author>" );
            if ( q )
                p = q + 9;

            continue;
        }

        //  -- dc:subject             タグ (複数)
        if ( !strncmp( p, "<dc:subject>", 12 ) ) {
            p += 12;
            q = strstr( p, "</dc:subject>" );
            if ( q ) {
                if ( !strncmp( p, "system:private", 14 ) ) {
                    mp[numOfPosts].publication = PUB_PRIVATE;
                }
                else {
                    int len = mp[numOfPosts].tags[0]
                                    ? strlen(mp[numOfPosts].tags)
                                    : 0;
                    if ( len >= 1 ) {
                        strcat( mp[numOfPosts].tags, " " );
                        len++;
                    }
                    strncat( mp[numOfPosts].tags, p, q - p );
                    mp[numOfPosts].tags[len + (q - p)] = NUL;
                }
                p = q + 13;
            }

            continue;
        }

        //  -- rvw:rating             評価
        if ( !strncmp( p, "<rvw:rating>", 12 ) ) {
            p += 12;
            q = strstr( p, "</rvw:rating>" );
            if ( q ) {
                long    rating = atol( p );
                if ( rating > 0 ) {
                    // 100段階評価 → 5段階評価
                    mp[numOfPosts].evaluation = rating / 20;
                }

                p = q + 13;
            }

            continue;
        }

        if ( !strncmp( p, "</item>", 7 ) ) {
            numOfPosts++;
            if ( numOfPosts >= total )
                break;

            p += 7;
        }
    }

    *numOfClips = numOfPosts;

    free( temp );
    free( buf );

    return ( mp );
}

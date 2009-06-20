/*
 * clip saver <<getYJbookmark>>
 *
 *      Yahoo! ブックマーク → OPML 変換出力プログラム
 *          written by H.Tsujimura  20 Apr 2007
 *
 * $Log: /comm/bookey/getYJbookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     09/01/08 13:46 Tsujimura543
 * _getYJbookmark() の「コメント抽出処理」部分を修正
 * 
 * 5     08/12/02 19:33 Tsujimura543
 * コードを整理
 * 
 * 4     07/04/20 20:30 Tsujimura543
 * getYJbookmark.c へ compareMyClip() を移管
 * 
 * 3     07/04/20 19:24 Tsujimura543
 * リファクタリング
 * 
 * 2     07/04/20 19:02 Tsujimura543
 * エラーメッセージの文言を修正
 * 
 * 1     07/04/20 18:55 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getYJbookmark.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
getYBookmarksFromHtml(
        const char *endPointForExport,/* (I) エクスポート URI               */
        char       *cookie,           /* (I/O) クッキー                     */
        int        total,             /* (I) 当該ユーザのブックマークの総数 */
        int        *numOfClips        /* (O) 取得したブックマークの数       */
    );


MyClip  *
getYJbookmarkFromHtml(
        char *cookie,       /* (I/O) クッキー                     */
        int  total,         /* (I) 当該ユーザのブックマークの総数 */
        int  *numOfClips    /* (O) 取得したブックマークの数       */
    )
{
    return ( getYBookmarksFromHtml(
               "http://bookmarks.yahoo.co.jp/settings/exportybm?expformat=ie",
               cookie,
               total,
               numOfClips ) );
}

int
_getYJbookmark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    int     page = 1;
    int     yy, mm, dd;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    sprintf( target, "http://bookmarks.yahoo.co.jp/%s",
             cookie ? "my" : userName );
    strcpy( url, target );
    do {
        setUpReceiveBuffer( response, sz );
        setTargetURL( url );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !(*response) )
            break;

        if ( *total == 0 ) {
            // 全部で何件あるか、前もって調べておく
            p = strstr( response, sjis2utf("</strong>件 ]</h6>") );
            if ( p ) {
                while ( *--p && ((*p >= '0') && (*p <= '9')) )
                    if ( p <= response )
                        break;
                if ( *++p ) {
                    if ( *p == '0' )
                        p++;
                    *total = atol( p );
                }
            }
        }

        // ブックマークを抜き出す
        p = strstr( response, "<div id=\"visiblebms\">" );
        if ( !p )
            break;
        p += 21;

        do {
            if ( mp ) {
                MyClip  *np;
                np = allocateMyClipIfNecessary( mp, unit, &cnt, num );
                if ( !np )
                    break;
                *mp = np;
            }
            if ( mpEx ) {
                MyClipEx    *np;
                np = allocateMyClipExIfNecessary( mpEx, unit, &cnt, num );
                if ( !np )
                    break;
                *mpEx = np;
            }

            q = strstr( p, "<div class=\"saveitem\"" );
            s = strstr( p, "<div class=\"clr\"></div>" );
            if ( !s )
                s = strstr( p, "<div class=\"selectarea\">" );
            if ( !q || !s )
                break;
            p = q + 21;

            // ID
            q = strstr( p, " id=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 5;
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            if ( !strncmp( p, "fakenode", 8 ) )
                break;
            if ( mpEx ) {
                strncpy( (*mpEx)[num].entryID, p, q - p );
                (*mpEx)[num].entryID[q - p] = NUL;
            }
            p = q + 2;

            // URL
            q = strstr( p, "<h4 class=\"title\"><a href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 27;
            if ( !strncmp( p, "http://srd.yahoo.co.jp/BMK/", 27 ) ) {
                q = strstr( p, "/**" );
                if ( !q || (q > s) )
                    break;
                p = q + 3;
            }
            q = strstr( p, "\" " );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "%3A" ) ) != NULL ) {
                *r = ':';
                strcpy( r + 1, r + 3 );
            }
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );
            p = q + 2;

            // タイトル
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( !r )
                utf2sjisEx( tmp );
            else
                strcpy( tmp, r );
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );
            p = q + 4;

            // コメント
            q = strstr( p, "<div class=\"desc\">" );
            if ( q && (q < s) ) {
                // コメントが存在する場合
                p = q + 18;

                r = strstr( p, sjis2utf("コメント:</span>") );
                if ( r && (r < s) ) {
                    p = strstr( r, ":</span>" ) + 8;
                    while ( (*p == ' ') || (*p == '\t') )
                        p++;
                }

                q = strstr( p, "</div>" );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                r = utf2sjis( tmp );
                if ( !r )
                    utf2sjisEx( tmp );
                else
                    strcpy( tmp, r );
                if ( mp )
                    strcpy( (*mp)[num].comment, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].comment, tmp );
                p = q + 6;
            }

            // タグ
            q = strstr( p, "<div class=\"tags\">" );
            if ( q && (q < s) ) {
                // タグが存在する場合
                int len;

                p = q + 18;

                tmp[0] = NUL;
                p = strchr( q, '>' ) + 1;
                do {
                    q = strstr( p, "<li><a " );
                    if ( !q || (q > s) )
                        break;
                    q += 7;
                    p = strchr( q, '>' );
                    if ( !p )
                        break;
                    p++;
                    q = strstr( p, "</a>" );
                    if ( !q )
                        break;

                    if ( tmp[0] == NUL )
                        len = 0;
                    else {
                        strcat( tmp, " " );
                        len = strlen( tmp );
                    }
                    strncat( tmp, p, q - p );
                    tmp[len + (q - p)] = NUL;

                    p = q + 4;
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( !r )
                        utf2sjisEx( tmp );
                    else
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // 年月日 (時分秒は取得できない)
            q = strstr( p, "<span class=\"savedate\">" );
            if ( !q || (q > s) )
                break;
            p = q + 23;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            yy = atol( p );

            while ( (*p >= '0') && (*p <= '9') )
                p++;
            while ( (*p < '0') || (*p > '9') )
                p++;
            mm = atol( p );

            while ( (*p >= '0') && (*p <= '9') )
                p++;
            while ( (*p < '0') || (*p > '9') )
                p++;
            dd = atol( p );

            if ( mp ) {
                (*mp)[num].yyyy = yy;
                (*mp)[num].mm   = mm;
                (*mp)[num].dd   = dd;
                (*mp)[num].HH   = 0;
                (*mp)[num].MM   = 0;
                (*mp)[num].SS   = 0;
            }

            // 公開・非公開
            q = strstr( p, "<em class=\"me\">" );
            if ( q && (q < s) )
                if ( mp )
                    (*mp)[num].publication = PUB_PRIVATE;

            p = strchr( s, '>' );
            num++;
            if ( (*total > 0) && (num >= *total) ) {
                cont = FALSE;
                break;
            }
        } while ( p && *p );

        if ( cont ) {
            // 次へ
            cont = FALSE;
            if ( strstr( response, sjis2utf("class=\"next\">次へ") ) ) {
                page++;
                sprintf( url,
                         "%s?orderby=ctime&b=%d&sort=DESC",
                         target, page );
                cont = TRUE;
                Sleep( 1000 );
            }
        }
    } while ( cont );

    return ( num );
}


MyClip  *
getYJbookmark(
        const char *userName,   /* (I) Yahoo! Japan ID                */
        const char *password,   /* (I) パスワード                     */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 取得したブックマークの数       */
    )
{
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    int     num  = 0;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0]   = NUL;
    response[0] = NUL;

    fd = fileno( stderr );
    if ( password && *password ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( !cookie ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "メモリの確保に失敗しました\n"
                        : "memory exhausted.\n",
                       stderr );
            free( response );
            return ( mp );
        }
        memset( cookie, 0x00, MAX_COOKIE_LEN );

        if ( !loginYahooJapan( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "Yahoo! Japan への login に失敗しました\n"
                        : "Yahoo! Japan: login failed.\n",
                       stderr);
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // ブックマークを取得
    num = _getYJbookmark( userName, cookie, &mp, NULL, response, sz, total );
    if ( (num > 0) && cookie ) {
        // タイムスタンプを取得、上書き
        int     num2 = 0;
        MyClip  *mp2 = getYJbookmarkFromHtml( cookie, num, &num2 );

        if ( mp2 ) {
            if ( num2 > 0 ) {
                int i, j, k, l;

                for ( i = 0; i < num; i++ ) {
                    for ( j = 0; j < num2; j++ ) {
                        l = (i + j) % num2;
                        k = (num2 - l) - 1;
                        if ( !strcmp( mp[i].url, mp2[k].url ) ) {
                            mp[i].yyyy = mp2[k].yyyy;
                            mp[i].mm   = mp2[k].mm;
                            mp[i].dd   = mp2[k].dd;
                            mp[i].HH   = mp2[k].HH;
                            mp[i].MM   = mp2[k].MM;
                            mp[i].SS   = mp2[k].SS;
                            break;
                        }
                    }
                }
            }

            free( mp2 );
        }
    }
    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}

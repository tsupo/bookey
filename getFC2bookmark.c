/*
 * clip saver <<getFC2bookmark>>
 *
 *      FC2BOOKMARK → OPML 変換出力プログラム
 *          written by H.Tsujimura  29 Nar 2007
 *
 * $Log: /comm/bookey/getFC2bookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/12/02 19:31 Tsujimura543
 * nullポインタ参照が発生する可能性のある箇所の対処
 * 
 * 5     07/08/24 1:18 Tsujimura543
 * FC2BOOKMARK のページデザイン変更に対応
 * 
 * 4     07/03/30 16:52 Tsujimura543
 * 「公開状態」取得処理を追加
 * 
 * 3     07/03/30 13:43 Tsujimura543
 * 「エントリID」取得処理を追加
 * 
 * 2     07/03/29 23:02 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     07/03/29 15:06 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getFC2bookmark.c 1     09/05/14 3:48 tsupo $";
#endif

int
_getFC2Bookmark(
        const char *userName,
        char       *cookie,
        const char *uid,
        const char *cc,
        MyClip     **mp,
        MyClipEx   **mpEx,
        int        *total,
        char       *response,
        size_t     sz
    )
{
    char    url[MAX_URLLENGTH];
    BOOL    isPrivate = FALSE;
    BOOL    cont  = TRUE;
    int     num   = 0;
    int     cnt   = 0;
    int     unit  = 200;
    char    *p, *q, *r, *s;
    char    tmp[MAX_DESCRIPTION_LEN * 2];
    char    target[MAX_URLLENGTH];

    target[0] = NUL;
    if ( cookie && *cookie && *uid && *cc ) {
        isPrivate = TRUE;
        sprintf( url,
                 "http://bookmark.fc2.com/user/index?uid=%s&cc=%s",
                 uid, cc );
        strcpy( target, "http://bookmark.fc2.com/user" );
    }
    else {
        sprintf( url,
                 "http://bookmark.fc2.com/search/user/%s",
                 userName );
        strcpy( target, url );
    }

    do {
        setUpReceiveBuffer( response, sz );
        if ( isPrivate )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( *total == 0 ) {
            // 全部で何件あるか、前もって調べておく
            p = strstr( response, "<div id=\"content\">" );
            if ( p ) {
                p += 18;
                q = strstr( p, sjis2utf("件中") );
                if ( q ) {
                    while ( (q > p) &&
                            ((*q < '0') || (*q > '9')) )
                        q--;
                    while ( (q > p) &&
                            ((*(q - 1) >= '0') && (*(q - 1) <= '9')) )
                        q--;
                    if ( (q > p) && (*q >= '0') && (*q <= '9') )
                        *total = atol( q );
                }
            }
        }

        // ブックマークを抜き出す
        p = response;
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

            q = strstr( p, "<div id=\"b-" );
            if ( !q )
                break;
            p = q + 11;
            q = strstr( p, "<h4>" );
            if ( !q )
                break;

            if ( isPrivate && mp ) {
                // 公開・非公開
                r = strstr( p, "<p class=\"allow-access\">" );
                if ( r && (r < q) ) {
                    p = r + 24;
                    s = sjis2utf( "非公開" );
                    if ( !strncmp( p, s, strlen(s) ) )
                        (*mp)[num].publication = PUB_PRIVATE;
                }
            }

            // URL
            p = q + 4;
            q = strstr( p, "<a href=\"" );
            if ( !q )
                break;
            q += 9;
            r = strstr( q, "\">" );
            if ( !r )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // タイトル
            p = r + 2;
            while ( (*p == ' ')  || (*p == '\t') ||
                    (*p == '\r') || (*p == '\n')    )
                p++;
            q = strstr( p, "</a>" );
            if ( !q )
                break;
            while ( (*(q - 1) == ' ')  || (*(q - 1) == '\t') ||
                    (*(q - 1) == '\r') || (*(q - 1) == '\n')    )
                q--;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjisEx( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( ( r = strstr( tmp, "&#39;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 5 ); /* &#39; → ' に置換 */
            }
            while ( ( r = strstr( tmp, "&quot;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &quot; → ' に置換 */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            p = q + 4;
            s = strstr( p, "</table>" );
            if ( !s )
                break;

            // エントリID
            if ( isPrivate && mpEx ) {
                q = strstr( p, "_bookmark/" );
                if ( q ) {
                    p = q + 10;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( tmp, p, q - p );
                        tmp[q - p] = NUL;
                        strcpy( (*mpEx)[num].entryID, tmp );
                        p = q + 1;
                    }
                }
            }

            // コメント
            q = strstr( p, "<p class=\"description\">" );
            if ( q && (q < s) ) {
                p = q + 23;
                q = strstr( p, "<img " );
                if ( q ) {
                    p = q + 5;
                    q = strstr( p, "/>" );
                    if ( q )
                        p = q + 2;
                }
                while ( isWhiteSpace( *p ) )
                    p++;
                s = q = strstr( p, "</p>" );
                if ( q ) {
                    while ( isWhiteSpace( *(q - 1) ) )
                        q--;
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    r = utf2sjisEx( tmp );
                    if ( r )
                        strcpy( tmp, r );

                    while ( ( r = strstr( tmp, "&#39;" ) ) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 5 ); /* &#39; → ' に置換 */
                    }
                    while ( ( r = strstr( tmp, "&quot;" ) ) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 6 ); /* &quot; → ' に置換 */
                    }
                    if ( mp )
                        strcpy( (*mp)[num].comment, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].comment, tmp );

                    p = s + 4;
                    s = strstr( p, "</table>" );
                    if ( !s )
                        break;
                }
            }

            // タグ
            q = strstr( p, "<p class=\"note\">" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 16;
                s = strstr( p, "<span class=\"date\">" );
                if ( !s ) {
                    s = strstr( p, "</p>" );
                    if ( !s )
                        break;
                }
                do {
                    if ( isPrivate )
                        q = strstr( p, "<a href=\"/user/tag/" );
                    else
                        q = strstr( p, "<a href=\"/search/tag/" );
                    if ( !q || (q > s) )
                        break;
                    p = q + (isPrivate ? 19 : 22);
                    q = strstr( p, "\">" );
                    if ( !q || (q > s) )
                        break;
                    p = q + 2;
                    q = strstr( p, "</a>" );
                    if ( !q || (q > s) )
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
                    r = utf2sjisEx( tmp );
                    if ( r )
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
                p = s;
            }

            // 投稿日時
            q = strstr( p, "<span class=\"date\">" );
            if ( !q )
                break;
            p = q + 19;
            q = strchr( p, '(' );
            if ( !q )
                break;
            p = q + 1;
            q = strchr( p, ')' );
            if ( !q )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            strcat( tmp, " +0900" );    /* {@@} */
            if ( mp )
                getDateTimeFromDateString( tmp,
                                           &((*mp)[num].yyyy),
                                           &((*mp)[num].mm),
                                           &((*mp)[num].dd),
                                           &((*mp)[num].HH),
                                           &((*mp)[num].MM),
                                           &((*mp)[num].SS) );
            p = q + 1;
            num++;
        } while ( p && *p );

        // 次へ
        cont = FALSE;
        q = strstr( p, "<div class=\"pagenation\">" );
        if ( !q )
            q = strstr( p, "<div class=\"pagination\">" );
        if ( q ) {
            p = q + 24;
            q = strstr( p, sjis2utf("\">次の") );
            if ( !q )
                q = strstr( p, sjis2utf(">&raquo;次へ") );
            if ( q ) {
                while ( (q >= response) && (*q != '?') )
                    q--;
                if ( *q == '?' ) {
                    char    page[MAX_URLLENGTH];
                    p = strchr( q, '"' );
                    if ( p ) {
                        strncpy( page, q, p - q );
                        page[p - q] = NUL;
                        sprintf( url, "%s%s", target, page );
                        cont = TRUE;
                        Sleep( 1000 );
                    }
                }
            }
        }
    } while ( cont );

    return ( num );
}


MyClip  *
getFC2Bookmark(
        const char *userName,   /* (I) ユーザ名 (FC2ID またはメールア */
                                /*     ドレス)                        */
        const char *password,   /* (I) パスワード (非公開のブックマー */
                                /*     クも取得したい場合に必要 [さら */
                                /*     に、userName で指定するのは    */
                                /*     FC2ID ではなく、メールアドレス */
                                /*     である必要がある])             */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    )
{
    /*
     *  userName で指定されたユーザのブックマーク(のうち、公開されて
     *  いるもの)を全件取得する(非公開のものも取得するには、userName
     *  のユーザの password の指定も必要)
     */
    MyClip  *mp = NULL;
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    int     num = 0;
    char    uid[MAX_NAMELEN];
    char    cc[MAX_KEYLENGTH];

    *numOfClips = 0;
    uid[0] = NUL;
    cc[0]  = NUL;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

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

        // FC2BOOKMARK にlogin (cookie を取得)
        if ( !loginFC2Bookmark( userName, password, cookie, uid, cc ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "FC2BOOKMARK への login に失敗しました\n"
                        : "FC2BOOKMARK: login failed.\n",
                       stderr );
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // ブックマークの取得
    num = _getFC2Bookmark( userName, cookie, uid, cc,
                           &mp, NULL, total, response, sz );
    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}
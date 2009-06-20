/*
 * clip saver <<getNiftyClip>>
 *
 *      ニフティクリップ → OPML 変換出力プログラム
 *          written by H.Tsujimura  7 Jul 2006
 *
 * $Log: /comm/bookey/getNiftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 22    08/12/02 19:32 Tsujimura543
 * (1) nullポインタ参照が発生する可能性のある箇所の対処
 * (2) メモリ解放忘れ対処
 * 
 * 21    08/11/11 18:23 Tsujimura543
 * _getNiftyClipWithApiKey() 内でタイトル、コメント、タグを URL デコード
 * するのをやめた
 * 
 * 20    08/11/11 17:17 Tsujimura543
 * 「APIキーを使用して@niftyクリップから取得する」処理を追加、動作確認した
 * 
 * 19    08/11/11 16:41 Tsujimura543
 * NUM_OF_INFO_PER_NIFTY_API の定義を niftyClip.h へ移動
 * 
 * 18    08/11/04 13:56 Tsujimura543
 * @niftyクリップの html 構造変更(AutoPagerize 対応)に伴う更新
 * 
 * 17    08/03/17 18:10 Tsujimura543
 * getScreenNameOnNiftyClip() を導入。ソースを整理した
 * 
 * 16    08/03/12 5:21 Tsujimura543
 * デバッグ用コードを削除(し忘れていた)
 * 
 * 15    08/03/12 4:37 Tsujimura543
 * 2008年3月11日の「@niftyクリップ」リニューアルに対応した
 * 
 * 14    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 13    07/01/19 18:25 Tsujimura543
 * _getNiftyClip() を導入、リファクタリングを実施
 * 
 * 12    07/01/17 23:48 Tsujimura543
 * (1) 英語モード対応
 * (2) コマンドライン版をビルドできるようにした
 * 
 * 11    06/12/11 20:47 Tsujimura543
 * 「公開フラグ」 (public/private) に対応
 * 
 * 10    06/12/07 19:53 Tsujimura543
 * getDateTimeFromDateString() を導入し、日時情報の解析を委ねることにする
 * 
 * 9     06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 8     06/10/05 16:30 Tsujimura543
 * skipToNextItemWithSeparator() の定義を myClip.h へ移動
 * 
 * 7     06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 6     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 5a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 5     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 4     06/07/21 21:09 Tsujimura543
 * ニフティクリップの取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 3     06/07/19 19:22 Tsujimura543
 * cookie 解放漏れルートがあったので、修正
 * 
 * 2     06/07/19 15:02 Tsujimura543
 * 少しだけリファクタリング
 * 
 * 1     06/07/07 18:42 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#include "niftyClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getNiftyClip.c 1     09/05/14 3:48 tsupo $";
#endif


int
_getNiftyClipWithApiKey(
        const char *apiKey,     /* (I) APIキー */
        long       offset,      /* (I) 取得開始ブックマーク位置     */
        long       *numOfPosts, /* (I) 取得するブックマークの数     */
                                /* (O) 取得したブックマークの数     */
        MyClip     *posts,      /* (O) 取得したブックマーク         */
        BOOL       *more        /* (O) 取得可能残存ブックマーク有無 */
    )
{
    int     n = 0;
    size_t  sz = MAX_CONTENT_SIZE * 64;
    char    *request;
    char    *response;

    *more = FALSE;
    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( n );

    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( n );
    }

    // APIキー + max + start
    sprintf( request,
             "api_key=%s&"
             "max=%d&"
             "start=%d&"
             "alt=xml",
             apiKey,
             *numOfPosts,
             offset );

    setUpReceiveBuffer( response, sz );
    http_post( "http://api.clip.nifty.com/api/v1/clip/list",
               "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        char    *p = strstr( response, "<message>OK</message>" );
        if ( p ) {
            char    *q = strstr( p + 21, "<clips>" );
            if ( q ) {
                char    *r, *s;
                char    temp[MAX_DESCRIPTION_LEN];
                int     numOfTags = 0;

                p = q + 7;
                do {
                    q = strstr( p, "<clip>" );
                    if ( !q )
                        break;
                    p = q + 6;

                    // title
                    q = strstr( p, "<title>" );
                    if ( !q )
                        break;
                    r = q + 7;
                    q = strstr( r, "</title>" );
                    if ( !q )
                        break;
                    strncpy( temp, r, q - r );
                    temp[q - r] = NUL;
                    s = utf2sjisEx( temp );
                    strcpy( posts[n].title, s ? s : temp );

                    // url
                    q = strstr( p, "<url>" );
                    if ( !q )
                        break;
                    r = q + 5;
                    while ( (*r == ' ')  || (*r == '\t') ||
                            (*r == '\r') || (*r == '\n')    )
                        r++;
                    q = strstr( r, "</url>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ')  || (*(q - 1) == '\t') ||
                            (*(q - 1) == '\r') || (*(q - 1) == '\n')    )
                        q--;
                    strncpy( posts[n].url, r, q - r );
                    posts[n].url[q - r] = NUL;

                    // comment
                    q = strstr( p, "<comment>" );
                    if ( !q )
                        break;
                    r = q + 9;
                    q = strstr( r, "</comment>" );
                    if ( !q )
                        break;
                    strncpy( temp, r, q - r );
                    temp[q - r] = NUL;
                    while ( ((s = strchr(temp, '\r')) != NULL) ||
                            ((s = strchr(temp, '\n')) != NULL)    )
                        strcpy( s, s + 1 ); /* 改行を取り除く */
                    s = utf2sjisEx( temp );
                    strcpy( posts[n].comment, s ? s : temp );

                    // created_at
                    q = strstr( p, "<created_at>" );
                    if ( !q )
                        break;
                    r = q + 12;
                    q = strstr( r, "</created_at>" );
                    if ( !q )
                        break;
                    strncpy( temp, r, q - r );
                    temp[q - r] = NUL;
                    getDateTimeFromDateString( temp,
                                               &(posts[n].yyyy),
                                               &(posts[n].mm),
                                               &(posts[n].dd),
                                               &(posts[n].HH),
                                               &(posts[n].MM),
                                               &(posts[n].SS) );

                    // tags - tag
                    numOfTags = 0;
                    posts[n].tags[0] = NUL;
                    q = strstr( p, "<tags>" );
                    if ( !q )
                        break;
                    q += 6;
                    s = strstr( q, "</tags>" );
                    if ( !s )
                        break;
                    do {
                        r = strstr( q, "<tag>" );
                        if ( !r || (r > s) )
                            break;
                        q = r + 5;
                        r = strstr( q, "<tag_name>" );
                        if ( !r || (r > s) )
                            break;
                        q = r + 10;
                        r = strstr( q, "</tag_name>" );
                        if ( !r || (r > s) )
                            break;

                        strncpy( temp, q, r - q );
                        temp[r - q] = NUL;
                        q = utf2sjisEx( temp );

                        if ( numOfTags > 0 )
                            strcat( posts[n].tags, " " );
                        strcat( posts[n].tags, q ? q : temp );

                        numOfTags++;
                        q = r + 11;
                    } while ( numOfTags < 10 );

                    n++;

                    q = strstr( p, "</clip>" );
                    if ( !q )
                        break;
                    p = q + 7;
                } while ( n < *numOfPosts );
            }
        }
    }

    free( response );
    free( request );

    if ( n == *numOfPosts )
        *more = TRUE;
    else
        *numOfPosts = n;

    return ( n );
}

int
_getNiftyClip2(
        const char *apiKey,     /* (I) APIキー */
        MyClip     **mp,
        int        *total
    )
{
    int     n = 0;
    int     max = 1000; /* 暫定 */
    int     cnt = 0, block = 1;
    long    num = NUM_OF_INFO_PER_NIFTY_API;
    long    offset = 0;
    BOOL    more = TRUE;
    MyClip  *posts =
        (MyClip *)malloc( sizeof (MyClip) * NUM_OF_INFO_PER_NIFTY_API );

    if ( !posts )
        return ( cnt );

    *total = 0;

    do {
        long    i;
        MyClip  *newClip_p;

        memset( posts, 0x00, sizeof ( MyClip ) * num );
        n = _getNiftyClipWithApiKey( apiKey, offset, &num, posts, &more );
        if ( n <= 0 )
            break;

        for ( i = 0; i < n; i++ ) {
            newClip_p = allocateMyClipIfNecessary( mp, max, &block, cnt );
            if ( !newClip_p ) {
                more = FALSE;
                break;
            }
            *mp = newClip_p;

            memcpy( &((*mp)[cnt]), &(posts[i]), sizeof ( MyClip ) );
            cnt++;
        }
        offset += n;
    } while ( more == TRUE );

    *total = cnt;
    free( posts );

    return ( cnt );
}



void
getDateTimeOnNiftyClip(
        const char *entryURL,
        const char *userName,
        char       *cookie,
        MyClip     *mp
    )
{
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    setUpReceiveBuffer( response, sz );
    if ( cookie )
        http_getEx( entryURL, response, cookie );
    else
        http_get( entryURL, response );

    if ( *response ) {
        const char  *p;
        const char  *q;
        const char  *r;
        char        target[BUFSIZ];

        sprintf( target, "%s</a>", userName );
        p = strstr( response, target );
        if ( p ) {
            r = p;
            p += strlen(target);
            q = strstr( p, "class=\"date\"" );
            if ( q ) {
                p = q + 12;
                while ( *p && ((*p < '0') || (*p > '9')) )
                    p++;
                if ( p ) {
                    q = strchr( p, '<' );
                    if ( q ) {
                        char    tmp[BUFSIZ];
                        strncpy( tmp, p, q - p );
                        tmp[q -p] = NUL;
                        strcat( tmp, " +0900" );
                        if ( mp )
                            getDateTimeFromDateString( tmp,
                                                       &(mp->yyyy),
                                                       &(mp->mm),
                                                       &(mp->dd),
                                                       &(mp->HH),
                                                       &(mp->MM),
                                                       &(mp->SS) );
                    }
                }
            }

            // ついでに「公開状態」を取得
            p = r;
            q = response;
            while ( (p > q) && (strncmp( p, "<em>", 4 ) != 0) )
                p--;
            if ( !strncmp( p, "<em>", 4 ) ) {
                p += 4;
                q = strstr( p, sjis2utf("非表示") );
                if ( q && (q < r) )
                    mp->publication = PUB_PRIVATE;
            }
        }
    }


    free( response );
}

int
_getNiftyClip(
        const char *target,
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    url[MAX_URLLENGTH];
    char    entryURL[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    char    tmp[MAX_DESCRIPTION_LEN * 2];

    strcpy( url, target );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie ) {
            // cookie が無限に長くなっていくのを抑止
            const char  *p = strstr( cookie, "; VISIT_" );

            if ( p ) {
                const char  *q = strstr( p + 9, "; VISIT_" );

                if ( q ) {
                    const char  *r;

                    do {
                        r = strstr( q + 9, "; VISIT_" );
                        if ( r )
                            q = r;
                    } while ( r );

                    strcpy( (char *)p, q );
                }
            }

            http_getEx( url, response, cookie );
        }
        else
            http_get( url, response );

        if ( !response || !(response[0]) )
            break;

        if ( *total == 0 ) {
            // 全部で何件あるか、前もって調べておく
            p = strstr( response, sjis2utf("件中") );
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
        p = strstr( response, "class=\"clipList\"" );
        if ( !p ) {
            p = strstr( response, "class=\"clipList " );
            if ( !p )
                break;
        }
        p += 16;

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

            q = strstr( p, "<!-- roop -->" );
            s = strstr( p, "<!-- /roop -->" );
            if ( !q || !s )
                break;
            p = q + 13;

            // エントリページURL
            q = strstr( p, "<a id=\"bm-" );
            if ( !q )
                q = strstr( p, "\" id=\"bm-" );
            if ( !q || (q > s) ) {
                q = strstr( p, "<a href=\"" );
                if ( !q || (q > s) )
                    break;
                p = q + 9;
            }
            else {
                p = q + 10;
                q = strstr( p, "\" href=\"" );
                if ( !q || (q > s) )
                    break;
                p = q + 8;
            }
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
            if ( tmp[0] == '/' )
                sprintf( entryURL, "http://clip.nifty.com%s", tmp );
            else
                strcpy( entryURL, tmp );

            // タイトル
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &#039; → ' に置換 */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // URL
            p = q + 4;
            q = strstr( p, "<p class=\"url\">" );
            if ( q && (q > s) )
                break;
            p = q + 15;
            q = strstr( p, "<a href=\"" );
            if ( q && (q > s) )
                break;
            p = q + 9;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // タグ
            p = q + 1;
            q = strstr( p, "class=\"tagList\"" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 15;
                do {
                    r = sjis2utf( "\" class=\"tag\">【" );
                    q = strstr( p, r );
                    if ( !q || (q > s) )
                        break;
                    p = q + strlen( r );
                    r = sjis2utf( "】</a>" );
                    q = strstr( p, r );
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

                    p = q + strlen( r );
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );
                    while ( (r = strstr( tmp, "&#039;" )) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 6 ); /* &#039; → ' に置換 */
                    }
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            // 年月日時分秒 → @niftyクリップ リニューアルにより、エントリ
            //                 ページからしか日時が取れなくなった

            // コメント
            q = strstr( p, "<p class=\"comment\">" );
            if ( !q || (q > s) )
                break;
            p = q + 19;
            if ( !strncmp( p, "<img ", 5 ) ) {
                p += 5;
                q = strchr( p, '>' );
                if ( q )
                    p = q + 1;
            }
            q = strstr( p, "</p>" );
            if ( !q || (q > s) )
                break;

            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );

            /* ニフティクリップのコメントには改行が含まれ得る */
            while ( ((p = strchr(tmp, '\r')) != NULL) ||
                    ((p = strchr(tmp, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* 改行を取り除く */
            /* ニフティクリップのコメントには <br /> が含まれ得る */
            while ( (p = strstr( tmp, "<br />" )) != NULL )
                strcpy( p, p + 6 ); /* <br /> を取り除く */
            while ( (p = strstr( tmp, "&#039;" )) != NULL ) {
                *p = '\'';
                strcpy( p + 1, p + 6 ); /* &#039; → ' に置換 */
            }
            if ( mp )
                strcpy( (*mp)[num].comment, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].comment, tmp );

            // 削除用ブックマークID
            p = q + 4;
            q = strstr( p, "onclick=\"javascript:removeThisClip(" );
            if ( !q || (q > s) )
                break;
            p = q + 35;
            q = strchr( p, ')' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            if ( mpEx )
                strcpy( (*mpEx)[num].entryID, tmp );

            // 年月日時分秒 + 公開状態
            if ( mp )
                getDateTimeOnNiftyClip(
                            entryURL, userName, cookie, &((*mp)[num]) );

            p = s + 14;

            num++;
        } while ( p && *p );

        // 次へ
        cont = FALSE;
        p = strstr( response, "\" class=\"nextprev\">&gt;</a>" );
        if ( !p )
            p = strstr( response, "\" rel=\"next\">&gt;</a>" );
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;
                    sprintf( url, "%s%s", target, page );
                    cont = TRUE;
                    Sleep( 1000 );
                }
            }
        }
    } while ( cont );

    return ( num );
}

char    *
getScreenNameOnNiftyClip(
        char   *screenname,
        char   *targetURL,
        char   *response,
        size_t sz,
        char   *cookie )
{
    // ニフティクリップのトップページを取得し、ユーザ名を確定する
    setUpReceiveBuffer( response, sz );
    http_getEx( "http://clip.nifty.com/", response, cookie );
    if ( *response ) {
        char    *p, *q;

        p = strstr( response, "/rss/users/" );
        if ( !p )
            p = strstr( response, "/tags/users/" );
        if ( p ) {
            p += 10;
            while ( *p != '/' )
                p++;
            if ( *p == '/' )
                p++;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( screenname, p, q - p );
                screenname[q - p] = NUL;
                sprintf( targetURL,
                         "http://clip.nifty.com/users/%s", screenname );
            }
        }

        response[0] = NUL;
    }

    return ( screenname );
}

MyClip  *
getNiftyClip(
        const char *userName,   /* (I) @nifty ID または PLEASY ID もしくは */
                                /*     ユーザー名                          */
        const char *password,   /* (I) パスワード (userName に @nifty ID   */
                                /*     または PLEASY ID を指定したときのみ */
                                /*     必須)                               */
        const char *apiKey,     /* (I) APIキー                             */
        int        *total,      /* (O) 当該ユーザのブックマークの総数      */
        int        *numOfClips  /* (O) 取得したブックマークの数            */
    )
{
    /*
     *  userName で指定されたユーザーのクリップを全件取得する(@nifty ID また
     *  は PLEASY ID で指定する場合は、password の指定も必要。ユーザー名で指
     *  定する場合は、password は不要[ただし、プライベートモードのクリップは
     *  取得できない]。)
     */
    MyClip  *mp = NULL;
    int     num = 0;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;
    char    screenname[80];

    screenname[0] = NUL;
    *numOfClips   = 0;

    if ( apiKey != NULL && *apiKey != NUL ) {
        num = _getNiftyClip2( apiKey, &mp, total );
        *numOfClips = num;
        return ( mp );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0] = NUL;

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

        // ニフティクリップにlogin (cookie を取得)
        if ( !loginNiftyClip( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "ニフティクリップへの login に失敗しました\n"
                        : "nifty clip: login failed.\n",
                       stderr);
            free( response );
            free( cookie );
            return ( mp );
        }

        // ニフティクリップのトップページを取得し、ユーザ名を確定する
        getScreenNameOnNiftyClip( screenname, target,
                                  response, sz, cookie );
    }
    else
        sprintf( target, "http://clip.nifty.com/users/%s", userName );

    if ( target[0] == NUL ) {
        if ( cookie )
            free( cookie );
        free( response );
        return ( mp );
    }

    // ブックマークの取得
    num = _getNiftyClip( target,
                         screenname[0] ? screenname : userName,
                         cookie,
                         &mp, NULL, response, sz, total );
    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_NIFTY_CLIP_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( username, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    if ( getLanguageCode() == 0x0411 ) {
        // 日本語
        fprintf( stderr,
                 "getNC: ニフティクリップ → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tニフティクリップから吸い出した内容を OPML ファイルとして"
                 "出力する\n" );
        fprintf( stderr,
                 "    getNC [-x] -u ID -p パスワード\n" );
        fprintf( stderr,
                 "      ID: @nifty ID または PLEASY ID\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getNC: get bookmarks from nifty clip, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getNC [-x] -u ID -p password\n" );
        fprintf( stderr,
                 "      ID: @nifty ID or PLEASY ID\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* nifty clip へ登録済みのブックマークを取得 */
    mp = getNiftyClip( username, password, NULL, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  nifty clip のブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "nifty clip", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_NIFTY_CLIP_EXE */

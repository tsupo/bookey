/*
 *  指定 Web ページのタグ候補を抽出する
 *      written by H.Tsujimura  30 Nov 2005
 *
 * $Log: /comm/bookey/extractTags.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 30    09/03/30 16:48 Tsujimura543
 * getTagsFromYahooAPI() の request の確保サイズ計算式を修正
 * 
 * 29    09/02/24 16:25 Tsujimura543
 * Yahoo! Japan の「形態素解析API」を利用した頻出語抽出処理を実装。
 * (タグ候補の選定に当たって使う処理の1つとして追加)
 * 
 * 28    08/11/17 14:48 Tsujimura543
 * USE_BULKFEEDS_API が define 済みの場合のみ、bulkfeeds API を
 * 使うように変更
 * 
 * 27    08/05/21 17:40 Tsujimura543
 * 暫定的に、changeHatenaKeyword() を呼ぶのをやめる
 * 
 * 26    08/05/20 22:56 Tsujimura543
 * getHatenaKeywordLink(), getTagsFromKoshian() の内部で呼んでいる
 * decodeURL() / encodeURL() 内で落ちることがある現象(いまのところ、
 * 原因不明)への対策を実施
 * 
 * 25    07/09/05 1:49 Tsujimura543
 * extractTags() に第2引数を追加(stat1470netを引数化)
 * 
 * 24    07/06/26 13:30 Tsujimura543
 * はてなダイアリーキーワードAPIが停止中のときに
 * getHatenaKeywordLink() 内で落ちることがある不具合に対処
 * 
 * 23    07/04/25 10:23 Tsujimura543
 * 1470.net のタグ候補抽出APIが Not Found を返す場合に対処
 * 
 * 22    07/03/05 17:16 Tsujimura543
 * setKeywordLink() に引数を追加したのに伴う修正を実施
 * 
 * 21    07/03/01 21:42 Tsujimura543
 * リファクタリング
 * 
 * 20    07/03/01 19:08 Tsujimura543
 * 登録対象のURLが長いとき、getTagsFrom1470net() 内でメモリ破壊が起きる
 * 不具合に対処
 * 
 * 19    07/02/27 23:05 Tsujimura543
 * さらにリファクタリング
 * 
 * 18    07/02/27 22:57 Tsujimura543
 * リファクタリング
 * 
 * 17    07/02/27 22:32 Tsujimura543
 * はてなダイアリーキーワード自動リンクAPIを利用した特徴語の発見処理を
 * 入れてみる
 * 
 * 16    07/02/27 0:04 Tsujimura543
 * 1470.net のタグ候補取得APIが使えない場合は、KOSHIANを使うようにしてみた
 * (暫定実装)
 * 
 * 15    06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 14    06/06/29 10:39 Tsujimura543
 * Bulkfeeds API で取得したタグ候補に関して、空文字のタグ候補が発生しない
 * ように修正した
 * 
 * 13    06/06/29 10:25 Tsujimura543
 * (1) タグ候補の最初の1個目が空文字列になることがある現象に対処
 * (2) はてブのタグクラウドから取得したタグ候補が既存のタグ候補と重複して
 *     いないかどうかチェックするようにした
 * 
 * 12    06/06/20 16:29 Tsujimura543
 * isWhiteSpace() を myClip.h へ移動
 * 
 * 11    06/06/20 16:25 Tsujimura543
 * iskanji1(), iskanji2() を myClip.h へ移動
 * 
 * 10    06/05/23 16:31 Tsujimura543
 * extractTags() を修正(はてなブックマークからのタグ取得処理を修正、
 * 1470.net API で取得したタグとの重複チェックを追加)
 * 
 * 9     06/05/23 13:56 Tsujimura543
 * getTitle() と extractTags() の連携による「はてなブックマーク」からの
 * タグ候補取得をサポート
 * 
 * 8     06/03/13 20:58 Tsujimura543
 * コメントを整理
 * 
 * 7     06/03/13 20:55 Tsujimura543
 * 1470.net の API が停止しているとき、最初のタグ候補がいしなお氏の日記の
 * URL になってしまう現象に対処
 * 
 * 6     06/02/09 23:41 Tsujimura543
 * タグ抽出APIを呼び出す前処理を微調整
 * 
 * 5     06/02/09 17:30 Tsujimura543
 * (1) 1470.net API で取得したタグ候補が 20個に満たないときは Bulkfeeds
 *     API を併用するようにした
 * (2) 文字列長が2バイト以下のタグ候補は捨てるようにした
 * 
 * 4     05/12/07 19:21 Tsujimura543
 * normalizeTag() を修正 (いわゆる半角文字のみで構成される文字列のとき、
 * 20バイトではなく21バイトに丸めていた)
 * 
 * 3     05/12/01 15:41 Tsujimura543
 * (1) タグ候補が20バイトより大きい場合は20バイト以内に収めるようにした
 * (2) euc2sjis 失敗時のリカバリ処理を入れた
 * 
 * 2     05/11/30 23:43 Tsujimura543
 * extractTags() の第3引数を (I) から (I/O) へ変更
 * 
 * 1     05/11/30 23:24 Tsujimura543
 * 最初の版
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/extractTags.c 1     09/05/14 3:48 tsupo $";
#endif

static void
normalizeTag( char *tag )
{
    if ( strlen( tag ) > 20 ) {
        char    *s = tag;
        BOOL    kanjiFlag = FALSE;
        int     i = 0;

        while ( *s ) {
            if ( ++i > 20 )
                break;
            if ( !kanjiFlag && iskanji1( *s ) )
                kanjiFlag = TRUE;
            else
                kanjiFlag = FALSE;
            *s++;
        }
        if ( kanjiFlag )
            *(s - 1) = NUL;
        else
            *s = NUL;
    }
}

static char *
stripTags( char *p )
{
    char    *q = (char *)malloc( strlen( p ) + 1 );
    char    *r, *s;

    r = p;
    if ( q && r ) {
        s = q;
        while ( *r ) {
            if ( *r == '<' ) {
                if ( !strncmp( r + 1, "!--", 3 ) ) {
                    char    *t;
                    t = strstr( r + 4, "-->" );
                    if ( t ) {
                        if ( !isWhiteSpace(*(s - 1)) )
                            *s++ = ' ';
                        r = t + 3;
                    }
                    else
                        r += 4;
                }
                else if ( !strncmp( r + 1, "script", 6 ) ) {
                    char    *t;
                    t = strstr( r + 7, "</script>" );
                    if ( t ) {
                        if ( !isWhiteSpace(*(s - 1)) )
                            *s++ = ' ';
                        r = t + 9;
                    }
                    else
                        r += 7;
                }
                else {
                    while ( *r && (*r != '>') )
                        r++;
                    if ( *r == '>' ) {
                        if ( !isWhiteSpace(*(s - 1)) )
                            *s++ = ' ';
                        r++;
                    }
                }
                continue;
            }

            if ( !strncmp( r, "&amp;", 5 ) ) {
                r += 5;
                *s++ = '&';
                continue;
            }
            if ( !strncmp( r, "&lt;", 4 ) ) {
                r += 4;
                *s++ = '<';
                continue;
            }
            if ( !strncmp( r, "&gt;", 4 ) ) {
                r += 4;
                *s++ = '>';
                continue;
            }
            if ( !strncmp( r, "&nbsp;", 6 ) ) {
                r += 6;
                *s++ = ' ';
                continue;
            }
            if ( !strncmp( r, "&quot;", 6 ) ) {
                r += 6;
                *s++ = '"';
                continue;
            }

            while ( isWhiteSpace(*r) && isWhiteSpace(*(r + 1)) )
                r++;

            if ( !(isWhiteSpace(*(s - 1)) && isWhiteSpace(*r)) )
                *s++ = *r;
            r++;
        }
        *s = NUL;

        strcpy( p, q );
        free( q );
    }

    return ( p );
}

void
getTagsFromHatenaBookmark(
        char       **tags,      /* (O)   タグ候補                         */
        char       **hatenaTags,/* (I/O) はてブから取得したタグ候補       */
        int        *curNum,     /* (I/O) 取得済みのタグ候補の数           */
        int        numOfTags    /* (I)   取得しようとしているタグ候補の数 */
    )
{
    char    *p, *q;
    int     num = *curNum;

    p = utf2sjisEx( (char *)(*hatenaTags) );
    if ( p ) {
        while ( *p ) {
            q = tags[num];
            while ( *p && (*p != ' ') )
                *q++ = *p++;
            *q = NUL;
            normalizeTag( tags[num] );
            if ( (tags[num][0] != NUL) && (tags[num][0] != '&') ) {
                // 重複チェック
                int i;

                for ( i = 0; i < num; i++ )
                    if ( !strcmp( tags[i], tags[num] ) )
                        break;

                if ( i == num ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }
            }
            while ( *p == ' ' )
                p++;
        }
    }

    *curNum = num;
}

void
getTagsFromYahooAPI(
        const char *body,       /* (I)   解析対象                         */
        char       **tags,      /* (O)   タグ候補                         */
        int        *curNum,     /* (I/O) 今までに取得済みのタグ候補の数   */
        int        numOfTags,   /* (I)   取得しようとしているタグ候補の数 */
        const char *yahooAppID  /* (I)   Yahoo! Japan アプリケーションID  */
    )
{
    char        *request;
    char        *response;
    size_t      sz  = strlen(encodeURL(body)) + MAX_CONTENT_SIZE;
    size_t      sz2 = MAX_CONTENT_SIZE * 16;

    request = (char *)malloc( sz );
    if ( !request )
        return;
    response = (char *)malloc( sz2 );
    if ( !response ) {
        free( request );
        return;
    }

    sprintf( request,
             "appid=%s&"
             "sentence=%s&"
             "results=uniq&"
             "response=surface&"        // 表記
             "filter=1|2|9|10&"         // 形容詞, 形容動詞, 名詞, 動詞
             "uniq_by_baseform=true",
             yahooAppID,
             encodeURL( body ) );
    setUpReceiveBuffer( response, sz2 );
    http_post( "http://jlp.yahooapis.jp/MAService/V1/parse",
               "application/x-www-form-urlencoded", request, response );
    if ( *response &&
         strstr( response, "<word>"  ) &&
         strstr( response, "<count>" )    ) {
        // 「出現数」の多いものから順にタグ候補にする
        BOOL    found;
        char    *p, *q;
        int     i;
        int     num = *curNum;

        p = any2sjis( response );
        p = strstr( p ? p : response, "<surface>" );
        while ( p ) {
            p += 9;
            q = strstr( p, "</surface>" );
            if ( !q )
                break;

            strncpy( tags[num], p, q - p );
            tags[num][q - p] = NUL;
            normalizeTag( tags[num] );
            found = FALSE;
            for ( i = 0; i < num; i++ ) {
                if ( !strcmp( tags[i], tags[num] ) ) {
                    found = TRUE;
                    break;
                }
            }

            if ( found == FALSE ) {
                num++;
                if ( num >= numOfTags )
                    break;
            }

            q += 4;
            p = strstr( q, "<surface>" );
        }

        *curNum = num;
    }

    free( response );
    free( request );
}

void
getHatenaKeywordLink(
        const char *body,       /* (I)   解析対象                         */
        char       **tags,      /* (O)   タグ候補                         */
        int        *curNum,     /* (I/O) 今までに取得済みのタグ候補の数   */
        int        numOfTags,   /* (I)   取得しようとしているタグ候補の数 */
        BOOL       striped      /* (I)   すでに stripTags 済みか否か      */
    )
{
    /* キーワードリンク埋め込み */
    char    *p, *result;
    size_t  sz = ((body && *body) ? strlen( body )
                                  : MAX_CONTENT_SIZE) * 32;
    result = (char *)malloc( sz );
    if ( result ) {
        const char  *q = body;
        if ( !striped ) {
            p = any2utf( body );
            q = stripTags( p ? p : body );
        }

        memset( result, 0x00, sz );
        p = setKeywordLink( q,
                            result, sz, 0, CNAME_GENERAL,
                            "_blank", "hatena" );
        if ( p && *p && strcmp( p, "(null)" ) ) {
            if ( !strncmp( p, ";lt=;lt=", 8 ) ) {
                /* 文字化け検出 */
                free( result );
                return;
            }
            else
                utf2sjisEx( p );
        }
        else {
#if 0
            /* はてなダイアリーキーワード自動リンクAPIが */
            /* 機能していない場合                        */
            char    *q;
            size_t  len = 0;

            memset( result, 0x00, sz );
            p = changeHatenaKeyword( body, result, MODE_HTML );
            q = euc2sjis( p );
            if ( !q )
                q = any2sjis( p );
            if ( q && *q )
                len = strlen( q );
            if ( len >= sz - 1 ) {
                strncpy( result, q, sz - 1 );
                result[sz - 1] = NUL;
            }
            else if ( len > 0 )
                strcpy( result, q );
#else
            /* http://d.hatena.ne.jp/images/keyword/keywordlist のフォー  */
            /* マットが変更されているため、changeHatenaKeyword() がうまく */
            /* 機能しなくなっている (変更時期不明)                        */
            *result = NUL;  /* 暫定対処 */
#endif
        }

        if ( *result ) {
            /* キーワードを抜き出す */
            BOOL    found;
            char    *q;
            int     i;
            int     num = *curNum;

            p = any2sjis( result );

            p = strstr( p ? p : result, "<a class=\"hatena\" " );
            while ( p ) {
                p += 18;
                q = strchr( p, '>' );
                if ( !q )
                    break;
                p = q + 1;
                q = strstr( p, "</a>" );
                if ( !q )
                    break;

                strncpy( tags[num], p, q - p );
                tags[num][q - p] = NUL;
                normalizeTag( tags[num] );
                found = FALSE;
                for ( i = 0; i < num; i++ ) {
                    if ( !strcmp( tags[i], tags[num] ) ) {
                        found = TRUE;
                        break;
                    }
                }

                if ( found == FALSE ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }

                q += 4;
                p = strstr( q, "<a class=\"hatena\" " );
            }

            *curNum = num;
        }

        free( result );
    }
}

BOOL
getTagsFrom1470net(
        const char *url,        /* (I)   当該WebページのURL               */
        char       **tags,      /* (O)   タグ候補                         */
        char       **hatenaTags,/* (I/O) はてブから取得したタグ候補       */
        int        *curNum,     /* (I/O) 今までに取得済みのタグ候補の数   */
        int        numOfTags,   /* (I)   取得しようとしているタグ候補の数 */
        char       *response,   /* (O)   受信バッファ                     */
        size_t     sz           /* (I)   受信バッファのサイズ             */
    )
{
    BOOL    stat1470net = TRUE;
    BOOL    recover = FALSE;
    char    *p, *q;
    char    *targetURL;
    int     num = *curNum;

    p = encodeURL( url );
    targetURL = (char *)malloc( strlen( p ) + 128 );
    if ( !targetURL )
        return ( stat1470net );

    // http://1470.net/api/mmutil.php?cmd=getwords;url=[URL] を GET
    sprintf( targetURL,
             "http://1470.net/api/mmutil.php?cmd=getwords&url=%s",
             p );
    setUpReceiveBuffer( response, sz );
    http_get( targetURL, response );

    if ( response[0]                               &&
         (strncmp( response, "<a ", 3 ) != 0)      &&
         !strstr( response, "<li>Not Found</li>" )    ) {
        /* 注意: http://1470.net/api/mmutil.php がサービス停止中の場合は */
        /*       <a href="http://tdiary.ishinao.net/">blog</a>. のような */
        /*       内容の response が返ってくる                            */
        /*   --- 2007年4月25日現在、<li>Not Found</li>  を含む応答が返っ */
        /*       てくる (サービス停止中?)                                */
        p = euc2sjis( response );
        if ( !p ) {
            p = response;
            recover = TRUE;
        }
        while ( *p ) {
            q = tags[num];
            while ( *p && (*p != '\t') && (*p != '\r') && (*p != '\n') )
                *q++ = *p++;
            *q = NUL;

            if ( recover ) {
                q = euc2sjis( tags[num] );
                if ( q )
                    strcpy( tags[num], q );
                else
                    goto next;
            }
            normalizeTag( tags[num] );
            if ( strlen( tags[num] ) <= 2 )
                goto next;

            if ( hatenaTags && *hatenaTags ) {
                // 重複チェック
                int i;
                for ( i = 0; i < num; i++ ) {
                    if ( !strcmp( tags[i], tags[num] ) )
                        goto next;
                }
            }

            num++;
            if ( num >= numOfTags )
                break;

            if ( (*p == '\t') || (*p == '\r') || (*p == '\n') ) {
              next:
                while ( *p && ((*p == '\t') || (*p == '\r') || (*p == '\n')) )
                    p++;
                if ( *p )
                    continue;
            }
            break;
        }

        *curNum = num;
    }
    else
        stat1470net = FALSE;

    free( targetURL );

    return ( stat1470net );
}

BOOL
getTagsFromKoshian(
        char   **tags,      /* (O)   タグ候補                         */
        int    *curNum,     /* (I/O) 今までに取得済みのタグ候補の数   */
        int    numOfTags,   /* (I)   取得しようとしているタグ候補の数 */
        char   *response,   /* (O)   受信バッファ                     */
        char   *response2,  /* (O)   受信バッファ                     */
        size_t sz,          /* (I)   受信バッファのサイズ             */
        BOOL   striped      /* (I)   すでに stripTags 済みか否か      */
    )
{
    static int  statZuzara  = TRUE;
    int         num = *curNum;
    char        *p, *q;
    char        targetURL[MAX_URLLENGTH];
    char        *request;
    size_t      sz2 = sz * 16;

    /* 
     * 文章からキーワードを抜き出すAPI: KOSHIAN
     *     (詳細: http://blog.zuzara.com/2006/12/10/171/)
     * を使って、特徴語(最大20個)を抽出する
     */
    request = (char *)malloc( sz2 );
    if ( request ) {
        if ( !striped ) {
            p = any2utf( response2 );
            q = stripTags(p ? p : response2);
            if ( strlen( q ) >= sz2 - 3 )
                q[sz2 - 3] = NUL;
        }
        else
            q = response2;
        sprintf( request, "q=%s", encodeURL( q ) );
        setUpReceiveBuffer( response, sz );
        strcpy( targetURL, "http://zuzara.dyndns.org/api/koshian" );
        http_post( targetURL,
                   "application/x-www-form-urlencoded",
                   request, response );
        if ( *response ) {
            BOOL    found;
            int     i;

            p = strstr( utf2sjisEx(response), "<Result " );
            while ( p ) {
                p += 8;
                q = strchr( p, '>' );
                if ( !q )
                    break;
                p = q + 1;
                q = strstr( p, "</Result>" );
                if ( !q )
                    break;

                strncpy( tags[num], p, q - p );
                tags[num][q - p] = NUL;
                normalizeTag( tags[num] );
                found = FALSE;
                for ( i = 0; i < num; i++ ) {
                    if ( !strcmp( tags[i], tags[num] ) ) {
                        found = TRUE;
                        break;
                    }
                }

                if ( found == FALSE ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }

                q += 9;
                p = strstr( q, "<Result " );
            }
        }
        else
            statZuzara = FALSE;

        free( request );
    }

    return ( statZuzara );
}

#ifdef  USE_BULKFEEDS_API
void
getTagsFromBulkfeeds(
        char       *response,   /* (I)   受信バッファ                     */
        char       **tags,      /* (O)   タグ候補                         */
        int        *curNum,     /* (I/O) 今までに取得済みのタグ候補の数   */
        int        numOfTags,   /* (I)   取得しようとしているタグ候補の数 */
        BOOL       striped      /* (I)   すでに stripTags 済みか否か      */
    )
{
    BF_TERM bt[20];
    int     numOfTerms = 20;
    int     num = *curNum;
    int     ret;

    ret = extractAnalyseOnBulkfeeds( response, NULL, &numOfTerms, bt );
    if ( ret > 0 ) {
        char    *p;
        int     preNum = num;
        int     i, j;
        BOOL    found;

        for ( i = 0; i < ret; i++ ) {
            p = utf2sjis( bt[i].term );
            if ( p ) {
                if ( (strlen( p ) <= 2) || strchr( p, '&' ) )
                    continue;
                found = FALSE;
                for ( j = 0; j < preNum; j++ ) {
                    if ( !strcmp( tags[j], p ) ) {
                        found = TRUE;
                        break;
                    }
                }
                if ( found )
                    continue;
                strcpy( tags[num], p );
                normalizeTag( tags[num] );
                if ( tags[num][0] ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }
            }
        }
    }
}
#endif  /* USE_BULKFEEDS_API */

void
extractTags(
        const char *url,        /* (I)   当該WebページのURL         */
        char       **tags,      /* (O)   タグ候補                   */
        char       **hatenaTags,/* (I/O) はてブから取得したタグ候補 */
        int        *numOfTags,  /* (I/O) タグ候補の数               */
        BOOL       *stat1470net,/* (I/O) 1470.net の稼働状況        */
        const char *yahooAppID  /* (I)   Yahoo! アプリケーションID  */
    )
{
    char        *response;
    int         num = 0;
 // size_t      sz = MAX_CONTENT_SIZE * 20;
    size_t      sz = MAX_CONTENT_SIZE * 2;
    static int  statZuzara  = TRUE;

    /* 当該Webページのはてなブックマークページからタグを取得 */
    if ( hatenaTags && *hatenaTags ) {
        getTagsFromHatenaBookmark( tags, hatenaTags, &num, *numOfTags );
        if ( num >= *numOfTags ) {
            *numOfTags = num;
            return;
        }
    }

    response = (char *)malloc( sz );
    if ( !response )
        return;

    /* 1470.net の「タグ候補抽出API」を使ってタグ候補を取得 */
    if ( *stat1470net )
        *stat1470net = getTagsFrom1470net( url, tags, hatenaTags,
                                           &num, *numOfTags, response, sz );

    if ( num < *numOfTags ) {
        char    *response2;

        response2 = (char *)malloc( sz );
        if ( response2 ) {
            // 解析対象ページ(ブックマークしようとしているページ)を取得
            setUpReceiveBuffer( response2, sz );
            http_get( url, response2 );

            /* 各種 API を利用して、特徴語を抽出 */
            if ( *response2 ) {
                size_t  sz2  = strlen(response2) * 16;
                char    *buf = (char *)malloc( sz2 );
                if ( buf ) {
                    char    *p = any2utf( response2 );
                    char    *q = stripTags(p ? p : response2);
                    if ( strlen( q ) >= sz2 - 3 )
                        q[sz2 - 3] = NUL;
                    strcpy( buf, q );
                }

                /* Yahoo! Japan 形態素解析 API を利用して、特徴語を抽出 */
                if ( buf )
                    getTagsFromYahooAPI( buf,
                                         tags, &num, *numOfTags, yahooAppID );

                /* はてなダイアリーキーワードリンクAPI */
                if ( num < *numOfTags )
                    getHatenaKeywordLink( buf ? buf : response2,
                                          tags, &num, *numOfTags,
                                          buf ? TRUE : FALSE );


                /* KOSHIAN */
                if ( statZuzara && (num < *numOfTags) )
                    statZuzara = getTagsFromKoshian( tags, &num, *numOfTags,
                                                     response,
                                                     buf ? buf : response2,
                                                     sz,
                                                     buf ? TRUE : FALSE );
#ifdef  USE_BULKFEEDS_API
                /* Bulkfeeds API の「形態素解析+特徴語抽出」 */
                if ( num < *numOfTags )
                    getTagsFromBulkfeeds( buf ? buf : response2,
                                          tags, &num, *numOfTags,
                                          buf ? TRUE : FALSE );
#endif  /* USE_BULKFEEDS_API */

                if ( buf )
                    free( buf );
            }

            free( response2 );
        }
    }

    *numOfTags = num;

    free( response );
}


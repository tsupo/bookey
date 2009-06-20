/*
 *  指定 Web ページの title を取得する
 *      written by H.Tsujimura  14 Oct 2005
 *
 * $Log: /comm/bookey/getTitle.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 32    09/02/24 2:15 Tsujimura543
 * 「はてなブックマーク」の現状のエントリページに合わせて、タグ抽出処理を
 * 改訂
 * 
 * 31    08/11/25 19:37 Tsujimura543
 * 「はてなブックマーク」2008年11月25日リニューアル版での動作を確認
 * 
 * 30    08/11/25 13:08 Tsujimura543
 * getTitle() を、「はてなブックマーク」が 503 を返してきた場合にも対応
 * させた
 * 
 * 29    08/11/25 11:35 Tsujimura543
 * 「はてなブックマーク」がメインテナンス中のときに、charset=Shift_JIS な
 * ページをブックマークしようとすると、getTitle() が返す title が文字化け
 * してしまう不具合に対処
 * 
 * 28    08/07/28 21:09 Tsujimura543
 * コメントを修正
 * 
 * 27    08/07/28 21:05 Tsujimura543
 * getTitle() をアップデート
 * (はてなブックマークのエントリページが、login済みかどうかで、タグ
 * クラウドが表示されたりされなかったりするようになった、等いくつか
 * 変更があったのに伴う修正を実施)
 * 
 * 26    08/04/15 15:07 Tsujimura543
 * コメントを修正
 * 
 * 25    08/04/15 15:05 Tsujimura543
 * title要素に &lt;, &gt;, &quot; が含まれる場合、デコードして表示する
 * ように変更
 * 
 * 24    07/06/08 14:44 Tsujimura543
 * 「はてなブックマークからタグ候補を取得」を2007年6月8日時点のはてな
 * ブックマークのエントリページのフォーマットに合わせて変更
 * (6月のはじめにデザインが変更された)
 * 
 * 23    07/02/02 23:36 Tsujimura543
 * getTitle() の引数を追加
 * 
 * 22    06/07/27 18:55 Tsujimura543
 * (1) 受信電文格納用領域のオーバーラン防止機能を組み込んだ
 * (2) 受信電文格納用領域のサイズを 1/20 に減らした
 * 
 * 21    06/07/27 18:46 Tsujimura543
 * はてなブックマークがメンテナンス中のとき、実際の記事のタイトルに関係な
 * く、タイトルが「現在メンテナンス中です。」になってしまう不具合に対処
 * 
 * 20    06/07/18 20:47 Tsujimura543
 * &raquo: 関連の処理を修正(はてなブックマークの挙動変更に伴うコードの見直
 * し)
 * 
 * 19    06/07/06 14:57 Tsujimura543
 * 「はてなブックマーク」から取得したタイトルに &#39; など数値参照が
 * 含まれる場合、デコードするようにした
 * 
 * 18    06/06/29 10:35 Tsujimura543
 * はてなブックマークのタグクラウドを抽出する処理を、2人以上の人が使用して
 * いるものだけを抽出するように変更した
 * 
 * 17    06/06/26 12:33 Tsujimura543
 * asahi.com 対策 #2 (asahi.com と はてなブックマークの組み合わせで発生
 * する文字化け対策) を追加
 * 
 * 16    06/06/12 14:18 Tsujimura543
 * 関数内 staic 変数を TLS 化した
 * 
 * 15    06/06/01 11:33 Tsujimura543
 * charset が ISO-2022-JP な Web ページにも対応した
 * 
 * 14    06/05/23 15:59 Tsujimura543
 * getTitle() と extractTags() の連携による「はてなブックマーク」からの
 * タグ候補取得をサポート
 * 
 * 13    06/03/13 20:53 Tsujimura543
 * 他者によってはてなブックマークに登録済みのページを登録する場合、当該
 * ページが EUC-JP だとタイトルが文字化けする不具合に対処 (はてなブック
 * マークから取得したタイトルは UTF-8 なので EUC-JP とみなして処理すると
 * 文字化けする)
 * 
 * 12    06/02/22 17:33 Tsujimura543
 * ソースコードを整理
 * 
 * 11    06/02/22 16:45 Tsujimura543
 * &raquo; など、Shift_JIS や EUC-JP では文字化けを起こす文字に関する対策
 * を実施
 * 
 * 10    06/02/06 20:47 Tsujimura543
 * コメントを修正
 * 
 * 9     06/02/06 20:44 Tsujimura543
 * すでに誰かが「はてなブックマーク」に登録している場合は、「はてなブック
 * マークに登録されている title で上書きするようにした
 * 
 * 8     06/02/01 15:41 Tsujimura543
 * <title lang="ja"> のように属性が指定されているケースにも対応した
 * 
 * 7     05/12/22 19:09 Tsujimura543
 * title 要素に余分な white space が含まれる場合、除去するようにした
 * (はてなブックマークの仕様に合わせた)
 * 
 * 6     05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 5     05/10/28 15:40 Tsujimura543
 * ISO-8859-1 の 0xA0 ～ 0xFF の区間にある文字に対処するためのコードを追加
 * 
 * 4     05/10/24 19:00 Tsujimura543
 * タイトルに &#160; が含まれる場合は、空白文字に置換するようにした
 * 
 * 3     05/10/24 17:37 Tsujimura543
 * getTitle() を Account-auto-discovery に対応するよう拡張した
 * 
 * 2     05/10/14 20:37 Tsujimura543
 * 文字コードが Shift_JIS 以外の Web ページのことをうっかり忘れていた
 * 
 * 1     05/10/14 15:23 Tsujimura543
 * 最初の版
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getTitle.c 1     09/05/14 3:48 tsupo $";
#endif

#define BUFFER_SIZE_FOR_GETTITLE    2048

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
encodeURLforHatena( const char *url )
{
    Thread  static char url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *p;
    char                *q;

    strcpy( url2, url );
    while ( (p = strchr( url2, '#' )) != NULL ) {
        q = &url2[strlen(url2)];
        while ( q >= p + 1 ) {
            *(q + 2) = *q;
            q--;
        }
        *p++ = '%';
        *p++ = '2';
        *p   = '3';
    }

    return ( url2 );
}

char    *
getTitle(
        const char *url,        /* (I) 当該WebページのURL                  */
        char       *accountName,/* (O) AccountName-auto-discovery で取得し */
                                /*     た当該Webページのオーナーの(はてな) */
                                /*     アカウント名                        */
        char       *hatenaID,   /* (I) はてなID(すでに自分自身で登録済みか */
                                /*     否かのチェックを行なうときに指定)   */
        char       **hatenaTags,/* (O) はてブから取得したタグ候補          */
                                /*     (注意: 本関数内で格納用の領域を確保 */
                                /*      する。本関数の呼び出し元で領域の解 */
                                /*      放を行なうこと)                    */
        BOOL       *posted      /* (O) すでに自分自身で登録済みか否か      */
    )
{
    Thread  static char title[BUFFER_SIZE_FOR_GETTITLE];
    char                title2[BUFFER_SIZE_FOR_GETTITLE];
    char                url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *response;
    char                *p, *q;
    BOOL                useHatenaBookmark = FALSE;
    size_t              sz;

    *hatenaTags = NULL;
    *posted     = FALSE;
    title[0]    = NUL;
    title2[0]   = NUL;

    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( title );

    sprintf( url2, "http://b.hatena.ne.jp/entry/%s",
             encodeURLforHatena( url ) );

    setUpReceiveBuffer( response, sz );
    http_get( url2, response );
    if ( response && response[0] ) {
        if ( !strstr( response,
     //               sjis2utf( "<div id=\"breadcrumbs\"><a href=\"/\">はてな"
     //                         "ブックマーク</a> &gt; 未ブックマークエントリ"
     //                         "ー</div>") ) ) {
                      sjis2utf( "未ブックマークエントリー") ) ) {
            p = strstr( response, "<title>" );
            if ( p ) {
                char    *q = strstr( p, " - " );
                if ( q ) {
                    p = q + 3;
                    q = strstr( p, "</" );
                    if ( q ) {
                        strncpy( title2, p, q - p );
                        title2[q - p] = NUL;
                    }
                }
                
                p = title2;
                while ( ( q = strstr( p, "&lt;" ) ) != NULL ) {
                    *q = '<';
                    strcpy( q + 1, q + 4 );
                }
                while ( ( q = strstr( p, "&gt;" ) ) != NULL ) {
                    *q = '>';
                    strcpy( q + 1, q + 4 );
                }
                while ( ( q = strstr( p, "&quot;" ) ) != NULL ) {
                    *q = '"';
                    strcpy( q + 1, q + 6 );
                }
                while ( ( q = strstr( p, "&amp;" ) ) != NULL )
                    strcpy( q + 1, q + 5 );

                while ( ( q = strstr( p, "&#" ) ) != NULL ) {
                    char    *r;
                    long    l;

                    q += 2;
                    r = strchr( q, ';' );
                    if ( !r ) {
                        r = strstr( q, "&#" );
                        if ( !r )
                            break;
                        p = r;
                        continue;
                    }

                    l = atol( q );
                    if ( (l >= ' ') && (l < 0x80) ) {
                        q -= 2;
                        *q = (char)l;
                        strcpy( q + 1, r + 1 );
                        p = q + 1;
                    }
                    else
                        p = r + 1;
                }

                if (!strcmp(title2, sjis2utf("現在メンテナンス中です。") ) ||
                    !strcmp(title2, sjis2utf("Service Not Available")    )   )
                    title2[0] = NUL;
            }

#ifdef  OLDFASHIONED
            p = strstr( response, "<dd class=\"list-cloud\">" );
            if ( !p )
                p = strstr( response, "<dd class=\"list-cloud\" " );
#else
            p = strstr( response, "<div id=\"entryinfo\">" );
#endif
            if ( p ) {
#ifdef  OLDFASHIONED
                p += 23;
                q = strstr( p, "</dd>" );
#else
                p += 20;
                q = strstr( p, "<!-- entryinfo -->" );
#endif
                if ( q ) {
                    char    *r = strstr( p, "<a href=\"/t/" );
                    if ( r && (r < q) ) {
                        // はてなブックマークからタグ候補を取得
                        *hatenaTags = (char *)malloc( MAX_CONTENT_SIZE );
                        if ( *hatenaTags ) {
                            char    *s = *hatenaTags;
#ifdef  OLDFASHIONED
                            char    *t;
#endif
                            do {
                                p = r;
                                r = strstr( p, "<a " );
                                if ( r && (r < q) )
                                    p = r + 3;
                                else
                                    break;
                                r = strstr( p, "tag\">" );
                                if ( r && (r < q) ) {
                                    r += 5;
                                    p = strstr( r, "</a>" );
                                    if ( !p )
                                        break;
#ifdef  OLDFASHIONED
                                    t = strstr( r, "<span class=\"tagcount\">" );
                                    if ( t && (t < p) )
                                        p = t;
#endif
                                    while ( r < p )
                                        *s++ = *r++;
                                    *s++ = ' ';
                                }
                            } while ( r && (r < q) );
                            *s = NUL;
                            if ( s > *hatenaTags )
                                *(s - 1) = NUL;
                        }
                    }
                }
            }

            p = strstr( response, "<ul id=\"bookmarked_user\"" );
            if ( p ) {
                if ( hatenaID && *hatenaID ) {
                    char    target[MAX_NAMELEN + 16 + 1];

                    sprintf( target, "<a href=\"/%s/", hatenaID );
                    if ( strstr( response, target ) )
                        *posted = TRUE;
                }
            }

            if ( title2[0] )
                useHatenaBookmark = TRUE;
        }
    }

    setUpReceiveBuffer( response, sz );
    http_get( url, response );

    if ( response && response[0] ) {
        p = strstr( response, "<title>" );
        if ( !p )
            p = strstr( response, "<title " );
        if ( !p )
            p = strstr( response, "<TITLE>" );
        if ( !p )
            p = strstr( response, "<TITLE " );
        if ( !p )
            p = strstr( response, "<h1>" );
        if ( !p )
            p = strstr( response, "<h1 " );
        if ( !p )
            p = strstr( response, "<H1>" );
        if ( !p )
            p = strstr( response, "<H1 " );
        if ( p ) {
            p++;
            p = strchr( p, '>' );
            p++;
            q = strstr( p + 1, "</" );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;

                while ( ( ( p = strchr( title, '\r' ) ) != NULL ) ||
                        ( ( p = strchr( title, '\n' ) ) != NULL )    )
                    strcpy( p, p + 1 );
            }
        }

        if ( title2[0] != NUL )
            strcpy( title, title2 );

        /* asahi.com 対策 #1 */
        while ( ( p = strstr( title, "&#160;" ) ) != NULL ) {
            *p++ = ' ';
            strcpy( p, p + 5 );
        }

        /* asahi.com 対策 #2 */
        if ( ( p = strstr( title, "\xEF\xBF\xBD-\xEF\xBF\xBD" ) ) != NULL ) {
            strcpy( p, " - " );
            strcpy( p + 3, p + 7 );
        }

        if ( accountName ) {
            p = strstr( response, "<foaf:holdsAccount>" );
            if ( p ) {
                char    *r, *s;

                p += 19;
                q = strstr( p, "<foaf:OnlineAccount foaf:accountName=\"" );
                r = strstr( p, "<foaf:accountServiceHomepage rdf:resource="
                               "\"http://www.hatena.ne.jp/\" />" );
                s = strstr( p, "</foaf:OnlineAccount>" );
                if ( q && r && s && (q < r) && (r < s) ) {
                    // 当該アカウントが「はてな投げ銭対応アカウント」であれば
                    q += 38;
                    r = strchr( q, '"' );
                    strncpy( accountName, q, r - q );
                    accountName[r - q] = NUL;
                }
            }
        }
    }

    if ( !(title[0]) && title2[0] )
        strcpy( title, title2 );

    if ( strstr( response, "charset=UTF-8" ) ||
         strstr( response, "charset=utf-8" ) ||
         useHatenaBookmark                      )
        p = utf2sjisEx( title );
    else if ( strstr( response, "charset=Shift_JIS" ) ||
              strstr( response, "charset=shift_jis" )    )
        p = title;
    else
        p = utf2sjis( title );
    if ( p ) {
        if ( p != title )
            strcpy( title, p );
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) ) {
            q = jis2sjis( title );
            if ( q )
                strcpy( title, q );
        }
    }
    else {
        q = NULL;
        if ( strstr( response, "charset=iso-8859-1" ) ||
             strstr( response, "charset=ISO-8859-1" )    ) {
            for ( p = title; *p; p++ ) {
                if ( (unsigned char)(*p & 0xFF) >= 0xA0 ) {
                    q = iso8859_1toUtf8( title );
                    if ( q )
                        p = decodeURL( q ); // utf8 → us-ascii 変換を兼ねる
                    break;
                }
            }
        }

        if ( !q )
            p = euc2sjis( title );
        if ( p )
            strcpy( title, p );
    }
    free( response );

    p = title;
    while ( *p ) {
        if ( (*p == '\t') || (*p == '\r') || (*p == '\n' ) )
            *p = ' ';
        p++;
    }

    p = title;
    while ( *p ) {
        while ( (*p == ' ') && (*(p + 1) == ' ') )
            strcpy( p, p + 1);
        p++;
    }

    p = title;
    while ( *p == ' ' )
        strcpy( p, p + 1);

    if ( *p ) {
        p = &(title[strlen(title) - 1]);
        while ( *p == ' ' )
            *p-- = NUL;
    }
    while ( ( p = strstr( title, "&raquo;" ) ) != NULL ) {
        strncpy( p, "≫", 2 );
        strcpy( p + 2, p + 7 );
    }
    while ( ( p = strstr( title, "&laquo;" ) ) != NULL ) {
        strncpy( p, "≪", 2 );
        strcpy( p + 2, p + 7 );
    }

    return ( title );
}

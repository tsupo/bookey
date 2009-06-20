/*
 * registerBookmark.cpp : ソーシャルブックマーク管理プログラム
 *      ブックマーク登録スレッド
 *          written by H.Tsujimura  13 Oct 2005, 5 Jul 2006
 *
 * $Log: /comm/bookey/registerBookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 73    09/02/25 18:02 Tsujimura543
 * http://d.hatena.ne.jp/gyogyo6/20090225/bookmark を参考にしつつ、
 * getRegularURL() を改訂
 * 
 * 72    09/02/24 16:27 Tsujimura543
 * タグ候補抽出処理群の引数を各々追加
 * 
 * 71    08/12/26 14:33 Tsujimura543
 * 削除対象URL断片に ?rss_fdn= (MSDN) を追加
 * 
 * 70    08/12/03 17:56 Tsujimura543
 * getBookmarkViaEntryPageOnLivedoor() を導入
 * (再登録時の)コメント、タグを取得する際の予備的な処理として使用する
 * 
 * 69    08/12/03 15:37 Tsujimura543
 * 「はてなブックマーク」API による「(再登録実行時の)コメント、タグの取
 * 得」がうまくいかなかった場合は、「はてなブックマーク」のエントリペー
 * ジをスクレイピングして、コメント、タグを取得するようにした
 * 
 * 68    08/12/01 19:17 Tsujimura543
 * escapeAmpasand() → escapeAmpersand() に変更 (綴り誤りを修正)
 * 
 * 67    08/11/04 12:49 Tsujimura543
 * @nifty Clip 登録者数も表示するようにした
 * 
 * 66    08/10/23 18:03 Tsujimura543
 * リダイレクト対策 URL に partners.extranet.microsoft.com を追加
 * 
 * 65    08/10/21 20:00 Tsujimura543
 * リダイレクト対策 URL に sum.com と amazon.com のメールマガジン掲載用
 * リダイレクタを追加
 * 
 * 64    08/09/19 18:04 Tsujimura543
 * 削除対象URL断片に ?from=main (読売新聞) を追加
 * 
 * 63    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 62    08/06/12 17:17 Tsujimura543
 * リダイレクト対策 URL として rss.yomiuri.co.jp/click.phdo を追加
 * 
 * 61    08/05/16 0:22 Tsujimura543
 * コメントを修正
 * 
 * 60    08/05/15 15:29 Tsujimura543
 * リダイレクト対策 c2.lenovo-news.com/g.php を追加
 * (今後の課題: リダイレクト対策 URL を外部設定ファイル等から読込むようにする)
 * 
 * 59    08/05/14 18:56 Tsujimura543
 * リダイレクト対策 URL として www.oracle.co.jp/mp を追加
 * 
 * 58    08/05/14 14:54 Tsujimura543
 * リダイレクト対策 URL として symantecenterprise.rsys3.net を追加
 * 
 * 57    08/05/13 21:25 Tsujimura543
 * リダイレクタ対策 URL として feeds.japan.cnet.com を追加
 * 
 * 56    08/03/11 19:11 Tsujimura543
 * getRegularURL() の対象に ?feedType=RSS (ロイター) を追加
 * 
 * 55    07/12/26 19:42 Tsujimura543
 * http://z.la/ にも対応してみた
 * 
 * 54    07/12/20 20:26 Tsujimura543
 * getRegularURL() の対象に &fm=rss (CDジャーナル) を追加
 * 
 * 53    07/12/19 20:22 Tsujimura543
 * InquiryWebPageInfo() の対象 URL を追加
 * 
 * 52    07/12/17 23:09 Tsujimura543
 * コメントを修正
 * 
 * 51    07/12/17 21:07 Tsujimura543
 * asahi.com の RSS が pheedo 経由に変更された(いつから変更されたのかは不明)
 * のに伴い、InquiryWebPageInfo() を修正した
 * 
 * 50    07/11/15 22:34 Tsujimura543
 * 削除対象URL断片に ?ref=BPN (日経BP) を追加
 * 
 * 49    07/11/13 18:30 Tsujimura543
 * japan.internet.com 対策 (末尾に ?rss が付く) を追加
 * 
 * 48    07/11/12 19:08 Tsujimura543
 * 削除対象URL断片に &ST=web_threat (日経BP) を追加
 * 
 * 47    07/09/05 20:30 Tsujimura543
 * UserAgent 回りをリファクタリング
 * 
 * 46    07/09/05 1:54 Tsujimura543
 * extractTags() で stat1470net が FALSE になった場合は、その直後以降
 * getUsersOfMMmemo() を呼ばないようにした
 * 
 * 45    07/09/05 1:50 Tsujimura543
 * getUsersOfMMmemo() と extractTags() に各々第2引数を追加
 * (stat1470netを引数化)
 * 
 * 44    07/08/27 21:55 Tsujimura543
 * 「はてなスター」に対応
 * 
 * 43    07/07/24 18:21 Tsujimura543
 * getRegularURL() の削除対象 query に bcsi_scan を追加
 * 
 * 42    07/07/09 19:59 Tsujimura543
 * 「digg の投票数」を取得する処理を追加
 * 
 * 41    07/07/02 16:32 Tsujimura543
 * Visual C++ 2005 でのコンパイルチェック結果を反映
 * 
 * 40    07/05/23 14:40 Tsujimura543
 * 407(Proxy Authentication Required) 対策
 * 
 * 39    07/04/25 10:02 Tsujimura543
 * マイクロソフトのリダイレクタ(go.microsoft.com)に対応
 * 
 * 38    07/04/24 13:46 Tsujimura543
 * pheedo.vector.co.jp と pheedo.com のリダイレクタに対応
 * 
 * 37    07/04/16 22:47 Tsujimura543
 * Yahoo! ブックマーク のリダイレクタにも対応
 * 
 * 36    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 35    07/04/09 16:57 Tsujimura543
 * tinyurl.com と rurl.org の短縮URL(リダイレクタ)が使われている場合、リダ
 * イレクト先URLをブックマークするようにした
 * 
 * 34    07/04/02 13:50 Tsujimura543
 * 削除対象URL断片に ?tag=nl (CNET Japan) を追加
 * 
 * 33    07/03/30 16:38 Tsujimura543
 * FC2BOOKMARK(の公開レベル)に対応
 * 
 * 32    07/03/26 23:16 Tsujimura543
 * ローカルOPML登録時にメモリ破壊が発生する可能性のある箇所を発見、
 * 修正を実施
 * 
 * 31    07/03/16 1:03 Tsujimura543
 * proxyサーバ経由でないとインターネットアクセスできないのに、proxyサーバ
 * を使わない設定になっている場合の対策を追加
 * 
 * 30    07/03/14 20:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 29    07/03/14 15:45 Tsujimura543
 * URL 中に & が含まれる場合でも、コメント、タグの内容を復元できるようにし
 * た
 * 
 * 28    07/03/01 21:37 Tsujimura543
 * livedoorクリップに登録している人の数を取得するようにした
 * 
 * 27    07/02/02 23:56 Tsujimura543
 * 改修部分の動作確認完了
 * 
 * 26    07/02/02 23:40 Tsujimura543
 * 再登録しようとしている場合の一連の処理を修正。ドリコムRSSやFlogのカテゴ
 * リも復元できるようにした
 * 
 * 25    07/02/02 23:39 Tsujimura543
 * 実際には「はてなブックマーク」未登録でも getBookmarkOnHatenaWithURI()
 * が登録済みコメント(として記事の概要)を返すことが判明。getTitle() を改
 * 修し、すでに登録済みかどうか判断できるようにした
 * 
 * 24    07/02/02 21:03 Tsujimura543
 * getBookmarkOnHatenaWithURI() から文字列を受け取る各領域のサイズ
 * を暫定値から正式な値に変更
 * 
 * 23    07/02/02 20:59 Tsujimura543
 * すでに「はてなブックマーク」に登録済みのブックマークを改めて登録し直そ
 * うとしている場合は、以前に登録したコメント、タグを取得して、編集し直せ
 * るようにした
 * 
 * 22    07/02/02 20:13 Tsujimura543
 * getRegularURL() に IBM の developerworks 関連ページの URL 正規化
 * 処理を追加
 * 
 * 21    07/01/16 22:32 Tsujimura543
 * 英語モード対応 (抜けがあった)
 * 
 * 20    07/01/16 15:10 Tsujimura543
 * コメント内の typo を修正
 * 
 * 19    07/01/16 15:09 Tsujimura543
 * (1) 英語モード対応
 * (2) amazon.co.jp 以外の Amazon (amazon.com など) の商品の URL も正規化
 *     するようにした
 * 
 * 18    07/01/11 17:01 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 17    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 16    06/12/27 17:37 Tsujimura543
 * ブックマーク投稿ダイアログで右クリックメニューが使えるようにした
 * 
 * 15    06/12/26 0:49 Tsujimura543
 * 3つの「公開レベル」対応部分、修正
 * 
 * 14    06/12/25 22:07 Tsujimura543
 * 「BlogPet 気になる記事」の3つの「公開レベル」に対応
 * 
 * 13    06/12/06 18:59 Tsujimura543
 * 「公開状態」の設定に対応
 * 
 * 12    06/11/10 20:07 Tsujimura543
 * strncmpi() の実体を myClip.c に移動
 * 
 * 11    06/09/29 23:45 Tsujimura543
 * newsing (の「○×」評価) に対応
 * 
 * 10    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 9     06/09/12 13:58 Tsujimura543
 * URL の正規化処理部分を修正 (コンパイルエラーが発生していた)
 * 
 * 8     06/09/11 11:41 Tsujimura543
 * はてなブックマークのコレクションに登録する場合、アマゾンのURLの
 * 形式によっては登録することができないことがあるため、URLを正規化
 * してから登録するようにしてみた
 * 
 * 7     06/09/04 22:33 Tsujimura543
 * SleepEx() → Sleep() に置換
 * 
 * 6     06/09/04 22:30 Tsujimura543
 * 「はてなブックマーク」のコレクションに追加可能か判断するのに getASIN()
 * の結果を利用するようにした
 * 
 * 5     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 4     06/07/27 13:27 Tsujimura543
 * ThinkIT のリダイレクタ(http://cm.thinkit.co.jp/)に対応
 * 
 * 3     06/07/11 22:49 Tsujimura543
 * ECナビ人気ニュースのブックマーク登録者数も表示するようにした
 * (ブックマーク登録画面/EditBookmarkDialog)
 * 
 * 2     06/07/05 11:21 Tsujimura543
 * 余分なコードを削除、整理
 * 
 * 1     06/07/05 11:14 Tsujimura543
 * 「ブックマーク登録スレッド」関連部分を bookeyView.cpp から分離独立させた
 */

#include "bookey.h"
#include <process.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "hatenaApi.h"
#include "twitStar.h"
#ifdef __cplusplus
}
#endif
#include "confirmProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/registerBookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef  WIN32
#include <shlwapi.h>
#else

char    *strstri( const char *src, const char *target )
{
    char        *p = NULL;
    const char  *q;
    size_t      len1 = (src && *src) ? strlen( src ) : 0;
    size_t      len2 = (target && *target) ? strlen( target ) : 0;

    if ( (len1 == 0) || (len2 == 0) || (len1 < len2) )
        return ( p );

    for ( q = src; *src && (len1 >= len2); q++, len1-- ) {
        if ( !strncmpi( q, target, len2 ) ) {
            p = (char *)q;
            break;
        }
    }

    return ( p );
}

#define StrStrI strstri
#endif

void    SetUserAgent( bool set );


// URL の末尾の ?{ref|from}={rss|RSS|atom}, &f=rss を削除する
char    *
getRegularURL( char *url )
{
    char    *p;
    char    tmp[1024];

    if ( !strncmp( url, "http://www.google.com/url?", 26 ) ) {
        p = strstr( url, "?q=http://" );
        if ( !p )
            p = strstr( url, "&q=http://" );
        if ( p )
            strcpy( url, p + 3 );
    }

    if ( !strncmp( url, "http://www.neowing.co.jp/rss/rss.html?", 38 ) ) {
        p = strchr( url, '?' );
        if ( p ) {
            strcpy( tmp, p );
            sprintf( url, "http://www.neowing.co.jp/detailview.html%s", tmp );
        }
    }

    if ( !strncmp( url, "http://codezine.jp/r.x/rss/aid/",  31 ) ||
         !strncmp( url, "http://markezine.jp/r.x/rss/aid/", 32 )    ) {
        p = strrchr( url, '/' );
        if ( p ) {
            strcpy( tmp, p + 1 );
            if ( !strncmp( url, "http://codezine.jp/", 19 ) )
                sprintf(url, "http://codezine.jp/a/article.aspx?aid=%s", tmp);
            else
                sprintf(url, "http://markezine.jp/a/article.aspx?aid=%s",tmp);
        }
    }

    if ( !strncmp( url, "http://markezine.jp/r.x/rss/bid/", 32 ) ) {
        p = strrchr( url, '/' );
        if ( p ) {
            strcpy( tmp, p );
            sprintf( url,
              "http://markezine.jp/bookmark/default.aspx?mode=detail&bid=%s",
                     tmp );
        }
    }

    if ( strstr( url, ".ibm.com/" ) ) {
        p = strstr( url, "/index.shtml?ca=drs-" );
        if ( p )
            *(p + 1) = NUL;
    }

    if ( strstr( url, "japan.internet.com/" ) ) {
        p = strstr( url, "?rss" );
        if ( p )
            *p = NUL;
    }

    if ( ( ( p = StrStrI( url, "?ref=rss"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=rss"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?fr=RSS"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?fr=rdf"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?ref=atom"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=atom"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&f=rss"         ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&from=rss"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?in=rssw"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=top"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?topic=1"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?tag=nl"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?bcsi_scan"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&ST=web_threat" ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?ref=BPN"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&fm=rss"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?feedType=RSS"  ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=main"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=navr"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=any"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=hot"      ) ) != NULL ) ||
      // ( ( p = StrStrI( url, "?rss_fdn="      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?rss"           ) ) != NULL )    )
        *p = NUL;

    return ( url );
}


// Webページ情報取得スレッド
typedef struct IWparam {
    RBparam_t           rbParam;
    char                accountName[32];
    EditBookmarkDialog  *editDlg;
    ProceedingDialog    *procDlg;
}   IWparam_t;

static char    *
escapeAmpersand( char *p )
{
    char    *s, *t, *u;

    s = strchr( p, '&' );
    while ( s ) {
        t = strchr( s, ';' );
        u = strchr( s, '&' );
        if ( !t || (u && (u < t)) ) {
            char    *pp = s + strlen( s );
            while ( pp > s ) {
                *(pp + 2) = *pp;
                pp--;
            }
            *s++ = '%';
            *s++ = '2';
            *s++ = '6';

            s = strchr( s, '&' );
        }
        else
            break;
    }

    return ( p );
}

void
getBookmarkViaEntryPageOnHatena(
        const char *username,
        const char *url,
        char       *title,
        char       *summary,
        char       *tags
    )
{
    int     sz = MAX_CONTENT_SIZE * 20;
    char    *response;
    char    *temp;
    char    entryPageURL[MAX_URLLENGTH * 8];

    response = (char *)malloc( sz );
    if ( !response )
        return;
    temp = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !temp ) {
        free( response );
        return;
    }

    sprintf( entryPageURL,
             "http://b.hatena.ne.jp/entry/%s",
             escapeAmpersand( encodeURLforHatena( url ) ) );
    setUpReceiveBuffer( response, sz );
    http_get( entryPageURL, response );
    if ( *response ) {
        char    *p, *q, *r, *s;
        char    targetString[BUFSIZ];
        size_t  len;

        sprintf( targetString,
                 "id=\"bookmark-user-%s\"",
                 username );
        len = strlen( targetString );
        p = strstr( response, targetString );
        if ( p ) {
            p += len;
            s = strstr( p, "</li>" );

            if ( s ) {
                /* tags */
                q = strstr( p, "<span class=\"tags\">" );
                if ( q && (q < s) ) {
                    r = q + 19;
                    q = strstr( r, "</span>" );
                    if ( q && (q < s) ) {
                        char    *pp, *qq;

                        temp[0] = NUL;
                        len     = 0;
                        while ( r < q ) {
                            pp = strstr( r, "<a " );
                            qq = strstr( r , "</a>" );
                            if ( pp && qq && (pp < qq) && (qq < q) ) {
                                pp = strchr( pp, '>' );
                                if ( pp ) {
                                    if ( len > 0 ) {
                                        temp[len++] = ' ';
                                        temp[len]   = NUL;
                                    }
                                    pp++;
                                    strncat( temp, pp, qq - pp );
                                    len += (qq - pp);
                                    temp[len] = NUL;
                                    r = qq + 4;
                                    continue;
                                }
                            }
                            break;
                        }
                        if ( temp[0] ) {
                            r = utf2sjisEx( temp );
                            strcpy( tags, r ? r : temp );
                        }
                    }
                }

                /* comment */
                q = strstr( p, "<span class=\"comment\">" );
                if ( q && (q < s) ) {
                    r = q + 22;
                    q = strstr( r, "</span>" );
                    if ( q && (q < s) ) {
                        strncpy( temp, r, q - r );
                        temp[q - r] = NUL;
                        r = utf2sjisEx( temp );
                        strcpy( summary, r ? r : temp );
                    }
                }

                /* title */
                p = strstr( response, "<h2 class=\"entrytitle\">" );
                if ( p ) {
                    p += 23;
                    q = r = strstr( p, "</a></h2>" );
                    if ( q ) {
                        while ( q > p ) {
                            if ( (*q == '<') && !strncmp( q + 1, "a ", 2 ) ) {
                                p = q + 3;
                                q = strchr( p, '>' );
                                if ( q ) {
                                    q++;
                                    strncpy( title, q, r - q );
                                    title[r - q] = NUL;
                                    utf2sjisEx( title );
                                }
                                break;
                            }
                            q--;
                        }
                    }
                }
            }
        }
    }

    free( temp );
    free( response );
}

void
getBookmarkViaEntryPageOnLivedoor(
        const char *username,
        const char *url,
        char       *title,
        char       *summary,
        char       *tags
    )
{
    int     sz = MAX_CONTENT_SIZE * 20;
    char    *response;
    char    *temp;
    char    entryPageURL[MAX_URLLENGTH * 8];

    response = (char *)malloc( sz );
    if ( !response )
        return;
    temp = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !temp ) {
        free( response );
        return;
    }

    sprintf( entryPageURL,
             "http://clip.livedoor.com/page/%s",
             escapeAmpersand( encodeURLforHatena( url ) ) );
    setUpReceiveBuffer( response, sz );
    http_get( entryPageURL, response );
    if ( *response ) {
        char    *p, *q, *r, *s;
        char    targetString[BUFSIZ];
        size_t  len;

        sprintf( targetString,
                 "livedoorProfileNickname('%s')",
                 username );
        len = strlen( targetString );
        p = strstr( response, targetString );
        if ( p ) {
            p += len;
            s = strstr( p, "<ul" );
            if ( !s )
                s = strstr( p, "<h4" );

            if ( s ) {
                /* tags */
                q = strstr( p, "user-tag-box" );
                if ( q && (q < s) ) {
                    r = q + 12;
                    q = strstr( r, "</span>" );
                    if ( q && (q < s) ) {
                        char    *pp, *qq;

                        temp[0] = NUL;
                        len     = 0;
                        while ( r < q ) {
                            pp = strstr( r, "<a " );
                            qq = strstr( r , "</a>" );
                            if ( pp && qq && (pp < qq) && (qq < q) ) {
                                pp = strchr( pp, '>' );
                                if ( pp ) {
                                    if ( len > 0 ) {
                                        temp[len++] = ' ';
                                        temp[len]   = NUL;
                                    }
                                    pp++;
                                    strncat( temp, pp, qq - pp );
                                    len += (qq - pp);
                                    temp[len] = NUL;
                                    r = qq + 4;
                                    continue;
                                }
                            }
                            break;
                        }
                        if ( temp[0] ) {
                            r = utf2sjisEx( temp );
                            strcpy( tags, r ? r : temp );
                        }
                    }
                }

                /* comment */
                q = strstr( p, "<p " );
                if ( q && (q < s) ) {
                    r = strchr( q + 3, '>' );
                    if ( r ) {
                        r++;
                        q = strstr( r, "</p>" );
                        if ( q && (q < s) ) {
                            strncpy( temp, r, q - r );
                            temp[q - r] = NUL;
                            r = utf2sjisEx( temp );
                            strcpy( summary, r ? r : temp );
                        }
                    }
                }

                /* title */
                p = strstr( response, "id=\"pagettl\"" );
                if ( !p ) {
                    p = strstr( response, url );
                    if ( p )
                        p -= 12;
                }
                if ( p ) {
                    p += 12;
                    q = r = strstr( p, "</a></h3>" );
                    if ( q ) {
                        while ( q > p ) {
                            if ( (*q == '<') && !strncmp( q + 1, "a ", 2 ) ) {
                                p = q + 3;
                                q = strchr( p, '>' );
                                if ( q ) {
                                    q++;
                                    strncpy( title, q, r - q );
                                    title[r - q] = NUL;
                                    utf2sjisEx( title );
                                }
                                break;
                            }
                            q--;
                        }
                    }
                }
            }
        }
    }

    free( temp );
    free( response );
}


UINT
InquiryWebPageInfo( LPVOID pParam )
{
    IWparam_t   *p  = (IWparam_t *)pParam;
    int         ret = 0;
    char        url[MAX_URLLENGTH];
    char        asin[32];
    CString     ttle;
    CString     text;
    static BOOL stat1470net = TRUE;

    SetUserAgent( TRUE );   /* User-Agent を一時的に変更 */

    ttle.LoadString(IDS_TTL_CONTINUE_GETTING_TITLE);
    text.LoadString(IDS_TXT_CONTINUE_GETTING_TITLE);
    p->procDlg->ChangeDialogText( ttle,     // タイトル取得中
                                  text );   // タイトル取得中……
    asin[0] = NUL;

    // URL の末尾の ?{ref|from}={rss|RSS|atom}, &f=rss を削除する
    getRegularURL( p->rbParam.url );

    // -- 407(Proxy Authentication Required) 対策      @@
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();    // @@
    if ( bp->m_useProxy )                           // @@
        setConfirmProxyInfoFunc( confirmProxyInfo );// @@
    // 当該 URL の Webページの title を取得
    p->accountName[0] = NUL;
    BOOL posted       = FALSE;
    char *hatenaTags  = NULL;
    char *title = getTitle( p->rbParam.url, p->accountName,
                            p->rbParam.hatena.isTarget
                                ? p->rbParam.hatena.username : "",
                            &hatenaTags,
                            &posted );
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );     // @@

    if (!strncmp(p->rbParam.url, "http://feeds.feedburner.com/",     28) ||
        !strncmp(p->rbParam.url, "http://feeds.feedburner.jp/",      27) ||
        !strncmp(p->rbParam.url, "http://rd.yahoo.co.jp/rss/l/",     28) ||
        !strncmp(p->rbParam.url, "http://srd.yahoo.co.jp/BMK/",      27) ||
        !strncmp(p->rbParam.url, "http://www.pheedo.jp/click.phdo?", 32) ||
        !strncmp(p->rbParam.url, "http://www.pheedo.com/click.phdo?",33) ||
        !strncmp(p->rbParam.url,
                           "http://pheedo.vector.co.jp/click.phdo?", 38) ||
        !strncmp(p->rbParam.url, "http://markezine.jp/r.x/bmc/bid/", 32) ||
        !strncmp(p->rbParam.url, "http://cgi.itmedia.co.jp/rss/",    29) || 
        !strncmp(p->rbParam.url, "http://cm.thinkit.co.jp/?",        25) ||
        !strncmp(p->rbParam.url, "http://go.microsoft.com/?linkid=", 32) ||
        !strncmp(p->rbParam.url,
                    "http://co1piltwb.partners.extranet.microsoft.com/"
                    "mcoeredir/mcoeredirect.aspx?",                  77) ||
        !strncmp(p->rbParam.url, "http://tinyurl.com/",              19) ||
        !strncmp(p->rbParam.url, "http://rurl.org/",                 16) ||
        !strncmp(p->rbParam.url, "http://z.la/",                     12) ||
        !strncmp(p->rbParam.url, "http://rss.asahi.com/click.phdo?", 32) ||
        !strncmp(p->rbParam.url,
                           "http://rss.yomiuri.co.jp/click.phdo?",   36) ||
        !strncmp(p->rbParam.url, "http://feeds.japan.zdnet.com/"   , 29) ||
        !strncmp(p->rbParam.url, "http://feeds.japan.cnet.com/"    , 28) ||
        !strncmp(p->rbParam.url, "http://feeds.reuters.com/",        25) ||
        !strncmp(p->rbParam.url, "http://rd.nikkei.co.jp/",          23) ||
        !strncmp(p->rbParam.url, "http://rss.rssad.jp/rss/",         24) ||
        !strncmp(p->rbParam.url,
                           "http://symantecenterprise.rsys3.net/",   36) ||
        !strncmp(p->rbParam.url, "http://www.oracle.co.jp/mp/",      27) ||  
        !strncmp(p->rbParam.url, "http://c2.lenovo-news.com/g.php/", 32) ||
        !strncmp(p->rbParam.url, "http://communications1.sun.com/r/",33) ||
        !strncmp(p->rbParam.url, "http://www.amazon.com/gp/r.html?", 32)   ) {
        url[0] = NUL;
        getCurrentLocation( url );
        p->editDlg->m_url = getRegularURL( url );
        if (!strncmp( p->rbParam.url,"http://www.pheedo.jp/click.phdo?",32)) {
            if ( hatenaTags ) {
                free( hatenaTags );
                hatenaTags = NULL;
            }
            p->accountName[0] = NUL;
            title = getTitle( url, p->accountName,
                              p->rbParam.hatena.isTarget
                                ? p->rbParam.hatena.username : "",
                              &hatenaTags,
                              &posted );
        }
        // CNET Japan での例
        //    (1) http://feeds.feedburner.jp/cnet/rss?m=1575
        //    (2) http://japan.cnet.com/news/ent/story/0,2000056022,20122187,00.htm?ref=rss
        //    (3) http://japan.cnet.com/news/ent/story/0,2000056022,20122187,00.htm
        //  (1) が feedburner.jp 経由で配信されているフィード中の permalink
        //  (2) は (1) にアクセスしたときのリダイレクト先 URL
        //  bookey は、最終的に (3) の URL を採用し、ブックマークに登録する
    }
    else
        p->editDlg->m_url = p->rbParam.url;

    if ( checkProxyInfo() ) {
        SetUserAgent( FALSE );  /* User-Agent を元に戻す */
        return ( ret );
    }

    if ( title && *title )
        p->editDlg->m_title = title;
    p->editDlg->m_enableTipJar = p->accountName[0] ? true : false;
    p->editDlg->m_useCategory  =
        (p->rbParam.drecomRss.username[0] || p->rbParam.flog.username[0])
                                                               ? true : false;
    getASIN( p->rbParam.url, asin );
    if ( asin[0] &&
         !strncmp( p->editDlg->m_url, "http://www.amazon.", 18 ) ) {
        // URL の正規化 (はてなブックマークのコレクション対策)
        //   ここでは、amazon.co.jp 以外の amazon についても URL の
        //   正規化を行なっているが、「はてなブックマーク」のコレク
        //   ションとして登録可能なのは amazon.co.jp の商品だけであ
        //   る (amazon.com の商品はコレクション登録しようとしても
        //   登録されない)
        //   ちなみに、1470.net の MONO は ASIN さえ指定すれば、
        //   amazon.co.jp 以外の商品も登録できる(なぜか、たまに MONO
        //   の登録ではなく、普通のブックマークの登録になってしまう
        //   こともあるようだが)
        char        host[MAX_URLLENGTH];
        const char  *pp;

        pp = strchr( (const char *)(p->editDlg->m_url) + 18, '/' );
        if ( pp ) {
            char    *qq;
            strncpy( host, p->editDlg->m_url, 64 );
            host[64] = NUL;
            qq = strchr( host + 18, '/' );
            if ( qq )
                *(qq + 1) = NUL;
            pp = qq;
        }
        if ( !pp )
            strcpy( host, "http://www.amazon.co.jp/" );

        p->editDlg->m_url =  host;
        p->editDlg->m_url += "gp/product/";
        p->editDlg->m_url += asin;
        p->editDlg->m_url += "/";
    }
    p->editDlg->m_enableCollection =
            p->rbParam.hatena.username[0] && asin[0] ? true : false;

    if ( p->rbParam.useTagSuggestion ) {
        // 当該 URL の Webページのタグ候補を抽出
        char    **tags;
        int     numOfTags    = 0;
        int     maxNumOfTags = 20;
        tags = (char **)malloc( maxNumOfTags * sizeof ( char * ) );
        if ( tags ) {
            ttle.LoadString(IDS_TTL_CONTINUE_ANALYSING);
            text.LoadString(IDS_TXT_CONTINUE_ANALYSING);
            p->procDlg->ChangeDialogText( ttle,     // タグ候補抽出中
                                          text );   // タグ候補抽出中……
            int i;
            for ( i = 0; i < maxNumOfTags; i++ ) {
                tags[i] = (char *)malloc( MAX_DESCRIPTION_LEN );
                if ( !(tags[i]) )
                    break;
                tags[i][0] = NUL;
                numOfTags++;
            }

            CString yahooAppID;
            yahooAppID.LoadString(IDS_BOOKEY_API_ID);
            extractTags( (const char *)(p->editDlg->m_url), tags, &hatenaTags,
                         &numOfTags, &stat1470net, (const char*)yahooAppID );

            for ( i = 0; i < numOfTags; i++ )
                *(p->editDlg->m_tag[i]) = tags[i][0] ? tags[i] : "";
            for ( i = maxNumOfTags; i > 0; i-- )
                free( tags[i - 1] );
            free( tags );
        }
    }

    if ( p->rbParam.useUsers ) {
        // 当該URL をブックマークしている人の数を取得
        ttle.LoadString(IDS_TTL_GETTING_BOOKMARK_USERS);
        text.LoadString(IDS_TXT_GETTING_HATENA_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ブックマーク登録者数取得中
                                      text );   // はてなブックマーク 調査中……
        p->editDlg->m_hbUsers = getUsersOfHatenaBookmark( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_DELICIOUS_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ブックマーク登録者数取得中
                                      text );   // del.icio.us 調査中……
        p->editDlg->m_deliciousUsers = getUsersOfDelicious(p->editDlg->m_url);

        if ( stat1470net ) {
            text.LoadString(IDS_TXT_GETTING_MMMEMO_USERS);
            p->procDlg->ChangeDialogText( ttle,  // ブックマーク登録者数取得中
                                          text );// MM/Memo 調査中……
            p->editDlg->m_mmUsers = getUsersOfMMmemo( p->editDlg->m_url,
                                                      &stat1470net );
        }

        text.LoadString(IDS_TXT_GETTING_ECNAVI_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ブックマーク登録者数取得中
                                      text );   // Buzzurl 調査中……
        p->editDlg->m_ecNaviUsers = getUsersOfECnaviClip( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_LIVEDOORCLIP_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ブックマーク登録者数取得中
                                      text );   // livedoorクリップ 調査中……
        p->editDlg->m_livedoorClipUsers = getUsersOfLivedoorClip( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_NIFTYCLIP_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ブックマーク登録者数取得中
                                      text );   // @niftyクリップ 調査中……
        p->editDlg->m_niftyClipUsers = getUsersOfNiftyClip( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_DIGG_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ブックマーク登録者数取得中
                                      text );   // digg 調査中……
        p->editDlg->m_diggUsers = getUsersOfDigg( p->editDlg->m_url );

        ttle.LoadString(IDS_TTL_GETTING_NUM_OF_STARS);
        text.LoadString(IDS_TXT_GETTING_HATENA_STAR_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ☆の数取得中
                                      text );   // はてなスター 調査中……
        char    buf[64];
        long    numOfHatenaStar = getHatenaStar( p->editDlg->m_url );
        p->editDlg->m_hatenaStarUsers = _T("(");
        p->editDlg->m_hatenaStarUsers += ltoa( numOfHatenaStar, buf, 10 );
        p->editDlg->m_hatenaStarUsers += _T(")");
    }

    if ( hatenaTags ) {
        free( hatenaTags );
        hatenaTags = NULL;
    }

    // (再登録実行時の)コメント、タグの取得
    if ( (p->rbParam.hatena.isTarget == TRUE) && (posted == TRUE) ) {
        char    title[MAX_DESCRIPTION_LEN];
        char    summary[MAX_DESCRIPTION_LEN];
        char    tags[MAX_DESCRIPTION_LEN];
        char    entryID[HASH_LENGTH + 1];

        title[0]   = NUL;
        summary[0] = NUL;
        tags[0]    = NUL;
        entryID[0] = NUL;
        if ( strchr( p->editDlg->m_url, '?' ) &&
             strchr( p->editDlg->m_url, '=' ) &&
             strchr( p->editDlg->m_url, '&' )    ) {
            char    temp[MAX_DESCRIPTION_LEN];
            strcpy( temp, p->editDlg->m_url );
            getBookmarkOnHatenaWithURI( p->rbParam.hatena.username,
                                        p->rbParam.hatena.password,
                                        escapeAmpersand( temp ),
                                        title, summary, tags, entryID );
        }
        else
            getBookmarkOnHatenaWithURI( p->rbParam.hatena.username,
                                        p->rbParam.hatena.password,
                                        encodeURLforHatena(p->editDlg->m_url),
                                        title, summary, tags, entryID );
        if ( summary[0] )
            p->editDlg->m_comment = summary;
        else if ((!(title[0]) || !strcmp( title, "はてなブックマーク" )) &&
                 (entryID[0] == NUL)                                       ) {
            getBookmarkViaEntryPageOnHatena(
                                        p->rbParam.hatena.username,
                                        p->editDlg->m_url,
                                        title, summary, tags );
            if ( summary[0] )
                p->editDlg->m_comment = summary;
        }
        if ( tags[0] )
            p->editDlg->m_tags = tags;
    }

    if ( (p->editDlg->m_comment.GetLength() >= 98)       ||
         ( (p->editDlg->m_comment.GetLength() == 0) &&
           (p->editDlg->m_tags.GetLength() == 0)       )    ) {
        char    title[MAX_DESCRIPTION_LEN];
        char    summary[MAX_DESCRIPTION_LEN];
        char    tags[MAX_DESCRIPTION_LEN];

        title[0]   = NUL;
        summary[0] = NUL;
        tags[0]    = NUL;

        if ( p->rbParam.livedoorClip.isTarget == TRUE )
            getBookmarkViaEntryPageOnLivedoor(
                                        p->rbParam.livedoorClip.username,
                                        p->editDlg->m_url,
                                        title, summary, tags );

        if ( summary[0] )
            p->editDlg->m_comment = summary;
        if ( tags[0] )
            p->editDlg->m_tags = tags;
    }

    SetUserAgent( FALSE );  /* User-Agent を元に戻す */
    return ( ret );
}

void
GetWebPageInfo( const RBparam_t    *p, 
                char               *accountName,
                EditBookmarkDialog *editDlg,
                ProceedingDialog   *procDlg )
{
    IWparam_t           param2;

    procDlg->ShowWindow( SW_SHOWNORMAL );

    memcpy( &param2.rbParam, p, sizeof ( RBparam_t ) );
    param2.accountName[0] = NUL;
    param2.editDlg        = editDlg;
    param2.procDlg        = procDlg;

    // Webページ情報取得スレッドを起動
    CWinThread  *tp = AfxBeginThread( InquiryWebPageInfo,
                                      (void *)&param2 );
    if ( tp ) {
        DWORD       exitCode  = 0;
        int         status;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        // Webページ情報取得スレッドが終了するのを待つ
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView の再描画
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog の再描画
                procDlg->SetFocus();
                procDlg->UpdateWindow();
                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        if ( param2.accountName[0] )
            strcpy( accountName, param2.accountName );

        delete tp;
    }

    procDlg->ShowWindow( SW_HIDE );
}

// ブックマーク登録スレッド
UINT
RegisterBookmark( LPVOID pParam )
{
    UINT        ret = 0;
    RBparam_t   *p  = (RBparam_t *)pParam;
    RBparam_t   param;

    // 安全のため、コピーしたものを使う
    memcpy( &param, p, sizeof ( RBparam_t ) );
    p = &param;

    EditBookmarkDialog  editDlg;
    ProceedingDialog    *procDlg = param.procDialog;
    char                accountName[32];

    // 登録しようとしているWebページに関する情報を取得(タイトル、タグ候補)
    accountName[0] = NUL;
    procDlg->ResetDialogText();
    procDlg->ShowWindow( SW_SHOWNORMAL );
    GetWebPageInfo( p, accountName, &editDlg, procDlg );

    if ( checkProxyInfo() )
        return ( ret );

    // 「評価」関連
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    if ( pp->m_newsing == true ) {
          /* newsing の ○×投票を利用する場合 */
        editDlg.m_affirmation = AFF_REQUESTED;
    }
    editDlg.m_evaluation = (pp->m_mmMemo       == true) ||
                           (pp->m_livedoorClip == true) ||
                           (pp->m_next1470net  == true)    ? EVL_REQUESTED
                                                           : EVL_NONE;
    // 「公開状態」関連
    /* Blue Dot の「公開状態」指定は将来対応とする */
    editDlg.m_public = (pp->m_blogPet      == true) /* ||
                       (pp->m_blueDot      == true) */
                                                    ? PUB_REQUESTED2 :
                       (pp->m_livedoorClip == true) ||
                       (pp->m_fc2bookmark  == true) ||
                       (pp->m_yjBookmark   == true)
                                                    ? PUB_REQUESTED
                                                    : PUB_EVERYONE;

    // 登録するか否かの設定を一時的に変更する目的で param を使用 {@@}
    editDlg.m_param = param;

    // コメント、タグの入力
    int r = editDlg.DoModal();
    if ( r == IDOK ) {
        if ( editDlg.m_url.GetLength() > 0 ) {
            // ブックマークの登録
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            p = &(editDlg.m_param); /* {@@} */
            pp->PutBookmarks( p, accountName, &editDlg, procDlg );
        }
        else {
            CString title;
            CString text;

            title.LoadString(IDS_TTL_URL_CHECK_RESULT);
            text.LoadString( IDS_TXT_INVALID_URL);
            text += editDlg.m_url;
            ::MessageBox( NULL,
                          text,
                          title,    // URL チェック結果
                          MB_OK|MB_ICONWARNING );
        }
    }

    procDlg->ShowWindow( SW_HIDE );

    return ( ret );
}


/*
 *  inputOpml.c
 *      OPML ファイルからブックマークを取り込む
 *          written by H.Tsujimura  17 Jan 2005 / 28 Sep 2005
 *
 * $Log: /comm/bookey/inputOpml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 18    07/03/03 22:13 Tsujimura543
 * FC2BOOKMARK の OPML ファイルが bookey で読み取れないとの指摘を
 * 受け、読めるようにしてみた
 * 
 * 17    06/12/08 15:37 Tsujimura543
 * getDateTimeFromDateString() を導入し、日時情報の解析を委ねることにする
 * 
 * 16    06/12/07 17:35 Tsujimura543
 * outputOPML() で「公開状態」を記録できるようにしたのに呼応して、
 * inputOPML() でも「公開状態」を読み取れるようにした
 * 
 * 15    06/11/17 19:42 Tsujimura543
 * コメントアウトにより無効化していた処理を削除
 * 
 * 14    06/11/17 19:40 Tsujimura543
 * outputOPML() の変更(MM/Memo形式の title を使うのをやめて、独自拡張属性
 * を使って「評価」を記録するようにした)のに呼応して、 inputOPML() でも独
 * 自拡張属性を扱える(読み取れる)ようにした
 * 
 * 13    06/11/14 15:45 Tsujimura543
 * unescapeURL() の実体を myClip.c へ移動
 * 
 * 12    06/10/26 23:31 Tsujimura543
 * メモリを破壊する可能性のある箇所を修正
 * 
 * 11    06/10/07 8:48 Tsujimura543
 * JST → GMT 変換処理の計算式が間違っていたのを修正
 * 
 * 10    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 9     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 8     06/07/24 19:10 Tsujimura543
 * リファクタリング
 * 
 * 7     06/07/24 19:05 Tsujimura543
 * '<outline text="' の直後に改行がある場合の救済措置を追加
 * 
 * 6     05/10/20 22:46 Tsujimura543
 * コメントが空のとき、ゴミが入ってしまっていた (修正済み)
 * 
 * 5     05/10/03 11:41 Tsujimura543
 * unescapeURL() 処理を追加
 * 
 * 4     05/10/03 11:21 Tsujimura543
 * inputOPML() して outputOPML() すると、日時が18時間未来方向にずれてしまう
 * 不具合を修正
 * 
 * 3     05/09/28 19:36 Tsujimura543
 * 外部変数へのアクセスを廃止
 * 
 * 2     05/09/28 18:27 Tsujimura543
 * ブックマーク登録日時の「秒」をファイルから読み忘れていたのを修正
 * 
 * 1     05/09/28 14:55 Tsujimura543
 * 最初の版(clipConverter.c から分離独立)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputOpml.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
inputOPML( int *numOfClips, FILE *fp )
{
    char    buf[65536], *p, *q;
    char    tmp[65536];
    char    *note;
    int     num = 1000; /* 暫定 */
    int     cnt = 0, block = 1;
    MyClip  *mp = NULL;
    MyClip  *newClip_p;
    int     rate;

    if ( !numOfClips )
        return ( mp );
    *numOfClips = 0;

    while ( ( p = fgets( buf, 65536 - 1, fp ) ) != NULL ) {
        while ( (*p == ' ') || (*p == '\t') )
            p++;
        if ( !strncmp( p, "</body>", 7 ) || !strncmp( p, "</opml>", 7 ) )
            break;
        if ( strncmp( p, "<outline ", 9 ) != 0 )
            continue;

        newClip_p = allocateMyClipIfNecessary( &mp, num, &block, cnt );
        if ( !newClip_p )
            break;
        mp = newClip_p;

        rate = 0;
        note = p;

        /* text [必須] */
        q = strstr( note, "text=\"" );
        if ( !q )
            continue;
        p = q + 6;
        q = strchr( p, '"' );
        while ( !q ) {
            /* '<outline text="' の直後に改行がある場合の救済措置 */
            p = fgets( buf, 65536 - 1, fp );
            if ( !p )
                break;
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            q = strchr( p, '"' );
            if ( q )
                note = q;
        }
        if ( !p )
            break;
        if ( q ) {
            strncpy( mp[cnt].title, p, q - p );
            mp[cnt].title[q - p] = '\0';
            p = q + 1;

            // MM/Memo 形式の title を扱うための処理
            rate = getEvaluation( mp[cnt].title, UTF8 );
        }

        /* url [必須] */
        q = strstr( note, "url=\"" );
        if ( q ) {
            q += 5;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( tmp, q, p - q );
                tmp[p - q] = '\0';
                strcpy( mp[cnt].url, unescapeURL( tmp ) );
                p++;
            }
            else
                p = q;
        }

        /* title [必須] */
        q = strstr( note, "title=\"" );
        if ( q ) {
            q += 7;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( mp[cnt].tags, q, p - q );
                mp[cnt].tags[p - q] = NUL;
                p++;
            }
            else
                p = q;
        }

        /* notes [必須] */
        q = strstr( note, "notes=\"" );
        if ( q ) {
            q += 7;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( mp[cnt].comment, q, p - q );
                mp[cnt].comment[p - q] = '\0';
                p++;
            }
            else
                p = q;
        }

        /* date [必須] */
        q = strstr( note, "date=\"" );
        if ( q ) {
            q += 6;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( tmp, q, p - q );
                tmp[p - q] = '\0';
                getDateTimeFromDateString( tmp,
                                           &(mp[cnt].yyyy),
                                           &(mp[cnt].mm),
                                           &(mp[cnt].dd),
                                           &(mp[cnt].HH),
                                           &(mp[cnt].MM),
                                           &(mp[cnt].SS) );
                p++;
            }
            else
                p = q;
        }

        /* 以下は bookey 独自拡張 */
        /* evaluation [optional] */
        q = strstr( note, "evaluation=\"" );
        if ( q ) {
            q += 12;
            mp[cnt].evaluation = atol( q );
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }
        if ( mp[cnt].evaluation == 0 )
            if ( rate > 0 )
                mp[cnt].evaluation = rate;

        /* rating [optional] */
        q = strstr( note, "rating=\"" );
        if ( q ) {
            q += 8;
            mp[cnt].rating = atol( q );
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }

        /* affirmation [optional] */
        q = strstr( note, "affirmation=\"" );
        if ( q ) {
            q += 13;
            if ( !strncmpi( q, "good", 4 ) )
                mp[cnt].affirmation = AFF_GOOD;
            else if ( !strncmpi( q, "bad", 3 ) )
                mp[cnt].affirmation = AFF_BAD;
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }

        /* publication [optional] */
        q = strstr( note, "publication=\"" );
        if ( q ) {
            q += 13;
            if ( !strncmpi( q, "friends", 7 ) )
                mp[cnt].publication = PUB_FRIENDS;
            else if ( !strncmpi( q, "private", 7 ) )
                mp[cnt].publication = PUB_PRIVATE;
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }

        cnt++;
    }
    if ( fp == stdin ) {
        clearerr( fp );
    }

    *numOfClips = cnt;

    return ( mp );
}


/*
 * 参考
 *  FC2BOOKMARK の出力する OPML の例
 *
 *     <?xml version="1.0" encoding="UTF-8"?>
 *     <opml version="1.1">
 *       <head>
 *         <title>fc2 bookmark</title>
 *       </head>
 *       <body>
 *         <outline url="http://watcher.moe-nifty.com/memo/2005/10/bookey.html#c12284852" text="[観] ソーシャルブックマーク管理ツール (コメント欄)" type="link" notes="あー、そうなんですか。どちらかというと、(経緯を考えると)FC2BOOKMARK側が合わせて欲しいんですが、属性の順序に依存する実装はよくないので、修正します。" date="2007-03-03T11:22:23Z" title="bookey"/>
 *       </body>
 *     </opml>
 *
 * http://bookmark.fc2.com/help/show/4#opml-is
 *  > FC2BookmarkからエクスポートされるOPMLのデータ構造は、ソーシャル
 *  > ブックマーク管理ツールbookey と同じ形式になります。
 * と書いてあるから、てっきり bookey の OPML 形式と同じだと思ってた
 * んだけど違ってました。 orz
 *
 * http://watcher.moe-nifty.com/memo/2005/10/bookey.html#c12284852
 *  > FC2からエクスポートしたOPMLは属性の順序が違うので読めないようです。
 *  > HTML形式もあるので問題はないのですが、
 *  > http://bookmark.fc2.com/help/show/4 で紹介されていますし
 *  > XMLの読み込みは何らかのライブラリを利用した方が良いかと思います。
 *  > 重要度は低くて構いません。
 *  > 投稿者: ksuzu (2007.03.03 午後 12:26)
 *
 * http://bookmark.fc2.com/help/show/4 の件
 * リファラの解析で上記、FC2 の解説ページの存在は知ってましたが、
 * FC2BOOKMARK の方でわざわざ bookey に合わせてくれたものだと理解して
 * ました。今回の問題が発覚したということは FC2側で自分たちの生成した
 * OPML ファイルを「bookey で実際に読み込んでみる試験」とかはしてない
 * ということですよね。 確認せずに、「bookey と同じ形式になります」と
 * 書かれても困っちゃいます。
 *
 * と言ってるだけでは詮無いので、 bookey 側で対応すべきところは対応し
 * ます。
 *
 * OPML の形式に関していえば、 bookey は outline 要素は text 属性から
 * 始まることを前提にしてるんだけど、FC2BOOKAMRKは url 属性から始まっ
 * ています。属性の出現順序に依存するのはよくないと言われればそれはそ
 * うなので、bookey 側で対応します。
 *
 * ただし、FC2BOOKMARK の方にも問題があり、type="Link" が入っていませ
 * ん。RSS リーダ向けの OPML ではなく、ブックマーク(というかリンク集)
 * 向けのOPML であることを明示するためにも type="Link" は入れて欲しい
 * と思います。
 *
 * bookey の取り扱う OPML の例 (一部分)
 *    <outline text="naoyaグループ - naoyaの日記 -  OPML" type="Link" url="http://naoya.g.hatena.ne.jp/naoya/20061030/1162194825" title="OPML" notes="この記事、見落としてた。はてブに関して、OPMLでのエクスポートを検討してたけど、やめちゃった、という話。結局、html/RSS/Atom の3本立てになっちゃったけど、RSS と Atom はどっちか片方だけでよかったような。" date="2006-12-25T07:54:00Z" />
 *    <outline text="asahi.com： ヒョウ柄の新種の深海魚見つかる - サイエンス" type="Link" url="http://www.asahi.com/science/news/OSK200611110026.html" title="fish 新種" notes="小型の魚ではなく、これほど大型で、かつ目立つ模様を持つ魚が、これまで発見されなかったのは驚きだ" date="2006-12-21T09:05:07Z" evaluation="3" />
 *
 * つまり、RSSリーダの OPML ファイル(type="rss")とは type が違う(わざ
 * と変えてる)ので、livedoor Reader や Bloglines の OPML ファイルを読
 * み込ませようとしても、無視します。
 *
 * 以下、Bloglines の OPML の例 (一部分)
 *    <outline title="100SHIKI" text="100SHIKI" htmlUrl="http://www.100shiki.com/" type="rss" xmlUrl="http://www.100shiki.com/index.xml" />
 *
 *                                                    (2007/03/03 記)
 */

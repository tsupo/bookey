/*
 *  outputOpml.c
 *      ブックマークを OPML ファイルとして出力する
 *          written by H.Tsujimura  17 Jan 2005 / 26 Sep 2005
 *
 * $Log: /comm/bookey/outputOpml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 23    08/11/25 19:25 Tsujimura543
 * escapeQuote() を修正、この段階でまだ '<' および '>' がエンコードされて
 * いない場合は、escapeQuote() にてエンコードするようにする
 * 
 * 22    08/11/11 17:29 Tsujimura543
 * &shy; に関する暫定対応
 * 
 * 21    07/04/20 17:07 Tsujimura543
 * escapeQuote() を修正、エスケープする必要のある & があればエスケープ
 * するようにした
 * 
 * 20    07/03/26 23:16 Tsujimura543
 * ローカルOPML登録時にメモリ破壊が発生する可能性のある箇所を発見、
 * 修正を実施
 * 
 * 19    06/12/07 17:26 Tsujimura543
 * 「公開状態」が「全員に公開」以外の場合は、「公開状態」を記録するように
 * した
 * 
 * 18    06/11/17 16:53 Tsujimura543
 * getEvaluation() を導入。MM/Memo 形式の title を正規化(他のソーシャル
 * ブックマークにインポートしても不自然にならない形式に変換)するようにして
 * みた
 * 
 * 17    06/11/16 13:55 Tsujimura543
 * タグの総バイト数(タグとタグを区切る文字を含む)が512バイトより大きいと、
 * クラッシュする不具合に対処
 * 
 * 16    06/11/14 16:50 Tsujimura543
 * ローカル時間と UTC の時差を 9時間固定(=日本時間)ではなく、
 * _timezone の値を使うようにした
 * 
 * 15    06/10/07 6:38 Tsujimura543
 * タイトルも escapeQuote() を通すようにする
 * 
 * 14    06/10/07 6:08 Tsujimura543
 * コメントのみ escapeQuote() を通すようにしてみた
 * 
 * 13    06/10/07 5:25 Tsujimura543
 * " を &quot; に変換するようにした
 * 
 * 12    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 11    06/07/13 18:23 Tsujimura543
 * regularize() を追加。XML としては invalid な OPML を吐き出す可能性を
 * 減らしてみた
 * 
 * 10    06/06/23 19:42 Tsujimura543
 * escapeURL() 内の buf[] のサイズも念のために増やしておく
 * 
 * 9     06/06/23 18:03 Tsujimura543
 * outputOPML() 内の comment[] のサイズを増やす (for Flog)
 * 
 * 8     06/05/08 17:11 Tsujimura543
 * &amp; を &amp;amp; に変換してしまうのを抑制するようにした
 * 
 * 7     05/10/20 21:39 Tsujimura543
 * JST → GMT 変換式の誤りを修正 (9 * 24 * 24 → 9 * 60 * 60)
 * 
 * 6     05/10/03 11:20 Tsujimura543
 * (1) codeChange が UTF8 のときに、「コメント」が正しく出力されない不具合
 * (2) 日時が18時間未来になってしまう不具合
 * を各々修正
 * 
 * 5     05/09/30 23:39 Tsujimura543
 * ブックマークのコメントを出力し忘れていた (デグレード)
 * 
 * 4     05/09/30 17:41 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 3     05/09/28 19:41 Tsujimura543
 * 外部変数へのアクセスを廃止
 * 
 * 2     05/09/28 13:13 Tsujimura543
 * #define 部分を myClip.h に移動
 * 
 * 1     05/09/28 12:07 Tsujimura543
 * ブックマーク切り出しツールのソースから切り出し(分離独立)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/outputOpml.c 1     09/05/14 3:48 tsupo $";
#endif

static char *
escapeURL( const char *url )
{
    const char  *p;
    char        *q;
    static char buf[4096];

    p = url;
    q = buf;
    while ( *p ) {
        if ( (*p == '&') && (strncmp( p + 1, "amp;", 4 ) != 0) ) {
            *q++ = '&';
            *q++ = 'a';
            *q++ = 'm';
            *q++ = 'p';
            *q++ = ';';
            p++;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    return ( buf );
}

static char *
escapeQuote( const char *url )
{
    const char  *p, *pp;
    char        *q;
    static char buf[4096];

    p = url;
    q = buf;
    while ( *p ) {
        if ( *p == '"' ) {
            *q++ = '&';
            *q++ = 'q';
            *q++ = 'u';
            *q++ = 'o';
            *q++ = 't';
            *q++ = ';';
            p++;
        }
        else if ( *p == '<' ) {
            *q++ = '&';
            *q++ = 'l';
            *q++ = 't';
            *q++ = ';';
            p++;
        }
        else if ( *p == '>' ) {
            *q++ = '&';
            *q++ = 'g';
            *q++ = 't';
            *q++ = ';';
            p++;
        }
        else if ( (*p == '&') &&
                  (((pp = strchr( p + 1, ';' )) == NULL) || (pp - p > 9)) ) {
            *q++ = '&';
            *q++ = 'a';
            *q++ = 'm';
            *q++ = 'p';
            *q++ = ';';
            p++;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    return ( buf );
}


char    *
regularize( char *p )
{
    char            *q, *r;
    unsigned char   code;

    while ( (( q = strstr( p, "&#039;" ) ) != NULL) ||
            (( q = strstr( p, "&#39;"  ) ) != NULL)    ) {
        *q = '\'';
        r = strchr( q, ';' );
        strcpy( q + 1, r + 1 );
    }

    while ( ( q = strstr( p, "&raquo;-&raquo;" ) ) != NULL ) {
        *q++ = ' ';
        *q++ = '-';
        *q++ = ' ';
        strcpy( q, q + 12 );
    }

    while ( ( q = strstr( p, "&raquo;" ) ) != NULL ) {
        code = 187;
        *q++ = (unsigned char)(((code & 0x07C0) >> 6) | 0xC0);
        *q++ = (unsigned char)(( code & 0x003F)       | 0x80);
        strcpy( q, q + 5 );
    }
    while ( ( q = strstr( p, "&laquo;" ) ) != NULL ) {
        code = 171;
        *q++ = (unsigned char)(((code & 0x07C0) >> 6) | 0xC0);
        *q++ = (unsigned char)(( code & 0x003F)       | 0x80);
        strcpy( q, q + 5 );
    }

    while ( ( q = strstr( p, "&shy;" ) ) != NULL ) {
        code = 173;
        *q++ = (unsigned char)(((code & 0x07C0) >> 6) | 0xC0);
        *q++ = (unsigned char)(( code & 0x003F)       | 0x80);
        strcpy( q, q + 3 );
    }

    return ( p );
}

void
outputOPML(
        const MyClip *mp,
        int          numOfClips,
        const char   *title,
        int          codeChange,
        FILE         *fp
    )
{
    int         i;
    int         rate;
    char        buf[BUFSIZ];
    char        tag[4096];
    char        comment[4096];

    struct tm   tm, *tt;
    time_t      t;
    int         yyyy, mm, dd, HH, MM, SS;
    char        *p = NULL;

    /* OPML ファイル書き出し */
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
    fprintf( fp,
             "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
             "<opml version=\"1.1\">\n<head>\n"
             "<title>%s</title>\n",
             p ? p : title );
    fprintf( fp, "</head>\n<body>\n" );

    for ( i = 0; i < numOfClips; i++ ) {
        switch ( codeChange ) {
        case SJIS2UTF:
         // p = sjis2utf( mp[i].title );
         // strcpy( buf, p ? p : mp[i].title );
            p = sjis2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = sjis2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case EUC2UTF:
         // p = euc2utf( mp[i].title );
         // strcpy( buf, p ? p : mp[i].title );
            p = euc2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = euc2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case UTF8:
        default:
         // strcpy( buf, mp[i].title );
            strcpy( tag, mp[i].tags );
            strcpy( comment, mp[i].comment );
            break;
        }

        // MM/Memo 形式の title を扱うための処理
        strcpy( buf, mp[i].title );
        rate = getEvaluation( buf, UTF8 );

        regularize( buf );
        regularize( tag );
        regularize( comment );

        tm.tm_year = mp[i].yyyy - 1900;
        tm.tm_mon  = mp[i].mm - 1;
        tm.tm_mday = mp[i].dd;
        tm.tm_hour = mp[i].HH;
        tm.tm_min  = mp[i].MM;
        tm.tm_sec  = mp[i].SS;
        t = timelocal( &tm );
#ifdef  WIN32
        if ( _timezone != 0 )
            t += _timezone;
#else
        t -= 9 * 60 * 60;   /* JST → GMT */
#endif

        tt = gmtime( &t );
        if ( !tt )
            tt = localtime( &t );
        if ( tt ) {
            yyyy = tt->tm_year + 1900;
            mm   = tt->tm_mon + 1;
            dd   = tt->tm_mday;
            HH   = tt->tm_hour;
            MM   = tt->tm_min;
            SS   = tt->tm_sec;
        }
        else {
            yyyy = mp[i].yyyy;
            mm   = mp[i].mm;
            dd   = mp[i].dd;
            HH   = mp[i].HH;
            MM   = mp[i].MM;
            SS   = mp[i].SS;
        }

        strcpy( buf, escapeQuote( buf ) );
        fprintf( fp,
                 "<outline text=\"%s\" type=\"Link\" "
                 "url=\"%s\" title=\"%s\" notes=\"%s\" "
                 "date=\"%04d-%02d-%02dT%02d:%02d:%02dZ\"",
                 buf,
                 escapeURL( mp[i].url ),
                 tag,
                 escapeQuote( comment ),
                 yyyy, mm, dd, HH, MM, SS );

        // 以下は bookey 独自拡張 [OPML 1.0 の仕様書を読む限りは、独自に属性を
        //                         追加するのは問題なさそう]
        //   -- 2006年11月17日現在、OPML validator は Internal database error
        //      が発生して利用できない(新しいデータベースでサービス再開するま
        //      で待っていてください、云々と表示される)ため、本当に valid なの
        //      かどうかは未確認
        if ( ((rate >= EVL_ONE)  &&
              (rate <= EVL_FIVE)    )             ||
             ((mp[i].evaluation >= EVL_ONE)  &&
              (mp[i].evaluation <= EVL_FIVE)    )    )
            fprintf( fp,
                     " evaluation=\"%d\"",
                     mp[i].evaluation );
        if ( (mp[i].rating >= RAT_ONE) && (mp[i].rating <= RAT_THREE) )
            fprintf( fp,
                     " rating=\"%d\"",
                     mp[i].rating );
        if ((mp[i].affirmation == AFF_GOOD) || (mp[i].affirmation == AFF_BAD))
            fprintf( fp,
                     " affirmation=\"%s\"",
                     mp[i].affirmation == AFF_GOOD ? "good" : "bad" );

        if ( mp[i].publication != PUB_EVERYONE ) {
            switch ( mp[i].publication ) {
            case PUB_FRIENDS:
                fprintf( fp, " publication=\"friends\"" );
                break;
            case PUB_PRIVATE:
                fprintf( fp, " publication=\"private\"" );
                break;
            }
        }

        fputs( " />\n", fp );
#ifdef  _DEBUG
        fprintf( stderr, "%d) %s (URL: %s)\n",
                 i + 1, utf2sjis(buf),
                 mp[i].url );
#endif
    }

 // fprintf( fp, "</body>\n</opml>\n" );
    fputs( "</body>\n</opml>\n", fp );
}

/** \note
 *  以下、OPML に関するメモ
 *      <a href="http://www.opml.org/" target="_blank">Outline Processor Markup Language</a>
 *      <a href="http://www.opml.org/spec" target="_blank">OPML 1.0 Specification</a>
 *      <a href="http://www.opml.org/2006/03/04#a278" target="_blank">OPML 2.0 draft spec</a>
 *      <a href="http://validator.opml.org/" target="_blank">OPML Validator Beta</a>
 *      <a href="http://hail2u.net/documents/opml_spec.html" target="_blank">OPML 1.0 Specificationの勝手な日本語訳</a>
 *      <a href="http://naoya.g.hatena.ne.jp/naoya/20061030/1162194825" target="_blank">naoyaグループ - naoyaの日記 - OPML</a>
 *      <a href="http://ja.wikipedia.org/wiki/OPML" target="_blank">Outline Processor Markup Language - Wikipedia</a>
 */
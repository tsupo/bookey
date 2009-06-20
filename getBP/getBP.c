/*
 * clip saver <<getBP>>
 *
 *      BlogPeople IB → OPML 変換出力プログラム
 *          written by H.Tsujimura  23 Jun 2005
 *
 * $Log: /comm/bookey/getBP/getBP.c $
 * 
 * 1     09/05/14 4:23 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 20    07/01/18 13:40 Tsujimura543
 * 英語モード対応
 * 
 * 19    06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 18    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 17    05/11/02 13:09 Tsujimura543
 * BPIB というタグを強制的に付加するのをやめる
 * 
 * 16    05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 15    05/09/30 17:42 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 14    05/09/28 20:42 Tsujimura543
 * 外部変数へのアクセスを廃止
 * 
 * 13    05/09/28 13:53 Tsujimura543
 * getIB() をブックマーク管理ツールから呼び出せるようにした
 * 
 * 12    05/09/27 18:29 Tsujimura543
 * コードを整理
 * 
 * 11    05/09/26 20:50 Tsujimura543
 * outputOPML() を getBPT のものと統一
 * 
 * 10    05/09/26 20:36 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備 (bug修正)
 * 
 * 9     05/09/26 20:18 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備 (つづき)
 * 
 * 8     05/09/26 20:10 Tsujimura543
 * struct myClip のメンバ tag を tags に名称変更
 * 
 * 7     05/09/26 20:04 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備
 * 
 * 6     05/09/26 19:53 Tsujimura543
 * struct myClip のメンバ catrgory を tag に名称変更
 * 
 * 5     05/09/26 19:38 Tsujimura543
 * 変換結果を標準エラー出力に表示するのはデバッグビルド時のみにした
 * 
 * 4     05/09/26 18:55 Tsujimura543
 * 少しだけリファクタリング (まだまだリファクタリングの余地ありまくり)
 * 
 * 3     05/09/26 18:45 Tsujimura543
 * 生成する OPML ファイルの title を BlogPeople Instant Bookmarks にした
 * 
 * 2     05/06/27 14:18 Tsujimura543
 * 本ツールと clcoo を連携させて、del.icio.us にインポートできることを確認
 * 
 * 1     05/06/23 19:52 Tsujimura543
 * 最初の版
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBP/getBP.c 1     09/05/14 4:23 tsupo $";
#endif

/* BlogPeople IB に登録済みのブックマークを取得する方法は、
 * 以下のものがある
 *  (1) 管理画面の html ファイルを解析して情報を抽出
 *  (2) blog 表示用の Javascript を取得、解析して情報を抽出
 *  (3) RSS を取得、解析して情報を抽出
 *  (4) OPML を取得、解析して情報を抽出
 *  (5) PHP でインクルードできる形式 (実体は html) を取得、解析して情報を抽出
 *
 * なお、
 *      (1) の方法は、ブックマーク登録日時が「月/日 時:分」のため「年」が不明
 *      (3) の RSS ファイルには「分類」(dc:subject) が含まれないこととソートさ
 *      れている順が不明(登録日時順でもないし、URL の abc 順でもない)
 *      (4) の OPML ファイルにも「分類」が含まれないことと、ソートされている順
 *      が不明(登録日時順でもないし、URL の abc 順でもない)
 *      (2) ～ (5) は URL が BlogPeolpe のリダイレクタ経由のものになっている
 * といった欠点がある
 *
 *      ※ (3)、(4) のソート順は、まず、「分類」でソートした後、登録日時順(古
 *         いものから新しいものへの順番)でソートされている模様 (管理画面からの
 *         設定により、逆順(新着のものから古いものへ)にソートすることも可能)
 * 
 * 以上を踏まえ、(5) の html を取得し、解析、情報抽出するという方法を採用する
 */


#define MAX_NUMBER_OF_IB    100 /* BlogPeople IB は最大100件 */

MyClip  *
getIB( const char *ibID, int *numOfClips )
{
    char    *response;
    char    url[MAX_URLLENGTH];
    char    tmp[BUFSIZ * 2];
    char    *p, *q, *r;
    int     maxNum = MAX_NUMBER_OF_IB;
    int     yyyy, mm, dd, HH, MM, num;
    MyClip  *mp = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 20;

    *numOfClips = num = 0;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    sprintf( url, "http://www.blogpeople.net/display/usr/ib/%s.html", ibID );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    p = http_get( url, response );
    if ( !p || !(*p) || !(*response) ) {
        free( response );
        return ( mp );
    }

    mp = (MyClip *)malloc( sizeof ( MyClip ) * maxNum );
    if ( mp ) {
        char    tag[80];
        char    *t = sjis2utf( "title=\"更新日:" );
        int     tlen = strlen( t );

        memset( mp, 0x00, sizeof ( MyClip ) * maxNum );
        p = response;
        tag[0] = NUL;
        while ( *p ) {
            if ( !strncmp( p, "<span class=\"blogpeople-linklist\">", 34 ) ) {
                q = p + 34;
                r = strstr( q, "</span>" );
                if ( r ) {
                    strncpy( tag, q, r - q );
                    tag[r - q] = NUL;
                    p = r + 7;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p,
            "<a href=\"http://www.blogpeople.net/cgi-bin/ib_click.cgi?u=http",
                           62 ) ) {
                q = p + 58;
                r = strstr( q, "\" " );
                if ( r ) {
                    strncpy( tmp, q, r - q );
                    tmp[r - q] = NUL;
                    strcpy( mp[num].url, decodeURL( tmp ) );
                    p = r + 2;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p, t, tlen ) ) {
                q = p + tlen;
                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                yyyy = 2000 + (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                mm   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                dd   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                HH   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                while ( *q && ((*q < '0') || (*q > '9')) )
                    q++;
                MM   = (*q - '0') * 10 + (*(q + 1) - '0');
                q += 2;

                mp[num].yyyy = yyyy;
                mp[num].mm   = mm;
                mp[num].dd   = dd;
                mp[num].HH   = HH;
                mp[num].MM   = MM;
                mp[num].SS   = 0;

                p = q + 20;

                r = strchr( q, '>' );
                if ( r ) {
                    r++;
#ifdef  _DEBUG
                    if ( tag[0] ) {
                        if ( !strstr( tag, "BPIB" ) )
                            strcat( tag, " BPIB" );
                    }
                    else
                        strcpy( tag, "BPIB" );
#endif  /* _DEBUG */
                    strcpy( mp[num].tags, tag );

                    q = strstr( r, "</a>" );
                    if ( q ) {
                        strncpy( mp[num].title, r, q - r );
                        mp[num].title[q - r] = NUL;
                        p = q + 4;
                    }

                    num++;
                    if ( num >= maxNum )
                        break;
                }

                continue;
            }

            p++;
        }
    }

    free( response );
    *numOfClips = num;

    return ( mp );
}

#ifdef  GET_BLOGPEOPLE_IB_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *IBIDForBlogPeople,
        BOOL *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'd':
                    if ( argv[i][j + 1] ) {
                        strcpy( IBIDForBlogPeople, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( IBIDForBlogPeople, argv[i] );
                        j = strlen( argv[i] ) - 1;
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
                 "getBP: BlogPeople IB → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tBlogPeople IB から吸い出した内容を OPML ファイルとして"
                 "出力する\n" );
        fprintf( stderr,
                "    getBP [-x] -d 16進16桁のID\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
        fprintf( stderr,
                 "\t16進16桁のID: BlogPeople IB の「基本設定」の「11.コード"
                 "の生成」\n\tでOPMLを生成したときの URL に含まれる16進16桁"
                 "の文字列部分のこと\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getBP: get bookmarks from BlogPeople IB, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getBP [-x] -d hashcode\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
        fprintf( stderr,
                 "\thashcode: Visit the web page of BlogPeople IB - \"11. "
                 "Generate\n\t\tcode\" - \"Configure Base Settings\", "
                 "generate OPML code,\n\t\tand get hashcode as 16 columns of "
                 "HEX string from this OPML\n\t\tcode.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    ibID[MAX_USERIDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( ibID, 0x00, MAX_USERIDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, ibID, &useProxy );

    if ( !(ibID[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* BlogPeople IB へ登録済みのブックマークを取得 */
    mp = getIB( ibID, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  BlogPeople IB 情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips,
                    "BlogPeople Instant Bookmarks", UTF8, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLOGPEOPLE_IB_EXE */

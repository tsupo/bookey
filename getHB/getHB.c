/*
 * clip saver <<getHB>>
 *
 *      はてなブックマーク → OPML 変換出力プログラム
 *          written by H.Tsujimura  26 Sep 2005
 *
 * $Log: /comm/bookey/getHB/getHB.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    08/11/28 17:03 Tsujimura543
 * getHB() 内にリトライ処理を追加
 * 
 * 14    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 13    07/01/17 22:59 Tsujimura543
 * 英語モード対応
 * 
 * 12    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 11    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 10    05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 9     05/10/25 14:10 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 8     05/10/03 23:06 Tsujimura543
 * NUM_OF_INFO_PER_HATENA_API の #define を myClip.h に移す
 * 
 * 7     05/10/03 22:54 Tsujimura543
 * リファクタリングを実施
 * 
 * 6     05/09/30 17:42 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 5     05/09/28 22:22 Tsujimura543
 * 外部変数へのアクセスを廃止
 * 
 * 4     05/09/28 13:30 Tsujimura543
 * getHB() をブックマーク管理ツールから呼び出せるようにした
 * 
 * 3     05/09/27 18:30 Tsujimura543
 * コードを整理
 * 
 * 2     05/09/26 20:55 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備
 * 
 * 1     05/09/26 18:47 Tsujimura543
 * 最初の版 (動作確認済み)
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getHB/getHB.c 1     09/05/14 3:48 tsupo $";
#endif


/* はてなブックマーク に登録済みのブックマークを取得する方法は、
 * 以下のものがある
 *  (1) http://b.hatena.ne.jp/ユーザ名 を取得、解析して情報を抽出
 *      (さらに過去に遡ってブックマークを取得・抽出)
 *  (2) はてなブックマーク Atom API (FeedURI への GET) を使って自分のブック
 *      マークを取得
 *  (3) はてなブックマーク REST API を使って指定ユーザのブックマークを取得
 *
 * (2) は「最近」のブックマークしか取得できないため、本ツールでは (3) を使う
 * ことにする。
 */

MyClip  *
getHB( const char *hatenaID, int *numOfClips )
{
    int             max    = 1000; /* 暫定 */
    int             cnt    = 0;
    int             block  = 1;
    long            num    = NUM_OF_INFO_PER_HATENA_API, n;
    long            offset = 0;
    BOOL            more   = TRUE;
    HATENA_BOOKMARK posts[NUM_OF_INFO_PER_HATENA_API];
    MyClip          *mp    = NULL;
    int             retry  = 0;

    *numOfClips = 0;

    do {
        long    i;
        MyClip  *newClip_p;

        num = NUM_OF_INFO_PER_HATENA_API;
        n = getRecentPostsOnHatenaUser(hatenaID, offset, &num, posts, &more);
        if ( n <= 0 ) {
            if ( more == TRUE ) {
                retry++;
                if ( retry < 5 ) {
                    Sleep( 2000 );
                    continue;
                }
            }
            break;
        }
        retry = 0;

        for ( i = 0; i < n; i++ ) {
            newClip_p = allocateMyClipIfNecessary( &mp, max, &block, cnt );
            if ( !newClip_p ) {
                more = FALSE;
                break;
            }
            mp = newClip_p;

            strcpy( mp[cnt].comment, posts[i].summary );
            strcpy( mp[cnt].tags,    posts[i].tags );
            strcpy( mp[cnt].title,   posts[i].title );
            strcpy( mp[cnt].url,     posts[i].href );
            mp[cnt].yyyy = posts[i].yyyy;
            mp[cnt].mm   = posts[i].mm;
            mp[cnt].dd   = posts[i].dd;
            mp[cnt].HH   = posts[i].HH;
            mp[cnt].MM   = posts[i].MM;
            mp[cnt].SS   = posts[i].SS;

            cnt++;
        }
        offset += n;
    } while ( more == TRUE );

    *numOfClips = cnt;

    return ( mp );
}

#ifdef  GET_HATENA_BOOKMARK_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForHatena,
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
                        strcpy( usernameForHatena, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForHatena, argv[i] );
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
                 "getHB: はてなブックマーク → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tはてなブックマークから吸い出した内容を OPML ファイルと"
                 "して出力する\n");
        fprintf( stderr,
                 "    getHB [-x] -u ユーザ名\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getHB: get bookmarks from 'Hatena Bookmark', and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getHB [-x] -u username\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    hatenaID[MAX_USERIDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( hatenaID, 0x00, MAX_USERIDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, hatenaID, &useProxy );

    if ( !(hatenaID[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* はてなブックマークへ登録済みのブックマークを取得 */
    mp = getHB( hatenaID, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  はてなブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "Hatena Bookmark", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_HATENA_BOOKMARK_EXE */

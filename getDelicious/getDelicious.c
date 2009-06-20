/*
 * clip saver <<getDelicious>>
 *
 *      del.icio.us → OPML 変換出力プログラム
 *          written by H.Tsujimura  2 Jun 2005 / 27 Sep 2005
 *
 * History:
 * $Log: /comm/bookey/getDelicious/getDelicious.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 16    08/07/25 0:36 Tsujimura543
 * private saving に対応
 * 
 * 15    07/04/16 16:44 Tsujimura543
 * リファクタリング
 * 
 * 14    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 13    07/01/17 21:46 Tsujimura543
 * 英語モード対応
 * 
 * 12    06/10/07 1:57 Tsujimura543
 * http 応答受信待ちタイムアウト時間をブックマーク数に比例して設定する
 * ことで、ブックマーク数が多い場合でも全ブックマークの取得に成功する
 * 可能性を高めてみた
 * 
 * 11    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 10    06/07/20 19:02 Tsujimura543
 * del.icio.us からの「取得」時、取得に失敗した場合、全何件中の何件までは
 * 取得
 * に成功したか、ダイアログで表示するようにした
 * 
 * 9     06/07/20 14:58 Tsujimura543
 * getDelicious() の呼び出し側で、あらかじめ全部で何件あるか調査した後で、
 * getDelicious() を呼び出すような状況に備えて、第3引数を (O) から (I/O)
 * に変更した
 * 
 * 8     06/06/20 15:54 Tsujimura543
 * 「コメント」中に含まれる改行(\r,\n)を取り除くようにした
 * 
 * 7     05/10/20 16:07 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 6     05/09/30 17:42 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 5     05/09/28 21:06 Tsujimura543
 * 外部変数へのアクセスを廃止
 * 
 * 4     05/09/28 13:35 Tsujimura543
 * getDelicious() をブックマーク管理ツールから呼び出せるようにした
 * 
 * 3     05/09/27 18:26 Tsujimura543
 * コードを整理
 * 
 * 2     05/09/27 16:33 Tsujimura543
 * 変換結果を標準エラー出力に表示するのはデバッグビルド時のみにした
 * 
 * 1     05/09/27 16:31 Tsujimura543
 * 最初の版(d2hb のソースを元に作成。API を他のブックマーク取得関数に合わせる)
 */

#define  USE_DELICIOUS_POSTS
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getDelicious/getDelicious.c 1     09/05/14 3:48 tsupo $";
#endif

MyClip  *
deliciousPosts2MyClip( DELICIOUS_POSTS *posts, int numOfPosts )
{
    MyClip  *mp;
    int     i;
    char    *s, *t;

    mp = (MyClip *)malloc( sizeof ( MyClip ) * numOfPosts );
    if ( !mp )
        return ( mp );

    for ( i = 0; i < numOfPosts; i++ ) {
        strcpy( mp[i].title,   posts[i].description );
        strcpy( mp[i].tags,    posts[i].tag );
        strcpy( mp[i].url,     posts[i].href );
        strcpy( mp[i].comment, posts[i].extended );

        s = mp[i].comment;
        while ( ((t = strchr( s, '\n' )) != NULL) ||
                ((t = strchr( s, '\r' )) != NULL)    ) {
            if ( (*(t + 1) == '\r') || (*(t + 1) == '\n') )
                strcpy( t, t + 1 );
            *t = ' ';
        }

        getDateTimeFromDateString( posts[i].dateTime,
                                   &(mp[i].yyyy), &(mp[i].mm), &(mp[i].dd),
                                   &(mp[i].HH), &(mp[i].MM), &(mp[i].SS) );

        if ( posts[i].shared == FALSE )
            mp[i].publication = PUB_PRIVATE;
    }

    return ( mp );
}

MyClip  *
getDelicious(
        const char *usernameForDelicious,   /* (I)   ユーザ名         */
        const char *passwordForDelicious,   /* (I)   パスワード       */
        int        *numOfClips              /* (I/O) ブックマーク件数 */
    )
{
    long            n, num, numOfPosts = 0;
    DELICIOUS_POSTS *posts;
    MyClip          *mp = NULL;

    n = *numOfClips;
    *numOfClips = 0;

    /* del.icio.us のブックマークを取得 */
    if ( n == 0 )
        num = getNumberOfBookmarksOnDelicious( usernameForDelicious,
                                               passwordForDelicious );
    else
        num = n;
    if ( num <= 0 )
        return ( mp );
    Sleep( 1000 );

    numOfPosts = num;
    posts = (DELICIOUS_POSTS *)
                malloc( sizeof ( DELICIOUS_POSTS ) * numOfPosts );
    if ( !posts )
        return ( mp );
    memset( posts, 0x00, sizeof ( DELICIOUS_POSTS ) * numOfPosts );

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * (numOfPosts / 100) );
                        // ブックマーク総数に比例したタイムアウト時間を設定
    n = getAllPostsOnDelicious( usernameForDelicious,
                                passwordForDelicious,
                                NULL,
                                &numOfPosts,
                                posts );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT );    // デフォルト値に戻しておく
    if ( n <= 0 ) {
        free( posts );
        return ( mp );
    }

    mp = deliciousPosts2MyClip( posts, n );
    if ( mp )
        *numOfClips = n;
    free( posts );

    return ( mp );
}

#ifdef  GET_DELICIOUS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForDelicious,
        char *passwordForDelicious,
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
                        strcpy( usernameForDelicious, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForDelicious, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForDelicious, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForDelicious, argv[i] );
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
                 "getDelicious: del.icio.us → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "    getDelicious [-x] -u ユーザ名 -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getDelicious: get bookmarks from del.icio.us, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getDelicious [-x] -u username -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    usernameForDelicious[MAX_USERIDLEN + 1];
    char    passwordForDelicious[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( usernameForDelicious, 0x00, MAX_USERIDLEN );
    memset( passwordForDelicious, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  usernameForDelicious, passwordForDelicious, &useProxy );

    if ( !(usernameForDelicious[0]) || !(passwordForDelicious[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* del.icio.us登録済みのブックマークを取得 */
    mp = getDelicious( usernameForDelicious, passwordForDelicious,
                       &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /*  del.icio.us情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "del.icio.us", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_DELICIOUS_EXE */

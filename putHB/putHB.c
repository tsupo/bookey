/*
 * clip loader <<putHB>>
 *
 *      OPML → はてなブックマーク 登録プログラム
 *          written by H.Tsujimura  2 Jun 2005 / 28 Sep 2005
 *
 * History:
 * $Log: /comm/bookey/putHB/putHB.c $
 * 
 * 2     09/06/18 0:53 tsupo
 * 0.63b版
 * 
 * 19    09/06/16 21:46 Tsujimura543
 * 「コレクション」の登録時のみ、private(非公開)で投稿できることを確認
 * (はてなブックマークプラスを使っている場合)
 * -- 通常のブックマークは API による private 指定方法が不明(不可能?)
 * -- なため、今後の課題とする
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 18    07/11/12 19:16 Tsujimura543
 * any2sjisEx() を導入、Shift_JIS なのに EUC-JP だと誤認するケースに対処
 * 
 * 17    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 16    07/02/16 16:19 Tsujimura543
 * コメントを修正
 * 
 * 15    07/02/16 16:16 Tsujimura543
 * すでに登録されているタイトルと登録しようとしているタイトルが食い違う場
 * 合は、登録しようとしているタイトルで上書きするか、すでに登録されている
 * タイトルをそのまま流用するか、選択できるようにした
 * 
 * 14    07/01/23 16:42 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 13    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 12    07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 11    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 10    06/07/24 19:22 Tsujimura543
 * 登録しようとしているWebページの title の先頭が改行の場合、改行部分を
 * 捨てて、残りの部分を titile として採用するようにした
 * 
 * 9     06/06/28 21:06 Tsujimura543
 * コメントに改行が含まれる場合、取り除いてから登録するようにした
 * 
 * 8     06/05/22 15:30 Tsujimura543
 * 登録実行時の Sleep() のタイミング、sleepする時間の長さを調整
 * 
 * 7     06/04/06 22:16 Tsujimura543
 * 「コレクション」の登録(追加)に対応した
 * 
 * 6     05/10/25 14:22 Tsujimura543
 * メッセージボックスのタイトルと本文の文言が逆になっていたのを修正
 * 
 * 5     05/10/25 14:12 Tsujimura543
 * 標準エラー出力が対話に利用可能かどうかを調査する方法を修正
 * 
 * 4     05/10/20 21:13 Tsujimura543
 * 入力の文字コードが Shift_JIS, EUC-JP, UTF-8 のどれでもいいようにした
 * 
 * 3     05/10/19 17:23 Tsujimura543
 * ブックマーク登録失敗時の「リトライするかどうかの質問」処理を変更
 * 
 * 2     05/10/11 18:02 Tsujimura543
 * 第3引数に const 修飾子を付加
 * 
 * 1     05/09/28 23:44 Tsujimura543
 * 新規作成(d2hb.c からはてなブックマークへの登録処理を切り出し、汎用化)
 */

#include "myClip.h"
#include "hatenaAPI.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putHB/putHB.c 2     09/06/18 0:53 tsupo $";
#endif

typedef struct paramPutHB   {
    const char      *userName;
    const char      *password;
    HATENA_BOOKMARK *entries;
}   PARAM_HB;

BOOL
_putHB(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    BOOL            ret      = FALSE;
    PARAM_HB        *param   = (PARAM_HB *)(args->args);
    HATENA_BOOKMARK *entries = param->entries + args->index;
    char            *p;
    char            title[1024];

    errorString[0] = NUL;

    strcpy( entries->href, mp->url );

    p = any2sjisEx( entries->title, mp->title );
    while ( p && ((*p == '\r') || (*p == '\n')) )
        p++;
    strcpy( entries->title, p ? p : mp->title );

    p = any2sjisEx( entries->summary, mp->comment );
    while ( p && (((p = strchr(entries->summary, '\r')) != NULL) ||
                  ((p = strchr(entries->summary, '\n')) != NULL)   ) )
        strcpy( p, p + 1 ); /* 改行を取り除く */

    any2sjisEx( entries->tags, mp->tags );

    memset( title, 0x00, 1024 );
    entries->entryID[0] = NUL;

    if ( mp->asin )
        ret = postBookmarkWithCollectionOnHatena(
                    param->userName, param->password,
                    entries->href,
                    title,
                    entries->summary,
                    entries->tags,
                    mp->publication == PUB_PRIVATE ? TRUE : FALSE,
                    entries->entryID );
    else
        ret = postBookmarkOnHatena(
                    param->userName, param->password,
                    entries->href,
                    title,
                    entries->summary,
                    entries->tags,
                    mp->publication == PUB_PRIVATE ? TRUE : FALSE,
                    entries->entryID );

    if ( (ret == TRUE) &&
         title[0] && !strcmp( title, entries->title ) ) {
        strcpy( entries->entryID, "0" );    /* title を登録し直す必要なし */
    }

    return ( ret );
}

void
putHB(
        const char   *userName,  /* (I) はてなID                       */
        const char   *password,  /* (I) パスワード                     */
        BOOL         useMyTitle, /* (I) タイトルを独自に設定するか否か */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    )
{
    int             ret, i;
    int             n = numOfClips;
    HATENA_BOOKMARK *entries;
    PARAM_HB        param;

    entries = (HATENA_BOOKMARK *)malloc( sizeof ( HATENA_BOOKMARK ) * n );
    if ( !entries )
        return;
    memset( entries, 0x00, sizeof ( HATENA_BOOKMARK ) * n );

    /* はてなブックマークに登録 */
    param.entries  = entries;
    param.userName = userName;
    param.password = password;
    putBookmarks( getLanguageCode() == 0x0411
                   ? "はてなブックマーク"
                   : "Hatena Bookmark",
                  mp, numOfClips, NULL, 0, &param, _putHB );

    if ( useMyTitle ) {
        /* ブックマークの title 要素をオリジナルに合わせる */
        for ( i = 0; i < n; i++ ) {
            if ( atol( entries[i].entryID ) == 0 )
                continue;
            Sleep( 2000 );
            ret = editBookmarkOnHatena(
                        userName, password,
                        entries[i].href,
                        entries[i].title,
                        entries[i].summary,
                        entries[i].tags,
                        entries[i].entryID );
        }
    }

    free( entries );
}


#ifdef  PUT_HATENA_BOOKMARK_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForHatena,
        char *passwordForHatene,
        BOOL *useMyTitle,
        BOOL *useProxy,
        FILE **fp
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

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForHatene, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForHatene, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;

                case 'F':
                    *useMyTitle = !(*useMyTitle);
                    break;

                case 'i':
                    if ( argv[i][j + 1] ) {
                        FILE    *gp = fopen( &(argv[i][j + 1]), "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s が見つかりません\n"
                                      : "%s: Not found.\n",
                                     &(argv[i][j + 1]) );
                            exit( 255 );
                        }
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        FILE    *gp = fopen( argv[i + 1], "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s が見つかりません\n"
                                      : "%s: Not found.\n",
                                     argv[i + 1] );
                            exit( 255 );
                        }
                        i++;
                        j = strlen( argv[i] ) - 1;
                    }
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
        fprintf( stderr, "putHB: OPML → はてなブックマーク 登録ツール\n" );
        fprintf( stderr,
         "    putHB [-x] [-F] -u はてなID -p パスワード [-i OPMLファイル名]"
         "\n" );
        fprintf( stderr,
         "\t-x: proxy を使う\n"
         "\t-F: すでに登録されているタイトルと登録しようとしているタイトル\n"
         "\t    が食い違う場合は、登録しようとしているタイトルで上書きする\n"
         "\t    (はてなブックマークでは、タイトルは全員で共有しています。\n"
         "\t     上書きするかどうかは慎重に判断して決めてください)\n"
         "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n");
    }
    else {
        // 英語
        fprintf( stderr,
      "putHB: read bookmarks from OPML, and put them into Hatena Bookmark\n" );
        fprintf( stderr,
      "    putHB [-x] [-F] -u hatenaID -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-F: overwrite entry title, if original title was different from\n"
      "\t    your specified title\n"
      "\t    (Caution: entry title is shared by all users of Hatena Bookmark)"
      "\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    usernameForHatena[MAX_USERIDLEN + 1];
    char    passwordForHatena[MAX_PASSWDLEN + 1];
    BOOL    useProxy   = FALSE;
    BOOL    useMyTitle = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( usernameForHatena, 0x00, MAX_USERIDLEN );
    memset( passwordForHatena, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  usernameForHatena, passwordForHatena,
                  &useMyTitle, &useProxy, &fp );

    if ( !(usernameForHatena[0]) || !(passwordForHatena[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを はてなブックマーク に登録 */
        putHB( usernameForHatena, passwordForHatena, useMyTitle,
               mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_HATENA_BOOKMARK_EXE */

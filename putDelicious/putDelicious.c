/*
 * clip loader <<putDelicious>>
 *
 *      OPML → del.icio.us 登録プログラム
 *          written by H.Tsujimura  17 Jan 2005 / 27 Sep 2005
 *
 * History:
 * $Log: /comm/bookey/putDelicious/putDelicious.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 17    08/07/25 0:37 Tsujimura543
 * private saving に対応
 * 
 * 16    07/11/12 19:09 Tsujimura543
 * any2sjisEx() を導入、Shift_JIS なのに EUC-JP だと誤認するケースに対処
 * 
 * 15    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
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
 * 11    06/11/16 19:31 Tsujimura543
 * デバッグ用の(デバッグビルド時のみ有効な)コードを削除
 * 
 * 10    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 9     06/08/17 11:50 Tsujimura543
 * リトライ時、念のために Sleep() を入れてみた
 * 
 * 8     05/10/25 14:22 Tsujimura543
 * メッセージボックスのタイトルと本文の文言が逆になっていたのを修正
 * 
 * 7     05/10/25 14:12 Tsujimura543
 * 標準エラー出力が対話に利用可能かどうかを調査する方法を修正
 * 
 * 6     05/10/20 21:13 Tsujimura543
 * 入力の文字コードが Shift_JIS, EUC-JP, UTF-8 のどれでもいいようにした
 * 
 * 5     05/10/19 17:23 Tsujimura543
 * ブックマーク登録失敗時の「リトライするかどうかの質問」処理を変更
 * 
 * 4     05/10/11 18:02 Tsujimura543
 * 第3引数に const 修飾子を付加
 * 
 * 3     05/09/28 23:09 Tsujimura543
 * usage() を修正
 * 
 * 2     05/09/28 19:37 Tsujimura543
 * putDelicious() の仕様(引数の数、戻り値の型)を変更
 * 
 * 1     05/09/28 18:30 Tsujimura543
 * clipConverter.c から del.icio.us へのインポート処理を切り出す
 */

#include "myClip.h"
#include "delicious.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDelicious/putDelicious.c 1     09/05/14 3:48 tsupo $";
#endif

typedef struct paramPutDeli {
    const char  *userName;
    const char  *password;
}   PARAM_DELI;

BOOL
_putDelicious(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    PARAM_DELI      *param = (PARAM_DELI *)(args->args);
    DELICIOUS_ENTRY entry;
    BOOL            ret = FALSE;

    errorString[0] = NUL;

    if ( mp->url[0] == NUL )
        return ( ret ); // 正常終了扱い

    any2sjisEx( entry.description, mp->title );
    any2sjisEx( entry.extended,    mp->comment );
    any2sjisEx( entry.tag,         mp->tags );

    strcpy( entry.url,         mp->url );
    sprintf( entry.dateTime,
             "%04d-%02d-%02dT%02d:%02d:%02dZ",
             mp->yyyy, mp->mm, mp->dd,
             mp->HH, mp->MM, mp->SS );

    entry.shared = (mp->publication == PUB_PRIVATE) ? FALSE : TRUE;

    ret = postEntryOnDelicious( param->userName, param->password, &entry );

    return ( ret );
}

void
putDelicious(
        const char   *userName2,
        const char   *password2,
        const MyClip *mp,
        int          numOfClips
    )
{
    PARAM_DELI  param;

    param.userName = userName2;
    param.password = password2;

    putBookmarks( "del.icio.us", mp, numOfClips, NULL, 0, &param,
                  _putDelicious );
}

#ifdef  PUT_DELICIOUS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForDelicious,
        char *passwordForDelicious,
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
        fprintf( stderr, "putDelicious: OPML → del.icio.us 登録ツール\n" );
        fprintf( stderr,
     "    putDelicious [-x] -u ユーザ名 -p パスワード [-i OPMLファイル名]\n");
        fprintf( stderr,
     "\t-x: proxy を使う\n"
     "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
   "putDelicious: read bookmarks from OPML, and put them into del.icio.us\n");
        fprintf( stderr,
   "    putDelicious [-x] [-u username] [-p password] [-i OPMLfilename]\n" );
        fprintf( stderr,
   "\t-x: use http access via proxy server\n"
   "\t-i: If this option is not specified, read from standard input\n"
   "\t    instead of OPML\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    usernameForDelicious[MAX_USERIDLEN + 1];
    char    passwordForDelicious[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( usernameForDelicious, 0x00, MAX_USERIDLEN );
    memset( passwordForDelicious, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  usernameForDelicious, passwordForDelicious,
                  &useProxy, &fp );

    if ( !(usernameForDelicious[0]) || !(passwordForDelicious[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを del.icio.us に登録 */
        putDelicious( usernameForDelicious, passwordForDelicious,
                      mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_DELICIOUS_EXE */

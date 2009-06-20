/*
 * clip loader <<putBlueDot>>
 *
 *      OPML → Blue Dot 登録プログラム
 *          written by H.Tsujimura  6 Oct 2006
 *
 * History:
 * $Log: /comm/bookey/putDelicious/putBlueDot.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     08/07/25 0:37 Tsujimura543
 * private saving に対応
 * 
 * 8     07/11/12 19:09 Tsujimura543
 * any2sjisEx() を導入、Shift_JIS なのに EUC-JP だと誤認するケースに対処
 * 
 * 7     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 6     07/01/23 16:42 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 5     07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 4     07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 3     06/11/16 19:31 Tsujimura543
 * デバッグ用の(デバッグビルド時のみ有効な)コードを削除
 * 
 * 2     06/10/07 8:50 Tsujimura543
 * Blue Dot に投稿するときのタイムスタンプは PDT だとみなされて処理される
 * ことがわかったので、対策を施してみた
 * 
 * 1     06/10/07 1:07 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#include "delicious.h"
#include "blueDot.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDelicious/putBlueDot.c 1     09/05/14 3:48 tsupo $";
#endif

typedef struct paramPutBD   {
    const char  *userName;
    const char  *password;
}   PARAM_BD;


BOOL
_putBlueDot(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    PARAM_BD        *param = (PARAM_BD *)(args->args);
    DELICIOUS_ENTRY entry;
    time_t          t;
    struct tm       tm, *tt;
    BOOL            ret = FALSE;

    errorString[0] = NUL;

    if ( mp->url[0] == NUL )
        return ( ret ); // 正常終了扱い

    any2sjisEx( entry.description, mp->title );
    any2sjisEx( entry.extended,    mp->comment );
    any2sjisEx( entry.tag,         mp->tags );

    strcpy( entry.url, mp->url );

    // Blue Dot の時間は PST(PDT)
    //  -- GMT → PDT 変換
    tm.tm_year = mp->yyyy - 1900;
    tm.tm_mon  = mp->mm - 1;
    tm.tm_mday = mp->dd;
    tm.tm_hour = mp->HH;
    tm.tm_min  = mp->MM;
    tm.tm_sec  = mp->SS;

    t = timelocal( &tm );
    t += 7 * 60 * 60;   /* GMT との時差 */
    tt = gmtime( &t );

    sprintf( entry.dateTime,
             "%04d-%02d-%02dT%02d:%02d:%02dZ",
             tt->tm_year + 1900, tt->tm_mon + 1, tt->tm_mday,
             tt->tm_hour, tt->tm_min, tt->tm_sec );

    entry.shared = (mp->publication == PUB_PRIVATE) ? FALSE : TRUE;

    ret = postEntryOnBlueDot( param->userName, param->password, &entry );

    return ( ret );
}

void
putBlueDot(
        const char   *userName2,
        const char   *password2,
        const MyClip *mp,
        int          numOfClips
    )
{
    PARAM_BD    param;

    param.userName = userName2;
    param.password = password2;

    putBookmarks( "Blue Dot", mp, numOfClips, NULL, 0, &param, _putBlueDot );
}

#ifdef  PUT_BLUEDOT_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
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
                        strcpy( username, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
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
        fprintf( stderr,
                 "putBlueDot: OPML → Blue Dot 登録ツール\n" );
        fprintf( stderr,
     "    putBlueDot [-x] -u Blue Dot ユーザ名 -p Blue Dot パスワード\n"
     "               [-i OPMLファイル名]\n" );
        fprintf( stderr,
     "\t-x: proxy を使う\n"
     "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putBlueDot: read bookmarks from OPML, and put them into Blue Dot\n" );
        fprintf( stderr,
      "    putBlueDot [-x] -u username -p password [-i OPMLfilename]\n" );
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
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを Blue Dot に登録 */
        putBlueDot( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_BLUEDOT_EXE */

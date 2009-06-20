/*
 * putBookmarks.c
 *      ブックマーク登録処理メインループ
 *          written by H.Tsujimura  17 Oct 2005 / 18 Jan 2007
 *
 * $Log: /comm/bookey/putBookmarks.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 3     07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 2     07/01/18 23:45 Tsujimura543
 * 引数を変更。当該ブックマーク独自の引数郡を(構造体へのポインタ渡しで)
 * 指定できるようにした
 * 
 * 1     07/01/18 17:20 Tsujimura543
 * 新規作成 (各ブックマークサービスへの登録処理のうち、共通化できる部分を
 * 抽出)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBookmarks.c 1     09/05/14 3:48 tsupo $";
#endif

void
putBookmarks(
        const char   *bookmarkName,
        const MyClip *mp,
        int          numOfClips,
        char         *cookie,
        size_t       cookieSize,
        void         *args,
        int (__cdecl *func)( const MyClip *mp,
                             char         *errorString,
                             PARAM_PBM    *args )
    )
{
    char        *request;
    char        *response;
    BOOL        retry;
    int         ret, i;
    size_t      sz = MAX_CONTENT_SIZE * 20;
    char        errorString[BUFSIZ];
    PARAM_PBM   param;
    LCID        l = getLanguageCode();

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return;
    }

    param.cookie     = cookie;
    param.cookieSize = cookieSize;
    param.request    = request;
    param.response   = response;
    param.sz         = sz;
    param.args       = args;

    for ( i = 0; i < numOfClips; i++ ) {
        /* ブックマークへ登録 */
        if ( (numOfClips == 1) || (i < numOfClips - 1) )
            Sleep( 2000 );
        do {
            retry = FALSE;
            param.index    = i;
            errorString[0] = NUL;
            memset( request, 0x00, MAX_CONTENT_SIZE );
            setUpReceiveBuffer( response, sz );
            ret = func( &mp[i], errorString, &param );
            if ( (ret == FALSE) || errorString[0] ) {
                int fd = fileno( stderr );
                if ( (fd >= 0) && isatty( fd ) ) {
                    int c;

                    if ( errorString[0] ) {
                        fprintf( stderr,
                                 l == 0x0411
                                  ? "%s: ブックマークの登録に失敗しました。\n"
                                    "  -- 理由: %s\n"
                                  : "%s: Cannot register bookmarks.\n"
                                    "  -- Reason: %s",
                                 bookmarkName,
                                 errorString );
                        break;/* 登録失敗だが、リトライしてもリカバリ不可能 */
                              /* だと思われるので、リトライせずに抜ける     */
                    }
                    fprintf( stderr,
                             l == 0x0411
                              ? "%s: ブックマークの登録に失敗しました。\n"
                                "もう一度、試しますか? (y/n) "
                              : "%s: Cannot register bookmarks.\n"
                                "Do you try again? (y/n)",
                                 bookmarkName );
#ifdef  WIN32
                    c = getch();
#else
                    do {
                        c = getchar();
                        if ( c == EOF )
                            clearerr( stdin );
                    }
                    while ( (c != 'y') && (c != 'Y') &&
                            (c != 'n') && (c != 'N')    );
#endif
                    if ( (c == 'y') || (c == 'Y') )
                        retry = TRUE;
                }
#ifdef  WIN32
                else {
                    char    message[BUFSIZ * 2];
                    int     r;

                    if ( errorString[0] ) {
                        sprintf( message,
                                 l == 0x0411
                                  ? "%s への登録に失敗しま"
                                    "した。  \r\n -- 理由: %s    "
                                  : "%s: Cannot register bookmarks."
                                    "    \r\n -- Reason: %s",
                                 bookmarkName,
                                 errorString );
                        r = MessageBox( NULL,
                                        message,
                                        l == 0x0411
                                         ? "登録失敗"
                                         : "Registration failure",
                                        MB_OK|MB_ICONERROR );
                    }
                    else {
                        sprintf( message,
                                 l == 0x0411
                                  ? "%s への登録に失敗しました。"
                                    "  \r\nもう一度、試しますか?"
                                  : "%s: Cannot register bookmarks."
                                    "    \r\nDo you try again?",
                                 bookmarkName );
                        r = MessageBox( NULL,
                                        message,
                                        l == 0x0411
                                         ? "登録失敗"
                                         : "Registration failure",
                                        MB_YESNO|MB_ICONERROR );
                    }
                    if ( r == IDYES )
                        retry = TRUE;
                    else if ( numOfClips > 1 ) {
                        r = MessageBox( NULL,
                                        l == 0x0411
                                         ? "登録を中断しますか?    "
                                         : "Do you discontinue registering?"
                                           "    ",
                                        l == 0x0411
                                         ? "登録続行確認"
                                         : "Confirmation of registration "
                                           "continuation",// この英語は変かも
                                        MB_YESNO|MB_ICONERROR );
                        if ( r == IDYES )
                            i = numOfClips + 1;
                    }
                }
#endif
            }
        } while ( retry == TRUE );

    }

    encodeURL( NULL );
    free( response );
    free( request  );
}

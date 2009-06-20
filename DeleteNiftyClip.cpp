/*
 *  DeleteNiftyClip.cpp
 *      ニフティクリップ ブックマーク 削除処理
 *          written by H.Tsujimura  12 Jul 2006
 *
 * $Log: /comm/bookey/DeleteNiftyClip.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 19    08/11/11 17:18 Tsujimura543
 * NUM_OF_INFO_PER_NIFTY_API の定義を niftyClip.h へ移動
 * 
 * 18    08/11/11 16:16 Tsujimura543
 * GetNiftyClipWithApiKey() を _getNiftyClipWithApiKey() に変更し、
 * getNiftyClip.c へ移管
 * 
 * 17    08/11/11 15:10 Tsujimura543
 * 「APIキーを使用して@niftyクリップから削除する」処理を追加、動作確認した
 * 
 * 16    08/03/17 18:10 Tsujimura543
 * getScreenNameOnNiftyClip() を導入。ソースを整理した
 * 
 * 15    08/03/12 5:05 Tsujimura543
 * 2008年3月11日の「@niftyクリップ」リニューアルに対応した
 * 
 * 14    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 13    07/01/19 18:25 Tsujimura543
 * _getNiftyClip() を導入、リファクタリングを実施
 * 
 * 12    07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 11    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 10    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 9     06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 8     06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() を導入。MyClipEx 構造体格納領域確保
 * 処理を共通関数化してみた
 * 
 * 7     06/08/26 1:53 Tsujimura543
 * もはやインクルード不要になったヘッダファイルのインクルードをやめた
 * 
 * 6     06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 5     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() を導入し、(削除用)ブックマーク情報取得処理を
 * 別スレッド化した
 * 
 * 4     06/08/22 17:21 Tsujimura543
 * 独自の構造体を廃止し、MyClipEx を導入
 * 
 * 3     06/07/12 15:05 Tsujimura543
 * 余分な処理を削除
 * 
 * 2     06/07/12 12:09 Tsujimura543
 * deleteEntryOnNiftyClip() 内で response を解放し忘れていた
 * 
 * 1     06/07/12 12:02 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"
#include "niftyClip.h"
#include "DeleteBookmarkDialog4.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteNiftyClip.cpp 1     09/05/14 3:48 tsupo $";
#endif


/*
 *  APIキーを使わない削除処理
 */

#define MAX_NIFTYCLIP_PER_BLOCK 200

MyClipEx    *
getNiftyClip2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        *response;
    long        num = 0;
    char        target[MAX_URLLENGTH];
    size_t      sz = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;
    int         total = 0;
    char        screenname[80];

    screenname[0] = NUL;
    *numOfClips   = 0;
    bookmarkName.LoadString( IDS_TGT_NIFTY_CLIP );

    // ニフティクリップ へログイン
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginNiftyClip( username, password, cookie ) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // ニフティクリップのトップページを取得し、ブックマークユーザ名を確定する
    // [注: ニフティクリップでは、ログインユーザ名(@nifty ID または PLEASY ID)
    //      とは別に、ブックマークユーザ名(screenname)を設定できる]
    target[0] = NUL;
    getScreenNameOnNiftyClip( screenname, target,
                              response, sz, cookie );
    if ( target[0] == NUL ) {
        free( response );
        return ( mp );
    }

    // ブックマークを取得
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……
    num = _getNiftyClip( target,
                         screenname[0] ? screenname : username,
                         cookie,
                         NULL, &mp, response, sz, &total );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnNiftyClip( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url, "http://clip.nifty.com/delete?bookmarkId=%s", mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}



/*
 *  APIキーを使う削除処理
 */

BOOL
deleteBookmarkOnNiftyClip(
        const char *apiKey, /* (I) APIキー     */
        const char *url     /* (I) 削除対象URL */
    )
{
    BOOL    ret = FALSE;
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *request;
    char    *response;

    request  = (char *)malloc( strlen( url ) * 6 + BUFSIZ );
    if ( !request )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    // APIキー + URL
    sprintf( request,
             "api_key=%s&"
             "url=%s&"
             "alt=xml",
             apiKey,
             encodeURL( url ) );

    setUpReceiveBuffer( response, sz );
    http_post( "http://api.clip.nifty.com/api/v1/clip/delete",
               "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        char    *p = strstr( response, "<message>OK</message>" );
        if ( p )
            ret = TRUE;
    }

    free( response );
    free( request );

    return ( ret );
}

void
DeleteNiftyClip(
        const char       *apiKey,
        bool             withQuery /* = true */,
        ProceedingDialog *dlg      /* = NULL */
    )
{
    CString title;
    CString text;

    if ( withQuery == false ) {
        title.LoadString(IDS_TTL_DELETE_ALL_BOOKMARKS);
        text.LoadString( IDS_TXT_DELETE_ALL_BOOKMARKS);
        int r = MessageBox( NULL,
                            text,   // 本当にブックマークを全部削除してしまっても構わないんですね?
                            title,  // ブックマーク削除確認
                            MB_YESNO|MB_ICONQUESTION );
        if ( r == IDNO )
            return;
    }

    CWaitCursor         cur;    // マウスカーソルを砂時計表示
    long                num, n, nn;
    long                offset;
    BOOL                more = TRUE;
    BOOL                ret;
    bool                executeDelete;
    ProceedingDialog    *pdlg;
    MyClip              *posts   = new MyClip[NUM_OF_INFO_PER_NIFTY_API];
    BOOL                *deleted = new BOOL[NUM_OF_INFO_PER_NIFTY_API];
    CString             bookmarkName;

    if ( !posts || !deleted ) {
        if ( posts )
            delete [] posts;
        if ( deleted )
            delete [] deleted;
        return;
    }

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }
    bookmarkName.LoadString( IDS_TGT_NIFTY_CLIP );

    offset = 0;
    do {
        // ブックマーク情報を取得
        text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
        pdlg->ShowWindow( SW_SHOWNORMAL );
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // ブックマーク情報取得中 ……

        num = NUM_OF_INFO_PER_NIFTY_API;
        nn  = 0;
        memset( posts, 0x00, sizeof ( MyClip ) * num );

        n = _getNiftyClipWithApiKey( apiKey, offset, &num, posts, &more );
        if ( n <= 0 )
            break;

        // ブックマークを1件づつ削除
        int     i;
        for ( i = 0; i < n; i++ )
            deleted[i] = FALSE;
        for ( i = 0; i < n; i++ ) {
            if ( deleted[i] == TRUE )
                continue;
            if ( withQuery ) {
                pdlg->ShowWindow( SW_HIDE );

                // ブックマーク情報を表示
                DeleteBookmarkDialog4   d;

                d.m_url     = posts[i].url;
                d.m_title   = posts[i].title;
                d.m_comment = posts[i].comment;
                d.m_tags    = posts[i].tags;
                d.m_enableToBackward = (i == 0) ? false : true;
                d.m_backToPrevious   = false;

                if ( i > 0 ) {
                    int j = i - 1;
                    while ( (j >= 0) && deleted[j] )
                        j--;
                    if ( j < 0 )
                        d.m_enableToBackward = false;
                }

                int r = d.DoModal();
                if ( r == IDCANCEL ) {
                    more = FALSE;
                    executeDelete = false;
                    break;
                }
                if ( d.m_backToPrevious ) {
                    int j = i;
                    while ( (--i > 0) && deleted[i] )
                        ;
                    if ( deleted[i] == FALSE ) {
                        i--;
                        continue;
                    }
                    i = j;
                }
                if ( d.m_executeWithoutQuery == true ) {
                    title.LoadString(IDS_TTL_DELETE_ALL);
                    text.LoadString( IDS_TXT_DELETE_ALL);
                    r = MessageBox( NULL,
                                    text,   // 残りのブックマークを全部一気に削除してしまっても構わないですね?
                                    title,  // ブックマーク一括削除確認
                                    MB_YESNO|MB_ICONQUESTION );
                    if ( r == IDYES )
                        withQuery = false;
                }
                if ( d.m_execute == false )
                    continue;
                executeDelete = d.m_execute;

                pdlg->ShowWindow( SW_SHOWNORMAL );
            }
            else
                executeDelete = true;

            // 削除を実行
            if ( executeDelete ) {
                text.LoadString(IDS_TXT_CONTINUE_DELETING);
                pdlg->ChangeDialogText( bookmarkName,
                                        text ); // ブックマーク削除中 ……
                ret = deleteBookmarkOnNiftyClip( apiKey, posts[i].url );
                if ( ret == FALSE ) {
                    int r;

                    title.LoadString(IDS_TTL_FAILURE_DELETE_BOOKMARKS);
                    text.LoadString( IDS_TXT_FAILURE_DELETE_BOOKMARKS);
                    r = MessageBox( NULL,
                                    text,   // ブックマークの削除に失敗しました    \r\n処理を続行しますか?
                                    title,  // ブックマーク削除失敗
                                    MB_YESNO|MB_ICONWARNING );
                    if ( r == IDYES )
                        continue;
                    break;
                }
                nn++;
                deleted[i] = TRUE;
            }
        }

        offset += (n - nn);
    } while ( more == TRUE );

    if ( !dlg )
        delete pdlg;
    delete [] deleted;
    delete [] posts;
}

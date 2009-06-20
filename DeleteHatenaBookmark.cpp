/*
 *  DeleteHatenaBookmark.cpp
 *      はてなブックマーク 削除処理
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteHatenaBookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    08/12/15 23:54 Tsujimura543
 * getRks() から static をはずした
 * 
 * 23    08/12/02 19:27 Tsujimura543
 * Visual C++ 2008 でのビルドチェック結果を反映
 * 
 * 22    08/11/28 17:05 Tsujimura543
 * getRecentPostsOnHatenaUser() の情報源を atomfeed から rss に変更
 * したのに伴う修正を実施
 * 
 * 21    08/11/28 10:53 Tsujimura543
 * API による削除が失敗した場合は deleteBookmarkOnHatenaWithURL()
 * を呼び出して、削除を試みるようにした
 * 
 * 20    08/07/25 1:30 Tsujimura543
 * ブックマーク削除後、前方に未削除のブックマークが残っていないとき
 * でも、「1個前に戻る」ボタンが有効なままになってしまう不具合を修正
 * 
 * 19    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 18    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 17    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 16    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 15    06/10/26 23:53 Tsujimura543
 * コメントを修正
 * 
 * 14    06/10/26 23:51 Tsujimura543
 * 「1個前に戻る」で戻りすぎてしまうことがある(消したはずのブックマークが
 * 表示される)不具合に対処
 * 
 * 13    06/09/04 18:15 Tsujimura543
 * 「1個前へ戻る」機能を追加
 * 
 * 12    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 11a   06/09/03 22:13 tsupo
 * ブックマークの削除に失敗した場合、いきなり処理を中断するのはやめて、処
 * 理を続行するかどうか尋ねるようにした
 * 
 * 11    06/08/25 18:17 Tsujimura543
 * DeleteHetanaBookmark() の引数を1個追加
 * 
 * 10    06/07/03 15:15 Tsujimura543
 * ProceedingDialog 絡みの改修 (ProceedingDialog の delete時に例外が
 * 発生することがある件の対策実施)
 * 
 * 9     06/06/22 14:56 Tsujimura543
 * 使っていない関数を削除
 * 
 * 8     06/06/19 20:31 Tsujimura543
 * m_pDlg->DestroyWindow(); をコメントアウト
 * 
 * 7     06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 6     05/11/11 0:03 Tsujimura543
 * 最初の削除実行後の「ブックマーク情報取得中」が表示されない不具合を修正
 * 
 * 5     05/11/10 21:21 Tsujimura543
 * 進行状況表示ダイアログを使うようにした
 * 
 * 4     05/10/11 19:08 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 3     05/10/03 23:06 Tsujimura543
 * NUM_OF_INFO_PER_HATENA_API の #define を myClip.h に移す
 * 
 * 2     05/10/03 22:59 Tsujimura543
 * はてなブックマークを削除する処理を実装
 * 
 * 1     05/10/03 21:03 Tsujimura543
 * ブックマーク削除処理の実装開始
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog4.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#include "hatenaApi.h"
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteHatenaBookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
char *
getRks( char *rks, const char *htmlSrcCode )
{
    const char  *p;
    const char  *q;
    const char  *r;

    rks[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"rks\" " );
    if ( p ) {
        r = strstr( p, "value=\"" );
        q = strstr( p, "/>" );
        if ( r && (r < q) ) {
            r += 7;
            q = strchr( r, '\"' );
            if ( q ) {
                strncpy( rks, r, q - r );
                rks[q - r] = NUL;
            }
        }
        else {
            while ( p > htmlSrcCode ) {
                p--;
                if ( !strncmp( p, "value=\"", 7 ) ) {
                    r = p + 7;
                    q = strchr( r, '\"' );
                    if ( q ) {
                        strncpy( rks, r, q - r );
                        rks[q - r] = NUL;
                    }
                    break;
                }
            }
        }
    }

    return ( rks );
}
#ifdef __cplusplus
}
#endif


BOOL
deleteBookmarkOnHatenaWithURL(
                const char *username,
                const char *password,
                const char *targetURL
            )
{
    BOOL    ret = FALSE;
    char    *cookie;

    cookie = new char[MAX_COOKIE_LEN];
    if ( !cookie )
        return ( ret );
    memset( cookie,  0x00, MAX_COOKIE_LEN );

    if ( loginHatenaBookmark( username, password, cookie ) ) {
        size_t  sz        = MAX_CONTENT_SIZE * 4;
        char    *url      = new char [strlen( targetURL ) * 3 + BUFSIZ ];
        char    *request  = new char [MAX_CONTENT_SIZE];
        char    *response = new char [sz];

        if ( url && request && response ) {
            sprintf( url,
                     "http://b.hatena.ne.jp/%s/add.delete?url=%s",
                     username, encodeURL( targetURL ) );
            setUpReceiveBuffer( response, sz );
            http_getEx( url, response, cookie );
            if ( *response ) {
                char    rks[MAX_KEYLENGTH];

                getRks( rks, response );
                sprintf( url,
                         "http://b.hatena.ne.jp/%s/add.delete",
                         username );
                sprintf( request,
                         "rks=%s&"
                         "url=%s",
                         rks, encodeURL( targetURL ) );
                setUpReceiveBuffer( response, sz );
                http_postEx( url, "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response )
                    ret = TRUE;
            }
        }

        if ( request )
            delete [] request;
        if ( response )
            delete [] response;
        if ( url )
            delete [] url;
    }

    delete [] cookie;

    return ( ret );
}

void    DeleteHetanaBookmark(
                const char       *username,
                const char       *password,
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
    HATENA_BOOKMARK     *posts   =
                            new HATENA_BOOKMARK[NUM_OF_INFO_PER_HATENA_API];
    BOOL                *deleted = new BOOL[NUM_OF_INFO_PER_HATENA_API];
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
    bookmarkName.LoadString( IDS_TGT_HATENA_BOOKMARK );

    offset = 0;
    do {
        // ブックマーク情報を取得
        text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
        pdlg->ShowWindow( SW_SHOWNORMAL );
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // ブックマーク情報取得中 ……

        num = NUM_OF_INFO_PER_HATENA_API;
        nn  = 0;
        memset( posts, 0x00,
                sizeof ( HATENA_BOOKMARK ) * NUM_OF_INFO_PER_HATENA_API );
        n = getRecentPostsOnHatenaUser(username, offset, &num, posts, &more);
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

                d.m_url     = posts[i].href;
                d.m_title   = posts[i].title;
                d.m_comment = posts[i].summary;
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
                ret = FALSE;
                if ( posts[i].entryID[0] )
                    ret = deleteBookmarkOnHatena( username, password,
                                                  posts[i].entryID );
                if ( ret == FALSE )
                    ret = deleteBookmarkOnHatenaWithURL( username, password,
                                                         posts[i].href );
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


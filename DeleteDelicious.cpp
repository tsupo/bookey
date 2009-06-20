/*
 *  DeleteDelicious.cpp
 *      del.icio.us 削除処理
 *          written by H.Tsujimura  3 Oct 2005
 *
 * $Log: /comm/bookey/DeleteDelicious.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 18    08/07/25 1:30 Tsujimura543
 * ブックマーク削除後、前方に未削除のブックマークが残っていないとき
 * でも、「1個前に戻る」ボタンが有効なままになってしまう不具合を修正
 * 
 * 17    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 16    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 15    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 14    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 13    06/10/26 23:53 Tsujimura543
 * コメントを修正
 * 
 * 12    06/10/26 23:51 Tsujimura543
 * 「1個前に戻る」で戻りすぎてしまうことがある(消したはずのブックマークが
 * 表示される)不具合に対処
 * 
 * 11    06/09/04 18:15 Tsujimura543
 * 「1個前へ戻る」機能を追加
 * 
 * 10    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 9a    06/09/03 22:13 tsupo
 * ブックマークの削除に失敗した場合、いきなり処理を中断するのはやめて、処
 * 理を続行するかどうか尋ねるようにした
 * 
 * 9     06/08/25 18:13 Tsujimura543
 * DeleteDeliciousBookmark() の引数を1個追加
 * 
 * 8     06/07/03 15:15 Tsujimura543
 * ProceedingDialog 絡みの改修 (ProceedingDialog の delete時に例外が
 * 発生することがある件の対策実施)
 * 
 * 7     06/06/20 14:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第9段階、終了
 * 
 * 6     06/06/19 20:31 Tsujimura543
 * m_pDlg->DestroyWindow(); をコメントアウト
 * 
 * 5     06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 4     05/11/10 21:21 Tsujimura543
 * 進行状況表示ダイアログを使うようにした
 * 
 * 3     05/10/11 19:08 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 2     05/10/03 22:17 Tsujimura543
 * del.icio.us のブックマークを削除する処理を実装
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
#include "delicious.h"
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteDelicious.cpp 1     09/05/14 3:48 tsupo $";
#endif

void
DeleteDeliciousBookmark(
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
    BOOL                ret;
    ProceedingDialog    *pdlg;
    CBookeyApp          *pp = (CBookeyApp *)AfxGetApp();
    CString             bookmarkName;

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }
    bookmarkName.LoadString( IDS_TGT_DELICIOUS );

    if ( (pp->m_bookmarkGotten == false)                   ||
         !(pp->m_myClip)                                   ||
         (pp->m_bookmarkName.Compare( bookmarkName ) != 0)    ) {
        // ブックマーク情報をまだ取得していない場合
        if ( pp->m_myClip ) {
            pp->m_bookmarkGotten = false;
            pp->m_bookmarkName   = "";
            free( pp->m_myClip );
            pp->m_myClip = NULL;
        }

        /// ブックマーク情報を取得
        pp->m_myClip = pp->m_delicious.GetBookmarks( pp->m_numOfClips,
                                                     username, password );
        if ( !(pp->m_myClip) ) {
            pdlg->ShowWindow( SW_HIDE );
            title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS);
            text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS);
            MessageBox( NULL,
                        text,   // ブックマーク情報を取得できませんでした
                        title,  // ブックマーク取得失敗
                        MB_OK|MB_ICONWARNING );
            if ( !dlg )
                delete pdlg;
            return;
        }

        pp->m_bookmarkGotten = true;
        pp->m_bookmarkName   = bookmarkName;
    }

    // ブックマークを1件づつ削除
    BOOL    *deleted = new BOOL[pp->m_numOfClips];
    int     i;
    for ( i = 0; i < pp->m_numOfClips; i++ )
        deleted[i] = FALSE;
    for ( i = 0; i < pp->m_numOfClips; i++ ) {
        if ( deleted[i] == TRUE )
            continue;
        if ( withQuery ) {
            pdlg->ShowWindow( SW_HIDE );

            // ブックマーク情報を表示
            DeleteBookmarkDialog4   d;

            d.m_url     = pp->m_myClip[i].url;
            d.m_title   = pp->m_myClip[i].title;
            d.m_comment = pp->m_myClip[i].comment;
            d.m_tags    = pp->m_myClip[i].tags;
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
            if ( r == IDCANCEL )
                break;
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

            pdlg->ShowWindow( SW_SHOWNORMAL );
        }

        text.LoadString(IDS_TXT_CONTINUE_DELETING);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // ブックマーク削除中 ……
        ret = deleteEntryOnDelicious(username, password, pp->m_myClip[i].url);
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
        deleted[i] = TRUE;
    }

    // ブックマーク情報を破棄
    delete [] deleted;
    pp->m_bookmarkGotten = false;
    pp->m_bookmarkName   = "";
    free( pp->m_myClip );
    pp->m_myClip = NULL;

    if ( !dlg )
        delete pdlg;
}

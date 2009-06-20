/*
 *  DeleteLocalOpml.cpp
 *      ローカルOPMLファイル ブックマーク 削除処理
 *          written by H.Tsujimura  26 Oct 2006
 *
 * $Log: /comm/bookey/DeleteLocalOpml.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     08/07/25 1:30 Tsujimura543
 * ブックマーク削除後、前方に未削除のブックマークが残っていないとき
 * でも、「1個前に戻る」ボタンが有効なままになってしまう不具合を修正
 * 
 * 7     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 6     07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 5     07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 4     07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 3     06/10/26 23:53 Tsujimura543
 * コメントを修正
 * 
 * 2     06/10/26 23:51 Tsujimura543
 * 「1個前に戻る」で戻りすぎてしまうことがある(消したはずのブックマークが
 * 表示される)不具合に対処
 * 
 * 1     06/10/26 22:37 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog4.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteLocalOpml.cpp 1     09/05/14 3:48 tsupo $";
#endif


/*
 *  ローカルOPMLファイル から指定ブックマークを削除する
 */

BOOL
deleteEntryOnLocalOpml(
        const char *filename,   /* (I) ローカルOPMLファイル名          */
        const char *url         /* (I) 削除対象ブックマーク(対象のURL) */
    )
{
    BOOL    ret  = FALSE;
    BOOL    done = FALSE;
    FILE    *fp, *gp;

    fp = fopen( filename, "r" );
    if ( fp ) {
        gp = tmpfile();
        if ( gp ) {
            char    *p, *q;
            char    buf[MAX_CONTENT_SIZE];

            while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
                q = strstr( p, url );
                if ( q && (*(q - 1) == '"') && (*(q + strlen(url)) == '"') )
                    continue;
                fputs( p, gp );
            }

            done = TRUE;
        }

        fclose( fp );

        if ( gp ) {
            if ( done ) {
                fp = fopen( filename, "w" );
                if ( fp ) {
                    char    *p;
                    char    buf[BUFSIZ];

                    rewind( gp );
                    while ( ( p = fgets( buf, BUFSIZ - 1, gp ) ) != NULL )
                        fputs( p, fp );

                    fclose( fp );
                    ret = TRUE;
                }
            }

            fclose( gp );
        }
    }

    return ( ret );
}


/*
 *  ローカルOPMLファイル から登録済みブックマークを削除する
 */

void
DeleteLocalOpml(
        const char       *filename,
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
        if ( r == IDYES )
            unlink( filename );
        return;
    }

    CWaitCursor         cur;    // マウスカーソルを砂時計表示
    BOOL                ret;
    CBookeyApp          *pp = (CBookeyApp *)AfxGetApp();
    ProceedingDialog    *pdlg;
    CString             bookmarkName;

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }
    bookmarkName.LoadString( IDS_TGT_LOCAL_OPML );

    text.LoadString(IDS_TXT_GET_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク取得準備中 ……
    if ( pp->m_myClip ) {
        pp->m_bookmarkGotten = false;
        pp->m_bookmarkName   = "";
        free( pp->m_myClip );
        pp->m_myClip = NULL;
    }
    pdlg->ShowWindow( SW_HIDE );

    /// ブックマーク情報を取得
    pp->m_myClip = pp->m_localOpml.GetBookmarks( pp->m_numOfClips );
    if ( !(pp->m_myClip) ) {
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

    pdlg->ShowWindow( SW_SHOWNORMAL );
    pp->m_bookmarkGotten = true;
    pp->m_bookmarkName   = bookmarkName;

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
            char                    *p;

            d.m_url     = pp->m_myClip[i].url;

            p = utf2sjis( pp->m_myClip[i].title );
            d.m_title   = p ? p : pp->m_myClip[i].title;

            p = utf2sjis( pp->m_myClip[i].comment );
            d.m_comment = p ? p : pp->m_myClip[i].comment;

            p = utf2sjis( pp->m_myClip[i].tags );
            d.m_tags    = p ? p : pp->m_myClip[i].tags;

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
        ret = deleteEntryOnLocalOpml( filename, pp->m_myClip[i].url );
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

/*
 *  DeleteDiigo.cpp
 *      Diigo ブックマーク 削除処理
 *          written by H.Tsujimura  25 Jul 2008
 *
 * $Log: /comm/bookey/DeleteDiigo.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/07/26 0:17 Tsujimura543
 * 新規作成 (今のところ、削除に成功していない)
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
char    *encodeURLforJSON( const char *url );
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteDiigo.cpp 1     09/05/14 3:48 tsupo $";
#endif


/*
 *  Diigo から指定ブックマークを削除する
 */

BOOL
deleteEntryOnDiigo(
        const char *username,   /* (I) ユーザ名                        */
        const char *password,   /* (I) パスワード                      */
        const char *url )       /* (I) 削除対象ブックマーク(対象のURL) */
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    targetUrl[MAX_URLLENGTH];
    int     sz = MAX_CONTENT_SIZE * 20;
    char    *URLforJSON = NUL;
    char    *urls  = NUL;
    char    *p;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    strcpy( targetUrl, "http://api2.diigo.com/bookmarks" );

    // URL
    URLforJSON = encodeURLforJSON( url );
#if 1
    sprintf( request,
             "[{\"url\":\"%s\"}]",
             URLforJSON );
    /* ↑ deleted: 0 bookmark が返ってくる (削除できない) */
#else
    sprintf( request,
             "[{\"%s\"}]",
             URLforJSON );
    /* ↑ API 仕様書に書いてあるやり方通り(のはず)
          なぜか 400 Bad Request になる            */
#endif

    urls = (char *)malloc( strlen( request ) * 8 + 1 );
    if ( urls ) {
        sprintf( urls, "urls=%s", encodeURL(request) );

        setUpReceiveBuffer( response, sz );
        http_deleteBASIC( targetUrl, username, password,
                          "application/x-www-form-urlencoded",
                          urls, response );
        if ( *response ) {
            p = strstr( response, "deleted" );
            if ( p )
                ret = TRUE; /* 削除成功 */
        }

        free( urls );
    }

    if ( URLforJSON )
        free( URLforJSON );

    free( response );
    free( request );

    return ( ret );
}


/*
 *  Diigo から登録済みブックマークを削除する
 */

void
DeleteDiigo(
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
    char                cookie[MAX_COOKIE_LEN];
    CBookeyApp          *pp = (CBookeyApp *)AfxGetApp();
    ProceedingDialog    *pdlg;
    CString             bookmarkName;

    bookmarkName.LoadString( IDS_TGT_DIIGO );
    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }

    cookie[0] = NUL;
    if ( (pp->m_bookmarkGotten == false)                   ||
         !(pp->m_myClip)                                   ||
         (pp->m_bookmarkName.Compare( bookmarkName ) != 0)    ) {
        // ブックマーク情報をまだ取得していない場合
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
        pp->m_myClip = pp->m_diigo.GetBookmarks( pp->m_numOfClips,
                                                 username, password );
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
        ret = deleteEntryOnDiigo( username, password, pp->m_myClip[i].url );
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

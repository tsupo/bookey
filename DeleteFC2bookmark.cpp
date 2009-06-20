/*
 *  DeleteFC2bokmark.cpp
 *      FC2BOOKMARK ブックマーク 削除処理
 *          written by H.Tsujimura  30 Mar 2007
 *
 * $Log: /comm/bookey/DeleteFC2bookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/03/30 14:19 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteFC2bookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getFC2Bookmark(
        const char *userName,
        char       *cookie,
        const char *uid,
        const char *cc,
        MyClip     **mp,
        MyClipEx   **mpEx,
        int        *total,
        char       *response,
        size_t     sz
    );
#ifdef __cplusplus
}
#endif


#define MAX_POOKMARK_PER_BLOCK 200

MyClipEx    *
getFC2bookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp   = NULL;
    char        *response;
    long        num   = 0;
    int         total = 0;
    size_t      sz    = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;
    char        uid[MAX_NAMELEN];
    char        cc[MAX_KEYLENGTH];

    uid[0] = NUL;
    cc[0]  = NUL;
    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_FC2_BOOKMARK );

    // FC2BOOKMARK にログイン
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginFC2Bookmark( username, password, cookie, uid, cc ) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // ブックマークを取得
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……
    num = _getFC2Bookmark( username, cookie, uid, cc,
                           NULL, &mp, &total, response, sz );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnFC2bookmark( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url,
             "http://bookmark.fc2.com/user/delete_bookmark/%s",
             mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}


/*
 *  DeleteJoltMark.cpp
 *      JoltMark ブックマーク 削除処理
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/DeleteJoltMark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 10    07/01/19 23:20 Tsujimura543
 * 不要になった行を削除
 * 
 * 9     07/01/19 23:20 Tsujimura543
 * _getJoltMark() を導入、リファクタリングを実施
 * 
 * 8     07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 7     07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 6     07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 5     07/01/12 22:33 Tsujimura543
 * (1) 「次のページ」の URL の末尾に余分な文字がつく現象に対処
 * (2) 「コメント」中に <br> が含まれる場合は除去するようにした
 * 
 * 4     06/12/26 0:00 Tsujimura543
 * 「実行中」ダイアログの文言変更し忘れ、修正
 * 
 * 3     06/12/22 15:25 Tsujimura543
 * (1) getJoltMark2() を実装
 * (2) 実際に削除できることを確認
 * 
 * 2     06/12/22 14:25 Tsujimura543
 * deleteEntryOnJoltMark() を実装
 * 
 * 1     06/12/21 15:00 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"
#ifdef  UNIX
#include <sys/time.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteJoltMark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getJoltMark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    );
#ifdef __cplusplus
}
#endif



#define MAX_JOLTMARK_PER_BLOCK  200

MyClipEx    *
getJoltMark2(
        const char       *userName,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp  = NULL;
    long        num  = 0;
    char        *response;
    size_t      sz;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_JOLTMARK );

    // JoltMark へログイン
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginJoltMark( userName, password, cookie ) )
        return ( mp );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // ブックマークの取得
    num = _getJoltMark( userName, cookie, NULL, &mp, response, sz );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnJoltMark( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url,
             "http://mark.jolt.jp/deleteMark.do?"
             "markNo=%s&"
             "viewUserFlag=list&"
             "ckString=%s",
             mp->entryID, mp->remarks );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}


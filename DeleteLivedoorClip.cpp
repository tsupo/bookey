/*
 *  DeleteLivedoorClip.cpp
 *      livedoorクリップ ブックマーク 削除処理
 *          written by H.Tsujimura  12 Jul 2006
 *
 * $Log: /comm/bookey/DeleteLivedoorClip.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    08/07/28 20:32 Tsujimura543
 *  deleteEntryOnLivedoorClip2() を追加
 * 
 * 13    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 12    07/01/19 22:05 Tsujimura543
 * _getLivedoorClip() を導入、リファクタリングを実施
 * 
 * 11    07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 10    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 9     07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
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
 * 3     06/07/24 22:20 Tsujimura543
 * http 応答格納領域のオーバーラン防止機能を利用するように修正
 * 
 * 2     06/07/24 20:57 Tsujimura543
 * (1) livedoorクリップの2006年7月20日付の変更に対応
 * (2) プライベートモードのクリップがあると削除対象クリップの内容に過不足
 *     が発生する不具合を修正
 * 
 * 1     06/07/12 15:43 Tsujimura543
 * 新規作成 (動作確認済み)
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
"$Header: /comm/bookey/DeleteLivedoorClip.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getLivedoorClip(
        const char *target,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    );
#ifdef __cplusplus
}
#endif


double
getTimeOfDay()
{
    double          s;
#ifdef  UNIX
    struct timeval  tv;
    struct timezone tx;

    gettimeofday( &tv, &tx );
    s = (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
#else
    time_t          t;
    SYSTEMTIME      systime;

    t = time( &t );
    GetSystemTime( &systime );
    s = t * 1000.0 + systime.wMilliseconds;
#endif

    return ( s );
}


#define MAX_LIVEDOORCLIP_PER_BLOCK  200
#define NUM_OF_CLIPS_PER_PAGE       20

MyClipEx    *
getLivedoorClip2(
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
    char        target[MAX_URLLENGTH];
    CString     bookmarkName;
    int         total = 0;
    CString     text;
    size_t      sz;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_LIVEDOOR_CLIP );

    // livedoorクリップ へログイン
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginLivedoorClip( username, password, cookie ) )
        return ( mp );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    *numOfClips = 0;

    // マイクリップを取得
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……
    sprintf( target, "http://clip.livedoor.com/clips/%s", username );
    num = _getLivedoorClip( target, cookie, NULL, &mp, response, sz, &total );

    *numOfClips = num;
    free( response );

    return ( mp );
}

BOOL
deleteEntryOnLivedoorClip( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://clip.livedoor.com/clip/delete" );
    sprintf( request,
             "hash=%s&"
             "postkey=%s&"
             "rand=%.f",
             mp->entryID, mp->remarks,
             getTimeOfDay() );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}


BOOL    deleteEntryOnLivedoorClip2(
            const char *username,
            const char *apiKey,
            const char *url )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    size_t  sz;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    sprintf( request,
             "%s?url=%s",
             "http://api.clip.livedoor.com/v1/posts/delete",
             encodeURL(url) );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( request, username, apiKey, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<result" );

        if ( p )
            ret = TRUE;
    }

    free( response );
    free( request );

    return ( ret );
}

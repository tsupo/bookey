/*
 *  DeleteEcNaviClip.cpp
 *      Buzzurl ブックマーク 削除処理
 *          written by H.Tsujimura  18 Aug 2006 / 11 Jan 2007
 *
 * $Log: /comm/bookey/DeleteEcNaviClip.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 17    07/10/05 2:40 Tsujimura543
 * getEcNaviClipUserID() の引数追加に伴う変更
 * 
 * 16    07/09/13 22:30 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 15    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 14    07/01/19 19:52 Tsujimura543
 * _getEcNaviClip() を導入、リファクタリングを実施
 * 
 * 13    07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 12    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 11    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 10    07/01/11 17:17 Tsujimura543
 * 「コメント」に含まれる &nbsp; を除去するようにした
 * 
 * 9     07/01/11 15:47 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 8     06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 7     06/10/10 16:49 Tsujimura543
 * ECナビ人気ニュースの Webページの charSet が EUC-JP から UTF-8 に
 * 変更されたのに伴う修正を実施
 * 
 * 6     06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() を導入。MyClipEx 構造体格納領域確保
 * 処理を共通関数化してみた
 * 
 * 5     06/08/26 1:53 Tsujimura543
 * もはやインクルード不要になったヘッダファイルのインクルードをやめた
 * 
 * 4     06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 3     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() を導入し、(削除用)ブックマーク情報取得処理を
 * 別スレッド化した
 * 
 * 2     06/08/22 17:21 Tsujimura543
 * 独自の構造体を廃止し、MyClipEx を導入
 * 
 * 1     06/08/18 20:35 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteEcNaviClip.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
char    *
deleteHtmlTags( char *text );

int
_getEcNaviClip(
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


#define MAX_ECNAVICLIP_PER_BLOCK    200

MyClipEx    *
getEcNaviClip2(
        const char       *username,
        const char       *password,
        const char       *username2,  /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char       *password2,  /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE        authType,    /* (I) 認証タイプ                     */
        char             *cookie,
        size_t           *cookieSize,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        target[MAX_URLLENGTH];
    char        *response;
    int         sz   = MAX_CONTENT_SIZE * 20;
    int         num  = 0;
    int         total = 0;
    CString     bookmarkName;
    CString     text;
    const char  *u = username;
    const char  *p = password;

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        u = username2;
        p = password2;
    }

    *numOfClips = 0;
    target[0]   = NUL;
    bookmarkName.LoadString( IDS_TGT_ECNAVI_CLIP );

    if ( u && u[0] && p && p[0] ) {
        text.LoadString(IDS_TXT_CONTINUE_LOGIN);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // ログイン中 ……
        char    *uID = getEcNaviClipUserID( u, p, authType,
                                            cookie, cookieSize );
        if ( uID )
            sprintf( target, "http://buzzurl.jp/user/%s/all", uID );
    }
    if ( target[0] == NUL )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // ブックマークの取得
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……
    num = _getEcNaviClip( target, cookie, NULL, &mp, response, sz, &total );

    *numOfClips = num;
    free( response );

    return ( mp );
}

BOOL
deleteEntryOnEcNaviClip( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    int     sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url,
             "http://buzzurl.jp/config/delete/execute?"
             "entry_id=%s&"
             "thumbprint=%s",
             mp->entryID, mp->remarks );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}

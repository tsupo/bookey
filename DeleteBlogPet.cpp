/*
 *  DeleteBlogPet.cpp
 *      「BlogPet 気になる記事」削除処理
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/DeleteBlogPet.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     07/07/13 2:01 Tsujimura543
 * 2007年7月12日に実施された BlogPet リニューアルに対応
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 7     07/02/14 23:13 Tsujimura543
 * _getBlogPet() のプロトタイプ宣言を blogPet.h へ移動
 * 
 * 6     07/01/19 15:44 Tsujimura543
 * (1) MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * (2) _getBlogPet() を導入、リファクタリングを実施
 * 
 * 5     07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 4     07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 3     06/12/26 0:23 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 2     06/12/26 0:22 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     06/12/22 21:50 Tsujimura543
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
"$Header: /comm/bookey/DeleteBlogPet.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "blogPet.h"

#ifdef __cplusplus
}
#endif

#define MAX_BLOGPET_PER_BLOCK   200


MyClipEx    *
getBlogPet2(
        const char       *userName,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp  = NULL;
    char        *response;
    char        userID[MAX_KEYLENGTH];
    size_t      sz;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    userID[0]   = NUL;
    bookmarkName.LoadString( IDS_TGT_BLOGPET );

    // BlogPet 管理画面 へログイン
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginBlogPet( userName, password, cookie, userID ) )
        return ( mp );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    *numOfClips = 0;

    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……

    *numOfClips = _getBlogPet( userID, cookie, NULL, &mp, response, sz );

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnBlogPet( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    entryKey[MAX_KEYLENGTH];
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

    entryKey[0] = NUL;
    sprintf( url,
             "http://www.blogpet.net/bookmark/remove?url=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );    // 削除確認
    if ( *response ) {
        char    *p, *q;

        p = strstr( response, "name=\"CID\" value=\"" );
        if ( p ) {
            entryKey[0] = NUL;
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( entryKey, p, q - p );
                entryKey[q - p] = NUL;
            }
        }
    }

    if ( entryKey[0] ) {
        strcpy( url, "http://www.blogpet.net/bookmark/remove" );
        sprintf( request,
                 "CID=%s&"
                 "remove=%s",
                 entryKey,
                 encodeURL( sjis2utf("<span>削除する</span>") ) );

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );       // 削除実行
        if ( *response )
            ret = TRUE;
    }

    free( response );
    free( request );

    return ( ret );
}


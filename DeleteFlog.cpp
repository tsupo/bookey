/*
 *  DeleteFlog.cpp
 *      Flog ブックマーク 削除処理
 *          written by H.Tsujimura  27 Jun 2006
 *
 * $Log: /comm/bookey/DeleteFlog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 13    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
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
 * 3     06/07/12 12:10 Tsujimura543
 * deleteEntryOnFlog() 内で response を解放し忘れていた
 * 
 * 2     06/07/03 15:15 Tsujimura543
 * ProceedingDialog 絡みの改修 (ProceedingDialog の delete時に例外が
 * 発生することがある件の対策実施)
 * 
 * 1     06/06/27 17:57 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteFlog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define MAX_FLOG_PER_BLOCK  200

MyClipEx    *
getFlog2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        *response;
    long        num   = 0;
    int         block = 0;
    char        url[MAX_URLLENGTH];
    size_t      sz = MAX_CONTENT_SIZE * 64;
    CString     bookmarkName;
    CString     text;

    bookmarkName.LoadString( IDS_TGT_FLOG );

    // Flog へログイン
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginFlog( username, password, cookie ) )
        return ( mp );

    // 管理画面を取得
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );
    strcpy( url, "http://www.flog.jp/mybookmark.php" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( response[0] != NUL ) {
        // 管理画面を解析し、ブックマーク情報を取得
        char    *p, *q, *r;
        int     len;

        p = strstr( response, "<td align=\"left\" class=\"txt\">" );
        if ( p )
            p = strstr( p + 29, "<a href=/j.php/" );
        if ( !p ) {
            free( response );
            return ( mp );
        }

        do {
            MyClipEx    *newClip_p;
            newClip_p = allocateMyClipExIfNecessary( &mp, MAX_FLOG_PER_BLOCK,
                                                     &block, num );
            if ( !newClip_p )
                break;
            mp = newClip_p;

            // URL
            p += 15;
            q = strstr( p, " target=_blank>" );
            if ( !q )
                break;
            strncpy( mp[num].url, p, q - p );
            mp[num].url[q - p] = NUL;

            // 題名
            p = q + 15;
            q = strstr( p, "</a>" );
            if ( !q )
                break;
            strncpy( mp[num].title, p, q - p );
            mp[num].title[q - p] = NUL;

            // タグ
            p = q + 4;
            r = strstr( p, "</table>" );
            if ( !r )
                break;
            do {
                q = strstr( p, " class=\"txt_s\">[" );
                if ( !q || (q > r) )
                    break;
                p = q + 16;
                q = strstr( p, "]</a>" ); // 2byte 目が ']' な漢字があると罠に
                if ( !q || (q > r) )      // はまるので、"</a>" 付きで評価する
                    break;

                if ( mp[num].tags[0] )
                    strcat( mp[num].tags, " " );
                len = mp[num].tags[0] ? strlen( mp[num].tags ) : 0;
                strncat( mp[num].tags, p, q - p );
                mp[num].tags[len + (q - p)] = NUL;

                p = q + 5;
            } while ( q );
            if ( p > r )
                break;

            // コメント
            q = strstr( p, "<div class=\"comment\">" );
            if ( !q || (q > r) )
                break;
            p += 21;
            q = strstr( p, "\">&nbsp;" );
            if ( !q || (q > r) )
                break;
            p = q + 8;

            q = strstr( p, "&nbsp;(" );
            if ( !q || (q > r) )
                break;
            strncpy( mp[num].comment, p, q - p );
            mp[num].comment[q - p] = NUL;

            // 削除用エントリID
            p = q + 7;
            q = strstr( p, "<a href=\"/delurl.php/" );
            if ( !q )
                break;
            p = q + 21;
            q = strstr( p, "\" onclick=\"" );
            if ( !q )
                break;
            strncpy( mp[num].entryID, p, q - p );
            mp[num].entryID[q - p] = NUL;

            // 次へ
            num++;

            p = strstr( r, "<a href=/j.php/" );
        } while ( p );
    }

    free( response );

    *numOfClips = num;

    return ( mp );
}

BOOL
deleteEntryOnFlog( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 64;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url, "http://www.flog.jp/delurl.php/%s", mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}

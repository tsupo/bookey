/*
 * getBookmarks.cpp : ソーシャルブックマーク管理プログラム
 *      (ブックマーク削除用)ブックマーク情報取得スレッド
 *          written by H.Tsujimura  25 Aug 2006
 *
 * $Log: /comm/bookey/getBookmarks.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    07/10/05 2:41 Tsujimura543
 * getEcNaviClip2() の引数追加に伴う変更
 * 
 * 14    07/09/13 22:30 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 13    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks と Yahoo! ブックマークの「削除」に対応
 * 
 * 12    07/03/30 14:09 Tsujimura543
 * FC2BOOKMARK の「削除」に対応
 * 
 * 11    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 10    07/02/16 16:35 Tsujimura543
 * コメントを修正
 * 
 * 9     06/12/25 23:23 Tsujimura543
 * 「BlogPet 気になる記事」に対応
 * 
 * 8     06/12/21 22:31 Tsujimura543
 * JoltMark 対応
 * 
 * 7     06/10/05 22:30 Tsujimura543
 * POOKMARK Airlines の「削除」に対応
 * 
 * 6     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 5a    06/09/03 22:03 tsupo
 * 再描画のためのメッセージループを当初のもの(revision 2 時点)に戻す
 * (戻しても落ちなくなったことを確認)
 * 
 * 5     06/09/03 5:54 tsupo
 * GetBookmarksForDelete() を元(revision 3 時点)に戻す
 * (xmlRPC.dll の cookie 回りの修正にて問題が解決したため)
 * 
 * 4     06/09/02 1:32 Tsujimura543
 * http 通信中には SetFocus() しないようにした後も、まだ落ちる(ことがある。
 * 今まで100%落ちていたのが、落ちなくなることもある、程度に改善されただけ
 * だった。根本的な原因が判明するまで、何らかの暫定対処が必要)
 * 
 * 3     06/09/02 1:17 Tsujimura543
 * ドリコムRSS(Clip!)の取得中に SetFocus() で落ちる件は、状況証拠により、
 * http 通信実行中に SetFocus() するのがまずいらしいことが判明。http 通信
 * 実行中でない場合のみ、メッセージループ相当処理を実行するようにした
 * 
 * 2     06/08/25 19:25 Tsujimura543
 * ソースを整形
 *
 * 1     06/08/25 19:21 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "deleteBookmark.h"
#include <process.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBookmarks.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// (削除用)ブックマーク情報の取得
UINT
DeleteBookmarkSub( LPVOID pParam )
{
    // (削除用)ブックマーク情報取得スレッド
    UINT        ret = 0;
    DBSparam_t  *p  = (DBSparam_t *)pParam;

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_MM_MEMO:
        // MM/Memo からブックマーク情報を取得
        p->myBookmark = getMMmemo2( p->u.username, p->u.password,
                                    p->cookie,
                                    &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_DRECOM_RSS:
        // ドリコムRSS からブックマーク情報を取得
        p->myBookmark = getDrecomRSS2( p->u.username, p->u.password,
                                       p->cookie,
                                       &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_FLOG:
        // Flog からブックマーク情報を取得
        p->myBookmark = getFlog2( p->u.username, p->u.password,
                                  p->cookie,
                                  &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP:
        // livedoorクリップ からブックマーク情報を取得
        p->myBookmark = getLivedoorClip2( p->u.username, p->u.password,
                                          p->cookie,
                                          &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_ECNAVI_CLIP:
        // Buzzurl からブックマーク情報を取得
        p->myBookmark = getEcNaviClip2( p->u.username,  p->u.password,
                                        p->u.username2, p->u.password2,
                                        p->u.authType,  p->cookie,
                                        &(p->cookieSize),
                                        &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_NIFTY_CLIP:
        // ニフティクリップ からブックマーク情報を取得
        p->myBookmark = getNiftyClip2( p->u.username, p->u.password,
                                       p->cookie,
                                       &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_1470NET:
        // 1470.netリニューアル版 からブックマーク情報を取得
        p->myBookmark = get1470net2( p->u.username,  p->u.password,
                                     p->u.username2, p->u.password2,
                                     p->u.authType,  p->cookie,
                                     &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_POOKMARK:
        // POOKMARK Airlines からブックマーク情報を取得
        p->myBookmark = getPookmark2( p->u.username, p->u.password,
                                      p->cookie,
                                      &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_JOLTMARK:
        // JoltMark からブックマーク情報を取得
        p->myBookmark = getJoltMark2( p->u.username, p->u.password,
                                      p->cookie,
                                      &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_BLOGPET:
        // BlogPet 気になる記事 からブックマーク情報を取得
        p->myBookmark = getBlogPet2( p->u.username, p->u.password,
                                     p->cookie,
                                     &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_FC2BOOKMARK:
        // FC2BOOKMARK からブックマーク情報を取得
        p->myBookmark = getFC2bookmark2( p->u.username, p->u.password,
                                         p->cookie,
                                         &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_YJ_BOOKMARK:
        // Yahoo! ブックマーク からブックマーク情報を取得
        p->myBookmark = getYJbookmark2( p->u.username, p->u.password,
                                        p->cookie,
                                        &(p->numOfBookmarks), p->dlg );
        break;

    case CUserInfo::BK_YAHOO_BOOKMARKS:
        // Yahoo! Bookmarks からブックマーク情報を取得
        p->myBookmark = getYahooBookmarks2( p->u.username, p->u.password,
                                            p->cookie,
                                            &(p->numOfBookmarks), p->dlg );
        break;

    default:
        // はてなブックマーク、del.icio.us、BlogPeople tags は(通常の)ブック
        // マーク取得処理を使用するため、本スレッドを利用することはない
        break;
    }

    return ( ret );
}

MyClipEx  *
GetBookmarksForDelete( DBSparam_t *param,
                       int        &numOfMyBookmarks )
{
    MyClipEx    *p = NULL;
    CWaitCursor cur;    // マウスカーソルを砂時計表示

    // ブックマーク取得スレッドを起動
    CWinThread  *tp = AfxBeginThread( DeleteBookmarkSub,
                                      (void *)param );
    if ( tp ) {
        DWORD       exitCode  = 0;
        int         status;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        // ブックマーク取得スレッドが終了するのを待つ
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView もしくは CBookeyDlg の再描画
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog の再描画
                param->dlg->SetFocus();
                param->dlg->UpdateWindow();

                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        if ( param->myBookmark ) {
            if ( param->numOfBookmarks > 0 ) {
                p = param->myBookmark;
                numOfMyBookmarks = param->numOfBookmarks;
            }
            else
                free( param->myBookmark );
        }

        delete tp;
    }

    return ( p );
}

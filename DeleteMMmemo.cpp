/*
 *  DeleteMMmemo.cpp
 *      MM/Memo ブックマーク 削除処理
 *          written by H.Tsujimura  1 Nov 2005
 *
 * $Log: /comm/bookey/DeleteMMmemo.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 26    07/06/29 13:49 Tsujimura543
 * http://1470.net/mm/ → http://mmmemo.1470.net/mm/ へ変更
 * 
 * 25    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 24    07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 23    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 22    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 21    06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 20    06/09/25 16:12 Tsujimura543
 * allocateMyClipExIfNecessary() を導入(リファクタリングを実施)
 * 
 * 19    06/08/26 1:53 Tsujimura543
 * もはやインクルード不要になったヘッダファイルのインクルードをやめた
 * 
 * 18    06/08/26 1:42 Tsujimura543
 * 修正後の削除動作を確認 (問題なし)
 * 
 * 17    06/08/26 1:40 Tsujimura543
 * (1) deleteEntryOnMMmemo() 内で受信バッファオーバーランする不具合を修正
 *     (バッファオーバーラン防止機能を組み込んだ)
 * (2) 上記修正後も、削除に失敗する(delete_key が取得できない)不具合を発見。
 *     修正を実施 (受信バッファサイズを増やした)
 * 
 * 16    06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 15    06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() を導入し、(削除用)ブックマーク情報取得処理を
 * 別スレッド化した
 * 
 * 14    06/08/22 17:21 Tsujimura543
 * 独自の構造体を廃止し、MyClipEx を導入
 * 
 * 13    06/07/19 13:47 Tsujimura543
 * FEATURE_NOT_AVAILABLE な部分を削除 (1470.netリニューアル版の登場で
 * MM/Memo 自体の API 整備の可能性はなくなったため)
 * 
 * 12    06/07/03 15:15 Tsujimura543
 * ProceedingDialog 絡みの改修 (ProceedingDialog の delete時に例外が
 * 発生することがある件の対策実施)
 * 
 * 11    06/06/20 16:29 Tsujimura543
 * isWhiteSpace() を myClip.h へ移動
 * 
 * 10    06/06/19 20:31 Tsujimura543
 * m_pDlg->DestroyWindow(); をコメントアウト
 * 
 * 9     06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 8     05/11/30 14:30 Tsujimura543
 * MAX_DESCRIPTION_LEN の定義を統一し、xmlRPC.h に移動
 * 
 * 7     05/11/11 13:19 Tsujimura543
 * 少しだけリファクタリング
 * 
 * 6     05/11/11 0:03 Tsujimura543
 * 「ブックマーク削除中」の表示を追加
 * 
 * 5     05/11/10 21:21 Tsujimura543
 * 進行状況表示ダイアログを使うようにした
 * 
 * 4     05/11/09 23:52 Tsujimura543
 * 余分なコメントを削除
 * 
 * 3     05/11/09 23:48 Tsujimura543
 * 削除処理の実装完了、動作確認済み
 * 
 * 2     05/11/09 21:24 Tsujimura543
 * getMMmemo2() を実装 (削除処理そのものは未実装)
 * 
 * 1     05/11/01 18:20 Tsujimura543
 * 最初の版 (実際に削除する直前まで実行し、削除自体はまだ実行せずに終了す
 * る版)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteMMmemo.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define skipWhiteSpace( p ) \
            while ( isWhiteSpace(*(p)) ) \
                (p)++;
#define skipNumber( p ) \
            while ( (*(p) >= '0') && (*(p) <= '9') ) \
                (p)++;
#define skipNonNumber( p ) \
            while ( (*(p) < '0') || (*(p) > '9') ) \
                (p)++;
#define skipToNextNumber( p ) \
            skipNumber(p); \
            skipNonNumber(p); \
            if ( *(p) == '0' ) \
                (p)++;

#define MAX_MEMO_PER_PAGE   50

long
getPostsOnMMmemo(
        const char *response,
        long       *numOfPosts,
        MyClipEx   *posts
    )
{
    long        num = 0;
    const char  *p = response, *q, *r, *s, *t;
    char        temp[MAX_DESCRIPTION_LEN];
    int         yyyy, mm, dd;
    int         preYyyy = 0, preMm = 0, preDd = 0;

    while ( *p ) {
        yyyy = 0;
        mm   = 0;
        dd   = 0;
        q = strstr( p, "<h2><span class=\"date\">" );
        r = strstr( p, "<h3>" );
        if ( !r )
            break;
        if ( q && r && (q < r) ) {
            // 年月日
            s = strstr( q, "?date=" );
            if ( s && (s < r) ) {
                s += 6;
                yyyy = atol( s );

                skipToNextNumber(s);
                mm = atol( s );

                skipToNextNumber(s);
                dd = atol( s );
            }
        }
        if ( num > 0 ) {
            if ( yyyy == 0 ) {
                yyyy = preYyyy;
                mm   = preMm;
                dd   = preDd;
            }
        }
        preYyyy = yyyy;
        preMm   = mm;
        preDd   = dd;
        sprintf( posts[num].remarks, "%04d%02d%02d", yyyy, mm, dd );

        // genre
        p = r + 4;
        q = r;
        t = strstr( p, "</h3>" );
        if ( !t )
            break;
        posts[num].tags[0] = NUL;
        memset( temp, NUL, MAX_DESCRIPTION_LEN );
        while ( p < t ) {
            q = strstr( p, "?genre=" );
            if ( !q || (q > t) )
                break;
            q += 7;
            r = strstr( q, ">[" );
            if ( !r || (r > t) )
                break;
            r += 2;
            s = strstr( r, "]<" );
            if ( !s || (s > t) )
                break;
            if ( temp[0] )
                strcat( temp, " " );
            strncat( temp, r, s - r );
            p = s + 2;
        }
        if ( temp[0] ) {
            q = euc2sjis( temp );
            strcpy( posts[num].tags, q ? q : temp );
        }

        // href と title
        q = strstr( p, sjis2euc( "『" ) );
        if ( !q )
            break;
        p = q + 2;
        q = strstr( p, sjis2euc( "』" ) );
        if ( !q )
            break;

        r = strstr( p, "<a href=\"" );
        if ( !r )
            break;
        r += 9;
        s = strchr( r, '"' );
        if ( !s )
            break;
        strncpy( posts[num].url, r, s - r );
        posts[num].url[s - r] = NUL;

        p = s + 1;
        s = strchr( p, '>' );
        if ( !s )
            break;
        s++;
        r = strstr( s, "</a>" );
        if ( !r )
            break;
        strncpy( temp, s, r - s );
        temp[r - s] = NUL;
        s = euc2sjis( temp );
        if ( s )
            strcpy( posts[num].title, s );
        else
            strcpy( posts[num].title, temp );
        p = q + 2;

        // メモID
        q = strstr( p, "?memo=" );
        if ( !q )
            break;
        q += 6;
        r = strchr( q, '"' );
        if ( !r )
            break;
        strncpy( posts[num].entryID, q , r - q );
        posts[num].entryID[r - q] = NUL;
        p = r + 1;

        // コメント
        if ( p > t )
            break;
        p = t + 5;
        q = strstr( p, "<p>" );
        t = strstr( p, "<div class=\"" );
        if ( q && t && (q < t) ) {
            q += 4;
            skipWhiteSpace(q);
            r = strstr( q, "</p>" );
            if ( !r )
                break;
            p = r + 5;
            while ( isWhiteSpace(*(r - 1)) )
                r--;
            strncpy( temp, q, r - q );
            temp[r - q] = NUL;
            q = euc2sjis( temp );
            strcpy( posts[num].comment, q ? q : temp );
        }
        else
            posts[num].comment[0] = NUL;

        num++;
        if ( num >= *numOfPosts )
            break;
    }

    *numOfPosts = num;

    return ( num );
}

long
getRecentPostsOnMMmemo(
        const char       *username,     /* (I) ユーザ名                     */
        const char       *password,     /* (I) パスワード                   */
        char             *userID,       /* (I/O) ユーザID                   */
        long             offset,        /* (I) 取得開始位置(ページ番号)     */
        long             *numOfPosts,   /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        MyClipEx         *posts,        /* (O) 取得したブックマーク         */
        BOOL             *more,         /* (O) 取得可能残存ブックマーク有無 */
        char             *cookie,       /* (I/O) クッキー                   */
        ProceedingDialog *pdlg
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         (offset < 0) || !more )
        return ( num );

    sz = MAX_CONTENT_SIZE * 2;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    CString text;
    CString bookmarkName;
    bookmarkName.LoadString( IDS_TGT_MMMEMO );

    if ( offset == 0 ) {
        // MM/Memo へログイン
        text.LoadString(IDS_TXT_CONTINUE_CHECKING_TYPEKEY);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // TypeKey 認証中 ……
        res = loginMMmemo( username, password, cookie, userID );
        if ( res == 0 ) {
            // ログイン失敗
            free( response );
            return ( num );
        }

        // http://1470.net/mm/mylist.html を GET
        //  -- http://1470.net/mm/ → http://mmmemo.1470.net/mm/
        sprintf( url, "http://mmmemo.1470.net/mm/mylist.html/%s", userID );
    }
    else {
        // http://1470.net/mm/mylist.html/ユーザID?limit=50&page=ページ番号
        // を GET
        sprintf( url, "http://mmmemo.1470.net/mm/mylist.html/%s?limit=%d&page=%d",
                 userID, MAX_MEMO_PER_PAGE, offset + 1 );
    }

    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( response[0] != NUL ) {
        char    *p;

        p = response;
        if ( strstr( p, "-&gt;</a>" ) )
            *more = TRUE;
        else
            *more = FALSE;

        // サーバから返ってきた html を解析して、ブックマークのリストを生成
        num = getPostsOnMMmemo( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}


/* MM/Memo の全メモを取得 */
MyClipEx    *
getMMmemo2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp            = NULL;
    int         offset         = 0;
    int         total          = 0;
    BOOL        more           = TRUE;
    long        num            = MAX_MEMO_PER_PAGE;
    long        numOfBookmarks = 0;
    char        userID[32];

    do {
        MyClipEx    *newClip_p;

        total = *numOfClips;
        newClip_p = allocateMyClipExIfNecessary( &mp, num, &offset, total );
        if ( !newClip_p ) {
            more = FALSE;
            break;
        }
        mp = newClip_p;

        numOfBookmarks = getRecentPostsOnMMmemo( username, password, userID,
                                                 offset - 1, &num,
                                                 &(mp[num * (offset - 1)]),
                                                 &more,
                                                 cookie,
                                                 pdlg );
        *numOfClips += numOfBookmarks;
        num = MAX_MEMO_PER_PAGE;
    } while ( more == TRUE );

    return ( mp );
}

BOOL
deleteEntryOnMMmemo(
        char           *cookie,
        const MyClipEx *mp
    )
{
    BOOL    ret = FALSE;
    char    url[MAX_URLLENGTH];
    char    *request;
    char    *response;
    size_t  sz  = MAX_CONTENT_SIZE * 20;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    // http://1470.net/mm/memo_form.html?memo=メモID&delete=true を GET
    setUpReceiveBuffer( response, sz );
    sprintf( url,
             "http://mmmemo.1470.net/mm/memo_form.html?memo=%s&delete=true",
             mp->entryID );
    http_getEx( url, response, cookie );
    if ( response[0] != NUL ) {
        char    *p, *q;
        char    checkKey[MAX_BLOGIDLENGTH + 1];
        char    deleteKey[MAX_BLOGIDLENGTH + 1];
        char    webpage[MAX_BLOGIDLENGTH + 1];

        checkKey[0]  = NUL;
        deleteKey[0] = NUL;
        webpage[0]   = NUL;

        // check_key を取得
        p = strstr( response, "name=\"check_key\" value=\"" );
        if ( p ) {
            p += 24;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( checkKey, p, q - p );
                checkKey[q - p] = NUL;
            }
        }

        // delete_key を取得
        p = strstr( response, "name=\"delete_key\" value=\"" );
        if ( p ) {
            p += 25;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( deleteKey, p, q - p );
                deleteKey[q - p] = NUL;
            }
        }

        // webpage を取得
        p = strstr( response, "name=\"webpage\" value=\"" );
        if ( p ) {
            p += 22;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( webpage, p, q - p );
                webpage[q - p] = NUL;
            }
        }

        if ( checkKey[0] && deleteKey[0] && webpage[0] ) {
            // 削除実行
            setUpReceiveBuffer( response, sz );
            strcpy( url, "http://mmmemo.1470.net/mm/memo_form.html" );
            sprintf( request,
                     "memo=%s&"
                     "check_key=%s&"
                     "webpage=%s&",
                     mp->entryID, checkKey, webpage );
            sprintf( request + strlen( request ),
                     "delete=%s&"
                     "delete_key=%s",
                     sjis2euc( "削除する" ), deleteKey );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );
            if ( response[0] )
                ret = TRUE;
        }
    }

    free( response );
    free( request );

    return ( ret );
}


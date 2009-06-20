/*
 *  DeleteDrecomRSS.cpp
 *      ドリコムRSS(Clip!) ブックマーク 削除処理
 *          written by H.Tsujimura  22 Aug 2006
 *
 * $Log: /comm/bookey/DeleteDrecomRSS.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 16    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 15    07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 14    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 13    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 12    06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() を導入。MyClipEx 構造体格納領域確保
 * 処理を共通関数化してみた
 * 
 * 11    06/09/04 15:20 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 10    06/09/02 2:14 Tsujimura543
 * 環境を変えて調査するため、「進行状況ダイアログ」を元に戻す
 * (→ Visual Studio 2005 でもビルドして動作確認をしてみたところ、cookie
 *     格納領域のメモリオーバーランにより、スタックフレームが破壊されて
 *     いるのが原因で、諸々の現象が発生していることが判明。cookie まわり
 *     の処理の改修にて、現象が発生しなくなったことを確認)
 * 
 * 9     06/09/02 2:12 Tsujimura543
 * いったんチェックイン(「進行状況」ダイアログの表示をやめると、今度は
 * スタックオーバーフローで落ちる。今まで見えてなかった原因をつかむ手が
 * かりか?)
 * 
 * 8     06/09/01 19:07 Tsujimura543
 * さらにリファクタリング (まだ、原因わからず)
 * 
 * 7     06/09/01 1:27 Tsujimura543
 * 原因追求をしやすくするため、少しリファクタリング
 * 
 * 6     06/09/01 1:01 Tsujimura543
 * とりあえず、処理は書けたけど、ダイアログのフォーカスが変わるところで不
 * 正なメモリ参照が発生して落ちる問題が残っている (今のところ、原因不明)
 * 
 * 5     06/08/26 1:53 Tsujimura543
 * もはやインクルード不要になったヘッダファイルのインクルードをやめた
 * 
 * 4     06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 3     06/08/25 22:20 Tsujimura543
 * 実際にブックマークを取得して、削除する処理以外の作り込み、終了
 * 
 * 2     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() を導入し、(削除用)ブックマーク情報取得処理を
 * 別スレッド化した
 * 
 * 1     06/08/22 20:05 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"
#include "getDrecomRSS.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteDrecomRSS.cpp 1     09/05/14 3:48 tsupo $";
#endif

void
getClipInfo2( const char *htmlSrc,
              MyClipEx   **mp,
              const char *tag,
              const char *objectID,
              char       *cookie,
              int        *numOfClips )
{
    int                 unit = MAX_DRECOM_RSS_PER_BLOCK;
    Thread  static int  cnt  = 0;
    const char          *p, *q, *r;
    char                articleID[64];
    char                *response;
    char                title[1024];
    char                href[1024];
    char                summary[2048];
    int                 num = 0;
    size_t              sz  = MAX_CONTENT_SIZE * 20;

    if ( !(*mp) )
        cnt = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    p = htmlSrc;
    do {
        // article ID
        q = strstr( p, "<div class=\"articleRow\" id=\"" );
        if ( !q )
            break;
        r = strstr( q, "</div>" );
        if ( !r )
            break;
        p = q + 28;
        q = strstr( p, "\">" );
        if ( !q || (q > r) )
            break;
        strncpy( articleID, p, q - p );
        articleID[q - p] = NUL;

        // title
        p = q + 2;
        q = strstr( p, " all=\"");
        if ( !q || (q > r) )
            break;
        p = q + 6;
        q = strstr( p, "\">" );
        if ( !q || (q > r) )
            break;
        strncpy( title, p, q - p );
        title[q - p] = NUL;

        p = r + 6;

        getArticleDetail( articleID, objectID,
                          response, sz, cookie );
        if ( *response ) {
            char        *s, *t;
            MyClipEx    *pp;

            decodeContents( response );
            s = response;

            // url
            t = strstr( s, "<a href=\"" );
            if ( !t )
                continue;
            s = t + 9;
            t = strstr( s, "\" " );
            if ( !t )
                continue;
            strncpy( href, s, t - s );
            href[t - s] = NUL;

            // comment
            summary[0] = NUL;
            s = t + 2;
            t = strstr( s, "<td style=\"color:#666666;\">" );
            if ( t ) {
                s = t + 27;
                t = strstr( s, "</td>" );
                if ( t ) {
                    strncpy( summary, s, t - s );
                    summary[t - s] = NUL;
                }
            }

            pp = allocateMyClipExIfNecessary( mp, unit, &cnt,
                                              *numOfClips + num );
            if ( !pp )
                break;
            *mp = pp;

            while ( (s = strstr( title, "&#039;" )) != NULL ) {
                *s = '\'';
                strcpy( s + 1, s + 6 ); /* &#039; → ' に置換 */
            }

            /* ドリコムRSSのClip!のコメントには改行が含まれ得る */
            while ( ((s = strchr(summary, '\r')) != NULL) ||
                    ((s = strchr(summary, '\n')) != NULL)    )
                strcpy( s, s + 1 ); /* 改行を取り除く */
            /* ドリコムRSSのClip!のコメントには <br /> が含まれ得る */
            while ( (s = strstr( summary, "<br />" )) != NULL )
                strcpy( s, s + 6 ); /* <br /> を取り除く */
            while ( (s = strstr( summary, "&#039;" )) != NULL ) {
                *s = '\'';
                strcpy( s + 1, s + 6 ); /* &#039; → ' に置換 */
            }

            pp = &((*mp)[*numOfClips + num]);
            strcpy( pp->title, utf2sjisEx(title) );
            if ( summary[0] )
                strcpy( pp->comment, utf2sjisEx(summary) );
            else
                pp->comment[0] = NUL;

            strcpy( pp->url,  href );
            strcpy( pp->tags, tag );

            strcpy( pp->entryID, articleID );
            strcpy( pp->remarks, objectID );

            num++;
        }
    } while ( p && *p );

    if ( num > 0 )
        *numOfClips += num;

    free( response );
}

void
getDrecomRSSclip2(
        MyClipEx   **mp,
        const char *objectID,
        const char *folderName,
        int        folderNumber,
        int        year,
        char       *cookie,
        int        *numOfClips )
{
    char    *p;
    char    tag[80];
    int     totalPages = 0;
    int     page = 1;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return;

    // フォルダ名 → タグ
    getTagByName( tag, folderName );

    // 指定フォルダ・指定年のクリップ一覧(の1ページ目)を取得
    getArticleList( folderNumber, year, page, objectID,
                    response, sz, cookie );
    if ( *response ) {
        int     page = 1;

        if ( !strstr( response, "\"error\":null" ) ) {
            free( response );
            return; /* 取得失敗 */
        }

        decodeContents( response );
        if ( !strstr( response, "<div class=\"articleRow\"" ) ) {
            free( response );
            return; /* 指定年のクリップデータなし */
        }

        p = strstr( response, "title=\"last page\">[" );
        if ( p ) {
            p += 19;
            totalPages = atol( p );
        }
        getClipInfo2( response, mp, tag,
                      objectID, cookie, numOfClips );

        // 指定フォルダ・指定年のクリップ一覧(の2ページ目以降)を取得
        for ( ++page; page <= totalPages; page++ ) {
            Sleep( 1000 );  /* サーバへの負荷集中回避のため sleep */
            getArticleList( folderNumber, year, page, objectID,
                            response, sz, cookie );
            if ( !(*response) || !strstr( response, "\"error\":null" ) )
                break;      /* 取得失敗 */

            decodeContents( response );
            if ( !strstr( response, "<div class=\"articleRow\"" ) )
                continue;   /* クリップデータなし */

            getClipInfo2( response, mp, tag,
                          objectID, cookie, numOfClips );
        }
    }

    free( response );
}

MyClipEx    *
getDrecomRSS2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        *response;
    char        url[MAX_URLLENGTH];
    int         num = 0;
    size_t      sz  = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_DRECOM_RSS );

    // ドリコムRSS に login
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    if ( !loginDrecomRSS( username, password, cookie ) ) {
        // login 失敗
        return ( mp );
    }

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // クリップリーダー にアクセス
    text.LoadString(IDS_TXT_CONTINUE_GETTING_FOLDER);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // フォルダ一覧取得中 ……
    strcpy( url, "http://rss.drecom.jp/clip" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        FOLDER_LIST *list = NULL;
        int         numOfFolders = 0;

        // フォルダ一覧を取得
        list = getFolderList( response, &numOfFolders );
        if ( list ) {
            char        objectID[64];
            int         i, y;
            time_t      t = time( NULL );
            struct tm   *tm = localtime( &t );
            int         yyyy = tm->tm_year + 1900;
            BOOL        b;

            // objectID を登録
            b = setObjectID( objectID, cookie );
            if ( b ) {
                CString text;
                text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
                pdlg->ChangeDialogText( bookmarkName,
                                        text ); // ブックマーク情報取得中 ……

                // 各フォルダについて、年ごとのクリップ一覧を取得
                for ( i = 0; i < numOfFolders; i++ ) {
                    for (y = yyyy; y > 2003; y--) // 最古のクリップは2004年3月
                        getDrecomRSSclip2( &mp, objectID, list[i].folderName,
                                           i, y, cookie, &num );
                }
            }

            free( list );
        }
    }

    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnDrecomRSS( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    sprintf( request,
             "{\"method\": \"clip.deleteClip\", \"params\": "
             "[[\"%s\"]], \"objectID\": \"%s\"}",
             mp->entryID, mp->remarks );
    strcpy( url, "http://rss.drecom.jp/jsonrpc" );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "text/plain",
                 request, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}

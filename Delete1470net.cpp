/*
 *  Delete1470net.cpp
 *      1470.netリニューアル版 ブックマーク 削除処理
 *          written by H.Tsujimura  22 Aug 2006
 *
 * $Log: /comm/bookey/Delete1470net.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 21    08/07/25 1:30 Tsujimura543
 * ブックマーク削除後、前方に未削除のブックマークが残っていないとき
 * でも、「1個前に戻る」ボタンが有効なままになってしまう不具合を修正
 * 
 * 20    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 19    07/01/19 15:47 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 18    07/01/18 15:13 Tsujimura543
 * justify() を Delete1470net.cpp から分離、独立させた (justify.c へ移動)
 * 
 * 17    07/01/15 22:41 Tsujimura543
 * 英語モード対応
 * 
 * 16    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 15    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 14    06/10/26 23:53 Tsujimura543
 * コメントを修正
 * 
 * 13    06/10/26 23:51 Tsujimura543
 * 「1個前に戻る」で戻りすぎてしまうことがある(消したはずのブックマークが
 * 表示される)不具合に対処
 * 
 * 12    06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 11    06/09/25 16:25 Tsujimura543
 * allocateMyClipExIfNecessary() を導入(リファクタリングを実施)
 * 
 * 10    06/09/04 18:15 Tsujimura543
 * 「1個前へ戻る」機能を追加
 * 
 * 9     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 8b    06/09/03 22:13 tsupo
 * ブックマークの削除に失敗した場合、いきなり処理を中断するのはやめて、処
 * 理を続行するかどうか尋ねるようにした
 * 
 * 8a    06/09/03 19:26 tsupo
 * cookie 回りを修正 (メモリオーバーラン対策)
 * 
 * 8     06/08/25 22:22 Tsujimura543
 * justify() と decodeString() を C の関数化 (extern "C" 指定)
 * 
 * 7     06/08/25 20:22 Tsujimura543
 * getFeedOn1470net2() の URL から「日付」を取り出す処理を修正
 * (数字の先頭が 0 で始まる場合に8進数と解釈されてしまう可能性を排除)
 * 
 * 6     06/08/25 20:08 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 5     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() を導入し、(削除用)ブックマーク情報取得処理を
 * 別スレッド化した
 * 
 * 4     06/08/24 21:24 Tsujimura543
 * API 経由でエントリ情報(JSON形式)を取得する処理 getFeedOn1470net2()
 * を追加
 * 
 * 3     06/08/24 14:25 Tsujimura543
 * (1) _csrf の値を取得し忘れていたため、処理を追加
 * (2) 奇数番目のブックマークしか取得していないことが判明、修正を実施
 * (3) 実際に削除できることを確認
 * 
 * 2     06/08/23 20:14 Tsujimura543
 * 実装完了
 * 
 * 1     06/08/22 19:53 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog4.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/Delete1470net.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define MAX_1470NET_MEMO_PER_BLOCK  200

void
getFeedOn1470net2(
        const char *userID,
        const char *url,
        MyClipEx   **mp,
        int        *num,
        int        *cnt,
        int        unit
    )
{
    char        entryListURL[MAX_URLLENGTH];
    const char  *p, *q, *r;
    char        *response;
    int         sz = MAX_CONTENT_SIZE * 20;

    entryListURL[0] = NUL;
    p = strstr( url, "/2" );
    if ( p ) {
        int yyyy = 0, mm = 0, dd = 0;

        yyyy = atol( ++p );
        if ( yyyy >= 1970 ) {
            while ( *p && (*p != '/') )
                p++;
            if ( *p == '/' ) {
                if ( *++p == '0' )
                    p++;
                mm = atol( p );
            }
            while ( *p && (*p != '/') )
                p++;
            if ( *p == '/' ) {
                if ( *++p == '0' )
                    p++;
                dd = atol( p );
            }
        }

        if ( (yyyy > 0) && (mm > 0) && (dd > 0) )
            sprintf( entryListURL,
                     "http://1470.net/api/memo/daily?"
                     "userName=%s&"
                     "day=%04d-%02d-%02d",
                     userID, yyyy, mm, dd );
    }
    if ( !(entryListURL[0]) )
        sprintf( entryListURL,
                 "http://1470.net/api/memo/daily?"
                 "userName=%s",
                 userID );

    response = (char *)malloc( sz );
    if ( !response )
        return;

    // 当該年月日のエントリ(メモ)一覧を取得
    Sleep( 2000 );
    setUpReceiveBuffer( response, sz );
    http_get( entryListURL, response );
    if ( *response ) {
        // 各メモの情報を順に取得
        char    entryURL[MAX_URLLENGTH];
        char    *response2;
        int     len;

        response2 = (char *)malloc( sz );
        if ( !response2 ) {
            free( response );
            return;
        }

        p = response;
        while ( *p ) {
            q = strstr( p, "{\"id\" : " );
            if ( !q )
                break;
            q += 8;
            r = strchr( q, ',' );
            if ( !r )
                break;

            strncpy( ((*mp)[*num]).entryID, q, r - q );
            ((*mp)[*num]).entryID[r - q] = NUL;

            // 当該メモを取得
            Sleep( 2000 );
            sprintf( entryURL,
                     "http://1470.net/api/memo/%s",
                     ((*mp)[*num]).entryID );
            setUpReceiveBuffer( response2, sz );
            http_get( entryURL, response2 );
            if ( *response2 ) {
                char        *s, *t, *u;
                MyClipEx    *pp;

                pp = allocateMyClipExIfNecessary( mp, unit, cnt, *num );
                if ( !pp )
                    break;
                *mp = pp;

                // タイトル
                s = response2;
                t = strstr( s, "\"title\" : \"" );
                if ( !t )
                    break;
                s = t + 11;
                t = strstr( s, "\"," );
                if ( !t )
                    break;
                strncpy( ((*mp)[*num]).title, s, t - s );
                ((*mp)[*num]).title[t - s] = NUL;
                s = utf2sjis( ((*mp)[*num]).title );
                if ( s )
                    strcpy( ((*mp)[*num]).title, decodeString( s ) );

                s = t + 2;

                // コメント
                ((*mp)[*num]).comment[0] = NUL;
                t = strstr( s, "\"comment\" : \"" );
                if ( t ) {
                    s = t + 11;
                    t = strstr( s, "\"," );
                    if ( t ) {
                        len = t - s;
                        if ( len >= MAX_DESCRIPTION_LEN ) {
                            /* あふれた分を切り捨てる */
                            char    *temp = (char *)malloc( len + 1 );
                            if ( temp ) {
                                strncpy( temp, s, len );
                                temp[len] = NUL;

                                strcpy( ((*mp)[*num]).comment,
                                        justify( temp,
                                                 MAX_DESCRIPTION_LEN - 2 ) );

                                free( temp );
                            }
                        }
                        else if ( len > 0 ) {
                            strncpy( ((*mp)[*num]).comment, s, len );
                            ((*mp)[*num]).comment[len] = NUL;
                        }

                        if ( len > 0 ) {
                            /* 1470.netリニューアル版のコメントには <br /> */
                            /* が含まれ得る                                */
                            while ( (u = strstr( ((*mp)[*num]).comment,
                                                 "<br />"         )) != NULL )
                                strcpy( u, u + 6 ); /* <br /> を取り除く */

                            s = utf2sjis( ((*mp)[*num]).comment );
                            if ( s )
                                strcpy( ((*mp)[*num]).comment,
                                        decodeString( s ) );
                        }

                        s = t + 2;
                    }
                }

                // タグ
                ((*mp)[*num]).tags[0] = NUL;
                t = strstr( s, "\"tags\" : [" );
                if ( t ) {
                    s = t + 10;
                    t = strstr( s, "]," );
                    if ( t ) {
                        strncpy( ((*mp)[*num]).tags, s, t - s );
                        ((*mp)[*num]).tags[t - s] = NUL;
                        while ( (u = strstr( ((*mp)[*num]).tags,
                                             "\", \"")           ) != NULL ) {
                            *u = ' ';
                            strcpy( u + 1, u + 4 );
                        }
                        u = ((*mp)[*num]).tags;
                        strcpy( u, u + 1 );
                        u[strlen(u) - 1] = NUL;
                        s = utf2sjis( ((*mp)[*num]).tags );
                        if ( s )
                            strcpy( ((*mp)[*num]).tags, decodeString( s ) );

                        s = t + 2;
                    }
                }

                // URL
                t = strstr( s, "\"uri\" : [{\"url\" : \"" );
                if ( !t )
                    break;
                s = t + 19;
                t = strstr( s, "\"," );
                if ( !t )
                    break;
                strncpy( ((*mp)[*num]).url, s, t - s );
                ((*mp)[*num]).url[t - s] = NUL;

                (*num)++;
            }

            p = r + 1;
        }

        free( response2 );
    }

    free( response );
}

MyClipEx    *
get1470net2(
        const char       *username,
        const char       *password,
        const char       *username2,
        const char       *password2,
        AUTH_TYPE        authType,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL, *pp;
    char        target[MAX_URLLENGTH];
    char        url[MAX_URLLENGTH];
    char        userID[32];
    char        *response;
    char        *p, *q, *r, *s;
    int         num  = 0;
    int         cnt  = 0;
    int         unit = MAX_1470NET_MEMO_PER_BLOCK;
    int         sz   = MAX_CONTENT_SIZE * 20;
    int         len;
    int         ret;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    target[0]   = NUL;
    userID[0]   = NUL;
    bookmarkName.LoadString( IDS_TGT_1470NET );

    /* 1470.net にログイン */
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ログイン中 ……
    ret = login1470net( username, password, username2, password2, authType,
                        cookie, userID );
    if ( ret == 0 )
        return ( mp );  // ログイン失敗

    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ブックマーク情報取得中 ……"

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // マイページ(もしくは Feed を取得)
    //  http://1470.net/redirect/user/index (→ http://1470.net/user/ユーザ名)
    strcpy( url, "http://1470.net/redirect/user/index" );
    do {
        Sleep( 2000 );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( !(*response) )
            break;

        p = response;
        while ( *p ) {
            pp = allocateMyClipExIfNecessary( &mp, unit, &cnt, num );
            if ( !pp )
                break;
            mp = pp;

            q = strstr( p, "<p class=\"error\">" );
            if ( q ) {  // エラー発生時、当該ページは読み飛ばして、
                char    userID[64];

                q = strstr( response, "User.name = '" );
                if ( q ) {
                    q += 13;
                    r = strchr( q, '\'' );
                    if ( r ) {
                        strncpy( userID, q, r - q );
                        userID[r - q] = NUL;

                        // API 経由でエントリ一覧を取得
                        getFeedOn1470net2(userID, url, &mp, &num, &cnt, unit);
                    }
                }
                break;  // 次のページへ進む
            }
                // error の例: 1日の登録件数が多すぎるため、表示できません。

            q = strstr( p, "<li class=\"memo odd\">" );
            r = strstr( p, "<li class=\"memo even\">" );
            if ( !q && !r )
                break;
            if ( !q || (r && (q > r)) )
                q = r;

            p = strchr( q, '>' ) + 1;

            // タグ
            mp[num].tags[0] = NUL;
            q = strstr( p, "<span class=\"tags\">" );
            if ( !q )
                break;
            q += 19;
            s = strstr( q, "<br />" );
            if ( !s )
                break;
            while ( (r = strstr( q, "<span class=\"tag\">" )) != NULL ) {
                if ( r > s )
                    break;
                r += 18;
                q = strstr( r, "<a href=\"" );
                if ( !q || (q > s) )
                    break;
                r = strchr( q, '>' );
                if ( !r || (r > s) )
                    break;
                r++;
                while ( isWhiteSpace( *r ) )
                    r++;
                q = strstr( r, "</a>" );
                if ( !q || (q > s) )
                    break;

                len = mp[num].tags[0] == NUL ? 0 : strlen( mp[num].tags );
                if ( len > 0 ) {
                    strcat( mp[num].tags, " " );
                    len++;
                }
                strncat( mp[num].tags, r, q - r );
                mp[num].tags[len + (q - r)] = NUL;

                q += 4;
            }
            p = s + 6;
            s = utf2sjis( mp[num].tags );
            if ( s )
                strcpy( mp[num].tags, s );

            // タイトル
            q = strstr( p, "<span class=\"title\">" );
            if ( !q )
                break;
            q += 20;
            r = strstr( q, "</span>" );
            if ( !r )
                break;
            r += 7;
            while ( isWhiteSpace( *r ) )
                r++;
            q = strstr( r, "<span class=\"button\">" );
            if ( !q )
                break;
            p = q + 21;
            if ( isWhiteSpace( *(q - 1) ) )
                q--;
            strncpy( mp[num].title, r, q - r );
            mp[num].title[q - r] = NUL;
            s = utf2sjis( mp[num].title );
            if ( s )
                strcpy( mp[num].title, decodeString( s ) );

            // メモID
            q = strstr( p, "<a href=\"/tools/memo/" );
            if ( !q ) {
                q = strstr( p, "<a href=\"/tools/memo/new?resId=" );
                if ( !q )
                    break;
                q += 31;
            }
            else
                q += 21;
            r = strstr( q, "\">" );
            if ( !r )
                break;
            strncpy( mp[num].entryID, q, r - q );
            mp[num].entryID[r - q] = NUL;

            p = r + 2;

            // URL
            q = strstr( p, "<span class=\"count\">" );
            if ( !q )
                break;
            q += 20;
            r = strstr( q, "<a href=\"" );
            if ( !r )
                break;
            r += 9;
            q = strstr( r, "\">" );
            if ( !q )
                break;
            strncpy( mp[num].url, r, q - r );
            mp[num].url[q - r] = NUL;

            p = q + 2;

            // コメント (1470.net のコメントの長さは制限がないので、
            //           コメントが4096バイトより長い場合はあふれた
            //           部分を切り捨てる)
            mp[num].comment[0] = NUL;
            q = strstr( p, "<p class=\"comment\">" );
            if ( !q ) {
                q = strstr( p, "<p class=\"comment\" " );
                if ( !q )
                    break;
                q = strchr( q + 19, '>' );
                if ( !q )
                    break;
                q++;
            }
            else
                q += 19;
            if ( isWhiteSpace( *q ) )
                q++;
            r = strstr( q, "</p>" );
            s = strstr( q, "<span class=\"readMore\">" );
            if ( !r )
                break;
            p = r + 4;
            if ( s && (s < r) )
                r = s;
            len = r - q;
            if ( len >= MAX_DESCRIPTION_LEN ) {
                /* あふれた分を切り捨てる */
                char    *temp = (char *)malloc( len + 1 );
                if ( temp ) {
                    strncpy( temp, q, len );
                    temp[len] = NUL;

                    strcpy( mp[num].comment,
                            justify( temp, MAX_DESCRIPTION_LEN - 2 ) );

                    free( temp );
                }
            }
            else if ( len > 0 ) {
                strncpy( mp[num].comment, q, len );
                mp[num].comment[len] = NUL;
            }

            if ( len > 0 ) {
                /* 1470.netリニューアル版のコメントには <br /> が含まれ得る */
                while ( (q = strstr( mp[num].comment, "<br />" )) != NULL )
                    strcpy( q, q + 6 ); /* <br /> を取り除く */

                s = utf2sjis( mp[num].comment );
                if ( s )
                    strcpy( mp[num].comment, decodeString( s ) );
            }

            num++;
        }

        // 次へ
        p = strstr( response, "<div class=\"pageNavigationArea\">" );
        if ( !p )
            break;
        p += 32;
        q = strstr( p, "<a href=\"" );
        r = strchr( p, '|' );
        if ( !q || (q > r) )
            break;
        q += 9;
        r = strchr( q, '"' );
        if ( !r )
            break;
        strcpy( url, "http://1470.net" );
        strncat( url, q, r - q );
        url[15 + (r - q)] = NUL;
    } while ( *response );

    *numOfClips = num;
    free( response );

    return ( mp );
}

BOOL
deleteEntryOn1470net( char *cookie, MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    csrf[MAX_KEYLENGTH + 1];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    memset( request, 0x00, MAX_CONTENT_SIZE );

    // _csrf の取得
    csrf[0] = NUL;
    sprintf( url,
             "http://1470.net/tools/memo/%s",
             mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        char    *p, *q;
        p = strstr( response, "name=\"_csrf\" value=\"" );
        if ( p ) {
            p += 20;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( csrf, p, q - p );
                csrf[q - p] = NUL;
            }
        }

        if ( csrf[0] ) {
            // 削除実行
            sprintf( url,
                     "http://1470.net/tools/memo/%s",
                     mp->entryID );
            sprintf( request,
                     "_csrf=%s&"
                     "_delete_confirm=%s",
                     csrf, encodeURL( sjis2utf( "　削除確認　" ) ) );
            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );       // 削除確認
            if ( *response ) {
                sprintf( url,
                         "http://1470.net/tools/memo/%s",
                         mp->entryID );
                sprintf( request,
                         "_csrf=%s&"
                         "_delete=%s",
                         csrf, encodeURL( sjis2utf( "　削除実行　" ) ) );
                setUpReceiveBuffer( response, sz );
                http_postEx( url, "application/x-www-form-urlencoded",
                             request, response, cookie );   // 削除実行
                if ( *response )
                    ret = TRUE; // 注意: 1470.net のデータベースからは即座に
                                //       削除されるが、キャッシュにはしばらく
                                //       の間残ったままになる
            }
        }
    }

    free( response );
    free( request  );

    return ( ret );
}

void
Delete1470net(
        const char       *username,
        const char       *password,
        const char       *username2,
        const char       *password2,
        AUTH_TYPE        authType,
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
    MyClipEx            *mp;
    int                 numOfClips = 0;
    ProceedingDialog    *pdlg;
    CString             bookmarkName;

    cookie[0] = NUL;
    bookmarkName.LoadString( IDS_TGT_1470NET );

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }

    /* 削除用ブックマークID一覧の取得 */
#if 0
    mp = get1470net2( username, password, username2, password2, authType,
                      cookie, &numOfClips, pdlg );
#else
    DBSparam_t param;

    param.myBookmark     = NULL;
    param.numOfBookmarks = 0;
    param.bookmarkKind   = CUserInfo::BK_1470NET;
    memset( param.cookie, 0x00, MAX_COOKIE_LEN );
    param.dlg            = pdlg;
    param.u.authType     = authType;
    strcpy( param.u.username,  username );
    strcpy( param.u.password,  password );
    strcpy( param.u.username2, username2 );
    strcpy( param.u.password2, password2 );

    mp = GetBookmarksForDelete( &param, numOfClips );
#endif
    if ( !mp || (numOfClips == 0) ) {
        if ( mp )
            free( mp );

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

    // ブックマークを1件づつ削除
    strcpy( cookie, param.cookie );
    BOOL    *deleted = new BOOL[numOfClips];
    int     i;
    for ( i = 0; i < numOfClips; i++ )
        deleted[i] = FALSE;
    for ( i = 0; i < numOfClips; i++ ) {
        if ( deleted[i] == TRUE )
            continue;
        if ( withQuery ) {
            pdlg->ShowWindow( SW_HIDE );

            // ブックマーク情報を表示
            DeleteBookmarkDialog4   d;

            d.m_title   = mp[i].title;
            d.m_url     = mp[i].url;
            d.m_comment = mp[i].comment;
            d.m_tags    = mp[i].tags;
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
                                text,   // 残りのブックマークを全部一気に削除してしまっても構わないですね?    ",
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
        ret = deleteEntryOn1470net( cookie, &(mp[i]) );
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

    delete [] deleted;
    free( mp );
    if ( !dlg )
        delete pdlg;
}

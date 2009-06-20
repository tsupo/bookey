/*
 * clip loader <<putYJbookmark>>
 *
 *      OPML → Yahoo! ブックマーク 登録プログラム
 *          written by H.Tsujimura  16 Apr 2007
 *
 * History:
 * $Log: /comm/bookey/putYJbookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/12/02 19:39 Tsujimura543
 * フォーマットストリング脆弱性関連のバグ修正
 * 
 * 3     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 2     07/04/16 22:29 Tsujimura543
 * crumbs を GET するときの title を Shift_JIS にしていたのを UTF-8 に
 * するように変更
 * 
 * 1     07/04/16 22:03 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putYJbookmark.c 1     09/05/14 3:48 tsupo $";
#endif

BOOL
_putYJbookmark(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    url[MAX_URLLENGTH * 4];
    char    *p, *q;
    BOOL    ret = FALSE;
    char    crumbs[MAX_KEYLENGTH];

    errorString[0] = NUL;

    /* http://bookmarks.yahoo.co.jp/bookmarklet/showpopup (crumbs) を GET */
    crumbs[0] = NUL;
    p = any2utf( mp->title );
    sprintf( url,
             "http://bookmarks.yahoo.co.jp/bookmarklet/showpopup?"
             "t=%s&",
             encodeURL( p ? p : mp->title ) );
    sprintf( url + strlen( url ),
             "u=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "name=\"crumbs\" value=\"" );
        if ( p ) {
            p += 21;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( crumbs, p, q - p );
                crumbs[q - p] = NUL;
            }
        }
    }
    if ( !(crumbs[0]) )
        return ( ret );

    /* ブックマークを POST */
    strcpy( url, "http://bookmarks.yahoo.co.jp/bookmarklet/savebm" );
    sprintf( request,
             "tbact=save&"
             "crumbs=%s&",
             crumbs );

    // タイトル
    p = any2utf( chcode( (char *)(mp->title) ) );
    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( p ? p : mp->title ) );

    // URL
    sprintf( request + strlen(request),
             "url=%s&",
             encodeURL( mp->url ) );

    // タグ (空白区切り)
    p = any2utf( chcode( (char *)(mp->tags) ) );
    sprintf( request + strlen(request),
             "tags=%s&"
             "currentfid=0&",
             encodeURLex( p ? p : mp->tags ) );

    // 登録先フォルダ
    sprintf( request + strlen(request),
             "pfid=root&"
             "newname=&" );

    // コメント
    p = any2utf( chcode( (char *)(mp->comment) ) );
    sprintf( request + strlen(request),
             "desc=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // 公開設定
    sprintf( request + strlen(request),
             mp->publication == PUB_PRIVATE
                ? "visibility=0&"       // 非公開 (自分のみ)
                : "visibility=1&" );    // みんなに公開

    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL( sjis2utf("登録") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "<body onLoad=\"javascript:winClose()\">" ) )
            ret = TRUE; /* 登録成功 */
    }

    return ( ret );
}

void
putYJbookmark(
        const char   *userName,  /* (I) ユーザ名(Yahoo! Japan ID) */
        const char   *password,  /* (I) パスワード                */
        const MyClip *mp,        /* (I) ブックマーク情報          */
        int          numOfClips  /* (I) ブックマーク数            */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    // Yahoo! Japan ID でログイン
    ret = loginYahooJapan( userName, password, cookie );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "Yahoo! Japan Bookmark",
                      mp, numOfClips, cookie, cookieSize, NULL,
                      _putYJbookmark );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Yahoo! Japan への login に失敗しました\n"
                    : "Yahoo! Japan: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Yahoo! Japan へのログインに失敗しました。  "
                         : "Yahoo! Japan: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


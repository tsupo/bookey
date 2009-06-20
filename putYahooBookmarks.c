/*
 * clip loader <<putYahooBookmarks>>
 *
 *      OPML → Yahoo! Bookmarks 登録プログラム
 *          written by H.Tsujimura  18 Apr 2007
 *
 * History:
 * $Log: /comm/bookey/putYahooBookmarks.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/12/02 19:39 Tsujimura543
 * フォーマットストリング脆弱性関連のバグ修正
 * 
 * 4     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 3     07/04/19 20:18 Tsujimura543
 * 使用するタグの個数の上限を 5 から 20 に変更
 * 
 * 2     07/04/18 21:33 Tsujimura543
 * 登録に成功したかどうかを判断する条件を修正
 * 
 * 1     07/04/18 21:31 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putYahooBookmarks.c 1     09/05/14 3:48 tsupo $";
#endif

void
setTagsOnRequestOnYahooBookmarks( const char *tags, char *request )
{
    char        tmpTags[2048];
    const char  *p, *q;
    int         i;

    p = tags;
    for ( i = 0; i <= 19; i++ ) {
        q = strchr( p, ' ' );
        if ( q ) {
            strncpy( tmpTags, p, q - p );
            tmpTags[q - p] = NUL;
        }
        else
            strcpy( tmpTags, p );
        sprintf( request + strlen(request),
                 "tag[]=%s&",
                 encodeURL( tmpTags ) );
        if ( !q )
            break;
        p = q + 1;
    }
}

BOOL
_putYahooBookmarks(
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
    char    docid[MAX_KEYLENGTH];

    errorString[0] = NUL;

    /* http://bookmarks.yahoo.com/toolbar/savebm (crumbs) を GET */
    crumbs[0] = NUL;
    docid[0]  = NUL;
    p = any2utf( mp->title );
    sprintf( url,
             "http://bookmarks.yahoo.com/toolbar/savebm?"
             "t=%s&",
             encodeURL( p ? p : mp->title ) );
    sprintf( url + strlen( url ),
             "u=%s&"
             "ei=UTF-8",
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

        p = strstr( response, "name=\"docid\" id=\"docid\" value=\"" );
        if ( p ) {  // 通常は docid は空文字列
            p += 31;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( docid, p, q - p );
                docid[q - p] = NUL;
            }
        }
    }
    if ( !(crumbs[0]) )
        return ( ret );

    /* ブックマークを POST */
    strcpy( url, "http://bookmarks.yahoo.com/toolbar/addbm" );
    if ( docid[0] )
        sprintf( request,
                 "docid=%s&"
                 "crumbs=%s&",
                 docid, crumbs );
    else
        sprintf( request,
                 "docid=&"
                 "crumbs=%s&",
                 crumbs );

    // URL
    sprintf( request + strlen(request),
             "u=%s&"
             "v=&",
             encodeURL( mp->url ) );

    // タイトル
    p = any2utf( chcode( (char *)(mp->title) ) );
    sprintf( request + strlen(request),
             "t=%s&",
             encodeURLex2( p ? p : mp->title ) );

    // 登録先フォルダ
    sprintf( request + strlen(request),
             "newname=&"
             "pfidopt=0&"
             "fname=&"
             "pfid=&"
             "fid=0&" );

    // コメント
    p = any2utf( chcode( (char *)(mp->comment) ) );
    sprintf( request + strlen(request),
             "d=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // タグ (暫定的に20個まで)
    sprintf( request + strlen(request),
             "tags=yes&" );
    p = any2utf( chcode( (char *)(mp->tags) ) );
    setTagsOnRequestOnYahooBookmarks( p ? p : mp->tags, request );

    sprintf( request + strlen(request),
             "cache=yes&"
             "save=Save" );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response,
                     "<p>This bookmark was successfully saved</p>" ) )
            ret = TRUE; /* 登録成功 */
    }

    return ( ret );
}

void
putYahooBookmarks(
        const char   *userName,  /* (I) ユーザ名(Yahoo! ID) */
        const char   *password,  /* (I) パスワード          */
        const MyClip *mp,        /* (I) ブックマーク情報    */
        int          numOfClips  /* (I) ブックマーク数      */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    // Yahoo! ID でログイン
    ret = loginYahoo( userName, password, cookie );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( "Yahoo! Bookmarks",
                      mp, numOfClips, cookie, cookieSize, NULL,
                      _putYahooBookmarks );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Yahoo! への login に失敗しました\n"
                    : "Yahoo!: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Yahoo! へのログインに失敗しました。  "
                         : "Yahoo!: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}

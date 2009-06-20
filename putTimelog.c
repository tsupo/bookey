/*
 * clip loader <<putTimelog>>
 *
 *      OPML → Timelog 発言プログラム
 *          written by H.Tsujimura  23 May 2007
 *
 * History:
 * $Log: /comm/bookey/putTimelog.c $
 * 
 * 2     09/06/11 2:57 tsupo
 * 0.62a版
 * 
 * 4     09/06/10 20:55 Tsujimura543
 * Timelog 投稿時のレスポンスが空文字列に変更されたのに伴う修正
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 2     07/09/05 18:58 Tsujimura543
 * UserAgent 回りをリファクタリング
 * 
 * 1     07/05/23 16:59 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putTimelog.c 2     09/06/11 2:57 tsupo $";
#endif

typedef struct paramForTimelog  {
    char    userName[MAX_NAMELEN + 1];  /* ユーザ名(メールアドレス) */
    char    password[MAX_NAMELEN + 1];  /* パスワード               */
    char    version[MAX_NAMELEN + 1];   /* userAgent 版数           */
    char    url[MAX_URLLENGTH + 1];     /* userAgent 関連Webページ  */
    char    resource[MAX_URLLENGTH + 1];/* userAgent 関連XML        */
}   PARAM_TIMELOG;


BOOL
_putTimelog(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char            *request  = args->request;
    char            *response = args->response;
    size_t          sz        = args->sz;
    PARAM_TIMELOG   *arg = (PARAM_TIMELOG *)args->args; 
    char            url[MAX_URLLENGTH * 4];
    char            userAgent[BUFSIZ];
    char            monologue[MAX_DESCRIPTION_LEN];
    char            *p, *q;
    BOOL            ret = FALSE;
    int             i;
    char            tag[80];

    /*
     * 「(どこかのソーシャルブックマークに)ブックマークを POST したこと」
     * を報告
     */
    errorString[0] = NUL;
    strcpy( url, "http://api.timelog.jp/new.asp" );
    sprintf( monologue,
             "/B %s %s",
             mp->url, mp->title );
    p = any2utf( monologue );
    if ( p )
        strcpy( monologue, p );
    sprintf( request,
             "remsgid=&"
             "text=%s",
             encodeURL( monologue ) );

    // タグ (とりあえず最大10個までにしておく)
    if ( mp->tags[0] )
        strcat( request, " " );
    p = any2utf( mp->tags );
    q = p ? p : mp->tags;
    i = 0;
    do {
        p = strchr( q, ' ' );
        if ( p ) {
            strncpy( tag, q, p - q );
            tag[p - q] = NUL;
            sprintf( request + strlen(request),
                     "[%s]",
                     encodeURL( tag ) );
            i++;
            q = p + 1;
        }
        else {
            sprintf( request + strlen(request),
                     "[%s]",
                     encodeURL( q ) );
            break;
        }
    } while ( (i < 10) && *q );

    sprintf( userAgent,
             "bookey/%s (%s)\r\n"
             "X-Timelog-Client: bookey\r\n"
             "X-Timelog-Client-Version: %s\r\n"
             "X-Timelog-Client-URL: %s",
             arg->version, arg->url, arg->version, arg->resource );
    setUserAgent( userAgent );  /* User-Agent を一時的に変更 */

    setUpReceiveBuffer( response, sz );
    http_postBASIC( url, arg->userName, arg->password,
                    "application/x-www-form-urlencoded",
                    request, response );
    if ( *response ) {
        if ( strstr( response, "OK" ) )
            ret = TRUE; /* 投稿成功 */
    }
    else {
        unsigned short status = getStatusCode();
        if ( status / 100 == 2 )    // 200 OK (～ 299) なら成功とみなす
            ret = TRUE; /* 投稿成功 */
    }

    setUserAgent( NULL );       /* User-Agent を元に戻す */

    return ( ret );
}

void
putTimelog(
        const char   *userName,  /* (I) ユーザ名                */
        const char   *password,  /* (I) パスワード              */
        const char   *version,   /* (I) userAgent 版数          */
        const char   *url,       /* (I) userAgent 関連Webページ */
        const char   *resource,  /* (I) userAgent 関連XML       */
        const MyClip *mp,        /* (I) ブックマーク情報        */
        int          numOfClips  /* (I) ブックマーク数          */
    )
{
    PARAM_TIMELOG   arg;

    strcpy( arg.userName, userName );
    strcpy( arg.password, password );
    strcpy( arg.version,  version );
    strcpy( arg.url,      url );
    strcpy( arg.resource, resource );
    putBookmarks( "Timelog",
                  mp, numOfClips, NULL, 0, &arg, _putTimelog );
}

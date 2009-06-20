/*
 * clip loader <<putTwitter>>
 *
 *      OPML → Twitter 発言プログラム
 *          written by H.Tsujimura  10 Apr 2007
 *
 * History:
 * $Log: /comm/bookey/putTwitter.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 25    09/04/09 18:17 Tsujimura543
 * コメント修正
 * 
 * 24    09/04/09 18:16 Tsujimura543
 * OAuth 認証エラーが発生しているかどうかを判定するのに http レスポンス
 * コードが 401 かどうかも見るようにしてみた
 * 
 * 23    09/04/09 17:53 Tsujimura543
 * OAuth 認証エラー時のレスポンス仕様変更に伴う修正を実施
 * 
 * 22    09/04/07 15:46 Tsujimura543
 * OAuth で "Invalid OAuth Request" が発生したときの処理を追加
 * 
 * 21    09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 20    08/11/17 11:33 Tsujimura543
 * getTinyURL() を修正 (いつの間にか、tinyurl の返すレスポンスの
 * フォーマットが変わっていた)
 * -- cxxさんの http://twitter.com/cxx/status/1000191856 による
 * -- 指摘で発見。Thanks!
 * 
 * 19    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 18    07/09/05 18:58 Tsujimura543
 * UserAgent 回りをリファクタリング
 * 
 * 17    07/07/10 22:32 Tsujimura543
 * 「発言」の POST 時のパラメータに source=API名 を追加してみた
 * 
 * 16    07/07/02 16:30 Tsujimura543
 * Twitter への投稿時、記事タイトルが文字化けすることがある不具合に対処
 * 
 * 15    07/06/19 0:00 Tsujimura543
 * Twitter への投稿時、Webページのタイトル部分が文字化けすることがある
 * 不具合に対処
 * 
 * 14    07/05/23 17:42 Tsujimura543
 * メインテナンス中画面が返ってきた場合は、その旨、errorString に設定する
 * ようにした
 * 
 * 13    07/05/22 20:39 Tsujimura543
 * POST に対する応答が空白文字のみのときも投稿成功とみなすようにした
 * (投稿に成功しているとは限らないが、成功していることが多いため)
 * 
 * 12    07/05/11 19:10 Tsujimura543
 * Twitter に送る bookey の版数をリソースから取得したものを使うように
 * してみた
 * 
 * 11    07/05/11 18:45 Tsujimura543
 * normalizeDescription() を修正
 * 
 * 10    07/04/12 18:29 Tsujimura543
 * ブックマーク対象 URL が25バイト以上のときは tinyurl するようにした
 * 
 * 9     07/04/12 16:18 Tsujimura543
 * ? や # が含まれる URL も問題なく tinyurl できるように対策してみた
 * 
 * 8     07/04/11 17:58 Tsujimura543
 * User-Agent を chirrup から bookey に変更
 * 
 * 7     07/04/11 15:00 Tsujimura543
 * (1) tinyurl で取得した短縮URL にゴミ(chunked)がつくことがある現象に対処
 * (2) User-Agent を chirrup に挿げ替えて Twitter にリクエストを発行するよ
 *     うにした
 * 
 * 6     07/04/10 21:56 Tsujimura543
 * TWITTER → Twitter で統一
 * 
 * 5     07/04/10 21:55 Tsujimura543
 * getTinyURL() を修正 [tinyurl がうまくリダイレクトできない短縮URLを
 * 生成することがあるので、対策を実施]
 * 
 * 4     07/04/10 19:07 Tsujimura543
 * 「末尾に空白文字を付加」してから投稿するようにした
 * 
 * 3     07/04/10 17:16 Tsujimura543
 * 発言内容の末尾を切り捨てた場合は ... を付けるようにした
 * 
 * 2     07/04/10 17:12 Tsujimura543
 * 発言内容が160バイトより長い場合は、あふれた部分を捨ててから投稿する
 * ようにした
 * 
 * 1     07/04/10 16:46 Tsujimura543
 * 最初の版
 */

#include "myClip.h"
#include "sha1.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putTwitter.c 1     09/05/14 3:48 tsupo $";
#endif

typedef struct paramForTwitter  {
    BOOL    useOAuth;                   /* OAuth 認証を使うかどうか */
    char    userName[MAX_NAMELEN + 1];  /* ユーザ名(メールアドレス) */
    char    password[MAX_NAMELEN + 1];  /* パスワード               */
    char    token[MAX_KEYLENGTH + 1];   /* アクセストークン         */
    char    secret[MAX_KEYLENGTH + 1];  /* アクセストークン秘密鍵   */
    char    version[MAX_NAMELEN + 1];   /* userAgent 版数           */
    char    url[MAX_URLLENGTH + 1];     /* userAgent 関連Webページ  */
    char    resource[MAX_URLLENGTH + 1];/* userAgent 関連XML        */
}   PARAM_TWITTER;

#define MAX_DESCRIPTION_LENGTH          160
#define MAX_DESCRIPTION_BYTES_IN_SJIS   100
          // UTF-8で160バイト以下 → (Shift_JIS で)106文字以下
          //                      → やや余裕を持たせて 100文字以下にする

char    *TwitterOAuthConsumerKey();
char    *TwitterOAuthConsumerSecret();

void
makeOAuthBase(
        const char *oauthToken,
        const char *oauthTokenSecret,
        const char *url,
        const char *method,
        char       *key,
        char       *base,
        char       *param
    )
{
    time_t  t = time( NULL );
    char    nonce[MAX_KEYLENGTH];

    strcpy( nonce, getNonce(NULL) );

    sprintf( key,
             "%s&",
             encodeURLi( TwitterOAuthConsumerSecret(), FALSE ) );
    sprintf( key + strlen(key),
             "%s",
             encodeURLi( oauthTokenSecret, FALSE ) );

    sprintf( base,
             "%s&"
             "%s&",
             method,
             encodeURLi( url, FALSE ) );

    sprintf( param[0] ? param + strlen(param) : param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_version=1.0",
             TwitterOAuthConsumerKey(),
             nonce,
             t,
             oauthToken );
}

void
makeOAuthRequest(
        const char *url,
        char       *request,
        char       *key,
        char       *base,
        char       *param
    )
{
    char    digest[SHA1HashSize * 4];

    sprintf( base + strlen(base),
             "%s",
             encodeURLi( param, FALSE ) );

    memset( digest, 0x00, SHA1HashSize );
    hmac_sha1( (unsigned char *)base, strlen(base),
               (unsigned char *)key,  strlen(key),
               digest );
    strcpy( digest, base64( (unsigned char *)digest, SHA1HashSize ) );

    sprintf( request,
             "%s?"
             "%s&"
             "oauth_signature=%s",
             url,
             param,
             encodeURLi( digest, TRUE ) );
}


static char *
normalizeDescription( char *description )
{
    char    *p;

    if ( strlen( description ) > MAX_DESCRIPTION_BYTES_IN_SJIS ) {
        char    *s = description;
        int     kanjiFlag = 0;
        int     i = 0;

        while ( *s ) {
            if ( ++i > MAX_DESCRIPTION_BYTES_IN_SJIS )
                break;
            if ( kanjiFlag == 0 ) {
                if ( iskanji1( *s ) )
                    kanjiFlag = 1;
            }
            else
                kanjiFlag = ((kanjiFlag + 1) % 3);
            *s++;
        }
        switch ( kanjiFlag ) {
        case 0:
            *s = NUL;
            break;
        case 1:
            *(s - 1) = NUL;
            break;
        case 2:
            *(s - 2) = NUL;
            break;
        }

        strcat( description, "...\"" );
    }

    p = any2utf( description );

    return ( p ? p : description );
}


char    *
getTinyURL( const char *targetURL,
            char       *request,
            char       *response,
            size_t     sz )
{
    char    url[MAX_URLLENGTH];

    if ( !strchr( targetURL, '#' ) &&
         !strchr( targetURL, '?' )    ) {
        sprintf( url,
                 "http://tinyurl.com/api-create.php?url=%s", targetURL );

        setUpReceiveBuffer( response, sz );
        http_get( url, response );
        if ( response[0] ) {
            char    *p = strstr( response, "http" );

            if ( p && (response < p) )
                strcpy( response, p );

            p = strchr( response, '\r' );
            if ( !p )
                p = strchr( response, '\n' );
            if ( p )
                *p = NUL;
        }
    }
    else {
        strcpy( url, "http://tinyurl.com/create.php" );
        sprintf( request, "url=%s", encodeURL(targetURL) );
        setUpReceiveBuffer( response, sz );
        http_post( url, "application/x-www-form-urlencoded",
                   request, response );
        if ( *response ) {
            char    *p = strstr( response,
                                 "<input type=hidden name=tinyurl value=\"" );
            if ( p )
                p += 39;
            else {
                char *q = strstr( response, "<h1>TinyURL was created!</h1>" );
                if ( !q )
                    q = strstr( response, "<blockquote" );
                if ( q ) {
                    p = strstr( q, "[<a href=\"" );
                    if ( p )
                        p += 10;
                }
            }
            if ( p ) {
                char    *q = strchr( p, '"' );
                if ( q ) {
                    strncpy( response, p, q - p );
                    response[q - p] = NUL;
                }
            }
            else
                response[0] = NUL;
        }
    }

    return ( response[0] ? response : NULL );
}

BOOL
_putTwitter(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char            *request  = args->request;
    char            *response = args->response;
    size_t          sz        = args->sz;
    PARAM_TWITTER   *arg = (PARAM_TWITTER *)args->args; 
    char            url[MAX_URLLENGTH * 4];
    char            userAgent[BUFSIZ];
    char            monologue[MAX_DESCRIPTION_LEN];
    char            *p;
    BOOL            ret = FALSE;

    /*
     * 「(どこかのソーシャルブックマークに)ブックマークを POST したこと」
     * を報告
     */
    errorString[0] = NUL;
    strcpy( url, "http://twitter.com/statuses/update.xml" );
    sprintf( monologue,
             "Bookmarked %s - \"%s\"",
             (strlen(mp->url) >= 25)                    ||
             (strlen(mp->url) + strlen(mp->title) > 80)
                ? getTinyURL( mp->url, request, response, sz )
                : mp->url,
             mp->title );
    if ( strlen( monologue ) > MAX_DESCRIPTION_LENGTH ) {
        p = any2sjis( monologue );
        if ( p ) {
            char    temp[MAX_DESCRIPTION_LEN];
            strcpy( temp, p );
            p = normalizeDescription( temp );
            if ( p )
                strcpy( monologue, p );
        }
    }
 // strcat( monologue, " " ); /* 末尾に空白文字を付加 */

    sprintf( userAgent,
             "bookey/%s (%s)\r\n"
             "X-Twitter-Client: bookey\r\n"
             "X-Twitter-Client-Version: %s\r\n"
             "X-Twitter-Client-URL: %s",
             arg->version, arg->url, arg->version, arg->resource );
    setUserAgent( userAgent );  /* User-Agent を一時的に変更 */

    p = any2utf( monologue );
    if ( arg->useOAuth ) {
        // OAuth 認証
        char    key[MAX_KEYLENGTH * 2];
        char    base[MAX_CONTENT_SIZE];
        char    param[MAX_CONTENT_SIZE];

        key[0]   = NUL;
        base[0]  = NUL;
        param[0] = NUL;
        makeOAuthBase(arg->token, arg->secret, url, "POST", key, base, param);

        sprintf( param + strlen(param),
                 "&"
                 "source=%s&"
                 "status=%s",
                 "bookey",
                 encodeURLi( p ? p : monologue, FALSE ) );

        makeOAuthRequest( url, request, key, base, param );

        setUpReceiveBuffer( response, sz );
        http_postBASIC( request, NULL, NULL,
                        "application/x-www-form-urlencoded",
                        "", response );
    }
    else {
        // BASIC 認証
        sprintf( request,
                 "status=%s&"
                 "source=%s",
                 encodeURL( p ? p : monologue ),
                 "bookey" );
        setUpReceiveBuffer( response, sz );
        http_postBASIC( url, arg->userName, arg->password,
                        "application/x-www-form-urlencoded",
                        request, response );
    }
    if ( *response ) {
        if ( strstr( response, "<created_at>" ) || (*response == ' ') )
            ret = TRUE; /* 投稿成功 */
        else {
            unsigned short responseCode = getStatusCode();

            getCurrentLocation( url );
            if ( strstr( url, "maintenance" ) )
                strcpy( errorString, "Now maintenance ..." );
            else if ( ( arg->useOAuth && (responseCode == 401) )  ||
                      strstr( response, "Invalid OAuth Request" ) ||
                      strstr( response,
                          "Failed to validate oauth signature or token" ) ) {
                LCID    l = getLanguageCode();

                strcpy( errorString,
                        l == 0x0411
                          ? "OAuth 認証に失敗しました。\r\n"
                            "アクセストークンを取得し直してください。"
                          : "Failed to authenticate.\r\n"
                            "Get a new 'Access Token', again.");
            }
        }
    }

    setUserAgent( NULL );       /* User-Agent を元に戻す */

    return ( ret );
}

void
putTwitter(
        const char   *userName,  /* (I) ユーザ名(メールアドレス) */
        const char   *password,  /* (I) パスワード               */
        const char   *token,     /* (I) アクセストークン         */
        const char   *secret,    /* (I) アクセストークン秘密鍵   */
        AUTH_TYPE    authType,   /* (I) 認証タイプ               */
        const char   *version,   /* (I) userAgent 版数           */
        const char   *url,       /* (I) userAgent 関連Webページ  */
        const char   *resource,  /* (I) userAgent 関連XML        */
        const MyClip *mp,        /* (I) ブックマーク情報         */
        int          numOfClips  /* (I) ブックマーク数           */
    )
{
    PARAM_TWITTER   arg;

    arg.useOAuth = authType == AK_OAUTH ? TRUE : FALSE;

    strcpy( arg.userName, userName );
    strcpy( arg.password, password );
    strcpy( arg.token,    token );
    strcpy( arg.secret,   secret );
    strcpy( arg.version,  version );
    strcpy( arg.url,      url );
    strcpy( arg.resource, resource );
    putBookmarks( "Twitter",
                  mp, numOfClips, NULL, 0, &arg, _putTwitter );
}

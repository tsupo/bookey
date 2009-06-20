/*
 * clip loader <<putDigg>>
 *
 *      OPML → digg 登録プログラム
 *          written by H.Tsujimura  9 Jul 2007
 *
 * History:
 * $Log: /comm/bookey/putDigg.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     07/10/10 22:40 Tsujimura543
 * (1) CAPTCHA画像の URL 構成変更に対応
 * (2) CAPTCHA画像の取得に cookie が必要になったのに対応
 * (3) カテゴリ名に空白文字が含まれる場合に対応できてなかった → 修正
 * 
 * 6     07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 5     07/08/28 23:31 Tsujimura543
 * digg のデザイン変更に伴い、getDiggCatID() を修正
 * 
 * 4     07/07/10 20:59 Tsujimura543
 * digg の投票もうまくいくようになった
 * 
 * 3     07/07/10 19:37 Tsujimura543
 * 「すでに誰かが digg している場合」のルートを実装。現在、コメント投稿
 * には成功するが、digg の投票は失敗する
 * 
 * 2     07/07/10 1:01 Tsujimura543
 * inputCaptchaString() の引数追加とそれに伴う各種変更
 * 
 * 1     07/07/10 0:09 Tsujimura543
 * 新規作成 (「まだ誰も digg してない場合」のルートのみ動作確認終了)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDigg.c 1     09/05/14 3:48 tsupo $";
#endif


int
getDiggCatID( const char *topic, const char *response )
{
    int         catID = 0;
    const char  *p = response;
    const char  *q;
    const char  *r;
    char        targetString[BUFSIZ];

    q = strstr( topic, " - " );
    if ( q )
        q += 3;
    else
        q = topic;
    sprintf( targetString, "name=\"catid\" id=\"%s\"", q );

    r = strstr( p, targetString );
    if ( !r ) {
        char    *s = targetString + strlen("name=\"catid\" id=\"");
        while ( *s ) {
            if ( *s == ' ' )
                *s = '_';
            else
                *s = (char)tolower( *s );
            s++;
        }
        r = strstr( p, targetString );
    }
    if ( !r )
        r = strstr( p, q );
    if ( r ) {
        const char  *s;

        s = strstr( r, "value=\"" );
        if ( s )
            catID = atol( s + 7 );
    }

    return ( catID );
}

char    *
generateDiggTitle( char *title, const char *origTitle )
{
    char                buf[BUFSIZ];
    const unsigned char *p;
    char                *q = buf;
    BOOL                nonAscii = FALSE;
    int                 cnt = 0;

    p = (unsigned char *)any2utf( origTitle );
    if ( !p )
        p = (unsigned char *)origTitle;

    while ( *p ) {
        if ( (*p < 0x20) || (*p >= 0x80) ) {
            nonAscii = TRUE;
            break;
        }
        *q++ = *p++;
        cnt++;
        if ( cnt >= BUFSIZ )
            break;
    }
    *q = NUL;

    if ( nonAscii )
        strcpy( title, buf );
    else
        strcpy( title, origTitle );

    return ( title );
}

char    *
generateDiggComment( char       *comment,
                     const char *origComment,
                     CAP_MODE   mode )
{
    const unsigned char *p = (unsigned char *)origComment;
    BOOL                nonAscii = FALSE;

    if ( mode == CAP_MAKE_STORY ) {
        while ( *p ) {
            if ( *p >= 0x80 ) {
                nonAscii = TRUE;
                break;
            }
            p++;
        }
    }

    if ( nonAscii )
        strcpy( comment, "No comment." );
    else
        strcpy( comment, origComment );

    return ( comment );
}

void
getDiggSubmitPage( const char *targetURL,
                   char       *key,
                   char       *request,
                   char       *response,
                   size_t     sz,
                   char       *cookie )
{
    char    url[MAX_URLLENGTH * 16];

    // http://digg.com/submit を GET (key を取得)
    strcpy( url, "http://digg.com/submit" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        const char  *p, *q;

        p = strstr( response, "name=\"key\" value=\"" );
        if ( p ) {
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( key, p, q - p );
                key[q - p] = NUL;
            }
        }
    }

    if ( key[0] ) {
        // http://digg.com/submit へ URL を POST
        sprintf( request,
                 "url=%s&"
                 "phase=1&"
                 "key=%s",
                 encodeURL( targetURL ),
                 key );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
    }
}

BOOL
_putDiggFirst( const MyClip *mp,
               char         *key,
               char         *request,
               char         *response,
               size_t       sz,
               char         *cookie )
{
    BOOL        ret   = FALSE;
    int         catID = 0;
    char        key2[MAX_KEYLENGTH];
    char        url[MAX_URLLENGTH * 16];
    char        title[BUFSIZ];
    char        comment[BUFSIZ];
    char        captchaString[BUFSIZ];
    char        topic[MAX_KEYLENGTH];
    const char  *p, *q;

    title[0]         = NUL;
    comment[0]       = NUL;
    captchaString[0] = NUL;
    topic[0]         = NUL;

    //  -- key
    p = strstr( response, "name=\"key\" value=\"" );
    if ( p ) {
        p += 18;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( key, p, q - p );
            key[q - p] = NUL;
        }
    }

    key2[0] = NUL;
    p = strstr( response, "generateAudioCaptcha(\"" );
    if ( p ) {
        // CAPTCHA の入力
        p += 22;
        q = strchr( p, '"' );
        if ( q ) {
            if ( *p == '/' )
                p++;
            strncpy( key2, p, q - p );
            key2[q - p] = NUL;
            p = strstr( key2, ".mp3" );
            if ( p )
                *(char *)p = NUL;
        }
        if ( key2[0] ) {
            sprintf( url, "http://digg.com/%s.jpg", key2 );
            if ( title[0] == NUL )
                generateDiggTitle( title, mp->title );
            if ( comment[0] == NUL )
                generateDiggComment( comment, mp->comment, CAP_MAKE_STORY );
            inputCaptchaString( url, cookie,
                                captchaString,
                                title, comment, topic,
                                CAP_MAKE_STORY );
            catID = getDiggCatID( topic, response );
        }
    }

    if ( captchaString[0] ) {
        // 投稿
        if ( title[0] == NUL )
            generateDiggTitle( title, mp->title );
        if ( comment[0] == NUL )
            generateDiggComment( comment, mp->comment, CAP_MAKE_STORY );

        sprintf( url,
                 "http://digg.com/submit?"
                 "title=%s&",
                 encodeURL( title ) );
        sprintf( url + strlen(url),
                 "bodytext=%s&"
                 "catid=%d&"
                 "captchatext=%s&"
                 "captchaid=%s&"
                 "submit=Submit+Story&",
                 encodeURL( comment ),
                 catID,
                 captchaString,
                 (p = strchr( key2, '/' )) != NULL ? p + 1 : key2 );
        sprintf( url + strlen(url),
                 "url=%s&"
                 "phase=3&"
                 "key=%s",
                 encodeURL( mp->url ),
                 key );

        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
    }

    if ( *response ) {
        p = strstr( response,
                    "<h3>We think your story might be a duplicate of "
                    "one that was submitted by someone else.</h3>" );
        if ( p ) {
            // 投稿確認 (類似 story 一覧提示)
            //  -- key
            p = strstr( response, "name=\"key\" value=\"" );
            if ( p ) {
                p += 18;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( key, p, q - p );
                    key[q - p] = NUL;
                }
            }

            strcpy( url, "http://digg.com/submit" );
            sprintf( request,
                     "submit=Continue%%2C+Submit&"
                     "title=%s&",
                     encodeURL( title ) );
            sprintf( request + strlen(request),
                     "url=%s&",
                     encodeURL( mp->url ) );
            sprintf( request + strlen(request),
                     "bodytext=%s&"
                     "blogtext=&"
                     "category=%d&"
                     "phase=4&"
                     "dupes=1&"
                     "key=%s",
                     encodeURL( comment ),
                     catID,
                     key );

            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );
        }
    }

    if ( *response ) {
        p = strstr( response,
                    "<h3>Success! Your story has been submitted.</h3>" );
        if ( p )
            ret = TRUE; /* 登録成功 */
    }

    return ( ret );
}

BOOL
_putDiggComment( const MyClip *mp,
                 char         *key,
                 char         *request,
                 char         *response,
                 size_t       sz,
                 char         *cookie,
                 char         *errorString )
{
    BOOL        ret   = FALSE;
    char        url[MAX_URLLENGTH * 16];
    char        title[BUFSIZ];
    char        comment[BUFSIZ];
    char        captchaString[BUFSIZ];
    char        topic[MAX_KEYLENGTH];
    char        key2[MAX_KEYLENGTH];
    char        keyname[MAX_KEYLENGTH];
    char        postToken[MAX_KEYLENGTH];
    char        storyID[MAX_KEYLENGTH];
    const char  *p, *q;

    title[0]         = NUL;
    comment[0]       = NUL;
    captchaString[0] = NUL;
    topic[0]         = NUL;
    postToken[0]     = NUL;
    storyID[0]       = NUL;
    key2[0]          = NUL;
    keyname[0]       = NUL;

    //  -- title
    p = strstr( response, "<title>Digg - " );
    if ( p ) {
        p += 14;
        q = strstr( p, "</title>" );
        if ( q ) {
            strncpy( title, p, q - p );
            title[q - p] = NUL;
        }
    }

    //  -- topic
    p = strstr( response, "<dt>Topic:</dt>" );
    if ( p ) {
        p += 15;
        q = strstr( p, "<a href=\"/view/" );
        if ( q ) {
            q += 15;
            p = strchr( q, '>' );
            if ( p ) {
                p++;
                q = strstr( p, "</a>" );
                if ( q ) {
                    strncpy( topic, p, q - p );
                    topic[q - p] = NUL;
                    strcat( topic, " - " );

                    p = strstr( q + 4, "\">" );
                    if ( p ) {
                        p += 2;
                        q = strstr( p, "</a>" );
                        if ( q ) {
                            size_t  len = strlen( topic ); 
                            strncat( topic, p, q - p );
                            topic[len + (q - p)] = NUL;
                        }
                    }
                }
            }
        }
    }

    //  -- storyID
    p = strstr( response, "=\"storyid\" value=\"" );
    if ( p ) {
        p += 18;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( storyID, p, q - p );
            storyID[q - p] = NUL;
        }
    }

    //  -- post
    p = strstr( response, "'post' : '" );
    if ( p ) {
        p += 10;
        q = strchr( p, '\'' );
        if ( q ) {
            strncpy( postToken, p, q - p );
            postToken[q - p] = NUL;
        }
    }

    // CAPTCHA 画像 URL の取得
    //  -- keyname → CAPTCHA画像のURL
    p = strstr( response, "'captcha' : '" );
    if ( p ) {
        p += 13;
        q = strchr( p, '\'' );
        if ( q ) {
            strncpy( keyname, p, q - p );
            keyname[q - p] = NUL;
        }
    }
    if ( keyname[0] ) {
        sprintf( url,
                 "http://digg.com/get_captcha?keyname=%s",
                 keyname );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        if ( *response ) {
            p = strstr( response, "generateAudioCaptcha(\"" );
            if ( p ) {
                p += 22;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( key2, p, q - p );
                    key2[q - p] = NUL;
                }
            }
        }
    }

    if ( key2[0] ) {
        // CAPTCHA の入力
        sprintf( url, "http://digg.com/%s.jpg", key2 );
        if ( title[0] == NUL )
            generateDiggTitle( title, mp->title );
        if ( comment[0] == NUL )
            generateDiggComment( comment, mp->comment,
                                 CAP_POST_COMMENT );
        inputCaptchaString( url, cookie,
                            captchaString,
                            title, comment, topic,
                            CAP_POST_COMMENT );
    }
    
    // コメントを投稿
    strcpy( url, "http://digg.com/ajax/comments/post" );
    p = any2utf( comment );
    sprintf( request,
             "parent=0&"
             "comments=%s&",
             encodeURL( p ? p : comment ) );
    sprintf( request + strlen(request),
             "token=%s&"
             "itemid=%s&"
             "md5=%s&"
             "captcha=%s",
             postToken,
             storyID,
             key2,
             captchaString );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        p = strstr( response, "\"success\":true" );
        if ( p )
            ret = TRUE; /* 登録成功 */
        else {
            p = strstr( response, "\"success\":false" );
            if ( p ) {
                p = strstr( response, "\"error\":\"" );
                if ( p ) {
                    p += 9;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( errorString, p, q - p );
                        errorString[q - p] = NUL;
                    }
                }
            }
        }
    }

    // 投票する (digg 1 up)
    //  -- 改めて Story ページを取得
    p = NULL;
    getDiggSubmitPage( mp->url, key, request, response, sz, cookie );
    if ( *response )
        p = strstr( response, "javascript:dig(" );
    if ( p ) {
        char    row[MAX_KEYLENGTH];
        char    digicheck[MAX_KEYLENGTH];

        row[0]       = NUL;
        digicheck[0] = NUL;

        // -- row
        p += 16;
        q = strchr( p, ',' );
        if ( q ) {
            strncpy( row, p, q - p );
            row[q - p] = NUL;
            p = q + 1;
        }

        // -- itemID
        if ( storyID[0] == NUL ) {
            q = strchr( p, ',' );
            if ( q ) {
                strncpy( storyID, p, q - p );
                storyID[q - p] = NUL;
                p = q + 1;
            }
        }

        // -- digicheck
        q = strchr( p, '\'' );
        if ( q ) {
            p = q + 1;
            q = strchr( p, '\'' );
            if ( q ) {
                strncpy( digicheck, p, q - p );
                digicheck[q - p] = NUL;
            }
        }

        strcpy( url, "http://digg.com/diginfull" );
        sprintf( request,
                 "id=%s&"
                 "row=%s&"
                 "digcheck=%s&"
                 "type=s&"
                 "loc=permalink",
                 storyID,
                 row,
                 digicheck );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
    }

    return ( ret );
}

BOOL
_putDigg(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    key[MAX_KEYLENGTH];
    BOOL    ret = FALSE;

    errorString[0] = NUL;
    key[0]         = NUL;

    getDiggSubmitPage( mp->url, key, request, response, sz, cookie );
    if ( *response ) {
        const char  *p, *q;

        p = strstr( response,
                    "<legend>Choose the Most Appropriate Topic</legend>" );
        q = strstr( response,
                    "<h3>Cool, this story has already been submitted.</h3>" );
        if ( p ) {
            // まだ誰も digg してない場合
            ret = _putDiggFirst( mp, key, request, response, sz, cookie );
        }
        else if ( q ) {
            // すでに誰かが digg している場合
            //   -- すでに自分で digg 済みの場合も含む
            ret = _putDiggComment( mp, key, request, response, sz, cookie,
                                   errorString );
        }
    }

    return ( ret );
}

void
putDigg(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    setUserAgent( "Mozilla/4.0 (compatible; MSIE 6.0)" );   /* @@ */

    /* digg に login */
    ret = loginDigg( userName, password, cookie );
    if ( ret == 1 )
        putBookmarks( "digg", mp, numOfClips, cookie, cookieSize, NULL,
                      _putDigg );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "digg への login に失敗しました\n"
                    : "digg: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "digg へのログインに失敗しました。  "
                         : "digg: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}

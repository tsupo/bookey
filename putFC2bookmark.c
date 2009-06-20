/*
 * clip loader <<putFC2bookmark>>
 *
 *      OPML → FC2BOOKMARK 登録プログラム
 *          written by H.Tsujimura  29 Mar 2007
 *
 * History:
 * $Log: /comm/bookey/putFC2bookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    08/08/12 12:57 Tsujimura543
 * _putFC2Bookmark() 内の投稿成功/失敗判定条件を見直した
 * 
 * 14    07/10/05 4:18 Tsujimura543
 * putFC2Bookmark() 内で確保している cookie のサイズが1バイト小さすぎた
 * 
 * 13    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 12    07/09/26 18:41 Tsujimura543
 * 登録済みのブックマークの上書きについても、新しい仕様の元での動作を
 * 確認した
 * 
 * 11    07/09/26 18:31 Tsujimura543
 * 2007年9月20日の仕様変更(ブックマーク登録時の引数の追加、変更、他)
 * に対応
 * 
 * 10    07/08/24 1:18 Tsujimura543
 * FC2BOOKMARK のページデザイン変更に対応
 * 
 * 9     07/06/08 21:06 Tsujimura543
 * サーバが Proxy Error を返してきたときの対策を実装
 * 
 * 8     07/05/11 18:43 Tsujimura543
 * normalizeDescription() を修正
 * 
 * 7     07/04/10 17:07 Tsujimura543
 * normalizeDescription() を修正 (最後に any2utf() し忘れていた)
 * 
 * 6     07/04/10 16:58 Tsujimura543
 * 英語モード時に表示するエラーメッセージの文言を修正
 * 
 * 5     07/03/30 22:14 Tsujimura543
 * コメントが255文字より長い場合は、短くしてから登録するようにした
 * 
 * 4     07/03/30 20:55 Tsujimura543
 * リファクタリング
 * 
 * 3     07/03/30 20:14 Tsujimura543
 * すでに登録済みのWebページをさらに登録しようとした場合は、上書き登録
 * できるようにした (上書きしてよいか訊いてから上書き登録する)
 * 
 * 2     07/03/30 15:37 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     07/03/29 15:06 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putFC2bookmark.c 1     09/05/14 3:48 tsupo $";
#endif


#define MAX_DESCRIPTION_LENGTH          765
#define MAX_DESCRIPTION_BYTES_IN_SJIS   (255 * 2)
          // UTF-8で255文字以下 → 765バイト(Shift_JIS で 255 * 2 バイト)以下
          //   -- 255文字 * 3 = 765 バイト (いわゆる半角英数字が含まれて
          //                                いないと仮定した場合)

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
    }

    p = any2utf( description );

    return ( p ? p : description );
}


BOOL
searchFC2Bookmark(
    const char  *targetURL,
    char        *cookie,
    char        *entryID,
    char        *response,
    size_t      sz )
{
    char    url[MAX_URLLENGTH];
    BOOL    found = FALSE;
    BOOL    cont  = TRUE;
    char    *p, *q, *r;
    char    tmp[MAX_DESCRIPTION_LEN * 2];
    char    target[MAX_URLLENGTH];

    target[0] = NUL;
    strcpy( url,    "http://bookmark.fc2.com/user" );
    strcpy( target, "http://bookmark.fc2.com/user" );

    do {
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        // ブックマークを抜き出す
        p = response;
        do {
            q = strstr( p, "<div id=\"b-" );
            if ( !q )
                break;
            p = q + 11;
            q = strstr( p, "<h4>" );
            if ( !q )
                break;

            // URL
            p = q + 4;
            q = strstr( p, "<a href=\"" );
            if ( !q )
                break;
            q += 9;
            r = strstr( q, "\">" );
            if ( !r )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;
            if ( !strcmp( tmp, targetURL ) ) {
                // エントリID
                q = strstr( p, "_bookmark/" );
                if ( q ) {
                    p = q + 10;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( tmp, p, q - p );
                        tmp[q - p] = NUL;
                        strcpy( entryID, tmp );
                        p = q + 1;
                    }
                }

                found = TRUE;
                break;
            }

            p = strstr( p, "</table>" );
            if ( p )
                p += 8;
        } while ( p && *p );

        if ( found )
            break;

        // 次へ
        cont = FALSE;
        q = strstr( p, "<div class=\"pagenation\">" );
        if ( !q )
            q = strstr( p, "<div class=\"pagination\">" );
        if ( q ) {
            p = q + 24;
            q = strstr( p, sjis2utf("\">次の") );
            if ( !q )
                q = strstr( p, sjis2utf(">&raquo;次へ") );
            if ( q ) {
                while ( (q >= response) && (*q != '?') )
                    q--;
                if ( *q == '?' ) {
                    char    page[MAX_URLLENGTH];
                    p = strchr( q, '"' );
                    if ( p ) {
                        strncpy( page, q, p - q );
                        page[p - q] = NUL;
                        sprintf( url, "%s%s", target, page );
                        cont = TRUE;
                        Sleep( 1000 );
                    }
                }
            }
        }
    } while ( cont );

    return ( found );
}

char    *
getKeyForFC2bookmark( char *key, char *response, size_t sz, char *cookie )
{
    const char  *url = "http://bookmark.fc2.com/user/new_bookmark";

    key[0] = NUL;
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        const char  *p, *q;
        p = strstr( response, "name=\"data[key]\"" );
        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( key, p, q - p );
                    key[q - p] = NUL;
                }
            }
        }
        setReferer( url );
    }

    return ( key );
}

#define FC2_ADD_BOOKMARK        1
#define FC2_UPDATE_BOOKMARK     2

void
makeRequestForFC2bookmark(
        const MyClip *mp,
        const char   *key,
        char         *request,
        int          mode
    )
{
    char    *p;
    char    *temp = NULL;

    // タイトル
    p = any2utf( mp->title );
    sprintf( request,
             "data[Bookmark][title]=%s&",
             encodeURL( p ? p : mp->title ) );

    // URL
    sprintf( request + strlen(request),
             "data[Bookmark][url]=%s&",
             encodeURL( mp->url ) );

    // 説明
    p = any2utf( mp->comment );
    if ( p ) {
        size_t  len = strlen( p );
        if ( len >= MAX_DESCRIPTION_LENGTH ) {
            temp = (char *)malloc( len + 1 );
            if ( temp ) {
                char    *q;

                strcpy( temp, p );
                q = utf2sjis( temp );
                if ( q ) {
                    strcpy( temp, q );
                    p = normalizeDescription( temp );
                }
                else
                    p = any2utf( mp->title );
            }
        }
    }
    sprintf( request + strlen(request),
             "data[Bookmark][description]=%s&",
             encodeURL( p ? p : mp->comment ) );
    if ( temp )
        free( temp );

    // タグ (スペース区切り)
    p = any2utf( mp->tags );
    sprintf( request + strlen(request),
             "data[Bookmark][tag_txt]=%s&",
             encodeURL( p ? p : mp->tags ) );

    // mode
    switch ( mode ) {
    case FC2_ADD_BOOKMARK:
        sprintf( request + strlen(request),
                 "data[commit]=%s&",
                 encodeURL(sjis2utf("追加")) );
        break;
    case FC2_UPDATE_BOOKMARK:
        sprintf( request + strlen(request),
                 "data[commit]=%s&",
                 encodeURL(sjis2utf("更新")) );
        break;
    }

    // 公開・非公開
    sprintf( request + strlen(request),
             "data[Bookmark][allow_access]=0&"
             "data[Bookmark][allow_access]=%d&"
#ifdef  BEFORE_20070920
             "data[Bookmark][favorite]=0&"  // よく使うアイテムに追加: off
             "data[Bookmark][adult]=0",     // 18歳未満には表示しない: off
#else
             "data[Bookmark][favorite]=0",  // よく使うアイテムに追加: off
                                // R18なブックマークは無条件で登録禁止になった
#endif
             mp->publication == PUB_EVERYONE ? 1 : 0 );

    // key (2007年9月20日に追加されたパラメータ)
    if ( key && *key )
        sprintf( request + strlen(request),
                 "&data[key]=%s", key );
}

void
refineRequestForFC2bookmark( char *request )
{
    char    *p, *q;

    while ( (p = strchr( request, '[' )) != NULL ) {
        q = p + strlen( p );
        while ( q > p ) {
            *(q + 2) = *q;
            q--;
        }
        if ( q == p ) {
            *q++ = '%';
            *q++ = '5';
            *q++ = 'B';
        }
    }

    while ( (p = strchr( request, ']' )) != NULL ) {
        q = p + strlen( p );
        while ( q > p ) {
            *(q + 2) = *q;
            q--;
        }
        if ( q == p ) {
            *q++ = '%';
            *q++ = '5';
            *q++ = 'D';
        }
    }
}

void
getErrorStringForFC2bookmark( const char *response, char *errorString )
{
    char    *p;
    char    *q;

    errorString[0] = NUL;
    p = strstr( response,
                "<p id=\"flash-message\" class=\"info\">" );
    if ( p ) {
        p += 35;
        q = strstr( p, "</p>" );
        if ( q ) {
            strncpy( errorString, p, q - p );
            errorString[q - p] = NUL;
            p = utf2sjis( errorString );
            if ( p )
                strcpy( errorString, p );
        }
    }
    else {
        p = strstr( response,
                    "<div class=\"errorExplanation\" "
                    "id=\"errorExplanation\">" );
        if ( p ) {
            p += 52;
            q = strstr( p, "<ul><li>" );
            if ( !q )
                q = strstr( p, "<li>" );
            if ( q ) {
                p = strstr( p, "<li>" ) + 4;
                q = strstr( p, "</li>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString, p );
                }
            }
            else {
                q = strstr( p, "</div>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString, p );
                    deleteHtmlTags( errorString );
                }
            }
        }
        else {
            p = strstr( response,
                        "<h1>Proxy Error</h1>" );
            if ( p )
                strcpy( errorString, "Proxy Error" );
            else {
                p = strstr( response, "<div id=\"content\">" );
                if ( p ) {
                    p += 18;
                    q = strstr( p, "<h2>" );
                    if ( q ) {
                        p = q + 4;
                        q = strstr( p, "</h2>" );
                        if ( q ) {
                            strncpy( errorString, p, q - p );
                            errorString[q - p] = NUL;
                            p = utf2sjis( errorString );
                            if ( p )
                                strcpy( errorString, p );
                        }
                    }
                }
            }
        }
    }

    if ( errorString[0] == NUL )
        strcpy( errorString, "何らかのエラーが発生しました" );
    else if ( !strcmp( errorString, "Proxy Error" ) )
        errorString[0] = NUL;
}

BOOL
editFC2bookmark(
        const MyClip *mp,
        char         *cookie,
        char         *errorString,
        char         *request,
        char         *response,
        size_t       sz )
{
    char    entryID[MAX_KEYLENGTH];
    BOOL    found = FALSE;
    BOOL    ret   = FALSE;

    entryID[0] = NUL;
    found = searchFC2Bookmark( mp->url, cookie, entryID, response, sz );
    if ( found ) {
        char    url[MAX_URLLENGTH];
        char    key[MAX_KEYLENGTH];

        key[0] = NUL; /* @@ */
        strcpy( url,
#ifdef  BEFORE_20070920
                "http://bookmark.fc2.com/user/update_bookmark"
#else
                "http://bookmark.fc2.com/user/update_or_delete_bookmark"
#endif
              );
        makeRequestForFC2bookmark( mp, key, request, FC2_UPDATE_BOOKMARK );

        // 更新
        sprintf( request + strlen(request),
                 "&data[Bookmark][id_md5]=%s",
                 entryID );

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
            if ( strstr( response, sjis2utf("更新しました") ) )
                ret = TRUE;
            else
                getErrorStringForFC2bookmark( response, errorString );
        }
    }

    return ( ret );
}

BOOL
_putFC2Bookmark(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    BOOL    ret       = FALSE;
    char    url[MAX_URLLENGTH];
    char    key[MAX_KEYLENGTH];

    getKeyForFC2bookmark( key, response, sz, cookie );
    strcpy( url, "http://bookmark.fc2.com/user/add_bookmark" );
    makeRequestForFC2bookmark( mp, key, request, FC2_ADD_BOOKMARK );
    refineRequestForFC2bookmark( request );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, sjis2utf("ブックマークに追加しました") ) )
            ret = TRUE;
        else {
            getErrorStringForFC2bookmark( response, errorString );
            if ( !strcmp( errorString, "URLはすでに存在します"   ) ||
                 !strcmp( errorString, "URLは既に存在しています" )    ) {
#ifndef WIN32
# ifndef IDNO
#  define IDNO  FALSE
#  define IDYES TRUE
# endif /* !IDNO  */
#endif  /* !WIN32 */
                int     r = IDNO;
                int     fd = fileno( stderr );
                LCID    l = getLanguageCode();

                strcpy( errorString,
                        l == 0x0411
                         ? "そのWebページは、すでにFC2BOOKMARKに"
                           "登録済みです。"
                         : "this web page was already registered by"
                           " you." );
#ifdef  WIN32
                if ( (fd >= 0) && isatty( fd ) )
                    r = IDNO;
                else
                    r = MessageBox(
                            NULL,
                            l == 0x0411
                             ? "当該Webページは既に登録済みです。    "
                               "\r\n登録内容を上書きしますか?"
                             : "This web page was already registered "
                               "by you.    \r\n"
                               "Overwrite this bookmark?",
                            l == 0x0411
                             ? "上書き確認 (FC2BOOKMARK)"
                             : "Overwrite bookmark (FC2BOOKMARK)",
                            MB_YESNO|MB_ICONQUESTION );
#endif
                if ( r == IDYES )
                    ret = editFC2bookmark( mp, cookie, errorString,
                                           request, response, sz );
                else
                    ret = TRUE;
                if ( ret == TRUE )
                    errorString[0] = NUL;
            }
        }
    }
    else if ( getStatusCode() == 200 )  /* {@@} */
        ret = TRUE;                     /* {@@} */
    setReferer( NULL );

    return ( ret );
}

void
putFC2Bookmark(
        const char   *userName,  /* (I) ユーザ名 (FC2ID) */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    )
{
    int     ret;
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    uid[MAX_NAMELEN];
    char    cc[MAX_KEYLENGTH];

    uid[0] = NUL;
    cc[0]  = NUL;
    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* FC2BOOKMARK に login */
    ret = loginFC2Bookmark( userName, password, cookie, uid, cc );
    if ( !ret ) {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "FC2BOOKMARK への login に失敗しました\n"
                    : "FC2BOOKMARK: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "FC2BOOKMARK へのログインに失敗しました。  "
                         : "FC2BOOKMARK: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
        return;
    }

    if ( cookie[0] ) {
        // cookie から fcu と glgd_val 以外のものを削除する
        char    *p, *q;
        char    fcu[MAX_LOGICALLINELEN];
        char    glgd_val[MAX_LOGICALLINELEN];

        fcu[0] = NUL;
        glgd_val[0] = NUL;

        p = strstr( cookie, "fcu=" );
        if ( p ) {
            q = strchr( p + 4, ';' );
            if ( !q )
                q = strchr( p + 4, '\r' );
            if ( !q )
                q = strchr( p + 4, '\n' );
            if ( q ) {
                strncpy( fcu, p, q - p );
                fcu[q - p] = NUL;
            }
        }

        p = strstr( cookie, "glgd_val=" );
        if ( p ) {
            q = strchr( p + 9, ';' );
            if ( !q )
                q = strchr( p + 9, '\r' );
            if ( !q )
                q = strchr( p + 9, '\n' );
            if ( q ) {
                strncpy( glgd_val, p, q - p );
                glgd_val[q - p] = NUL;
            }
        }

        if ( fcu[0] && glgd_val[0] )
            sprintf( cookie, "Cookie: %s; %s\r\n", glgd_val, fcu );
    }

    /* FC2BOOKMARK に登録 */
    putBookmarks( "FC2BOOKMARK", mp, numOfClips, cookie, cookieSize, NULL,
                  _putFC2Bookmark );
}

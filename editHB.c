/*
 *  editHB.c
 *      「指定ユーザが はてなブックマーク で使っているタグの一覧」を取得する
 *          written by H.Tsujimura  29 Jan 2007 / 30 Jan 2007
 *
 * $Log: /comm/bookey/editHB.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     08/12/15 23:56 Tsujimura543
 * _getTagListOnHatenaBookmark() を新規作成
 * (サイドバーに表示されているタグ一覧を取得する関数。サイドバーに
 * タグ一覧を表示しない設定にしている場合は、一時的に表示する設定
 * にした後、タグ一覧を取得し、その後、設定を元に戻している)
 * 
 * 2     07/01/30 18:47 Tsujimura543
 * コードを整理
 * 
 * 1     07/01/30 18:44 Tsujimura543
 * getTagListOnHatenaBookmark() に相当する処理を UserInfo.cpp から
 * 分離、独立させた
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editHB.c 1     09/05/14 3:48 tsupo $";
#endif

char *
getRks( char *rks, const char *htmlSrcCode );

void
getConfigValue(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r, *s;
    char    target[BUFSIZ];
    char    buf[MAX_CONTENT_SIZE];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    if ( p && (p < formEnd) ) {
        q = strstr( p, "value=\"" );
        r = strstr( p, "/>" );
        if ( q && r && (q < r) && (r < formEnd) ) {
            q += 7;
            s = strchr( q, '"' );
            if ( s && (s < r) ) {
                sprintf( buf, "&%s=", name );
                strcat( setting, buf );

                strncpy( buf, q, s - q );
                buf[s - q] = NUL;
                strcat( setting, encodeURL(buf) );
            }
        }
        else {
            q = p;
            while ( q > formStart ) {
                q--;
                if ( !strncmp( q, "value=\"", 7 ) ) {
                    q += 7;
                    s = strchr( q, '"' );
                    if ( s && (s < p) ) {
                        sprintf( buf, "&%s=", name );
                        strcat( setting, buf );

                        strncpy( buf, q, s - q );
                        buf[s - q] = NUL;
                        strcat( setting, encodeURL(buf) );
                    }
                    break;
                }
            }
        }
    }
}

void
getConfigValueChecked(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r, *s;
    char    target[BUFSIZ];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    if ( p && (p < formEnd) ) {
        r = p;
        while ( p > formStart ) {
            p--;
            if ( !strncmp( p, "<input ", 7 ) ) {
                s = p;
                p += 7;
                q = strstr( p, "checked" );
                if ( q ) {
                    if ( q < r ) {
                        getConfigValue( name, setting, s, formEnd );
                    }
                    else {
                        s = r + strlen( target );
                        getConfigValueChecked( name, setting, s, formEnd );
                    }
                    break;
                }
            }
        }
    }
}

void
getConfigValueSelected(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r, *s;
    char    target[BUFSIZ];
    char    buf[MAX_CONTENT_SIZE];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    if ( p && (p < formEnd) ) {
        p += strlen( target );
        q = strstr( p, "</select>" );
        if ( q && (q < formEnd) ) {
            r = strstr( p, "selected" );
            if ( r && (r < q) ) {
                while ( r > formStart ) {
                    r--;
                    if ( !strncmp( r, "value=\"", 7 ) ) {
                        r += 7;
                        s = strchr( r, '"' );
                        if ( s && (s < q) ) {
                            sprintf( buf, "&%s=", name );
                            strcat( setting, buf );

                            strncpy( buf, r, s - r );
                            buf[s - r] = NUL;
                            strcat( setting, encodeURL(buf) );
                        }
                        break;
                    }
                }
            }
        }
    }
}

void
getConfigValueGroup(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r;
    char    target[BUFSIZ];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    while ( p && (p < formEnd) ) {
        q = strchr( p, '>' );
        if ( q < formEnd ) {
            while ( p > formStart ) {
                p--;
                if ( *p == '<' ) {
                    r = strstr( p, "checked" );
                    if ( r && (r < q) )
                        getConfigValue( name, setting, p, q );

                    p = strstr( q + 1, target );
                    break;
                }
            }
        }
    }
}

char    *
getConfig( const char *response, char *setting )
{
    char    *p, *s;

    p = strstr( response, "id=\"config-container\"" );
    if ( p ) {
        p += 21;
        s = strstr( p, "</form>" );
        if ( s ) {
            // btitle
            getConfigValue( "btitle", setting, p, s );

            // sitename
            getConfigValue( "sitename", setting, p, s );

            // siteurl
            getConfigValue( "siteurl", setting, p, s );

            // status
            getConfigValueChecked( "status", setting, p, s );

            // allowuser
            getConfigValue( "allowuser", setting, p, s );

            // allowgroup (× 所属グループ数分)
            getConfigValueGroup( "allowgroup", setting, p, s );

            // sendmailinterval
            getConfigValueSelected( "sendmailinterval", setting, p, s );

            // sendmailto
            getConfigValueSelected( "sendmailto", setting, p, s );

            // ignore_users
            getConfigValue( "ignore_users", setting, p, s );

            // hotthreshold
            getConfigValueChecked( "hotthreshold", setting, p, s );

            // include_news
            getConfigValueChecked( "include_news", setting, p, s );

            // linktarget
            getConfigValue( "linktarget", setting, p, s );

            // dateview
            getConfigValueChecked( "dateview", setting, p, s );

            // pagecount
            getConfigValueSelected( "pagecount", setting, p, s );

            // favoritepagecount
            getConfigValueSelected( "favoritepagecount", setting, p, s );

            // tagsuggest
            getConfigValueChecked( "tagsuggest", setting, p, s );

            // module_StarFriends
            getConfigValueChecked( "module_StarFriends", setting, p, s );

            // module_Asin
            getConfigValueChecked( "module_Asin", setting, p, s );

            // module_Group
            getConfigValueChecked( "module_Group", setting, p, s );
        }
    }

    return ( setting );
}


/* タグ一覧の取得 */
int
_getTagListOnHatenaBookmark(
        const char *username,   /* (I) ユーザ名         */
        const char *password,   /* (I) パスワード       */
        long       *numOfTags,  /* (I) 取得するタグの数 */
                                /* (O) 取得したタグの数 */
        TagList    *lp          /* (O) タグ一覧         */
    )
{
    int     num = 0;
    char    *cookie;
    int     ret;

    if ( !username  || !(*username)      ||
         !password  || !(*password)      ||
         !numOfTags || (*numOfTags <= 0) ||
         !lp                                )
        return ( num );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( num );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* はてなに login */
    ret = loginHatenaBookmark( username, password, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    *setting = NULL;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 32;
        BOOL    needToReset = FALSE;
        char    *p, *q, *r;

        ret = FALSE;

        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request ) {
            free( cookie );
            return ( num );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( num );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

        // 「タグ一覧の表示」設定取得
        sprintf( url, "http://b.hatena.ne.jp/%s/config", username );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        if ( *response ) {
            char    rks[MAX_KEYLENGTH];

            /* rks の値を取得 */
            getRks( rks, response );

            // 「タグ一覧の表示」が「タグ一覧を表示しない」に設定されている
            // 場合、一時的に「タグ一覧を表示する」に切り替える
            p = strstr( response, "id=\"showtags-on\"" );
            if ( p ) {
                r = p;
                while ( p > response ) {
                    p--;
                    if ( !strncmp( p, "<input ", 7 ) ) {
                        p += 7;
                        q = strstr( p, "checked" );
                        if ( q ) {
                            if ( q < r )
                                needToReset = FALSE;    // showtags-on
                            else {
                                needToReset = TRUE;     // showtags-off

                                // 設定保存
                                setting = (char *)malloc( MAX_CONTENT_SIZE );
                                if ( setting ) {
                                    *setting = NUL;
                                    getConfig( response, setting );
                                }

                                // 設定切替 (showtags-off → showtags-on)
                                sprintf( request,
                                         "rks=%s&"
                                         "showtags=1",
                                         rks );
                                if ( setting && *setting )
                                    strcat( request, setting );

                                setUpReceiveBuffer( response, sz );
                                http_postEx(
                                    url, "application/x-www-form-urlencoded",
                                    request, response, cookie );
                            }
                        }
                        ret = TRUE;
                        break;
                    }
                }
            }
        }

        if ( ret ) {
            ret = FALSE;

            // ユーザの「はてなブックマーク」トップページを取得し、
            // 右サイドバーに表示されている「タグ」の一覧を抽出
            sprintf( url, "http://b.hatena.ne.jp/%s/", username );
            setUpReceiveBuffer( response, sz );
            http_getEx( url, response, cookie );

            if ( *response ) {
                p = strstr( response, "id=\"tags\"" );
                if ( p ) {
                    p += 9;

                    do {
                        q = strstr( p, " class=\"tag\"" );
                        if ( !q )
                            break;
                        q += 12;

                        r = strchr( q, '>' );
                        if ( !r )
                            break;

                        p = r + 1;
                        q = strstr( p, "</a>" );
                        if ( !q )
                            break;

                        strncpy( lp[num].tag, p, q - p );
                        lp[num].tag[q - p] = NUL;

                        num++;
                    } while ( num < *numOfTags );
                }
            }

            // 「タグ一覧の表示」の設定を元に戻す (必要がある場合)
            if ( needToReset ) {
                sprintf( url, "http://b.hatena.ne.jp/%s/config", username );
                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );

                if ( *response ) {
                    char    rks[MAX_KEYLENGTH];

                    /* rks の値を取得 */
                    getRks( rks, response );

                    // 設定復帰 (showtags-on → showtags-off)
                    sprintf( request,
                             "rks=%s&"
                             "showtags=0",
                             rks );
                    if ( setting ) {
                        if ( *setting )
                            strcat( request, setting );
                        free( setting );
                        setting = NULL;
                    }

                    setUpReceiveBuffer( response, sz );
                    http_postEx(
                        url, "application/x-www-form-urlencoded",
                        request, response, cookie );
                }
            }


            if ( setting )
                free( setting );
        }

        free( response );
        free( request );
    }

    *numOfTags = num;
    free( cookie );

    return ( num );
}

TagList *
getTagListOnHatenaBookmark(
        const char *username,
        const char *password,
        int        *numOfTags )
{
    TagList *p = NULL;
#ifdef  BEFORE_20081125
    long    num = 1000; // 最大1000個までしか取得できない
#else
    long    num = 5000; // 最大5000個までしか取得できない
#endif

    *numOfTags = 0;

    p = (TagList *)malloc( sizeof (TagList) * num );
    if ( p ) {
#ifdef  BEFORE_20081125
        *numOfTags = getListOfTagsOnHatena( username, password, &num, p );
#else
        *numOfTags = _getTagListOnHatenaBookmark(username, password, &num, p);
#endif
    }

    return ( p );
}

/*
 * clip saver <<get1470net>>
 *
 *      1470.netリニューアル版 → OPML 変換出力プログラム
 *          written by H.Tsujimura  25 Aug 2006
 *
 * $Log: /comm/bookey/getMMmemo/get1470net.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    08/12/02 19:28 Tsujimura543
 * メモリ解放忘れ対処
 * 
 * 11    08/11/25 19:26 Tsujimura543
 * ブックマークの取得ができなくなっていたことが判明したため、対処した
 * 
 * 10    07/07/02 17:28 Tsujimura543
 * getFeedOn1470net() を void から BOOL に変更
 * 
 * 9     07/06/29 22:27 Tsujimura543
 * ソースコードを整理
 * 
 * 8     07/06/29 22:26 Tsujimura543
 * (1) 1470.net のデザイン変更に対応 (スクレイピング処理がうまく動かなく
 *     なってしまっていた)
 * (2) メモ取得API が 404 Not Found を返してくる場合は、すぐに処理を打ち
 *     切るようにした
 * 
 * 7     07/01/18 15:15 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 6     07/01/17 17:54 Tsujimura543
 * 英語モード対応
 * 
 * 5     06/11/17 14:03 Tsujimura543
 *  「評価」を title に埋め込んで記録する方式(MM/Memo互換方式)をやめ、
 * MyClip 構造体の evaluation に記憶する方式に移行
 * 
 * 4     06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 3     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 2a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 2     06/08/26 0:06 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     06/08/25 19:48 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getMMmemo/get1470net.c 1     09/05/14 3:48 tsupo $";
#endif

#define MAX_1470NET_MEMO_PER_BLOCK  200

BOOL
getFeedOn1470net(
        const char *userID,
        const char *url,
        MyClip     **mp,
        int        *num,
        int        *cnt,
        int        unit
    )
{
    char        entryListURL[MAX_URLLENGTH];
    char        entryID[32];
    const char  *p, *q, *r;
    char        *response;
    int         sz = MAX_CONTENT_SIZE * 20;
    int         yyyy, mm, dd, HH, MM, SS;
    BOOL        ret = FALSE;

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
        return ( ret );

    // 当該年月日のエントリ(メモ)一覧を取得
    Sleep( 2000 );
    setUpReceiveBuffer( response, sz );
    http_get( entryListURL, response );
    if ( *response ) {
        // 各メモの情報を順に取得
        char    entryURL[MAX_URLLENGTH];
        char    *response2;
        int     len;
        int     eval;

        if ( strstr(response,
                    "<html><head>\n<title>404 Not Found</title>\n</head>") ) {
            free( response );
            return ( ret );
        }

        response2 = (char *)malloc( sz );
        if ( !response2 ) {
            free( response );
            return ( ret );
        }

        p = response;
        if ( strchr( p, '{' ) )
            ret = TRUE;
        while ( *p ) {
            q = strstr( p, "{\"id\" : " );
            if ( !q )
                break;
            q += 8;
            r = strchr( q, ',' );
            if ( !r )
                break;

            strncpy( entryID, q, r - q );
            entryID[r - q] = NUL;

            // 当該メモを取得
            Sleep( 2000 );
            sprintf( entryURL,
                     "http://1470.net/api/memo/%s",
                     entryID );
            setUpReceiveBuffer( response2, sz );
            http_get( entryURL, response2 );
            if ( *response2 ) {
                char    *s, *t, *u;
                MyClip  *newClip_p;

                newClip_p = allocateMyClipIfNecessary( mp, unit, cnt, *num );
                if ( !newClip_p )
                    break;
                *mp = newClip_p;

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

                // 評価
                eval = 0;
                t = strstr( s, "\"eval\" : " );
                if ( t ) {
                    t += 9;
                    if ( (*t >= '0') && (*t <= '9') ) {
                        eval = atol( t );
                        if ( eval > 0 ) {
#ifdef  OLD_FASHIONED
                            // タイトルの頭に評価を埋め込む
                            char    tmp[4096];

                            sprintf( tmp,
                                     "(%d)『%s』",
                                     eval, ((*mp)[*num]).title );
                            strcpy( ((*mp)[*num]).title, tmp );
#else
                            // 「評価」は ((*mp)[*num]).evaluation に格納する
                            ((*mp)[*num]).evaluation = eval;
#endif
                        }
                    }

                    s = t + 1;
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

                s = t + 2;

                // タイムスタンプ (登録日時と最終変更日時があるが、登録日時の
                // 方を取得する)
                t = strstr( s, "\"rgdt\" : \"" );
                if ( !t )
                    break;
                t += 10;

                yyyy = mm = dd = HH = MM = SS = 0;
                yyyy = atol( t );
                if ( yyyy >= 1970 ) {
                    while ( *t && (*t != '-') )
                        t++;
                    if ( *t == '-' ) {
                        if ( *++t == '0' )
                            t++;
                        mm = atol( t );
                    }
                    while ( *t && (*t != '-') )
                        t++;
                    if ( *t == '-' ) {
                        if ( *++t == '0' )
                            t++;
                        dd = atol( t );
                    }
                    while ( *t && (*t != ' ') )
                        t++;
                    if ( *t == ' ' ) {
                        if ( *++t == '0' )
                            t++;
                        HH = atol( t );
                    }
                    while ( *t && (*t != ':') )
                        t++;
                    if ( *t == ':' ) {
                        if ( *++t == '0' )
                            t++;
                        MM = atol( t );
                    }
                    while ( *t && (*t != ':') )
                        t++;
                    if ( *t == ':' ) {
                        if ( *++t == '0' )
                            t++;
                        SS = atol( t );
                    }
                }

                ((*mp)[*num]).yyyy = yyyy;
                ((*mp)[*num]).mm   = mm;
                ((*mp)[*num]).dd   = dd;
                ((*mp)[*num]).HH   = HH;
                ((*mp)[*num]).MM   = MM;
                ((*mp)[*num]).SS   = SS;

                (*num)++;
                ret = TRUE;
            }

            p = r + 1;
        }

        free( response2 );
    }
    free( response );

    return ( ret );
}


MyClip  *
get1470net(
        const char *username,   /* (I) TypeKey認証用ユーザ名   */
        const char *password,   /* (I) TypeKey認証用パスワード */
        const char *username2,  /* (I) はてな認証用ユーザ名    */
        const char *password2,  /* (I) はてな認証用パスワード  */
        AUTH_TYPE  authType,    /* (I) 認証タイプ              */
        int        *numOfClips  /* (O) ブックマーク数          */
    )
{
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    char    url2[MAX_URLLENGTH];
    char    userID[32];
    char    *response;
    char    *p, *q, *r;
    char    *pp;
    int     num     = 0;
    int     cnt     = 0;
    int     unit    = MAX_1470NET_MEMO_PER_BLOCK;
    int     sz      = MAX_CONTENT_SIZE * 20;
    char    *cookie = NULL;
    int     fd;
    int     ret;

    *numOfClips = 0;
    target[0]   = NUL;
    userID[0]   = NUL;

    fd = fileno( stderr );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "メモリの確保に失敗しました\n"
                    : "memory exhausted.\n",
                   stderr );
        return ( mp );
    }
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* 1470.net にログイン */
    ret = login1470net( username, password, username2, password2, authType,
                        cookie, userID );
    if ( ret == 0 ) {
        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "1470.net への login に失敗しました\n"
                    : "1470.net: login failed.\n",
                   stderr );
        free( cookie );
        return ( mp );  // ログイン失敗
    }

    response = (char *)malloc( sz );
    if ( !response ) {
        free( cookie );
        return ( mp );
    }

    // マイページ(もしくは Feed を取得)
    //  http://1470.net/redirect/user/index (→ http://1470.net/user/ユーザ名)
    strcpy( url, "http://1470.net/redirect/user/index" );
    do {
        Sleep( 2000 );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( !(*response) )
            break;

        // API 経由で当該年月日のエントリ一覧を取得
        if ( !getFeedOn1470net( userID, url, &mp, &num, &cnt, unit ) )
            break;

        // 次へ (過去方向へ遡る)
        p = strstr( response, "<div class=\"pageNavigationArea\">" );
        if ( !p )
            break;
        p += 32;
        pp = strstr( p, "<div class=\"pageNavigationArea\">" );
        if ( pp )
            p = pp + 32;
        else {
            pp = strstr( p, "</div>" );
            if ( pp ) {
                while ( pp > p ) {
                    if ( *pp == '<' ) {
                        if ( !strncmp( pp + 1, "a href=\"", 8 ) ) {
                            p = pp;
                            break;
                        }
                    }
                    pp--;
                }
            }
        }

        q = strstr( p, "<a href=\"" );
        r = strchr( p, '|' );
        if ( !r )
            r = strchr( p, '"' );
        if ( !q || (q > r) )
            break;
        q += 9;
        r = strchr( q, '"' );
        if ( !r )
            break;
        strcpy( url2, "http://1470.net" );
        strncat( url2, q, r - q );
        url2[15 + (r - q)] = NUL;

        if ( !strcmp( url2, url ) )
            break;
        strcpy( url, url2 );
    } while ( *response );

    *numOfClips = num;
    free( response );
    free( cookie );

    return ( mp );
}

#ifdef  GET_1470NET_EXE
void
setParam(
        int       argc,
        char      *argv[],
        char      *username,
        char      *password,
        char      *username2,
        char      *password2,
        AUTH_TYPE *authType,
        BOOL      *useProxy
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( username, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'U':
                    if ( argv[i][j + 1] ) {
                        strcpy( username2, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username2, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'P':
                    if ( argv[i][j + 1] ) {
                        strcpy( password2, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password2, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'a':
                    switch ( argv[i][j + 1] ) {
                    case 't':
                        *authType = AK_TYPEKEY;
                        if ( argv[i][j + 2] == 'h' ) {
                            *authType = AK_TYPEKEY_HATENA;
                            j++;
                        }
                        break;
                    case 'h':
                        *authType = AK_HATENA;
                        if ( argv[i][j + 2] == 't' ) {
                            *authType = AK_HATENA_TYPEKEY;
                            j++;
                        }
                        break;
                    case 'T':
                        *authType = AK_TYPEKEY_HATENA;
                        break;
                    case 'H':
                        *authType = AK_HATENA_TYPEKEY;
                        break;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    if ( getLanguageCode() == 0x0411 ) {
        // 日本語
        fprintf( stderr, "get1470net: 1470net → OPML 変換出力ツール\n" );
        fprintf( stderr,
          "\t1470.net から吸い出した内容を OPML ファイルとして出力する\n");
        fprintf( stderr,
             "    get1470net [-x] -u TypeKeyユーザ名 -p TypeKeyパスワード\n");
        fprintf( stderr,
             "    get1470net [-x] -U はてなID -P はてなパスワード\n" );
        fprintf( stderr,
             "    get1470net [-x] -a{T|H} -u TypeKeyユーザ名 -p TypeKeyパス"
             "ワード\n               -U はてなID -P はてなパスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
        fprintf( stderr,
            "\t-aT: まず TypeKey 認証でのアクセスを試し、失敗した場合ははてな"
            "認証でのアクセスを試みる\n" );
        fprintf( stderr,
            "\t-aH: まずはてな認証でのアクセスを試し、失敗した場合は TypeKey "
            "認証でのアクセスを試みる\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "get1470net: get bookmarks from 1470.net, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    get1470net [-x] -u TypekeyID -p TypeKeyPassword\n" );
        fprintf( stderr,
             "    get1470net [-x] -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "    get1470net [-x] -a{T|H} -u TypekeyID -p TypeKeyPassword\n"
             "               -U hatenaID -P hatenaPassword\n" );
        fprintf( stderr,
             "      TypekeyID: ID for TypeKey authentication\n"
             "      TypeKeyPassword: password for TypeKey authentication\n" );
        fprintf( stderr,
             "      hatenaID: ID for Hatena authentication\n"
             "      hatenaPassword: password for Hatena authentication\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
        fprintf( stderr,
            "\t-aT: Use 'TypeKey' authentication first. If 'TypeKey' failure,"
            "\n\t\tthen try 'Hatena' authentication.\n" );
        fprintf( stderr,
            "\t-aH: Use 'Hatena' authentication first. If 'Hatena' falure,\n"
            "\t\tthen try 'TypeKey' authentication.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL        useProxy = FALSE;
    char        username[MAX_USERIDLEN];
    char        password[MAX_PASSWDLEN];
    char        username2[MAX_USERIDLEN];
    char        password2[MAX_PASSWDLEN];
    AUTH_TYPE   authType = AK_TYPEKEY; /* default */
    int         numOfClips = 0;
    MyClip      *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username,  0x00, MAX_USERIDLEN );
    memset( password,  0x00, MAX_PASSWDLEN );
    memset( username2, 0x00, MAX_USERIDLEN );
    memset( password2, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username,  password,
                  username2, password2,
                  &authType, &useProxy );

    if ( username[0]  && password[0]  &&
         username2[0] && password2[0]    ) {
        if ( (authType != AK_TYPEKEY_HATENA) &&
             (authType != AK_HATENA_TYPEKEY)    )
            authType = AK_TYPEKEY_HATENA;
    }
    else if ( username[0] && password[0] )
        authType = AK_TYPEKEY;
    else if ( username2[0] && password2[0] )
        authType = AK_HATENA;
    else
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* 1470.net に登録済みのブックマークを取得 */
    mp = get1470net( username,  password,
                     username2, password2,
                     authType,
                     &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "1470.net", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_1470NET_EXE */

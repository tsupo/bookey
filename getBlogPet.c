/*
 * clip saver <<getBlogPet>>
 *
 *      「BlogPetブックマーク」 → OPML 変換出力プログラム
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/getBlogPet.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 13    08/12/02 19:29 Tsujimura543
 * null ポインタ参照が発生する可能性のある箇所の対処
 * 
 * 12    08/02/19 22:35 Tsujimura543
 * コメントを整理
 * 
 * 11    08/02/19 22:33 Tsujimura543
 * _getBlogPet() を修正、変更
 *     (1) タイトルの先頭と末尾に white space が存在する場合は削除する
 *         ようにした
 *     (2) タイトルに改行が含まれる場合は削除するようにした
 *     (3) コメントが空のとき、「(コメントがありません)」がコメントに
 *         なってしまう件に対処
 * 
 * 10    08/02/19 21:58 Tsujimura543
 * 「BlogPet 気になる記事」 → 「BlogPetブックマーク」に名称変更
 * 
 * 9     07/07/13 2:01 Tsujimura543
 * 2007年7月12日に実施された BlogPet リニューアルに対応
 * 
 * 8     07/02/14 23:16 Tsujimura543
 * _getBlogPet() のプロトタイプ宣言を blogPet.h へ移動
 * 
 * 7     07/02/13 21:43 Tsujimura543
 * encodeURLe() を getBlogPet.c から blogPet.c へ移動
 * 
 * 6     07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 5     07/01/19 15:43 Tsujimura543
 * html の取得・解析処理を分離し、_getBlogPet() を作成
 * 
 * 4     07/01/17 21:45 Tsujimura543
 * (1) 英語モード対応
 * (2) コマンドライン版をビルドできるようにした
 * 
 * 3     06/12/25 23:37 Tsujimura543
 * loginBlogPet() に第4引数を追加
 * 
 * 2     06/12/25 23:22 Tsujimura543
 * 暫定実装 (動作確認済み)
 * 
 * 1     06/12/22 21:58 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"
#include "blogPet.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBlogPet.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20


int
_getBlogPet(
        const char *userID,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    )
{
    char    target[MAX_URLLENGTH];
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    char    *p, *q, *r, *s;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    int     page = 1;
    char    bmNumber[MAX_KEYLENGTH];
    char    tmp[MAX_DESCRIPTION_LEN * 2];

 // if ( cookie )
        sprintf( target,
                 "http://www.blogpet.net/profile/bookmarks/%s",
                 userID );
 // else
 //     strcpy( target, "http://www.blogpet.net/bookmark/my" );
 //        -- http://www.blogpet.net/bookmark/my の方は最大10ページ分しか
 //           過去方向に遡れないため、
 //           http://www.blogpet.net/profile/bookmarks/xxxxxx の方を取得
 //           する
    strcpy( url, target );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) )
            break;

        // ブックマークを抜き出す
        p = strstr( response, "<div class=\"bookmarks\">" );
        if ( !p )
            break;
        p += 23;

        do {
            if ( mp ) {
                MyClip  *np;
                np = allocateMyClipIfNecessary( mp, unit, &cnt, num );
                if ( !np )
                    break;
                *mp = np;
            }
            if ( mpEx ) {
                MyClipEx    *np;
                np = allocateMyClipExIfNecessary( mpEx, unit, &cnt, num );
                if ( !np )
                    break;
                *mpEx = np;
            }

            q = strstr( p, "<li class=\"clearfix\">" );
            if ( !q )
                q = strstr( p, "<li>" );
            s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = strchr( q, '>' ) + 1;

            // URL
            q = strstr( p, "<a href=\"/view_url?url=" );
            if ( !q || (q > s) )
                break;
            p = q + 23;
            q = strstr( p, "\" " );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            strcpy( tmp, encodeURLe( decodeURL( tmp ) ) );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );
 
            // タイトル
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );

            while ( ((r = strchr(tmp, '\r')) != NULL) ||
                    ((r = strchr(tmp, '\n')) != NULL)    )
                strcpy( r, r + 1 ); /* 改行を取り除く */

            r = &(tmp[strlen(tmp) - 1]);
            while ( (r > tmp) && ((*r == ' ') || (*r == '\t')) )
                *r-- = NUL;

            r = tmp;
            while ( ((*r == ' ') || (*r == '\t')) )
                r++;

            if ( mp )
                strcpy( (*mp)[num].title, r );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, r );

            // ブックマーク番号
            bmNumber[0] = NUL;
            p = q + 4;
            q = strstr( p, "<a href=\"/bookmark/view/" );
            if ( q && (q < s) ) {
                p = q + 24;
                if ( (*p >= '1') && (*p <= '9') )
                    sprintf( bmNumber, "%d", atol( p ) );
            }

            // タグ
            p = q + 2;
            q = strstr( p, "<dd class=\"keywords\">" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 21;
                do {
                    r = "<a href=\"/bookmark/search?keyword=";
                    q = strstr( p, r );
                    if ( !q || (q > s) ) {
                        r = "<a href=\"/bookmark/search?tag=";
                        q = strstr( p, r );
                        if ( !q || (q > s) )
                            break;
                    }
                    p = q + strlen( r );
                    q = strstr( p, "\">" );
                    if ( q && (q < s) ) {
                        q += 2;
                        r = strstr( q, "</a>" );
                        if ( !r || (r > s) )
                            break;

                        if ( tmp[0] == NUL )
                            len = 0;
                        else {
                            strcat( tmp, " " );
                            len = strlen( tmp );
                        }
                        strncat( tmp, q, r - q );
                        tmp[len + (r - q)] = NUL;
                        p = q + 4;
                    }
                    else
                        break;
                } while ( p < s );

                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
            }

            //   -- コメント
            q = strstr( p, "<dd class=\"comment\">" );
            if ( q && (q < s) ) {
                p = q + 20;
                q = strstr( p, "&nbsp;</dd>" );
                if ( !q || (q > s) )
                    q = strstr( p, "</dd>" );
                if ( q && (q < s) ) {
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    deleteHtmlTags( tmp );
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );

                    if ( strstr( tmp, ">(コメントがありません)</span>" ) )
                        tmp[0] = NUL;

                    if ( mp )
                        strcpy( (*mp)[num].comment, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].comment, tmp );
                }
            }

            if ( mp ) {
                //   -- 登録日時
                tmp[0] = NUL;
                q = strstr( p, "<div class=\"bookmarkFooter\">" );
                if ( q && (q < s) ) {
                    p = q + 28;
                    q = strstr( p, "<br />" );
                    if ( q && (q < s) ) {
                        while ( isWhiteSpace( *p ) && (p < q) )
                            p++;
                        if ( p < q ) {
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;
                        }
                    }
                }
                else {
                    q = strstr( p, "<dd class=\"date\">" );
                    if ( q && (q < s) ) {
                        p = q + 17;
                        q = strstr( p, "</dd>" );
                        if ( q && (q < s) ) {
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;
                        }
                    }
                }
                if ( tmp[0] ) {
                    strcat( tmp, " +0900" );
                    getDateTimeFromDateString(
                            tmp,
                            &((*mp)[num].yyyy),
                            &((*mp)[num].mm),
                            &((*mp)[num].dd),
                            &((*mp)[num].HH),
                            &((*mp)[num].MM),
                            &((*mp)[num].SS) );
                }

                //   -- 公開レベル
                q = strstr( p, sjis2utf("公開レベル：<em>") );
                if ( q && (q < s) ) {
                    q = strstr( p, "<em>" ) + 4;
                    r = strstr( q, "</em>" );
                    if ( q && r && !strncmp( q, sjis2utf("公開"), r - q ) )
                        (*mp)[num].publication = PUB_EVERYONE;
                    else
                        (*mp)[num].publication = PUB_PRIVATE;
                }
            }
            p = s + 5;

            if ( bmNumber[0] ) {
                if ( mpEx )
                    strcpy( (*mpEx)[num].entryID, bmNumber );
                num++;
            }
        } while ( p && *p );

        // 次へ
        cont = FALSE;
        p = strstr( response, "<div class=\"pagingNext\">" );
        if ( p ) {
            page++;
            sprintf( url, "%s/%d", target, page );
            cont = TRUE;
            Sleep( 1000 );
        }
    } while ( cont );

    return ( num );
}

MyClip  *
getBlogPet(
        const char *userName,   /* (I) ユーザ名                       */
        const char *password,   /* (I) パスワード (非公開のブックマー */
                                /*     クも取得したい場合に必要)      */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    )
{
    /*
     *  (1) userName でユーザ名を指定した場合は、そのユーザ(自分自身を想定)
     *      のブックマークを取得する (password の指定も必要)
     *        → http://www.blogpet.net/bookmark/my
     *           が自分のブックマークの一覧のトップページ、
     *           http://www.blogpet.net/bookmark/my/n
     *           が自分のブックマークの一覧の n ページ目になる
     *  (2) userName で「ハッシュ化されたID」を指定した場合は、そのユーザの
     *      ブックマーク(のうち、公開されているもの)を全件取得する(password
     *      は不要)
     *        -- 当該ユーザのプロフィールページの URL
     *             http://www.blogpet.net/profile/view/XXXXXX
     *           の XXXXXX 部分(32文字)が「ハッシュ化されたID」に相当する
     *        → http://www.blogpet.net/profile/bookmarks/XXXXXX
     *           が当該ユーザの「公開されている」ブックマークの一覧のトップ
     *           ページ、
     *           http://www.blogpet.net/profile/bookmarks/XXXXXX/n
     *           が当該ユーザの「公開されている」ブックマークの一覧の n ペー
     *           ジ目になる
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz = MAX_CONTENT_SIZE * 20;
    char    userID[MAX_KEYLENGTH];

    *numOfClips = 0;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    target[0] = NUL;
    userID[0] = NUL;

    fd = fileno( stderr );
    if ( password && *password ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( !cookie ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "メモリの確保に失敗しました\n"
                        : "memory exhausted.\n",
                       stderr );
            free( response );
            return ( mp );
        }
        memset( cookie, 0x00, MAX_COOKIE_LEN );

        // BlogPet 管理画面 にlogin (cookie を取得)
        if ( !loginBlogPet( userName, password, cookie, userID ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "BlogPet管理画面への login に失敗しました\n"
                        : "BlogPet: login failed.\n",
                       stderr );
            free( cookie );
            free( response );
            return ( mp );
        }
    }
    else
        strcpy( userID, userName );

    if ( !(userID[0]) ) {
        if ( cookie )
            free( cookie );
        free( response );
        return ( mp );
    }

    *numOfClips = _getBlogPet( userID, cookie, &mp, NULL, response, sz );

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}


#ifdef  GET_BLOGPET_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy
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
        fprintf( stderr,
             "getBlogPet: BlogPetブックマーク → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "    getBlogPet [-x] -u BlogPetユーザ名 "
                 "-p BlogPetパスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getBlogPet: get bookmarks from 'BlogPet bookmarks',"
                 " and output them as OPML\n" );
        fprintf( stderr,
                 "    getBlogPet [-x] -u username -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password, &useProxy );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* 「BlogPetブックマーク」登録済みのブックマークを取得 */
    mp = getBlogPet( username, password, &numOfClips );
    if ( mp && (numOfClips > 0) ) {
        /* ブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "BlogPet", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLOGPET_EXE */

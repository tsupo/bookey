/*
 * clip saver <<getLivedoorClip>>
 *
 *      livedoor クリップ → OPML 変換出力プログラム
 *          written by H.Tsujimura  6 Jul 2006
 *
 * $Log: /comm/bookey/getLivedoorClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 19    08/02/23 4:00 Tsujimura543
 * コメントを追加
 * 
 * 18    08/02/23 3:57 Tsujimura543
 * (1) サーバが busy を返してきたときは2秒間隔でリトライ(最大5回)するよう
 *     にしてみた
 * (2) 応答1個あたり20件のブックマーク情報が入っているが、ちょうど20件目の
 *     ブックマークがプライベートもしくはR18フラグONの場合、そのブックマー
 *     ク情報をスキップしてしまい、そこでブックマークの取得を終了してしま
 *     う不具合を修正
 * 
 * 17    08/01/22 15:06 Tsujimura543
 * _getLivedoorClip() を修正(18禁フラグ対応、無限ループ防止処理追加)
 * 
 * 16    07/01/23 16:19 Tsujimura543
 * usage() で表示する文言を修正
 * 
 * 15    07/01/19 22:05 Tsujimura543
 * _getLivedoorClip() を導入、リファクタリングを実施
 * 
 * 14    07/01/17 23:31 Tsujimura543
 * (1) 英語モード対応
 * (2) コマンドライン版をビルドできるようにした
 * 
 * 13    06/12/07 17:25 Tsujimura543
 * 「公開状態」の取得処理(取得タイミング)を修正
 * 
 * 12    06/12/07 16:52 Tsujimura543
 * 実際の「公開状態」の値を mp[].publication に格納するようにした
 * 
 * 11    06/11/17 13:48 Tsujimura543
 * 「評価」を title に埋め込んで記録する方式(MM/Memo互換方式)をやめ、
 * MyClip 構造体の evaluation に記憶する方式に移行
 * 
 * 10    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() を導入。MyClip 構造体格納領域確保処理を
 * 共通関数化してみた
 * 
 * 9     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 8a    06/09/03 20:19 tsupo
 * cookie まわりを修正
 * 
 * 8     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 7     06/07/24 22:20 Tsujimura543
 * http 応答格納領域のオーバーラン防止機能を利用するように修正
 * 
 * 6     06/07/24 20:55 Tsujimura543
 * 先頭(最新)のクリップがプライベートモードの場合、取得内容に過不足が
 * 生じる不具合を修正(先頭のクリップが捨てられ、最後のページのクリップ
 * を重複して取得してしまう)
 * 
 * 5     06/07/21 17:47 Tsujimura543
 * livedoorクリップの html の書き方が変わった(2006年7月20日)影響で、
 * クリップの先頭の20件のみしか取得できなくなってしまったため、新しい
 * html に対応するよう、処理を書き直した
 * 
 * 4     06/07/19 19:25 Tsujimura543
 * cookie 解放漏れルートがあったので、修正
 * 
 * 3     06/07/12 15:51 Tsujimura543
 * 64 → MAX_KEYLENGTH に置換
 * 
 * 2     06/07/07 11:00 Tsujimura543
 * 「評価」の記録方法を MM/Memo 互換にする
 * 
 * 1     06/07/06 19:52 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getLivedoorClip.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20

int
_getLivedoorClip(
        const char *target,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    BOOL    isPrivate;
    char    *p, *q, *r, *s;
    char    *qq;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    int     rate;
    int     yy, mm, dd;
    char    postkey[MAX_KEYLENGTH];
    char    tmp[MAX_DESCRIPTION_LEN * 2];
    int     retry = 5;

    postkey[0] = NUL;
    strcpy( url, target );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) ) {
            // 応答が空の場合
            if ( (num > 0) && (num < *total) ) {
                retry--;
                if ( retry > 0 ) {
                    Sleep( 2000 );
                    continue;
                }
            }
            break;
        }

        if ( *total == 0 ) {
            // 全部で何件あるか、前もって調べておく
            //   -- ただし、「公開」状態のものの全件数なので、非公開の
            //      ブックマークが存在する場合は、実際のブックマーク数
            //      はもっと大きな値になる
            p = strstr( response, "class=\"myclip-clipcount\"" );
            if ( !p )
                p = strstr( response, "class=\"pager-total\"" );
            if ( p ) {
                p = strchr( p, '>' );
                if ( p ) {
                    while ( *p && ((*p <= '0') || (*p > '9')) )
                        p++;
                    if ( *p )
                        *total = atol( p );
                }
            }
        }

        // postkey を抽出
        p = strstr( response, "=\"postkey\" value=\"" );
        if ( p ) {
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( postkey, p, q - p );
                postkey[q - p] = NUL;
            }
        }

        // ブックマークを抜き出す
        if ( !strcmp( url, "http://clip.livedoor.com/clips/tsupo?p=242" ) ) {
            Sleep( 1000 );
        }
        p = response;
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

            if ( cookie ) {
                q  = strstr( p, "<li class=\"clip\" id=\"" );
                qq = strstr( p, "<li class=\"clip clip-" );
                if ( qq && ((qq < q) || !q))
                    q = qq;
            }
            else
                q = strstr( p, "<li class=\"clip\">" );
            if ( !q )
                break;

            s = strstr( q, "</li>" );
            if ( !s )
                break;
            qq = strchr( q, '>' );
            if ( !qq )
                break;
            p = qq + 1;

            rate = 0;

            // ハッシュ
            if ( mpEx ) {
                q = strstr( p, "<a id=\"hash_" );
                if ( !q || (q > s) )
                    break;
                p = q + 12;
                q = strstr( p, "\" name=\"p_" );
                if ( !q || (q > s) )
                    break;
                p = q + 10;
                q = strchr( p, '"' );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                strcpy( (*mpEx)[num].entryID, tmp );
            }

            q = strstr( p, "<h4 class=\"clip-title\" id=\"" );
            s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = q + 27;

            // URL
            q = strstr( p, "<a href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 9;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
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
            while ( ((p = strchr(tmp, '\r')) != NULL) ||
                    ((p = strchr(tmp, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* 改行を取り除く */
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // 公開状態
            p = q + 4;
            isPrivate = FALSE;
            q = strstr( p, "<small class=\"clip-public\">" );
            if ( q && (q < s) ) {
                p = q + 27;
                q = strstr( p, "</small>" );
                r = strstr( p, "private" );
                if ( q && (q < s) ) {
                    if ( r && (r < q) )
                        isPrivate = TRUE;
                    p = q + 8;
                }
            }

            // 年月日 (時分秒は取得できない)
            q = strstr( p, "<span class=\"clip-date" );
            if ( !q || (q > s) )
                break;
            p = q + 22;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            yy = atol( p );
            p += 5;

            while ( *p && ((*p <= '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            mm = atol( p );

            while ( *p && ((*p >= '0') && (*p <= '9')) && (p < s) )
                p++;
            while ( *p && ((*p <= '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            dd = atol( p );

            if ( mp ) {
                (*mp)[num].yyyy = yy;
                (*mp)[num].mm   = mm;
                (*mp)[num].dd   = dd;
             // (*mp)[num].HH   = 0;
             // (*mp)[num].MM   = 0;
             // (*mp)[num].SS   = 0;
            }

            while ( *p && ((*p >= '0') && (*p <= '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;

            // 評価
            q = strstr( p, " src=\"/img/rate/pad/" );
            if ( !q )
                q = strstr( p, " src=\"/img/rate/" );
            if ( !q || (q > s) )
                break;
            p = q + 20;
            rate = atol( p );
            if ( (rate > 0) && (rate <= 5) ) {
                if ( mp )
                    (*mp)[num].evaluation = rate;
            }

            p = q + 4;
            q = strstr( p, "<div class=\"clip-tags\"" );
            if ( q && (q < s) ) {
                // タグ
                int len;

                tmp[0] = NUL;
                p = q + 22;
                do {
                    q = strstr( p, "class=\"linkgray tag\">" );
                    if ( !q || (q > s) )
                        break;
                    p = q + 21;
                    q = strstr( p, "</a>" );
                    if ( !q )
                        break;

                    if ( tmp[0] == NUL )
                        len = 0;
                    else {
                        strcat( tmp, " " );
                        len = strlen( tmp );
                    }
                    strncat( tmp, p, q - p );
                    tmp[len + (q - p)] = NUL;

                    p = q + 4;
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

                // コメント
                q = strstr( p, "<p class=\"notes\" " );
                if ( !q || (q > s) )
                    break;
                p = q + 17;
                q = strstr( p, "\">" );
                if ( !q || (q > s) )
                    break;
                p = q + 2;
                q = strstr( p, "</p>" );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;

                r = utf2sjis( tmp );
                if ( r )
                    strcpy( tmp, r );
                while ( ((p = strchr(tmp, '\r')) != NULL) ||
                        ((p = strchr(tmp, '\n')) != NULL)    )
                    strcpy( p, p + 1 ); /* 改行を取り除く */
                if ( mp )
                    strcpy( (*mp)[num].comment, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].comment, tmp );

                p = q + 4;
            }

            // postkey を保存
            if ( mpEx )
                strcpy( (*mpEx)[num].remarks, postkey );

            // 公開状態 を保存
            if ( isPrivate )
                if ( mp )
                    (*mp)[num].publication = PUB_PRIVATE;

            p = s + 5;

            num++;
        } while ( p && *p );

        assert( (num == *total) || (num % 20 == 0) );

        // 次へ
        cont = FALSE;
     // p = strstr( response, sjis2utf("class=\"linkgray\">次の") );
        p = strstr(response, sjis2utf("title=\"次のページ\" rel=\"next\">"));
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;
                    sprintf( url, "%s%s", target, page );
                    cont = TRUE;
                    Sleep( 1000 );
                }
            }
        }
        else if ( num < *total ) {    
            char    preURL[MAX_URLLENGTH];

            if ( !strstr( response, "postkey" ) ) {
                // ブックマーク情報が空の場合 (サーバーが busy 状態)
                if ( (num > 0) && (num < *total) ) {
                    retry--;
                    if ( retry > 0 ) {
                        cont = TRUE;
                        Sleep( 2000 );
                        continue;
                    }
                }
                break;
            }

            /* htmlのフォーマットが多少変わっても、以下の処理で何とか切り抜 */
            /* けられるはず(API が変わらなければ、という前提ではあるものの) */
            strcpy( preURL, url );

            sprintf( url, "%s/?p=%d",
                     target,
                     (num + NUM_OF_CLIPS_PER_PAGE) / NUM_OF_CLIPS_PER_PAGE );
            if ( strcmp( url, preURL ) != 0 ) {
                cont = TRUE;
                Sleep( 1000 );
            }
        }

        retry = 5;
    } while ( cont );

    assert( num == *total );

    return ( num );
}

MyClip  *
getLivedoorClip(
        const char *userName,   /* (I) livedoor ID                    */
        const char *password,   /* (I) パスワード (シークレットモード */
                                /*     のブックマークも取得したい場合 */
                                /*     に必要)                        */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    )
{
    /*
     *  userName で指定されたユーザのブックマーク(のうち、パブリック
     *  モードのもの)を全件取得する(プライベートモードのものも取得す
     *  るには、userName のユーザの password の指定も必要。
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    int     num = 0;
    size_t  sz;

    fd = fileno( stderr );
    if ( password && *password ) {
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

        // livedoorクリップにlogin (cookie を取得)
        if ( !loginLivedoorClip( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "livedoorへの login に失敗しました\n"
                        : "livedoor clip: login failed.\n",
                       stderr );
            free( cookie );
            return ( mp );
        }
    }

    *total      = 0;
    *numOfClips = 0;
    sprintf( target, "http://clip.livedoor.com/clips/%s", userName );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response ) {
        if ( cookie )
            free( cookie );
        return ( mp );
    }

    // マイクリップを取得
    num = _getLivedoorClip( target, cookie, &mp, NULL, response, sz, total );

    *numOfClips = num;

    free( response );
    if ( cookie )
        free( cookie );

    return ( mp );
}


#ifdef  GET_LIVEDOOR_CLIP_EXE
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
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
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
                 "getLC: livedoor クリップ → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tlivedoor クリップから吸い出した内容を OPML ファイルと"
                 "して出力する\n" );
        fprintf( stderr,
                 "    getLC [-x] -u ユーザ名 -p パスワード\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getLC: get bookmarks from livedoor clip, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getLC [-x] -u username -p password\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* livedoor clip へ登録済みのブックマークを取得 */
    mp = getLivedoorClip( username, password, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  livedoor clip のブックマーク情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "livedoor clip", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_LIVEDOOR_CLIP_EXE */

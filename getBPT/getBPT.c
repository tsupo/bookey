/*
 * clip saver <<getBPT>>
 *
 *      BlogPeople Tags → OPML 変換出力プログラム
 *          written by H.Tsujimura  27 Jun 2005
 *
 * $Log: /comm/bookey/getBPT/getBPT.c $
 * 
 * 1     09/05/14 4:23 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 27    07/01/18 13:53 Tsujimura543
 * 英語モード対応
 * 
 * 26    06/11/17 13:52 Tsujimura543
 * 「評価」を title に埋め込んで記録する方式(MM/Memo互換方式)をやめ、
 * MyClip 構造体の evaluation に記憶する方式に移行
 * 
 * 25    06/10/20 21:26 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 24    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 23    06/07/21 20:17 Tsujimura543
 * BlogPeople Tags の取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 22    06/06/20 11:14 Tsujimura543
 * 「コメント」中に含まれる改行(\r,\n)を取り除くようにした
 * 
 * 21    06/06/20 0:04 Tsujimura543
 * 同一ページ上に「マイレート」ありとなしが混在する場合の処理誤りを修正
 * 
 * 20    06/06/19 23:09 Tsujimura543
 * (1) メモリオーバーラン対策を実施 (メモリサイズ、再々調整)
 * (2) ブックマークの件数(=nとする)が999件以上あると、(n%1000)件しか取得
 *   しない不具合を修正
 * 
 * 19    06/06/06 22:22 Tsujimura543
 * メモリオーバーラン対策を実施 (メモリサイズ、再調整)
 * [課題: 抜本的な対策が必要]
 * 
 * 18    06/05/22 15:31 Tsujimura543
 * メモリオーバーラン対策を実施
 * 
 * 17    05/11/02 13:42 Tsujimura543
 * 「評価(マイレート)」を MM/Memo 互換形式で opml に書き出すようにした
 * 
 * 16    05/11/01 19:31 Tsujimura543
 * 警告レベル4でコンパイルしても警告が出ないように修正
 * 
 * 15    05/10/31 21:41 Tsujimura543
 * BP_TAGS というタグを強制的に付加するのをやめる
 * 
 * 14    05/09/30 17:42 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 13    05/09/28 20:48 Tsujimura543
 * 外部変数へのアクセスを廃止
 * 
 * 12    05/09/28 13:44 Tsujimura543
 * getBPTags() をブックマーク管理ツールから呼び出せるようにした
 * 
 * 11    05/09/27 18:30 Tsujimura543
 * コードを整理
 * 
 * 10    05/09/26 20:47 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備 (bug修正)
 * 
 * 9     05/09/26 20:23 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備 (つづき)
 * 
 * 8     05/09/26 20:11 Tsujimura543
 * 他のブックマーク吸出しツールとの統合準備
 * 
 * 7     05/09/26 19:37 Tsujimura543
 * 変換結果を標準エラー出力に表示するのはデバッグビルド時のみにした
 * 
 * 6     05/09/26 18:53 Tsujimura543
 * 少しだけリファクタリング (まだまだリファクタリングの余地ありまくり)
 * 
 * 5     05/09/26 18:45 Tsujimura543
 * 生成する OPML ファイルの title を BlogPeople tags にした
 * 
 * 4     05/06/27 22:21 Tsujimura543
 * title 属性(に格納すべきもの)を拾い忘れていたのを修正
 * 
 * 3     05/06/27 21:36 Tsujimura543
 * OPML ファイルに notes 属性を出力し忘れていたのを修正
 * 
 * 2     05/06/27 21:28 Tsujimura543
 * 動作確認完了
 * 
 * 1     05/06/27 20:48 Tsujimura543
 * 最初の版
 */

#include "myClip.h"
#include <math.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBPT/getBPT.c 1     09/05/14 4:23 tsupo $";
#endif

/* BlogPeople Tags に登録済みのブックマークは
 *   http://tags.blogpeople.net/user/ユーザ名
 *   http://tags.blogpeople.net/user/ユーザ名/1
 *     ……
 *   http://tags.blogpeople.net/user/ユーザ名/n
 * の各ページから取得する (n の値は 「約xx件中　1～20件を表示」という
 * 表示中の xx の値を元に決定することができる)
 *
 * なお、ブックマークの登録日時に関して、日付は取得できるが時刻は取得
 * できないため、本ツールでは一律 0時0分0秒 として取り扱うことにする。
 * また、カテゴリ(分類)は取得できない。
 *
 * 注意: 「ユーザ名」は BlogPeople のユーザ名(ログイン時に入力するメー
 *       ルアドレス)ではなく、ブックマークサービスを新規に利用申請した
 *       ときに指定した名前(ブックマークの名前というか、ディレクトリ名)
 *       になる
 */

MyClip  *
getBPTags( const char *username, int *total, int *numOfClips )
{
    char    *response;
    char    url[MAX_URLLENGTH];
    char    *p, *q, *r, *s, *t, *u;
    int     num = 0, cnt = 0;
    int     maxNum = 20;    /* 暫定値 */
    int     maxCnt = 0;
    int     yyyy, mm, dd;
    MyClip  *mp = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 64;

    *total      = 0;
    *numOfClips = 0;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    sprintf( url, "http://tags.blogpeople.net/user/%s", username );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    p = http_get( url, response );
    if ( !p || !(*p) || !(*response) ) {
        free( response );
        return ( mp );
    }

    p = response;
    if ( p && *p ) {
        q = strstr( p, ">全ブックマーク</a>(" );
        if ( q )
            *total = cnt = atol( q + 20 );
        else {
            q = strstr( p, "件中　1～20件を表示" );
            if ( q ) {
                do {
                    while ( (*(q - 1) >= '0') && (*(q - 1) <= '9') )
                        q--;
                    cnt += (int)(atol( q ) * pow( 1000.0, (double)num ));
                    num++;
                } while ( *--q == ',' );

                *total = cnt;
            }
            else {
                free( response );
                return ( mp );
            }
        }

        maxNum = ((cnt / 20) + 1) * 20;
        maxCnt = cnt / 20;
        cnt = 0;
        num = 0;
    }

    mp = (MyClip *)malloc( sizeof ( MyClip ) * maxNum );
    if ( mp ) {
        char    tags[80];

        memset( mp, 0x00, sizeof ( MyClip ) * maxNum );
        p = response;

        while ( *p ) {
            u = NULL;
            if ( !strncmp( p, "<div class=\"bookmark-title\">", 28 ) ) {
                q = p + 28;
                u = strstr( q, "</li>" );
                r = strstr( q, "<a href=\"" );
                if ( r ) {
                    r += 9;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( mp[num].url, r, s - r );
                        mp[num].url[s - r] = NUL;

                        q = strstr( r, "\">" );
                        if ( q ) {
                            q += 2;
                            r = strstr( q, "</a>" );
                            if ( r ) {
                                strncpy( mp[num].title, q, r - q );
                                mp[num].title[r - q] = NUL;
                                p = r + 4;
                            }
                            else
                                p = q;
                        }
                        else
                            p = s + 1;
                    }
                    else
                        p = r;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p, "<div class=\"bookmark-description\">", 34 ) ) {
                q = p + 34;
                while ( (*q == ' ')  || (*q == '\t') ||
                        (*q == '\r') || (*q == '\n')    )
                    q++;
                r = strstr( q, "<br />" );
                if ( r ) {
                    strncpy( mp[num].comment, q, r - q );
                    mp[num].comment[r - q] = NUL;

                    s = mp[num].comment;
                    while ( ((t = strchr( s, '\n' )) != NULL) ||
                            ((t = strchr( s, '\r' )) != NULL)    ) {
                        if ( (*(t + 1) == '\r') || (*(t + 1) == '\n') )
                            strcpy( t, t + 1 );
                        *t = ' ';
                    }

                    p = r + 6;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p, "<div class=\"sublink\">", 21 ) ) {
                p = q = p + 21;
                r = strstr( q, "Tag: " );
                if ( r ) {
                    mp[num].tags[0] = NUL;
                    r += 5;
                    p = r;
                    do {
                        tags[0] = NUL;
                        s = strstr( r, "<a href=\"" );
                        t = strchr( r, ' ' );
                        if ( s && ((s < t) || (s == t + 1)) ) {
                            r = s + 9;
                            s = strchr( r, '>' );
                            if ( s ) {
                                s++;
                                t = strstr( s, "</a>" );
                                if ( t ) {
                                    strncpy( tags, s, t - s );
                                    tags[t - s] = NUL;
                                    p = r = t + 4;

                                    if ( mp[num].tags[0] != NUL )
                                        strcat( mp[num].tags, " " );
                                    strcat( mp[num].tags, tags );
                                }
                                else
                                    break;
                            }
                            else
                                break;
                        }
                        else
                            break;
                    } while ( r );

                    if ( !strncmp( p, "  <a href=\"/url/", 16 ) ) {
                        /* 「他:n人がリンク」 をスキップ */
                        p += 16;
                        q = strstr( p, "</a>" );
                        if ( q )
                            p = q + 4;
                    }
                    while ( p && ((*p < '0') || (*p > '9')) )
                        p++;
                    if ( p ) {
                        q = p;
                        yyyy = 2000 + (*q - '0') * 10 + (*(q + 1) - '0');
                        q += 2;

                        while ( *q && ((*q < '0') || (*q > '9')) )
                            q++;
                        mm   = (*q - '0') * 10 + (*(q + 1) - '0');
                        q += 2;

                        while ( *q && ((*q < '0') || (*q > '9')) )
                            q++;
                        dd   = (*q - '0') * 10 + (*(q + 1) - '0');
                        q += 2;

                        mp[num].yyyy = yyyy;
                        mp[num].mm   = mm;
                        mp[num].dd   = dd;
                        mp[num].HH   = 0;
                        mp[num].MM   = 0;
                        mp[num].SS   = 0;

                        p = q;

                        // 評価(マイレート)
                        if (((q = strstr(p, "alt=\"マイレート: ")) != NULL) &&
                            (q < u) ) {
                            long    rate;

                            q += 17;
                            rate = atol( q );
                            p = q + 1;

                            if ( rate > 0 ) {
#ifdef  OLD_FASHIONED
                                //   -- MM/Memo 互換の方法で記録する
                                //        title の前に (評価) を付加する
                                char    tmpTitle[BUFSIZ * 2];

                                sprintf( tmpTitle, "(%d)『%s』",
                                         rate, mp[num].title );
                                strcpy( mp[num].title, tmpTitle );
#else
                                // 「評価」は mp[num].evaluation に格納する
                                mp[num].evaluation = rate;
#endif
                            }
                        }

                        num++;
                        if ( num >= maxNum )
                            break;
                        mp[num].tags[0] = NUL;

                        if ( (num % 20) == 0 ) {
                            /* 次のページを読む */
                            cnt++;
                            if ( cnt > maxCnt )
                                break;
                            memset( response, 0x00, MAX_CONTENT_SIZE * 20 );
                            sprintf( url,
                                     "http://tags.blogpeople.net/user/%s/%d",
                                     username, cnt );
                            setTargetURL( url );
                            setUpReceiveBuffer( response, sz );
                            p = http_get( url, response );
                            if ( !p || !(*p) || !(*response) )
                                break;
                            p = response;
                            continue;
                        }
                    }
                }

                continue;
            }

            p++;
        }
    }

    *numOfClips = num;
    free( response );

    return ( mp );
}

#ifdef  GET_BLOGPEOPLE_TAGS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
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
                 "getBPT: BlogPeople Tags → OPML 変換出力ツール\n" );
        fprintf( stderr,
                 "\tBlogPeople Tags から吸い出した内容を OPML ファイルとして"
                 "出力する\n" );
        fprintf( stderr,
             "    getBPT [-x] -u ユーザ名\n" );
        fprintf( stderr, "\t-x: proxy を使う\n" );
        fprintf( stderr,
                 "\tユーザ名: BlogPeople にログインするときのユーザ名(メール"
                 "アドレス)\n\tではなく、BlogPeople Tags 用に指定したユーザ名"
                 "を使用する\n" );
    }
    else {
        // 英語
        fprintf( stderr,
                 "getBPT: get bookmarks from BlogPeople Tags, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getBPT [-x] -u username\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
        fprintf( stderr,
                 "\tusername: this is NOT E-mail address when log into "
                 "BlogPeople.\n\t\tSpecify the username as screen name for "
                 "BlogPeople Tags.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, &useProxy );

    if ( !(username[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* BlogPeople Tags へ登録済みのブックマークを取得 */
    mp = getBPTags( username, &total, &numOfClips );

    if ( (total > 0) && (numOfClips < total) ) {
        if ( getLanguageCode() == 0x0411 )
            fprintf( stderr,
                     "警告: 全 %d 件中、%d 件しか取得できませんでした\n",
                     total, numOfClips );
        else
            fprintf( stderr,
                     "Warning: Only %d in %d all was able to be acquired.\n",
                     numOfClips, total );
    }

    if ( mp && (numOfClips > 0) ) {
        /*  BlogPeople Tags 情報を OPML ファイルへ書き出す */
        outputOPML( mp, numOfClips, "BlogPeople Tags", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLOGPEOPLE_TAGS_EXE */

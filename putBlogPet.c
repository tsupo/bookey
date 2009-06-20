/*
 * clip loader <<putBlogPet>>
 *
 *      OPML → 「BlogPetブックマーク」登録プログラム
 *          written by H.Tsujimura  22 Dec 2006
 *
 * History:
 * $Log: /comm/bookey/putBlogPet.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 30    09/02/25 20:12 Tsujimura543
 * _putBlogPet() を修正 (初期化していないメモリ領域を参照していた)
 * 
 * 29    08/12/02 19:36 Tsujimura543
 * フォーマットストリング脆弱性関連のバグ修正
 * 
 * 28    08/02/19 21:58 Tsujimura543
 * 「BlogPet 気になる記事」 → 「BlogPetブックマーク」に名称変更
 * 
 * 27    07/11/13 23:15 Tsujimura543
 * コメントを整理
 * 
 * 26    07/11/13 23:12 Tsujimura543
 * (1) 登録しようとしているブックマークのタイトルが空文字列になることがあ
 *     る現象に対処 (2007年11月12日に現象を観測。翌13日には観測できていな
 *     いため、サーバ側で何か変更が行なわれた可能性がある。念のために
 *     bookey 側での対策も残しておく)
 * (2) 少しリファクタリング
 * 
 * 25    07/11/12 22:03 Tsujimura543
 * setTitleOnRequest() を修正、タイトルが長くて許容文字数を超える場合は、
 * 越えた部分を切り捨てるようにした
 * 
 * 24    07/11/09 18:03 Tsujimura543
 * エラーメッセージ(もしくは警告メッセージ)を取得できた場合は、その内容を
 * エラーダイアログに表示するようにした [様子見終了]
 * 
 * 23    07/11/05 20:43 Tsujimura543
 * 様子見バージョン
 * 
 * 22    07/10/31 20:49 Tsujimura543
 * ログを解析するときの目印用に dputs() を1箇所追加
 * 
 * 21    07/10/05 2:43 Tsujimura543
 * putBookmarks() の引数追加に伴う変更
 * 
 * 20    07/07/13 2:01 Tsujimura543
 * 2007年7月12日に実施された BlogPet リニューアルに対応
 * 
 * 19    07/02/16 16:19 Tsujimura543
 * コメントを修正
 * 
 * 18    07/02/16 16:16 Tsujimura543
 * すでに登録されているタイトルと登録しようとしているタイトルが食い違う場
 * 合は、登録しようとしているタイトルで上書きするか、すでに登録されている
 * タイトルをそのまま流用するか、選択できるようにした
 * 
 * 17    07/02/15 0:25 Tsujimura543
 * コードを整理
 * 
 * 16    07/02/14 23:26 Tsujimura543
 * getArticleIDbyURLonBlogPet(), editBogPet() を editBlogPet.c へ移動
 * 
 * 15    07/02/14 22:59 Tsujimura543
 * getArticleIDbyURLonBlogPet() のバグを2件修正
 *   (1) articleID が見つからない場合、永久にページ取得・探索を続けて
 *       しまう
 *   (2) ページ内のブックマークのうち最初の方の2つのみ評価するだけで、
 *       残りは読み飛ばしてしまう
 * 
 * 14    07/02/14 0:19 Tsujimura543
 * confirmPostBlogPet() の動作確認完了 (新規登録、上書き編集とも)
 * 
 * 13    07/02/14 0:06 Tsujimura543
 * すでに登録済みの記事を再登録しようとした場合は、上書き登録を実行する
 * ようにした
 * 
 * 12    07/02/05 21:41 Tsujimura543
 * タイトルの扱い方を変えてみた
 * 
 * 11    07/01/23 21:12 Tsujimura543
 * コマンドライン版をビルドできるようにした
 * 
 * 10    07/01/22 22:20 Tsujimura543
 * 英語モード対応
 * 
 * 9     07/01/18 23:45 Tsujimura543
 * putBookmarks() を導入。リファクタリングを実施
 * 
 * 8     07/01/17 16:28 Tsujimura543
 * Vox の記事を投稿しようとすると落ちる(BM_BODY に格納される「概要」
 * (Vox から返されるhtml本文)がbot 向けのメッセージで、そのメッセージ
 * 中に any2utf() では扱えない文字が含まれているのが原因で、any2utf()
 * が NULL を返す)不具合に対する改修を実施
 * (本格的な改修は any2utf() 側で行なう必要あり)
 * 
 * 7     06/12/25 23:37 Tsujimura543
 * loginBlogPet() に第4引数を追加
 * 
 * 6     06/12/25 23:21 Tsujimura543
 * タグ(キーワード)が1個しか登録できない不具合を修正
 * 
 * 5     06/12/25 19:28 Tsujimura543
 * 登録失敗時に表示するダイアログの文言を修正
 * 
 * 4     06/12/25 17:17 Tsujimura543
 * BM_TITLE, BM_BODY の元ネタ取得関連処理を修正
 * 
 * 3     06/12/25 17:13 Tsujimura543
 * すでに登録済みのページも、「公開レベル」が「一般公開」である場合、もし
 * くはタイトルや概要をまったく変更していない場合は、登録できるようにした
 * 
 * 2     06/12/25 16:11 Tsujimura543
 * すでに登録済みのページの登録に失敗するという不具合を除いて、
 * 動作確認終了
 * 
 * 1     06/12/22 21:58 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"
#include "blogPet.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBlogPet.c 1     09/05/14 3:48 tsupo $";
#endif

void
getTitleWithoutRate( const char *title, char *titleWithoutRate )
{
    char    *p;

    p = any2utf( title );
    strcpy( titleWithoutRate, p ? p : title );

    // MM/Memo 形式の title を扱うための処理
    getEvaluation( titleWithoutRate, UTF8 );
}

void
setUrlOnRequest( const char *url, char *request )
{
    sprintf( request + strlen(request),
             "url=%s&",
             encodeURL( url ) );
}

void
setTitleOnRequest( const char *title, char *request )
{
#define MAX_TITLE_LEN_FOR_BLOGPET   (50 * 2)  // タイトルは「全角50文字」まで
    char    tmpTitle[MAX_DESCRIPTION_LEN];
    char    *p = tmpTitle;

    tmpTitle[0] = NUL;
    any2sjisEx( tmpTitle, title );
    if ( tmpTitle[0] && (strlen( tmpTitle ) > MAX_TITLE_LEN_FOR_BLOGPET) )
        adjustStringLength( tmpTitle, MAX_TITLE_LEN_FOR_BLOGPET );

    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( any2utf( p && *p ? p : title ) ) );
}

void
setBodyOnRequest( const char *body, char *request )
{
    if ( body && body[0] )
        sprintf( request + strlen(request),
                 "excerpt=%s&",
                 encodeURLex2( any2utf( body ) ) );
    else
        sprintf( request + strlen(request),
                 "excerpt=&" );
}

void
setTagsOnRequest( const char *tags, char *request )
{
    char        tmpTags[2048];
    const char  *p, *q;
    int         i;

    p = any2utf( tags );
    if ( !p )
        p = tags;
    for ( i = 0; i <= 9; i++ ) {
        q = strchr( p, ' ' );
        if ( q ) {
            strncpy( tmpTags, p, q - p );
            tmpTags[q - p] = NUL;
        }
        else
            strcpy( tmpTags, p );
        sprintf( request + strlen(request),
                 "keywords=%s&",
                 encodeURL( tmpTags ) );
        if ( !q )
            break;
        p = q + 1;
    }
    for ( ; i <= 9; i++ )
        strcat( request, "keywords=&" );
}

void
setPolicyOnRequest( int publication, char *request )
{
    sprintf( request + strlen(request),
             "type=%s&",
             publication == PUB_PRIVATE ? "private"
                                        : "public" );
}

void
setCommentOnRequest( const char *comment, char *request )
{
    char    *p;

    p = any2utf( comment );
    sprintf( request /* + strlen(request) */,
             "comment=%s&",
             encodeURLex( p ? p : comment ) );
}


BOOL
_putBlogPet(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie    = args->cookie;
    char        *request   = args->request;
    char        *response  = args->response;
    size_t      sz         = args->sz;
    BOOL        useMyTitle = (BOOL)(args->args);
    char        url[MAX_URLLENGTH * 4];
    const char  *p, *q;
    char        tmpTitle[BLOGPET_TEMP_TITLE_LEN];
    char        tmpTitle2[BLOGPET_TEMP_TITLE_LEN];
    char        tmpBody[MAX_DESCRIPTION_LEN];
    char        cid[MAX_KEYLENGTH];
    BOOL        ret    = FALSE;
    BOOL        modify = FALSE;

    errorString[0] = NUL;
    tmpTitle2[0]   = NUL;
    tmpBody[0]     = NUL;
    cid[0]         = NUL;

    /* title と excerpt の元ネタを GET */
    sprintf( url,
             "http://www.blogpet.net/bookmark/modify?url=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "<div id=\"summary\">" );
        if ( p ) {
            const char  *r;

            if ( strstr( p, sjis2utf("<span>変更する</span>") ) )
                modify = TRUE;

            // title
            p += 18;
            q = strstr( p, "<input type=\"text\" name=\"title\"" );
            if ( q ) {
                q += 31;
                r = strstr( q, "value=\"" );
                if ( r ) {
                    q = r + 7;
                    r = strchr( q, '"' );
                    if ( r ) {
                        strncpy( tmpTitle2, q, r - q );
                        tmpTitle2[r - q] = NUL;
                    }
                }
            }

            // excerpt
            q = strstr( p, "<textarea name=\"excerpt\"" );
            if ( q ) {
                q += 24;
                r = strstr( q, "\">" );
                if ( r ) {
                    q = r + 2;
                    r = strstr( q, "</textarea>" );
                    if ( r ) {
                        strncpy( tmpBody, q, r - q );
                        tmpBody[r - q] = NUL;
                        if ( tmpBody[0] ) {
                            size_t  l = 0;
                            while ( ((l = strlen(tmpBody)) > 0)    &&
                                     ((tmpBody[l - 1] == '\r') ||
                                      (tmpBody[l - 1] == '\n')   )    )
                                tmpBody[l - 1] = NUL;
                        }
                    }
                }
            }

            // CID
            q = strstr( p, "name=\"CID\" value=\"" );
            if ( q ) {
                p = q + 18;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( cid, p, q - p );
                    cid[q - p] = NUL;
                }
            }
        }
    }

    /* ブックマークを POST */
    strcpy( url, "http://www.blogpet.net/bookmark/modify" );

    // コメント
    setCommentOnRequest( mp->comment, request );

    // キーワード (タグに相当、10個まで)
    setTagsOnRequest( mp->tags, request );

    // 公開レベル (一般公開、非公開)
    setPolicyOnRequest( mp->publication, request );

    // タイトル
    if ( useMyTitle )
        getTitleWithoutRate( mp->title, tmpTitle );
    else
        strcpy( tmpTitle, tmpTitle2 );
    if ( tmpTitle[0] == NUL )
        strcpy( tmpTitle, mp->title );
    setTitleOnRequest( tmpTitle, request );

    // 概要
    setBodyOnRequest( tmpBody, request );

    // CID
    sprintf( request + strlen( request ),
             "CID=%s&"
             "regist=%s",
             cid,
             modify ? encodeURL( sjis2utf("<span>変更する</span>") )
                    : encodeURL( sjis2utf("<span>登録する</span>") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        p = strstr( response, sjis2utf("ブックマークを登録しました") );
        if ( !p )
            p = strstr( response, sjis2utf("ブックマークを変更しました") );
        if ( p )
            ret = TRUE; // 登録成功
        else {
            dputs( "BlogPet: ブックマーク登録失敗\n" );
            p = strstr( response,
                        "<div class=\"systemMessage\">"
                        "<span class=\"warning\">" );
            if ( p ) {
                p += 49;
                q = strstr( p, "</span></div>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString, p );
                    ret = TRUE; /* 登録失敗だが、このままリトライしても失敗 */
                                /* するだけなので登録成功扱いとする         */
                }
            }
        }
    }

    return ( ret );
}

void
putBlogPet(
        const char   *userName,  /* (I) ユーザ名                       */
        const char   *password,  /* (I) パスワード                     */
        BOOL         useMyTitle, /* (I) タイトルを独自に設定するか否か */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    userID[MAX_KEYLENGTH];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* BlogPet 管理画面に login */
    userID[0] = NUL;
    ret = loginBlogPet( userName, password, cookie, userID );
    if ( ret == 1 ) /* login 成功 */
        putBookmarks( getLanguageCode() == 0x0411
                       ? "BlogPetブックマーク"
                       : "BlogPet bookmarks",
                      mp, numOfClips, cookie, cookieSize,
                      (void *)useMyTitle,
                      _putBlogPet );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "BlogPet管理画面への login に失敗しました\n"
                    : "BlogPet: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "BlogPet管理画面へのログインに失敗しました。  "
                         : "BlogPet: login failed.    ",
                        l == 0x0411
                         ? "ログイン失敗"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_BLOGPET_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useMyTitle,
        BOOL *useProxy,
        FILE **fp
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

                case 'F':
                    *useMyTitle = !(*useMyTitle);
                    break;

                case 'i':
                    if ( argv[i][j + 1] ) {
                        FILE    *gp = fopen( &(argv[i][j + 1]), "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s が見つかりません\n"
                                      : "%s: Not found.\n",
                                     &(argv[i][j + 1]) );
                            exit( 255 );
                        }
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        FILE    *gp = fopen( argv[i + 1], "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s が見つかりません\n"
                                      : "%s: Not found.\n",
                                     argv[i + 1] );
                            exit( 255 );
                        }
                        i++;
                        j = strlen( argv[i] ) - 1;
                    }
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
                 "putBlogPet: OPML → BlogPetブックマーク 登録ツール\n" );
        fprintf( stderr,
      "    putBlogPet [-x] [-F] -u ユーザ名 -p パスワード [-i OPMLファイル名]"
      "\n" );
        fprintf( stderr,
      "\t-x: proxy を使う\n"
      "\t-F: すでに登録されているタイトルと登録しようとしているタイトル\n"
      "\t    が食い違う場合は、登録しようとしているタイトルで上書きする\n"
      "\t    (「BlogPetブックマーク」では、タイトルは全員で共有しています。"
    "\n\t     上書きするかどうかは慎重に判断して決めてください)\n"
      "\t-i オプション省略時は標準入力から OPML ファイルを読み込みます\n" );
    }
    else {
        // 英語
        fprintf( stderr,
      "putBlogPet: read bookmarks from OPML, and put them into BlogPet \n"
      "            bookmarks\n");
        fprintf( stderr,
      "    putBlogPet [-x] [-F] -u username -p password [-i OPMLfilename]\n");
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-F: overwrite entry title, if original title was different from\n"
      "\t    your specified title\n"
      "\t    (Caution: entry title is shared by all users of BlogPet bookmarks)\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy   = FALSE;
    BOOL    useMyTitle = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &useMyTitle, &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPMLファイルからブックマークを取得 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* ブックマークを BlogPetブックマーク に登録 */
        putBlogPet( username, password, useMyTitle, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_BLOGPET_EXE */

/*
 *  editNiftyClip.c
 *      ニフティクリップへ登録済みのブックマークを編集するための各種関数群
 *          written by H.Tsujimura  30 Jan 2007
 *
 * $Log: /comm/bookey/editNiftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/03/17 18:23 Tsujimura543
 * 2008年3月11日の「@niftyクリップ」リニューアルに対応した
 * 
 * 3     07/01/30 21:31 Tsujimura543
 * コメントの typo を修正
 * 
 * 2     07/01/30 21:30 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     07/01/30 19:20 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"
#include "niftyClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editNiftyClip.c 1     09/05/14 3:48 tsupo $";
#endif

// ニフティクリップでは、JSON を利用した(仕様詳細が非公開の)APIを使ってタグ
// 一覧の取得、置換、削除などができる [注意: 2008年3月11日のリニューアルに
// 伴い、USERNAME の指定が必要になった]
//    (1) タグ一覧取得
//      http://clip.nifty.com/ajax/edittag/USERNAME に
//          command=init&_=
//      を POST
//    (2) タグの置換(タグの統合)
//      http://clip.nifty.com/ajax/edittag/USERNAME に
//          command=fusion&select_tags=統合前のタグ&select_tag=統合後のタグ&_=
//      を POST
//    (3) タグの削除
//      http://clip.nifty.com/ajax/edittag/USERNAME に
//          command=delete&select_tags=削除したいタグ&_=
//      を POST
//    (4) バルーン表示用のテキストの取得
//      http://clip.nifty.com/ajax/edittag/USERNAME に
//          command=balloon&select_tag=注目しているタグ&_=
//      を POST (select_tags ではなく select_tag であることに注意)


/*
 *  「指定ユーザが ニフティクリップ で使っているタグの一覧」を取得する
 */

TagList *
getTagListOnNiftyClip(
        const char *username,
        const char *password,
        int        *numOfTags )
{
    TagList *tagList = NULL;
    int     num = 0;
    char    cookie[MAX_COOKIE_LEN];

    *numOfTags = 0;
    cookie[0]  = NUL;

    if ( loginNiftyClip( username, password, cookie ) ) {
        char    url[MAX_URLLENGTH];
        char    request[MAX_CONTENT_SIZE];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    screenname[80];
        char    targetURL[MAX_URLLENGTH];

        response = (char *)malloc( sz );
        if ( !response )
            return ( tagList );

        screenname[0] = NUL;
        targetURL[0] = NUL;
        getScreenNameOnNiftyClip( screenname, targetURL,
                                  response, sz, cookie );

        sprintf( url, "http://clip.nifty.com/ajax/edittag/%s", screenname );
        strcpy( request, "command=init&_=" );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            char        *p, *q;
            const char  *target = "{\"name\":\"";

            p = response;
            while ( ( q = strstr( p, target ) ) != NULL ) {
                num++;
                p = q + 9;
            }

            if ( num > 0 ) {
                int num2 = 0;

                tagList = (TagList *)malloc( sizeof (TagList) * num );
                if ( tagList ) {
                    TagList *pp = tagList;

                    p = response;
                    while ( ( q = strstr( p, target ) ) != NULL ) {
                        p = q + 9;
                        q = strstr( p, "\"," );
                        if ( !q )
                            q = strstr( p, "\"}" );
                        if ( q ) {
                            strncpy( pp->tag, p, q - p );
                            pp->tag[q - p] = NUL;
                            p = q + 2;
                            pp++;
                            num2++;
                        }
                    }
                }

                if ( num != num2 )
                    num = num2;
            }
        }

        free( response );
    }

    *numOfTags = num;

    return ( tagList );
}



/* タグの削除 */
BOOL
removeTagFromBookmarksOnNiftyClip(
        const char *username,
        const char *password,
        const char *tag )
{
    BOOL    ret = FALSE;
    char    cookie[MAX_COOKIE_LEN];

    cookie[0] = NUL;

    if ( loginNiftyClip( username, password, cookie ) ) {
        char    url[MAX_URLLENGTH];
        char    *targetTag;
        char    request[MAX_CONTENT_SIZE];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    screenname[80];
        char    targetURL[MAX_URLLENGTH];

        response = (char *)malloc( sz );
        if ( !response )
            return ( ret );

        screenname[0] = NUL;
        targetURL[0] = NUL;
        getScreenNameOnNiftyClip( screenname, targetURL,
                                  response, sz, cookie );

        sprintf( url, "http://clip.nifty.com/ajax/edittag/%s", screenname );
        targetTag = sjis2utf( tag );
        sprintf( request,
                 "command=delete&"
                 "select_tags=%s&"
                 "_=",
                 encodeURL( targetTag ? targetTag : tag ) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"status\"" );
            if ( p ) {
                p += 8;
                p = strstr( p, "\"code\":\"0\"" );
                if ( p )
                    ret = TRUE;
            }
        }

        free( response );
    }

    return ( ret );
}

/* タグの置換 */
BOOL
renameTagFromBookmarksOnNiftyClip(
        const char *username,
        const char *password,
        const char *oldTag,
        const char *newTag )
{
    BOOL    ret = FALSE;
    char    cookie[MAX_COOKIE_LEN];

    cookie[0] = NUL;

    if ( loginNiftyClip( username, password, cookie ) ) {
        char    url[MAX_URLLENGTH];
        char    *targetTag;
        char    request[MAX_CONTENT_SIZE];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    screenname[80];
        char    targetURL[MAX_URLLENGTH];

        response = (char *)malloc( sz );
        if ( !response )
            return ( ret );

        screenname[0] = NUL;
        targetURL[0] = NUL;
        getScreenNameOnNiftyClip( screenname, targetURL,
                                  response, sz, cookie );

        sprintf( url, "http://clip.nifty.com/ajax/edittag/%s", screenname );
 
        targetTag = sjis2utf( oldTag );
        sprintf( request,
                 "command=fusion&"
                 "select_tags=%s&",
                 encodeURL( targetTag ? targetTag : oldTag ) );
        
        targetTag = sjis2utf( newTag );
        sprintf( request + strlen(request),
                 "select_tag=%s&"
                 "_=",
                 encodeURL( targetTag ? targetTag : newTag ) );

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"status\"" );
            if ( p ) {
                p += 8;
                p = strstr( p, "\"code\":\"0\"" );
                if ( p )
                    ret = TRUE;
            }
        }

        free( response );
    }

    return ( ret );
}

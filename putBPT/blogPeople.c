/*
 *  blogPeople.c
 *      BlogPeople にログインする
 *          written by H.Tsujimura  30 Sep 2005 / 18 Oct 2005
 *
 * $Log: /comm/bookey/putBPT/blogPeople.c $
 * 
 * 1     09/05/14 4:31 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     06/10/20 21:25 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 3     05/10/19 16:54 Tsujimura543
 * 冒頭のコメントを修正 (ファイル分離前のコメントのままだった)
 * 
 * 2     05/10/18 13:39 Tsujimura543
 * 注意書き(コメント)を追加
 * 
 * 1     05/10/18 13:34 Tsujimura543
 * getBPhash.c から loginBlogPeople() を分離、独立させて blogPeople.c を作成
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBPT/blogPeople.c 1     09/05/14 4:31 tsupo $";
#endif


/* BlogPeople にログインする */
//  注意: 第1引数で指定するメールアドレスについて
//          1つの login 用メールアドレスに他のメールアドレスを紐付けている場
//          合(複数blogを登録している場合)は、BlogPeople IB や BlogPeople Tags
//          を利用しているメールアドレスを指定する。他のメールアドレスを指定
//          して login しても、当該サービスは利用できない)
int
loginBlogPeople( const char *username,  // (I)   ユーザ名 (メールアドレス)
                 const char *password,  // (I)   パスワード
                 char       *cookie )   // (I/O) クッキー
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    if ( !cookie )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://member.blogpeople.net/member/member_index.jsp" );
    setTargetURL( url );
    sprintf( request,
             "user_id=%s&"
             "passwd=%s&"
             "autologin=1&"
             "Submit=　ログイン　&opt=&url=",
             username, password );
    setUpReceiveBuffer( response, sz );
    p = http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

    if ( !p || !(*p) )
        ret = 0;        /* サーバとの通信失敗 */
    else if ( *response ) {
        if ( strstr( response, "さんログイン中" ) != NULL )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }

    free( response );
    free( request  );

    return ( ret );
}

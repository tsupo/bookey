/*
 * blogPet.h  : ソーシャルブックマーク管理プログラム
 *      「BlogPet 気になる記事」関連の関数群
 *          written by H.Tsujimura  22 Dec 2006 / 14 Feb 2007
 *
 * $Log: /comm/bookey/blogPet.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     07/07/13 2:01 Tsujimura543
 * 2007年7月12日に実施された BlogPet リニューアルに対応
 * 
 * 4     07/02/15 0:25 Tsujimura543
 * コードを整理
 * 
 * 3     07/02/14 23:24 Tsujimura543
 * getArticleIDbyURLonBlogPet(), editBogPet(), confirmPostBlogpet() の
 * プロトタイプ宣言を blogPet.h へ移動
 * 
 * 2     07/02/14 23:13 Tsujimura543
 * _getBlogPet() のプロトタイプ宣言を blogPet.h へ移動
 * 
 * 1     07/02/14 23:10 Tsujimura543
 * encodeURLe() のプロトタイプ宣言を blogPet.h へ移動
 */

#ifndef __BLOGPET_H__
#define __BLOGPET_H__

/* 0x80 以上の値の文字コードのみをパーセントエンコードする */
char    *
encodeURLe( const char *p );


/* BlogPet気になる記事に登録済みのブックマーク情報の取得 */
int
_getBlogPet(
        const char *userID,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    );


/* 指定URLのBlogPet気になる記事内記事IDの取得 */
BOOL
getArticleIDbyURLonBlogPet(
        const char *targetURL,  /* (I)   検索対象URL */
        char       *cookie,     /* (I/O) クッキー    */
        char       *articleID   /* (O)   記事ID      */
    );

/* 指定記事IDの登録内容の編集 */
BOOL
editBlogPet(
        const MyClip *mp,           /* (I)   編集内容       */
        const char   *articleID,    /* (I)   編集対象記事ID */
        char         *cookie,       /* (I/O) クッキー       */
        char         *errorString   /* (O)   エラー情報     */
    );

/* BlogPet気になる記事にブックマークを登録(登録確認) */
BOOL
confirmPostBlogPet(
        const MyClip *mp,
        const char   *tmpTitle,
        const char   *tmpBody,
        const char   *articleID,
        char         *errorString,
        char         *request,
        char         *response,
        size_t       sz,
        char         *cookie
    );


void
getTitleWithoutRate( const char *title, char *titleWithoutRate );

void
setUrlOnRequest( const char *url, char *request );

void
setTitleOnRequest( const char *title, char *request );

void
setBodyOnRequest( const char *body, char *request );

void
setTagsOnRequest( const char *tags, char *request );

void
setPolicyOnRequest( int publication, char *request );

void
setCommentOnRequest( const char *comment, char *request );


#define BLOGPET_TEMP_TITLE_LEN  2048

#endif  /* __BLOGPET_H__ */

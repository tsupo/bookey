/*
 * deleteBookmark.h  : ソーシャルブックマーク管理プログラム
 *      ブックマークを削除する関数群
 *          written by H.Tsujimura  7 Jun 2005
 *
 * $Log: /comm/bookey/deleteBookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    08/11/11 15:09 Tsujimura543
 * DeleteNiftyClip() を追加
 * 
 * 23    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 22    08/07/28 20:32 Tsujimura543
 *  deleteEntryOnLivedoorClip2() を追加
 * 
 * 21    08/07/26 0:32 Tsujimura543
 * DeleteDiigo() を追加
 * 
 * 20    07/10/05 2:42 Tsujimura543
 * BBAuth 対応関連の各種修正を実施
 * 
 * 19    07/09/13 22:29 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 18    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks と Yahoo! ブックマークの「削除」に対応
 * 
 * 17    07/03/30 14:09 Tsujimura543
 * FC2BOOKMARK の「削除」に対応
 * 
 * 16    07/03/30 13:49 Tsujimura543
 * deleteEntryOnFC2bookmark() を追加
 * 
 * 15    06/12/22 21:47 Tsujimura543
 * 「BlogPet 気になる記事」に対応
 * 
 * 14    06/12/21 21:18 Tsujimura543
 * JoltMark に対応
 * 
 * 13    06/10/26 22:38 Tsujimura543
 * 「ローカルOPML」に対応
 * 
 * 12    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 11    06/10/05 20:01 Tsujimura543
 * POOKMARK Airlines 関連のプロトタイプ宣言を追加
 * 
 * 10    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 9a    06/09/03 19:21 tsupo
 * DBSparam_t の cookie をポインタから、実体(配列)に変更
 * 
 * 9     06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 8     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() を導入し、(削除用)ブックマーク情報取得処理を
 * 別スレッド化した
 * 
 * 7     06/08/25 18:11 Tsujimura543
 * 各関数の引数を1個追加(ProceedingDialog) [削除用のブックマーク取得処理を
 * 別スレッド化するための準備]
 * 
 * 6     06/08/22 17:57 Tsujimura543
 * DeleteDrecomRSS() と Delete1470net() を追加
 * 
 * 5     06/08/18 15:05 Tsujimura543
 * ECナビ人気ニュースの「削除」に対応
 * 
 * 4     06/07/12 9:40 Tsujimura543
 * DeleteLivedoorClip() と DeleteNiftyClip() を追加
 * 
 * 3     06/06/27 15:24 Tsujimura543
 * Flog の削除に対応
 * 
 * 2     06/06/22 14:56 Tsujimura543
 * 使っていない関数を削除
 * 
 * 1     06/06/07 15:34 Tsujimura543
 * 新規作成 (CUserInfo 導入によるリファクタリング第3段階、終了)
 */

#ifndef __DELETE_BOOKMARK_H__
#define __DELETE_BOOKMARK_H__

void    DeleteHetanaBookmark(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteDeliciousBookmark(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteBlueDotBookmark(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    Delete1470net(
                const char       *userName,  /* (I) 認証用ユーザ名         */
                const char       *password,  /* (I) 認証用パスワード       */
                const char       *userName2, /* (I) 認証用ユーザ名(予備)   */
                const char       *password2, /* (I) 認証用パスワード(予備) */
                AUTH_TYPE        authType,   /* (I) 認証タイプ             */
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteDiigo(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteNiftyClip(
                const char       *apiKey,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteLocalOpml(
                const char       *filename,  /* (I) OPMLファイル名 */
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

/* 削除実行処理 */
BOOL    deleteEntryOnMMmemo( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnDrecomRSS( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnFlog( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnLivedoorClip( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnEcNaviClip( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnNiftyClip( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnPookmark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnJoltMark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnBlogPet( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnFC2bookmark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnYJbookmark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnYahooBookmarks( char *cookie, const MyClipEx *mp );

BOOL    deleteEntryOnLivedoorClip2(
            const char *username,
            const char *apiKey,
            const char *url );

/* (削除用)ブックマーク取得処理 */
MyClipEx    *
getMMmemo2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getDrecomRSS2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getFlog2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getLivedoorClip2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getEcNaviClip2(
        const char       *username,
        const char       *password,
        const char       *username2,  /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char       *password2,  /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE        authType,    /* (I) 認証タイプ                     */
        char             *cookie,
        size_t           *cookieSize,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getNiftyClip2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
get1470net2(
        const char       *username,
        const char       *password,
        const char       *username2,
        const char       *password2,
        AUTH_TYPE        authType,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getPookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getJoltMark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getBlogPet2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getFC2bookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getYJbookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getYahooBookmarks2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

/* (削除用)ブックマーク情報取得スレッド起動処理 */
typedef struct param_sub2a  {
    // ブックマーク情報取得スレッドに渡す引数構造体
    int                 bookmarkKind;
    RBuser_t            u;
    int                 numOfBookmarks;
    char                cookie[MAX_COOKIE_LEN + 1];
    size_t              cookieSize;
    MyClipEx            *myBookmark;
    ProceedingDialog    *dlg;
}   DBSparam_t;

MyClipEx  *
GetBookmarksForDelete( DBSparam_t *param,
                       int        &numOfMyBookmarks );

#endif  /* __DELETE_BOOKMARK_H__ */

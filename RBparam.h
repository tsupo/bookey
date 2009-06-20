/*
 * RBparam.h : ソーシャルブックマーク管理プログラム
 *      RBparam 構造体の定義
 *          written by H.Tsujimura  29 Sep 2005, 27 Dec 2006
 *
 * $Log: /comm/bookey/RBparam.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 13    09/05/28 22:13 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 11    08/11/05 18:14 Tsujimura543
 * RBuser_t 構造体に apiKey メンバを追加
 * 
 * 10    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 9     08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 8     07/10/31 17:14 Tsujimura543
 * tumblr に対応
 * 
 * 7     07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 6     07/05/23 16:11 Tsujimura543
 * Timelog への登録(発言)に対応
 * 
 * 5     07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 4     07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 3     07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 2     07/02/16 13:58 Tsujimura543
 * RBuser_t 構造体に useMyTitle メンバを追加
 * 
 * 1     06/12/27 11:47 Tsujimura543
 * RBparam 構造体の定義を bookey.h から分離独立させて RBparam.h とする
 */

#ifndef __RB_PARAM_H__
#define __RB_PARAM_H__

// ブックマーク登録スレッド(および EditBookmarkDialog ダイアログ)に渡す
// パラメータ格納用構造体

typedef struct RBuserInfo {
    BOOL        isTarget;           /* 登録対象か否か                       */
    BOOL        useMyTitle;         /* タイトルを独自に設定するか否か       */
    char        username[32];       /* for メイン認証                       */
    char        password[32];       /* for メイン認証                       */
    char        username2[32];      /* for 予備認証                         */
    char        password2[32];      /* for 予備認証                         */
    char        apiKey[MAX_KEYLENGTH + 1]; /* APIキー / OAuth access token  */
    char        secret[MAX_KEYLENGTH + 1]; /* OAuth access token secret     */
    char        blogID[MAX_URLLENGTH + 1]; /* 投稿対象 Blog ID または group */
    char        filename[MAX_PATH]; /* ローカルOPMLファイル名               */
    AUTH_TYPE   authType;           /* 認証種別                             */
}   RBuser_t;

typedef struct RBparam {
    RBuser_t            hatena;
    RBuser_t            delicious;
    RBuser_t            mmMemo;
    RBuser_t            drecomRss;
    RBuser_t            flog;
    RBuser_t            livedoorClip;
    RBuser_t            ecNaviClip;
    RBuser_t            niftyClip;
    RBuser_t            next1470net;
    RBuser_t            newsing;
    RBuser_t            pookmark;
    RBuser_t            blueDot;
    RBuser_t            joltMark;
    RBuser_t            fc2bookmark;
    RBuser_t            blogPet;
    RBuser_t            twitter;
    RBuser_t            yjBookmark;
    RBuser_t            yahooBookmarks;
    RBuser_t            timelog;
    RBuser_t            digg;
    RBuser_t            tumblr;
    RBuser_t            diigo;
    RBuser_t            localOpml;
    char                url[MAX_URLLENGTH];
    BOOL                useTagSuggestion;
    BOOL                useUsers;
    BOOL                active;
    ProceedingDialog    *procDialog;
}   RBparam_t;


// ブックマーク登録スレッド
UINT
RegisterBookmark( LPVOID pParam );

#endif  /*__RB_PARAM_H__ */

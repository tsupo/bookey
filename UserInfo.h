/*
 * UserInfo.h  : ソーシャルブックマーク管理プログラム
 *      CUserInfo クラスの宣言およびインターフェイスの定義
 *          written by H.Tsujimura  1 Jun 2005
 *
 * $Log: /comm/bookey/UserInfo.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 56    09/05/28 22:40 Tsujimura543
 * m_blogName を追加
 * 
 * 55    09/05/28 22:13 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 54    09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 53    08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 52    08/07/28 15:30 Tsujimura543
 * m_apiKey を追加
 * 
 * 51    08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 50    07/10/31 16:58 Tsujimura543
 * tumblr に対応
 * 
 * 49    07/09/13 22:29 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 48    07/09/06 18:02 Tsujimura543
 * CUserInfoクラスのコピーコンストラクタ、代入演算子の内容を書き直し、
 * private化した
 * 
 * 47    07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 46    07/05/23 16:11 Tsujimura543
 * Timelog への登録(発言)に対応
 * 
 * 45    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 44    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 43    07/04/16 17:59 Tsujimura543
 * del.icio.us の posts/all 形式の XML ファイルのインポートとエクスポート
 * に対応した
 * 
 * 42    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 41    07/03/29 23:04 Tsujimura543
 * FC2BOOKMARK に対応
 * 
 * 40    07/01/29 17:51 Tsujimura543
 * タグ一覧の取得、タグの削除、タグの置換の各処理を追加
 * 
 * 39    07/01/12 23:34 Tsujimura543
 * 英語モード対応
 * 
 * 38    06/12/22 22:36 Tsujimura543
 * 「BlogPet 気になる記事」対応
 * 
 * 37    06/12/21 14:08 Tsujimura543
 * FC2BOOKMARK, 「BlogPet 気になる記事」対応準備
 * 
 * 36    06/12/06 19:48 Tsujimura543
 * コメントを修正
 * 
 * 35    06/12/06 19:46 Tsujimura543
 * livedoor Clip のエクスポートファイル(RSS 2.0 形式)をインポートする機能
 * を追加した
 * 
 * 34    06/11/16 16:43 Tsujimura543
 * CUserInfo 導入によるリファクタリング第16段階、終了
 * 
 * 33    06/11/16 14:02 Tsujimura543
 * CUserInfo 導入によるリファクタリング第15段階、終了
 * 
 * 32    06/11/10 19:26 Tsujimura543
 * ブラウザのブックマークを取り込む/ブラウザに取り込める形式のブックマーク
 * ファイルを生成する機能をサポートするための準備
 * 
 * 31    06/10/28 1:14 Tsujimura543
 * 「ローカルOPML」へ登録できないことがある不具合に対処
 * 
 * 30    06/10/26 22:54 Tsujimura543
 * 「ローカルOPML」に対応
 * 
 * 29    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 28    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline に対応
 * 
 * 27    06/09/29 23:48 Tsujimura543
 * newsing に対応
 * 
 * 26    06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 25    06/08/22 17:53 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 24    06/08/22 16:59 Tsujimura543
 * enum authenticationType の定義を myClip.h 内に移した
 * 
 * 23    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 22    06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 21    06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 * 
 * 20    06/07/19 14:19 Tsujimura543
 * MyClip! 関係の処理を削除 (2006年6月末でサービス終了のため)
 * 
 * 19    06/07/14 18:09 Tsujimura543
 * はてな認証API 対応準備
 * 
 * 18    06/07/05 18:19 Tsujimura543
 * CUserInfo 導入によるリファクタリング第13段階、終了
 * 
 * 17    06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 16    06/06/29 18:47 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 15    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 14    06/06/22 21:21 Tsujimura543
 * inquery → inquiry に修正(綴りミス)
 * 
 * 13    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() を実行しても、設定が変更できなくなって
 * しまっていた(エンバグ)のを修正。変更できるようにした
 * 
 * 12    06/06/21 21:14 Tsujimura543
 * CUserInfo 導入によるリファクタリング第11段階、終了
 * 
 * 11    06/06/20 17:59 Tsujimura543
 * CUserInfo 導入によるリファクタリング第10段階、終了
 * 
 * 10    06/06/20 14:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第9段階、終了
 * 
 * 9     06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 8     06/06/14 22:40 Tsujimura543
 * CUserInfo 導入によるリファクタリング第7段階、終了
 * 
 * 7     06/06/14 11:44 Tsujimura543
 * CUserInfo 導入によるリファクタリング第5段階、終了
 * 
 * 6     06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 5     06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 4     06/06/06 22:23 Tsujimura543
 * CUserInfo 導入によるリファクタリング第2段階、終了
 * 
 * 3     06/06/01 23:10 Tsujimura543
 * CUserInfo 導入によるリファクタリング第1段階、終了
 * 
 * 2     06/06/01 20:28 Tsujimura543
 * CBookeyDlg 内のユーザ名、パスワードを CUserInfo を使って管理する
 * ように変更した
 * 
 * 1     06/06/01 19:08 Tsujimura543
 * bookeyView.h から分離独立させた
 */

#ifndef __CUSER_INFO_H__
#define __CUSER_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#ifdef __cplusplus
}
#endif

#include "ProceedingDialog.h"

// CUserInfo クラス
class CUserInfo
{
public:
    /* ブックマーク種別 */
    enum bookmarkType {
        BK_UNKNOWN = 0,
        BK_HATENA,
        BK_DELICIOUS,
        BK_MM_MEMO,
        BK_DRECOM_RSS,
        BK_FLOG,
        BK_LIVEDOOR_CLIP,
        BK_ECNAVI_CLIP,
        BK_NIFTY_CLIP,
        BK_JOLTMARK,
        BK_NEWSING,
        BK_POOKMARK,
        BK_BLUEDOT,
        BK_FC2BOOKMARK,
        BK_BLOGPET,
        BK_TWITTER,
        BK_YJ_BOOKMARK,
        BK_YAHOO_BOOKMARKS,
        BK_TIMELOG,
        BK_DIGG,
        BK_TUMBLR,
        BK_DIIGO,
        BK_1470NET = 1024,
        BK_LOCAL_OPML = 2048,
        BK_NETSCAPE_BOOKMARK_FILE_1,
        BK_OPERA6_ADR,
        BK_HATENA_BOOKMARK_ATOM,
        BK_LIVEDOOR_CLIP_RSS,
        BK_DELICIOUS_XML
    };

    /* コンストラクタ */
    CUserInfo()
    {
        Init();
    }
    CUserInfo( bool isTarget, CString username, CString password )
    {
        Init( isTarget, username, password );
    }

    /* 初期化 */
    void    Init();
    void    Init( bool isTarget, CString username, CString password );
    void    Init( bool isTarget ) { m_isTarget = isTarget; }
    void    Init( enum bookmarkType bmType );

    void    GetUserInfo( CString &username,
                         CString &password,
                         enum bookmarkType &bmType );

    /* 再設定 */
    void    ResetUserInfo( bool &needToSave );
    void    ResetUserInfo( bool &needToSave,
                           BOOL &isTarget,
                           char *username, char *password );
    void    ResetUserInfo( bool &needToSave,
                           BOOL &isTarget,
                           char *filename );

    /* ユーザ名、パスワードの設定 */
    void    SetBookeyInfo();

    /* 表示 */
    void    SetWindowText( CString &username,
                           CString &password,
                           CEdit   *editUsername,
                           CEdit   *editPassword );
    void    SetWindowText( CString &username,
                           CEdit   *editUsername );

    /* 問い合わせ */
    int     InquiryToUseService();
    bool    InquiryUserInfo( CString bookmark1, CString bookmark2, 
                             CString txt );

    /* ブックマークのインポート */
    void    ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction );
    void    ImportFromAnotherToOne(
                const MyClip     *myAnother, int numOfAnother,
                const MyClip     *myOne,     int numOfOne,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg );

    /* ブックマークのエクスポート */
    bool    ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2);
    bool    ExportFromAnother(
                MyClip **myAnother, int *numOfAnother );

    /* ブックマークの削除 */
    void    DeleteBookmarks(
                const char       *username,
                const char       *password,
                const char       *username2,
                const char       *password2,
                AUTH_TYPE        authType,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL );
    void    DeleteBookmarks( bool deleteAll, bool deleteInteractive );

    /* ブックマークの登録 */
    void    PutBookmarks( const MyClip     *myBookmark,
                          int              numOfMyBookmarks,
                          const char       *username,
                          const char       *password,
                          ProceedingDialog *pDlg );
    void    PutBookmarks( const MyClip     *myBookmark,
                          ProceedingDialog *pDlg,
                          bool             useOrigText = false );
    void    PutBookmarks( const MyClip *myBookmark,
                          int          numOfMyBookmarks,
                          const char   *username = NULL,
                          const char   *password = NULL );
    void    PutBookmarks( const MyClip *myBookmark,
                          int          numOfMyBookmarks,
                          const char   *bookmarkNameAsImport,
                          bool         &result );

    void    PutBookmarks( bool         force,
                          const MyClip *myBookmark,
                          int          numOfMyBookmarks,
                          const char   *username = NULL,
                          const char   *password = NULL );


    /* ブックマークの取得 */
    MyClip  *GetBookmarks( int        &numOfMyBookmarks,
                           const char *username = NULL,
                           const char *password = NULL );
    MyClip  *GetBookmarks( int        *numOfMyBookmarks,
                           const char *username = NULL,
                           const char *password = NULL ) {
        MyClip  *p  = NULL;
        int     num = 0;
        p = GetBookmarks( num, username, password );
        *numOfMyBookmarks = num;
        return ( p );
    }
    MyClip  *GetBookmarks( int  &numOfMyBookmarks,
                           bool &result );

    /* タグ一覧の取得 */
    TagList *GetTagList( int &numOfTags );

    /* タグの削除 */
    void    DeleteTag( const char *tag );

    /* タグの置換 */
    void    ReplaceTag( const char *oldTag, const char *newTag );

    /* 認証方法 */
    AUTH_TYPE   GetAuthType() { return (m_authType); }
    void    SetAuthType( AUTH_TYPE authType ) {
                m_authType = authType;
            }

    /* 初期設定ファイル関連 */
    bool    EvalKeys(
                const char          *p,      // (I) 設定データ取得対象文字列
                const unsigned char *secret);// (I) 復号に必要な情報(秘密鍵)
    bool    CheckKeys(
                const char          *p,      // (I) 設定データ取得対象文字列
                const unsigned char *secret, // (I) 復号に必要な情報(秘密鍵)
                bool                &ret );  // (O) 復号保証可否
    void    WriteKeys(
                FILE          *fp,      // (I/O) 書き出し先
                char          *key,     // (I)   公開鍵
                unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
                bool          &done );  // (O)   暗号化処理実行済みか否か

    /* ブックマーク出力(エクスポート)時の入力(インポート)側の文字コードを取得 */
    int GetChangeCode( CString bookmarkNameAsImport );

    /* 各種演算子 */
    operator bool()                 { return (m_isTarget); }
    bool operator=  ( bool value )  { m_isTarget = value;
                                      return (m_isTarget); }
    operator const char *()         { return ((const char *)m_bmName); }

    CString             m_username;     // ユーザ名
    CString             m_password;     // パスワード
    CString             m_username2;    // ユーザ名 (予備)
    CString             m_password2;    // パスワード (予備)
    CString             m_blogID;       // 投稿先 Blog ID または group
    CString             m_blogName;     // 投稿先 Blog または group の名前
    CString             m_opmlFilename; // ローカルOPMLファイル名
    CString             m_apiKey;       // APIキー / OAuth access token
    CString             m_secret;       // OAuth access token secret
    bool                m_useMyTitle;   // ブックマーク登録時、自分で設定しよ
                                        // うとしているタイトルを優先的に適用
                                        // するか否か (他者によって設定済みの
                                        // タイトルを受け入れるか否か)

private:
    bool                m_isTarget; // 登録対象とするか否か
    enum bookmarkType   m_bmType;   // ブックマーク種別
    AUTH_TYPE           m_authType; // 認証種別
    CString             m_bmName;   // ブックマークサービス名
    CString             m_bmSymbol; // ブックマークサービスを象徴する名前

protected:
    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_fc2bookmark;
    CString m_tgt_blogPet;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_diigo;
    CString m_tgt_hatenaFeed;
    CString m_tgt_deliciousXML;

private:
    CUserInfo operator= ( CUserInfo &u ) {
        m_username     = u.m_username;
        m_password     = u.m_password;
        m_username2    = u.m_username2;
        m_password2    = u.m_password2;
        m_opmlFilename = u.m_opmlFilename;
        m_useMyTitle   = u.m_useMyTitle;
        m_isTarget     = u.m_isTarget;
        m_bmType       = u.m_bmType;
        m_authType     = u.m_authType;
        m_bmName       = u.m_bmName;
        m_bmSymbol     = u.m_bmSymbol;

        return ( *this );
    }

    CUserInfo( CUserInfo &info ) {
        m_username     = info.m_username;
        m_password     = info.m_password;
        m_username2    = info.m_username2;
        m_password2    = info.m_password2;
        m_opmlFilename = info.m_opmlFilename;
        m_useMyTitle   = info.m_useMyTitle;
        m_isTarget     = info.m_isTarget;
        m_bmType       = info.m_bmType;
        m_authType     = info.m_authType;
        m_bmName       = info.m_bmName;
        m_bmSymbol     = info.m_bmSymbol;
    }
};

#endif  /* __CUSER_INFO_H__ */

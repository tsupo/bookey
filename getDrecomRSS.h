/*
 * clip saver <<getDrecomRSS>>
 *
 *      ドリコムRSS-Clip → OPML 変換出力プログラム
 *          written by H.Tsujimura  1 Sep 2006
 *
 * $Log: /comm/bookey/getDrecomRSS.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     08/07/26 0:32 Tsujimura543
 * decodeContents() のプロトタイプ宣言を myClip.h へ移動
 * 
 * 6     07/02/15 0:29 Tsujimura543
 * getArticleIDbyURL() を getArticleIDbyURLonDrecomRSS() に名称変更
 * 
 * 5     07/02/05 21:40 Tsujimura543
 * getArticleIDbyURL() の引数を追加。フォルダ番号がわかっている場合は
 * 記事IDの発見に要する時間を短縮できるようになった
 * 
 * 4     07/02/05 17:55 Tsujimura543
 * getArticleIDbyURL() と editDrecomRSS() を実装
 * 
 * 3     06/09/04 19:25 Tsujimura543
 * 二重インクルード防止用の記述を追加
 * 
 * 2     06/09/01 19:48 Tsujimura543
 * コメントを記入
 * 
 * 1     06/09/01 18:53 Tsujimura543
 * 最初の版 (getDrecomRSS.c と DeleteDrecomRSS.cpp の共通部分をヘッダ
 * ファイル化)
 */

#ifndef __GET_DRECOM_RSS_H__
#define __GET_DRECOM_RSS_H__

/* スレッドローカル格納領域 (TLS stands for "Thread Local Storage", but not */
/*             neither "Transport Layer Security" nor "True Love Story" :-) */
#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

#define MAX_DRECOM_RSS_PER_BLOCK    200 /* ブロック単位でのメモリ一括取得時 */
                                        /* の 1ブロックあたりの配列個数     */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ドリコムRSSの Clip! のフォルダ一覧
 */
typedef struct folderListOnDrecomRSS  {
    int     folderNumber;   /* フォルダ番号 */
    char    folderName[80]; /* フォルダ名   */
}   FOLDER_LIST;


/*
 *  ドリコムRSSの Clip! 関連共通関数
 *      ・ドリコムRSS の Clip! の操作(クリップの一覧取得・詳細取得・編集・削
 *        除、フォルダの作成・削除)は、原則としては JSON-RPC API 経由で行なう
 *      ・JSON-RPC API を実行するには objectID が必要である
 *      ・objectID は ドリコムRSS に logon 後、クリップリーダーにアクセスした
 *        日時を元に生成する
 *      ・フォルダ一覧は、クリップリーダーのトップページの html ソースを解析す
 *        ることで得られるため、フォルダ一覧の取得にあたっては JSON-RPC API の
 *        実行(objectID)は必要ない
 */

/* objectID の生成・登録 */
BOOL
setObjectID(
        char *objectID, /* (O)   生成(後、登録を実施)した objectID */
        char *cookie    /* (I/O) クッキー                          */
    );

/* フォルダ名に対応する(他のソーシャルブックマークでいうところの)タグを取得 */
void
getTagByName(
        char       *tag,        /* (O) タグ       */
        const char *folderName  /* (I) フォルダ名 */
    );

/* フォルダ一覧の取得 */
FOLDER_LIST *
getFolderList(
        const char *htmlSrc,        /* (I) クリップリーダーのトップページの */
                                    /*     html ソース                      */
        int        *numOfFolders    /* (O) フォルダの数                     */
    );

/* 指定フォルダの指定年のクリップ一覧の取得 */
char    *
getArticleList(
        int        folderNumber,    /* (I)   取得対象「フォルダ番号」    */
        int        year,            /* (I)   取得対象「年」              */
        int        page,            /* (I)   取得対象「ページ番号」      */
        const char *objectID,       /* (I)   objectID                    */
        char       *response,       /* (I/O) JSON-RPC API 実行結果格納用 */
        size_t     sz,              /* (I)   response の示す領域のサイズ */
        char       *cookie          /* (I/O) クッキー                    */
    );

/* 指定クリップの内容の取得 */
char    *
getArticleDetail(
        const char *articleID,  /* (I)   取得対象のクリップの ID     */
        const char *objectID,   /* (I)   objectID                    */
        char       *response,   /* (I/O) JSON-RPC API 実行結果格納用 */
        size_t     sz,          /* (I)   response の示す領域のサイズ */
        char       *cookie      /* (I/O) クッキー                    */
    );

/* 指定URLのドリコムRSSクリップリーダー内記事IDの取得 */
BOOL
getArticleIDbyURLonDrecomRSS(
        const char *url,        /* (I)   検索対象URL */
        long       folderNumber,/* (I) フォルダ番号  */
        char       *cookie,     /* (I/O) クッキー    */
        char       *articleID   /* (O)   記事ID      */
    );

/* 指定記事IDの登録内容の編集 */
BOOL
editDrecomRSS(
        const MyClip *mp,           /* (I)   編集内容       */
        const char   *articleID,    /* (I)   編集対象記事ID */
        char         *cookie,       /* (I/O) クッキー       */
        char         *errorString   /* (O)   エラー情報     */
    );

#ifdef __cplusplus
}
#endif

#endif  /* __GET_DRECOM_RSS_H__ */

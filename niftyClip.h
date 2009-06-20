/*
 * niftyClip.h  : ソーシャルブックマーク管理プログラム
 *      「ニフティクリップ」関連の関数群
 *          written by H.Tsujimura  7 Jul 2006 / 17 Mar 2008
 *
 * $Log: /comm/bookey/niftyClip.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/11/11 16:41 Tsujimura543
 * NUM_OF_INFO_PER_NIFTY_API の定義を niftyClip.h へ移動
 * 
 * 3     08/11/11 16:17 Tsujimura543
 * _getNiftyClipWithApiKey() を追加
 * 
 * 2     08/03/17 17:59 Tsujimura543
 * コメント(引数の説明)を修正
 * 
 * 1     08/03/17 17:57 Tsujimura543
 * 今までニフティクリップ関連の各ソースファイル中で別々に宣言していた
 * プロトタイプ宣言を共通のヘッダファイルに集約した
 */

#ifndef __NIFTY_CLIP_H__
#define __NIFTY_CLIP_H__

#ifdef __cplusplus
extern "C" {
#endif

char    *
getScreenNameOnNiftyClip(
        char   *screenname, // (O)   スクリーン名
        char   *targetURL,  // (O)   ログイン中ユーザのクリップのトップページ
        char   *response,   // (I/O) 受信電文格納領域
        size_t sz,          // (I)   受信電文格納領域サイズ
        char   *cookie      // (I/O) クッキー
    );

int
_getNiftyClip(
        const char *target,  // (I)   ユーザのクリップのトップページ
        const char *userName,// (I)   ユーザ名またはスクリーン名
        char       *cookie,  // (I/O) クッキー
        MyClip     **mp,     // (I/O) ブックマーク情報 (for 取得系)
        MyClipEx   **mpEx,   // (I/O) ブックマーク情報 (for 削除系)
        char       *response,// (I/O) 受信電文格納領域
        size_t     sz,       // (I)   受信電文格納領域サイズ
        int        *total    // (O)   クリップ数
    );

int
_getNiftyClipWithApiKey(
        const char *apiKey,     /* (I) APIキー                      */
        long       offset,      /* (I) 取得開始ブックマーク位置     */
        long       *numOfPosts, /* (I) 取得するブックマークの数     */
                                /* (O) 取得したブックマークの数     */
        MyClip     *posts,      /* (O) 取得したブックマーク         */
        BOOL       *more        /* (O) 取得可能残存ブックマーク有無 */
    );

#define NUM_OF_INFO_PER_NIFTY_API   100  /* 1回のAPI実行で取得する情報数 */

#ifdef __cplusplus
}
#endif

#endif  /* __NIFTY_CLIP_H__ */

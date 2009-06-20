/*
 * tumblr.h : ソーシャルブックマーク管理プログラム
 *      tumblr 関連 ヘッダーファイル
 *          written by H.Tsujimura  29 May 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/tumblr.h $
 * 
 * 1     09/05/29 8:31 tsupo
 * VSSサーバ拠点を変更
 * 
 * 1     09/05/29 0:14 Tsujimura543
 * 最初の版 (BloGolEe向けに作成したソースを流用)
 */

#ifndef __TUMBLR_H__
#define __TUMBLR_H__

#ifdef __cplusplus
extern "C" {
#endif
int
getBlogIDsTumblr(
    const char *userName,       // (I) ユーザ名 (メールアドレス)
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する/取得した blog 情報の数
    BLOGINF    *blogInfo );     // (O) 取得した blog 情報
#ifdef __cplusplus
}
#endif

#endif  /* __TUMBLR_H__ */

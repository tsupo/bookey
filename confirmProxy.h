/*
 * confirmProxy.h  : ソーシャルブックマーク管理プログラム
 *      proxy情報設定確認処理 ヘッダーファイル
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/confirmProxy.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 2     07/03/14 17:38 Tsujimura543
 * checkProxyInfo() を改良
 * 
 * 1     07/03/14 16:22 Tsujimura543
 * (1) 「ブログクライアント BloGolEe」用に書いたソースを取り込む
 * (2) バイリンガル対応
 * =======================================================================
 * 3     07/03/10 5:22 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応してみた
 * 
 * 2     07/03/09 21:21 Tsujimura543
 * checkProxyInfo() を追加
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#ifndef __CONFIRM_PROXY_INFO_H__
#define __CONFIRM_PROXY_INFO_H__

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword );

void    initProxyInfo();
bool    checkProxyInfo();

#define syncProxyInfo   initProxyInfo

#endif  /* __CONFIRM_PROXY_INFO_H__ */

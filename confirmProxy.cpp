/*
 * confirmProxy.cpp : ソーシャルブックマーク管理プログラム
 *      proxy情報設定確認処理
 *
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/confirmProxy.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 3     07/03/14 20:09 Tsujimura543
 * proxy.txt に書き出すポート番号の値がおかしい不具合を修正
 * 
 * 2     07/03/14 17:38 Tsujimura543
 * checkProxyInfo() を改良
 * 
 * 1     07/03/14 16:22 Tsujimura543
 * (1) 「ブログクライアント BloGolEe」用に書いたソースを取り込む
 * (2) バイリンガル対応
 * =======================================================================
 * 5     07/03/13 19:56 Tsujimura543
 * proxy設定情報を BlogoleeApp 内に保持するようにした
 * 
 * 4     07/03/10 5:22 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応してみた
 * 
 * 3     07/03/09 21:23 Tsujimura543
 * FILE_CONFIG_PROXY を追加
 * 
 * 2     07/03/09 21:21 Tsujimura543
 * checkProxyInfo() を追加
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "ProxyInfoDialog.h"
#include "confirmProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/confirmProxy.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define FILE_CONFIG_PROXY   "./proxy.txt"   // proxyサーバ情報設定ファイル

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword )
{
    int         ret = FALSE;
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
    LCID        l = getLanguageCode();

    int r = MessageBox( NULL,
                        l == 0x0411
                            ? "proxyサーバ経由でインターネットを"
                              "利用していますか?"
                            : "Do you access the Internet via a "
                              "proxy server ?",
                        l == 0x0411
                            ? "インターネット利用形態確認"
                            : "Confirmation of proxy server",
                        MB_YESNO|MB_ICONQUESTION );

    if ( r == IDYES ) {
        CProxyInfoDialog    dlg;
        if ( proxyServer[0] ) {
            dlg.m_proxyServerName = proxyServer;
            dlg.m_proxyPortNumber = *proxyPort;
            if ( proxyUserName[0] ) {
                dlg.m_proxyUserName = proxyUserName;
                if ( proxyPassword[0] )
                    dlg.m_proxyPassword = proxyPassword;
            }
        }
        dlg.DoModal();

        *useProxy = TRUE;
        strcpy( proxyServer, dlg.m_proxyServerName );
        *proxyPort = (unsigned short)(dlg.m_proxyPortNumber);

        bp->m_proxyServer = proxyServer;
        bp->m_proxyPort   = *proxyPort;

        if ( dlg.m_proxyUserName.GetLength() > 0 ) {
            bp->m_proxyUsername = dlg.m_proxyUserName;
            if ( dlg.m_proxyPassword.GetLength() > 0 )
                bp->m_proxyPassword = dlg.m_proxyPassword;
        }

        FILE    *fp;
        if ( ( fp = fopen( FILE_CONFIG_PROXY, "w" ) ) != NULL ) {
            fprintf( fp, "%s\n", proxyServer );
            fprintf( fp, "%d\n", *proxyPort );

            if ( dlg.m_proxyUserName.GetLength() > 0 ) {
                if ( proxyUserName )
                    strcpy( proxyUserName, dlg.m_proxyUserName );
                fprintf( fp, "%s\n", (const char *)dlg.m_proxyUserName );

                if ( dlg.m_proxyPassword.GetLength() > 0 ) {
                    if ( proxyPassword )
                        strcpy( proxyPassword, dlg.m_proxyPassword );
                    fprintf( fp, "%s\n", (const char *)dlg.m_proxyPassword );
                }
            }
            fclose( fp );
        }

        ret = TRUE;
    }
    else {
        *useProxy = FALSE;
        ret = TRUE;
    }

    bp->m_proxyType = CBookeyApp::manualSetting;
    bp->m_useProxy  = *useProxy == TRUE ? true : false;

    return ( ret );
}

bool
checkProxyInfo()
{
    bool    ret = isNecessaryToCheckProxyInfo() ? true : false;

    if ( ret )
        initProxyInfo();

    return ( ret );
}

void
initProxyInfo()
{
    unlink( FILE_CONFIG_PROXY );
}

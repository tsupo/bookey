/*
 * SettingDelicious.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(del.icio.us) インプリメンテーション ファイル
 *          written by H.Tsujimura  28 Jul 2006
 *
 * $Log: /comm/bookey/SettingDelicious.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 7     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 6     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 5     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 4     06/09/29 18:57 Tsujimura543
 * RCS(VSS)の Header 情報を埋め込み忘れていたので、改めて埋め込んでみた
 * 
 * 3     06/07/31 17:14 Tsujimura543
 * ソースの整理 (コメント追加、余分な改行・空白の削除、など)
 * 
 * 2     06/07/31 17:03 Tsujimura543
 * 設定ダイアログを OK ボタン押下で終了すると、それまでにタブをクリックして
 * いなかったブックマークサービスの設定内容が破壊されてしまう不具合に対処
 * 
 * 1     06/07/28 23:00 Tsujimura543
 * 新規作成 (タブ切り替え式の「設定ダイアログ」を作成、導入した)
 */

#include "bookey.h"
#include "SettingDelicious.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingDelicious.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDelicious ダイアログ

SettingDelicious::SettingDelicious(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingDelicious::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDelicious)
	//}}AFX_DATA_INIT
}

void SettingDelicious::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDelicious)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingDelicious::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_delicious.m_username = m_username;
        pp->m_delicious.m_password = m_password;
        pp->m_delicious = m_isTarget;
    }
}

void SettingDelicious::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_delicious.m_username;
        m_password = pp->m_delicious.m_password;
        m_isTarget = (bool)(pp->m_delicious);
    }
}

BEGIN_MESSAGE_MAP(SettingDelicious, CTabDialog)
	//{{AFX_MSG_MAP(SettingDelicious)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
 * SettingPookmark.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(pookmark) インプリメンテーション ファイル
 *          written by H.Tsujimura  4 Oct 2006
 *
 * $Log: /comm/bookey/SettingPookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 5     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 4     07/02/16 16:15 Tsujimura543
 * コメントを修正
 * 
 * 3     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 2     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 1     06/10/04 20:22 Tsujimura543
 * 新規作成 (pookmark 対応)
 */

#include "bookey.h"
#include "SettingPookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingPookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingPookmark ダイアログ

SettingPookmark::SettingPookmark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingPookmark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingPookmark)
	//}}AFX_DATA_INIT
}

void SettingPookmark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingPookmark)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingPookmark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_pookmark.m_username = m_username;
        pp->m_pookmark.m_password = m_password;
        pp->m_pookmark = m_isTarget;
    }
}

void SettingPookmark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_pookmark.m_username;
        m_password = pp->m_pookmark.m_password;
        m_isTarget = (bool)(pp->m_pookmark);
    }
}

BEGIN_MESSAGE_MAP(SettingPookmark, CTabDialog)
	//{{AFX_MSG_MAP(SettingPookmark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

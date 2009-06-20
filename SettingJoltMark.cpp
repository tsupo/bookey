/*
 * SettingJoltMark.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(JoltMark) インプリメンテーション ファイル
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/SettingJoltMark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 6     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 5     07/02/16 13:57 Tsujimura543
 * コメントを修正
 * 
 * 4     07/02/16 9:49 Tsujimura543
 * 「適用」ボタンを押下せずに複数のタブを行ったり来たりすると、以前入力し
 * た内容が消えてしまう(初期状態に戻っている)不具合を修正
 * 
 * 3     07/01/23 22:29 Tsujimura543
 * 余分なコメント(自動生成されたもの、など)を削除
 * 
 * 2     06/12/22 22:12 Tsujimura543
 * 版数管理用文字列を埋め込む
 * 
 * 1     06/12/21 16:37 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "bookey.h"
#include "SettingJoltMark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingJoltMark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingJoltMark ダイアログ

SettingJoltMark::SettingJoltMark(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingJoltMark::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingJoltMark)
	//}}AFX_DATA_INIT
}

void SettingJoltMark::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingJoltMark)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingJoltMark::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_joltMark.m_username = m_username;
        pp->m_joltMark.m_password = m_password;
        pp->m_joltMark = m_isTarget;
    }
}

void SettingJoltMark::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username = pp->m_joltMark.m_username;
        m_password = pp->m_joltMark.m_password;
        m_isTarget = (bool)(pp->m_joltMark);
    }
}

BEGIN_MESSAGE_MAP(SettingJoltMark, CTabDialog)
	//{{AFX_MSG_MAP(SettingJoltMark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
 * ReplaceTagsDialog.cpp : ソーシャルブックマーク管理プログラム
 *      タグ置換ダイアログ インプリメンテーション ファイル
 *          written by H.Tsujimura  24 Jan 2007
 *
 * $Log: /comm/bookey/ReplaceTagsDialog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 7     08/07/25 18:44 Tsujimura543
 * Diigo 対応準備
 * 
 * 6     07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 5     07/01/30 21:36 Tsujimura543
 * OnReplaceTags() 内で表示する文言の ID 指定が間違っていたのを修正
 * 
 * 4     07/01/30 0:57 Tsujimura543
 * 英語モード対応
 * 
 * 3     07/01/29 22:01 Tsujimura543
 * ユーザインターフェースのロジック部分、フィックス
 * 
 * 2     07/01/29 18:04 Tsujimura543
 * ユーザインターフェースの細部を詰める必要が残っているが、とりあえず、
 * 使えるものが完成
 * 
 * 1     07/01/24 21:01 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "bookey.h"
#include "ReplaceTagsDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/ReplaceTagsDialog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceTagsDialog ダイアログ

CReplaceTagsDialog::CReplaceTagsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceTagsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplaceTagsDialog)
	m_newTag = _T("");
	m_oldTag = _T("");
	m_bookmarkName = _T("");
	//}}AFX_DATA_INIT

    m_numOfTags = 0;
    m_tagIndex  = -1;

    m_tgt_hatenaBookmark.LoadString( IDS_TGT_HATENA_BOOKMARK );
    m_tgt_delicious.LoadString( IDS_TGT_DELICIOUS );
    m_tgt_mmMemo.LoadString( IDS_TGT_MMMEMO );
    m_tgt_drecomRSS.LoadString( IDS_TGT_DRECOM_RSS );
    m_tgt_flog.LoadString( IDS_TGT_FLOG );
    m_tgt_livedoorClip.LoadString( IDS_TGT_LIVEDOOR_CLIP );
    m_tgt_ecNaviClip.LoadString( IDS_TGT_ECNAVI_CLIP );
    m_tgt_niftyClip.LoadString( IDS_TGT_NIFTY_CLIP );
    m_tgt_1470net.LoadString( IDS_TGT_1470NET );
    m_tgt_pookmark.LoadString( IDS_TGT_POOKMARK );
    m_tgt_blueDot.LoadString( IDS_TGT_BLUEDOT );
    m_tgt_joltMark.LoadString( IDS_TGT_JOLTMARK );
    m_tgt_blogPet.LoadString( IDS_TGT_BLOGPET );
    m_tgt_fc2Bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
    m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
    m_tgt_localOPML.LoadString( IDS_TGT_LOCAL_OPML );
}

void CReplaceTagsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceTagsDialog)
	DDX_Control(pDX, IDC_COMBO_DELETELIST_TAGS, m_bookmarkList);
	DDX_Control(pDX, IDC_COMBO_DELETE_TAGLIST, m_tagList);
	DDX_Text(pDX, IDC_EDIT_NEW_TAG, m_newTag);
	DDV_MaxChars(pDX, m_newTag, 512);
	DDX_CBString(pDX, IDC_COMBO_DELETE_TAGLIST, m_oldTag);
	DDV_MaxChars(pDX, m_oldTag, 512);
	DDX_CBString(pDX, IDC_COMBO_DELETELIST_TAGS, m_bookmarkName);
	DDV_MaxChars(pDX, m_bookmarkName, 96);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReplaceTagsDialog, CDialog)
	//{{AFX_MSG_MAP(CReplaceTagsDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET_TAGS, OnButtonGetTags)
	ON_BN_CLICKED(IDOK, OnReplaceTags)
	ON_CBN_SELCHANGE(IDC_COMBO_DELETE_TAGLIST, OnSelchangeComboDeleteTaglist)
	ON_CBN_SELCHANGE(IDC_COMBO_DELETELIST_TAGS, OnSelchangeComboDeletelistTags)
	ON_WM_SHOWWINDOW()
	ON_EN_KILLFOCUS(IDC_EDIT_NEW_TAG, OnKillfocusEditNewTag)
	ON_EN_UPDATE(IDC_EDIT_NEW_TAG, OnUpdateEditNewTag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplaceTagsDialog メッセージ ハンドラ

void CReplaceTagsDialog::OnButtonGetTags() 
{
    if ( m_targetBookmark != CUserInfo::BK_UNKNOWN ) {
        // タグの一覧を取得
        CWaitCursor         cur;    // マウスカーソルを砂時計表示
        ProceedingDialog    dlg;

        CString title;
        CString text;

        title.LoadString(IDS_TTL_CONTINUE_GET_TAG_LIST);
        text.LoadString( IDS_TXT_CONTINUE_GET_TAG_LIST);

        dlg.Create( IDD_PROCEEDING_DIALOG );
        dlg.ChangeDialogText( title,    // タグ一覧取得
                              text );   // タグ一覧取得中……

        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        TagList     *p  = pp->GetTagList( m_targetBookmark, m_numOfTags );

        if ( p && (m_numOfTags > 0) ) {
            // タグの一覧を選択肢として登録
            if ( m_tagList.GetCount() > 0 )
                m_tagList.ResetContent();
            m_tagList.InitStorage( m_numOfTags,
                                   BUFSIZ * m_numOfTags );

            int     i;
            char    *q;
            TagList *qq = p;
            for ( i = 0; i < m_numOfTags; i++, qq++ ) {
                q = utf2sjisEx( qq->tag );
                m_tagList.AddString( q ? q : qq->tag );
            }
        }

        if ( p )
            free( p );
    }
}

void CReplaceTagsDialog::OnReplaceTags() 
{
    if ( (m_targetBookmark != CUserInfo::BK_UNKNOWN) &&
         (m_oldTag.GetLength() > 0)                  &&
         (m_newTag.GetLength() > 0)                     ) {
        CWaitCursor         cur;    // マウスカーソルを砂時計表示
        ProceedingDialog    dlg;

        CString title;
        CString text;

        title.LoadString(IDS_TTL_CONTINUE_REPLACE_TAGS);
        text.LoadString( IDS_TXT_CONTINUE_REPLACE_TAGS);

        dlg.Create( IDD_PROCEEDING_DIALOG );
        dlg.ChangeDialogText( title,    // 指定されたタグの置換
                              text );   // 指定されたタグの置換中……

        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        pp->ReplaceTag( m_targetBookmark, m_oldTag, m_newTag );

        m_tagList.DeleteString( m_tagIndex );
        m_numOfTags--;
        if ( m_numOfTags <= 0 ) {
            m_targetBookmark = CUserInfo::BK_UNKNOWN;
            m_tagList.ResetContent();
        }
        m_oldTag   = "";
        m_newTag   = "";
        m_tagIndex = -1;

        CButton *p = (CButton *)GetDlgItem( IDOK );
        p->EnableWindow( FALSE );

        if ( pp->m_langCode == 0x0411 ) {
            p = (CButton *)GetDlgItem( IDCANCEL );
            p->SetWindowText( "終了" );
        }

        CEdit   *q = (CEdit *)GetDlgItem( IDC_EDIT_NEW_TAG );
        q->SetWindowText( m_newTag );
    }
}

void CReplaceTagsDialog::OnSelchangeComboDeleteTaglist() 
{
    int     location = m_tagList.GetCurSel();

    CButton *p = (CButton *)GetDlgItem( IDOK );
    if ( location == LB_ERR ) {
        p->EnableWindow( FALSE );
        return;
    }

	m_tagList.GetLBText( location, m_oldTag );
    m_tagIndex = location;
}

void CReplaceTagsDialog::OnSelchangeComboDeletelistTags() 
{
    int     location = m_bookmarkList.GetCurSel();
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET_TAGS );

    if ( location == LB_ERR ) {
        p->EnableWindow( FALSE );
        return;
    }

    CString bookmarkName = m_bookmarkName;

	m_bookmarkList.GetLBText( location, m_bookmarkName );
    if ( m_bookmarkName.Compare( bookmarkName ) == 0 )
        return; // 変化なし

    m_targetBookmark = CUserInfo::BK_UNKNOWN;

    if ( m_tagList.GetCount() > 0 ) {
        m_numOfTags = 0;
        m_tagList.ResetContent();

        CButton *q = (CButton *)GetDlgItem( IDOK );
        q->EnableWindow( FALSE );
    }

    if ( m_bookmarkName.Compare( m_tgt_hatenaBookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_HATENA;
    else
    if ( m_bookmarkName.Compare( m_tgt_delicious ) == 0 )
        m_targetBookmark = CUserInfo::BK_DELICIOUS;
    else
    if ( m_bookmarkName.Compare( m_tgt_mmMemo ) == 0 )
        m_targetBookmark = CUserInfo::BK_MM_MEMO;
    else
    if ( m_bookmarkName.Compare( m_tgt_drecomRSS ) == 0 )
        m_targetBookmark = CUserInfo::BK_DRECOM_RSS;
    else
    if ( m_bookmarkName.Compare( m_tgt_flog ) == 0 )
        m_targetBookmark = CUserInfo::BK_FLOG;
    else
    if ( m_bookmarkName.Compare( m_tgt_livedoorClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_LIVEDOOR_CLIP;
    else
    if ( m_bookmarkName.Compare( m_tgt_ecNaviClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_ECNAVI_CLIP;
    else
    if ( m_bookmarkName.Compare( m_tgt_niftyClip ) == 0 )
        m_targetBookmark = CUserInfo::BK_NIFTY_CLIP;
    else
    if ( m_bookmarkName.Compare( m_tgt_1470net ) == 0 )
        m_targetBookmark = CUserInfo::BK_1470NET;
    else
    if ( m_bookmarkName.Compare( m_tgt_pookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_POOKMARK;
    else
    if ( m_bookmarkName.Compare( m_tgt_blueDot ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLUEDOT;
    else
    if ( m_bookmarkName.Compare( m_tgt_joltMark ) == 0 )
        m_targetBookmark = CUserInfo::BK_JOLTMARK;
    else
    if ( m_bookmarkName.Compare( m_tgt_blogPet ) == 0 )
        m_targetBookmark = CUserInfo::BK_BLOGPET;
    else
    if ( m_bookmarkName.Compare( m_tgt_fc2Bookmark ) == 0 )
        m_targetBookmark = CUserInfo::BK_FC2BOOKMARK;
    else
    if ( m_bookmarkName.Compare( m_tgt_diigo ) == 0 )
        m_targetBookmark = CUserInfo::BK_DIIGO;
    else
    if ( m_bookmarkName.Compare( m_tgt_localOPML ) == 0 )
        m_targetBookmark = CUserInfo::BK_LOCAL_OPML;

    p->EnableWindow( TRUE );
}

void CReplaceTagsDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_GET_TAGS );
        p->EnableWindow( FALSE );

        p = (CButton *)GetDlgItem( IDOK );
        p->EnableWindow( FALSE );
    }
}

void CReplaceTagsDialog::OnKillfocusEditNewTag() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_NEW_TAG );
    p->GetWindowText( m_newTag );

    CButton *q = (CButton *)GetDlgItem( IDOK );
    q->EnableWindow( m_newTag.GetLength() > 0 ? TRUE : FALSE );
}

void CReplaceTagsDialog::OnUpdateEditNewTag() 
{
    OnKillfocusEditNewTag();
}

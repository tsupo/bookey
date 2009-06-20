/*
 * SettingTwitter.cpp : ソーシャルブックマーク管理プログラム
 *      設定ダイアログ(Twitter) インプリメンテーション ファイル
 *          written by H.Tsujimura  10 Apr 2007
 *
 * $Log: /comm/bookey/SettingTwitter.cpp $
 * 
 * 2     09/06/18 0:53 tsupo
 * 0.63b版
 * 
 * 5     09/06/11 17:50 Tsujimura543
 * Twitter の OAuth が 1.0 から 1.0a へ移行したのに伴う修正
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     09/04/01 22:24 Tsujimura543
 * OAuth 関連部分のバイリンガル対応
 * 
 * 3     09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 2     07/06/08 22:18 Tsujimura543
 * CTabDialog クラスを導入し、各タブの共通処理を集約した
 * 
 * 1     07/04/10 18:46 Tsujimura543
 * 新規作成
 */

#include "bookey.h"
#include "SettingTwitter.h"
#include "InputPinDialog.h"

#ifdef __cplusplus
extern "C" {
#endif
char    *TwitterOAuthConsumerKey();
char    *TwitterOAuthConsumerSecret();

void    makeOAuthRequest(
                const char *url,
                char       *request,
                char       *key,
                char       *base,
                char       *param
            );

#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/SettingTwitter.cpp 2     09/06/18 0:53 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingTwitter ダイアログ

SettingTwitter::SettingTwitter(CWnd* pParent /*=NULL*/)
	: CTabDialog(SettingTwitter::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingTwitter)
	//}}AFX_DATA_INIT

    m_auth = AK_ORIGINAL;
    m_oauthToken       = _T("");
    m_oauthTokenSecret = _T("");
}

void SettingTwitter::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingTwitter)
	//}}AFX_DATA_MAP
}

// 「設定ダイアログ」での「適用」ボタン押下時処理
void SettingTwitter::Accept()
{
    if ( m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        pp->m_twitter.m_username = m_username;
        pp->m_twitter.m_password = m_password;

        pp->m_twitter.SetAuthType( m_auth );
        pp->m_twitter.m_apiKey   = m_oauthToken;
        pp->m_twitter.m_secret   = m_oauthTokenSecret;

        pp->m_twitter            = m_isTarget;
    }
}

void SettingTwitter::LoadSetting()
{
    if ( !m_initialized ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        m_username         = pp->m_twitter.m_username;
        m_password         = pp->m_twitter.m_password;

        m_oauthToken       = pp->m_twitter.m_apiKey;
        m_oauthTokenSecret = pp->m_twitter.m_secret;
        m_auth             = pp->m_twitter.GetAuthType();

        m_isTarget         = (bool)(pp->m_twitter);
    }
}

void SettingTwitter::ShowCurrentStatus()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_RADIO_OAUTH );
    bp->SetCheck( m_auth == AK_ORIGINAL ? 0 : 1 );

    bp = (CButton *)GetDlgItem( IDC_RADIO_BASIC );
    bp->SetCheck( m_auth == AK_ORIGINAL ? 1 : 0 );

    bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_TOKEN );
    bp->EnableWindow( m_auth == AK_OAUTH );

    CString status;
    CStatic *sp = (CStatic *)GetDlgItem( IDC_TOKEN_STATUS );
    if ( (m_oauthToken.GetLength()       > 0) &&
         (m_oauthTokenSecret.GetLength() > 0)    )
	    status.LoadString( IDS_ACCESSTOKEN_ACQUIRED );
    else
	    status.LoadString( IDS_ACCESSTOKEN_UNTAKEN );
    sp->SetWindowText( status );

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
    p->SetWindowText( m_username );
    p->EnableWindow( m_auth == AK_ORIGINAL );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
    p->SetWindowText( m_password );
    p->EnableWindow( m_auth == AK_ORIGINAL );
}

BEGIN_MESSAGE_MAP(SettingTwitter, CTabDialog)
	//{{AFX_MSG_MAP(SettingTwitter)
	ON_BN_CLICKED(IDC_BUTTON_GET_TOKEN, OnButtonGetToken)
	ON_BN_CLICKED(IDC_RADIO_OAUTH, OnRadioOauth)
	ON_BN_CLICKED(IDC_RADIO_BASIC, OnRadioBasic)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingTwitter メッセージ ハンドラ

void SettingTwitter::OnButtonGetToken() 
{
    CWaitCursor cur;    // マウスカーソルを砂時計表示

    // アクセストークンの取得
    GetAccessToken( TwitterOAuthConsumerKey(),
                    TwitterOAuthConsumerSecret() );
    ShowCurrentStatus();
}

void SettingTwitter::OnRadioOauth() 
{
    m_auth = AK_OAUTH;
    ShowCurrentStatus();
}

void SettingTwitter::OnRadioBasic() 
{
    m_auth = AK_ORIGINAL;
    ShowCurrentStatus();
}

void SettingTwitter::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTabDialog::OnShowWindow(bShow, nStatus);

    if ( bShow )
        ShowCurrentStatus();
}

/////////////////////////////////////////////////////////////////////////////
// SettingTwitter 追加メソッド

bool
SettingTwitter::GetToken(
        const char *response,
        CString    &oauthToken,
        CString    &oauthTokenSecret
    )
{
    bool    ret = false;

    if ( response && *response ) {
        char    oauth_token[BUFSIZ];
        char    oauth_token_secret[BUFSIZ];

        char    *p = strstr( response, "oauth_token=" );
        if ( p ) {
            p += 12;

            char    *q = strchr( p, '&' );
            if ( q ) {
                strncpy( oauth_token, p, q - p );
                oauth_token[q - p] = NUL;
            }
            else {
                strcpy( oauth_token, p );
            }

            oauthToken = oauth_token;
        }

        p = strstr( response, "oauth_token_secret=" );
        if ( p ) {
            p += 19;

            char    *q = strchr( p, '&' );
            if ( q ) {
                strncpy( oauth_token_secret, p, q - p );
                oauth_token_secret[q - p] = NUL;
            }
            else {
                strcpy( oauth_token_secret, p );
            }

            oauthTokenSecret = oauth_token_secret;
        }

        if ( (oauthToken.GetLength()       > 0) &&
             (oauthTokenSecret.GetLength() > 0)    )
            ret = true;
    }

    return ( ret );
}

bool
SettingTwitter::GetRequestToken(
        const char *consumerKey,
        const char *consumerSecret,
        CString    &oauthToken,
        CString    &oauthTokenSecret
    )
{
    bool    ret = false;

    time_t  t  = time( NULL );
    size_t  sz = MAX_CONTENT_SIZE * 16;
    char    base[MAX_CONTENT_SIZE];
    char    param[MAX_CONTENT_SIZE];
    char    nonce[MAX_KEYLENGTH];
    char    key[MAX_KEYLENGTH * 2];

    char    *request  = new char[sz];
    char    *response = new char[sz];

    CString targetURL = _T("");
    targetURL.LoadString(IDS_URL_TWITTER_REQUEST_TOKEN);

    strcpy( nonce, getNonce(NULL) );

    sprintf( key, "%s&", encodeURLi( consumerSecret, FALSE ) );

    sprintf( base,
             "GET&"
             "%s&",
             encodeURLi( targetURL, FALSE ) );
    sprintf( param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_version=1.0",
             consumerKey,
             nonce,
             t );

    makeOAuthRequest( targetURL, request, key, base, param );

    setUpReceiveBuffer( response, sz );
    http_get( request, response );
    ret = GetToken( response, oauthToken, oauthTokenSecret );

    delete [] response;
    delete [] request;

    return ( ret );
}

bool
SettingTwitter::GetAccessToken(
        const char *consumerKey,
        const char *consumerSecret
    )
{
    bool    ret = false;

    if ( !consumerKey    || !(*consumerKey)    ||
         !consumerSecret || !(*consumerSecret)    )
        return ( ret );

    // request token 取得
    CString _oauthToken       = _T("");
    CString _oauthTokenSecret = _T("");
    if ( !GetRequestToken( consumerKey, consumerSecret,
                           _oauthToken, _oauthTokenSecret ) )
        return ( ret );

    // ブラウザ起動 -- ユーザにアクセス許可を求める
    CString targetURL = _T("");
    targetURL.LoadString(IDS_URL_TWITTER_AUTHORIZE);

    char    url[MAX_URLLENGTH];
    sprintf( url, "%s?oauth_token=%s", targetURL, _oauthToken );
    ShellExecute( NULL, "open", url, NULL, NULL, SW_SHOWNORMAL );

    // ユーザの許可待ち
#ifdef  BEFORE_20090610
    // OAuth 1.0
    CString ttl = _T("");
    CString msg = _T("");

    ttl.LoadString(IDS_TWITTER_ALLOW_OAUTH);
    msg.LoadString(IDS_TXT_TWITTER_ALLOW_OAUTH);
    int r = MessageBox( msg, ttl, MB_OKCANCEL|MB_ICONINFORMATION );
    if ( r != IDOK ) {
        ttl.LoadString(IDS_TWITTER_STOP_OAUTH);
        msg.LoadString(IDS_TXT_TWITTER_STOP_OAUTH);
        MessageBox( msg, ttl, MB_OK|MB_ICONWARNING );
        return ( ret );
    }
#else   /* !BEFORE_20090610 */
    // OAuth 1.0a
    InputPinDialog  dlg;

    int r = dlg.DoModal();
    if ( (r != IDOK) || (dlg.m_pin.GetLength() < 6) )
        return ( ret );
#endif  /* !BEFORE_20090610 */

    // access token 取得
    time_t  t  = time( NULL );
    size_t  sz = MAX_CONTENT_SIZE * 16;
    char    base[MAX_CONTENT_SIZE];
    char    param[MAX_CONTENT_SIZE];
    char    nonce[MAX_KEYLENGTH];
    char    key[MAX_KEYLENGTH * 2];

    char    *request  = new char[sz];
    char    *response = new char[sz];

    targetURL = _T("");
    targetURL.LoadString(IDS_URL_TWITTER_ACCESS_TOKEN);

    strcpy( nonce, getNonce(NULL) );

    sprintf( key,
             "%s&",
             encodeURLi( consumerSecret, FALSE ) );
    sprintf( key + strlen(key),
             "%s",
             encodeURLi( _oauthTokenSecret, FALSE ) );

    sprintf( base,
             "GET&"
             "%s&",
             encodeURLi( targetURL, FALSE ) );

#ifdef  BEFORE_20090610
    // OAuth 1.0
    sprintf( param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_version=1.0",
             consumerKey,
             nonce,
             t,
             _oauthToken );
#else   /* !BEFORE_20090610 */
    // OAuth 1.0a
    sprintf( param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_verifier=%s&"
             "oauth_version=1.0",
             consumerKey,
             nonce,
             t,
             _oauthToken,
             (const char *)dlg.m_pin );
#endif  /* !BEFORE_20090610 */

    makeOAuthRequest( targetURL, request, key, base, param );

    setUpReceiveBuffer( response, sz );
    http_get( request, response );
    ret = GetToken( response, m_oauthToken, m_oauthTokenSecret );

    delete [] response;
    delete [] request;

    return ( ret );
}

/*
 *  bbAuth.c
 *      Yahoo! Japan �� BBAuth �ɂ��F�؂����s����
 *
 *          written by H.Tsujimura  14 Sep 2007 / 24 Oct 2007
 *
 * $Log: /comm/bookey/bbAuth.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 14    08/12/02 19:25 Tsujimura543
 * (1) �Ӗ��̂Ȃ������̍폜
 * (2) ����������Y��Ώ�
 * 
 * 13    07/12/06 5:09 Tsujimura543
 * �R���p�C������ wininet.h ���ŏo�� warning C4201 ��}������悤�ɂ���
 * 
 * 12    07/11/05 20:49 Tsujimura543
 * �l�q���o�[�W����
 * 
 * 11    07/10/13 3:30 Tsujimura543
 * Buzzurl �ւ̃A�N�Z�X�� newsing �ւ̃A�N�Z�X��A���ōs�Ȃ����Ƃ���ƁA
 * newsing �ւ̃A�N�Z�X���ɉ��X�Ɓu�p�X���[�h�̍Ċm�F�v���o�����錻��
 * ����B���҂̃A�N�Z�X�̊Ԃɂ�����x���Ԃ�u���΂Ƃ肠�������v�B
 * �������܂��΍�͂Ȃ����͍����B
 * 
 * 10    07/10/13 2:45 Tsujimura543
 * Buzzurl, newsing ����̃��O�A�E�g��A�N�b�L�[���폜����悤�ɂ���
 * 
 * 9     07/10/13 2:39 Tsujimura543
 * �f�o�b�O�p�̃R�[�h�𐮗�
 * 
 * 8     07/10/13 2:35 Tsujimura543
 * newsing �� BBAuth�o�R�Ń��O�C���ł���悤�ɂȂ���(����m�F�ς�)
 * [���ƂŃ��t�@�N�^�����O����]
 * 
 * 7     07/10/10 17:49 Tsujimura543
 * (1) doYahooStep1() ���̃��O�A�E�g�ɂ�郊�J�o��������p�~
 * (2) ����� _loginEcNaviOnBBAuth() ���Ƀ��O�A�E�g�����݂鏈����}��
 * 
 * 6     07/10/10 1:58 Tsujimura543
 * _loginEcNaviOnBBAuth() ���C�� (�C�����Y��Ă����Ƃ��낪������)
 * 
 * 5     07/10/10 1:55 Tsujimura543
 * (1) �f�o�b�O���o�͏�����ǉ�
 * (2) _loginEcNaviOnBBAuth() ���C���Acookie ���L���ȏꍇ�͍ė��p����悤
 *     �ɂ���
 * (3) doYahooStep1() ���̃��J�o���������C���AYahoo! �ȊO�ɁA�^�[�Q�b�g��
 *     ��������������񃍃O�A�E�g����悤�ɂ���
 * 
 * 4     07/10/05 23:08 Tsujimura543
 * ���g���C����(+ ���J�o������)������
 * 
 * 3     07/10/05 15:19 Tsujimura543
 * ������A������ BBAuth �o�R�Ń��O�C�����悤�Ƃ���ƁA���O�C���Ɏ��s����
 * ���Ƃ����邱�Ƃ������BdoYahooStep1() ���C�����邱�ƂőΏ�����
 * 
 * 2     07/10/05 4:39 Tsujimura543
 * InternetConnect() �� proxy ���[�U���E�p�X���[�h ��n���������C��
 * 
 * 1     07/10/05 2:38 Tsujimura543
 * �F�؂ɐ������邱�Ƃ��m�F
 */

#include "xmlRPC.h"
#include "MD5.h"
#pragma warning ( disable : 4201 )
#include <wininet.h>
#pragma warning ( default : 4201 )
#ifdef  _DEBUG_BBAUTH
#include <time.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bbAuth.c 1     09/05/14 3:48 tsupo $";
#endif


struct proxyInfo    {
    int             useProxy;
    char            proxyServer[MAX_SERVERNAME];
    unsigned short  proxyPort;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];
}   proxyInfoForBBAuth;


char *
ToLower( char *p )
{
    char    *s = p;
    while ( *s ) {
        if ( (*s >= 'A') && (*s <= 'Z') )
            *s = (char)((*s - 'A') + 'a');
        s++;
    }

    return ( p );
}

BOOL
parseURL(
        const char *address,
        char       *host,
        char       *webPage,
        BOOL       *useHttps
    )
{
    BOOL        ret = FALSE;
    const char  *p, *q;

    if ( !strncmp( address, "https://", 8 ) )
        *useHttps = TRUE;
    p = strstr( address, "://" );
    if ( !p )
        return ( ret );

    p += 3;
    q = strchr( p, '/' );
    if ( !q ) {
        strcpy( host, address );
        strcpy( webPage, "/" );
    }
    else {
        strncpy( host, p, q - address );
        host[q - p] = NUL;
        if ( *(q + 1) )
            strcpy( webPage, q + 1 );
        else
            strcpy( webPage, "/" );
    }

    ret = TRUE;
    return ( ret );
}


#ifdef  _DEBUG
void
dump( char *buffer, size_t sz )
{
    unsigned int    i, c;
    unsigned char   buf[80];

    dputs( ">>|\n" );
    for ( i = 0; i < sz; i++ ) {
        if ( (i != 0) && (i % 16 == 0) ) {
            buf[16] = NUL;
            dprintf( "    %s\n", buf );
        }
        if ( i % 16 == 0 )
            dprintf( "%08x:", &buffer[i] );
        c = buffer[i] & 0xFF;
        if ( (c >= ' ') && (c <= 0x7E) )
            buf[i % 16] = (unsigned char)c;
        else
            buf[i % 16] = '.';
        dprintf( " %02x", c & 0xFF );
    }
    if ( i % 16 == 0 )
        buf[16] = NUL;
    else {
        buf[i % 16] = NUL;
        for ( i = i % 16; i < 16; i++ )
            dputs( "   " );
    }
    dprintf( "    %s\n|<<\n\n", buf );
}
#endif  /* _DEBUG */


void
_openConnectionIC(
        HINTERNET  *hInet,
        HINTERNET  *hConn,
        const char *host,
        BOOL       useHttps
    )
{
    char    proxyServer[MAX_SERVERNAME + MAX_KEYLENGTH];

    proxyServer[0] = NUL;
    if ( proxyInfoForBBAuth.useProxy )
        sprintf( proxyServer, "%s:%d",
                 proxyInfoForBBAuth.proxyServer,
                 proxyInfoForBBAuth.proxyPort );

    *hInet = InternetOpen( 
             // "httpAuth/1.0 (written by H.Tsujimura)", /* �� Buzzurl �͂���ł� OK */
                "Mozilla/4.0 (compatible; MSIE 6.0)",    /* �� newsing �͂���������Ȃ��ƒʂ�Ȃ� */
                proxyInfoForBBAuth.useProxy ? INTERNET_OPEN_TYPE_PROXY
                                            : INTERNET_OPEN_TYPE_PRECONFIG,
                proxyInfoForBBAuth.useProxy ? proxyServer
                                            : NULL,
                proxyInfoForBBAuth.useProxy ? "<local>"
                                            : NULL,
                0 );
    if ( *hInet == NULL )
        return;

    *hConn = InternetConnect(
                *hInet,
                host,
                (INTERNET_PORT)
                    (useHttps ? INTERNET_DEFAULT_HTTPS_PORT
                              : INTERNET_DEFAULT_HTTP_PORT),
                proxyInfoForBBAuth.useProxy &&
                proxyInfoForBBAuth.proxyUserName[0]
                                            ? proxyInfoForBBAuth.proxyUserName
                                            : NULL,
                proxyInfoForBBAuth.useProxy &&
                proxyInfoForBBAuth.proxyPassword[0]
                                            ? proxyInfoForBBAuth.proxyPassword
                                            : NULL,
                INTERNET_SERVICE_HTTP,
                0, 0 );
    if ( *hConn == NULL ) {
        dputs( "_openConnectionIC(): ���s\n" );
        InternetCloseHandle( *hInet );
        *hInet = NULL;
    }
}

void
_closeConnectionIC(
        HINTERNET hInet,
        HINTERNET hConn
    )
{
    if ( hConn )
        InternetCloseHandle( hConn );
    if ( hInet )
        InternetCloseHandle( hInet );
}


char    *
_httpGetIC(
        const char *address,
        char       *buffer,
        BOOL       withHeader,
        BOOL       escapeURL
    )
{
    HINTERNET   hInet;
    HINTERNET   hConn;
    HINTERNET   hReq;
    char        szBuf[BUFSIZ * 2 + 1];
    DWORD       dwSize;
    DWORD       dwIndex;
    BOOL        bret;
    char        host[MAX_PATH];
    char        webPage[MAX_WEBPAGENAME];
    BOOL        useHttps = FALSE;
    char        *tail = buffer;

    if ( escapeURL == FALSE ) {
        // newsing �΍�
        char    *p;
        char    *q;

        p = strstr( address, "&done=http%3A%2F%2F" );
        if ( p ) {
            while ( (q = strstr( p, "%3A" )) != NULL ) {
                *q = ':';
                strcpy( q + 1, q + 3 );
            }
            while ( (q = strstr( p, "%2F" )) != NULL ) {
                *q = '/';
                strcpy( q + 1, q + 3 );
            }
        }
    }

    *buffer  = NUL;
    *webPage = NUL;
    parseURL( address, host, webPage, &useHttps );
    if ( !webPage )
        return ( buffer );

    _openConnectionIC( &hInet, &hConn, host, useHttps );
    if ( !hInet || !hConn )
        return ( buffer );

    // GET �Ώۂ� URL ��ݒ�
    hReq = HttpOpenRequest(
                hConn,
                "GET",
                webPage,
                NULL, NULL, NULL,
                useHttps ? INTERNET_FLAG_SECURE : 0,
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS  );
    if ( hReq == NULL ) {
        dputs( "HttpOpenRequest(): ���s\n" );
        _closeConnectionIC( hInet, hConn );
        return ( buffer );
    }
    dprintf( "_httpGetIC(): GET %s\n", address );

    // GET ���N�G�X�g�𑗐M
    if( HttpSendRequest( hReq, NULL, 0, NULL, 0 ) != TRUE ) {
        DWORD   err = GetLastError();

        // HttpOpenRequest() ��
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS
        // ��ݒ肵�Ă���̂ɁA�Ȃ����G���[���������邱�Ƃ�����

        if ( (err != ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR) &&
             (err != ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR)    ) {
            MessageBox( NULL,
                        "http���N�G�X�g�̑��M�����ŃG���[���������܂���  ",
                        "http GET ���\�b�h", MB_ICONHAND|MB_OK );
            InternetCloseHandle( hReq );
            _closeConnectionIC( hInet, hConn );
            return ( buffer );
        }

        // http �X�e�[�^�X�R�[�h�̒l�ɑΉ������n�������s
        dwIndex = 0;
        dwSize  = sizeof( szBuf ) - 1;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = HttpQueryInfo( hReq, 
                              HTTP_QUERY_STATUS_CODE,
                              szBuf, &dwSize, &dwIndex );
        if ( bret == TRUE ) {
            int statusCode = atol( szBuf );
            switch ( statusCode ) {
            case 301:
            case 302:
                dwSize = sizeof( szBuf ) - 1;
                memset( szBuf, 0x00, sizeof( szBuf ) );
                bret = HttpQueryInfo( hReq, 
                                      HTTP_QUERY_LOCATION,
                                      szBuf, &dwSize, &dwIndex );
                if ( bret == TRUE ) {
                    InternetCloseHandle( hReq );
                    _closeConnectionIC( hInet, hConn );

                    // ���_�C���N�g�����s
                    dprintf( "_httpGetIC(): %s �փ��_�C���N�g\n", szBuf );
                    _httpGetIC( szBuf, buffer, FALSE, escapeURL );
                    return ( buffer );
                }
                break;
            }
        }
    }

    // ���X�|���X�w�b�_����M
    bret    = TRUE;
    dwIndex = 0;
    while ( bret == TRUE ) {
        dwSize = sizeof( szBuf ) - 1;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = HttpQueryInfo( hReq, 
                              HTTP_QUERY_RAW_HEADERS_CRLF |
                              HTTP_QUERY_FLAG_NUMBER,
                              szBuf, &dwSize, &dwIndex );
        dwIndex++;
        if ( bret ) {
            if ( withHeader ) {
                memcpy( tail, szBuf, dwSize + 1 );
                tail += dwSize;
            }
#ifdef  _DEBUG
            dump( szBuf, dwSize );
#endif
        }
    }

    // ���X�|���X�{�̂���M
    bret = TRUE;
    while ( bret == TRUE ) {
        dwSize = 0;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = InternetReadFile( hReq,
                                 szBuf, sizeof( szBuf ) - 1, &dwSize );
        if ( bret ) {
            memcpy( tail, szBuf, dwSize );
            tail += dwSize;
        }
        if ( dwSize == 0 ) {
            if ( szBuf[0] ) {
                strcpy( tail, szBuf );
                tail += strlen( szBuf );
            }
            else
                *tail = NUL;
#ifdef  _DEBUG
            dump( buffer, tail - buffer );
#endif
            break;
        }
    }

    InternetCloseHandle( hReq );
    _closeConnectionIC( hInet, hConn );

#ifdef  _DEBUG_BBAUTH
    {
        FILE    *fp;
        char    filename[MAX_PATH];

        sprintf( filename, "./Debug/bbAuth_%d.html", time( NULL ) );
        fp = fopen( filename, "w" );
        if ( fp ) {
            fprintf( fp, "GET %s\n\n", address );
            fputs( buffer, fp );
            fclose( fp );
        }
    }
#endif

    return ( buffer );
}


char    *
_httpPostIC(
        const char *address,
        const char *request,
        char       *buffer,
        BOOL       escapeURL
    )
{
    HINTERNET   hInet;
    HINTERNET   hConn;
    HINTERNET   hReq;
    char        szBuf[BUFSIZ * 2 + 1];
    DWORD       dwSize;
    DWORD       dwIndex;
    BOOL        bret;
    char        host[MAX_PATH];
    char        webPage[MAX_WEBPAGENAME];
    BOOL        useHttps = FALSE;
    char        *tail = buffer;
    const char  *contentType =
                    "Content-Type: application/x-www-form-urlencoded";

    *buffer  = NUL;
    *webPage = NUL;
    parseURL( address, host, webPage, &useHttps );
    if ( !webPage )
        return ( buffer );

    _openConnectionIC( &hInet, &hConn, host, useHttps );
    if ( !hInet || !hConn )
        return ( buffer );

    hReq = HttpOpenRequest(
                hConn,
                "POST",
                webPage,
                NULL, NULL, NULL,
                useHttps ? INTERNET_FLAG_SECURE : 0,
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
                SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS  );
    if ( hReq == NULL ) {
        dputs( "HttpOpenRequest(): ���s\n" );
        _closeConnectionIC( hInet, hConn );
        return ( buffer );
    }
    dprintf( "_httpPostIC(): POST %s\n>>\n%s\n<<\n", address, request );

    // request�𑗐M����
    bret = HttpSendRequest( hReq,
                            contentType, strlen(contentType),
                            (void *)request, strlen(request) );
    if( bret != TRUE ) {
        DWORD   err = GetLastError();

        // HttpOpenRequest() ��
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP |
        //     SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS
        // ��ݒ肵�Ă���̂ɁA�Ȃ����G���[���������邱�Ƃ�����

        if ( (err != ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR) &&
             (err != ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR)    ) {
            MessageBox( NULL,
                        "http���N�G�X�g�̑��M�����ŃG���[���������܂���  ",
                        "http POST ���\�b�h", MB_ICONHAND|MB_OK );
            InternetCloseHandle( hReq );
            _closeConnectionIC( hInet, hConn );
            return ( buffer );
        }

        // http �X�e�[�^�X�R�[�h�̒l�ɑΉ������n�������s
        dwIndex = 0;
        dwSize  = sizeof( szBuf ) - 1;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = HttpQueryInfo( hReq, 
                              HTTP_QUERY_STATUS_CODE,
                              szBuf, &dwSize, &dwIndex );
        if ( bret == TRUE ) {
            int statusCode = atol( szBuf );
            switch ( statusCode ) {
            case 301:
            case 302:
                dwSize = sizeof( szBuf ) - 1;
                memset( szBuf, 0x00, sizeof( szBuf ) );
                bret = HttpQueryInfo( hReq, 
                                      HTTP_QUERY_LOCATION,
                                      szBuf, &dwSize, &dwIndex );
                if ( bret == TRUE ) {
                    InternetCloseHandle( hReq );
                    _closeConnectionIC( hInet, hConn );

                    // ���_�C���N�g�����s
                    dprintf( "_httpPostIC(): %s �փ��_�C���N�g\n", szBuf );
                    _httpGetIC( szBuf, buffer, FALSE, escapeURL );
                    return ( buffer );
                }
                break;
            }
        }
    }

    // ���X�|���X�{�̂���M
    bret = TRUE;
    while ( bret == TRUE ) {
        dwSize = 0;
        memset( szBuf, 0x00, sizeof( szBuf ) );
        bret = InternetReadFile( hReq,
                                 szBuf, sizeof( szBuf ) - 1, &dwSize );
        if ( bret ) {
            memcpy( tail, szBuf, dwSize );
            tail += dwSize;
        }
        if ( dwSize == 0 ) {
            if ( szBuf[0] ) {
                strcpy( tail, szBuf );
                tail += strlen( szBuf );
            }
            else
                *tail = NUL;
#ifdef  _DEBUG
            dump( buffer, tail - buffer );
#endif
            break;
        }
    }

    InternetCloseHandle( hReq );
    _closeConnectionIC( hInet, hConn );

#ifdef  _DEBUG_BBAUTH
    {
        FILE    *fp;
        char    filename[MAX_PATH];

        sprintf( filename, "./Debug/bbAuth_%d.html", time( NULL ) );
        fp = fopen( filename, "w" );
        if ( fp ) {
            fprintf( fp, "POST %s\n",   address );
            fprintf( fp, ">>   %s\n\n", request );
            fputs( buffer, fp );
            fclose( fp );
        }
    }
#endif

    return ( buffer );
}


void
doYahooStep2(
        char       *buffer,
        char       *request,
        const char *target,
        char       *cookie,
        size_t     *cookieSize
    )
{
    // �u���ӂ���v�{�^��������
    const char  *p, *q;
    char        url[BUFSIZ * 2];

    dputs( "doYahooStep2(): ���s�J�n\n" );

    p = strstr( buffer, "<form action=\"" );
    if ( p ) {
        p += 14;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( url, p, q - p );
            url[q - p] = NUL;
        }

        strcpy( request, "na=0" );
        _httpPostIC( url, request, buffer, TRUE );
        if ( *buffer )
            InternetGetCookie( target,
                               "external_session",
                               cookie,
                               (unsigned long *)cookieSize );
    }
}


BOOL
doYahooStep1b(
        char       *buffer,
        char       *request,
        const char *username,
        const char *password
    )
{
    char    *p, *q;
    char    src[MAX_NAMELEN];
    char    done[MAX_WEBPAGENAME];
    char    challenge[MAX_KEYLENGTH];
    char    u[MAX_USERIDLEN];
    char    passwd[BUFSIZ * 2];
    char    url[MAX_WEBPAGENAME];
    int     tries     = 2;
    BOOL    usePost   = FALSE;
    BOOL    ret       = FALSE;
    BOOL    escapeURL = TRUE;

    dputs( "doYahooStep1b(): ���s�J�n\n" );

    // �p�X���[�h�̍Ċm�F
    src[0]       = NUL;
    done[0]      = NUL;
    challenge[0] = NUL;
    u[0]         = NUL;
    passwd[0]    = NUL;

    if ( strstr( buffer, "name=\"login_form\">" ) )
        usePost = TRUE;

    p = strstr( buffer, "name=\".tries\" value=\"" );
    if ( p ) {
        p += 21;
        q = strchr( p, '"' );
        if ( q ) {
            char    buf[BUFSIZ];

            strncpy( buf, p, q - p );
            buf[q - p] = NUL;
            tries = atol( buf );
        }
    }

    p = strstr( buffer, "name=\".src\" value=\"" );
    if ( p ) {
        p += 19;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( src, p, q - p );
            src[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".done\" value=\"" );
    if ( p ) {
        p += 20;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( done, p, q - p );
            done[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".challenge\" value=\"" );
    if ( p ) {
        p += 25;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( challenge, p, q - p );
            challenge[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".u\" value=\"" );
    if ( p ) {
        p += 17;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( u, p, q - p );
            u[q - p] = NUL;
        }
    }

    sprintf( passwd, "%s%s", ToLower(MD5(password)), challenge );
    strcpy( passwd, ToLower( MD5( passwd ) ) );

    if ( !strcmp( src, "ba_newsing" ) )
        escapeURL = FALSE;

    if ( escapeURL ) {
        strcpy( done, translateURL( done ) );
        p = strstr( done, "appdata" );
        if ( p ) {
            char    *r;
            p += 7;
            while ( ((q = strstr( p, "%3A" )) != NULL) ||
                    ((q = strstr( p, "%2F" )) != NULL) ||
                    ((q = strstr( p, "%2E" )) != NULL)    ) {
                r = p + strlen( p );
                while ( r > q ) {
                    *(r + 2) = *r;
                    r--;
                }
                *++q = '2';
                *++q = '5';
            }
        }
    }

    if ( strstr( buffer, "name=\"promo\" value=\"" ) ) {
        strcpy( url,
            usePost ? "https://login.yahoo.co.jp/config/login?"
                    : "http://login.yahoo.co.jp/config/login?" );
        sprintf( request,
                 ".tries=%d&"
                 ".src=%s&"
                 ".md5=&"
                 ".hash=&"
                 ".js=1&"
                 ".last=&"
                 "promo=&"
                 ".intl=jp&"
                 ".bypass=&"
                 ".partner=&"
                 ".u=%s&"
                 ".v=0&"
                 ".challenge=%s&"
                 ".yplus=&"
                 ".emailCode=&"
                 "pkg=&"
                 "stepid=&"
                 ".ev=&"
                 "hasMsgr=0&"
                 ".chkP=Y&"
                 ".done=%s&"
                 ".pd=&"
                 ".protoctl=&"
                 "login=%s&"
                 "passwd=%s&"
                 ".persistent=y&"
                 ".hash=1&"
                 ".md5=1",
                 tries,
                 src,
                 u,
                 challenge,
                 done,
                 username,
                 passwd );
    }
    else {
        strcpy( url, 
                usePost ? "https://login.yahoo.co.jp/config/login_verify2?"
                        : "http://login.yahoo.co.jp/config/login_verify2?" );
        sprintf( request,
                 usePost ? ".src=%s&"
                           ".tries=%d&"
                           ".done=%s&"
                           ".md5=&"
                           ".hash=&"
                           ".js=&"
                           ".partner=&"
                           ".slogin=%s&"
                           ".intl=jp&"
                           ".fUpdate=&"
                           ".prelog=&"
                           ".bid=&"
                           ".aucid=&"
                           ".challenge=%s&"
                           ".yplus=&"
                           ".chldID=&"
                           "pkg=&"
                           "hasMsgr=0&"
                           ".pd=&"
                           ".protoctl=&"
                           ".u=%s&"
                           "passwd=%s"
                         : ".src=%s&"
                           ".tries=%d&"
                           ".done=%s&"
                           ".md5=&"
                           ".hash=&"
                           ".js=1&"
                           ".partner=&"
                           ".slogin=%s&"
                           ".intl=jp&"
                           ".fUpdate=&"
                           ".prelog=&"
                           ".bid=&"
                           ".aucid=&"
                           ".challenge=%s&"
                           ".yplus=&"
                           ".chldID=&"
                           "pkg=&"
                           "hasMsgr=0&"
                           ".pd=&"
                           ".protoctl=&"
                           ".u=%s&"
                           "passwd=%s&"
                           ".hash=1&"
                           ".md5=1",
                 src,
                 tries,
                 done,
                 username,
                 challenge,
                 u,
                 usePost ? password : passwd );
    }
    if ( usePost ) {
        p = strstr( buffer, "<form method=\"post\" action=\"" );
        if ( p ) {
            p += 28;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( url, p, q - p );
                url[q - p] = NUL;
            }
        }

#ifdef  _DEBUG
        {
            FILE    *fp = fopen( "./bbauthPost.html", "w" );
            fputs( buffer, fp );
            fclose( fp );
        }
#endif

        _httpPostIC( url, request, buffer, escapeURL );

#ifdef  _DEBUG
        {
            FILE    *fp = fopen( "./bbauthPost2.html", "w" );
            fputs( buffer, fp );
            fclose( fp );
        }
#endif
    }
    else {
        strcat( url, request );
        _httpGetIC( url, buffer, FALSE, escapeURL );
    }
    if ( *buffer ) {
        if ( strstr( buffer, "<input type=\"submit\" class=\"fakebutton\"" ) )
            ret = TRUE;
    }

    return ( ret );
}

void
doYahooStep1a(
        char       *buffer,
        char       *request,
        const char *target,
        const char *username,
        const char *password,
        char       *cookie,
        size_t     *cookieSize
    )
{
    int retry = 5;

    while ( strstr( buffer, sjis2euc("�p�X���[�h�̍Ċm�F") ) ) {
        Sleep( 2000 );
        doYahooStep1b( buffer, request, username, password );
        if ( strstr( buffer,
                     "<input type=\"submit\" class=\"fakebutton\"" ) )
            break;

        retry--;
        if ( retry <= 0 )
            break;
    }

    if ( strstr( buffer, "<input type=\"submit\" class=\"fakebutton\"" ) )
        doYahooStep2( buffer, request, target, cookie, cookieSize );
}


void
doYahooStep1(
        char       *buffer,
        const char *target,
        const char *username,
        const char *password,
        char       *cookie,
        size_t     *cookieSize
    )
{
    char    *request;
    char    *p, *q;
    char    src[MAX_NAMELEN];
    char    done[MAX_WEBPAGENAME];
    char    challenge[MAX_KEYLENGTH];
    char    u[MAX_USERIDLEN];
    char    passwd[BUFSIZ * 2];
    char    url[BUFSIZ * 2];
    int     tries     = 1;
    BOOL    escapeURL = TRUE;

    dputs( "doYahooStep1(): ���s�J�n\n" );

    // Yahoo! Japan �Ƀ��O�C��
    request  = (char *)malloc( RCV_BUFFER_SIZE );
    if ( !request ) 
        return;

    src[0]       = NUL;
    done[0]      = NUL;
    challenge[0] = NUL;
    u[0]         = NUL;
    passwd[0]    = NUL;

    p = strstr( buffer, "name=\".tries\" value=\"" );
    if ( p ) {
        p += 21;
        q = strchr( p, '"' );
        if ( q ) {
            char    buf[BUFSIZ];

            strncpy( buf, p, q - p );
            buf[q - p] = NUL;
            tries = atol( buf );
        }
    }

    p = strstr( buffer, "name=\".src\" value=\"" );
    if ( p ) {
        p += 19;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( src, p, q - p );
            src[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".done\" value=\"" );
    if ( p ) {
        p += 20;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( done, p, q - p );
            done[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".challenge\" value=\"" );
    if ( p ) {
        p += 25;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( challenge, p, q - p );
            challenge[q - p] = NUL;
        }
    }
    p = strstr( buffer, "name=\".u\" value=\"" );
    if ( p ) {
        p += 17;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( u, p, q - p );
            u[q - p] = NUL;
        }
    }

    sprintf( passwd, "%s%s", ToLower(MD5(password)), challenge );
    strcpy( passwd, ToLower( MD5( passwd ) ) );

    strcpy( done, translateURL( done ) );
    p = strstr( done, "appdata" );
    if ( p ) {
        char    *r;
        p += 7;
        while ( ((q = strstr( p, "%3A" )) != NULL) ||
                ((q = strstr( p, "%2F" )) != NULL) ||
                ((q = strstr( p, "%2E" )) != NULL)    ) {
            r = p + strlen( p );
            while ( r > q ) {
                *(r + 2) = *r;
                r--;
            }
            *++q = '2';
            *++q = '5';
        }
    }

    strcpy( url, "http://login.yahoo.co.jp/config/login?" );
    sprintf( request,
             ".tries=%d&"
             ".src=%s&"
             ".md5=&"
             ".hash=&"
             ".js=1&"
             ".last=&"
             "promo=&"
             ".intl=jp&"
             ".bypass=&"
             ".partner=&"
             ".u=%s&"
             ".v=0&"
             ".challenge=%s&"
             ".yplus=&"
             ".emailCode=&"
             "pkg=&"
             "stepid=&"
             ".ev=&"
             "hasMsgr=0&"
             ".chkP=Y&"
             ".done=%s&"
             ".pd=&"
             ".protoctl=&"
             "login=%s&"
             "passwd=%s&"
             ".persistent=y&"
             ".hash=1&"
             ".md5=1",
             tries,
             src,
             u,
             challenge,
             done,
             username,
             passwd );
    strcat( url, request );

    if ( !strcmp( src, "ba_newsing" ) )
        escapeURL = FALSE;

    _httpGetIC( url, buffer, FALSE, escapeURL );
    if ( *buffer )
        doYahooStep1a( buffer, request, target,
                       username, password, cookie, cookieSize );

    free( request );
}


void
logoutYahooJapan( char *buffer )
{
    char    *p, *q;
    char    cookie[MAX_COOKIE_LEN + 1];

    _httpGetIC( "http://www.yahoo.co.jp/", buffer, FALSE, TRUE );
    p = strstr( buffer, sjis2euc("���O�A�E�g</a>") );
    if ( p ) {
        while ( (p > buffer) && (strncmpi( p, " href=\"", 7 ) != 0) )
            p--;
        if ( !strncmpi( p, " href=\"", 7 ) ) {
            p += 7;
            q = strchr( p, '"' );
            if ( q ) {
                char    url[BUFSIZ * 2];

                strncpy( url, p, q - p );
                url[q - p] = NUL;
                if ( url[0] == '/' ) {
                    char    buf[BUFSIZ];

                    sprintf( buf, "http://www.yahoo.co.jp%s", url );
                    strcpy( url, buf );
                }

                // Yahoo! Japan ���烍�O�A�E�g����
                _httpGetIC( url, buffer, FALSE, TRUE );

                // �N�b�L�[���폜
                cookie[0] = NUL;
                InternetSetCookie( "http://www.yahoo.co.jp/", NULL, cookie );

                _httpGetIC( "http://www.yahoo.co.jp/", buffer, FALSE, TRUE );
                p = strstr( buffer, sjis2euc("���O�C��</a>") );
                if ( !p )
                    logoutYahooJapan( buffer );
            }
        }
    }
}


void
getLoginAddressOnYahooJapan(
        const char *target,
        char       *buffer,
        char       *address,
        BOOL       escapeURL
    )
{
    _httpGetIC( target, buffer, FALSE, escapeURL );
    if ( *buffer ) {
        char    *p, *q;

        p = strstr( buffer, "<a href=\"https://api.login.yahoo.co.jp/" );
        if ( p ) {
            p += 9;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( address, p, q - p );
                address[q - p] = NUL;

                while ( (p = strstr( address, "&amp;" ) ) != NULL )
                    strcpy( p + 1, p + 5 );
            }
        }
    }
}


BOOL
_loginEcNaviOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    )
{
    BOOL        ret     = FALSE;
    const char  *target = "http://buzzurl.jp/";
    char        address[MAX_WEBPAGENAME];
    char        *p;
    char        *buffer = (char *)malloc( MAX_CONTENT_SIZE * 16 );

    *cookie = NUL;
    if ( !buffer )
        return ( ret );

    // proxy ���擾
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    proxyInfoForBBAuth.useProxy         = FALSE;
    proxyInfoForBBAuth.proxyServer[0]   = NUL;
    proxyInfoForBBAuth.proxyPort        = 0;
    proxyInfoForBBAuth.proxyUserName[0] = NUL;
    proxyInfoForBBAuth.proxyPassword[0] = NUL;
    getProxyInfo( &(proxyInfoForBBAuth.useProxy),
                  proxyInfoForBBAuth.proxyServer,
                  &(proxyInfoForBBAuth.proxyPort),
                  proxyInfoForBBAuth.proxyUserName,
                  proxyInfoForBBAuth.proxyPassword );

    // �������[�U�œ���PC���g���Ă���ꍇ�����蓾��̂ŁA���O�C����Ԃł����
    // �O�̂��߂ɂ������񃍃O�A�E�g���Ă���
    _httpGetIC( target, buffer, FALSE, TRUE );
    p = strstr( buffer, "/config/logout" );
    if ( p ) {
        // Buzzurl ���烍�O�A�E�g����
        _httpGetIC( "http://buzzurl.jp/config/logout", buffer, FALSE, TRUE );

        // �N�b�L�[���폜
        cookie[0] = NUL;
        InternetSetCookie( target, NULL, cookie );
    }

    // Yahoo! Japan ���烍�O�A�E�g����
    logoutYahooJapan( buffer );

    // Buzzurl����BBAuth�J�nURL���擾
    getLoginAddressOnYahooJapan( "https://buzzurl.jp/config/login?"
                                 "done=http%3A%2F%2Fbuzzurl.jp%2F",
                                 buffer, address, TRUE );

    // BBAuth �J�n
    _httpGetIC( address, buffer, FALSE, TRUE );
    if ( *buffer ) {
        doYahooStep1( buffer, target, username, password,
                      cookie, cookieSize );
        if ( *cookie )
            ret = TRUE;
    }
    translateURL( NULL );
    free( buffer );

    return ( ret );
}

BOOL
_loginNewsingOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    )
{
    BOOL        ret     = FALSE;
    const char  *target = "http://newsing.jp/";
    char        address[MAX_WEBPAGENAME];
    char        *p;
    char        *buffer = (char *)malloc( MAX_CONTENT_SIZE * 16 );
    BOOL        done    = FALSE;
    int         retry   = 5;

    *cookie = NUL;
    if ( !buffer )
        return ( ret );

    // proxy ���擾
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    proxyInfoForBBAuth.useProxy         = FALSE;
    proxyInfoForBBAuth.proxyServer[0]   = NUL;
    proxyInfoForBBAuth.proxyPort        = 0;
    proxyInfoForBBAuth.proxyUserName[0] = NUL;
    proxyInfoForBBAuth.proxyPassword[0] = NUL;
    getProxyInfo( &(proxyInfoForBBAuth.useProxy),
                  proxyInfoForBBAuth.proxyServer,
                  &(proxyInfoForBBAuth.proxyPort),
                  proxyInfoForBBAuth.proxyUserName,
                  proxyInfoForBBAuth.proxyPassword );

    // �������[�U�œ���PC���g���Ă���ꍇ�����蓾��̂ŁA���O�C����Ԃł����
    // �O�̂��߂ɂ������񃍃O�A�E�g���Ă���
    _httpGetIC( target, buffer, FALSE, TRUE );
    p = strstr( buffer, "/logout\">" );
    if ( p ) {
        // newsing ���烍�O�A�E�g����
        _httpGetIC( "http://newsing.jp/logout", buffer, FALSE, TRUE );

        // �N�b�L�[���폜
     // cookie[0] = NUL;
     // InternetSetCookie( target, NULL, cookie );
    }

    done = FALSE;
    do {
        // Yahoo! Japan ���烍�O�A�E�g����
        logoutYahooJapan( buffer );
     // Sleep( 10000 );

        // newsing����BBAuth�J�nURL���擾
        getLoginAddressOnYahooJapan( "http://newsing.jp/login",
                                     buffer, address, FALSE );

        // BBAuth �J�n
        _httpGetIC( address, buffer, FALSE, FALSE );
        if ( strstr( buffer, sjis2euc("�p�X���[�h�̍Ċm�F") ) ) {
            char    *request  = (char *)malloc( RCV_BUFFER_SIZE );
            if ( request ) {
                doYahooStep1a( buffer, request, target,
                               username, password, cookie, cookieSize );
                free( request );
                if ( *cookie )
                    break;
            }
            retry--;
            if ( retry <= 0 )
                break;
        }
        else
            done = TRUE;
    } while ( !done );

    if ( done )
        if ( !(*cookie) )
            doYahooStep1( buffer, target, username, password,
                          cookie, cookieSize );
    if ( *cookie )
        ret = TRUE;

    translateURL( NULL );
    free( buffer );

    return ( ret );
}

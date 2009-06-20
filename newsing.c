/*
 *  newsing.c
 *      newsing �� login ����
 *          written by H.Tsujimura  29 Sep 2006
 *
 * History:
 * $Log: /comm/bookey/newsing.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     08/11/18 1:08 Tsujimura543
 * loginNewsing() �ɂ��L���b�V���𓱓�
 * 
 * 5     08/10/20 14:22 Tsujimura543
 * logi���y�[�W����g�b�v�y�[�W�֑J�ڂ���܂ł̊Ԃɑ}������钆�ԃy�[�W
 * �̓��e���ύX���ꂽ�̂ɔ����C�������{
 * 
 * 4     07/10/13 2:40 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X���ł��邱�Ƃ��m�F
 * 
 * 3     07/10/12 13:56 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�ɑΉ� (�܂��A_loginNewsingOnBBAuth() ��
 * ���Ғʂ蓮���Ă��Ȃ����߁A���ۂɂ̓A�N�Z�X�͂ł��Ȃ����)
 * 
 * 2     07/10/10 23:09 Tsujimura543
 * ���O�C�������E���s�̔���������C��
 * 
 * 1     06/09/29 23:42 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/newsing.c 1     09/05/14 3:48 tsupo $";
#endif

/* newsing �� login ���� */
int
loginNewsing(
        const char *username,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    ) {
        /* �L���b�V���N���A */
        firstTime = 0;
        return ( ret );
    }

    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* �L���b�V���̗L�����Ԃ�1���ԂƂ��� */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        if ( saveCookie[0] )
            dputs( "loginNewsing(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginNewsing(): �L���b�V���𗘗p\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ���O�C������ */
        return ( ret );
    }

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://newsing.jp/index.php" );
    sprintf( request,
             "address=%s&"
             "password=%s&"
             "autologin=1&",
             username, password );
    sprintf( request + strlen(request),
             "submit=%s&"
             "action_login=1&"
             "rurl=/login",
             encodeURL( sjis2euc("���O�C��") ) );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        char    *p, *q;

        p = strstr(response, "<meta http-equiv=\"Refresh\" content=\"1;URL=");
        if ( p ) {
            p += 42;
            q = strchr( p, '"' );
            if ( q ) {
                int len = 0;
                url[0] = NUL;
                if ( strncmp( p, "http://", 7 ) != 0 ) {
                    strcpy( url, "http://newsing.jp" );
                    len = strlen( url );
                }
                strncat( url, p, q - p );
                url[len + (q - p)] = NUL;
                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );
            }
        }

        if ( *response ) {
            if ( strstr( response, "/logout\">" )   ||
                 strstr( cookie, "NewsingSESSID=" )    )
                ret = 1;    /* ���O�C������ */
            else
                ret = 0;    /* ���O�C�����s */
        }
    }
    else
        ret = 0;        /* ���O�C�����s */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginNewsing(): ���O�C�������A�L���b�V���ɕۑ�\n" );
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
    }
    else {
        /* �L���b�V����j�� */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        firstTime       = 0;
    }

    return ( ret );
}


BOOL
_loginNewsingOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    );

/* Yahoo! Japan ID �� newsing �� login ���� */
int
loginNewsingOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    )
{
    int             ret   = 0;
    int             retry = 5;
    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    ) {
        /* �L���b�V���N���A */
        firstTime = 0;
        return ( ret );
    }

    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* �L���b�V���̗L�����Ԃ�1���ԂƂ��� */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        if ( saveCookie[0] )
            dputs( "loginNewsingOnBBAuth(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginNewsingOnBBAuth(): �L���b�V���𗘗p\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ���O�C������ */
        return ( ret );
    }

    do {
        _loginNewsingOnBBAuth( username, password, cookie, cookieSize );
        retry--;
        if ( retry <= 0 )
            break;
    } while ( !cookie || !(*cookie) );

    if ( cookie && *cookie ) {
        char        sessionID[BUFSIZ];
        const char  *p, *q;

        sessionID[0] = NUL;

        p = strstr( cookie, "NewsingSESSID" );
        if ( p ) {
            q = strchr( p, ';' );
            if ( !q )
                q = p + strlen( p );
            strncpy( sessionID, p, q - p );
            sessionID[q - p] = NUL;
        }

        if ( sessionID[0] )
            sprintf( cookie, "Cookie: %s\r\n",
                     sessionID );

        ret = 1;
    }

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginNewsingOnBBAuth(): ���O�C�������A�L���b�V���ɕۑ�\n" );
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
    }
    else {
        /* �L���b�V����j�� */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        firstTime       = 0;
    }

    return ( ret );
}

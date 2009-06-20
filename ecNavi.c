/*
 *  ecNavi.c
 *      Buzzurl �� login ����
 *          written by H.Tsujimura  29 Jun 2006
 *
 * $Log: /comm/bookey/ecNavi.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    08/11/18 1:11 Tsujimura543
 * loginEcNavi() �ɂ��L���b�V���𓱓�
 * 
 * 14    07/10/09 20:21 Tsujimura543
 * dputs() �𓱓�
 * 
 * 13    07/10/05 23:08 Tsujimura543
 * ���g���C����(+ ���J�o������)������
 * 
 * 12    07/10/05 3:02 Tsujimura543
 * loginEcNaviOnBBAuth() �� cookie �ݒ菈�����C��
 * 
 * 11    07/10/05 2:44 Tsujimura543
 * BBAuth �o�R�ł̃��O�C���������m�F
 * 
 * 10    07/09/20 20:57 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 9     07/09/20 20:51 Tsujimura543
 * ��������A�\�[�X�R�[�h�𐮗�
 * 
 * 8     07/09/20 20:45 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�Ή� (�����O�i�B�܂��������Ă��Ȃ�)
 * 
 * 7     07/09/19 21:39 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�Ή� (�Â��B�܂���ƒ�)
 * 
 * 6     07/09/14 23:26 Tsujimura543
 * BBAuth �o�R�ł̃A�N�Z�X�Ή� (�܂��r��)
 * 
 * 5     07/02/01 17:44 Tsujimura543
 * 2007�N2��1���t�� login ����� html �y�[�W�̓��e���ς�������߁A
 * ����ɂ��킹�� login �ɐ����������ǂ����̃`�F�b�N�̎d����ύX����
 * 
 * 4     07/01/11 11:35 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 3     06/10/18 19:42 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 2     06/10/10 16:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�� Web�y�[�W�� charSet �� EUC-JP ���� UTF-8 ��
 * �ύX���ꂽ�̂ɔ����C�������{
 * 
 * 1     06/06/29 18:28 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"
#include "MD5.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/ecNavi.c 1     09/05/14 3:48 tsupo $";
#endif


/* Buzzurl �� login ���� */
int
loginEcNavi(
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
            dputs( "loginEcNavi(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginEcNavi(): �L���b�V���𗘗p\n" );
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
    memset( request, 0x00, MAX_CONTENT_SIZE );

#ifdef  BEFORE_20070110
    strcpy( url, "https://ecnavi.jp/login/scripts/login.php" );
    setTargetURL( url );
    sprintf( request,
             "URL=%s&"
             "email=%s&"
             "passwd=%s&",
             encodeURL("http://news.ecnavi.jp/"),
             username, password );
    sprintf( request + strlen(request),
             "formSend=%s",
             encodeURL( sjis2utf("�@���O�C���@") ) );
#else
    strcpy( url, "https://buzzurl.jp/config/login/execute" );
    setTargetURL( url );
    sprintf( request,
             "done=%s&"
             "mail=%s&"
             "pass=%s&",
             encodeURL("http://buzzurl.jp/"),
             username, password );
    sprintf( request + strlen(request),
             "login_button=%s",
             encodeURL( sjis2utf("�@���O�C���@") ) );
#endif
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( (strstr(response, "/config/logout") != NULL) ||
             (strstr(cookie, "Apache=") != NULL)             )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }
    else
        ret = 0;        /* ���O�C�����s */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginEcNavi(): ���O�C�������A�L���b�V���ɕۑ�\n" );
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
_loginEcNaviOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    );

/* Yahoo! Japan ID �� Buzzurl �� login ���� */
int
loginEcNaviOnBBAuth(
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
            dputs( "loginEcNaviOnBBAuth(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginEcNaviOnBBAuth(): �L���b�V���𗘗p\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ���O�C������ */
        return ( ret );
    }

    do {
        _loginEcNaviOnBBAuth( username, password, cookie, cookieSize );
        retry--;
        if ( retry <= 0 )
            break;
    } while ( !cookie || !(*cookie) );

    if ( cookie && *cookie ) {
        char        external_session[BUFSIZ];
        char        apache[BUFSIZ];
        const char  *p, *q;

        external_session[0] = NUL;
        apache[0]           = NUL;

        p = strstr( cookie, "external_session" );
        if ( p ) {
            q = strchr( p, ';' );
            if ( !q )
                q = p + strlen( p );
            strncpy( external_session, p, q - p );
            external_session[q - p] = NUL;
        }

        p = strstr( cookie, "Apache" );
        if ( p ) {
            q = strchr( p, ';' );
            if ( !q )
                q = p + strlen( p );
            strncpy( apache, p, q - p );
            apache[q - p] = NUL;
        }

        if ( external_session[0] && apache[0] )
            sprintf( cookie, "Cookie: %s; %s; SESSION\r\n",
                     external_session, apache );

        ret = 1;
    }

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginEcNaviOnBBAuth(): ���O�C�������A�L���b�V���ɕۑ�\n" );
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

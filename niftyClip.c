/*
 *  niftyClip.c
 *      �j�t�e�B�N���b�v �� login ����
 *          written by H.Tsujimura  29 Jun 2006
 *
 * $Log: /comm/bookey/niftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 12    09/01/30 17:33 Tsujimura543
 * @nifty �N���b�v�� "settings" �y�[�W�̓��e�ύX�ɔ����A
 * API�L�[�擾�������X�V
 * 
 * 11    08/11/18 1:05 Tsujimura543
 * �R�����g���C��
 * 
 * 10    08/11/18 1:02 Tsujimura543
 * ���O�C�������̃L���b�V�������C��
 * 
 * 9     08/11/05 17:30 Tsujimura543
 * �uAPI�L�[�ݒ�v�{�^���������������C��
 * 
 * 8     08/11/04 16:45 Tsujimura543
 * getApiKeyOnNiftyClip() ��ǉ�
 * 
 * 7     08/11/04 11:56 Tsujimura543
 * ���O�C���������X�V (login �y�[�W�� GET ���Ă��� POST ���Ȃ���
 * ���O�C���ł��Ȃ��Ȃ����͗l)
 * 
 * 6     08/04/02 17:32 Tsujimura543
 * login�������X�V (2008�N4��1���Ƀ��O�C����ɕ\�������y�[�W�̓��e
 * �������ɕύX���ꂽ�B����ɍ��킹��login�������f�������C��)
 * 
 * 5     08/03/17 18:08 Tsujimura543
 * �L���b�V���𓱓��B���N�G�X�g����������s�x�A���O�C�����Ȃ��Ă������悤
 * �ɂ��Ă݂�
 * 
 * 4     08/03/17 16:46 Tsujimura543
 * login�������X�V (2008�N3��17���Ɏd�l�ύX�����{���ꂽ�͗l)
 * 
 * 3     06/10/19 13:58 Tsujimura543
 * �R�����g���C��
 * 
 * 2     06/10/19 13:57 Tsujimura543
 * (1) login ���s���A���g���C����悤�ɂ���
 * (2) �������A�u���[�UID�܂��̓p�X���[�h���Ⴄ�v�̂����R�ł� login ���s��
 *     �̓��g���C���s�Ȃ�Ȃ�
 * (3) ��M�o�b�t�@�I�[�o�[�t���[�΍�����{����
 * 
 * 1     06/06/29 21:26 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/niftyClip.c 1     09/05/14 3:48 tsupo $";
#endif


/* �j�t�e�B�N���b�v �� login ���� */
int
loginNiftyClip(
        const char *username,   // (I)   ���[�U�� (@nifty ID �܂��� PLEASY ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    // �L���b�V���`�F�b�N
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
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        strcpy( cookie, saveCookie );
        ret = TRUE;     /* ���O�C������ */
        return ( ret );
    }

    // ���O�C������
    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }

    sz = MAX_CONTENT_SIZE * 2;
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }

    do {
        memset( request, 0x00, MAX_CONTENT_SIZE );
        setUpReceiveBuffer( response, sz );

        *cookie = NUL;
        http_getEx( "http://clip.nifty.com/login", response, cookie );
        if ( *response ) {
            setUpReceiveBuffer( response, sz );
            strcpy( url, "https://clip.nifty.com/login" );
            setTargetURL( url );
            sprintf( request,
                     "name=&"
                     "username=%s&"
                     "password=%s",
                     username, password );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

            if ( *response ) {
                if ( strstr( response, "<a href=\"/logout\">" )             ||
                     (strstr( response, "<meta http-equiv=\"Refresh\" "
                                        "content=\"0; url=" )          &&
                      strstr( response, "window.location.replace(" )      )    ) {
                    ret = 1;    /* ���O�C������ */
                    break;
                }
                else if ( strstr( response, "login-failure" ) ) {
                    /* �u���[�UID�܂��̓p�X���[�h���Ⴂ�܂��B�v �̏ꍇ */
                    ret = 0;    /* ���O�C�����s */
                    break;
                }
            }
        }

        retry--;
        if ( retry <= 0 )
            break;
        Sleep( 2000 );
    } while ( ret == 0 );

    free( response );
    free( request  );

    // �L���b�V�����X�V
    if ( ret == TRUE ) {
        /* �L���b�V���ɕۑ� */
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie,   cookie );
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



char    *
_getApiKeyOnNiftyClip( const char *response, char *apiKey )
{
    const char  *p = response;
    const char  *q;

    q = strstr( p, "</button>" );
    if ( q ) {
        q += 9;
        while ( (*q == ' ')  || (*q == '\t') ||
                (*q == '\r') || (*q == '\n')    )
            q++;
        p = q;
        q = strstr( p, "</form>" );
        if ( q ) {
            while ( (*(q - 1) == ' ')  || (*(q - 1) == '\t') ||
                    (*(q - 1) == '\r') || (*(q - 1) == '\n')    )
                q--;

            if ( !strncmpi( p, "<input ", 7 ) ) {
                q = strstr( p, "value=\"" );
                if ( q ) {
                    p = q + 7;
                    q = strchr( p, '"' );
                    if ( !q )
                        q = p + MAX_KEYLENGTH;
                }
            }

            if ( ((q - p) <= MAX_KEYLENGTH ) ) {
                strncpy( apiKey, p, q - p );
                apiKey[q - p] = NUL;
            }
        }
    }

    return ( apiKey );
}

char    *
getApiKeyOnNiftyClip(
        const char *username,   // (I)   ���[�U�� (@nifty ID �܂��� PLEASY ID)
        const char *password,   // (I) �p�X���[�h
        char       *apiKey      // (O) API�L�[
    )
{
    char    cookie[MAX_COOKIE_LEN + 1];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( !apiKey )
        return ( NULL );

    *apiKey = NUL;
    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    if ( loginNiftyClip( username, password, cookie ) ) {
        response = (char *)malloc( sz );
        if ( !response )
            return ( apiKey );

        setUpReceiveBuffer( response, sz );
        http_getEx( "http://clip.nifty.com/settings", response, cookie );
        if ( *response ) {
            char    *p = strstr( response, sjis2utf("API�L�[�Ĕ��s") );
            if ( p ) {
                // ���ł� API�L�[���s�ς݂̏ꍇ
                _getApiKeyOnNiftyClip( p, apiKey );
            }
            else {
                // �܂� API�L�[�����s����Ă��Ȃ��ꍇ
                char    request[BUFSIZ];
                sprintf( request, "submitAction=%s",
                         sjis2utf("API�L�[���s") );
                setUpReceiveBuffer( response, sz );
                http_postEx( "http://clip.nifty.com/settings",
                             "application/x-www-form-urlencoded",
                             request, response, cookie );
                if ( *response ) {
                    p = strstr( response, "setAPIKey" );
                    if ( p )
                        _getApiKeyOnNiftyClip( p, apiKey );
                }
            }
        }

        free( response );
    }

    return ( apiKey );
}

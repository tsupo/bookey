/*
 *  livedoorClip.c
 *      livedoor �N���b�v �� login ����
 *          written by H.Tsujimura  28 Jun 2006
 *
 * $Log: /comm/bookey/livedoorClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     08/11/18 1:20 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 8     08/07/28 15:29 Tsujimura543
 * getApiKeyOnLivedoorClip() ��ǉ�
 * 
 * 7     08/03/10 14:58 Tsujimura543
 * �u���O�C������ɕ\������� Web �y�[�W�v�̎d�l�ύX(2008�N3��8����
 * ���{?)�ɂ��킹�āAlogin�������X�V
 * 
 * 6     07/11/07 5:02 Tsujimura543
 * 2007�N11��6���Ɏ��{���ꂽ�����ȕύX�ɑΉ� (���O�C������/���s�������
 * ������) [livedoor�N���b�v�� Google Analytics �����ɂ��ύX�̖͗l]
 * 
 * 5     06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 4     06/07/31 17:43 Tsujimura543
 * �R�����g���C��
 * 
 * 3     06/07/31 17:42 Tsujimura543
 * (1) ���O�C������� Web �y�[�W�̃T�C�Y���傫���Ȃ���(2006�N7��31������
 *     �ȍ~)���߁A�o�b�t�@�[�I�[�o�[�������������Abookey���ُ�I�������
 *     ���ɂȂ��Ă��܂������߁A��M�d���i�[�̈�T�C�Y�𑝂₵�A����ɃI�[
 *     �o�[�����h�~�@�\��g�ݍ���
 * (2) login ���s���A�ő�5��܂Ń��g���C����悤�ɂ��� (���܂� login �Ɏ�
 *     �s���邱�Ƃ����邽��)
 * 
 * 2     06/06/29 17:04 Tsujimura543
 * �R�����g���C��
 * 
 * 1     06/06/29 0:02 Tsujimura543
 * �ŏ��̔� (����m�F�ς�) [livedoor Blog �ւ� login ���������ɍ쐬]
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/livedoorClip.c 1     09/05/14 3:48 tsupo $";
#endif


/* livedoor �N���b�v �� login ���� */
int
loginLivedoorClip(
        const char *username,   // (I)   ���[�U�� (livedoor ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 4;

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
            dputs( "loginLivedoorClip(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginLivedoorClip(): �L���b�V���𗘗p\n" );
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

    do {
        memset( request,  0x00, MAX_CONTENT_SIZE );

        setUpReceiveBuffer( response, sz );
        http_getEx( "http://clip.livedoor.com/",
                    response, cookie );

        strcpy( url, "http://member.livedoor.com/login/index" );
        setTargetURL( url );
        sprintf( request,
                 ".next=%s&"
                 ".sv=clip&"
                 "livedoor_id=%s&"
                 "password=%s&"
                 "auto_login=on\r\n",
                 encodeURL("http://clip.livedoor.com/register/"),
                 username, password );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            if ( strstr( response, "<a href=\"/logout\">" ) ||
                 strstr( response, "<a href=\"/logout\" " ) ||
                 strstr( response, "/logout\"" )            ||
                 strstr( response, "/logout\'" )               )
                ret = 1;    /* ���O�C������ */
            else
                ret = 0;    /* ���O�C�����s */
        }
        else
            ret = 0;        /* ���O�C�����s */

        if ( ret == 0 ) {
            retry--;
            if ( retry <= 0 )
                break;
            Sleep( 2000 );
        }
    } while ( ret == 0 );

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginLivedoorClip(): ���O�C�������A�L���b�V���ɕۑ�\n" );
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


char    *
getApiKeyOnLivedoorClip(
        const char *username,   // (I) ���[�U�� (livedoor ID)
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
    if ( loginLivedoorClip( username, password, cookie ) ) {
        response = (char *)malloc( sz );
        if ( !response )
            return ( apiKey );

        setUpReceiveBuffer( response, sz );
        http_getEx( "http://clip.livedoor.com/config/api", response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"api-key-box\"" );
            if ( p ) {
                char    *q;

                p += 13;
                q = strchr( p, '>' );
                if ( q ) {
                    p = q + 1;
                    q = strchr( p, '<' );
                    if ( q && ((q - p) <= MAX_KEYLENGTH ) ) {
                        strncpy( apiKey, p, q - p );
                        apiKey[q - p] = NUL;
                    }
                }
            }
        }

        free( response );
    }

    return ( apiKey );
}

/*
 *  joltMark.c
 *      JoltMark �� login ����
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/joltMark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     08/11/18 1:20 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 1     06/12/21 16:53 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/joltMark.c 1     09/05/14 3:48 tsupo $";
#endif


/* JoltMark �� login ���� */
int
loginJoltMark(
        const char *username,   // (I)   ���[�U��
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
            dputs( "loginJoltMark(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginJoltMark(): �L���b�V���𗘗p\n" );
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

        strcpy( url, "https://mark.jolt.jp/login.do" );
        setTargetURL( url );
        sprintf( request,
                 "userId=%s&"
                 "password=%s&"
                 "autoLogin=on&"
                 "login=%s",
                 username, password,
                 encodeURL(sjis2utf("���O�C��")) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            char    *p, *q;

            p = strstr( response,
                        "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=" );
            if ( p ) {
                p += 42;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                    setUpReceiveBuffer( response, sz );
                    http_getEx( url, response, cookie );
                }
            }

            if ( *response ) {
                if ( strstr( response, sjis2utf("�Ń��O�C����") ) != NULL )
                    ret = 1;    /* ���O�C������ */
                else
                    ret = 0;    /* ���O�C�����s */
            }
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
        dputs( "loginJoltMark(): ���O�C�������A�L���b�V���ɕۑ�\n" );
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

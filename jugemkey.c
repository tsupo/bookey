/*
 *  jugemkey.c
 *      jugemkey �� login ����
 *          written by H.Tsujimura  4 Oct 2006
 *
 * $Log: /comm/bookey/jugemkey.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/11/18 1:20 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 3     07/01/30 0:32 Tsujimura543
 * ���O�C���������ďC�� (�N�b�L�[�̃t�H�[�}�b�g���ς������͈̂ꎞ�I�Ȍ���
 * �炵���B�T�[�o�̕��ׂ��d���ƃN�b�L�[�̕����o���������ςɂȂ�̂���)
 * 
 * 2     07/01/30 0:01 Tsujimura543
 * login �������C�� (cookie �̃t�H�[�}�b�g���ύX���ꂽ)
 * 
 * 1     06/10/04 21:48 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/jugemkey.c 1     09/05/14 3:48 tsupo $";
#endif


/* jugemkey �� login ���� */
int
loginJugemkey(
        const char *username,   // (I)   jugemkey
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
            dputs( "loginJugemkey(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginJugemkey(): �L���b�V���𗘗p\n" );
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
        strcpy( url, "http://pookmark.jp/ajax/login" );
        setTargetURL( url );
        sprintf( request,
                 "username=%s&"
                 "password=%s&"
                 "cookie=on&"
                 "_=",
                 username, password );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response && *cookie ) {
            if ( (strstr( cookie, "username=" ) != NULL) &&
                 (strstr( cookie, "POOKMARK=" ) != NULL)    )
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
        dputs( "loginJugemkey(): ���O�C�������A�L���b�V���ɕۑ�\n" );
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

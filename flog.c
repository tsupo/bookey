/*
 *  flog.c
 *      Flog �� login ����
 *          written by H.Tsujimura  31 May 2006
 *
 * $Log: /comm/bookey/flog.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     08/11/18 1:26 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 2     06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 1     06/05/31 17:42 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/flog.c 1     09/05/14 3:48 tsupo $";
#endif


/* Flog �� login ���� */
int
loginFlog(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    )
{
    int     ret = 0;    /* �����l�́ulogin ���s�v */
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie   ||
         !userName || !(*userName) ||
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
        else if ( ( strcmp( userName, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 )    )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        if ( saveCookie[0] )
            dputs( "loginFlog(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginFlog(): �L���b�V���𗘗p\n" );
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

    strcpy( url, "http://www.flog.jp/login.php" );
    sprintf( request,
             "m=%s&"
             "p=%s&"
             "submit=%s",
             userName, password, encodeURL("���O�C��") );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "���O�C�����������܂���" ) != NULL ) {
            if ( !(cookie[0]) ) {
                /*
                 * html �\�[�X�̒��ɁAcookie ���Z�b�g���邽�߂� JavaScript ��
                 * �L�q����Ă���B���̋L�q������ cookie ��g�ݗ��Ă�
                 *
                 * ��)
                 *     document.cookie = 'MDMD=8317558c2959e8bdb7d774dd77c9b8
                 *     72 ; expires=Thu,05-Jan-30 00:00:01 GMT; path=/;';docu
                 *     ment.cookie = 'DMDM=' + 'tsupo@na.rim.or.jp' + ' ; exp
                 *     ires=Thu,05-Jan-30 00:00:01 GMT; path=/;';var name = e
                 *     scape("tsupo");document.cookie = "NAME =" + name +"; e
                 *     xpires=Thu,05-Jan-10 00:00:01 GMT; path=/";
                 *      ��
                 *     MDMD=8317558c2959e8bdb7d774dd77c9b872; DMDM=tsupo@na.r
                 *     im.or.jp; NAME=tsupo
                 */
                char    *p, *q, *r;
                p = strstr( response, "document.cookie = '" );
                if ( p ) {
                    p += 19;
                    q = strchr( p, ';' );
                    if ( q ) {
                        r = q + 1;
                        while ( *(q - 1) == ' ' )
                            q--;
                        strcpy( cookie, "Cookie: " );
                        strncat( cookie, p, q - p );
                        cookie[8 + (q - p)] = NUL;
                        sprintf( cookie + strlen( cookie ),
                                 "; DMDM=%s; NAME=", userName );
                        p = strstr( r, "name = escape(\"" );
                        if ( p ) {
                            p += 15;
                            q = strchr( p, '"' );
                            if ( q ) {
                                int len = strlen( cookie );
                                strncat( cookie, p, q - p );
                                cookie[len + (q - p)] = NUL;
                                ret = 1;    /* login ���� */
                            }
                        }
                    }
                }
            }
            else
                ret = 1;    /* login ���� */
        }
        else
            ret = 0;        /* login ���s */
    }
    else
        ret = 0;            /* login ���s */

    free( response );
    free( request );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginFlog(): ���O�C�������A�L���b�V���ɕۑ�\n" );
        strcpy( saveUserName, userName );
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

/*
 *  blogPet.c
 *      BlogPet �Ǘ���� �� login ����
 *          written by H.Tsujimura  12 Sep 2006 / 22 Dec 2006
 *
 * $Log: /comm/bookey/blogPet.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     08/11/18 1:04 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 7     08/01/25 15:32 Tsujimura543
 * ���[�U���A�p�X���[�h�Ƀ}���`�o�C�g�������g���Ă���l������Ƃ̂��ƂŁA
 * ���[�U���ƃp�X���[�h�� UTF-8�ɕϊ�����悤�ɂ��Ă݂�
 * 
 * 6     07/07/13 2:01 Tsujimura543
 * 2007�N7��12���Ɏ��{���ꂽ BlogPet ���j���[�A���ɑΉ�
 * 
 * 5     07/02/14 23:14 Tsujimura543
 * encodeURLe() �̃v���g�^�C�v�錾�� blogPet.h �ֈړ�
 * 
 * 4     07/02/13 21:43 Tsujimura543
 * encodeURLe() �� getBlogPet.c ���� blogPet.c �ֈړ�
 * 
 * 3     06/12/25 23:37 Tsujimura543
 * loginBlogPet() �ɑ�4������ǉ�
 * 
 * 2     06/12/25 13:51 Tsujimura543
 * "jump=&" ��ǉ�
 * 
 * 1     06/12/22 21:38 Tsujimura543
 * �u�����������v�p�ɍ���������𗬗p
 */

#include "xmlRPC.h"
#include "myClip.h"
#include "blogPet.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/blogPet.c 1     09/05/14 3:48 tsupo $";
#endif


/* BlogPet �Ǘ���� �� login ���� */
int
loginBlogPet(
        const char *userName,   // (I)   ���[�U��
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        char       *userID      // (O)   ���[�UID
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    _username[MAX_USERIDLEN];
    char    _password[MAX_PASSWDLEN];
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 4;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static char     saveUserID[MAX_NAMELEN];
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
            dputs( "loginBlogPet(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
    }
    else {
        dputs( "loginBlogPet(): �L���b�V���𗘗p\n" );
        strcpy( cookie, saveCookie );
        strcpy( userID, saveUserID );
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

    strcpy( _username, userName );
    any2utf( _username );
    strcpy( _password, password );
    any2utf( _password );

    do {
        memset( request, 0x00, MAX_CONTENT_SIZE );

        strcpy( url, "https://www.blogpet.net/login" );
        setTargetURL( url );
        setUpReceiveBuffer( response, MAX_CONTENT_SIZE * 4 );
        sprintf( request,
                 "username=%s&",
                 encodeURL(_username) );
        sprintf( request + strlen(request),
                 "password=%s&"
                 "remember=1&"
                 "jump_url=%%2Fhome",
                 encodeURL(_password) );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            if ( strstr( response, "/logout" ) != NULL )
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

    if ( ret == 1 ) {
        setUpReceiveBuffer( response, sz );
        http_getEx( "http://www.blogpet.net/home", response, cookie );
        if ( *response ) {
            char    *p;

            p = strstr( response, "/profile/friends/" );
            if ( !p )
                p = strstr( response, "/profile/groups/" );
            if ( p ) {
                char    *q;

                p = strstr( p, "s/" ) + 2;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( userID, p, q - p );
                    userID[q - p] = NUL;
                }
            }
        }
    }

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginBlogPet(): ���O�C�������A�L���b�V���ɕۑ�\n" );
        strcpy( saveUserName, userName );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
        strcpy( saveUserID, userID );
    }
    else {
        /* �L���b�V����j�� */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        firstTime       = 0;
    }

    return ( ret );
}

char    *
encodeURLe( const char *p )
{
    static char hex[] = "0123456789ABCDEF";
    static char temp[MAX_CONTENT_SIZE];
    char        *q = temp;

    while ( *p ) {
        if ( (unsigned char)(*p) < 0x80 )
            *q++ = *p++;
        else {
            *q++ = '%';
            *q++ = hex[(*p &0xF0) >> 4];
            *q++ = hex[*p & 0x0F];
            p++;
        }
    }
    *q = NUL;

    return ( temp );
}


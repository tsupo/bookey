/*
 *  fc2bookmark.c
 *      FC2BOOKMARK �� login ����
 *          written by H.Tsujimura  29 Mar 2007
 *
 * $Log: /comm/bookey/fc2bookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     08/11/18 1:05 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 5     07/09/26 14:00 Tsujimura543
 * keep_login �� Submit �̏��������ւ���
 * 
 * 4     07/03/29 18:06 Tsujimura543
 * loginFC2Bookmark() �̈�����2�ǉ��Buid �� cc ���擾����悤�ɂ���
 * 
 * 3     07/03/29 17:25 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 2     07/03/29 17:24 Tsujimura543
 * �������� (���ۂɃ��O�C���ł��邱�Ƃ��m�F)
 * 
 * 1     07/03/29 15:06 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/fc2bookmark.c 1     09/05/14 3:48 tsupo $";
#endif


/* FC2BOOKMARK �� login ���� */
int
loginFC2Bookmark(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        char       *uid,        // (O)   uid (FC2ID �̃��[�UID)
        char       *cc          // (O)   cc  (FC2BOOKMARK ��cc)
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
    static char     saveUserID[MAX_NAMELEN];
    static char     saveCC[MAX_KEYLENGTH];
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
            dputs( "loginFC2Bookmark(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveCC[0]       = NUL;
    }
    else {
        dputs( "loginFC2Bookmark(): �L���b�V���𗘗p\n" );
        strcpy( cookie, saveCookie );
        strcpy( uid,    saveUserID );
        strcpy( cc,     saveCC );
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

    strcpy( url, "https://secure.id.fc2.com/?mode=login" );
    setTargetURL( url );
    sprintf( request,
             "email=%s&"
             "pass=%s&",
             userName, password );
    sprintf( request + strlen(request),
             "Submit=%s&"
             "keep_login=1",
             encodeURL( sjis2utf("���O�C��") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        char    *p = strstr(response,
                            "<META http-equiv=\"Refresh\" content=\"0; url=");
        if ( p ) {
            char    *q;

            p += 43;
            q = strstr( p, "\">" );
            if ( q ) {
                strncpy( url, p, q - p );
                url[q - p] = NUL;

                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );
            }
        }

        if ( *response && strstr( response, "logout" ) ) {
            char    *p = strstr( response,
                                 "http://bookmark.fc2.com/user/index?uid=" );
            if ( p ) {
                char    *q;

                p += 39;
                q = strchr( p, '&' );
                if ( q ) {
                    strncpy( uid, p, q - p );
                    uid[q - p] = NUL;

                    q++;
                    p = strstr( q, "cc=" );
                    if ( p ) {
                        p += 3;
                        q = strchr( q, '"' );
                        if ( !q )
                            q = strchr( q, '>' );
                        if ( !q )
                            q = strchr( q, ' ' );
                        if ( q ) {
                            strncpy( cc, p, q - p );
                            cc[q - p] = NUL;
                        }
                    }
                }
                /* uid �� FC2ID ���K�v�ȑS�T�[�r�X�ŋ���         */
                /* cc  �� FC2ID ���K�v�ȃT�[�r�X���Ƃɑ��݂���l */
            }
            ret = 1;    /* ���O�C������ */
        }
        else
            ret = 0;    /* ���O�C�����s */
    }
    else
        ret = 0;        /* ���O�C�����s */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginFC2Bookmark(): ���O�C�������A�L���b�V���ɕۑ�\n" );
        strcpy( saveUserName, userName );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
        strcpy( saveUserID, uid );
        strcpy( saveCC,     cc );
    }
    else {
        /* �L���b�V����j�� */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveCC[0]       = NUL;
        firstTime       = 0;
    }

    return ( ret );
}

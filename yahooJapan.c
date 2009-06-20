/*
 *  yahooJapan.c
 *      Yahoo! Japan �� login ����
 *          written by H.Tsujimura  16 Apr 2007
 *
 * $Log: /comm/bookey/yahooJapan.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/04/16 22:02 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/yahooJapan.c 1     09/05/14 3:48 tsupo $";
#endif


/* Yahoo! Japan �� login ���� */
int
loginYahooJapan(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    )
{
    int     ret   = 0;
    int     retry = 5;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    challenge[MAX_KEYLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    // http://bookmarks.yahoo.co.jp/all �� GET
    challenge[0] = NUL;
    setUpReceiveBuffer( response, sz );
    http_get( "http://bookmarks.yahoo.co.jp/all", response );
    if ( *response ) {
        char    *p, *q;

        p = strstr( response, "name=\".challenge\" value=\"" );
        if ( p ) {
            p += 25;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( challenge, p, q - p );
                challenge[q - p] = NUL;
            }
        }
    }

    if ( challenge[0] ) {
        do {
            memset( request,  0x00, MAX_CONTENT_SIZE );

            strcpy( url, "https://login.yahoo.co.jp/config/login" );
            setTargetURL( url );
            sprintf( request,
                     ".done=%s&"
                     ".src=bmk2&"
                     ".challenge=%s&"
                     ".chkP=Y&"
                     "login=%s&"
                     "passwd=%s&"
                     ".persistent=Y&",
                     encodeURL( "http://bookmarks.yahoo.co.jp/all" ),
                     challenge,
                     username, password );
            sprintf( request + strlen( request ),
                     "submit=%s",
                     encodeURL(sjis2utf("���O�C��")) );
            setUpReceiveBuffer( response, sz );
            http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

            if ( *response ) {
                char    *p, *q;

                p = strstr( response,
                            "<meta http-equiv=\"Refresh\" content=\"0; url=" );
                if ( p ) {
                    p += 43;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( url, p, q - p );
                        url[q - p] = NUL;
                        setUpReceiveBuffer( response, sz );
                        http_getEx( url, response, cookie );
                    }
                }

                if ( *response ) {
                    if ( strstr( response,
                     "http://login.yahoo.co.jp/config/login?logout") != NULL )
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
    }

    free( response );
    free( request  );

    return ( ret );
}

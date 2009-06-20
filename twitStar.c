/*
 * twitStar.c : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �������֘A�e�폈���Q
 *          written by H.Tsujimura  24 Aug 2007 / 27 Aug 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/twitStar.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/11/18 1:05 Tsujimura543
 * �R�����g���C��
 * 
 * 3     08/11/18 1:00 Tsujimura543
 * ���O�C�������̃L���b�V�������C��
 * 
 * 2     07/08/27 21:54 Tsujimura543
 * ���̐��� 0 �̂Ƃ��AgetHatenaStar() ���Ŗ������[�v�Ɋׂ�s����C��
 * 
 * 1     07/08/27 20:51 Tsujimura543
 * Chirrup �p�ɍ쐬�����\�[�X����荞�݂Abookey �p�ɃA�����W
 * 
 * ------------------------------------------------------------------------
 * �ȉ��́Achirrup/twitStar.c �̕ύX����
 * ------------------------------------------------------------------------
 * 2     07/08/27 17:17 Tsujimura543
 * �͂ĂȃX�^�[�ɓn�� title ���u�������v Greasemonkey �̎d�l�ɂ��킹��
 * 
 * 1     07/08/24 22:29 Tsujimura543
 * �ŏ��̔�
 */


#include <time.h>
#include "xmlRpc.h"
#include "twitStar.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/twitStar.c 1     09/05/14 3:48 tsupo $";
#endif


BOOL
loginHatenaStar(
    const char *username,   // (I) �͂Ă�ID
    const char *password,   // (I) �p�X���[�h
    char       *cookie )    // (O) �N�b�L�[
{
    int     ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !cookie || !username || !password )
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
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        firstTime = 0;
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

    strcpy( url,
            "https://www.hatena.ne.jp/login?"
            "location=http%3A%2F%2Fs.hatena.ne.jp%2F" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    strcpy( url, "https://www.hatena.ne.jp/login" );
    setTargetURL( url );
    sprintf( request,
             "name=%s&"
             "password=%s&"
             "persistent=1&"
             "location=http://s.hatena.ne.jp/",
             username, password );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, sjis2utf("���O�C�����ł�") ) != NULL ) {
            setUpReceiveBuffer( response, sz );
            http_getEx( "http://s.hatena.ne.jp/", response, cookie );
            if ( *response ) {
                if ( strstr( response, sjis2utf(">���O�A�E�g</a>") ) != NULL )
                    ret = TRUE;     /* ���O�C������ */
            }
        }
    }

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
getTitleForTwitStar( const char *url )
{
    // ���̏������̂́ATwitter �ȊO�� Web�T�C�g�ɑ΂��Ă��A�͂ĂȃX�^�[��
    // ���[����(��������)���Ƃ��ł���悤�ɔz�����ď����Ă���
    static char title[MAX_CONTENT_SIZE];
    char        *response;
    char        *p, *q;
    size_t      sz;

    title[0] = NUL;
    sz       = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( title );

    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response ) {
        // title �v�f���擾
        p = strstr( response, "<title>" );
        if ( !p )
            p = strstr( response, "<title " );
        if ( !p )
            p = strstr( response, "<TITLE>" );
        if ( !p )
            p = strstr( response, "<TITLE " );
        if ( !p )
            p = strstr( response, "<h1>" );
        if ( !p )
            p = strstr( response, "<h1 " );
        if ( !p )
            p = strstr( response, "<H1>" );
        if ( !p )
            p = strstr( response, "<H1 " );
        if ( p ) {
            p++;
            p = strchr( p, '>' );
            p++;
            q = strstr( p + 1, "</" );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;

                while ( ( ( p = strchr( title, '\r' ) ) != NULL ) ||
                        ( ( p = strchr( title, '\n' ) ) != NULL )    )
                    strcpy( p, p + 1 );
            }
        }

        /* for Twitter */
        if ( !strncmp( title, "Twitter / ", 10 ) ) {
            p = title + 10;
            q = strchr( p, ':' );
            if ( q ) {
                q++;
                if ( !strcmp( q, " " ) ) {
                    // protected user
                    char    username[BUFSIZ];

                    q--;
                    strncpy( username, p, q - p );
                    username[q - p] = NUL;
                    sprintf( title,
                             "%s is only giving updates to friends.",
                             username );
                }
                else {
                    strcpy( title, q );

                    // �u�������v Greasemonkey �Ǝd�l�����킹�邽�߁A
                    // Twitter �̔����{�����擾����
                    // (http://d.hatena.ne.jp/os0x/20070823/1187832762 ���Q��)
                    p = strstr( response, "<div class=\"desc\">" );
                    if ( p ) {
                        p += 18;
                        q = strstr( p, "<p>" );
                        if ( q ) {
                            p = q + 3;
                            while ( (*p == ' ')  || (*p == '\t') ||
                                    (*p == '\r') || (*p == '\r')    )
                                p++;
                            q = strstr( p, "</p>" );
                            if ( q ) {
                                while ( (q > p)                  &&
                                        ((*(q - 1) == ' ')  ||
                                         (*(q - 1) == '\t') ||
                                         (*(q - 1) == '\r') ||
                                         (*(q - 1) == '\r')    )    )
                                    q--;
                            }
                            strncpy( title, p, q - p );
                            title[q - p] = NUL;
                            if ( strchr( title, '<' ) ) {
                                /* html �^�O�̏��� */
                                const char  *r;

                                p = title;
                                while ( ( q = strchr( p, '<' ) ) != NULL ) {
                                    if ( (r = strchr(q + 1, '>')) != NULL )
                                        strcpy( q, r + 1 );
                                    else {
                                        *q = NUL;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        /* asahi.com �΍� #1 */
        while ( ( p = strstr( title, "&#160;" ) ) != NULL ) {
            *p++ = ' ';
            strcpy( p, p + 5 );
        }

        /* asahi.com �΍� #2 */
        if ( ( p = strstr( title, "\xEF\xBF\xBD-\xEF\xBF\xBD" ) ) != NULL ) {
            strcpy( p, " - " );
            strcpy( p + 3, p + 7 );
        }
    }

    free( response );

    // UTF-8 �ȊO�̕����R�[�h�̏ꍇ�AUTF-8 �ɕϊ�����
    if ( strstr( title, "\033$@" ) || strstr( title, "\033$B" ) ) {
        p = jis2sjis( title );
        if ( p )
            strcpy( title, p );
    }

    p = any2utf( title );
    if ( p )
        strcpy( title, p );

    // �]���ȃz���C�g�X�y�[�X������
    p = title;
    while ( *p ) {
        if ( (*p == '\t') || (*p == '\r') || (*p == '\n' ) )
            *p = ' ';
        p++;
    }

    p = title;
    while ( *p ) {
        while ( (*p == ' ') && (*(p + 1) == ' ') )
            strcpy( p, p + 1);
        p++;
    }

    p = title;
    while ( *p == ' ' )
        strcpy( p, p + 1);

    if ( *p ) {
        p = &(title[strlen(title) - 1]);
        while ( *p == ' ' )
            *p-- = NUL;
    }

    return ( title );
}

// targetURL �Ŏw�肵��Web�y�[�W�� �� ������
BOOL
setHatenaStar( const char *targetURL,   // (I) ����������Web�y�[�WURL
               const char *username,    // (I) �͂Ă�ID
               const char *password )   // (I) �p�X���[�h
{
    size_t  sz = MAX_CONTENT_SIZE;
    char    *request;
    char    *response;
    char    *url;
    char    cookie[MAX_COOKIE_LEN];
    BOOL    r;
    BOOL    ret = FALSE;

    memset( cookie, 0x00, MAX_COOKIE_LEN );
    request  = (char *)malloc( sz );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    url = (char *)malloc( strlen( targetURL ) + MAX_CONTENT_SIZE );
    if ( !url ) {
        free( response );
        free( request );
        return ( ret );
    }

    // �͂ĂȃX�^�[�Ƀ��O�C��
    r = loginHatenaStar( username, password, cookie );
    if ( r ) {
        time_t      t = time( NULL );
        struct tm   *tm = localtime( &t );
        char        timeStr[BUFSIZ];

        strftime( timeStr, BUFSIZ - 1,
                  "%a %b %d %H:%M:%S UTC+0900 %Y", tm );

        // rks ���擾
        setUpReceiveBuffer( response, sz );
        sprintf( url,
                 "http://s.hatena.ne.jp/entries.json?"
                 "uri=%s&"
                 "callback=Ten.JSONP.callback&",
                 encodeURL( targetURL ) );
        sprintf( url + strlen(url),
                 "%s",
                 encodeURL( timeStr ) );
        http_getEx( url, response, cookie );
        if ( *response ) {
            char        rks[BUFSIZ];
            char        title[BUFSIZ];
            const char  *p, *q;

            p = strstr( response, "\"rks\":\"" );
            if ( p ) {
                p += 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( rks, p, q - p );
                    rks[q - p] = NUL;
                }

                // ��������
                t = time( NULL );
                tm = localtime( &t );
                strftime( timeStr, BUFSIZ - 1,
                          "%a %b %d %H:%M:%S UTC+0900 %Y", tm );

                strcpy( title, getTitleForTwitStar( targetURL ) );

                setUpReceiveBuffer( response, sz );
                sprintf( url,
                         "http://s.hatena.ne.jp/star.add.json?uri=%s&",
                         encodeURL( targetURL ) );
                sprintf( url + strlen(url),
                         "title=%s&"
                         "rks=%s&"
                         "callback=Ten.JSONP.callback&",
                         encodeURL( title ), rks );
                sprintf( url + strlen(url),
                         "%s",
                         encodeURL( timeStr ) );
                http_getEx( url, response, cookie );
                if ( *response ) {
                    if ( strstr( response, username )      ||
                         strstr( response, "\"name\":\"" )    )
                        ret = TRUE;
                }
            }
        }
    }

    free( url );
    free( response );
    free( request );

    return ( ret );
}


// targetURL �Ŏw�肵��Web�y�[�W�� �� �𐔂���
long
getHatenaStar( const char *targetURL )  // (I) ���̐��𒲂ׂ���Web�y�[�WURL
{
    size_t      sz = MAX_CONTENT_SIZE;
    char        *response;
    char        *url;
    BOOL        ret = FALSE;
    long        numOfStars = 0;
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );
    char        timeStr[BUFSIZ];

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    url = (char *)malloc( strlen( targetURL ) + MAX_CONTENT_SIZE );
    if ( !url ) {
        free( response );
        return ( ret );
    }

    strftime( timeStr, BUFSIZ - 1,
              "%a %b %d %H:%M:%S UTC+0900 %Y", tm );

    // �� �����擾
    setUpReceiveBuffer( response, sz );
    sprintf( url,
             "http://s.hatena.ne.jp/entries.json?"
             "uri=%s&"
             "callback=Ten.JSONP.callback&",
             encodeURL( targetURL ) );
    sprintf( url + strlen(url),
             "%s",
             encodeURL( timeStr ) );
    http_get( url, response );
    if ( *response ) {
        // �� �𐔂���
        const char  *p, *q;

        p = response;
        while ( *p ) {
            q = strstr( p, "{\"name\":\"" );
            if ( q ) {
                numOfStars++;
                p = q + 9;
                q = strchr( p, '}' );
                if ( q ) {
                    p = q + 1;
                    if ( *p == ',' ) {
                        if ( (*(p + 1) >= '1') && (*(p + 1) <= '9') ) {
                            numOfStars = atol( p + 1 );
                            break;
                        }
                        p++;
                    }
                }
                continue;
            }
            else
                break;
        }
    }

    free( url );
    free( response );

    return ( numOfStars );
}

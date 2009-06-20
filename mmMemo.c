/*
 *  mmMemo.c
 *      MM/Memo ��(TypeKey�F�،o�R��) login ����
 *          written by H.Tsujimura  18 Oct 2005
 *
 * $Log: /comm/bookey/mmMemo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 22    08/12/05 17:32 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 21    08/12/05 17:29 Tsujimura543
 * �f�o�b�O�p�̏������폜(���Y��Ă���)
 * 
 * 20    08/12/05 15:03 Tsujimura543
 * login1470netViaHatena() ���C�� (�͂ĂȔF�؉��̃��O�C���菇�ύX�ɑΉ�)
 * 
 * 19    08/12/02 22:02 Tsujimura543
 * TypePad Connect �o�R�� MM/Memo �փ��O�C�����悤�Ƃ����Ƃ���
 * ���񃊃g���C���Ă� [RETRY] ���Ԃ��Ă���悤�ȏ�Ԃ�(MM/Memo��)
 * �Ȃ��Ă��邱�Ƃ����邱�Ƃ������B���̑΍�����{����
 * 
 * 18    08/11/25 17:49 Tsujimura543
 * TypeKey �F�� �� TypePad Connect �ڍs�ɔ����C�������{
 * 
 * 17    08/11/18 1:05 Tsujimura543
 * �R�����g���C��
 * 
 * 16    08/11/18 1:02 Tsujimura543
 * ���O�C�������̃L���b�V�������C��
 * 
 * 15    07/06/29 22:24 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 14    07/06/29 22:22 Tsujimura543
 * (1) http://1470.net/mm/ �� http://mmmemo.1470.net/mm/ �֕ύX
 * (2) TypeKey �F�؂܂����C�� (���̊Ԃɂ��F�؂Ɏ��s����悤�ɂȂ��Ă���)
 * 
 * 13    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 12a   06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 12    06/08/22 17:48 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 11    06/08/22 16:59 Tsujimura543
 * enum authenticationType �̒�`�� myClip.h ���Ɉڂ���
 * 
 * 10    06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 9     06/07/31 18:03 Tsujimura543
 * (1) ��M�o�b�t�@�I�[�o�[�����h�~�@�\��g�ݍ���
 * (2) login1470net() �� login �Ď��s�Ԋu�� 2�b �ɕύX
 * 
 * 8     06/07/24 19:23 Tsujimura543
 * login1470net() ���ŁA��M�d���i�[�̈�̑|�����Y�ꂪ�������̂��C��
 * 
 * 7     06/07/18 20:47 Tsujimura543
 * �R�����g�̏C��
 * 
 * 6     06/07/18 15:26 Tsujimura543
 * MM/Memo �� 1470.net ���j���[�A���łւ̓����o�^���s���A�ǂ��炩�������
 * �o�^�ł��Ȃ����Ƃ����錏�ɑΏ�����(login���̃L���b�V����j������@�\
 * ��ǉ����邱�ƂőΏ�)
 * 
 * 5     06/07/15 0:42 Tsujimura543
 * login1470net() ��ǉ�
 * 
 * 4     06/07/12 15:51 Tsujimura543
 * 64 �� MAX_KEYLENGTH �ɒu��
 * 
 * 3     06/06/19 20:42 Tsujimura543
 * �C���f���g�C��
 * 
 * 2     06/05/22 18:56 Tsujimura543
 * MM/Memo �ɑ΂��鑀��̂��т� TypeKey ���擾�������̂�������邽�߁A
 * �L���b�V���𓱓�����
 * 
 * 1     05/10/19 16:46 Tsujimura543
 * getMMmemo.c ���番���A�Ɨ�������
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/mmMemo.c 1     09/05/14 3:48 tsupo $";
#endif

/* MM/Memo �Ƀ��O�C������ */
int
_loginMMmemo( const char *username,     // (I)   TypeKey���[�U��
              const char *password,     // (I)   TypeKey�p�X���[�h
              char       *cookie,       // (I/O) �N�b�L�[
              char       *userID,       // (O)   MM/Memo ���[�UID
              int        stackCount )   // (I)   
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];
    char    cookie2[MAX_COOKIE_LEN];
    char    key[MAX_KEYLENGTH];
    char    token[MAX_LOGICALLINELEN];
    size_t  sz;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static char     saveUserID[MAX_NAMELEN];
    static time_t   firstTime = 0;
    BOOL            refresh = FALSE;

    if ( !username ) {
        /* �L���b�V���N���A */
        firstTime = 0;
        return ( ret );
    }
    login1470net( NULL, NULL, NULL, NULL, AK_ORIGINAL, NULL, NULL );
                                    /* login1470net()���̃L���b�V�����N���A */
    if ( !cookie )
        return ( ret );

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
        saveUserID[0]   = NUL;
    }
    else {
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

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        firstTime = 0;
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( cookie2, 0x00, MAX_COOKIE_LEN );

    strcpy( url, "http://mmmemo.1470.net/mm/mylist.html" );
    setTargetURL( url );

    key[0]   = NUL;
    token[0] = NUL;
    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( !p || !(*p) ) {
        char    url2[MAX_URLLENGTH];
        char    *q, *r;

        getCurrentLocation( url2 );
        q = strstr( url2, "t=" );
        if ( !q ) {
            q = strstr( url2, "typekey_token=" );
            if ( q )
                q += 12; /* 12 (= 14 - 2) */
        }
        if ( q ) {
            q += 2;
            r = strchr( q, '&' );
            if ( r ) {
                strncpy( key, q, r - q );
                key[r - q] = NUL;
            }
        }
    }
    else {
        char    *q, *r;

        // MM/Memo �̌��J�����擾 (TypePad Connect �F�ؗp login �y�[�W�̉��)
        key[0] = NUL;
        q = strstr( p, "<input type=\"hidden\" name=\"t\"" );
        if ( !q ) {
            q = strstr( p, "<input type=\"hidden\" name=\"typekey_token\"" );
            if ( q )
                q += 12; /* 12 (= 41 - 29) */
        }
        if ( q ) {
            q += 29;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( key, r, q - r );
                    key[q - r] = NUL;
                }
            }
        }

        p = response;
        token[0] = NUL;
        q = strstr( p,
              "<input type=\"hidden\" id=\"password-token\" name=\"token\"");
        if ( q ) {
            q += 53;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( token, r, q - r );
                    token[q - r] = NUL;
                }
            }
        }
    }
    if ( key[0] && token[0] ) {
        // TypePad Connect �F��
        strcpy( url, "https://www.typepad.com/secure/services/signin/save" );
        sprintf( request,
                 "token=%s&"
                 "resp=&"
                 "to=%s&"
                 "is_typekey=1&",
                 token,
                 encodeURL( "http://mmmemo.1470.net/login" ) );
        sprintf( request + strlen( request ),
                 "typekey_token=%s&"
                 "typekey_version=1.1&"
                 "username=%s&"
                 "password=%s&"
                 "remember=1",
                 key, username, password );
        setUpReceiveBuffer( response, sz );
        p = http_postEx2( url, "application/x-www-form-urlencoded",
                          request, response, cookie2,
                          "http://mmmemo.1470.net/", cookie );
        if ( !p || !(*p) )
            ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
        else {
            // TypeKey �F�؎��s��� redirect ��� Web �y�[�W�̓��e�����
            char        *q, *r;
            const char  *targetString = "<link rel=\"alternate\" "
                                        "type=\"application/rss+xml\" "
                                        "title=\"RSS\" href=\"http://";
            if ( strstr( p, "RETRY" ) != NULL ) {
                stackCount++;
                if ( stackCount >= 6 ) {
                    // �X�^�b�N�I�[�o�[�t���[(+ �������[�v)�h�~
                    return ( ret );
                }

                Sleep( 5000 );  // 5�b�҂��Ă��烊�g���C
                firstTime = 0;
                memset( cookie, 0x00, MAX_COOKIE_LEN );
                ret = _loginMMmemo( username, password, cookie, userID,
                                    stackCount );
                stackCount--;
            }
            else if ( ( q = strstr( p, targetString ) ) != NULL ) {
                q += strlen( targetString );
                r = strstr( q, "mylist.html/" );
                if ( r )
                    q = r + 12;
                r = strchr( q, '?' );
                if ( r ) {
                    strncpy( userID, q, r - q );
                    userID[r - q] = NUL;
                }
                ret = 1;    /* ���O�C������ */
            }
            else
                ret = 0;    /* ���O�C�����s */
        }
    }
    else
        ret = 0;    /* ���O�C�����s */

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        strcpy( saveUserName, username );
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

int
loginMMmemo( const char *username,  // (I)   TypeKey���[�U��
             const char *password,  // (I)   TypeKey�p�X���[�h
             char       *cookie,    // (I/O) �N�b�L�[
             char       *userID )   // (O)   MM/Memo ���[�UID
{
    int stackCount = 0;

    return ( _loginMMmemo( username, password, cookie, userID, stackCount ) );
}

int
login1470netViaTypeKey(
        const char *username,   // (I)   TypeKey���[�U��
        const char *password,   // (I)   TypeKey�p�X���[�h
        char       *request,    // (I/O) request  �i�[�̈�
        char       *response,   // (I/O) response �i�[�̈�
        size_t     sz,          // (I)   response �i�[�̈�̃T�C�Y
        char       *cookie,     // (I/O) �N�b�L�[
        char       *userID      // (O)   1470.net���j���[�A���� ���[�U��
    )
{
    int     ret = 0;
    char    url[MAX_URLLENGTH];
    char    cookie2[MAX_COOKIE_LEN];
    char    *p;

    memset( cookie2, 0x00, MAX_COOKIE_LEN );

    strcpy( url, "http://1470.net/tools/" );
    setTargetURL( url );

    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( p && *p ) {
        char    key[MAX_KEYLENGTH];
        char    token[MAX_LOGICALLINELEN];
        char    *q, *r;

        // PHPSESSID=
        q = strstr( cookie, "; PHPSESSID=" );
        if ( q )
            strcpy( q, "\r\n" );

        key[0]   = NUL;
        token[0] = NUL;
        q = strstr(p, "<a href=\"https://www.typekey.com/t/typekey/login?t=");
        if ( q ) {
            p = q + 9;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( url, p, q - p );
                url[q - p] = NUL;

                q = strstr( url, "t=" );
                if ( !q ) {
                    q = strstr( url, "typekey_token=" );
                    if ( q )
                        q += 12; /* 12 (= 14 - 2) */
                }
                if ( q ) {
                    q += 2;
                    r = strchr( q, '&' );
                    if ( r ) {
                        strncpy( key, q, r - q );
                        key[r - q] = NUL;
                    }
                }

                setUpReceiveBuffer( response, sz );
                p = http_getEx( url, response, cookie2 );
                if ( !p )
                    return ( ret );
            }
        }

        // 1470.net �̌��J�����擾 (TypePad Connect �F�ؗp login �y�[�W�̉��)
        p = response;
        q = strstr( p, "<input type=\"hidden\" name=\"typekey_token\"" );
        if ( q ) {
            q += 41;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( key, r, q - r );
                    key[q - r] = NUL;
                }
            }
        }

        p = response;
        q = strstr( p,
              "<input type=\"hidden\" id=\"password-token\" name=\"token\"");
        if ( q ) {
            q += 53;
            r = strstr( q, "value=\"" );
            if ( r ) {
                r += 7;
                q = strchr( r, '"' );
                if ( q ) {
                    strncpy( token, r, q - r );
                    token[q - r] = NUL;
                }
            }
        }

        // TypePad Connect �F��
        strcpy( url, "https://www.typepad.com/secure/services/signin/save" );
        sprintf( request,
                 "token=%s&"
                 "resp=&"
                 "to=%s&"
                 "is_typekey=1&",
                 token,
                 encodeURL( "http://1470.net/tools/" ) );
        sprintf( request + strlen( request ),
                 "typekey_token=%s&"
                 "typekey_version=1.1&"
                 "username=%s&"
                 "password=%s&"
                 "remember=1",
                 key,
                 username, password );
        setUpReceiveBuffer( response, sz );
        p = http_postEx2( url, "application/x-www-form-urlencoded",
                          request, response, cookie2,
                          "http://1470.net/", cookie );
        if ( !p || !(*p) )
            ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
        else {
            // TypeKey �F�؎��s��� redirect ��� Web �y�[�W�̓��e�����
            char    *q;
            int     retry = 0;
            if ( strstr( p, sjis2utf("���O�C���ɐ������܂���") ) ) {
                const char  *targetString = "<meta http-equiv=\"refresh\" "
                                            "content=\"1; url=";
                url[0] = NUL;
                q = strstr( p, targetString );
                if ( q ) {
                    p = q + strlen( targetString );
                    q = strstr( p, "\">" );
                    if ( q ) {
                        strcpy( url, "http://1470.net" );
                        strncat( url, p, q - p );
                        url[15 + (q - p)] = NUL;
                        while ( (q = strstr( url, "&amp;" )) != NULL )
                            strcpy( q + 1, q + 5 );
                    }
                }

                do {
                    if ( url[0] == NUL )
                        strcpy( url, "http://1470.net/tools/" );
                    setTargetURL( url );
                    Sleep( 1000 );

                    setUpReceiveBuffer( response, sz );
                    p = http_getEx( url, response, cookie );
                            // ����: �Ȃ����A���� url ��2�� GET ���Ȃ���
                            //       userID ��������y�[�W�ւ��܂� redirect
                            //       ����Ȃ�
                    if ( p && *p ) {
                        q = strstr( p, "<a href=\"/user/" );
                        if ( q ) {
                            p = q + 15;
                            q = strstr( p, "/\">" );
                            if ( q ) {
                                strncpy( userID, p, q - p );
                                userID[q - p] = NUL;
                            }
                        }
                    }

                    if ( userID[0] )
                        ret = 1;    /* ���O�C������ */
                    else {
                        ret = 0;    /* ���O�C�����s */
                        retry++;
                        if ( retry > 5 )
                            break;
                        Sleep( 2000 );
                    }
                } while ( ret == 0 );
            }
            else
                ret = 0;    /* ���O�C�����s */
        }
    }
    else
        ret = 0;    /* ���O�C�����s */

    return ( ret );
}


int
login1470netViaHatena(
        const char *username,   // (I)   �͂Ă�ID
        const char *password,   // (I)   �͂Ăȃp�X���[�h
        char       *request,    // (I/O) request  �i�[�̈�
        char       *response,   // (I/O) response �i�[�̈�
        size_t     sz,          // (I)   response �i�[�̈�̃T�C�Y
        char       *cookie,     // (I/O) �N�b�L�[
        char       *userID      // (O)   1470.net���j���[�A���� ���[�U��
    )
{
    int     ret = 0;
    char    url[MAX_URLLENGTH];
    char    targetURL[MAX_URLLENGTH];
    char    *p;

    strcpy( url, "http://1470.net/tools/" );
    setTargetURL( url );

    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( p && *p ) {
        char    api_key[MAX_KEYLENGTH];
        char    api_sig[MAX_KEYLENGTH];
        char    *q, *r;

        // 1470.net �� api_key �� api_sig ���擾
        api_key[0] = NUL;
        api_sig[0] = NUL;
        q = strstr( p, "http://auth.hatena.ne.jp/auth?api_key=" );
        if ( q ) {
            q += 38;
            r = strstr( q, "&amp;api_sig=" );
            if ( r ) {
                strncpy( api_key, q, r - q );
                api_key[r - q] = NUL;

                q = r + 13;
                r = strstr( q, "\">" );
                if ( r ) {
                    strncpy( api_sig, q, r - q );
                    api_sig[r - q] = NUL;
                }
            }
        }

        sprintf( targetURL,
                 "http://auth.hatena.ne.jp/auth?api_key=%s&api_sig=%s",
                 api_key, api_sig );

        // �͂ĂȔF��API
        strcpy( url, "https://www.hatena.ne.jp/login" );
        sprintf( request,
                 "name=%s&"
                 "password=%s&",
                 username, password );
        sprintf( request + strlen( request ),
                 "persistent=1&"
                 "location=%s&",
                 encodeURL( targetURL ) );

        setUpReceiveBuffer( response, sz );
        p = http_postEx( url, "application/x-www-form-urlencoded",
                         request, response, cookie );

        if ( !p || !(*p) )
            ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
        else {
            // �͂ĂȔF�؎��s��� redirect ��� Web �y�[�W�̓��e�����
            char    *q;
            int     retry = 0;

            Sleep( 1000 );
            setUpReceiveBuffer( response, sz );
            p = http_getEx( targetURL, response, cookie );
            if ( p && strstr( p, sjis2utf("���O�C���ɐ������܂���") ) ) {
                const char  *targetString = "<meta http-equiv=\"refresh\" "
                                            "content=\"1; url=";
                url[0] = NUL;
                q = strstr( p, targetString );
                if ( q ) {
                    p = q + strlen( targetString );
                    q = strstr( p, "\">" );
                    if ( q ) {
                        strcpy( url, "http://1470.net" );
                        strncat( url, p, q - p );
                        url[15 + (q - p)] = NUL;
                        while ( (q = strstr( url, "&amp;" )) != NULL )
                            strcpy( q + 1, q + 5 );
                    }
                }

                do {
                    if ( url[0] == NUL )
                        strcpy( url, "http://1470.net/tools/" );
                    setTargetURL( url );
                    Sleep( 1000 );

                    setUpReceiveBuffer( response, sz );
                    p = http_getEx( url, response, cookie );
                    if ( p && *p ) {
                        q = strstr( p, "<a href=\"/user/" );
                        if ( q ) {
                            p = q + 15;
                            q = strstr( p, "/\">" );
                            if ( q ) {
                                strncpy( userID, p, q - p );
                                userID[q - p] = NUL;
                            }
                        }
                    }

                    if ( userID[0] )
                        ret = 1;    /* ���O�C������ */
                    else {
                        ret = 0;    /* ���O�C�����s */
                        retry++;
                        if ( retry > 5 )
                            break;
                        Sleep( 2000 );
                    }
                } while ( ret == 0 );
            }
            else
                ret = 0;    /* ���O�C�����s */
        }
    }
    else
        ret = 0;    /* ���O�C�����s */

    return ( ret );
}

/* 1470.net���j���[�A���� �Ƀ��O�C������ */
int
login1470net(
        const char *username,   // (I)   TypeKey���[�U��
        const char *password,   // (I)   TypeKey�p�X���[�h
        const char *username2,  // (I)   �͂Ă�ID
        const char *password2,  // (I)   �͂Ăȃp�X���[�h
        AUTH_TYPE  authType,    // (I)   �F�؎�� (TypeKey, �͂ĂȔF��API)
        char       *cookie,     // (I/O) �N�b�L�[
        char       *userID      // (O)   1470.net���j���[�A���� ���[�U��
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    size_t  sz;

    static char     saveUserName[MAX_USERIDLEN + 1];
    static char     savePassword[MAX_PASSWDLEN + 1];
    static char     saveCookie[MAX_COOKIE_LEN];
    static char     saveUserID[MAX_NAMELEN];
    static int      saveAuthType = AK_ORIGINAL;
    static time_t   firstTime    = 0;
    BOOL            refresh = FALSE;

    if ( !username ) {
        /* �L���b�V���N���A */
        firstTime = 0;
        return ( ret );
    }
    loginMMmemo( NULL, NULL, NULL, NULL );
                                    /* loginMMmemo()���̃L���b�V�����N���A */

    if ( !cookie )
        return ( ret );

    if ( firstTime == 0 ) {
        firstTime = time( NULL );
        refresh   = TRUE;
    }
    else {
        time_t  now = time( NULL );
        if ( now - firstTime >= 1 * 60 * 60 )
            refresh = TRUE; /* �L���b�V���̗L�����Ԃ�1���ԂƂ��� */
        else if ( ( strcmp( username, saveUserName ) != 0 ) ||
                  ( strcmp( password, savePassword ) != 0 ) ||
                  ( authType != saveAuthType )                 )
            refresh = TRUE;
    }

    if ( refresh == TRUE ) {
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveAuthType    = AK_ORIGINAL;
    }
    else {
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

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        firstTime = 0;
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    userID[0] = NUL;

    if ( (authType == AK_TYPEKEY) || (authType == AK_TYPEKEY_HATENA) ) {
        ret = login1470netViaTypeKey( username, password, request, response,
                                      sz, cookie, userID );
    }
    if ( (ret == 0)                            &&
         ((authType == AK_HATENA)         ||
          (authType == AK_HATENA_TYPEKEY) ||
          (authType == AK_TYPEKEY_HATENA)    )    ) {
        memset( request, 0x00, MAX_CONTENT_SIZE );
        userID[0] = NUL;
        ret = login1470netViaHatena( username2, password2, request, response,
                                     sz, cookie, userID );
    }
    if ( (ret == 0) && (authType == AK_HATENA_TYPEKEY) ) {
        memset( request, 0x00, MAX_CONTENT_SIZE );
        userID[0] = NUL;
        ret = login1470netViaTypeKey( username, password, request, response,
                                      sz, cookie, userID );
    }

    free( response );
    free( request  );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        strcpy( saveUserName, username );
        strcpy( savePassword, password );
        strcpy( saveCookie, cookie );
        strcpy( saveUserID, userID );
        saveAuthType = authType;
    }
    else {
        /* �L���b�V����j�� */
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
        saveUserID[0]   = NUL;
        saveAuthType    = AK_ORIGINAL;
        firstTime       = 0;
    }

    return ( ret );
}

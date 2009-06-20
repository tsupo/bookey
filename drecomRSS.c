/*
 *  drecomRSS.c
 *      �h���R��RSS �� login ����
 *          written by H.Tsujimura  28 Mar 2006
 *
 * $Log: /comm/bookey/drecomRSS.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    08/11/18 1:14 Tsujimura543
 * ���O�C�������ɃL���b�V���𓱓�
 * 
 * 10    07/05/22 17:57 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 9     07/04/16 20:19 Tsujimura543
 * �܂��܂��A�����Ƀh���R��RSS(�Ƃ������h���R���A�J�E���g)�̎d�l���ς����
 * ���邱�Ƃ������A�Ή�����
 * 
 * 8     07/04/12 15:25 Tsujimura543
 * 2007�N4��12���̃h���R��RSS���j���[�A���ɑΉ�
 * 
 * 7     07/02/15 15:54 Tsujimura543
 * __ticket__ �̓T�[�o���� cookie �Ɋi�[����d�l�ɕύX���ꂽ�͗l
 * (2007�N1��17���Ɏd�l�ύX���ꂽ?)�B�O�̂��߁Acookie �� __ticket__
 * ���i�[�ς݂��m�F���A�i�[����Ă��Ȃ��ꍇ�̂݁A__ticket__�擾�A��
 * ����s�Ȃ��悤�ɂ��� (���̏������́A����͕s�v��������Ȃ�)
 * 
 * 6     07/01/17 17:54 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 5     06/09/12 14:00 Tsujimura543
 * Visual C++ 6 / Visual C++ 2005 �̗����Ŗ��Ȃ��r���h�ł��邱�Ƃ��m�F
 * 
 * 4a    06/09/12 5:17 tsupo
 * MessageBox() �� ascii �o�[�W���� / wide char �o�[�W�����̂ǂ���ł�
 * warning �Ȃ��ŃR���p�C���ł���悤�ɂ��� (for Visual Studio 2005)
 * 
 * 4     06/07/31 17:36 Tsujimura543
 * ���g���C�񐔂�5��ɂ���
 * 
 * 3     06/07/25 18:26 Tsujimura543
 * �h���R���A�J�E���g(2006�N7��25���ғ��J�n)�ɑΉ�
 * 
 * 2     06/07/18 21:40 Tsujimura543
 * login ���s���A�ő�3��܂ōĎ��s����悤�ɂ��Ă݂�
 * 
 * 1     06/03/28 17:08 Tsujimura543
 * putDrecomRSS.c ���番���A�Ɨ�������
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/drecomRSS.c 1     09/05/14 3:48 tsupo $";
#endif


/* �h���R��RSS �� login ���� */
int
loginDrecomRSS(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
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
            dputs( "loginDrecomRSS(): �L���b�V����j��\n" );
        firstTime = time( NULL );
        saveUserName[0] = NUL;
        savePassword[0] = NUL;
        saveCookie[0]   = NUL;
    }
    else {
        dputs( "loginDrecomRSS(): �L���b�V���𗘗p\n" );
        strcpy( cookie, saveCookie );
        ret = 1;    /* ���O�C������ */
        return ( ret );
    }

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) {
        firstTime = 0;
        return ( ret );
    }

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response ) {
        firstTime = 0;
        free( request );
        return ( ret );
    }

    do {
        memset( request,  0x00, MAX_CONTENT_SIZE );
        setUpReceiveBuffer( response, sz );

        /* ���O�C���y�[�W���擾 */
        strcpy( url, "http://rss.drecom.jp/logging/re" );
        cookie[0] = NUL;
        http_getEx( url, response, cookie );
        if ( *response ) {
            /* iframe �Ŏw������Ă��� login form �� GET */
            char    *p = strstr( response, "<iframe src=\"" );
            if ( p ) {
                char    *q;

                p += 13;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;

                    setUpReceiveBuffer( response, sz );
                    http_getEx( url, response, cookie );
                    if ( *response ) {
                        char    appKey[64];
                        char    sig[64];

                        /* applicationKey �� signature ���擾 */
                        appKey[0] = NUL;
                        sig[0]    = NUL;
                        p = strstr( response, " name=\"app_key\" " );
                        if ( p ) {
                            p += 16;
                            q = strstr( p, "value=\"" );
                            if ( q ) {
                                p = q + 7;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    strncpy( appKey, p, q - p );
                                    appKey[q - p] =  NUL;
                                }
                            }
                        }

                        p = strstr( p ? p : response, " name=\"sig\" " );
                        if ( p ) {
                            p += 12;
                            q = strstr( p, "value=\"" );
                            if ( q ) {
                                p = q + 7;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    strncpy( sig, p, q - p );
                                    sig[q - p] =  NUL;
                                }
                            }
                        }

                        if ( !(appKey[0]) || (!sig[0]) )
                            break;

                        /* �h���R���A�J�E���g�փT�C���C�� */
                        sprintf( request,
                                 "app_key=%s&"
                                 "from=&"
                                 "method=frame_signin&"
                                 "sig=%s&"
                                 "account[name]=%s&"
                                 "account[password]=%s&"
                                 "account[remember]=1&"
                                 "commit=%s",
                                 appKey,
                                 sig,
                                 userName, password,
                                 "Click+Login" );
                        strcpy(url, "https://account.drecom.jp/frame/signin");
                        setUpReceiveBuffer( response, sz );
                        http_postEx( url,
                                     "application/x-www-form-urlencoded",
                                     request, response, cookie );
                        if ( *response ) {
                            /* �h���R���A�J�E���g���L���ɂȂ��Ă��邩 */
                            /* �ǂ������m�F                           */
                            if ( strstr( response,
                                         "https://account.drecom.jp/"
                                         "questionnaire" ) ) {
                                DWORD   langCode = getLanguageCode();

                                if ( langCode == 0x0411 ) {
                                    // ���{��
                                    MessageBox( NULL,
                                      (LPCTSTR)
                                      "�h���R���A�J�E���g�ւ̓o�^�E�ڍs�葱"
                                      "�����܂��I����Ă��܂���B\r\n"
                                      "�葱�����s�Ȃ��Ă����Ă��������B  ",
                                      (LPCTSTR)
                                      "�h���R���A�J�E���g�ւ̓o�^�E�ڍs����"
                                      "�Ă�������",
                                                MB_OK|MB_ICONERROR );
                                }
                                else {
                                    // �p��
                                    MessageBox( NULL,
                                           "You should get a Drecom Account.",
                                                "Get your Drecom Account",
                                                MB_OK|MB_ICONERROR );
                                }
                                break;
                            }

                            if ( !strstr( cookie, "__ticket__" ) ) {
                                /* ticket ���擾���Acookie �ɖ��ߍ��� */
                                p = strstr( response,
                                            "\"__ticket__\",\"=\",escape(\"" );
                                if ( p ) {
                                    char    ticket[64];

                                    p += 25;
                                    q = strchr( p, '"' );
                                    strncpy( ticket, p, q - p );
                                    ticket[q - p] = NUL;

                                    p = strchr( cookie, '\r' );
                                    if ( p )
                                        sprintf( p, "; __ticket__=%s\r\n",
                                                 ticket );
                                }
                            }

                            /* �ŏI�I�ȃ��O�C���y�[�W(���O�C����̃g�b�v */
                            /* �؁[�W)���擾                             */
                            p = strstr( response,
                                        "parent.location.href = \"" );
                            if ( p ) {
                                p += 24;
                                q = strchr( p, '"' );
                                strncpy( url, p, q - p );
                                url[q - p] = NUL;

                                setUpReceiveBuffer( response, sz );
                                http_getEx( url, response, cookie );
                                if ( *response ) {
                                    if ( (strstr( response,
                                       "https://account.drecom.jp/signout"
                                               ) != NULL) ||
                                         (strstr( response, "/logging/out"
                                               ) != NULL)    ) {
                                        ret = 1;    /* login ���� */
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        retry--;
        if ( retry <= 0 )
            break;
        Sleep( 2000 );
    } while ( ret == 0 );

    free( response );
    free( request );

    if ( ret == 1 ) {
        /* �L���b�V���ɕۑ� */
        dputs( "loginDrecomRSS(): ���O�C�������A�L���b�V���ɕۑ�\n" );
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

/*
 * clip loader <<putFC2bookmark>>
 *
 *      OPML �� FC2BOOKMARK �o�^�v���O����
 *          written by H.Tsujimura  29 Mar 2007
 *
 * History:
 * $Log: /comm/bookey/putFC2bookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    08/08/12 12:57 Tsujimura543
 * _putFC2Bookmark() ���̓��e����/���s�����������������
 * 
 * 14    07/10/05 4:18 Tsujimura543
 * putFC2Bookmark() ���Ŋm�ۂ��Ă��� cookie �̃T�C�Y��1�o�C�g����������
 * 
 * 13    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 12    07/09/26 18:41 Tsujimura543
 * �o�^�ς݂̃u�b�N�}�[�N�̏㏑���ɂ��Ă��A�V�����d�l�̌��ł̓����
 * �m�F����
 * 
 * 11    07/09/26 18:31 Tsujimura543
 * 2007�N9��20���̎d�l�ύX(�u�b�N�}�[�N�o�^���̈����̒ǉ��A�ύX�A��)
 * �ɑΉ�
 * 
 * 10    07/08/24 1:18 Tsujimura543
 * FC2BOOKMARK �̃y�[�W�f�U�C���ύX�ɑΉ�
 * 
 * 9     07/06/08 21:06 Tsujimura543
 * �T�[�o�� Proxy Error ��Ԃ��Ă����Ƃ��̑΍������
 * 
 * 8     07/05/11 18:43 Tsujimura543
 * normalizeDescription() ���C��
 * 
 * 7     07/04/10 17:07 Tsujimura543
 * normalizeDescription() ���C�� (�Ō�� any2utf() ���Y��Ă���)
 * 
 * 6     07/04/10 16:58 Tsujimura543
 * �p�ꃂ�[�h���ɕ\������G���[���b�Z�[�W�̕������C��
 * 
 * 5     07/03/30 22:14 Tsujimura543
 * �R�����g��255������蒷���ꍇ�́A�Z�����Ă���o�^����悤�ɂ���
 * 
 * 4     07/03/30 20:55 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 3     07/03/30 20:14 Tsujimura543
 * ���łɓo�^�ς݂�Web�y�[�W������ɓo�^���悤�Ƃ����ꍇ�́A�㏑���o�^
 * �ł���悤�ɂ��� (�㏑�����Ă悢���u���Ă���㏑���o�^����)
 * 
 * 2     07/03/30 15:37 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     07/03/29 15:06 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putFC2bookmark.c 1     09/05/14 3:48 tsupo $";
#endif


#define MAX_DESCRIPTION_LENGTH          765
#define MAX_DESCRIPTION_BYTES_IN_SJIS   (255 * 2)
          // UTF-8��255�����ȉ� �� 765�o�C�g(Shift_JIS �� 255 * 2 �o�C�g)�ȉ�
          //   -- 255���� * 3 = 765 �o�C�g (�����锼�p�p�������܂܂��
          //                                ���Ȃ��Ɖ��肵���ꍇ)

static char *
normalizeDescription( char *description )
{
    char    *p;

    if ( strlen( description ) > MAX_DESCRIPTION_BYTES_IN_SJIS ) {
        char    *s = description;
        int     kanjiFlag = 0;
        int     i = 0;

        while ( *s ) {
            if ( ++i > MAX_DESCRIPTION_BYTES_IN_SJIS )
                break;
            if ( kanjiFlag == 0 ) {
                if ( iskanji1( *s ) )
                    kanjiFlag = 1;
            }
            else
                kanjiFlag = ((kanjiFlag + 1) % 3);
            *s++;
        }
        switch ( kanjiFlag ) {
        case 0:
            *s = NUL;
            break;
        case 1:
            *(s - 1) = NUL;
            break;
        case 2:
            *(s - 2) = NUL;
            break;
        }
    }

    p = any2utf( description );

    return ( p ? p : description );
}


BOOL
searchFC2Bookmark(
    const char  *targetURL,
    char        *cookie,
    char        *entryID,
    char        *response,
    size_t      sz )
{
    char    url[MAX_URLLENGTH];
    BOOL    found = FALSE;
    BOOL    cont  = TRUE;
    char    *p, *q, *r;
    char    tmp[MAX_DESCRIPTION_LEN * 2];
    char    target[MAX_URLLENGTH];

    target[0] = NUL;
    strcpy( url,    "http://bookmark.fc2.com/user" );
    strcpy( target, "http://bookmark.fc2.com/user" );

    do {
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        // �u�b�N�}�[�N�𔲂��o��
        p = response;
        do {
            q = strstr( p, "<div id=\"b-" );
            if ( !q )
                break;
            p = q + 11;
            q = strstr( p, "<h4>" );
            if ( !q )
                break;

            // URL
            p = q + 4;
            q = strstr( p, "<a href=\"" );
            if ( !q )
                break;
            q += 9;
            r = strstr( q, "\">" );
            if ( !r )
                break;
            strncpy( tmp, q, r - q );
            tmp[r - q] = NUL;
            if ( !strcmp( tmp, targetURL ) ) {
                // �G���g��ID
                q = strstr( p, "_bookmark/" );
                if ( q ) {
                    p = q + 10;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( tmp, p, q - p );
                        tmp[q - p] = NUL;
                        strcpy( entryID, tmp );
                        p = q + 1;
                    }
                }

                found = TRUE;
                break;
            }

            p = strstr( p, "</table>" );
            if ( p )
                p += 8;
        } while ( p && *p );

        if ( found )
            break;

        // ����
        cont = FALSE;
        q = strstr( p, "<div class=\"pagenation\">" );
        if ( !q )
            q = strstr( p, "<div class=\"pagination\">" );
        if ( q ) {
            p = q + 24;
            q = strstr( p, sjis2utf("\">����") );
            if ( !q )
                q = strstr( p, sjis2utf(">&raquo;����") );
            if ( q ) {
                while ( (q >= response) && (*q != '?') )
                    q--;
                if ( *q == '?' ) {
                    char    page[MAX_URLLENGTH];
                    p = strchr( q, '"' );
                    if ( p ) {
                        strncpy( page, q, p - q );
                        page[p - q] = NUL;
                        sprintf( url, "%s%s", target, page );
                        cont = TRUE;
                        Sleep( 1000 );
                    }
                }
            }
        }
    } while ( cont );

    return ( found );
}

char    *
getKeyForFC2bookmark( char *key, char *response, size_t sz, char *cookie )
{
    const char  *url = "http://bookmark.fc2.com/user/new_bookmark";

    key[0] = NUL;
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        const char  *p, *q;
        p = strstr( response, "name=\"data[key]\"" );
        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( key, p, q - p );
                    key[q - p] = NUL;
                }
            }
        }
        setReferer( url );
    }

    return ( key );
}

#define FC2_ADD_BOOKMARK        1
#define FC2_UPDATE_BOOKMARK     2

void
makeRequestForFC2bookmark(
        const MyClip *mp,
        const char   *key,
        char         *request,
        int          mode
    )
{
    char    *p;
    char    *temp = NULL;

    // �^�C�g��
    p = any2utf( mp->title );
    sprintf( request,
             "data[Bookmark][title]=%s&",
             encodeURL( p ? p : mp->title ) );

    // URL
    sprintf( request + strlen(request),
             "data[Bookmark][url]=%s&",
             encodeURL( mp->url ) );

    // ����
    p = any2utf( mp->comment );
    if ( p ) {
        size_t  len = strlen( p );
        if ( len >= MAX_DESCRIPTION_LENGTH ) {
            temp = (char *)malloc( len + 1 );
            if ( temp ) {
                char    *q;

                strcpy( temp, p );
                q = utf2sjis( temp );
                if ( q ) {
                    strcpy( temp, q );
                    p = normalizeDescription( temp );
                }
                else
                    p = any2utf( mp->title );
            }
        }
    }
    sprintf( request + strlen(request),
             "data[Bookmark][description]=%s&",
             encodeURL( p ? p : mp->comment ) );
    if ( temp )
        free( temp );

    // �^�O (�X�y�[�X��؂�)
    p = any2utf( mp->tags );
    sprintf( request + strlen(request),
             "data[Bookmark][tag_txt]=%s&",
             encodeURL( p ? p : mp->tags ) );

    // mode
    switch ( mode ) {
    case FC2_ADD_BOOKMARK:
        sprintf( request + strlen(request),
                 "data[commit]=%s&",
                 encodeURL(sjis2utf("�ǉ�")) );
        break;
    case FC2_UPDATE_BOOKMARK:
        sprintf( request + strlen(request),
                 "data[commit]=%s&",
                 encodeURL(sjis2utf("�X�V")) );
        break;
    }

    // ���J�E����J
    sprintf( request + strlen(request),
             "data[Bookmark][allow_access]=0&"
             "data[Bookmark][allow_access]=%d&"
#ifdef  BEFORE_20070920
             "data[Bookmark][favorite]=0&"  // �悭�g���A�C�e���ɒǉ�: off
             "data[Bookmark][adult]=0",     // 18�Ζ����ɂ͕\�����Ȃ�: off
#else
             "data[Bookmark][favorite]=0",  // �悭�g���A�C�e���ɒǉ�: off
                                // R18�ȃu�b�N�}�[�N�͖������œo�^�֎~�ɂȂ���
#endif
             mp->publication == PUB_EVERYONE ? 1 : 0 );

    // key (2007�N9��20���ɒǉ����ꂽ�p�����[�^)
    if ( key && *key )
        sprintf( request + strlen(request),
                 "&data[key]=%s", key );
}

void
refineRequestForFC2bookmark( char *request )
{
    char    *p, *q;

    while ( (p = strchr( request, '[' )) != NULL ) {
        q = p + strlen( p );
        while ( q > p ) {
            *(q + 2) = *q;
            q--;
        }
        if ( q == p ) {
            *q++ = '%';
            *q++ = '5';
            *q++ = 'B';
        }
    }

    while ( (p = strchr( request, ']' )) != NULL ) {
        q = p + strlen( p );
        while ( q > p ) {
            *(q + 2) = *q;
            q--;
        }
        if ( q == p ) {
            *q++ = '%';
            *q++ = '5';
            *q++ = 'D';
        }
    }
}

void
getErrorStringForFC2bookmark( const char *response, char *errorString )
{
    char    *p;
    char    *q;

    errorString[0] = NUL;
    p = strstr( response,
                "<p id=\"flash-message\" class=\"info\">" );
    if ( p ) {
        p += 35;
        q = strstr( p, "</p>" );
        if ( q ) {
            strncpy( errorString, p, q - p );
            errorString[q - p] = NUL;
            p = utf2sjis( errorString );
            if ( p )
                strcpy( errorString, p );
        }
    }
    else {
        p = strstr( response,
                    "<div class=\"errorExplanation\" "
                    "id=\"errorExplanation\">" );
        if ( p ) {
            p += 52;
            q = strstr( p, "<ul><li>" );
            if ( !q )
                q = strstr( p, "<li>" );
            if ( q ) {
                p = strstr( p, "<li>" ) + 4;
                q = strstr( p, "</li>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString, p );
                }
            }
            else {
                q = strstr( p, "</div>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString, p );
                    deleteHtmlTags( errorString );
                }
            }
        }
        else {
            p = strstr( response,
                        "<h1>Proxy Error</h1>" );
            if ( p )
                strcpy( errorString, "Proxy Error" );
            else {
                p = strstr( response, "<div id=\"content\">" );
                if ( p ) {
                    p += 18;
                    q = strstr( p, "<h2>" );
                    if ( q ) {
                        p = q + 4;
                        q = strstr( p, "</h2>" );
                        if ( q ) {
                            strncpy( errorString, p, q - p );
                            errorString[q - p] = NUL;
                            p = utf2sjis( errorString );
                            if ( p )
                                strcpy( errorString, p );
                        }
                    }
                }
            }
        }
    }

    if ( errorString[0] == NUL )
        strcpy( errorString, "���炩�̃G���[���������܂���" );
    else if ( !strcmp( errorString, "Proxy Error" ) )
        errorString[0] = NUL;
}

BOOL
editFC2bookmark(
        const MyClip *mp,
        char         *cookie,
        char         *errorString,
        char         *request,
        char         *response,
        size_t       sz )
{
    char    entryID[MAX_KEYLENGTH];
    BOOL    found = FALSE;
    BOOL    ret   = FALSE;

    entryID[0] = NUL;
    found = searchFC2Bookmark( mp->url, cookie, entryID, response, sz );
    if ( found ) {
        char    url[MAX_URLLENGTH];
        char    key[MAX_KEYLENGTH];

        key[0] = NUL; /* @@ */
        strcpy( url,
#ifdef  BEFORE_20070920
                "http://bookmark.fc2.com/user/update_bookmark"
#else
                "http://bookmark.fc2.com/user/update_or_delete_bookmark"
#endif
              );
        makeRequestForFC2bookmark( mp, key, request, FC2_UPDATE_BOOKMARK );

        // �X�V
        sprintf( request + strlen(request),
                 "&data[Bookmark][id_md5]=%s",
                 entryID );

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
            if ( strstr( response, sjis2utf("�X�V���܂���") ) )
                ret = TRUE;
            else
                getErrorStringForFC2bookmark( response, errorString );
        }
    }

    return ( ret );
}

BOOL
_putFC2Bookmark(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    BOOL    ret       = FALSE;
    char    url[MAX_URLLENGTH];
    char    key[MAX_KEYLENGTH];

    getKeyForFC2bookmark( key, response, sz, cookie );
    strcpy( url, "http://bookmark.fc2.com/user/add_bookmark" );
    makeRequestForFC2bookmark( mp, key, request, FC2_ADD_BOOKMARK );
    refineRequestForFC2bookmark( request );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, sjis2utf("�u�b�N�}�[�N�ɒǉ����܂���") ) )
            ret = TRUE;
        else {
            getErrorStringForFC2bookmark( response, errorString );
            if ( !strcmp( errorString, "URL�͂��łɑ��݂��܂�"   ) ||
                 !strcmp( errorString, "URL�͊��ɑ��݂��Ă��܂�" )    ) {
#ifndef WIN32
# ifndef IDNO
#  define IDNO  FALSE
#  define IDYES TRUE
# endif /* !IDNO  */
#endif  /* !WIN32 */
                int     r = IDNO;
                int     fd = fileno( stderr );
                LCID    l = getLanguageCode();

                strcpy( errorString,
                        l == 0x0411
                         ? "����Web�y�[�W�́A���ł�FC2BOOKMARK��"
                           "�o�^�ς݂ł��B"
                         : "this web page was already registered by"
                           " you." );
#ifdef  WIN32
                if ( (fd >= 0) && isatty( fd ) )
                    r = IDNO;
                else
                    r = MessageBox(
                            NULL,
                            l == 0x0411
                             ? "���YWeb�y�[�W�͊��ɓo�^�ς݂ł��B    "
                               "\r\n�o�^���e���㏑�����܂���?"
                             : "This web page was already registered "
                               "by you.    \r\n"
                               "Overwrite this bookmark?",
                            l == 0x0411
                             ? "�㏑���m�F (FC2BOOKMARK)"
                             : "Overwrite bookmark (FC2BOOKMARK)",
                            MB_YESNO|MB_ICONQUESTION );
#endif
                if ( r == IDYES )
                    ret = editFC2bookmark( mp, cookie, errorString,
                                           request, response, sz );
                else
                    ret = TRUE;
                if ( ret == TRUE )
                    errorString[0] = NUL;
            }
        }
    }
    else if ( getStatusCode() == 200 )  /* {@@} */
        ret = TRUE;                     /* {@@} */
    setReferer( NULL );

    return ( ret );
}

void
putFC2Bookmark(
        const char   *userName,  /* (I) ���[�U�� (FC2ID) */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    )
{
    int     ret;
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    uid[MAX_NAMELEN];
    char    cc[MAX_KEYLENGTH];

    uid[0] = NUL;
    cc[0]  = NUL;
    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* FC2BOOKMARK �� login */
    ret = loginFC2Bookmark( userName, password, cookie, uid, cc );
    if ( !ret ) {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "FC2BOOKMARK �ւ� login �Ɏ��s���܂���\n"
                    : "FC2BOOKMARK: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "FC2BOOKMARK �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "FC2BOOKMARK: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
        return;
    }

    if ( cookie[0] ) {
        // cookie ���� fcu �� glgd_val �ȊO�̂��̂��폜����
        char    *p, *q;
        char    fcu[MAX_LOGICALLINELEN];
        char    glgd_val[MAX_LOGICALLINELEN];

        fcu[0] = NUL;
        glgd_val[0] = NUL;

        p = strstr( cookie, "fcu=" );
        if ( p ) {
            q = strchr( p + 4, ';' );
            if ( !q )
                q = strchr( p + 4, '\r' );
            if ( !q )
                q = strchr( p + 4, '\n' );
            if ( q ) {
                strncpy( fcu, p, q - p );
                fcu[q - p] = NUL;
            }
        }

        p = strstr( cookie, "glgd_val=" );
        if ( p ) {
            q = strchr( p + 9, ';' );
            if ( !q )
                q = strchr( p + 9, '\r' );
            if ( !q )
                q = strchr( p + 9, '\n' );
            if ( q ) {
                strncpy( glgd_val, p, q - p );
                glgd_val[q - p] = NUL;
            }
        }

        if ( fcu[0] && glgd_val[0] )
            sprintf( cookie, "Cookie: %s; %s\r\n", glgd_val, fcu );
    }

    /* FC2BOOKMARK �ɓo�^ */
    putBookmarks( "FC2BOOKMARK", mp, numOfClips, cookie, cookieSize, NULL,
                  _putFC2Bookmark );
}

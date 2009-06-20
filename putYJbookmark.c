/*
 * clip loader <<putYJbookmark>>
 *
 *      OPML �� Yahoo! �u�b�N�}�[�N �o�^�v���O����
 *          written by H.Tsujimura  16 Apr 2007
 *
 * History:
 * $Log: /comm/bookey/putYJbookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/12/02 19:39 Tsujimura543
 * �t�H�[�}�b�g�X�g�����O�Ǝ㐫�֘A�̃o�O�C��
 * 
 * 3     07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 2     07/04/16 22:29 Tsujimura543
 * crumbs �� GET ����Ƃ��� title �� Shift_JIS �ɂ��Ă����̂� UTF-8 ��
 * ����悤�ɕύX
 * 
 * 1     07/04/16 22:03 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putYJbookmark.c 1     09/05/14 3:48 tsupo $";
#endif

BOOL
_putYJbookmark(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char    *cookie   = args->cookie;
    char    *request  = args->request;
    char    *response = args->response;
    size_t  sz        = args->sz;
    char    url[MAX_URLLENGTH * 4];
    char    *p, *q;
    BOOL    ret = FALSE;
    char    crumbs[MAX_KEYLENGTH];

    errorString[0] = NUL;

    /* http://bookmarks.yahoo.co.jp/bookmarklet/showpopup (crumbs) �� GET */
    crumbs[0] = NUL;
    p = any2utf( mp->title );
    sprintf( url,
             "http://bookmarks.yahoo.co.jp/bookmarklet/showpopup?"
             "t=%s&",
             encodeURL( p ? p : mp->title ) );
    sprintf( url + strlen( url ),
             "u=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "name=\"crumbs\" value=\"" );
        if ( p ) {
            p += 21;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( crumbs, p, q - p );
                crumbs[q - p] = NUL;
            }
        }
    }
    if ( !(crumbs[0]) )
        return ( ret );

    /* �u�b�N�}�[�N�� POST */
    strcpy( url, "http://bookmarks.yahoo.co.jp/bookmarklet/savebm" );
    sprintf( request,
             "tbact=save&"
             "crumbs=%s&",
             crumbs );

    // �^�C�g��
    p = any2utf( chcode( (char *)(mp->title) ) );
    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( p ? p : mp->title ) );

    // URL
    sprintf( request + strlen(request),
             "url=%s&",
             encodeURL( mp->url ) );

    // �^�O (�󔒋�؂�)
    p = any2utf( chcode( (char *)(mp->tags) ) );
    sprintf( request + strlen(request),
             "tags=%s&"
             "currentfid=0&",
             encodeURLex( p ? p : mp->tags ) );

    // �o�^��t�H���_
    sprintf( request + strlen(request),
             "pfid=root&"
             "newname=&" );

    // �R�����g
    p = any2utf( chcode( (char *)(mp->comment) ) );
    sprintf( request + strlen(request),
             "desc=%s&",
             encodeURLex( p ? p : mp->comment ) );

    // ���J�ݒ�
    sprintf( request + strlen(request),
             mp->publication == PUB_PRIVATE
                ? "visibility=0&"       // ����J (�����̂�)
                : "visibility=1&" );    // �݂�ȂɌ��J

    sprintf( request + strlen(request),
             "submit=%s",
             encodeURL( sjis2utf("�o�^") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "<body onLoad=\"javascript:winClose()\">" ) )
            ret = TRUE; /* �o�^���� */
    }

    return ( ret );
}

void
putYJbookmark(
        const char   *userName,  /* (I) ���[�U��(Yahoo! Japan ID) */
        const char   *password,  /* (I) �p�X���[�h                */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���          */
        int          numOfClips  /* (I) �u�b�N�}�[�N��            */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    // Yahoo! Japan ID �Ń��O�C��
    ret = loginYahooJapan( userName, password, cookie );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( "Yahoo! Japan Bookmark",
                      mp, numOfClips, cookie, cookieSize, NULL,
                      _putYJbookmark );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "Yahoo! Japan �ւ� login �Ɏ��s���܂���\n"
                    : "Yahoo! Japan: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "Yahoo! Japan �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "Yahoo! Japan: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


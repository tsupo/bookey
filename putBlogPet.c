/*
 * clip loader <<putBlogPet>>
 *
 *      OPML �� �uBlogPet�u�b�N�}�[�N�v�o�^�v���O����
 *          written by H.Tsujimura  22 Dec 2006
 *
 * History:
 * $Log: /comm/bookey/putBlogPet.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 30    09/02/25 20:12 Tsujimura543
 * _putBlogPet() ���C�� (���������Ă��Ȃ��������̈���Q�Ƃ��Ă���)
 * 
 * 29    08/12/02 19:36 Tsujimura543
 * �t�H�[�}�b�g�X�g�����O�Ǝ㐫�֘A�̃o�O�C��
 * 
 * 28    08/02/19 21:58 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v �� �uBlogPet�u�b�N�}�[�N�v�ɖ��̕ύX
 * 
 * 27    07/11/13 23:15 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 26    07/11/13 23:12 Tsujimura543
 * (1) �o�^���悤�Ƃ��Ă���u�b�N�}�[�N�̃^�C�g�����󕶎���ɂȂ邱�Ƃ���
 *     �錻�ۂɑΏ� (2007�N11��12���Ɍ��ۂ��ϑ��B��13���ɂ͊ϑ��ł��Ă���
 *     �����߁A�T�[�o���ŉ����ύX���s�Ȃ�ꂽ�\��������B�O�̂��߂�
 *     bookey ���ł̑΍���c���Ă���)
 * (2) �������t�@�N�^�����O
 * 
 * 25    07/11/12 22:03 Tsujimura543
 * setTitleOnRequest() ���C���A�^�C�g���������ċ��e�������𒴂���ꍇ�́A
 * �z����������؂�̂Ă�悤�ɂ���
 * 
 * 24    07/11/09 18:03 Tsujimura543
 * �G���[���b�Z�[�W(�������͌x�����b�Z�[�W)���擾�ł����ꍇ�́A���̓��e��
 * �G���[�_�C�A���O�ɕ\������悤�ɂ��� [�l�q���I��]
 * 
 * 23    07/11/05 20:43 Tsujimura543
 * �l�q���o�[�W����
 * 
 * 22    07/10/31 20:49 Tsujimura543
 * ���O����͂���Ƃ��̖ڈ�p�� dputs() ��1�ӏ��ǉ�
 * 
 * 21    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 20    07/07/13 2:01 Tsujimura543
 * 2007�N7��12���Ɏ��{���ꂽ BlogPet ���j���[�A���ɑΉ�
 * 
 * 19    07/02/16 16:19 Tsujimura543
 * �R�����g���C��
 * 
 * 18    07/02/16 16:16 Tsujimura543
 * ���łɓo�^����Ă���^�C�g���Ɠo�^���悤�Ƃ��Ă���^�C�g�����H���Ⴄ��
 * ���́A�o�^���悤�Ƃ��Ă���^�C�g���ŏ㏑�����邩�A���łɓo�^����Ă���
 * �^�C�g�������̂܂ܗ��p���邩�A�I���ł���悤�ɂ���
 * 
 * 17    07/02/15 0:25 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 16    07/02/14 23:26 Tsujimura543
 * getArticleIDbyURLonBlogPet(), editBogPet() �� editBlogPet.c �ֈړ�
 * 
 * 15    07/02/14 22:59 Tsujimura543
 * getArticleIDbyURLonBlogPet() �̃o�O��2���C��
 *   (1) articleID ��������Ȃ��ꍇ�A�i�v�Ƀy�[�W�擾�E�T���𑱂���
 *       ���܂�
 *   (2) �y�[�W���̃u�b�N�}�[�N�̂����ŏ��̕���2�̂ݕ]�����邾���ŁA
 *       �c��͓ǂݔ�΂��Ă��܂�
 * 
 * 14    07/02/14 0:19 Tsujimura543
 * confirmPostBlogPet() �̓���m�F���� (�V�K�o�^�A�㏑���ҏW�Ƃ�)
 * 
 * 13    07/02/14 0:06 Tsujimura543
 * ���łɓo�^�ς݂̋L�����ēo�^���悤�Ƃ����ꍇ�́A�㏑���o�^�����s����
 * �悤�ɂ���
 * 
 * 12    07/02/05 21:41 Tsujimura543
 * �^�C�g���̈�������ς��Ă݂�
 * 
 * 11    07/01/23 21:12 Tsujimura543
 * �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 10    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 9     07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 8     07/01/17 16:28 Tsujimura543
 * Vox �̋L���𓊍e���悤�Ƃ���Ɨ�����(BM_BODY �Ɋi�[�����u�T�v�v
 * (Vox ����Ԃ����html�{��)��bot �����̃��b�Z�[�W�ŁA���̃��b�Z�[�W
 * ���� any2utf() �ł͈����Ȃ��������܂܂�Ă���̂������ŁAany2utf()
 * �� NULL ��Ԃ�)�s��ɑ΂�����C�����{
 * (�{�i�I�ȉ��C�� any2utf() ���ōs�Ȃ��K�v����)
 * 
 * 7     06/12/25 23:37 Tsujimura543
 * loginBlogPet() �ɑ�4������ǉ�
 * 
 * 6     06/12/25 23:21 Tsujimura543
 * �^�O(�L�[���[�h)��1�����o�^�ł��Ȃ��s����C��
 * 
 * 5     06/12/25 19:28 Tsujimura543
 * �o�^���s���ɕ\������_�C�A���O�̕������C��
 * 
 * 4     06/12/25 17:17 Tsujimura543
 * BM_TITLE, BM_BODY �̌��l�^�擾�֘A�������C��
 * 
 * 3     06/12/25 17:13 Tsujimura543
 * ���łɓo�^�ς݂̃y�[�W���A�u���J���x���v���u��ʌ��J�v�ł���ꍇ�A����
 * ���̓^�C�g����T�v���܂������ύX���Ă��Ȃ��ꍇ�́A�o�^�ł���悤�ɂ���
 * 
 * 2     06/12/25 16:11 Tsujimura543
 * ���łɓo�^�ς݂̃y�[�W�̓o�^�Ɏ��s����Ƃ����s��������āA
 * ����m�F�I��
 * 
 * 1     06/12/22 21:58 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"
#include "blogPet.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBlogPet.c 1     09/05/14 3:48 tsupo $";
#endif

void
getTitleWithoutRate( const char *title, char *titleWithoutRate )
{
    char    *p;

    p = any2utf( title );
    strcpy( titleWithoutRate, p ? p : title );

    // MM/Memo �`���� title ���������߂̏���
    getEvaluation( titleWithoutRate, UTF8 );
}

void
setUrlOnRequest( const char *url, char *request )
{
    sprintf( request + strlen(request),
             "url=%s&",
             encodeURL( url ) );
}

void
setTitleOnRequest( const char *title, char *request )
{
#define MAX_TITLE_LEN_FOR_BLOGPET   (50 * 2)  // �^�C�g���́u�S�p50�����v�܂�
    char    tmpTitle[MAX_DESCRIPTION_LEN];
    char    *p = tmpTitle;

    tmpTitle[0] = NUL;
    any2sjisEx( tmpTitle, title );
    if ( tmpTitle[0] && (strlen( tmpTitle ) > MAX_TITLE_LEN_FOR_BLOGPET) )
        adjustStringLength( tmpTitle, MAX_TITLE_LEN_FOR_BLOGPET );

    sprintf( request + strlen(request),
             "title=%s&",
             encodeURLex2( any2utf( p && *p ? p : title ) ) );
}

void
setBodyOnRequest( const char *body, char *request )
{
    if ( body && body[0] )
        sprintf( request + strlen(request),
                 "excerpt=%s&",
                 encodeURLex2( any2utf( body ) ) );
    else
        sprintf( request + strlen(request),
                 "excerpt=&" );
}

void
setTagsOnRequest( const char *tags, char *request )
{
    char        tmpTags[2048];
    const char  *p, *q;
    int         i;

    p = any2utf( tags );
    if ( !p )
        p = tags;
    for ( i = 0; i <= 9; i++ ) {
        q = strchr( p, ' ' );
        if ( q ) {
            strncpy( tmpTags, p, q - p );
            tmpTags[q - p] = NUL;
        }
        else
            strcpy( tmpTags, p );
        sprintf( request + strlen(request),
                 "keywords=%s&",
                 encodeURL( tmpTags ) );
        if ( !q )
            break;
        p = q + 1;
    }
    for ( ; i <= 9; i++ )
        strcat( request, "keywords=&" );
}

void
setPolicyOnRequest( int publication, char *request )
{
    sprintf( request + strlen(request),
             "type=%s&",
             publication == PUB_PRIVATE ? "private"
                                        : "public" );
}

void
setCommentOnRequest( const char *comment, char *request )
{
    char    *p;

    p = any2utf( comment );
    sprintf( request /* + strlen(request) */,
             "comment=%s&",
             encodeURLex( p ? p : comment ) );
}


BOOL
_putBlogPet(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie    = args->cookie;
    char        *request   = args->request;
    char        *response  = args->response;
    size_t      sz         = args->sz;
    BOOL        useMyTitle = (BOOL)(args->args);
    char        url[MAX_URLLENGTH * 4];
    const char  *p, *q;
    char        tmpTitle[BLOGPET_TEMP_TITLE_LEN];
    char        tmpTitle2[BLOGPET_TEMP_TITLE_LEN];
    char        tmpBody[MAX_DESCRIPTION_LEN];
    char        cid[MAX_KEYLENGTH];
    BOOL        ret    = FALSE;
    BOOL        modify = FALSE;

    errorString[0] = NUL;
    tmpTitle2[0]   = NUL;
    tmpBody[0]     = NUL;
    cid[0]         = NUL;

    /* title �� excerpt �̌��l�^�� GET */
    sprintf( url,
             "http://www.blogpet.net/bookmark/modify?url=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "<div id=\"summary\">" );
        if ( p ) {
            const char  *r;

            if ( strstr( p, sjis2utf("<span>�ύX����</span>") ) )
                modify = TRUE;

            // title
            p += 18;
            q = strstr( p, "<input type=\"text\" name=\"title\"" );
            if ( q ) {
                q += 31;
                r = strstr( q, "value=\"" );
                if ( r ) {
                    q = r + 7;
                    r = strchr( q, '"' );
                    if ( r ) {
                        strncpy( tmpTitle2, q, r - q );
                        tmpTitle2[r - q] = NUL;
                    }
                }
            }

            // excerpt
            q = strstr( p, "<textarea name=\"excerpt\"" );
            if ( q ) {
                q += 24;
                r = strstr( q, "\">" );
                if ( r ) {
                    q = r + 2;
                    r = strstr( q, "</textarea>" );
                    if ( r ) {
                        strncpy( tmpBody, q, r - q );
                        tmpBody[r - q] = NUL;
                        if ( tmpBody[0] ) {
                            size_t  l = 0;
                            while ( ((l = strlen(tmpBody)) > 0)    &&
                                     ((tmpBody[l - 1] == '\r') ||
                                      (tmpBody[l - 1] == '\n')   )    )
                                tmpBody[l - 1] = NUL;
                        }
                    }
                }
            }

            // CID
            q = strstr( p, "name=\"CID\" value=\"" );
            if ( q ) {
                p = q + 18;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( cid, p, q - p );
                    cid[q - p] = NUL;
                }
            }
        }
    }

    /* �u�b�N�}�[�N�� POST */
    strcpy( url, "http://www.blogpet.net/bookmark/modify" );

    // �R�����g
    setCommentOnRequest( mp->comment, request );

    // �L�[���[�h (�^�O�ɑ����A10�܂�)
    setTagsOnRequest( mp->tags, request );

    // ���J���x�� (��ʌ��J�A����J)
    setPolicyOnRequest( mp->publication, request );

    // �^�C�g��
    if ( useMyTitle )
        getTitleWithoutRate( mp->title, tmpTitle );
    else
        strcpy( tmpTitle, tmpTitle2 );
    if ( tmpTitle[0] == NUL )
        strcpy( tmpTitle, mp->title );
    setTitleOnRequest( tmpTitle, request );

    // �T�v
    setBodyOnRequest( tmpBody, request );

    // CID
    sprintf( request + strlen( request ),
             "CID=%s&"
             "regist=%s",
             cid,
             modify ? encodeURL( sjis2utf("<span>�ύX����</span>") )
                    : encodeURL( sjis2utf("<span>�o�^����</span>") ) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        p = strstr( response, sjis2utf("�u�b�N�}�[�N��o�^���܂���") );
        if ( !p )
            p = strstr( response, sjis2utf("�u�b�N�}�[�N��ύX���܂���") );
        if ( p )
            ret = TRUE; // �o�^����
        else {
            dputs( "BlogPet: �u�b�N�}�[�N�o�^���s\n" );
            p = strstr( response,
                        "<div class=\"systemMessage\">"
                        "<span class=\"warning\">" );
            if ( p ) {
                p += 49;
                q = strstr( p, "</span></div>" );
                if ( q ) {
                    strncpy( errorString, p, q - p );
                    errorString[q - p] = NUL;
                    p = utf2sjis( errorString );
                    if ( p )
                        strcpy( errorString, p );
                    ret = TRUE; /* �o�^���s�����A���̂܂܃��g���C���Ă����s */
                                /* ���邾���Ȃ̂œo�^���������Ƃ���         */
                }
            }
        }
    }

    return ( ret );
}

void
putBlogPet(
        const char   *userName,  /* (I) ���[�U��                       */
        const char   *password,  /* (I) �p�X���[�h                     */
        BOOL         useMyTitle, /* (I) �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    userID[MAX_KEYLENGTH];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );

    /* BlogPet �Ǘ���ʂ� login */
    userID[0] = NUL;
    ret = loginBlogPet( userName, password, cookie, userID );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( getLanguageCode() == 0x0411
                       ? "BlogPet�u�b�N�}�[�N"
                       : "BlogPet bookmarks",
                      mp, numOfClips, cookie, cookieSize,
                      (void *)useMyTitle,
                      _putBlogPet );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "BlogPet�Ǘ���ʂւ� login �Ɏ��s���܂���\n"
                    : "BlogPet: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "BlogPet�Ǘ���ʂւ̃��O�C���Ɏ��s���܂����B  "
                         : "BlogPet: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}


#ifdef  PUT_BLOGPET_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useMyTitle,
        BOOL *useProxy,
        FILE **fp
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( username, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;

                case 'F':
                    *useMyTitle = !(*useMyTitle);
                    break;

                case 'i':
                    if ( argv[i][j + 1] ) {
                        FILE    *gp = fopen( &(argv[i][j + 1]), "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s ��������܂���\n"
                                      : "%s: Not found.\n",
                                     &(argv[i][j + 1]) );
                            exit( 255 );
                        }
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        FILE    *gp = fopen( argv[i + 1], "r" );
                        if ( gp )
                            *fp = gp;
                        else {
                            fprintf( stderr,
                                     getLanguageCode() == 0x0411
                                      ? "%s ��������܂���\n"
                                      : "%s: Not found.\n",
                                     argv[i + 1] );
                            exit( 255 );
                        }
                        i++;
                        j = strlen( argv[i] ) - 1;
                    }
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    if ( getLanguageCode() == 0x0411 ) {
        // ���{��
        fprintf( stderr,
                 "putBlogPet: OPML �� BlogPet�u�b�N�}�[�N �o�^�c�[��\n" );
        fprintf( stderr,
      "    putBlogPet [-x] [-F] -u ���[�U�� -p �p�X���[�h [-i OPML�t�@�C����]"
      "\n" );
        fprintf( stderr,
      "\t-x: proxy ���g��\n"
      "\t-F: ���łɓo�^����Ă���^�C�g���Ɠo�^���悤�Ƃ��Ă���^�C�g��\n"
      "\t    ���H���Ⴄ�ꍇ�́A�o�^���悤�Ƃ��Ă���^�C�g���ŏ㏑������\n"
      "\t    (�uBlogPet�u�b�N�}�[�N�v�ł́A�^�C�g���͑S���ŋ��L���Ă��܂��B"
    "\n\t     �㏑�����邩�ǂ����͐T�d�ɔ��f���Č��߂Ă�������)\n"
      "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putBlogPet: read bookmarks from OPML, and put them into BlogPet \n"
      "            bookmarks\n");
        fprintf( stderr,
      "    putBlogPet [-x] [-F] -u username -p password [-i OPMLfilename]\n");
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-F: overwrite entry title, if original title was different from\n"
      "\t    your specified title\n"
      "\t    (Caution: entry title is shared by all users of BlogPet bookmarks)\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy   = FALSE;
    BOOL    useMyTitle = FALSE;
    FILE    *fp = stdin;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  username, password,
                  &useMyTitle, &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� BlogPet�u�b�N�}�[�N �ɓo�^ */
        putBlogPet( username, password, useMyTitle, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_BLOGPET_EXE */

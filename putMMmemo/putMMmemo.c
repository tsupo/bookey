/*
 * clip loader <<putMMmemo>>
 *
 *      OPML �� MM/Memo �o�^�v���O����
 *          written by H.Tsujimura  19 Oct 2005
 *
 * $Log: /comm/bookey/putMMmemo/putMMmemo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 32    07/11/12 21:55 Tsujimura543
 * adjustStringLength() �� myClip.c �ֈڊ�
 * 
 * 31    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 30    07/09/04 22:05 Tsujimura543
 * setVerbose() �̑�2�����ǉ��ɔ����ύX
 * 
 * 29    07/07/02 16:34 Tsujimura543
 * http://1470.net/mm/ �� http://mmmemo.1470.net/mm/ �ɕύX
 * (�ύX���Ȃ��Ɠo�^�Ɏ��s����[�o�^���悤�Ƃ��Ă���URL�������A�ƕ\��
 *  �����]���Ƃ�����)
 * 
 * 28    07/01/23 16:42 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 27    07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 26    07/01/18 23:45 Tsujimura543
 * putBookmarks() �𓱓��B���t�@�N�^�����O�����{
 * 
 * 25    06/11/17 19:38 Tsujimura543
 * getEvaluation() �𓱓��Btitle �� MM/Memo �`���ł���΁A���K�����Ă���
 * �o�^����悤�ɂ��Ă݂�
 * 
 * 24    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 23    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 22a   06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 22    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 21    06/07/27 20:45 Tsujimura543
 * ��M�d���i�[�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * 
 * 20    06/07/07 13:36 Tsujimura543
 * �R�����g���C��
 * 
 * 19    06/06/28 21:39 Tsujimura543
 * �u�b�N�}�[�N�Ώی�Web�y�[�W��charset��EUC-JP�ł��^�C�g����128�o�C�g
 * ���傫���Ƃ��A��̃^�C�g���œo�^���悤�Ƃ��Ă��܂��s��ɑΏ�
 * 
 * 18    06/06/05 22:10 Tsujimura543
 * MM/Memo �̃^�O(�W������)�̍ő勖�e�o�C�g��(80�o�C�g)�𒴂��镔����
 * �����E�폜���Ă���A�o�^�����s����悤�ɂ���
 * 
 * 17    06/05/22 16:49 Tsujimura543
 * Sleep() ����^�C�~���O���Ē���
 * 
 * 16    06/05/22 15:30 Tsujimura543
 * �o�^���s���� Sleep() �̃^�C�~���O�Asleep���鎞�Ԃ̒����𒲐�
 * 
 * 15    06/02/22 16:47 Tsujimura543
 * &raquo; �΍�����{
 * 
 * 14    05/12/07 20:39 Tsujimura543
 * MM/Memo �`���� title ���ǂ������f���鏈�����������
 * 
 * 13    05/12/07 20:03 Tsujimura543
 * �u�b�N�}�[�N�Ώۂ�Web�y�[�W��title�� "�w" �� "�x" ���܂܂��ꍇ�A
 * MM/Memo �`���� title ���ƌ�F����Ă��܂��\�����ɗ͌��炷�悤��
 * ���Ă݂�
 * 
 * 12    05/11/02 18:00 Tsujimura543
 * memo_kind �����f����Ȃ��s����C�� (Date_Day=xx �̒���� & ��
 * �����Ă���)
 * 
 * 11    05/11/02 15:31 Tsujimura543
 * getStringImplanted() �� getString.c �֕����A�Ɨ�������
 * 
 * 10    05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 9     05/10/29 1:12 Tsujimura543
 * �u�b�N�}�[�N�o�^���Ɏg�p���鏈�����e�X��������(����m�F�ς�)
 * 
 * 8     05/10/25 15:00 Tsujimura543
 * (1) �A�}�]���̏��i�ʃy�[�W�̃u�b�N�}�[�N�Ɏ��s����s����C��
 * (2) �u�b�N�}�[�N�Ώۂ�Web�y�[�W�� Shift_JIS �܂��� EUC-JP �̏ꍇ�A
 *     �u�b�N�}�[�N�o�^��̃^�C�g�������Ғʂ�̂��̂ɂȂ�Ȃ����Ƃ�����
 *     �s����C��
 * 
 * 7     05/10/25 14:22 Tsujimura543
 * ���b�Z�[�W�{�b�N�X�̃^�C�g���Ɩ{���̕������t�ɂȂ��Ă����̂��C��
 * 
 * 6     05/10/25 14:12 Tsujimura543
 * �W���G���[�o�͂��Θb�ɗ��p�\���ǂ����𒲍�������@���C��
 * 
 * 5     05/10/24 20:37 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 4     05/10/24 20:34 Tsujimura543
 * �^�C�g����128�o�C�g���傫���ꍇ�̑΍�����{
 * 
 * 3     05/10/20 23:39 Tsujimura543
 * �u�b�N�}�[�N�o�^���s���̃��g���C������ǉ�
 * 
 * 2     05/10/20 21:13 Tsujimura543
 * ���͂̕����R�[�h�� Shift_JIS, EUC-JP, UTF-8 �̂ǂ�ł������悤�ɂ���
 * 
 * 1     05/10/20 20:08 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putMMmemo/putMMmemo.c 1     09/05/14 3:48 tsupo $";
#endif


BOOL
_putMMmemo(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    char        url[1024];
    char        checkKey[32 + 1];
    char        webpageID[16];
    char        asin[16];
    char        tmpTitle[BUFSIZ];
    char        tmpTags[180];
    char        tmpComment[2048];
    const char  *p;
    char        *q;
    BOOL        ret  = FALSE;
    int         rate = 0;
    int         len;

    errorString[0] = NUL;

    // check_key �� webpageID �������� asin ���擾
    checkKey[0]  = NUL;
    webpageID[0] = NUL;
    asin[0]      = NUL;

    sprintf( url, "http://mmmemo.1470.net/mm/memo_form.html?url=%s",
             encodeURL( mp->url ) );

    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( !p || !(*p) )
        return ( ret );

    getStringImplanted( checkKey,  p, "name=\"check_key\" value=\"", "\"" );
    getStringImplanted( webpageID, p, "name=\"webpage\" value=\"",   "\"" );
    getStringImplanted( asin,      p, "name=\"asin\" value=\"",   "\"" );
    if ( !(checkKey[0]) || (!(webpageID[0]) && !(asin[0])) )
        return ( ret );

    // �u�b�N�}�[�N��o�^
    strcpy( url, "http://mmmemo.1470.net/mm/memo_form.html" );

    // MM/Memo �`���� title ���������߂̏���
    strcpy( tmpTitle, mp->title );
    rate = getEvaluation( tmpTitle, EUC2UTF );
    p = tmpTitle;

    // MM/Memo �́u�^�C�g���v��128�o�C�g�ȓ��ɂ���K�v����
    len = strlen( p );
    if ( len > 128 ) {
        const char  *q;

        q = euc2sjis( p );
        if ( q )
            strcpy( tmpTitle, q );
        adjustStringLength( tmpTitle, 128 );
        p = sjis2euc( tmpTitle );
        if ( !p )
            p = tmpTitle;
    }

    sprintf( request,
             "memo=&"
             "check_key=%s&",
             checkKey );
    if ( webpageID[0] )
        sprintf( request + strlen( request ),
                 "webpage=%s&",
                 webpageID );
    else if ( asin[0] )
        sprintf( request + strlen( request ),
                 "asin=%s&",
                 asin );
    sprintf( request + strlen( request ),
             "memo_title=%s&"
             "Date_Year=%d&"
             "Date_Month=%d&"
             "Date_Day=%d&",
             encodeURLex3( p ),
             mp->yyyy, mp->mm, mp->dd );
    // -- memo_kind
    p = utf2euc( mp->title );
    if ( !p )
        p = sjis2euc( mp->title );
    strcpy( tmpTitle, p ? p : mp->title );
    if ( (tmpTitle[0] == '[') && (tmpTitle[3] == ']') )
        sprintf( request + strlen( request ),
                 "memo_kind=%%%02x%%%02x&",
                 tmpTitle[1] & 0xFF, tmpTitle[2] & 0xFF );
    else
        strcat( request, "memo_kind=&" );
    // -- memo_eval
    if ( rate > 0 )
        sprintf( request + strlen( request ),
                 "memo_eval=%d&",
                 rate );
    else if ( (mp->evaluation >= EVL_ONE) && (mp->evaluation <= EVL_FIVE) )
        sprintf( request + strlen( request ),
                 "memo_eval=%d&",
                 mp->evaluation );
    else
        strcat( request, "memo_eval=&" );
    // -- memo_genre
    p = utf2euc( mp->tags );
    if ( !p )
        p = sjis2euc( mp->tags );
    strcpy( tmpTags, p ? p : mp->tags );
    q = tmpTags;
    if ( *q ) {
        while ( *q ) {
            if ( *q == ' ' ) {
                *q = '|';

                /* �ȉ��� bookey 0.04, 0.04a, 0.04b �� getMMmemo() �����u�b */
                /* �N�}�[�N�� putMMmemo() ����ꍇ�̑΍�(�Ȃ̂ŁA������͔p */
                /* �~����)                                                  */
                while ( *(q + 1) == ' ' )
                    strcpy( q + 1, q + 2 );
            }
            q++;
        }

        // MM/Memo �́u�W�������v��80�o�C�g�ȓ��ɂ���K�v����
        while ( strlen( tmpTags ) > 80 ) {
            q = strrchr( tmpTags, '|' );
            if ( q )
                *q = NUL;
            else {
                adjustStringLength( tmpTags, 80 );
                break;
            }
        }

        sprintf( request + strlen( request ),
                 "memo_genre=%s&",
                 encodeURL( tmpTags ) );
    }
    else
        strcat( request, "memo_genre=&" );
    // -- memo_text
    p = utf2euc( mp->comment );
    if ( !p )
        p = sjis2euc( mp->comment );
    strcpy( tmpComment, p ? encodeURL( p ) : mp->comment );
    sprintf( request + strlen( request ),
             "memo_text=%s&"
             "memo_url=&"
             "submit_button=%s&"
             "save_copy=1",
             tmpComment, encodeURL(sjis2euc("�ۑ�����")) );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    ret = response && response[0] ? TRUE : FALSE;
    encodeURLex3( NULL );

    return ( ret );
}


void
putMMmemo(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    size_t  cookieSize = MAX_COOKIE_LEN;
    char    cookie[MAX_COOKIE_LEN + 1];
    char    userID[32];
    int     ret;

    memset( cookie, 0x00, MAX_COOKIE_LEN + 1 );
    memset( userID, 0x00, 32 );

    /* MM/Memo �Ƀ��O�C�� */
    ret = loginMMmemo( userName, password, cookie, userID );
    if ( ret == 1 ) /* login ���� */
        putBookmarks( "MM/Memo", mp, numOfClips, cookie, cookieSize, NULL,
                      _putMMmemo );
    else {
        int fd = fileno( stderr );

        if ( (fd >= 0) && isatty( fd ) )
            fputs( getLanguageCode() == 0x0411
                    ? "MM/Memo �ւ� login �Ɏ��s���܂���\n"
                    : "MM/Memo: login failed.\n",
                   stderr );
#ifdef  WIN32
        else {
            LCID    l = getLanguageCode();
            MessageBox( NULL,
                        l == 0x0411
                         ? "MM/Memo �ւ̃��O�C���Ɏ��s���܂����B  "
                         : "MM/Memo: login failed.    ",
                        l == 0x0411
                         ? "���O�C�����s"
                         : "Login failure",
                        MB_OK|MB_ICONERROR );
        }
#endif
    }
}



#ifdef  PUT_MM_MEMO_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
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
        fprintf( stderr, "putMMmemo: OPML �� MM/Memo �o�^�c�[��\n" );
        fprintf( stderr,
                 "    putMMmemo [-x] -u TypeKey�F�ؗp���[�U��\n"
                 "                   -p TypeKey�F�ؗp�p�X���[�h\n"
                 "                   [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
        "\t-x: proxy ���g��\n"
        "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putMMmemo: read bookmarks from OPML, and put them into MM/Memo\n" );
        fprintf( stderr,
      "    putMMmemo [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "      username: ID for TypeKey authentication\n"
      "      password: password for TypeKey authentication\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
      "\t-i: If this option is not specified, read from standard input\n"
      "\t    instead of OPML\n" );
    }
}

int
main( int argc, char *argv[] )
{
    int     numOfClips = 0;
    char    username[MAX_USERIDLEN + 1];
    char    password[MAX_PASSWDLEN + 1];
    BOOL    useProxy = FALSE;
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
                  &useProxy, &fp );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* OPML�t�@�C������u�b�N�}�[�N���擾 */
    mp = inputOPML( &numOfClips, fp );
    if ( fp && (fp != stdin) )
        fclose( fp );

#ifdef  _DEBUG
    setVerbose( TRUE, stderr );
#endif
    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� MM/Memo �ɓo�^ */
        putMMmemo( username, password, mp, numOfClips );
        free( mp );
        encodeURL( NULL );  // �̈���
    }

    return ( 1 );
}
#endif  /* PUT_MM_MEMO_EXE */

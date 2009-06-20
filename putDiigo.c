/*
 * clip loader <<putDiigo>>
 *
 *      OPML �� Diigo �o�^�v���O����
 *          written by H.Tsujimura  25 Jul 2008
 *
 * History:
 * $Log: /comm/bookey/putDiigo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/08/18 14:04 Tsujimura543
 * �uerrorString �ɃG���[�������̕�������Z�b�g����v�������C��
 * 
 * 3     08/08/12 19:26 Tsujimura543
 * errorString �ɃG���[�������̕�������Z�b�g����悤�ɂ��Ă݂�
 * 
 * 2     08/07/26 0:46 Tsujimura543
 * �\�[�X�𐮗�
 * 
 * 1     08/07/25 22:16 Tsujimura543
 * �V�K�쐬 (�b��ŁB����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putDiigo.c 1     09/05/14 3:48 tsupo $";
#endif

char    *
encodeURLforJSON( const char *url )
{
    char        *s = (char *)malloc( strlen( url ) * 2 + 1 );
    const char  *t = url;
    char        *ret = s;

    if ( s ) {
        while ( *t ) {
            if ( *t == '/' )
                *s++ = '\\';
            *s++ = *t++;
        }
        *s = NUL;
    }

    return ( ret );
}

char    *
encodeTagsForJSON( const char *tags )
{
    char        *s = (char *)malloc( strlen( tags ) + 1 );
    const char  *t = tags;
    char        *ret = s;

    if ( s ) {
        while ( *t ) {
            if ( *t == ' ' )
                *s++ = ',';
            else
                *s++ = *t;
            t++;
        }
        *s = NUL;
    }

    return ( ret );
}



typedef struct paramPutDiigo    {
    const char  *userName;
    const char  *password;
}   PARAM_DIIGO;


BOOL
_putDiigo(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
 // char        *cookie   = args->cookie;
    char        *request  = args->request;
    char        *response = args->response;
    size_t      sz        = args->sz;
    PARAM_DIIGO *param = (PARAM_DIIGO *)(args->args);
    char        url[MAX_URLLENGTH * 4];
    char        tmpTitle[2048];
    char        *p, *q;
    char        *URLforJSON  = NUL;
    char        *tagsForJSON = NUL;
    char        *bookmarks   = NUL;
    int         rate;
    BOOL        ret = FALSE;

    errorString[0] = NUL;
    rate = 0;

    /* �u�b�N�}�[�N�� POST */
    strcpy( url, "http://api2.diigo.com/bookmarks" );

    p = any2utf( mp->title );
    strcpy( tmpTitle, p ? p : mp->title );

    // MM/Memo �`���� title ���������߂̏���
    rate = getEvaluation( tmpTitle, UTF8 );
    q = tmpTitle;

    if ( rate == 0 )
        if ( (mp->evaluation >= EVL_ONE)  &&
             (mp->evaluation <= EVL_FIVE)    )
            rate = mp->evaluation;

    // �^�C�g��
    sprintf( request,
             "[{\"title\":\"%s\",",
             encodeContents( q ) );

    // URL
    URLforJSON = encodeURLforJSON( mp->url );
    sprintf( request + strlen(request),
             "\"url\":\"%s\",",
             URLforJSON );

    // ���J�E����J
    sprintf( request + strlen(request),
             "\"shared\":\"%s\",",
             mp->publication == PUB_PRIVATE ? "no" : "yes" );

    // �^�O (�R���}��؂�)
    p = any2utf( mp->tags );
    tagsForJSON = encodeTagsForJSON( p ? p : mp->tags );
    sprintf( request + strlen(request),
             "\"tags\":\"%s\",",
             encodeContents( tagsForJSON ) );

    // ����
    p = any2utf( mp->comment );
    sprintf( request + strlen(request),
             "\"desc\":\"%s\"}]",
             encodeContents( p ? p : mp->comment ) );

    bookmarks = (char *)malloc( strlen( request ) * 8 + 1 );
    if ( bookmarks ) {
        sprintf( bookmarks, "bookmarks=%s", encodeURL(request) );

        setUpReceiveBuffer( response, sz );
        http_postBASIC( url, param->userName, param->password,
                        "application/x-www-form-urlencoded",
                        bookmarks, response );
        if ( *response ) {
            p = strstr( response, "added" );
            if ( p )
                ret = TRUE; /* �o�^���� */
            else {
                p = response;
                if ( (*p >= 'A') && (*p <= 'Z') && (strlen(p) <= 64) )
                    strcpy( errorString, p );
#ifdef  _DEBUG
                else {
                    FILE    *fp = fopen( "./diigo.txt", "w" );
                    if ( fp ) {
                        fputs( response, fp );
                        fclose( fp );
                    }
                }
#endif
            }
        }
    }

    if ( bookmarks )
        free( bookmarks );
    if ( tagsForJSON )
        free( tagsForJSON );
    if ( URLforJSON )
        free( URLforJSON );

    return ( ret );
}

void
putDiigo(
        const char   *userName,
        const char   *password,
        const MyClip *mp,
        int          numOfClips
    )
{
    PARAM_DIIGO param;

    param.userName = userName;
    param.password = password;

    /* Diigo �ɓo�^ */
    putBookmarks( "Diigo", mp, numOfClips, NULL, 0, &param, _putDiigo );
}


#ifdef  PUT_DIIGO_EXE
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
        fprintf( stderr,
                 "putDiigo: OPML �� Diigo �o�^�c�[��\n" );
        fprintf( stderr,
    "    putDiigo [-x] -u ���[�U�� -p �p�X���[�h [-i OPML�t�@�C����]\n" );
        fprintf( stderr,
    "\t-x: proxy ���g��\n"
    "\t-i �I�v�V�����ȗ����͕W�����͂��� OPML �t�@�C����ǂݍ��݂܂�\n" );
    }
    else {
        // �p��
        fprintf( stderr,
      "putDiigo: read bookmarks from OPML, and put them into Diigo\n" );
        fprintf( stderr,
      "    putDiigo [-x] -u username -p password [-i OPMLfilename]\n" );
        fprintf( stderr,
      "\t-x: use http access via proxy server\n"
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

    if ( mp && (numOfClips > 0) ) {
        /* �u�b�N�}�[�N�� Diigo �ɓo�^ */
        putDiigo( username, password, mp, numOfClips );
        free( mp );
    }

    return ( 1 );
}
#endif  /* PUT_DIIGO_EXE */

/*
 * clip saver <<getMyClip>>
 *
 *      MyClip! �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  17 Jan 2005 / 28 Sep 2005
 *
 * $Log: /comm/bookey/getMyClip/getMyClip.c $
 * 
 * 1     09/05/14 4:27 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 16    06/09/04 15:56 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 15a   06/09/03 20:17 tsupo
 * cookie �܂����C��
 * 
 * 15    06/08/22 15:47 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 14    06/03/28 16:57 Tsujimura543
 * MyClip! �T�[�r�X �I�����O �t�B�b�N�X��
 * 
 * 13    06/03/28 16:54 Tsujimura543
 * putDrecomRSS() ���Ăяo���O�ɁA���炩���� UTF-8 �ɕϊ�����Ă��邱�Ƃ�O��
 * �Ƃ���d�l�ɕύX���� (���̃u�b�N�}�[�N�T�[�r�X�p�� putXXX() �Ǝd�l�����킹
 * �邽��)
 * 
 * 12    06/03/28 16:24 Tsujimura543
 * -i �I�v�V������ǉ����AputDrecomRSS() ��g�ݍ���
 * 
 * 11    05/11/02 0:50 Tsujimura543
 * �b��I�ȃ��t�@�N�^�����O�����{
 * 
 * 10    05/10/20 16:09 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 9     05/09/30 17:41 Tsujimura543
 * outputOPML() �Ɉ�����ǉ�
 * 
 * 8     05/09/28 20:18 Tsujimura543
 * getMyClip() �̎d�l(�����̐��A�߂�l�̌^)��ύX
 * 
 * 7     05/09/28 13:21 Tsujimura543
 * �R�[�h�̐���
 * 
 * 6     05/09/28 13:19 Tsujimura543
 * getMyClip() ���u�b�N�}�[�N�Ǘ��c�[������Ăяo����悤�ɂ���
 * 
 * 5     05/09/28 11:57 Tsujimura543
 * �R�[�h�̐���
 * 
 * 4     05/09/28 11:28 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓�������
 * 
 * 3     05/09/28 11:04 Tsujimura543
 * struct myClip �𑼂̃u�b�N�}�[�N�z�o�������Ɗ��S�ɓ������̂ɂ���
 * 
 * 2     05/09/28 10:59 Tsujimura543
 * struct myClip �̒�`�𑼂̃u�b�N�}�[�N�z�o�������ł̒�`�ɋ߂Â���
 * 
 * 1     05/09/28 10:43 Tsujimura543
 * �ŏ��̔� (clipCOnverter.c �����Ƀu�b�N�}�[�N�z�o���`OPML�o�͂܂ł̏�����
 * �؂�o��)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getMyClip/getMyClip.c 1     09/05/14 4:27 tsupo $";
#endif


static char *
cutBrCrLf( char *p )
{
    char    *r;

    while ( ( r = strstr( p, "<br />" ) ) != NULL ) {
        if ( *(r - 1) == ' ' )
            strcpy( r, r + 7 );
        else
            strcpy( r, r + 6 );
    }

    while ( ( ( r = strchr( p, '\r' ) ) != NULL ) ||
            ( ( r = strchr( p, '\n' ) ) != NULL )    ) {
        strcpy( r, r + 1 );
    }

    return ( p );
}


int
loginMyClip( const char *username,
             const char *password,
             char       *cookie )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];

    if ( !cookie )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( MAX_CONTENT_SIZE * 20 );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );
    memset( response, 0x00, MAX_CONTENT_SIZE * 20 );

    strcpy( url, "http://clip.myblog.jp/login" );
    setTargetURL( url );
    sprintf( request,
             "email=%s&"
             "password=%s&"
             "auto_login=true",
             username, password );

    p = http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

    if ( !p || !(*p) )
        ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
    else if ( *response ) {
        if ( strstr( response, "/logout" ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}


#define URL_CLIPLIST_MYBLOG "http://clip.myblog.jp/member/list?"

long
getNumOfMyClips( char *cookie, int yyyy, int mm )
{
    long    num = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    *p, *q, *buf;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( num );
    response = (char *)malloc( MAX_CONTENT_SIZE * 20 );
    if ( !response ) {
        free( request );
        return ( num );
    }

    do {
        memset( request,  0x00, MAX_CONTENT_SIZE );
        memset( response, 0x00, MAX_CONTENT_SIZE * 20 );
        sprintf( url,
                 URL_CLIPLIST_MYBLOG
                 "year=%d&month=%d&cid=0",
                 yyyy, mm );
        setTargetURL( url );
        p = http_getEx( url, response, cookie );
        buf = response;
        if ( buf ) {
            if ( strstr( buf, url + 21 ) != NULL ) {
                    /* �� 21 := "http://clip.myblog.jp" �����X�L�b�v */
                p = strstr( buf, sjis2euc("Page1 �F") );
                if ( p ) {
                    p += 8;
                    q = strchr( p, '/' );
                    if ( q ) {
                        while ( *q && ((*q < '0') || (*q > '9')) )
                            q++;
                        if ( *q )
                            num += atol( q );
                    }
                }
            }
        }

        mm--;
        if ( mm <= 0 ) {
            mm = 12;
            yyyy--;
        }
    } while ( (yyyy >= 2005) || (mm >= 3) ); /* �ŌÂ� MyClip! �� 2004�N3�� */

    free( response );
    free( request  );

    return ( num );
}

char    *
setTag( char *tag, const char *catStr )
{
    if ( !strcmp( catStr, "IT" ) )
        strcpy( tag, "Internet" );
    else if ( !strcmp( catStr, sjis2euc("�Љ�") ) )
        strcpy( tag, "social" );
    else if ( !strcmp( catStr, sjis2euc("�X�|�[�c") ) )
        strcpy( tag, "sport" );
    else if ( !strcmp( catStr, sjis2euc("�o�ρE�o�c") ) )
        strcpy( tag, "economy" );
    else if ( !strcmp( catStr, sjis2euc("����") ) )
        strcpy( tag, "politics" );
    else if ( !strcmp( catStr, sjis2euc("����") ) )
        strcpy( tag, "international" );
    else if ( !strcmp( catStr, sjis2euc("�T�C�G���X") ) )
        strcpy( tag, "science" );
    else if ( !strcmp( catStr, sjis2euc("�����E�|�\") ) )
        strcpy( tag, "culture" );
    else if ( !strcmp( catStr, sjis2euc("�n��") ) )
        strcpy( tag, "region" );
    else if ( !strcmp( catStr, sjis2euc("�]��") ) )
        strcpy( tag, "news-of-death" );
    else if ( !strcmp( catStr, sjis2euc("�R����") ) )
        strcpy( tag, "column" );
    else if ( !strcmp( catStr, sjis2euc("�G���^�[�e�C�������g") ) )
        strcpy( tag, "entertainment" );
    else if ( !strcmp( catStr, sjis2euc("�u�b�N���r���[") ) )
        strcpy( tag, "book-review" );
    else if ( !strcmp( catStr, sjis2euc("�e�N�m���W�[") ) )
        strcpy( tag, "technology" );
    else if ( !strcmp( catStr, "blog" ) )
        strcpy( tag, "blog" );
    else
        strcpy( tag, "no-detail" );

    strcat( tag, " MyClip" );

    return ( tag );
}

MyClip  *
getMyClips( char *cookie, int *numOfClips )
{
    char        *request;
    char        *response;
    char        url[MAX_URLLENGTH];
    char        catStr[80];
    char        timestr[80];
    int         yyyy, mm;
    int         s_yyyy, s_mm;
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );
    char        *p, *q, *buf, *cur;
    long        num = 0, cnt = 0, preCnt = 0, page;
    const char  *aim  = "<td width=\"336\" valign=\"top\" class=\"tx12bh\">";
    const char  *aim2 = "<td width=\"336\" class=\"tx12bh\">";
    int         maxNum = 1000;  /* �b�� */
    MyClip      *mp = NULL;

    s_yyyy = yyyy = tm->tm_year + 1900;
    s_mm   = mm   = tm->tm_mon + 1;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( mp );
    response = (char *)malloc( MAX_CONTENT_SIZE * 20 );
    if ( !response ) {
        free( request );
        return ( mp );
    }

    /* http://clip.myblog.jp/member/list?year=2005&month=1&cid=0 */

    /* ��Clip�� 479 */
    /* �^�C�g�� �F WAY TO GO: WWW::Mixi�ŃT�C�h�o�[�ɃR�~���j�e�B�ꗗ��\��  
�@   * �L��URL  �F http://www.kreis-net.jp/blog/archives/000035.html  
�@   * �J�e�S�� �F IT, �Љ�, �X�|�[�c, �o�ρE�o�c, ����, ����, �T�C�G���X, 
     *             �����E�|�\, �n��, �]��, �R����, �G���^�[�e�C�������g,
     *             �u�b�N���r���[, �e�N�m���W�[, blog
     * �R�����g �F �ꕔ���ӂł��Ȃ��Ƃ�������邯�ǁA�T�ˎ^���B  
     */

    do {
        page = 0;
        do {
            preCnt = cnt;
            memset( request,  0x00, MAX_CONTENT_SIZE );
            memset( response, 0x00, MAX_CONTENT_SIZE * 20 );
            if ( page == 0 )
                sprintf( url,
                         URL_CLIPLIST_MYBLOG
                         "year=%d&month=%d&cid=0",
                         yyyy, mm );
            else
                sprintf( url,
                         URL_CLIPLIST_MYBLOG
                         "year=%d&month=%d&cid=0&page=%d",
                         yyyy, mm, page );
            setTargetURL( url );
            p = http_getEx( url, response, cookie );
            if ( !p || !(*p) || !(*response) ) 
                break;

            buf = response;
            if ( buf ) {
                if ( (page == 0) && (strstr( buf, url + 21 ) == NULL) ) {
                    goto next;          /* �� 21 := "http://clip.myblog.jp" */
                }                       /*    byte �����X�L�b�v             */

                if ( num == 0 ) {
                    p = strstr( buf, sjis2euc("��Clip��") );
                    if ( p ) {
                        p += 8;
                        while ( (*p < '0') || (*p > '9') )
                            p++;
                        num = atol( p );
                    }
                    else {
                        /* ���̊Ԃɂ� MyClip! �ꗗ��ʂ̎d�l���ς��A */
                        /*�u��Clip���v���\������Ȃ��Ȃ��Ă���           */
                        /*
                         * �N���b�v�������͂ŃJ�E���g
                         */
                        num = getNumOfMyClips( cookie, yyyy, mm );
                    }

                    if ( num <= 0 )
                        num = maxNum;

                    mp = (MyClip *)malloc( sizeof ( MyClip ) * num );
                    if ( !mp )
                        break;
                }

                cur = buf;
                do {
                    if ( cnt == 0 )
                        p = strstr( cur,
                                    "<table width=\"450\" height=\"200\" "
                                    "valign=\"middle\"" );
                    else
                        p = strstr( cur,
                                    "<table width=\"420\" border=\"0\" "
                                    "cellspacing=\"0\" cellpadding=\"0\">" );
                    if ( !p )
                        break;
                    cur = strchr( p, '>' );
                    if ( !cur )
                        break;
                    cur++;

                    p = strstr( cur, sjis2euc("�^�C�g��") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                        q--;
                    if ( q - cur > (512 - 1) )  /* {@@} */
                        break;                  /* {@@} */
                    strncpy( mp[cnt].title, cur, q - cur );
                    mp[cnt].title[q - cur] = NUL;
                    cur = p + 5;

                    p = strstr( cur, sjis2euc("�L��URL") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;

                    if ( !strncmp( cur, "<a href=\"", 9 ) ) {
                        cur += 9;
                        q = strchr( cur, '"' );
                        if ( q ) {
                            strncpy( mp[cnt].url, cur, q - cur );
                            mp[cnt].url[q - cur] = NUL;
                        }

                        while( *cur && (*cur != '>') )
                            cur++;
                        cur++;
                        while( (*cur == ' ')  || (*cur == '\t') ||
                               (*cur == '\r') || (*cur == '\n')    )
                            cur++;
                        p = q = strstr( cur, "</a>" );
                    }
                    else
                        p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    cur = p + 5;

                    p = strstr( cur, sjis2euc("�J�e�S��") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                        q--;
                    strncpy( catStr, cur, q - cur );
                    catStr[q - cur] = NUL;
                    cur = p + 5;
                    setTag( mp[cnt].tags, catStr );

                    p = strstr( cur, sjis2euc("�R�����g") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim );
                    if ( !p )
                        break;
                    cur = p += strlen( aim );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    if ( !strncmp( cur, "</td>", 5 ) )
                        mp[cnt].comment[0] = NUL;
                    else {
                        p = q = strstr( cur, "</td>" );
                        if ( !q )
                            break;
                        while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                            q--;
                        strncpy( mp[cnt].comment, cur, q - cur );
                        mp[cnt].comment[q - cur] = NUL;
                        cutBrCrLf( mp[cnt].comment );
                    }
                    cur = p + 5;

                    p = strstr( cur, sjis2euc("�ǉ�����") );
                    if ( !p )
                        break;
                    cur = p;
                    p = strstr( cur, aim2 );
                    if ( !p )
                        break;
                    cur = p += strlen( aim2 );
                    while( (*cur == ' ')  || (*cur == '\t') ||
                           (*cur == '\r') || (*cur == '\n')    )
                        cur++;
                    p = q = strstr( cur, "</td>" );
                    if ( !q )
                        break;
                    while ( (*(q - 1) == ' ') || (*(q - 1) == '\t') )
                        q--;
                    strncpy( timestr, cur, q - cur );
                    timestr[q - cur] = NUL;
                    q = euc2sjis( timestr );
                    if ( !q )
                        q = timestr;
                    mp[cnt].yyyy = atol( q );

                    q += 6;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].mm   = atol( q );

                    q = timestr + 10;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].dd   = atol( q );

                    q = timestr + 15;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].HH   = atol( q );

                    q = timestr + 19;
                    if ( *q == '0' )
                        q++;
                    mp[cnt].MM   = atol( q );
                    cur = p + 5;

                    mp[cnt].SS   = 0;

                    cnt++;
                    if ( cnt >= num )
                        break;
                } while ( p );
            }

            page++;
        } while ( preCnt != cnt );

        if ( !mp )
            break;

      next:
        mm--;
        if ( mm <= 0 ) {
            mm = 12;
            yyyy--;
        }
    } while ( (yyyy >= 2005) || (mm >= 3) ); /* �ŌÂ� MyClip! �� 2004�N3�� */

    free( response );
    free( request  );

    *numOfClips = num;

    return ( mp );
}

MyClip  *
getMyClip( const char *userName, const char *password, int *numOfClips )
{
    int     ret;
    char    cookie[MAX_COOKIE_LEN];
    MyClip  *mp = NULL;

    /* MyClip �� login */
    memset( cookie, 0x00, MAX_COOKIE_LEN );
    ret = loginMyClip( userName, password, cookie );
    if ( ret == 1 ) {   /* login ���� */
        /* MyClip �֓o�^�ς݂� clip ���擾 */
        mp = getMyClips( cookie, numOfClips );
    }

    return ( mp );
}


#ifdef  GET_MYCLIP_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *usernameForMyClip,
        char *passwordForMyClip,
        BOOL *useProxy,
        BOOL *useImport
    )
{
    int i, j;

    for ( i = 1; i < argc; i++ ) {
        if ( argv[i][0] == '-' ) {
            for ( j = 1; argv[i][j]; j++ ) {
                switch ( argv[i][j] ) {
                case 'u':
                    if ( argv[i][j + 1] ) {
                        strcpy( usernameForMyClip, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( usernameForMyClip, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( passwordForMyClip, &argv[i][j + 1] );
                        j = strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( passwordForMyClip, argv[i] );
                        j = strlen( argv[i] ) - 1;
                    }
                    break;

                case 'x':
                    *useProxy = !(*useProxy);
                    break;

                case 'i':
                    *useImport = !(*useImport);
                    break;
                }
            }
        }
    }
}

void
usage( void )
{
    fprintf( stderr, "getMyClip: MyClip! �� OPML �ϊ��o�̓c�[��\n" );
    fprintf( stderr,
             "    getMyClip [-x] [-i] [-u MyBlogList���[�U��] "
             "[-p MyBlogList�p�X���[�h]\n" );
    fprintf( stderr,
             "\t-x: proxy ���g��\n"
             "\t-i: �h���R��RSS �ɃC���|�[�g����\n" );
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy   = FALSE;
    BOOL    useImport  = FALSE;
    char    userName[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( userName,  0x00, MAX_USERIDLEN );
    memset( password,  0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv,
                  userName, password, &useProxy, &useImport );

    if ( !(userName[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* MyClip! �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getMyClip( userName, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  MyClip ���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "MyClip!", EUC2UTF, stdout );

        if ( useImport ) {
            int     i;
            char    *p;

            for ( i = 0; i < numOfClips; i++ ) {
                p = euc2utf( mp[i].title );
                if ( p )
                    strcpy( mp[i].title, p );

                p = euc2utf( mp[i].tags );
                if ( p )
                    strcpy( mp[i].tags, p );

                p = euc2utf( mp[i].comment );
                if ( p )
                    strcpy( mp[i].comment, p );
            }

            putDrecomRSS( userName, password, mp, numOfClips );
        }

        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_MYCLIP_EXE */

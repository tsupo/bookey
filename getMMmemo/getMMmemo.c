/*
 * clip saver <<getMMmemo>>
 *
 *      MM/Memo �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  18 Oct 2005
 *
 * $Log: /comm/bookey/getMMmemo/getMMmemo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    07/09/04 22:03 Tsujimura543
 * setVerbose() �̑�2�����ǉ��ɔ����ύX
 * 
 * 18    07/07/02 16:38 Tsujimura543
 * http://1470.net/mm/ �� http://mmmemo.1470.net/mm/ �֕ύX
 * (��URL�̂܂܂ł����Ȃ��擾�ł��邪�A�O�̂��߂ɕύX���Ă���)
 * 
 * 17    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 16    07/01/17 23:48 Tsujimura543
 * typo �C��
 * 
 * 15    07/01/17 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 14    06/12/08 15:17 Tsujimura543
 * getDateTime() �� getDateTimeFromDateString() �ɒu��������
 * 
 * 13    06/11/17 15:38 Tsujimura543
 * getEvaluation() �ɑ�2������ǉ������̂ɔ����ύX�����{
 * 
 * 12    06/11/17 14:25 Tsujimura543
 * �u�]���v�� title �ɖ��ߍ���ŋL�^�������(MM/Memo�݊�����)����߁A
 * MyClip �\���̂� evaluation �ɋL����������Ɉڍs
 * 
 * 11    06/09/25 15:23 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����h�~������{
 * 
 * 10    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 9a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 9     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 8     06/07/11 15:26 Tsujimura543
 * ��M�f�[�^�i�[�̈�̃T�C�Y�𑝂₷ (�������I�[�o�[�����΍�)
 * 
 * 7     05/11/02 16:54 Tsujimura543
 * <dc:subject>tag1, tag2, �c�c, tagN</dc:subject> �� , �̌�̋󔒕�����
 * �ǂݔ�΂��̂�Y��Ă���(���߁A�X�� putMMmemo() ���� getMMmemo()
 * ����ƁA�ǂ�ǂ�]���ȋ󔒂������Ă��܂��Ă���)�s����C��
 * 
 * 6     05/11/01 18:19 Tsujimura543
 * �����������t�@�N�^�����O
 * 
 * 5     05/11/01 18:09 Tsujimura543
 * (1) dc:date ���玞�������o��������1�̊֐��Ƃ��ēƗ�������
 * (2) ��L�֐��̃o�O�C��(�����b�̂����ꂩ��00�̂Ƃ��A�擾��������������
 *     �Ȃ��Ă���)
 * 
 * 4     05/11/01 17:45 Tsujimura543
 * �擾�����u�b�N�}�[�N�̃^�C�g���A�R�����g�A�^�O����̂Ƃ��ɃS�~�����邱
 * �Ƃ�����s��ɑΏ�����
 * 
 * 3     05/10/20 22:53 Tsujimura543
 * �R�����g�ɉ��s���܂܂��ꍇ�A��������悤�ɂ���
 * 
 * 2     05/10/19 16:52 Tsujimura543
 * loginMMmemo() �� mmMemo.c �Ƃ����t�@�C��������ĕ�������
 * 
 * 1     05/10/18 21:37 Tsujimura543
 * �ŏ��̔� (����m�F�ς�)
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getMMmemo/getMMmemo.c 1     09/05/14 3:48 tsupo $";
#endif

#define skipWhiteSpace( p ) \
            while ( (*(p) == ' ')  || \
                    (*(p) == '\t') || \
                    (*(p) == '\r') || \
                    (*(p) == '\n')    ) \
                (p)++;

/* ���j:
 *   �܂��A�u(����܂ł�)�o�b�N�A�b�v�v���擾������A�ŐV�̃u�b�N�}�[�N
 *   ���擾���A�}�[�W����
 */

/*
 * MM/Memo �̐������� XML �̃t�H�[�}�b�g
 *
 *  <item rdf:about="http://dublincore.org/">
 *   <title>[sw](3)�wDublin Core Metadata Initiative (DCMI)�x</title> 
 *   <link>http://dublincore.org/</link>
 *   <dc:creator>755����̃���</dc:creator>
 *   <dc:date>2005-10-17T19:08:59+09:00</dc:date>
 *   <dc:subject>dublinCore, DCMI, Ohaio, Ohio</dc:subject>
 *   <description>The Dublin Core Metadata Initiative</description>
 *  </item>
 *
 *       (1) title �̐擪�� [xx] ���u������ʁv�A(x) ���u�]���v�ɑ���
 *       (2) dc:subject �ɃW������(���̃\�[�V�����u�b�N�}�[�N�̃^�O����)��
 *           ',' ��؂�ŕ���
 *       (3) �u�֘AURL�v�̏��͎�����
 */
MyClip  *
getBookmarks( const char *response, int *numOfClips )
{
    MyClip      *mp = NULL;
    const char  *p  = response;
    const char  *q;
    char        *r;
    int         flag = 0;
    int         cnt  = 0;
    int         num  = 0;

    while ( *p ) {
        if ( *p != '<' ) {
            p++;
            continue;
        }

        if ( flag == 0 ) {
            if ( !strncmp( p, "<rdf:li rdf:resource=\"", 22 ) ) {
                cnt++;
                p += 22;
                continue;
            }
            if ( !strncmp( p, "</channel>", 10 ) ) {
                flag = 1;
                if ( cnt > 0 ) {
                    mp = (MyClip *)malloc( sizeof ( MyClip ) * cnt );
                    if ( !mp ) {
                        fputs("getBackup(): memory exhausted.\n", stderr);
                        break;
                    }
                    memset( mp, 0x00, sizeof ( MyClip ) * cnt );
                }
                else
                    break;
                p += 10;
                continue;
            }
        }

        if ( (flag == 1) &&
             !strncmp( p, "<item rdf:about=\"", 17 ) ) {
            flag = 2;
            p += 17;
            continue;
        }

        if ( flag == 2 ) {
            if ( !strncmp( p, "</rdf:RDF>",     10 ) )
                break;

            if ( !strncmp( p, "<title>",         7 ) ) {
                p += 7;
                skipWhiteSpace(p);
                q = strchr( p, '<' );
                if ( q ) {
                    strncpy( mp[num].title, p, q - p );
                    mp[num].title[q - p] = NUL;
                }
                continue;
            }

            if ( !strncmp( p, "<link>",          6 ) ) {
                p += 6;
                skipWhiteSpace(p);
                q = strchr( p, '<' );
                if ( q ) {
                    strncpy( mp[num].url, p, q - p );
                    mp[num].url[q - p] = NUL;
                }
                continue;
            }

            if ( !strncmp( p, "<dc:date>",       9 ) ) {
                p += 9;
                skipWhiteSpace(p);
                q = strchr( p, '<' );
                if ( q ) {
                    char    dateTime[32];

                    strncpy( dateTime, p, q - p );
                    dateTime[q - p] = NUL; // ���{����
                    getDateTimeFromDateString( dateTime,
                                               &(mp[num].yyyy),
                                               &(mp[num].mm),
                                               &(mp[num].dd),
                                               &(mp[num].HH),
                                               &(mp[num].MM),
                                               &(mp[num].SS) );
                }
                continue;
            }

            if ( !strncmp( p, "<dc:subject>",   12 ) ) {
                p += 12;
                skipWhiteSpace(p);
                q = strchr( p, '<' );
                if ( q ) {
                    char    *r;

                    strncpy( mp[num].tags, p, q - p );
                    mp[num].tags[q - p] = NUL;
                    r = mp[num].tags;
                    while ( *r ) {
                        if ( *r == ',' ) {
                            *r = ' ';
                            while ( *(r + 1) == ' ' )
                                strcpy( r + 1, r + 2 );
                        }
                        r++;
                    }
                }
                continue;
            }

            if ( !strncmp( p, "<description>",  13 ) ) {
                p += 13;
                skipWhiteSpace(p);
                q = strchr( p, '<' );
                if ( q ) {
                    strncpy( mp[num].comment, p, q - p );
                    mp[num].comment[q - p] = NUL;

                    /* MM/Memo �̃R�����g�ɂ͉��s���܂܂꓾�� */
                    while ( ((r = strchr(mp[num].comment, '\r')) != NULL) ||
                            ((r = strchr(mp[num].comment, '\n')) != NULL)    )
                        strcpy( r, r + 1 ); /* ���s����菜�� */
                }
                continue;
            }

            if ( !strncmp( p, "</item>",         7 ) ) {
                num++;
                if ( num >= cnt )
                    break;
                p += 7;
                continue;
            }
        }

        p++;
    }

    *numOfClips = num;
    return ( mp );
}

MyClip  *
getBackup( char *cookie, int *numOfClips )
{
    MyClip  *mp = NULL;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 36;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    strcpy( url, "http://mmmemo.1470.net/mm/export" );
    /*
    setUpReceiveBuffer( response, sz );
    http_headEx( url, response, cookie );
    if ( *response ) {
        p = strstr( response, "Content-Length: " );
        if ( !p )
            p = strstr( response, "Content-length: " );
        if ( p ) {
            size_t  len = atol( p + 16 );
            if ( len > sz ) {
                p = (char *)realloc( response, len + MAX_CONTENT_SIZE );
                if ( p ) {
                    response = p;
                    sz  = len + MAX_CONTENT_SIZE;
                }
            }
        }
    }
    */
    setUpReceiveBuffer( response, sz );
    p = http_getEx( url, response, cookie );
    if ( p && *p )
        mp = getBookmarks( p, numOfClips );
    free( response );

    return ( mp );
}

MyClip  *
getRecentBookmarks( MyClip **mp, const char *userID, int *numOfClips )
{
    MyClip  *mp2 = NULL;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];
    int     numOfClips1 = *numOfClips;
    int     numOfClips2 = 0;
    size_t  sz = MAX_CONTENT_SIZE * 24;

    response = (char *)malloc( sz );
    if ( !response )
        return ( *mp );
    setUpReceiveBuffer( response, sz );
    sprintf(url, "http://mmmemo.1470.net/mm/mylist.html/%s?mode=xml", userID);
    p = http_get( url, response );
    if ( p && *p )
        mp2 = getBookmarks( p, &numOfClips2 );
    free( response );

    if ( *mp && mp2 ) {
        int i, j;
        int cnt = 0;

        for ( i = 0; i < numOfClips1; i++ ) {
            for ( j = 0; j < numOfClips2; j++ ) {
                if ( !strcmp( (*mp)[i].url, mp2[j].url ) ) {
                    // �d��
                    mp2[j].url[0] = NUL;
                    cnt++;
                    break;
                }

                if (!strncmp(mp2[j].url,  "http://www.amazon.co.jp/",24) &&
                    !strncmp((*mp)[i].url,"http://www.amazon.co.jp/",24)   ) {
                    // ����: �o�b�N�A�b�v�̕��� ishinao ���̃A�\�V�G�C�gID�A
                    //       �ŐV�u�b�N�}�[�N�̕��̓��[�U�̃A�\�V�G�C�gID��
                    //       �Ȃ��Ă���
                    char    *q, *r;
                    q = strstr( mp2[j].url,   "/ASIN/" );
                    r = strstr( (*mp)[i].url, "/ASIN/" );
                    if ( q && r ) {
                        char    *qq, *rr;
                        q += 6;
                        r += 6;
                        qq = strchr( q, '/' );
                        rr = strchr( r, '/' );
                        if ( qq && rr && (qq - q == rr - r) &&
                             !strncmp( q, r, qq - q )           ) {
                            // �d��
                            strcpy( (*mp)[i].url, mp2[j].url );
                                   // ���[�U�̃A�\�V�G�C�gID���܂܂������c��
                            mp2[j].url[0] = NUL;
                            cnt++;
                            break;
                        }
                    }
                }
            }
        }

        if ( cnt < numOfClips2 ) {
            // �}�[�W���K�v
            MyClip *mp3 = (MyClip *)
                            malloc( sizeof ( MyClip ) * 
                                        (numOfClips1 + numOfClips2 - cnt) );
            if ( mp3 ) {
                for ( i = 0, j = 0; j < numOfClips2; j++ ) {
                    if ( mp2[j].url[0] == NUL )
                        continue;
                    strcpy( mp3[i].url,     mp2[j].url );
                    strcpy( mp3[i].title,   mp2[j].title );
                    strcpy( mp3[i].comment, mp2[j].comment );
                    strcpy( mp3[i].tags,    mp2[j].tags );
                    mp3[i].yyyy = mp2[j].yyyy;
                    mp3[i].mm   = mp2[j].mm;
                    mp3[i].dd   = mp2[j].dd;
                    mp3[i].HH   = mp2[j].HH;
                    mp3[i].MM   = mp2[j].MM;
                    mp3[i].SS   = mp2[j].SS;
                    i++;
                }
                for ( j = 0; j < numOfClips1; j++ ) {
                    strcpy( mp3[i].url,     (*mp)[j].url );
                    strcpy( mp3[i].title,   (*mp)[j].title );
                    strcpy( mp3[i].comment, (*mp)[j].comment );
                    strcpy( mp3[i].tags,    (*mp)[j].tags );
                    mp3[i].yyyy = (*mp)[j].yyyy;
                    mp3[i].mm   = (*mp)[j].mm;
                    mp3[i].dd   = (*mp)[j].dd;
                    mp3[i].HH   = (*mp)[j].HH;
                    mp3[i].MM   = (*mp)[j].MM;
                    mp3[i].SS   = (*mp)[j].SS;
                    i++;
                }

                free( *mp );
                *mp = mp3;
                *numOfClips = numOfClips1 + numOfClips2 - cnt;
            }
        }

        free( mp2 );
    }
    else if ( *mp == NULL ) {
        *mp = mp2;
        *numOfClips = numOfClips2;
    }

    return ( *mp );
}

MyClip  *
getMMmemo( const char *username, const char *password, int *numOfClips )
{
    MyClip  *mp = NULL;
    char    cookie[MAX_COOKIE_LEN];
    char    userID[32];
    int     ret;

    // MM/Memo �Ƀ��O�C�� (TypeKey �F��)
    memset( cookie, 0x00, MAX_COOKIE_LEN );
    memset( userID, 0x00, 32 );
    ret = loginMMmemo( username, password, cookie, userID );
    if ( ret == 1 ) {
        // �o�b�N�A�b�v���擾
        //   http://1470.net/mm/export �� GET
        mp = getBackup( cookie, numOfClips );

        // �ŐV�̃u�b�N�}�[�N���擾�A�o�b�N�A�b�v�ƃ}�[�W
        //   http://1470.net/mm/mylist.html/���[�UID?mode=xml �� GET
        mp = getRecentBookmarks( &mp, userID, numOfClips );

        // �u�]���v�̒��o�Ɓu�薼�v�̐��K��
        if ( mp && (*numOfClips > 0) ) {
            int i;
            for ( i = 0; i < *numOfClips; i++ )
                mp[i].evaluation = getEvaluation( mp[i].title, EUC2UTF );
        }
    }

    return ( mp );
}

#ifdef  GET_MM_MEMO_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
        char *password,
        BOOL *useProxy
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
        fprintf( stderr, "getMMmemo: MM/Memo �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
          "\tMM/Memo ����z���o�������e�� OPML �t�@�C���Ƃ��ďo�͂���\n");
        fprintf( stderr,
             "    getMMmemo [-x] -u TypeKey���[�U�� -p TypeKey�p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getMMmemo: get bookmarks from MM/Memo, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getMMmemo [-x] -u username -p password\n" );
        fprintf( stderr,
                 "      username: ID for TypeKey authentication\n"
                 "      password: password for TypeKey authentication\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    char    password[MAX_PASSWDLEN];
    int     numOfClips = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !(password[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );
#ifdef  _DEBUG
    setVerbose( TRUE, stderr );
#endif

    /* MM/Memo �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getMMmemo( username, password, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  MM/Memo ���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "MM/Memo", EUC2UTF, stdout );
        free( mp );
    }
    encodeURL( NULL );  // �̈���

    return ( 1 );
}
#endif  /* GET_MM_MEMO_EXE */

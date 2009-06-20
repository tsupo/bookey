/*
 * clip saver <<getBPT>>
 *
 *      BlogPeople Tags �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  27 Jun 2005
 *
 * $Log: /comm/bookey/getBPT/getBPT.c $
 * 
 * 1     09/05/14 4:23 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 27    07/01/18 13:53 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 26    06/11/17 13:52 Tsujimura543
 * �u�]���v�� title �ɖ��ߍ���ŋL�^�������(MM/Memo�݊�����)����߁A
 * MyClip �\���̂� evaluation �ɋL����������Ɉڍs
 * 
 * 25    06/10/20 21:26 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 24    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 23    06/07/21 20:17 Tsujimura543
 * BlogPeople Tags �̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 22    06/06/20 11:14 Tsujimura543
 * �u�R�����g�v���Ɋ܂܂����s(\r,\n)����菜���悤�ɂ���
 * 
 * 21    06/06/20 0:04 Tsujimura543
 * ����y�[�W��Ɂu�}�C���[�g�v����ƂȂ������݂���ꍇ�̏��������C��
 * 
 * 20    06/06/19 23:09 Tsujimura543
 * (1) �������I�[�o�[�����΍�����{ (�������T�C�Y�A�āX����)
 * (2) �u�b�N�}�[�N�̌���(=n�Ƃ���)��999���ȏ゠��ƁA(n%1000)�������擾
 *   ���Ȃ��s����C��
 * 
 * 19    06/06/06 22:22 Tsujimura543
 * �������I�[�o�[�����΍�����{ (�������T�C�Y�A�Ē���)
 * [�ۑ�: ���{�I�ȑ΍􂪕K�v]
 * 
 * 18    06/05/22 15:31 Tsujimura543
 * �������I�[�o�[�����΍�����{
 * 
 * 17    05/11/02 13:42 Tsujimura543
 * �u�]��(�}�C���[�g)�v�� MM/Memo �݊��`���� opml �ɏ����o���悤�ɂ���
 * 
 * 16    05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 15    05/10/31 21:41 Tsujimura543
 * BP_TAGS �Ƃ����^�O�������I�ɕt������̂���߂�
 * 
 * 14    05/09/30 17:42 Tsujimura543
 * outputOPML() �Ɉ�����ǉ�
 * 
 * 13    05/09/28 20:48 Tsujimura543
 * �O���ϐ��ւ̃A�N�Z�X��p�~
 * 
 * 12    05/09/28 13:44 Tsujimura543
 * getBPTags() ���u�b�N�}�[�N�Ǘ��c�[������Ăяo����悤�ɂ���
 * 
 * 11    05/09/27 18:30 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 10    05/09/26 20:47 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓������� (bug�C��)
 * 
 * 9     05/09/26 20:23 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓������� (�Â�)
 * 
 * 8     05/09/26 20:11 Tsujimura543
 * ���̃u�b�N�}�[�N�z�o���c�[���Ƃ̓�������
 * 
 * 7     05/09/26 19:37 Tsujimura543
 * �ϊ����ʂ�W���G���[�o�͂ɕ\������̂̓f�o�b�O�r���h���݂̂ɂ���
 * 
 * 6     05/09/26 18:53 Tsujimura543
 * �����������t�@�N�^�����O (�܂��܂����t�@�N�^�����O�̗]�n����܂���)
 * 
 * 5     05/09/26 18:45 Tsujimura543
 * �������� OPML �t�@�C���� title �� BlogPeople tags �ɂ���
 * 
 * 4     05/06/27 22:21 Tsujimura543
 * title ����(�Ɋi�[���ׂ�����)���E���Y��Ă����̂��C��
 * 
 * 3     05/06/27 21:36 Tsujimura543
 * OPML �t�@�C���� notes �������o�͂��Y��Ă����̂��C��
 * 
 * 2     05/06/27 21:28 Tsujimura543
 * ����m�F����
 * 
 * 1     05/06/27 20:48 Tsujimura543
 * �ŏ��̔�
 */

#include "myClip.h"
#include <math.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getBPT/getBPT.c 1     09/05/14 4:23 tsupo $";
#endif

/* BlogPeople Tags �ɓo�^�ς݂̃u�b�N�}�[�N��
 *   http://tags.blogpeople.net/user/���[�U��
 *   http://tags.blogpeople.net/user/���[�U��/1
 *     �c�c
 *   http://tags.blogpeople.net/user/���[�U��/n
 * �̊e�y�[�W����擾���� (n �̒l�� �u��xx�����@1�`20����\���v�Ƃ���
 * �\������ xx �̒l�����Ɍ��肷�邱�Ƃ��ł���)
 *
 * �Ȃ��A�u�b�N�}�[�N�̓o�^�����Ɋւ��āA���t�͎擾�ł��邪�����͎擾
 * �ł��Ȃ����߁A�{�c�[���ł͈ꗥ 0��0��0�b �Ƃ��Ď�舵�����Ƃɂ���B
 * �܂��A�J�e�S��(����)�͎擾�ł��Ȃ��B
 *
 * ����: �u���[�U���v�� BlogPeople �̃��[�U��(���O�C�����ɓ��͂��郁�[
 *       ���A�h���X)�ł͂Ȃ��A�u�b�N�}�[�N�T�[�r�X��V�K�ɗ��p�\������
 *       �Ƃ��Ɏw�肵�����O(�u�b�N�}�[�N�̖��O�Ƃ������A�f�B���N�g����)
 *       �ɂȂ�
 */

MyClip  *
getBPTags( const char *username, int *total, int *numOfClips )
{
    char    *response;
    char    url[MAX_URLLENGTH];
    char    *p, *q, *r, *s, *t, *u;
    int     num = 0, cnt = 0;
    int     maxNum = 20;    /* �b��l */
    int     maxCnt = 0;
    int     yyyy, mm, dd;
    MyClip  *mp = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 64;

    *total      = 0;
    *numOfClips = 0;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    sprintf( url, "http://tags.blogpeople.net/user/%s", username );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    p = http_get( url, response );
    if ( !p || !(*p) || !(*response) ) {
        free( response );
        return ( mp );
    }

    p = response;
    if ( p && *p ) {
        q = strstr( p, ">�S�u�b�N�}�[�N</a>(" );
        if ( q )
            *total = cnt = atol( q + 20 );
        else {
            q = strstr( p, "�����@1�`20����\��" );
            if ( q ) {
                do {
                    while ( (*(q - 1) >= '0') && (*(q - 1) <= '9') )
                        q--;
                    cnt += (int)(atol( q ) * pow( 1000.0, (double)num ));
                    num++;
                } while ( *--q == ',' );

                *total = cnt;
            }
            else {
                free( response );
                return ( mp );
            }
        }

        maxNum = ((cnt / 20) + 1) * 20;
        maxCnt = cnt / 20;
        cnt = 0;
        num = 0;
    }

    mp = (MyClip *)malloc( sizeof ( MyClip ) * maxNum );
    if ( mp ) {
        char    tags[80];

        memset( mp, 0x00, sizeof ( MyClip ) * maxNum );
        p = response;

        while ( *p ) {
            u = NULL;
            if ( !strncmp( p, "<div class=\"bookmark-title\">", 28 ) ) {
                q = p + 28;
                u = strstr( q, "</li>" );
                r = strstr( q, "<a href=\"" );
                if ( r ) {
                    r += 9;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( mp[num].url, r, s - r );
                        mp[num].url[s - r] = NUL;

                        q = strstr( r, "\">" );
                        if ( q ) {
                            q += 2;
                            r = strstr( q, "</a>" );
                            if ( r ) {
                                strncpy( mp[num].title, q, r - q );
                                mp[num].title[r - q] = NUL;
                                p = r + 4;
                            }
                            else
                                p = q;
                        }
                        else
                            p = s + 1;
                    }
                    else
                        p = r;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p, "<div class=\"bookmark-description\">", 34 ) ) {
                q = p + 34;
                while ( (*q == ' ')  || (*q == '\t') ||
                        (*q == '\r') || (*q == '\n')    )
                    q++;
                r = strstr( q, "<br />" );
                if ( r ) {
                    strncpy( mp[num].comment, q, r - q );
                    mp[num].comment[r - q] = NUL;

                    s = mp[num].comment;
                    while ( ((t = strchr( s, '\n' )) != NULL) ||
                            ((t = strchr( s, '\r' )) != NULL)    ) {
                        if ( (*(t + 1) == '\r') || (*(t + 1) == '\n') )
                            strcpy( t, t + 1 );
                        *t = ' ';
                    }

                    p = r + 6;
                }
                else
                    p = q;

                continue;
            }

            if ( !strncmp( p, "<div class=\"sublink\">", 21 ) ) {
                p = q = p + 21;
                r = strstr( q, "Tag: " );
                if ( r ) {
                    mp[num].tags[0] = NUL;
                    r += 5;
                    p = r;
                    do {
                        tags[0] = NUL;
                        s = strstr( r, "<a href=\"" );
                        t = strchr( r, ' ' );
                        if ( s && ((s < t) || (s == t + 1)) ) {
                            r = s + 9;
                            s = strchr( r, '>' );
                            if ( s ) {
                                s++;
                                t = strstr( s, "</a>" );
                                if ( t ) {
                                    strncpy( tags, s, t - s );
                                    tags[t - s] = NUL;
                                    p = r = t + 4;

                                    if ( mp[num].tags[0] != NUL )
                                        strcat( mp[num].tags, " " );
                                    strcat( mp[num].tags, tags );
                                }
                                else
                                    break;
                            }
                            else
                                break;
                        }
                        else
                            break;
                    } while ( r );

                    if ( !strncmp( p, "  <a href=\"/url/", 16 ) ) {
                        /* �u��:n�l�������N�v ���X�L�b�v */
                        p += 16;
                        q = strstr( p, "</a>" );
                        if ( q )
                            p = q + 4;
                    }
                    while ( p && ((*p < '0') || (*p > '9')) )
                        p++;
                    if ( p ) {
                        q = p;
                        yyyy = 2000 + (*q - '0') * 10 + (*(q + 1) - '0');
                        q += 2;

                        while ( *q && ((*q < '0') || (*q > '9')) )
                            q++;
                        mm   = (*q - '0') * 10 + (*(q + 1) - '0');
                        q += 2;

                        while ( *q && ((*q < '0') || (*q > '9')) )
                            q++;
                        dd   = (*q - '0') * 10 + (*(q + 1) - '0');
                        q += 2;

                        mp[num].yyyy = yyyy;
                        mp[num].mm   = mm;
                        mp[num].dd   = dd;
                        mp[num].HH   = 0;
                        mp[num].MM   = 0;
                        mp[num].SS   = 0;

                        p = q;

                        // �]��(�}�C���[�g)
                        if (((q = strstr(p, "alt=\"�}�C���[�g: ")) != NULL) &&
                            (q < u) ) {
                            long    rate;

                            q += 17;
                            rate = atol( q );
                            p = q + 1;

                            if ( rate > 0 ) {
#ifdef  OLD_FASHIONED
                                //   -- MM/Memo �݊��̕��@�ŋL�^����
                                //        title �̑O�� (�]��) ��t������
                                char    tmpTitle[BUFSIZ * 2];

                                sprintf( tmpTitle, "(%d)�w%s�x",
                                         rate, mp[num].title );
                                strcpy( mp[num].title, tmpTitle );
#else
                                // �u�]���v�� mp[num].evaluation �Ɋi�[����
                                mp[num].evaluation = rate;
#endif
                            }
                        }

                        num++;
                        if ( num >= maxNum )
                            break;
                        mp[num].tags[0] = NUL;

                        if ( (num % 20) == 0 ) {
                            /* ���̃y�[�W��ǂ� */
                            cnt++;
                            if ( cnt > maxCnt )
                                break;
                            memset( response, 0x00, MAX_CONTENT_SIZE * 20 );
                            sprintf( url,
                                     "http://tags.blogpeople.net/user/%s/%d",
                                     username, cnt );
                            setTargetURL( url );
                            setUpReceiveBuffer( response, sz );
                            p = http_get( url, response );
                            if ( !p || !(*p) || !(*response) )
                                break;
                            p = response;
                            continue;
                        }
                    }
                }

                continue;
            }

            p++;
        }
    }

    *numOfClips = num;
    free( response );

    return ( mp );
}

#ifdef  GET_BLOGPEOPLE_TAGS_EXE
void
setParam(
        int  argc,
        char *argv[],
        char *username,
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
        fprintf( stderr,
                 "getBPT: BlogPeople Tags �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tBlogPeople Tags ����z���o�������e�� OPML �t�@�C���Ƃ���"
                 "�o�͂���\n" );
        fprintf( stderr,
             "    getBPT [-x] -u ���[�U��\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
        fprintf( stderr,
                 "\t���[�U��: BlogPeople �Ƀ��O�C������Ƃ��̃��[�U��(���[��"
                 "�A�h���X)\n\t�ł͂Ȃ��ABlogPeople Tags �p�Ɏw�肵�����[�U��"
                 "���g�p����\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getBPT: get bookmarks from BlogPeople Tags, and output "
                 "them as OPML\n" );
        fprintf( stderr,
                 "    getBPT [-x] -u username\n" );
        fprintf( stderr, "\t-x: use http access via proxy server\n" );
        fprintf( stderr,
                 "\tusername: this is NOT E-mail address when log into "
                 "BlogPeople.\n\t\tSpecify the username as screen name for "
                 "BlogPeople Tags.\n" );
    }
}

int
main( int argc, char *argv[] )
{
    BOOL    useProxy = FALSE;
    char    username[MAX_USERIDLEN];
    int     numOfClips = 0;
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, &useProxy );

    if ( !(username[0]) )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* BlogPeople Tags �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getBPTags( username, &total, &numOfClips );

    if ( (total > 0) && (numOfClips < total) ) {
        if ( getLanguageCode() == 0x0411 )
            fprintf( stderr,
                     "�x��: �S %d �����A%d �������擾�ł��܂���ł���\n",
                     total, numOfClips );
        else
            fprintf( stderr,
                     "Warning: Only %d in %d all was able to be acquired.\n",
                     numOfClips, total );
    }

    if ( mp && (numOfClips > 0) ) {
        /*  BlogPeople Tags ���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "BlogPeople Tags", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_BLOGPEOPLE_TAGS_EXE */

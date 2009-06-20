/*
 * clip saver <<getLivedoorClip>>
 *
 *      livedoor �N���b�v �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  6 Jul 2006
 *
 * $Log: /comm/bookey/getLivedoorClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    08/02/23 4:00 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 18    08/02/23 3:57 Tsujimura543
 * (1) �T�[�o�� busy ��Ԃ��Ă����Ƃ���2�b�Ԋu�Ń��g���C(�ő�5��)����悤
 *     �ɂ��Ă݂�
 * (2) ����1������20���̃u�b�N�}�[�N��񂪓����Ă��邪�A���傤��20���ڂ�
 *     �u�b�N�}�[�N���v���C�x�[�g��������R18�t���OON�̏ꍇ�A���̃u�b�N�}�[
 *     �N�����X�L�b�v���Ă��܂��A�����Ńu�b�N�}�[�N�̎擾���I�����Ă���
 *     ���s����C��
 * 
 * 17    08/01/22 15:06 Tsujimura543
 * _getLivedoorClip() ���C��(18�փt���O�Ή��A�������[�v�h�~�����ǉ�)
 * 
 * 16    07/01/23 16:19 Tsujimura543
 * usage() �ŕ\�����镶�����C��
 * 
 * 15    07/01/19 22:05 Tsujimura543
 * _getLivedoorClip() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 14    07/01/17 23:31 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή�
 * (2) �R�}���h���C���ł��r���h�ł���悤�ɂ���
 * 
 * 13    06/12/07 17:25 Tsujimura543
 * �u���J��ԁv�̎擾����(�擾�^�C�~���O)���C��
 * 
 * 12    06/12/07 16:52 Tsujimura543
 * ���ۂ́u���J��ԁv�̒l�� mp[].publication �Ɋi�[����悤�ɂ���
 * 
 * 11    06/11/17 13:48 Tsujimura543
 * �u�]���v�� title �ɖ��ߍ���ŋL�^�������(MM/Memo�݊�����)����߁A
 * MyClip �\���̂� evaluation �ɋL����������Ɉڍs
 * 
 * 10    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() �𓱓��BMyClip �\���̊i�[�̈�m�ۏ�����
 * ���ʊ֐������Ă݂�
 * 
 * 9     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 8a    06/09/03 20:19 tsupo
 * cookie �܂����C��
 * 
 * 8     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 7     06/07/24 22:20 Tsujimura543
 * http �����i�[�̈�̃I�[�o�[�����h�~�@�\�𗘗p����悤�ɏC��
 * 
 * 6     06/07/24 20:55 Tsujimura543
 * �擪(�ŐV)�̃N���b�v���v���C�x�[�g���[�h�̏ꍇ�A�擾���e�ɉߕs����
 * ������s����C��(�擪�̃N���b�v���̂Ă��A�Ō�̃y�[�W�̃N���b�v
 * ���d�����Ď擾���Ă��܂�)
 * 
 * 5     06/07/21 17:47 Tsujimura543
 * livedoor�N���b�v�� html �̏��������ς����(2006�N7��20��)�e���ŁA
 * �N���b�v�̐擪��20���݂̂����擾�ł��Ȃ��Ȃ��Ă��܂������߁A�V����
 * html �ɑΉ�����悤�A����������������
 * 
 * 4     06/07/19 19:25 Tsujimura543
 * cookie ����R�ꃋ�[�g���������̂ŁA�C��
 * 
 * 3     06/07/12 15:51 Tsujimura543
 * 64 �� MAX_KEYLENGTH �ɒu��
 * 
 * 2     06/07/07 11:00 Tsujimura543
 * �u�]���v�̋L�^���@�� MM/Memo �݊��ɂ���
 * 
 * 1     06/07/06 19:52 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"
#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getLivedoorClip.c 1     09/05/14 3:48 tsupo $";
#endif

#define NUM_OF_CLIPS_PER_PAGE   20

int
_getLivedoorClip(
        const char *target,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    )
{
    char    url[MAX_URLLENGTH];
    BOOL    cont = TRUE;
    BOOL    isPrivate;
    char    *p, *q, *r, *s;
    char    *qq;
    int     num  = 0;
    int     cnt  = 0;
    int     unit = 200;
    int     rate;
    int     yy, mm, dd;
    char    postkey[MAX_KEYLENGTH];
    char    tmp[MAX_DESCRIPTION_LEN * 2];
    int     retry = 5;

    postkey[0] = NUL;
    strcpy( url, target );
    do {
        setTargetURL( url );
        setUpReceiveBuffer( response, sz );
        if ( cookie )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( !response || !(response[0]) ) {
            // ��������̏ꍇ
            if ( (num > 0) && (num < *total) ) {
                retry--;
                if ( retry > 0 ) {
                    Sleep( 2000 );
                    continue;
                }
            }
            break;
        }

        if ( *total == 0 ) {
            // �S���ŉ������邩�A�O�����Ē��ׂĂ���
            //   -- �������A�u���J�v��Ԃ̂��̂̑S�����Ȃ̂ŁA����J��
            //      �u�b�N�}�[�N�����݂���ꍇ�́A���ۂ̃u�b�N�}�[�N��
            //      �͂����Ƒ傫�Ȓl�ɂȂ�
            p = strstr( response, "class=\"myclip-clipcount\"" );
            if ( !p )
                p = strstr( response, "class=\"pager-total\"" );
            if ( p ) {
                p = strchr( p, '>' );
                if ( p ) {
                    while ( *p && ((*p <= '0') || (*p > '9')) )
                        p++;
                    if ( *p )
                        *total = atol( p );
                }
            }
        }

        // postkey �𒊏o
        p = strstr( response, "=\"postkey\" value=\"" );
        if ( p ) {
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( postkey, p, q - p );
                postkey[q - p] = NUL;
            }
        }

        // �u�b�N�}�[�N�𔲂��o��
        if ( !strcmp( url, "http://clip.livedoor.com/clips/tsupo?p=242" ) ) {
            Sleep( 1000 );
        }
        p = response;
        do {
            if ( mp ) {
                MyClip  *np;
                np = allocateMyClipIfNecessary( mp, unit, &cnt, num );
                if ( !np )
                    break;
                *mp = np;
            }
            if ( mpEx ) {
                MyClipEx    *np;
                np = allocateMyClipExIfNecessary( mpEx, unit, &cnt, num );
                if ( !np )
                    break;
                *mpEx = np;
            }

            if ( cookie ) {
                q  = strstr( p, "<li class=\"clip\" id=\"" );
                qq = strstr( p, "<li class=\"clip clip-" );
                if ( qq && ((qq < q) || !q))
                    q = qq;
            }
            else
                q = strstr( p, "<li class=\"clip\">" );
            if ( !q )
                break;

            s = strstr( q, "</li>" );
            if ( !s )
                break;
            qq = strchr( q, '>' );
            if ( !qq )
                break;
            p = qq + 1;

            rate = 0;

            // �n�b�V��
            if ( mpEx ) {
                q = strstr( p, "<a id=\"hash_" );
                if ( !q || (q > s) )
                    break;
                p = q + 12;
                q = strstr( p, "\" name=\"p_" );
                if ( !q || (q > s) )
                    break;
                p = q + 10;
                q = strchr( p, '"' );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;
                strcpy( (*mpEx)[num].entryID, tmp );
            }

            q = strstr( p, "<h4 class=\"clip-title\" id=\"" );
            s = strstr( p, "</li>" );
            if ( !q || !s )
                break;
            p = q + 27;

            // URL
            q = strstr( p, "<a href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 9;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            while ( ( r = strstr( tmp, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // �^�C�g��
            q = strstr( p, "\">" );
            if ( !q || (q > s) )
                break;
            p = q + 2;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjis( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( ((p = strchr(tmp, '\r')) != NULL) ||
                    ((p = strchr(tmp, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* ���s����菜�� */
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            // ���J���
            p = q + 4;
            isPrivate = FALSE;
            q = strstr( p, "<small class=\"clip-public\">" );
            if ( q && (q < s) ) {
                p = q + 27;
                q = strstr( p, "</small>" );
                r = strstr( p, "private" );
                if ( q && (q < s) ) {
                    if ( r && (r < q) )
                        isPrivate = TRUE;
                    p = q + 8;
                }
            }

            // �N���� (�����b�͎擾�ł��Ȃ�)
            q = strstr( p, "<span class=\"clip-date" );
            if ( !q || (q > s) )
                break;
            p = q + 22;
            while ( *p && ((*p < '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            yy = atol( p );
            p += 5;

            while ( *p && ((*p <= '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            mm = atol( p );

            while ( *p && ((*p >= '0') && (*p <= '9')) && (p < s) )
                p++;
            while ( *p && ((*p <= '0') || (*p > '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;
            dd = atol( p );

            if ( mp ) {
                (*mp)[num].yyyy = yy;
                (*mp)[num].mm   = mm;
                (*mp)[num].dd   = dd;
             // (*mp)[num].HH   = 0;
             // (*mp)[num].MM   = 0;
             // (*mp)[num].SS   = 0;
            }

            while ( *p && ((*p >= '0') && (*p <= '9')) && (p < s) )
                p++;
            if ( !(*p) || (p > s) )
                break;

            // �]��
            q = strstr( p, " src=\"/img/rate/pad/" );
            if ( !q )
                q = strstr( p, " src=\"/img/rate/" );
            if ( !q || (q > s) )
                break;
            p = q + 20;
            rate = atol( p );
            if ( (rate > 0) && (rate <= 5) ) {
                if ( mp )
                    (*mp)[num].evaluation = rate;
            }

            p = q + 4;
            q = strstr( p, "<div class=\"clip-tags\"" );
            if ( q && (q < s) ) {
                // �^�O
                int len;

                tmp[0] = NUL;
                p = q + 22;
                do {
                    q = strstr( p, "class=\"linkgray tag\">" );
                    if ( !q || (q > s) )
                        break;
                    p = q + 21;
                    q = strstr( p, "</a>" );
                    if ( !q )
                        break;

                    if ( tmp[0] == NUL )
                        len = 0;
                    else {
                        strcat( tmp, " " );
                        len = strlen( tmp );
                    }
                    strncat( tmp, p, q - p );
                    tmp[len + (q - p)] = NUL;

                    p = q + 4;
                } while ( p < s );
                if ( tmp[0] ) {
                    r = utf2sjis( tmp );
                    if ( r )
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );

                // �R�����g
                q = strstr( p, "<p class=\"notes\" " );
                if ( !q || (q > s) )
                    break;
                p = q + 17;
                q = strstr( p, "\">" );
                if ( !q || (q > s) )
                    break;
                p = q + 2;
                q = strstr( p, "</p>" );
                if ( !q || (q > s) )
                    break;
                strncpy( tmp, p, q - p );
                tmp[q - p] = NUL;

                r = utf2sjis( tmp );
                if ( r )
                    strcpy( tmp, r );
                while ( ((p = strchr(tmp, '\r')) != NULL) ||
                        ((p = strchr(tmp, '\n')) != NULL)    )
                    strcpy( p, p + 1 ); /* ���s����菜�� */
                if ( mp )
                    strcpy( (*mp)[num].comment, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].comment, tmp );

                p = q + 4;
            }

            // postkey ��ۑ�
            if ( mpEx )
                strcpy( (*mpEx)[num].remarks, postkey );

            // ���J��� ��ۑ�
            if ( isPrivate )
                if ( mp )
                    (*mp)[num].publication = PUB_PRIVATE;

            p = s + 5;

            num++;
        } while ( p && *p );

        assert( (num == *total) || (num % 20 == 0) );

        // ����
        cont = FALSE;
     // p = strstr( response, sjis2utf("class=\"linkgray\">����") );
        p = strstr(response, sjis2utf("title=\"���̃y�[�W\" rel=\"next\">"));
        if ( p ) {
            while ( (p >= response) && (*p != '?') )
                p--;
            if ( *p == '?' ) {
                char    page[16];
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( page, p, q - p );
                    page[q - p] = NUL;
                    sprintf( url, "%s%s", target, page );
                    cont = TRUE;
                    Sleep( 1000 );
                }
            }
        }
        else if ( num < *total ) {    
            char    preURL[MAX_URLLENGTH];

            if ( !strstr( response, "postkey" ) ) {
                // �u�b�N�}�[�N��񂪋�̏ꍇ (�T�[�o�[�� busy ���)
                if ( (num > 0) && (num < *total) ) {
                    retry--;
                    if ( retry > 0 ) {
                        cont = TRUE;
                        Sleep( 2000 );
                        continue;
                    }
                }
                break;
            }

            /* html�̃t�H�[�}�b�g�������ς���Ă��A�ȉ��̏����ŉ��Ƃ��؂蔲 */
            /* ������͂�(API ���ς��Ȃ���΁A�Ƃ����O��ł͂�����̂�) */
            strcpy( preURL, url );

            sprintf( url, "%s/?p=%d",
                     target,
                     (num + NUM_OF_CLIPS_PER_PAGE) / NUM_OF_CLIPS_PER_PAGE );
            if ( strcmp( url, preURL ) != 0 ) {
                cont = TRUE;
                Sleep( 1000 );
            }
        }

        retry = 5;
    } while ( cont );

    assert( num == *total );

    return ( num );
}

MyClip  *
getLivedoorClip(
        const char *userName,   /* (I) livedoor ID                    */
        const char *password,   /* (I) �p�X���[�h (�V�[�N���b�g���[�h */
                                /*     �̃u�b�N�}�[�N���擾�������ꍇ */
                                /*     �ɕK�v)                        */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�̃u�b�N�}�[�N(�̂����A�p�u���b�N
     *  ���[�h�̂���)��S���擾����(�v���C�x�[�g���[�h�̂��̂��擾��
     *  ��ɂ́AuserName �̃��[�U�� password �̎w����K�v�B
     */
    MyClip  *mp = NULL;
    char    target[MAX_URLLENGTH];
    char    *response;
    int     fd;
    char    *cookie = NULL;
    int     num = 0;
    size_t  sz;

    fd = fileno( stderr );
    if ( password && *password ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( !cookie ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "�������̊m�ۂɎ��s���܂���\n"
                        : "memory exhausted.\n",
                       stderr );
            return ( mp );
        }
        memset( cookie, 0x00, MAX_COOKIE_LEN );

        // livedoor�N���b�v��login (cookie ���擾)
        if ( !loginLivedoorClip( userName, password, cookie ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "livedoor�ւ� login �Ɏ��s���܂���\n"
                        : "livedoor clip: login failed.\n",
                       stderr );
            free( cookie );
            return ( mp );
        }
    }

    *total      = 0;
    *numOfClips = 0;
    sprintf( target, "http://clip.livedoor.com/clips/%s", userName );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response ) {
        if ( cookie )
            free( cookie );
        return ( mp );
    }

    // �}�C�N���b�v���擾
    num = _getLivedoorClip( target, cookie, &mp, NULL, response, sz, total );

    *numOfClips = num;

    free( response );
    if ( cookie )
        free( cookie );

    return ( mp );
}


#ifdef  GET_LIVEDOOR_CLIP_EXE
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
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( username, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    break;

                case 'p':
                    if ( argv[i][j + 1] ) {
                        strcpy( password, &argv[i][j + 1] );
                        j = (int)strlen( argv[i] ) - 1;
                    }
                    else if ( i + 1 < argc ) {
                        i++;
                        strcpy( password, argv[i] );
                        j = (int)strlen( argv[i] ) - 1;
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
        fprintf( stderr,
                 "getLC: livedoor �N���b�v �� OPML �ϊ��o�̓c�[��\n" );
        fprintf( stderr,
                 "\tlivedoor �N���b�v����z���o�������e�� OPML �t�@�C����"
                 "���ďo�͂���\n" );
        fprintf( stderr,
                 "    getLC [-x] -u ���[�U�� -p �p�X���[�h\n" );
        fprintf( stderr, "\t-x: proxy ���g��\n" );
    }
    else {
        // �p��
        fprintf( stderr,
                 "getLC: get bookmarks from livedoor clip, and output them "
                 "as OPML\n" );
        fprintf( stderr,
                 "    getLC [-x] -u username -p password\n" );
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
    int     total      = 0;
    MyClip  *mp = NULL;

    if ( argc <= 1 ) {
        usage();
        return ( 0 );
    }

    memset( username, 0x00, MAX_USERIDLEN );
    memset( password, 0x00, MAX_PASSWDLEN );

    if ( argc >= 2 )
        setParam( argc, argv, username, password, &useProxy );

    if ( !(username[0]) || !password[0] )
        return ( 0 );

    if ( useProxy )
        setUseProxy( useProxy );

    /* livedoor clip �֓o�^�ς݂̃u�b�N�}�[�N���擾 */
    mp = getLivedoorClip( username, password, &total, &numOfClips );

    if ( mp && (numOfClips > 0) ) {
        /*  livedoor clip �̃u�b�N�}�[�N���� OPML �t�@�C���֏����o�� */
        outputOPML( mp, numOfClips, "livedoor clip", SJIS2UTF, stdout );
        free( mp );
    }

    return ( 1 );
}
#endif  /* GET_LIVEDOOR_CLIP_EXE */

/*
 * clip saver <<getFC2bookmark>>
 *
 *      FC2BOOKMARK �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  29 Nar 2007
 *
 * $Log: /comm/bookey/getFC2bookmark.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     08/12/02 19:31 Tsujimura543
 * null�|�C���^�Q�Ƃ���������\���̂���ӏ��̑Ώ�
 * 
 * 5     07/08/24 1:18 Tsujimura543
 * FC2BOOKMARK �̃y�[�W�f�U�C���ύX�ɑΉ�
 * 
 * 4     07/03/30 16:52 Tsujimura543
 * �u���J��ԁv�擾������ǉ�
 * 
 * 3     07/03/30 13:43 Tsujimura543
 * �u�G���g��ID�v�擾������ǉ�
 * 
 * 2     07/03/29 23:02 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     07/03/29 15:06 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getFC2bookmark.c 1     09/05/14 3:48 tsupo $";
#endif

int
_getFC2Bookmark(
        const char *userName,
        char       *cookie,
        const char *uid,
        const char *cc,
        MyClip     **mp,
        MyClipEx   **mpEx,
        int        *total,
        char       *response,
        size_t     sz
    )
{
    char    url[MAX_URLLENGTH];
    BOOL    isPrivate = FALSE;
    BOOL    cont  = TRUE;
    int     num   = 0;
    int     cnt   = 0;
    int     unit  = 200;
    char    *p, *q, *r, *s;
    char    tmp[MAX_DESCRIPTION_LEN * 2];
    char    target[MAX_URLLENGTH];

    target[0] = NUL;
    if ( cookie && *cookie && *uid && *cc ) {
        isPrivate = TRUE;
        sprintf( url,
                 "http://bookmark.fc2.com/user/index?uid=%s&cc=%s",
                 uid, cc );
        strcpy( target, "http://bookmark.fc2.com/user" );
    }
    else {
        sprintf( url,
                 "http://bookmark.fc2.com/search/user/%s",
                 userName );
        strcpy( target, url );
    }

    do {
        setUpReceiveBuffer( response, sz );
        if ( isPrivate )
            http_getEx( url, response, cookie );
        else
            http_get( url, response );

        if ( *total == 0 ) {
            // �S���ŉ������邩�A�O�����Ē��ׂĂ���
            p = strstr( response, "<div id=\"content\">" );
            if ( p ) {
                p += 18;
                q = strstr( p, sjis2utf("����") );
                if ( q ) {
                    while ( (q > p) &&
                            ((*q < '0') || (*q > '9')) )
                        q--;
                    while ( (q > p) &&
                            ((*(q - 1) >= '0') && (*(q - 1) <= '9')) )
                        q--;
                    if ( (q > p) && (*q >= '0') && (*q <= '9') )
                        *total = atol( q );
                }
            }
        }

        // �u�b�N�}�[�N�𔲂��o��
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

            q = strstr( p, "<div id=\"b-" );
            if ( !q )
                break;
            p = q + 11;
            q = strstr( p, "<h4>" );
            if ( !q )
                break;

            if ( isPrivate && mp ) {
                // ���J�E����J
                r = strstr( p, "<p class=\"allow-access\">" );
                if ( r && (r < q) ) {
                    p = r + 24;
                    s = sjis2utf( "����J" );
                    if ( !strncmp( p, s, strlen(s) ) )
                        (*mp)[num].publication = PUB_PRIVATE;
                }
            }

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
            if ( mp )
                strcpy( (*mp)[num].url, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].url, tmp );

            // �^�C�g��
            p = r + 2;
            while ( (*p == ' ')  || (*p == '\t') ||
                    (*p == '\r') || (*p == '\n')    )
                p++;
            q = strstr( p, "</a>" );
            if ( !q )
                break;
            while ( (*(q - 1) == ' ')  || (*(q - 1) == '\t') ||
                    (*(q - 1) == '\r') || (*(q - 1) == '\n')    )
                q--;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            r = utf2sjisEx( tmp );
            if ( r )
                strcpy( tmp, r );
            while ( ( r = strstr( tmp, "&#39;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 5 ); /* &#39; �� ' �ɒu�� */
            }
            while ( ( r = strstr( tmp, "&quot;" ) ) != NULL ) {
                *r = '\'';
                strcpy( r + 1, r + 6 ); /* &quot; �� ' �ɒu�� */
            }
            if ( mp )
                strcpy( (*mp)[num].title, tmp );
            if ( mpEx )
                strcpy( (*mpEx)[num].title, tmp );

            p = q + 4;
            s = strstr( p, "</table>" );
            if ( !s )
                break;

            // �G���g��ID
            if ( isPrivate && mpEx ) {
                q = strstr( p, "_bookmark/" );
                if ( q ) {
                    p = q + 10;
                    q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( tmp, p, q - p );
                        tmp[q - p] = NUL;
                        strcpy( (*mpEx)[num].entryID, tmp );
                        p = q + 1;
                    }
                }
            }

            // �R�����g
            q = strstr( p, "<p class=\"description\">" );
            if ( q && (q < s) ) {
                p = q + 23;
                q = strstr( p, "<img " );
                if ( q ) {
                    p = q + 5;
                    q = strstr( p, "/>" );
                    if ( q )
                        p = q + 2;
                }
                while ( isWhiteSpace( *p ) )
                    p++;
                s = q = strstr( p, "</p>" );
                if ( q ) {
                    while ( isWhiteSpace( *(q - 1) ) )
                        q--;
                    strncpy( tmp, p, q - p );
                    tmp[q - p] = NUL;
                    r = utf2sjisEx( tmp );
                    if ( r )
                        strcpy( tmp, r );

                    while ( ( r = strstr( tmp, "&#39;" ) ) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 5 ); /* &#39; �� ' �ɒu�� */
                    }
                    while ( ( r = strstr( tmp, "&quot;" ) ) != NULL ) {
                        *r = '\'';
                        strcpy( r + 1, r + 6 ); /* &quot; �� ' �ɒu�� */
                    }
                    if ( mp )
                        strcpy( (*mp)[num].comment, tmp );
                    if ( mpEx )
                        strcpy( (*mpEx)[num].comment, tmp );

                    p = s + 4;
                    s = strstr( p, "</table>" );
                    if ( !s )
                        break;
                }
            }

            // �^�O
            q = strstr( p, "<p class=\"note\">" );
            if ( q && (q < s) ) {
                int len;

                tmp[0] = NUL;
                p = q + 16;
                s = strstr( p, "<span class=\"date\">" );
                if ( !s ) {
                    s = strstr( p, "</p>" );
                    if ( !s )
                        break;
                }
                do {
                    if ( isPrivate )
                        q = strstr( p, "<a href=\"/user/tag/" );
                    else
                        q = strstr( p, "<a href=\"/search/tag/" );
                    if ( !q || (q > s) )
                        break;
                    p = q + (isPrivate ? 19 : 22);
                    q = strstr( p, "\">" );
                    if ( !q || (q > s) )
                        break;
                    p = q + 2;
                    q = strstr( p, "</a>" );
                    if ( !q || (q > s) )
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
                    r = utf2sjisEx( tmp );
                    if ( r )
                        strcpy( tmp, r );
                }
                if ( mp )
                    strcpy( (*mp)[num].tags, tmp );
                if ( mpEx )
                    strcpy( (*mpEx)[num].tags, tmp );
                p = s;
            }

            // ���e����
            q = strstr( p, "<span class=\"date\">" );
            if ( !q )
                break;
            p = q + 19;
            q = strchr( p, '(' );
            if ( !q )
                break;
            p = q + 1;
            q = strchr( p, ')' );
            if ( !q )
                break;
            strncpy( tmp, p, q - p );
            tmp[q - p] = NUL;
            strcat( tmp, " +0900" );    /* {@@} */
            if ( mp )
                getDateTimeFromDateString( tmp,
                                           &((*mp)[num].yyyy),
                                           &((*mp)[num].mm),
                                           &((*mp)[num].dd),
                                           &((*mp)[num].HH),
                                           &((*mp)[num].MM),
                                           &((*mp)[num].SS) );
            p = q + 1;
            num++;
        } while ( p && *p );

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

    return ( num );
}


MyClip  *
getFC2Bookmark(
        const char *userName,   /* (I) ���[�U�� (FC2ID �܂��̓��[���A */
                                /*     �h���X)                        */
        const char *password,   /* (I) �p�X���[�h (����J�̃u�b�N�}�[ */
                                /*     �N���擾�������ꍇ�ɕK�v [���� */
                                /*     �ɁAuserName �Ŏw�肷��̂�    */
                                /*     FC2ID �ł͂Ȃ��A���[���A�h���X */
                                /*     �ł���K�v������])             */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    )
{
    /*
     *  userName �Ŏw�肳�ꂽ���[�U�̃u�b�N�}�[�N(�̂����A���J�����
     *  �������)��S���擾����(����J�̂��̂��擾����ɂ́AuserName
     *  �̃��[�U�� password �̎w����K�v)
     */
    MyClip  *mp = NULL;
    char    *response;
    int     fd;
    char    *cookie = NULL;
    size_t  sz  = MAX_CONTENT_SIZE * 20;
    int     num = 0;
    char    uid[MAX_NAMELEN];
    char    cc[MAX_KEYLENGTH];

    *numOfClips = 0;
    uid[0] = NUL;
    cc[0]  = NUL;

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    fd = fileno( stderr );
    if ( password && *password ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( !cookie ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "�������̊m�ۂɎ��s���܂���\n"
                        : "memory exhausted.\n",
                       stderr );
            free( response );
            return ( mp );
        }
        memset( cookie, 0x00, MAX_COOKIE_LEN );

        // FC2BOOKMARK ��login (cookie ���擾)
        if ( !loginFC2Bookmark( userName, password, cookie, uid, cc ) ) {
            if ( (fd >= 0) && isatty( fd ) )
                fputs( getLanguageCode() == 0x0411
                        ? "FC2BOOKMARK �ւ� login �Ɏ��s���܂���\n"
                        : "FC2BOOKMARK: login failed.\n",
                       stderr );
            free( response );
            free( cookie );
            return ( mp );
        }
    }

    // �u�b�N�}�[�N�̎擾
    num = _getFC2Bookmark( userName, cookie, uid, cc,
                           &mp, NULL, total, response, sz );
    *numOfClips = num;

    if ( cookie )
        free( cookie );
    free( response );

    return ( mp );
}
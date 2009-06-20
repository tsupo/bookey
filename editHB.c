/*
 *  editHB.c
 *      �u�w�胆�[�U�� �͂Ăȃu�b�N�}�[�N �Ŏg���Ă���^�O�̈ꗗ�v���擾����
 *          written by H.Tsujimura  29 Jan 2007 / 30 Jan 2007
 *
 * $Log: /comm/bookey/editHB.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     08/12/15 23:56 Tsujimura543
 * _getTagListOnHatenaBookmark() ��V�K�쐬
 * (�T�C�h�o�[�ɕ\������Ă���^�O�ꗗ���擾����֐��B�T�C�h�o�[��
 * �^�O�ꗗ��\�����Ȃ��ݒ�ɂ��Ă���ꍇ�́A�ꎞ�I�ɕ\������ݒ�
 * �ɂ�����A�^�O�ꗗ���擾���A���̌�A�ݒ�����ɖ߂��Ă���)
 * 
 * 2     07/01/30 18:47 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 1     07/01/30 18:44 Tsujimura543
 * getTagListOnHatenaBookmark() �ɑ������鏈���� UserInfo.cpp ����
 * �����A�Ɨ�������
 */

#include "myClip.h"
#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editHB.c 1     09/05/14 3:48 tsupo $";
#endif

char *
getRks( char *rks, const char *htmlSrcCode );

void
getConfigValue(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r, *s;
    char    target[BUFSIZ];
    char    buf[MAX_CONTENT_SIZE];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    if ( p && (p < formEnd) ) {
        q = strstr( p, "value=\"" );
        r = strstr( p, "/>" );
        if ( q && r && (q < r) && (r < formEnd) ) {
            q += 7;
            s = strchr( q, '"' );
            if ( s && (s < r) ) {
                sprintf( buf, "&%s=", name );
                strcat( setting, buf );

                strncpy( buf, q, s - q );
                buf[s - q] = NUL;
                strcat( setting, encodeURL(buf) );
            }
        }
        else {
            q = p;
            while ( q > formStart ) {
                q--;
                if ( !strncmp( q, "value=\"", 7 ) ) {
                    q += 7;
                    s = strchr( q, '"' );
                    if ( s && (s < p) ) {
                        sprintf( buf, "&%s=", name );
                        strcat( setting, buf );

                        strncpy( buf, q, s - q );
                        buf[s - q] = NUL;
                        strcat( setting, encodeURL(buf) );
                    }
                    break;
                }
            }
        }
    }
}

void
getConfigValueChecked(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r, *s;
    char    target[BUFSIZ];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    if ( p && (p < formEnd) ) {
        r = p;
        while ( p > formStart ) {
            p--;
            if ( !strncmp( p, "<input ", 7 ) ) {
                s = p;
                p += 7;
                q = strstr( p, "checked" );
                if ( q ) {
                    if ( q < r ) {
                        getConfigValue( name, setting, s, formEnd );
                    }
                    else {
                        s = r + strlen( target );
                        getConfigValueChecked( name, setting, s, formEnd );
                    }
                    break;
                }
            }
        }
    }
}

void
getConfigValueSelected(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r, *s;
    char    target[BUFSIZ];
    char    buf[MAX_CONTENT_SIZE];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    if ( p && (p < formEnd) ) {
        p += strlen( target );
        q = strstr( p, "</select>" );
        if ( q && (q < formEnd) ) {
            r = strstr( p, "selected" );
            if ( r && (r < q) ) {
                while ( r > formStart ) {
                    r--;
                    if ( !strncmp( r, "value=\"", 7 ) ) {
                        r += 7;
                        s = strchr( r, '"' );
                        if ( s && (s < q) ) {
                            sprintf( buf, "&%s=", name );
                            strcat( setting, buf );

                            strncpy( buf, r, s - r );
                            buf[s - r] = NUL;
                            strcat( setting, encodeURL(buf) );
                        }
                        break;
                    }
                }
            }
        }
    }
}

void
getConfigValueGroup(
        const char *name,
        char       *setting,
        const char *formStart,
        const char *formEnd )
{
    char    *p, *q, *r;
    char    target[BUFSIZ];

    sprintf( target, "name=\"%s\"", name );
    p = strstr( formStart, target );
    while ( p && (p < formEnd) ) {
        q = strchr( p, '>' );
        if ( q < formEnd ) {
            while ( p > formStart ) {
                p--;
                if ( *p == '<' ) {
                    r = strstr( p, "checked" );
                    if ( r && (r < q) )
                        getConfigValue( name, setting, p, q );

                    p = strstr( q + 1, target );
                    break;
                }
            }
        }
    }
}

char    *
getConfig( const char *response, char *setting )
{
    char    *p, *s;

    p = strstr( response, "id=\"config-container\"" );
    if ( p ) {
        p += 21;
        s = strstr( p, "</form>" );
        if ( s ) {
            // btitle
            getConfigValue( "btitle", setting, p, s );

            // sitename
            getConfigValue( "sitename", setting, p, s );

            // siteurl
            getConfigValue( "siteurl", setting, p, s );

            // status
            getConfigValueChecked( "status", setting, p, s );

            // allowuser
            getConfigValue( "allowuser", setting, p, s );

            // allowgroup (�~ �����O���[�v����)
            getConfigValueGroup( "allowgroup", setting, p, s );

            // sendmailinterval
            getConfigValueSelected( "sendmailinterval", setting, p, s );

            // sendmailto
            getConfigValueSelected( "sendmailto", setting, p, s );

            // ignore_users
            getConfigValue( "ignore_users", setting, p, s );

            // hotthreshold
            getConfigValueChecked( "hotthreshold", setting, p, s );

            // include_news
            getConfigValueChecked( "include_news", setting, p, s );

            // linktarget
            getConfigValue( "linktarget", setting, p, s );

            // dateview
            getConfigValueChecked( "dateview", setting, p, s );

            // pagecount
            getConfigValueSelected( "pagecount", setting, p, s );

            // favoritepagecount
            getConfigValueSelected( "favoritepagecount", setting, p, s );

            // tagsuggest
            getConfigValueChecked( "tagsuggest", setting, p, s );

            // module_StarFriends
            getConfigValueChecked( "module_StarFriends", setting, p, s );

            // module_Asin
            getConfigValueChecked( "module_Asin", setting, p, s );

            // module_Group
            getConfigValueChecked( "module_Group", setting, p, s );
        }
    }

    return ( setting );
}


/* �^�O�ꗗ�̎擾 */
int
_getTagListOnHatenaBookmark(
        const char *username,   /* (I) ���[�U��         */
        const char *password,   /* (I) �p�X���[�h       */
        long       *numOfTags,  /* (I) �擾����^�O�̐� */
                                /* (O) �擾�����^�O�̐� */
        TagList    *lp          /* (O) �^�O�ꗗ         */
    )
{
    int     num = 0;
    char    *cookie;
    int     ret;

    if ( !username  || !(*username)      ||
         !password  || !(*password)      ||
         !numOfTags || (*numOfTags <= 0) ||
         !lp                                )
        return ( num );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( num );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* �͂ĂȂ� login */
    ret = loginHatenaBookmark( username, password, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    *setting = NULL;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 32;
        BOOL    needToReset = FALSE;
        char    *p, *q, *r;

        ret = FALSE;

        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request ) {
            free( cookie );
            return ( num );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( num );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

        // �u�^�O�ꗗ�̕\���v�ݒ�擾
        sprintf( url, "http://b.hatena.ne.jp/%s/config", username );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        if ( *response ) {
            char    rks[MAX_KEYLENGTH];

            /* rks �̒l���擾 */
            getRks( rks, response );

            // �u�^�O�ꗗ�̕\���v���u�^�O�ꗗ��\�����Ȃ��v�ɐݒ肳��Ă���
            // �ꍇ�A�ꎞ�I�Ɂu�^�O�ꗗ��\������v�ɐ؂�ւ���
            p = strstr( response, "id=\"showtags-on\"" );
            if ( p ) {
                r = p;
                while ( p > response ) {
                    p--;
                    if ( !strncmp( p, "<input ", 7 ) ) {
                        p += 7;
                        q = strstr( p, "checked" );
                        if ( q ) {
                            if ( q < r )
                                needToReset = FALSE;    // showtags-on
                            else {
                                needToReset = TRUE;     // showtags-off

                                // �ݒ�ۑ�
                                setting = (char *)malloc( MAX_CONTENT_SIZE );
                                if ( setting ) {
                                    *setting = NUL;
                                    getConfig( response, setting );
                                }

                                // �ݒ�ؑ� (showtags-off �� showtags-on)
                                sprintf( request,
                                         "rks=%s&"
                                         "showtags=1",
                                         rks );
                                if ( setting && *setting )
                                    strcat( request, setting );

                                setUpReceiveBuffer( response, sz );
                                http_postEx(
                                    url, "application/x-www-form-urlencoded",
                                    request, response, cookie );
                            }
                        }
                        ret = TRUE;
                        break;
                    }
                }
            }
        }

        if ( ret ) {
            ret = FALSE;

            // ���[�U�́u�͂Ăȃu�b�N�}�[�N�v�g�b�v�y�[�W���擾���A
            // �E�T�C�h�o�[�ɕ\������Ă���u�^�O�v�̈ꗗ�𒊏o
            sprintf( url, "http://b.hatena.ne.jp/%s/", username );
            setUpReceiveBuffer( response, sz );
            http_getEx( url, response, cookie );

            if ( *response ) {
                p = strstr( response, "id=\"tags\"" );
                if ( p ) {
                    p += 9;

                    do {
                        q = strstr( p, " class=\"tag\"" );
                        if ( !q )
                            break;
                        q += 12;

                        r = strchr( q, '>' );
                        if ( !r )
                            break;

                        p = r + 1;
                        q = strstr( p, "</a>" );
                        if ( !q )
                            break;

                        strncpy( lp[num].tag, p, q - p );
                        lp[num].tag[q - p] = NUL;

                        num++;
                    } while ( num < *numOfTags );
                }
            }

            // �u�^�O�ꗗ�̕\���v�̐ݒ�����ɖ߂� (�K�v������ꍇ)
            if ( needToReset ) {
                sprintf( url, "http://b.hatena.ne.jp/%s/config", username );
                setUpReceiveBuffer( response, sz );
                http_getEx( url, response, cookie );

                if ( *response ) {
                    char    rks[MAX_KEYLENGTH];

                    /* rks �̒l���擾 */
                    getRks( rks, response );

                    // �ݒ蕜�A (showtags-on �� showtags-off)
                    sprintf( request,
                             "rks=%s&"
                             "showtags=0",
                             rks );
                    if ( setting ) {
                        if ( *setting )
                            strcat( request, setting );
                        free( setting );
                        setting = NULL;
                    }

                    setUpReceiveBuffer( response, sz );
                    http_postEx(
                        url, "application/x-www-form-urlencoded",
                        request, response, cookie );
                }
            }


            if ( setting )
                free( setting );
        }

        free( response );
        free( request );
    }

    *numOfTags = num;
    free( cookie );

    return ( num );
}

TagList *
getTagListOnHatenaBookmark(
        const char *username,
        const char *password,
        int        *numOfTags )
{
    TagList *p = NULL;
#ifdef  BEFORE_20081125
    long    num = 1000; // �ő�1000�܂ł����擾�ł��Ȃ�
#else
    long    num = 5000; // �ő�5000�܂ł����擾�ł��Ȃ�
#endif

    *numOfTags = 0;

    p = (TagList *)malloc( sizeof (TagList) * num );
    if ( p ) {
#ifdef  BEFORE_20081125
        *numOfTags = getListOfTagsOnHatena( username, password, &num, p );
#else
        *numOfTags = _getTagListOnHatenaBookmark(username, password, &num, p);
#endif
    }

    return ( p );
}

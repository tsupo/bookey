/*
 * tumblr.c : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      tumblr �֘A ���[�e�B���e�B�֐��Q
 *          written by H.Tsujimura  29 May 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/tumblr.c $
 * 
 * 1     09/05/29 8:31 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 2     09/05/29 0:20 Tsujimura543
 * ����m�F�I��
 * 
 * 1     09/05/29 0:18 Tsujimura543
 * �ŏ��̔� (BloGolEe�����ɍ쐬�����\�[�X�𗬗p)
 */

#include "xmlRPC.h"
#include "tumblr.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/tumblr.c 1     09/05/29 8:31 tsupo $";
#endif


int
getBlogIDsTumblr(
    const char *userName,       // (I) ���[�U�� (���[���A�h���X)
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾����/�擾���� blog ���̐�
    BLOGINF    *blogInfo )      // (O) �擾���� blog ���
{
    char    cookie[MAX_COOKIE_LEN];
    char    url[MAX_URLLENGTH];
    char    name[MAX_BLOGNAMELENGTH];
    char    id[MAX_BLOGIDLENGTH];
    int     numOfBlogs = 0;
    size_t  sz  = MAX_CONTENT_SIZE;
    BOOL    ret = FALSE;
    char    request[BUFSIZ];
    char    *response = (char *)malloc( sz );

    if ( !response )
        return ( ret );

    cookie[0] = NUL;
    sprintf( request,
             "email=%s&"
             "password=%s",
             userName, password );

    setUpReceiveBuffer( response, sz );
    http_postEx( APIURL_TUMBLR_ACOUNT,
                 "application/x-www-form-urlencoded",
                 request, response, cookie );


    if ( *response ) {
        char    *p = strstr( response, "<tumblelog title=\"" );
        char    *q;
        char    *r;
        char    *s;

        while ( p ) {
            url[0]  = NUL;
            name[0] = NUL;
            id[0]   = NUL;
            blogInfo[numOfBlogs].blogName[0] = NUL;
            blogInfo[numOfBlogs].url[0]      = NUL;
            blogInfo[numOfBlogs].blogID[0]   = NUL;

            p += 18;
            q = strchr( p, '"' );
            r = strstr( p, "/>" );
            if ( !q || !r )
                break;

            if ( q < r ) {
                strncpy( name, p, q - p );
                name[q - p] = NUL;
                s = utf2sjis( name );
                strcpy( blogInfo[numOfBlogs].blogName, s ? s : name );

                p = q + 1;
            }

            q = strstr( p, "url=\"" );
            if ( q && (q < r) ) {
                p = q + 5;
                q = strchr( p, '"' );
                if ( q && (q < r) ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                    strcpy( blogInfo[numOfBlogs].url, url );

                    s = strstr( url, "http://" );
                    if ( s ) {
                        strcpy( blogInfo[numOfBlogs].blogID, s + 7 );
                        s = blogInfo[numOfBlogs].blogID;
                        if ( s[strlen(s) - 1] == '/' )
                            s[strlen(s) - 1] = NUL;
                    }

                    p = q + 1;
                }
            }
            else
                strcpy( blogInfo[numOfBlogs].url, "(private)" );

            q = strstr( p, "id=\"" );
            if ( q && (q < r) ) {
                p = q + 4;
                q = strchr( p, '"' );
                if ( q && (q < r) ) {
                    strncpy( id, p, q - p );
                    id[q - p] = NUL;
                    strcpy( blogInfo[numOfBlogs].blogID, id );

                    p = q + 1;
                }
            }

            q = p;
            p = strstr( q, "<tumblelog title=\"" );
            numOfBlogs++;

            if ( numOfBlogs >= *numberOfBlogs )
                break;
        }

        ret = TRUE;
        *numberOfBlogs = numOfBlogs;
    }

    free( response );

    return ( numOfBlogs );
}

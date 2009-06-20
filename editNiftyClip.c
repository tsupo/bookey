/*
 *  editNiftyClip.c
 *      �j�t�e�B�N���b�v�֓o�^�ς݂̃u�b�N�}�[�N��ҏW���邽�߂̊e��֐��Q
 *          written by H.Tsujimura  30 Jan 2007
 *
 * $Log: /comm/bookey/editNiftyClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/03/17 18:23 Tsujimura543
 * 2008�N3��11���́u@nifty�N���b�v�v���j���[�A���ɑΉ�����
 * 
 * 3     07/01/30 21:31 Tsujimura543
 * �R�����g�� typo ���C��
 * 
 * 2     07/01/30 21:30 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     07/01/30 19:20 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"
#include "niftyClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/editNiftyClip.c 1     09/05/14 3:48 tsupo $";
#endif

// �j�t�e�B�N���b�v�ł́AJSON �𗘗p����(�d�l�ڍׂ�����J��)API���g���ă^�O
// �ꗗ�̎擾�A�u���A�폜�Ȃǂ��ł��� [����: 2008�N3��11���̃��j���[�A����
// �����AUSERNAME �̎w�肪�K�v�ɂȂ���]
//    (1) �^�O�ꗗ�擾
//      http://clip.nifty.com/ajax/edittag/USERNAME ��
//          command=init&_=
//      �� POST
//    (2) �^�O�̒u��(�^�O�̓���)
//      http://clip.nifty.com/ajax/edittag/USERNAME ��
//          command=fusion&select_tags=�����O�̃^�O&select_tag=������̃^�O&_=
//      �� POST
//    (3) �^�O�̍폜
//      http://clip.nifty.com/ajax/edittag/USERNAME ��
//          command=delete&select_tags=�폜�������^�O&_=
//      �� POST
//    (4) �o���[���\���p�̃e�L�X�g�̎擾
//      http://clip.nifty.com/ajax/edittag/USERNAME ��
//          command=balloon&select_tag=���ڂ��Ă���^�O&_=
//      �� POST (select_tags �ł͂Ȃ� select_tag �ł��邱�Ƃɒ���)


/*
 *  �u�w�胆�[�U�� �j�t�e�B�N���b�v �Ŏg���Ă���^�O�̈ꗗ�v���擾����
 */

TagList *
getTagListOnNiftyClip(
        const char *username,
        const char *password,
        int        *numOfTags )
{
    TagList *tagList = NULL;
    int     num = 0;
    char    cookie[MAX_COOKIE_LEN];

    *numOfTags = 0;
    cookie[0]  = NUL;

    if ( loginNiftyClip( username, password, cookie ) ) {
        char    url[MAX_URLLENGTH];
        char    request[MAX_CONTENT_SIZE];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    screenname[80];
        char    targetURL[MAX_URLLENGTH];

        response = (char *)malloc( sz );
        if ( !response )
            return ( tagList );

        screenname[0] = NUL;
        targetURL[0] = NUL;
        getScreenNameOnNiftyClip( screenname, targetURL,
                                  response, sz, cookie );

        sprintf( url, "http://clip.nifty.com/ajax/edittag/%s", screenname );
        strcpy( request, "command=init&_=" );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

        if ( *response ) {
            char        *p, *q;
            const char  *target = "{\"name\":\"";

            p = response;
            while ( ( q = strstr( p, target ) ) != NULL ) {
                num++;
                p = q + 9;
            }

            if ( num > 0 ) {
                int num2 = 0;

                tagList = (TagList *)malloc( sizeof (TagList) * num );
                if ( tagList ) {
                    TagList *pp = tagList;

                    p = response;
                    while ( ( q = strstr( p, target ) ) != NULL ) {
                        p = q + 9;
                        q = strstr( p, "\"," );
                        if ( !q )
                            q = strstr( p, "\"}" );
                        if ( q ) {
                            strncpy( pp->tag, p, q - p );
                            pp->tag[q - p] = NUL;
                            p = q + 2;
                            pp++;
                            num2++;
                        }
                    }
                }

                if ( num != num2 )
                    num = num2;
            }
        }

        free( response );
    }

    *numOfTags = num;

    return ( tagList );
}



/* �^�O�̍폜 */
BOOL
removeTagFromBookmarksOnNiftyClip(
        const char *username,
        const char *password,
        const char *tag )
{
    BOOL    ret = FALSE;
    char    cookie[MAX_COOKIE_LEN];

    cookie[0] = NUL;

    if ( loginNiftyClip( username, password, cookie ) ) {
        char    url[MAX_URLLENGTH];
        char    *targetTag;
        char    request[MAX_CONTENT_SIZE];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    screenname[80];
        char    targetURL[MAX_URLLENGTH];

        response = (char *)malloc( sz );
        if ( !response )
            return ( ret );

        screenname[0] = NUL;
        targetURL[0] = NUL;
        getScreenNameOnNiftyClip( screenname, targetURL,
                                  response, sz, cookie );

        sprintf( url, "http://clip.nifty.com/ajax/edittag/%s", screenname );
        targetTag = sjis2utf( tag );
        sprintf( request,
                 "command=delete&"
                 "select_tags=%s&"
                 "_=",
                 encodeURL( targetTag ? targetTag : tag ) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"status\"" );
            if ( p ) {
                p += 8;
                p = strstr( p, "\"code\":\"0\"" );
                if ( p )
                    ret = TRUE;
            }
        }

        free( response );
    }

    return ( ret );
}

/* �^�O�̒u�� */
BOOL
renameTagFromBookmarksOnNiftyClip(
        const char *username,
        const char *password,
        const char *oldTag,
        const char *newTag )
{
    BOOL    ret = FALSE;
    char    cookie[MAX_COOKIE_LEN];

    cookie[0] = NUL;

    if ( loginNiftyClip( username, password, cookie ) ) {
        char    url[MAX_URLLENGTH];
        char    *targetTag;
        char    request[MAX_CONTENT_SIZE];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;
        char    screenname[80];
        char    targetURL[MAX_URLLENGTH];

        response = (char *)malloc( sz );
        if ( !response )
            return ( ret );

        screenname[0] = NUL;
        targetURL[0] = NUL;
        getScreenNameOnNiftyClip( screenname, targetURL,
                                  response, sz, cookie );

        sprintf( url, "http://clip.nifty.com/ajax/edittag/%s", screenname );
 
        targetTag = sjis2utf( oldTag );
        sprintf( request,
                 "command=fusion&"
                 "select_tags=%s&",
                 encodeURL( targetTag ? targetTag : oldTag ) );
        
        targetTag = sjis2utf( newTag );
        sprintf( request + strlen(request),
                 "select_tag=%s&"
                 "_=",
                 encodeURL( targetTag ? targetTag : newTag ) );

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "\"status\"" );
            if ( p ) {
                p += 8;
                p = strstr( p, "\"code\":\"0\"" );
                if ( p )
                    ret = TRUE;
            }
        }

        free( response );
    }

    return ( ret );
}

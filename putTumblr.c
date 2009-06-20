/*
 * clip loader <<putTumblr>>
 *
 *      OPML �� Tumblr ���e�v���O����
 *          written by H.Tsujimura  31 Oct 2007
 *
 * History:
 * $Log: /comm/bookey/putTumblr.c $
 * 
 * 3     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 8     09/05/28 22:13 Tsujimura543
 * ����A�J�E���g�ŕ��� tumbleblog ���J�݂��Ă���ꍇ�̓��e��
 * tumbleblog ���w�肵�Ă̓��e���\�ɂ���
 * 
 * 2     09/05/27 1:34 tsupo
 * xmlRPC 1.266�őΉ�
 * 
 * 7     09/05/26 18:08 Tsujimura543
 * URL �n�[�h�R�[�f�B���O�ӏ������炵��
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     08/02/19 23:42 Tsujimura543
 * tag ���w�肵�Ă̓��e�ɑΉ� (API ���g�����ꂽ�̂ɔ����ύX)
 * 
 * 5     08/02/14 19:40 Tsujimura543
 * replaceString() �� myClip.c �ֈړ�
 * 
 * 4     08/02/14 19:34 Tsujimura543
 * �u�� �� &Lt; �ɉ�������A�� �� &Gt; �ɉ������肷�錏�̑΍�v���R�����g
 * �����ɂ��K�p
 * 
 * 3     08/02/14 0:49 Tsujimura543
 * �u�� �� &Lt; �ɉ�������A�� �� &Gt; �ɉ������肷�錏�̑΍�v�����{
 * 
 * 2     07/11/12 19:04 Tsujimura543
 * ���e���s���ɃG���[���b�Z�[�W��\���\�ȏꍇ�́A�\������悤�ɂ���
 * 
 * 1     07/10/31 19:26 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putTumblr.c 3     09/05/29 8:43 tsupo $";
#endif

typedef struct paramForTumblr  {
    char    userName[MAX_NAMELEN + 1];  /* ���[�U��         */
    char    password[MAX_NAMELEN + 1];  /* �p�X���[�h       */
    char    group[MAX_URLLENGTH + 1];   /* ���e��tumbleblog */
    char    version[MAX_NAMELEN + 1];   /* userAgent �Ő�   */
}   PARAM_TUMBLR;


BOOL
_putTumblr(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char            *request  = args->request;
    char            *response = args->response;
    size_t          sz        = args->sz;
    PARAM_TUMBLR    *arg = (PARAM_TUMBLR *)args->args; 
    char            url[MAX_URLLENGTH * 4];
    char            name[MAX_DESCRIPTION_LEN];
    char            description[MAX_DESCRIPTION_LEN];
    char            tags[MAX_DESCRIPTION_LEN];
    char            *p, *q;
    BOOL            ret = FALSE;
    int             i;
    char            tag[80];

    /*
     * Tumblr �� link �𗘗p���āAURL �� �R�����g�𓊍e 
     */
    errorString[0] = NUL;
    strcpy( url, APIURL_TUMBLR_WRITE );

    strcpy( name, mp->title );
    p = any2utf( name );
    if ( p )
        strcpy( name, p );

    /* �� �� &Lt; �ɉ�������A�� �� &Gt; �ɉ������肷�錏�̑΍� */
    if ( strstr( name, "\342\211\253" ) )   // &raquo; (E2 89 AB)
        replaceString( name, "\342\211\253", "\302\273" );// E2 89 AB �� C2 BB
    if ( strstr( name, "\342\211\252" ) )   // &laquo; (E2 89 AA)
        replaceString( name, "\342\211\252", "\302\253" );// E2 89 AA �� C2 AB

    sprintf( description,
             "<p>comment: %s",
             mp->comment );
    p = any2utf( description );
    if ( p )
        strcpy( description, p );

    /* �� �� &Lt; �ɉ�������A�� �� &Gt; �ɉ������肷�錏�̑΍� */
    if ( strstr( description, "\342\211\253" ) )    // &raquo;
        replaceString( description, "\342\211\253", "\302\273" );
    if ( strstr( description, "\342\211\252" ) )    // &laquo;
        replaceString( description, "\342\211\252", "\302\253" );
    if ( strstr( description + 3, "<" ) )           // &lt;
        replaceString( description + 3, "<", "&lt;" );

    // �^�O (�Ƃ肠�����ő�10�܂łɂ��Ă���)
    tags[0] = NUL;
    if ( mp->tags[0] )
        strcat( description, "</p><p>tags: " );
    p = any2utf( mp->tags );
    q = p ? p : mp->tags;
    i = 0;
    do {
        p = strchr( q, ' ' );
        if ( p ) {
            strncpy( tag, q, p - q );
            tag[p - q] = NUL;
            sprintf( description + strlen(description),
                     "[%s]",
                     tag );
            sprintf( tags + strlen(tags), "%s,", tag );
            i++;
            q = p + 1;
        }
        else {
            sprintf( description + strlen(description),
                     "[%s]",
                     q );
            sprintf( tags + strlen(tags), "%s", q );
            break;
        }
    } while ( (i < 10) && *q );
    sprintf( description + strlen(description),
             "<br />-- posted by bookey/%s</p>",
             arg->version );

    sprintf( request,
             "email=%s&"
             "password=%s&"
             "type=link&"
             "name=%s&",
             arg->userName,
             arg->password,
             encodeURL( name ) );
    sprintf( request + strlen(request),
             "url=%s&",
             encodeURL( mp->url ) );
    sprintf( request + strlen(request),
             "description=%s&"
             "generator=bookey/%s",
             encodeURL( description ),
             arg->version );
    if ( tags[0] )
        sprintf( request + strlen(request),
                 "&"
                 "tags=%s",
                 encodeURL( tags ) );
    if ( arg->group[0] )
        sprintf( request + strlen(request),
                 "&group=%s", arg->group );

    setUpReceiveBuffer( response, sz );
    http_post( url, "application/x-www-form-urlencoded",
               request, response );
    if ( *response ) {
        int postID = atol( response );
        if ( postID >= 1 )
            ret = TRUE; /* ���e���� */
        else {
            p = strstr( response, "Tumblr is undergoing maintenance" );
            if ( p )
                strcpy( errorString, "���݁ATumblr �̓����e�i���X���ł�" );
            else {
                p = strstr( response,
                            "You've exceeded your daily post limit." );
                if ( p )
                    strcpy( errorString,
                            "���ł�1�����̓��e�񐔏���܂œ��e���Ă��܂�" );
            }
        }
    }

    return ( ret );
}

void
putTumblr(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const char   *group,     /* (I) ���e��tumbleblog */
        const char   *version,   /* (I) userAgent �Ő�   */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    )
{
    PARAM_TUMBLR    arg;

    strcpy( arg.userName, userName );
    strcpy( arg.password, password );
    if ( group && *group )
        strcpy( arg.group,    group );
    else
        arg.group[0] = NUL;
    strcpy( arg.version,  version );
    putBookmarks( "tumblr",
                  mp, numOfClips, NULL, 0, &arg, _putTumblr );
}

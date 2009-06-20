/*
 * clip loader <<putTimelog>>
 *
 *      OPML �� Timelog �����v���O����
 *          written by H.Tsujimura  23 May 2007
 *
 * History:
 * $Log: /comm/bookey/putTimelog.c $
 * 
 * 2     09/06/11 2:57 tsupo
 * 0.62a��
 * 
 * 4     09/06/10 20:55 Tsujimura543
 * Timelog ���e���̃��X�|���X���󕶎���ɕύX���ꂽ�̂ɔ����C��
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 2     07/09/05 18:58 Tsujimura543
 * UserAgent �������t�@�N�^�����O
 * 
 * 1     07/05/23 16:59 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putTimelog.c 2     09/06/11 2:57 tsupo $";
#endif

typedef struct paramForTimelog  {
    char    userName[MAX_NAMELEN + 1];  /* ���[�U��(���[���A�h���X) */
    char    password[MAX_NAMELEN + 1];  /* �p�X���[�h               */
    char    version[MAX_NAMELEN + 1];   /* userAgent �Ő�           */
    char    url[MAX_URLLENGTH + 1];     /* userAgent �֘AWeb�y�[�W  */
    char    resource[MAX_URLLENGTH + 1];/* userAgent �֘AXML        */
}   PARAM_TIMELOG;


BOOL
_putTimelog(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char            *request  = args->request;
    char            *response = args->response;
    size_t          sz        = args->sz;
    PARAM_TIMELOG   *arg = (PARAM_TIMELOG *)args->args; 
    char            url[MAX_URLLENGTH * 4];
    char            userAgent[BUFSIZ];
    char            monologue[MAX_DESCRIPTION_LEN];
    char            *p, *q;
    BOOL            ret = FALSE;
    int             i;
    char            tag[80];

    /*
     * �u(�ǂ����̃\�[�V�����u�b�N�}�[�N��)�u�b�N�}�[�N�� POST �������Ɓv
     * ���
     */
    errorString[0] = NUL;
    strcpy( url, "http://api.timelog.jp/new.asp" );
    sprintf( monologue,
             "/B %s %s",
             mp->url, mp->title );
    p = any2utf( monologue );
    if ( p )
        strcpy( monologue, p );
    sprintf( request,
             "remsgid=&"
             "text=%s",
             encodeURL( monologue ) );

    // �^�O (�Ƃ肠�����ő�10�܂łɂ��Ă���)
    if ( mp->tags[0] )
        strcat( request, " " );
    p = any2utf( mp->tags );
    q = p ? p : mp->tags;
    i = 0;
    do {
        p = strchr( q, ' ' );
        if ( p ) {
            strncpy( tag, q, p - q );
            tag[p - q] = NUL;
            sprintf( request + strlen(request),
                     "[%s]",
                     encodeURL( tag ) );
            i++;
            q = p + 1;
        }
        else {
            sprintf( request + strlen(request),
                     "[%s]",
                     encodeURL( q ) );
            break;
        }
    } while ( (i < 10) && *q );

    sprintf( userAgent,
             "bookey/%s (%s)\r\n"
             "X-Timelog-Client: bookey\r\n"
             "X-Timelog-Client-Version: %s\r\n"
             "X-Timelog-Client-URL: %s",
             arg->version, arg->url, arg->version, arg->resource );
    setUserAgent( userAgent );  /* User-Agent ���ꎞ�I�ɕύX */

    setUpReceiveBuffer( response, sz );
    http_postBASIC( url, arg->userName, arg->password,
                    "application/x-www-form-urlencoded",
                    request, response );
    if ( *response ) {
        if ( strstr( response, "OK" ) )
            ret = TRUE; /* ���e���� */
    }
    else {
        unsigned short status = getStatusCode();
        if ( status / 100 == 2 )    // 200 OK (�` 299) �Ȃ琬���Ƃ݂Ȃ�
            ret = TRUE; /* ���e���� */
    }

    setUserAgent( NULL );       /* User-Agent �����ɖ߂� */

    return ( ret );
}

void
putTimelog(
        const char   *userName,  /* (I) ���[�U��                */
        const char   *password,  /* (I) �p�X���[�h              */
        const char   *version,   /* (I) userAgent �Ő�          */
        const char   *url,       /* (I) userAgent �֘AWeb�y�[�W */
        const char   *resource,  /* (I) userAgent �֘AXML       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���        */
        int          numOfClips  /* (I) �u�b�N�}�[�N��          */
    )
{
    PARAM_TIMELOG   arg;

    strcpy( arg.userName, userName );
    strcpy( arg.password, password );
    strcpy( arg.version,  version );
    strcpy( arg.url,      url );
    strcpy( arg.resource, resource );
    putBookmarks( "Timelog",
                  mp, numOfClips, NULL, 0, &arg, _putTimelog );
}

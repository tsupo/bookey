/*
 * clip loader <<putTwitter>>
 *
 *      OPML �� Twitter �����v���O����
 *          written by H.Tsujimura  10 Apr 2007
 *
 * History:
 * $Log: /comm/bookey/putTwitter.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 25    09/04/09 18:17 Tsujimura543
 * �R�����g�C��
 * 
 * 24    09/04/09 18:16 Tsujimura543
 * OAuth �F�؃G���[���������Ă��邩�ǂ����𔻒肷��̂� http ���X�|���X
 * �R�[�h�� 401 ���ǂ���������悤�ɂ��Ă݂�
 * 
 * 23    09/04/09 17:53 Tsujimura543
 * OAuth �F�؃G���[���̃��X�|���X�d�l�ύX�ɔ����C�������{
 * 
 * 22    09/04/07 15:46 Tsujimura543
 * OAuth �� "Invalid OAuth Request" �����������Ƃ��̏�����ǉ�
 * 
 * 21    09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 20    08/11/17 11:33 Tsujimura543
 * getTinyURL() ���C�� (���̊Ԃɂ��Atinyurl �̕Ԃ����X�|���X��
 * �t�H�[�}�b�g���ς���Ă���)
 * -- cxx����� http://twitter.com/cxx/status/1000191856 �ɂ��
 * -- �w�E�Ŕ����BThanks!
 * 
 * 19    07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 18    07/09/05 18:58 Tsujimura543
 * UserAgent �������t�@�N�^�����O
 * 
 * 17    07/07/10 22:32 Tsujimura543
 * �u�����v�� POST ���̃p�����[�^�� source=API�� ��ǉ����Ă݂�
 * 
 * 16    07/07/02 16:30 Tsujimura543
 * Twitter �ւ̓��e���A�L���^�C�g���������������邱�Ƃ�����s��ɑΏ�
 * 
 * 15    07/06/19 0:00 Tsujimura543
 * Twitter �ւ̓��e���AWeb�y�[�W�̃^�C�g�������������������邱�Ƃ�����
 * �s��ɑΏ�
 * 
 * 14    07/05/23 17:42 Tsujimura543
 * ���C���e�i���X����ʂ��Ԃ��Ă����ꍇ�́A���̎|�AerrorString �ɐݒ肷��
 * �悤�ɂ���
 * 
 * 13    07/05/22 20:39 Tsujimura543
 * POST �ɑ΂��鉞�����󔒕����݂̂̂Ƃ������e�����Ƃ݂Ȃ��悤�ɂ���
 * (���e�ɐ������Ă���Ƃ͌���Ȃ����A�������Ă��邱�Ƃ���������)
 * 
 * 12    07/05/11 19:10 Tsujimura543
 * Twitter �ɑ��� bookey �̔Ő������\�[�X����擾�������̂��g���悤��
 * ���Ă݂�
 * 
 * 11    07/05/11 18:45 Tsujimura543
 * normalizeDescription() ���C��
 * 
 * 10    07/04/12 18:29 Tsujimura543
 * �u�b�N�}�[�N�Ώ� URL ��25�o�C�g�ȏ�̂Ƃ��� tinyurl ����悤�ɂ���
 * 
 * 9     07/04/12 16:18 Tsujimura543
 * ? �� # ���܂܂�� URL �����Ȃ� tinyurl �ł���悤�ɑ΍􂵂Ă݂�
 * 
 * 8     07/04/11 17:58 Tsujimura543
 * User-Agent �� chirrup ���� bookey �ɕύX
 * 
 * 7     07/04/11 15:00 Tsujimura543
 * (1) tinyurl �Ŏ擾�����Z�kURL �ɃS�~(chunked)�������Ƃ����錻�ۂɑΏ�
 * (2) User-Agent �� chirrup �ɑ}���ւ��� Twitter �Ƀ��N�G�X�g�𔭍s�����
 *     ���ɂ���
 * 
 * 6     07/04/10 21:56 Tsujimura543
 * TWITTER �� Twitter �œ���
 * 
 * 5     07/04/10 21:55 Tsujimura543
 * getTinyURL() ���C�� [tinyurl �����܂����_�C���N�g�ł��Ȃ��Z�kURL��
 * �������邱�Ƃ�����̂ŁA�΍�����{]
 * 
 * 4     07/04/10 19:07 Tsujimura543
 * �u�����ɋ󔒕�����t���v���Ă��瓊�e����悤�ɂ���
 * 
 * 3     07/04/10 17:16 Tsujimura543
 * �������e�̖�����؂�̂Ă��ꍇ�� ... ��t����悤�ɂ���
 * 
 * 2     07/04/10 17:12 Tsujimura543
 * �������e��160�o�C�g��蒷���ꍇ�́A���ӂꂽ�������̂ĂĂ��瓊�e����
 * �悤�ɂ���
 * 
 * 1     07/04/10 16:46 Tsujimura543
 * �ŏ��̔�
 */

#include "myClip.h"
#include "sha1.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putTwitter.c 1     09/05/14 3:48 tsupo $";
#endif

typedef struct paramForTwitter  {
    BOOL    useOAuth;                   /* OAuth �F�؂��g�����ǂ��� */
    char    userName[MAX_NAMELEN + 1];  /* ���[�U��(���[���A�h���X) */
    char    password[MAX_NAMELEN + 1];  /* �p�X���[�h               */
    char    token[MAX_KEYLENGTH + 1];   /* �A�N�Z�X�g�[�N��         */
    char    secret[MAX_KEYLENGTH + 1];  /* �A�N�Z�X�g�[�N���閧��   */
    char    version[MAX_NAMELEN + 1];   /* userAgent �Ő�           */
    char    url[MAX_URLLENGTH + 1];     /* userAgent �֘AWeb�y�[�W  */
    char    resource[MAX_URLLENGTH + 1];/* userAgent �֘AXML        */
}   PARAM_TWITTER;

#define MAX_DESCRIPTION_LENGTH          160
#define MAX_DESCRIPTION_BYTES_IN_SJIS   100
          // UTF-8��160�o�C�g�ȉ� �� (Shift_JIS ��)106�����ȉ�
          //                      �� ���]�T���������� 100�����ȉ��ɂ���

char    *TwitterOAuthConsumerKey();
char    *TwitterOAuthConsumerSecret();

void
makeOAuthBase(
        const char *oauthToken,
        const char *oauthTokenSecret,
        const char *url,
        const char *method,
        char       *key,
        char       *base,
        char       *param
    )
{
    time_t  t = time( NULL );
    char    nonce[MAX_KEYLENGTH];

    strcpy( nonce, getNonce(NULL) );

    sprintf( key,
             "%s&",
             encodeURLi( TwitterOAuthConsumerSecret(), FALSE ) );
    sprintf( key + strlen(key),
             "%s",
             encodeURLi( oauthTokenSecret, FALSE ) );

    sprintf( base,
             "%s&"
             "%s&",
             method,
             encodeURLi( url, FALSE ) );

    sprintf( param[0] ? param + strlen(param) : param,
             "oauth_consumer_key=%s&"
             "oauth_nonce=%s&"
             "oauth_signature_method=HMAC-SHA1&"
             "oauth_timestamp=%ld&"
             "oauth_token=%s&"
             "oauth_version=1.0",
             TwitterOAuthConsumerKey(),
             nonce,
             t,
             oauthToken );
}

void
makeOAuthRequest(
        const char *url,
        char       *request,
        char       *key,
        char       *base,
        char       *param
    )
{
    char    digest[SHA1HashSize * 4];

    sprintf( base + strlen(base),
             "%s",
             encodeURLi( param, FALSE ) );

    memset( digest, 0x00, SHA1HashSize );
    hmac_sha1( (unsigned char *)base, strlen(base),
               (unsigned char *)key,  strlen(key),
               digest );
    strcpy( digest, base64( (unsigned char *)digest, SHA1HashSize ) );

    sprintf( request,
             "%s?"
             "%s&"
             "oauth_signature=%s",
             url,
             param,
             encodeURLi( digest, TRUE ) );
}


static char *
normalizeDescription( char *description )
{
    char    *p;

    if ( strlen( description ) > MAX_DESCRIPTION_BYTES_IN_SJIS ) {
        char    *s = description;
        int     kanjiFlag = 0;
        int     i = 0;

        while ( *s ) {
            if ( ++i > MAX_DESCRIPTION_BYTES_IN_SJIS )
                break;
            if ( kanjiFlag == 0 ) {
                if ( iskanji1( *s ) )
                    kanjiFlag = 1;
            }
            else
                kanjiFlag = ((kanjiFlag + 1) % 3);
            *s++;
        }
        switch ( kanjiFlag ) {
        case 0:
            *s = NUL;
            break;
        case 1:
            *(s - 1) = NUL;
            break;
        case 2:
            *(s - 2) = NUL;
            break;
        }

        strcat( description, "...\"" );
    }

    p = any2utf( description );

    return ( p ? p : description );
}


char    *
getTinyURL( const char *targetURL,
            char       *request,
            char       *response,
            size_t     sz )
{
    char    url[MAX_URLLENGTH];

    if ( !strchr( targetURL, '#' ) &&
         !strchr( targetURL, '?' )    ) {
        sprintf( url,
                 "http://tinyurl.com/api-create.php?url=%s", targetURL );

        setUpReceiveBuffer( response, sz );
        http_get( url, response );
        if ( response[0] ) {
            char    *p = strstr( response, "http" );

            if ( p && (response < p) )
                strcpy( response, p );

            p = strchr( response, '\r' );
            if ( !p )
                p = strchr( response, '\n' );
            if ( p )
                *p = NUL;
        }
    }
    else {
        strcpy( url, "http://tinyurl.com/create.php" );
        sprintf( request, "url=%s", encodeURL(targetURL) );
        setUpReceiveBuffer( response, sz );
        http_post( url, "application/x-www-form-urlencoded",
                   request, response );
        if ( *response ) {
            char    *p = strstr( response,
                                 "<input type=hidden name=tinyurl value=\"" );
            if ( p )
                p += 39;
            else {
                char *q = strstr( response, "<h1>TinyURL was created!</h1>" );
                if ( !q )
                    q = strstr( response, "<blockquote" );
                if ( q ) {
                    p = strstr( q, "[<a href=\"" );
                    if ( p )
                        p += 10;
                }
            }
            if ( p ) {
                char    *q = strchr( p, '"' );
                if ( q ) {
                    strncpy( response, p, q - p );
                    response[q - p] = NUL;
                }
            }
            else
                response[0] = NUL;
        }
    }

    return ( response[0] ? response : NULL );
}

BOOL
_putTwitter(
        const MyClip *mp,
        char         *errorString,
        PARAM_PBM    *args
    )
{
    char            *request  = args->request;
    char            *response = args->response;
    size_t          sz        = args->sz;
    PARAM_TWITTER   *arg = (PARAM_TWITTER *)args->args; 
    char            url[MAX_URLLENGTH * 4];
    char            userAgent[BUFSIZ];
    char            monologue[MAX_DESCRIPTION_LEN];
    char            *p;
    BOOL            ret = FALSE;

    /*
     * �u(�ǂ����̃\�[�V�����u�b�N�}�[�N��)�u�b�N�}�[�N�� POST �������Ɓv
     * ���
     */
    errorString[0] = NUL;
    strcpy( url, "http://twitter.com/statuses/update.xml" );
    sprintf( monologue,
             "Bookmarked %s - \"%s\"",
             (strlen(mp->url) >= 25)                    ||
             (strlen(mp->url) + strlen(mp->title) > 80)
                ? getTinyURL( mp->url, request, response, sz )
                : mp->url,
             mp->title );
    if ( strlen( monologue ) > MAX_DESCRIPTION_LENGTH ) {
        p = any2sjis( monologue );
        if ( p ) {
            char    temp[MAX_DESCRIPTION_LEN];
            strcpy( temp, p );
            p = normalizeDescription( temp );
            if ( p )
                strcpy( monologue, p );
        }
    }
 // strcat( monologue, " " ); /* �����ɋ󔒕�����t�� */

    sprintf( userAgent,
             "bookey/%s (%s)\r\n"
             "X-Twitter-Client: bookey\r\n"
             "X-Twitter-Client-Version: %s\r\n"
             "X-Twitter-Client-URL: %s",
             arg->version, arg->url, arg->version, arg->resource );
    setUserAgent( userAgent );  /* User-Agent ���ꎞ�I�ɕύX */

    p = any2utf( monologue );
    if ( arg->useOAuth ) {
        // OAuth �F��
        char    key[MAX_KEYLENGTH * 2];
        char    base[MAX_CONTENT_SIZE];
        char    param[MAX_CONTENT_SIZE];

        key[0]   = NUL;
        base[0]  = NUL;
        param[0] = NUL;
        makeOAuthBase(arg->token, arg->secret, url, "POST", key, base, param);

        sprintf( param + strlen(param),
                 "&"
                 "source=%s&"
                 "status=%s",
                 "bookey",
                 encodeURLi( p ? p : monologue, FALSE ) );

        makeOAuthRequest( url, request, key, base, param );

        setUpReceiveBuffer( response, sz );
        http_postBASIC( request, NULL, NULL,
                        "application/x-www-form-urlencoded",
                        "", response );
    }
    else {
        // BASIC �F��
        sprintf( request,
                 "status=%s&"
                 "source=%s",
                 encodeURL( p ? p : monologue ),
                 "bookey" );
        setUpReceiveBuffer( response, sz );
        http_postBASIC( url, arg->userName, arg->password,
                        "application/x-www-form-urlencoded",
                        request, response );
    }
    if ( *response ) {
        if ( strstr( response, "<created_at>" ) || (*response == ' ') )
            ret = TRUE; /* ���e���� */
        else {
            unsigned short responseCode = getStatusCode();

            getCurrentLocation( url );
            if ( strstr( url, "maintenance" ) )
                strcpy( errorString, "Now maintenance ..." );
            else if ( ( arg->useOAuth && (responseCode == 401) )  ||
                      strstr( response, "Invalid OAuth Request" ) ||
                      strstr( response,
                          "Failed to validate oauth signature or token" ) ) {
                LCID    l = getLanguageCode();

                strcpy( errorString,
                        l == 0x0411
                          ? "OAuth �F�؂Ɏ��s���܂����B\r\n"
                            "�A�N�Z�X�g�[�N�����擾�������Ă��������B"
                          : "Failed to authenticate.\r\n"
                            "Get a new 'Access Token', again.");
            }
        }
    }

    setUserAgent( NULL );       /* User-Agent �����ɖ߂� */

    return ( ret );
}

void
putTwitter(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X) */
        const char   *password,  /* (I) �p�X���[�h               */
        const char   *token,     /* (I) �A�N�Z�X�g�[�N��         */
        const char   *secret,    /* (I) �A�N�Z�X�g�[�N���閧��   */
        AUTH_TYPE    authType,   /* (I) �F�؃^�C�v               */
        const char   *version,   /* (I) userAgent �Ő�           */
        const char   *url,       /* (I) userAgent �֘AWeb�y�[�W  */
        const char   *resource,  /* (I) userAgent �֘AXML        */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���         */
        int          numOfClips  /* (I) �u�b�N�}�[�N��           */
    )
{
    PARAM_TWITTER   arg;

    arg.useOAuth = authType == AK_OAUTH ? TRUE : FALSE;

    strcpy( arg.userName, userName );
    strcpy( arg.password, password );
    strcpy( arg.token,    token );
    strcpy( arg.secret,   secret );
    strcpy( arg.version,  version );
    strcpy( arg.url,      url );
    strcpy( arg.resource, resource );
    putBookmarks( "Twitter",
                  mp, numOfClips, NULL, 0, &arg, _putTwitter );
}

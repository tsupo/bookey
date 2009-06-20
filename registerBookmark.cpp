/*
 * registerBookmark.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N�o�^�X���b�h
 *          written by H.Tsujimura  13 Oct 2005, 5 Jul 2006
 *
 * $Log: /comm/bookey/registerBookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 73    09/02/25 18:02 Tsujimura543
 * http://d.hatena.ne.jp/gyogyo6/20090225/bookmark ���Q�l�ɂ��A
 * getRegularURL() ������
 * 
 * 72    09/02/24 16:27 Tsujimura543
 * �^�O��⒊�o�����Q�̈������e�X�ǉ�
 * 
 * 71    08/12/26 14:33 Tsujimura543
 * �폜�Ώ�URL�f�Ђ� ?rss_fdn= (MSDN) ��ǉ�
 * 
 * 70    08/12/03 17:56 Tsujimura543
 * getBookmarkViaEntryPageOnLivedoor() �𓱓�
 * (�ēo�^����)�R�����g�A�^�O���擾����ۂ̗\���I�ȏ����Ƃ��Ďg�p����
 * 
 * 69    08/12/03 15:37 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�vAPI �ɂ��u(�ēo�^���s����)�R�����g�A�^�O�̎�
 * ���v�����܂������Ȃ������ꍇ�́A�u�͂Ăȃu�b�N�}�[�N�v�̃G���g���y�[
 * �W���X�N���C�s���O���āA�R�����g�A�^�O���擾����悤�ɂ���
 * 
 * 68    08/12/01 19:17 Tsujimura543
 * escapeAmpasand() �� escapeAmpersand() �ɕύX (�Ԃ�����C��)
 * 
 * 67    08/11/04 12:49 Tsujimura543
 * @nifty Clip �o�^�Ґ����\������悤�ɂ���
 * 
 * 66    08/10/23 18:03 Tsujimura543
 * ���_�C���N�g�΍� URL �� partners.extranet.microsoft.com ��ǉ�
 * 
 * 65    08/10/21 20:00 Tsujimura543
 * ���_�C���N�g�΍� URL �� sum.com �� amazon.com �̃��[���}�K�W���f�ڗp
 * ���_�C���N�^��ǉ�
 * 
 * 64    08/09/19 18:04 Tsujimura543
 * �폜�Ώ�URL�f�Ђ� ?from=main (�ǔ��V��) ��ǉ�
 * 
 * 63    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 62    08/06/12 17:17 Tsujimura543
 * ���_�C���N�g�΍� URL �Ƃ��� rss.yomiuri.co.jp/click.phdo ��ǉ�
 * 
 * 61    08/05/16 0:22 Tsujimura543
 * �R�����g���C��
 * 
 * 60    08/05/15 15:29 Tsujimura543
 * ���_�C���N�g�΍� c2.lenovo-news.com/g.php ��ǉ�
 * (����̉ۑ�: ���_�C���N�g�΍� URL ���O���ݒ�t�@�C��������Ǎ��ނ悤�ɂ���)
 * 
 * 59    08/05/14 18:56 Tsujimura543
 * ���_�C���N�g�΍� URL �Ƃ��� www.oracle.co.jp/mp ��ǉ�
 * 
 * 58    08/05/14 14:54 Tsujimura543
 * ���_�C���N�g�΍� URL �Ƃ��� symantecenterprise.rsys3.net ��ǉ�
 * 
 * 57    08/05/13 21:25 Tsujimura543
 * ���_�C���N�^�΍� URL �Ƃ��� feeds.japan.cnet.com ��ǉ�
 * 
 * 56    08/03/11 19:11 Tsujimura543
 * getRegularURL() �̑Ώۂ� ?feedType=RSS (���C�^�[) ��ǉ�
 * 
 * 55    07/12/26 19:42 Tsujimura543
 * http://z.la/ �ɂ��Ή����Ă݂�
 * 
 * 54    07/12/20 20:26 Tsujimura543
 * getRegularURL() �̑Ώۂ� &fm=rss (CD�W���[�i��) ��ǉ�
 * 
 * 53    07/12/19 20:22 Tsujimura543
 * InquiryWebPageInfo() �̑Ώ� URL ��ǉ�
 * 
 * 52    07/12/17 23:09 Tsujimura543
 * �R�����g���C��
 * 
 * 51    07/12/17 21:07 Tsujimura543
 * asahi.com �� RSS �� pheedo �o�R�ɕύX���ꂽ(������ύX���ꂽ�̂��͕s��)
 * �̂ɔ����AInquiryWebPageInfo() ���C������
 * 
 * 50    07/11/15 22:34 Tsujimura543
 * �폜�Ώ�URL�f�Ђ� ?ref=BPN (���oBP) ��ǉ�
 * 
 * 49    07/11/13 18:30 Tsujimura543
 * japan.internet.com �΍� (������ ?rss ���t��) ��ǉ�
 * 
 * 48    07/11/12 19:08 Tsujimura543
 * �폜�Ώ�URL�f�Ђ� &ST=web_threat (���oBP) ��ǉ�
 * 
 * 47    07/09/05 20:30 Tsujimura543
 * UserAgent �������t�@�N�^�����O
 * 
 * 46    07/09/05 1:54 Tsujimura543
 * extractTags() �� stat1470net �� FALSE �ɂȂ����ꍇ�́A���̒���ȍ~
 * getUsersOfMMmemo() ���Ă΂Ȃ��悤�ɂ���
 * 
 * 45    07/09/05 1:50 Tsujimura543
 * getUsersOfMMmemo() �� extractTags() �Ɋe�X��2������ǉ�
 * (stat1470net��������)
 * 
 * 44    07/08/27 21:55 Tsujimura543
 * �u�͂ĂȃX�^�[�v�ɑΉ�
 * 
 * 43    07/07/24 18:21 Tsujimura543
 * getRegularURL() �̍폜�Ώ� query �� bcsi_scan ��ǉ�
 * 
 * 42    07/07/09 19:59 Tsujimura543
 * �udigg �̓��[���v���擾���鏈����ǉ�
 * 
 * 41    07/07/02 16:32 Tsujimura543
 * Visual C++ 2005 �ł̃R���p�C���`�F�b�N���ʂ𔽉f
 * 
 * 40    07/05/23 14:40 Tsujimura543
 * 407(Proxy Authentication Required) �΍�
 * 
 * 39    07/04/25 10:02 Tsujimura543
 * �}�C�N���\�t�g�̃��_�C���N�^(go.microsoft.com)�ɑΉ�
 * 
 * 38    07/04/24 13:46 Tsujimura543
 * pheedo.vector.co.jp �� pheedo.com �̃��_�C���N�^�ɑΉ�
 * 
 * 37    07/04/16 22:47 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �̃��_�C���N�^�ɂ��Ή�
 * 
 * 36    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 35    07/04/09 16:57 Tsujimura543
 * tinyurl.com �� rurl.org �̒Z�kURL(���_�C���N�^)���g���Ă���ꍇ�A���_
 * �C���N�g��URL���u�b�N�}�[�N����悤�ɂ���
 * 
 * 34    07/04/02 13:50 Tsujimura543
 * �폜�Ώ�URL�f�Ђ� ?tag=nl (CNET Japan) ��ǉ�
 * 
 * 33    07/03/30 16:38 Tsujimura543
 * FC2BOOKMARK(�̌��J���x��)�ɑΉ�
 * 
 * 32    07/03/26 23:16 Tsujimura543
 * ���[�J��OPML�o�^���Ƀ������j�󂪔�������\���̂���ӏ��𔭌��A
 * �C�������{
 * 
 * 31    07/03/16 1:03 Tsujimura543
 * proxy�T�[�o�o�R�łȂ��ƃC���^�[�l�b�g�A�N�Z�X�ł��Ȃ��̂ɁAproxy�T�[�o
 * ���g��Ȃ��ݒ�ɂȂ��Ă���ꍇ�̑΍��ǉ�
 * 
 * 30    07/03/14 20:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 29    07/03/14 15:45 Tsujimura543
 * URL ���� & ���܂܂��ꍇ�ł��A�R�����g�A�^�O�̓��e�𕜌��ł���悤�ɂ�
 * ��
 * 
 * 28    07/03/01 21:37 Tsujimura543
 * livedoor�N���b�v�ɓo�^���Ă���l�̐����擾����悤�ɂ���
 * 
 * 27    07/02/02 23:56 Tsujimura543
 * ���C�����̓���m�F����
 * 
 * 26    07/02/02 23:40 Tsujimura543
 * �ēo�^���悤�Ƃ��Ă���ꍇ�̈�A�̏������C���B�h���R��RSS��Flog�̃J�e�S
 * ���������ł���悤�ɂ���
 * 
 * 25    07/02/02 23:39 Tsujimura543
 * ���ۂɂ́u�͂Ăȃu�b�N�}�[�N�v���o�^�ł� getBookmarkOnHatenaWithURI()
 * ���o�^�ς݃R�����g(�Ƃ��ċL���̊T�v)��Ԃ����Ƃ������BgetTitle() ����
 * �C���A���łɓo�^�ς݂��ǂ������f�ł���悤�ɂ���
 * 
 * 24    07/02/02 21:03 Tsujimura543
 * getBookmarkOnHatenaWithURI() ���當������󂯎��e�̈�̃T�C�Y
 * ���b��l���琳���Ȓl�ɕύX
 * 
 * 23    07/02/02 20:59 Tsujimura543
 * ���łɁu�͂Ăȃu�b�N�}�[�N�v�ɓo�^�ς݂̃u�b�N�}�[�N�����߂ēo�^������
 * ���Ƃ��Ă���ꍇ�́A�ȑO�ɓo�^�����R�����g�A�^�O���擾���āA�ҏW������
 * ��悤�ɂ���
 * 
 * 22    07/02/02 20:13 Tsujimura543
 * getRegularURL() �� IBM �� developerworks �֘A�y�[�W�� URL ���K��
 * ������ǉ�
 * 
 * 21    07/01/16 22:32 Tsujimura543
 * �p�ꃂ�[�h�Ή� (������������)
 * 
 * 20    07/01/16 15:10 Tsujimura543
 * �R�����g���� typo ���C��
 * 
 * 19    07/01/16 15:09 Tsujimura543
 * (1) �p�ꃂ�[�h�Ή�
 * (2) amazon.co.jp �ȊO�� Amazon (amazon.com �Ȃ�) �̏��i�� URL �����K��
 *     ����悤�ɂ���
 * 
 * 18    07/01/11 17:01 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 17    07/01/04 18:54 Tsujimura543
 * ShowWindow() �̈������C��
 * 
 * 16    06/12/27 17:37 Tsujimura543
 * �u�b�N�}�[�N���e�_�C�A���O�ŉE�N���b�N���j���[���g����悤�ɂ���
 * 
 * 15    06/12/26 0:49 Tsujimura543
 * 3�́u���J���x���v�Ή������A�C��
 * 
 * 14    06/12/25 22:07 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v��3�́u���J���x���v�ɑΉ�
 * 
 * 13    06/12/06 18:59 Tsujimura543
 * �u���J��ԁv�̐ݒ�ɑΉ�
 * 
 * 12    06/11/10 20:07 Tsujimura543
 * strncmpi() �̎��̂� myClip.c �Ɉړ�
 * 
 * 11    06/09/29 23:45 Tsujimura543
 * newsing (�́u���~�v�]��) �ɑΉ�
 * 
 * 10    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 9     06/09/12 13:58 Tsujimura543
 * URL �̐��K�������������C�� (�R���p�C���G���[���������Ă���)
 * 
 * 8     06/09/11 11:41 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̃R���N�V�����ɓo�^����ꍇ�A�A�}�]����URL��
 * �`���ɂ���Ă͓o�^���邱�Ƃ��ł��Ȃ����Ƃ����邽�߁AURL�𐳋K��
 * ���Ă���o�^����悤�ɂ��Ă݂�
 * 
 * 7     06/09/04 22:33 Tsujimura543
 * SleepEx() �� Sleep() �ɒu��
 * 
 * 6     06/09/04 22:30 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v�̃R���N�V�����ɒǉ��\�����f����̂� getASIN()
 * �̌��ʂ𗘗p����悤�ɂ���
 * 
 * 5     06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 4     06/07/27 13:27 Tsujimura543
 * ThinkIT �̃��_�C���N�^(http://cm.thinkit.co.jp/)�ɑΉ�
 * 
 * 3     06/07/11 22:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�̃u�b�N�}�[�N�o�^�Ґ����\������悤�ɂ���
 * (�u�b�N�}�[�N�o�^���/EditBookmarkDialog)
 * 
 * 2     06/07/05 11:21 Tsujimura543
 * �]���ȃR�[�h���폜�A����
 * 
 * 1     06/07/05 11:14 Tsujimura543
 * �u�u�b�N�}�[�N�o�^�X���b�h�v�֘A������ bookeyView.cpp ���番���Ɨ�������
 */

#include "bookey.h"
#include <process.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "hatenaApi.h"
#include "twitStar.h"
#ifdef __cplusplus
}
#endif
#include "confirmProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/registerBookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef  WIN32
#include <shlwapi.h>
#else

char    *strstri( const char *src, const char *target )
{
    char        *p = NULL;
    const char  *q;
    size_t      len1 = (src && *src) ? strlen( src ) : 0;
    size_t      len2 = (target && *target) ? strlen( target ) : 0;

    if ( (len1 == 0) || (len2 == 0) || (len1 < len2) )
        return ( p );

    for ( q = src; *src && (len1 >= len2); q++, len1-- ) {
        if ( !strncmpi( q, target, len2 ) ) {
            p = (char *)q;
            break;
        }
    }

    return ( p );
}

#define StrStrI strstri
#endif

void    SetUserAgent( bool set );


// URL �̖����� ?{ref|from}={rss|RSS|atom}, &f=rss ���폜����
char    *
getRegularURL( char *url )
{
    char    *p;
    char    tmp[1024];

    if ( !strncmp( url, "http://www.google.com/url?", 26 ) ) {
        p = strstr( url, "?q=http://" );
        if ( !p )
            p = strstr( url, "&q=http://" );
        if ( p )
            strcpy( url, p + 3 );
    }

    if ( !strncmp( url, "http://www.neowing.co.jp/rss/rss.html?", 38 ) ) {
        p = strchr( url, '?' );
        if ( p ) {
            strcpy( tmp, p );
            sprintf( url, "http://www.neowing.co.jp/detailview.html%s", tmp );
        }
    }

    if ( !strncmp( url, "http://codezine.jp/r.x/rss/aid/",  31 ) ||
         !strncmp( url, "http://markezine.jp/r.x/rss/aid/", 32 )    ) {
        p = strrchr( url, '/' );
        if ( p ) {
            strcpy( tmp, p + 1 );
            if ( !strncmp( url, "http://codezine.jp/", 19 ) )
                sprintf(url, "http://codezine.jp/a/article.aspx?aid=%s", tmp);
            else
                sprintf(url, "http://markezine.jp/a/article.aspx?aid=%s",tmp);
        }
    }

    if ( !strncmp( url, "http://markezine.jp/r.x/rss/bid/", 32 ) ) {
        p = strrchr( url, '/' );
        if ( p ) {
            strcpy( tmp, p );
            sprintf( url,
              "http://markezine.jp/bookmark/default.aspx?mode=detail&bid=%s",
                     tmp );
        }
    }

    if ( strstr( url, ".ibm.com/" ) ) {
        p = strstr( url, "/index.shtml?ca=drs-" );
        if ( p )
            *(p + 1) = NUL;
    }

    if ( strstr( url, "japan.internet.com/" ) ) {
        p = strstr( url, "?rss" );
        if ( p )
            *p = NUL;
    }

    if ( ( ( p = StrStrI( url, "?ref=rss"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=rss"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?fr=RSS"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?fr=rdf"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?ref=atom"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=atom"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&f=rss"         ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&from=rss"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?in=rssw"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=top"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?topic=1"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?tag=nl"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?bcsi_scan"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&ST=web_threat" ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?ref=BPN"       ) ) != NULL ) ||
         ( ( p = StrStrI( url, "&fm=rss"        ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?feedType=RSS"  ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=main"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=navr"     ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=any"      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?from=hot"      ) ) != NULL ) ||
      // ( ( p = StrStrI( url, "?rss_fdn="      ) ) != NULL ) ||
         ( ( p = StrStrI( url, "?rss"           ) ) != NULL )    )
        *p = NUL;

    return ( url );
}


// Web�y�[�W���擾�X���b�h
typedef struct IWparam {
    RBparam_t           rbParam;
    char                accountName[32];
    EditBookmarkDialog  *editDlg;
    ProceedingDialog    *procDlg;
}   IWparam_t;

static char    *
escapeAmpersand( char *p )
{
    char    *s, *t, *u;

    s = strchr( p, '&' );
    while ( s ) {
        t = strchr( s, ';' );
        u = strchr( s, '&' );
        if ( !t || (u && (u < t)) ) {
            char    *pp = s + strlen( s );
            while ( pp > s ) {
                *(pp + 2) = *pp;
                pp--;
            }
            *s++ = '%';
            *s++ = '2';
            *s++ = '6';

            s = strchr( s, '&' );
        }
        else
            break;
    }

    return ( p );
}

void
getBookmarkViaEntryPageOnHatena(
        const char *username,
        const char *url,
        char       *title,
        char       *summary,
        char       *tags
    )
{
    int     sz = MAX_CONTENT_SIZE * 20;
    char    *response;
    char    *temp;
    char    entryPageURL[MAX_URLLENGTH * 8];

    response = (char *)malloc( sz );
    if ( !response )
        return;
    temp = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !temp ) {
        free( response );
        return;
    }

    sprintf( entryPageURL,
             "http://b.hatena.ne.jp/entry/%s",
             escapeAmpersand( encodeURLforHatena( url ) ) );
    setUpReceiveBuffer( response, sz );
    http_get( entryPageURL, response );
    if ( *response ) {
        char    *p, *q, *r, *s;
        char    targetString[BUFSIZ];
        size_t  len;

        sprintf( targetString,
                 "id=\"bookmark-user-%s\"",
                 username );
        len = strlen( targetString );
        p = strstr( response, targetString );
        if ( p ) {
            p += len;
            s = strstr( p, "</li>" );

            if ( s ) {
                /* tags */
                q = strstr( p, "<span class=\"tags\">" );
                if ( q && (q < s) ) {
                    r = q + 19;
                    q = strstr( r, "</span>" );
                    if ( q && (q < s) ) {
                        char    *pp, *qq;

                        temp[0] = NUL;
                        len     = 0;
                        while ( r < q ) {
                            pp = strstr( r, "<a " );
                            qq = strstr( r , "</a>" );
                            if ( pp && qq && (pp < qq) && (qq < q) ) {
                                pp = strchr( pp, '>' );
                                if ( pp ) {
                                    if ( len > 0 ) {
                                        temp[len++] = ' ';
                                        temp[len]   = NUL;
                                    }
                                    pp++;
                                    strncat( temp, pp, qq - pp );
                                    len += (qq - pp);
                                    temp[len] = NUL;
                                    r = qq + 4;
                                    continue;
                                }
                            }
                            break;
                        }
                        if ( temp[0] ) {
                            r = utf2sjisEx( temp );
                            strcpy( tags, r ? r : temp );
                        }
                    }
                }

                /* comment */
                q = strstr( p, "<span class=\"comment\">" );
                if ( q && (q < s) ) {
                    r = q + 22;
                    q = strstr( r, "</span>" );
                    if ( q && (q < s) ) {
                        strncpy( temp, r, q - r );
                        temp[q - r] = NUL;
                        r = utf2sjisEx( temp );
                        strcpy( summary, r ? r : temp );
                    }
                }

                /* title */
                p = strstr( response, "<h2 class=\"entrytitle\">" );
                if ( p ) {
                    p += 23;
                    q = r = strstr( p, "</a></h2>" );
                    if ( q ) {
                        while ( q > p ) {
                            if ( (*q == '<') && !strncmp( q + 1, "a ", 2 ) ) {
                                p = q + 3;
                                q = strchr( p, '>' );
                                if ( q ) {
                                    q++;
                                    strncpy( title, q, r - q );
                                    title[r - q] = NUL;
                                    utf2sjisEx( title );
                                }
                                break;
                            }
                            q--;
                        }
                    }
                }
            }
        }
    }

    free( temp );
    free( response );
}

void
getBookmarkViaEntryPageOnLivedoor(
        const char *username,
        const char *url,
        char       *title,
        char       *summary,
        char       *tags
    )
{
    int     sz = MAX_CONTENT_SIZE * 20;
    char    *response;
    char    *temp;
    char    entryPageURL[MAX_URLLENGTH * 8];

    response = (char *)malloc( sz );
    if ( !response )
        return;
    temp = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !temp ) {
        free( response );
        return;
    }

    sprintf( entryPageURL,
             "http://clip.livedoor.com/page/%s",
             escapeAmpersand( encodeURLforHatena( url ) ) );
    setUpReceiveBuffer( response, sz );
    http_get( entryPageURL, response );
    if ( *response ) {
        char    *p, *q, *r, *s;
        char    targetString[BUFSIZ];
        size_t  len;

        sprintf( targetString,
                 "livedoorProfileNickname('%s')",
                 username );
        len = strlen( targetString );
        p = strstr( response, targetString );
        if ( p ) {
            p += len;
            s = strstr( p, "<ul" );
            if ( !s )
                s = strstr( p, "<h4" );

            if ( s ) {
                /* tags */
                q = strstr( p, "user-tag-box" );
                if ( q && (q < s) ) {
                    r = q + 12;
                    q = strstr( r, "</span>" );
                    if ( q && (q < s) ) {
                        char    *pp, *qq;

                        temp[0] = NUL;
                        len     = 0;
                        while ( r < q ) {
                            pp = strstr( r, "<a " );
                            qq = strstr( r , "</a>" );
                            if ( pp && qq && (pp < qq) && (qq < q) ) {
                                pp = strchr( pp, '>' );
                                if ( pp ) {
                                    if ( len > 0 ) {
                                        temp[len++] = ' ';
                                        temp[len]   = NUL;
                                    }
                                    pp++;
                                    strncat( temp, pp, qq - pp );
                                    len += (qq - pp);
                                    temp[len] = NUL;
                                    r = qq + 4;
                                    continue;
                                }
                            }
                            break;
                        }
                        if ( temp[0] ) {
                            r = utf2sjisEx( temp );
                            strcpy( tags, r ? r : temp );
                        }
                    }
                }

                /* comment */
                q = strstr( p, "<p " );
                if ( q && (q < s) ) {
                    r = strchr( q + 3, '>' );
                    if ( r ) {
                        r++;
                        q = strstr( r, "</p>" );
                        if ( q && (q < s) ) {
                            strncpy( temp, r, q - r );
                            temp[q - r] = NUL;
                            r = utf2sjisEx( temp );
                            strcpy( summary, r ? r : temp );
                        }
                    }
                }

                /* title */
                p = strstr( response, "id=\"pagettl\"" );
                if ( !p ) {
                    p = strstr( response, url );
                    if ( p )
                        p -= 12;
                }
                if ( p ) {
                    p += 12;
                    q = r = strstr( p, "</a></h3>" );
                    if ( q ) {
                        while ( q > p ) {
                            if ( (*q == '<') && !strncmp( q + 1, "a ", 2 ) ) {
                                p = q + 3;
                                q = strchr( p, '>' );
                                if ( q ) {
                                    q++;
                                    strncpy( title, q, r - q );
                                    title[r - q] = NUL;
                                    utf2sjisEx( title );
                                }
                                break;
                            }
                            q--;
                        }
                    }
                }
            }
        }
    }

    free( temp );
    free( response );
}


UINT
InquiryWebPageInfo( LPVOID pParam )
{
    IWparam_t   *p  = (IWparam_t *)pParam;
    int         ret = 0;
    char        url[MAX_URLLENGTH];
    char        asin[32];
    CString     ttle;
    CString     text;
    static BOOL stat1470net = TRUE;

    SetUserAgent( TRUE );   /* User-Agent ���ꎞ�I�ɕύX */

    ttle.LoadString(IDS_TTL_CONTINUE_GETTING_TITLE);
    text.LoadString(IDS_TXT_CONTINUE_GETTING_TITLE);
    p->procDlg->ChangeDialogText( ttle,     // �^�C�g���擾��
                                  text );   // �^�C�g���擾���c�c
    asin[0] = NUL;

    // URL �̖����� ?{ref|from}={rss|RSS|atom}, &f=rss ���폜����
    getRegularURL( p->rbParam.url );

    // -- 407(Proxy Authentication Required) �΍�      @@
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();    // @@
    if ( bp->m_useProxy )                           // @@
        setConfirmProxyInfoFunc( confirmProxyInfo );// @@
    // ���Y URL �� Web�y�[�W�� title ���擾
    p->accountName[0] = NUL;
    BOOL posted       = FALSE;
    char *hatenaTags  = NULL;
    char *title = getTitle( p->rbParam.url, p->accountName,
                            p->rbParam.hatena.isTarget
                                ? p->rbParam.hatena.username : "",
                            &hatenaTags,
                            &posted );
    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );     // @@

    if (!strncmp(p->rbParam.url, "http://feeds.feedburner.com/",     28) ||
        !strncmp(p->rbParam.url, "http://feeds.feedburner.jp/",      27) ||
        !strncmp(p->rbParam.url, "http://rd.yahoo.co.jp/rss/l/",     28) ||
        !strncmp(p->rbParam.url, "http://srd.yahoo.co.jp/BMK/",      27) ||
        !strncmp(p->rbParam.url, "http://www.pheedo.jp/click.phdo?", 32) ||
        !strncmp(p->rbParam.url, "http://www.pheedo.com/click.phdo?",33) ||
        !strncmp(p->rbParam.url,
                           "http://pheedo.vector.co.jp/click.phdo?", 38) ||
        !strncmp(p->rbParam.url, "http://markezine.jp/r.x/bmc/bid/", 32) ||
        !strncmp(p->rbParam.url, "http://cgi.itmedia.co.jp/rss/",    29) || 
        !strncmp(p->rbParam.url, "http://cm.thinkit.co.jp/?",        25) ||
        !strncmp(p->rbParam.url, "http://go.microsoft.com/?linkid=", 32) ||
        !strncmp(p->rbParam.url,
                    "http://co1piltwb.partners.extranet.microsoft.com/"
                    "mcoeredir/mcoeredirect.aspx?",                  77) ||
        !strncmp(p->rbParam.url, "http://tinyurl.com/",              19) ||
        !strncmp(p->rbParam.url, "http://rurl.org/",                 16) ||
        !strncmp(p->rbParam.url, "http://z.la/",                     12) ||
        !strncmp(p->rbParam.url, "http://rss.asahi.com/click.phdo?", 32) ||
        !strncmp(p->rbParam.url,
                           "http://rss.yomiuri.co.jp/click.phdo?",   36) ||
        !strncmp(p->rbParam.url, "http://feeds.japan.zdnet.com/"   , 29) ||
        !strncmp(p->rbParam.url, "http://feeds.japan.cnet.com/"    , 28) ||
        !strncmp(p->rbParam.url, "http://feeds.reuters.com/",        25) ||
        !strncmp(p->rbParam.url, "http://rd.nikkei.co.jp/",          23) ||
        !strncmp(p->rbParam.url, "http://rss.rssad.jp/rss/",         24) ||
        !strncmp(p->rbParam.url,
                           "http://symantecenterprise.rsys3.net/",   36) ||
        !strncmp(p->rbParam.url, "http://www.oracle.co.jp/mp/",      27) ||  
        !strncmp(p->rbParam.url, "http://c2.lenovo-news.com/g.php/", 32) ||
        !strncmp(p->rbParam.url, "http://communications1.sun.com/r/",33) ||
        !strncmp(p->rbParam.url, "http://www.amazon.com/gp/r.html?", 32)   ) {
        url[0] = NUL;
        getCurrentLocation( url );
        p->editDlg->m_url = getRegularURL( url );
        if (!strncmp( p->rbParam.url,"http://www.pheedo.jp/click.phdo?",32)) {
            if ( hatenaTags ) {
                free( hatenaTags );
                hatenaTags = NULL;
            }
            p->accountName[0] = NUL;
            title = getTitle( url, p->accountName,
                              p->rbParam.hatena.isTarget
                                ? p->rbParam.hatena.username : "",
                              &hatenaTags,
                              &posted );
        }
        // CNET Japan �ł̗�
        //    (1) http://feeds.feedburner.jp/cnet/rss?m=1575
        //    (2) http://japan.cnet.com/news/ent/story/0,2000056022,20122187,00.htm?ref=rss
        //    (3) http://japan.cnet.com/news/ent/story/0,2000056022,20122187,00.htm
        //  (1) �� feedburner.jp �o�R�Ŕz�M����Ă���t�B�[�h���� permalink
        //  (2) �� (1) �ɃA�N�Z�X�����Ƃ��̃��_�C���N�g�� URL
        //  bookey �́A�ŏI�I�� (3) �� URL ���̗p���A�u�b�N�}�[�N�ɓo�^����
    }
    else
        p->editDlg->m_url = p->rbParam.url;

    if ( checkProxyInfo() ) {
        SetUserAgent( FALSE );  /* User-Agent �����ɖ߂� */
        return ( ret );
    }

    if ( title && *title )
        p->editDlg->m_title = title;
    p->editDlg->m_enableTipJar = p->accountName[0] ? true : false;
    p->editDlg->m_useCategory  =
        (p->rbParam.drecomRss.username[0] || p->rbParam.flog.username[0])
                                                               ? true : false;
    getASIN( p->rbParam.url, asin );
    if ( asin[0] &&
         !strncmp( p->editDlg->m_url, "http://www.amazon.", 18 ) ) {
        // URL �̐��K�� (�͂Ăȃu�b�N�}�[�N�̃R���N�V�����΍�)
        //   �����ł́Aamazon.co.jp �ȊO�� amazon �ɂ��Ă� URL ��
        //   ���K�����s�Ȃ��Ă��邪�A�u�͂Ăȃu�b�N�}�[�N�v�̃R���N
        //   �V�����Ƃ��ēo�^�\�Ȃ̂� amazon.co.jp �̏��i�����ł�
        //   �� (amazon.com �̏��i�̓R���N�V�����o�^���悤�Ƃ��Ă�
        //   �o�^����Ȃ�)
        //   ���Ȃ݂ɁA1470.net �� MONO �� ASIN �����w�肷��΁A
        //   amazon.co.jp �ȊO�̏��i���o�^�ł���(�Ȃ����A���܂� MONO
        //   �̓o�^�ł͂Ȃ��A���ʂ̃u�b�N�}�[�N�̓o�^�ɂȂ��Ă��܂�
        //   ���Ƃ�����悤����)
        char        host[MAX_URLLENGTH];
        const char  *pp;

        pp = strchr( (const char *)(p->editDlg->m_url) + 18, '/' );
        if ( pp ) {
            char    *qq;
            strncpy( host, p->editDlg->m_url, 64 );
            host[64] = NUL;
            qq = strchr( host + 18, '/' );
            if ( qq )
                *(qq + 1) = NUL;
            pp = qq;
        }
        if ( !pp )
            strcpy( host, "http://www.amazon.co.jp/" );

        p->editDlg->m_url =  host;
        p->editDlg->m_url += "gp/product/";
        p->editDlg->m_url += asin;
        p->editDlg->m_url += "/";
    }
    p->editDlg->m_enableCollection =
            p->rbParam.hatena.username[0] && asin[0] ? true : false;

    if ( p->rbParam.useTagSuggestion ) {
        // ���Y URL �� Web�y�[�W�̃^�O���𒊏o
        char    **tags;
        int     numOfTags    = 0;
        int     maxNumOfTags = 20;
        tags = (char **)malloc( maxNumOfTags * sizeof ( char * ) );
        if ( tags ) {
            ttle.LoadString(IDS_TTL_CONTINUE_ANALYSING);
            text.LoadString(IDS_TXT_CONTINUE_ANALYSING);
            p->procDlg->ChangeDialogText( ttle,     // �^�O��⒊�o��
                                          text );   // �^�O��⒊�o���c�c
            int i;
            for ( i = 0; i < maxNumOfTags; i++ ) {
                tags[i] = (char *)malloc( MAX_DESCRIPTION_LEN );
                if ( !(tags[i]) )
                    break;
                tags[i][0] = NUL;
                numOfTags++;
            }

            CString yahooAppID;
            yahooAppID.LoadString(IDS_BOOKEY_API_ID);
            extractTags( (const char *)(p->editDlg->m_url), tags, &hatenaTags,
                         &numOfTags, &stat1470net, (const char*)yahooAppID );

            for ( i = 0; i < numOfTags; i++ )
                *(p->editDlg->m_tag[i]) = tags[i][0] ? tags[i] : "";
            for ( i = maxNumOfTags; i > 0; i-- )
                free( tags[i - 1] );
            free( tags );
        }
    }

    if ( p->rbParam.useUsers ) {
        // ���YURL ���u�b�N�}�[�N���Ă���l�̐����擾
        ttle.LoadString(IDS_TTL_GETTING_BOOKMARK_USERS);
        text.LoadString(IDS_TXT_GETTING_HATENA_USERS);
        p->procDlg->ChangeDialogText( ttle,     // �u�b�N�}�[�N�o�^�Ґ��擾��
                                      text );   // �͂Ăȃu�b�N�}�[�N �������c�c
        p->editDlg->m_hbUsers = getUsersOfHatenaBookmark( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_DELICIOUS_USERS);
        p->procDlg->ChangeDialogText( ttle,     // �u�b�N�}�[�N�o�^�Ґ��擾��
                                      text );   // del.icio.us �������c�c
        p->editDlg->m_deliciousUsers = getUsersOfDelicious(p->editDlg->m_url);

        if ( stat1470net ) {
            text.LoadString(IDS_TXT_GETTING_MMMEMO_USERS);
            p->procDlg->ChangeDialogText( ttle,  // �u�b�N�}�[�N�o�^�Ґ��擾��
                                          text );// MM/Memo �������c�c
            p->editDlg->m_mmUsers = getUsersOfMMmemo( p->editDlg->m_url,
                                                      &stat1470net );
        }

        text.LoadString(IDS_TXT_GETTING_ECNAVI_USERS);
        p->procDlg->ChangeDialogText( ttle,     // �u�b�N�}�[�N�o�^�Ґ��擾��
                                      text );   // Buzzurl �������c�c
        p->editDlg->m_ecNaviUsers = getUsersOfECnaviClip( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_LIVEDOORCLIP_USERS);
        p->procDlg->ChangeDialogText( ttle,     // �u�b�N�}�[�N�o�^�Ґ��擾��
                                      text );   // livedoor�N���b�v �������c�c
        p->editDlg->m_livedoorClipUsers = getUsersOfLivedoorClip( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_NIFTYCLIP_USERS);
        p->procDlg->ChangeDialogText( ttle,     // �u�b�N�}�[�N�o�^�Ґ��擾��
                                      text );   // @nifty�N���b�v �������c�c
        p->editDlg->m_niftyClipUsers = getUsersOfNiftyClip( p->editDlg->m_url );

        text.LoadString(IDS_TXT_GETTING_DIGG_USERS);
        p->procDlg->ChangeDialogText( ttle,     // �u�b�N�}�[�N�o�^�Ґ��擾��
                                      text );   // digg �������c�c
        p->editDlg->m_diggUsers = getUsersOfDigg( p->editDlg->m_url );

        ttle.LoadString(IDS_TTL_GETTING_NUM_OF_STARS);
        text.LoadString(IDS_TXT_GETTING_HATENA_STAR_USERS);
        p->procDlg->ChangeDialogText( ttle,     // ���̐��擾��
                                      text );   // �͂ĂȃX�^�[ �������c�c
        char    buf[64];
        long    numOfHatenaStar = getHatenaStar( p->editDlg->m_url );
        p->editDlg->m_hatenaStarUsers = _T("(");
        p->editDlg->m_hatenaStarUsers += ltoa( numOfHatenaStar, buf, 10 );
        p->editDlg->m_hatenaStarUsers += _T(")");
    }

    if ( hatenaTags ) {
        free( hatenaTags );
        hatenaTags = NULL;
    }

    // (�ēo�^���s����)�R�����g�A�^�O�̎擾
    if ( (p->rbParam.hatena.isTarget == TRUE) && (posted == TRUE) ) {
        char    title[MAX_DESCRIPTION_LEN];
        char    summary[MAX_DESCRIPTION_LEN];
        char    tags[MAX_DESCRIPTION_LEN];
        char    entryID[HASH_LENGTH + 1];

        title[0]   = NUL;
        summary[0] = NUL;
        tags[0]    = NUL;
        entryID[0] = NUL;
        if ( strchr( p->editDlg->m_url, '?' ) &&
             strchr( p->editDlg->m_url, '=' ) &&
             strchr( p->editDlg->m_url, '&' )    ) {
            char    temp[MAX_DESCRIPTION_LEN];
            strcpy( temp, p->editDlg->m_url );
            getBookmarkOnHatenaWithURI( p->rbParam.hatena.username,
                                        p->rbParam.hatena.password,
                                        escapeAmpersand( temp ),
                                        title, summary, tags, entryID );
        }
        else
            getBookmarkOnHatenaWithURI( p->rbParam.hatena.username,
                                        p->rbParam.hatena.password,
                                        encodeURLforHatena(p->editDlg->m_url),
                                        title, summary, tags, entryID );
        if ( summary[0] )
            p->editDlg->m_comment = summary;
        else if ((!(title[0]) || !strcmp( title, "�͂Ăȃu�b�N�}�[�N" )) &&
                 (entryID[0] == NUL)                                       ) {
            getBookmarkViaEntryPageOnHatena(
                                        p->rbParam.hatena.username,
                                        p->editDlg->m_url,
                                        title, summary, tags );
            if ( summary[0] )
                p->editDlg->m_comment = summary;
        }
        if ( tags[0] )
            p->editDlg->m_tags = tags;
    }

    if ( (p->editDlg->m_comment.GetLength() >= 98)       ||
         ( (p->editDlg->m_comment.GetLength() == 0) &&
           (p->editDlg->m_tags.GetLength() == 0)       )    ) {
        char    title[MAX_DESCRIPTION_LEN];
        char    summary[MAX_DESCRIPTION_LEN];
        char    tags[MAX_DESCRIPTION_LEN];

        title[0]   = NUL;
        summary[0] = NUL;
        tags[0]    = NUL;

        if ( p->rbParam.livedoorClip.isTarget == TRUE )
            getBookmarkViaEntryPageOnLivedoor(
                                        p->rbParam.livedoorClip.username,
                                        p->editDlg->m_url,
                                        title, summary, tags );

        if ( summary[0] )
            p->editDlg->m_comment = summary;
        if ( tags[0] )
            p->editDlg->m_tags = tags;
    }

    SetUserAgent( FALSE );  /* User-Agent �����ɖ߂� */
    return ( ret );
}

void
GetWebPageInfo( const RBparam_t    *p, 
                char               *accountName,
                EditBookmarkDialog *editDlg,
                ProceedingDialog   *procDlg )
{
    IWparam_t           param2;

    procDlg->ShowWindow( SW_SHOWNORMAL );

    memcpy( &param2.rbParam, p, sizeof ( RBparam_t ) );
    param2.accountName[0] = NUL;
    param2.editDlg        = editDlg;
    param2.procDlg        = procDlg;

    // Web�y�[�W���擾�X���b�h���N��
    CWinThread  *tp = AfxBeginThread( InquiryWebPageInfo,
                                      (void *)&param2 );
    if ( tp ) {
        DWORD       exitCode  = 0;
        int         status;
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

        // Web�y�[�W���擾�X���b�h���I������̂�҂�
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView �̍ĕ`��
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog �̍ĕ`��
                procDlg->SetFocus();
                procDlg->UpdateWindow();
                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        if ( param2.accountName[0] )
            strcpy( accountName, param2.accountName );

        delete tp;
    }

    procDlg->ShowWindow( SW_HIDE );
}

// �u�b�N�}�[�N�o�^�X���b�h
UINT
RegisterBookmark( LPVOID pParam )
{
    UINT        ret = 0;
    RBparam_t   *p  = (RBparam_t *)pParam;
    RBparam_t   param;

    // ���S�̂��߁A�R�s�[�������̂��g��
    memcpy( &param, p, sizeof ( RBparam_t ) );
    p = &param;

    EditBookmarkDialog  editDlg;
    ProceedingDialog    *procDlg = param.procDialog;
    char                accountName[32];

    // �o�^���悤�Ƃ��Ă���Web�y�[�W�Ɋւ�������擾(�^�C�g���A�^�O���)
    accountName[0] = NUL;
    procDlg->ResetDialogText();
    procDlg->ShowWindow( SW_SHOWNORMAL );
    GetWebPageInfo( p, accountName, &editDlg, procDlg );

    if ( checkProxyInfo() )
        return ( ret );

    // �u�]���v�֘A
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    if ( pp->m_newsing == true ) {
          /* newsing �� ���~���[�𗘗p����ꍇ */
        editDlg.m_affirmation = AFF_REQUESTED;
    }
    editDlg.m_evaluation = (pp->m_mmMemo       == true) ||
                           (pp->m_livedoorClip == true) ||
                           (pp->m_next1470net  == true)    ? EVL_REQUESTED
                                                           : EVL_NONE;
    // �u���J��ԁv�֘A
    /* Blue Dot �́u���J��ԁv�w��͏����Ή��Ƃ��� */
    editDlg.m_public = (pp->m_blogPet      == true) /* ||
                       (pp->m_blueDot      == true) */
                                                    ? PUB_REQUESTED2 :
                       (pp->m_livedoorClip == true) ||
                       (pp->m_fc2bookmark  == true) ||
                       (pp->m_yjBookmark   == true)
                                                    ? PUB_REQUESTED
                                                    : PUB_EVERYONE;

    // �o�^���邩�ۂ��̐ݒ���ꎞ�I�ɕύX����ړI�� param ���g�p {@@}
    editDlg.m_param = param;

    // �R�����g�A�^�O�̓���
    int r = editDlg.DoModal();
    if ( r == IDOK ) {
        if ( editDlg.m_url.GetLength() > 0 ) {
            // �u�b�N�}�[�N�̓o�^
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            p = &(editDlg.m_param); /* {@@} */
            pp->PutBookmarks( p, accountName, &editDlg, procDlg );
        }
        else {
            CString title;
            CString text;

            title.LoadString(IDS_TTL_URL_CHECK_RESULT);
            text.LoadString( IDS_TXT_INVALID_URL);
            text += editDlg.m_url;
            ::MessageBox( NULL,
                          text,
                          title,    // URL �`�F�b�N����
                          MB_OK|MB_ICONWARNING );
        }
    }

    procDlg->ShowWindow( SW_HIDE );

    return ( ret );
}


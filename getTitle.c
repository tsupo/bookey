/*
 *  �w�� Web �y�[�W�� title ���擾����
 *      written by H.Tsujimura  14 Oct 2005
 *
 * $Log: /comm/bookey/getTitle.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 32    09/02/24 2:15 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v�̌���̃G���g���y�[�W�ɍ��킹�āA�^�O���o������
 * ����
 * 
 * 31    08/11/25 19:37 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v2008�N11��25�����j���[�A���łł̓�����m�F
 * 
 * 30    08/11/25 13:08 Tsujimura543
 * getTitle() ���A�u�͂Ăȃu�b�N�}�[�N�v�� 503 ��Ԃ��Ă����ꍇ�ɂ��Ή�
 * ������
 * 
 * 29    08/11/25 11:35 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v�����C���e�i���X���̂Ƃ��ɁAcharset=Shift_JIS ��
 * �y�[�W���u�b�N�}�[�N���悤�Ƃ���ƁAgetTitle() ���Ԃ� title ����������
 * ���Ă��܂��s��ɑΏ�
 * 
 * 28    08/07/28 21:09 Tsujimura543
 * �R�����g���C��
 * 
 * 27    08/07/28 21:05 Tsujimura543
 * getTitle() ���A�b�v�f�[�g
 * (�͂Ăȃu�b�N�}�[�N�̃G���g���y�[�W���Alogin�ς݂��ǂ����ŁA�^�O
 * �N���E�h���\�����ꂽ�肳��Ȃ������肷��悤�ɂȂ����A��������
 * �ύX���������̂ɔ����C�������{)
 * 
 * 26    08/04/15 15:07 Tsujimura543
 * �R�����g���C��
 * 
 * 25    08/04/15 15:05 Tsujimura543
 * title�v�f�� &lt;, &gt;, &quot; ���܂܂��ꍇ�A�f�R�[�h���ĕ\������
 * �悤�ɕύX
 * 
 * 24    07/06/08 14:44 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N����^�O�����擾�v��2007�N6��8�����_�̂͂Ă�
 * �u�b�N�}�[�N�̃G���g���y�[�W�̃t�H�[�}�b�g�ɍ��킹�ĕύX
 * (6���̂͂��߂Ƀf�U�C�����ύX���ꂽ)
 * 
 * 23    07/02/02 23:36 Tsujimura543
 * getTitle() �̈�����ǉ�
 * 
 * 22    06/07/27 18:55 Tsujimura543
 * (1) ��M�d���i�[�p�̈�̃I�[�o�[�����h�~�@�\��g�ݍ���
 * (2) ��M�d���i�[�p�̈�̃T�C�Y�� 1/20 �Ɍ��炵��
 * 
 * 21    06/07/27 18:46 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�������e�i���X���̂Ƃ��A���ۂ̋L���̃^�C�g���Ɋ֌W��
 * ���A�^�C�g�����u���݃����e�i���X���ł��B�v�ɂȂ��Ă��܂��s��ɑΏ�
 * 
 * 20    06/07/18 20:47 Tsujimura543
 * &raquo: �֘A�̏������C��(�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����R�[�h�̌���
 * ��)
 * 
 * 19    06/07/06 14:57 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v����擾�����^�C�g���� &#39; �Ȃǐ��l�Q�Ƃ�
 * �܂܂��ꍇ�A�f�R�[�h����悤�ɂ���
 * 
 * 18    06/06/29 10:35 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̃^�O�N���E�h�𒊏o���鏈�����A2�l�ȏ�̐l���g�p����
 * ������̂����𒊏o����悤�ɕύX����
 * 
 * 17    06/06/26 12:33 Tsujimura543
 * asahi.com �΍� #2 (asahi.com �� �͂Ăȃu�b�N�}�[�N�̑g�ݍ��킹�Ŕ���
 * ���镶�������΍�) ��ǉ�
 * 
 * 16    06/06/12 14:18 Tsujimura543
 * �֐��� staic �ϐ��� TLS ������
 * 
 * 15    06/06/01 11:33 Tsujimura543
 * charset �� ISO-2022-JP �� Web �y�[�W�ɂ��Ή�����
 * 
 * 14    06/05/23 15:59 Tsujimura543
 * getTitle() �� extractTags() �̘A�g�ɂ��u�͂Ăȃu�b�N�}�[�N�v�����
 * �^�O���擾���T�|�[�g
 * 
 * 13    06/03/13 20:53 Tsujimura543
 * ���҂ɂ���Ă͂Ăȃu�b�N�}�[�N�ɓo�^�ς݂̃y�[�W��o�^����ꍇ�A���Y
 * �y�[�W�� EUC-JP ���ƃ^�C�g����������������s��ɑΏ� (�͂Ăȃu�b�N
 * �}�[�N����擾�����^�C�g���� UTF-8 �Ȃ̂� EUC-JP �Ƃ݂Ȃ��ď��������
 * ������������)
 * 
 * 12    06/02/22 17:33 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 11    06/02/22 16:45 Tsujimura543
 * &raquo; �ȂǁAShift_JIS �� EUC-JP �ł͕����������N���������Ɋւ���΍�
 * �����{
 * 
 * 10    06/02/06 20:47 Tsujimura543
 * �R�����g���C��
 * 
 * 9     06/02/06 20:44 Tsujimura543
 * ���łɒN�����u�͂Ăȃu�b�N�}�[�N�v�ɓo�^���Ă���ꍇ�́A�u�͂Ăȃu�b�N
 * �}�[�N�ɓo�^����Ă��� title �ŏ㏑������悤�ɂ���
 * 
 * 8     06/02/01 15:41 Tsujimura543
 * <title lang="ja"> �̂悤�ɑ������w�肳��Ă���P�[�X�ɂ��Ή�����
 * 
 * 7     05/12/22 19:09 Tsujimura543
 * title �v�f�ɗ]���� white space ���܂܂��ꍇ�A��������悤�ɂ���
 * (�͂Ăȃu�b�N�}�[�N�̎d�l�ɍ��킹��)
 * 
 * 6     05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 5     05/10/28 15:40 Tsujimura543
 * ISO-8859-1 �� 0xA0 �` 0xFF �̋�Ԃɂ��镶���ɑΏ����邽�߂̃R�[�h��ǉ�
 * 
 * 4     05/10/24 19:00 Tsujimura543
 * �^�C�g���� &#160; ���܂܂��ꍇ�́A�󔒕����ɒu������悤�ɂ���
 * 
 * 3     05/10/24 17:37 Tsujimura543
 * getTitle() �� Account-auto-discovery �ɑΉ�����悤�g������
 * 
 * 2     05/10/14 20:37 Tsujimura543
 * �����R�[�h�� Shift_JIS �ȊO�� Web �y�[�W�̂��Ƃ���������Y��Ă���
 * 
 * 1     05/10/14 15:23 Tsujimura543
 * �ŏ��̔�
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getTitle.c 1     09/05/14 3:48 tsupo $";
#endif

#define BUFFER_SIZE_FOR_GETTITLE    2048

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
encodeURLforHatena( const char *url )
{
    Thread  static char url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *p;
    char                *q;

    strcpy( url2, url );
    while ( (p = strchr( url2, '#' )) != NULL ) {
        q = &url2[strlen(url2)];
        while ( q >= p + 1 ) {
            *(q + 2) = *q;
            q--;
        }
        *p++ = '%';
        *p++ = '2';
        *p   = '3';
    }

    return ( url2 );
}

char    *
getTitle(
        const char *url,        /* (I) ���YWeb�y�[�W��URL                  */
        char       *accountName,/* (O) AccountName-auto-discovery �Ŏ擾�� */
                                /*     �����YWeb�y�[�W�̃I�[�i�[��(�͂Ă�) */
                                /*     �A�J�E���g��                        */
        char       *hatenaID,   /* (I) �͂Ă�ID(���łɎ������g�œo�^�ς݂� */
                                /*     �ۂ��̃`�F�b�N���s�Ȃ��Ƃ��Ɏw��)   */
        char       **hatenaTags,/* (O) �͂ău����擾�����^�O���          */
                                /*     (����: �{�֐����Ŋi�[�p�̗̈���m�� */
                                /*      ����B�{�֐��̌Ăяo�����ŗ̈�̉� */
                                /*      �����s�Ȃ�����)                    */
        BOOL       *posted      /* (O) ���łɎ������g�œo�^�ς݂��ۂ�      */
    )
{
    Thread  static char title[BUFFER_SIZE_FOR_GETTITLE];
    char                title2[BUFFER_SIZE_FOR_GETTITLE];
    char                url2[BUFFER_SIZE_FOR_GETTITLE];
    char                *response;
    char                *p, *q;
    BOOL                useHatenaBookmark = FALSE;
    size_t              sz;

    *hatenaTags = NULL;
    *posted     = FALSE;
    title[0]    = NUL;
    title2[0]   = NUL;

    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( title );

    sprintf( url2, "http://b.hatena.ne.jp/entry/%s",
             encodeURLforHatena( url ) );

    setUpReceiveBuffer( response, sz );
    http_get( url2, response );
    if ( response && response[0] ) {
        if ( !strstr( response,
     //               sjis2utf( "<div id=\"breadcrumbs\"><a href=\"/\">�͂Ă�"
     //                         "�u�b�N�}�[�N</a> &gt; ���u�b�N�}�[�N�G���g��"
     //                         "�[</div>") ) ) {
                      sjis2utf( "���u�b�N�}�[�N�G���g���[") ) ) {
            p = strstr( response, "<title>" );
            if ( p ) {
                char    *q = strstr( p, " - " );
                if ( q ) {
                    p = q + 3;
                    q = strstr( p, "</" );
                    if ( q ) {
                        strncpy( title2, p, q - p );
                        title2[q - p] = NUL;
                    }
                }
                
                p = title2;
                while ( ( q = strstr( p, "&lt;" ) ) != NULL ) {
                    *q = '<';
                    strcpy( q + 1, q + 4 );
                }
                while ( ( q = strstr( p, "&gt;" ) ) != NULL ) {
                    *q = '>';
                    strcpy( q + 1, q + 4 );
                }
                while ( ( q = strstr( p, "&quot;" ) ) != NULL ) {
                    *q = '"';
                    strcpy( q + 1, q + 6 );
                }
                while ( ( q = strstr( p, "&amp;" ) ) != NULL )
                    strcpy( q + 1, q + 5 );

                while ( ( q = strstr( p, "&#" ) ) != NULL ) {
                    char    *r;
                    long    l;

                    q += 2;
                    r = strchr( q, ';' );
                    if ( !r ) {
                        r = strstr( q, "&#" );
                        if ( !r )
                            break;
                        p = r;
                        continue;
                    }

                    l = atol( q );
                    if ( (l >= ' ') && (l < 0x80) ) {
                        q -= 2;
                        *q = (char)l;
                        strcpy( q + 1, r + 1 );
                        p = q + 1;
                    }
                    else
                        p = r + 1;
                }

                if (!strcmp(title2, sjis2utf("���݃����e�i���X���ł��B") ) ||
                    !strcmp(title2, sjis2utf("Service Not Available")    )   )
                    title2[0] = NUL;
            }

#ifdef  OLDFASHIONED
            p = strstr( response, "<dd class=\"list-cloud\">" );
            if ( !p )
                p = strstr( response, "<dd class=\"list-cloud\" " );
#else
            p = strstr( response, "<div id=\"entryinfo\">" );
#endif
            if ( p ) {
#ifdef  OLDFASHIONED
                p += 23;
                q = strstr( p, "</dd>" );
#else
                p += 20;
                q = strstr( p, "<!-- entryinfo -->" );
#endif
                if ( q ) {
                    char    *r = strstr( p, "<a href=\"/t/" );
                    if ( r && (r < q) ) {
                        // �͂Ăȃu�b�N�}�[�N����^�O�����擾
                        *hatenaTags = (char *)malloc( MAX_CONTENT_SIZE );
                        if ( *hatenaTags ) {
                            char    *s = *hatenaTags;
#ifdef  OLDFASHIONED
                            char    *t;
#endif
                            do {
                                p = r;
                                r = strstr( p, "<a " );
                                if ( r && (r < q) )
                                    p = r + 3;
                                else
                                    break;
                                r = strstr( p, "tag\">" );
                                if ( r && (r < q) ) {
                                    r += 5;
                                    p = strstr( r, "</a>" );
                                    if ( !p )
                                        break;
#ifdef  OLDFASHIONED
                                    t = strstr( r, "<span class=\"tagcount\">" );
                                    if ( t && (t < p) )
                                        p = t;
#endif
                                    while ( r < p )
                                        *s++ = *r++;
                                    *s++ = ' ';
                                }
                            } while ( r && (r < q) );
                            *s = NUL;
                            if ( s > *hatenaTags )
                                *(s - 1) = NUL;
                        }
                    }
                }
            }

            p = strstr( response, "<ul id=\"bookmarked_user\"" );
            if ( p ) {
                if ( hatenaID && *hatenaID ) {
                    char    target[MAX_NAMELEN + 16 + 1];

                    sprintf( target, "<a href=\"/%s/", hatenaID );
                    if ( strstr( response, target ) )
                        *posted = TRUE;
                }
            }

            if ( title2[0] )
                useHatenaBookmark = TRUE;
        }
    }

    setUpReceiveBuffer( response, sz );
    http_get( url, response );

    if ( response && response[0] ) {
        p = strstr( response, "<title>" );
        if ( !p )
            p = strstr( response, "<title " );
        if ( !p )
            p = strstr( response, "<TITLE>" );
        if ( !p )
            p = strstr( response, "<TITLE " );
        if ( !p )
            p = strstr( response, "<h1>" );
        if ( !p )
            p = strstr( response, "<h1 " );
        if ( !p )
            p = strstr( response, "<H1>" );
        if ( !p )
            p = strstr( response, "<H1 " );
        if ( p ) {
            p++;
            p = strchr( p, '>' );
            p++;
            q = strstr( p + 1, "</" );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;

                while ( ( ( p = strchr( title, '\r' ) ) != NULL ) ||
                        ( ( p = strchr( title, '\n' ) ) != NULL )    )
                    strcpy( p, p + 1 );
            }
        }

        if ( title2[0] != NUL )
            strcpy( title, title2 );

        /* asahi.com �΍� #1 */
        while ( ( p = strstr( title, "&#160;" ) ) != NULL ) {
            *p++ = ' ';
            strcpy( p, p + 5 );
        }

        /* asahi.com �΍� #2 */
        if ( ( p = strstr( title, "\xEF\xBF\xBD-\xEF\xBF\xBD" ) ) != NULL ) {
            strcpy( p, " - " );
            strcpy( p + 3, p + 7 );
        }

        if ( accountName ) {
            p = strstr( response, "<foaf:holdsAccount>" );
            if ( p ) {
                char    *r, *s;

                p += 19;
                q = strstr( p, "<foaf:OnlineAccount foaf:accountName=\"" );
                r = strstr( p, "<foaf:accountServiceHomepage rdf:resource="
                               "\"http://www.hatena.ne.jp/\" />" );
                s = strstr( p, "</foaf:OnlineAccount>" );
                if ( q && r && s && (q < r) && (r < s) ) {
                    // ���Y�A�J�E���g���u�͂Ăȓ����K�Ή��A�J�E���g�v�ł����
                    q += 38;
                    r = strchr( q, '"' );
                    strncpy( accountName, q, r - q );
                    accountName[r - q] = NUL;
                }
            }
        }
    }

    if ( !(title[0]) && title2[0] )
        strcpy( title, title2 );

    if ( strstr( response, "charset=UTF-8" ) ||
         strstr( response, "charset=utf-8" ) ||
         useHatenaBookmark                      )
        p = utf2sjisEx( title );
    else if ( strstr( response, "charset=Shift_JIS" ) ||
              strstr( response, "charset=shift_jis" )    )
        p = title;
    else
        p = utf2sjis( title );
    if ( p ) {
        if ( p != title )
            strcpy( title, p );
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) ) {
            q = jis2sjis( title );
            if ( q )
                strcpy( title, q );
        }
    }
    else {
        q = NULL;
        if ( strstr( response, "charset=iso-8859-1" ) ||
             strstr( response, "charset=ISO-8859-1" )    ) {
            for ( p = title; *p; p++ ) {
                if ( (unsigned char)(*p & 0xFF) >= 0xA0 ) {
                    q = iso8859_1toUtf8( title );
                    if ( q )
                        p = decodeURL( q ); // utf8 �� us-ascii �ϊ������˂�
                    break;
                }
            }
        }

        if ( !q )
            p = euc2sjis( title );
        if ( p )
            strcpy( title, p );
    }
    free( response );

    p = title;
    while ( *p ) {
        if ( (*p == '\t') || (*p == '\r') || (*p == '\n' ) )
            *p = ' ';
        p++;
    }

    p = title;
    while ( *p ) {
        while ( (*p == ' ') && (*(p + 1) == ' ') )
            strcpy( p, p + 1);
        p++;
    }

    p = title;
    while ( *p == ' ' )
        strcpy( p, p + 1);

    if ( *p ) {
        p = &(title[strlen(title) - 1]);
        while ( *p == ' ' )
            *p-- = NUL;
    }
    while ( ( p = strstr( title, "&raquo;" ) ) != NULL ) {
        strncpy( p, "��", 2 );
        strcpy( p + 2, p + 7 );
    }
    while ( ( p = strstr( title, "&laquo;" ) ) != NULL ) {
        strncpy( p, "��", 2 );
        strcpy( p + 2, p + 7 );
    }

    return ( title );
}

/*
 *  �w�� Web �y�[�W�̃^�O���𒊏o����
 *      written by H.Tsujimura  30 Nov 2005
 *
 * $Log: /comm/bookey/extractTags.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 30    09/03/30 16:48 Tsujimura543
 * getTagsFromYahooAPI() �� request �̊m�ۃT�C�Y�v�Z�����C��
 * 
 * 29    09/02/24 16:25 Tsujimura543
 * Yahoo! Japan �́u�`�ԑf���API�v�𗘗p�����p�o�ꒊ�o�����������B
 * (�^�O���̑I��ɓ������Ďg��������1�Ƃ��Ēǉ�)
 * 
 * 28    08/11/17 14:48 Tsujimura543
 * USE_BULKFEEDS_API �� define �ς݂̏ꍇ�̂݁Abulkfeeds API ��
 * �g���悤�ɕύX
 * 
 * 27    08/05/21 17:40 Tsujimura543
 * �b��I�ɁAchangeHatenaKeyword() ���ĂԂ̂���߂�
 * 
 * 26    08/05/20 22:56 Tsujimura543
 * getHatenaKeywordLink(), getTagsFromKoshian() �̓����ŌĂ�ł���
 * decodeURL() / encodeURL() ���ŗ����邱�Ƃ����錻��(���܂̂Ƃ���A
 * �����s��)�ւ̑΍�����{
 * 
 * 25    07/09/05 1:49 Tsujimura543
 * extractTags() �ɑ�2������ǉ�(stat1470net��������)
 * 
 * 24    07/06/26 13:30 Tsujimura543
 * �͂Ăȃ_�C�A���[�L�[���[�hAPI����~���̂Ƃ���
 * getHatenaKeywordLink() ���ŗ����邱�Ƃ�����s��ɑΏ�
 * 
 * 23    07/04/25 10:23 Tsujimura543
 * 1470.net �̃^�O��⒊�oAPI�� Not Found ��Ԃ��ꍇ�ɑΏ�
 * 
 * 22    07/03/05 17:16 Tsujimura543
 * setKeywordLink() �Ɉ�����ǉ������̂ɔ����C�������{
 * 
 * 21    07/03/01 21:42 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 20    07/03/01 19:08 Tsujimura543
 * �o�^�Ώۂ�URL�������Ƃ��AgetTagsFrom1470net() ���Ń������j�󂪋N����
 * �s��ɑΏ�
 * 
 * 19    07/02/27 23:05 Tsujimura543
 * ����Ƀ��t�@�N�^�����O
 * 
 * 18    07/02/27 22:57 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 17    07/02/27 22:32 Tsujimura543
 * �͂Ăȃ_�C�A���[�L�[���[�h���������NAPI�𗘗p����������̔���������
 * ����Ă݂�
 * 
 * 16    07/02/27 0:04 Tsujimura543
 * 1470.net �̃^�O���擾API���g���Ȃ��ꍇ�́AKOSHIAN���g���悤�ɂ��Ă݂�
 * (�b�����)
 * 
 * 15    06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 14    06/06/29 10:39 Tsujimura543
 * Bulkfeeds API �Ŏ擾�����^�O���Ɋւ��āA�󕶎��̃^�O��₪�������Ȃ�
 * �悤�ɏC������
 * 
 * 13    06/06/29 10:25 Tsujimura543
 * (1) �^�O���̍ŏ���1�ڂ��󕶎���ɂȂ邱�Ƃ����錻�ۂɑΏ�
 * (2) �͂ău�̃^�O�N���E�h����擾�����^�O��₪�����̃^�O���Əd������
 *     ���Ȃ����ǂ����`�F�b�N����悤�ɂ���
 * 
 * 12    06/06/20 16:29 Tsujimura543
 * isWhiteSpace() �� myClip.h �ֈړ�
 * 
 * 11    06/06/20 16:25 Tsujimura543
 * iskanji1(), iskanji2() �� myClip.h �ֈړ�
 * 
 * 10    06/05/23 16:31 Tsujimura543
 * extractTags() ���C��(�͂Ăȃu�b�N�}�[�N����̃^�O�擾�������C���A
 * 1470.net API �Ŏ擾�����^�O�Ƃ̏d���`�F�b�N��ǉ�)
 * 
 * 9     06/05/23 13:56 Tsujimura543
 * getTitle() �� extractTags() �̘A�g�ɂ��u�͂Ăȃu�b�N�}�[�N�v�����
 * �^�O���擾���T�|�[�g
 * 
 * 8     06/03/13 20:58 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 7     06/03/13 20:55 Tsujimura543
 * 1470.net �� API ����~���Ă���Ƃ��A�ŏ��̃^�O��₪�����Ȃ����̓��L��
 * URL �ɂȂ��Ă��܂����ۂɑΏ�
 * 
 * 6     06/02/09 23:41 Tsujimura543
 * �^�O���oAPI���Ăяo���O�����������
 * 
 * 5     06/02/09 17:30 Tsujimura543
 * (1) 1470.net API �Ŏ擾�����^�O��₪ 20�ɖ����Ȃ��Ƃ��� Bulkfeeds
 *     API �𕹗p����悤�ɂ���
 * (2) �����񒷂�2�o�C�g�ȉ��̃^�O���͎̂Ă�悤�ɂ���
 * 
 * 4     05/12/07 19:21 Tsujimura543
 * normalizeTag() ���C�� (�����锼�p�����݂̂ō\������镶����̂Ƃ��A
 * 20�o�C�g�ł͂Ȃ�21�o�C�g�Ɋۂ߂Ă���)
 * 
 * 3     05/12/01 15:41 Tsujimura543
 * (1) �^�O��₪20�o�C�g���傫���ꍇ��20�o�C�g�ȓ��Ɏ��߂�悤�ɂ���
 * (2) euc2sjis ���s���̃��J�o����������ꂽ
 * 
 * 2     05/11/30 23:43 Tsujimura543
 * extractTags() �̑�3������ (I) ���� (I/O) �֕ύX
 * 
 * 1     05/11/30 23:24 Tsujimura543
 * �ŏ��̔�
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/extractTags.c 1     09/05/14 3:48 tsupo $";
#endif

static void
normalizeTag( char *tag )
{
    if ( strlen( tag ) > 20 ) {
        char    *s = tag;
        BOOL    kanjiFlag = FALSE;
        int     i = 0;

        while ( *s ) {
            if ( ++i > 20 )
                break;
            if ( !kanjiFlag && iskanji1( *s ) )
                kanjiFlag = TRUE;
            else
                kanjiFlag = FALSE;
            *s++;
        }
        if ( kanjiFlag )
            *(s - 1) = NUL;
        else
            *s = NUL;
    }
}

static char *
stripTags( char *p )
{
    char    *q = (char *)malloc( strlen( p ) + 1 );
    char    *r, *s;

    r = p;
    if ( q && r ) {
        s = q;
        while ( *r ) {
            if ( *r == '<' ) {
                if ( !strncmp( r + 1, "!--", 3 ) ) {
                    char    *t;
                    t = strstr( r + 4, "-->" );
                    if ( t ) {
                        if ( !isWhiteSpace(*(s - 1)) )
                            *s++ = ' ';
                        r = t + 3;
                    }
                    else
                        r += 4;
                }
                else if ( !strncmp( r + 1, "script", 6 ) ) {
                    char    *t;
                    t = strstr( r + 7, "</script>" );
                    if ( t ) {
                        if ( !isWhiteSpace(*(s - 1)) )
                            *s++ = ' ';
                        r = t + 9;
                    }
                    else
                        r += 7;
                }
                else {
                    while ( *r && (*r != '>') )
                        r++;
                    if ( *r == '>' ) {
                        if ( !isWhiteSpace(*(s - 1)) )
                            *s++ = ' ';
                        r++;
                    }
                }
                continue;
            }

            if ( !strncmp( r, "&amp;", 5 ) ) {
                r += 5;
                *s++ = '&';
                continue;
            }
            if ( !strncmp( r, "&lt;", 4 ) ) {
                r += 4;
                *s++ = '<';
                continue;
            }
            if ( !strncmp( r, "&gt;", 4 ) ) {
                r += 4;
                *s++ = '>';
                continue;
            }
            if ( !strncmp( r, "&nbsp;", 6 ) ) {
                r += 6;
                *s++ = ' ';
                continue;
            }
            if ( !strncmp( r, "&quot;", 6 ) ) {
                r += 6;
                *s++ = '"';
                continue;
            }

            while ( isWhiteSpace(*r) && isWhiteSpace(*(r + 1)) )
                r++;

            if ( !(isWhiteSpace(*(s - 1)) && isWhiteSpace(*r)) )
                *s++ = *r;
            r++;
        }
        *s = NUL;

        strcpy( p, q );
        free( q );
    }

    return ( p );
}

void
getTagsFromHatenaBookmark(
        char       **tags,      /* (O)   �^�O���                         */
        char       **hatenaTags,/* (I/O) �͂ău����擾�����^�O���       */
        int        *curNum,     /* (I/O) �擾�ς݂̃^�O���̐�           */
        int        numOfTags    /* (I)   �擾���悤�Ƃ��Ă���^�O���̐� */
    )
{
    char    *p, *q;
    int     num = *curNum;

    p = utf2sjisEx( (char *)(*hatenaTags) );
    if ( p ) {
        while ( *p ) {
            q = tags[num];
            while ( *p && (*p != ' ') )
                *q++ = *p++;
            *q = NUL;
            normalizeTag( tags[num] );
            if ( (tags[num][0] != NUL) && (tags[num][0] != '&') ) {
                // �d���`�F�b�N
                int i;

                for ( i = 0; i < num; i++ )
                    if ( !strcmp( tags[i], tags[num] ) )
                        break;

                if ( i == num ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }
            }
            while ( *p == ' ' )
                p++;
        }
    }

    *curNum = num;
}

void
getTagsFromYahooAPI(
        const char *body,       /* (I)   ��͑Ώ�                         */
        char       **tags,      /* (O)   �^�O���                         */
        int        *curNum,     /* (I/O) ���܂łɎ擾�ς݂̃^�O���̐�   */
        int        numOfTags,   /* (I)   �擾���悤�Ƃ��Ă���^�O���̐� */
        const char *yahooAppID  /* (I)   Yahoo! Japan �A�v���P�[�V����ID  */
    )
{
    char        *request;
    char        *response;
    size_t      sz  = strlen(encodeURL(body)) + MAX_CONTENT_SIZE;
    size_t      sz2 = MAX_CONTENT_SIZE * 16;

    request = (char *)malloc( sz );
    if ( !request )
        return;
    response = (char *)malloc( sz2 );
    if ( !response ) {
        free( request );
        return;
    }

    sprintf( request,
             "appid=%s&"
             "sentence=%s&"
             "results=uniq&"
             "response=surface&"        // �\�L
             "filter=1|2|9|10&"         // �`�e��, �`�e����, ����, ����
             "uniq_by_baseform=true",
             yahooAppID,
             encodeURL( body ) );
    setUpReceiveBuffer( response, sz2 );
    http_post( "http://jlp.yahooapis.jp/MAService/V1/parse",
               "application/x-www-form-urlencoded", request, response );
    if ( *response &&
         strstr( response, "<word>"  ) &&
         strstr( response, "<count>" )    ) {
        // �u�o�����v�̑������̂��珇�Ƀ^�O���ɂ���
        BOOL    found;
        char    *p, *q;
        int     i;
        int     num = *curNum;

        p = any2sjis( response );
        p = strstr( p ? p : response, "<surface>" );
        while ( p ) {
            p += 9;
            q = strstr( p, "</surface>" );
            if ( !q )
                break;

            strncpy( tags[num], p, q - p );
            tags[num][q - p] = NUL;
            normalizeTag( tags[num] );
            found = FALSE;
            for ( i = 0; i < num; i++ ) {
                if ( !strcmp( tags[i], tags[num] ) ) {
                    found = TRUE;
                    break;
                }
            }

            if ( found == FALSE ) {
                num++;
                if ( num >= numOfTags )
                    break;
            }

            q += 4;
            p = strstr( q, "<surface>" );
        }

        *curNum = num;
    }

    free( response );
    free( request );
}

void
getHatenaKeywordLink(
        const char *body,       /* (I)   ��͑Ώ�                         */
        char       **tags,      /* (O)   �^�O���                         */
        int        *curNum,     /* (I/O) ���܂łɎ擾�ς݂̃^�O���̐�   */
        int        numOfTags,   /* (I)   �擾���悤�Ƃ��Ă���^�O���̐� */
        BOOL       striped      /* (I)   ���ł� stripTags �ς݂��ۂ�      */
    )
{
    /* �L�[���[�h�����N���ߍ��� */
    char    *p, *result;
    size_t  sz = ((body && *body) ? strlen( body )
                                  : MAX_CONTENT_SIZE) * 32;
    result = (char *)malloc( sz );
    if ( result ) {
        const char  *q = body;
        if ( !striped ) {
            p = any2utf( body );
            q = stripTags( p ? p : body );
        }

        memset( result, 0x00, sz );
        p = setKeywordLink( q,
                            result, sz, 0, CNAME_GENERAL,
                            "_blank", "hatena" );
        if ( p && *p && strcmp( p, "(null)" ) ) {
            if ( !strncmp( p, ";lt=;lt=", 8 ) ) {
                /* �����������o */
                free( result );
                return;
            }
            else
                utf2sjisEx( p );
        }
        else {
#if 0
            /* �͂Ăȃ_�C�A���[�L�[���[�h���������NAPI�� */
            /* �@�\���Ă��Ȃ��ꍇ                        */
            char    *q;
            size_t  len = 0;

            memset( result, 0x00, sz );
            p = changeHatenaKeyword( body, result, MODE_HTML );
            q = euc2sjis( p );
            if ( !q )
                q = any2sjis( p );
            if ( q && *q )
                len = strlen( q );
            if ( len >= sz - 1 ) {
                strncpy( result, q, sz - 1 );
                result[sz - 1] = NUL;
            }
            else if ( len > 0 )
                strcpy( result, q );
#else
            /* http://d.hatena.ne.jp/images/keyword/keywordlist �̃t�H�[  */
            /* �}�b�g���ύX����Ă��邽�߁AchangeHatenaKeyword() �����܂� */
            /* �@�\���Ȃ��Ȃ��Ă��� (�ύX�����s��)                        */
            *result = NUL;  /* �b��Ώ� */
#endif
        }

        if ( *result ) {
            /* �L�[���[�h�𔲂��o�� */
            BOOL    found;
            char    *q;
            int     i;
            int     num = *curNum;

            p = any2sjis( result );

            p = strstr( p ? p : result, "<a class=\"hatena\" " );
            while ( p ) {
                p += 18;
                q = strchr( p, '>' );
                if ( !q )
                    break;
                p = q + 1;
                q = strstr( p, "</a>" );
                if ( !q )
                    break;

                strncpy( tags[num], p, q - p );
                tags[num][q - p] = NUL;
                normalizeTag( tags[num] );
                found = FALSE;
                for ( i = 0; i < num; i++ ) {
                    if ( !strcmp( tags[i], tags[num] ) ) {
                        found = TRUE;
                        break;
                    }
                }

                if ( found == FALSE ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }

                q += 4;
                p = strstr( q, "<a class=\"hatena\" " );
            }

            *curNum = num;
        }

        free( result );
    }
}

BOOL
getTagsFrom1470net(
        const char *url,        /* (I)   ���YWeb�y�[�W��URL               */
        char       **tags,      /* (O)   �^�O���                         */
        char       **hatenaTags,/* (I/O) �͂ău����擾�����^�O���       */
        int        *curNum,     /* (I/O) ���܂łɎ擾�ς݂̃^�O���̐�   */
        int        numOfTags,   /* (I)   �擾���悤�Ƃ��Ă���^�O���̐� */
        char       *response,   /* (O)   ��M�o�b�t�@                     */
        size_t     sz           /* (I)   ��M�o�b�t�@�̃T�C�Y             */
    )
{
    BOOL    stat1470net = TRUE;
    BOOL    recover = FALSE;
    char    *p, *q;
    char    *targetURL;
    int     num = *curNum;

    p = encodeURL( url );
    targetURL = (char *)malloc( strlen( p ) + 128 );
    if ( !targetURL )
        return ( stat1470net );

    // http://1470.net/api/mmutil.php?cmd=getwords;url=[URL] �� GET
    sprintf( targetURL,
             "http://1470.net/api/mmutil.php?cmd=getwords&url=%s",
             p );
    setUpReceiveBuffer( response, sz );
    http_get( targetURL, response );

    if ( response[0]                               &&
         (strncmp( response, "<a ", 3 ) != 0)      &&
         !strstr( response, "<li>Not Found</li>" )    ) {
        /* ����: http://1470.net/api/mmutil.php ���T�[�r�X��~���̏ꍇ�� */
        /*       <a href="http://tdiary.ishinao.net/">blog</a>. �̂悤�� */
        /*       ���e�� response ���Ԃ��Ă���                            */
        /*   --- 2007�N4��25�����݁A<li>Not Found</li>  ���܂މ������Ԃ� */
        /*       �Ă��� (�T�[�r�X��~��?)                                */
        p = euc2sjis( response );
        if ( !p ) {
            p = response;
            recover = TRUE;
        }
        while ( *p ) {
            q = tags[num];
            while ( *p && (*p != '\t') && (*p != '\r') && (*p != '\n') )
                *q++ = *p++;
            *q = NUL;

            if ( recover ) {
                q = euc2sjis( tags[num] );
                if ( q )
                    strcpy( tags[num], q );
                else
                    goto next;
            }
            normalizeTag( tags[num] );
            if ( strlen( tags[num] ) <= 2 )
                goto next;

            if ( hatenaTags && *hatenaTags ) {
                // �d���`�F�b�N
                int i;
                for ( i = 0; i < num; i++ ) {
                    if ( !strcmp( tags[i], tags[num] ) )
                        goto next;
                }
            }

            num++;
            if ( num >= numOfTags )
                break;

            if ( (*p == '\t') || (*p == '\r') || (*p == '\n') ) {
              next:
                while ( *p && ((*p == '\t') || (*p == '\r') || (*p == '\n')) )
                    p++;
                if ( *p )
                    continue;
            }
            break;
        }

        *curNum = num;
    }
    else
        stat1470net = FALSE;

    free( targetURL );

    return ( stat1470net );
}

BOOL
getTagsFromKoshian(
        char   **tags,      /* (O)   �^�O���                         */
        int    *curNum,     /* (I/O) ���܂łɎ擾�ς݂̃^�O���̐�   */
        int    numOfTags,   /* (I)   �擾���悤�Ƃ��Ă���^�O���̐� */
        char   *response,   /* (O)   ��M�o�b�t�@                     */
        char   *response2,  /* (O)   ��M�o�b�t�@                     */
        size_t sz,          /* (I)   ��M�o�b�t�@�̃T�C�Y             */
        BOOL   striped      /* (I)   ���ł� stripTags �ς݂��ۂ�      */
    )
{
    static int  statZuzara  = TRUE;
    int         num = *curNum;
    char        *p, *q;
    char        targetURL[MAX_URLLENGTH];
    char        *request;
    size_t      sz2 = sz * 16;

    /* 
     * ���͂���L�[���[�h�𔲂��o��API: KOSHIAN
     *     (�ڍ�: http://blog.zuzara.com/2006/12/10/171/)
     * ���g���āA������(�ő�20��)�𒊏o����
     */
    request = (char *)malloc( sz2 );
    if ( request ) {
        if ( !striped ) {
            p = any2utf( response2 );
            q = stripTags(p ? p : response2);
            if ( strlen( q ) >= sz2 - 3 )
                q[sz2 - 3] = NUL;
        }
        else
            q = response2;
        sprintf( request, "q=%s", encodeURL( q ) );
        setUpReceiveBuffer( response, sz );
        strcpy( targetURL, "http://zuzara.dyndns.org/api/koshian" );
        http_post( targetURL,
                   "application/x-www-form-urlencoded",
                   request, response );
        if ( *response ) {
            BOOL    found;
            int     i;

            p = strstr( utf2sjisEx(response), "<Result " );
            while ( p ) {
                p += 8;
                q = strchr( p, '>' );
                if ( !q )
                    break;
                p = q + 1;
                q = strstr( p, "</Result>" );
                if ( !q )
                    break;

                strncpy( tags[num], p, q - p );
                tags[num][q - p] = NUL;
                normalizeTag( tags[num] );
                found = FALSE;
                for ( i = 0; i < num; i++ ) {
                    if ( !strcmp( tags[i], tags[num] ) ) {
                        found = TRUE;
                        break;
                    }
                }

                if ( found == FALSE ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }

                q += 9;
                p = strstr( q, "<Result " );
            }
        }
        else
            statZuzara = FALSE;

        free( request );
    }

    return ( statZuzara );
}

#ifdef  USE_BULKFEEDS_API
void
getTagsFromBulkfeeds(
        char       *response,   /* (I)   ��M�o�b�t�@                     */
        char       **tags,      /* (O)   �^�O���                         */
        int        *curNum,     /* (I/O) ���܂łɎ擾�ς݂̃^�O���̐�   */
        int        numOfTags,   /* (I)   �擾���悤�Ƃ��Ă���^�O���̐� */
        BOOL       striped      /* (I)   ���ł� stripTags �ς݂��ۂ�      */
    )
{
    BF_TERM bt[20];
    int     numOfTerms = 20;
    int     num = *curNum;
    int     ret;

    ret = extractAnalyseOnBulkfeeds( response, NULL, &numOfTerms, bt );
    if ( ret > 0 ) {
        char    *p;
        int     preNum = num;
        int     i, j;
        BOOL    found;

        for ( i = 0; i < ret; i++ ) {
            p = utf2sjis( bt[i].term );
            if ( p ) {
                if ( (strlen( p ) <= 2) || strchr( p, '&' ) )
                    continue;
                found = FALSE;
                for ( j = 0; j < preNum; j++ ) {
                    if ( !strcmp( tags[j], p ) ) {
                        found = TRUE;
                        break;
                    }
                }
                if ( found )
                    continue;
                strcpy( tags[num], p );
                normalizeTag( tags[num] );
                if ( tags[num][0] ) {
                    num++;
                    if ( num >= numOfTags )
                        break;
                }
            }
        }
    }
}
#endif  /* USE_BULKFEEDS_API */

void
extractTags(
        const char *url,        /* (I)   ���YWeb�y�[�W��URL         */
        char       **tags,      /* (O)   �^�O���                   */
        char       **hatenaTags,/* (I/O) �͂ău����擾�����^�O��� */
        int        *numOfTags,  /* (I/O) �^�O���̐�               */
        BOOL       *stat1470net,/* (I/O) 1470.net �̉ғ���        */
        const char *yahooAppID  /* (I)   Yahoo! �A�v���P�[�V����ID  */
    )
{
    char        *response;
    int         num = 0;
 // size_t      sz = MAX_CONTENT_SIZE * 20;
    size_t      sz = MAX_CONTENT_SIZE * 2;
    static int  statZuzara  = TRUE;

    /* ���YWeb�y�[�W�̂͂Ăȃu�b�N�}�[�N�y�[�W����^�O���擾 */
    if ( hatenaTags && *hatenaTags ) {
        getTagsFromHatenaBookmark( tags, hatenaTags, &num, *numOfTags );
        if ( num >= *numOfTags ) {
            *numOfTags = num;
            return;
        }
    }

    response = (char *)malloc( sz );
    if ( !response )
        return;

    /* 1470.net �́u�^�O��⒊�oAPI�v���g���ă^�O�����擾 */
    if ( *stat1470net )
        *stat1470net = getTagsFrom1470net( url, tags, hatenaTags,
                                           &num, *numOfTags, response, sz );

    if ( num < *numOfTags ) {
        char    *response2;

        response2 = (char *)malloc( sz );
        if ( response2 ) {
            // ��͑Ώۃy�[�W(�u�b�N�}�[�N���悤�Ƃ��Ă���y�[�W)���擾
            setUpReceiveBuffer( response2, sz );
            http_get( url, response2 );

            /* �e�� API �𗘗p���āA������𒊏o */
            if ( *response2 ) {
                size_t  sz2  = strlen(response2) * 16;
                char    *buf = (char *)malloc( sz2 );
                if ( buf ) {
                    char    *p = any2utf( response2 );
                    char    *q = stripTags(p ? p : response2);
                    if ( strlen( q ) >= sz2 - 3 )
                        q[sz2 - 3] = NUL;
                    strcpy( buf, q );
                }

                /* Yahoo! Japan �`�ԑf��� API �𗘗p���āA������𒊏o */
                if ( buf )
                    getTagsFromYahooAPI( buf,
                                         tags, &num, *numOfTags, yahooAppID );

                /* �͂Ăȃ_�C�A���[�L�[���[�h�����NAPI */
                if ( num < *numOfTags )
                    getHatenaKeywordLink( buf ? buf : response2,
                                          tags, &num, *numOfTags,
                                          buf ? TRUE : FALSE );


                /* KOSHIAN */
                if ( statZuzara && (num < *numOfTags) )
                    statZuzara = getTagsFromKoshian( tags, &num, *numOfTags,
                                                     response,
                                                     buf ? buf : response2,
                                                     sz,
                                                     buf ? TRUE : FALSE );
#ifdef  USE_BULKFEEDS_API
                /* Bulkfeeds API �́u�`�ԑf���+�����ꒊ�o�v */
                if ( num < *numOfTags )
                    getTagsFromBulkfeeds( buf ? buf : response2,
                                          tags, &num, *numOfTags,
                                          buf ? TRUE : FALSE );
#endif  /* USE_BULKFEEDS_API */

                if ( buf )
                    free( buf );
            }

            free( response2 );
        }
    }

    *numOfTags = num;

    free( response );
}


/*
 *  myClip.c
 *      MyClip �\���̊֘A�֐��Q
 *          written by H.Tsujimura  22 Sep 2006
 *
 * $Log: /comm/bookey/myClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 22    08/12/02 19:35 Tsujimura543
 * null�|�C���^�Q�Ƃ���������\���̂���ӏ��̑Ώ�
 * 
 * 21    08/02/14 19:41 Tsujimura543
 * replaceString() �� getFlog.c ����� putTumblr.c ����ړ�
 * 
 * 20    07/11/12 21:56 Tsujimura543
 * adjustStringLength() �� putLocalOpml.c, putMMmemo.c ����ڊ�
 * 
 * 19    07/11/12 19:03 Tsujimura543
 * any2sjisEx() ��ǉ�
 * 
 * 18    07/04/20 20:29 Tsujimura543
 * getYJbookmark.c ���� compareMyClip() ���ڊ�
 * 
 * 17    07/02/22 18:33 Tsujimura543
 * any2sjis() ��ǉ�
 * 
 * 16    07/01/19 15:37 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 15    07/01/17 17:33 Tsujimura543
 * �uVox �΍�v�̓���m�F����
 * 
 * 14    07/01/17 17:32 Tsujimura543
 * Vox �΍� (&ccedil; �� %C3%A7 �ő����Ă��邽�߁Aiconv ���R�[�h�ϊ��Ɏ��s
 * ����) �Ƃ��āA�������� utf2sjisEx() ���Ă��� sjis2utf() ���邱�Ƃŏ���
 * ���s�\�Ȃ悤�ɂ���
 * 
 * 13    06/12/25 19:24 Tsujimura543
 * any2euc() ���C���AcharSet �딻��̊m�������炷
 * 
 * 12    06/12/25 15:09 Tsujimura543
 * any2euc() ��ǉ�
 * 
 * 11    06/12/08 15:57 Tsujimura543
 * getDateTimeFromDateString() ��ύX�B���[�J�����Ԃŕێ�����悤�ɂ���
 * 
 * 10    06/12/07 16:45 Tsujimura543
 * getDateTimeFromDateString() �́u_timezone ���Q�Ƃ��Ď�����␳����
 * �ꍇ�̏����v���C��
 * 
 * 9     06/12/07 15:57 Tsujimura543
 * getDateTimeFromDateString() �� inputLivedoorFeed.c ����
 * myClip.c �ֈڂ�
 * 
 * 8     06/12/07 14:21 Tsujimura543
 * �R�����g���C�� (typo)
 * 
 * 7     06/12/07 14:20 Tsujimura543
 * allocateMyClipIfNecessary() ���Őݒ肷�� publication �̏����l��
 * �u�S�̂Ɍ��J�v�Ƃ���
 * 
 * 6     06/11/14 15:54 Tsujimura543
 * chcode() �̎��̂� myClip.c �ֈړ�
 * 
 * 5     06/11/14 15:47 Tsujimura543
 * any2utf() �̎��̂� myClip.c �ֈړ�
 * 
 * 4     06/11/14 15:45 Tsujimura543
 * unescapeURL() �̎��̂� myClip.c �ֈړ�
 * 
 * 3     06/11/10 20:07 Tsujimura543
 * strncmpi() �̎��̂� myClip.c �Ɉړ�
 * 
 * 2     06/09/22 21:40 Tsujimura543
 * allocateMyClipExIfNecessary() ��ǉ�
 * 
 * 1     06/09/22 20:49 Tsujimura543
 * �V�K�쐬 (MyClip �\���̊i�[�̈���m�ۂ��鏈�������ʊ֐������Ă݂�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/myClip.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
allocateMyClipIfNecessary(
        MyClip **mp,        /* (I/O) �m�ۂ���/�m�ۍς݃������̈�     */
        int    unit,        /* (I)   1��ӂ�̃������̈抄�蓖�ĒP�� */
        int    *cnt,        /* (I/O) ���������蓖�Ď��s��          */
        int    numOfClips   /* (I)   �i�[�ς݃u�b�N�}�[�N��          */
    )
{
    MyClip  *pp;

    if ( !(*mp) ) {
        *cnt = 1;
        *mp = (MyClip *)malloc( sizeof ( MyClip ) * unit * *cnt );
        if ( !(*mp) )
            return ( NULL );
    }
    else if ( numOfClips >= unit * *cnt ) {
        MyClip  *newMp;

        (*cnt)++;
        newMp = (MyClip *)realloc( *mp, sizeof ( MyClip ) * unit * *cnt );
        if ( !newMp )
            return ( NULL );
        *mp = newMp;
    }

    pp = &((*mp)[numOfClips]);
    pp->url[0]      = NUL;
    pp->title[0]    = NUL;
    pp->comment[0]  = NUL;
    pp->tags[0]     = NUL;
    pp->yyyy        = -1;
    pp->mm          = 0;
    pp->dd          = 0;
    pp->HH          = 0;
    pp->MM          = 0;
    pp->SS          = 0;
    pp->asin        = FALSE;
    pp->publication = PUB_EVERYONE; /* default �́u�S�̂Ɍ��J�v */

    return ( *mp );
}


MyClipEx    *
allocateMyClipExIfNecessary(
        MyClipEx **mp,      /* (I/O) �m�ۂ���/�m�ۍς݃������̈�     */
        int      unit,      /* (I)   1��ӂ�̃������̈抄�蓖�ĒP�� */
        int      *cnt,      /* (I/O) ���������蓖�Ď��s��          */
        int      numOfClips /* (I)   �i�[�ς݃u�b�N�}�[�N��          */
    )
{
    MyClipEx    *pp;

    if ( !(*mp) ) {
        *cnt = 1;
        *mp = (MyClipEx *)malloc( sizeof ( MyClipEx ) * unit * *cnt );
        if ( !(*mp) )
            return ( NULL );
    }
    else if ( numOfClips >= unit * *cnt ) {
        MyClipEx    *newMp;

        (*cnt)++;
        newMp = (MyClipEx *)realloc( *mp, sizeof ( MyClipEx ) * unit * *cnt );
        if ( !newMp )
            return ( NULL );
        *mp = newMp;
    }

    pp = &((*mp)[numOfClips]);
    pp->url[0]     = NUL;
    pp->title[0]   = NUL;
    pp->comment[0] = NUL;
    pp->tags[0]    = NUL;
    pp->entryID[0] = NUL;
    pp->remarks[0] = NUL;

    return ( *mp );
}

int
compareMyClip( const void *elem1, const void *elem2 )
{
    MyClip *w1 = (MyClip *)elem1;
    MyClip *w2 = (MyClip *)elem2;

    if ( w1->yyyy != w2->yyyy )
        return ( w1->yyyy - w2->yyyy );
    if ( w1->mm != w2->mm )
        return ( w1->mm - w2->mm );
    if ( w1->dd != w2->dd )
        return ( w1->dd - w2->dd );
    if ( w1->HH != w2->HH )
        return ( w1->HH - w2->HH );
    if ( w1->MM != w2->MM )
        return ( w1->MM - w2->MM );
    if ( w1->SS != w2->SS )
        return ( w1->SS - w2->SS );
    return ( strcmp(w1->url, w2->url) );
}


int
strncmpi( const char *s, const char *t, size_t n )
{
    int             ret = 0;
    register int    i, j;

    while ( *s && *t && ( n > 0 ) ) {
        i = *s++; j = *t++;
        if ( i != j ) {
            if ( ( i >= 'a' ) && ( i <= 'z' ) ) {
#if	0
                i = i - 'a' + 'A';
#else
                i &= ~0x20;
#endif
            }
            if ( ( j >= 'a' ) && ( j <= 'z' ) ) {
#if	0
                j = j - 'a' + 'A';
#else
                j &= ~0x20;
#endif
            }
            if ( i != j ) {
                ret = i - j;
                break;
            }
        }
        n--;
    }

    if ( ( ret == 0 ) && ( n > 0 ) ) {
        if ( *s )
            ret = *s;
        if ( *t )
            ret = -(*t);
    }

    return ( ret );
}


char *
unescapeURL( const char *url )
{
    const char  *p;
    char        *q;
    static char buf[1024];

    p = url;
    q = buf;
    while ( *p ) {
        if ( !strncmp( p, "&amp;", 5 ) ) {
            *q++ = '&';
            p += 5;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    return ( buf );
}

char    *
any2utf( const char *p )
{
    char    *q;

    q = utf2sjis( p );
    if ( q )
        q = (char *)p;  // ���ł� UTF-8 �ϊ��ς�
    else {
        // p �� charset �� UTF-8 �ł͂Ȃ�
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2utf( p );
        else {
            q = euc2sjis( p );
            if ( q )
                q = euc2utf( p );
            if ( !q )
                q = sjis2utf( p );
            if ( !q && p ) {
                /* �ȉ��AVox �΍� */
                char    *r = (char *)malloc( strlen(p) * 12 + 1 );

                if ( r ) {
                    char    *s;

                    strcpy( r, p );
                    s = utf2sjisEx( r );    /* (��Ƃ���) &ccedil; �΍� */
                    if ( s )
                        q = sjis2utf( s );
                    free( r );
                }
            }
            if ( !q )
                q = (char *)p;
        }
    }

    return ( q );
}

char    *
any2euc( const char *p )
{
    char    *q;

    q = utf2sjis( p );
    if ( q )    // �ϊ��Ώە������ UTF-8 �ł���
        q = utf2euc( p );
    else {
        // p �� charset �� UTF-8 �ł͂Ȃ�
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2euc( p );
        else {
            q = sjis2euc( p );
            if ( !q )
                q = (char *)p;  // ���ł� EUC-JP �ϊ��ς�(�Ƃ݂Ȃ�)
        }
    }

    return ( q );
}

char    *
any2sjis( const char *p )
{
    char    *q;

    q = utf2sjis( p );
    if ( !q ) {
        // p �� charset �� UTF-8 �ł͂Ȃ�
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2sjis( p );
        else {
            q = euc2sjis( p );
            if ( !q )
                q = (char *)p;  // ���ł� Shift_JIS �ϊ��ς�(�Ƃ݂Ȃ�)
        }
    }

    return ( q );
}

char    *
any2sjisEx( char *dst, const char *src )
{
    char    *p;

    p = any2utf( src );
    if ( p ) {
        strcpy( dst, p );
        p = utf2sjis( dst );
        if ( p )
            strcpy( dst, p );
    }
    strcpy( dst, p ? p : src );

    return ( dst );
}

char    *
chcode( char *p )
{
    char    *q = p;

    while ( q && *q ) {
        if ( (*q == '&') && (*(q + 1) == '#') && (*(q + 2) == '0') &&
             ((*(q + 3) >= '0') && (*(q + 3) <= '9')) &&
             ((*(q + 4) >= '0') && (*(q + 4) <= '9')) &&
             (*(q + 5) == ';')                                        ) {
            int c = (*(q + 3) - '0') * 10 + (*(q + 4) - '0');
            *q = (char)c;
            strcpy( q + 1, q + 6 );
        }

        q++;
    }

    return ( p );
}

/* �w�肳�ꂽ������(Shift_JIS)���w�蕶���񒷂Ɋۂ߂� */
char *
adjustStringLength( char *p, int len )
{
    int     i;
    BOOL    flag = FALSE;

    for ( i = 0; i < len; i++ ) {
        if ( (flag == FALSE) && iskanji1(p[i]) )
            flag = TRUE;
        else
            flag = FALSE;
    }
    if ( flag == TRUE )
        p[len - 1] = NUL;
    else
        p[len] = NUL;

    return ( p );
}

/*      ������\�킷�����񂩂�A�N���������b�����o�� */
time_t
getDateTimeFromDateString(
        const char *date,   /* (I) �������(������) */
        int        *yyyy,   /* (O) �N               */
        int        *mm,     /* (O) ��               */
        int        *dd,     /* (O) ��               */
        int        *HH,     /* (O) ��               */
        int        *MM,     /* (O) ��               */
        int        *SS      /* (O) �b               */
    )
{
    const char  *p = date;
    const char  *q;
    time_t      t = 0;
    struct tm   tm;
    int         i;
    int         dHH = 0, dMM = 0, d = 0;
    BOOL        found = FALSE;
    static char monStr[12][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    *yyyy = 0;
    *mm   = 0;
    *dd   = 0;
    *HH   = 0;
    *MM   = 0;
    *SS   = 0;

    /* �܂��A�u�N�����v���������� */
    for ( i = 0; i < 12; i++ ) {
        q = strstr( p, monStr[i] );
        if ( q                                 &&
             (*(q - 1) == ' ')                 &&
             (*(q + strlen(monStr[i])) == ' ')    ) {
            found = TRUE;
            break;
        }
    }
    if ( found ) {
        /* RFC 822 �`���̓��t�̏ꍇ              */
        /*   ��) Tue, 20 May 2003 08:56:02 GMT   */
        /*       20 May 2003 08:56:02 GMT        */
        /*       Tue, 20 May 2003 17:56:02 JST   */
        /*       Tue, 20 May 2003 17:56:02 +0900 */
        /*       Tue, 20 May 2003 17:56:02+0900  */
        /*       Wed, 06 Dec 2006 14:54:02 +0900 */
        /*       Wed, 6 Dec 2006 14:54:02 +0900  */
        while ( *p && ((*p < '0') || (*p > '9')) )
            p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *dd = *p - '0';
            p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *dd = *dd * 10 + (*p - '0');
                p++;
            }
        }

        while ( *p && ((*p < 'A') || (*p > 'Z')) )
            p++;
        *mm = i + 1;

        while ( *p && ((*p < '0') || (*p > '9')) )
            p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *yyyy = *p - '0';
            p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *yyyy * 10 + (*p - '0');
                p++;
            }
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *yyyy * 10 + (*p - '0');
                p++;
            }
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *yyyy * 10 + (*p - '0');
                p++;
            }
        }

        while ( *p && ((*p < '0') || (*p > '9')) )
            p++;
    }
    else {
     // q = strchr( p, 'T' );
     // if ( q &&
     //      (*(q - 1) >= '0') && (*(q - 1) <= '9') &&
     //      (*(q + 1) >= '0') && (*(q + 1) <= '9')    ) {
            /* ISO8601 �`���̓��t�̏ꍇ      */
            /* ��) 2003-12-03T23:59:59+09:00 */
            /*     2003-12-03T23:59:59Z      */
            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *yyyy = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
                if ( (*p >= '0') && (*p <= '9') ) {
                    *yyyy = *yyyy * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *mm = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *mm = *mm * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                *dd = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *dd = *dd * 10 + (*p - '0');
                    p++;
                }
            }
    //  }
    //  else {
    //      /* ����ȊO�̌`���̏ꍇ */
    //  }
    }

    /* ���ɁA�u�����b�v���������� */
    while ( *p && ((*p < '0') || (*p > '9')) )
        p++;
    if ( (*p >= '0') && (*p <= '9') ) {
        *HH = *p - '0';
        p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *HH = *HH * 10 + (*p - '0');
            p++;
        }
    }

    while ( *p && ((*p < '0') || (*p > '9')) )
        p++;
    if ( (*p >= '0') && (*p <= '9') ) {
        *MM = *p - '0';
        p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *MM = *MM * 10 + (*p - '0');
            p++;
        }
    }

    while ( *p                         &&
            ((*p < '0') || (*p > '9')) &&
            (*p != '-')                &&
            (*p != '+')                &&
            ((*p < 'A') || (*p > 'Z'))    )
        p++;
    if ( (*p >= '0') && (*p <= '9') ) {
        *SS = *p - '0';
        p++;
        if ( (*p >= '0') && (*p <= '9') ) {
            *SS = *SS * 10 + (*p - '0');
            p++;
        }
    }

    while ( *p ) {
        /* �uUTC �Ƃ̎����v���������� */
        if ( *p == 'Z' )
            ;   // UTC(�Ȃ̂ŁA���ɏ�������K�v�͂Ȃ�)
        else if ( (*p == '-') || (*p == '+') ) {
            /* +09:00 �� +0900 ��2�p�^�[��(':'�̗L��)���� */
            d = (*p == '-') ? -1 : 1;
            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                dHH = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    dHH = dHH * 10 + (*p - '0');
                    p++;
                }
            }

            while ( *p && ((*p < '0') || (*p > '9')) )
                p++;
            if ( (*p >= '0') && (*p <= '9') ) {
                dMM = *p - '0';
                p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    dMM = dMM * 10 + (*p - '0');
                    p++;
                }
            }
            break;
        }
        else {
            // ���[�J������(���̃v���O�����𓮂����Ă���PC�̃^�C���]�[�����̗p)
            //  -- �{���́A�T�[�o�ݒu�ꏊ�̃��[�J�����Ԃ��̗p����K�v������
#ifdef  WIN32
            if ( _timezone != 0 ) {
                d = (_timezone > 0 ) ? 1 : -1;
                if ( d == -1 )
                    _timezone *= d;
                dHH = (timezone / 60) / 60;
                dMM = (timezone / 60) % 60;
            }
#else
            /* JST �� GMT (�Ƃ肠�����A���{�ȊO�ł��̃v���O�������g���l�� */
            /*             ���Ƃ͖Y���) [�b��]                           */
            d   = 1;
            dHH = 9;
            dMM = 0;
#endif
        }
        p++;
    }

    if ( *yyyy > 2000 ) {    
        struct tm   *m;

        tm.tm_year = *yyyy - 1900;
        tm.tm_mon  = *mm   - 1;
        tm.tm_mday = *dd;
        tm.tm_hour = *HH;
        tm.tm_min  = *MM;
        tm.tm_sec  = *SS;

        t = timelocal( &tm );
        if ( d != 0 )
            t -= (dHH * 60 + dMM) * 60 * d; // UTC
#ifdef  USE_UTC
        m = gmtime( &t );       // UTC �̂܂ܕێ�
#else
        m = localtime( &t );    // ���[�J�����Ԃɕϊ����ĕێ�
#endif
        *yyyy = m->tm_year + 1900;
        *mm   = m->tm_mon  + 1;
        *dd   = m->tm_mday;
        *HH   = m->tm_hour;
        *MM   = m->tm_min;
        *SS   = m->tm_sec;
    }

    return ( t );
}

/* �w�蕶�����ʂ̎w�蕶����ɒu������ */
BOOL
replaceString( char *target, const char *src, const char *dst )
{
    char    *p = target;
    char    *q;
    BOOL    ret = FALSE;
    int     len = strlen( dst );

    while ( ( q = strstr( p, src ) ) != NULL ) {
        char    *temp;
        int     l = strlen( src );

        temp = (char *)malloc( strlen( p ) - l + strlen( dst ) + 1 );
        if ( temp ) {
            strncpy( temp, p, q - p );
            strcpy( &(temp[q - p]), dst );
            strcat( temp, q + l );

            strcpy( p, temp );
            free( temp );
            ret = TRUE;

            p = q + len;
        }
        else
            break;
    }

    return ( ret );
}

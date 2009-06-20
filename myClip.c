/*
 *  myClip.c
 *      MyClip 構造体関連関数群
 *          written by H.Tsujimura  22 Sep 2006
 *
 * $Log: /comm/bookey/myClip.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 22    08/12/02 19:35 Tsujimura543
 * nullポインタ参照が発生する可能性のある箇所の対処
 * 
 * 21    08/02/14 19:41 Tsujimura543
 * replaceString() を getFlog.c および putTumblr.c から移動
 * 
 * 20    07/11/12 21:56 Tsujimura543
 * adjustStringLength() を putLocalOpml.c, putMMmemo.c から移管
 * 
 * 19    07/11/12 19:03 Tsujimura543
 * any2sjisEx() を追加
 * 
 * 18    07/04/20 20:29 Tsujimura543
 * getYJbookmark.c から compareMyClip() を移管
 * 
 * 17    07/02/22 18:33 Tsujimura543
 * any2sjis() を追加
 * 
 * 16    07/01/19 15:37 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 15    07/01/17 17:33 Tsujimura543
 * 「Vox 対策」の動作確認完了
 * 
 * 14    07/01/17 17:32 Tsujimura543
 * Vox 対策 (&ccedil; を %C3%A7 で送ってくるため、iconv がコード変換に失敗
 * する) として、いったん utf2sjisEx() してから sjis2utf() することで処理
 * 続行可能なようにした
 * 
 * 13    06/12/25 19:24 Tsujimura543
 * any2euc() を修正、charSet 誤判定の確率を減らす
 * 
 * 12    06/12/25 15:09 Tsujimura543
 * any2euc() を追加
 * 
 * 11    06/12/08 15:57 Tsujimura543
 * getDateTimeFromDateString() を変更。ローカル時間で保持するようにした
 * 
 * 10    06/12/07 16:45 Tsujimura543
 * getDateTimeFromDateString() の「_timezone を参照して時差を補正する
 * 場合の処理」を修正
 * 
 * 9     06/12/07 15:57 Tsujimura543
 * getDateTimeFromDateString() を inputLivedoorFeed.c から
 * myClip.c へ移す
 * 
 * 8     06/12/07 14:21 Tsujimura543
 * コメントを修正 (typo)
 * 
 * 7     06/12/07 14:20 Tsujimura543
 * allocateMyClipIfNecessary() 内で設定する publication の初期値を
 * 「全体に公開」とする
 * 
 * 6     06/11/14 15:54 Tsujimura543
 * chcode() の実体を myClip.c へ移動
 * 
 * 5     06/11/14 15:47 Tsujimura543
 * any2utf() の実体を myClip.c へ移動
 * 
 * 4     06/11/14 15:45 Tsujimura543
 * unescapeURL() の実体を myClip.c へ移動
 * 
 * 3     06/11/10 20:07 Tsujimura543
 * strncmpi() の実体を myClip.c に移動
 * 
 * 2     06/09/22 21:40 Tsujimura543
 * allocateMyClipExIfNecessary() を追加
 * 
 * 1     06/09/22 20:49 Tsujimura543
 * 新規作成 (MyClip 構造体格納領域を確保する処理を共通関数化してみた)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/myClip.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
allocateMyClipIfNecessary(
        MyClip **mp,        /* (I/O) 確保する/確保済みメモリ領域     */
        int    unit,        /* (I)   1回辺りのメモリ領域割り当て単位 */
        int    *cnt,        /* (I/O) メモリ割り当て実行回数          */
        int    numOfClips   /* (I)   格納済みブックマーク数          */
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
    pp->publication = PUB_EVERYONE; /* default は「全体に公開」 */

    return ( *mp );
}


MyClipEx    *
allocateMyClipExIfNecessary(
        MyClipEx **mp,      /* (I/O) 確保する/確保済みメモリ領域     */
        int      unit,      /* (I)   1回辺りのメモリ領域割り当て単位 */
        int      *cnt,      /* (I/O) メモリ割り当て実行回数          */
        int      numOfClips /* (I)   格納済みブックマーク数          */
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
        q = (char *)p;  // すでに UTF-8 変換済み
    else {
        // p の charset は UTF-8 ではない
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2utf( p );
        else {
            q = euc2sjis( p );
            if ( q )
                q = euc2utf( p );
            if ( !q )
                q = sjis2utf( p );
            if ( !q && p ) {
                /* 以下、Vox 対策 */
                char    *r = (char *)malloc( strlen(p) * 12 + 1 );

                if ( r ) {
                    char    *s;

                    strcpy( r, p );
                    s = utf2sjisEx( r );    /* (主として) &ccedil; 対策 */
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
    if ( q )    // 変換対象文字列は UTF-8 である
        q = utf2euc( p );
    else {
        // p の charset は UTF-8 ではない
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2euc( p );
        else {
            q = sjis2euc( p );
            if ( !q )
                q = (char *)p;  // すでに EUC-JP 変換済み(とみなす)
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
        // p の charset は UTF-8 ではない
        if ( strstr( p, "\033$@" ) || strstr( p, "\033$B" ) )
            q = jis2sjis( p );
        else {
            q = euc2sjis( p );
            if ( !q )
                q = (char *)p;  // すでに Shift_JIS 変換済み(とみなす)
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

/* 指定された文字列(Shift_JIS)を指定文字列長に丸める */
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

/*      日時を表わす文字列から、年月日時分秒を取り出す */
time_t
getDateTimeFromDateString(
        const char *date,   /* (I) 日時情報(文字列) */
        int        *yyyy,   /* (O) 年               */
        int        *mm,     /* (O) 月               */
        int        *dd,     /* (O) 日               */
        int        *HH,     /* (O) 時               */
        int        *MM,     /* (O) 分               */
        int        *SS      /* (O) 秒               */
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

    /* まず、「年月日」部分を処理 */
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
        /* RFC 822 形式の日付の場合              */
        /*   例) Tue, 20 May 2003 08:56:02 GMT   */
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
            /* ISO8601 形式の日付の場合      */
            /* 例) 2003-12-03T23:59:59+09:00 */
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
    //      /* それ以外の形式の場合 */
    //  }
    }

    /* 次に、「時分秒」部分を処理 */
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
        /* 「UTC との時差」部分を処理 */
        if ( *p == 'Z' )
            ;   // UTC(なので、特に処理する必要はない)
        else if ( (*p == '-') || (*p == '+') ) {
            /* +09:00 と +0900 の2パターン(':'の有無)ある */
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
            // ローカル時間(このプログラムを動かしているPCのタイムゾーンを採用)
            //  -- 本当は、サーバ設置場所のローカル時間を採用する必要がある
#ifdef  WIN32
            if ( _timezone != 0 ) {
                d = (_timezone > 0 ) ? 1 : -1;
                if ( d == -1 )
                    _timezone *= d;
                dHH = (timezone / 60) / 60;
                dMM = (timezone / 60) % 60;
            }
#else
            /* JST → GMT (とりあえず、日本以外でこのプログラムを使う人の */
            /*             ことは忘れる) [暫定]                           */
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
        m = gmtime( &t );       // UTC のまま保持
#else
        m = localtime( &t );    // ローカル時間に変換して保持
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

/* 指定文字列を別の指定文字列に置換する */
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

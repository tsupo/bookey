/*
 *  outputDeliciousXML.c
 *      ブックマークを del.icio.us の posts/all 形式互換のXMLファイルとして
 *      出力する
 *          written by H.Tsujimura  16 Apr 2007
 *
 * $Log: /comm/bookey/ouputDeliciousXML.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/04/16 17:57 Tsujimura543
 * コメントを修正
 * 
 * 1     07/04/16 17:57 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "myClip.h"
#include "md5.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/ouputDeliciousXML.c 1     09/05/14 3:48 tsupo $";
#endif

char    *regularize( char *p );

char    *
lowerize( char *s )
{
    char    *p = s;

    while ( *p ) {
        if ( (*p >= 'A') && (*p <= 'Z') )
            *p = (char)(*p - 'A' + 'a');
        p++;
    }

    return ( s );
}

void
outputDeliciousXML(
        const MyClip *mp,
        int          numOfClips,
        FILE         *fp,
        const char   *userName
    )
{
    char        *p;
    char        buf[MAX_DESCRIPTION_LEN];
    char        tag[MAX_DESCRIPTION_LEN];
    char        comment[MAX_DESCRIPTION_LEN];
    char        hash[MAX_KEYLENGTH];
    int         i;
    time_t      t = time( NULL );
    struct tm   tm, *tt;
    int         yyyy, mm, dd, HH, MM, SS;

    fputs( "<?xml version='1.0' standalone='yes'?>\n", fp );

    for ( i = 0; i < numOfClips; i++ ) {
        p = any2utf( mp[i].title );
        strcpy( buf, p ? p : mp[i].title );

        p = any2utf( mp[i].tags );
        strcpy( tag, p ? p : mp[i].tags );

        p = any2utf( mp[i].comment );
        strcpy( comment, p ? p : mp[i].comment );

        regularize( buf );
        regularize( tag );
        regularize( comment );

        tm.tm_year = mp[i].yyyy - 1900;
        tm.tm_mon  = mp[i].mm - 1;
        tm.tm_mday = mp[i].dd;
        tm.tm_hour = mp[i].HH;
        tm.tm_min  = mp[i].MM;
        tm.tm_sec  = mp[i].SS;
        t = timelocal( &tm );
#ifdef  WIN32
        if ( _timezone != 0 )
            t += _timezone;
#else
        t -= 9 * 60 * 60;   /* JST → GMT */
#endif

        tt = gmtime( &t );
        if ( !tt )
            tt = localtime( &t );
        if ( tt ) {
            yyyy = tt->tm_year + 1900;
            mm   = tt->tm_mon + 1;
            dd   = tt->tm_mday;
            HH   = tt->tm_hour;
            MM   = tt->tm_min;
            SS   = tt->tm_sec;
        }
        else {
            yyyy = mp[i].yyyy;
            mm   = mp[i].mm;
            dd   = mp[i].dd;
            HH   = mp[i].HH;
            MM   = mp[i].MM;
            SS   = mp[i].SS;
        }

        if ( i == 0 )
        fprintf( fp,
                 "<posts update=\"%04d-%02d-%02dT%02d:%02d:%02dZ\" "
                 "user=\"%s\">\n",
                 yyyy, mm, dd, HH, MM, SS,
                 userName && *userName ? userName : "???" );

        fprintf( fp,
                 "  <post href=\"%s\" description=\"%s\" ",
                 mp[i].url, buf );

        if ( comment[0] )
            fprintf( fp,
                     "extened=\"%s\" ",
                     comment );
        else
            fputs( "extened=\"\" ", fp );

        strcpy( hash, lowerize( MD5( mp[i].url ) ) );
        fprintf( fp,
                 "hash=\"%s\" ",
                 hash );

        if ( tag )
            fprintf( fp,
                     "tag=\"%s\" ",
                     tag );
        else
            fputs( "tag=\"\" ", fp );

        fprintf( fp,
                 "time=\"%04d-%02d-%02dT%02d:%02d:%02dZ\" />\n",
                 yyyy, mm, dd, HH, MM, SS );
    }

    fputs( "</posts>\n\n", fp );
}

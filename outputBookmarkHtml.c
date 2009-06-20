/*
 *  outputBookmarkHtml.c
 *      ブックマークを NETSCAPE-Bookmark-file-1 形式の htmlファイルとして
 *      出力する
 *          written by H.Tsujimura  10 Nov 2006
 *
 * $Log: /comm/bookey/outputBookmarkHtml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     06/12/04 19:18 Tsujimura543
 * (Internet Explorer 向けに) Shift_JIS でも出力できるようにした
 * 
 * 4     06/11/16 16:42 Tsujimura543
 * valid な html になっていないところがあったので修正
 * 
 * 3     06/11/16 13:55 Tsujimura543
 * タグの総バイト数(タグとタグを区切る文字を含む)が512バイトより大きいと、
 * クラッシュする不具合に対処
 * 
 * 2     06/11/14 20:38 Tsujimura543
 * 実装完了 (動作確認済み)
 * 
 * 1     06/11/10 19:39 Tsujimura543
 * 新規作成 (スケルトン)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/outputBookmarkHtml.c 1     09/05/14 3:48 tsupo $";
#endif

char    *regularize( char *p );


void
outputBookmarkHtml(
        const MyClip *mp,
        int          numOfClips,
        const char   *title,
        int          codeChange,
        FILE         *fp
    )
{
    char    *p;
    char    buf[BUFSIZ];
    char    tag[4096];
    char    comment[4096];
    int     i;
    time_t  t = time( NULL ), tt;
    struct tm   tm;

    fprintf( fp,
             "<!DOCTYPE NETSCAPE-Bookmark-file-1>\n"
             "<!-- This is an automatically generated file.\n"
             "     It will be read and overwritten.\n"
             "     DO NOT EDIT! -->\n"
             "<HTML>\n<HEAD>\n"
             "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; "
             "charset=%s\">\n"
             "<TITLE>Bookmarks</TITLE>\n"
             "</HEAD>\n\n<BODY>\n"
             "<H1>Bookmarks</H1>\n\n"
             "<DL><p></p>\n",
             codeChange == SJIS ? "Shift_JIS" : "UTF-8" );

    switch ( codeChange ) {
    case SJIS:
        p = euc2sjis( title );
        if ( !p )
            p = utf2sjis( title );
        break;

    case SJIS2UTF:
        p = sjis2utf( title );
        break;

    case EUC2UTF:
        p = euc2utf( title );
        break;

    case UTF8:
    default:
        p = NULL;
        break;
    }
    fprintf( fp,
           "    <DT><H3 FOLDED ADD_DATE=\"%d\" LAST_MODIFIED=\"%d\">%s</H3>\n"
           "    <DL><p></p>\n",
             t, t, p ? p : title );

    for ( i = 0; i < numOfClips; i++ ) {
        switch ( codeChange ) {
        case SJIS:
            p = utf2sjis( mp[i].title );
            if ( !p )
                p = euc2sjis( mp[i].title );
            if ( !p ) {
                strcpy( buf, mp[i].title );
                p = utf2sjisEx( buf );
            }
            strcpy( buf, p ? p : mp[i].title );

            p = utf2sjis( mp[i].tags );
            if ( !p )
                p = euc2sjis( mp[i].tags );
            if ( !p ) {
                strcpy( buf, mp[i].tags );
                p = utf2sjisEx( buf );
            }
            strcpy( tag, p ? p : mp[i].tags );

            p = utf2sjis( mp[i].comment );
            if ( !p )
                p = euc2sjis( mp[i].comment );
            if ( !p ) {
                strcpy( buf, mp[i].comment );
                p = utf2sjisEx( buf );
            }
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case SJIS2UTF:
            p = sjis2utf( mp[i].title );
            strcpy( buf, p ? p : mp[i].title );
            p = sjis2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = sjis2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case EUC2UTF:
            p = euc2utf( mp[i].title );
            strcpy( buf, p ? p : mp[i].title );
            p = euc2utf( mp[i].tags );
            strcpy( tag, p ? p : mp[i].tags );
            p = euc2utf( mp[i].comment );
            strcpy( comment, p ? p : mp[i].comment );
            break;

        case UTF8:
        default:
            strcpy( buf, mp[i].title );
            strcpy( tag, mp[i].tags );
            strcpy( comment, mp[i].comment );
            break;
        }

        regularize( buf );
        regularize( tag );
        regularize( comment );

        tm.tm_year = mp[i].yyyy - 1900;
        tm.tm_mon  = mp[i].mm - 1;
        tm.tm_mday = mp[i].dd;
        tm.tm_hour = mp[i].HH;
        tm.tm_min  = mp[i].MM;
        tm.tm_sec  = mp[i].SS;
        tt = timelocal( &tm );
#ifdef  WIN32
        if ( _timezone != 0 )
            tt += _timezone;
#else
        tt -= 9 * 60 * 60;   /* JST → GMT */
#endif

        fprintf( fp,
               "        <DT><A HREF=\"%s\" ADD_DATE=\"%d\" LAST_VISIT=\"%d\"",
                 mp[i].url, tt, tt );
        if ( tag[0] ) {
            p = tag;
            while ( *p ) {
                if ( *p == ' ' )
                    *p = ',';
                p++;
            }
            fprintf( fp,
                     " TAGS=\"%s\"",
                     tag );
        }
        fprintf( fp,
                 ">%s</A></DT>\n",
                 buf );
        if ( comment[0] )
            fprintf( fp,
                     "        <DD>%s</DD>\n",
                     comment );
    }

    fputs( "    </DL><p></p>\n"
           "</DL><p></p>\n"
           "</BODY>\n</HTML>\n\n",
           fp );
}

/*
 * decodeContents.c
 *      JSON 関連ライブラリ (Unicode → UTF-8 変換処理)
 *          written by H.Tsujimura  12 Jul 2006 / 26 Jul 2008
 *
 * $Log: /comm/bookey/decodeContents.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     08/07/26 0:30 Tsujimura543
 * getDrecomRSS.c から decodeContents() を分離独立させた
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/decodeContents.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/* Unicode(UCS-2BE) (%uXXXX) → UTF-8 (xxyyzz) 変換 */
char    *
convUnicode( unsigned long code )
{
    unsigned short      a, b, c, d;
    Thread  static char codeStr[6];

    if ( code < 0x0080 ) {
        a = (unsigned short)code;
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = NUL;
    }
    else if ( code < 0x0800 ) {
        a = (unsigned short)(((code & 0x07C0) >> 6) | 0xC0);
        b = (unsigned short)(( code & 0x003F)       | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = NUL;
    }
    else if ( code < 0x010000 ) {
        a = (unsigned short)(((code & 0xF000) >> 12) | 0xE0);
        b = (unsigned short)(((code & 0x0FC0) >>  6) | 0x80);
        c = (unsigned short)(( code & 0x003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = NUL;
    }
    else {
        a = (unsigned short)(((code & 0x001C0000) >> 18) | 0xF0);
        b = (unsigned short)(((code & 0x0003F000) >> 12) | 0x80);
        c = (unsigned short)(((code & 0x00000FC0) >>  6) | 0x80);
        d = (unsigned short)(( code & 0x0000003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = (char)(d & 0xFF);
        codeStr[4] = NUL;
    }

    return ( codeStr );
}


/* JSON 形式で取得したコンテンツのデコード */
char    *
decodeContents( char *contents )
{
    unsigned char   *p = (unsigned char *)contents;
    unsigned char   *q;
    char            *r;

    while ( p && *p ) {
        if ( *p != '\\' ) {
            p++;
            continue;
        }

        p++;
        switch ( *p ) {
        case '"':
        case '/':
            strcpy( (char *)p - 1, (char *)p );
            break;

        case 'r':
            strcpy( (char *)p - 1, (char *)p );
            *(p - 1) = '\r';
            break;

        case 'n':
            strcpy( (char *)p - 1, (char *)p );
            *(p - 1) = '\n';
            break;

        case 'u':   /* UCS-2 */
            {
                char            *term;
                unsigned long   hex;
                char            tmp[8];

                p++;
                tmp[0] = *p++;
                tmp[1] = *p++;
                tmp[2] = *p++;
                tmp[3] = *p++;
                tmp[4] = NUL;
                hex = strtol( tmp, &term, 16 );
                term = (char *)p;
                q = (unsigned char *)convUnicode( hex );
                p -= 6;
                while ( *q )
                    *p++ = *q++;
                strcpy( (char *)p, term );
            }
            break;

        default:
            p++;
            break;
        }
    }

    while ( ( r = strstr( contents, "&amp;" ) ) != NULL )
        strcpy( r + 1, r + 5 );

    return ( contents );
}

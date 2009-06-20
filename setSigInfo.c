/*
 *  setSigInfo.c
 *      BAZエンコード文字列をデコード(ZAB)する
 *          written by H.Tsujimura  8 Jan 2008 / 1 Apr 2009
 *          (chirrup の utility.c 中の同名の関数をほとんどそのまま流用)
 *
 * $Log: /comm/bookey/setSigInfo.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     09/04/01 17:46 Tsujimura543
 * 最初の版
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/setSigInfo.c 1     09/05/14 3:48 tsupo $";
#endif


/* BAZ.H
 * Contributed to Public Domain 9/93
 * by Thad Smith, Boulder Co.
 */

typedef enum {      /* decoder return status: */
    DECR_OK,            /* normal return      */
    DECR_INVALID_DATA,  /* invalid input data */
    DECR_CRC_ERR,       /* CRC error          */
    DECR_END            /* decoding complete  */
}   decode_stat;


/* BAZCOM.H
 * Contributed to Public Domain 9/93
 * by Thad Smith, Boulder Co.
 */

/* Internal constants */
#define BASE            94  /* # possible output chars */
#define FIRST_CODE      '!' /* lowest output char      */
#define END_FLAG        '}' /* starts last data block  */
#define PBASE           56  /* prefix base             */
#define BINB_LEN         9  /* length of binary block  */
#define ENCB_LEN        11  /* length of encoded block */
#define MAX_ENDBLK_DB   13  /* max # data bytes in     *
                             * final ensemble          */
#define CRC_INIT_VALUE  (~0)/* CRC seed                */
#define PBMULT  (unsigned)(((0xffffffffUL/PBASE)>>16)+1)
                            /* prefix multiplier       */

#define	BASESQ          (unsigned long)(BASE * BASE)
#define	LAST_CODE       (FIRST_CODE + BASE - 1)
#define	ISENCODE(c)     (((c) >= FIRST_CODE) && ((c) <= LAST_CODE))
#define	BASEVAL(c)      (unsigned)((c)-FIRST_CODE)

#define CRCW            16              /* # bits in CRC     */
#define CRCLBY          (CRCW/8)        /* CRC byte length   */
#define CRCMASK         ((1U<<CRCW)-1)  /* mask for full CRC */


/* Use updcrc() for a block of data,
 *     UPDATE_CRC1() for a single byte.
 *
 * Adapted from CRC-16F.C, a public domain routine
 * in Bob Stout's Snippets file collection.
 * Adaptations donates to public domain.
 */

#define	UPDATE_CRC1(c,crc)  (((crc)<<8) ^ \
                             crctab[(((crc)>>(CRCW-8)) ^ (c)) & 0xff])

#define P   0x1021  /* CRC polynomial */

static unsigned short
updcrc( unsigned short      crc,    /* prev CRC */
        const unsigned char *cp,    /* new data */
        unsigned int        cnt )   /* # bytes  */
{
    static unsigned short   crctab[1 << 8];
    static int              initialized = 0;

    if ( !initialized ) {
        /* Initialize CRC table */
        unsigned int    b, v;
        int             i;

        for ( b = 0; b <= (1 << 8) - 1; ++b ) {
            for ( v = b << (CRCW - 8), i = 8; --i >= 0; )
                v = v & 0x8000 ? (v << 1) ^ P : v << 1;
            crctab[b] = (unsigned short)v;
        }

        initialized = 1;
    }

    while ( cnt-- )
        crc = (unsigned short)UPDATE_CRC1( *cp++, crc );
    return ( (unsigned short) (crc & (unsigned short)(CRCMASK)) );
}

/* Decode 11 printable ASCII characters into 9 bytes */
static int         /* return: 0=OK, 1= invalid input */
decode_11_to_9( unsigned char out[], const char in[] )
{
    unsigned long   block;
    unsigned        b2, q1, q2, i;

    block  = BASEVAL(in[0]) * BASESQ +
                (BASEVAL(in[1]) * BASE + BASEVAL(in[2]));
    out[0] = (unsigned char)(block & 0xff);
    b2 = (unsigned)(block >> 8);
    q1 = b2 / PBASE;
    q2 = b2 - q1 * PBASE;
    if ( q1 >= PBASE )
        return ( 1 );

    for ( i = 1; i < 9; i += 4 ) {
        block = (BASEVAL(in[i+2]) * BASE +
                    BASEVAL(in[i+3])) * BASESQ +
                        (BASEVAL(in[i+4]) * BASE + BASEVAL(in[i+5]));

        if ( ( (unsigned)(block >> 16) >= PBMULT)                    ||
               q1 == PBASE-1                                      &&
               block > (0xffffffffUL - (PBMULT*(PBASE-1UL) << 16)       ) )
        return ( 1 );

        block   += (unsigned long) (q1 * PBMULT) << 16;
        out[i+0] = (unsigned char) (block >> 24);
        out[i+1] = (unsigned char) (block >> 16);
        out[i+2] = (unsigned char) (block >> 8);
        out[i+3] = (unsigned char) block;
        q1 = q2;
    }

    return ( 0 );
}

static decode_stat
decode_endmark(
        char          *buf,
        const char    *data,    /* data following inbuf */
        size_t        len,      /* length of data       */
        char          *inbuf,
        unsigned char *outbuf,
        unsigned int  *crc,     /* input file CRC       */
        int           *ninb     /* # bytes in inbuf	    */
    )
{
    int             nreq;   /* # input bytes required for *
                             * end ensemble		          */
    unsigned int    rc;     /* # remaining data bytes     */

    if ( (rc = BASEVAL(inbuf[1])) > MAX_ENDBLK_DB )
        return ( DECR_INVALID_DATA );

    memset( inbuf + *ninb, FIRST_CODE, 2 * ENCB_LEN + 2 - *ninb );
    nreq = rc + 4 + CRCLBY;
    if ( nreq < ENCB_LEN) 
        nreq = ENCB_LEN;    /* min size is 1 block */
    if ( rc > BINB_LEN - CRCLBY )
        nreq += 2;          /* use part of 2nd blk */

    /* get remaining characters */
    while ( *ninb < nreq ) {
        if ( len == 0 )
            return ( DECR_OK ); /* need more input chars */
        if ( ISENCODE(*data) )
            inbuf[(*ninb)++] = *data;
        data++;
        len--;
    }

    if ( decode_11_to_9( outbuf, inbuf + 2 ) )
        return ( DECR_INVALID_DATA );
    if ( rc > BINB_LEN - CRCLBY ) {
        if ( decode_11_to_9( outbuf + BINB_LEN, inbuf + 2 + ENCB_LEN ) )
            return ( DECR_INVALID_DATA );
    }
    *crc = updcrc( (unsigned short)(*crc), outbuf, rc );

    outbuf[rc] = NUL;
    strcat( buf, (char *)outbuf );
    if ( strlen( (const char *)outbuf ) < BINB_LEN )
        return ( DECR_OK );

    if ( (((*crc) >> 8) & 0xff) != outbuf[rc]   ||
         ( (*crc)       & 0xff) != outbuf[rc+1]    )
        return ( DECR_CRC_ERR );

    return ( DECR_END );
}

static decode_stat
dbaz_data(
        char                *buf,
        const unsigned char *sig,
        size_t              sigLen,
        char                *inbuf,
        unsigned char       *outbuf,
        unsigned int        *crc,
        int                 *ninb
    )
{
    for (;;) {
        /* fill block input buffer */
        while ( *ninb < ENCB_LEN ) {
            if ( ISENCODE(*sig) )
                inbuf[(*ninb)++] = (char) *sig;
            sig++;
            if ( --sigLen == 0 )
                return ( DECR_OK );
        }

        if ( *inbuf == END_FLAG )
            return ( decode_endmark( buf,
                                     (const char*) sig, sigLen,
                                     inbuf, outbuf,
                                     crc, ninb ) );

        if ( decode_11_to_9( outbuf, inbuf ) )
            return ( DECR_INVALID_DATA );

        *ninb = 0;
        *crc  = updcrc( (unsigned short)(*crc), outbuf, BINB_LEN );

        strcat( buf, (const char *)outbuf );
        if ( strlen( (const char *)outbuf ) < BINB_LEN )
            break;
    }

    return ( DECR_OK );
}

BOOL
setSigInfo( char *key, char *secret, const char *sig1, const char *sig2 )
{
    char            buf[BUFSIZ * 2];
    const char      *p, *q;
    int             cnt  = 0;
    int             ninb = 0;
    unsigned int    crc  = (unsigned int)CRC_INIT_VALUE;
    char            inbuf[ENCB_LEN * 2 + 2];
    unsigned char   outbuf[BINB_LEN * 2];

    buf[0] = NUL;
    memset( inbuf,  0x00, ENCB_LEN * 2 + 2 );
    memset( outbuf, 0x00, BINB_LEN * 2 );
    dbaz_data( buf, (const unsigned char *)sig1, strlen(sig1),
               inbuf, outbuf, &crc, &ninb );
    dbaz_data( buf, (const unsigned char *)sig2, strlen(sig2),
               inbuf, outbuf, &crc, &ninb );

    p = buf;
    q = strstr( p, "-ts" );
    if ( q ) {
        strncpy( key, p, q - p );
        key[q - p] = NUL;
        cnt++;
    }

    p = strstr( buf, "ey-" );
    if ( p ) {
        strcpy( secret, p + 3 );
        cnt++;
    }

    return ( cnt >= 2 ? TRUE : FALSE );
}

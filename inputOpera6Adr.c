/*
 *  inputOpera6Adr.c
 *      opera6.adr �`���̃e�L�X�g�t�@�C������u�b�N�}�[�N����荞��
 *          written by H.Tsujimura  10 Nov 2006
 *
 * $Log: /comm/bookey/inputOpera6Adr.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     06/11/14 15:45 Tsujimura543
 * unescapeURL() �̎��̂� myClip.c �ֈړ�
 * 
 * 3     06/11/14 15:29 Tsujimura543
 * �������̎�舵�����@���C�� (���[�J�����Ԃŕێ�����)
 * 
 * 2     06/11/13 22:49 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     06/11/10 19:35 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputOpera6Adr.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
inputOpera6Adr( int *numOfClips, FILE *fp )
{
    MyClip  *mp = NULL;
    MyClip  *newClip_p;
    char    *p, *q, *r;
    char    buf[MAX_CONTENT_SIZE];
    BOOL    found = FALSE;
    char    tags[BUFSIZ * 2];
    char    tmp[65536];
    int     num = 1000; /* �b�� */
    int     cnt = 0, block = 1;

    *numOfClips = 0;
    while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
        while ( isWhiteSpace(*p) )
            p++;
        if ( !strncmp( p, "Opera Hotlist ", 14 ) ) {
            found = TRUE;
            break;
        }
    }

    if ( found ) {
        while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
            while ( isWhiteSpace(*p) )
                p++;

            if ( !strncmpi( p, "#FOLDER", 7 ) ) {
                p += 8;

                tags[0] = NUL;
                while ( (p = fgets(buf, MAX_CONTENT_SIZE - 1, fp)) != NULL ) {
                    while ( isWhiteSpace(*p) )
                        p++;
                    if ( !(*p) )
                        break;
                    if ( !strncmpi( p, "NAME=", 5 ) ) {
                        p += 5;
                        q = strchr( p, '\r' );
                        if ( !q )
                            q = strchr( p, '\n' );
                        if ( q ) {
                            strncpy( tags, p, q - p );
                            tags[q - p] = NUL;
                        }
                    }
                }
            }
            else if ( !strncmpi( p, "#URL", 4 ) ) {
                newClip_p = allocateMyClipIfNecessary(&mp, num, &block, cnt);
                if ( !newClip_p )
                    break;
                mp = newClip_p;

                mp[cnt].url[0]   = NUL;
                mp[cnt].title[0] = NUL;
                while ( (p = fgets(buf, MAX_CONTENT_SIZE - 1, fp)) != NULL ) {
                    while ( isWhiteSpace(*p) )
                        p++;
                    if ( !(*p) ) {
                        if ( mp[cnt].url[0] && mp[cnt].title[0] ) {
                            struct tm   *tt;
                            time_t      t;

                            t  = time( NULL );
                            tt = localtime( &t );

                            mp[cnt].yyyy = tt->tm_year + 1900;
                            mp[cnt].mm   = tt->tm_mon  + 1;
                            mp[cnt].dd   = tt->tm_mday;
                            mp[cnt].HH   = tt->tm_hour;
                            mp[cnt].MM   = tt->tm_min;
                            mp[cnt].SS   = tt->tm_sec;

                            if ( tags[0] ) {
                                r = any2utf( tags );
                                strcpy( mp[cnt].tags, r ? r : tags );
                            }

                            cnt++;
                        }

                        break;
                    }

                    // title
                    if ( !strncmpi( p, "NAME=", 5 ) ) {
                        p += 5;
                        q = strchr( p, '\r' );
                        if ( !q )
                            q = strchr( p, '\n' );
                        if ( q ) {
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;
                            r = any2utf( tmp );
                            strcpy( mp[cnt].title, r ? r : tmp );
                        }
                    }

                    // url
                    if ( !strncmpi( p, "URL=", 4 ) ) {
                        p += 4;
                        q = strchr( p, '\r' );
                        if ( !q )
                            q = strchr( p, '\n' );
                        if ( q ) {
                            strncpy( tmp, p, q - p );
                            tmp[q - p] = NUL;
                            strcpy( mp[cnt].url, unescapeURL( tmp ) );
                        }
                    }
                }
            }
        }
    }
    *numOfClips = cnt;

    return ( mp );
}

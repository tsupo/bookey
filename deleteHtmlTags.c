/*
 *  �w�肳�ꂽ�����񒆂Ɋ܂܂�� html �^�O����菜��
 *      written by H.Tsujimura  6 Oct 2006 / 17 Jan 2007
 *
 * $Log: /comm/bookey/deleteHtmlTags.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/01/17 21:41 Tsujimura543
 * deleteHtmlTags() �� getBlueDot.c ���番���A�Ɨ�������
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/deleteHtmlTags.c 1     09/05/14 3:48 tsupo $";
#endif

char    *
deleteHtmlTags( char *text )
{
    char    *p = text;
    char    *tmp, *q;
    int     innerBlockquote = 0;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* ���̊֐��̏������e               */
    /*   (1) ���s����菜��             */
    /*   (2) <br /> ����菜��          */
    /*   (3) <p>, <img>, <a> ����菜�� */
    /*   (4) <blockquote> ����菜��    */
    /*   (5) </blockquote> ����菜��   */

    while ( *p ) {
        if ( (*p == '\r') || (*p == '\n') ) {
            /* (1) ���s����菜�� */
            p++;
        }
        else if ( !strncmp( p, "<br />", 6 ) ) {
            /* (2) <br /> ����菜�� */
            p += 6;
        }
        else if ( !strncmp( p, "<br>", 4 ) ) {
            /* (2') <br> ����菜�� */
            p += 4;
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (3a1) <p> ����菜�� */
            p += 3;
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (3a2) </p> ����菜�� */
            p += 4;
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (3b1) <cite> ����菜�� */
            p += 6;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (3b2) </cite> ����菜�� */
            p += 7;
        }
        else if ( !strncmp( p, "<a ", 3 ) ) {
            /* (3c1) <a> ����菜�� */
            p += 3;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "</a>", 4 ) ) {
            /* (3c2) </a> ����菜�� */
            p += 4;
        }
        else if ( !strncmp( p, "<img ", 5 ) ) {
            /* (3c1) <img> ����菜�� */
            p += 5;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "<blockquote>", 12 ) ) {
            /* (4a) <blockquote> ����菜�� */
            innerBlockquote = 1;
            p += 12;
        }
        else if ( !strncmp( p, "</blockquote>", 13 ) ) {
            /* (4b) </blockquote> ����菜�� */
            innerBlockquote = 0;
            p += 13;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    if ( tmp ) {
        strcpy( text, tmp );
        free( tmp );
    }

    return ( text );
}

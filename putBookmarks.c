/*
 * putBookmarks.c
 *      �u�b�N�}�[�N�o�^�������C�����[�v
 *          written by H.Tsujimura  17 Oct 2005 / 18 Jan 2007
 *
 * $Log: /comm/bookey/putBookmarks.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/10/05 2:43 Tsujimura543
 * putBookmarks() �̈����ǉ��ɔ����ύX
 * 
 * 3     07/01/22 22:20 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 2     07/01/18 23:45 Tsujimura543
 * ������ύX�B���Y�u�b�N�}�[�N�Ǝ��̈����S��(�\���̂ւ̃|�C���^�n����)
 * �w��ł���悤�ɂ���
 * 
 * 1     07/01/18 17:20 Tsujimura543
 * �V�K�쐬 (�e�u�b�N�}�[�N�T�[�r�X�ւ̓o�^�����̂����A���ʉ��ł��镔����
 * ���o)
 */

#include "xmlRPC.h"
#include "myClip.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBookmarks.c 1     09/05/14 3:48 tsupo $";
#endif

void
putBookmarks(
        const char   *bookmarkName,
        const MyClip *mp,
        int          numOfClips,
        char         *cookie,
        size_t       cookieSize,
        void         *args,
        int (__cdecl *func)( const MyClip *mp,
                             char         *errorString,
                             PARAM_PBM    *args )
    )
{
    char        *request;
    char        *response;
    BOOL        retry;
    int         ret, i;
    size_t      sz = MAX_CONTENT_SIZE * 20;
    char        errorString[BUFSIZ];
    PARAM_PBM   param;
    LCID        l = getLanguageCode();

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return;
    }

    param.cookie     = cookie;
    param.cookieSize = cookieSize;
    param.request    = request;
    param.response   = response;
    param.sz         = sz;
    param.args       = args;

    for ( i = 0; i < numOfClips; i++ ) {
        /* �u�b�N�}�[�N�֓o�^ */
        if ( (numOfClips == 1) || (i < numOfClips - 1) )
            Sleep( 2000 );
        do {
            retry = FALSE;
            param.index    = i;
            errorString[0] = NUL;
            memset( request, 0x00, MAX_CONTENT_SIZE );
            setUpReceiveBuffer( response, sz );
            ret = func( &mp[i], errorString, &param );
            if ( (ret == FALSE) || errorString[0] ) {
                int fd = fileno( stderr );
                if ( (fd >= 0) && isatty( fd ) ) {
                    int c;

                    if ( errorString[0] ) {
                        fprintf( stderr,
                                 l == 0x0411
                                  ? "%s: �u�b�N�}�[�N�̓o�^�Ɏ��s���܂����B\n"
                                    "  -- ���R: %s\n"
                                  : "%s: Cannot register bookmarks.\n"
                                    "  -- Reason: %s",
                                 bookmarkName,
                                 errorString );
                        break;/* �o�^���s�����A���g���C���Ă����J�o���s�\ */
                              /* ���Ǝv����̂ŁA���g���C�����ɔ�����     */
                    }
                    fprintf( stderr,
                             l == 0x0411
                              ? "%s: �u�b�N�}�[�N�̓o�^�Ɏ��s���܂����B\n"
                                "������x�A�����܂���? (y/n) "
                              : "%s: Cannot register bookmarks.\n"
                                "Do you try again? (y/n)",
                                 bookmarkName );
#ifdef  WIN32
                    c = getch();
#else
                    do {
                        c = getchar();
                        if ( c == EOF )
                            clearerr( stdin );
                    }
                    while ( (c != 'y') && (c != 'Y') &&
                            (c != 'n') && (c != 'N')    );
#endif
                    if ( (c == 'y') || (c == 'Y') )
                        retry = TRUE;
                }
#ifdef  WIN32
                else {
                    char    message[BUFSIZ * 2];
                    int     r;

                    if ( errorString[0] ) {
                        sprintf( message,
                                 l == 0x0411
                                  ? "%s �ւ̓o�^�Ɏ��s����"
                                    "�����B  \r\n -- ���R: %s    "
                                  : "%s: Cannot register bookmarks."
                                    "    \r\n -- Reason: %s",
                                 bookmarkName,
                                 errorString );
                        r = MessageBox( NULL,
                                        message,
                                        l == 0x0411
                                         ? "�o�^���s"
                                         : "Registration failure",
                                        MB_OK|MB_ICONERROR );
                    }
                    else {
                        sprintf( message,
                                 l == 0x0411
                                  ? "%s �ւ̓o�^�Ɏ��s���܂����B"
                                    "  \r\n������x�A�����܂���?"
                                  : "%s: Cannot register bookmarks."
                                    "    \r\nDo you try again?",
                                 bookmarkName );
                        r = MessageBox( NULL,
                                        message,
                                        l == 0x0411
                                         ? "�o�^���s"
                                         : "Registration failure",
                                        MB_YESNO|MB_ICONERROR );
                    }
                    if ( r == IDYES )
                        retry = TRUE;
                    else if ( numOfClips > 1 ) {
                        r = MessageBox( NULL,
                                        l == 0x0411
                                         ? "�o�^�𒆒f���܂���?    "
                                         : "Do you discontinue registering?"
                                           "    ",
                                        l == 0x0411
                                         ? "�o�^���s�m�F"
                                         : "Confirmation of registration "
                                           "continuation",// ���̉p��͕ς���
                                        MB_YESNO|MB_ICONERROR );
                        if ( r == IDYES )
                            i = numOfClips + 1;
                    }
                }
#endif
            }
        } while ( retry == TRUE );

    }

    encodeURL( NULL );
    free( response );
    free( request  );
}

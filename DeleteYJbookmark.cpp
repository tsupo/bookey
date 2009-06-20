/*
 *  DeleteYJbookmark.cpp
 *      Yahoo! �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  20 Apr 2007
 *
 * $Log: /comm/bookey/DeleteYJbookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/04/20 23:06 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteYJbookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getYJbookmark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz,
        int        *total
    );
#ifdef __cplusplus
}
#endif


MyClipEx    *
getYJbookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp   = NULL;
    char        *response;
    long        num   = 0;
    int         total = 0;
    size_t      sz    = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_YJ_BOOKMARK );

    // Yahoo! Japan ID �Ń��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginYahooJapan( username, password, cookie ) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �u�b�N�}�[�N���擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    num = _getYJbookmark( username, cookie, NULL, &mp,
                          response, sz, &total );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnYJbookmark( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    size_t  sz  = MAX_CONTENT_SIZE;
    char    url[MAX_URLLENGTH];

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://bookmarks.yahoo.co.jp/action/delete/done" );
    sprintf( request,
             "ratings%%5B%s%%5D=0&"
             "IDS%%5B%s%%5D=on",
             mp->entryID, mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}


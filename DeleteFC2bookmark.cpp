/*
 *  DeleteFC2bokmark.cpp
 *      FC2BOOKMARK �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  30 Mar 2007
 *
 * $Log: /comm/bookey/DeleteFC2bookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/03/30 14:19 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteFC2bookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getFC2Bookmark(
        const char *userName,
        char       *cookie,
        const char *uid,
        const char *cc,
        MyClip     **mp,
        MyClipEx   **mpEx,
        int        *total,
        char       *response,
        size_t     sz
    );
#ifdef __cplusplus
}
#endif


#define MAX_POOKMARK_PER_BLOCK 200

MyClipEx    *
getFC2bookmark2(
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
    char        uid[MAX_NAMELEN];
    char        cc[MAX_KEYLENGTH];

    uid[0] = NUL;
    cc[0]  = NUL;
    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_FC2_BOOKMARK );

    // FC2BOOKMARK �Ƀ��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginFC2Bookmark( username, password, cookie, uid, cc ) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �u�b�N�}�[�N���擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    num = _getFC2Bookmark( username, cookie, uid, cc,
                           NULL, &mp, &total, response, sz );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnFC2bookmark( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url,
             "http://bookmark.fc2.com/user/delete_bookmark/%s",
             mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}


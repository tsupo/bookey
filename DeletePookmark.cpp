/*
 *  DeletePookmark.cpp
 *      POOKMARK Airlines �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  5 Oct 2006
 *
 * $Log: /comm/bookey/DeletePookmark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 7     07/01/19 18:25 Tsujimura543
 * �R�����g���C��
 * 
 * 6     07/01/19 17:11 Tsujimura543
 * _getPookmark() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 5     07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 4     07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 3     07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 2     06/10/27 0:56 Tsujimura543
 * POOKMARK Airlines �̃u�b�N�}�[�N�ꗗ�y�[�W�̃t�H�[�}�b�g���ύX����
 * ���̂ɔ����C�������{
 * 
 * 1     06/10/05 22:29 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeletePookmark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getPookmark(
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


#define MAX_POOKMARK_PER_BLOCK 200

MyClipEx    *
getPookmark2(
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
    char        target[MAX_URLLENGTH];
    size_t      sz    = MAX_CONTENT_SIZE * 20;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_POOKMARK );

    // jugemkey �Ń��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginJugemkey( username, password, cookie ) )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    sprintf( target,
             "http://pookmark.jp/user/%s", username );

    // �u�b�N�}�[�N���擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    num = _getPookmark( username, cookie, NULL, &mp, response, sz, &total );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnPookmark( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://pookmark.jp/ajax/delete_bookmark" );
    sprintf( request,
             "id=%s&"
             "_=",
             mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}


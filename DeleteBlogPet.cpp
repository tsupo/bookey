/*
 *  DeleteBlogPet.cpp
 *      �uBlogPet �C�ɂȂ�L���v�폜����
 *          written by H.Tsujimura  22 Dec 2006
 *
 * $Log: /comm/bookey/DeleteBlogPet.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     07/07/13 2:01 Tsujimura543
 * 2007�N7��12���Ɏ��{���ꂽ BlogPet ���j���[�A���ɑΉ�
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 7     07/02/14 23:13 Tsujimura543
 * _getBlogPet() �̃v���g�^�C�v�錾�� blogPet.h �ֈړ�
 * 
 * 6     07/01/19 15:44 Tsujimura543
 * (1) MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * (2) _getBlogPet() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 5     07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 4     07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 3     06/12/26 0:23 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 2     06/12/26 0:22 Tsujimura543
 * �������� (����m�F�ς�)
 * 
 * 1     06/12/22 21:50 Tsujimura543
 * �V�K�쐬 (�X�P���g��)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"
#ifdef  UNIX
#include <sys/time.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteBlogPet.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "blogPet.h"

#ifdef __cplusplus
}
#endif

#define MAX_BLOGPET_PER_BLOCK   200


MyClipEx    *
getBlogPet2(
        const char       *userName,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp  = NULL;
    char        *response;
    char        userID[MAX_KEYLENGTH];
    size_t      sz;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    userID[0]   = NUL;
    bookmarkName.LoadString( IDS_TGT_BLOGPET );

    // BlogPet �Ǘ���� �փ��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginBlogPet( userName, password, cookie, userID ) )
        return ( mp );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    *numOfClips = 0;

    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c

    *numOfClips = _getBlogPet( userID, cookie, NULL, &mp, response, sz );

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnBlogPet( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    entryKey[MAX_KEYLENGTH];
    size_t  sz;

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    entryKey[0] = NUL;
    sprintf( url,
             "http://www.blogpet.net/bookmark/remove?url=%s",
             encodeURL( mp->url ) );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );    // �폜�m�F
    if ( *response ) {
        char    *p, *q;

        p = strstr( response, "name=\"CID\" value=\"" );
        if ( p ) {
            entryKey[0] = NUL;
            p += 18;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( entryKey, p, q - p );
                entryKey[q - p] = NUL;
            }
        }
    }

    if ( entryKey[0] ) {
        strcpy( url, "http://www.blogpet.net/bookmark/remove" );
        sprintf( request,
                 "CID=%s&"
                 "remove=%s",
                 entryKey,
                 encodeURL( sjis2utf("<span>�폜����</span>") ) );

        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );       // �폜���s
        if ( *response )
            ret = TRUE;
    }

    free( response );
    free( request );

    return ( ret );
}


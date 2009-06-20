/*
 *  DeleteEcNaviClip.cpp
 *      Buzzurl �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  18 Aug 2006 / 11 Jan 2007
 *
 * $Log: /comm/bookey/DeleteEcNaviClip.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 17    07/10/05 2:40 Tsujimura543
 * getEcNaviClipUserID() �̈����ǉ��ɔ����ύX
 * 
 * 16    07/09/13 22:30 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 15    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 14    07/01/19 19:52 Tsujimura543
 * _getEcNaviClip() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 13    07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 12    07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 11    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 10    07/01/11 17:17 Tsujimura543
 * �u�R�����g�v�Ɋ܂܂�� &nbsp; ����������悤�ɂ���
 * 
 * 9     07/01/11 15:47 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 8     06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 7     06/10/10 16:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�� Web�y�[�W�� charSet �� EUC-JP ���� UTF-8 ��
 * �ύX���ꂽ�̂ɔ����C�������{
 * 
 * 6     06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() �𓱓��BMyClipEx �\���̊i�[�̈�m��
 * ���������ʊ֐������Ă݂�
 * 
 * 5     06/08/26 1:53 Tsujimura543
 * ���͂�C���N���[�h�s�v�ɂȂ����w�b�_�t�@�C���̃C���N���[�h����߂�
 * 
 * 4     06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 3     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() �𓱓����A(�폜�p)�u�b�N�}�[�N���擾������
 * �ʃX���b�h������
 * 
 * 2     06/08/22 17:21 Tsujimura543
 * �Ǝ��̍\���̂�p�~���AMyClipEx �𓱓�
 * 
 * 1     06/08/18 20:35 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteEcNaviClip.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
char    *
deleteHtmlTags( char *text );

int
_getEcNaviClip(
        const char *target,
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


#define MAX_ECNAVICLIP_PER_BLOCK    200

MyClipEx    *
getEcNaviClip2(
        const char       *username,
        const char       *password,
        const char       *username2,  /* (I) �F�ؗp���[�U��(Yahoo! Japan)   */
        const char       *password2,  /* (I) �F�ؗp�p�X���[�h(Yahoo! Japan) */
        AUTH_TYPE        authType,    /* (I) �F�؃^�C�v                     */
        char             *cookie,
        size_t           *cookieSize,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        target[MAX_URLLENGTH];
    char        *response;
    int         sz   = MAX_CONTENT_SIZE * 20;
    int         num  = 0;
    int         total = 0;
    CString     bookmarkName;
    CString     text;
    const char  *u = username;
    const char  *p = password;

    if ( authType == AK_YAHOOJAPAN_BBAUTH ) {
        u = username2;
        p = password2;
    }

    *numOfClips = 0;
    target[0]   = NUL;
    bookmarkName.LoadString( IDS_TGT_ECNAVI_CLIP );

    if ( u && u[0] && p && p[0] ) {
        text.LoadString(IDS_TXT_CONTINUE_LOGIN);
        pdlg->ChangeDialogText( bookmarkName,
                                text ); // ���O�C���� �c�c
        char    *uID = getEcNaviClipUserID( u, p, authType,
                                            cookie, cookieSize );
        if ( uID )
            sprintf( target, "http://buzzurl.jp/user/%s/all", uID );
    }
    if ( target[0] == NUL )
        return ( mp );

    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �u�b�N�}�[�N�̎擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    num = _getEcNaviClip( target, cookie, NULL, &mp, response, sz, &total );

    *numOfClips = num;
    free( response );

    return ( mp );
}

BOOL
deleteEntryOnEcNaviClip( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    int     sz = MAX_CONTENT_SIZE * 20;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url,
             "http://buzzurl.jp/config/delete/execute?"
             "entry_id=%s&"
             "thumbprint=%s",
             mp->entryID, mp->remarks );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}

/*
 *  DeleteJoltMark.cpp
 *      JoltMark �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  21 Dec 2006
 *
 * $Log: /comm/bookey/DeleteJoltMark.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 10    07/01/19 23:20 Tsujimura543
 * �s�v�ɂȂ����s���폜
 * 
 * 9     07/01/19 23:20 Tsujimura543
 * _getJoltMark() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 8     07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 7     07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 6     07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 5     07/01/12 22:33 Tsujimura543
 * (1) �u���̃y�[�W�v�� URL �̖����ɗ]���ȕ����������ۂɑΏ�
 * (2) �u�R�����g�v���� <br> ���܂܂��ꍇ�͏�������悤�ɂ���
 * 
 * 4     06/12/26 0:00 Tsujimura543
 * �u���s���v�_�C�A���O�̕����ύX���Y��A�C��
 * 
 * 3     06/12/22 15:25 Tsujimura543
 * (1) getJoltMark2() ������
 * (2) ���ۂɍ폜�ł��邱�Ƃ��m�F
 * 
 * 2     06/12/22 14:25 Tsujimura543
 * deleteEntryOnJoltMark() ������
 * 
 * 1     06/12/21 15:00 Tsujimura543
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
"$Header: /comm/bookey/DeleteJoltMark.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getJoltMark(
        const char *userName,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    );
#ifdef __cplusplus
}
#endif



#define MAX_JOLTMARK_PER_BLOCK  200

MyClipEx    *
getJoltMark2(
        const char       *userName,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp  = NULL;
    long        num  = 0;
    char        *response;
    size_t      sz;
    CString     bookmarkName;
    CString     text;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_JOLTMARK );

    // JoltMark �փ��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginJoltMark( userName, password, cookie ) )
        return ( mp );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    // �u�b�N�}�[�N�̎擾
    num = _getJoltMark( userName, cookie, NULL, &mp, response, sz );
    *numOfClips = num;

    free( response );

    return ( mp );
}

BOOL
deleteEntryOnJoltMark( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz;

    sz = MAX_CONTENT_SIZE * 20;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url,
             "http://mark.jolt.jp/deleteMark.do?"
             "markNo=%s&"
             "viewUserFlag=list&"
             "ckString=%s",
             mp->entryID, mp->remarks );

    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}


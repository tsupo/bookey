/*
 *  DeleteLivedoorClip.cpp
 *      livedoor�N���b�v �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  12 Jul 2006
 *
 * $Log: /comm/bookey/DeleteLivedoorClip.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 14    08/07/28 20:32 Tsujimura543
 *  deleteEntryOnLivedoorClip2() ��ǉ�
 * 
 * 13    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 12    07/01/19 22:05 Tsujimura543
 * _getLivedoorClip() �𓱓��A���t�@�N�^�����O�����{
 * 
 * 11    07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 10    07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 9     07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 8     06/09/22 22:30 Tsujimura543
 * allocateMyClipExIfNecessary() �𓱓��BMyClipEx �\���̊i�[�̈�m��
 * ���������ʊ֐������Ă݂�
 * 
 * 7     06/08/26 1:53 Tsujimura543
 * ���͂�C���N���[�h�s�v�ɂȂ����w�b�_�t�@�C���̃C���N���[�h����߂�
 * 
 * 6     06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 5     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() �𓱓����A(�폜�p)�u�b�N�}�[�N���擾������
 * �ʃX���b�h������
 * 
 * 4     06/08/22 17:21 Tsujimura543
 * �Ǝ��̍\���̂�p�~���AMyClipEx �𓱓�
 * 
 * 3     06/07/24 22:20 Tsujimura543
 * http �����i�[�̈�̃I�[�o�[�����h�~�@�\�𗘗p����悤�ɏC��
 * 
 * 2     06/07/24 20:57 Tsujimura543
 * (1) livedoor�N���b�v��2006�N7��20���t�̕ύX�ɑΉ�
 * (2) �v���C�x�[�g���[�h�̃N���b�v������ƍ폜�ΏۃN���b�v�̓��e�ɉߕs��
 *     ����������s����C��
 * 
 * 1     06/07/12 15:43 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
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
"$Header: /comm/bookey/DeleteLivedoorClip.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef __cplusplus
extern "C" {
#endif
int
_getLivedoorClip(
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


double
getTimeOfDay()
{
    double          s;
#ifdef  UNIX
    struct timeval  tv;
    struct timezone tx;

    gettimeofday( &tv, &tx );
    s = (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
#else
    time_t          t;
    SYSTEMTIME      systime;

    t = time( &t );
    GetSystemTime( &systime );
    s = t * 1000.0 + systime.wMilliseconds;
#endif

    return ( s );
}


#define MAX_LIVEDOORCLIP_PER_BLOCK  200
#define NUM_OF_CLIPS_PER_PAGE       20

MyClipEx    *
getLivedoorClip2(
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
    char        target[MAX_URLLENGTH];
    CString     bookmarkName;
    int         total = 0;
    CString     text;
    size_t      sz;

    *numOfClips = 0;
    bookmarkName.LoadString( IDS_TGT_LIVEDOOR_CLIP );

    // livedoor�N���b�v �փ��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginLivedoorClip( username, password, cookie ) )
        return ( mp );

    sz = MAX_CONTENT_SIZE * 32;
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );

    *numOfClips = 0;

    // �}�C�N���b�v���擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    sprintf( target, "http://clip.livedoor.com/clips/%s", username );
    num = _getLivedoorClip( target, cookie, NULL, &mp, response, sz, &total );

    *numOfClips = num;
    free( response );

    return ( mp );
}

BOOL
deleteEntryOnLivedoorClip( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
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
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://clip.livedoor.com/clip/delete" );
    sprintf( request,
             "hash=%s&"
             "postkey=%s&"
             "rand=%.f",
             mp->entryID, mp->remarks,
             getTimeOfDay() );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}


BOOL    deleteEntryOnLivedoorClip2(
            const char *username,
            const char *apiKey,
            const char *url )
{
    BOOL    ret = FALSE;
    char    *request;
    char    *response;
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
    memset( request,  0x00, MAX_CONTENT_SIZE );

    sprintf( request,
             "%s?url=%s",
             "http://api.clip.livedoor.com/v1/posts/delete",
             encodeURL(url) );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( request, username, apiKey, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<result" );

        if ( p )
            ret = TRUE;
    }

    free( response );
    free( request );

    return ( ret );
}

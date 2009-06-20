/*
 *  DeleteFlog.cpp
 *      Flog �u�b�N�}�[�N �폜����
 *          written by H.Tsujimura  27 Jun 2006
 *
 * $Log: /comm/bookey/DeleteFlog.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 13    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 12    07/01/19 15:47 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 11    07/01/15 22:41 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 10    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 9     06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
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
 * 3     06/07/12 12:10 Tsujimura543
 * deleteEntryOnFlog() ���� response ��������Y��Ă���
 * 
 * 2     06/07/03 15:15 Tsujimura543
 * ProceedingDialog ���݂̉��C (ProceedingDialog �� delete���ɗ�O��
 * �������邱�Ƃ����錏�̑΍���{)
 * 
 * 1     06/06/27 17:57 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "ProceedingDialog.h"
#include "deleteBookmark.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/DeleteFlog.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define MAX_FLOG_PER_BLOCK  200

MyClipEx    *
getFlog2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    )
{
    MyClipEx    *mp = NULL;
    char        *response;
    long        num   = 0;
    int         block = 0;
    char        url[MAX_URLLENGTH];
    size_t      sz = MAX_CONTENT_SIZE * 64;
    CString     bookmarkName;
    CString     text;

    bookmarkName.LoadString( IDS_TGT_FLOG );

    // Flog �փ��O�C��
    text.LoadString(IDS_TXT_CONTINUE_LOGIN);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // ���O�C���� �c�c
    if ( !loginFlog( username, password, cookie ) )
        return ( mp );

    // �Ǘ���ʂ��擾
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    pdlg->ChangeDialogText( bookmarkName,
                            text ); // �u�b�N�}�[�N���擾�� �c�c
    response = (char *)malloc( sz );
    if ( !response )
        return ( mp );
    strcpy( url, "http://www.flog.jp/mybookmark.php" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( response[0] != NUL ) {
        // �Ǘ���ʂ���͂��A�u�b�N�}�[�N�����擾
        char    *p, *q, *r;
        int     len;

        p = strstr( response, "<td align=\"left\" class=\"txt\">" );
        if ( p )
            p = strstr( p + 29, "<a href=/j.php/" );
        if ( !p ) {
            free( response );
            return ( mp );
        }

        do {
            MyClipEx    *newClip_p;
            newClip_p = allocateMyClipExIfNecessary( &mp, MAX_FLOG_PER_BLOCK,
                                                     &block, num );
            if ( !newClip_p )
                break;
            mp = newClip_p;

            // URL
            p += 15;
            q = strstr( p, " target=_blank>" );
            if ( !q )
                break;
            strncpy( mp[num].url, p, q - p );
            mp[num].url[q - p] = NUL;

            // �薼
            p = q + 15;
            q = strstr( p, "</a>" );
            if ( !q )
                break;
            strncpy( mp[num].title, p, q - p );
            mp[num].title[q - p] = NUL;

            // �^�O
            p = q + 4;
            r = strstr( p, "</table>" );
            if ( !r )
                break;
            do {
                q = strstr( p, " class=\"txt_s\">[" );
                if ( !q || (q > r) )
                    break;
                p = q + 16;
                q = strstr( p, "]</a>" ); // 2byte �ڂ� ']' �Ȋ����������㩂�
                if ( !q || (q > r) )      // �͂܂�̂ŁA"</a>" �t���ŕ]������
                    break;

                if ( mp[num].tags[0] )
                    strcat( mp[num].tags, " " );
                len = mp[num].tags[0] ? strlen( mp[num].tags ) : 0;
                strncat( mp[num].tags, p, q - p );
                mp[num].tags[len + (q - p)] = NUL;

                p = q + 5;
            } while ( q );
            if ( p > r )
                break;

            // �R�����g
            q = strstr( p, "<div class=\"comment\">" );
            if ( !q || (q > r) )
                break;
            p += 21;
            q = strstr( p, "\">&nbsp;" );
            if ( !q || (q > r) )
                break;
            p = q + 8;

            q = strstr( p, "&nbsp;(" );
            if ( !q || (q > r) )
                break;
            strncpy( mp[num].comment, p, q - p );
            mp[num].comment[q - p] = NUL;

            // �폜�p�G���g��ID
            p = q + 7;
            q = strstr( p, "<a href=\"/delurl.php/" );
            if ( !q )
                break;
            p = q + 21;
            q = strstr( p, "\" onclick=\"" );
            if ( !q )
                break;
            strncpy( mp[num].entryID, p, q - p );
            mp[num].entryID[q - p] = NUL;

            // ����
            num++;

            p = strstr( r, "<a href=/j.php/" );
        } while ( p );
    }

    free( response );

    *numOfClips = num;

    return ( mp );
}

BOOL
deleteEntryOnFlog( char *cookie, const MyClipEx *mp )
{
    BOOL    ret = FALSE;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 64;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    sprintf( url, "http://www.flog.jp/delurl.php/%s", mp->entryID );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    if ( *response )
        ret = TRUE;

    free( response );

    return ( ret );
}

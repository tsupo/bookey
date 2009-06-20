/*
 * deleteBookmark.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N���폜����֐��Q
 *          written by H.Tsujimura  7 Jun 2005
 *
 * $Log: /comm/bookey/deleteBookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 24    08/11/11 15:09 Tsujimura543
 * DeleteNiftyClip() ��ǉ�
 * 
 * 23    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 22    08/07/28 20:32 Tsujimura543
 *  deleteEntryOnLivedoorClip2() ��ǉ�
 * 
 * 21    08/07/26 0:32 Tsujimura543
 * DeleteDiigo() ��ǉ�
 * 
 * 20    07/10/05 2:42 Tsujimura543
 * BBAuth �Ή��֘A�̊e��C�������{
 * 
 * 19    07/09/13 22:29 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 18    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks �� Yahoo! �u�b�N�}�[�N�́u�폜�v�ɑΉ�
 * 
 * 17    07/03/30 14:09 Tsujimura543
 * FC2BOOKMARK �́u�폜�v�ɑΉ�
 * 
 * 16    07/03/30 13:49 Tsujimura543
 * deleteEntryOnFC2bookmark() ��ǉ�
 * 
 * 15    06/12/22 21:47 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 14    06/12/21 21:18 Tsujimura543
 * JoltMark �ɑΉ�
 * 
 * 13    06/10/26 22:38 Tsujimura543
 * �u���[�J��OPML�v�ɑΉ�
 * 
 * 12    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 11    06/10/05 20:01 Tsujimura543
 * POOKMARK Airlines �֘A�̃v���g�^�C�v�錾��ǉ�
 * 
 * 10    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 9a    06/09/03 19:21 tsupo
 * DBSparam_t �� cookie ���|�C���^����A����(�z��)�ɕύX
 * 
 * 9     06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 8     06/08/25 19:26 Tsujimura543
 * GetBookmarksForDelete() �𓱓����A(�폜�p)�u�b�N�}�[�N���擾������
 * �ʃX���b�h������
 * 
 * 7     06/08/25 18:11 Tsujimura543
 * �e�֐��̈�����1�ǉ�(ProceedingDialog) [�폜�p�̃u�b�N�}�[�N�擾������
 * �ʃX���b�h�����邽�߂̏���]
 * 
 * 6     06/08/22 17:57 Tsujimura543
 * DeleteDrecomRSS() �� Delete1470net() ��ǉ�
 * 
 * 5     06/08/18 15:05 Tsujimura543
 * EC�i�r�l�C�j���[�X�́u�폜�v�ɑΉ�
 * 
 * 4     06/07/12 9:40 Tsujimura543
 * DeleteLivedoorClip() �� DeleteNiftyClip() ��ǉ�
 * 
 * 3     06/06/27 15:24 Tsujimura543
 * Flog �̍폜�ɑΉ�
 * 
 * 2     06/06/22 14:56 Tsujimura543
 * �g���Ă��Ȃ��֐����폜
 * 
 * 1     06/06/07 15:34 Tsujimura543
 * �V�K�쐬 (CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��)
 */

#ifndef __DELETE_BOOKMARK_H__
#define __DELETE_BOOKMARK_H__

void    DeleteHetanaBookmark(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteDeliciousBookmark(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteBlueDotBookmark(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    Delete1470net(
                const char       *userName,  /* (I) �F�ؗp���[�U��         */
                const char       *password,  /* (I) �F�ؗp�p�X���[�h       */
                const char       *userName2, /* (I) �F�ؗp���[�U��(�\��)   */
                const char       *password2, /* (I) �F�ؗp�p�X���[�h(�\��) */
                AUTH_TYPE        authType,   /* (I) �F�؃^�C�v             */
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteDiigo(
                const char       *username,
                const char       *password,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteNiftyClip(
                const char       *apiKey,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

void    DeleteLocalOpml(
                const char       *filename,  /* (I) OPML�t�@�C���� */
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL
            );

/* �폜���s���� */
BOOL    deleteEntryOnMMmemo( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnDrecomRSS( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnFlog( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnLivedoorClip( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnEcNaviClip( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnNiftyClip( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnPookmark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnJoltMark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnBlogPet( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnFC2bookmark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnYJbookmark( char *cookie, const MyClipEx *mp );
BOOL    deleteEntryOnYahooBookmarks( char *cookie, const MyClipEx *mp );

BOOL    deleteEntryOnLivedoorClip2(
            const char *username,
            const char *apiKey,
            const char *url );

/* (�폜�p)�u�b�N�}�[�N�擾���� */
MyClipEx    *
getMMmemo2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getDrecomRSS2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getFlog2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getLivedoorClip2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

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
    );

MyClipEx    *
getNiftyClip2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
get1470net2(
        const char       *username,
        const char       *password,
        const char       *username2,
        const char       *password2,
        AUTH_TYPE        authType,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getPookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getJoltMark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getBlogPet2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getFC2bookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getYJbookmark2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

MyClipEx    *
getYahooBookmarks2(
        const char       *username,
        const char       *password,
        char             *cookie,
        int              *numOfClips,
        ProceedingDialog *pdlg
    );

/* (�폜�p)�u�b�N�}�[�N���擾�X���b�h�N������ */
typedef struct param_sub2a  {
    // �u�b�N�}�[�N���擾�X���b�h�ɓn�������\����
    int                 bookmarkKind;
    RBuser_t            u;
    int                 numOfBookmarks;
    char                cookie[MAX_COOKIE_LEN + 1];
    size_t              cookieSize;
    MyClipEx            *myBookmark;
    ProceedingDialog    *dlg;
}   DBSparam_t;

MyClipEx  *
GetBookmarksForDelete( DBSparam_t *param,
                       int        &numOfMyBookmarks );

#endif  /* __DELETE_BOOKMARK_H__ */

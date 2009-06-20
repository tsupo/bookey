/*
 * UserInfo.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CUserInfo �N���X�̐錾����уC���^�[�t�F�C�X�̒�`
 *          written by H.Tsujimura  1 Jun 2005
 *
 * $Log: /comm/bookey/UserInfo.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 56    09/05/28 22:40 Tsujimura543
 * m_blogName ��ǉ�
 * 
 * 55    09/05/28 22:13 Tsujimura543
 * ����A�J�E���g�ŕ��� tumbleblog ���J�݂��Ă���ꍇ�̓��e��
 * tumbleblog ���w�肵�Ă̓��e���\�ɂ���
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 54    09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 53    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 52    08/07/28 15:30 Tsujimura543
 * m_apiKey ��ǉ�
 * 
 * 51    08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 50    07/10/31 16:58 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 49    07/09/13 22:29 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 48    07/09/06 18:02 Tsujimura543
 * CUserInfo�N���X�̃R�s�[�R���X�g���N�^�A������Z�q�̓��e�����������A
 * private������
 * 
 * 47    07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 46    07/05/23 16:11 Tsujimura543
 * Timelog �ւ̓o�^(����)�ɑΉ�
 * 
 * 45    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 44    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 43    07/04/16 17:59 Tsujimura543
 * del.icio.us �� posts/all �`���� XML �t�@�C���̃C���|�[�g�ƃG�N�X�|�[�g
 * �ɑΉ�����
 * 
 * 42    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 41    07/03/29 23:04 Tsujimura543
 * FC2BOOKMARK �ɑΉ�
 * 
 * 40    07/01/29 17:51 Tsujimura543
 * �^�O�ꗗ�̎擾�A�^�O�̍폜�A�^�O�̒u���̊e������ǉ�
 * 
 * 39    07/01/12 23:34 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 38    06/12/22 22:36 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�Ή�
 * 
 * 37    06/12/21 14:08 Tsujimura543
 * FC2BOOKMARK, �uBlogPet �C�ɂȂ�L���v�Ή�����
 * 
 * 36    06/12/06 19:48 Tsujimura543
 * �R�����g���C��
 * 
 * 35    06/12/06 19:46 Tsujimura543
 * livedoor Clip �̃G�N�X�|�[�g�t�@�C��(RSS 2.0 �`��)���C���|�[�g����@�\
 * ��ǉ�����
 * 
 * 34    06/11/16 16:43 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��16�i�K�A�I��
 * 
 * 33    06/11/16 14:02 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��15�i�K�A�I��
 * 
 * 32    06/11/10 19:26 Tsujimura543
 * �u���E�U�̃u�b�N�}�[�N����荞��/�u���E�U�Ɏ�荞�߂�`���̃u�b�N�}�[�N
 * �t�@�C���𐶐�����@�\���T�|�[�g���邽�߂̏���
 * 
 * 31    06/10/28 1:14 Tsujimura543
 * �u���[�J��OPML�v�֓o�^�ł��Ȃ����Ƃ�����s��ɑΏ�
 * 
 * 30    06/10/26 22:54 Tsujimura543
 * �u���[�J��OPML�v�ɑΉ�
 * 
 * 29    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 28    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline �ɑΉ�
 * 
 * 27    06/09/29 23:48 Tsujimura543
 * newsing �ɑΉ�
 * 
 * 26    06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 25    06/08/22 17:53 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 24    06/08/22 16:59 Tsujimura543
 * enum authenticationType �̒�`�� myClip.h ���Ɉڂ���
 * 
 * 23    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 22    06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 21    06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 * 
 * 20    06/07/19 14:19 Tsujimura543
 * MyClip! �֌W�̏������폜 (2006�N6�����ŃT�[�r�X�I���̂���)
 * 
 * 19    06/07/14 18:09 Tsujimura543
 * �͂ĂȔF��API �Ή�����
 * 
 * 18    06/07/05 18:19 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��13�i�K�A�I��
 * 
 * 17    06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 16    06/06/29 18:47 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 15    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 14    06/06/22 21:21 Tsujimura543
 * inquery �� inquiry �ɏC��(�Ԃ�~�X)
 * 
 * 13    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() �����s���Ă��A�ݒ肪�ύX�ł��Ȃ��Ȃ���
 * ���܂��Ă���(�G���o�O)�̂��C���B�ύX�ł���悤�ɂ���
 * 
 * 12    06/06/21 21:14 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��11�i�K�A�I��
 * 
 * 11    06/06/20 17:59 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��10�i�K�A�I��
 * 
 * 10    06/06/20 14:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��9�i�K�A�I��
 * 
 * 9     06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 8     06/06/14 22:40 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��7�i�K�A�I��
 * 
 * 7     06/06/14 11:44 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��5�i�K�A�I��
 * 
 * 6     06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 5     06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 4     06/06/06 22:23 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��
 * 
 * 3     06/06/01 23:10 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��1�i�K�A�I��
 * 
 * 2     06/06/01 20:28 Tsujimura543
 * CBookeyDlg ���̃��[�U���A�p�X���[�h�� CUserInfo ���g���ĊǗ�����
 * �悤�ɕύX����
 * 
 * 1     06/06/01 19:08 Tsujimura543
 * bookeyView.h ���番���Ɨ�������
 */

#ifndef __CUSER_INFO_H__
#define __CUSER_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "myClip.h"
#ifdef __cplusplus
}
#endif

#include "ProceedingDialog.h"

// CUserInfo �N���X
class CUserInfo
{
public:
    /* �u�b�N�}�[�N��� */
    enum bookmarkType {
        BK_UNKNOWN = 0,
        BK_HATENA,
        BK_DELICIOUS,
        BK_MM_MEMO,
        BK_DRECOM_RSS,
        BK_FLOG,
        BK_LIVEDOOR_CLIP,
        BK_ECNAVI_CLIP,
        BK_NIFTY_CLIP,
        BK_JOLTMARK,
        BK_NEWSING,
        BK_POOKMARK,
        BK_BLUEDOT,
        BK_FC2BOOKMARK,
        BK_BLOGPET,
        BK_TWITTER,
        BK_YJ_BOOKMARK,
        BK_YAHOO_BOOKMARKS,
        BK_TIMELOG,
        BK_DIGG,
        BK_TUMBLR,
        BK_DIIGO,
        BK_1470NET = 1024,
        BK_LOCAL_OPML = 2048,
        BK_NETSCAPE_BOOKMARK_FILE_1,
        BK_OPERA6_ADR,
        BK_HATENA_BOOKMARK_ATOM,
        BK_LIVEDOOR_CLIP_RSS,
        BK_DELICIOUS_XML
    };

    /* �R���X�g���N�^ */
    CUserInfo()
    {
        Init();
    }
    CUserInfo( bool isTarget, CString username, CString password )
    {
        Init( isTarget, username, password );
    }

    /* ������ */
    void    Init();
    void    Init( bool isTarget, CString username, CString password );
    void    Init( bool isTarget ) { m_isTarget = isTarget; }
    void    Init( enum bookmarkType bmType );

    void    GetUserInfo( CString &username,
                         CString &password,
                         enum bookmarkType &bmType );

    /* �Đݒ� */
    void    ResetUserInfo( bool &needToSave );
    void    ResetUserInfo( bool &needToSave,
                           BOOL &isTarget,
                           char *username, char *password );
    void    ResetUserInfo( bool &needToSave,
                           BOOL &isTarget,
                           char *filename );

    /* ���[�U���A�p�X���[�h�̐ݒ� */
    void    SetBookeyInfo();

    /* �\�� */
    void    SetWindowText( CString &username,
                           CString &password,
                           CEdit   *editUsername,
                           CEdit   *editPassword );
    void    SetWindowText( CString &username,
                           CEdit   *editUsername );

    /* �₢���킹 */
    int     InquiryToUseService();
    bool    InquiryUserInfo( CString bookmark1, CString bookmark2, 
                             CString txt );

    /* �u�b�N�}�[�N�̃C���|�[�g */
    void    ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction );
    void    ImportFromAnotherToOne(
                const MyClip     *myAnother, int numOfAnother,
                const MyClip     *myOne,     int numOfOne,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg );

    /* �u�b�N�}�[�N�̃G�N�X�|�[�g */
    bool    ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2);
    bool    ExportFromAnother(
                MyClip **myAnother, int *numOfAnother );

    /* �u�b�N�}�[�N�̍폜 */
    void    DeleteBookmarks(
                const char       *username,
                const char       *password,
                const char       *username2,
                const char       *password2,
                AUTH_TYPE        authType,
                bool             withQuery = true,
                ProceedingDialog *dlg      = NULL );
    void    DeleteBookmarks( bool deleteAll, bool deleteInteractive );

    /* �u�b�N�}�[�N�̓o�^ */
    void    PutBookmarks( const MyClip     *myBookmark,
                          int              numOfMyBookmarks,
                          const char       *username,
                          const char       *password,
                          ProceedingDialog *pDlg );
    void    PutBookmarks( const MyClip     *myBookmark,
                          ProceedingDialog *pDlg,
                          bool             useOrigText = false );
    void    PutBookmarks( const MyClip *myBookmark,
                          int          numOfMyBookmarks,
                          const char   *username = NULL,
                          const char   *password = NULL );
    void    PutBookmarks( const MyClip *myBookmark,
                          int          numOfMyBookmarks,
                          const char   *bookmarkNameAsImport,
                          bool         &result );

    void    PutBookmarks( bool         force,
                          const MyClip *myBookmark,
                          int          numOfMyBookmarks,
                          const char   *username = NULL,
                          const char   *password = NULL );


    /* �u�b�N�}�[�N�̎擾 */
    MyClip  *GetBookmarks( int        &numOfMyBookmarks,
                           const char *username = NULL,
                           const char *password = NULL );
    MyClip  *GetBookmarks( int        *numOfMyBookmarks,
                           const char *username = NULL,
                           const char *password = NULL ) {
        MyClip  *p  = NULL;
        int     num = 0;
        p = GetBookmarks( num, username, password );
        *numOfMyBookmarks = num;
        return ( p );
    }
    MyClip  *GetBookmarks( int  &numOfMyBookmarks,
                           bool &result );

    /* �^�O�ꗗ�̎擾 */
    TagList *GetTagList( int &numOfTags );

    /* �^�O�̍폜 */
    void    DeleteTag( const char *tag );

    /* �^�O�̒u�� */
    void    ReplaceTag( const char *oldTag, const char *newTag );

    /* �F�ؕ��@ */
    AUTH_TYPE   GetAuthType() { return (m_authType); }
    void    SetAuthType( AUTH_TYPE authType ) {
                m_authType = authType;
            }

    /* �����ݒ�t�@�C���֘A */
    bool    EvalKeys(
                const char          *p,      // (I) �ݒ�f�[�^�擾�Ώە�����
                const unsigned char *secret);// (I) �����ɕK�v�ȏ��(�閧��)
    bool    CheckKeys(
                const char          *p,      // (I) �ݒ�f�[�^�擾�Ώە�����
                const unsigned char *secret, // (I) �����ɕK�v�ȏ��(�閧��)
                bool                &ret );  // (O) �����ۏ؉�
    void    WriteKeys(
                FILE          *fp,      // (I/O) �����o����
                char          *key,     // (I)   ���J��
                unsigned char **secret, // (I/O) �����ɕK�v�ȏ��(�閧��)
                bool          &done );  // (O)   �Í����������s�ς݂��ۂ�

    /* �u�b�N�}�[�N�o��(�G�N�X�|�[�g)���̓���(�C���|�[�g)���̕����R�[�h���擾 */
    int GetChangeCode( CString bookmarkNameAsImport );

    /* �e�퉉�Z�q */
    operator bool()                 { return (m_isTarget); }
    bool operator=  ( bool value )  { m_isTarget = value;
                                      return (m_isTarget); }
    operator const char *()         { return ((const char *)m_bmName); }

    CString             m_username;     // ���[�U��
    CString             m_password;     // �p�X���[�h
    CString             m_username2;    // ���[�U�� (�\��)
    CString             m_password2;    // �p�X���[�h (�\��)
    CString             m_blogID;       // ���e�� Blog ID �܂��� group
    CString             m_blogName;     // ���e�� Blog �܂��� group �̖��O
    CString             m_opmlFilename; // ���[�J��OPML�t�@�C����
    CString             m_apiKey;       // API�L�[ / OAuth access token
    CString             m_secret;       // OAuth access token secret
    bool                m_useMyTitle;   // �u�b�N�}�[�N�o�^���A�����Őݒ肵��
                                        // ���Ƃ��Ă���^�C�g����D��I�ɓK�p
                                        // ���邩�ۂ� (���҂ɂ���Đݒ�ς݂�
                                        // �^�C�g�����󂯓���邩�ۂ�)

private:
    bool                m_isTarget; // �o�^�ΏۂƂ��邩�ۂ�
    enum bookmarkType   m_bmType;   // �u�b�N�}�[�N���
    AUTH_TYPE           m_authType; // �F�؎��
    CString             m_bmName;   // �u�b�N�}�[�N�T�[�r�X��
    CString             m_bmSymbol; // �u�b�N�}�[�N�T�[�r�X���ے����閼�O

protected:
    CString m_tgt_hatenaBookmark;
    CString m_tgt_delicious;
    CString m_tgt_mmMemo;
    CString m_tgt_drecomRSS;
    CString m_tgt_flog;
    CString m_tgt_livedoorClip;
    CString m_tgt_ecNaviClip;
    CString m_tgt_niftyClip;
    CString m_tgt_1470net;
    CString m_tgt_pookmark;
    CString m_tgt_blueDot;
    CString m_tgt_joltMark;
    CString m_tgt_fc2bookmark;
    CString m_tgt_blogPet;
    CString m_tgt_yjBookmark;
    CString m_tgt_yahooBookmarks;
    CString m_tgt_diigo;
    CString m_tgt_hatenaFeed;
    CString m_tgt_deliciousXML;

private:
    CUserInfo operator= ( CUserInfo &u ) {
        m_username     = u.m_username;
        m_password     = u.m_password;
        m_username2    = u.m_username2;
        m_password2    = u.m_password2;
        m_opmlFilename = u.m_opmlFilename;
        m_useMyTitle   = u.m_useMyTitle;
        m_isTarget     = u.m_isTarget;
        m_bmType       = u.m_bmType;
        m_authType     = u.m_authType;
        m_bmName       = u.m_bmName;
        m_bmSymbol     = u.m_bmSymbol;

        return ( *this );
    }

    CUserInfo( CUserInfo &info ) {
        m_username     = info.m_username;
        m_password     = info.m_password;
        m_username2    = info.m_username2;
        m_password2    = info.m_password2;
        m_opmlFilename = info.m_opmlFilename;
        m_useMyTitle   = info.m_useMyTitle;
        m_isTarget     = info.m_isTarget;
        m_bmType       = info.m_bmType;
        m_authType     = info.m_authType;
        m_bmName       = info.m_bmName;
        m_bmSymbol     = info.m_bmSymbol;
    }
};

#endif  /* __CUSER_INFO_H__ */

/*
 * RBparam.h : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      RBparam �\���̂̒�`
 *          written by H.Tsujimura  29 Sep 2005, 27 Dec 2006
 *
 * $Log: /comm/bookey/RBparam.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 13    09/05/28 22:13 Tsujimura543
 * ����A�J�E���g�ŕ��� tumbleblog ���J�݂��Ă���ꍇ�̓��e��
 * tumbleblog ���w�肵�Ă̓��e���\�ɂ���
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 12    09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 11    08/11/05 18:14 Tsujimura543
 * RBuser_t �\���̂� apiKey �����o��ǉ�
 * 
 * 10    08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 9     08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 8     07/10/31 17:14 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 7     07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 6     07/05/23 16:11 Tsujimura543
 * Timelog �ւ̓o�^(����)�ɑΉ�
 * 
 * 5     07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 4     07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 3     07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 2     07/02/16 13:58 Tsujimura543
 * RBuser_t �\���̂� useMyTitle �����o��ǉ�
 * 
 * 1     06/12/27 11:47 Tsujimura543
 * RBparam �\���̂̒�`�� bookey.h ���番���Ɨ������� RBparam.h �Ƃ���
 */

#ifndef __RB_PARAM_H__
#define __RB_PARAM_H__

// �u�b�N�}�[�N�o�^�X���b�h(����� EditBookmarkDialog �_�C�A���O)�ɓn��
// �p�����[�^�i�[�p�\����

typedef struct RBuserInfo {
    BOOL        isTarget;           /* �o�^�Ώۂ��ۂ�                       */
    BOOL        useMyTitle;         /* �^�C�g����Ǝ��ɐݒ肷�邩�ۂ�       */
    char        username[32];       /* for ���C���F��                       */
    char        password[32];       /* for ���C���F��                       */
    char        username2[32];      /* for �\���F��                         */
    char        password2[32];      /* for �\���F��                         */
    char        apiKey[MAX_KEYLENGTH + 1]; /* API�L�[ / OAuth access token  */
    char        secret[MAX_KEYLENGTH + 1]; /* OAuth access token secret     */
    char        blogID[MAX_URLLENGTH + 1]; /* ���e�Ώ� Blog ID �܂��� group */
    char        filename[MAX_PATH]; /* ���[�J��OPML�t�@�C����               */
    AUTH_TYPE   authType;           /* �F�؎��                             */
}   RBuser_t;

typedef struct RBparam {
    RBuser_t            hatena;
    RBuser_t            delicious;
    RBuser_t            mmMemo;
    RBuser_t            drecomRss;
    RBuser_t            flog;
    RBuser_t            livedoorClip;
    RBuser_t            ecNaviClip;
    RBuser_t            niftyClip;
    RBuser_t            next1470net;
    RBuser_t            newsing;
    RBuser_t            pookmark;
    RBuser_t            blueDot;
    RBuser_t            joltMark;
    RBuser_t            fc2bookmark;
    RBuser_t            blogPet;
    RBuser_t            twitter;
    RBuser_t            yjBookmark;
    RBuser_t            yahooBookmarks;
    RBuser_t            timelog;
    RBuser_t            digg;
    RBuser_t            tumblr;
    RBuser_t            diigo;
    RBuser_t            localOpml;
    char                url[MAX_URLLENGTH];
    BOOL                useTagSuggestion;
    BOOL                useUsers;
    BOOL                active;
    ProceedingDialog    *procDialog;
}   RBparam_t;


// �u�b�N�}�[�N�o�^�X���b�h
UINT
RegisterBookmark( LPVOID pParam );

#endif  /*__RB_PARAM_H__ */

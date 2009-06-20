/*
 * clip saver <<getDrecomRSS>>
 *
 *      �h���R��RSS-Clip �� OPML �ϊ��o�̓v���O����
 *          written by H.Tsujimura  1 Sep 2006
 *
 * $Log: /comm/bookey/getDrecomRSS.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 7     08/07/26 0:32 Tsujimura543
 * decodeContents() �̃v���g�^�C�v�錾�� myClip.h �ֈړ�
 * 
 * 6     07/02/15 0:29 Tsujimura543
 * getArticleIDbyURL() �� getArticleIDbyURLonDrecomRSS() �ɖ��̕ύX
 * 
 * 5     07/02/05 21:40 Tsujimura543
 * getArticleIDbyURL() �̈�����ǉ��B�t�H���_�ԍ����킩���Ă���ꍇ��
 * �L��ID�̔����ɗv���鎞�Ԃ�Z�k�ł���悤�ɂȂ���
 * 
 * 4     07/02/05 17:55 Tsujimura543
 * getArticleIDbyURL() �� editDrecomRSS() ������
 * 
 * 3     06/09/04 19:25 Tsujimura543
 * ��d�C���N���[�h�h�~�p�̋L�q��ǉ�
 * 
 * 2     06/09/01 19:48 Tsujimura543
 * �R�����g���L��
 * 
 * 1     06/09/01 18:53 Tsujimura543
 * �ŏ��̔� (getDrecomRSS.c �� DeleteDrecomRSS.cpp �̋��ʕ������w�b�_
 * �t�@�C����)
 */

#ifndef __GET_DRECOM_RSS_H__
#define __GET_DRECOM_RSS_H__

/* �X���b�h���[�J���i�[�̈� (TLS stands for "Thread Local Storage", but not */
/*             neither "Transport Layer Security" nor "True Love Story" :-) */
#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

#define MAX_DRECOM_RSS_PER_BLOCK    200 /* �u���b�N�P�ʂł̃������ꊇ�擾�� */
                                        /* �� 1�u���b�N������̔z���     */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  �h���R��RSS�� Clip! �̃t�H���_�ꗗ
 */
typedef struct folderListOnDrecomRSS  {
    int     folderNumber;   /* �t�H���_�ԍ� */
    char    folderName[80]; /* �t�H���_��   */
}   FOLDER_LIST;


/*
 *  �h���R��RSS�� Clip! �֘A���ʊ֐�
 *      �E�h���R��RSS �� Clip! �̑���(�N���b�v�̈ꗗ�擾�E�ڍ׎擾�E�ҏW�E��
 *        ���A�t�H���_�̍쐬�E�폜)�́A�����Ƃ��Ă� JSON-RPC API �o�R�ōs�Ȃ�
 *      �EJSON-RPC API �����s����ɂ� objectID ���K�v�ł���
 *      �EobjectID �� �h���R��RSS �� logon ��A�N���b�v���[�_�[�ɃA�N�Z�X����
 *        ���������ɐ�������
 *      �E�t�H���_�ꗗ�́A�N���b�v���[�_�[�̃g�b�v�y�[�W�� html �\�[�X����͂�
 *        �邱�Ƃœ����邽�߁A�t�H���_�ꗗ�̎擾�ɂ������Ă� JSON-RPC API ��
 *        ���s(objectID)�͕K�v�Ȃ�
 */

/* objectID �̐����E�o�^ */
BOOL
setObjectID(
        char *objectID, /* (O)   ����(��A�o�^�����{)���� objectID */
        char *cookie    /* (I/O) �N�b�L�[                          */
    );

/* �t�H���_���ɑΉ�����(���̃\�[�V�����u�b�N�}�[�N�ł����Ƃ����)�^�O���擾 */
void
getTagByName(
        char       *tag,        /* (O) �^�O       */
        const char *folderName  /* (I) �t�H���_�� */
    );

/* �t�H���_�ꗗ�̎擾 */
FOLDER_LIST *
getFolderList(
        const char *htmlSrc,        /* (I) �N���b�v���[�_�[�̃g�b�v�y�[�W�� */
                                    /*     html �\�[�X                      */
        int        *numOfFolders    /* (O) �t�H���_�̐�                     */
    );

/* �w��t�H���_�̎w��N�̃N���b�v�ꗗ�̎擾 */
char    *
getArticleList(
        int        folderNumber,    /* (I)   �擾�Ώہu�t�H���_�ԍ��v    */
        int        year,            /* (I)   �擾�Ώہu�N�v              */
        int        page,            /* (I)   �擾�Ώہu�y�[�W�ԍ��v      */
        const char *objectID,       /* (I)   objectID                    */
        char       *response,       /* (I/O) JSON-RPC API ���s���ʊi�[�p */
        size_t     sz,              /* (I)   response �̎����̈�̃T�C�Y */
        char       *cookie          /* (I/O) �N�b�L�[                    */
    );

/* �w��N���b�v�̓��e�̎擾 */
char    *
getArticleDetail(
        const char *articleID,  /* (I)   �擾�Ώۂ̃N���b�v�� ID     */
        const char *objectID,   /* (I)   objectID                    */
        char       *response,   /* (I/O) JSON-RPC API ���s���ʊi�[�p */
        size_t     sz,          /* (I)   response �̎����̈�̃T�C�Y */
        char       *cookie      /* (I/O) �N�b�L�[                    */
    );

/* �w��URL�̃h���R��RSS�N���b�v���[�_�[���L��ID�̎擾 */
BOOL
getArticleIDbyURLonDrecomRSS(
        const char *url,        /* (I)   �����Ώ�URL */
        long       folderNumber,/* (I) �t�H���_�ԍ�  */
        char       *cookie,     /* (I/O) �N�b�L�[    */
        char       *articleID   /* (O)   �L��ID      */
    );

/* �w��L��ID�̓o�^���e�̕ҏW */
BOOL
editDrecomRSS(
        const MyClip *mp,           /* (I)   �ҏW���e       */
        const char   *articleID,    /* (I)   �ҏW�ΏۋL��ID */
        char         *cookie,       /* (I/O) �N�b�L�[       */
        char         *errorString   /* (O)   �G���[���     */
    );

#ifdef __cplusplus
}
#endif

#endif  /* __GET_DRECOM_RSS_H__ */

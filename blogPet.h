/*
 * blogPet.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �uBlogPet �C�ɂȂ�L���v�֘A�̊֐��Q
 *          written by H.Tsujimura  22 Dec 2006 / 14 Feb 2007
 *
 * $Log: /comm/bookey/blogPet.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     07/07/13 2:01 Tsujimura543
 * 2007�N7��12���Ɏ��{���ꂽ BlogPet ���j���[�A���ɑΉ�
 * 
 * 4     07/02/15 0:25 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 3     07/02/14 23:24 Tsujimura543
 * getArticleIDbyURLonBlogPet(), editBogPet(), confirmPostBlogpet() ��
 * �v���g�^�C�v�錾�� blogPet.h �ֈړ�
 * 
 * 2     07/02/14 23:13 Tsujimura543
 * _getBlogPet() �̃v���g�^�C�v�錾�� blogPet.h �ֈړ�
 * 
 * 1     07/02/14 23:10 Tsujimura543
 * encodeURLe() �̃v���g�^�C�v�錾�� blogPet.h �ֈړ�
 */

#ifndef __BLOGPET_H__
#define __BLOGPET_H__

/* 0x80 �ȏ�̒l�̕����R�[�h�݂̂��p�[�Z���g�G���R�[�h���� */
char    *
encodeURLe( const char *p );


/* BlogPet�C�ɂȂ�L���ɓo�^�ς݂̃u�b�N�}�[�N���̎擾 */
int
_getBlogPet(
        const char *userID,
        char       *cookie,
        MyClip     **mp,
        MyClipEx   **mpEx,
        char       *response,
        size_t     sz
    );


/* �w��URL��BlogPet�C�ɂȂ�L�����L��ID�̎擾 */
BOOL
getArticleIDbyURLonBlogPet(
        const char *targetURL,  /* (I)   �����Ώ�URL */
        char       *cookie,     /* (I/O) �N�b�L�[    */
        char       *articleID   /* (O)   �L��ID      */
    );

/* �w��L��ID�̓o�^���e�̕ҏW */
BOOL
editBlogPet(
        const MyClip *mp,           /* (I)   �ҏW���e       */
        const char   *articleID,    /* (I)   �ҏW�ΏۋL��ID */
        char         *cookie,       /* (I/O) �N�b�L�[       */
        char         *errorString   /* (O)   �G���[���     */
    );

/* BlogPet�C�ɂȂ�L���Ƀu�b�N�}�[�N��o�^(�o�^�m�F) */
BOOL
confirmPostBlogPet(
        const MyClip *mp,
        const char   *tmpTitle,
        const char   *tmpBody,
        const char   *articleID,
        char         *errorString,
        char         *request,
        char         *response,
        size_t       sz,
        char         *cookie
    );


void
getTitleWithoutRate( const char *title, char *titleWithoutRate );

void
setUrlOnRequest( const char *url, char *request );

void
setTitleOnRequest( const char *title, char *request );

void
setBodyOnRequest( const char *body, char *request );

void
setTagsOnRequest( const char *tags, char *request );

void
setPolicyOnRequest( int publication, char *request );

void
setCommentOnRequest( const char *comment, char *request );


#define BLOGPET_TEMP_TITLE_LEN  2048

#endif  /* __BLOGPET_H__ */

/*
 * niftyClip.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�j�t�e�B�N���b�v�v�֘A�̊֐��Q
 *          written by H.Tsujimura  7 Jul 2006 / 17 Mar 2008
 *
 * $Log: /comm/bookey/niftyClip.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/11/11 16:41 Tsujimura543
 * NUM_OF_INFO_PER_NIFTY_API �̒�`�� niftyClip.h �ֈړ�
 * 
 * 3     08/11/11 16:17 Tsujimura543
 * _getNiftyClipWithApiKey() ��ǉ�
 * 
 * 2     08/03/17 17:59 Tsujimura543
 * �R�����g(�����̐���)���C��
 * 
 * 1     08/03/17 17:57 Tsujimura543
 * ���܂Ńj�t�e�B�N���b�v�֘A�̊e�\�[�X�t�@�C�����ŕʁX�ɐ錾���Ă���
 * �v���g�^�C�v�錾�����ʂ̃w�b�_�t�@�C���ɏW�񂵂�
 */

#ifndef __NIFTY_CLIP_H__
#define __NIFTY_CLIP_H__

#ifdef __cplusplus
extern "C" {
#endif

char    *
getScreenNameOnNiftyClip(
        char   *screenname, // (O)   �X�N���[����
        char   *targetURL,  // (O)   ���O�C�������[�U�̃N���b�v�̃g�b�v�y�[�W
        char   *response,   // (I/O) ��M�d���i�[�̈�
        size_t sz,          // (I)   ��M�d���i�[�̈�T�C�Y
        char   *cookie      // (I/O) �N�b�L�[
    );

int
_getNiftyClip(
        const char *target,  // (I)   ���[�U�̃N���b�v�̃g�b�v�y�[�W
        const char *userName,// (I)   ���[�U���܂��̓X�N���[����
        char       *cookie,  // (I/O) �N�b�L�[
        MyClip     **mp,     // (I/O) �u�b�N�}�[�N��� (for �擾�n)
        MyClipEx   **mpEx,   // (I/O) �u�b�N�}�[�N��� (for �폜�n)
        char       *response,// (I/O) ��M�d���i�[�̈�
        size_t     sz,       // (I)   ��M�d���i�[�̈�T�C�Y
        int        *total    // (O)   �N���b�v��
    );

int
_getNiftyClipWithApiKey(
        const char *apiKey,     /* (I) API�L�[                      */
        long       offset,      /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long       *numOfPosts, /* (I) �擾����u�b�N�}�[�N�̐�     */
                                /* (O) �擾�����u�b�N�}�[�N�̐�     */
        MyClip     *posts,      /* (O) �擾�����u�b�N�}�[�N         */
        BOOL       *more        /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    );

#define NUM_OF_INFO_PER_NIFTY_API   100  /* 1���API���s�Ŏ擾������ */

#ifdef __cplusplus
}
#endif

#endif  /* __NIFTY_CLIP_H__ */

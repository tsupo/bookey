/*
 * tumblr.h : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      tumblr �֘A �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  29 May 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/tumblr.h $
 * 
 * 1     09/05/29 8:31 tsupo
 * VSS�T�[�o���_��ύX
 * 
 * 1     09/05/29 0:14 Tsujimura543
 * �ŏ��̔� (BloGolEe�����ɍ쐬�����\�[�X�𗬗p)
 */

#ifndef __TUMBLR_H__
#define __TUMBLR_H__

#ifdef __cplusplus
extern "C" {
#endif
int
getBlogIDsTumblr(
    const char *userName,       // (I) ���[�U�� (���[���A�h���X)
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾����/�擾���� blog ���̐�
    BLOGINF    *blogInfo );     // (O) �擾���� blog ���
#ifdef __cplusplus
}
#endif

#endif  /* __TUMBLR_H__ */

/*
 * twitStar.h : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �������֘A �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  24 Aug 2007 / 27 Aug 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/twitStar.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 1     07/08/27 20:51 Tsujimura543
 * Chirrup �p�ɍ쐬�����\�[�X����荞�݂Abookey �p�ɃA�����W
 * 
 * ------------------------------------------------------------------------
 * �ȉ��́Achirrup/twitStar.h �̕ύX����
 * ------------------------------------------------------------------------
 * 1     07/08/24 22:29 Tsujimura543
 * �ŏ��̔�
 */

#ifndef __TWIT_STAR_H__
#define __TWIT_STAR_H__

// targetURL �Ŏw�肵��Web�y�[�W�� �� ������
BOOL
setHatenaStar( const char *targetURL,   // (I) ����������Web�y�[�WURL
               const char *username,    // (I) �͂Ă�ID
               const char *password );  // (I) �p�X���[�h

// targetURL �Ŏw�肵��Web�y�[�W�� �� �𐔂���
long
getHatenaStar( const char *targetURL ); // (I) ���̐��𒲂ׂ���Web�y�[�WURL

#endif  /* __TWIT_STAR_H__ */

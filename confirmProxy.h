/*
 * confirmProxy.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      proxy���ݒ�m�F���� �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/confirmProxy.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 2     07/03/14 17:38 Tsujimura543
 * checkProxyInfo() ������
 * 
 * 1     07/03/14 16:22 Tsujimura543
 * (1) �u�u���O�N���C�A���g BloGolEe�v�p�ɏ������\�[�X����荞��
 * (2) �o�C�����K���Ή�
 * =======================================================================
 * 3     07/03/10 5:22 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ����Ă݂�
 * 
 * 2     07/03/09 21:21 Tsujimura543
 * checkProxyInfo() ��ǉ�
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#ifndef __CONFIRM_PROXY_INFO_H__
#define __CONFIRM_PROXY_INFO_H__

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword );

void    initProxyInfo();
bool    checkProxyInfo();

#define syncProxyInfo   initProxyInfo

#endif  /* __CONFIRM_PROXY_INFO_H__ */

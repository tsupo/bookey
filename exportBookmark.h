/*
 * exportBookmark.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N���G�N�X�|�[�g����֐��Q
 *          written by H.Tsujimura  6 Jun 2005
 *
 * $Log: /comm/bookey/exportBookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 3     06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 2     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 1     06/06/06 22:24 Tsujimura543
 * �V�K�쐬 (CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��)
 */

#ifndef __EXPORT_BOOKMARK_H__
#define __EXPORT_BOOKMARK_H__

bool    ExportFromHatena(
                CString username,
                CString password,
                MyClip  **myHatena,
                int     *numOfHatenaBookmarks
            );

bool    ExportFromDelicious(
                CString username,
                CString password,
                MyClip  **myDelicious,
                int     *numOfDelicious
            );

bool    ExportFromBlueDot(
                CString username,
                CString password,
                MyClip  **myDelicious,
                int     *numOfDelicious
            );

bool    ExportFromMMmemo(
                CString username,
                CString password,
                MyClip  **myMMmemo,
                int     *numOfMMmemo
            );

#endif  /* __EXPORT_BOOKMARK_H__ */

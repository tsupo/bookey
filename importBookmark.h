/*
 * importBookmark.h  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      �u�b�N�}�[�N���C���|�[�g����֐��Q
 *          written by H.Tsujimura  6 Jun 2005
 *
 * $Log: /comm/bookey/importBookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
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

#ifndef __IMPORT_BOOKMARK_H__
#define __IMPORT_BOOKMARK_H__


void    ImportFromAnotherToHatena(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myHatena,
                int              numOfHatenaBookmarks,
                const char       *usernameForHatena,
                const char       *passwordForHatena,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            );

void    ImportFromAnotherToDelicious(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myDelicious,
                int              numOfDelicious,
                const char       *usernameForDelicious,
                const char       *passwordForDelicious,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            );

void    ImportFromAnotherToBlueDot(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myDelicious,
                int              numOfDelicious,
                const char       *usernameForDelicious,
                const char       *passwordForDelicious,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            );

void    ImportFromAnotherToMMmemo(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myMMmemo,
                int              numOfMMmemo,
                const char       *usernameForMMmemo,
                const char       *passwordForMMmemo,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            );

void    ImportFromAnotherToBPtags(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myBPtags,
                int              numOfBPtags,
                const char       *usernameForBPtags,
                const char       *passwordForBPtags,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            );

#endif  /* __IMPORT_BOOKMARK_H__ */

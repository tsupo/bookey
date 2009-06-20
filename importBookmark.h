/*
 * importBookmark.h  : ソーシャルブックマーク管理プログラム
 *      ブックマークをインポートする関数群
 *          written by H.Tsujimura  6 Jun 2005
 *
 * $Log: /comm/bookey/importBookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 2     06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 1     06/06/06 22:24 Tsujimura543
 * 新規作成 (CUserInfo 導入によるリファクタリング第2段階、終了)
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

/*
 * exportBookmark.h  : ソーシャルブックマーク管理プログラム
 *      ブックマークをエクスポートする関数群
 *          written by H.Tsujimura  6 Jun 2005
 *
 * $Log: /comm/bookey/exportBookmark.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
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

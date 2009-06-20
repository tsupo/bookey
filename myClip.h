/*
 *  ブックマーク吸出し、登録ツール 共通ヘッダファイル
 *          written by H.Tsujimura  17 Jan 2005 / 26 Sep 2005
 *
 * $Log: /comm/bookey/myClip.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 131   09/05/28 22:13 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 130   09/05/27 19:40 Tsujimura543
 * setSigInfo() を削除 (xmlRPC.dll へ移管)
 * 
 * 129   09/05/27 17:08 Tsujimura543
 * setSigInfo() の引数を追加
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 128   09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 127   09/04/01 17:47 Tsujimura543
 * setSigInfo() を追加
 * 
 * 126   09/02/24 16:26 Tsujimura543
 * タグ候補抽出処理群の引数を各々追加
 * 
 * 125   08/11/11 16:19 Tsujimura543
 * 「APIキーを使用して@niftyクリップから取得する」処理を追加
 * 
 * 124   08/11/05 19:48 Tsujimura543
 * 「APIキーを使用して@niftyクリップへ登録する」処理を追加、動作確認した
 * 
 * 123   08/11/04 16:45 Tsujimura543
 * getApiKeyOnNiftyClip() を追加
 * 
 * 122   08/11/04 12:25 Tsujimura543
 * getUsersOfNiftyClip() を追加
 * 
 * 121   08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 120   08/07/28 15:28 Tsujimura543
 * getApiKeyOnLivedoorClip() を追加
 * 
 * 119   08/07/26 0:45 Tsujimura543
 * encodeContents()、decodeContents() のプロトタイプ宣言を
 * myClip.h へ集約
 * 
 * 118   08/07/25 20:33 Tsujimura543
 * Diigo 対応
 * 
 * 117   08/02/14 19:41 Tsujimura543
 * replaceString() を getFlog.c および putTumblr.c から移動
 * 
 * 116   07/11/12 21:56 Tsujimura543
 * adjustStringLength() を putLocalOpml.c, putMMmemo.c から移管
 * 
 * 115   07/11/12 19:03 Tsujimura543
 * any2sjisEx() を追加
 * 
 * 114   07/10/31 18:42 Tsujimura543
 * putTumblr() に引数(version)を追加
 * 
 * 113   07/10/31 17:14 Tsujimura543
 * tumblr に対応
 * 
 * 112   07/10/11 22:23 Tsujimura543
 * Yahoo! Japan の ID で newsing を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 111   07/10/10 22:38 Tsujimura543
 * 画像を取得するのに cookie が必要な場合(今のところ、diggのみ)に対応
 * 
 * 110   07/10/05 2:42 Tsujimura543
 * BBAuth 対応関連の各種修正を実施
 * 
 * 109   07/09/13 22:29 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 108   07/09/05 18:58 Tsujimura543
 * UserAgent 回りをリファクタリング
 * 
 * 107   07/09/05 1:50 Tsujimura543
 * getUsersOfMMmemo() と extractTags() に各々第2引数を追加
 * (stat1470netを引数化)
 * 
 * 106   07/07/10 19:34 Tsujimura543
 * inputCaptchaString() の引数追加とそれに伴う各種変更(その2)
 * 
 * 105   07/07/10 1:01 Tsujimura543
 * inputCaptchaString() の引数追加とそれに伴う各種変更
 * 
 * 104   07/07/09 21:49 Tsujimura543
 * inputCaptchaString() の引数を追加
 * 
 * 103   07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 102   07/07/09 18:35 Tsujimura543
 * getUsersOfDigg() を追加
 * 
 * 101   07/05/23 16:11 Tsujimura543
 * Timelog への登録(発言)に対応
 * 
 * 100   07/05/11 19:10 Tsujimura543
 * Twitter に送る bookey の版数をリソースから取得したものを使うように
 * してみた
 * 
 * 99    07/04/20 20:34 Tsujimura543
 * Yahoo! ブックマーク、Yahoo! Bookmarks のインポートとエクスポートに対応
 * 
 * 98    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 97    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 96    07/04/16 17:59 Tsujimura543
 * del.icio.us の posts/all 形式の XML ファイルのインポートとエクスポート
 * に対応した
 * 
 * 95    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 94    07/03/29 17:55 Tsujimura543
 * loginFC2Bookmark() の引数を2つ追加
 * 
 * 93    07/03/01 21:36 Tsujimura543
 * getUsersOfLivedoorClip() を追加
 * 
 * 92    07/02/22 18:33 Tsujimura543
 * any2sjis() を追加
 * 
 * 91    07/02/16 16:35 Tsujimura543
 * コメントを修正
 * 
 * 90    07/02/16 16:22 Tsujimura543
 * はてなブックマーク、Buzzurl、BlogPet気になる記事に関して、タイトルを上
 * 書きするかどうか選択(指定)できるようにした
 * 
 * 89    07/02/14 23:46 Tsujimura543
 * struct myClip のメンバ publication の型を BOOL から int に変更
 * 
 * 88    07/02/02 23:36 Tsujimura543
 * getTitle() の引数を追加
 * 
 * 87    07/01/30 19:21 Tsujimura543
 * タグの一覧取得、タグの削除、タグの置換に関連する関数のプロトタイプ宣言
 * を追加
 * 
 * 86    07/01/29 17:50 Tsujimura543
 * TagList 構造体を用意した
 * 
 * 85    07/01/19 15:37 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 84    07/01/18 22:41 Tsujimura543
 * getValue() のプロトタイプ宣言を追加
 * 
 * 83    07/01/18 16:57 Tsujimura543
 * putBookmarks() のプロトタイプ宣言を追加
 * 
 * 82    07/01/18 15:08 Tsujimura543
 * decodeString() のプロトタイプ宣言を削除
 * 
 * 81    07/01/18 14:55 Tsujimura543
 * justify() と decodeString() のプロトタイプ宣言を追加
 * 
 * 80    07/01/17 21:41 Tsujimura543
 * deleteHtmlTags() を getBlueDot.c から分離、独立させた
 * 
 * 79    06/12/25 23:37 Tsujimura543
 * loginBlogPet() に第4引数を追加
 * 
 * 78    06/12/25 15:07 Tsujimura543
 * any2euc() を追加
 * 
 * 77    06/12/21 21:19 Tsujimura543
 * JoltMark、FC2BOOKMARK、「BlogPet 気になる記事」に対応
 * 
 * 76    06/12/07 15:56 Tsujimura543
 * getDateTimeFromDateString() のプロトタイプ宣言と解説を追加
 * 
 * 74    06/12/06 19:44 Tsujimura543
 * inputLivedoorFeed() のプロトタイプ宣言を追加
 * 
 * 73    06/12/06 18:55 Tsujimura543
 * 「公開状態」の値を改定した
 * 
 * 72    06/12/06 17:59 Tsujimura543
 * 「公開状態」の値を定義した
 * 
 * 71    06/12/06 17:55 Tsujimura543
 * NETSCAPE_BOOKMARK_FILE_1形式でのブックマーク情報出力時に
 * Shift_JIS での出力も選択できるようにした
 * 
 * 70    06/11/17 15:25 Tsujimura543
 * getEvaluation() に第2引数を追加
 * 
 * 69    06/11/17 14:47 Tsujimura543
 * getEvaluation() を追加
 * 
 * 68    06/11/14 15:53 Tsujimura543
 * chcode() のプロトタイプ宣言を追加
 * 
 * 67    06/11/14 15:44 Tsujimura543
 * unescapeURL() と any2utf() のプロトタイプ宣言を追加
 * 
 * 66    06/11/13 20:37 Tsujimura543
 * MyClip 構造体および MyClipEx 構造体内の Webページ URL 記憶領域の
 * サイズを2倍にした
 * 
 * 65    06/11/10 20:07 Tsujimura543
 * strncmpi() のプロトタイプ宣言を追加
 * 
 * 64    06/11/10 19:26 Tsujimura543
 * ブラウザのブックマークを取り込む/ブラウザに取り込める形式のブックマーク
 * ファイルを生成する機能をサポートするための準備
 * 
 * 63    06/10/26 22:54 Tsujimura543
 * 「ローカルOPML」に対応
 * 
 * 62    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 61    06/10/05 16:32 Tsujimura543
 * POOKMARK Airline 関連のプロトタイプ宣言を追加 (取得処理、削除処理)
 * 
 * 60    06/10/05 16:31 Tsujimura543
 * skipToNextItemWithSeparator() の定義を getNiftyClip.c から移動
 * 
 * 59    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline に対応
 * 
 * 58    06/09/29 18:59 Tsujimura543
 * newsing (の登録)関連のプロトタイプ宣言を追加
 * 
 * 57    06/09/28 21:58 Tsujimura543
 * ブックマーク編集ダイアログでの「評価」設定をサポート
 * 
 * 56    06/09/26 16:11 Tsujimura543
 * MyClip 構造体のメンバを追加 (「評価」機能対応準備)
 * 
 * 55    06/09/22 21:40 Tsujimura543
 * allocateMyClipIfNecessary(), allocateMyClipExIfNecessary() を追加
 * 
 * 54    06/08/25 18:10 Tsujimura543
 * get1470net() のプロトタイプ宣言を変更
 * 
 * 53    06/08/22 17:48 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 52    06/08/22 16:59 Tsujimura543
 * enum authenticationType の定義を myClip.h 内に移した
 * 
 * 51    06/08/22 16:03 Tsujimura543
 * MyClipEx の定義を追加
 * 
 * 50    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 49    06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 48    06/08/18 15:04 Tsujimura543
 * getEcNaviClipUserID() のプロトタイプ宣言を追加
 * 
 * 47    06/07/21 21:09 Tsujimura543
 * ニフティクリップの取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 46    06/07/21 20:51 Tsujimura543
 * ECナビ人気ニュースの取得処理の引数を追加(全何件あるか、取得できるように
 * した)
 * 
 * 45    06/07/21 20:17 Tsujimura543
 * BlogPeople Tags の取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 44    06/07/21 17:48 Tsujimura543
 * livedoorクリップの取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 43    06/07/15 0:56 Tsujimura543
 * 1470.netリニューアル版への「登録」に対応
 * 
 * 42    06/07/12 17:34 Tsujimura543
 * ドリコムRSS(のClip!)の取得、同期に対応
 * 
 * 41    06/07/11 22:49 Tsujimura543
 * ECナビ人気ニュースのブックマーク登録者数も表示するようにした
 * (ブックマーク登録画面/EditBookmarkDialog)
 * 
 * 40    06/07/07 19:34 Tsujimura543
 * ニフティクリップの取得、同期に対応
 * 
 * 39    06/07/06 19:53 Tsujimura543
 * livedoorクリップの取得、同期に対応
 * 
 * 38    06/07/03 13:35 Tsujimura543
 * getNumberOfHatenaBookmark() を追加
 * 
 * 37    06/06/30 19:43 Tsujimura543
 * ECナビ人気ニュースの取得、同期に対応
 * 
 * 36    06/06/29 19:04 Tsujimura543
 * loginNifty() を loginNiftyClip() に名称変更
 * 
 * 35    06/06/29 18:47 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 34    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 33    06/06/28 15:54 Tsujimura543
 * ブックマーク登録者数を調べて表示する機能を追加
 * 
 * 32    06/06/23 17:06 Tsujimura543
 * getFlog() を追加
 * 
 * 31    06/06/20 16:29 Tsujimura543
 * isWhiteSpace() を myClip.h へ移動
 * 
 * 30    06/06/20 16:25 Tsujimura543
 * iskanji1(), iskanji2() を myClip.h へ移動
 * 
 * 29    06/06/19 20:25 Tsujimura543
 * getBPhash() のプロトタイプ宣言を bookey.h から myClip.h へ移す
 * 
 * 28    06/05/31 21:11 Tsujimura543
 * loginFlog() と putFlog() を追加
 * 
 * 27    06/05/24 16:21 Tsujimura543
 * getASIN() を追加
 * 
 * 26    06/05/23 14:08 Tsujimura543
 * getTitle() の注意書き(コメント)を追加
 * 
 * 25    06/05/23 13:53 Tsujimura543
 * getTitle() と extractTags() の連携による「はてなブックマーク」からの
 * タグ候補取得をサポート
 * 
 * 24    06/04/06 22:16 Tsujimura543
 * はてなブックマークの「コレクション」への追加に対応
 * 
 * 23    06/03/28 17:04 Tsujimura543
 * loginDrecomRSS() のプロトタイプ宣言を追加
 * 
 * 22    06/03/28 16:28 Tsujimura543
 * putDrecomRSS() を追加
 * 
 * 21    06/02/17 21:00 Tsujimura543
 * getUsernameForBlogPeopleTags() のプロトタイプ宣言を追加
 * 
 * 20    05/11/30 23:43 Tsujimura543
 * extractTags() の第3引数を (I) から (I/O) へ変更
 * 
 * 19    05/11/30 23:27 Tsujimura543
 * extractTags() を追加
 * 
 * 18    05/11/30 14:32 Tsujimura543
 * はてなブックマークのタグが3個まで→10個まで、コメントが50文字まで→
 * 100文字までに各々変更されたのに伴う修正を実施
 * 
 * 17    05/11/02 13:51 Tsujimura543
 * getStringImplanted() のプロトタイプ宣言を追加
 * 
 * 16    05/10/24 17:37 Tsujimura543
 * getTitle() を Account-auto-discovery に対応するよう拡張した
 * 
 * 15    05/10/20 20:07 Tsujimura543
 * putMMmemo() を追加
 * 
 * 14    05/10/19 16:47 Tsujimura543
 * loginMMmemo() を追加
 * 
 * 13    05/10/18 21:54 Tsujimura543
 * getMMmemo() を追加
 * 
 * 12    05/10/18 14:32 Tsujimura543
 * putBPT() → putBPTags() に名称変更
 * 
 * 11    05/10/18 14:30 Tsujimura543
 * putBPT() を追加
 * 
 * 10    05/10/18 13:40 Tsujimura543
 * loginBlogPeople() のプロトタイプ宣言を追加
 * 
 * 9     05/10/14 15:09 Tsujimura543
 * getTitle() を追加
 * 
 * 8     05/10/11 18:03 Tsujimura543
 * putDelicious() と putHB() の第3引数に const 修飾子を付加
 * 
 * 7     05/10/03 23:06 Tsujimura543
 * NUM_OF_INFO_PER_HATENA_API の #define を myClip.h に移す
 * 
 * 6     05/10/03 11:59 Tsujimura543
 * tags の領域を 80 → 160 に増やした
 * 
 * 5     05/09/30 17:41 Tsujimura543
 * outputOPML() に引数を追加
 * 
 * 4     05/09/28 23:14 Tsujimura543
 * ブックマーク読み出し、登録各処理のプロトタイプ宣言を追加
 * 
 * 3     05/09/28 14:55 Tsujimura543
 * inputOpml() のプロトタイプ宣言を追加
 * 
 * 2     05/09/28 13:14 Tsujimura543
 * outputOPML() 関連の定義を myClip.h に移動
 * 
 * 1     05/09/28 12:07 Tsujimura543
 * ブックマーク切り出しツールのソースから切り出し(分離独立)
 */

#ifndef __MY_CLIP_H__
#define __MY_CLIP_H__

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif
#include "xmlRPC.h"
#include "delicious.h"

time_t  timelocal( struct tm *tm );

char    *
getTitle(
        const char *url,        /* (I) 当該WebページのURL                  */
        char       *accountName,/* (O) AccountName-auto-discovery で取得し */
                                /*     た当該Webページのオーナーの(はてな) */
                                /*     アカウント名                        */
        char       *hatenaID,   /* (I) はてなID(すでに自分自身で登録済みか */
                                /*     否かのチェックを行なうときに指定)   */
        char       **hatenaTags,/* (O) はてブから取得したタグ候補          */
                                /*     (注意: 本関数内で格納用の領域を確保 */
                                /*      する。本関数の呼び出し元で領域の解 */
                                /*      放を行なうこと)                    */
        BOOL       *posted      /* (O) すでに自分自身で登録済みか否か      */
    );

void
extractTags(
        const char *url,        /* (I)   当該WebページのURL         */
        char       **tags,      /* (O)   タグ候補                   */
        char       **hatenaTags,/* (I/O) はてブから取得したタグ候補 */
        int        *numOfTags,  /* (I/O) タグ候補の数               */
        BOOL       *stat1470net,/* (I/O) 1470.net の稼働状況        */
        const char *yahooAppID  /* (I)   Yahoo! アプリケーションID  */
    );


/* 認証方式 */
typedef enum authenticationType {
    AK_ORIGINAL = 0,        /* 独自認証                         */
    AK_TYPEKEY,             /* TypeKey                          */
    AK_HATENA,              /* はてな認証API                    */
    AK_TYPEKEY_HATENA,      /* TypeKey 優先、はてな認証API 併用 */
    AK_HATENA_TYPEKEY,      /* はてな認証API 優先、TypeKey 併用 */
    AK_JUGEMKEY,            /* JugemKey                         */
    AK_YAHOOJAPAN_BBAUTH,   /* Yahoo! Japan  BBAuth 認証        */
    AK_FLICKR,              /* Flickr                           */
    AK_OAUTH                /* OAuth                            */
}   AUTH_TYPE;


/* ブックマーク情報 */
typedef struct myClip   {
    char    title[MAX_DESCRIPTION_LEN];     /* Webページ 題名            */
    char    url[MAX_URLLENGTH * 2];         /* Webページ URL             */
    char    tags[MAX_DESCRIPTION_LEN];      /* tag (分類)                */
    char    comment[MAX_DESCRIPTION_LEN];   /* コメント                  */
    int     yyyy;                           /* 登録日時 (年)             */
    int     mm;                             /* 登録日時 (月)             */
    int     dd;                             /* 登録日時 (日)             */
    int     HH;                             /* 登録日時 (時)             */
    int     MM;                             /* 登録日時 (分)             */
    int     SS;                             /* 登録日時 (秒)             */
    BOOL    asin;                           /* コレクション              */
    int     publication;                    /* 公開状態 (public/private) */
    int     evaluation;                     /* 評価#1 (5段階 + 未評価)   */
    int     rating;                         /* 評価#2 (3段階)            */
    int     affirmation;                    /* 評価#3 (肯定/否定)        */
}   MyClip;

typedef struct myClipForDelete  {
    char    title[MAX_DESCRIPTION_LEN];   /* 題名                           */
    char    url[MAX_URLLENGTH * 2];       /* ブックマーク済み Webページ URL */
    char    tags[MAX_DESCRIPTION_LEN];    /* tag (分類)                     */
    char    comment[MAX_DESCRIPTION_LEN]; /* コメント                       */
    char    entryID[MAX_BLOGIDLENGTH + 1];/* 削除用対象のエントリID         */
    char    remarks[MAX_KEYLENGTH + 1];   /* 削除用ハッシュキー             */
}   MyClipEx;

typedef struct tagList  {
#define MAX_TAG_LENGTH  512             /* タグ最大長 (暫定値) */
    char    tag[MAX_TAG_LENGTH];        /* tag (分類)          */
}   TagList;

/* 評価#1 */
#define EVL_NONE        0       /* 未評価 */
#define EVL_REQUESTED   (-1)    /* 要評価 */
#define EVL_ONE         1       /* 評価1  */
#define EVL_TWO         2       /* 評価2  */
#define EVL_THREE       3       /* 評価3  */
#define EVL_FOUR        4       /* 評価4  */
#define EVL_FIVE        5       /* 評価5  */

/* 評価#2 */
#define RAT_NONE        0       /* 未評価 */
#define RAT_REQUESTED   (-1)    /* 要評価 */
#define RAT_ONE         1       /* 評価1  */
#define RAT_TWO         2       /* 評価2  */
#define RAT_THREE       3       /* 評価3  */

/* 評価#3 */
#define AFF_NONE        0       /* 未評価 */
#define AFF_REQUESTED   (-1)    /* 要評価 */
#define AFF_GOOD        1       /* ○     */
#define AFF_BAD         2       /* ×     */

/* 公開状態 */
#define PUB_REQUESTED   (-1)    /* 要設定(友人にのみ公開非対応) */
#define PUB_REQUESTED2  (-2)    /* 要設定(友人にのみ公開対応)   */
#define PUB_EVERYONE    0       /* (全員に)公開/パブリック      */
#define PUB_FRIENDS     1       /* 友人にのみ公開               */
#define PUB_PRIVATE     2       /* 非公開/プライベート          */

/* メモリ領域確保処理 */
MyClip  *
allocateMyClipIfNecessary(
        MyClip **mp,        /* (I/O) 確保する/確保済みメモリ領域     */
        int    unit,        /* (I)   1回辺りのメモリ領域割り当て単位 */
        int    *cnt,        /* (I/O) メモリ割り当て実行回数          */
        int    numOfClips   /* (I)   格納済みブックマーク数          */
    );

MyClipEx    *
allocateMyClipExIfNecessary(
        MyClipEx **mp,      /* (I/O) 確保する/確保済みメモリ領域     */
        int      unit,      /* (I)   1回辺りのメモリ領域割り当て単位 */
        int      *cnt,      /* (I/O) メモリ割り当て実行回数          */
        int      numOfClips /* (I)   格納済みブックマーク数          */
    );

/* 比較(タイムスタンプ、URLの昇順にソートする場面などで使用) */
int
compareMyClip( const void *elem1, const void *elem2 );


/* ブックマーク取得処理 */
MyClip  *
getMyClip(
        const char *userName,   /* (I) メールアドレス */
        const char *password,   /* (I) パスワード     */
        int        *numOfClips  /* (O) ブックマーク数 */
    );

MyClip  *
getDelicious(
        const char *username,   /* (I) ユーザ名       */
        const char *password,   /* (I) パスワード     */
        int        *numOfClips  /* (O) ブックマーク数 */
    );

MyClip  *
getBlueDot(
        const char *username,   /* (I) ユーザ名       */
        const char *password,   /* (I) パスワード     */
        int        *numOfClips  /* (O) ブックマーク数 */
    );

MyClip  *
getHB(
        const char *username,   /* (I) ユーザ名       */
        int        *numOfClips  /* (O) ブックマーク数 */
    );

MyClip  *
getMMmemo(
        const char *username,   /* (I) TypeKeyユーザ名   */
        const char *password,   /* (I) TypeKeyパスワード */
        int        *numOfClips  /* (O) ブックマーク数    */
    );                          /* 注意: MM/Memo は TypeKey による認証 */
                                /* を利用している                      */
MyClip  *
getFlog(
        const char *userName,   /* (I) login時に使うメールアドレス */
        const char *password,   /* (I) login時に使うパスワード     */
        const char *userID,     /* (I) ユーザID                    */
        int        *numOfClips  /* (O) 取得したブックマークの数    */
    );

MyClip  *
getEcNaviClip(
        const char *userName,   /* (I) login時に使うメールアドレス    */
        const char *password,   /* (I) login時に使うパスワード        */
        const char *userName2,  /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char *password2,  /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE  authType,    /* (I) 認証タイプ                     */
        const char *userID,     /* (I) 記者名                         */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 取得したブックマークの数       */
    );

MyClip  *
getLivedoorClip(
        const char *userName,   /* (I) livedoor ID                    */
        const char *password,   /* (I) パスワード (シークレットモード */
                                /*     のブックマークも取得したい場合 */
                                /*     に必要)                        */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    );

MyClip  *
getNiftyClip(
        const char *userName,   /* (I) @nifty ID または PLEASY ID もしくは */
                                /*     ユーザー名                          */
        const char *password,   /* (I) パスワード (userName に @nifty ID   */
                                /*     または PLEASY ID を指定したときのみ */
                                /*     必須)                               */
        const char *apiKey,     /* (I) APIキー                             */
        int        *total,      /* (O) 当該ユーザのブックマークの総数      */
        int        *numOfClips  /* (O) 取得したブックマークの数            */
    );

MyClip  *
getDrecomRSS(
        const char *userName,   /* (I) login時に使うメールアドレス */
        const char *password,   /* (I) login時に使うパスワード     */
        int        *numOfClips  /* (O) 取得したブックマークの数    */
    );

MyClip  *
get1470net(
        const char *username,   /* (I) TypeKey認証用ユーザ名   */
        const char *password,   /* (I) TypeKey認証用パスワード */
        const char *username2,  /* (I) はてな認証用ユーザ名    */
        const char *password2,  /* (I) はてな認証用パスワード  */
        AUTH_TYPE  authType,    /* (I) 認証タイプ              */
        int        *numOfClips  /* (O) ブックマーク数          */
    );                          /* 注意: 1470.net は TypeKey と はてな */
                                /*       認証API による認証の2つの認証 */
                                /*       方法を選択できるようになって  */
                                /*       いる                          */
MyClip  *
getPookmark(
        const char *userName,   /* (I) JugemKey ID (JUGEMユーザー名)  */
        const char *password,   /* (I) パスワード                     */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 取得したブックマークの数       */
    );

MyClip  *
getJoltMark(
        const char *userName,   /* (I) ユーザ名                       */
        const char *password,   /* (I) パスワード (非公開のブックマー */
                                /*     クも取得したい場合に必要)      */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    );

MyClip  *
getFC2Bookmark(
        const char *userName,   /* (I) ユーザ名 (FC2ID またはメールア */
                                /*     ドレス)                        */
        const char *password,   /* (I) パスワード (非公開のブックマー */
                                /*     クも取得したい場合に必要 [さら */
                                /*     に、userName で指定するのは    */
                                /*     FC2ID ではなく、メールアドレス */
                                /*     である必要がある])             */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    );

MyClip  *
getBlogPet(
        const char *userName,   /* (I) ユーザ名                       */
        const char *password,   /* (I) パスワード (非公開のブックマー */
                                /*     クも取得したい場合に必要)      */
        int        *numOfClips  /* (O) 実際に取得したブックマークの数 */
    );

MyClip  *
getYJbookmark(
        const char *userName,   /* (I) Yahoo! Japan ID                */
        const char *password,   /* (I) パスワード                     */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 取得したブックマークの数       */
    );

MyClip  *
getYahooBookmarks(
        const char *userName,   /* (I) Yahoo! ID                      */
        const char *password,   /* (I) パスワード                     */
        int        *total,      /* (O) 当該ユーザのブックマークの総数 */
        int        *numOfClips  /* (O) 取得したブックマークの数       */
    );

MyClip  *
getDiigo(
        const char *username,   /* (I) ユーザ名       */
        const char *password,   /* (I) パスワード     */
        int        *numOfClips  /* (O) ブックマーク数 */
    );

MyClip  *
getLocalOpml(
        const char *filename,   /* (I) OPMLファイル名           */
        int        *numOfClips  /* (O) 取得したブックマークの数 */
    );

/* ブックマーク登録処理 */
void
putDelicious(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putBlueDot(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putHB(
        const char   *userName,  /* (I) はてなID                       */
        const char   *password,  /* (I) パスワード                     */
        BOOL         useMyTitle, /* (I) タイトルを独自に設定するか否か */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    );

void
putBPTags(
        const char   *userName,  /* (I) ユーザ名(メールアドレス) */
        const char   *password,  /* (I) パスワード               */
        const MyClip *mp,        /* (I) ブックマーク情報         */
        int          numOfClips  /* (I) ブックマーク数           */
    );

void
putMMmemo(
        const char   *userName,  /* (I) TypeKeyユーザ名   */
        const char   *password,  /* (I) TypeKeyパスワード */
        const MyClip *mp,        /* (I) ブックマーク情報  */
        int          numOfClips  /* (I) ブックマーク数    */
    );

void
putDrecomRSS(
        const char   *userName,  /* (I) ユーザ名(メールアドレス) */
        const char   *password,  /* (I) パスワード               */
        const MyClip *mp,        /* (I) ブックマーク情報         */
        int          numOfClips  /* (I) ブックマーク数           */
    );

void
putFlog(
        const char   *userName,  /* (I) ユーザ名(メールアドレス) */
        const char   *password,  /* (I) パスワード               */
        const MyClip *mp,        /* (I) ブックマーク情報         */
        int          numOfClips  /* (I) ブックマーク数           */
    );

void
putLivedoorClip(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putEcNaviClip(
        const char   *userName,  /* (I) ユーザ名                       */
        const char   *password,  /* (I) パスワード                     */
        const char   *userName2, /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char   *password2, /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE    authType,   /* (I) 認証タイプ                     */
        BOOL         useMyTitle, /* (I) タイトルを独自に設定するか否か */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    );

void
putNiftyClip(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const char   *apiKey,    /* (I) APIキー          */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
put1470net(
        const char   *userName,  /* (I) 認証用ユーザ名         */
        const char   *password,  /* (I) 認証用パスワード       */
        const char   *userName2, /* (I) 認証用ユーザ名(予備)   */
        const char   *password2, /* (I) 認証用パスワード(予備) */
        AUTH_TYPE    authType,   /* (I) 認証タイプ             */
        const MyClip *mp,        /* (I) ブックマーク情報       */
        int          numOfClips  /* (I) ブックマーク数         */
    );

void
putNewsing(
        const char   *userName,  /* (I) ユーザ名(メールアドレス)       */
        const char   *password,  /* (I) パスワード                     */
        const char   *userName2, /* (I) 認証用ユーザ名(Yahoo! Japan)   */
        const char   *password2, /* (I) 認証用パスワード(Yahoo! Japan) */
        AUTH_TYPE    authType,   /* (I) 認証タイプ                     */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    );

void
putPookmark(
        const char   *userName,  /* (I) ユーザ名(メールアドレス) */
        const char   *password,  /* (I) パスワード               */
        const MyClip *mp,        /* (I) ブックマーク情報         */
        int          numOfClips  /* (I) ブックマーク数           */
    );

void
putJoltMark(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putFC2Bookmark(
        const char   *userName,  /* (I) ユーザ名 (FC2ID) */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putBlogPet(
        const char   *userName,  /* (I) ユーザ名                       */
        const char   *password,  /* (I) パスワード                     */
        BOOL         useMyTitle, /* (I) タイトルを独自に設定するか否か */
        const MyClip *mp,        /* (I) ブックマーク情報               */
        int          numOfClips  /* (I) ブックマーク数                 */
    );

void
putTwitter(
        const char   *userName,  /* (I) ユーザ名(メールアドレス) */
        const char   *password,  /* (I) パスワード               */
        const char   *token,     /* (I) アクセストークン         */
        const char   *secret,    /* (I) アクセストークン秘密鍵   */
        AUTH_TYPE    authType,   /* (I) 認証タイプ               */
        const char   *version,   /* (I) userAgent 版数           */
        const char   *url,       /* (I) userAgent 関連Webページ  */
        const char   *resource,  /* (I) userAgent 関連XML        */
        const MyClip *mp,        /* (I) ブックマーク情報         */
        int          numOfClips  /* (I) ブックマーク数           */
    );

void
putYJbookmark(
        const char   *userName,  /* (I) ユーザ名(Yahoo! Japan ID) */
        const char   *password,  /* (I) パスワード                */
        const MyClip *mp,        /* (I) ブックマーク情報          */
        int          numOfClips  /* (I) ブックマーク数            */
    );

void
putYahooBookmarks(
        const char   *userName,  /* (I) ユーザ名(Yahoo! ID) */
        const char   *password,  /* (I) パスワード          */
        const MyClip *mp,        /* (I) ブックマーク情報    */
        int          numOfClips  /* (I) ブックマーク数      */
    );

void
putTimelog(
        const char   *userName,  /* (I) ユーザ名                */
        const char   *password,  /* (I) パスワード              */
        const char   *version,   /* (I) userAgent 版数          */
        const char   *url,       /* (I) userAgent 関連Webページ */
        const char   *resource,  /* (I) userAgent 関連XML       */
        const MyClip *mp,        /* (I) ブックマーク情報        */
        int          numOfClips  /* (I) ブックマーク数          */
    );

void
putDigg(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putTumblr(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const char   *group,     /* (I) 投稿先tumbleblog */
        const char   *version,   /* (I) userAgent 版数   */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putDiigo(
        const char   *userName,  /* (I) ユーザ名         */
        const char   *password,  /* (I) パスワード       */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

void
putLocalOpml(
        const char   *filename,  /* (I) OPMLファイル名   */
        const MyClip *mp,        /* (I) ブックマーク情報 */
        int          numOfClips  /* (I) ブックマーク数   */
    );

/* ブックマーク登録処理メインループ */
typedef struct paramOfPutBookmarks  {
    char    *cookie;
    size_t  cookieSize;
    char    *request;
    char    *response;
    size_t  sz;
    int     index;
    void    *args;
}   PARAM_PBM;

void
putBookmarks(
        const char   *bookmarkName,
        const MyClip *mp,
        int          numOfClips,
        char         *cookie,
        size_t       cookieSize,
        void         *args,
        int (__cdecl *func)( const MyClip *mp,
                             char         *errorString,
                             PARAM_PBM    *args )
    );

/* ブックマーク登録者数取得処理 */
char    *getUsersOfHatenaBookmark( const char *url );
char    *getUsersOfDelicious( const char *url );
char    *getUsersOfBlueDot( const char *url );
char    *getUsersOfMMmemo( const char *url, BOOL *stat1470net );
char    *getUsersOfECnaviClip( const char *url );
char    *getUsersOfLivedoorClip( const char *url );
char    *getUsersOfDigg( const char *url );
char    *getUsersOfNiftyClip( const char *url );

/* タグ一覧の取得 */
TagList *
getTagListOnDelicious(
        const char *username,
        const char *password,
        int        *numOfTags );

TagList *
getTagListOnBlueDot(
        const char *username,
        const char *password,
        int        *numOfTags );

TagList *
getTagListOnHatenaBookmark(
        const char *username,
        const char *password,
        int        *numOfTags );

TagList *
getTagListOnNiftyClip(
        const char *username,
        const char *password,
        int        *numOfTags );

/* タグの削除 */
BOOL
removeTagFromBookmarksOnNiftyClip(
        const char *username,
        const char *password,
        const char *tag );

/* タグの置換 */
BOOL
renameTagFromBookmarksOnNiftyClip(
    const char *username,
    const char *password,
    const char *oldTag,
    const char *newTag );

/* ブックマークをファイルに書き出す処理 */
/* outputOPML() の第4引数 codeChange の値: 文字コード変換 */
#define UTF8        0   /* 無変換(UTF-8 のまま)           */
#define SJIS2UTF    1   /* Shift_JIS → UTF-8 変換を実行  */
#define EUC2UTF     2   /* EUC-JP → UTF-8 変換を実行     */
/* 上記に加えて、outputBookmarkHtml() では以下も使用 */
#define SJIS        4   /* EUC-JP,UTF-8 → Shift_JIS 変換を実行 */

void
outputOPML(
        const MyClip *myClip,    /* (I) ブックマーク情報 */
        int          numOfClips, /* (I) ブックマーク数   */
        const char   *title,     /* (I) ブックマーク名称 */
        int          codeChange, /* (I) 文字コード変換   */
        FILE         *fp         /* (I/O) ブックマーク書き出し先 */
                                 /*       ファイルストリーム     */
    );  // OPMLファイルに書き出す

void
outputBookmarkHtml(
        const MyClip *myClip,    /* (I) ブックマーク情報 */
        int          numOfClips, /* (I) ブックマーク数   */
        const char   *title,     /* (I) ブックマーク名称 */
        int          codeChange, /* (I) 文字コード変換   */
        FILE         *fp         /* (I/O) ブックマーク書き出し先 */
                                 /*       ファイルストリーム     */
    );  // NETSCAPE-Bookmark-file-1 形式の htmlファイルに書き出す

void
outputOpera6Adr(
        const MyClip *myClip,    /* (I) ブックマーク情報 */
        int          numOfClips, /* (I) ブックマーク数   */
        const char   *title,     /* (I) ブックマーク名称 */
        int          codeChange, /* (I) 文字コード変換   */
        FILE         *fp         /* (I/O) ブックマーク書き出し先 */
                                 /*       ファイルストリーム     */
    );  // opera6.adr 形式のテキストファイルに書き出す

void
outputHatenaFeed(
        const MyClip *myClip,    /* (I) ブックマーク情報 */
        int          numOfClips, /* (I) ブックマーク数   */
        const char   *title,     /* (I) ブックマーク名称 */
        int          codeChange, /* (I) 文字コード変換   */
        FILE         *fp         /* (I/O) ブックマーク書き出し先 */
                                 /*       ファイルストリーム     */
    );  // はてなブックマークの Atom フィード形式のXMLファイルに書き出す

void
outputDeliciousXML(
        const MyClip *myClip,    /* (I)   ブックマーク情報       */
        int          numOfClips, /* (I)   ブックマーク数         */
        FILE         *fp,        /* (I/O) ブックマーク書き出し先 */
                                 /*       ファイルストリーム     */
        const char   *userName   /* (I)   del.icio.us ユーザ名   */
    );  // del.icio.us の posts/all で取得可能な形式と同じ形式のXMLファイルに
        // 書き出す

/* ブックマークをファイルから読み取る処理 */
MyClip  *
inputOPML(
        int  *numOfClips,   /* (O) ブックマーク数                           */
        FILE *fp            /* (I) ブックマーク読み取り先ファイルストリーム */
    );  // OPMLファイルから読み取る

MyClip  *
inputBookmarkHtml(
        int  *numOfClips,   /* (O) ブックマーク数                           */
        FILE *fp            /* (I) ブックマーク読み取り先ファイルストリーム */
    );  // NETSCAPE-Bookmark-file-1 形式の htmlファイルから読み取る

MyClip  *
inputOpera6Adr(
        int  *numOfClips,   /* (O) ブックマーク数                           */
        FILE *fp            /* (I) ブックマーク読み取り先ファイルストリーム */
    );  // opera6.adr 形式のテキストファイルから読み取る

MyClip  *
inputHatenaFeed(
        int  *numOfClips,   /* (O) ブックマーク数                           */
        FILE *fp            /* (I) ブックマーク読み取り先ファイルストリーム */
    );  // はてなブックマークの RSS/Atom フィード形式のXMLファイルから読み取る

MyClip  *
inputLivedoorFeed(
        int  *numOfClips,   /* (O) ブックマーク数                           */
        FILE *fp            /* (I) ブックマーク読み取り先ファイルストリーム */
    );  // livedoorクリップの RSS 2.0 フィード形式のXMLファイルから読み取る

MyClip  *
inputDeliciousXML(
        int    *numOfClips, /* (O) ブックマーク数                           */
        FILE   *fp,         /* (I) ブックマーク読み取り先ファイルストリーム */
        size_t fileSize     /* (I) ブックマーク読み取り先ファイルサイズ     */
    );  // del.icio.us の posts/all で取得可能な形式のXMLファイルから読み取る

/* for はてなブックマーク REST API */
#define NUM_OF_INFO_PER_HATENA_API  50  /* 1回のAPI実行で取得する情報数 */
            /* 注意: 実際に1回のAPI実行で取得できるブックマーク数は20個 */
            /*       (デフォルト、設定変更可能)                         */


/* MM/Memo 関連独自処理 */
int
loginMMmemo(
        const char *username,  // (I)   TypeKeyユーザ名
        const char *password,  // (I)   TypeKeyパスワード
        char       *cookie,    // (I/O) クッキー
        char       *userID     // (O)   MM/Memo ユーザID
    );

int
login1470net(
        const char *username,  // (I)   認証用ユーザ名
        const char *password,  // (I)   認証用パスワード
        const char *username2, // (I)   はてなID
        const char *password2, // (I)   はてなパスワード
        AUTH_TYPE  authType,   // (I)   認証種別 (TypeKey, はてな認証API)
        char       *cookie,    // (I/O) クッキー
        char       *userID     // (O)   1470.netリニューアル版 ユーザ名
    );

/* ドリコムRSS 関連独自処理 */
int
loginDrecomRSS(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* Flog 関連独自処理 */
int
loginFlog(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* livedoorクリップ 関連独自処理 */
int
loginLivedoorClip(
        const char *userName,   // (I)   ユーザ名 (livedoor ID)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

char    *
getApiKeyOnLivedoorClip(
        const char *username,   // (I) ユーザ名 (livedoor ID)
        const char *password,   // (I) パスワード
        char       *apiKey      // (O) APIキー
    );  /* 「del.icio.us 互換API」用 APIキーの取得 */

/* Buzzurl 関連独自処理l*/      
int
loginEcNavi(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

int
loginEcNaviOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    );  /* Yahoo! Japan ID で Buzzurl に login する */

char    *
getEcNaviClipUserID(
        const char *userName,   // (I)   ユーザ名 (メールアドレス or Y!J ID)
        const char *password,   // (I)   パスワード
        AUTH_TYPE  auth_type,   // (I)   認証タイプ
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    );

/* ニフティクリップ 関連独自処理 */
int
loginNiftyClip(
        const char *userName,   // (I)   ユーザ名 (@nifty ID または PLEASY ID)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

char    *
getApiKeyOnNiftyClip(
        const char *username,   // (I) ユーザ名 (livedoor ID)
        const char *password,   // (I) パスワード
        char       *apiKey      // (O) APIキー
    );  /* APIキーの取得 */

/* はてなブックマーク関連独自処理 */
char    *
encodeURLforHatena( const char *url );

int
getNumberOfHatenaBookmark(
        const char *username,
        const char *password
    );

/* newsing 関連独自処理 */
int
loginNewsing(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

int
loginNewsingOnBBAuth(
        const char *username,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        size_t     *cookieSize  // (I/O) クッキー文字列長
    );

/* POOKEY (jugemkey) 関連独自処理 */
int
loginJugemkey(
        const char *userName,   // (I)   jugemkey (JUGEM ユーザ名)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* JoltMark 関連独自処理 */
int
loginJoltMark(
        const char *userName,   // (I)   ユーザ名
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* FC2BOOKMARK 関連独自処理 */
int
loginFC2Bookmark(
        const char *userName,   // (I)   ユーザ名 (メールアドレス)
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        char       *uid,        // (O)   uid (FC2ID のユーザID)
        char       *cc          // (O)   cc  (FC2BOOKMARK のcc)
    );

/* BlogPet 気になる記事 関連独自処理 */
int
loginBlogPet(
        const char *userName,   // (I)   ユーザ名
        const char *password,   // (I)   パスワード
        char       *cookie,     // (I/O) クッキー
        char       *userID      // (O)   ユーザID
    );

/* Yahoo! ブックマーク 関連独自処理 */
int
loginYahooJapan(
        const char *userName,   // (I)   ユーザ名 (Yahoo! Japan ID)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* Yahoo! Bookmarks 関連独自処理 */
int
loginYahoo(
        const char *userName,   // (I)   ユーザ名 (Yahoo! ID)
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* digg 関連独自処理 */
int
loginDigg(
        const char *userName,   // (I)   ユーザ名
        const char *password,   // (I)   パスワード
        char       *cookie      // (I/O) クッキー
    );

/* del.icio.us 関連独自処理 */
MyClip  *
deliciousPosts2MyClip( DELICIOUS_POSTS *posts, int numOfPosts );

/* ユーティリティ関数 */

int     strncmpi( const char *s, const char *t, size_t n );
char    *unescapeURL( const char *url );
char    *any2utf( const char *p );
char    *any2euc( const char *p );
char    *any2sjis( const char *p );
char    *any2sjisEx( char *dst, const char *src );
char    *chcode( char *p );
char    *justify( char *s, size_t len );
char    *getValue( const char *p, const char *name );

typedef enum captchaDialogMode  {
    CAP_MAKE_STORY,
    CAP_POST_COMMENT
}   CAP_MODE;

char    *inputCaptchaString( const char *url,
                             char       *cookie,
                             char       *captcha,
                             char       *title,
                             char       *comment,
                             char       *topic,
                             CAP_MODE   mode );

/*
 *  getStringImplanted()
 *      文字列 src から、startString と endString で挟まれた部分の
 *      文字列を抽出(したものを dst に格納)する
 *
 *          例:
 *              src:         <p>abcd <strong>efg</strong> hijkl</p>
 *              startString: <strong>
 *              endString:   </strong>
 *            のとき
 *              getStringImplanted(dst, src, startString, endString);
 *            を実行すると、dst には
 *              efg
 *            が格納される
 */
char    *
getStringImplanted(
        char       *dst,        /* (O) 結果           */
        const char *src,        /* (I) 調査対象文字列 */
        const char *startString,/* (I) 開始文字列     */
        const char *endString   /* (I) 終了文字列     */
    );

/*
 *  getEvaluation()
 *      MM/Memo 形式の title から、「評価」と本来の「題名」を抽出する
 */
int
getEvaluation( char *title, int changeCode );

/*
 *  getASIN()
 *      URL に含まれる ASIN を取り出す
 *      (amazon, はてな の URL が対象)
 */
char    *
getASIN(
        const char *url,    /* (I) 解析対象 URL */
        char       *asin    /* (O) ASIN 文字列  */
    );

/* 指定された文字列中に含まれる html タグを取り除く */
char    *
deleteHtmlTags( char *text );

/* 
 *  getDateTimeFromDateString()
 *      日時を表わす文字列から、年月日時分秒を取り出す
 *        RFC822形式、ISO8601形式、および以下の形式に対応
 *            yyyy[{/|-| }]mm[{/|-| }]dd HH[{:| }]MM[{:| }]SS [{+|-}dH[:]dM]
 *          -- RFC822形式
 *            [曜日,] dd 月名 {yy|yyyy} HH:MM:SS [{{+|-}dH[:]dM|GMT|JST|...}]
 *          -- ISO8601形式
 *            yyyy[-]mm[-]ddTHH:MM:SS{Z|{+|-}dHdM}}
 *          以下の形式には未対応
 *            mm/dd/yy HH:MM:SS   (→ 03/01/05 だと
 *                                        2003年1月5日なのか、
 *                                        2005年1月3日なのか、
 *                                        2005年3月1日なのか、
 *                                    判断しかねる [そもそも
 *                                        平成3年1月5日とか
 *                                    西暦じゃない可能性もある]
 *            dd/mm/yy HH:MM:SS
 *            mm/dd/yyyy HH:MM:SS
 *            dd/mm/yyyy HH:MM:SS
 *          なお、
 *            yyyy: 年(4桁)
 *            yy:   年(下2桁)
 *            mm:   月(1桁または2桁)
 *            dd:   日(1桁または2桁)
 *            HH:   時(1桁または2桁)
 *            MM:   分(1桁または2桁)
 *            SS:   秒(1桁または2桁)
 *            dH:   UTC との時差のうち「時」部分
 *            dM:   UTC との時差のうち「分」部分
 *          とする
 */
time_t
getDateTimeFromDateString(
        const char *date,   /* (I) 日時情報(文字列) */
        int        *yyyy,   /* (O) 年               */
        int        *mm,     /* (O) 月               */
        int        *dd,     /* (O) 日               */
        int        *HH,     /* (O) 時               */
        int        *MM,     /* (O) 分               */
        int        *SS      /* (O) 秒               */
    );

/* 指定された文字列(Shift_JIS)を指定文字列長に丸める */
char *
adjustStringLength( char *p, int len );

/* 指定文字列を別の指定文字列に置換する */
BOOL
replaceString( char *target, const char *src, const char *dst );

/* JSON形式で取得したコンテンツのデコード */
char        *
decodeContents(
        char *contents  /* (I) デコード対象のコンテンツ */
                        /* (O) デコード結果             */
    );

/* コンテンツのJSON形式へのエンコード */
char    *
encodeContents( const char *contents );

/* ユーティリティマクロ */
#ifndef	iskanji1
#define	iskanji1(s) \
    (((((short)s & 0xFF)>=0x81) && (((short)s & 0xFF)<=0x9f)) || \
     ((((short)s & 0xFF)>=0xe0) && (((short)s & 0xFF)<=0xfc)))
#endif
#ifndef	iskanji2
#define	iskanji2(s) \
    (((((short)s & 0xFF)>=0x40) && (((short)s & 0xFF)<=0x7e)) || \
     ((((short)s & 0xFF)>=0x80) && (((short)s & 0xFF)<=0xfc)))
#endif

#define isWhiteSpace(c) \
    (((c) == ' ') || ((c) == '\t') || ((c) == '\r') || ((c) == '\n'))

#define skipToNextItemWithSeparator( p, separator, terminator ) \
    while ( *(p) && (*(p )!= (separator) ) && (p < (terminator)) ) \
        (p)++; \
    if ( !(*(p)) || ((p) > (terminator)) ) \
        break; \
    (p)++; \
    if ( *(p) == '0' ) \
        (p)++;

#endif  /* __MY_CLIP_H__ */
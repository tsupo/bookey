/*
 *  getEvaluation.c
 *      MM/Memo 形式の「評価」
 *          written by H.Tsujimura  19 Oct 2005 / 17 Nov 2006
 *
 * $Log: /comm/bookey/getEvaluation.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     06/11/27 16:01 Tsujimura543
 * コメントを追加
 * 
 * 3     06/11/27 15:58 Tsujimura543
 * 「評価」の指定が存在しない場合も title の文字コード変換が必要である
 * ことを忘れていた (処理抜け)
 * 
 * 2     06/11/17 15:25 Tsujimura543
 * getEvaluation() に第2引数を追加
 * 
 * 1     06/11/17 14:43 Tsujimura543
 * 新規作成 (今まで各関数内部で各々処理していたのを、共通関数化してみた)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getEvaluation.c 1     09/05/14 3:48 tsupo $";
#endif

//  MM/Memo 形式の「評価」(title の先頭に埋め込まれている)を取得し、
//  title を他のソーシャルブックマークサービスへそのままインポートで
//  きる形式に変換する
//
//      MM/Memo の title の例 (以下のような3種類のパターンがある)
//          ・種類 + 評価 + タイトル
//              [sw](3)『Dublin Core Metadata Initiative (DCMI)』
//          ・評価 + タイトル
//              (3)『Dublin Core Metadata Initiative (DCMI)』
//          ・タイトル
//              『Dublin Core Metadata Initiative (DCMI)』
int
getEvaluation( char *title, int changeCode )
{
    const char  *p, *q;
    BOOL        multiple = FALSE;
    int         rate = 0;
    char        temp[MAX_DESCRIPTION_LEN];
    char        tmpTitle[MAX_DESCRIPTION_LEN];

    temp[0] = NUL;

    // いったん Shift_JIS に変換しておいてから、処理を進める
    p = utf2sjis( title );
    if ( !p )
        p = euc2sjis( title );
    strcpy( tmpTitle, p ? p : title );

    p = strstr( tmpTitle, "『" );
    q = strstr( tmpTitle, "』" );
    if ( q && *(q + 2) ) {
        const char  *r;
        do {
            r = strstr( q + 2, "』" );
            if ( r ) {
                q = r;
                multiple = TRUE;
            }
        } while ( r );
    }
    if ( p && q && (p < q) && (*(q + 2) == NUL) &&
         ((p == tmpTitle)   ||
          (*(p - 1) == ')') ||
          (*(p - 1) == ']')    )                   ) {
        if ( multiple == FALSE )
            p = getStringImplanted( temp, tmpTitle, "『", "』" );
        else {
            // 『』が入れ子構造になっている場合
            ///  -- いちばん外側の『』を外す
            strcpy( temp, p + 2 );
            temp[strlen(temp) - 2] = NUL;
            p = temp;
        }
        if ( p && *p ) {
            if ( ((tmpTitle[0] == '(') && (tmpTitle[2] == ')')) ||
                 ((tmpTitle[4] == '(') && (tmpTitle[6] == ')'))    ) {
                // 「評価」を title から取り出す
                rate = atol( (tmpTitle[0] == '(') && (tmpTitle[2] == ')')
                                 ? &(tmpTitle[1])
                                 : &(tmpTitle[5]) );
            }
        }
    }

    // title から「種類」、「評価」(が存在する場合)を取り除いたものを
    // 新しい title にする [さらに、(「評価」が存在するかどうかに関わ
    // らず、Shift_JIS から)オリジナルの文字コードに戻しておく]
    q = temp[0] ? temp : tmpTitle;
    if ( *q ) {
        switch ( changeCode ) {
        case EUC2UTF:
            p = sjis2euc( q );
            strcpy( title, p ? p : q );
            break;
        case SJIS2UTF:
            strcpy( title, q );
            break;
        case UTF8:
        default:
            p = any2utf( q );
            strcpy( title, p ? p : q );
            break;
        }
    }

    return ( rate );
}

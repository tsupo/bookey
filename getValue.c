/*
 * getValue.c
 *      指定文字列を id 属性の値としてもつ(input)要素の value 属性の
 *      値を取得する
 *          written by H.Tsujimura  29 Jun 2006 / 18 Jan 2007
 *
 * History:
 * $Log: /comm/bookey/getValue.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     07/01/19 0:11 Tsujimura543
 * コメントを修正
 * 
 * 2     07/01/19 0:09 Tsujimura543
 * id属性で見つからなかった場合は、name属性で探すようにした
 * (Buzzurl は name属性を使っている) [putNiftyClip.c の getValue()
 * と putEcNavi.c  の getValue() の微妙な仕様の違いを見落としていた]
 * 
 * 1     07/01/18 22:45 Tsujimura543
 * putEcNavi.c と putNiftyClip.c のそれぞれに配置してあった getValue() を
 * 分離、独立させた (getValue.c へ移動)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/getValue.c 1     09/05/14 3:48 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char *
getValue( const char *p, const char *name )
{
    Thread  static char value[BUFSIZ];

    value[0] = NUL;
    if ( p && *p ) {
        char    target[BUFSIZ];
        char    *q, *r;

        sprintf( target, "id=\"%s\" value=\"", name );
        q = strstr( p, target );
        if ( !q ) {
            sprintf( target, "name=\"%s\" value=\"", name );
            q = strstr( p, target );
        }
        if ( q ) {
            q += strlen( target );
            r = strchr( q, '"' );
            if ( r ) {
                strncpy( value, q, r - q );
                value[r - q] = NUL;
            }
        }
    }

    return ( value );
}

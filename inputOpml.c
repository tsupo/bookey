/*
 *  inputOpml.c
 *      OPML �t�@�C������u�b�N�}�[�N����荞��
 *          written by H.Tsujimura  17 Jan 2005 / 28 Sep 2005
 *
 * $Log: /comm/bookey/inputOpml.c $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 18    07/03/03 22:13 Tsujimura543
 * FC2BOOKMARK �� OPML �t�@�C���� bookey �œǂݎ��Ȃ��Ƃ̎w�E��
 * �󂯁A�ǂ߂�悤�ɂ��Ă݂�
 * 
 * 17    06/12/08 15:37 Tsujimura543
 * getDateTimeFromDateString() �𓱓����A�������̉�͂��ς˂邱�Ƃɂ���
 * 
 * 16    06/12/07 17:35 Tsujimura543
 * outputOPML() �Łu���J��ԁv���L�^�ł���悤�ɂ����̂Ɍĉ����āA
 * inputOPML() �ł��u���J��ԁv��ǂݎ���悤�ɂ���
 * 
 * 15    06/11/17 19:42 Tsujimura543
 * �R�����g�A�E�g�ɂ�薳�������Ă����������폜
 * 
 * 14    06/11/17 19:40 Tsujimura543
 * outputOPML() �̕ύX(MM/Memo�`���� title ���g���̂���߂āA�Ǝ��g������
 * ���g���āu�]���v���L�^����悤�ɂ���)�̂Ɍĉ����āA inputOPML() �ł���
 * ���g��������������(�ǂݎ���)�悤�ɂ���
 * 
 * 13    06/11/14 15:45 Tsujimura543
 * unescapeURL() �̎��̂� myClip.c �ֈړ�
 * 
 * 12    06/10/26 23:31 Tsujimura543
 * ��������j�󂷂�\���̂���ӏ����C��
 * 
 * 11    06/10/07 8:48 Tsujimura543
 * JST �� GMT �ϊ������̌v�Z�����Ԉ���Ă����̂��C��
 * 
 * 10    06/09/22 20:50 Tsujimura543
 * allocateMyClipIfNecessary() �𓱓��BMyClip �\���̊i�[�̈�m�ۏ�����
 * ���ʊ֐������Ă݂�
 * 
 * 9     06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 8     06/07/24 19:10 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 7     06/07/24 19:05 Tsujimura543
 * '<outline text="' �̒���ɉ��s������ꍇ�̋~�ϑ[�u��ǉ�
 * 
 * 6     05/10/20 22:46 Tsujimura543
 * �R�����g����̂Ƃ��A�S�~�������Ă��܂��Ă��� (�C���ς�)
 * 
 * 5     05/10/03 11:41 Tsujimura543
 * unescapeURL() ������ǉ�
 * 
 * 4     05/10/03 11:21 Tsujimura543
 * inputOPML() ���� outputOPML() ����ƁA������18���Ԗ��������ɂ���Ă��܂�
 * �s����C��
 * 
 * 3     05/09/28 19:36 Tsujimura543
 * �O���ϐ��ւ̃A�N�Z�X��p�~
 * 
 * 2     05/09/28 18:27 Tsujimura543
 * �u�b�N�}�[�N�o�^�����́u�b�v���t�@�C������ǂݖY��Ă����̂��C��
 * 
 * 1     05/09/28 14:55 Tsujimura543
 * �ŏ��̔�(clipConverter.c ���番���Ɨ�)
 */

#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/inputOpml.c 1     09/05/14 3:48 tsupo $";
#endif


MyClip  *
inputOPML( int *numOfClips, FILE *fp )
{
    char    buf[65536], *p, *q;
    char    tmp[65536];
    char    *note;
    int     num = 1000; /* �b�� */
    int     cnt = 0, block = 1;
    MyClip  *mp = NULL;
    MyClip  *newClip_p;
    int     rate;

    if ( !numOfClips )
        return ( mp );
    *numOfClips = 0;

    while ( ( p = fgets( buf, 65536 - 1, fp ) ) != NULL ) {
        while ( (*p == ' ') || (*p == '\t') )
            p++;
        if ( !strncmp( p, "</body>", 7 ) || !strncmp( p, "</opml>", 7 ) )
            break;
        if ( strncmp( p, "<outline ", 9 ) != 0 )
            continue;

        newClip_p = allocateMyClipIfNecessary( &mp, num, &block, cnt );
        if ( !newClip_p )
            break;
        mp = newClip_p;

        rate = 0;
        note = p;

        /* text [�K�{] */
        q = strstr( note, "text=\"" );
        if ( !q )
            continue;
        p = q + 6;
        q = strchr( p, '"' );
        while ( !q ) {
            /* '<outline text="' �̒���ɉ��s������ꍇ�̋~�ϑ[�u */
            p = fgets( buf, 65536 - 1, fp );
            if ( !p )
                break;
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            q = strchr( p, '"' );
            if ( q )
                note = q;
        }
        if ( !p )
            break;
        if ( q ) {
            strncpy( mp[cnt].title, p, q - p );
            mp[cnt].title[q - p] = '\0';
            p = q + 1;

            // MM/Memo �`���� title ���������߂̏���
            rate = getEvaluation( mp[cnt].title, UTF8 );
        }

        /* url [�K�{] */
        q = strstr( note, "url=\"" );
        if ( q ) {
            q += 5;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( tmp, q, p - q );
                tmp[p - q] = '\0';
                strcpy( mp[cnt].url, unescapeURL( tmp ) );
                p++;
            }
            else
                p = q;
        }

        /* title [�K�{] */
        q = strstr( note, "title=\"" );
        if ( q ) {
            q += 7;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( mp[cnt].tags, q, p - q );
                mp[cnt].tags[p - q] = NUL;
                p++;
            }
            else
                p = q;
        }

        /* notes [�K�{] */
        q = strstr( note, "notes=\"" );
        if ( q ) {
            q += 7;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( mp[cnt].comment, q, p - q );
                mp[cnt].comment[p - q] = '\0';
                p++;
            }
            else
                p = q;
        }

        /* date [�K�{] */
        q = strstr( note, "date=\"" );
        if ( q ) {
            q += 6;
            p = strchr( q, '"' );
            if ( p ) {
                strncpy( tmp, q, p - q );
                tmp[p - q] = '\0';
                getDateTimeFromDateString( tmp,
                                           &(mp[cnt].yyyy),
                                           &(mp[cnt].mm),
                                           &(mp[cnt].dd),
                                           &(mp[cnt].HH),
                                           &(mp[cnt].MM),
                                           &(mp[cnt].SS) );
                p++;
            }
            else
                p = q;
        }

        /* �ȉ��� bookey �Ǝ��g�� */
        /* evaluation [optional] */
        q = strstr( note, "evaluation=\"" );
        if ( q ) {
            q += 12;
            mp[cnt].evaluation = atol( q );
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }
        if ( mp[cnt].evaluation == 0 )
            if ( rate > 0 )
                mp[cnt].evaluation = rate;

        /* rating [optional] */
        q = strstr( note, "rating=\"" );
        if ( q ) {
            q += 8;
            mp[cnt].rating = atol( q );
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }

        /* affirmation [optional] */
        q = strstr( note, "affirmation=\"" );
        if ( q ) {
            q += 13;
            if ( !strncmpi( q, "good", 4 ) )
                mp[cnt].affirmation = AFF_GOOD;
            else if ( !strncmpi( q, "bad", 3 ) )
                mp[cnt].affirmation = AFF_BAD;
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }

        /* publication [optional] */
        q = strstr( note, "publication=\"" );
        if ( q ) {
            q += 13;
            if ( !strncmpi( q, "friends", 7 ) )
                mp[cnt].publication = PUB_FRIENDS;
            else if ( !strncmpi( q, "private", 7 ) )
                mp[cnt].publication = PUB_PRIVATE;
            p = strchr( q, '"' );
            if ( !p )
                p = q;
        }

        cnt++;
    }
    if ( fp == stdin ) {
        clearerr( fp );
    }

    *numOfClips = cnt;

    return ( mp );
}


/*
 * �Q�l
 *  FC2BOOKMARK �̏o�͂��� OPML �̗�
 *
 *     <?xml version="1.0" encoding="UTF-8"?>
 *     <opml version="1.1">
 *       <head>
 *         <title>fc2 bookmark</title>
 *       </head>
 *       <body>
 *         <outline url="http://watcher.moe-nifty.com/memo/2005/10/bookey.html#c12284852" text="[��] �\�[�V�����u�b�N�}�[�N�Ǘ��c�[�� (�R�����g��)" type="link" notes="���[�A�����Ȃ�ł����B�ǂ��炩�Ƃ����ƁA(�o�܂��l�����)FC2BOOKMARK�������킹�ė~������ł����A�����̏����Ɉˑ���������͂悭�Ȃ��̂ŁA�C�����܂��B" date="2007-03-03T11:22:23Z" title="bookey"/>
 *       </body>
 *     </opml>
 *
 * http://bookmark.fc2.com/help/show/4#opml-is
 *  > FC2Bookmark����G�N�X�|�[�g�����OPML�̃f�[�^�\���́A�\�[�V����
 *  > �u�b�N�}�[�N�Ǘ��c�[��bookey �Ɠ����`���ɂȂ�܂��B
 * �Ə����Ă��邩��A�Ă����� bookey �� OPML �`���Ɠ������Ǝv���Ă�
 * �񂾂��ǈ���Ă܂����B orz
 *
 * http://watcher.moe-nifty.com/memo/2005/10/bookey.html#c12284852
 *  > FC2����G�N�X�|�[�g����OPML�͑����̏������Ⴄ�̂œǂ߂Ȃ��悤�ł��B
 *  > HTML�`��������̂Ŗ��͂Ȃ��̂ł����A
 *  > http://bookmark.fc2.com/help/show/4 �ŏЉ��Ă��܂���
 *  > XML�̓ǂݍ��݂͉��炩�̃��C�u�����𗘗p���������ǂ����Ǝv���܂��B
 *  > �d�v�x�͒Ⴍ�č\���܂���B
 *  > ���e��: ksuzu (2007.03.03 �ߌ� 12:26)
 *
 * http://bookmark.fc2.com/help/show/4 �̌�
 * ���t�@���̉�͂ŏ�L�AFC2 �̉���y�[�W�̑��݂͒m���Ă܂������A
 * FC2BOOKMARK �̕��ł킴�킴 bookey �ɍ��킹�Ă��ꂽ���̂��Ɨ�������
 * �܂����B����̖�肪���o�����Ƃ������Ƃ� FC2���Ŏ��������̐�������
 * OPML �t�@�C�����ubookey �Ŏ��ۂɓǂݍ���ł݂鎎���v�Ƃ��͂��ĂȂ�
 * �Ƃ������Ƃł���ˁB �m�F�����ɁA�ubookey �Ɠ����`���ɂȂ�܂��v��
 * ������Ă��������Ⴂ�܂��B
 *
 * �ƌ����Ă邾���ł͑F�����̂ŁA bookey ���őΉ����ׂ��Ƃ���͑Ή���
 * �܂��B
 *
 * OPML �̌`���Ɋւ��Ă����΁A bookey �� outline �v�f�� text ��������
 * �n�܂邱�Ƃ�O��ɂ��Ă�񂾂��ǁAFC2BOOKAMRK�� url ��������n�܂�
 * �Ă��܂��B�����̏o�������Ɉˑ�����̂͂悭�Ȃ��ƌ�����΂���͂�
 * ���Ȃ̂ŁAbookey ���őΉ����܂��B
 *
 * �������AFC2BOOKMARK �̕��ɂ���肪����Atype="Link" �������Ă��܂�
 * ��BRSS ���[�_������ OPML �ł͂Ȃ��A�u�b�N�}�[�N(�Ƃ����������N�W)
 * ������OPML �ł��邱�Ƃ𖾎����邽�߂ɂ� type="Link" �͓���ė~����
 * �Ǝv���܂��B
 *
 * bookey �̎�舵�� OPML �̗� (�ꕔ��)
 *    <outline text="naoya�O���[�v - naoya�̓��L -  OPML" type="Link" url="http://naoya.g.hatena.ne.jp/naoya/20061030/1162194825" title="OPML" notes="���̋L���A�����Ƃ��Ă��B�͂ău�Ɋւ��āAOPML�ł̃G�N�X�|�[�g���������Ă����ǁA��߂�������A�Ƃ����b�B���ǁAhtml/RSS/Atom ��3�{���ĂɂȂ�����������ǁARSS �� Atom �͂ǂ������Е������ł悩�����悤�ȁB" date="2006-12-25T07:54:00Z" />
 *    <outline text="asahi.com�F �q���E���̐V��̐[�C�������� - �T�C�G���X" type="Link" url="http://www.asahi.com/science/news/OSK200611110026.html" title="fish �V��" notes="���^�̋��ł͂Ȃ��A����قǑ�^�ŁA���ڗ��͗l���������A����܂Ŕ�������Ȃ������̂͋�����" date="2006-12-21T09:05:07Z" evaluation="3" />
 *
 * �܂�ARSS���[�_�� OPML �t�@�C��(type="rss")�Ƃ� type ���Ⴄ(�킴
 * �ƕς��Ă�)�̂ŁAlivedoor Reader �� Bloglines �� OPML �t�@�C�����
 * �ݍ��܂��悤�Ƃ��Ă��A�������܂��B
 *
 * �ȉ��ABloglines �� OPML �̗� (�ꕔ��)
 *    <outline title="100SHIKI" text="100SHIKI" htmlUrl="http://www.100shiki.com/" type="rss" xmlUrl="http://www.100shiki.com/index.xml" />
 *
 *                                                    (2007/03/03 �L)
 */

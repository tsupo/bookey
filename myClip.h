/*
 *  �u�b�N�}�[�N�z�o���A�o�^�c�[�� ���ʃw�b�_�t�@�C��
 *          written by H.Tsujimura  17 Jan 2005 / 26 Sep 2005
 *
 * $Log: /comm/bookey/myClip.h $
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 131   09/05/28 22:13 Tsujimura543
 * ����A�J�E���g�ŕ��� tumbleblog ���J�݂��Ă���ꍇ�̓��e��
 * tumbleblog ���w�肵�Ă̓��e���\�ɂ���
 * 
 * 130   09/05/27 19:40 Tsujimura543
 * setSigInfo() ���폜 (xmlRPC.dll �ֈڊ�)
 * 
 * 129   09/05/27 17:08 Tsujimura543
 * setSigInfo() �̈�����ǉ�
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 128   09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 127   09/04/01 17:47 Tsujimura543
 * setSigInfo() ��ǉ�
 * 
 * 126   09/02/24 16:26 Tsujimura543
 * �^�O��⒊�o�����Q�̈������e�X�ǉ�
 * 
 * 125   08/11/11 16:19 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v����擾����v������ǉ�
 * 
 * 124   08/11/05 19:48 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v�֓o�^����v������ǉ��A����m�F����
 * 
 * 123   08/11/04 16:45 Tsujimura543
 * getApiKeyOnNiftyClip() ��ǉ�
 * 
 * 122   08/11/04 12:25 Tsujimura543
 * getUsersOfNiftyClip() ��ǉ�
 * 
 * 121   08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 120   08/07/28 15:28 Tsujimura543
 * getApiKeyOnLivedoorClip() ��ǉ�
 * 
 * 119   08/07/26 0:45 Tsujimura543
 * encodeContents()�AdecodeContents() �̃v���g�^�C�v�錾��
 * myClip.h �֏W��
 * 
 * 118   08/07/25 20:33 Tsujimura543
 * Diigo �Ή�
 * 
 * 117   08/02/14 19:41 Tsujimura543
 * replaceString() �� getFlog.c ����� putTumblr.c ����ړ�
 * 
 * 116   07/11/12 21:56 Tsujimura543
 * adjustStringLength() �� putLocalOpml.c, putMMmemo.c ����ڊ�
 * 
 * 115   07/11/12 19:03 Tsujimura543
 * any2sjisEx() ��ǉ�
 * 
 * 114   07/10/31 18:42 Tsujimura543
 * putTumblr() �Ɉ���(version)��ǉ�
 * 
 * 113   07/10/31 17:14 Tsujimura543
 * tumblr �ɑΉ�
 * 
 * 112   07/10/11 22:23 Tsujimura543
 * Yahoo! Japan �� ID �� newsing �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 111   07/10/10 22:38 Tsujimura543
 * �摜���擾����̂� cookie ���K�v�ȏꍇ(���̂Ƃ���Adigg�̂�)�ɑΉ�
 * 
 * 110   07/10/05 2:42 Tsujimura543
 * BBAuth �Ή��֘A�̊e��C�������{
 * 
 * 109   07/09/13 22:29 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 108   07/09/05 18:58 Tsujimura543
 * UserAgent �������t�@�N�^�����O
 * 
 * 107   07/09/05 1:50 Tsujimura543
 * getUsersOfMMmemo() �� extractTags() �Ɋe�X��2������ǉ�
 * (stat1470net��������)
 * 
 * 106   07/07/10 19:34 Tsujimura543
 * inputCaptchaString() �̈����ǉ��Ƃ���ɔ����e��ύX(����2)
 * 
 * 105   07/07/10 1:01 Tsujimura543
 * inputCaptchaString() �̈����ǉ��Ƃ���ɔ����e��ύX
 * 
 * 104   07/07/09 21:49 Tsujimura543
 * inputCaptchaString() �̈�����ǉ�
 * 
 * 103   07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 102   07/07/09 18:35 Tsujimura543
 * getUsersOfDigg() ��ǉ�
 * 
 * 101   07/05/23 16:11 Tsujimura543
 * Timelog �ւ̓o�^(����)�ɑΉ�
 * 
 * 100   07/05/11 19:10 Tsujimura543
 * Twitter �ɑ��� bookey �̔Ő������\�[�X����擾�������̂��g���悤��
 * ���Ă݂�
 * 
 * 99    07/04/20 20:34 Tsujimura543
 * Yahoo! �u�b�N�}�[�N�AYahoo! Bookmarks �̃C���|�[�g�ƃG�N�X�|�[�g�ɑΉ�
 * 
 * 98    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 97    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 96    07/04/16 17:59 Tsujimura543
 * del.icio.us �� posts/all �`���� XML �t�@�C���̃C���|�[�g�ƃG�N�X�|�[�g
 * �ɑΉ�����
 * 
 * 95    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 94    07/03/29 17:55 Tsujimura543
 * loginFC2Bookmark() �̈�����2�ǉ�
 * 
 * 93    07/03/01 21:36 Tsujimura543
 * getUsersOfLivedoorClip() ��ǉ�
 * 
 * 92    07/02/22 18:33 Tsujimura543
 * any2sjis() ��ǉ�
 * 
 * 91    07/02/16 16:35 Tsujimura543
 * �R�����g���C��
 * 
 * 90    07/02/16 16:22 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�ABuzzurl�ABlogPet�C�ɂȂ�L���Ɋւ��āA�^�C�g������
 * �������邩�ǂ����I��(�w��)�ł���悤�ɂ���
 * 
 * 89    07/02/14 23:46 Tsujimura543
 * struct myClip �̃����o publication �̌^�� BOOL ���� int �ɕύX
 * 
 * 88    07/02/02 23:36 Tsujimura543
 * getTitle() �̈�����ǉ�
 * 
 * 87    07/01/30 19:21 Tsujimura543
 * �^�O�̈ꗗ�擾�A�^�O�̍폜�A�^�O�̒u���Ɋ֘A����֐��̃v���g�^�C�v�錾
 * ��ǉ�
 * 
 * 86    07/01/29 17:50 Tsujimura543
 * TagList �\���̂�p�ӂ���
 * 
 * 85    07/01/19 15:37 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 84    07/01/18 22:41 Tsujimura543
 * getValue() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 83    07/01/18 16:57 Tsujimura543
 * putBookmarks() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 82    07/01/18 15:08 Tsujimura543
 * decodeString() �̃v���g�^�C�v�錾���폜
 * 
 * 81    07/01/18 14:55 Tsujimura543
 * justify() �� decodeString() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 80    07/01/17 21:41 Tsujimura543
 * deleteHtmlTags() �� getBlueDot.c ���番���A�Ɨ�������
 * 
 * 79    06/12/25 23:37 Tsujimura543
 * loginBlogPet() �ɑ�4������ǉ�
 * 
 * 78    06/12/25 15:07 Tsujimura543
 * any2euc() ��ǉ�
 * 
 * 77    06/12/21 21:19 Tsujimura543
 * JoltMark�AFC2BOOKMARK�A�uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 76    06/12/07 15:56 Tsujimura543
 * getDateTimeFromDateString() �̃v���g�^�C�v�錾�Ɖ����ǉ�
 * 
 * 74    06/12/06 19:44 Tsujimura543
 * inputLivedoorFeed() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 73    06/12/06 18:55 Tsujimura543
 * �u���J��ԁv�̒l�����肵��
 * 
 * 72    06/12/06 17:59 Tsujimura543
 * �u���J��ԁv�̒l���`����
 * 
 * 71    06/12/06 17:55 Tsujimura543
 * NETSCAPE_BOOKMARK_FILE_1�`���ł̃u�b�N�}�[�N���o�͎���
 * Shift_JIS �ł̏o�͂��I���ł���悤�ɂ���
 * 
 * 70    06/11/17 15:25 Tsujimura543
 * getEvaluation() �ɑ�2������ǉ�
 * 
 * 69    06/11/17 14:47 Tsujimura543
 * getEvaluation() ��ǉ�
 * 
 * 68    06/11/14 15:53 Tsujimura543
 * chcode() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 67    06/11/14 15:44 Tsujimura543
 * unescapeURL() �� any2utf() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 66    06/11/13 20:37 Tsujimura543
 * MyClip �\���̂���� MyClipEx �\���̓��� Web�y�[�W URL �L���̈��
 * �T�C�Y��2�{�ɂ���
 * 
 * 65    06/11/10 20:07 Tsujimura543
 * strncmpi() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 64    06/11/10 19:26 Tsujimura543
 * �u���E�U�̃u�b�N�}�[�N����荞��/�u���E�U�Ɏ�荞�߂�`���̃u�b�N�}�[�N
 * �t�@�C���𐶐�����@�\���T�|�[�g���邽�߂̏���
 * 
 * 63    06/10/26 22:54 Tsujimura543
 * �u���[�J��OPML�v�ɑΉ�
 * 
 * 62    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 61    06/10/05 16:32 Tsujimura543
 * POOKMARK Airline �֘A�̃v���g�^�C�v�錾��ǉ� (�擾�����A�폜����)
 * 
 * 60    06/10/05 16:31 Tsujimura543
 * skipToNextItemWithSeparator() �̒�`�� getNiftyClip.c ����ړ�
 * 
 * 59    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline �ɑΉ�
 * 
 * 58    06/09/29 18:59 Tsujimura543
 * newsing (�̓o�^)�֘A�̃v���g�^�C�v�錾��ǉ�
 * 
 * 57    06/09/28 21:58 Tsujimura543
 * �u�b�N�}�[�N�ҏW�_�C�A���O�ł́u�]���v�ݒ���T�|�[�g
 * 
 * 56    06/09/26 16:11 Tsujimura543
 * MyClip �\���̂̃����o��ǉ� (�u�]���v�@�\�Ή�����)
 * 
 * 55    06/09/22 21:40 Tsujimura543
 * allocateMyClipIfNecessary(), allocateMyClipExIfNecessary() ��ǉ�
 * 
 * 54    06/08/25 18:10 Tsujimura543
 * get1470net() �̃v���g�^�C�v�錾��ύX
 * 
 * 53    06/08/22 17:48 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 52    06/08/22 16:59 Tsujimura543
 * enum authenticationType �̒�`�� myClip.h ���Ɉڂ���
 * 
 * 51    06/08/22 16:03 Tsujimura543
 * MyClipEx �̒�`��ǉ�
 * 
 * 50    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 49    06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 48    06/08/18 15:04 Tsujimura543
 * getEcNaviClipUserID() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 47    06/07/21 21:09 Tsujimura543
 * �j�t�e�B�N���b�v�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 46    06/07/21 20:51 Tsujimura543
 * EC�i�r�l�C�j���[�X�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤��
 * ����)
 * 
 * 45    06/07/21 20:17 Tsujimura543
 * BlogPeople Tags �̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 44    06/07/21 17:48 Tsujimura543
 * livedoor�N���b�v�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 43    06/07/15 0:56 Tsujimura543
 * 1470.net���j���[�A���łւ́u�o�^�v�ɑΉ�
 * 
 * 42    06/07/12 17:34 Tsujimura543
 * �h���R��RSS(��Clip!)�̎擾�A�����ɑΉ�
 * 
 * 41    06/07/11 22:49 Tsujimura543
 * EC�i�r�l�C�j���[�X�̃u�b�N�}�[�N�o�^�Ґ����\������悤�ɂ���
 * (�u�b�N�}�[�N�o�^���/EditBookmarkDialog)
 * 
 * 40    06/07/07 19:34 Tsujimura543
 * �j�t�e�B�N���b�v�̎擾�A�����ɑΉ�
 * 
 * 39    06/07/06 19:53 Tsujimura543
 * livedoor�N���b�v�̎擾�A�����ɑΉ�
 * 
 * 38    06/07/03 13:35 Tsujimura543
 * getNumberOfHatenaBookmark() ��ǉ�
 * 
 * 37    06/06/30 19:43 Tsujimura543
 * EC�i�r�l�C�j���[�X�̎擾�A�����ɑΉ�
 * 
 * 36    06/06/29 19:04 Tsujimura543
 * loginNifty() �� loginNiftyClip() �ɖ��̕ύX
 * 
 * 35    06/06/29 18:47 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 34    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 33    06/06/28 15:54 Tsujimura543
 * �u�b�N�}�[�N�o�^�Ґ��𒲂ׂĕ\������@�\��ǉ�
 * 
 * 32    06/06/23 17:06 Tsujimura543
 * getFlog() ��ǉ�
 * 
 * 31    06/06/20 16:29 Tsujimura543
 * isWhiteSpace() �� myClip.h �ֈړ�
 * 
 * 30    06/06/20 16:25 Tsujimura543
 * iskanji1(), iskanji2() �� myClip.h �ֈړ�
 * 
 * 29    06/06/19 20:25 Tsujimura543
 * getBPhash() �̃v���g�^�C�v�錾�� bookey.h ���� myClip.h �ֈڂ�
 * 
 * 28    06/05/31 21:11 Tsujimura543
 * loginFlog() �� putFlog() ��ǉ�
 * 
 * 27    06/05/24 16:21 Tsujimura543
 * getASIN() ��ǉ�
 * 
 * 26    06/05/23 14:08 Tsujimura543
 * getTitle() �̒��ӏ���(�R�����g)��ǉ�
 * 
 * 25    06/05/23 13:53 Tsujimura543
 * getTitle() �� extractTags() �̘A�g�ɂ��u�͂Ăȃu�b�N�}�[�N�v�����
 * �^�O���擾���T�|�[�g
 * 
 * 24    06/04/06 22:16 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�́u�R���N�V�����v�ւ̒ǉ��ɑΉ�
 * 
 * 23    06/03/28 17:04 Tsujimura543
 * loginDrecomRSS() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 22    06/03/28 16:28 Tsujimura543
 * putDrecomRSS() ��ǉ�
 * 
 * 21    06/02/17 21:00 Tsujimura543
 * getUsernameForBlogPeopleTags() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 20    05/11/30 23:43 Tsujimura543
 * extractTags() �̑�3������ (I) ���� (I/O) �֕ύX
 * 
 * 19    05/11/30 23:27 Tsujimura543
 * extractTags() ��ǉ�
 * 
 * 18    05/11/30 14:32 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̃^�O��3�܂Ł�10�܂ŁA�R�����g��50�����܂Ł�
 * 100�����܂łɊe�X�ύX���ꂽ�̂ɔ����C�������{
 * 
 * 17    05/11/02 13:51 Tsujimura543
 * getStringImplanted() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 16    05/10/24 17:37 Tsujimura543
 * getTitle() �� Account-auto-discovery �ɑΉ�����悤�g������
 * 
 * 15    05/10/20 20:07 Tsujimura543
 * putMMmemo() ��ǉ�
 * 
 * 14    05/10/19 16:47 Tsujimura543
 * loginMMmemo() ��ǉ�
 * 
 * 13    05/10/18 21:54 Tsujimura543
 * getMMmemo() ��ǉ�
 * 
 * 12    05/10/18 14:32 Tsujimura543
 * putBPT() �� putBPTags() �ɖ��̕ύX
 * 
 * 11    05/10/18 14:30 Tsujimura543
 * putBPT() ��ǉ�
 * 
 * 10    05/10/18 13:40 Tsujimura543
 * loginBlogPeople() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 9     05/10/14 15:09 Tsujimura543
 * getTitle() ��ǉ�
 * 
 * 8     05/10/11 18:03 Tsujimura543
 * putDelicious() �� putHB() �̑�3������ const �C���q��t��
 * 
 * 7     05/10/03 23:06 Tsujimura543
 * NUM_OF_INFO_PER_HATENA_API �� #define �� myClip.h �Ɉڂ�
 * 
 * 6     05/10/03 11:59 Tsujimura543
 * tags �̗̈�� 80 �� 160 �ɑ��₵��
 * 
 * 5     05/09/30 17:41 Tsujimura543
 * outputOPML() �Ɉ�����ǉ�
 * 
 * 4     05/09/28 23:14 Tsujimura543
 * �u�b�N�}�[�N�ǂݏo���A�o�^�e�����̃v���g�^�C�v�錾��ǉ�
 * 
 * 3     05/09/28 14:55 Tsujimura543
 * inputOpml() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 2     05/09/28 13:14 Tsujimura543
 * outputOPML() �֘A�̒�`�� myClip.h �Ɉړ�
 * 
 * 1     05/09/28 12:07 Tsujimura543
 * �u�b�N�}�[�N�؂�o���c�[���̃\�[�X����؂�o��(�����Ɨ�)
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
        const char *url,        /* (I) ���YWeb�y�[�W��URL                  */
        char       *accountName,/* (O) AccountName-auto-discovery �Ŏ擾�� */
                                /*     �����YWeb�y�[�W�̃I�[�i�[��(�͂Ă�) */
                                /*     �A�J�E���g��                        */
        char       *hatenaID,   /* (I) �͂Ă�ID(���łɎ������g�œo�^�ς݂� */
                                /*     �ۂ��̃`�F�b�N���s�Ȃ��Ƃ��Ɏw��)   */
        char       **hatenaTags,/* (O) �͂ău����擾�����^�O���          */
                                /*     (����: �{�֐����Ŋi�[�p�̗̈���m�� */
                                /*      ����B�{�֐��̌Ăяo�����ŗ̈�̉� */
                                /*      �����s�Ȃ�����)                    */
        BOOL       *posted      /* (O) ���łɎ������g�œo�^�ς݂��ۂ�      */
    );

void
extractTags(
        const char *url,        /* (I)   ���YWeb�y�[�W��URL         */
        char       **tags,      /* (O)   �^�O���                   */
        char       **hatenaTags,/* (I/O) �͂ău����擾�����^�O��� */
        int        *numOfTags,  /* (I/O) �^�O���̐�               */
        BOOL       *stat1470net,/* (I/O) 1470.net �̉ғ���        */
        const char *yahooAppID  /* (I)   Yahoo! �A�v���P�[�V����ID  */
    );


/* �F�ؕ��� */
typedef enum authenticationType {
    AK_ORIGINAL = 0,        /* �Ǝ��F��                         */
    AK_TYPEKEY,             /* TypeKey                          */
    AK_HATENA,              /* �͂ĂȔF��API                    */
    AK_TYPEKEY_HATENA,      /* TypeKey �D��A�͂ĂȔF��API ���p */
    AK_HATENA_TYPEKEY,      /* �͂ĂȔF��API �D��ATypeKey ���p */
    AK_JUGEMKEY,            /* JugemKey                         */
    AK_YAHOOJAPAN_BBAUTH,   /* Yahoo! Japan  BBAuth �F��        */
    AK_FLICKR,              /* Flickr                           */
    AK_OAUTH                /* OAuth                            */
}   AUTH_TYPE;


/* �u�b�N�}�[�N��� */
typedef struct myClip   {
    char    title[MAX_DESCRIPTION_LEN];     /* Web�y�[�W �薼            */
    char    url[MAX_URLLENGTH * 2];         /* Web�y�[�W URL             */
    char    tags[MAX_DESCRIPTION_LEN];      /* tag (����)                */
    char    comment[MAX_DESCRIPTION_LEN];   /* �R�����g                  */
    int     yyyy;                           /* �o�^���� (�N)             */
    int     mm;                             /* �o�^���� (��)             */
    int     dd;                             /* �o�^���� (��)             */
    int     HH;                             /* �o�^���� (��)             */
    int     MM;                             /* �o�^���� (��)             */
    int     SS;                             /* �o�^���� (�b)             */
    BOOL    asin;                           /* �R���N�V����              */
    int     publication;                    /* ���J��� (public/private) */
    int     evaluation;                     /* �]��#1 (5�i�K + ���]��)   */
    int     rating;                         /* �]��#2 (3�i�K)            */
    int     affirmation;                    /* �]��#3 (�m��/�ے�)        */
}   MyClip;

typedef struct myClipForDelete  {
    char    title[MAX_DESCRIPTION_LEN];   /* �薼                           */
    char    url[MAX_URLLENGTH * 2];       /* �u�b�N�}�[�N�ς� Web�y�[�W URL */
    char    tags[MAX_DESCRIPTION_LEN];    /* tag (����)                     */
    char    comment[MAX_DESCRIPTION_LEN]; /* �R�����g                       */
    char    entryID[MAX_BLOGIDLENGTH + 1];/* �폜�p�Ώۂ̃G���g��ID         */
    char    remarks[MAX_KEYLENGTH + 1];   /* �폜�p�n�b�V���L�[             */
}   MyClipEx;

typedef struct tagList  {
#define MAX_TAG_LENGTH  512             /* �^�O�ő咷 (�b��l) */
    char    tag[MAX_TAG_LENGTH];        /* tag (����)          */
}   TagList;

/* �]��#1 */
#define EVL_NONE        0       /* ���]�� */
#define EVL_REQUESTED   (-1)    /* �v�]�� */
#define EVL_ONE         1       /* �]��1  */
#define EVL_TWO         2       /* �]��2  */
#define EVL_THREE       3       /* �]��3  */
#define EVL_FOUR        4       /* �]��4  */
#define EVL_FIVE        5       /* �]��5  */

/* �]��#2 */
#define RAT_NONE        0       /* ���]�� */
#define RAT_REQUESTED   (-1)    /* �v�]�� */
#define RAT_ONE         1       /* �]��1  */
#define RAT_TWO         2       /* �]��2  */
#define RAT_THREE       3       /* �]��3  */

/* �]��#3 */
#define AFF_NONE        0       /* ���]�� */
#define AFF_REQUESTED   (-1)    /* �v�]�� */
#define AFF_GOOD        1       /* ��     */
#define AFF_BAD         2       /* �~     */

/* ���J��� */
#define PUB_REQUESTED   (-1)    /* �v�ݒ�(�F�l�ɂ̂݌��J��Ή�) */
#define PUB_REQUESTED2  (-2)    /* �v�ݒ�(�F�l�ɂ̂݌��J�Ή�)   */
#define PUB_EVERYONE    0       /* (�S����)���J/�p�u���b�N      */
#define PUB_FRIENDS     1       /* �F�l�ɂ̂݌��J               */
#define PUB_PRIVATE     2       /* ����J/�v���C�x�[�g          */

/* �������̈�m�ۏ��� */
MyClip  *
allocateMyClipIfNecessary(
        MyClip **mp,        /* (I/O) �m�ۂ���/�m�ۍς݃������̈�     */
        int    unit,        /* (I)   1��ӂ�̃������̈抄�蓖�ĒP�� */
        int    *cnt,        /* (I/O) ���������蓖�Ď��s��          */
        int    numOfClips   /* (I)   �i�[�ς݃u�b�N�}�[�N��          */
    );

MyClipEx    *
allocateMyClipExIfNecessary(
        MyClipEx **mp,      /* (I/O) �m�ۂ���/�m�ۍς݃������̈�     */
        int      unit,      /* (I)   1��ӂ�̃������̈抄�蓖�ĒP�� */
        int      *cnt,      /* (I/O) ���������蓖�Ď��s��          */
        int      numOfClips /* (I)   �i�[�ς݃u�b�N�}�[�N��          */
    );

/* ��r(�^�C���X�^���v�AURL�̏����Ƀ\�[�g�����ʂȂǂŎg�p) */
int
compareMyClip( const void *elem1, const void *elem2 );


/* �u�b�N�}�[�N�擾���� */
MyClip  *
getMyClip(
        const char *userName,   /* (I) ���[���A�h���X */
        const char *password,   /* (I) �p�X���[�h     */
        int        *numOfClips  /* (O) �u�b�N�}�[�N�� */
    );

MyClip  *
getDelicious(
        const char *username,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        int        *numOfClips  /* (O) �u�b�N�}�[�N�� */
    );

MyClip  *
getBlueDot(
        const char *username,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        int        *numOfClips  /* (O) �u�b�N�}�[�N�� */
    );

MyClip  *
getHB(
        const char *username,   /* (I) ���[�U��       */
        int        *numOfClips  /* (O) �u�b�N�}�[�N�� */
    );

MyClip  *
getMMmemo(
        const char *username,   /* (I) TypeKey���[�U��   */
        const char *password,   /* (I) TypeKey�p�X���[�h */
        int        *numOfClips  /* (O) �u�b�N�}�[�N��    */
    );                          /* ����: MM/Memo �� TypeKey �ɂ��F�� */
                                /* �𗘗p���Ă���                      */
MyClip  *
getFlog(
        const char *userName,   /* (I) login���Ɏg�����[���A�h���X */
        const char *password,   /* (I) login���Ɏg���p�X���[�h     */
        const char *userID,     /* (I) ���[�UID                    */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�    */
    );

MyClip  *
getEcNaviClip(
        const char *userName,   /* (I) login���Ɏg�����[���A�h���X    */
        const char *password,   /* (I) login���Ɏg���p�X���[�h        */
        const char *userName2,  /* (I) �F�ؗp���[�U��(Yahoo! Japan)   */
        const char *password2,  /* (I) �F�ؗp�p�X���[�h(Yahoo! Japan) */
        AUTH_TYPE  authType,    /* (I) �F�؃^�C�v                     */
        const char *userID,     /* (I) �L�Җ�                         */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�       */
    );

MyClip  *
getLivedoorClip(
        const char *userName,   /* (I) livedoor ID                    */
        const char *password,   /* (I) �p�X���[�h (�V�[�N���b�g���[�h */
                                /*     �̃u�b�N�}�[�N���擾�������ꍇ */
                                /*     �ɕK�v)                        */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    );

MyClip  *
getNiftyClip(
        const char *userName,   /* (I) @nifty ID �܂��� PLEASY ID �������� */
                                /*     ���[�U�[��                          */
        const char *password,   /* (I) �p�X���[�h (userName �� @nifty ID   */
                                /*     �܂��� PLEASY ID ���w�肵���Ƃ��̂� */
                                /*     �K�{)                               */
        const char *apiKey,     /* (I) API�L�[                             */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑���      */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�            */
    );

MyClip  *
getDrecomRSS(
        const char *userName,   /* (I) login���Ɏg�����[���A�h���X */
        const char *password,   /* (I) login���Ɏg���p�X���[�h     */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�    */
    );

MyClip  *
get1470net(
        const char *username,   /* (I) TypeKey�F�ؗp���[�U��   */
        const char *password,   /* (I) TypeKey�F�ؗp�p�X���[�h */
        const char *username2,  /* (I) �͂ĂȔF�ؗp���[�U��    */
        const char *password2,  /* (I) �͂ĂȔF�ؗp�p�X���[�h  */
        AUTH_TYPE  authType,    /* (I) �F�؃^�C�v              */
        int        *numOfClips  /* (O) �u�b�N�}�[�N��          */
    );                          /* ����: 1470.net �� TypeKey �� �͂Ă� */
                                /*       �F��API �ɂ��F�؂�2�̔F�� */
                                /*       ���@��I���ł���悤�ɂȂ���  */
                                /*       ����                          */
MyClip  *
getPookmark(
        const char *userName,   /* (I) JugemKey ID (JUGEM���[�U�[��)  */
        const char *password,   /* (I) �p�X���[�h                     */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�       */
    );

MyClip  *
getJoltMark(
        const char *userName,   /* (I) ���[�U��                       */
        const char *password,   /* (I) �p�X���[�h (����J�̃u�b�N�}�[ */
                                /*     �N���擾�������ꍇ�ɕK�v)      */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    );

MyClip  *
getFC2Bookmark(
        const char *userName,   /* (I) ���[�U�� (FC2ID �܂��̓��[���A */
                                /*     �h���X)                        */
        const char *password,   /* (I) �p�X���[�h (����J�̃u�b�N�}�[ */
                                /*     �N���擾�������ꍇ�ɕK�v [���� */
                                /*     �ɁAuserName �Ŏw�肷��̂�    */
                                /*     FC2ID �ł͂Ȃ��A���[���A�h���X */
                                /*     �ł���K�v������])             */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    );

MyClip  *
getBlogPet(
        const char *userName,   /* (I) ���[�U��                       */
        const char *password,   /* (I) �p�X���[�h (����J�̃u�b�N�}�[ */
                                /*     �N���擾�������ꍇ�ɕK�v)      */
        int        *numOfClips  /* (O) ���ۂɎ擾�����u�b�N�}�[�N�̐� */
    );

MyClip  *
getYJbookmark(
        const char *userName,   /* (I) Yahoo! Japan ID                */
        const char *password,   /* (I) �p�X���[�h                     */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�       */
    );

MyClip  *
getYahooBookmarks(
        const char *userName,   /* (I) Yahoo! ID                      */
        const char *password,   /* (I) �p�X���[�h                     */
        int        *total,      /* (O) ���Y���[�U�̃u�b�N�}�[�N�̑��� */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐�       */
    );

MyClip  *
getDiigo(
        const char *username,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        int        *numOfClips  /* (O) �u�b�N�}�[�N�� */
    );

MyClip  *
getLocalOpml(
        const char *filename,   /* (I) OPML�t�@�C����           */
        int        *numOfClips  /* (O) �擾�����u�b�N�}�[�N�̐� */
    );

/* �u�b�N�}�[�N�o�^���� */
void
putDelicious(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putBlueDot(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putHB(
        const char   *userName,  /* (I) �͂Ă�ID                       */
        const char   *password,  /* (I) �p�X���[�h                     */
        BOOL         useMyTitle, /* (I) �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    );

void
putBPTags(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X) */
        const char   *password,  /* (I) �p�X���[�h               */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���         */
        int          numOfClips  /* (I) �u�b�N�}�[�N��           */
    );

void
putMMmemo(
        const char   *userName,  /* (I) TypeKey���[�U��   */
        const char   *password,  /* (I) TypeKey�p�X���[�h */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���  */
        int          numOfClips  /* (I) �u�b�N�}�[�N��    */
    );

void
putDrecomRSS(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X) */
        const char   *password,  /* (I) �p�X���[�h               */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���         */
        int          numOfClips  /* (I) �u�b�N�}�[�N��           */
    );

void
putFlog(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X) */
        const char   *password,  /* (I) �p�X���[�h               */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���         */
        int          numOfClips  /* (I) �u�b�N�}�[�N��           */
    );

void
putLivedoorClip(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putEcNaviClip(
        const char   *userName,  /* (I) ���[�U��                       */
        const char   *password,  /* (I) �p�X���[�h                     */
        const char   *userName2, /* (I) �F�ؗp���[�U��(Yahoo! Japan)   */
        const char   *password2, /* (I) �F�ؗp�p�X���[�h(Yahoo! Japan) */
        AUTH_TYPE    authType,   /* (I) �F�؃^�C�v                     */
        BOOL         useMyTitle, /* (I) �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    );

void
putNiftyClip(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const char   *apiKey,    /* (I) API�L�[          */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
put1470net(
        const char   *userName,  /* (I) �F�ؗp���[�U��         */
        const char   *password,  /* (I) �F�ؗp�p�X���[�h       */
        const char   *userName2, /* (I) �F�ؗp���[�U��(�\��)   */
        const char   *password2, /* (I) �F�ؗp�p�X���[�h(�\��) */
        AUTH_TYPE    authType,   /* (I) �F�؃^�C�v             */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���       */
        int          numOfClips  /* (I) �u�b�N�}�[�N��         */
    );

void
putNewsing(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X)       */
        const char   *password,  /* (I) �p�X���[�h                     */
        const char   *userName2, /* (I) �F�ؗp���[�U��(Yahoo! Japan)   */
        const char   *password2, /* (I) �F�ؗp�p�X���[�h(Yahoo! Japan) */
        AUTH_TYPE    authType,   /* (I) �F�؃^�C�v                     */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    );

void
putPookmark(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X) */
        const char   *password,  /* (I) �p�X���[�h               */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���         */
        int          numOfClips  /* (I) �u�b�N�}�[�N��           */
    );

void
putJoltMark(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putFC2Bookmark(
        const char   *userName,  /* (I) ���[�U�� (FC2ID) */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putBlogPet(
        const char   *userName,  /* (I) ���[�U��                       */
        const char   *password,  /* (I) �p�X���[�h                     */
        BOOL         useMyTitle, /* (I) �^�C�g����Ǝ��ɐݒ肷�邩�ۂ� */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���               */
        int          numOfClips  /* (I) �u�b�N�}�[�N��                 */
    );

void
putTwitter(
        const char   *userName,  /* (I) ���[�U��(���[���A�h���X) */
        const char   *password,  /* (I) �p�X���[�h               */
        const char   *token,     /* (I) �A�N�Z�X�g�[�N��         */
        const char   *secret,    /* (I) �A�N�Z�X�g�[�N���閧��   */
        AUTH_TYPE    authType,   /* (I) �F�؃^�C�v               */
        const char   *version,   /* (I) userAgent �Ő�           */
        const char   *url,       /* (I) userAgent �֘AWeb�y�[�W  */
        const char   *resource,  /* (I) userAgent �֘AXML        */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���         */
        int          numOfClips  /* (I) �u�b�N�}�[�N��           */
    );

void
putYJbookmark(
        const char   *userName,  /* (I) ���[�U��(Yahoo! Japan ID) */
        const char   *password,  /* (I) �p�X���[�h                */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���          */
        int          numOfClips  /* (I) �u�b�N�}�[�N��            */
    );

void
putYahooBookmarks(
        const char   *userName,  /* (I) ���[�U��(Yahoo! ID) */
        const char   *password,  /* (I) �p�X���[�h          */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���    */
        int          numOfClips  /* (I) �u�b�N�}�[�N��      */
    );

void
putTimelog(
        const char   *userName,  /* (I) ���[�U��                */
        const char   *password,  /* (I) �p�X���[�h              */
        const char   *version,   /* (I) userAgent �Ő�          */
        const char   *url,       /* (I) userAgent �֘AWeb�y�[�W */
        const char   *resource,  /* (I) userAgent �֘AXML       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N���        */
        int          numOfClips  /* (I) �u�b�N�}�[�N��          */
    );

void
putDigg(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putTumblr(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const char   *group,     /* (I) ���e��tumbleblog */
        const char   *version,   /* (I) userAgent �Ő�   */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putDiigo(
        const char   *userName,  /* (I) ���[�U��         */
        const char   *password,  /* (I) �p�X���[�h       */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

void
putLocalOpml(
        const char   *filename,  /* (I) OPML�t�@�C����   */
        const MyClip *mp,        /* (I) �u�b�N�}�[�N��� */
        int          numOfClips  /* (I) �u�b�N�}�[�N��   */
    );

/* �u�b�N�}�[�N�o�^�������C�����[�v */
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

/* �u�b�N�}�[�N�o�^�Ґ��擾���� */
char    *getUsersOfHatenaBookmark( const char *url );
char    *getUsersOfDelicious( const char *url );
char    *getUsersOfBlueDot( const char *url );
char    *getUsersOfMMmemo( const char *url, BOOL *stat1470net );
char    *getUsersOfECnaviClip( const char *url );
char    *getUsersOfLivedoorClip( const char *url );
char    *getUsersOfDigg( const char *url );
char    *getUsersOfNiftyClip( const char *url );

/* �^�O�ꗗ�̎擾 */
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

/* �^�O�̍폜 */
BOOL
removeTagFromBookmarksOnNiftyClip(
        const char *username,
        const char *password,
        const char *tag );

/* �^�O�̒u�� */
BOOL
renameTagFromBookmarksOnNiftyClip(
    const char *username,
    const char *password,
    const char *oldTag,
    const char *newTag );

/* �u�b�N�}�[�N���t�@�C���ɏ����o������ */
/* outputOPML() �̑�4���� codeChange �̒l: �����R�[�h�ϊ� */
#define UTF8        0   /* ���ϊ�(UTF-8 �̂܂�)           */
#define SJIS2UTF    1   /* Shift_JIS �� UTF-8 �ϊ������s  */
#define EUC2UTF     2   /* EUC-JP �� UTF-8 �ϊ������s     */
/* ��L�ɉ����āAoutputBookmarkHtml() �ł͈ȉ����g�p */
#define SJIS        4   /* EUC-JP,UTF-8 �� Shift_JIS �ϊ������s */

void
outputOPML(
        const MyClip *myClip,    /* (I) �u�b�N�}�[�N��� */
        int          numOfClips, /* (I) �u�b�N�}�[�N��   */
        const char   *title,     /* (I) �u�b�N�}�[�N���� */
        int          codeChange, /* (I) �����R�[�h�ϊ�   */
        FILE         *fp         /* (I/O) �u�b�N�}�[�N�����o���� */
                                 /*       �t�@�C���X�g���[��     */
    );  // OPML�t�@�C���ɏ����o��

void
outputBookmarkHtml(
        const MyClip *myClip,    /* (I) �u�b�N�}�[�N��� */
        int          numOfClips, /* (I) �u�b�N�}�[�N��   */
        const char   *title,     /* (I) �u�b�N�}�[�N���� */
        int          codeChange, /* (I) �����R�[�h�ϊ�   */
        FILE         *fp         /* (I/O) �u�b�N�}�[�N�����o���� */
                                 /*       �t�@�C���X�g���[��     */
    );  // NETSCAPE-Bookmark-file-1 �`���� html�t�@�C���ɏ����o��

void
outputOpera6Adr(
        const MyClip *myClip,    /* (I) �u�b�N�}�[�N��� */
        int          numOfClips, /* (I) �u�b�N�}�[�N��   */
        const char   *title,     /* (I) �u�b�N�}�[�N���� */
        int          codeChange, /* (I) �����R�[�h�ϊ�   */
        FILE         *fp         /* (I/O) �u�b�N�}�[�N�����o���� */
                                 /*       �t�@�C���X�g���[��     */
    );  // opera6.adr �`���̃e�L�X�g�t�@�C���ɏ����o��

void
outputHatenaFeed(
        const MyClip *myClip,    /* (I) �u�b�N�}�[�N��� */
        int          numOfClips, /* (I) �u�b�N�}�[�N��   */
        const char   *title,     /* (I) �u�b�N�}�[�N���� */
        int          codeChange, /* (I) �����R�[�h�ϊ�   */
        FILE         *fp         /* (I/O) �u�b�N�}�[�N�����o���� */
                                 /*       �t�@�C���X�g���[��     */
    );  // �͂Ăȃu�b�N�}�[�N�� Atom �t�B�[�h�`����XML�t�@�C���ɏ����o��

void
outputDeliciousXML(
        const MyClip *myClip,    /* (I)   �u�b�N�}�[�N���       */
        int          numOfClips, /* (I)   �u�b�N�}�[�N��         */
        FILE         *fp,        /* (I/O) �u�b�N�}�[�N�����o���� */
                                 /*       �t�@�C���X�g���[��     */
        const char   *userName   /* (I)   del.icio.us ���[�U��   */
    );  // del.icio.us �� posts/all �Ŏ擾�\�Ȍ`���Ɠ����`����XML�t�@�C����
        // �����o��

/* �u�b�N�}�[�N���t�@�C������ǂݎ�鏈�� */
MyClip  *
inputOPML(
        int  *numOfClips,   /* (O) �u�b�N�}�[�N��                           */
        FILE *fp            /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���X�g���[�� */
    );  // OPML�t�@�C������ǂݎ��

MyClip  *
inputBookmarkHtml(
        int  *numOfClips,   /* (O) �u�b�N�}�[�N��                           */
        FILE *fp            /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���X�g���[�� */
    );  // NETSCAPE-Bookmark-file-1 �`���� html�t�@�C������ǂݎ��

MyClip  *
inputOpera6Adr(
        int  *numOfClips,   /* (O) �u�b�N�}�[�N��                           */
        FILE *fp            /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���X�g���[�� */
    );  // opera6.adr �`���̃e�L�X�g�t�@�C������ǂݎ��

MyClip  *
inputHatenaFeed(
        int  *numOfClips,   /* (O) �u�b�N�}�[�N��                           */
        FILE *fp            /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���X�g���[�� */
    );  // �͂Ăȃu�b�N�}�[�N�� RSS/Atom �t�B�[�h�`����XML�t�@�C������ǂݎ��

MyClip  *
inputLivedoorFeed(
        int  *numOfClips,   /* (O) �u�b�N�}�[�N��                           */
        FILE *fp            /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���X�g���[�� */
    );  // livedoor�N���b�v�� RSS 2.0 �t�B�[�h�`����XML�t�@�C������ǂݎ��

MyClip  *
inputDeliciousXML(
        int    *numOfClips, /* (O) �u�b�N�}�[�N��                           */
        FILE   *fp,         /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���X�g���[�� */
        size_t fileSize     /* (I) �u�b�N�}�[�N�ǂݎ���t�@�C���T�C�Y     */
    );  // del.icio.us �� posts/all �Ŏ擾�\�Ȍ`����XML�t�@�C������ǂݎ��

/* for �͂Ăȃu�b�N�}�[�N REST API */
#define NUM_OF_INFO_PER_HATENA_API  50  /* 1���API���s�Ŏ擾������ */
            /* ����: ���ۂ�1���API���s�Ŏ擾�ł���u�b�N�}�[�N����20�� */
            /*       (�f�t�H���g�A�ݒ�ύX�\)                         */


/* MM/Memo �֘A�Ǝ����� */
int
loginMMmemo(
        const char *username,  // (I)   TypeKey���[�U��
        const char *password,  // (I)   TypeKey�p�X���[�h
        char       *cookie,    // (I/O) �N�b�L�[
        char       *userID     // (O)   MM/Memo ���[�UID
    );

int
login1470net(
        const char *username,  // (I)   �F�ؗp���[�U��
        const char *password,  // (I)   �F�ؗp�p�X���[�h
        const char *username2, // (I)   �͂Ă�ID
        const char *password2, // (I)   �͂Ăȃp�X���[�h
        AUTH_TYPE  authType,   // (I)   �F�؎�� (TypeKey, �͂ĂȔF��API)
        char       *cookie,    // (I/O) �N�b�L�[
        char       *userID     // (O)   1470.net���j���[�A���� ���[�U��
    );

/* �h���R��RSS �֘A�Ǝ����� */
int
loginDrecomRSS(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* Flog �֘A�Ǝ����� */
int
loginFlog(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* livedoor�N���b�v �֘A�Ǝ����� */
int
loginLivedoorClip(
        const char *userName,   // (I)   ���[�U�� (livedoor ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

char    *
getApiKeyOnLivedoorClip(
        const char *username,   // (I) ���[�U�� (livedoor ID)
        const char *password,   // (I) �p�X���[�h
        char       *apiKey      // (O) API�L�[
    );  /* �udel.icio.us �݊�API�v�p API�L�[�̎擾 */

/* Buzzurl �֘A�Ǝ�����l*/      
int
loginEcNavi(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

int
loginEcNaviOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    );  /* Yahoo! Japan ID �� Buzzurl �� login ���� */

char    *
getEcNaviClipUserID(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X or Y!J ID)
        const char *password,   // (I)   �p�X���[�h
        AUTH_TYPE  auth_type,   // (I)   �F�؃^�C�v
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    );

/* �j�t�e�B�N���b�v �֘A�Ǝ����� */
int
loginNiftyClip(
        const char *userName,   // (I)   ���[�U�� (@nifty ID �܂��� PLEASY ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

char    *
getApiKeyOnNiftyClip(
        const char *username,   // (I) ���[�U�� (livedoor ID)
        const char *password,   // (I) �p�X���[�h
        char       *apiKey      // (O) API�L�[
    );  /* API�L�[�̎擾 */

/* �͂Ăȃu�b�N�}�[�N�֘A�Ǝ����� */
char    *
encodeURLforHatena( const char *url );

int
getNumberOfHatenaBookmark(
        const char *username,
        const char *password
    );

/* newsing �֘A�Ǝ����� */
int
loginNewsing(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

int
loginNewsingOnBBAuth(
        const char *username,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        size_t     *cookieSize  // (I/O) �N�b�L�[������
    );

/* POOKEY (jugemkey) �֘A�Ǝ����� */
int
loginJugemkey(
        const char *userName,   // (I)   jugemkey (JUGEM ���[�U��)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* JoltMark �֘A�Ǝ����� */
int
loginJoltMark(
        const char *userName,   // (I)   ���[�U��
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* FC2BOOKMARK �֘A�Ǝ����� */
int
loginFC2Bookmark(
        const char *userName,   // (I)   ���[�U�� (���[���A�h���X)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        char       *uid,        // (O)   uid (FC2ID �̃��[�UID)
        char       *cc          // (O)   cc  (FC2BOOKMARK ��cc)
    );

/* BlogPet �C�ɂȂ�L�� �֘A�Ǝ����� */
int
loginBlogPet(
        const char *userName,   // (I)   ���[�U��
        const char *password,   // (I)   �p�X���[�h
        char       *cookie,     // (I/O) �N�b�L�[
        char       *userID      // (O)   ���[�UID
    );

/* Yahoo! �u�b�N�}�[�N �֘A�Ǝ����� */
int
loginYahooJapan(
        const char *userName,   // (I)   ���[�U�� (Yahoo! Japan ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* Yahoo! Bookmarks �֘A�Ǝ����� */
int
loginYahoo(
        const char *userName,   // (I)   ���[�U�� (Yahoo! ID)
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* digg �֘A�Ǝ����� */
int
loginDigg(
        const char *userName,   // (I)   ���[�U��
        const char *password,   // (I)   �p�X���[�h
        char       *cookie      // (I/O) �N�b�L�[
    );

/* del.icio.us �֘A�Ǝ����� */
MyClip  *
deliciousPosts2MyClip( DELICIOUS_POSTS *posts, int numOfPosts );

/* ���[�e�B���e�B�֐� */

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
 *      ������ src ����AstartString �� endString �ŋ��܂ꂽ������
 *      ������𒊏o(�������̂� dst �Ɋi�[)����
 *
 *          ��:
 *              src:         <p>abcd <strong>efg</strong> hijkl</p>
 *              startString: <strong>
 *              endString:   </strong>
 *            �̂Ƃ�
 *              getStringImplanted(dst, src, startString, endString);
 *            �����s����ƁAdst �ɂ�
 *              efg
 *            ���i�[�����
 */
char    *
getStringImplanted(
        char       *dst,        /* (O) ����           */
        const char *src,        /* (I) �����Ώە����� */
        const char *startString,/* (I) �J�n������     */
        const char *endString   /* (I) �I��������     */
    );

/*
 *  getEvaluation()
 *      MM/Memo �`���� title ����A�u�]���v�Ɩ{���́u�薼�v�𒊏o����
 */
int
getEvaluation( char *title, int changeCode );

/*
 *  getASIN()
 *      URL �Ɋ܂܂�� ASIN �����o��
 *      (amazon, �͂Ă� �� URL ���Ώ�)
 */
char    *
getASIN(
        const char *url,    /* (I) ��͑Ώ� URL */
        char       *asin    /* (O) ASIN ������  */
    );

/* �w�肳�ꂽ�����񒆂Ɋ܂܂�� html �^�O����菜�� */
char    *
deleteHtmlTags( char *text );

/* 
 *  getDateTimeFromDateString()
 *      ������\�킷�����񂩂�A�N���������b�����o��
 *        RFC822�`���AISO8601�`���A����шȉ��̌`���ɑΉ�
 *            yyyy[{/|-| }]mm[{/|-| }]dd HH[{:| }]MM[{:| }]SS [{+|-}dH[:]dM]
 *          -- RFC822�`��
 *            [�j��,] dd ���� {yy|yyyy} HH:MM:SS [{{+|-}dH[:]dM|GMT|JST|...}]
 *          -- ISO8601�`��
 *            yyyy[-]mm[-]ddTHH:MM:SS{Z|{+|-}dHdM}}
 *          �ȉ��̌`���ɂ͖��Ή�
 *            mm/dd/yy HH:MM:SS   (�� 03/01/05 ����
 *                                        2003�N1��5���Ȃ̂��A
 *                                        2005�N1��3���Ȃ̂��A
 *                                        2005�N3��1���Ȃ̂��A
 *                                    ���f�����˂� [��������
 *                                        ����3�N1��5���Ƃ�
 *                                    �����Ȃ��\��������]
 *            dd/mm/yy HH:MM:SS
 *            mm/dd/yyyy HH:MM:SS
 *            dd/mm/yyyy HH:MM:SS
 *          �Ȃ��A
 *            yyyy: �N(4��)
 *            yy:   �N(��2��)
 *            mm:   ��(1���܂���2��)
 *            dd:   ��(1���܂���2��)
 *            HH:   ��(1���܂���2��)
 *            MM:   ��(1���܂���2��)
 *            SS:   �b(1���܂���2��)
 *            dH:   UTC �Ƃ̎����̂����u���v����
 *            dM:   UTC �Ƃ̎����̂����u���v����
 *          �Ƃ���
 */
time_t
getDateTimeFromDateString(
        const char *date,   /* (I) �������(������) */
        int        *yyyy,   /* (O) �N               */
        int        *mm,     /* (O) ��               */
        int        *dd,     /* (O) ��               */
        int        *HH,     /* (O) ��               */
        int        *MM,     /* (O) ��               */
        int        *SS      /* (O) �b               */
    );

/* �w�肳�ꂽ������(Shift_JIS)���w�蕶���񒷂Ɋۂ߂� */
char *
adjustStringLength( char *p, int len );

/* �w�蕶�����ʂ̎w�蕶����ɒu������ */
BOOL
replaceString( char *target, const char *src, const char *dst );

/* JSON�`���Ŏ擾�����R���e���c�̃f�R�[�h */
char        *
decodeContents(
        char *contents  /* (I) �f�R�[�h�Ώۂ̃R���e���c */
                        /* (O) �f�R�[�h����             */
    );

/* �R���e���c��JSON�`���ւ̃G���R�[�h */
char    *
encodeContents( const char *contents );

/* ���[�e�B���e�B�}�N�� */
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
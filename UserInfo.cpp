/*
 * UserInfo.cpp  : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CUserInfo �N���X �C���v�������e�[�V���� �t�@�C��
 *          written by H.Tsujimura  6 Jun 2006
 *
 * $Log: /comm/bookey/UserInfo.cpp $
 * 
 * 4     09/06/22 22:31 tsupo
 * 0.63c��
 * 
 * 131   09/06/22 17:56 Tsujimura543
 * ���{�ꃂ�[�h�����p�ꃂ�[�h�ؑ֊֘A�A�C��
 * 
 * 3     09/06/18 0:53 tsupo
 * 0.63b��
 * 
 * 130   09/06/16 1:56 Tsujimura543
 * �u�ݒ�t�@�C�������Ă���悤�ł��B�v��\������������C��
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62��
 * 
 * 129   09/05/28 22:40 Tsujimura543
 * m_blogName ��ǉ�
 * 
 * 128   09/05/28 22:13 Tsujimura543
 * ����A�J�E���g�ŕ��� tumbleblog ���J�݂��Ă���ꍇ�̓��e��
 * tumbleblog ���w�肵�Ă̓��e���\�ɂ���
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 127   09/04/01 21:07 Tsujimura543
 * Twitter �� OAuth �ɑΉ�
 * 
 * 126   08/11/13 13:56 Tsujimura543
 * CUserInfo::CheckKeys() ���C�� (ret �̒l�̐ݒ���@���C��)
 * 
 * 125   08/11/11 18:24 Tsujimura543
 * dumpBookmark() �ŃR�����g���o�͂���悤�ɕύX (�f�o�b�O�p)
 * 
 * 124   08/11/11 16:20 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v����擾����v������ǉ�
 * 
 * 123   08/11/11 15:10 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v����폜����v������ǉ��A����m�F����
 * 
 * 122   08/11/10 17:41 Tsujimura543
 * ApiKey �� CheckKeys() �̃`�F�b�N�Ώۂɂ���悤�ɂ���
 * 
 * 121   08/11/05 19:48 Tsujimura543
 * �uAPI�L�[���g�p����@nifty�N���b�v�֓o�^����v������ǉ��A����m�F����
 * 
 * 120   08/08/21 17:35 Tsujimura543
 * BlogPeople tags �� BlogPeople IB �̃T�|�[�g���I��
 * 
 * 119   08/07/28 20:35 Tsujimura543
 * livedoor�N���b�v�Ɋւ��āA�]���̕��@�ł́u�폜�v�Ɏ��s�����ꍇ�́A
 * del.icio.us�݊�API�ɂ��u�폜�v�����݂�悤�ɂ��Ă݂�(API�L�[�擾
 * �ς݂̏ꍇ�̂�)
 * 
 * 118   08/07/26 0:33 Tsujimura543
 * Diigo �́u�폜�v�ɑΉ�
 * 
 * 117   08/07/25 22:16 Tsujimura543
 * Diigo �Ή�
 * 
 * 116   08/07/25 1:30 Tsujimura543
 * �u�b�N�}�[�N�폜��A�O���ɖ��폜�̃u�b�N�}�[�N���c���Ă��Ȃ��Ƃ�
 * �ł��A�u1�O�ɖ߂�v�{�^�����L���Ȃ܂܂ɂȂ��Ă��܂��s����C��
 * 
 * 115   08/05/21 14:09 Tsujimura543
 * �u�����v�������C��(�u��C�ɓo�^����v�ꍇ�� &amp; ���܂� URL ��
 * ���̂܂�(&amp;�̂܂�)�o�^���Ă��܂��s����C��)
 * 
 * 114   08/05/19 19:24 Tsujimura543
 * (1) ����������������
 * (2) �u���[�J��OPML�v�����ޏꍇ�̓����������C��
 * 
 * 113   08/05/16 20:04 Tsujimura543
 * IDS_TTL_SYNCHRONIZE �� IDS_TXT_SYNCHRONIZE �� LoadString
 * ����^�C�~���O���C��
 * 
 * 112   08/05/15 23:25 Tsujimura543
 * InquiryBookmarkSub() ���C���A�u�b�N�}�[�N�擾���s(0��)����
 * �G���[�_�C�A���O�� http �X�e�[�^�X�R�[�h��\������悤�ɂ���
 * 
 * 111   08/05/14 15:04 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̏ꍇ�̂� m_useMyTitle �̃f�t�H���g�l��
 * false �ɂ��� (�d�l�ύX)
 * 
 * 110   08/01/22 15:08 Tsujimura543
 * InquiryBookmarkSub() ���C���B�S���擾�Ɏ��s�����ꍇ�ł��A1���ȏ�
 * �擾���邱�Ƃ��ł����ꍇ�́A�擾�����u�b�N�}�[�N�������̂܂ܕێ�
 * ����悤�ɂ���
 * 
 * 109   07/10/31 18:49 Tsujimura543
 * putTumblr() �Ɉ���(version)��ǉ�
 * 
 * 108   07/10/31 17:16 Tsujimura543
 * tumblr �ւ̓o�^(���e)�ɑΉ�
 * 
 * 107   07/10/11 22:23 Tsujimura543
 * Yahoo! Japan �� ID �� newsing �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 106   07/10/10 1:50 Tsujimura543
 * BBAuth�o�R�� Buzzurl �𗘗p����ꍇ�̍폜�����̃��[�U���A�p�X���[�h
 * �̎擾�E�ݒ�����C��
 * 
 * 105   07/10/05 2:42 Tsujimura543
 * BBAuth �Ή��֘A�̊e��C�������{
 * 
 * 104   07/09/14 23:16 Tsujimura543
 * Buzzurl �ւ̃A�N�Z�X�� BBAuth ���g���Ă���ꍇ�́A�_�C�A���O��
 * �\�����郆�[�U���A�p�X���[�h�� Yahoo! Japan �� ID �ƃp�X���[�h
 * �ɂ���
 * 
 * 103   07/09/13 22:30 Tsujimura543
 * Yahoo! Japan �� ID �� Buzzurl �𗘗p�ł���悤�ɂȂ����̂ɑΉ�����
 * ���߂̏C�������{
 * 
 * 102   07/09/10 15:01 Tsujimura543
 * DeleteBookmarks() ���C���B�폜�p�̃u�b�N�}�[�N���\���_�C�A���O��
 * URL �� &amp; ���܂܂��ꍇ�� & �ɕϊ����Ă���\������悤�ɂ���
 * 
 * 101   07/09/06 18:04 Tsujimura543
 * CUserInfo�N���X�̃R�s�[�R���X�g���N�^�A������Z�q��CBookeyApp����
 * �g���Ă����̂��ACUserInfo�N���X���Ɉڊ� (PutBookmarks)
 * 
 * 100   07/09/05 20:30 Tsujimura543
 * UserAgent �������t�@�N�^�����O
 * 
 * 99    07/07/09 20:00 Tsujimura543
 * digg �ւ́u�o�^�v�ɑΉ�
 * 
 * 98    07/05/23 16:11 Tsujimura543
 * Timelog �ւ̓o�^(����)�ɑΉ�
 * 
 * 97    07/05/11 19:10 Tsujimura543
 * Twitter �ɑ��� bookey �̔Ő������\�[�X����擾�������̂��g���悤��
 * ���Ă݂�
 * 
 * 96    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks �� Yahoo! �u�b�N�}�[�N�́u�폜�v�ɑΉ�
 * 
 * 95    07/04/20 20:34 Tsujimura543
 * Yahoo! �u�b�N�}�[�N�AYahoo! Bookmarks �̃C���|�[�g�ƃG�N�X�|�[�g�ɑΉ�
 * 
 * 94    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (�́u�o�^�v�̂�) �ɑΉ�
 * 
 * 93    07/04/16 22:05 Tsujimura543
 * Yahoo! �u�b�N�}�[�N �ւ́u�o�^�v�ɑΉ�
 * 
 * 92    07/04/16 17:59 Tsujimura543
 * del.icio.us �� posts/all �`���� XML �t�@�C���̃C���|�[�g�ƃG�N�X�|�[�g
 * �ɑΉ�����
 * 
 * 91    07/04/10 18:46 Tsujimura543
 * Twitter �ւ́u�o�^�v�ɑΉ�
 * 
 * 90    07/03/30 13:50 Tsujimura543
 * FC2BOOKMARK �́u�폜�v�ɂ��Ή�
 * 
 * 89    07/03/29 23:04 Tsujimura543
 * FC2BOOKMARK �ɑΉ�
 * 
 * 88    07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 87    07/02/16 16:35 Tsujimura543
 * �R�����g���C��
 * 
 * 86    07/02/16 16:22 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�ABuzzurl�ABlogPet�C�ɂȂ�L���Ɋւ��āA�^�C�g������
 * �������邩�ǂ����I��(�w��)�ł���悤�ɂ���
 * 
 * 85    07/01/30 19:22 Tsujimura543
 * �^�O�ꗗ�̎擾�A�^�O�̍폜�A�^�O�̒u�������ۂɍs�Ȃ��֐��� UserInfo.cpp
 * ���番�����A�ʂ̃\�[�X�t�@�C���Ɉڊǂ���
 * 
 * 84    07/01/30 0:00 Tsujimura543
 * �ꕔ�����܂��ȋL�q��������
 * 
 * 83    07/01/29 21:59 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�́u�^�O�̍폜�v�A�u�^�O�̒u���v�ɂ��Ή�����
 * 
 * 82    07/01/29 20:13 Tsujimura543
 * �^�O�̈ꗗ�擾�A�^�O�̒u���Ɋւ��āABlue Dot �ɂ��Ή�����
 * (Blue Dot �̓T�[�o�����炿���Ɖ������Ԃ��Ă��Ȃ����Ƃ��悭���邪�A
 * �������Ԃ��Ă����Ƃ��͂����Ɗ��Ғʂ�ɓ��삷�邱�Ƃ��m�F����)
 * 
 * 81    07/01/29 17:51 Tsujimura543
 * �^�O�ꗗ�̎擾�A�^�O�̍폜�A�^�O�̒u���̊e������ǉ�
 * 
 * 80    07/01/19 15:38 Tsujimura543
 * MyClipEx �\���̂̃����o���� MyClip �\���̂ɍ��킹��
 * 
 * 79    07/01/18 0:53 Tsujimura543
 * �f�o�b�O�p�̃R�[�h(�̖��c)���폜
 * 
 * 78    07/01/16 1:26 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 77    07/01/13 1:42 Tsujimura543
 * CBookeyApp::CBookeyApp() �̒����� CString#LoadString() �����
 * assertion failed ���邱�Ƃ������B�΍�����{ (�p�ꃂ�[�h�Ή��ɂ�������
 * ����������Q)
 * 
 * 76    07/01/13 0:23 Tsujimura543
 * CFileDialog �֘A���������t�@�N�^�����O (���E�p�ꃂ�[�h�Ή����� ����3)
 * 
 * 75    07/01/12 23:51 Tsujimura543
 * �p�ꃂ�[�h�Ή����� ����2
 * 
 * 74    07/01/12 23:35 Tsujimura543
 * �p�ꃂ�[�h�Ή�����
 * 
 * 73    07/01/11 17:01 Tsujimura543
 * 2007�N1��10���t�ŁuEC�i�r�l�C�j���[�X�v�� Buzzurl �Ɉڍs�����̂�
 * �����C��
 * 
 * 72    07/01/04 18:54 Tsujimura543
 * ShowWindow() �̈������C��
 * 
 * 71    06/12/25 23:23 Tsujimura543
 * �uBlogPet �C�ɂȂ�L���v�ɑΉ�
 * 
 * 70    06/12/21 21:17 Tsujimura543
 * JoltMark �̓o�^�A�擾�ɑΉ�
 * 
 * 69    06/12/21 14:08 Tsujimura543
 * FC2BOOKMARK, �uBlogPet �C�ɂȂ�L���v�Ή�����
 * 
 * 68    06/12/06 19:48 Tsujimura543
 * �R�����g���C��
 * 
 * 67    06/12/06 19:46 Tsujimura543
 * livedoor Clip �̃G�N�X�|�[�g�t�@�C��(RSS 2.0 �`��)���C���|�[�g����@�\
 * ��ǉ�����
 * 
 * 66    06/12/04 19:19 Tsujimura543
 * NETSCAPE_BOOKMARK_FILE_1�`���ł̃u�b�N�}�[�N���o�͎���
 * Shift_JIS �ł̏o�͂��I���ł���悤�ɂ���
 * 
 * 65    06/11/27 16:32 Tsujimura543
 * �R�����g���C��
 * 
 * 64    06/11/27 16:24 Tsujimura543
 * CUserInfo::PutBookmarks() ���ŌĂяo���Ă��� CFileDialog �̃R���X�g��
 * �N�^�̑�1������ TRUE ���� FALSE �ɏC�� (�t�@�C�����㏑�����Ă������q
 * �˂�_�C�A���O���o�Ȃ��s��ւ̑Ώ�)
 * 
 * 63    06/11/16 16:43 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��16�i�K�A�I��
 * 
 * 62    06/11/16 14:02 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��15�i�K�A�I��
 * 
 * 61    06/11/10 19:26 Tsujimura543
 * �u���E�U�̃u�b�N�}�[�N����荞��/�u���E�U�Ɏ�荞�߂�`���̃u�b�N�}�[�N
 * �t�@�C���𐶐�����@�\���T�|�[�g���邽�߂̏���
 * 
 * 60    06/11/06 16:42 Tsujimura543
 * ResetUserInfo() �Ɏb��I�ȑΏ������{(�u���[�J��OPML�v�t�@�C�����̎b��I
 * �ȏC��������ǉ�)
 * 
 * 59    06/10/28 1:14 Tsujimura543
 * �u���[�J��OPML�v�֓o�^�ł��Ȃ����Ƃ�����s��ɑΏ�
 * 
 * 58    06/10/26 23:52 Tsujimura543
 * �u1�O�ɖ߂�v�Ŗ߂肷���Ă��܂����Ƃ�����(�������͂��̃u�b�N�}�[�N��
 * �\�������)�s��ɑΏ�
 * 
 * 57    06/10/26 23:17 Tsujimura543
 * �u���[�J�� OPML�v�ɑΉ�
 * 
 * 56    06/10/07 1:09 Tsujimura543
 * Blue Dot �ɑΉ�
 * 
 * 55    06/10/05 22:30 Tsujimura543
 * POOKMARK Airlines �́u�폜�v�ɑΉ�
 * 
 * 54    06/10/04 21:10 Tsujimura543
 * POOKMARK Airline �� POOKMARK Airlines �ɏC��
 * 
 * 53    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline �ɑΉ�
 * 
 * 52    06/09/29 19:38 Tsujimura543
 * newsing �� m_bmSymbol �̒l��ύX (�擪�̕���������������啶���ɕύX)
 * 
 * 51    06/09/04 22:33 Tsujimura543
 * SleepEx() �� Sleep() �ɒu��
 * 
 * 50    06/09/04 22:28 Tsujimura543
 * DeleteBookmarks() ���C�� (deleted �̉���R��)
 * 
 * 49    06/09/04 18:16 Tsujimura543
 * �u�폜�v�_�C�A���O�Ɓu�����v�_�C�A���O�Ɂu1�O�ɖ߂�v�@�\��ǉ�
 * 
 * 48    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 47c   06/09/03 22:13 tsupo
 * �u�b�N�}�[�N�̍폜�Ɏ��s�����ꍇ�A�����Ȃ菈���𒆒f����̂͂�߂āA��
 * ���𑱍s���邩�ǂ����q�˂�悤�ɂ���
 * 
 * 47b   06/09/03 19:26 tsupo
 * cookie �����C�� (�������I�[�o�[�����΍�)
 * 
 * 47a   06/09/03 5:51 tsupo
 * Visual Studio 2500 �Ńr���h�����ꍇ�ɏo�� warning (VC++ 6 �ł͏o�Ȃ�
 * warning) �ɑΏ�
 * 
 * 47    06/08/26 1:37 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��14�i�K�A�I��
 * 
 * 46    06/08/26 0:30 Tsujimura543
 * �R�����g���C��
 * 
 * 45    06/08/25 18:08 Tsujimura543
 * DeleteBookmarks() �����t�@�N�^�����O
 * 
 * 44    06/08/23 21:37 Tsujimura543
 * 1470.net���j���[�A���ł̓����̏ꍇ�̃��[�U���ݒ菈��������
 * (�������A��������[�̂����A�擾��]�{�͖̂�����) [�� 06/08/25 �����ς�]
 * 
 * 43    06/08/23 21:35 Tsujimura543
 * �u1470.net���j���[�A���ł̃��[�U��񖢐ݒ�̂܂܁A�폜�����s���悤�Ƃ�
 * ���Ƃ��v�̃��[�U���ݒ�p�_�C�A���O�\��������������
 * 
 * 42    06/08/22 19:46 Tsujimura543
 * �h���R��RSS�̍폜�����A1470.net���j���[�A���ł̍폜�����̌Ăяo����ǉ�
 * 
 * 41    06/08/22 17:53 Tsujimura543
 * enum authenticationType �� AUTH_TYPE
 * 
 * 40    06/08/22 15:46 Tsujimura543
 * struct myClip �� MyClip �ɒu�� (typedef struct myClip MyClip)
 * 
 * 39    06/08/22 11:41 Tsujimura543
 * #include ����K�v�̂Ȃ��t�@�C�����C���N���[�h����̂���߂�
 * 
 * 38    06/08/21 21:06 Tsujimura543
 * authType �̒l���u�����ݒ�t�@�C���v�ɕۑ�����悤�ɂ���
 * 
 * 37    06/08/21 20:29 Tsujimura543
 * �u�͂ĂȔF��API�v�o�R�ł�1470.net���j���[�A���łւ̃A�N�Z�X�ɑΉ�
 * 
 * 36    06/08/18 15:05 Tsujimura543
 * EC�i�r�l�C�j���[�X�́u�폜�v�ɑΉ�
 * 
 * 35    06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 * 
 * 34    06/07/21 21:09 Tsujimura543
 * �j�t�e�B�N���b�v�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 33    06/07/21 20:51 Tsujimura543
 * EC�i�r�l�C�j���[�X�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤��
 * ����)
 * 
 * 32    06/07/21 20:17 Tsujimura543
 * BlogPeople Tags �̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 31    06/07/21 17:48 Tsujimura543
 * livedoor�N���b�v�̎擾�����̈�����ǉ�(�S�������邩�A�擾�ł���悤�ɂ�
 * ��)
 * 
 * 30    06/07/20 19:02 Tsujimura543
 * del.icio.us ����́u�擾�v���A�擾�Ɏ��s�����ꍇ�A�S�������̉����܂ł�
 * �擾�ɐ����������A�_�C�A���O�ŕ\������悤�ɂ���
 * 
 * 29    06/07/19 14:19 Tsujimura543
 * MyClip! �֌W�̏������폜 (2006�N6�����ŃT�[�r�X�I���̂���)
 * 
 * 28    06/07/15 0:56 Tsujimura543
 * 1470.net���j���[�A���łւ́u�o�^�v�ɑΉ�
 * 
 * 27    06/07/14 18:17 Tsujimura543
 * (1) JoltMark, 1470.net���j���[�A���� �Ή�����
 * (2) �͂ĂȔF��API (1470.net���j���[�A���Ō���) �Ή�����
 * 
 * 26    06/07/12 17:34 Tsujimura543
 * �h���R��RSS(��Clip!)�̎擾�A�����ɑΉ�
 * 
 * 25    06/07/12 9:40 Tsujimura543
 * DeleteLivedoorClip() �� DeleteNiftyClip() ��ǉ�
 * 
 * 24    06/07/07 19:34 Tsujimura543
 * �j�t�e�B�N���b�v�̎擾�A�����ɑΉ�
 * 
 * 23    06/07/06 19:53 Tsujimura543
 * livedoor�N���b�v�̎擾�A�����ɑΉ�
 * 
 * 22    06/07/05 18:19 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��13�i�K�A�I��
 * 
 * 21    06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 20    06/07/04 10:34 Tsujimura543
 * �����v�J�[�\���֘A�A�C��
 * 
 * 19    06/07/03 15:15 Tsujimura543
 * ProceedingDialog ���݂̉��C (ProceedingDialog �� delete���ɗ�O��
 * �������邱�Ƃ����錏�̑΍���{)
 * 
 * 18    06/07/03 14:37 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̎擾���ɁA�S���擾�ł������ǂ����`�F�b�N����悤��
 * ����
 * 
 * 17    06/06/30 19:43 Tsujimura543
 * EC�i�r�l�C�j���[�X�̎擾�A�����ɑΉ�
 * 
 * 16    06/06/29 18:47 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 15    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 14    06/06/27 15:24 Tsujimura543
 * Flog �̍폜�ɑΉ�
 * 
 * 13    06/06/23 21:50 Tsujimura543
 * Flog �̎擾�A�����ɑΉ�����
 * 
 * 12    06/06/22 21:21 Tsujimura543
 * inquery �� inquiry �ɏC��(�Ԃ�~�X)
 * 
 * 11    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() �����s���Ă��A�ݒ肪�ύX�ł��Ȃ��Ȃ���
 * ���܂��Ă���(�G���o�O)�̂��C���B�ύX�ł���悤�ɂ���
 * 
 * 10    06/06/21 21:14 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��11�i�K�A�I��
 * 
 * 9     06/06/21 19:36 Tsujimura543
 * �u�b�N�}�[�N�擾�������ʃX���b�h������
 * 
 * 8     06/06/20 17:59 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��10�i�K�A�I��
 * 
 * 7     06/06/20 14:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��9�i�K�A�I��
 * 
 * 6     06/06/14 23:02 Tsujimura543
 * �u�����v�������̐i�s�󋵕\���_�C�A���O�̕����𐮗�
 * 
 * 5a    06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 5     06/06/14 22:40 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��7�i�K�A�I��
 * 
 * 4     06/06/14 11:44 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��5�i�K�A�I��
 * 
 * 3     06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 2     06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 1     06/06/06 22:24 Tsujimura543
 * �V�K�쐬 (CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��)
 * 
 * 0h    06/05/24 17:15 Tsujimura543
 * (1) URL �� &amp; ���܂܂��ꍇ�́A�������� & �ɒu�����Ă���o�^����
 * ���Ăяo���悤�ɂ���
 * (2) MM/Memo �ւ́u�����v���́AAmazon �̏��i�y�[�W�Ɋւ��ẮAASIN
 * ���������ǂ�����r���邱�ƂŁA�o�^�ς݂��ǂ����𔻒f����悤�ɂ���
 * 
 * 0g    06/05/11 16:01 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 0f    06/05/11 15:58 Tsujimura543
 * MM/Memo �Ɋւ��Ă͓o�^���Ă���A���ۂ�(�擾���ʂ�)���f�����܂Ŏ��Ԃ�
 * �����邱�Ƃ�����A���ۂɂ͓o�^�ς݂ɂ��ւ炸�A���o�^�Ɣ��肳��A����(�]
 * ��)�����s����Ă��܂����Ƃ����� [����/����̉ۑ� �� MM/Memo ���ł̑΍�
 * ��҂����Ȃ���������Ȃ�]
 * 
 * 0e    06/05/11 15:56 Tsujimura543
 * �{���͓����URL�ł���ɂ��ւ炸�A�e�T�[�r�X����URL���L���E�i�[����Ƃ�
 * �̌`��(�ǂ̕����𐔒l�Q�ƁA���ԎQ�Ƃɕϊ����邩/���Ȃ���)���قȂ邽�߁A
 * �����URL�ł���Ɣ��f�ł����ɓ���(�]��)���悤�Ƃ��Ă��܂����Ƃ��������B
 * ��������AURL�f�R�[�h���Ă����r���邱�ƂŁA�����URL���ǂ�����������
 * �f�ł���悤�ɂȂ���
 * 
 * 0d    06/02/17 22:02 Tsujimura543
 * 4�̃u�b�N�}�[�N�T�[�r�X�̂����A�C�ӂ�2�ҊԂœ���������悤�ɂ���
 * 
 * 0c    06/02/17 18:07 Tsujimura543
 * �u�b�N�}�[�N�̓������A�͂Ăȃu�b�N�}�[�N��del.icio.us�ȊO�ɂ��e�ՂɑΉ�
 * �\�ɂ��邽�߁A�����̒��ۉ���i�߂�
 * 
 * 0b    05/11/10 22:25 Tsujimura543
 * �i�s�󋵕\���_�C�A���O���g���悤�ɂ���
 * 
 * 0a    05/10/11 19:07 Tsujimura543
 * �u�b�N�}�[�N�����@�\������ (����m�F�ς�)
 * 
 * 0     05/10/11 16:55 Tsujimura543
 * �u�b�N�}�[�N���������̎����J�n
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog3.h"
#include "DeleteBookmarkDialog4.h"
#include "SynchronizeBookmarkDialog.h"
#include "importBookmark.h"
#include "exportBookmark.h"
#include "deleteBookmark.h"
#include "SettingDialog.h"
#include "parameter.h"
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "delicious.h"
#include "blueDot.h"
#include "hatenaAPI.h"
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/UserInfo.cpp 4     09/06/22 22:31 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void    SetUserAgent( char    *userAgent,
                      CString &str1,
                      CString &str2 )
{
    str1.LoadString( IDS_BOOKEY_VERSION );
    str2.LoadString( IDS_BOOKEY_WEB_URL );
    sprintf( userAgent, "bookey/%s (%s)", str1, str2 );
    setUserAgent( userAgent );
}

void    SetUserAgent( CString &str1,
                      CString &str2,
                      CString &str3 )
{
    char    userAgent[BUFSIZ];

    SetUserAgent( userAgent, str1, str2 );
    str3.LoadString( IDS_BOOKEY_RESOURCE_XML );
}

void    SetUserAgent( bool set )
{
    if ( set ) {
        char    userAgent[BUFSIZ];
        CString str1;
        CString str2;

        SetUserAgent( userAgent, str1, str2 );
    }
    else
        setUserAgent( NULL );
}


#ifdef  _DEBUG
void
dumpBookmark( int kind, const MyClip *mp, int num )
{
    const char  *name = "bookmark";
    char        filename[MAX_PATH];
    FILE        *fp;
    time_t      t = time( NULL );

    switch ( kind ) {
    case CUserInfo::BK_HATENA:
        name = "hatena";
        break;
    case CUserInfo::BK_DELICIOUS:
        name = "delicious";
        break;
    case CUserInfo::BK_MM_MEMO:
        name = "mmMemo";
        break;
    case CUserInfo::BK_DRECOM_RSS:
        name = "drecom";
        break;
    case CUserInfo::BK_FLOG:
        name = "flog";
        break;
    case CUserInfo::BK_LIVEDOOR_CLIP:
        name = "livedoor";
        break;
    case CUserInfo::BK_ECNAVI_CLIP:
        name = "buzzurl";
        break;
    case CUserInfo::BK_NIFTY_CLIP:
        name = "nifty";
        break;
    case CUserInfo::BK_1470NET:
        name = "1470net";
        break;
    case CUserInfo::BK_POOKMARK:
        name = "pookmark";
        break;
    case CUserInfo::BK_BLUEDOT:
        name = "blueDot";
        break;
    case CUserInfo::BK_JOLTMARK:
        name = "joltMark";
        break;
    case CUserInfo::BK_BLOGPET:
        name = "blogpet";
        break;
    case CUserInfo::BK_FC2BOOKMARK:
        name = "fc2";
        break;
    case CUserInfo::BK_YJ_BOOKMARK:
        name = "yahooJapan";
        break;
    case CUserInfo::BK_YAHOO_BOOKMARKS:
        name = "yahoo";
        break;
    case CUserInfo::BK_DIIGO:
        name = "diigo";
        break;
    case CUserInfo::BK_LOCAL_OPML:
        name = "localOpml";
        break;
    }

    sprintf( filename, "./%s_%d.txt", name, t );
    fp = fopen( filename, "w" );
    if ( !fp )
        return;

    fprintf( fp, "bookmark kind: %s\n\n", name );
    for ( int i = 0; i < num; i++ ) {
        fprintf( fp, "[%05d] url     = ===[%s]===\n", i + 1, mp[i].url );
        fprintf( fp,"        title   = ===[%s]===\n", mp[i].title );
        if ( mp[i].comment[0] != NUL )
            fprintf( fp,
                    "        comment = ===[%s]===\n", mp[i].comment );
    }

    fclose( fp );
}
#endif


/*
 *  �������A���[�U���ݒ�
 */

void    CUserInfo::Init()
{
    m_isTarget     = false;
    m_useMyTitle   = true;
    m_username     = "";
    m_password     = "";
    m_username2    = "";
    m_password2    = "";
    m_blogID       = "";
    m_blogName     = "";
    m_opmlFilename = "";
    m_apiKey       = "";
    m_secret       = "";
    m_authType     = AK_ORIGINAL;

    m_tgt_hatenaBookmark = "";
    m_tgt_delicious      = "";
    m_tgt_mmMemo         = "";
    m_tgt_drecomRSS      = "";
    m_tgt_flog           = "";
    m_tgt_livedoorClip   = "";
    m_tgt_ecNaviClip     = "";
    m_tgt_niftyClip      = "";
    m_tgt_1470net        = "";
    m_tgt_pookmark       = "";
    m_tgt_blueDot        = "";
    m_tgt_joltMark       = "";
    m_tgt_blogPet        = "";
    m_tgt_fc2bookmark    = "";
    m_tgt_yjBookmark     = "";
    m_tgt_yahooBookmarks = "";
    m_tgt_diigo          = "";
    m_tgt_hatenaFeed     = "";
    m_tgt_deliciousXML   = "";
}

void    CUserInfo::Init( bool isTarget, CString username, CString password )
{
    m_isTarget = isTarget;
    m_username = username;
    m_password = password;
    m_authType = AK_ORIGINAL;
}

void    CUserInfo::Init( enum bookmarkType bmType )
{
    Init();
    m_bmType = bmType;

    switch ( m_bmType ) {
    case BK_HATENA:
        m_bmName.LoadString( IDS_TGT_HATENA_BOOKMARK );
        m_bmSymbol   = "Hatena";
        m_useMyTitle = false; // �͂ău�̏ꍇ�̂� false ���f�t�H���g�ɂ���
        break;
    case BK_DELICIOUS:
        m_bmName.LoadString( IDS_TGT_DELICIOUS );
        m_bmSymbol = "Delicious";
        break;
    case BK_MM_MEMO:
        m_bmName.LoadString( IDS_TGT_MMMEMO );
        m_bmSymbol = "MMmemo";
        m_authType = AK_TYPEKEY;
        break;
    case BK_DRECOM_RSS:
        m_bmName.LoadString( IDS_TGT_DRECOM_RSS );
        m_bmSymbol = "DrecomRSS";
        break;
    case BK_FLOG:
        m_bmName.LoadString( IDS_TGT_FLOG );
        m_bmSymbol = "Flog";
        break;
    case BK_LIVEDOOR_CLIP:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_CLIP );
        m_bmSymbol = "Livedoor";
        break;
    case BK_ECNAVI_CLIP:
        m_bmName.LoadString( IDS_TGT_ECNAVI_CLIP );
        m_bmSymbol = "EcNavi";
        break;
    case BK_NIFTY_CLIP:
        m_bmName.LoadString( IDS_TGT_NIFTY_CLIP );
        m_bmSymbol = "Nifty";
        break;
    case BK_JOLTMARK:
        m_bmName.LoadString( IDS_TGT_JOLTMARK );
        m_bmSymbol = "JoltMark";
        break;
    case BK_1470NET:
        m_bmName.LoadString( IDS_TGT_1470NET );
        m_bmSymbol = "1470.net";
        m_authType = AK_TYPEKEY; /* default �� TypeKey �F�؂Ƃ��� */
        break;
    case BK_NEWSING:
        m_bmName.LoadString( IDS_TGT_NEWSING );
        m_bmSymbol = "Newsing";
        break;
    case BK_POOKMARK:
        m_bmName.LoadString( IDS_TGT_POOKMARK );
        m_bmSymbol = "Pookmark";
        m_authType = AK_JUGEMKEY;   /* POOKMARK �� jugemkey �F�� */
        break;
    case BK_BLUEDOT:
        m_bmName.LoadString( IDS_TGT_BLUEDOT );
        m_bmSymbol = "BlueDot";
        break;
    case BK_FC2BOOKMARK:
        m_bmName.LoadString( IDS_TGT_FC2_BOOKMARK );
        m_bmSymbol = "FC2BOOKMARK";
        break;
    case BK_BLOGPET:
        m_bmName.LoadString( IDS_TGT_BLOGPET );
        m_bmSymbol = "BlogPet";
        break;
    case BK_TWITTER:
        m_bmName.LoadString( IDS_TGT_TWITTER );
        m_bmSymbol = "Twitter";
        break;
    case BK_YJ_BOOKMARK:
        m_bmName.LoadString( IDS_TGT_YJ_BOOKMARK );
        m_bmSymbol = "YahooJapanBookmark";
        break;
    case BK_YAHOO_BOOKMARKS:
        m_bmName.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
        m_bmSymbol = "YahooBookmarks";
        break;
    case BK_TIMELOG:
        m_bmName.LoadString( IDS_TGT_TIMELOG );
        m_bmSymbol = "Timelog";
        break;
    case BK_DIGG:
        m_bmName.LoadString( IDS_TGT_DIGG );
        m_bmSymbol = "Digg";
        break;
    case BK_TUMBLR:
        m_bmName.LoadString( IDS_TGT_TUMBLR );
        m_bmSymbol = "tumblr";
        break;
    case BK_DIIGO:
        m_bmName.LoadString( IDS_TGT_DIIGO );
        m_bmSymbol = "Diigo";
        break;
    case BK_LOCAL_OPML:
        m_bmName.LoadString( IDS_TGT_LOCAL_OPML );
        m_bmSymbol     = "LocalOpml";
        m_opmlFilename = BOOKEY_DEFAULT_OPML;
        break;
    case BK_NETSCAPE_BOOKMARK_FILE_1:
        m_bmName.LoadString( IDS_TGT_NETSCAPE_1 );
        break;
    case BK_OPERA6_ADR:
        m_bmName.LoadString( IDS_TGT_OPERA_6 );
        break;
    case BK_HATENA_BOOKMARK_ATOM:
        m_bmName.LoadString( IDS_TGT_HATENA_FEED );
        break;
    case BK_LIVEDOOR_CLIP_RSS:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_FEED );
        break;
    case BK_DELICIOUS_XML:
        m_bmName.LoadString( IDS_TGT_DELICIOUS_XML );
        break;
    }
}

void    CUserInfo::ReInit()
{
    switch ( m_bmType ) {
    case BK_HATENA:
        m_bmName.LoadString( IDS_TGT_HATENA_BOOKMARK );
        break;
    case BK_DELICIOUS:
        m_bmName.LoadString( IDS_TGT_DELICIOUS );
        break;
    case BK_MM_MEMO:
        m_bmName.LoadString( IDS_TGT_MMMEMO );
        break;
    case BK_DRECOM_RSS:
        m_bmName.LoadString( IDS_TGT_DRECOM_RSS );
        break;
    case BK_FLOG:
        m_bmName.LoadString( IDS_TGT_FLOG );
        break;
    case BK_LIVEDOOR_CLIP:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_CLIP );
        break;
    case BK_ECNAVI_CLIP:
        m_bmName.LoadString( IDS_TGT_ECNAVI_CLIP );
        break;
    case BK_NIFTY_CLIP:
        m_bmName.LoadString( IDS_TGT_NIFTY_CLIP );
        break;
    case BK_JOLTMARK:
        m_bmName.LoadString( IDS_TGT_JOLTMARK );
        break;
    case BK_1470NET:
        m_bmName.LoadString( IDS_TGT_1470NET );
        break;
    case BK_NEWSING:
        m_bmName.LoadString( IDS_TGT_NEWSING );
        break;
    case BK_POOKMARK:
        m_bmName.LoadString( IDS_TGT_POOKMARK );
        break;
    case BK_BLUEDOT:
        m_bmName.LoadString( IDS_TGT_BLUEDOT );
        break;
    case BK_FC2BOOKMARK:
        m_bmName.LoadString( IDS_TGT_FC2_BOOKMARK );
        break;
    case BK_BLOGPET:
        m_bmName.LoadString( IDS_TGT_BLOGPET );
        break;
    case BK_TWITTER:
        m_bmName.LoadString( IDS_TGT_TWITTER );
        break;
    case BK_YJ_BOOKMARK:
        m_bmName.LoadString( IDS_TGT_YJ_BOOKMARK );
        break;
    case BK_YAHOO_BOOKMARKS:
        m_bmName.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
        break;
    case BK_TIMELOG:
        m_bmName.LoadString( IDS_TGT_TIMELOG );
        break;
    case BK_DIGG:
        m_bmName.LoadString( IDS_TGT_DIGG );
        break;
    case BK_TUMBLR:
        m_bmName.LoadString( IDS_TGT_TUMBLR );
        break;
    case BK_DIIGO:
        m_bmName.LoadString( IDS_TGT_DIIGO );
        break;
    case BK_LOCAL_OPML:
        m_bmName.LoadString( IDS_TGT_LOCAL_OPML );
        break;
    case BK_NETSCAPE_BOOKMARK_FILE_1:
        m_bmName.LoadString( IDS_TGT_NETSCAPE_1 );
        break;
    case BK_OPERA6_ADR:
        m_bmName.LoadString( IDS_TGT_OPERA_6 );
        break;
    case BK_HATENA_BOOKMARK_ATOM:
        m_bmName.LoadString( IDS_TGT_HATENA_FEED );
        break;
    case BK_LIVEDOOR_CLIP_RSS:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_FEED );
        break;
    case BK_DELICIOUS_XML:
        m_bmName.LoadString( IDS_TGT_DELICIOUS_XML );
        break;
    }
}

/*
 *  ���[�U���擾
 */

void    CUserInfo::GetUserInfo( CString &username,
                                CString &password,
                                enum bookmarkType &bmType )
{
    if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        username = pp->m_yjBookmark.m_username;
        password = pp->m_yjBookmark.m_password;
    }
    else {
        if ( m_username.GetLength() > 0 )
            username = m_username;
        if ( m_password.GetLength() > 0 )
            password = m_password;
    }
    bmType = m_bmType;
}


/*
 *  ���[�U���\��
 */

void    CUserInfo::SetWindowText( CString &username,
                                  CString &password,
                                  CEdit   *editUsername,
                                  CEdit   *editPassword )
{
    username = _T("");
    password = _T("");
    if ( ((m_bmType == BK_ECNAVI_CLIP) ||
          (m_bmType == BK_NEWSING)        )   &&
         (m_authType == AK_YAHOOJAPAN_BBAUTH)    ) {
        if ( (m_username2.GetLength() > 0) &&
             (m_password2.GetLength() > 0)    ) {
            username = (const char *)m_username2;
            password = (const char *)m_password2;
        }
        else {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            username = pp->m_yjBookmark.m_username;
            password = pp->m_yjBookmark.m_password;
        }
    }
    else {
        if ( m_username.GetLength() > 0 )
            username = (const char *)m_username;
        if ( m_password.GetLength() > 0 )
            password = (const char *)m_password;
    }

    editUsername->SetWindowText( username );
    editPassword->SetWindowText( password );
}

void    CUserInfo::SetWindowText( CString &username,
                                  CEdit   *editUsername )
{
    if ( m_username.GetLength() > 0 ) {
        username = (const char *)m_username;
        editUsername->SetWindowText( username );
    }
}


/*
 *  ���[�U���A�p�X���[�h�̐ݒ�
 */

void    CUserInfo::SetBookeyInfo()
{
    int ret = IDNO;

    ret = InquiryToUseService();
    if ( ret == IDYES ) {
        DeleteBookmarkDialog3   dlg3;
        dlg3.m_messageOnCancel = "**";

        GetUserInfo( dlg3.m_username, dlg3.m_password,
                     dlg3.m_targetBookmark );
        ret = dlg3.DoModal();
        if ( ret == IDOK )
            Init( true, dlg3.m_username, dlg3.m_password );
    }
    else
        Init( false );
}


/*
 *  �e��₢���킹
 */

int     CUserInfo::InquiryToUseService()
{
    int     ret = IDNO;
    char    txt[BUFSIZ];
    CString title;
    CString text;

    title.LoadString(IDS_TTL_SYNC_TARGET);
    text.LoadString( IDS_TXT_SYNC_TARGET);

    m_isTarget = false;

#if 0
    strcpy( txt, (const char *)m_bmName );
    strcat( txt, " ���u�b�N�}�[�N�����o�^�Ώۂɂ��܂���?    " );
#else
    sprintf( txt, text, (const char *)m_bmName );
#endif
    ret = ::MessageBox(
                NULL,
                txt,
                title,  // �u�b�N�}�[�N�����o�^�Ώېݒ�
                MB_YESNO|MB_ICONQUESTION );

    return ( ret );
}

bool    CUserInfo::InquiryUserInfo( CString bookmark1, CString bookmark2, 
                                    CString txt )
{
    if ( m_bmType == BK_LOCAL_OPML )
        return ( true );

    DeleteBookmarkDialog3   dlg3;

    if ( (bookmark1.Compare( m_bmName ) == 0) ||
         (bookmark2.Compare( m_bmName ) == 0)    ) {
    	DeleteBookmarkDialog3   dlg3;

        dlg3.m_messageOnCancel = txt;

        GetUserInfo( dlg3.m_username, dlg3.m_password,
                     dlg3.m_targetBookmark );

        if ( m_bmType != BK_1470NET ) {
            int ret = dlg3.DoModal();
            if ( (ret == IDCANCEL)                  ||
                 (dlg3.m_username.GetLength() == 0) ||
                 (dlg3.m_password.GetLength() == 0)    )
                return ( false );

            if ( (dlg3.m_username.GetLength() > 0)           &&
                 ((m_username.GetLength() == 0)         ||
                  dlg3.m_username.Compare( m_username )    )    )
                m_username = dlg3.m_username;

            if ( (dlg3.m_password.GetLength() > 0)           &&
                 ((m_password.GetLength() == 0)         ||
                  dlg3.m_password.Compare( m_password )    )    )
                m_password = dlg3.m_password;
        }
        else {
            if ( dlg3.m_username.GetLength() == 0 ) {
                if ( m_username.GetLength() == 0 ) {
                    SettingDialog   sdlg;
                    sdlg.m_1470net = true;
                    sdlg.DoModal();

                    m_authType = sdlg.m_dlg08.m_authType;
                    m_username = sdlg.m_dlg08.m_username;
                    m_password = sdlg.m_dlg08.m_password;
                }
                dlg3.m_username = m_username;
                dlg3.m_password = m_password;
                if ( (dlg3.m_username.GetLength() == 0) ||
                     (dlg3.m_password.GetLength() == 0)    )
                    return ( false );
            }
        }
    }

    return ( true );
}


/*
 *  ���[�U���Đݒ�
 */

void    CUserInfo::ResetUserInfo( bool &needToSave )
{
    if ( m_bmType == BK_LOCAL_OPML ) {
        if ( m_isTarget ) {
            if ( m_opmlFilename.GetLength() == 0 )
                m_opmlFilename = BOOKEY_DEFAULT_OPML;
            if ( !m_opmlFilename.Compare( BOOKEY_DEFAULT_OPML ) )
                needToSave = true;
        }
        return;
    }

    if ( m_isTarget &&
         (m_username.GetLength() >  0) &&
         (m_password.GetLength() == 0) &&
         (m_secret.GetLength()   == 0)    ) {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_BROKEN_SETTING);
        text.LoadString( IDS_TXT_BROKEN_SETTING);

#if 0
        CString txt;

        txt = "�ݒ�t�@�C�������Ă���悤�ł��B\r\n�u";
        txt += m_bmName;
        txt += "�v�� login �p�p�X���[�h���Đݒ肵�Ă��������B  ";
#else
        char    txt[BUFSIZ];

        sprintf( txt, text, (const char *)m_bmName );
#endif

        MessageBox( NULL,
                    txt,
                    title,  // �ݒ�t�@�C���ُ�
                    MB_OK|MB_ICONWARNING );

        /* �p�X���[�h�Đݒ� */
        DeleteBookmarkDialog3   dlg;
        dlg.m_messageOnCancel = "**";
        GetUserInfo( dlg.m_username, dlg.m_password,
                     dlg.m_targetBookmark );
        dlg.m_password = "";

        int ret = dlg.DoModal();
        if ( ret == IDOK ) {
            Init( true, dlg.m_username, dlg.m_password );
            needToSave = true;
        }
    }
}

void    CUserInfo::ResetUserInfo( bool &needToSave,
                                  BOOL &isTarget,
                                  char *username, char *password )
{
    if ( m_isTarget &&
         (m_username.GetLength() > 0) ) {
        if ( m_password.GetLength() == 0 ) {
            /* �p�X���[�h���ݒ�A�������̓p�X���[�h�����Ă���ꍇ */
            DeleteBookmarkDialog3   dlg;
            CString                 action;

            action.LoadString( IDS_REGISTER );
            dlg.m_messageOnCancel = action; // �o�^
            GetUserInfo( dlg.m_username, dlg.m_password,
                         dlg.m_targetBookmark );
            dlg.m_password = "";

            int ret = dlg.DoModal();
            if ( ret == IDOK ) {
                Init( true, dlg.m_username, dlg.m_password );
                needToSave = true;
            }
            else
                return;
        }

        strcpy( username, (const char *)m_username );
        strcpy( password, (const char *)m_password );
    }
    else
        username[0] = NUL;
    isTarget = m_isTarget;
}

void    CUserInfo::ResetUserInfo( bool &needToSave,
                                  BOOL &isTarget,
                                  char *filename )
{
    if ( m_isTarget && (m_opmlFilename.GetLength() == 0) ) {
        ResetUserInfo( needToSave );
        if ( m_opmlFilename.GetLength() == 0 ) {
            // ���[�J��OPML�t�@�C���������ݒ�̏ꍇ
            CString title;
            CString text;

            title.LoadString(IDS_TTL_NO_SETTING_LOCAL_OPML);
            text.LoadString( IDS_TXT_NO_SETTING_LOCAL_OPML);

            MessageBox( NULL,
                        text,   // ���[�J��OPML�t�@�C�������ݒ肳��Ă��܂���B\r\n
                                // ���[�J��OPML�t�@�C������ݒ肵�Ă����Ă��������B
                        title,  // ���[�J��OPML�t�@�C�������ݒ�
                        MB_OK|MB_ICONWARNING );

            filename[0] = NUL;
            isTarget    = false;
            return;
        }
    }

    if ( m_opmlFilename.GetLength() > 0 )
        strcpy( filename, m_opmlFilename );
    else
        filename[0] = NUL;
    isTarget = m_isTarget;
}


/*
 *  �u�b�N�}�[�N�̃C���|�[�g(�o�^)
 */

void    CUserInfo::ImportFromAnotherToOne(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myOne,
                int              numOfOne,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            )
{
    // myAnother �݂̂ɓo�^����Ă��� myOne �ɂ͓o�^����Ă�
    // �Ȃ��u�b�N�}�[�N�� myOne �ɓo�^����
    bool    found     = false;
    bool    withQuery = true;
    int     cnt       = 0;
    int     first     = 0;
    CString title;
    CString dir;
    CString text;
    char    txt[BUFSIZ];
    BOOL    *synchronized = new BOOL[numOfAnother]; /* �����ς݃t���O */

    CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

    text.LoadString( IDS_DIRECTION );
    dir  = anotherBookmarkName;
    dir += text;    // ��
    dir += m_bmName;

    CString tgt_localOPML;
    tgt_localOPML.LoadString( IDS_TGT_LOCAL_OPML );

    for ( int i = 0; i < numOfAnother; i++ ) {
        title.LoadString(IDS_TTL_SYNCHRONIZE);
        text.LoadString( IDS_TXT_SYNCHRONIZE);
        synchronized[i] = FALSE;
            /* �����ς݃t���O                                 */
            /*   TRUE:  �����ς� or ��������K�v�Ȃ�          */
            /*   FALSE: ��������K�v���� and �܂��������ĂȂ� */
        dlg->ShowWindow( SW_SHOWNORMAL );
        dlg->ChangeDialogText( title,   // �u�b�N�}�[�N�̓���
                               text );  // ��������K�v�̂���u�b�N�}�[�N��T���� �c�c
        found = false;
        for ( int j = 0; j < numOfOne; j++ ) {
            if ( !strcmp( myAnother[i].url, myOne[j].url )       ||
                 (strchr( myAnother[i].url, '%' )            &&
                  !strcmpi( myAnother[i].url, myOne[j].url )   )    ) {
                found = true;
                break;
            }
        
            if ( (strstr( myAnother[i].url, "&amp;" ) && 
                  strchr( myOne[j].url, '&' )            ) ||
                 (strstr( myOne[j].url, "&amp;" ) && 
                  strchr( myAnother[i].url, '&' )    )     ||
                 (strchr( myAnother[i].url, '%' ) &&
                  strchr( myOne[j].url,  '%' )       )        ) {
                char        url1[2048];
                char        url2[2048];
                const char  *p;

                strcpy( url1, myAnother[i].url );
                while ( ( p = strstr( url1, "&amp;" ) ) != NULL )
                    strcpy( (char *)p + 1, p + 5 );
                strcpy( url1, decodeURL( url1 ) );

                strcpy( url2, myOne[j].url );
                while ( ( p = strstr( url2, "&amp;" ) ) != NULL )
                    strcpy( (char *)p + 1, p + 5 );
                strcpy( url2, decodeURL( url2 ) );

                if ( !strcmpi( url1, url2 ) ) {
                    found = true;
                    break;
                }
            }

            if ( m_bmType == BK_MM_MEMO ) {
                // MM/Memo �ł� Amazon �̏��i�� URL �������ʂȈ������K�v
                if ( !strncmp( myAnother[i].url,
                               "http://www.amazon.co.jp/", 24 ) &&
                     !strncmp( myOne[j].url,
                               "http://www.amazon.co.jp/", 24 )    ) {
                    char    asin1[16];
                    char    asin2[16];

                    if (strstr( myAnother[i].url, "/gp/product/images/") &&
                        !strstr(myOne[j].url,     "/gp/product/images/")   ) {
                        synchronized[i] = TRUE; /* ��������K�v�Ȃ� */
                        continue;
                    }

                    asin1[0] = NUL;
                    asin2[0] = NUL;
                    getASIN( myAnother[i].url, asin1 );
                    getASIN( myOne[j].url,     asin2 );
                    if ( asin1[0] && asin2[0]   &&
                         (asin1[0] == asin2[0]) &&
                         !strcmp( &(asin1[1]), &(asin2[1]) ) ) {
                        /* ASIN ����v������A����y�[�W�ł���Ƃ݂Ȃ� */
                        found = true;
                        break;
                    }
                }
            }
        }
        if ( found ) {
            synchronized[i] = TRUE; /* ��������K�v�Ȃ� */
            continue;
        }

        dlg->ShowWindow( SW_HIDE );
        cnt++;
        if ( cnt == 1 ) {
            text.LoadString(IDS_TXT_START_SYNCHRONIZING);
            sprintf( txt, text, (const char *)dir );
            MessageBox( NULL,
                        txt,    // %s �����̃u�b�N�}�[�N�̓������s�Ȃ��܂�
                        title,  // �u�b�N�}�[�N�̓���
                        MB_OK|MB_ICONINFORMATION );
            first = i;
        }

        const char  *p;
        while ( (p = strstr( myAnother[i].url, "&amp;" )) != NULL )
            strcpy( (char *)p + 1, p + 5 ); /* "&amp;" �� "&" �֒u��*/

        if ( withQuery ) {
            // �u�b�N�}�[�N����\��
            DeleteBookmarkDialog4   dlg4;

            dlg4.m_url     = myAnother[i].url;
            dlg4.m_title   = myAnother[i].title;
            dlg4.m_comment = myAnother[i].comment;
            dlg4.m_tags    = myAnother[i].tags;

            if ( !strcmp( anotherBookmarkName, tgt_localOPML ) ) {
                char    *pp;

                pp = utf2sjis( myAnother[i].title );
                dlg4.m_title   = pp ? pp : myAnother[i].title;

                pp = utf2sjis( myAnother[i].comment );
                dlg4.m_comment = pp ? pp : myAnother[i].comment;

                pp = utf2sjis( myAnother[i].tags );
                dlg4.m_tags    = pp ? pp : myAnother[i].tags;
            }

            dlg4.m_messageOnQuery.LoadString(IDS_REGISTER4); // �o�^
            dlg4.m_windowTextExtra  = "(" + dir + ")";
            dlg4.m_enableToBackward = (i == first) ? false : true;
            dlg4.m_backToPrevious   = false;

            int r = dlg4.DoModal();
            if ( r == IDCANCEL ) {
                withQuery = false;
                break;
            }
            if ( dlg4.m_backToPrevious ) {
                int j = i;
                while ( (--i > 0) && synchronized[i] )
                    ;
                if ( synchronized[i] == FALSE ) {
                    i--;
                    continue;
                }
                i = j;
            }
            if ( dlg4.m_executeWithoutQuery == true ) {
                CString title;
                CString text;

                title.LoadString(IDS_TTL_PUT_ALL_BOOKMARKS);
                text.LoadString( IDS_TXT_PUT_ALL_BOOKMARKS);
                sprintf( txt, text, (const char *)dir );
                r = MessageBox( NULL,
                                text,   // �c��̃u�b�N�}�[�N��S����C�ɓo�^���Ă��܂��Ă��\��Ȃ��ł���?
                                txt,    // (%s) �u�b�N�}�[�N�ꊇ�o�^�m�F
                                MB_YESNO|MB_ICONQUESTION );
                if ( r == IDYES )
                    withQuery = false;
            }
            if ( dlg4.m_execute == false )
                continue;
        }

        text.LoadString(IDS_TXT_CONTINUE_SYNCHRONIZING);
        sprintf( txt, text, (const char *)dir );
        dlg->ShowWindow( SW_SHOWNORMAL );
        dlg->ChangeDialogText( title,   // �u�b�N�}�[�N�̓���
                               txt );   // %s �]���� �c�c
        PutBookmarks( &(myAnother[i]), dlg, true );
        synchronized[i] = TRUE; /* �����ς� */
    }

    if ( cnt == 0 ) {
        text.LoadString(IDS_TXT_NO_SYNCHRONIZING);
        sprintf( txt, text, (const char *)dir );
        MessageBox( NULL,
                    txt,    // %s �����֓]������K�v�̂���u�b�N�}�[�N�͌�����܂���ł���
                    title,  // �u�b�N�}�[�N�̓���
                    MB_OK|MB_ICONINFORMATION );
    }
    else if ( withQuery ) {
        text.LoadString(IDS_TXT_END_SYNCHONIZING);
        sprintf( txt, text, (const char *)dir );
        MessageBox( NULL,
                    txt,    // %s �����ւ̓������I���܂���
                    title,  // �u�b�N�}�[�N�̓���
                    MB_OK|MB_ICONINFORMATION );
    }

    delete [] synchronized;
}

void    CUserInfo::ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction )
{
    if ( (bookmark1.Compare( m_bmName ) == 0) ||
         (bookmark2.Compare( m_bmName ) == 0)    ) {
        ProceedingDialog    dlg;
        CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��

        dlg.Create( IDD_PROCEEDING_DIALOG );

        if ( ((direction == SynchronizeBookmarkDialog::fromBM1toBM2) &&
              (bookmark2.Compare( m_bmName ) == 0)          ) ||
             ((direction == SynchronizeBookmarkDialog::fromBM2toBM1) &&
              (bookmark1.Compare( m_bmName ) == 0)          ) ||
             ((direction == SynchronizeBookmarkDialog::both)         &&
              ((bookmark1.Compare( m_bmName ) == 0) ||
               (bookmark2.Compare( m_bmName ) == 0)    )    )    ) {
            // OneBookmark �̒��g�� AnotherBookmark �ɓo�^
            MyClip      *myOne;
            int         numOfOneBookmarks;
            MyClip      *myAnother;
            int         numOfAnother;
            const char  *anotherBookmarkName;

            if ( bookmark1.Compare( m_bmName ) == 0 ) {
                myOne               = myBookmark1;
                numOfOneBookmarks   = numOfBookmark1;
                myAnother           = myBookmark2;
                numOfAnother        = numOfBookmark2;
                anotherBookmarkName = (const char*)bookmark2;
            }
            else {
                myOne               = myBookmark2;
                numOfOneBookmarks   = numOfBookmark2;
                myAnother           = myBookmark1;
                numOfAnother        = numOfBookmark1;
                anotherBookmarkName = (const char*)bookmark1;
            }

            ImportFromAnotherToOne( myAnother, numOfAnother,
                                    myOne,     numOfOneBookmarks,
                                    anotherBookmarkName,
                                    &dlg );
        }
    }
}


/*
 *  �u�b�N�}�[�N�̃G�N�X�|�[�g(�擾)
 */

bool    CUserInfo::ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2 )
{
    bool    cont = true;

    if ( (bookmark1.Compare( m_bmName ) == 0) ||
         (bookmark2.Compare( m_bmName ) == 0)    ) {
        MyClip  **myAnother;
        int     *numOfAnother;

        if ( bookmark1.Compare( m_bmName ) == 0 ) {
            myAnother    = myBookmark1;
            numOfAnother = numOfBookmark1;
        }
        else {
            myAnother    = myBookmark2;
            numOfAnother = numOfBookmark2;
        }

        cont = ExportFromAnother( myAnother, numOfAnother );

        switch ( m_bmType ) {
        case BK_MM_MEMO:
            if ( *numOfAnother > 0 ) {
                for ( int i = 0; i < *numOfAnother; i++ ) {
                    strcpy( (*myAnother)[i].title,
                            euc2sjis((*myAnother)[i].title) );
                    strcpy( (*myAnother)[i].comment,
                            euc2sjis((*myAnother)[i].comment) );
                    strcpy( (*myAnother)[i].tags,
                            euc2sjis((*myAnother)[i].tags) );
                }
            }
            break;
        }
    }

    return ( cont );
}

bool    CUserInfo::ExportFromAnother(
            MyClip **myAnother,
            int    *numOfAnother )
{
    bool        retry = false;
    CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

    // �u�b�N�}�[�N�S�擾
    do {
        retry = false;
        *myAnother = GetBookmarks( numOfAnother );
        if ( !(*myAnother) ) {
            int     r;
            char    txt[BUFSIZ];
            CString title;
            CString text;

            title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS_NOT_EXIST);
            text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS_NOT_EXIST);

            sprintf( txt, text, (const char *)m_bmName );
            r = MessageBox( NULL,
                            txt,
                            title,  // �u�b�N�}�[�N�擾���s(�܂��̓u�b�N�}�[�N�����݂��Ȃ�)
                            MB_YESNOCANCEL|MB_ICONWARNING );
            if ( r == IDYES )
                retry = true;
            else if ( r == IDNO )
                break;
            else
                return ( false );
        }
    } while ( retry == true );

    return ( true );
}


/*
 *  �u�b�N�}�[�N�̍폜
 */

void    CUserInfo::DeleteBookmarks(
            const char       *username,
            const char       *password,
            const char       *username2,
            const char       *password2,
            AUTH_TYPE        authType,
            bool             withQuery /* = true */,
            ProceedingDialog *dlg      /* = NULL */
        )
{
    CString title;
    CString text;

    if ( withQuery == false ) {
        title.LoadString(IDS_TTL_DELETE_ALL_BOOKMARKS);
        text.LoadString( IDS_TXT_DELETE_ALL_BOOKMARKS);
        int r = MessageBox( NULL,
                            text,   // �{���Ƀu�b�N�}�[�N��S���폜���Ă��܂��Ă��\��Ȃ���ł���?
                            title,  // �u�b�N�}�[�N�폜�m�F
                            MB_YESNO|MB_ICONQUESTION );
        if ( r == IDNO )
            return;
    }

    CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
    BOOL                ret;
    char                cookie[MAX_COOKIE_LEN];
    MyClipEx            *mp;
    int                 numOfClips = 0;
    ProceedingDialog    *pdlg;

    cookie[0] = NUL;

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }

    /* �폜�p�G���g��ID�ꗗ�� �擾 */
    DBSparam_t param;

    param.myBookmark     = NULL;
    param.numOfBookmarks = 0;
    param.bookmarkKind   = m_bmType;
    memset( param.cookie, 0x00, MAX_COOKIE_LEN + 1 );
    param.cookieSize     = MAX_COOKIE_LEN;
    param.dlg            = pdlg;
    param.u.authType     = authType;
    strcpy( param.u.username, username );
    strcpy( param.u.password, password );
    if ( username2 )
        strcpy( param.u.username2, username2 );
    else
        param.u.username2[0] = NUL;
    if ( password2 )
        strcpy( param.u.password2, password2 );
    else
        param.u.password2[0] = NUL;

    mp = GetBookmarksForDelete( &param, numOfClips );
    if ( !mp || (numOfClips == 0) ) {
        if ( mp )
            free( mp );

        title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS);
        text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS);
        MessageBox( NULL,
                    text,   // �u�b�N�}�[�N�����擾�ł��܂���ł���
                    title,  // �u�b�N�}�[�N�擾���s
                    MB_OK|MB_ICONWARNING );
        if ( !dlg )
            delete pdlg;
        return;
    }

    // �u�b�N�}�[�N��1���Â폜
    strcpy( cookie, param.cookie );
    BOOL    *deleted = new BOOL[numOfClips];
    int     i;
    for ( i = 0; i < numOfClips; i++ )
        deleted[i] = FALSE;
    for ( i = 0; i < numOfClips; i++ ) {
        if ( deleted[i] == TRUE )
            continue;
        if ( withQuery ) {
            pdlg->ShowWindow( SW_HIDE );

            // �u�b�N�}�[�N����\��
            DeleteBookmarkDialog4   d;
            const char              *p;

            while ( (p = strstr( mp[i].url, "&amp;" )) != NULL )
                strcpy( (char *)p + 1, p + 5 ); /* "&amp;" �� "&" �֒u��*/

            d.m_title   = mp[i].title;
            d.m_url     = mp[i].url;
            d.m_comment = mp[i].comment;
            d.m_tags    = mp[i].tags;
            d.m_enableToBackward = (i == 0) ? false : true;
            d.m_backToPrevious   = false;

            if ( i > 0 ) {
                int j = i - 1;
                while ( (j >= 0) && deleted[j] )
                    j--;
                if ( j < 0 )
                    d.m_enableToBackward = false;
            }

            int r = d.DoModal();
            if ( r == IDCANCEL )
                break;
            if ( d.m_backToPrevious ) {
                int j = i;
                while ( (--i > 0) && deleted[i] )
                    ;
                if ( deleted[i] == FALSE ) {
                    i--;
                    continue;
                }
                i = j;
            }
            if ( d.m_executeWithoutQuery == true ) {
                title.LoadString(IDS_TTL_DELETE_ALL);
                text.LoadString( IDS_TXT_DELETE_ALL);
                r = MessageBox( NULL,
                                text,   // �c��̃u�b�N�}�[�N��S����C�ɍ폜���Ă��܂��Ă��\��Ȃ��ł���?
                                title,  // �u�b�N�}�[�N�ꊇ�폜�m�F
                                MB_YESNO|MB_ICONQUESTION );
                if ( r == IDYES )
                    withQuery = false;
            }
            if ( d.m_execute == false )
                continue;

            pdlg->ShowWindow( SW_SHOWNORMAL );
        }

        text.LoadString(IDS_TXT_CONTINUE_DELETING);
        pdlg->ChangeDialogText( m_bmName,
                                text ); // �u�b�N�}�[�N�폜�� �c�c

        switch ( m_bmType ) {
        case BK_MM_MEMO:
            ret = deleteEntryOnMMmemo( cookie, &(mp[i]) );
            break;
        case BK_DRECOM_RSS:
            ret = deleteEntryOnDrecomRSS( cookie, &(mp[i]) );
            break;
        case BK_FLOG:
            ret = deleteEntryOnFlog( cookie, &(mp[i]) );
            break;
        case BK_LIVEDOOR_CLIP:
            ret = deleteEntryOnLivedoorClip( cookie, &(mp[i]) );
            if ( ret == FALSE ) {
                if ( m_apiKey.GetLength() > 0 )
                    ret = deleteEntryOnLivedoorClip2(
                                username, m_apiKey, mp[i].url );
            }
            break;
        case BK_ECNAVI_CLIP:
            ret = deleteEntryOnEcNaviClip( cookie, &(mp[i]) );
            break;
        case BK_NIFTY_CLIP:
            ret = deleteEntryOnNiftyClip( cookie, &(mp[i]) );
            break;
        case BK_POOKMARK:
            ret = deleteEntryOnPookmark( cookie, &(mp[i]) );
            break;
        case BK_JOLTMARK:
            ret = deleteEntryOnJoltMark( cookie, &(mp[i]) );
            break;
        case BK_BLOGPET:
            ret = deleteEntryOnBlogPet( cookie, &(mp[i]) );
            break;
        case BK_FC2BOOKMARK:
            ret = deleteEntryOnFC2bookmark( cookie, &(mp[i]) );
            break;
        case BK_YJ_BOOKMARK:
            ret = deleteEntryOnYJbookmark( cookie, &(mp[i]) );
            break;
        case BK_YAHOO_BOOKMARKS:
            ret = deleteEntryOnYahooBookmarks( cookie, &(mp[i]) );
            break;
        default:
            ret = FALSE;
            break;
        }

        if ( ret == FALSE ) {
            int r;

            title.LoadString(IDS_TTL_FAILURE_DELETE_BOOKMARKS);
            text.LoadString( IDS_TXT_FAILURE_DELETE_BOOKMARKS);
            r = MessageBox( NULL,
                            text,   // �u�b�N�}�[�N�̍폜�Ɏ��s���܂���    \r\n�����𑱍s���܂���?
                            title,  // �u�b�N�}�[�N�폜���s
                            MB_YESNO|MB_ICONWARNING );
            if ( r == IDYES )
                continue;
            break;
        }
        deleted[i] = TRUE;
    }

    delete [] deleted;
    free( mp );
    if ( !dlg )
        delete pdlg;
}

void    CUserInfo::DeleteBookmarks( bool deleteAll, bool deleteInteractive )
{
    if ( (deleteAll == false) && (deleteInteractive == false) )
        return;

    char                    username2[MAX_USERIDLEN + 1];
    char                    password2[MAX_PASSWDLEN + 1];
    DeleteBookmarkDialog3   dlg3;
    ProceedingDialog        dlg;

    dlg.Create( IDD_PROCEEDING_DIALOG );

    dlg3.m_username = "";
    dlg3.m_password = "";
    username2[0]    = NUL;
    password2[0]    = NUL;

    if ( (m_bmType != BK_NIFTY_CLIP) || (m_apiKey.GetLength() == 0) ) {
        if ( m_bmType != BK_LOCAL_OPML ) {
            GetUserInfo( dlg3.m_username,
                         dlg3.m_password,
                         dlg3.m_targetBookmark );

            if ( m_bmType != BK_1470NET ) {
                int ret = dlg3.DoModal();
                if ( (ret == IDCANCEL)                  ||
                     (dlg3.m_username.GetLength() == 0) ||
                     (dlg3.m_password.GetLength() == 0)    )
                    return;
            }
            else {
                if ( dlg3.m_username.GetLength() == 0 ) {
                    if ( m_username.GetLength() == 0 ) {
                        SettingDialog   sdlg;
                        sdlg.m_1470net = true;
                        sdlg.DoModal();

                        m_authType = sdlg.m_dlg08.m_authType;
                        m_username = sdlg.m_dlg08.m_username;
                        m_password = sdlg.m_dlg08.m_password;
                    }
                    dlg3.m_username = m_username;
                    dlg3.m_password = m_password;
                    if ( (dlg3.m_username.GetLength() == 0) ||
                         (dlg3.m_password.GetLength() == 0)    )
                        return;
                }
            }

            if ( (m_authType == AK_HATENA)         ||
                 (m_authType == AK_TYPEKEY_HATENA) ||
                 (m_authType == AK_HATENA_TYPEKEY)    ) {
                CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
                strcpy( username2, pp->m_hatena.m_username );
                strcpy( password2, pp->m_hatena.m_password );
            }
            else if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
                CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
                strcpy( username2, pp->m_yjBookmark.m_username );
                strcpy( password2, pp->m_yjBookmark.m_password );
                pp->MakeProxyText();
            }
        }
    }

    switch ( m_bmType ) {
    case BK_HATENA:
        DeleteHetanaBookmark( dlg3.m_username, dlg3.m_password,
                              deleteAll ? false : true,
                              &dlg );
        break;

    case BK_DELICIOUS:
        DeleteDeliciousBookmark( dlg3.m_username, dlg3.m_password,
                                 deleteAll ? false : true,
                                 &dlg );
        break;

    case BK_BLUEDOT:
        DeleteBlueDotBookmark( dlg3.m_username, dlg3.m_password,
                               deleteAll ? false : true,
                               &dlg );
        break;

    case BK_NIFTY_CLIP:
        if ( m_apiKey.GetLength() > 0 ) {
            DeleteNiftyClip( m_apiKey,
                             deleteAll ? false : true,
                             &dlg );
            break;
        }
     /* else               */
     /*      fall into ... */
    case BK_MM_MEMO:
    case BK_DRECOM_RSS:
    case BK_FLOG:
    case BK_LIVEDOOR_CLIP:
    case BK_ECNAVI_CLIP:
    case BK_POOKMARK:
    case BK_JOLTMARK:
    case BK_BLOGPET:
    case BK_FC2BOOKMARK:
    case BK_YJ_BOOKMARK:
    case BK_YAHOO_BOOKMARKS:
        DeleteBookmarks( dlg3.m_username, dlg3.m_password,
                         username2, password2,
                         m_authType,
                         deleteAll ? false : true,
                         &dlg );
        break;

    case BK_1470NET:
        Delete1470net( dlg3.m_username, dlg3.m_password,
                       username2, password2,
                       m_authType,
                       deleteAll ? false : true,
                       &dlg );
        break;

    case BK_NEWSING:
    case BK_DIGG:
        break;

    case BK_DIIGO:
        DeleteDiigo( dlg3.m_username, dlg3.m_password,
                     deleteAll ? false : true,
                     &dlg );
        break;

    case BK_LOCAL_OPML:
        DeleteLocalOpml( m_opmlFilename,
                         deleteAll ? false : true,
                         &dlg );
        break;
    }
}


// �u�b�N�}�[�N�̓o�^
typedef struct param_sub    {
    // �u�b�N�}�[�N�o�^�X���b�h�ɓn�������\����
    int         bookmarkKind;
    RBuser_t    u;
    int         numOfBookmarks;
    MyClip      *myBookmark;
    char        *title;
    int         changeCode;
    FILE        *fp;
}   RBSparam_t;

UINT
RegisterBookmarkSub( LPVOID pParam )
{
    // �u�b�N�}�[�N�o�^�X���b�h
    UINT        ret = 0;
    RBSparam_t  *p  = (RBSparam_t *)pParam;
    CString     str1;
    CString     str2;
    CString     str3;

    SetUserAgent( str1, str2, str3 );   /* User-Agent ���ꎞ�I�ɕύX */

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_HATENA:
        // �͂Ăȃu�b�N�}�[�N�ɓo�^
        putHB( p->u.username, p->u.password,
               p->u.useMyTitle,
               p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DELICIOUS:
        // del.icio.us �ɓo�^
        putDelicious( p->u.username, p->u.password,
                      p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_MM_MEMO:
        // MM/Memo �ɓo�^
        putMMmemo( p->u.username, p->u.password,
                   p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DRECOM_RSS:
        // �h���R��RSS �ɓo�^
        putDrecomRSS( p->u.username, p->u.password,
                      p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_FLOG:
        // Flog �ɓo�^
        putFlog( p->u.username, p->u.password,
                 p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP:
        // livedoor�N���b�v �ɓo�^
        putLivedoorClip( p->u.username, p->u.password,
                         p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_ECNAVI_CLIP:
        // Buzzurl �ɓo�^
        putEcNaviClip( p->u.username,  p->u.password,
                       p->u.username2, p->u.password2,
                       p->u.authType,
                       p->u.useMyTitle,
                       p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_NIFTY_CLIP:
        // �j�t�e�B�N���b�v �ɓo�^
        putNiftyClip( p->u.username, p->u.password,
                      p->u.apiKey,
                      p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_1470NET:
        // 1470.net���j���[�A���� �ɓo�^
        put1470net( p->u.username,  p->u.password,
                    p->u.username2, p->u.password2,
                    p->u.authType,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_NEWSING:
        // newsing �ɓo�^
        putNewsing( p->u.username,  p->u.password,
                    p->u.username2, p->u.password2,
                    p->u.authType,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_POOKMARK:
        // POOKMARK �ɓo�^
        putPookmark( p->u.username, p->u.password,
                     p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_BLUEDOT:
        // Blue Dot �ɓo�^
        putBlueDot( p->u.username, p->u.password,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_JOLTMARK:
        // JoltMark �ɓo�^
        putJoltMark( p->u.username, p->u.password,
                     p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_BLOGPET:
        // BlogPet �C�ɂȂ�L�� �ɓo�^
        putBlogPet( p->u.username, p->u.password,
                    p->u.useMyTitle,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_FC2BOOKMARK:
        // FC2BOOKMARK �ɓo�^
        putFC2Bookmark( p->u.username, p->u.password,
                        p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_TWITTER:
        // Twitter �Ŕ���
        putTwitter( p->u.username, p->u.password,
                    p->u.apiKey,   p->u.secret,
                    p->u.authType,
                    str1, str2, str3,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_TIMELOG:
        // Timelog �Ŕ���
        putTimelog( p->u.username, p->u.password,
                    str1, str2, str3,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_YJ_BOOKMARK:
        // Yahoo! �u�b�N�}�[�N �ɓo�^
        putYJbookmark( p->u.username, p->u.password,
                       p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_YAHOO_BOOKMARKS:
        // Yahoo! Bookmarks �ɓo�^
        putYahooBookmarks( p->u.username, p->u.password,
                           p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DIGG:
        // digg �ɓo�^
        putDigg( p->u.username, p->u.password,
                 p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_TUMBLR:
        // tumblr �ɓ��e
        putTumblr( p->u.username, p->u.password,
                   p->u.blogID,
                   str1,
                   p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DIIGO:
        // Diigo �ɓ��e
        putDiigo( p->u.username, p->u.password,
                  p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_LOCAL_OPML:
        // ���[�J��OPML�t�@�C���ɓo�^
        putLocalOpml( p->u.filename, p->myBookmark, p->numOfBookmarks );
        break;
    }

    SetUserAgent( FALSE );  /* User-Agent �����ɖ߂� */
    return ( ret );
}

void    CUserInfo::PutBookmarks(
            const MyClip     *myBookmark,
            int              numOfMyBookmarks,
            const char       *username,
            const char       *password,
            ProceedingDialog *pDlg )
{
    RBSparam_t  param;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = numOfMyBookmarks;
    param.myBookmark = (MyClip *)
                            malloc( sizeof ( MyClip ) * numOfMyBookmarks );
    if ( !param.myBookmark ) {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_MEMORY_EXHAUSTED);
        text.LoadString( IDS_TXT_MEMORY_EXHAUSTED);
        MessageBox( NULL,
                    text,   // ��ƂɕK�v�ȃ��������m�ۂł��܂���ł����B
                    title,  // �������m�ێ��s
                    MB_OK|MB_ICONWARNING );
        return;
    }

    param.u.isTarget   = m_isTarget;
    param.u.useMyTitle = m_useMyTitle;
    strcpy( param.u.username, username );
    strcpy( param.u.password, password );
    param.u.authType = m_authType;
    if ( (m_authType == AK_HATENA)         ||
         (m_authType == AK_TYPEKEY_HATENA) ||
         (m_authType == AK_HATENA_TYPEKEY)    ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_hatena.m_username );
        strcpy( param.u.password2, pp->m_hatena.m_password );
    }
    else if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_yjBookmark.m_username );
        strcpy( param.u.password2, pp->m_yjBookmark.m_password );
        pp->MakeProxyText();
    }
    else {
        param.u.username2[0] = NUL;
        param.u.password2[0] = NUL;
    }
    if ( m_opmlFilename.GetLength() > 0 )
        strcpy( param.u.filename, m_opmlFilename );
    else
        param.u.filename[0] = NUL;

    if ( m_apiKey.GetLength() > 0 )
        strcpy( param.u.apiKey, m_apiKey );
    else
        param.u.apiKey[0] = NUL;

    if ( m_secret.GetLength() > 0 )
        strcpy( param.u.secret, m_secret );
    else
        param.u.secret[0] = NUL;

    if ( m_blogID.GetLength() > 0 )
        strcpy( param.u.blogID, m_blogID );
    else
        param.u.blogID[0] = NUL;

    memcpy( param.myBookmark, myBookmark,
            sizeof ( MyClip ) * numOfMyBookmarks );

    param.title      = NULL;
    param.changeCode = UTF8;
    param.fp         = NULL;

    // �u�b�N�}�[�N�o�^�X���b�h���N��
    CWinThread  *tp = AfxBeginThread( RegisterBookmarkSub,
                                      (void *)&param );
    if ( tp ) {
        DWORD   exitCode  = 0;
        int     status;
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

        // �u�b�N�}�[�N�o�^�X���b�h���I������̂�҂�
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView �������� CBookeyDlg �̍ĕ`��
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog �̍ĕ`��
                pDlg->SetFocus();
                pDlg->UpdateWindow();
                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        delete tp;
    }

    free( param.myBookmark );
}

void    CUserInfo::PutBookmarks(
            const MyClip     *myBookmark,
            ProceedingDialog *pDlg,
            bool             useOrigText /* = false */ )
{
    char    txt[BUFSIZ];
    CString title;
    CString text;

    if ( useOrigText == false ) {
        title.LoadString(IDS_TTL_CONTINUE_PUTTING_BOOKMARKS);
        text.LoadString( IDS_TXT_CONTINUE_PUTTING_BOOKMARKS);
        sprintf( txt, text, (const char *)m_bmName );
        pDlg->ChangeDialogText( title,  // �u�b�N�}�[�N�o�^��
                                txt );
    }

    PutBookmarks( myBookmark, 1,
                  (const char *)m_username, (const char *)m_password,
                  pDlg );
}

void    CUserInfo::PutBookmarks(
            const MyClip *myBookmark,
            int          numOfMyBookmarks,
            const char   *username /* = NULL */,
            const char   *password /* = NULL */ )
{
    CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
    ProceedingDialog    dlg;
    CString             text;

    text.LoadString(IDS_TXT_CONTINUE_PUTTING_BOOKMARK_INFO);
    dlg.Create( IDD_PROCEEDING_DIALOG );
    dlg.ChangeDialogText( m_bmName,
                          text );   // �u�b�N�}�[�N���o�^�� �c�c

    if ( !username && !password ) {
        username = (const char *)m_username;
        password = (const char *)m_password;
    }

    PutBookmarks( myBookmark, numOfMyBookmarks,
                  username, password,
                  &dlg );
}


UINT
RegisterBookmarkFromFile( LPVOID pParam )
{
    // �u�b�N�}�[�N���o�̓X���b�h
    UINT        ret = 0;
    RBSparam_t  *p  = (RBSparam_t *)pParam;
    const char  *s  = "generated by Bookey";

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_LOCAL_OPML:
        outputOPML( p->myBookmark, p->numOfBookmarks,
                    p->title && p->title[0] ? p->title : s,
                    p->changeCode, p->fp );
        break;

    case CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1:
        outputBookmarkHtml( p->myBookmark, p->numOfBookmarks,
                            p->title && p->title[0] ? p->title : s,
                            p->changeCode, p->fp );
        break;

    case CUserInfo::BK_OPERA6_ADR:
        outputOpera6Adr( p->myBookmark, p->numOfBookmarks,
                         p->title && p->title[0] ? p->title : s,
                         p->changeCode, p->fp );
        break;

    case CUserInfo::BK_HATENA_BOOKMARK_ATOM:
        break;

    case CUserInfo::BK_DELICIOUS_XML:
        outputDeliciousXML( p->myBookmark, p->numOfBookmarks, p->fp,
                            p->u.username );
        break;
    }

    return ( ret );
}

void    CUserInfo::PutBookmarks(
            const MyClip *myBookmark,
            int          numOfMyBookmarks,
            const char   *bookmarkNameAsImport,
            bool         &result )
{
    CFileDialog *fileDlg = NULL;
    FILE        *fp      = NULL;
    CString     fileName;
    CString     fileType;
    const char  *fileExtention;
    const char  *fileDefault;
    CString     title;
    CString     text;
    RBSparam_t  param;

    fileExtention = NULL;
    fileDefault   = NULL;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = numOfMyBookmarks;
    param.myBookmark = (MyClip *)
                            malloc( sizeof ( MyClip ) * numOfMyBookmarks );
    if ( !param.myBookmark ) {
        title.LoadString(IDS_TTL_MEMORY_EXHAUSTED);
        text.LoadString( IDS_TXT_MEMORY_EXHAUSTED);
        MessageBox( NULL,
                    text,   // ��ƂɕK�v�ȃ��������m�ۂł��܂���ł����B
                    title,  // �������m�ێ��s
                    MB_OK|MB_ICONWARNING );
        return;
    }

    param.u.isTarget     = m_isTarget;
    param.u.authType     = m_authType;
    param.u.username[0]  = NUL;
    param.u.password[0]  = NUL;
    param.u.username2[0] = NUL;
    param.u.password2[0] = NUL;
    param.u.filename[0]  = NUL;

    memcpy( param.myBookmark, myBookmark,
            sizeof ( MyClip ) * numOfMyBookmarks );

    param.title      = NULL;
    param.changeCode = UTF8;
    param.fp         = NULL;

    result   = false;
    fileName = _T("");

    switch ( m_bmType ) {
    case BK_LOCAL_OPML:
        fileType.LoadString( IDS_FILETYPE_OPML );
        title.LoadString(IDS_WRFAIL_OPML);
        text.LoadString( IDS_OPFAIL_OPML);
        fileExtention = "opml";
        break;

    case BK_NETSCAPE_BOOKMARK_FILE_1:
        fileType.LoadString( IDS_FILETYPE_HTML );
        title.LoadString(IDS_WRFAIL_HTML);
        text.LoadString( IDS_OPFAIL_HTML);
        fileExtention = "html";
        break;

    case BK_OPERA6_ADR:
        fileType.LoadString( IDS_FILETYPE_OPERA_6 );
        title.LoadString(IDS_WRFAIL_ADR);
        text.LoadString( IDS_OPFAIL_ADR);
        fileExtention = "adr";
        break;

    case BK_HATENA_BOOKMARK_ATOM:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_WRFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        break;

    case BK_DELICIOUS_XML:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_WRFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        break;
    }

    if ( fileExtention )
        fileDlg = new CFileDialog( FALSE, fileExtention, fileDefault,
                                   OFN_OVERWRITEPROMPT,
                                   fileType );
    if ( fileDlg ) {
        if ( fileDlg->DoModal() == IDOK )
            fileName = fileDlg->GetPathName();
        delete fileDlg;

        if ( fileName.GetLength() > 0 ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            if ( pp->m_langCode == 0x0411 ) {
                // ���{�ꃂ�[�h�̏ꍇ�̂�
                if ( m_bmType == BK_NETSCAPE_BOOKMARK_FILE_1 ) {
                    int r = ::MessageBox( NULL,
                                "UTF-8 �ŏo�͂��܂���? \r\n\r\n"
                                "�u�������v���N���b�N����� Shift_JIS �ŏo��"
                                "���܂��B    \r\nInternet Explorer �ւ̃C��"
                                "�|�[�g�����l���̏ꍇ��\r\n�u�������v��I��"
                                "���Ă�������",
                                "�����R�[�h�m�F",
                                MB_YESNO|MB_ICONQUESTION );
                    if ( r == IDNO )
                        param.changeCode = SJIS;
                }
            }
            fp = fopen( fileName, "w" );
        }
    }

    if ( fp ) {
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��
        ProceedingDialog    dlg;
        const char          *s;

        text.LoadString(IDS_TXT_CONTINUE_PUTTING_BOOKMARK_INFO);
        dlg.Create( IDD_PROCEEDING_DIALOG );
        dlg.ChangeDialogText( m_bmName,
                              text );   // �u�b�N�}�[�N���o�^��

        if ( param.changeCode != SJIS )
            param.changeCode = GetChangeCode( bookmarkNameAsImport );
        param.fp = fp;
        s = param.changeCode != UTF8 ? bookmarkNameAsImport
                                     : sjis2utf(bookmarkNameAsImport);
        if ( s ) {
            param.title = (char *)malloc( strlen( s ) + 1 );
            if ( param.title )
                strcpy( param.title, s );
        }

        if ( m_bmType == BK_DELICIOUS_XML ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            if ( pp->m_delicious.m_username.GetLength() > 0 )
                strcpy( param.u.username, pp->m_delicious.m_username );
        }

        // �u�b�N�}�[�N���o�̓X���b�h���N��
        CWinThread  *tp = AfxBeginThread( RegisterBookmarkFromFile,
                                          (void *)&param );
        if ( tp ) {
            DWORD   exitCode  = 0;
            int     status;
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

            // �u�b�N�}�[�N���o�̓X���b�h���I������̂�҂�
            tp->m_bAutoDelete = FALSE;
            do {
                status = GetExitCodeThread( tp->m_hThread, &exitCode );
                if ( status == FALSE )
                    break;
                if ( exitCode == STILL_ACTIVE ) {
                    // CBookeyView �������� CBookeyDlg �̍ĕ`��
                    MSG msg;
                    if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                        DispatchMessage( &msg );

                    // ProceedingDialog �̍ĕ`��
                    dlg.SetFocus();
                    dlg.UpdateWindow();
                    Sleep( MS_THREAD_REGISTERBOOKMARK );
                }
            } while ( exitCode == STILL_ACTIVE );

            delete tp;
        }

        if ( param.title )
            free( param.title );
        fclose( fp );
        result = true;
    }
    else {
        switch ( m_bmType ) {
        case BK_LOCAL_OPML:
        case BK_NETSCAPE_BOOKMARK_FILE_1:
        case BK_OPERA6_ADR:
        case BK_HATENA_BOOKMARK_ATOM:
        case BK_DELICIOUS_XML:
            ::MessageBox( NULL, text, title, MB_OK|MB_ICONWARNING );
            break;
        }
    }

    free( param.myBookmark );
}


// �u�b�N�}�[�N�̎擾
typedef struct param_sub2   {
    // �u�b�N�}�[�N�擾�X���b�h�ɓn�������\����
    int                 bookmarkKind;
    char                bookmarkName[32];
    char                dialogText[96];
    RBuser_t            u;
    int                 numOfBookmarks;
    MyClip              *myBookmark;
    ProceedingDialog    *dlg;
    FILE                *fp;
    size_t              fileSize;
}   IBSparam_t;

UINT
InquiryBookmarkSub( LPVOID pParam )
{
    // �u�b�N�}�[�N�擾�X���b�h
    UINT        ret   = 0;
    IBSparam_t  *p    = (IBSparam_t *)pParam;
    int         total = 0;

    SetUserAgent( TRUE );   /* User-Agent ���ꎞ�I�ɕύX */

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_HATENA:
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        total = getNumberOfHatenaBookmark( p->u.username, p->u.password );
        p->myBookmark = getHB( p->u.username, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_DELICIOUS:
        // del.icio.us ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        total = getNumberOfBookmarksOnDelicious( p->u.username, p->u.password );
        p->numOfBookmarks = total;
        p->myBookmark = getDelicious( p->u.username, p->u.password,
                                      &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_MM_MEMO:
        // MM/Memo ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getMMmemo( p->u.username, p->u.password,
                                   &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_DRECOM_RSS:
        // �h���R��RSS ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getDrecomRSS( p->u.username, p->u.password,
                                      &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_FLOG:
        // Flog ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        if ( p->u.password[0] )
            p->myBookmark = getFlog( p->u.username, p->u.password, NULL,
                                     &(p->numOfBookmarks) );
        else
            p->myBookmark = getFlog( NULL, NULL, p->u.username,
                                     &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP:
        // livedoor�N���b�v ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getLivedoorClip( p->u.username, p->u.password,
                                         &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_ECNAVI_CLIP:
        // Buzzurl ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        if ( p->u.password[0]                              ||
             ((p->u.authType == AK_YAHOOJAPAN_BBAUTH) &&
              (p->u.password2[0])                        )    ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            pp->MakeProxyText();
            p->myBookmark = getEcNaviClip( p->u.username,  p->u.password,
                                           p->u.username2, p->u.password2,
                                           p->u.authType,
                                           NULL,
                                           &total, &(p->numOfBookmarks) );
        }
        else
            p->myBookmark = getEcNaviClip( NULL, NULL,
                                           NULL, NULL,
                                           AK_ORIGINAL,
                                           p->u.username,
                                           &(p->numOfBookmarks), &total );
        break;

    case CUserInfo::BK_NIFTY_CLIP:
        // �j�t�e�B�N���b�v ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getNiftyClip( p->u.username, p->u.password,
                                      p->u.apiKey,
                                      &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_1470NET:
        // 1470.net���j���[�A���� ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = get1470net( p->u.username,  p->u.password,
                                    p->u.username2, p->u.password2,
                                    p->u.authType,
                                    &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_NEWSING:
    case CUserInfo::BK_DIGG:
        break;

    case CUserInfo::BK_POOKMARK:
        // POOKMARK Airlines ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getPookmark( p->u.username, p->u.password,
                                     &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_BLUEDOT:
        // Blue Dot ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        total = getNumberOfBookmarksOnBlueDot( p->u.username, p->u.password );
        p->numOfBookmarks = total;
        p->myBookmark = getBlueDot( p->u.username, p->u.password,
                                    &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_JOLTMARK:
        // JoltMark ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getJoltMark( p->u.username, p->u.password,
                                     &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_BLOGPET:
        // BlogPet �C�ɂȂ�L�� ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getBlogPet( p->u.username, p->u.password,
                                    &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_FC2BOOKMARK:
        // FC2BOOKMARK ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getFC2Bookmark( p->u.username, p->u.password,
                                        &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_YJ_BOOKMARK:
        // Yahoo! �u�b�N�}�[�N ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getYJbookmark( p->u.username, p->u.password,
                                       &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_YAHOO_BOOKMARKS:
        // Yahoo! Bookmarks ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getYahooBookmarks( p->u.username, p->u.password,
                                           &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_DIIGO:
        // Diigo ����u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getDiigo( p->u.username, p->u.password,
                                  &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_LOCAL_OPML:
        // ���[�J��OPML�t�@�C������u�b�N�}�[�N�����擾
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getLocalOpml( p->u.filename, &(p->numOfBookmarks) );
        break;
    }

    if ( (total > 0) && (p->numOfBookmarks < total) ) {
        // �擾���s
        char        msg[BUFSIZ];
        CString     title;
        CString     text;
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARK_INFO);
        text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARK_INFO);

        if ( pp->m_langCode != 0x0411 )
            sprintf( msg,
                     text,  // Only %d in %d all was able to be acquired.
                     p->numOfBookmarks, total );
        else
            sprintf( msg,
                     text,  // �S %d ���� %d �������擾�ł��܂���ł����B
                     total, p->numOfBookmarks );
        if ( p->numOfBookmarks == 0 ) {
            unsigned short status = getStatusCode();
            if ( status >= 400 )
                sprintf( msg + strlen(msg), "\r\n(status code: %d)", status );
        }
        MessageBox( NULL,
                    msg,
                    title,  // �u�b�N�}�[�N���擾���s
                    MB_OK|MB_ICONWARNING );
        if ( p->numOfBookmarks < total / 10 ) { /* {@@} */
            free( p->myBookmark );
            p->myBookmark = NULL;
            p->numOfBookmarks = 0;
        }                                       /* {@@} */
    }

#ifdef  _DEBUG
    if ( p->myBookmark && (p->numOfBookmarks > 0) )
        dumpBookmark( p->bookmarkKind, p->myBookmark, p->numOfBookmarks );
#endif

    SetUserAgent( FALSE );  /* User-Agent �����ɖ߂� */
    return ( ret );
}

MyClip  *CUserInfo::GetBookmarks(
            int        &numOfMyBookmarks,
            const char *username /* = NULL */,
            const char *password /* = NULL */ )
{
    IBSparam_t          param;
    MyClip              *p = NULL;
    ProceedingDialog    dlg;
    CWaitCursor         cur;    // �}�E�X�J�[�\���������v�\��
    CString             text;

    dlg.Create( IDD_PROCEEDING_DIALOG );

    numOfMyBookmarks = 0;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = 0;
    param.myBookmark     = NULL;
    param.dlg            = &dlg;
    param.fp             = NULL;
    strcpy( param.bookmarkName, (const char *)m_bmName );
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    strcpy( param.dialogText,
            text ); // �u�b�N�}�[�N���擾�� �c�c

    switch ( m_bmType ) {
    case BK_HATENA:
        if ( !username || !strcmp( username, m_username ) ) {
            strcpy( param.u.username, m_username );
            strcpy( param.u.password, m_password );
        }
        else {
            strcpy( param.u.username, username );
            param.u.password[0] = NUL;
        }
        break;

    case BK_MM_MEMO:
    case BK_1470NET:
    case BK_DELICIOUS:
    case BK_FLOG:
    case BK_ECNAVI_CLIP:
    case BK_LIVEDOOR_CLIP:
    case BK_NIFTY_CLIP:
    case BK_NEWSING:
    case BK_POOKMARK:
    case BK_BLUEDOT:
    case BK_JOLTMARK:
    case BK_BLOGPET:
    case BK_FC2BOOKMARK:
    case BK_YJ_BOOKMARK:
    case BK_YAHOO_BOOKMARKS:
    case BK_DIGG:
    case BK_DIIGO:
        if ( username && *username ) {
            strcpy( param.u.username, username );
            if ( password && *password )
                strcpy( param.u.password, password );
            else
                param.u.password[0] = NUL;
        }
        else {
            strcpy( param.u.username, m_username );
            strcpy( param.u.password, m_password );
        }
        break;

    case BK_DRECOM_RSS:
        if ( (username && *username) && (password && *password) ) {
            strcpy( param.u.username, username );
            strcpy( param.u.password, password );
        }
        else {
            strcpy( param.u.username, m_username );
            strcpy( param.u.password, m_password );
        }
        break;

    case BK_LOCAL_OPML:
    case BK_NETSCAPE_BOOKMARK_FILE_1:
    case BK_OPERA6_ADR:
    case BK_DELICIOUS_XML:
        param.u.username[0] = NUL;
        param.u.password[0] = NUL;
        break;
    }
    param.u.authType = m_authType;
    if ( (m_authType == AK_HATENA)         ||
         (m_authType == AK_TYPEKEY_HATENA) ||
         (m_authType == AK_HATENA_TYPEKEY)    ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_hatena.m_username );
        strcpy( param.u.password2, pp->m_hatena.m_password );
    }
    else if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_yjBookmark.m_username );
        strcpy( param.u.password2, pp->m_yjBookmark.m_password );
        pp->MakeProxyText();
    }
    else {
        param.u.username2[0] = NUL;
        param.u.password2[0] = NUL;
    }
    if ( m_opmlFilename.GetLength() > 0 )
        strcpy( param.u.filename, m_opmlFilename );
    else
        param.u.filename[0] = NUL;

    if ( m_apiKey.GetLength() > 0 )
        strcpy( param.u.apiKey, m_apiKey );
    else
        param.u.apiKey[0] = NUL;

    if ( m_secret.GetLength() > 0 )
        strcpy( param.u.secret, m_secret );
    else
        param.u.secret[0] = NUL;

    // �u�b�N�}�[�N�擾�X���b�h���N��
    CWinThread  *tp = AfxBeginThread( InquiryBookmarkSub,
                                      (void *)&param );
    if ( tp ) {
        DWORD   exitCode  = 0;
        int     status;
        CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

        // �u�b�N�}�[�N�擾�X���b�h���I������̂�҂�
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView �������� CBookeyDlg �̍ĕ`��
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog �̍ĕ`��
                dlg.SetFocus();
                dlg.UpdateWindow();
                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        if ( param.myBookmark ) {
            if ( param.numOfBookmarks > 0 ) {
                p = param.myBookmark;
                numOfMyBookmarks = param.numOfBookmarks;
            }
            else
                free( param.myBookmark );
        }

        delete tp;
    }

    return ( p );
}


UINT
InquiryBookmarkFromFile( LPVOID pParam )
{
    // �u�b�N�}�[�N�擾�X���b�h
    UINT        ret = 0;
    IBSparam_t  *p  = (IBSparam_t *)pParam;

    p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_LOCAL_OPML:
        p->myBookmark = inputOPML( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1:
        p->myBookmark = inputBookmarkHtml( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_OPERA6_ADR:
        p->myBookmark = inputOpera6Adr( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_HATENA_BOOKMARK_ATOM:
        p->myBookmark = inputHatenaFeed( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP_RSS:
        p->myBookmark = inputLivedoorFeed( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_DELICIOUS_XML:
        p->myBookmark = inputDeliciousXML( &(p->numOfBookmarks),
                                           p->fp, p->fileSize );
        break;
    }

    return ( ret );
}

MyClip  *CUserInfo::GetBookmarks(
            int  &numOfMyBookmarks,
            bool &result )
{
    IBSparam_t          param;
    CString             fileName;
    CString             fileType;
    const char          *fileExtention;
    const char          *fileDefault;
    CString             title;
    CString             text;
    ProceedingDialog    dlg;
    MyClip              *p         = NULL;
    CFileDialog         *fileDlg   = NULL;
    FILE                *fp        = NULL;
    int                 numOfClips = 0;

    result        = false;
    fileName      = _T("");
    fileType      = _T("");
    fileExtention = NULL;
    fileDefault   = NULL;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = 0;
    param.myBookmark     = NULL;
    param.dlg            = &dlg;
    param.fp             = NULL;
    param.fileSize       = 0;
    strcpy( param.bookmarkName, (const char *)m_bmName );
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    strcpy( param.dialogText,
            text ); // �u�b�N�}�[�N���擾�� �c�c
    param.u.username[0]  = NUL;
    param.u.password[0]  = NUL;
    param.u.username2[0] = NUL;
    param.u.password2[0] = NUL;
    param.u.authType     = m_authType;
    param.u.filename[0]  = NUL;

    switch ( m_bmType ) {
    case BK_LOCAL_OPML:
        fileType.LoadString( IDS_FILETYPE_OPML );
        title.LoadString(IDS_RDFAIL_OPML);
        text.LoadString( IDS_OPFAIL_OPML);
        fileExtention = "opml";
        break;

    case BK_NETSCAPE_BOOKMARK_FILE_1:
        fileType.LoadString( IDS_FILETYPE_HTML );
        title.LoadString(IDS_RDFAIL_HTML);
        text.LoadString( IDS_OPFAIL_HTML);
        fileExtention = "html";
        break;

    case BK_OPERA6_ADR:
        fileType.LoadString( IDS_FILETYPE_OPERA_6 );
        title.LoadString(IDS_RDFAIL_ADR);
        text.LoadString( IDS_OPFAIL_ADR);
        fileExtention = "adr";
        fileDefault   = "opera6.adr";
        break;

    case BK_HATENA_BOOKMARK_ATOM:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_RDFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        fileDefault   = "dump.xml";
        break;

    case BK_LIVEDOOR_CLIP_RSS:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_RDFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        fileDefault   = "export.xml";
        break;

    case BK_DELICIOUS_XML:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_RDFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        fileDefault   = "all.xml";
        break;
    }

    if ( fileExtention )
        fileDlg = new CFileDialog( TRUE, fileExtention, fileDefault,
                                   OFN_FILEMUSTEXIST | OFN_READONLY,
                                   fileType );
    if ( fileDlg ) {
        if ( fileDlg->DoModal() == IDOK )
            fileName = fileDlg->GetPathName();
        delete fileDlg;

        if ( fileName.GetLength() > 0 ) {
            struct stat s;
            if ( !stat( fileName, &s ) )
                param.fileSize = s.st_size;
            fp = fopen( fileName, "rb" );
        }
    }

    if ( fp ) {
        dlg.Create( IDD_PROCEEDING_DIALOG );
        param.fp = fp;

        // �u�b�N�}�[�N�擾�X���b�h���N��
        CWinThread  *tp = AfxBeginThread( InquiryBookmarkFromFile,
                                          (void *)&param );
        if ( tp ) {
            DWORD   exitCode  = 0;
            int     status;
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

            // �u�b�N�}�[�N�擾�X���b�h���I������̂�҂�
            tp->m_bAutoDelete = FALSE;
            do {
                status = GetExitCodeThread( tp->m_hThread, &exitCode );
                if ( status == FALSE )
                    break;
                if ( exitCode == STILL_ACTIVE ) {
                    // CBookeyView �������� CBookeyDlg �̍ĕ`��
                    MSG msg;
                    if ( PeekMessage(&msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE) )
                        DispatchMessage( &msg );

                    // ProceedingDialog �̍ĕ`��
                    dlg.SetFocus();
                    dlg.UpdateWindow();
                    Sleep( MS_THREAD_REGISTERBOOKMARK );
                }
            } while ( exitCode == STILL_ACTIVE );

            if ( param.myBookmark ) {
                if ( param.numOfBookmarks > 0 ) {
                    p = param.myBookmark;
                    numOfClips = param.numOfBookmarks;
                }
                else
                    free( param.myBookmark );
            }

            delete tp;
        }
        fclose( fp );
        result = true;
    }
    else {
        switch ( m_bmType ) {
        case BK_LOCAL_OPML:
        case BK_NETSCAPE_BOOKMARK_FILE_1:
        case BK_OPERA6_ADR:
        case BK_HATENA_BOOKMARK_ATOM:
        case BK_LIVEDOOR_CLIP_RSS:
        case BK_DELICIOUS_XML:
            ::MessageBox( NULL, text, title, MB_OK|MB_ICONWARNING );
            break;
        }
    }

    numOfMyBookmarks = numOfClips;

    return ( p );
}


/* �^�O�ꗗ�̎擾 */
TagList *CUserInfo::GetTagList( int &numOfTags )
{
    TagList *p = NULL;

    numOfTags = 0;
    switch ( m_bmType ) {
    case BK_DELICIOUS:
        p = getTagListOnDelicious( m_username, m_password, &numOfTags );
        break;

    case BK_BLUEDOT:
        p = getTagListOnBlueDot( m_username, m_password, &numOfTags );
        break;

    case BK_HATENA:
        p = getTagListOnHatenaBookmark( m_username, m_password, &numOfTags );
        break;

    case BK_NIFTY_CLIP:
        p = getTagListOnNiftyClip( m_username, m_password, &numOfTags );
        break;
    }

    return ( p );
}

/* �^�O�̍폜 */
void    CUserInfo::DeleteTag( const char *tag )
{
    switch ( m_bmType ) {
    case BK_DELICIOUS:
        removeTagOnDelicious( m_username, m_password, tag );
        break;

    case BK_HATENA:
        removeTagFromBookmarksOnHatena( m_username, m_password, tag );
        break;

    case BK_NIFTY_CLIP:
        removeTagFromBookmarksOnNiftyClip( m_username, m_password, tag );
        break;
    }
}

/* �^�O�̒u�� */
void    CUserInfo::ReplaceTag( const char *oldTag, const char *newTag )
{
    switch ( m_bmType ) {
    case BK_DELICIOUS:
        renameTagOnDelicious( m_username, m_password, oldTag, newTag );
        break;

    case BK_BLUEDOT:
        renameTagOnBlueDot( m_username, m_password, oldTag, newTag );
        break;

    case BK_HATENA:
        renameTagFromBookmarksOnHatena( m_username, m_password,
                                        oldTag, newTag );
        break;

    case BK_NIFTY_CLIP:
        renameTagFromBookmarksOnNiftyClip( m_username, m_password,
                                           oldTag, newTag );
        break;
    }
}


/*
 *  �����ݒ�t�@�C���֘A
 */

bool    CUserInfo::EvalKeys(
                        const char          *p,
                        const unsigned char *rsaString )
{
    bool    ret = false;
    char    target[BUFSIZ];
    char    encrypted[BUFSIZ];

    encrypted[0] = NUL;

    sprintf( target, "bookmarkFor%s", m_bmSymbol );
    if ( evalKey( p, target, m_isTarget ) )
        ret = true;
    if ( ret == false ) {
        sprintf( target, "useMyTitleFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_useMyTitle ) )
            ret = true;
    }
    if ( ret == false ) {
        long    l = 0;

        sprintf( target, "authTypeFor%s", m_bmSymbol );
        if ( evalKey( p, target, l ) ) {
            ret = true;
            m_authType = (AUTH_TYPE)l;
        }
    }
    if ( ret == false ) {
        sprintf( target, "usernameFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_username ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "passwordFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_password,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "filenameFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_opmlFilename ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "APIkeyFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_apiKey,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "SecretFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_secret,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "blogIDFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_blogID ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "blogNameFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_blogName ) )
            ret = true;
    }

    return ( ret );
}

bool    CUserInfo::CheckKeys(
                        const char          *p,
                        const unsigned char *rsaString,
                        bool                &ret )
{
    bool    cont = false;
    char    encrypted[BUFSIZ];
    char    target[BUFSIZ];
    bool    checkPassword = true;
    bool    checkApiKey   = true;
    bool    checkSecret   = true;

    sprintf( target, "passwordFor%sEncrypted", m_bmSymbol );
    if ( evalKey( p, target, encrypted ) ) {
        checkKey( m_password,
                  (unsigned char *)encrypted,
                  rsaString,
                  checkPassword );
        cont = true;
    }

    if ( cont == false ) {
        sprintf( target, "APIkeyFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_apiKey,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkApiKey );
            cont = true;
        }
    }

    if ( cont == false ) {
        sprintf( target, "SecretFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_secret,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkSecret );
            cont = true;
        }
    }

    ret &= (checkPassword & checkApiKey & checkSecret);

    return ( cont );
}

void    CUserInfo::WriteKeys(
            FILE          *fp,      // (I/O) �����o����
            char          *key,     // (I)   ���J��
            unsigned char **secret, // (I/O) �����ɕK�v�ȏ��(�閧��)
            bool          &done )   // (O)   �Í����������s�ς݂��ۂ�
{
    char    target[BUFSIZ];

    sprintf( target, "bookmarkFor%s", m_bmSymbol );
    writeKey( fp, target, m_isTarget );

    sprintf( target, "useMyTitleFor%s", m_bmSymbol );
    writeKey( fp, target, m_useMyTitle );

    sprintf( target, "authTypeFor%s", m_bmSymbol );
    writeKey( fp, target, (long)m_authType );

    if ( m_username.GetLength() > 0 ) {
        sprintf( target, "usernameFor%s", m_bmSymbol );
        writeKey( fp, target, m_username );
    }

    if ( m_password.GetLength() > 0 ) {
        sprintf( target, "passwordFor%s", m_bmSymbol );
        writeKey( fp, target, m_password, key, secret, done );
    }

    if ( m_opmlFilename.GetLength() > 0 ) {
        sprintf( target, "filenameFor%s", m_bmSymbol );
        writeKey( fp, target, m_opmlFilename );
    }

    if ( m_apiKey.GetLength() > 0 ) {
        sprintf( target, "APIkeyFor%s", m_bmSymbol );
        writeKey( fp, target, m_apiKey, key, secret, done );
    }

    if ( m_secret.GetLength() > 0 ) {
        sprintf( target, "SecretFor%s", m_bmSymbol );
        writeKey( fp, target, m_secret, key, secret, done );
    }

    if ( m_blogID.GetLength() > 0 ) {
        sprintf( target, "blogIDFor%s", m_bmSymbol );
        writeKey( fp, target, m_blogID );
    }
    if ( m_blogName.GetLength() > 0 ) {
        sprintf( target, "blogNameFor%s", m_bmSymbol );
        writeKey( fp, target, m_blogName );
    }
}


/* �u�b�N�}�[�N�o��(�G�N�X�|�[�g)���̓���(�C���|�[�g)���̕����R�[�h���擾 */
int CUserInfo::GetChangeCode( CString bookmarkNameAsImport )
{
    int         changeCode = UTF8;

    if ( m_tgt_hatenaBookmark.GetLength() == 0 ) {
        m_tgt_hatenaBookmark.LoadString( IDS_TGT_HATENA_BOOKMARK );
        m_tgt_delicious.LoadString( IDS_TGT_DELICIOUS );
        m_tgt_mmMemo.LoadString( IDS_TGT_MMMEMO );
        m_tgt_drecomRSS.LoadString( IDS_TGT_DRECOM_RSS );
        m_tgt_flog.LoadString( IDS_TGT_FLOG );
        m_tgt_livedoorClip.LoadString( IDS_TGT_LIVEDOOR_CLIP );
        m_tgt_ecNaviClip.LoadString( IDS_TGT_ECNAVI_CLIP );
        m_tgt_niftyClip.LoadString( IDS_TGT_NIFTY_CLIP );
        m_tgt_1470net.LoadString( IDS_TGT_1470NET );
        m_tgt_pookmark.LoadString( IDS_TGT_POOKMARK );
        m_tgt_blueDot.LoadString( IDS_TGT_BLUEDOT );
        m_tgt_joltMark.LoadString( IDS_TGT_JOLTMARK );
        m_tgt_blogPet.LoadString( IDS_TGT_BLOGPET );
        m_tgt_fc2bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
        m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
        m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
        m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
        m_tgt_hatenaFeed.LoadString( IDS_TGT_HATENA_FEED );
        m_tgt_deliciousXML.LoadString( IDS_TGT_DELICIOUS_XML );
    }

    if ( !bookmarkNameAsImport.Compare( m_tgt_mmMemo ) )
        changeCode = EUC2UTF;
    else if ( !bookmarkNameAsImport.Compare( m_tgt_hatenaBookmark ) ||
              !bookmarkNameAsImport.Compare( m_tgt_delicious )      ||
              !bookmarkNameAsImport.Compare( m_tgt_blueDot )        ||
              !bookmarkNameAsImport.Compare( m_tgt_drecomRSS )      ||
              !bookmarkNameAsImport.Compare( m_tgt_flog )           ||
              !bookmarkNameAsImport.Compare( m_tgt_livedoorClip )   ||
              !bookmarkNameAsImport.Compare( m_tgt_ecNaviClip )     ||
              !bookmarkNameAsImport.Compare( m_tgt_niftyClip )      ||
              !bookmarkNameAsImport.Compare( m_tgt_1470net )        ||
              !bookmarkNameAsImport.Compare( m_tgt_pookmark )       ||
              !bookmarkNameAsImport.Compare( m_tgt_joltMark )       ||
              !bookmarkNameAsImport.Compare( m_tgt_blogPet )        ||
              !bookmarkNameAsImport.Compare( m_tgt_fc2bookmark )    ||
              !bookmarkNameAsImport.Compare( m_tgt_yjBookmark )     ||
              !bookmarkNameAsImport.Compare( m_tgt_yahooBookmarks ) ||
              !bookmarkNameAsImport.Compare( m_tgt_diigo )          ||
              !bookmarkNameAsImport.Compare( m_tgt_hatenaFeed )     ||
              !bookmarkNameAsImport.Compare( m_tgt_deliciousXML )      )
        changeCode = SJIS2UTF; /* bookey������Shift_jis�ϊ��ς݂̏ꍇ���܂� */

    return ( changeCode );
}


void CUserInfo::PutBookmarks(
            bool         force,
            const MyClip *myBookmark,
            int          numOfMyBookmarks,
            const char   *username /* = NULL */,
            const char   *password /* = NULL */
        )
{
    CUserInfo   u = *this;

    u = force;
    u.PutBookmarks( myBookmark, numOfMyBookmarks,
                     (const char *)username,
                     (const char *)password );
}

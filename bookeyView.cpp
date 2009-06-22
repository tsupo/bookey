/*
 * bookeyView.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CBookeyView �N���X�̓���̒�`
 *          written by H.Tsujimura  13 Oct 2005
 *
 * $Log: /comm/bookey/bookeyView.cpp $
 * 
 * 3     09/06/22 22:31 tsupo
 * 0.63c��
 * 
 * 123   09/06/22 17:56 Tsujimura543
 * ���{�ꃂ�[�h�����p�ꃂ�[�h�ؑ֊֘A�A�C��
 * 
 * 2     09/06/18 0:53 tsupo
 * 0.63b��
 * 
 * 122   09/06/16 22:02 Tsujimura543
 * �o�^���悤�Ƃ��Ă��� URL �̒����� MAX_URLLENGTH �ȏ�̂Ƃ�
 * �Ƀo�b�t�@�I�[�o�[�������N����s����C��
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 121   09/01/19 23:55 Tsujimura543
 * �c�[���o�[�̉E�N���b�N���j���[�Ɂu�u�b�N�}�[�N�Ǘ��c�[���N���v��
 * �u�ݒ�v��ǉ� (�ŏ�����Ԃ�����N���ł���悤�ɂ���)
 * 
 * 120   08/12/05 18:19 Tsujimura543
 * ���O�t�@�C���� 2GB���傫���Ƃ��ɂ��A���Ғʂ胍�O�ޔ�������
 * �����悤�ɏC��
 * 
 * 119   08/12/03 15:35 Tsujimura543
 * (bookey�N������)���O�t�@�C���� 64MB ���傫���Ȃ��Ă�����A
 * �t�@�C������ύX���A�ޔ�����悤�ɂ���
 * 
 * 118   08/10/22 18:20 Tsujimura543
 * OnButtonProxy() ���s�����u����v�{�^���� disable �ɂ���悤�ɂ���
 * 
 * 117   08/10/22 17:13 Tsujimura543
 * �w�u����v�{�^���� enable/disable �ɂ���x�������C���A����������
 * 
 * 116   07/12/05 23:17 Tsujimura543
 * unbase64() �̈����ǉ��ɔ����C�������{
 * 
 * 115   07/11/13 23:08 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 114   07/09/05 2:35 Tsujimura543
 * Debug�r���h�ł� setDump() ����悤�ɂ���
 * 
 * 113   07/09/05 0:52 Tsujimura543
 * OnInitialUpdate() �� Release�r���h���ɃR���p�C���G���[�ɂȂ��Ă��܂���
 * ���̂��C��
 * 
 * 112   07/09/05 0:29 Tsujimura543
 * m_verboseFp ����钼�O�ɁA�^�C���X�^���v�������悤�ɂ���
 * 
 * 111   07/09/04 23:31 Tsujimura543
 * m_verboseFp �����ꏊ�� CBookeyView �̃f�X�g���N�^�Ɉړ�
 * 
 * 110   07/07/09 18:38 Tsujimura543
 * ���{�ꃂ�[�h�Ɖp�ꃂ�[�h��؂�ւ���@�\��ǉ�
 * (�����_�ł́A���̋@�\�́A�f�o�b�O�r���h���̂ݗL���ƂȂ�)
 * 
 * 109   07/06/08 21:36 Tsujimura543
 * �uspecialSetting ���� setProxyInfo() ���Ă�ł��Ȃ��s��v���C��
 * 
 * 108   07/04/11 15:01 Tsujimura543
 * bookey �N������� proxy �ݒ�֘A�̏������������� fix
 * 
 * 107   07/04/10 23:13 Tsujimura543
 * �uproxy�ݒ�����x���J��Ԃ����₵�Ă��܂����ہv�ɑ΂���΍��ǉ�
 * 
 * 106   07/04/09 16:58 Tsujimura543
 * proxy�ݒ�����x���J��Ԃ����₵�Ă��܂����ۂɑΏ�
 * 
 * 105   07/03/28 20:29 Tsujimura543
 * �u�b�N�}�[�N�o�^�������́u�v���L�V�T�[�o�ݒ�v�{�^���� disable �ɂ���
 * �悤�ɂ���
 * 
 * 104   07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 103   07/03/26 23:16 Tsujimura543
 * ���[�J��OPML�o�^���Ƀ������j�󂪔�������\���̂���ӏ��𔭌��A
 * �C�������{
 * 
 * 102   07/03/20 0:17 Tsujimura543
 * �R�����g���C��
 * 
 * 101   07/03/20 0:17 Tsujimura543
 * SetProxyInfo() ���C���B��x�ݒ肪���܂���������ŁA�ݒ肪����������Ă�
 * �܂��\����r��
 * 
 * 100   07/03/16 23:03 Tsujimura543
 * SetProxyInfo() �̎d�l��ύX�B�����ۑ����[�h��p�ӂ���
 * 
 * 99    07/03/16 1:03 Tsujimura543
 * proxy�T�[�o�o�R�łȂ��ƃC���^�[�l�b�g�A�N�Z�X�ł��Ȃ��̂ɁAproxy�T�[�o
 * ���g��Ȃ��ݒ�ɂȂ��Ă���ꍇ�̑΍��ǉ�
 * 
 * 98    07/03/15 22:43 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 97    07/03/15 22:35 Tsujimura543
 * proxy�ݒ�m�F�_�C�A���O���\�����ꂽ�ꍇ�A�����ݒ�t�@�C��(bookey.inf)
 * ���烆�[�U���A�p�X���[�h���̏�񂪏����Ă��܂��s��ɑΏ�
 * [OnInitialUpdate() ��� OnShowWindow() �̕�����ɓ����o�����Ƃ����O����
 * ����]
 * 
 * 96    07/03/14 23:35 Tsujimura543
 * �s�v�ɂȂ����R�[�h���폜
 * 
 * 95    07/03/14 23:32 Tsujimura543
 * URL �L���[�C���O�@�\������
 * 
 * 94    07/03/14 20:10 Tsujimura543
 * (1) StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * (2) proxy�֘A�̂������̏C���A�ǉ� (BloGolEe �̐��ʂ���荞��)
 * (3) ��L�̏C���ɍ��킹�āA�ݒ�t�@�C���̓ǂݏ����������A�b�v�f�[�g
 * 
 * 93    07/01/23 22:29 Tsujimura543
 * �]���ȃR�����g(�����������ꂽ���́A�Ȃ�)���폜
 * 
 * 92    07/01/16 23:14 Tsujimura543
 * �p�ꃂ�[�h�Ή�
 * 
 * 91    07/01/04 18:54 Tsujimura543
 * ShowWindow() �̈������C��
 * 
 * 90    07/01/04 18:42 Tsujimura543
 * �e�u�b�N�}�[�N�T�[�r�X�ւ̓o�^�����I������u�u�b�N�}�[�N�o�^���v
 * �_�C�A���O���������Ɏc�邱�Ƃ����錻�ۂɑΏ�����
 * 
 * 89    06/08/23 22:10 Tsujimura543
 * 1470.net���j���[�A���ł́u�폜�v���Ƀ��[�U����ݒ肵���ꍇ�A
 * ���̐ݒ���e�������ݒ�t�@�C���ɔ��f�ł���悤�ɂ���
 * 
 * 88    06/07/28 22:59 Tsujimura543
 * �^�u�؂�ւ����́u�ݒ�_�C�A���O�v���쐬�E��������
 * 
 * 87    06/07/18 21:35 Tsujimura543
 * �f�X�g���N�^�� encodeURL2() ���������̈���������ǉ�
 * 
 * 86    06/07/11 18:21 Tsujimura543
 * �R�����g�̏C���A����
 * 
 * 85    06/07/11 18:14 Tsujimura543
 * SetFocus() ���݂̏C�������{ (�u���s���v�_�C�A���O�� focus ���������悤
 * �ɒ�������)
 * 
 * 84    06/07/05 18:19 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��13�i�K�A�I��
 * 
 * 83    06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 82    06/07/05 13:09 Tsujimura543
 * �����ݒ�t�@�C������ǂݎ�������e����́A�i�[�A�ƍ����鏈���A
 * �����ݒ�t�@�C���֏����o�������� parameter.{h,cpp} �Ƃ��ĕ�����
 * ��������
 * 
 * 81    06/07/05 11:23 Tsujimura543
 * �u�u�b�N�}�[�N�o�^�X���b�h�v�֘A������ bookeyView.cpp ���番���Ɨ������A
 * registerBookmark.cpp ���쐬����
 * 
 * 80    06/07/04 23:48 Tsujimura543
 * CheckEncodedPassword() �����t�@�N�^�����O
 * 
 * 79    06/07/04 22:36 Tsujimura543
 * LoadSetting() ������Ƀ��t�@�N�^�����O
 * 
 * 78    06/07/04 21:46 Tsujimura543
 * LoadSetting(), SaveSetting(), CheckEncodedPassword() �����t�@�N�^�����O
 * 
 * 77    06/07/04 10:51 Tsujimura543
 * ���Ԃ̂����鏈���̎��s���́u����v�{�^���� disable �ɂ��悤�Ǝ��݂�
 * (���A���܂������Ȃ�)
 * 
 * 76    06/07/04 10:34 Tsujimura543
 * �����v�J�[�\���֘A�A�C��
 * 
 * 75    06/07/03 23:37 Tsujimura543
 * ProceedingDialog �� DestroyWindow() ���ɗ�O���������邱�Ƃ����錏��
 * �b��Ώ������{ (�f�o�b�O�łł����������Ȃ�?)
 * 
 * 74    06/07/03 14:36 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 73    06/07/03 14:23 Tsujimura543
 * (1) ProceedingDialog ���݂̉��C (ProceedingDialog �����ɉB��Ă��܂�
 *     ���Ƃ����錏�̑΍���{�AProceedingDialog �� delete���ɗ�O��������
 *     �邱�Ƃ����錏�̑΍���{)
 * (2) http://cgi.itmedia.co.jp/rss/ �̃��_�C���N�^�ɑΉ�
 * 
 * 72    06/06/29 21:27 Tsujimura543
 * �j�t�e�B�N���b�v�̃p�X���[�h�ǂݍ��ݏ����Ƀo�O���������̂��C��
 * 
 * 71    06/06/29 18:47 Tsujimura543
 * �uEC�i�r�l�C�j���[�X�v�Ɓu�j�t�e�B�N���b�v�v�̓o�^�Ɋe�X�Ή�����
 * 
 * 70    06/06/29 0:44 Tsujimura543
 * livedoor�N���b�v(�̓o�^)�ɑΉ�
 * 
 * 69    06/06/28 15:54 Tsujimura543
 * �u�b�N�}�[�N�o�^�Ґ��𒲂ׂĕ\������@�\��ǉ�
 * 
 * 68    06/06/22 21:21 Tsujimura543
 * inquery �� inquiry �ɏC��(�Ԃ�~�X)
 * 
 * 67    06/06/22 21:20 Tsujimura543
 * SetBookeyInfo() ���C��(�L�����Z���{�^���������� userInfo.Init(false);
 * ����K�v�͂Ȃ�)
 * 
 * 66    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() �����s���Ă��A�ݒ肪�ύX�ł��Ȃ��Ȃ���
 * ���܂��Ă���(�G���o�O)�̂��C���B�ύX�ł���悤�ɂ���
 * 
 * 65    06/06/22 14:53 Tsujimura543
 * Web�y�[�W���擾������ʃX���b�h������
 * 
 * 64    06/06/15 16:41 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��8�i�K�A�I��
 * 
 * 63    06/06/15 12:55 Tsujimura543
 * �u�Ǘ��c�[���N���v��u�ݒ�v���ɂ� EnableButton() ����悤�ɂ���
 * 
 * 62    06/06/14 12:06 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��6�i�K�A�I��
 * 
 * 61    06/06/14 11:44 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��5�i�K�A�I��
 * 
 * 60    06/06/13 22:11 Tsujimura543
 * RegisterBookmark() �����t�@�N�^�����O
 * 
 * 59    06/06/13 21:40 Tsujimura543
 * �^�C�g���擾���A�^�O��⒊�o���̐i�s�󋵃_�C�A���O��\������悤�ɂ���
 * 
 * 58    06/06/13 21:11 Tsujimura543
 * �u�b�N�}�[�N�o�^���ł���ʍĕ`��ł���悤�ɂ��Ă݂�
 * 
 * 57    06/06/07 20:25 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��4�i�K�A�I��
 * 
 * 56    06/06/07 15:33 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��3�i�K�A�I��
 * 
 * 55    06/06/06 22:23 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��2�i�K�A�I��
 * 
 * 54    06/06/06 15:18 Tsujimura543
 * CUserInfo �� CBookeyApp ���Ɉڂ���
 * 
 * 53    06/06/05 22:12 Tsujimura543
 * �X���b�h�Ԃŋ��������̂���̈�ւ̃A�N�Z�X�Ɋւ��āA�O�̂��߂�
 * critical section �𓱓����Ă݂�(���A���ɍ��܂łƕς���Ă��Ȃ�)
 * 
 * 52    06/06/01 23:10 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��1�i�K�A�I��
 * 
 * 51    06/06/01 20:28 Tsujimura543
 * CBookeyDlg ���̃��[�U���A�p�X���[�h�� CUserInfo ���g���ĊǗ�����
 * �悤�ɕύX����
 * 
 * 50    06/06/01 19:14 Tsujimura543
 * CUserInfo �� bookeyView.h ���� UserInfo.h �Ɉڂ����̂ɔ����C�������{
 * 
 * 49    06/06/01 19:04 Tsujimura543
 * �u�b�N�}�[�N��ʂ����� enum �l���Aenum CUserInfo::bookmarkType ��
 * ��{������
 * 
 * 48    06/06/01 18:49 Tsujimura543
 * enum bookmarkType �̒�`�� CBookeyView ���� CUserInfo �Ɉڂ���
 * 
 * 47    06/06/01 18:28 Tsujimura543
 * RegisterBookmark() ���ł������� RBparam_t �ȗ̈���R�s�[���Ă���
 * �g���悤�ɕύX
 * 
 * 46    06/06/01 17:19 Tsujimura543
 * CUserInfo �N���X�𓱓�
 * 
 * 45    06/06/01 15:13 Tsujimura543
 * struct RBparam �� RBuser_t ���g���Ē�`��������
 * 
 * 44    06/05/31 21:48 Tsujimura543
 * Flog �́u�o�^�v�ɑΉ�����
 * 
 * 43    06/05/29 17:15 Tsujimura543
 * http://markezine.jp/ �̃��_�C���N�^�ɑΉ�
 * 
 * 42    06/05/29 17:03 Tsujimura543
 * http://codezine.jp/ �̃��_�C���N�^(�Ƃ������A�ŏI�I�Ɉړ�������URL��
 * �����I�ɔ�΂�)�ɑΉ�
 * 
 * 41    06/05/26 15:33 Tsujimura543
 * ?fr=rdf ���폜�Ώۂɒǉ� (ThinkIT)
 * 
 * 40    06/05/25 20:16 Tsujimura543
 * ?topic=1 ���폜�Ώۂɒǉ� (japan.linux.com)
 * 
 * 39    06/05/25 19:20 Tsujimura543
 * http://www.pheedo.jp/ �� http://www.neowing.co.jp/ �̃��_�C���N�^�ɑΉ�
 * 
 * 38    06/05/25 17:12 Tsujimura543
 * &from=rss ���폜�Ώۂɒǉ� (�X���b�V���h�b�g �W���p��)
 * 
 * 37    06/05/25 17:08 Tsujimura543
 * ?from=top ���폜�Ώۂɒǉ� (�ǔ��V��)
 * 
 * 36    06/05/25 16:55 Tsujimura543
 * feedburner.jp �� google.com �̃��_�C���N�^�ɑΉ�����
 * 
 * 35    06/05/23 14:04 Tsujimura543
 * getTitle() �� extractTags() �̘A�g�ɂ��u�͂Ăȃu�b�N�}�[�N�v�����
 * �^�O���擾���T�|�[�g
 * 
 * 34    06/05/11 16:43 Tsujimura543
 * ?in=rssw (MSN�����V��) ���폜�Ώۂɒǉ�
 * 
 * 33    06/04/06 22:16 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�́u�R���N�V�����v�ւ̒ǉ��ɑΉ�
 * 
 * 32    06/04/04 12:08 Tsujimura543
 * ?fr=RSS ���폜�Ώۂɒǉ�
 * 
 * 31    06/03/29 21:42 Tsujimura543
 * �u�b�N�}�[�N�o�^���� ProceedingDialog �̕\���� on/off ��؂�ւ����
 * ��}��
 * 
 * 30    06/03/29 18:30 Tsujimura543
 * �h���R��RSS�ւ̃u�b�N�}�[�N(Clip)�o�^�ɑΉ�����
 * 
 * 29    06/03/27 17:21 Tsujimura543
 * RegisterBookmarkDialog ���g���Ă������Ղ��폜
 * 
 * 28    06/03/27 17:13 Tsujimura543
 * RegisterBookmarkDialog �̑���� ProceedingDialog ���g���悤�ɂ���
 * 
 * 27    06/03/13 20:56 Tsujimura543
 * �^�O���̕\���� ON/OFF �ł���悤�ɂ���
 * 
 * 26    06/03/13 16:51 Tsujimura543
 * FeedBurner �������� Yahoo! Japan �̃��_�C���N�^���o�R����Web�y�[�W��
 * ���_�C���N�g��� URL ���u�b�N�}�[�N�Ώۂ� URL �Ƃ݂Ȃ��悤�ɂ��� 
 * 
 * 25    06/03/10 19:11 Tsujimura543
 * �f�R�[�h���s���̃��J�o���������������[�v�ɂȂ�̂�\�h���鏈����
 * �ǉ� (�������[�v�ɂȂ邱�Ƃ͂Ȃ��͂������A�O�̂���)
 * 
 * 24    06/03/09 16:19 Tsujimura543
 * SaveSetting() ���C��
 * 
 * 23    06/03/09 15:55 Tsujimura543
 * CheckEncodedPassword() ��ǉ��A�p�X���[�h�f�R�[�h���s���̑΍������
 * 
 * 22    06/02/06 17:11 Tsujimura543
 * �p�X���[�h�̒��g���j�󂳂�Ă���ꍇ�ɍĐݒ�𑣂�������ǉ�
 * 
 * 21    05/11/30 23:43 Tsujimura543
 * extractTags() �̑�3������ (I) ���� (I/O) �֕ύX
 * 
 * 20    05/11/30 23:28 Tsujimura543
 * �^�O��⒊�o������ǉ�
 * 
 * 19    05/11/02 18:47 Tsujimura543
 * ref=atom �Ȃǂ��폜�Ώۂɒǉ�
 * 
 * 18    05/11/02 12:04 Tsujimura543
 * ?from=RSS �Ƃ����p�^�[���ɂ��Ή�
 * 
 * 17    05/11/01 19:31 Tsujimura543
 * �x�����x��4�ŃR���p�C�����Ă��x�����o�Ȃ��悤�ɏC��
 * 
 * 16    05/11/01 18:37 Tsujimura543
 * �o�^�Ώۂ� URL �̖����� ?{ref|from}=rss ���t���Ă���ꍇ�͍폜����悤
 * �ɂ���
 * 
 * 15    05/11/01 16:50 Tsujimura543
 * (1) �����������t�@�N�^�����O
 * (2) MM/Memo �̍폜�֘A�������쐬
 * 
 * 14    05/10/29 1:11 Tsujimura543
 * �ݒ�t�@�C���ۑ��������C�� (���p����u�b�N�}�[�N�T�[�r�X�����炷�悤��
 * �ݒ�ύX���ɕۑ����e�����������Ȃ�s���������)
 * 
 * 13    05/10/28 21:14 Tsujimura543
 * �̈��������ǉ�
 * 
 * 12    05/10/24 20:36 Tsujimura543
 * (1) �͂Ăȓ����K�Ή�
 * (2) �u�b�N�}�[�N�o�^���_�C�A���O��V��
 * (3) �e��o�O�C��
 * 
 * 11    05/10/24 14:46 Tsujimura543
 * (1) �R���e�L�X�g���j���[������ǉ�
 * (2) �����u�b�N�}�[�N�o�^�_�C�A���O�Œ��~�������Ƃ����̂����񂩌J��Ԃ�
 *     �ƁA���̂��������錻�ۂ̌���������(�N���b�v�{�[�h����̃R�s�[����
 *     �����������肾����)�B�C�� + ����m�F�ς݁B
 * 
 * 10    05/10/24 11:10 Tsujimura543
 * �ݒ肵���͂��� BlogPeople �̃p�X���[�h������N�����ɏ����Ă��܂�
 * �s��ɑΏ�
 * 
 * 9     05/10/21 19:56 Tsujimura543
 * MM/Memo �� BlogPeople �̓����u�b�N�}�[�N�o�^�ɂ��Ή�
 * 
 * 8     05/10/21 18:03 Tsujimura543
 * �N���b�v�{�[�h�o�R�ł́u�u�b�N�}�[�N�Ώ�URL�v�̎擾�ɑΉ�
 * 
 * 7     05/10/21 16:36 Tsujimura543
 * �t�@�C���̃h���b�O�A���h�h���b�v�ɂ��Ή�
 * 
 * 6     05/10/20 21:22 Tsujimura543
 * ~CBookeyView() �ɗ̈���������ǉ�
 * 
 * 5     05/10/15 1:02 Tsujimura543
 * ���[�U���ƃp�X���[�h�� bookDlg �ɓn����悤�ɂ���
 * 
 * 4     05/10/15 0:07 Tsujimura543
 * ���[�U���ƃp�X���[�h��ݒ�t�@�C���ɕۑ�����悤�ɂ���
 * 
 * 3     05/10/14 20:38 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�Ή���Ɗ���
 * 
 * 2     05/10/14 15:04 Tsujimura543
 * �h���b�O�E�A���h�E�h���b�v�@�\(���m�ɂ̓h���b�v�̂�)�Ή�����
 * 
 * 1     05/10/14 14:37 Tsujimura543
 * �V�K�쐬 (�h���b�O�E�A���h�E�h���b�v�@�\�T�|�[�g�p)
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "bookeyDoc.h"
#include "bookeyView.h"
#include "SettingDialog.h"
#include "confirmProxy.h"

#include "parameter.h"
#include <process.h>
#include <sys/stat.h>
#ifdef _INTEGRAL_MAX_BITS
#if _INTEGRAL_MAX_BITS >= 64
#define USE_STAT_64
#endif
#endif  /* _INTEGRAL_MAX_BITS */

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/bookeyView.cpp 3     09/06/22 22:31 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookeyView

IMPLEMENT_DYNCREATE(CBookeyView, CFormView)

BEGIN_MESSAGE_MAP(CBookeyView, CFormView)
	//{{AFX_MSG_MAP(CBookeyView)
	ON_BN_CLICKED(IDC_BUTTON_TOOL, OnButtonTool)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, OnButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_FINISH, OnButtonFinish)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_CHECK_TAG_SUGGESTION, OnCheckTagSuggestion)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_USERS, OnCheckUsers)
	ON_BN_CLICKED(IDC_BUTTON_PROXY, OnButtonProxy)
	ON_BN_CLICKED(IDC_CHECK_LANGUAGE, OnCheckLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookeyView �N���X�̍\�z/����

CBookeyView::CBookeyView()
	: CFormView(CBookeyView::IDD)
{
	//{{AFX_DATA_INIT(CBookeyView)
	m_useTagSuggestion = FALSE;
	m_useUsers = FALSE;
	//}}AFX_DATA_INIT

    m_registerBookmarkThread = NULL;
    m_param.active           = FALSE;
    m_procCreated            = false;

    char *p = __argv[0];
    strcpy( m_path, p );
    p = m_path;
    char *q = strrchr( p, '/' );
    if ( !q )
        q = strrchr( p, '\\' );
    if ( q && (q - 1 > p) && (*(q - 1) != ':') )
        *q = NUL;

    m_numOfWaiting = 0;
    m_waitingHead  = -1;
    m_waitingTail  = -1;

    InitializeCriticalSection( &m_cs_bookey );
}

CBookeyView::~CBookeyView()
{
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();

    if ( checkProxyInfo() ) {
        // proxy�֘A�̐ݒ�Ɍ�肪����Ǝv����ꍇ�A����N�����ɍĐݒ�\��
        // ���邽�߁A���܂̐ݒ����������j������
        bp->m_proxyType = CBookeyApp::autoDetect;
        SaveSetting();
    }

    // �̈���
    DeleteCriticalSection( &m_cs_bookey );
    encodeURL( NULL );
    encodeURL2( NULL );
    encodeURLex( NULL );
    base64( NULL, 0 );

    if ( m_procCreated )
        m_procDialog.DestroyWindow();

    if ( bp->m_verboseFp ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );
        fprintf( bp->m_verboseFp,
                 "\n*** logging end:   %d/%02d/%02d %02d:%02d:%02d ***\n",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
        fclose( bp->m_verboseFp );
        bp->m_verboseFp = NULL;
    }
}

void CBookeyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookeyView)
	DDX_Check(pDX, IDC_CHECK_TAG_SUGGESTION, m_useTagSuggestion);
	DDX_Check(pDX, IDC_CHECK_USERS, m_useUsers);
	//}}AFX_DATA_MAP
}

BOOL CBookeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CBookeyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

    LoadSetting();
    SetProxyInfo();

    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_TAG_SUGGESTION );
    p->SetCheck( m_useTagSuggestion ? 1 : 0 );

    p = (CButton *)GetDlgItem( IDC_CHECK_USERS );
    p->SetCheck( m_useUsers ? 1 : 0 );

    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
#ifdef  _DEBUG
    LCID        l   = getLanguageCode();

    p = (CButton *)GetDlgItem( IDC_CHECK_LANGUAGE );
    p->SetCheck( l != bp->m_langCode ? 1 : 0 );
    setLanguageCode( bp->m_langCode );
    bp->ReInitialize();
#endif

    CStatic *sp = (CStatic *)GetDlgItem( IDC_WAITING );
    sp->ShowWindow( SW_HIDE );

    if ( bp->m_verbose ) {
        char            filename[MAX_PATH];
#ifdef  USE_STAT_64
        struct _stati64 s;
#else
        struct stat     s;
#endif  /* USE_STAT_64 */

        sprintf( filename, "%s/" BOOKEY_LOG_FILE, m_path );
#ifdef  USE_STAT_64
        if ( !_stati64( filename, &s ) ) {
            if ( s.st_size > (__int64)(1024 * 1024 * 64) ) {
#else   /* !USE_STAT_64 */
        if ( !stat( filename, &s ) ) {
            if ( (unsigned long)s.st_size > 1024 * 1024 * 64 ) {
#endif  /* !USE_STAT_64 */
                char        backup[MAX_PATH];
                time_t      t = time( NULL );
                struct tm   *tm = localtime( &t );

                sprintf( backup,
                         "%s/" BOOKEY_LOG_FILE ".%04d%02d%02d%02d%02d%02d",
                         m_path,
                         tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                         tm->tm_hour, tm->tm_min, tm->tm_sec );
                rename( filename, backup );
            }
        }

        bp->m_verboseFp = fopen( filename, "a" );
        if ( bp->m_verboseFp ) {
            time_t      t   = time( NULL );
            struct tm   *tm = localtime( &t );
            fprintf( bp->m_verboseFp,
                   "\n\n*** logging start: %d/%02d/%02d %02d:%02d:%02d ***\n",
                     tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                     tm->tm_hour, tm->tm_min, tm->tm_sec );
#ifdef  _DEBUG
            setDump( TRUE, bp->m_verboseFp );
#endif
        }
        setVerbose( bp->m_verbose, bp->m_verboseFp );
    }
}

void CBookeyView::SetProxyInfo( bool saveForcely /* = false */ )
{
    CBookeyApp              *bp = (CBookeyApp *)AfxGetApp();
    CBookeyApp::proxyType   saveProxyType = bp->m_proxyType;

    if ( bp->m_proxyType == CBookeyApp::autoDetect ) {
#if 0
        setConfirmProxyInfoFunc( confirmProxyInfo );
#else
        setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
#endif
        bp->m_useProxy = isUsedProxy() == TRUE ? true : false;
    }
    if ( (bp->m_proxyType == CBookeyApp::manualSetting)  ||
         (bp->m_proxyType == CBookeyApp::specialSetting)    ) {
        if ( bp->m_useProxy ) {
            setProxyInfo( bp->m_proxyServer,
                          (unsigned short)(bp->m_proxyPort),
                          bp->m_proxyUsername,
                          bp->m_proxyPassword );
        }
    }
    setUseProxy( bp->m_useProxy );

    if ( saveForcely || (saveProxyType != bp->m_proxyType) )
        SaveSetting();
    if ( saveForcely )
        setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
}

/////////////////////////////////////////////////////////////////////////////
// CBokeyView �N���X�̐f�f

#ifdef _DEBUG
void CBookeyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBookeyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CBookeyDoc* CBookeyView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBookeyDoc)));
	return (CBookeyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBookeyView �N���X �o�^�҂�URL�L���[�֘A����

long    CBookeyView::putWaiting( const char *url )
{
    long    ret = -1;
    long    num = -1;
    char    tmp[BUFSIZ];

    if ( !url || !(*url) )
        return ( ret );

    EnterCriticalSection( &m_cs_bookey );
    num = m_numOfWaiting;
    LeaveCriticalSection( &m_cs_bookey );

    if ( num >= MAX_WAITING_NUM ) {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_BUSY_GETTING);
        text.LoadString( IDS_TXT_BUSY_GETTING);
        MessageBox( text,   // �܂��O�̃u�b�N�}�[�N�o�^��ƒ��ł��B
                            // ���Ƃł�蒼���Ă��������B
                    title,  // �o�^��ƒ�
                    MB_OK|MB_ICONWARNING );
        return ( ret );
    }

    EnterCriticalSection( &m_cs_bookey );

    if ( m_waitingHead == m_waitingTail )
        m_waitingHead = m_waitingTail = 0;

    m_waitingURLs[m_waitingHead] = url;
    m_waitingHead = (m_waitingHead + 1) % MAX_WAITING_NUM;

    ret = ++m_numOfWaiting;

    LeaveCriticalSection( &m_cs_bookey );

    LCID    l = getLanguageCode();
    sprintf( tmp,
             l == 0x0411 ?
               "�o�^�҂�: %d��"  :
             ret == 1 ?
               "Waiting: %d URL" :
               "Waiting: %d URLs",
             ret );
    CStatic *sp = (CStatic *)GetDlgItem( IDC_WAITING );
    sp->SetWindowText( tmp );
    sp->ShowWindow( SW_SHOW );

    return ( ret );
}

CString CBookeyView::getWaiting()
{
    CString s = "";
    char    tmp[BUFSIZ];
    long    num = -1;

    EnterCriticalSection( &m_cs_bookey );
    num = m_numOfWaiting;
    LeaveCriticalSection( &m_cs_bookey );

    if ( num == 0 )
        return ( s );

    EnterCriticalSection( &m_cs_bookey );

    s = m_waitingURLs[m_waitingTail];
    m_waitingTail = (m_waitingTail + 1) % MAX_WAITING_NUM;
    if ( m_waitingHead == m_waitingTail )
        m_waitingHead = m_waitingTail = 0;

    num = --m_numOfWaiting;

    LeaveCriticalSection( &m_cs_bookey );

    LCID    l   = getLanguageCode();
    CStatic *sp = (CStatic *)GetDlgItem( IDC_WAITING );
    if ( num > 0 ) {
        sprintf( tmp,
                 l == 0x0411 ?
                   "�o�^�҂�: %d��"  :
                 num == 1 ?
                   "Waiting: %d URL" :
                   "Waiting: %d URLs",
                 num );
        sp->SetWindowText( tmp );
        sp->ShowWindow( SW_SHOW );
    }
    else
        sp->ShowWindow( SW_HIDE );

    return ( s );
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyView �N���X�̒ǉ�����

// �ݒ���ǂݍ���
void    CBookeyView::LoadSetting()
{
    char            filename[MAX_PATH];
    FILE            *fp;
    char            key[BUFSIZ];
    char            buf[BUFSIZ];
    char            tmp[BUFSIZ];
    unsigned char   rsaString[BUFSIZ];
    char            *p;
    size_t          l   = 0;
    CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

    key[0]       = NUL;
    rsaString[0] = NUL;

    sprintf( filename, "%s/" BOOKEY_INF_FILE, m_path );
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p                      &&
                    ((l = strlen( p )) > 0) &&
                    (p[l - 1] == '\n')         )
                p[l - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( evalKey( p, "useTagSuggestion", m_useTagSuggestion ) )
                continue;
            if ( evalKey( p, "useUsers", m_useUsers ) )
                continue;
#ifdef  _DEBUG
            if ( evalKey( p, "langCode", pp->m_langCode ) )
                continue;
#endif
            if ( evalKey( p, "verbose", pp->m_verbose ) )
                continue;

            if ( evalKey( p, "proxyType", tmp ) ) {
                if ( !strcmp( tmp, "notUsed" ) ) {
                    pp->m_proxyType = CBookeyApp::notUsed;
                    pp->m_useProxy  = false;
                }
                else if ( !strcmp( tmp, "specialSetting" ) )
                    pp->m_proxyType = CBookeyApp::specialSetting;
                else if ( !strcmp( tmp, "manualSetting" ) )
                    pp->m_proxyType = CBookeyApp::manualSetting;
                else
                    pp->m_proxyType = CBookeyApp::autoDetect;
                continue;
            }

            if ( (pp->m_proxyType == CBookeyApp::specialSetting) ||
                 (pp->m_proxyType == CBookeyApp::manualSetting)     ) {
                if ( evalKey( p, "useProxy", pp->m_useProxy ) )
                    continue;
                if ( evalKey( p, "proxyServer", pp->m_proxyServer ) )
                    continue;
                if ( evalKey( p, "proxyPort", pp->m_proxyPort ) )
                    continue;
                if ( evalKey( p, "proxyUsername", pp->m_proxyUsername ) )
                    continue;
                if ( evalKey( p, "proxyPassword", pp->m_proxyPassword ) )
                    continue;
            }

            if ( key[0] == NUL ) {
                if ( evalKey( p, "encryptedKey", key ) ) {
                    size_t  sz = 0;

                    unbase64( (unsigned char *)key,
                              (unsigned char *)rsaString,
                              &sz );
                    rewind( fp );
                }
                continue;
            }

            if ( pp->EvalKeys( p, rsaString ) )
                continue;
        }
        fclose( fp );
    }

    /* �K�v������΁A�p�X���[�h�̍Đݒ���s�Ȃ� */
    bool    needToSave = false;

    pp->ResetUserInfo( needToSave );
    if ( needToSave )
        SaveSetting();
}

// �ݒ��񏑂��o��
void    CBookeyView::SaveSetting()
{
    char            filename[MAX_PATH];
    FILE            *fp;
    char            key[BUFSIZ];
    unsigned char   *rsaString;
    bool            encrypted;
    bool            done = false;
    int             retryCount = 0;
    CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

    do {
        key[0]    = NUL;
        rsaString = NULL;
        encrypted = false;

        sprintf( filename, "%s/" BOOKEY_INF_FILE, m_path );
        if ( ( fp = fopen( filename, "w" ) ) != NULL ) {
            fputs( "[bookmark target]\n", fp );
            pp->WriteKeys( fp,  key, &rsaString, encrypted );
            if ( encrypted && key[0] ) {
                writeKey( fp, "encryptedKey", key );
                freeRSAkey( rsaString );
            }

            fputs( "[bookey options]\n", fp );
            writeKey( fp, "useTagSuggestion", m_useTagSuggestion );
            writeKey( fp, "useUsers", m_useUsers );
#ifdef  _DEBUG
            writeKey( fp, "langCode", pp->m_langCode );
#endif
            if ( pp->m_verbose )
                writeKey( fp, "verbose", pp->m_verbose );

            fputs( "[proxy setting]\n", fp );
            if ( (pp->m_proxyType == CBookeyApp::specialSetting) ||
                 (pp->m_proxyType == CBookeyApp::manualSetting)     ) {
                writeKey( fp, "proxyType",
                          pp->m_proxyType == CBookeyApp::specialSetting
                            ? "specialSetting"
                            : "manualSetting" );
                writeKey( fp, "useProxy", pp->m_useProxy );
                if ( pp->m_useProxy ) {
                    writeKey( fp, "proxyServer", pp->m_proxyServer );
                    writeKey( fp, "proxyPort", pp->m_proxyPort );

                    if ( pp->m_proxyUsername.GetLength() > 0 ) {
                        writeKey( fp, "proxyUsername", pp->m_proxyUsername );
                        if ( pp->m_proxyPassword.GetLength() > 0 )
                            writeKey( fp, "proxyPassword",
                                      pp->m_proxyPassword );
                    }
                }
            }
            else if ( pp->m_proxyType == CBookeyApp::notUsed )
                writeKey( fp, "proxyType", "notUsed" );
            else
                writeKey( fp, "proxyType", "autoDetect" );

            fclose( fp );
        }

        /* �p�X���[�h�� decode �ł��邱�Ƃ��m�F */
        if ( encrypted && key[0] )
            done = CheckEncodedPassword();
        else
            done = true;

        if ( done == false ) {
            retryCount++;
            if ( retryCount >= 27 )
                break;
        }
    } while ( done == false );
}

// �u�b�N�}�[�N�̓o�^
void    CBookeyView::putBookmark( const char *url )
{
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    bool        needToSave = false;

    // �u�b�N�}�[�N�o�^�X���b�h�𐶐�
    EnterCriticalSection( &m_cs_bookey );
    strcpy( m_param.url, url );
    m_param.procDialog = &m_procDialog;

    /*
     * �p�X���[�h���ݒ�A�������̓p�X���[�h�����Ă���ꍇ�́A
     * �p�X���[�h��(��)�ݒ肷��
     */
    pp->ResetUserInfo( needToSave, m_param );

    m_param.useTagSuggestion = m_useTagSuggestion;
    m_param.useUsers         = m_useUsers;
    LeaveCriticalSection( &m_cs_bookey );

    if ( needToSave )
        SaveSetting();

    EnterCriticalSection( &m_cs_bookey );
    m_param.active = TRUE;

    if ( m_procCreated == false ) {
        m_procDialog.Create( IDD_PROCEEDING_DIALOG );
        m_procCreated = true;
    }
    else
        m_procDialog.ResetDialogText();
    m_procDialog.ShowWindow( SW_HIDE );

    m_registerBookmarkThread = AfxBeginThread( RegisterBookmark,
                                               (void *)&m_param );
    if ( m_registerBookmarkThread ) {
        m_registerBookmarkThread->m_bAutoDelete = FALSE;
        SetTimer( ID_THREAD_REGISTERBOOKMARK,
                  MS_THREAD_REGISTERBOOKMARK,
                  NULL );
        EnableButton( false );
    }
    LeaveCriticalSection( &m_cs_bookey );
    // ����: �Ȃ��킴�킴�ʃX���b�h�𗧂Ăď������邩�Ƃ����ƁA
    //       ���� OnDrop() �𔲂���܂Ńh���b�O���̃v���Z�X(Web
    //       �u���E�U)�����b�N���ꂽ�܂܂ƂȂ邽�߁BOnDrop() ��
    //       �͓Ɨ������X���b�h��p�ӂ��邱�ƂŁA�o�^��Ǝ��s�O
    //       �� OnDrop() ��E�o���A�u�b�N�}�[�N�o�^�_�C�A���O��
    //       �u���E�U�̊Ԃ��s�����藈����ł���悤�ɂȂ�B
    //       (�u���E�U���當������R�s�[&�y�[�X�g������A�o�^��
    //        �� Web ���ēx�ǂݒ������肵�����ł����?)
}

void    CBookeyView::PutBookmark( const char *url )
{
    bool        continous = true;
    char        targetURL[MAX_URLLENGTH + 1];
    CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
    CString     title;
    CString     text;

    if ( !strncmp( url, "ttp:",  4 ) ||
         !strncmp( url, "ttps:", 5 )    )
        sprintf( targetURL, "h%s", url );
    else
        strcpy( targetURL, url );

    if ( (strncmp( targetURL, "http://",  7 ) != 0) &&
         (strncmp( targetURL, "https://", 8 ) != 0)    ) {
        title.LoadString(IDS_TTL_URL_CHECK_RESULT);
        text.LoadString( IDS_TXT_INVALID_URL);
        text += url;
        MessageBox( text, title, MB_OK|MB_ICONWARNING );
        continous = false;
    }
    else if ( pp->IsReady() == false ) {
        OnButtonSetting();
        if ( pp->IsReady() == false ) {
            title.LoadString(IDS_TTL_UNSETTING);
            text.LoadString( IDS_TXT_UNSETTING);
            MessageBox( text, title, MB_OK|MB_ICONWARNING );
            continous = false;
        }
    }

    if ( continous ) {
        BOOL    b;

        EnterCriticalSection( &m_cs_bookey );
        b = m_param.active;
        LeaveCriticalSection( &m_cs_bookey );

        if ( b )
            putWaiting( targetURL );
        else
            putBookmark( targetURL );
    }
}

// �{�^���̗L��/�����؂�ւ�
void    CBookeyView::EnableButton( bool enable )
{
    CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_FINISH );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_TOOL );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_SETTING );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_CHECK_TAG_SUGGESTION );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_CHECK_USERS );
    p->EnableWindow( enable ? TRUE : FALSE );

    p = (CButton *)GetDlgItem( IDC_BUTTON_PROXY );
    p->EnableWindow( enable ? TRUE : FALSE );

    // �u����v�{�^���� enable/disable �ɂ���
    CWnd    *wnd = AfxGetApp()->m_pMainWnd;
    if ( wnd ) {
        CMenu   *c = wnd->GetSystemMenu( FALSE );
        if ( c )
            c->EnableMenuItem(SC_CLOSE,
                              MF_BYCOMMAND | enable ? MF_ENABLED : MF_GRAYED);
    }
}

/* �G���R�[�h�ς݃p�X���[�h���{���Ƀf�R�[�h�ł���̂��ǂ������O�� */
/* �m�F���Ă��� (decodeByRSA() ���f�R�[�h�Ɏ��s���邱�Ƃ����邱�� */
/* �������A���̃��\�b�h��p�ӂ��邱�Ƃ�[�b��I��]�΍�Ƃ���)      */
bool
CBookeyView::CheckEncodedPassword()
{
    bool            ret = true;
    char            filename[MAX_PATH];
    FILE            *fp;
    char            key[BUFSIZ];
    char            buf[BUFSIZ];
    char            *p;
    unsigned char   rsaString[BUFSIZ];
    size_t          l   = 0;
    CBookeyApp      *pp = (CBookeyApp *)AfxGetApp();

    key[0]       = NUL;
    rsaString[0] = NUL;
    sprintf( filename, "%s/" BOOKEY_INF_FILE, m_path );
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            while ( (*p == ' ') || (*p == '\t') )
                p++;
            while ( *p                      &&
                    ((l = strlen( p )) > 0) &&
                    (p[l - 1] == '\n')         )
                p[l - 1] = NUL;
            if ( !(*p) )
                continue;

            if ( key[0] == NUL ) {
                if ( evalKey( p, "encryptedKey", key ) ) {
                    size_t  sz = 0;

                    unbase64( (unsigned char *)key,
                              (unsigned char *)rsaString,
                              &sz );
                    rewind( fp );
                }
                continue;
            }

            pp->CheckKeys( p, rsaString, ret );
        }
        fclose( fp );
    }

    return ( ret ); /* true: �f�R�[�h����, false: �f�R�[�h���s */
}

void
CBookeyView::ManagementBookmark()
{
    EnableButton( false );

    CBookeyDlg  dlg;
    dlg.m_needToSave = false;
    dlg.DoModal();
    if ( dlg.m_needToSave )
        SaveSetting();

    EnableButton( true );
}

void
CBookeyView::EditSetting()
{
    EnableButton( false );

    SettingDialog   dlg;
    dlg.DoModal();

    SaveSetting();

    EnableButton( true );
}

/////////////////////////////////////////////////////////////////////////////
// CBookeyView �N���X�̃��b�Z�[�W �n���h��

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBookeyView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    UpdateData( FALSE );	
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CBookeyView::OnButtonTool()
{
    ManagementBookmark();
}

void CBookeyView::OnButtonSetting()
{
    EditSetting();
}

void CBookeyView::OnButtonFinish()
{
    AfxGetMainWnd()->PostMessage( WM_CLOSE );
}

int CBookeyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    if( m_dropTarget.Register( this ) ) {   // �h���b�v�^�[�Q�b�g�ւ̓o�^
        DragAcceptFiles( TRUE );
        return 0;
    }
    return -1;
}

DROPEFFECT CBookeyView::OnDragEnter(
            COleDataObject* pDataObject,
            DWORD           dwKeyState,
            CPoint          point )
{
    if( pDataObject->IsDataAvailable(CF_TEXT)  ||
        pDataObject->IsDataAvailable(CF_HDROP)    ) {
        return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
                            //  �R���g���[���̏�Ԃɂ��A�R�s�[���ǂ�����ʒm
    }

	return CFormView::OnDragEnter(pDataObject, dwKeyState, point);
}

void CBookeyView::OnDragLeave()
{
	CFormView::OnDragLeave();
}

DROPEFFECT CBookeyView::OnDragOver(
            COleDataObject* pDataObject,
            DWORD           dwKeyState,
            CPoint          point )
{
    if( pDataObject->IsDataAvailable(CF_TEXT)  ||
        pDataObject->IsDataAvailable(CF_HDROP)    ) {
        return (dwKeyState & MK_CONTROL) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
    }

	return CFormView::OnDragOver(pDataObject, dwKeyState, point);
}

BOOL CBookeyView::OnDrop(
            COleDataObject* pDataObject,
            DROPEFFECT      dropEffect,
            CPoint          point )
{
    if( pDataObject->IsDataAvailable(CF_TEXT) ) {
        // �h���b�v���ꂽ�f�[�^���擾
        HGLOBAL     hData = pDataObject->GetGlobalData(CF_TEXT);
        ASSERT(hData);
        const char  *ptr  = (const char *)GlobalLock(hData);
        char        url[MAX_URLLENGTH + 2];

        // URL �����o��
        memset( url, 0x00, MAX_URLLENGTH + 1 );
        strncpy( url, ptr, MAX_URLLENGTH );
        GlobalUnlock(hData);
        GlobalFree(hData);

        // �u�b�N�}�[�N��o�^
        PutBookmark( url );

        return TRUE;
    }

    if( pDataObject->IsDataAvailable(CF_HDROP) ) {
        /* �h���b�v���ꂽ���̂��u�t�@�C���v�̏ꍇ */
        HDROP   hdrop;
        char    filename[MAX_PATH];
        int     num;

        HGLOBAL     hData = pDataObject->GetGlobalData(CF_HDROP);
        ASSERT(hData);
        const char  *ptr  = (const char *)GlobalLock(hData);
        size_t      sz    = MAX_PATH;

        hdrop = (HDROP)ptr;
        /* �h���b�v���ꂽ�t�@�C���̌��𓾂� */
        num = DragQueryFile( hdrop, (UINT)0xFFFFFFFF, NULL, 0 );
        /* �t�@�C�������� */
        for ( int i = 0; i < num; i++ ) {
            filename[0] = NUL;
            DragQueryFile( hdrop, i, filename, sz );
            if ( filename[0] ) {
                FILE    *fp;
                char    buf[BUFSIZ];
                char    *p;
                BOOL    flag = FALSE;

                if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                    // URL �����o��
                    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
                        if ( (flag == FALSE) &&
                             !strncmp( p, "[InternetShortcut]", 18 ) ) {
                            flag = TRUE;
                            continue;
                        }
                        else if ( (flag == TRUE) &&
                                  !strncmp( p, "URL=", 4 ) ) {
                            char    *q;

                            p += 4;
                            q = p + (strlen( p ) - 1);
                            while ((q > p) && ((*q == '\r') || (*q == '\n')))
                                *q-- = NUL;

                            // �u�b�N�}�[�N��o�^
                            PutBookmark( p );
                            break;
                        }
                        flag = FALSE;
                    }
                    fclose( fp );
                }
            }
        }
        GlobalUnlock(hData);
        GlobalFree(hData);

        return TRUE;
    }

	return CFormView::OnDrop(pDataObject, dropEffect, point);
}

void CBookeyView::OnEditPaste()
{
    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        return;

    HGLOBAL     hData;
    const char  *ptr;
    char        url[MAX_URLLENGTH + 1];

    // �N���b�v�{�[�h���� URL �����o��
    OpenClipboard();
    hData = (HGLOBAL)GetClipboardData(CF_TEXT);
    ASSERT(hData);
    ptr = (const char *)GlobalLock(hData);
    memset( url, 0x00, MAX_URLLENGTH + 1 );
    strncpy( url, ptr, MAX_URLLENGTH );
    GlobalUnlock(hData);
 // GlobalFree(hData); �� ������ free ���Ă͂����Ȃ�! (�q�[�v���s�������N����)
    CloseClipboard(); // �� free �� CloseClipboard() �̒��ł���Ă���

    // �u�b�N�}�[�N��o�^
    PutBookmark( url );
}

void CBookeyView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFormView::OnShowWindow(bShow, nStatus);
	
    if ( bShow == FALSE ) {
        BOOL    b;

        EnterCriticalSection( &m_cs_bookey );
        b = m_param.active;
        LeaveCriticalSection( &m_cs_bookey );

        if ( b ) {
            CString title;
            CString text;

            title.LoadString(IDS_TTL_BUSY_GETTING);
            text.LoadString( IDS_TXT_BUSY_BUSY);
            MessageBox( text,   // �܂��O�̃u�b�N�}�[�N�o�^��Ƃ��I�����Ă���
                                // ����B�������΂炭���҂����������B�ǂꂾ��
                                // �҂��Ă��I���Ȃ��ꍇ�́A�\���󂠂�܂���
                                // �� bookey �������I�������Ă��������B
                        title,  // �o�^��ƒ�
                        MB_OK|MB_ICONWARNING );
        }
    }
#ifdef  _DEBUG
    else {
        CButton *bp = (CButton *)GetDlgItem( IDC_CHECK_LANGUAGE );
        bp->EnableWindow( TRUE );
        bp->ShowWindow( SW_SHOW );
    }
#endif
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBookeyView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPoint  cMenuPt;
	GetCursorPos( &cMenuPt );

#define IDC_MENU_COPY   1
    CMenu   menu;
    CString text;

    text.LoadString(IDS_MENU_PASTE);
    menu.CreatePopupMenu();
    menu.AppendMenu( MF_STRING, IDC_MENU_COPY, text );  // �\��t��(&P)

    if ( !IsClipboardFormatAvailable(CF_TEXT) )
        menu.EnableMenuItem( IDC_MENU_COPY, MF_GRAYED );

    int iCommand;
	iCommand = menu.TrackPopupMenu(
                TPM_LEFTALIGN | TPM_BOTTOMALIGN  |
                TPM_RETURNCMD | TPM_LEFTBUTTON,
                cMenuPt.x, cMenuPt.y, this, NULL );

    if ( iCommand == IDC_MENU_COPY )
	    OnEditPaste();

    menu.DestroyMenu();
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

void CBookeyView::OnCheckTagSuggestion()
{
    m_useTagSuggestion = !m_useTagSuggestion;

    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_TAG_SUGGESTION );
    if ( m_useTagSuggestion == TRUE )
        p->SetCheck( 1 );
    else
        p->SetCheck( 0 );
    SaveSetting();
}

void CBookeyView::OnCheckUsers()
{
    m_useUsers = !m_useUsers;

    CButton *p = (CButton *)GetDlgItem( IDC_CHECK_USERS );
    if ( m_useUsers == TRUE )
        p->SetCheck( 1 );
    else
        p->SetCheck( 0 );
    SaveSetting();
}

void CBookeyView::OnTimer(UINT nIDEvent)
{
    if ( nIDEvent == ID_THREAD_REGISTERBOOKMARK ) {
        CWinThread  *p;

        KillTimer( nIDEvent );
        EnterCriticalSection( &m_cs_bookey );
        p = m_registerBookmarkThread;
        LeaveCriticalSection( &m_cs_bookey );
        if ( p ) {
            DWORD   exitCode = 0;
            int     status;
            CWaitCursor cur;    // �}�E�X�J�[�\���������v�\��

            EnterCriticalSection( &m_cs_bookey );
            status = GetExitCodeThread( p->m_hThread, &exitCode );
            LeaveCriticalSection( &m_cs_bookey );
            if ( (status != FALSE) && (exitCode == STILL_ACTIVE) ) {
             // SetFocus();
                UpdateWindow(); // CBookeyView �̍ĕ`��
                SetTimer( nIDEvent, MS_THREAD_REGISTERBOOKMARK, NULL );
            }
            else {
                long    num = 0;

                EnterCriticalSection( &m_cs_bookey );
                delete m_registerBookmarkThread;
                m_registerBookmarkThread = NULL;
                m_param.active = FALSE;
                m_procDialog.DestroyWindow();
                m_procCreated = false;
                num = m_numOfWaiting;
                LeaveCriticalSection( &m_cs_bookey );

                if ( checkProxyInfo() ) {
                    // proxy�֘A�̐ݒ�Ɍ�肪����Ǝv����ꍇ�A����N������
                    // �Đݒ�\�Ƃ��邽�߁A���܂̐ݒ����������j������
                    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();

                    bp->m_proxyType = CBookeyApp::autoDetect;
                    SetProxyInfo( true );
                }

                if ( num > 0 ) {
                    CString s = getWaiting();
                    if ( s.GetLength() > 0 ) {
                        putBookmark( s );
                        return;
                    }
                }
                EnableButton( true );
            }
        }
        return;
    }
	
	CFormView::OnTimer(nIDEvent);
}

void CBookeyView::OnButtonProxy() 
{
    CBookeyApp      *bp = (CBookeyApp *)AfxGetApp();
    int             useProxy = bp->m_useProxy;
    char            proxyServer[MAX_SERVERNAME];
    unsigned short  proxyPort;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];

    EnableButton( false );

    setConfirmProxyInfoFunc( (CONF_FUNC)(-1) );
    proxyServer[0]   = NUL;
    proxyPort        = 0;
    proxyUserName[0] = NUL;
    proxyPassword[0] = NUL;
    initProxyInfo();
    if ( bp->m_proxyServer.GetLength() == 0 ) {
        useProxy = FALSE;
        getProxyInfo( &useProxy, proxyServer, &proxyPort,
                      proxyUserName, proxyPassword );
    }
    else {
        strcpy( proxyServer, bp->m_proxyServer );
        proxyPort = (unsigned short)(bp->m_proxyPort);
        strcpy( proxyUserName, bp->m_proxyUsername );
        strcpy( proxyPassword, bp->m_proxyPassword );
    }
    confirmProxyInfo( &useProxy, proxyServer, &proxyPort,
                      proxyUserName, proxyPassword );

    if ( useProxy == FALSE ) {
        bp->m_proxyType = CBookeyApp::notUsed;
        bp->m_useProxy  = false;
    }
    else if ( bp->m_proxyType == CBookeyApp::manualSetting ) {
        bp->m_proxyType = CBookeyApp::specialSetting;
        if ( bp->m_useProxy ) {
            setProxyInfo( bp->m_proxyServer,
                          (unsigned short)(bp->m_proxyPort),
                          bp->m_proxyUsername,
                          bp->m_proxyPassword );
        }
    }
    setUseProxy( bp->m_useProxy );
    syncProxyInfo();
    SaveSetting();

    EnableButton( true );
}

void CBookeyView::OnCheckLanguage() 
{
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
    bp->m_langCode = getLanguageCode();
    if ( bp->m_langCode == 0x0409 ) {
        bp->m_langCode = 0x0411;
    }
    else {
        bp->m_langCode = 0x0409;
    } 
    setLanguageCode( bp->m_langCode );
    SaveSetting();
    bp->ReInitialize();
}

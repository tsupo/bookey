/*
 * parameter.h : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CParameter �N���X�̒�`
 *          written by H.Tsujimura  13 Oct 2005, 5 Jul 2006
 *
 * $Log: /comm/bookey/parameter.h $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/07/09 15:48 Tsujimura543
 * writeKey() �� evalKey() �� unsigned long �o�[�W������ǉ�
 * 
 * 5     07/01/18 0:53 Tsujimura543
 * �f�o�b�O�p�̃R�[�h(�̖��c)���폜
 * 
 * 4     06/08/21 21:06 Tsujimura543
 * authType �̒l���u�����ݒ�t�@�C���v�ɕۑ�����悤�ɂ���
 * 
 * 3     06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 2     06/07/05 13:59 Tsujimura543
 * �K�v�ŏ����̂��̂���������悤�ɂ���
 * 
 * 1     06/07/05 13:10 Tsujimura543
 * �����ݒ�t�@�C������ǂݎ�������e����́A�i�[�A�ƍ����鏈���A
 * �����ݒ�t�@�C���֏����o�������� bookeyView.cpp ���番���Ɨ�
 * ������
 */

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

/*
 * �Í����ς� parameter �𕜍�����
 */

void
extractKey(
    CString             &param,         // (O) �����ς݃f�[�^
    const unsigned char *encrypted,     // (I) ����������(�Í����ς�)�f�[�^
    const unsigned char *rsaString );   // (I) �����ɕK�v�ȏ��(�閧��)


/*
 * �Í����ς� parameter ������ɕ����ł��邱�Ƃ��m�F����
 */

void
checkKey(
    const char          *value,        // (I) �Í����O�̃f�[�^
    const unsigned char *encrypted,    // (I) �Í����ς݃f�[�^
    const unsigned char *rsaString,    // (I) �����ɕK�v�ȏ��(�閧��)
    bool                &ret );        // (O) �����ł��邱�Ƃ�ۏ؂ł��邩�ۂ�


/*
 * (�����ݒ�t�@�C������ǂݎ����)parameter �̒��o
 */

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    char       *value );    // (O) parameter �̒l(������)

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    CString    &value );    // (O) parameter �̒l(CString)

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    BOOL       &value );    // (O) parameter �̒l(BOOL)

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter ���ے����閼�O
    bool       &value );    // (O) parameter �̒l(bool)

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter ���ے����閼�O
    long       &value );    // (O) parameter �̒l(long)

bool
evalKey(
    const char    *context, // (I) �����ݒ�t�@�C������ǂݎ����������
    const char    *name,    // (I) parameter �̖��O
    unsigned long &value ); // (O) parameter �̒l(unsigned long)


/*
 * �����ݒ�t�@�C���ւ� parameter �̏����o��
 */

void
writeKey(
    FILE       *fp,         // (I/O) �����o����
    const char *name,       // (I) parameter �̖��O
    const char *value );    // (I) parameter �̒l(������)

void
writeKey(
    FILE       *fp,         // (I/O) �����o����
    const char *name,       // (I) parameter �̖��O
    BOOL       value );     // (I) parameter �̒l(BOOL)

void
writeKey(
    FILE       *fp,         // (I/O) �����o����
    const char *name,       // (I) parameter �̖��O
    long       value );     // (I) parameter �̒l(long)

void
writeKey(
    FILE          *fp,      // (I/O) �����o����
    const char    *name,    // (I) parameter �̖��O
    unsigned long value );  // (I) parameter �̒l(unsigned long)

void
writeKey(
    FILE          *fp,      // (I/O) �����o����
    const char    *name,    // (I)   parameter ���ے����閼�O
    const char    *value,   // (I)   parameter �̒l(������) [�Í����Ώ�]
    char          *key,     // (I)   ���J��
    unsigned char **secret, // (I/O) �����ɕK�v�ȏ��(�閧��)
    bool          &done );  // (O)   �Í����������s�ς݂��ۂ�

#endif  /* __PARAMETER_H__ */

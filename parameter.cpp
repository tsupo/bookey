/*
 * parameter.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      CParameter �N���X�̒�`
 *          written by H.Tsujimura  13 Oct 2005, 5 Jul 2006
 *
 * $Log: /comm/bookey/parameter.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    07/12/05 23:17 Tsujimura543
 * unbase64() �̈����ǉ��ɔ����C�������{
 * 
 * 10    07/07/09 15:48 Tsujimura543
 * writeKey() �� evalKey() �� unsigned long �o�[�W������ǉ�
 * 
 * 9     07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 8     07/03/14 17:08 Tsujimura543
 * StdAfx.h ���C���N���[�h���Ȃ��Ă������悤�ɂ���
 * 
 * 7     07/01/18 0:37 Tsujimura543
 * �f�o�b�O�p�̃R�[�h(�̖��c)���폜
 * 
 * 6     07/01/17 23:53 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 5     06/08/21 21:06 Tsujimura543
 * authType �̒l���u�����ݒ�t�@�C���v�ɕۑ�����悤�ɂ���
 * 
 * 4     06/07/05 20:50 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 3     06/07/05 17:49 Tsujimura543
 * CUserInfo �����ɂ�郊�t�@�N�^�����O��12�i�K�A�I��
 * 
 * 2     06/07/05 14:02 Tsujimura543
 * �R�[�h�𐮗�
 * 
 * 1     06/07/05 13:10 Tsujimura543
 * �����ݒ�t�@�C������ǂݎ�������e����́A�i�[�A�ƍ����鏈���A
 * �����ݒ�t�@�C���֏����o�������� bookeyView.cpp ���番���Ɨ�
 * ������
 */

#include "bookey.h"
#include "parameter.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/parameter.cpp 1     09/05/14 3:48 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
 *  �w�� parameter ���Í�������
 */

void
encodeParameter(
    FILE          *fp,          // (I/O) �Í����ς݃f�[�^�o�͐�
    const char    *param,       // (I)   �Í����Ώۃf�[�^�{��
    const char    *paramName,   // (I)   �Í����Ώۃf�[�^��
    char          *key,         // (I)   �Í������ɗ��p������J��
    unsigned char **rsaString,  // (O)   �����ɕK�v�ȏ��(�閧��)
    bool          &encrypted )  // (O)   �Í����ɐ����������ۂ�
{
    int           len;
    unsigned char *cryptedString = NULL;

    len = encodeByRSA( param, rsaString, &cryptedString );
    if ( len > 0 ) {
        encrypted = true;
        if ( !(key[0]) )
            strcpy( key, base64(*rsaString, strlen((char *)*rsaString)) );
        fprintf( fp, "%sEncrypted: %s\n",
                 paramName,
                 base64( cryptedString, len ) );
        freeRSAbuffer( (char *)cryptedString );
    }
    else
        fprintf( fp, "%s: %s\n", paramName, param );
}


/*
 *  �w�� parameter �𕜍�����
 */

void
decodeParameter(
    CString             &param,           // (O) �����ς݃f�[�^
    const unsigned char *encryptedString, // (I) ����������(�Í����ς�)�f�[�^
    const unsigned char *rsaString )      // (I) �����ɕK�v�ȏ��(�閧��)
{
    char            *p;
    unsigned char   targetString[BUFSIZ];   // �����Ώۃo�C�g��
    int             len = -1;               // ��������(������)�̒���
    size_t          sz  = 0;

    targetString[0] = NUL;
    p = unbase64( encryptedString, targetString, &sz );
    if ( p ) {
        char    *decodedString = NULL;      // �������ʊi�[�̈�ւ̃|�C���^

        if ( targetString[0] )
            len = decodeByRSA( &decodedString, rsaString,
                               (unsigned char *)targetString,
                               strlen( (char *)targetString ) );
        if ( len >= 0 ) {
            param = decodedString;
            freeRSAbuffer( decodedString );
        }
    }
}


/*
 * �Í����ς� parameter ������ɕ����ł��邱�Ƃ��m�F����
 */

void
checkKey(
    const char          *value,        // (I) �Í����O�̃f�[�^
    const unsigned char *encrypted,    // (I) �Í����ς݃f�[�^
    const unsigned char *rsaString,    // (I) �����ɕK�v�ȏ��(�閧��)
    bool                &ret )         // (O) �����ł��邱�Ƃ�ۏ؂ł��邩�ۂ�
{
    if ( encrypted[0] ) {
        CString param;

        decodeParameter( param,
                         (unsigned char *)encrypted,
                         (unsigned char *)rsaString );
        // param(�Í����ς݃f�[�^�𕜍���������) �� bookmark.m_password (�Í�
        // ������O�̃f�[�^) ���ƍ����A���҂���v����΁A(�����\�Ȍ`��)�Í�
        // ���ɐ������Ă�����̂Ɣ��f���� [�����Ɏ��s����Í����ς݃f�[�^����
        // ������邱�Ƃ����邽�߁A�Í����ς݃f�[�^������ɕ����ł��邱�Ƃ���
        // �炩���ߊm�F���Ă�������]
        if ( (param.GetLength() == 0)      ||
             (param.Compare( value ) != 0)    ) {
            ret = false;    // �ƍ����ʕs��v (���̈Í����ς݃f�[�^�͍̗p�ł�
                            // �Ȃ�)
        }
    }
}


/*
 * �Í����ς� parameter �𕜍�����
 */

void
extractKey(
    CString             &param,         // (O) �����ς݃f�[�^
    const unsigned char *encrypted,     // (I) ����������(�Í����ς�)�f�[�^
    const unsigned char *rsaString )    // (I) �����ɕK�v�ȏ��(�閧��)
{
    if ( encrypted[0] )
        decodeParameter( param,
                         (unsigned char *)encrypted,
                         (unsigned char *)rsaString );
}


/*
 * (�����ݒ�t�@�C������ǂݎ����)parameter �̒��o
 */

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    char       *value )     // (O) parameter �̒l(������)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        strcpy( value, context + len );
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    CString    &value )     // (O) parameter �̒l(������)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = context + len;
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter ���ے����閼�O
    bool       &value )     // (O) parameter �̒l(bool)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = !strncmpi( context + len, "TRUE", 4 ) ? true : false;
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    BOOL       &value )     // (O) parameter �̒l(BOOL)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = !strncmp( context + len, "TRUE", 4 ) ? TRUE : FALSE;
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char *context,    // (I) �����ݒ�t�@�C������ǂݎ����������
    const char *name,       // (I) parameter �̖��O
    long       &value )     // (O) parameter �̒l(long)
{
    bool    ret = false;
    char    target[BUFSIZ];
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = atol( context + len );
        ret = true;
    }

    return ( ret );
}

bool
evalKey(
    const char    *context, // (I) �����ݒ�t�@�C������ǂݎ����������
    const char    *name,    // (I) parameter �̖��O
    unsigned long &value )  // (O) parameter �̒l(unsigned long)
{
    bool    ret = false;
    char    target[BUFSIZ];
    char    *dummy;
    int     len;

    sprintf( target, "%s: ", name );
    len = strlen( target );

    if ( !strncmp( context, target, len ) ) {
        value = strtoul( context + len, &dummy, 10 );
        ret = true;
    }

    return ( ret );
}

/*
 * �����ݒ�t�@�C���ւ� parameter �̏����o��
 */

void
writeKey(
    FILE       *fp,     // (I/O) �����o����
    const char *name,   // (I)   parameter �̖��O
    const char *value ) // (I)   parameter �̒l(������)
{
    fprintf( fp, "%s: %s\n", name, value );
}

void
writeKey(
    FILE       *fp,     // (I/O) �����o����
    const char *name,   // (I)   parameter �̖��O
    CString    value )  // (I)   parameter �̒l(CString)
{
    if ( value.GetLength() > 0 )
        fprintf( fp, "%s: %s\n",
                 name,
                 (const char *)value );
}

void
writeKey(
    FILE       *fp,     // (I/O) �����o����
    const char *name,   // (I)   parameter �̖��O
    BOOL       value )  // (I)   parameter �̒l(BOOL)
{
    fprintf( fp, "%s: %s\n",
             name, value ? "TRUE" : "FALSE" );
}

void
writeKey(
    FILE       *fp,     // (I/O) �����o����
    const char *name,   // (I)   parameter �̖��O
    long       value )  // (I)   parameter �̒l(long)
{
    fprintf( fp, "%s: %ld\n", name, value );
}

void
writeKey(
    FILE          *fp,      // (I/O) �����o����
    const char    *name,    // (I)   parameter �̖��O
    unsigned long value )   // (I)   parameter �̒l(long)
{
    fprintf( fp, "%s: %lu\n", name, value );
}

void
writeKey(
    FILE          *fp,      // (I/O) �����o����
    const char    *name,    // (I)   parameter ���ے����閼�O
    const char    *value,   // (I)   parameter �̒l(������) [�Í����Ώ�]
    char          *key,     // (I)   ���J��
    unsigned char **secret, // (I/O) �����ɕK�v�ȏ��(�閧��)
    bool          &done )   // (O)   �Í����������s�ς݂��ۂ�
{
    if ( value && *value && (strlen( value ) > 0) )
        encodeParameter( fp,
                         value,
                         name,
                         key, secret, done );
}

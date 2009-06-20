/*
 *  blogPeople.c
 *      BlogPeople �Ƀ��O�C������
 *          written by H.Tsujimura  30 Sep 2005 / 18 Oct 2005
 *
 * $Log: /comm/bookey/putBPT/blogPeople.c $
 * 
 * 1     09/05/14 4:31 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     06/10/20 21:25 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 3     05/10/19 16:54 Tsujimura543
 * �`���̃R�����g���C�� (�t�@�C�������O�̃R�����g�̂܂܂�����)
 * 
 * 2     05/10/18 13:39 Tsujimura543
 * ���ӏ���(�R�����g)��ǉ�
 * 
 * 1     05/10/18 13:34 Tsujimura543
 * getBPhash.c ���� loginBlogPeople() �𕪗��A�Ɨ������� blogPeople.c ���쐬
 */

#include "xmlRPC.h"
#include "myClip.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/putBPT/blogPeople.c 1     09/05/14 4:31 tsupo $";
#endif


/* BlogPeople �Ƀ��O�C������ */
//  ����: ��1�����Ŏw�肷�郁�[���A�h���X�ɂ���
//          1�� login �p���[���A�h���X�ɑ��̃��[���A�h���X��R�t���Ă����
//          ��(����blog��o�^���Ă���ꍇ)�́ABlogPeople IB �� BlogPeople Tags
//          �𗘗p���Ă��郁�[���A�h���X���w�肷��B���̃��[���A�h���X���w��
//          ���� login ���Ă��A���Y�T�[�r�X�͗��p�ł��Ȃ�)
int
loginBlogPeople( const char *username,  // (I)   ���[�U�� (���[���A�h���X)
                 const char *password,  // (I)   �p�X���[�h
                 char       *cookie )   // (I/O) �N�b�L�[
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    *p;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 20;

    if ( !cookie )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "http://member.blogpeople.net/member/member_index.jsp" );
    setTargetURL( url );
    sprintf( request,
             "user_id=%s&"
             "passwd=%s&"
             "autologin=1&"
             "Submit=�@���O�C���@&opt=&url=",
             username, password );
    setUpReceiveBuffer( response, sz );
    p = http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );

    if ( !p || !(*p) )
        ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
    else if ( *response ) {
        if ( strstr( response, "���񃍃O�C����" ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}

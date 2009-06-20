/*
 * confirmProxy.cpp : �\�[�V�����u�b�N�}�[�N�Ǘ��v���O����
 *      proxy���ݒ�m�F����
 *
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/bookey/confirmProxy.cpp $
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 3     07/03/14 20:09 Tsujimura543
 * proxy.txt �ɏ����o���|�[�g�ԍ��̒l�����������s����C��
 * 
 * 2     07/03/14 17:38 Tsujimura543
 * checkProxyInfo() ������
 * 
 * 1     07/03/14 16:22 Tsujimura543
 * (1) �u�u���O�N���C�A���g BloGolEe�v�p�ɏ������\�[�X����荞��
 * (2) �o�C�����K���Ή�
 * =======================================================================
 * 5     07/03/13 19:56 Tsujimura543
 * proxy�ݒ���� BlogoleeApp ���ɕێ�����悤�ɂ���
 * 
 * 4     07/03/10 5:22 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ����Ă݂�
 * 
 * 3     07/03/09 21:23 Tsujimura543
 * FILE_CONFIG_PROXY ��ǉ�
 * 
 * 2     07/03/09 21:21 Tsujimura543
 * checkProxyInfo() ��ǉ�
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "bookey.h"
#include "ProxyInfoDialog.h"
#include "confirmProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/confirmProxy.cpp 1     09/05/14 3:48 tsupo $";
#endif

#define FILE_CONFIG_PROXY   "./proxy.txt"   // proxy�T�[�o���ݒ�t�@�C��

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword )
{
    int         ret = FALSE;
    CBookeyApp  *bp = (CBookeyApp *)AfxGetApp();
    LCID        l = getLanguageCode();

    int r = MessageBox( NULL,
                        l == 0x0411
                            ? "proxy�T�[�o�o�R�ŃC���^�[�l�b�g��"
                              "���p���Ă��܂���?"
                            : "Do you access the Internet via a "
                              "proxy server ?",
                        l == 0x0411
                            ? "�C���^�[�l�b�g���p�`�Ԋm�F"
                            : "Confirmation of proxy server",
                        MB_YESNO|MB_ICONQUESTION );

    if ( r == IDYES ) {
        CProxyInfoDialog    dlg;
        if ( proxyServer[0] ) {
            dlg.m_proxyServerName = proxyServer;
            dlg.m_proxyPortNumber = *proxyPort;
            if ( proxyUserName[0] ) {
                dlg.m_proxyUserName = proxyUserName;
                if ( proxyPassword[0] )
                    dlg.m_proxyPassword = proxyPassword;
            }
        }
        dlg.DoModal();

        *useProxy = TRUE;
        strcpy( proxyServer, dlg.m_proxyServerName );
        *proxyPort = (unsigned short)(dlg.m_proxyPortNumber);

        bp->m_proxyServer = proxyServer;
        bp->m_proxyPort   = *proxyPort;

        if ( dlg.m_proxyUserName.GetLength() > 0 ) {
            bp->m_proxyUsername = dlg.m_proxyUserName;
            if ( dlg.m_proxyPassword.GetLength() > 0 )
                bp->m_proxyPassword = dlg.m_proxyPassword;
        }

        FILE    *fp;
        if ( ( fp = fopen( FILE_CONFIG_PROXY, "w" ) ) != NULL ) {
            fprintf( fp, "%s\n", proxyServer );
            fprintf( fp, "%d\n", *proxyPort );

            if ( dlg.m_proxyUserName.GetLength() > 0 ) {
                if ( proxyUserName )
                    strcpy( proxyUserName, dlg.m_proxyUserName );
                fprintf( fp, "%s\n", (const char *)dlg.m_proxyUserName );

                if ( dlg.m_proxyPassword.GetLength() > 0 ) {
                    if ( proxyPassword )
                        strcpy( proxyPassword, dlg.m_proxyPassword );
                    fprintf( fp, "%s\n", (const char *)dlg.m_proxyPassword );
                }
            }
            fclose( fp );
        }

        ret = TRUE;
    }
    else {
        *useProxy = FALSE;
        ret = TRUE;
    }

    bp->m_proxyType = CBookeyApp::manualSetting;
    bp->m_useProxy  = *useProxy == TRUE ? true : false;

    return ( ret );
}

bool
checkProxyInfo()
{
    bool    ret = isNecessaryToCheckProxyInfo() ? true : false;

    if ( ret )
        initProxyInfo();

    return ( ret );
}

void
initProxyInfo()
{
    unlink( FILE_CONFIG_PROXY );
}

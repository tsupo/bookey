# Microsoft Developer Studio Project File - Name="bookey" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=bookey - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "bookey.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "bookey.mak" CFG="bookey - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "bookey - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "bookey - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/comm/bookey", JDAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bookey - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\xmlRPC" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 xmlRPC.lib shlwapi.lib wininet.lib /nologo /version:0.225 /subsystem:windows /machine:I386 /libpath:"..\xmlRPC\Release"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "bookey - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /I "..\xmlRPC" /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xmlRPC.lib shlwapi.lib wininet.lib /nologo /version:0.225 /subsystem:windows /incremental:no /debug /machine:I386 /pdbtype:sept /libpath:"..\xmlRPC\Debug"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "bookey - Win32 Release"
# Name "bookey - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\bbAuth.c
# End Source File
# Begin Source File

SOURCE=.\BlogIDSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\blogPet.c
# End Source File
# Begin Source File

SOURCE=.\bookey.cpp
# End Source File
# Begin Source File

SOURCE=.\bookey.rc
# End Source File
# Begin Source File

SOURCE=.\bookeyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\bookeyDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\bookeyView.cpp
# End Source File
# Begin Source File

SOURCE=.\CaptchaDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CImage.cpp
# End Source File
# Begin Source File

SOURCE=.\confirmProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\decodeContents.c
# End Source File
# Begin Source File

SOURCE=.\Delete1470net.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteBlogPet.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteBlueDot.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteBookmarkDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteBookmarkDialog3.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteBookmarkDialog4.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteDelicious.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteDiigo.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteDrecomRSS.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteEcNaviClip.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteFC2bookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteFlog.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteHatenaBookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\deleteHtmlTags.c
# End Source File
# Begin Source File

SOURCE=.\DeleteJoltMark.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteLivedoorClip.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteLocalOpml.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteMMmemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteNiftyClip.cpp
# End Source File
# Begin Source File

SOURCE=.\DeletePookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteTagsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteYahooBookmarks.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteYJbookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\digg.c
# End Source File
# Begin Source File

SOURCE=.\drecomRSS.c
# End Source File
# Begin Source File

SOURCE=.\ecNavi.c
# End Source File
# Begin Source File

SOURCE=.\editBlueDot.c
# End Source File
# Begin Source File

SOURCE=.\EditBookmarkDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\editDelicious.c
# End Source File
# Begin Source File

SOURCE=.\editDrecomRSS.c
# End Source File
# Begin Source File

SOURCE=.\editHB.c
# End Source File
# Begin Source File

SOURCE=.\editNiftyClip.c
# End Source File
# Begin Source File

SOURCE=.\encodeContents.c
# End Source File
# Begin Source File

SOURCE=.\extractTags.c
# End Source File
# Begin Source File

SOURCE=.\fc2bookmark.c
# End Source File
# Begin Source File

SOURCE=.\flog.c
# End Source File
# Begin Source File

SOURCE=.\getMMmemo\get1470net.c
# End Source File
# Begin Source File

SOURCE=.\getASIN.c
# End Source File
# Begin Source File

SOURCE=.\getBlogPet.c
# End Source File
# Begin Source File

SOURCE=.\getDelicious\getBlueDot.c
# End Source File
# Begin Source File

SOURCE=.\getBookmarks.cpp
# End Source File
# Begin Source File

SOURCE=.\getDelicious\getDelicious.c
# End Source File
# Begin Source File

SOURCE=.\getDiigo.c
# End Source File
# Begin Source File

SOURCE=.\getDrecomRSS.c
# End Source File
# Begin Source File

SOURCE=.\getEcNaviClip.c
# End Source File
# Begin Source File

SOURCE=.\getEvaluation.c
# End Source File
# Begin Source File

SOURCE=.\getFC2bookmark.c
# End Source File
# Begin Source File

SOURCE=.\getFlog.c
# End Source File
# Begin Source File

SOURCE=.\getHB\getHB.c
# End Source File
# Begin Source File

SOURCE=.\getJoltMark.c
# End Source File
# Begin Source File

SOURCE=.\getLivedoorClip.c
# End Source File
# Begin Source File

SOURCE=.\getLocalOpml.c
# End Source File
# Begin Source File

SOURCE=.\getMMmemo\getMMmemo.c
# End Source File
# Begin Source File

SOURCE=.\getNiftyClip.c
# End Source File
# Begin Source File

SOURCE=.\getPookmark.c
# End Source File
# Begin Source File

SOURCE=.\getString.c
# End Source File
# Begin Source File

SOURCE=.\getTitle.c
# End Source File
# Begin Source File

SOURCE=.\getUsers.c
# End Source File
# Begin Source File

SOURCE=.\getValue.c
# End Source File
# Begin Source File

SOURCE=.\getYahooBookmarks.c
# End Source File
# Begin Source File

SOURCE=.\getYJbookmark.c
# End Source File
# Begin Source File

SOURCE=.\hatena.c
# End Source File
# Begin Source File

SOURCE=.\inputBookmarkHtml.c
# End Source File
# Begin Source File

SOURCE=.\inputDeliciousXML.c
# End Source File
# Begin Source File

SOURCE=.\inputHatenaFeed.c
# End Source File
# Begin Source File

SOURCE=.\inputLivedoorFeed.c
# End Source File
# Begin Source File

SOURCE=.\inputOpera6Adr.c
# End Source File
# Begin Source File

SOURCE=..\bookey\inputOpml.c
# End Source File
# Begin Source File

SOURCE=.\InputPinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\joltMark.c
# End Source File
# Begin Source File

SOURCE=.\jugemkey.c
# End Source File
# Begin Source File

SOURCE=.\justify.c
# End Source File
# Begin Source File

SOURCE=.\livedoorClip.c
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\mmMemo.c
# End Source File
# Begin Source File

SOURCE=.\myClip.c
# End Source File
# Begin Source File

SOURCE=.\newsing.c
# End Source File
# Begin Source File

SOURCE=.\niftyClip.c
# End Source File
# Begin Source File

SOURCE=.\ouputDeliciousXML.c
# End Source File
# Begin Source File

SOURCE=.\outputBookmarkHtml.c
# End Source File
# Begin Source File

SOURCE=.\outputOpera6Adr.c
# End Source File
# Begin Source File

SOURCE=.\outputOpml.c
# End Source File
# Begin Source File

SOURCE=.\parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\ProceedingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ProxyInfoDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\putMMmemo\put1470net.c
# End Source File
# Begin Source File

SOURCE=.\putBlogPet.c
# End Source File
# Begin Source File

SOURCE=.\putDelicious\putBlueDot.c
# End Source File
# Begin Source File

SOURCE=.\putBookmarks.c
# End Source File
# Begin Source File

SOURCE=.\putDelicious\putDelicious.c
# End Source File
# Begin Source File

SOURCE=.\putDigg.c
# End Source File
# Begin Source File

SOURCE=.\putDiigo.c
# End Source File
# Begin Source File

SOURCE=.\putDrecomRSS.c
# End Source File
# Begin Source File

SOURCE=.\putEcNaviClip.c
# End Source File
# Begin Source File

SOURCE=.\putFC2bookmark.c
# End Source File
# Begin Source File

SOURCE=.\putFlog.c
# End Source File
# Begin Source File

SOURCE=.\putHB\putHB.c
# End Source File
# Begin Source File

SOURCE=.\putJoltMark.c
# End Source File
# Begin Source File

SOURCE=.\putLivedoorClip.c
# End Source File
# Begin Source File

SOURCE=.\putLocalOpml.c
# End Source File
# Begin Source File

SOURCE=.\putMMmemo\putMMmemo.c
# End Source File
# Begin Source File

SOURCE=.\putNewsing.c
# End Source File
# Begin Source File

SOURCE=.\putNiftyClip.c
# End Source File
# Begin Source File

SOURCE=.\putPookmark.c
# End Source File
# Begin Source File

SOURCE=.\putTimelog.c
# End Source File
# Begin Source File

SOURCE=.\putTumblr.c
# End Source File
# Begin Source File

SOURCE=.\putTwitter.c
# End Source File
# Begin Source File

SOURCE=.\putYahooBookmarks.c
# End Source File
# Begin Source File

SOURCE=.\putYJbookmark.c
# End Source File
# Begin Source File

SOURCE=.\registerBookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplaceTagsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Setting1470net.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingBlogPet.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingBlueDot.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDelicious.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDigg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDiigo.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDrecom.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingEcNavi.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingFC2bookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingFlog.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingHatena.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingJoltMark.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingLivedoor.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingLocalOpml.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingMMmemo.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingNewsing.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingNifty.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingPookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingTimelog.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingTumblr.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingTwitter.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingYahooBookmarks.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingYJbookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\SynchronizeBookmarkDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\timelocal.c
# End Source File
# Begin Source File

SOURCE=.\tumblr.c
# End Source File
# Begin Source File

SOURCE=.\twitStar.c
# End Source File
# Begin Source File

SOURCE=.\UserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\yahoo.c
# End Source File
# Begin Source File

SOURCE=.\yahooJapan.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlogIDSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\blogPet.h
# End Source File
# Begin Source File

SOURCE=.\bookey.h
# End Source File
# Begin Source File

SOURCE=.\bookeyDlg.h
# End Source File
# Begin Source File

SOURCE=.\bookeyDoc.h
# End Source File
# Begin Source File

SOURCE=.\bookeyView.h
# End Source File
# Begin Source File

SOURCE=.\CaptchaDialog.h
# End Source File
# Begin Source File

SOURCE=.\CImage.h
# End Source File
# Begin Source File

SOURCE=.\confirmProxy.h
# End Source File
# Begin Source File

SOURCE=.\deleteBookmark.h
# End Source File
# Begin Source File

SOURCE=.\DeleteBookmarkDialog.h
# End Source File
# Begin Source File

SOURCE=.\DeleteBookmarkDialog3.h
# End Source File
# Begin Source File

SOURCE=.\DeleteBookmarkDialog4.h
# End Source File
# Begin Source File

SOURCE=.\DeleteTagsDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditBookmarkDialog.h
# End Source File
# Begin Source File

SOURCE=.\exportBookmark.h
# End Source File
# Begin Source File

SOURCE=.\getDrecomRSS.h
# End Source File
# Begin Source File

SOURCE=.\importBookmark.h
# End Source File
# Begin Source File

SOURCE=.\InputPinDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\myClip.h
# End Source File
# Begin Source File

SOURCE=.\niftyClip.h
# End Source File
# Begin Source File

SOURCE=.\parameter.h
# End Source File
# Begin Source File

SOURCE=.\ProceedingDialog.h
# End Source File
# Begin Source File

SOURCE=.\ProxyInfoDialog.h
# End Source File
# Begin Source File

SOURCE=.\RBparam.h
# End Source File
# Begin Source File

SOURCE=.\ReplaceTagsDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Setting1470net.h
# End Source File
# Begin Source File

SOURCE=.\SettingBlogPet.h
# End Source File
# Begin Source File

SOURCE=.\SettingBlueDot.h
# End Source File
# Begin Source File

SOURCE=.\SettingDelicious.h
# End Source File
# Begin Source File

SOURCE=.\SettingDialog.h
# End Source File
# Begin Source File

SOURCE=.\SettingDigg.h
# End Source File
# Begin Source File

SOURCE=.\SettingDiigo.h
# End Source File
# Begin Source File

SOURCE=.\SettingDrecom.h
# End Source File
# Begin Source File

SOURCE=.\SettingEcNavi.h
# End Source File
# Begin Source File

SOURCE=.\SettingFC2bookmark.h
# End Source File
# Begin Source File

SOURCE=.\SettingFlog.h
# End Source File
# Begin Source File

SOURCE=.\SettingHatena.h
# End Source File
# Begin Source File

SOURCE=.\SettingJoltMark.h
# End Source File
# Begin Source File

SOURCE=.\SettingLivedoor.h
# End Source File
# Begin Source File

SOURCE=.\SettingLocalOpml.h
# End Source File
# Begin Source File

SOURCE=.\SettingMMmemo.h
# End Source File
# Begin Source File

SOURCE=.\SettingNewsing.h
# End Source File
# Begin Source File

SOURCE=.\SettingNifty.h
# End Source File
# Begin Source File

SOURCE=.\SettingPookmark.h
# End Source File
# Begin Source File

SOURCE=.\SettingTimelog.h
# End Source File
# Begin Source File

SOURCE=.\SettingTumblr.h
# End Source File
# Begin Source File

SOURCE=.\SettingTwitter.h
# End Source File
# Begin Source File

SOURCE=.\SettingYahooBookmarks.h
# End Source File
# Begin Source File

SOURCE=.\SettingYJbookmark.h
# End Source File
# Begin Source File

SOURCE=.\SynchronizeBookmarkDialog.h
# End Source File
# Begin Source File

SOURCE=.\TabDialog.h
# End Source File
# Begin Source File

SOURCE=.\tumblr.h
# End Source File
# Begin Source File

SOURCE=.\twitStar.h
# End Source File
# Begin Source File

SOURCE=.\UserInfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1470.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b_entry16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blogPet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blueDot.bmp
# End Source File
# Begin Source File

SOURCE=.\bookey.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\res\bookey.ico
# End Source File
# Begin Source File

SOURCE=.\res\bookey.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bookeyDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\clip_icon16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\delicious.bmp
# End Source File
# Begin Source File

SOURCE=.\res\digg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\digg_captcha.bmp
# End Source File
# Begin Source File

SOURCE=.\res\diigo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ecNaviPencil.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fc2bookmark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hatenaStarGray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon_flog.bmp
# End Source File
# Begin Source File

SOURCE=.\res\joltMark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\livedoorClip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mm_icon16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\myclip256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newsing.bmp
# End Source File
# Begin Source File

SOURCE=.\res\niftyClip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pookmark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\timelog.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tumblr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\twitterFavicon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yahooBookmark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yjBookmark.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\dist.bat
# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Target
# End Project

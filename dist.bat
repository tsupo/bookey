echo off

REM batch file for distribution of BOOKEY
REM $Header: /comm/bookey/dist.bat 1     09/05/14 3:48 tsupo $

chmod -R +w dist

rm -Rf dist\src

mkdir dist\src
mkdir dist\src\bookey
mkdir dist\src\bookey\res
mkdir dist\src\bookey\getDelicious
mkdir dist\src\bookey\getHB
mkdir dist\src\bookey\getMMmemo
mkdir dist\src\bookey\getMyClip
mkdir dist\src\bookey\putDelicious
mkdir dist\src\bookey\putHB
mkdir dist\src\bookey\putMMmemo
mkdir dist\src\include
mkdir dist\src\lib

copy *.c dist\src\bookey
copy *.h dist\src\bookey
copy *.cpp dist\src\bookey
copy bookey.rc dist\src\bookey
copy res\*.ico dist\src\bookey\res
copy res\*.rc2 dist\src\bookey\res
copy res\*.bmp dist\src\bookey\res
copy res\*.cur dist\src\bookey\res
copy bookey.exe.manifest dist
copy readme.txt          dist
copy Release\bookey.exe  dist
copy Release\xmlRPC.dll  dist

copy getDelicious\*.c dist\src\bookey\getDelicious
copy getDelicious\Release\getDelicious.exe dist

copy getHB\*.c dist\src\bookey\getHB
copy getHB\Release\getHB.exe dist

copy getMMmemo\*.c dist\src\bookey\getMMmemo
copy getMMmemo\Release\getMMmemo.exe dist

copy getMyClip\*.c dist\src\bookey\getMyClip
copy getDRC\Release\getDRC.exe dist

copy putDelicious\*.c dist\src\bookey\putDelicious
copy putDelicious\Release\putDelicious.exe dist

copy putHB\*.c dist\src\bookey\putHB
copy putHB\Release\putHB.exe dist

copy putMMmemo\*.c dist\src\bookey\putMMmemo
copy putMMmemo\Release\putMMmemo.exe dist

copy ..\xmlRPC\blueDot.h dist\src\include
copy ..\xmlRPC\delicious.h dist\src\include
copy ..\xmlRPC\deliciousApi.h dist\src\include
copy ..\xmlRPC\hatenaApi.h dist\src\include
copy ..\xmlRPC\md5.h dist\src\include
copy ..\xmlRPC\sha1.h dist\src\include
copy ..\xmlRPC\xmlRPC.h dist\src\include

copy ..\xmlRPC\Release\xmlRPC.lib dist\src\lib

copy getBlogPet\Release\getBlogPet.exe dist
copy getBlueDot\Release\getBlueDot.exe dist
copy getBuzzurl\Release\getBuzzurl.exe dist
copy getLC\Release\getLC.exe dist
copy getNC\Release\getNC.exe dist
copy getFlog\Release\getFlog.exe dist
copy getPookmark\Release\getPookmark.exe dist
copy getJoltMark\Release\getJoltMark.exe dist
copy get1470net\Release\get1470net.exe dist

copy putBlueDot\Release\putBlueDot.exe dist
copy putPookmark\Release\putPookmark.exe dist
copy putJoltMark\Release\putJoltMark.exe dist
copy put1470net\Release\put1470net.exe dist
copy putBlogPet\Release\putBlogPet.exe dist
copy putNC\Release\putNC.exe dist
copy putBuzzurl\Release\putBuzzurl.exe dist
copy putLC\Release\putLC.exe dist
copy putFlog\Release\putFlog.exe dist
copy putDRC\Release\putDRC.exe dist
copy putNewsing\Release\putNewsing.exe dist

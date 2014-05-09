#Creates a windows installer. 
#Change BUILD_DIR to your xCompiled path (/home/joshua/programming/qt/smarterp-github/build-smarterp-521_windows_x32-Release/build)
#Change MINGW to the location of mingw libs (/usr/i686-w64-mingw32/bin)
#Change QT_LIBS_DIR to the location of your qt plugin folders (/usr/i686-w64-mingw32/lib/qt/plugins)

#variables
BUILD_DIR=/home/joshua/programming/qt/smarterp-github/build-smarterp-521_windows_x32-Release/build
MINGW=/usr/i686-w64-mingw32/bin
QT_LIBS_DIR=/usr/i686-w64-mingw32/lib/qt/plugins


#Clear temp files
rm build -r -f

mkdir build
mkdir build/plugins
mkdir build/sqldrivers
mkdir build/platforms
mkdir build/printsupport

#Get my latest exes and dlls
cp $BUILD_DIR/*.dll build
cp $BUILD_DIR/SmartERP.exe build
cp $BUILD_DIR/plugins/*.dll build/plugins

#Get Qt plugins
cp $QT_LIBS_DIR/printsupport/*.dll build/printsupport
cp $QT_LIBS_DIR/sqldrivers/*.dll build/sqldrivers
cp $QT_LIBS_DIR/platforms/*.dll build/platforms

#Get Mingw and Qt dlls
cp $MINGW/libeay32.dll build
cp $MINGW/libEGL.dll build
cp $MINGW/libgcc_s_sjlj-1.dll build
cp $MINGW/libGLESv2.dll build
cp $MINGW/libmysql.dll build
cp $MINGW/libpcre16-0.dll build
cp $MINGW/libpng16-16.dll build
cp $MINGW/libsqlite3-0.dll build
cp $MINGW/libstdc++-6.dll build
cp $MINGW/libwinpthread-1.dll build
cp $MINGW/Qt5Core.dll build
cp $MINGW/Qt5Gui.dll build
cp $MINGW/Qt5Network.dll build
cp $MINGW/Qt5PrintSupport.dll build
cp $MINGW/Qt5Sql.dll build
cp $MINGW/Qt5Widgets.dll build
cp $MINGW/Qt5Xml.dll build
cp $MINGW/ssleay32.dll build
cp $MINGW/zlib1.dll build

#make NSIS package
makensis smarterp.nsi

#makensis smarterp.nsi




#Creates a windows installer. 
#Change BUILD_DIR to your xCompiled path (/home/joshua/programming/qt/smarterp-github/build-smarterp-521_windows_x32-Release/build)
#Change MINGW to the location of mingw libs (/usr/i686-w64-mingw32/bin)
#Change QT_LIBS_DIR to the location of your qt plugin folders (/usr/i686-w64-mingw32/lib/qt/plugins)

#variables
BUILD_DIR=/home/joshua/programming/qt/smarterp-github/build-smarterp-521_windows_x32-Release/build
MINGW=/usr/i686-w64-mingw32/bin
QT_LIBS_DIR=/usr/i686-w64-mingw32/lib/qt/plugins

OUT_PATH=./build
#Clear temp files
rm $OUT_PATH -r -f

mkdir $OUT_PATH
mkdir $OUT_PATH/plugins
mkdir $OUT_PATH/sqldrivers
mkdir $OUT_PATH/platforms
mkdir $OUT_PATH/printsupport

#Get my latest exes and dlls
cp $BUILD_DIR/*.dll $OUT_PATH
cp $BUILD_DIR/SmartERP.exe $OUT_PATH
cp $BUILD_DIR/plugins/*.dll $OUT_PATH/plugins

#Get Qt plugins
cp $QT_LIBS_DIR/printsupport/*.dll $OUT_PATH/printsupport
cp $QT_LIBS_DIR/sqldrivers/*.dll $OUT_PATH/sqldrivers
cp $QT_LIBS_DIR/platforms/*.dll $OUT_PATH/platforms

#Get Mingw and Qt dlls
cp $MINGW/libeay32.dll $OUT_PATH
cp $MINGW/libEGL.dll $OUT_PATH
cp $MINGW/libgcc_s_sjlj-1.dll $OUT_PATH
cp $MINGW/libGLESv2.dll $OUT_PATH
cp $MINGW/libmysql.dll $OUT_PATH
cp $MINGW/libpcre16-0.dll $OUT_PATH
cp $MINGW/libpng16-16.dll $OUT_PATH
cp $MINGW/libsqlite3-0.dll $OUT_PATH
cp $MINGW/libstdc++-6.dll $OUT_PATH
cp $MINGW/libwinpthread-1.dll $OUT_PATH
cp $MINGW/Qt5Core.dll $OUT_PATH
cp $MINGW/Qt5Gui.dll $OUT_PATH
cp $MINGW/Qt5Network.dll $OUT_PATH
cp $MINGW/Qt5PrintSupport.dll $OUT_PATH
cp $MINGW/Qt5Sql.dll $OUT_PATH
cp $MINGW/Qt5Widgets.dll $OUT_PATH
cp $MINGW/Qt5Xml.dll $OUT_PATH
cp $MINGW/ssleay32.dll $OUT_PATH
cp $MINGW/zlib1.dll $OUT_PATH

#make NSIS package
makensis smarterp.nsi

#Move setup package to out path
mv *.exe ../../
rm $OUT_PATH -r -f



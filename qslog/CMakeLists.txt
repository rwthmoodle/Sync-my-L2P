# Generated from QsLogSharedLibrary.pro.

#####################################################################
## QsLog Generic Library:
#####################################################################

qt_internal_add_cmake_library(QsLog
    OUTPUT_DIRECTORY "$$PWD/build-QsLogShared"
    SOURCES
        QsLog.cpp QsLog.h
        QsLogDest.cpp QsLogDest.h
        QsLogDestConsole.cpp QsLogDestConsole.h
        QsLogDestFile.cpp QsLogDestFile.h
        QsLogDestFunctor.cpp QsLogDestFunctor.h
        QsLogDisableForThisFile.h
        QsLogLevel.h
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_LIBRARIES
        Qt::Core
)

#### Keys ignored in scope 1:.:.:QsLogSharedLibrary.pro:<TRUE>:
# MOC_DIR = "$$DESTDIR/moc"
# OBJECTS_DIR = "$$DESTDIR/obj"
# TEMPLATE = "lib"
# VERSION = "2.0.0"

## Scopes:
#####################################################################

qt_internal_extend_target(QsLog CONDITION WIN32
    DEFINES
        QSLOG_IS_SHARED_LIBRARY
)

#### Keys ignored in scope 3:.:.:QsLogSharedLibrary.pro:UNIX AND NOT MACOS:
# INSTALLS = "headers" "target" "other_files"
# headers.files = "QsLog.h" "QsLogDest.h" "QsLogLevel.h"
# headers.path = "/usr/include/$(QMAKE_TARGET)"
# other_files.files = "*.txt"
# other_files.path = "/usr/local/share/$(QMAKE_TARGET)"

#### Keys ignored in scope 4:.:.:QsLogSharedLibrary.pro:QT_ARCH___contains___x86_64:
# target.path = "/usr/lib64"

#### Keys ignored in scope 5:.:.:QsLogSharedLibrary.pro:else:
# target.path = "/usr/lib"

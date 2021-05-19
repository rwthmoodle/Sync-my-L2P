# Generated from unittest.pro.

#####################################################################
## QsLogUnitTest Binary:
#####################################################################

qt_internal_add_executable(QsLogUnitTest
    SOURCES
        .././QsLog.cpp .././QsLog.h
        .././QsLogDest.cpp .././QsLogDest.h
        .././QsLogDestConsole.cpp .././QsLogDestConsole.h
        .././QsLogDestFile.cpp .././QsLogDestFile.h
        .././QsLogDestFunctor.cpp .././QsLogDestFunctor.h
        .././QsLogDisableForThisFile.h
        .././QsLogLevel.h
        QtTestUtil/QtTestUtil.h
        QtTestUtil/SimpleChecker.cpp
        QtTestUtil/TestRegistration.h
        QtTestUtil/TestRegistry.cpp QtTestUtil/TestRegistry.h
        TestLog.cpp
    INCLUDE_DIRECTORIES
        ../.
    PUBLIC_LIBRARIES
        Qt::Gui
)

#### Keys ignored in scope 1:.:.:unittest.pro:<TRUE>:
# TEMPLATE = "app"

# Generated from log_example.pro.

#####################################################################
## log_example_shared Generic Library:
#####################################################################

qt_internal_add_cmake_library(log_example_shared
    OUTPUT_DIRECTORY "$$PWD/../build-QsLogExample"
    SOURCES
        log_example_shared.cpp log_example_shared.h
    DEFINES
        EXAMPLE_IS_SHARED_LIBRARY
        QSLOG_IS_SHARED_LIBRARY_IMPORT
    INCLUDE_DIRECTORIES
        ..
    PUBLIC_LIBRARIES
        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/../build-QsLogShared
        # Remove: gui
)

#### Keys ignored in scope 2:.:.:log_example_shared.pro:<TRUE>:
# OBJECTS_DIR = "$$DESTDIR/obj"
# TEMPLATE = "lib"

## Scopes:
#####################################################################

qt_internal_extend_target(log_example_shared CONDITION WIN32
    PUBLIC_LIBRARIES
        QsLog2
)

qt_internal_extend_target(log_example_shared CONDITION UNIX
    PUBLIC_LIBRARIES
        QsLog
)
#####################################################################
## log_example Binary:
#####################################################################

qt_internal_add_executable(log_example
    OUTPUT_DIRECTORY "$$PWD/../build-QsLogExample"
    SOURCES
        log_example_main.cpp
    DEFINES
        QSLOG_IS_SHARED_LIBRARY_IMPORT
    INCLUDE_DIRECTORIES
        ..
    PUBLIC_LIBRARIES
        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/../build-QsLogExample
        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/../build-QsLogShared
        # Remove: gui
        log_example_shared
)

#### Keys ignored in scope 5:.:.:log_example_main.pro:<TRUE>:
# OBJECTS_DIR = "$$DESTDIR/obj"
# TEMPLATE = "app"

## Scopes:
#####################################################################

qt_internal_extend_target(log_example CONDITION WIN32
    PUBLIC_LIBRARIES
        QsLog2
)

qt_internal_extend_target(log_example CONDITION UNIX
    PUBLIC_LIBRARIES
        QsLog
)
add_subdirectory(..)


cmake_minimum_required(VERSION 3.18)

project(Sync-my-L2P)

# Set project version
file(READ ./include/version.h version_h_content)
string(REGEX MATCH "#define PRODUCT_VERSION \"([0-9]+)\\.([0-9]+)\\.([0-9]+)\"" unused "${version_h_content}")
set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_1})
set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_2})
set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_3})
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")
include("templates")
include("buildscripts")

# Generated from Sync-my-L2P.pro.

#####################################################################
## Sync-my-L2P Binary:
#####################################################################

qt_internal_add_executable(Sync-my-L2P
    GUI
    OUTPUT_DIRECTORY "bin"
    SOURCES
        gui/autoclosedialog.ui
        gui/browser.ui
        gui/dateidownloader.ui
        gui/info.ui
        gui/logger.ui
        gui/logindialog.ui
        gui/message.ui
        gui/mymainwindow.ui
        gui/options.ui
        include/autoclosedialog.h
        include/browser.h
        include/clientId.h
        include/filedownloader.h
        include/info.h
        include/l2pitemmodel.h
        include/logger.h
        include/login.h
        include/logindialog.h
        include/message.h
        include/mymainwindow.h
        include/mysortfilterproxymodel.h
        include/options.h
        include/parser.h
        include/structureelement.h
        include/urls.h
        include/utils.h
        qslog/QsLog.cpp qslog/QsLog.h
        qslog/QsLogDest.cpp qslog/QsLogDest.h
        qslog/QsLogDestConsole.cpp qslog/QsLogDestConsole.h
        qslog/QsLogDestFile.cpp qslog/QsLogDestFile.h
        qslog/QsLogDestFunctor.cpp qslog/QsLogDestFunctor.h
        qslog/QsLogDisableForThisFile.h
        qslog/QsLogLevel.h
        src/autoclosedialog.cpp
        src/browser.cpp
        src/filedownloader.cpp
        src/info.cpp
        src/l2pitemmodel.cpp
        src/logger.cpp
        src/login.cpp
        src/logindialog.cpp
        src/main.cpp
        src/message.cpp
        src/mymainwindow.cpp
        src/mysortfilterproxymodel.cpp
        src/options.cpp
        src/parser.cpp
        src/structureelement.cpp
        src/utils.cpp
    INCLUDE_DIRECTORIES
        include
        qslog
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Network
        Qt::Xml
        Qt::Core
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

# Look for .ui files in ./gui/ subdir.
set_property (TARGET "Sync-my-L2P" APPEND PROPERTY
    AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/gui"
)

# TODO is this needed?
qt_internal_extend_target("Sync-my-L2P" CONDITION LINUX
    PUBLIC_LIBRARIES
        pthread
)

target_compile_options("Sync-my-L2P"
    PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-fexceptions>
)

# Resources:
set(icons_resource_files
    "Sync-my-L2P.png"
    "about.png"
    "archive.png"
    "audio.png"
    "browser.png"
    "contact.png"
    "contributors.png"
    "course.png"
    "directory.png"
    "document.png"
    "download.png"
    "downloadDirectory.png"
    "license.png"
    "login.png"
    "logout.png"
    "logs.png"
    "magnifier.png"
    "mail.png"
    "otherFile.png"
    "pdf.png"
    "picture.png"
    "refresh.png"
    "semester.png"
    "settings.png"
    "sheet.png"
    "slideshow.png"
    "tutorial.png"
    "video.png"
)

qt_internal_add_resource(Sync-my-L2P "icons"
    PREFIX
        "/icons"
    BASE
        "icons"
    FILES
        ${icons_resource_files}
)
set(translation_resource_files
    "sync-my-l2p_de.qm"
    "sync-my-l2p_en.qm"
    "sync-my-l2p_lb.qm"
    "sync-my-l2p_sq.qm"
)

qt_internal_add_resource(Sync-my-L2P "translation"
    PREFIX
        "/lang"
    BASE
        "lang"
    FILES
        ${translation_resource_files}
)


#### Keys ignored in scope 1:.:.:Sync-my-L2P.pro:<TRUE>:
# OTHER_FILES = "Sync-my-L2P.icns" "README.md" "magnifier.ico" "LICENSE" ".gitignore" "$$PWD/QsLogChanges.txt" "$$PWD/QsLogReadme.txt" "$$PWD/LICENSE.txt"
# RC_FILE = "icon.rc"
# TEMPLATE = "app"
# TRANSLATIONS = "lang/sync-my-l2p_de.ts" "lang/sync-my-l2p_en.ts" "lang/sync-my-l2p_lb.ts" "lang/sync-my-l2p_sq.ts"

## Scopes:
#####################################################################

qt_internal_extend_target(Sync-my-L2P CONDITION (QT_MAJOR_VERSION GREATER 4)
    PUBLIC_LIBRARIES
        Qt::Widgets
    INCLUDE_DIRECTORIES
        ${QT_DIR}/include/QtWidgets
)

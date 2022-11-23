QT     += core gui network widgets xml
CONFIG += c++11

VERSION = "2.5.1"
VERSION_CODE = "20501"

TEMPLATE_FILES = include/version.h.template \
            gui/info.ui.template \
            windows/SyncMyMoodle.xml.template

template_compiler.input = TEMPLATE_FILES
template_compiler.output  = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}
#template_compiler.depends = ${QMAKE_FILE_IN} Sync-my-Moodle.pro
win32 {
    template_compiler.commands = powershell -Command \"(Get-Content -Encoding utf8 \\\"${QMAKE_FILE_IN}\\\").Replace(\\\"__PRODUCT_VERSION_CODE\\\",\\\"$$VERSION_CODE\\\").Replace(\\\"__PRODUCT_VERSION\\\",\\\"$$VERSION\\\") | Set-Content -Encoding utf8 -Path ${QMAKE_FILE_OUT}\"
}
unix {
    template_compiler.commands = sed 's/__PRODUCT_VERSION_CODE/$$VERSION_CODE/g' ${QMAKE_FILE_IN} | sed 's/__PRODUCT_VERSION/$$VERSION/g' > ${QMAKE_FILE_OUT}
}
template_compiler.CONFIG = target_predeps no_link
QMAKE_EXTRA_COMPILERS += template_compiler

macx {
    plistupdate.commands = /usr/libexec/PlistBuddy -c \"Add :CFBundleVersion string $$VERSION\" -c \"Add :CFBundleShortVersionString string $$VERSION\" -c \"Add :CFBundleName string Sync-my-Moodle\" -c \"Set :CFBundleIdentifier de.rwth-aachen.Sync-my-Moodle\" bin/Sync-my-Moodle.app/Contents/Info.plist
    QMAKE_EXTRA_TARGETS += plistupdate
    PRE_TARGETDEPS += plistupdate
}

TARGET = Sync-my-Moodle
TEMPLATE = app
DESTDIR = bin

SOURCES += \
    src/main.cpp \
    src/autoclosedialog.cpp \
    src/browser.cpp \
    src/filedownloader.cpp \
    src/info.cpp \
    src/l2pitemmodel.cpp \
    src/logger.cpp \
    src/login.cpp \
    src/logindialog.cpp \
    src/mymainwindow.cpp \
    src/mysortfilterproxymodel.cpp \
    src/options.cpp \
    src/parser.cpp \
    src/structureelement.cpp \
    src/utils.cpp

INCLUDEPATH += include/
HEADERS  += \
    include/clientId.h \
    include/autoclosedialog.h \
    include/browser.h \
    include/clientId.h \
    include/filedownloader.h \
    include/info.h \
    include/l2pitemmodel.h \
    include/logger.h \
    include/login.h \
    include/logindialog.h \
    include/mymainwindow.h \
    include/mysortfilterproxymodel.h \
    include/options.h \
    include/parser.h \
    include/structureelement.h \
    include/urls.h \
    include/utils.h \
    include/version.h

FORMS += \
    gui/autoclosedialog.ui \
    gui/browser.ui \
    gui/dateidownloader.ui \
    gui/info.ui \
    gui/logger.ui \
    gui/logindialog.ui \
    gui/message.ui \
    gui/mymainwindow.ui \
    gui/options.ui

TRANSLATIONS = lang/sync-my-moodle_de.ts \
               lang/sync-my-moodle_en.ts

RESOURCES += \
    icons/icons.qrc \
    lang/translation.qrc

RC_FILE = icon.rc

OTHER_FILES += \
    Sync-my-Moodle.icns \
    README.md \
    magnifier.ico \
    LICENSE \
    .gitignore

include(qslog/QsLog.pri)

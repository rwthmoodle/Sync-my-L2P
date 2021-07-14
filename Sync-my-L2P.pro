QT     += core gui network widgets xml
CONFIG += c++11

VERSION = "2.4.3"
VERSION_CODE = "20403"

TEMPLATE_FILES = include/version.h.template \
            gui/info.ui.template \
            windows/SyncMyL2P.xml.template

template_compiler.input = TEMPLATE_FILES
template_compiler.output  = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}
template_compiler.depends = ${QMAKE_FILE_IN} Sync-my-L2P.pro
win32|win64 {
    template_compiler.commands = powershell -Command \"(Get-Content -Encoding utf8 \\\"${QMAKE_FILE_IN}\\\").Replace(\\\"__PRODUCT_VERSION_CODE\\\",\\\"$$VERSION_CODE\\\").Replace(\\\"__PRODUCT_VERSION\\\",\\\"$$VERSION\\\") | Set-Content -Encoding utf8 -Path ${QMAKE_FILE_OUT}\"
}
unix {
    template_compiler.commands = sed 's/__PRODUCT_VERSION_CODE/$$VERSION_CODE/g' ${QMAKE_FILE_IN} | sed 's/__PRODUCT_VERSION/$$VERSION/g' > ${QMAKE_FILE_OUT}
}
template_compiler.CONFIG = target_predeps no_link
QMAKE_EXTRA_COMPILERS += template_compiler

macx {
    plistupdate.commands = /usr/libexec/PlistBuddy -c \"Add :CFBundleVersion string $$VERSION\" -c \"Add :CFBundleShortVersionString string $$VERSION\" -c \"Add :CFBundleName string Sync-my-L2P\" -c \"Set :CFBundleIdentifier de.rwth-aachen.Sync-my-L2P\" bin/Sync-my-L2P.app/Contents/Info.plist
    QMAKE_EXTRA_TARGETS += plistupdate
    PRE_TARGETDEPS += plistupdate
}

TARGET = Sync-my-L2P
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
    src/message.cpp \
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
    include/message.h \
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

TRANSLATIONS = lang/sync-my-l2p_de.ts \
               lang/sync-my-l2p_en.ts \
               lang/sync-my-l2p_lb.ts \
               lang/sync-my-l2p_sq.ts

RESOURCES += \
    icons/icons.qrc \
    lang/translation.qrc

RC_FILE = icon.rc

OTHER_FILES += \
    Sync-my-L2P.icns \
    README.md \
    magnifier.ico \
    LICENSE \
    .gitignore

include(qslog/QsLog.pri)

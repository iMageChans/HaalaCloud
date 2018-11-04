#-------------------------------------------------
#
# Project created by QtCreator 2018-08-29T16:11:31
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = HaalaCloud
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/Widget/mainwindow.cpp \
        src/Widget/login.cpp \
        src/Widget/detail.cpp \
        src/Widget/content.cpp \
        src/Widget/mitcontent.cpp \
    src/Widget/trash.cpp \
    src/Widget/progresslist.cpp \
    src/Widget/clearlist.cpp \
    src/Delegate/progressbardelegate.cpp \
    src/model/progressmodel.cpp \
    src/model/detailmodel.cpp \
    src/Widget/filesheaderview.cpp \
    src/Delegate/checkboxdelegate.cpp \
    src/model/sortfilterproxymodel.cpp \
    src/util/tool.cpp \
    src/util/request.cpp \
    src/util/configsetting.cpp \
    src/model/usermodel.cpp \
    src/Widget/messagebox.cpp \
    src/model/filesmodel.cpp \
    src/model/download.cpp \
    src/Delegate/tableviewdelegate.cpp \
    src/util/filedownloadthread.cpp \
    src/model/upload.cpp \
    src/util/filesplitutils.cpp

HEADERS += \
        src/Widget/mainwindow.h \
        src/Widget/login.h \
        src/Widget/detail.h \
        src/Widget/content.h \
        src/Widget/mitcontent.h \
    src/Widget/trash.h \
    src/Widget/progresslist.h \
    src/Widget/clearlist.h \
    src/Delegate/progressbardelegate.h \
    src/model/progressmodel.h \
    src/model/detailmodel.h \
    src/Widget/filesheaderview.h \
    src/Delegate/checkboxdelegate.h \
    src/model/sortfilterproxymodel.h \
    src/util/tool.h \
    src/util/request.h \
    src/util/configsetting.h \
    src/model/usermodel.h \
    src/Widget/messagebox.h \
    src/model/filesmodel.h \
    src/model/download.h \
    src/Delegate/tableviewdelegate.h \
    src/util/filedownloadthread.h \
    src/model/upload.h \
    src/util/filesplitutils.h

FORMS += \
        src/Widget/mainwindow.ui \
        src/Widget/login.ui \
        src/Widget/detail.ui \
    src/Widget/trash.ui \
    src/Widget/progresslist.ui \
    src/Widget/clearlist.ui \
    src/Widget/messagebox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

DISTFILES +=

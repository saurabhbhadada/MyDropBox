#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T17:26:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDropBox
TEMPLATE = app


SOURCES += registerscreen.cpp\
        main.cpp\
        mainapp.cpp\
        ../../common/common.cpp\
        ../../ClientDBManager/ClientDBManager.cpp\
        ../../client/client.cpp \
        ../../sync/sync.cpp\
    userfiles.cpp \
    listwidget.cpp \
    fileinfo.cpp \
    sharedfileinfo.cpp

QMAKE_CXXFLAGS += -std=c++11

LIBS += -L/usr/lib -lssl -lcrypto -lpthread -ldl -lsqlite3

HEADERS  += registerscreen.h\
    mainapp.h \
    userfiles.h \
    listwidget.h \
    fileinfo.h \
    sharedfileinfo.h

FORMS    += registerscreen.ui\
    mainapp.ui \
    userfiles.ui \
    listwidget.ui \
    fileinfo.ui \
    sharedfileinfo.ui


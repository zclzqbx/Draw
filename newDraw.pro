#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T23:11:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newDraw
TEMPLATE = app


SOURCES += main.cpp\
        drawdlg.cpp \
    sinx.cpp \
    ex.cpp \
    nordx.cpp

HEADERS  += drawdlg.h \
    sinx.h \
    ex.h \
    nordx.h

FORMS    += drawdlg.ui \
    sinx.ui \
    ex.ui \
    nordx.ui

RESOURCES += \
    newDraw.qrc

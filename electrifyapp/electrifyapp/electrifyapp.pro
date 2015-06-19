#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T13:15:26
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXX = ccache g++

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = electrifyapp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    symmetryglwidget.cpp

HEADERS  += mainwindow.h \
    symmetryglwidget.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/engine -lSymmetryEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/engine -lSymmetryEngine
else:unix: LIBS += -L$$OUT_PWD/engine -lSymmetryEngine

QMAKE_INCDIR += /usr/local/include
INCLUDEPATH += $$OUT_PWD/engine/include
DEPENDPATH += $$DESTDIR/../../engine/src

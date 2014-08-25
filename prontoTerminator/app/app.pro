QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += debug_and_release build_all
unix:LIBS += -L../lib/QScintilla/Qt4Qt5 -lqscintilla2
win32:LIBS += -L../lib/QScintilla/Qt4Qt5/release -lqscintilla2
INCLUDEPATH += ../lib/QScintilla/Qt4Qt5
DEPENDPATH  += ../lib/QScintilla/Qt4Qt5
CONFIG(debug, debug|release){
    DESTDIR = ../bin/debug
    OBJECTS_DIR = ../bin/debug
    MOC_DIR = ../bin/debug
    TARGET= PTDebug
}

CONFIG(release, debug|release){
    DESTDIR = ../bin/release
    OBJECTS_DIR = ../bin/release
    MOC_DIR = ../bin/release
    TARGET= PT
}


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

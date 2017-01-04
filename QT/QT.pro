#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T15:34:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treedialog.cpp \
    actuator.cpp \
    BaseSymbol.cpp \
    CheckTable.cpp \
    CodeGenerator.cpp \
    InterCode.cpp \
    LexAnalysis.cpp \
    Parse.cpp \
    SimpleSymbol.cpp

HEADERS  += mainwindow.h \
    treedialog.h \
    actuator.h \
    BaseSymbol.h \
    CheckTable.h \
    CodeGenerator.h \
    Global.h \
    InterCode.h \
    LexAnalysis.h \
    Parse.h \
    SimpleSymbol.h

FORMS    += mainwindow.ui \
    tree.ui

DISTFILES += \
    console.lex \
    grammar.txt

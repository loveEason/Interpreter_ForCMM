TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BaseSymbol.cpp \
    CheckTable.cpp \
    CodeGenerator.cpp \
    InterCode.cpp \
    LexAnalysis.cpp \
    Parse.cpp \
    SimpleSymbol.cpp \
    actuator.cpp

HEADERS += \
    BaseSymbol.h \
    CheckTable.h \
    CodeGenerator.h \
    Global.h \
    InterCode.h \
    LexAnalysis.h \
    Parse.h \
    SimpleSymbol.h \
    actuator.h

DISTFILES += \
    console.lex \
    grammar.txt \
    ../build-untitled-Desktop_Qt_5_7_0_MinGW_32bit-Debug/grammar.txt
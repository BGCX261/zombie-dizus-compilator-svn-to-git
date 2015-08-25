LIBS += -lboost_program_options
QT += core \
    gui
TARGET = compilador_novo
CONFIG += console \
    app_bundle
TEMPLATE = app
OBJECTS_DIR = build
MOC_DIR = build
DESTDIR = build
SOURCES += main.cpp \
    l09.cpp \
    filereader.cpp \
    filewriter.cpp \
    sintatico/sintatico.cpp \
    sintatico/producoes.cpp \
    sintatico/errosintatico.cpp \
    lexico/analizadorlexico.cpp \
    lexico/filemanager.cpp \
    lexico/state.cpp
OTHER_FILES += 
HEADERS += l09.h \
    filereader.h \
    filewriter.h \
    sintatico/sintatico.h \
    sintatico/producoes.h \
    sintatico/errosintatico.h \
    lexico/analizadorlexico.h \
    lexico/enumTypes.h \
    lexico/filemanager.h \
    lexico/state.h \
    sintatico/hashnode.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    bloco.c \
    tiro.c

LIBS += /usr/local/lib/libkfup.a
INCLUDEPATH += /usr/local/lib/

LIBS += /usr/lib/libX11.so
INCLUDEPATH += /usr/lib/

HEADERS += \
    bloco.h \
    desenhos.h \
    tiro.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
    src/kip.c \
    test/kip_test.c

HEADERS += \
    src/kip.h \
    test/kip_test.h


LIBS += /usr/lib/libX11.so
INCLUDEPATH += /usr/lib/

OTHER_FILES +=

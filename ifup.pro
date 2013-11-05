TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
    src/kip.c \
    test/kip_test.c \
    exemplos/jogos/rpg/rpg.c \
    exemplos/jogos/nave/nave.c

HEADERS += \
    src/kip.h \
    test/kip_test.h \
    exemplos/jogos/rpg/rpg.h \
    exemplos/jogos/nave/nave.h


LIBS += /usr/lib/libX11.so
INCLUDEPATH += /usr/lib/

OTHER_FILES +=

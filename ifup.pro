TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
    src/kip.c \
    test/kip_test.c \
    exemplos/jogos/rpg.c \
    exemplos/jogos/nave.c \
    exemplos/basico/basic_texto.c \
    exemplos/basico/basic_pegar_evento.c \
    exemplos/basico/basic_cores.c \
    exemplos/jogos/teste_digitacao.c \
    exemplos/jogos/homem_mola.c \
    exemplos/jogos/bicicleta.c

HEADERS += \
    src/kip.h \
    test/kip_test.h


LIBS += /usr/lib/libX11.so
INCLUDEPATH += /usr/lib/

OTHER_FILES +=

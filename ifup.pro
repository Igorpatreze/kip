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
    exemplos/jogos/bicicleta.c \
    exemplos/recursao/fractais.c \
    exemplos/lab.cpp \
    tkip/tkip.c

HEADERS += \
    src/kip.h \
    test/kip_test.h \
    tkip/tkip.h


#LIBS += /usr/lib/x86_64-linux-gnu/libX11.so
LIBS += -L/usr/lib -lX11
#INCLUDEPATH += /usr/lib/x86_64-linux-gnu/
INCLUDEPATH += /usr/lib/

#OTHER_FILES +=

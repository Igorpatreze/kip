====
kip
====

Repositório da biblioteca gráfica kip para ensino de FUP.
kip é um acrônimo para Knoledge is power, para simbolizar 
o poder do aprendizado.

O código fonte está na pasta src. 

Foi projetada para linux. As dependências são 

As dependências são o libX11-dev e mpg123.

Instalação
==========
Você só precisa instalar o libX11-dev e utilizar o arquivo kip.c e kip.h
como biblioteca local. Mas se quiser realmente instalar na máquina, 
primeiro instale todas as dependências::

    sudo apt-get update
    sudo apt-get install libX11-dev curl wget mpg123 git

Clone o repositório em uma pasta local e instale com os seguintes comandos::
    git clone https://github.com/senapk/kip
    cd kip/src/
    make
    make install

Ou apenas execute o script::
    curl https://raw.github.com/senapk/kfup/master/kfup_install.sh | sh;


Exemplos
========

Para ver exemplos basta entrar na pasta exemplos.

Tutoriais
=========

Os tutoriais podem ser encontrados na pasta tutoriais.

Compilando
==========
Compile pelo terminal ::

    gccx main.c -o main

O gccx é o gcc normal mais os parâmetros da biblioteca.

Para compilar pelo Geany::

    Ir em:
    Contruir / Definir Comandos de Construção/
    Em Build e em Compile substitua gcc por gccx

Para utilizar o Codeblocks ou o QtCreator você precisa descobrir onde fica a biblioteca do
X11 que você instalou na sua máquina::
    No terminal digite
    locate libX11.so | head -1
    O path que aparecer é o path da lib X11


Para compilar pelo Codeblocks::

    Settings, Compiler, Linker
    Adicionar o path para os dois arquivos:
    /usr/local/lib/libkip.a
    O path do libX11.so

Para compilar pelo QtCreator::

    Crie um projeto Plain C
    Abra o .pro e adicione as sequintes linhas:

    LIBS += /usr/local/lib/libkip.a
    INCLUDEPATH += /usr/local/lib/

    LIBS += O path do libX11.so
    INCLUDEPATH += A pasta do libX11.so

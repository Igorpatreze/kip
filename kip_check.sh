#!/bin/bash
cd /tmp
#rm -f homem_mola.c
rm -rf goku.tgz goku
#wget https://raw.github.com/senapk/kfup/master/exemplos/jogos/homem_mola.c 
wget https://raw.github.com/senapk/kfup/master/zip/goku.tgz 
tar -xzvf goku.tgz
cd goku
make
./main
#gccx homem_mola.c -o exemplo_kfup
#./exemplo_kfup

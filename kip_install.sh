#!/bin/bash
cd /tmp/

cd kfup_src
./install.sh

echo "Se tudo deu certo, soltaremos hadoukens com o Goku!!"
echo "Falta pouco"
echo "Ta quase"
curl https://raw.github.com/senapk/kfup/master/kfup_check.sh | sh 

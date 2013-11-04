/*
 * Exemplo 2
 */

#include <kip.h>



int main()
{
    k_open(1000,600,"nome");

    int botao;
    while(1){
        k_write(0, 0, "clique com o botao esquerdo do mouse para lancar");
        k_write(0, 1, "uma nova musica e com o direito para parar");

        botao = k_wait();
        if(botao == CLICK_LEFT)
            k_mp3_play("tron.mp3");
        if(botao == CLICK_RIGHT)
            k_mp3_stop("tron.mp3");
    }

    k_mp3_stop("tron.mp3");

    return 0;
}






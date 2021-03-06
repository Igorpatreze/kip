/*
   Exemplo 2 */
#include "../../src/kip.h"

int main_basic_evento()
{
    // Open a new window for drawing.
    k_open(1000, 500, "Exemplo 2");
    k_block(20);
    int cont = 0;
    while (1)
    {
        int c = (int)' ';
        k_clear('K');
        // se tiver alguma tecla pressionada, pegue e guarde o caractere em c
        c = k_peek();
        // fazendo o contador andar
        k_color('g');
        kenv_begin();
            k_rotate(45);
            k_zoom(3,3);
            k_write(5 + (cont++)/5.0, 11, "#");
        kenv_end();
        // imprimindo o número de contagem
        k_color('r');
        k_write(5, 13, "Contador %d", cont);

        // imprimindo qual o inteiro correpondente a tecla pressionada
        k_color('W');
        k_write(5, 15, "Numero da ultima tecla  %d", c);


        k_color('Y');
        k_write(5, 17, "Digite");
        k_color('W');
        k_write(12, 17, "q ");
        k_color('Y');
        k_write(14, 17, "para sair!");

        k_flush();
        k_sleep(100);
        // Quit if it is the letter q.
        if (c == 'q')
            break;
    }

    return 0;
}

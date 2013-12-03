/*
 * Exemplo de uso do dfx
 */
#include "../../src/kip.h"

int main_texto()
{

    k_open(1600, 1200, "Primeiro teste ");
    k_block(20);
    k_clear('w');               // pinta o background com a nova cor

    k_color('K');
    k_zoom(3, 4);

    k_write(0, 1, "Caracteres imprimiveis\n");



    k_zoom(2, 3);
    k_color('b');
    k_write(0, 4, "Letras e Numeros");

    k_zoom(2, 2);
    k_color('K');

    k_write(0, 5, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    k_write(0, 6, "abcdefghijklmnopqrstuvwxyz");
    k_write(0, 7, "0123456789\n");

    k_color('b');

    k_zoom(2, 4);

    k_color('b');
    k_zoom(2, 2);

    int i;
    for (i = 33; i < 80; i++)
    {
        k_write(i - 33, 10, "%c", i);
    }
    for (i = 81; i <= 126; i++)
    {
        k_write(i - 81, 11, "%c", i);
    }

    k_color('b');
    k_zoom(4, 4);
    k_write(0, 12, "Muito Grande");

    k_zoom(3, 3);
    k_write(0, 14, "Grande");
    k_zoom(2, 2);
    k_write(0, 16, "Medio");
    k_zoom(1, 1);
    k_write(0, 17, "Pequeno");

    k_wait();

    return 0;
}

/*
 * Exemplo de cores básicas
 */
#include "../../src/kip.h"
#include <string.h>

int main_cores()
{
    k_open(1000, 500, "Primeiro teste");
    fmt_block(50);
    k_clear('w');               // pinta o fundo de branco
    fmt_zoom(5, 5);
    fmt_rotate(-15);
    const char *cores = k_info().colors;
    int i;
    int t = strlen(cores);
    for (i = 0; i < t; i++)
    {
        fmt_color(cores[i]);
        k_plot(i, 2);

        fmt_color('K');
        k_write(i, 1, "%c", cores[i]);
    }

    k_wait();
    return 1;
}

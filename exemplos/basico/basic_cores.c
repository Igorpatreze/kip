/*
 * Exemplo de cores básicas
 */
#include <kip.h>
#include <string.h>

int main_cores()
{
    k_open(1000, 500, "Primeiro teste");
    k_block(50);
    k_clear('w');               // pinta o fundo de branco
    kf_zoom(5, 5);
    kf_rotate(-15);
    const char *cores = k_info().colors;
    int i;
    int t = strlen(cores);
    for (i = 0; i < t; i++)
    {
        k_color(cores[i]);
        k_plot(i, 2);

        k_color('K');
        k_write(i, 1, "%c", cores[i]);
    }

    k_wait();
    return 1;
}

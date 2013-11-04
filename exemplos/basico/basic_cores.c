/*
 * Exemplo de cores básicas
 */
#include <kip.h>
#include <string.h>

int main()
{
    k_open(1000, 500, "Primeiro teste");
    k_block(50);
    k_clear('w');               // pinta o fundo de branco
    f_zoom(5, 5);
    f_rotate(-15);
    const char *cores = k_env().color_list;
    int i;
    int t = strlen(cores);
    for (i = 0; i < t; i++)
    {
        k_color(cores[i]);
        k_plot(i, 2, 0);

        k_color('K');
        k_write(i, 1.2, "%c", cores[i]);
    }

    k_wait();
}

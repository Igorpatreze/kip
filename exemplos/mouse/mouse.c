/* 
 * Exemplo 2
 * Como pegar eventos de mouse
 */

#include <kip.h>

int main()
{
    k_open(800, 600, "nome ");

    k_write(1, 5, "Clique na tela\n");
    while (1)
    {
        if (k_event_waiting())
        {
            float x, y;
            int botao;
            botao = k_wait();
            x = k_xpos();
            y = k_ypos();

            k_write(x, y, "%d", botao);

        }
    }

    return 0;
}

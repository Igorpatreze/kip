/*
 * Exemplo 2
 * Como pegar eventos de mouse e teclado
 */

#include <kip.h>

int main()
{
    k_open(800,600,"nome  ");
    f_zoom(1,1);
    k_block(10);
    k_write(0, 5, "Clique na tela com o mouse ou digite uma tecla\n\n");
    int p = 6;
    while(1)
    {
        if(k_event_waiting())
        {
            int key = k_wait();
            if(key >0 && key < 6)
                k_write(0, p++, "Evento de Mouse  , clique: %d\n",key);
            else
                k_write(0, p++, "Evento de Teclado, tecla : %c\n",key);
        int x = k_xpos();
        int y = k_ypos();
        k_write(0, p++, " Posicao x:%d, y:%d\n",x,y);
        }
    }


return 0;
}






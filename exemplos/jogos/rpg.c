#include "../../src/kip.h"

void show_heroi(int x, int y, int xflip, int rot)
{
    const char heroi[10][10]={
        {"          "},
        {"   yyyy   "},
        {"  yg gy   "},
        {"  yrrr y  "},
        {"    b   y "},
        {"ccccbccccc"},
        {"   yby    "},
        {"  yyyyy   "},
        {"  yyyyyy  "},
        {"   w  w   "}
    };

    kenv_set((ks_env){xflip,0,4,4,rot, 'w', 40});
    k_draw(x, y, &(heroi[0][0]),10,10);
}

int main_rpg()
{
    k_open(1000, 700, "Rpg");
    k_block(40);
    show_heroi(10,10,0,0);
    int i;
    for(i = 0; i <= 360; i+=30)
    {
        k_clear('K');
        show_heroi(10,10,0,i);
        k_sleep(100);
    }
    k_wait();
    return 0;
}

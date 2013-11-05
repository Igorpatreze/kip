#include "rpg.h"
#include "../../../src/kip.h"

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

    kf_set('i',(ks_fmt){0,0,4,4,rot});
    k_draw(x, y, &(heroi[10][10]),10,10);
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
        k_sleep(50);
    }
    k_wait();
    return 0;
}

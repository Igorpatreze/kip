#include "../../src/kip.h"

typedef struct{
    float x, y, rot;
}bike;

void bicicleta(bike *b)
{
    int raio = 15;
    int base = base = 10;
    int lado = 40;

    pen_fix(b->x*fmt_get()->block, b->y*fmt_get()->block);
    pen_up();
    pen_goto(-lado, base);
    pen_fd(raio);
    pen_down();
    pen_curve(-lado, base, 360, 40);

    pen_goto( 30, 10);

    pen_goto(30, 10);
    pen_curve( 40, 10, 360, 40);

    //aros
    pen_up();
    pen_goto(-40,10);
    pen_down();

    int i;
    for(i = 0; i<6;i++ )
    {
        pen_seth(i*60 + b->rot);
        pen_fd(10);
        pen_bk(10);
    }
    pen_unfix();
}

int main_bike()
{
    k_open(800,600, "Bike");
    bike b;
    b.x = 200;
    b.y = 300;
    b.rot = 15;
    bicicleta(&b);
    k_wait();
    return 0;
}

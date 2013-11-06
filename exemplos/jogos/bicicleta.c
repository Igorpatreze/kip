#include "../../src/kip.h"

typedef struct{
    float x, y, rot;
}bike;

void bicicleta(bike *b)
{
    kp_fix(b->x*k_info().block, b->y*k_info().block);
    kp_up();
    kp_goto(-30, 10);
    kp_down();
    kp_arc(-40, 10, 360, 40);

    kp_goto( 30, 10);

    kp_goto(30, 10);
    kp_arc( 40, 10, 360, 40);

    //aros
    kp_up();
    kp_goto(-40,10);
    kp_down();

    int i;
    for(i = 0; i<6;i++ )
    {
        kp_seth(i*60 + b->rot);
        kp_fd(10);
        kp_bk(10);
    }





    kp_unfix();
}

int main()
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

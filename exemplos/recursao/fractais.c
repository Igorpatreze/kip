#include "../../src/kip.h"
#include <math.h>
void rtri(int nivel, double x, double y, double r)
{
    if(r<3)
        return;

    const char * cores = k_info().colors;

    k_color(cores[nivel]);
    k_polig(x,y,'s',r,3,0);
    k_sleep(1);
    double a = r/4;
    double b = (r/4)*tan(k_PI/6);

    rtri(nivel + 1, x-a,y+b,r/2);
    rtri(nivel + 1, x+a,y+b,r/2);
    rtri(nivel + 1, x,y-2*b,r/2);
}

void frac_square(int step, int x, int y, int side)
{
    const char * cores = k_info().colors;

    if(step > 8)
        return;

    k_color(cores[step+3]);
    k_square(x,y,side,0);

    frac_square(step +1, x-side/2, y-side/2, side/2.3);
    frac_square(step +1, x-side/2, y+side/2, side/2.3);
    frac_square(step +1, x+side/2, y-side/2, side/2.3);
    frac_square(step +1, x+side/2, y+side/2, side/2.3);
}

void frac_polig(int x, int y, int r){
    if(r<1)
        return;
    k_polig(x,y,'r',r, 40,0);

    frac_polig(x+r, y, r/2.8);
    frac_polig(x+r*cos(k_PI/3)  , y-r*sin(k_PI/3),   r/2.8);
    frac_polig(x+r*cos(2*k_PI/3), y-r*sin(2*k_PI/3), r/2.8);
    frac_polig(x+r*cos(3*k_PI/3), y-r*sin(3*k_PI/3), r/2.8);
    frac_polig(x+r*cos(4*k_PI/3), y-r*sin(4*k_PI/3), r/2.8);
    frac_polig(x+r*cos(5*k_PI/3), y-r*sin(5*k_PI/3), r/2.8);
}



int main_fractais()
{
    k_open(1000, 700, "oi");
    rtri(0, 250, 200, 300);
    frac_square(0, 800, 200, 200);
    frac_polig(400, 500,100);
    k_wait();
    return 0;
}

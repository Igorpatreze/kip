/*
* Exemplo 2
*/
#include <stdio.h>
#include "../../../src/kip.h"
#include <math.h>

//eu que fiz esse daqui
char nave[][10]={
{"    kk    "},
{"    kk    "},
{"    kk    "},
{" K  kk  K "},
{" K  kk  K "},
{"  KgkkgK  "},
{"   kkkk   "},
{" kkkkkkkk "},
{"KKKKKKKKKK"},
{"    rr    "}};

float x, y, vx, vy;
float angulo;
float speed;

int main_nave()
{
    k_open(800,600,"nome");
    k_block(1);
    k_clear('w');
    x = 300;
    y = 300;
    vx = 0, vy =0;
    speed = 1;
    angulo = 0;
    int c;

    while(1){
        k_clear('w');
        if(k_event_waiting())
        {
            c = k_wait();
            if(c == KEY_LEFT)
                angulo += 30;
            if(c == KEY_RIGHT)
                angulo -= 30;
            if(c == KEY_UP)
            {
                double ang = km_deg2rad(angulo);
                vx += cos(ang)*3;
                vy -= sin(ang)*3;
            }
        }
        x += vx;
        y += vy;

        kf_set('i',(ks_fmt){0,0,3,3,angulo-90});
        k_draw(x,y,&nave[0][0],10,10);

        k_sleep(100);
    }
    k_wait();

    return 0;
}






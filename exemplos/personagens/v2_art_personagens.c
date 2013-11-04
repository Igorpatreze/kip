/*
* Exemplo 2
*/
#include <stdio.h>
#include <kip.h>
#include <math.h>

//eu que fiz esse daqui
char nave[][10]={
{"    kk    "},
{"    kk    "},
{"    kk    "},
{"    kk    "},
{"    kk    "},
{"   gkkg   "},
{"   kkkk   "},
{" kkkkkkkk "},
{"kkkkkkkkkk"},
{"    rr    "}};

float x, y, vx, vy;
float angulo;
float speed;

int main()
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
            if(c == d_k_left)
                angulo += 30;
            if(c == d_k_right)
                angulo -= 30;
            if(c == d_k_up)
            {
                double ang = ki_DEG2RAD(angulo);
                vx += cos(ang)*3;
                vy -= sin(ang)*3;
            }
        }
        x += vx;
        y += vy;

        f_zoom(3,3);
        f_rotate(angulo - 90);
        k_draw(x,y,&(nave[0][0]),10,10);
        f_reset();

        k_sleep(100);
    }
    k_wait();

    return 0;
}






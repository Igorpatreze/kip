#include "../../src/kip.h"
#include <math.h>

typedef struct {
    float x, y, direcao, vx, vy;
}Nave;

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

void nave_draw(float x, float y, float rotate)
{
    char *vet = &(nave[0][0]);
    fmt_begin();
        fmt_zoom(4,4);
        fmt_rotate(rotate - 90);
        k_draw(x, y, vet, 10,10);
    fmt_end();
}
#define NBALAS 500

int main_nave()
{
    Nave cr = {100, 100, 0, 5, 5};
    Nave balas[NBALAS];
    int  bind = -1;
    k_open(1000, 700, "oi");
    fmt_block(1);
    fmt_zoom(4,4);

    while(1)
    {
        k_clear('w');
        char c = k_peek();
        if(c != 0)
        {
            if(c == KEY_LEFT)
                cr.direcao += 30;
            if(c == KEY_RIGHT)
                cr.direcao -= 30;
            if(c == KEY_UP)
            {
                float P = 5;
                cr.vx += P*cos(km_deg2rad(cr.direcao));
                cr.vy -= P*sin(km_deg2rad(cr.direcao));
            }
            if(c == ' ')
            {
                if(bind < NBALAS-1)
                {
                    bind++;
                    balas[bind].x = cr.x+10;
                    balas[bind].y = cr.y+10;
                    int vb = 15;
                    balas[bind].vx = vb*cos(km_deg2rad(cr.direcao));
                    balas[bind].vy = -vb*sin(km_deg2rad(cr.direcao));
                }
            }
        }
        cr.x += cr.vx;
        cr.y += cr.vy;


        int i;

        for(i = 0; i <= bind; i++)
        {
            balas[i].x += balas[i].vx;
            balas[i].y += balas[i].vy;
            k_write(balas[i].x, balas[i].y, "*");
        }
        nave_draw(cr.x,cr.y,cr.direcao);
        k_sleep(50);
    }
    k_wait();
    return 0;
}


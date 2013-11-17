#include "kip_test.h"
#include "../src/kip.h"
#include <string.h>

void tree(int tam){
    int dec = 20;
    if (tam > 5){
        k_set_color('B');
        pen_fd(tam);
        pen_rt(20);
        tree(tam-dec);

        pen_lt(40);
        tree(tam-dec);

        pen_rt(20);
        k_set_color('K');
        pen_bk(tam);
    }
}
void espiral(int tam)
{

    if(tam<10)
        return;

    pen_fd(tam);
    pen_rt(90);
    espiral(tam-10);
}


void alterna(int *v, int sup, int inf, int *inc)
{
        if( ((*inc > 0) && ((*v + *inc) > sup)) ||
            ((*inc < 0) && ((*v + *inc) < inf)) )
            *inc = -1 * *inc;
        *v = *v + *inc;
}


void boneco( int x, int y){
    static int pe = 0;
    static int high;
    static int size;
    static int init = 1;
    if(init == 1)
    {
        init = 0;
        high = km_rand()%40;
        size = km_rand()%40;
    }
    static int inc = 2;
    alterna(&high, size, 0, &inc );
    pen_fix(x,y + high);
    pen_up();
    pen_goto(0,-20);
    pen_down();
    pen_seth(270);
    pen_fd(50);
    pen_lt(45);
    pen_fd(20);
    pen_bk(20);
    pen_rt(90);
    pen_fd(20);
    pen_seth(180);//pe
    pe += 5;
    pen_rt(pe%45);
    pen_fd(10);
    pen_up();
    pen_goto(0,0);


        pen_unfix();
}

void anda(int t){
    if(t<5)
        return;
    pen_fd(t);
    pen_lt(90);
    anda(t-5);
}

void recpol (double ang, int tam, int qtd){
    if(qtd == 0)
        return;
    pen_fd(tam);
    pen_lt(ang);
    recpol(ang, tam, qtd-1);
    k_set_color('r');
    pen_rt(ang);
    pen_bk(tam);
}
void poligon( int nlados ){
    double ang = 360/nlados;
    recpol(ang, 50, nlados );
}

void kduck_teste1()
{
    k_open(800,600,"oi");
    pen_setd(0);
    while(1)
    {
        boneco(100,100);

        boneco(200,200);
        k_sleep(50);
        k_clear('w');
    }
}

void matriz(int x, int y){
    int i;
    for(i=0;i<=y; i++)
        k_line(0, i, x, i);
    for(i=0;i<=x; i++)
        k_line(i, 0, i, y);
}

void matriz2(int x, int y)
{
    k_clear('W');
    k_set_color('k');
    int i, j;
    for(i = 0; i < y; i++)
        for(j = 0; j < x; j++)
        {
            k_set_color('w');
            k_plot(j,i);
            k_set_color('r');
            k_square(j+0.1,i+0.1,k_env_get()->block *0.8, 1);
        }
}
void kip_test_sol(){
    k_open(800,600, "oi");
    pen_setd(0);
    int i;
    for (i=0;i<4000;i+=20){
        k_clear('K');
        k_set_rotate(i);
        pen_fix(400,300);
        pen_up();
        pen_fd(50+i/20);
        pen_down();
        pen_curve(0,0 , -i, 30);
        k_sleep(100);
    }
    k_wait();
}

void kip_test_polig(){
    k_open(800, 600, "oi");
    k_set_block(1);
    k_polig(200,200,'r', 100, 4, 1);
    k_set_color('r');
    k_polig(200,200,'s', 100, 4, 1);
    k_wait();
}

void kip_test_cores(){
        k_open(1000,500,"Primeiro teste");
        k_set_block(50);
        k_clear('w');//pinta o fundo de branco
        k_set_zoom(5,5);
        k_set_rotate(0);
        const char *cores = k_info().colors;
        int i;
        int t = strlen(cores);
        for( i = 0; i < t; i++)
        {
            k_set_color(cores[i]);
            k_plot(i, 2);

            k_set_color('K');
            k_set_rotate(0);
            k_write(i, 1, "%c", cores[i]);
        }

        k_wait();
}
void kip_teste1()
{
    k_open(800,600,"oi");
    k_set_block(40);
    matriz2(15,15);
    k_wait();
}

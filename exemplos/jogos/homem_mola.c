#include <math.h>
#include "../../src/kip.h"

#define DCHAO 30

struct bola_{
    float x;
    float y;
    float xf;
    float yf;
    float vy;
    float vx;
    char e;
    char ef;
    int pousar;
    int concentrar;
};
typedef struct bola_ bola;

bola b;

int xjanela;
int yjanela;

int ychao;

void desenhar_bolinha(){
    if(b.x != b.xf || b.y != b.yf || b.concentrar==2){
        k_color('K');
        k_write(b.x, b.y, "%c",b.e);

        k_color('W');
        k_write(b.xf, b.yf, "%c",b.ef);
    }
}

void dretangulo(int x, int y, int l, int p){
    k_line(x  ,  y, x +l , y);
    k_line(x  ,y+p, x +l , y+p);

    k_line(x  ,  y, x  , y+p);
    k_line(x +l ,y, x +l , y+p);

}

void desenhar_chao(){
    dretangulo(DCHAO,DCHAO,xjanela-2*DCHAO,yjanela-2*DCHAO);
}

void init(){
    xjanela=800;
    yjanela=600;
    b.x = DCHAO+10;
    b.y = DCHAO+10;
    b.e = 'O';
    b.xf = b.x;
    b.yf = b.y;
    b.ef = 'O';
    b.vy = 0;
    b.vx = 3;
    ychao = yjanela - DCHAO;
    b.pousar = 0;
    b.concentrar =0;

    k_open(xjanela,yjanela, "bolinha");
    k_block(1);
}

void gravidade(){
    b.vy += 1;
}

void next_bola(){
    b.yf = b.y + b.vy;

    b.xf = b.x + b.vx;

    if(fabs(b.vy)>1 || fabs(b.vx)>1)
        b.concentrar=0;
    if(b.vy<0)
        b.pousar=0;

}

void consolidar(){
    b.x = b.xf;
    b.y = b.yf;
    b.e = b.ef;
    if(b.concentrar==2)
        b.concentrar = 1;
}

void colisao(){

    //chao
    if(b.yf + 20 > ychao){
        b.yf = ychao -20;
        b.vx *= 0.90;
        b.vy *= -0.7;
        if (b.pousar==1){
            b.vy = 0;
            b.vx = 0;
            b.pousar = 0;
        }
    }

    if(b.yf < DCHAO){
        b.yf = DCHAO;
        b.vy *= -1;
    }

    if(b.xf < DCHAO){
        b.xf = DCHAO;
        b.vx *= -1;
    }
    if(b.xf +20 > xjanela -DCHAO){
        b.xf = xjanela -DCHAO -20;
        b.vx *= -1;
    }
}

void teclado(){
    int c = k_peek();
    if(c){
        switch(c){
            case KEY_RIGHT:
                if(b.vx < 24)
                    b.vx+=6;
                break;
            case KEY_LEFT:
                if(b.vx > -24)
                    b.vx-=6;
                break;
            case KEY_UP:
                b.vy -= 20;
                break;
            case KEY_DOWN:
                if((int)b.y + 25 > ychao){
                    b.concentrar = 2;
                }else{
                    b.vy = +50;
                    b.pousar = 1;
                }
                break;
            case ' ':
                if((int)b.y + 25 > ychao){
                    b.vy = -20;
                    if (b.concentrar)
                        b.vy = -50;
                }
                break;

        }
    }
}

void mudar_sprite(){
    if (b.concentrar){
        b.ef='M';
        return;
    }
    if (b.pousar){
        b.ef='V';
        return;
    }
    if(fabs(b.vx)>fabs(b.vy)){
        if(fabs(b.vx)<5)
            b.ef='O';
        else if(b.vx > 0)
            b.ef='>';
        else
            b.ef='<';
    }else{
        if(fabs(b.vy)<5)
            b.ef='O';
        else if(b.vy > 0)
            b.ef='!';
        else
            b.ef='A';
    }

}

void msg_texto(){
    kenv_begin();
        k_zoom(2,2);
        k_write(20,580,"Use os direcionais para mover e espaco para pular");
    kenv_end();
}

int main_mola(){
    init();
    msg_texto();
    while(1){
        //nexts
        gravidade();
        teclado();

        next_bola();
        colisao();
        mudar_sprite();
        //desenhos - Aqui o futuro já está certo
        desenhar_bolinha();
        desenhar_chao();

        consolidar();
        k_sleep(50);
        //canvas_clear();
    }
    k_wait();
    return 1;
}


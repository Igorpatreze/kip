#include <kfup.h>
#include "bloco.h"
#include <math.h>

Bloco bloco_init( int x, int y, char c, char cor, int existe){
    Bloco b;
    b.x = x;
    b.y = y;
    b.c = c;
    b.cor = cor;
    b.existe =existe;
    return b;
}

int bloco_colisao(Bloco A, Bloco B){
    int raio = 12;
    int cax = A.x + raio;
    int cay = A.y + raio;

    int cbx = B.x + raio;
    int cby = B.y + raio;

    if(sqrt( pow(cax-cbx,2) + pow(cay-cby,2))<2*raio)
        return 1;
    return 0;
}

//se nao encontrar retorna 0, se encontrar, retorna posicao
int bloco_colisao_vetor( Bloco A, Bloco B[], int tam, int *pos){
    int i;
    for(i=0;i<tam;i++){
        if( bloco_colisao(A, B[i]) && B[i].existe==1){
            *pos = i;
            return 1;
        }
    }
    return 0;
}

void bloco_pintar( Bloco b){
    if(b.existe==0)
        return;
    pen_pcw(b.x, b.y, b.cor, "%c", b.c);
}

void bloco_mover(Bloco *b, Direcao direcao, int fator){
    float vbase = 0.5;
    if(direcao == UP)
        b->vy += -vbase*fator;
    if(direcao == DOWN)
        b->vy += vbase*fator;
    if(direcao == LEFT)
        b->vx += -vbase*fator;
    if(direcao == RIGHT)
        b->vx += vbase*fator;
}

void bloco_update( Bloco *b){
    b->x += b->vx;
    if(b->x<0)
        b->x = 800 + b->x;
    if(b->x>800)
        b->x = 800 - b->x;

    b->y += b->vy;
    if(b->y<0)
        b->y = 600 + b->y;
    if(b->y>600)
        b->y = 600 - b->y;

    b->vx *= 0.9;
    b->vy *= 0.9;
}


Direcao bloco_pos_relativa(Bloco A, Bloco B)
{
    int dx = A.x - B.x;
    int dy = A.y - B.y;

    if(fabs(dx)>fabs(dy)){
        if(dx>0)
            return LEFT;
        else
            return RIGHT;
    }else{
        if(dy<0)
            return DOWN;
        else
            return UP;
    }
}

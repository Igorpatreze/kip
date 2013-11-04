#include "bloco.h"
#include "tiro.h"
#include <math.h>
#include <kfup.h>

char hadouken_desenho[]="\
                 yy \n\
y        cc    y    \n\
         cc   yy y  \n\
   y         y  y   \n\
    y               \n\
   y       yy       \n\
    y yy   y y      \n\
       y y  y       \n\
 c    y   y y     c \n\
  cc    y  y     c c\n\
  cc             c c\n\
     y y yy  y      \n\
         y   y      \n\
    y  y       y    \n\
  y    y     y      \n\
   yyy              \n\
   y y    c     y   \n\
    y    cc    y    \n\
yy                  \n\
   y           y  y ";


Tiro tiro_init( int x, int y, char c, char cor, int existe, int x0, int y0, char ct){
    Tiro t;
    t.b = bloco_init(x,y,c,cor,existe);
    t.x0 = x0;
    t.y0 = y0;
    t.cor = ct;
    return t;
}


//passa o tipo do tiro, a porcentagem de direcao entre -1 e +1 pra x e y
Tiro tiro_criar(int x0, int y0, FORCA tipo, float porc_x, float porc_y){
    Tiro t;
    char cor;
    if(tipo == FORTE)
        cor = 'r';
    else
        cor = 'b';
    t = tiro_init(x0,y0, 'o', cor,1, x0+10, y0+10, cor );
    t.tipo = tipo;
    float vel = 20*tipo;
    t.b.vx += vel * porc_x;
    t.b.vy += vel * porc_y;
    return t;
}

Tiro tiro_barra(Bloco goku){
    double porc_x = 0;
    double porc_y = 0;

    switch(goku.c){
    case '>':
        porc_x = 1;
        break;
    case '<':
        porc_x = -1;
        break;
    case 'A':
        porc_y = -1;
        break;
    case 'V':
        porc_y = 1;
        break;
    }
    Tiro t = tiro_criar(goku.x, goku.y, FORTE,porc_x,porc_y);
    return t;
}


Tiro tiro_mouse(Bloco goku, int botao, int xmouse, int ymouse){
    int xg = goku.x + 10, yg = goku.y + 10;

    int dx = - xg + xmouse;
    int dy = - yg + ymouse;

    float px = (dx)/(fabs(dx)+fabs(dy));
    float py = (dy)/(fabs(dx)+fabs(dy));
    Tiro t = tiro_criar(goku.x, goku.y, botao,px,py);
    return t;
}

void tiro_update(Tiro *t){
    if(t->b.existe == 1){
        t->b.x += t->b.vx;
        t->b.y += t->b.vy;
    }
}

void tiro_pintar(Tiro t){
    if(t.b.existe==1){
        Bloco b = t.b;
        pen_pix(b.x, b.y);
        font_zoom(1);
        pen_draw(hadouken_desenho);
        font_zoom(2);
        font_color(t.cor);
        pen_line(t.x0,t.y0,t.b.x+10,t.b.y+10);
    }
}

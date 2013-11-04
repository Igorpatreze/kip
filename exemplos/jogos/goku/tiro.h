#ifndef TIRO_H
#define TIRO_H

#include "bloco.h"

typedef struct{
    Bloco b;
    char cor;
    int x0,y0;
    int tipo;
} Tiro;

enum _forca{ FRACO=1, FORTE=3};
typedef enum _forca FORCA;

Tiro tiro_init( int x, int y, char c, char cor, int existe, int x0, int y0, char ct);


Tiro tiro_criar(int x0, int y0 ,FORCA tipo, float porc_x, float porc_y);


Tiro tiro_barra(Bloco goku);
Tiro tiro_mouse(Bloco goku, int botao, int xmouse, int ymouse);
void tiro_update(Tiro *t);
void tiro_pintar(Tiro t);

#endif // TIRO_H

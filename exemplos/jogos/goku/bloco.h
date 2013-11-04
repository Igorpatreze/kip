#ifndef BLOCO_H
#define BLOCO_H

typedef struct{
    float x, y;
    int existe;
    char c, cor;
    float vx, vy;
} Bloco;

enum _Direcao {UP=0, RIGHT,DOWN,LEFT};
typedef enum _Direcao Direcao;

Bloco bloco_init( int x, int y, char c, char cor, int existe);
int bloco_colisao(Bloco A, Bloco B);
int bloco_colisao_vetor(Bloco A, Bloco B[], int tam, int *pos);
void bloco_pintar( Bloco b);
void bloco_mover(Bloco *b, Direcao direcao, int fator);
void bloco_update( Bloco *b);
Direcao bloco_pos_relativa(Bloco A, Bloco B);

#endif // BLOCO_H

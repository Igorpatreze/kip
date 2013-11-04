/* Objetivo aqui: separar em arquivos
 * 1. coisas de bloco
 * 2. coisas de tiro
 * 3. coisas de jogo
 */


#include <kfup.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "tiro.h"
#include "bloco.h"
#include "desenhos.h"





enum _STATUS{CONTINUA=0, GANHOU, PERDEU };
typedef enum _STATUS STATUS;

#define n_postes 10

Bloco goku, destino, poste[n_postes], esfera_dragao;
Tiro hadouken;
int  __dificuldade;
void init(){
    canvas_open(800,600,"Goku, destrua todos!!");

}
void init_var()
{
    canvas_clear();
    pen_mcw(3,3,'W',"Seu objetivo eh destruir todos os P") ;
    pen_mcw(3,4,'g',"Fuja do ponto verde que te persegue");
    pen_mcw(3,5,'W',"Mate os brancos atirando hadoukens com o mouse");
    pen_mcw(3,7,'g',"Se o verde te pegar, todos os brancos renascem");
    pen_mcw(3,8,'W',"Se o branco te pegar, voce morre");
    pen_mcw(3,10,'W',"Com todos os brancos mortos, va ate a saida em vermelho");
    pen_mcw(3,11,'c',"Movimente-se com adws");
    pen_mcw(3,13,'w',"Digite:");
    pen_mcw(8,14,'g',"1 para facil");
    pen_mcw(8,15,'y',"2 para medio");
    pen_mcw(8,16,'Y',"3 para dificil");
    pen_mcw(8,17,'r',"4 para impossivel");
    pen_mcw(1,20,'r',"Se por acaso ficar preso, execute o jogo novamente");
    pen_mcw(1,21,'r',"Eh um bug macabro do gcc que nao vou corrigir");

    __dificuldade = -1;

    while(__dificuldade < 0 || __dificuldade >4 )
    {
        if(event_is_waiting()){
            __dificuldade = event_get()-'0';
        }
    }

    goku     = bloco_init(770,570,'>', 'y' ,1);
    destino  = bloco_init(0,0,'D','r',1);
    esfera_dragao   = bloco_init(100,100,'E','g', 1);
    hadouken = tiro_init (0,0, 'o','c',0,0,0,'r');
    int i;
    for(i=0;i<n_postes;i++){
        poste[i]   = bloco_init(util_rand()%600, rand()%400,'P', 'w' ,1 );
    }
}




void entrada(){
    if(event_is_waiting()){
        int evento;
        evento = event_get();
        int fator = 20;
        int xmouse, ymouse;
        switch(evento)
        {
        case 'd':
            bloco_mover(&goku, RIGHT, fator);
            goku.c = '>';
            break;
        case 's':
            bloco_mover(&goku, DOWN,fator);
            goku.c = 'V';
            break;
        case 'a':
            bloco_mover(&goku, LEFT,fator);
            goku.c = '<';
            break;
        case 'w':
            bloco_mover(&goku, UP,fator);
            goku.c = 'A';
            break;
        case ' ':
            hadouken = tiro_barra(goku);
            break;
        case 1:
        case 3:
            xmouse = event_get_pos_x();
            ymouse = event_get_pos_y();
            hadouken = tiro_mouse(goku,evento, xmouse, ymouse);
        }
    }
}


void update(){

    //PROCESSA INPUTS
    entrada();

    int j;
    for(j=0;j<n_postes;j++){
        bloco_mover(&poste[j],rand()%4,5);
        if(rand()%10<__dificuldade - 1){
            Direcao d = bloco_pos_relativa(poste[j],goku);
            bloco_mover(&poste[j],d,5);
        }
    }

    bloco_mover(&esfera_dragao, rand()%4, 10);
    if(rand()%10<__dificuldade+1){
        Direcao d = bloco_pos_relativa(esfera_dragao, goku);
        bloco_mover(&esfera_dragao,d, 10);
    }




    //UPDATES
    tiro_update(&hadouken);
    bloco_update(&goku);
    bloco_update(&esfera_dragao);
    int i;
    for(i=0;i<n_postes;i++)
        bloco_update(&poste[i]);

    //COLISOES
    //max e poste
    int pos;

    if (bloco_colisao(goku, esfera_dragao)){
        int i;
        for(i=0;i<n_postes;i++){
            poste[i].existe=1;
        }
        esfera_dragao   = bloco_init(rand()%800,rand()%600,'E', 'g', 1);
    }

    //hadouken e poste
    if(bloco_colisao_vetor(hadouken.b, poste, n_postes, &pos)){
        poste[pos].existe=0;
        if(hadouken.tipo == FORTE)
            hadouken.b.existe  =0;
    }
}

void pintar(){
    //Pintar goku
    bloco_pintar(goku);

    //Pintar outros blocos
    bloco_pintar(destino);
    bloco_pintar(esfera_dragao);

    //pintar hadouken
    tiro_pintar(hadouken);

    //pintar postes
    int i;
    for(i=0;i<n_postes;i++)
        bloco_pintar(poste[i]);
}
//se retorno ==1 entao ganhou, se retorno ==2 entao perdeu
STATUS game_over(){
    int temp;//inutil
    if( bloco_colisao(goku, destino)){
        int i;
        for(i=0;i<n_postes;i++)
            if(poste[i].existe==1)
                return CONTINUA;
        return GANHOU;
    }
    if(bloco_colisao_vetor(goku, poste, n_postes, &temp)){
        return PERDEU;
    }
    return CONTINUA;
}

int msg_final(STATUS *s){
    canvas_clear();
    pen_move(5,10);
    font_color('g');
    if(*s == GANHOU )
        pen_write("Voce eh um power ranger branco!!\n");
    else
        pen_write("Voce morreu seu fraco!!\n\n");
    util_msleep(1000);
    pen_write("Se quiser tentar de novo, tecla Espaco\n");
    pen_write("Caso tenha mais o que fazer, tecle Enter\n");
    while (1)
    {
        if(event_get()==key_SPACE)
        {
            *s = CONTINUA;
            return 0;
        }
        if(event_get()==key_ENTER)
            return 1;
    }
    return 0;
}

int main()
{
    init();
    //init_var();
    int quer_desistir = 0;
    //pintar();
    canvas_update();
    STATUS status = CONTINUA;
    while (!quer_desistir)
    {
        init_var();
        while( status == CONTINUA){
            update();
            canvas_clear();
            pintar();
            status = game_over();
            util_msleep(50);
        }
        quer_desistir = msg_final(&status);
    }

    return 0;
}

/*
Exemplo 2
*/

#include <kfup.h>

char nave[]="\
  #\n\
  #\n\
#####\n\
 ###\n\
#####";

     typedef struct{
         int atirou;
         float xtiro;
         float ytiro;
         float speed;
     } Bala;

//posicao da nave,
int xnave;
int ynave;
int vxnave;
Bala bala;
Bala missel;

void iniciar(){

    xnave=25;
    ynave=40;
    bala.atirou = 0;
    missel.atirou = 0;

    canvas_open(800,600,"Um tiro");
    font_mono_on();
    pen_move(1,1);//move para 1,1
    font_color('w');
    font_zoom_xy(1,2);
    pen_write("Nave e as duas balas com velocidades diferentes \n\n");

    pen_write("Aperte para cima para atirar bala e baixo para missel \n\n");
    pen_write("Movimente para esquerda e direita com os direcionais\n\n");
    pen_write("Aperte q para sair!\n\n");
    pen_write("Aperte qualquer tecla para continuar!");
    font_zoom(1);//apos escrever, retorne ampliar para o padra do seu jogo

    event_get();
}

int entrada_e_processamento_de_posicoes(){
    // se tiver algum evento, pegue e guarde o caractere em c
    int c=0;
    if(event_is_waiting()){
        c = event_get();

        switch (c){
            case key_LEFT: //Constante definida no kfup.h
                vxnave--;
                break;
            case key_RIGHT:
                vxnave++;
                break;
            case key_UP:
                bala.atirou = 1;
                bala.xtiro = xnave+2;
                bala.ytiro = ynave-1;
                bala.speed = 0.6;
                break;
            case key_DOWN:
                missel.atirou = 1;
                missel.xtiro = xnave+2;
                missel.ytiro = ynave-1;
                missel.speed = 0.2;
                break;

        }
    }

    xnave += vxnave;
    if(bala.atirou)
        bala.ytiro=bala.ytiro-bala.speed;
    if(missel.atirou)
        missel.ytiro=missel.ytiro-missel.speed;

    return c;
}

void desenhar_e_esperar(){
    canvas_clear();
    if(bala.atirou)
        pen_mcw(bala.xtiro,bala.ytiro,'c',"'");
    if(missel.atirou)
        pen_mcw(missel.xtiro,missel.ytiro, 'c',"@");

    pen_mcw(xnave,ynave, 'r',nave);
    pen_mcw(1,1,'y',"Aperte q para sair");
    util_msleep(50);
}
int main()
{
    iniciar();
    while(1) {
        int c;
        c = entrada_e_processamento_de_posicoes();
        desenhar_e_esperar();
        if(c==(int)'q') break;
    }
    return 0;
}





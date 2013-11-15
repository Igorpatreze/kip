/*
   Tecla saindo
   */

#include "../../src/kip.h"
#include <stdio.h>

float ytecla;
float xtecla;
int xflip;
float rotacao;
int game_over = 0;

char gerar_tecla(){
    char e = km_rand()%26+'a';
    xtecla = (km_rand()%25 +2);
    ytecla = 0;
    rotacao = km_rand()%360;
    xflip  = km_rand()%2;
    return e;
}

void atualizar_pos(){
    ytecla += 0.2;
}

void print_tecla(char e){
    fmt_begin();
        fmt_zoom(4,4);
        //kf_flip(xflip, 0);
        fmt_rotate(rotacao);
        fmt_color('K');
        k_write(xtecla,ytecla, "%c",e);
        fmt_color('g');
        k_write(xtecla,ytecla+0.2, "%c",e);
    fmt_end();
}

int main_dig(){

    k_open(1000,750,"Exemplo 2");
    fmt_block(20);
    putchar(5==5 - '1');
    puts("");
    fmt_color('g');
    char e =(char) 0;//inicializando com quaisquer valores que sejam diferentes
    int  c =       1;
    int cont = 0;
    int MAX = 25;
    int limite_inferior = 35;



    while(cont < MAX && game_over==0) {

        e = gerar_tecla();
        k_write(0,limite_inferior-cont, \
        "################################################################");
        while(1){
            c = k_peek();
            if(c != 0){
                if(c == (int) e){
                    cont++;
                    k_clear('K');
                    break;
                }
            }
            atualizar_pos();
            if(ytecla>=limite_inferior-cont){
                game_over = 1;
                break;
            }
            print_tecla(e);

            k_write(0,0,"Pontos faltantes %d :", MAX -cont);
            fmt_color('k');
            k_write(49,36,"%c",e);
            fmt_color('g');
            k_sleep(30 - cont/1.5);
        }
    }

    k_clear('K');
    if (game_over)
        k_write(0,10,"Treine mais meu filho!\n");
    else
        k_write(0,10,"Voce eh quase um X-MEN, parabens Wolverine!\n");


    k_write(0,11,"Aperter enter para sair!");
    while(k_wait() != KEY_ENTER);

    return 0;
}





/*
   Tecla saindo
   */

#include <kfup.h>

float ytecla;
int xtecla;
int game_over = 0;

char gerar_tecla(){
    char e = util_rand()%26+'a';
    xtecla = 20*(util_rand()%25 +2);
    ytecla = 0;
    return e;
}

void atualizar_pos(){
    ytecla += 2;
}

void print_tecla(char e){
    font_color(color_BLACK);
    pen_pix(xtecla,ytecla);
    pen_write("%c",e);

    font_color(color_green);
    pen_pix(xtecla,ytecla+2);
    pen_write("%c",e);
}

int main(){

    canvas_open(1000,800,"Exemplo 2");
    font_zoom(2);

    font_color(color_green);
    char e =(char) 0;//inicializando com quaisquer valores que sejam diferentes
    int  c =       1;
    int cont = 0;
    int MAX = 25;
    int limite_inferior = 35;



    while(cont < MAX && game_over==0) {

        e = gerar_tecla();
        pen_move(0,limite_inferior-cont);
        pen_write("################################################################");
        while(1){


            if(event_is_waiting()){
                c=event_get();
                if(c == (int) e){
                    cont++;
                    canvas_clear();
                    break;
                }
            }
            atualizar_pos();
            if((ytecla/20)>=limite_inferior-cont){
                game_over = 1;
                break;
            }
            print_tecla(e);

            pen_move(0,0);

            pen_write("Pontos faltantes :%d",MAX -cont);
            canvas_update();
            util_msleep(30 - cont);
        }
    }

    canvas_clear();
    pen_move(0,10);
    if (game_over)
        pen_write("Treine mais meu filho!\n");
    else
        pen_write("Voce eh quase um X-MEN, parabens Wolverine!\n");


    pen_write("Aperter enter para sair!");
    while(event_get() != key_ENTER);

    return 0;
}





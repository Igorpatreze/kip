/*
 * Exemplo 4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <kip.h>

#define MAX 500
#define BORRACHA ' '

char cfundo = 'K';
char cores[]="RrGgBbYyCcMmKkWw";
const int num_cores = 16;
const int tam_bloco = 10;
int L, C;
int fx, fy; //fator de amplicor_pincel;
char quadro[MAX][MAX];
int ycores;//posicao y das cores
int yborracha;//posicao y da borracha
int xborracha;
char cor_pincel;//contem cor de pintura atual
int  ind_pincel;//o indice da cor atual

void entrada(){
    k_open(800, 800,"Janela  ");
    font_mono_on();
    cor_pincel = 'R';
    ind_pincel = 0;

    char resp[10];
    k_color('y');

    f_zoom_xy(1,2);
    font_mono_off();
    pen_move(2,5);//posicao do titulo

    f_zoom_xy(2,3);
    k_write("Editor de Imagens\n\n");
    f_zoom_xy(1,2);

    pen_move(2,8);

    k_color('w');
    k_write("Instrucoes:\nPara selecionar uma cor, clique com o botao esquerdo ou rode a bolinha do mouse.\n");
    k_write("Clique com o direito para apagar.\n");
    k_write("Para gerar o codigo da tua arte tecle G\n\n");

    k_color('W');

    pen_move(2,pen_get_block_y()+1);
    k_write("Numero de linhas : ");
    util_gets(resp);//espera o texto ate o enter
    L = atoi(resp);

    pen_move(2,pen_get_block_y()+1);
    k_write("Numero de colunas: ");
    util_gets(resp);//espera o texto ate o enter
    font_mono_on();

    C = atoi(resp);

    //inicializando matriz
    int i,j;
    for (i=0;i<L;i++)
        for(j=0;j<C;j++)
            quadro[i][j]=' ';

    for (i=0;i<L;i++)
        quadro[i][C]='\0';
}

void gerar_codigo(){
    system("clear");
    printf("\nchar sprite[]=\"\\\n");
    int i,j;
    for (i=0;i<L;i++){
        for(j=0;j<C;j++){
            printf("%c",quadro[i][j]);
        }
        if(i == (L-1))
            printf("\";\n\n");
        else
            printf("\\n\\\n");
    }
    printf("\nCopie e cole esse texto no seu codigo fonte\n");
}

void interface(){

    k_color('K');
    font_clear_color('W');

    k_clear(K);
    /*if(L < 36){*/
    fx=2;
    fy=2;
    /*}else{*/
    /*fx=1;*/
    /*fy=1;*/
    /*}*/
    f_zoom_xy(fx,fy);
    int i,j;
    for (i=0;i<L;i++){
        for (j=0;j<C;j++){
            pen_move(j,i);
            if(quadro[i][j]==' '){
                pen_asc(asc_bloco_marcado);
            }else{
                k_color(quadro[i][j]);
                pen_asc(asc_bloco_fechado);
                k_color('K');
            }
        }
    }
    ycores = L;

    //pincel de cores
    for (i=0;i<strlen(cores);i++){
        pen_move(i,ycores);
        k_color(cores[i]);
        pen_asc(asc_bloco_fechado);
    }

    k_color('W');
    pen_line(0 , ycores * fy * ( tam_bloco + 1 ), fy * tam_bloco * num_cores , ycores * fy * (tam_bloco + 1));
    pen_line(0 , ycores * fy * ( tam_bloco     ), fy * tam_bloco * num_cores , ycores * fy * (tam_bloco    ));

    //marca o atual

    k_color('K');
    pen_move( ind_pincel, ycores + 1 );
    pen_asc('^');

}


int eventos(){
    e_event ev = k_event_waiting();

    if( ev != event_NONE ){

        int clique = k_wait();
        int bx =  k_wait_block_x();//qual bloco foi clicado
        int by =  k_wait_block_y();

        //clicou na arte
        if(bx<C && by<L){
            if( clique == click_LEFT )//atualizando cor no quadro
                quadro[by][bx]=cor_pincel;
            if( clique == click_RIGHT )
                quadro[by][bx]=' ';   //clique com o direito eh apagar
        }

        if(clique == click_DOWN)
            ind_pincel = (ind_pincel + 1) % num_cores;
        if(clique == click_UP)
            ind_pincel = (ind_pincel + num_cores - 1) % num_cores;
        //clicou na palheta de cores
        if( by == ycores && bx < num_cores ){
            ind_pincel= bx;
        }

        cor_pincel = cores[ ind_pincel ];

        if (clique == 'g') {
            gerar_codigo();
        }

        interface();
        return 1;
    }
    return 0;
}


int main()
{

    entrada();
    interface();
    while(1){
        eventos();
    }
    return 0;
}



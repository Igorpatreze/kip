/*
 * Exemplo 4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <kip.h>
#include <math.h>

#define MAX 500
#define BORRACHA ' '

typedef struct{
    int x, y;
} Point;
typedef struct{
    Point b, e;
    char cor;
} Line;
typedef struct{
    Line vet[500];
    int ind;
} Vector;

Vector list;
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

static int waiting_point = 0;//se esta esperando o segundo ponto
static Point first;//o primeiro ponto da linha

void list_add_line(Vector *v, Line line){
    v->ind++;
    v->vet[v->ind] = line;
}

void swap_line(Line *a, Line *b){
    Line temp = *a;
    *a = *b;
    *b = temp;
}

void del_line(Vector *v, Line *pl){
    swap_line(pl, &(v->vet[v->ind]));
    v->ind--;
}

int point_equal(Point a, Point b){
    if(a.x == b.x && a.y == b.y)
        return 1;
    return 0;
}

void list_del_point(Vector *v, Point p){
    int i=0;
    while(i<=v->ind){
        Line *pl = &(v->vet[i]);
        if(point_equal(pl->b, p) || point_equal(pl->e, p))
            del_line( v, pl);
        else
            i++;
    }
}

void put_bloco(int x, int y){
    k_plot(x,y,0);
}

void liney(double x1,double y1,double x2,double y2)
{

    double x,y;
    double d=(double)(x2-x1)/(y2-y1); //double for accuracy

    y = y1;
    while(1)//controle de parada e incremento no corpo do laco
    {
        x=x1+(d*(y-y1)); //y is the same precentage of trip x made on its trip
        //put_bloco(x+0.5,y+0.5);
        quadro[(int)(y+0.5)][(int)(x+0.5)] = cor_pincel;
        if(y1<y2){
            if(y>=y2)
                return;
            y++;
        }
        if(y1>y2){
            if(y<=y2)
                return;
            y--;
        }
    }
}

void linex(double x1,double y1,double x2,double y2)
{
    double x=0,y=0;
    double d = (double)(y2-y1)/(x2-x1);
    x = x1;
    while(1)
    {
        y=y1+(d*(x-x1)); //y is the same precentage of trip x made on its trip
        //put_bloco(x+0.5,y+0.5);
        quadro[(int)(y+0.5)][(int)(x+0.5)] = cor_pincel;
        if(x1<x2){
            if(x>=x2)
                return;
            x++;
        }
        if(x1>x2){
            if(x<=x2)
                return;
            x--;
        }
    }
}

void vec_line(int x1,int y1,int x2,int y2){
    if(x1==x2 && y1==y2){
        put_bloco(x1,y1);
        return;
    }
    if(fabs(x1-x2)>fabs(y1-y2))
        linex(x1,y1,x2,y2);
    else
        liney(x1,y1,x2,y2);
}
void entrada(){

    list.ind = -1;

    k_open(1000, 800,"Janela  ");

    cor_pincel = 'R';
    ind_pincel = 0;

    k_color('y');
    kf_zoom(1,2);
    k_write(2,5,"Editor de Imagens");

    k_color('w');
    k_write(0, 8, "Instrucoes:");
    k_write(0, 9, "Para selecionar uma cor, clique com o botao esquerdo ou rode a bolinha do mouse.");
    k_write(0, 10,"Clique com o direito para apagar.");
    k_write(0, 11,"Para gerar o codigo da tua arte tecle G");

    k_color('W');
    k_write(0, 12, "Digite: d (imagem 10x10), v(imagem 20x20), t(imagem 30x30), p(modo pen)");
    while(1)
    {
        char c = k_wait();
        if(c == 'd')
        {
            C = 10, L = 10;
            break;
        }
        if(c == 'v')
        {
            C = 20, L = 20;
            break;
        }
        if(c == 't')
        {
            C = 30, L = 30;
            break;
        }
        if(c == 'p')
        {
            C = 0, L = 0;
            break;
        }
    }

}

void gerar_codigo(){
    system("clear");
    printf("kdraft *nome = draft_new(%d,\n",list.ind +1);
    for (int i=0; i<=list.ind; i++){
        printf("(kp_line){{%d, %d},{%d, %d}, \'%c\'},\n",
                (int)list.vet[i].b.x, (int)list.vet[i].b.y,
                (int)list.vet[i].e.x, (int)list.vet[i].e.y,
                (int)list.vet[i].cor);
    }
    printf("(kpoint){%d,%d});\n\n",C/2, L/2);
}



void interface(){

    k_color('K');
    k_clear('w');

    for(int i=0; i<=C; i++)
        k_linep(i*20,0   , i*20, L*20);//linhas verticais

    for(int i=0; i<=L; i++)
        k_linep(0   ,i*20, C*20, i*20);//linhas horizontais

        //imprimir os pontos
    for (int i=0; i <= list.ind; i++){
        Line a = list.vet[i];
        k_color(a.cor);
        vec_line(a.b.x, a.b.y, a.e.x, a.e.y);
        k_line(a.b.x+0.5, a.b.y+0.5, a.e.x+0.5, a.e.y+0.5);

    }

    ycores = L;

    //imprimindo pincel de cores
    for (int i=0;i<strlen(cores);i++){
        k_color(cores[i]);
        k_plot(i,ycores, 0);
    }

    k_color('K');
    k_write( ind_pincel, ycores + 1, "^" );

    if(waiting_point){
        k_color(cor_pincel);
        k_write(first.x, first.y, "x");
    }

}


int eventos(){
    int x = k_event_waiting();
    if( x ){

        int clique = k_wait();
        int bx =  k_xpos();//qual bloco foi clicado
        int by =  k_ypos();

        //clicou na arte
        if(bx<C && by<L){
            if( clique == CLICK_LEFT ){//atualizando cor no quadro
                if(!waiting_point){
                    waiting_point = 1;
                    first.x = bx;
                    first.y = by;
                }else{
                    Line l = {first, {bx,by},cor_pincel};
                    list_add_line(&list, l);
                    waiting_point = 0;
                }
            }
            if( clique == CLICK_RIGHT ){
                Point atual = {bx,by};
                list_del_point(&list, atual);
            }
        }

        if(clique == CLICK_DOWN)
            ind_pincel = (ind_pincel + 1) % num_cores;
        if(clique == CLICK_UP)
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



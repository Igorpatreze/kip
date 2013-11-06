/*
 * David Sena
 * Versão dia: 22/10/2013
 */

#ifndef KIP_H
#define KIP_H

#include <stdarg.h>

/* ############################################ */
/* ######## DEFINES                   ######### */
/* ############################################ */

/* mouse */
#define CLICK_LEFT    1
#define CLICK_MIDDLE  2
#define CLICK_RIGHT   3
#define CLICK_UP      4
#define CLICK_DOWN    5

/* key */
#define KEY_ENTER 13
#define KEY_LEFT  81
#define KEY_UP    82
#define KEY_RIGHT 83
#define KEY_DOWN  84

/* CODIGOS */
#define CODE_HAPPY_FACE        6
#define CODE_APPLE            12
#define CODE_HEART            13
#define CODE_BOMBERMAN        14




/* ############################################ */
/* ######## FUNCOES BASICAS DE TELA   ######### */
/* ############################################ */


/* Agrupa pixels em blocos, para funcoes
 * k_write, k_xpos, k_ypos, k_image, k_draw
 * O default eh 1, que funciona como movimentação em pixeis */
void k_block(int size);

/* Inicializa a janela */
void k_open( int width, int height, const char *title );

/* Muda a cor corrente, opcoes:
 * R, r, G, g, B, b, Y, y, C, c, M, m, W, w, K, k */
void k_color( char color);

/* Muda a cor corrente */
void k_color_rgb(int r, int g, int b );

/* Repinta tudo com a cor de limpeza de fundo */
void k_clear(char color);

/* Repinta tudo com a cor de limpeza de fundo */
void k_clear_rgb(int r, int g, int b );

/* Espera pelo usuario efetuar algum evento e captura esse evento */
char k_wait();

/* retorna as coordenadas x e y do ultimo evento */
float k_xpos();
float k_ypos();

/* Verifica se aconteceu algum evento */
int  k_event_waiting();

/* Força o acontecimento das ações pendentes de pintura */
void k_flush();

/* Faz o programa dormir, em milessegundos */
void k_sleep(int msec);

/* O tempo que o programa esta em execução em milesegundos */
int  k_alive();

/* Toca uma audio mp3 dado o path */
void k_mp3_play(char *path);

/* Para um audio mp3 dado o path */
void k_mp3_stop(char *path);

/* ############################################ */
/* ######## FUNCOES DE FORMATACAO     ######### */
/* ############################################ */

typedef struct{
    int   xflip;//x flip, 0 normal, 1 flipped
    int   yflip;
    float xzoom;//x zoom, 1 normal, 0.5 half, 2 doubled
    float yzoom;
    double rot; //rotation angle, in degrees
} ks_fmt;

/* funcoes para formatacao */

/* Abre o escopo
   O novo escopo eh iniciado com a formatacao default
*/
void kf_open();

//fecha escopo de trans e volta as tranf default
void kf_close();
void kf_zoom   (float xscale, float yscale);
void kf_flip   (int xflag, int yflag);
void kf_rotate (float angle);
void kf_set    (ks_fmt fmt);
ks_fmt * kf_get  ();//retorna end das transformacoes

/* ############################################ */
/* ######## FUNCOES DE TEXTO E IMAGENS ######## */
/* ############################################ */

//desenha uma imagem de nlin por ncol dada por  em x, y
//address: o endereco da imagem
void k_draw (float x, float y, const char *address, int nlin, int ncol);

//escreve um texto no bloco x, y
//utiliza a formatacao das funcoes kf_zoom, kf_flip kf_rot
void k_write(float x, float y, const char *format, ...);

//retorna a imagem 10x10 de uma letra ou simbolo dado o codigo asc
const char *k_code(int code);

/* ############################################ */
/* ######## FUNCOES DE DESENHO     ############ */
/* ############################################ */

/* Desenha uma linha de (x1,y1) to (x2,y2) */
void k_line(float x1, float y1, float x2, float y2 );

/* Plota um pixel ou um bloco */
void k_plot(float x , float y);

/* Plot a square with side in block x, y */
/* If side == 0, side = default block size */
/* xc, yc posicao do centro */
void k_square(float xc, float yc, int side, int filled);

/* Desenha um poligono dado o centro, o numero de lados,
 * um bool se deve preencher ou nao.
 * Se flag = 's', value deve conter o valor do lado
 * Se flag = 'r', value deve conter o valor do raio*/
void k_polig(double xc, double yc, char flag,
             double value, int sides, int filled);

/* ############################################ */
/* ######## FUNCOES AUXILIARES MATEMATICAS   ## */
/* ############################################ */

#define km_PI 3.14159265358979323846
#define km_deg2rad(angle)   ((angle)   * (km_PI/ 180.0  ))
#define km_rad2deg(radians) ((radians) * (180.0  / km_PI))

/* # TODOS OS ANGULOS SAO DADOS E RETORNADOS EM GRAUS # */

/* Retorna um numero aleatorio */
int  km_rand();

/* Funcao para obter o angulo entre dois pontos em graus */
double km_angle(double ax, double ay, double bx, double by);

/* Distancia entre dois pontos */
double km_dist(double ax, double ay, double bx, double by);

/* Funcao para rotacionar um ponto em relacao ao centro */
void km_coor_rot(double cx, double cy,
                 double *px, double *py, double degrees);


/* ############################################ */
/* ######## VARIAVEIS DE AMBIENTE     ######### */
/* ############################################ */

typedef struct{
    int  width;  //largura da janela
    int  height; //altura da janela
    char color;  //atual cor de risco
    char clear;//atual cor de fundo
    int  block;  //atual tamanho do bloco
    int  letter;  //tamanho minimo de uma letra
    const char *colors;//string com a lista das cores disponiveis
    int start;//hora de inicio do programa em mseg
} ks_kip;

/* Pega informações do ambiente */
ks_kip k_info();

/* ############################################ */
/* #######   FUNCOES DE PEN           ######### */
/* ############################################ */

typedef struct{
    double x;
    double y;
    double head;
    int    isdown;
    double delay;// 0 instantaneous, delay em mseg para cada pixel plotado
    double xcenter;
    double ycenter;
    int    is_fixed;
    ks_fmt fmt;
} ks_pen;

//informacoes
ks_pen * kp_get();//retorna a variavel global que define a caneta
double kp_xcor ();
double kp_ycor ();
double kp_delay();
double kp_head () ;

//setando variaveis
void kp_setx(double x);//altera a posicao x
void kp_sety(double y);//altera a posicao y
void kp_seth(double head);//Direcao: 0-direita, 90-norte, 270-esquerda
void kp_setd(float delay);//0 instantaneous

//mudando estado
void kp_up();
void kp_down();

//movimenta a caneta
void kp_home();//vai para o centro da tela com heading = 0
void kp_goto(double xdest, double ydest);
void kp_fd(double dist); //pra frente
void kp_bk(double dist); //pra tras

void kp_lt (double degrees); //direita
void kp_rt (double degrees); //esquerda

//traça uma linha com a caneta
void kp_drag(double ax, double ay, double bx, double by);

//dado o centro, percorre o angulo em tantos steps
void kp_arc(double xcenter, double ycenter, double angle, int steps);

//transformacoes
void kp_fix(double xcenter, double ycenter);
void kp_unfix();

/* ############################################ */
/* ##########    FUNCOES INTERNAS   ########### */
/* ############################################ */

/*desenha uma linha entre os pixels (x1,y1) e (x2,y2) */
void ii_line(int x1, int y1, int x2, int y2);

typedef struct{
    double x, y;
} ks_point;

//desenha como k_draw, mas recebe a fmt diretamente
void ii_draw(int px, int py, const char * head, int nlin, int ncol, ks_fmt fmt);
//desenha como k_write, mas recebe a fmt diretamente
void ii_write(float x, float y, ks_fmt fmt, const char *format, ...);

//aplica a transformação fmt ao ponto relative dado o centro absoluto
ks_point ii_point_fmt(ks_point center, ks_point relative, ks_fmt fmt);

//a funcao plota o ponto x e y e recebe parametros adicionais se necessario
typedef void (*ii_plot_fn) (double x, double y, const void * param);
//processa uma linha entre a e b usando a funcao var_fn e os parametros
void  ii_line_process(ks_point a, ks_point b, ii_plot_fn fn, const void *param);

//retorna uma struct com os valores default para caneta
ks_pen ip_new(int delay);
//fixa para transformacoes
void ip_fix  (ks_pen *kp, double x, double y);
//leva a caneta para para posicao
void ip_goto (ks_pen *kp, double xdest, double ydest);
//leva a caneta kp pra frente
void ip_fd   (ks_pen *kp, double px);
//desenha um poligono dado o centro(xc,yc) o angulo (360 eh o angulo todo)
//o numero de passos(step 4 faz um quadrado se angulo = 360)
//kp da a posicao inicial da caneta
void ip_arc(ks_pen *kp, double xc, double yc, double angle, int steps);


#endif // HW_H

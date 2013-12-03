/*
 * David Sena
 * Versão dia: 22/10/2013
 */

#ifndef KIP_H
#define KIP_H
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

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
#define CODE_HAPPY_FACE       10
#define CODE_APPLE            11
#define CODE_HEART            12
#define CODE_BOMBERMAN        13
#define CODE_ROBOT            14
#define CODE_GIRL             15
#define CODE_SPACESHIP        16




/* ############################################ */
/* ######## FUNCOES BASICAS DE TELA   ######### */
/* ############################################ */


/* Basicas */
        /* Inicializa a janela */
        void k_open( int width, int height, const char *title );

        /* Repinta tudo com a cor de limpeza de fundo */
        void k_clear(char color);

        /* Força o acontecimento das ações pendentes de pintura */
        void k_flush();

/* Interacao usuario */

        /* Espera pelo usuario efetuar algum evento e captura esse evento */
        char k_wait();

        /* Se algum evento tiver acontecido retorna o evento,
         * se não, retorna 0 */
        char k_peek();

        /* retorna as coordenadas x e y do ultimo evento */
        float k_xpos();
        float k_ypos();


/* ############################################ */
/* ######## FUNCOES DE TEXTO E IMAGENS ######## */
/* ############################################ */

        //desenha uma imagem de nlin por ncol dada por  em x, y
        //address: o endereco da imagem
        void k_draw (float x, float y, const char *address, int nlin, int ncol);

        //escreve um texto no bloco x, y
        //utiliza a formatacao das funcoes kf_zoom, kf_flip kf_rot
        void k_write(float x, float y, const char *format, ...);


/* ############################################ */
/* ######## AUXILIARES                 ######## */
/* ############################################ */

        //retorna a imagem 10x10 de uma letra ou simbolo dado o codigo asc
        const char *k_code(int code);

        /* Faz o programa dormir, em milessegundos */
        void k_sleep(int msec);

        /* O tempo que o programa esta em execução em milesegundos */
        int  k_alive();

        /* Toca uma audio mp3 dado o path */
        void k_mp3_play(char *path);

        /* Para um audio mp3 dado o path */
        void k_mp3_stop(char *path);

        /* Para adicionar uma cor */
        void k_add_color(char color, int r, int g, int b);

/* ############################################ */
/* ######## FUNCOES DE FORMATACAO     ######### */
/* ############################################ */

        typedef struct{
            int   xflip;//x flip, 0 normal, 1 flipped
            int   yflip;
            float xzoom;//x zoom, 1 normal, 0.5 half, 2 doubled
            float yzoom;
            double rot; //rotation angle, in degrees

            char color;  //atual cor de risco
            int  block;  //atual tamanho do bloco

        } ks_env;

        #define FMT_DEFAULT (ks_env) {0, 0, 2, 2, 0, 'w', 20}

        //Todas as funcoes abaixo podem ser tratadas
        //como funcoes de escopo

        /* Agrupa pixels em blocos, para funcoes
         * k_write, k_xpos, k_ypos, k_image, k_draw
         * O default eh 20 */
        void k_block(int size);
        /* Muda a cor corrente, opcoes:
         * R, r, G, g, B, b, Y, y, C, c, M, m, W, w, K, k */
        void k_color( char color);
        void k_zoom   (float xscale, float yscale);
        void k_flip   (int xflag, int yflag);
        void k_rotate (float angle);


        // Abre o ambiente == environment - env. temporário de formatacao
        // O novo escopo eh iniciado com a copia do escopo default
        void     kenv_begin();
        //fecha o escopo temporario
        void     kenv_end();
        // Padrao flip x=0, y=0, zoom x=2, y=2, rot = 0,
        // Color 'w', Block 20
        void     kenv_reset   ();//reseta as configuracoes do escopo atual
        void     kenv_set (ks_env fmt);//seta passando uma struct
        ks_env * kenv_get ();//retorna endereco do escopo atual


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
     * e um bool se deve preencher ou nao.
     * Se flag = 's', value deve conter o valor do lado
     * Se flag = 'r', value deve conter o valor do raio*/
    void k_polig(double xc, double yc, char flag,
             double value, int sides, int filled);

/* ############################################ */
/* ######## FUNCOES MATEMATICAS              ## */
/* ############################################ */

    #define km_PI 3.14159265358979323846
    #define km_deg2rad(angle)   ((angle)   * (km_PI/ 180.0  ))
    #define km_rad2deg(radians) ((radians) * (180.0  / km_PI))

    /* # TODOS OS ANGULOS SAO DADOS E RETORNADOS EM GRAUS # */

    /* Retorna um numero aleatorio */
    int    k_rand();

    /* Funcao para obter o angulo entre dois pontos em graus */
    double k_calc_angle(double ax, double ay, double bx, double by);

    /* Distancia entre dois pontos */
    double k_calc_distance(double ax, double ay, double bx, double by);

    /* Funcao para rotacionar um ponto em relacao a um centro
     * cx e cy coordenadas do centro,
     * px e py endereco do ponto a ser rotacionado
     * O resultado da rotação é lançado em px py. */
    void k_rotate_coor(double cx, double cy,
             double *px, double *py, double degrees);


/* ############################################ */
/* ######## INFORMACOES DE AMBIENTE     ####### */
/* ############################################ */

    typedef struct{
        int  width;  //largura da janela
        int  height; //altura da janela
        char color;  //atual cor de risco
        char clear;  //cor de fundo
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
    /* A movimentacao da caneta eh feita em pixels sempre,
     * nunca em blocos */


    typedef struct{
        double x;
        double y;
        double head;
        int    isdown;
        double delay;// 0 instantaneous, delay em mseg para cada pixel plotado
        double xcenter;
        double ycenter;
        int    is_fixed;
        ks_env fmt;
    } ks_pen;

    //informacoes
    ks_pen * pen_get();//retorna a variavel global que define a caneta
    double pen_xcor ();
    double pen_ycor ();
    double pen_delay();
    double pen_head () ;

    //setando variaveis
    void pen_setx(double x);//altera a posicao x
    void pen_sety(double y);//altera a posicao y
    void pen_seth(double head);//Direcao: 0-direita, 90-norte, 270-esquerda
    void pen_setd(float delay);//0 instantaneous

    //mudando estado
    void pen_up();
    void pen_down();

    //movimenta a caneta
    void pen_home();//vai para o centro da tela com heading = 0
    void pen_goto(double xdest, double ydest);
    void pen_fd(double dist); //pra frente
    void pen_bk(double dist); //pra tras

    void pen_lt (double degrees); //direita
    void pen_rt (double degrees); //esquerda

    //traça uma linha com a caneta
    void pen_drag(double ax, double ay, double bx, double by);

    //A partir da posicao atual de pen faz uma curva
    //em relacao ao centro, percorrendo o angulo em tantos steps.
    void pen_curve(double xcenter, double ycenter, double angle, int steps);

    //Tal qual kp_curve, mas usa a posicao atual de pen como centro.
    //Desenha um arco entre o angulo inicial beg_ang e o angulo.
    //final end_ang, com o número de passos dados por steps.
    //Funciona como um compasso de desenho.
    void pen_compass(double radius, double beg_ang, double end_ang, int steps);

    //transformacoes
    //apos kp_fix todo comando de transformacao sera aplicado
    //a caneta, tendo o centro informado como centro do desenho
    void pen_fix(double xcenter, double ycenter);

    //desabilidata as transformações
    void pen_unfix();





#ifdef __cplusplus
}
#endif

#endif // HW_H

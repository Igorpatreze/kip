
/*
A simple graphics library for CSE 20211 by Douglas Thain
For complete documentation, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2011/kf
Version 2, 9/23/2011 - Fixes a bug that could result in jerky animation.

Adaptações por David Sena. sena.ufc@gmail.com
*/
#define _POSIX_C_SOURCE	199309L
#include <time.h>
#include <sys/time.h>

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



#include "kip.h"

/* ############################################ */
/* ######## VARIAVEIS GLOBAIS DO SISTEMA ###### */
/* ############################################ */
/*

kf_open creates several X11 objects, and stores them in globals
for use by the other functions in the library.
*/

static Display *kf_display;
static Window  kf_window;
static GC      kf_gc;
static Colormap kf_colormap;

/* These values are saved by kf_wait then retrieved later by kf_xpos and kf_ypos. */

static int saved_xpos = 0;
static int saved_ypos = 0;


ks_kip * __kip(){
    static ks_kip info;
    static int init = 1;
    if(init){
        init = 0;
        info.height = 0;
        info.width  = 0;
        info.color  = 'w';
        info.clear = 'B';
        info.block  = 20;
        info.colors = "RrGgBbYyCcMmWwKk";
        struct timeval tv;
        gettimeofday(&tv, 0);//salva o tempo inicial
        info.start = tv.tv_sec*1000 + tv.tv_usec/1000;
    }
    return &info;
}

ks_kip k_get(){
    return *(__kip());
}

void k_block(int size){
    __kip()->block = size;
}

/* ############################################ */
/* ######## MODULO GRAFICO BASICO     ######### */
/* ############################################ */

/* Open a new graphics window. */
void k_open( int width, int height, const char *title )
{
    __kip()->height = height;
    __kip()->width  = width;
    srand(time(NULL));
    kf_display = XOpenDisplay(0);
    if(!kf_display) {
        fprintf(stderr,"kf_open: unable to open the graphics window.\n");
        exit(1);
    }

    int blackColor = BlackPixel(kf_display, DefaultScreen(kf_display));
    int whiteColor = WhitePixel(kf_display, DefaultScreen(kf_display));

    kf_window = XCreateSimpleWindow(kf_display, DefaultRootWindow(kf_display), 0, 0, width, height, 0, blackColor, blackColor);

    XSetWindowAttributes attr;
    attr.backing_store = Always;

    XChangeWindowAttributes(kf_display,kf_window,CWBackingStore,&attr);

    XStoreName(kf_display,kf_window,title);

    XSelectInput(kf_display, kf_window, StructureNotifyMask|KeyPressMask|ButtonPressMask);

    XMapWindow(kf_display,kf_window);

    kf_gc = XCreateGC(kf_display, kf_window, 0, 0);

    kf_colormap = DefaultColormap(kf_display,0);

    XSetForeground(kf_display, kf_gc, whiteColor);

    // Wait for the MapNotify event

    for(;;) {
        XEvent e;
        XNextEvent(kf_display, &e);
        if (e.type == MapNotify)
            break;
    }
}





int k_event_waiting()
{
       XEvent event;

       k_flush();

       while (1) {
               if(XCheckMaskEvent(kf_display,-1,&event)) {
                       if(event.type==KeyPress) {
                               XPutBackEvent(kf_display,&event);
                               return 1;
                       } else if (event.type==ButtonPress) {
                               XPutBackEvent(kf_display,&event);
                               return 1;
                       } else {
                               return 0;
                       }
               } else {
                       return 0;
               }
       }
}

/* Wait for the user to press a key or mouse button. */

char k_wait()
{
    XEvent event;

    k_flush();

    while(1) {
        XNextEvent(kf_display,&event);

        if(event.type==KeyPress) {
            saved_xpos = event.xkey.x;
            saved_ypos = event.xkey.y;
            return XLookupKeysym(&event.xkey,0);
        } else if(event.type==ButtonPress) {
            saved_xpos = event.xkey.x;
            saved_ypos = event.xkey.y;
            return event.xbutton.button;
        }
    }
}

/* Return the X and Y coordinates of the last event. */

float k_xpos()
{
    return (float)saved_xpos/__kip()->block;
}

float k_ypos()
{
    return (float)saved_ypos/__kip()->block;
}

/* Flush all previous output to the window. */

void k_flush()
{
    XFlush(kf_display);
}

/* ############################################ */
/* ######## MODULO DE CORES           ######### */
/* ############################################ */

typedef struct{
    int r, g, b;
}icolor;

icolor __get_color(char color){
    static icolor RGB[256];//todos os possiveis valores para um char
    static int init = 1;
    if (init == 1)
    {
        init = 0;
        int i;
        icolor color_null = {-1,-1,-1};
        for (i = 0; i < 256; i++){
            RGB[i] =(icolor) color_null;
        }
        RGB['R'] =(icolor) {139, 0  , 0  };
        RGB['r'] =(icolor) {255, 0  , 0  };
        RGB['G'] =(icolor) {0  , 100, 0  };
        RGB['g'] =(icolor) {0  , 255, 0  };
        RGB['B'] =(icolor) {0  , 0  , 128};
        RGB['b'] =(icolor) {0  , 0  , 255};
        RGB['Y'] =(icolor) {255, 215, 0  };
        RGB['y'] =(icolor) {255, 255, 0  };
        RGB['C'] =(icolor) {0  , 139, 139};
        RGB['c'] =(icolor) {0  , 255, 255};
        RGB['M'] =(icolor) {148, 0  , 211};
        RGB['m'] =(icolor) {255, 192, 203};
        RGB['W'] =(icolor) {220, 245, 220};
        RGB['w'] =(icolor) {255, 255, 255};
        RGB['K'] =(icolor) {0  , 0  , 0  };
        RGB['k'] =(icolor) {61 , 43 , 31 };
    }
    return RGB[(int)color];
}

void k_color( char color ){
    if(color == __kip()->color)
        return;
    icolor kc = __get_color(color);
    if(kc.r == -1)
        return;
    __kip()->color = color;
    k_color_rgb(kc.r,kc.g,kc.b);
}

/* Change the current drawing color. */
void k_color_rgb( int r, int g, int b )
{

    XColor color;
    color.pixel = 0;
    color.red = r<<8;
    color.green = g<<8;
    color.blue = b<<8;
    XAllocColor(kf_display,kf_colormap,&color);
    XSetForeground(kf_display, kf_gc, color.pixel);
}

/* Change the current background color. */
void k_clear_color_rgb( int r, int g, int b )
{
    XColor color;
    color.pixel = 0;
    color.red = r<<8;
    color.green = g<<8;
    color.blue = b<<8;
    XAllocColor(kf_display,kf_colormap,&color);

    XSetWindowAttributes attr;
    attr.background_pixel = color.pixel;
    XChangeWindowAttributes(kf_display,kf_window,CWBackPixel,&attr);
}
void k_clear_color(char color){
    if(color == __kip()->clear)
        return;
    icolor kc = __get_color(color);
    if(kc.r == -1)
        return;
    __kip()->clear = color;
    k_clear_color_rgb(kc.r,kc.g,kc.b);
}
/* Clear the graphics window to the background color. */
void k_clear(char color)
{
    k_clear_color(color);
    XClearWindow(kf_display,kf_window);
}

void k_clear_rgb(int r, int g, int b )
{
    k_clear_color_rgb(r, g, b);
    XClearWindow(kf_display,kf_window);
}

/* ############################################ */
/* ######## FUNCOES DE DESENHO     ############ */
/* ############################################ */
/* Draw a line from block (x1,y1) to (x2,y2) */

void k_line( float x1, float y1, float x2, float y2 )
{
    int block = k_get().block;
    ki_line(x1*block,y1*block, x2*block, y2*block);
}

/* Draw a line from (x1,y1) to (x2,y2) */
void ki_line(int x1, int y1, int x2, int y2 )
{
    XDrawLine(kf_display,kf_window,kf_gc,x1,y1,x2,y2);
}

//plota um pixel ou um quadrado fechado
void k_plot(float x , float y)
{
    kd_square(x,y, k_get().block, 1);
}

/* Paint a square, filled if filled == 1 */
void kd_square( float x, float y, int side, int filled)
{
    int i;

    int block = k_get().block;
    if(side == 0)
        side = block;
    x = x * block;//convertendo para posicoes em pixels
    y = y * block;
    if(filled == 0)
    {
        ki_line(x, y, x+side, y);
        ki_line(x, y, x, y + side);
        ki_line(x + side, y, x + side , y + side);
        ki_line(x , y + side, x + side , y + side);
    }
    else{//filled
        for( i = 0; i < side; i++)
            ki_line(x, y + i, x + side, y + i);
    }
}


void __polig_plot(double x, double y, const void *param)
{
    // x centro
    double xc = *(double *)param;
    ki_line(x,y,x+2*(xc-x),y);
}


void k_polig(double x, double y, double radius, int sides, int filled)
{
    if (sides < 3)
        return;
    double int_ang = (sides - 2)*180.0/sides;
    double ext_ang = 360.0/sides;
    double side    = fabs(2 * radius*cos(ki_DEG2RAD(int_ang/2)));

    ks_pen kp = kpi_new(0);
    kp.x = x;
    kp.y = y;
    kp.head = 270 - (360/(2*sides));
    kp.isdown = 0;
    kpi_fd(&kp, radius);
    kp.isdown = 1;

    if (filled == 0)
    {
        kp.head = 0;
        int qtd = sides;
        while(qtd--)
        {
            kpi_fd(&kp, side);
            kp.head += ext_ang;
        }
        //ki_line();
    }
    else
    {
        kp.head = int_ang;
        int qtd = (sides-1)/2;
        while(qtd--)
        {
            double xbeg = kp.x;
            double ybeg = kp.y;
            kpi_fd(&kp, side);
            kp.head -= ext_ang;
            double xend = kp.x;
            double yend = kp.y;
            ki_line_process((ks_point){xbeg, ybeg}, (ks_point){xend,yend},
                            __polig_plot,&(x));
        }
    }
}

/* ######## FUNCOES AUXILIARES NAO GRAFICAS  ## */
/* ############################################ */

int ki_time2mseg(struct timeval tv)
{
    return  tv.tv_sec*1000 + tv.tv_usec/1000;
}

int ka_alive()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return ki_time2mseg(tv) - k_get().start;
}

void ka_sleep(int msec)
{
    k_flush();
    struct timespec interval;
    struct timespec remainder;
    interval.tv_sec = msec / 1000;
    interval.tv_nsec = (msec % 1000) * (1000 * 1000);
    nanosleep(&interval, &remainder) ;
    //usleep(1000*msec);
}



int ka_rand()
{
    return rand();
}

void ka_mp3_play(char *path){
    char c[500];
    sprintf(c,"mpg123 %s 2>/dev/null 1>/dev/null&",path);
    system(c);
}

void ka_mp3_stop(char *path){
    char c[500];
    sprintf(c,"ps aux  | grep \"mpg123 %s\" |head -1|  awk '{ print $2; }' | xargs kill -9 2>/dev/null 1>/dev/null&",path);
    system(c);
}


/* ############################################ */
/* ######## FUNCOES DE FORMATACAO     ######### */
/* ############################################ */

//Fornece uma variavel global para as funcoes de formatacao
ks_format * __geo()
{
    static ks_format fo = {0, 0, 2, 2, 0};
    return &fo;
}

//retorna o valor corrente das transformacoes
ks_format  kf_get()
{
    return *(__geo());
}

void kf_reset()
{
    *(__geo()) = (ks_format){0,0,2,2,0};
}

void kf_zoom(float xscale, float yscale)
{
    __geo()->xz = xscale;
    __geo()->yz = yscale;
}

void kf_flip(int xflag, int yflag)
{
    __geo()->xf = xflag;
    __geo()->yf = yflag;
}

void kf_rotate(float angle)
{
    __geo()->rot = angle;
}

void kf_set(ks_format format){
    *(__geo()) = format;
}

/* ############################################ */
/* ######## FUNCOES DE TRASFORMACOES  ######### */
/* ############################################ */

#include <stdarg.h>
#include <math.h>

//ks_point ki_point_rotate(ks_point center, ks_point relative, double degrees)
//{
//    relative.x -= center.x;
//    relative.y -= center.y;
//    double angle = (-1) * ki_DEG2RAD(degrees);
//    ks_point c;
//    c.x = relative.x*cos(angle) - relative.y*sin(angle);
//    c.y = relative.y*cos(angle) + relative.x*sin(angle);

//    c.x += center.x;
//    c.y += center.y;
//    return c;
//}

void ki_decompose(double degrees, double *xcomp, double *ycomp)
{
    double angle = ki_DEG2RAD(degrees);
    *xcomp = cos(angle);
    *ycomp = sin(angle);
}

/* Return the angle in degrees from a to b */
double ki_angle(double ax, double ay, double bx, double by)
{
    return ki_RAD2DEG(atan((ax - bx)/(ay - by))+ki_M_PI);
}

void ki_coor_rot(double cx, double cy, double *prx, double *pry, double degrees)
{
    double rx = *prx;
    double ry = *pry;
    double angle = (-1) * ki_DEG2RAD(degrees);
    *prx = (rx - cx)*cos(angle) - (ry - cy)*sin(angle) + cx;
    *pry = (ry - cy)*cos(angle) + (rx - cx)*sin(angle) + cy;
}

ks_point ki_point_fmt(ks_point center, ks_point relative, ks_format fmt)
{
    if(fmt.xf)
        relative.x *= -1;

    //yflip
    if(fmt.yf)
        relative.y *= -1;

    //xscale
    relative.x *= fmt.xz;
    //yscale
    relative.y *= fmt.yz;


    //changing relative to absolute before rotating
    relative.x += center.x;
    relative.y += center.y;
    //rotate
    //relative = ki_point_rotate(center, relative, fmt.rot);
    ki_coor_rot(center.x, center.y, &relative.x, &relative.y, fmt.rot);
    return relative;
}

/* ############################################ */
/* ##### PROCESSAMENTO GENERICO DE LINHAS  #### */
/* ############################################ */


void i_kline_y(ks_point a, ks_point b, ki_plot_fn fn, const void * param)
{
    double x, y = a.y;
    double d=(b.x - a.x)/(b.y - a.y);
    while(1)//controle de parada e incremento no corpo do laco
    {
        x = a.x + (d*(y - a.y));
        fn(x, y, param);
        if(a.y < b.y)
         {
            if(y >= b.y)
                return;
            y++;
        }
        if(a.y > b.y)
        {
            if(y <= b.y)
                return;
            y--;
        }
    }
}

void i_kline_x(ks_point a, ks_point b, ki_plot_fn fn, const void * param)
{
    double x = a.x, y;
    double d=(b.y - a.y)/(b.x - a.x);

    while(1)
    {
        y = a.y + (d*(x - a.x));
        fn(x, y, param);

        if(a.x < b.x)
        {
            if(x >= b.x)
                return;
            x++;
        }
        if(a.x > b.x)
        {
            if(x <= b.x)
                return;
            x--;
        }
    }
}

void i_kline_select_axes(ks_point a, ks_point b, ki_plot_fn fn, const void *param)
{
    if(a.x == b.x && a.y == b.y){
        fn(a.x, a.y, param);
        return;
    }

    if( fabs(a.x - b.x) > fabs(a.y - b.y) )
        i_kline_x(a, b, fn, param);
    else
        i_kline_y(a, b, fn, param );
}

void ki_line_process(ks_point a, ks_point b, ki_plot_fn fn, const void *param){
    i_kline_select_axes(a, b, fn, param) ;
}

/* ############################################ */
/* ######## MODULO DE TEXTO E IMAGENS ######### */
/* ############################################ */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


void __k_draw(int px, int py, const char * head, int nlin, int ncol)
{
    ks_format tg = kf_get();
    if ( head != 0)
    {
        float dx_center = (ncol * (int)(tg.xz + 0.5))/2;
        float dy_center = (nlin * (int)(tg.yz + 0.5))/2;
        ks_point pcenter = {dx_center + px ,
                           dy_center + py };
        int xzoom = (int) tg.xz;
        int yzoom = (int) tg.yz;
        tg.xz = 1;// a transformacao de zoom ja eh computada
        tg.yz = 1;// nessa funcao
        int i, j, I, J;

        //2 for para varrer a matriz
        for( i = 0; i < nlin; i++)
        {
            for( j = 0; j < ncol; j++)
            {
                char c = head[i*ncol+j];
                if(c == ' ')
                    continue;
                if(c != '#')
                    k_color(c);
                //2 for para fazer o preenchimento do pixel
                ks_point desl;
                ks_point abs;
                for (I=0; I < yzoom; I++)
                {
                    for(J = 0; J < xzoom; J++)
                    {   //deslocamento relativo de cada ponto em relacao
                        //ao centro absoluto da imagem
                        desl =(ks_point) {j*xzoom+J-dx_center, i*yzoom+I-dy_center};
                        abs  =(ks_point) ki_point_fmt(pcenter, desl, tg);
                        ki_line(abs.x, abs.y, abs.x, abs.y);
                    }
                }
            }
        }
    }
}



void k_draw(float x, float y, const char * head, int nlin, int ncol)
{
    __k_draw(x * k_get().block, y * k_get().block, head, nlin, ncol);
}

void k_write(float x, float y, const char *format, ...)
{
    char str[1000];
    va_list args;
    va_start( args, format );
    vsprintf(str, format, args);
    va_end( args );

    ks_format tg = kf_get();
    int len = strlen(str);
    int i;
    int block = k_get().block;
    int letter = 10;
    for(i = 0; i < len; i++)
    {
        if(str[i] != '\n' && str[i]>=0 && str[i]<127)
        {
            const char * head = k_code((int) str[i]);
            __k_draw(x * block + i * tg.xz * letter, y * block,
                     head, 10, 10 );
        }
    }
    k_flush();
}

/* ############################################ */
/* ######## MODULO DE PEN            ######### */
/* ############################################ */

ks_pen kpi_new(int delay){
    ks_pen pen;
    pen.x = k_get().width/2;
    pen.y = k_get().height/2;
    pen.head = 0;
    pen.isdown  = 1;
    pen.delay   = delay;

    pen.xcenter = 0;
    pen.ycenter = 0;

    pen.fmt = (ks_format){0,0,1,1,0};
    return pen;
}

/* ##########          Lines        ########### */

void __plot_delay_wrapper( double x, double y, const void *param)
{
    ki_line( x,y, x,y);
    k_flush();
    float delay = *(float *) param;
    if(delay>1)
        ka_sleep(delay);
    else
    {
        int r = ka_rand()%100;
        if(r < delay*100)
            ka_sleep(1);
    }
}

void __plot_line(int x1,int y1,int x2,int y2, float delay){
    ki_line_process((ks_point){x1,y1}, (ks_point){x2,y2}, __plot_delay_wrapper, &delay);
}

/* ##########        Tranformacoes  ########### */

void kpi_fix(ks_pen *kp, ks_format fmt, double x, double y){
    kp->xcenter = x;
    kp->ycenter = y;
    kp->fmt = fmt;

    kp->x = 0;
    kp->y = 0;
    kp->head = 0;
    kp->isdown = 1;
}

void kpi_goto( ks_pen *kp, double xdest, double ydest)
{
    ks_point pactual ={kp->x, kp->y};
    ks_point pdest   ={xdest, ydest};
    if(kp->isdown)
    {
        ks_point center = {kp->xcenter, kp->ycenter};
        ks_point abs_orig = ki_point_fmt(center,pactual, kp->fmt);
        ks_point abs_dest = ki_point_fmt(center,pdest  , kp->fmt);
        __plot_line(abs_orig.x, abs_orig.y, abs_dest.x, abs_dest.y, kp->delay);
    }
    kp->x = xdest;
    kp->y = ydest;
}

void kpi_fd(ks_pen *kp, double px)
{
    double nx, ny;
    nx = kp->x + px*cos(ki_DEG2RAD(kp->head));
    ny = kp->y - px*sin(ki_DEG2RAD(kp->head));
    kpi_goto(kp, nx, ny );
}

void kpi_polig(ks_pen *kp, double xc, double yc, double angle, int steps)
{
    double xorigin = kp->x;
    double yorigin = kp->y;
    int i;
    for(i=0; i<steps; i ++)
    {
        double destx = xorigin, desty = yorigin;
        ki_coor_rot(xc, yc, &destx, &desty, angle/steps);
        kp_goto(destx, desty);
    }
}

/* ##########          Funcoes      ########### */

ks_pen * __kpen(){
    static ks_pen pen;
    static int init = 1;
    if(init == 1)
    {
        init = 0;
        pen = kpi_new(0);
    }
    return &pen;
}
ks_pen kp_get(){
    return *(__kpen());
}

void kp_xcor(double x){__kpen()->x = x;}
void kp_ycor(double y){__kpen()->y = y;}
void kp_delay(float delay){__kpen()->delay = delay;}
void kp_head(double head){ __kpen()->head = head; }

// estado
void kp_up()  { __kpen()->isdown = 0; }
void kp_down(){ __kpen()->isdown = 1; }

//movimentacao

/* ############### METODOS GLOBAIS ########### */
void kp_fix(double x, double y)
{
    kpi_fix(__kpen(), kf_get(), x, y);
}

void kp_unfix()
{
    *__kpen() = kpi_new(__kpen()->delay);
}

void kp_home()
{
    *(__kpen()) = kpi_new(__kpen()->delay);
}

void kp_goto(double xdest, double ydest)
{
    kpi_goto(__kpen(), xdest, ydest);
}

void kp_line(double ax, double ay, double bx, double by)
{
    kp_up();
    kp_goto(ax,ay);
    kp_down();
    kp_goto(bx, by);
}

void kp_lt (double degrees){ __kpen()->head += degrees; }
void kp_rt (double degrees){ kp_lt(degrees*(-1)); }

void kp_fd(double px)
{
    kpi_fd(__kpen(), px);
}
void kp_bk(double px) { kp_fd(px*(-1));}

void kp_polig(double xcenter, double ycenter, double angle, int steps)
{
    kpi_polig(__kpen(), xcenter, ycenter, angle, steps);
}
/* ############################################ */
/* ##### BASE DE DADOS DE CARACTERES  #### */
/* ############################################ */

const char * k_code(int code)
{
    //o ultimo asc eh o 126
    static const char * mat[127];
    static int  init = 1;
    if (init == 1)
    {
        init = 0;
        static const char asc_000[][10]={
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"},
            {"##########"}};

        static const char asc_001[][10]={
            {"##########"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"#   #    #"},
            {"#    #   #"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"##########"}};

        static const char asc_002[][10]={
            {"# # # # # "},
            {" # # # # #"},
            {"# # # # # "},
            {" # # # # #"},
            {"# # # # # "},
            {" # # # # #"},
            {"# # # # # "},
            {" # # # # #"},
            {"# # # # # "},
            {" # # # # #"}};;

        static const char asc_003[][10] ={
            {"##########"},
            {"          "},
            {"##########"},
            {"          "},
            {"##########"},
            {"          "},
            {"##########"},
            {"          "},
            {"##########"},
            {"          "}};;

        static const char asc_004[][10] ={
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "},
            {"# # # # # "}};;

        static const char asc_005[][10]={
            {"##########"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"#        #"},
            {"##########"}};

        static const char asc_006[][10]={
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "},
            {"#         "}};

        static const char asc_007[][10]={
            {"##########"},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_008[][10]={
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"},
            {"         #"}};;

        static const char asc_009[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"##########"}};

        static const char asc_010[][10]={
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {" # #  # # "},
            {" #      # "},
            {" # #  # # "},
            {" #  ##  # "},
            {"  #    #  "},
            {"   ####   "},
            {"          "}};
        //arte de Felipe Silva
        static const char asc_011[][10]={
            {"   G ggg  "},
            {"    Gg    "},
            {" RrrG rrr "},
            {"RRRrrrrmrr"},
            {"RRRrrrmmmr"},
            {"RRRrrrrmrr"},
            {"RRRRrrrrrr"},
            {"RRRRRrrrrr"},
            {" RRRRRrrr "},
            {"  RRRRRR  "}};;

        //arte de Felipe Silva
        static const char asc_012[][10]={
            {" RRR  rrr "},
            {"RRrRR rWrr"},
            {"RRrrRrrWWr"},
            {"RRRrrrrrrr"},
            {"RRRrrrrrrr"},
            {"RRRRrrrrrr"},
            {" RRRrrrrr "},
            {"  RRRrrr  "},
            {"   RRRr   "},
            {"    RR    "}};;
        //arte de Lucas Henrique
        static const char asc_013[][10]={
            {"   wwww   "},
            {"  wmmmmw  "},
            {" wmKmmKmw "},
            {" wmKmmKmw "},
            {"  wwwwww  "},
            {"    bb    "},
            {"  wbbcbw  "},
            {"  MBcbbM  "},
            {"    Bb    "},
            {"   MmMm   "}};

        static const char asc_014[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_015[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_016[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_017[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_018[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_019[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_020[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_021[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_022[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_023[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_024[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_025[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_026[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_027[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_028[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_029[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_030[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_031[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_032[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};;

        static const char asc_033[][10]={
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"          "}};

        static const char asc_034[][10]={
            {"          "},
            {"   #  #   "},
            {"   #  #   "},
            {"   #  #   "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_035[][10]={
            {"          "},
            {"   # #    "},
            {"   # #    "},
            {" #######  "},
            {"   # #    "},
            {" #######  "},
            {"   # #    "},
            {"   # #    "},
            {"          "},
            {"          "}};

        static const char asc_036[][10]={
            {"          "},
            {"          "},
            {"     #    "},
            {"   #####  "},
            {"  #  #    "},
            {"   ####   "},
            {"     # #  "},
            {"  #####   "},
            {"     #    "},
            {"          "}};

        static const char asc_037[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ##  #  "},
            {"   ## #   "},
            {"     #    "},
            {"    # ##  "},
            {"   #  ##  "},
            {"          "},
            {"          "}};

        static const char asc_038[][10]={
            {"          "},
            {"   ###    "},
            {"  #   #   "},
            {"  #  #    "},
            {"   ##     "},
            {"   # #    "},
            {"  #   #   "},
            {"   ##  #  "},
            {"          "},
            {"          "}};

        static const char asc_039[][10]={
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_040[][10]={
            {"          "},
            {"     ##   "},
            {"    #     "},
            {"   #      "},
            {"   #      "},
            {"   #      "},
            {"    #     "},
            {"     ##   "},
            {"          "},
            {"          "}};

        static const char asc_041[][10]={
            {"          "},
            {"   ##     "},
            {"     #    "},
            {"      #   "},
            {"      #   "},
            {"      #   "},
            {"     #    "},
            {"   ##     "},
            {"          "},
            {"          "}};

        static const char asc_042[][10]={
            {"          "},
            {"    #     "},
            {"   ###    "},
            {"    #     "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_043[][10]={
            {"          "},
            {"          "},
            {"    #     "},
            {"    #     "},
            {"  #####   "},
            {"    #     "},
            {"    #     "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_044[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"     #    "},
            {"    #     "}};

        static const char asc_045[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"  #####   "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_046[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"          "}};

        static const char asc_047[][10]={
            {"          "},
            {"       #  "},
            {"      #   "},
            {"     #    "},
            {"    #     "},
            {"   #      "},
            {"  #       "},
            {" #        "},
            {"          "},
            {"          "}};

        static const char asc_048[][10]={
            {"          "},
            {"  #####   "},
            {" #    ##  "},
            {" #   # #  "},
            {" #  #  #  "},
            {" # #   #  "},
            {" ##    #  "},
            {"  #####   "},
            {"          "},
            {"          "}};

        static const char asc_049[][10]={
            {"          "},
            {"    #     "},
            {"   ##     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_050[][10]={
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"       #  "},
            {"    ###   "},
            {"   #      "},
            {"  #       "},
            {"  ######  "},
            {"          "},
            {"          "}};

        static const char asc_051[][10]={
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"       #  "},
            {"   ####   "},
            {"       #  "},
            {"  #    #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_052[][10]={
            {"          "},
            {"      #   "},
            {"     ##   "},
            {"    # #   "},
            {"   #  #   "},
            {"  ######  "},
            {"      #   "},
            {"      #   "},
            {"          "},
            {"          "}};

        static const char asc_053[][10]={
            {"          "},
            {"  ######  "},
            {"  #       "},
            {"  #####   "},
            {"       #  "},
            {"       #  "},
            {"  #    #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_054[][10]={
            {"          "},
            {"    ###   "},
            {"   #      "},
            {"  #       "},
            {"  #####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_055[][10]={
            {"          "},
            {"  ######  "},
            {"      #   "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"          "},
            {"          "}};

        static const char asc_056[][10]={
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"   ####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_057[][10]={
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"   #####  "},
            {"       #  "},
            {"      #   "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_058[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"          "}};

        static const char asc_059[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"          "},
            {"    ##    "},
            {"    ##    "},
            {"     #    "},
            {"    #     "}};

        static const char asc_060[][10]={
            {"          "},
            {"      ##  "},
            {"    ##    "},
            {"   ##     "},
            {"  #       "},
            {"   ##     "},
            {"    ##    "},
            {"      ##  "},
            {"          "},
            {"          "}};

        static const char asc_061[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  ######  "},
            {"          "},
            {"  ######  "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_062[][10]={
            {"          "},
            {"  ##      "},
            {"    ##    "},
            {"     ##   "},
            {"       #  "},
            {"     ##   "},
            {"    ##    "},
            {"  ##      "},
            {"          "},
            {"          "}};

        static const char asc_063[][10]={
            {"          "},
            {"   #####  "},
            {"  #     # "},
            {"        # "},
            {"      ##  "},
            {"     #    "},
            {"          "},
            {"     #    "},
            {"          "},
            {"          "}};

        static const char asc_064[][10]={
            {"          "},
            {"   #####  "},
            {"  #     # "},
            {"  # ### # "},
            {"  # # # # "},
            {"  # ####  "},
            {"  #       "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_065[][10]={
            {"          "},
            {"   #####  "},
            {"  #     # "},
            {"  ####### "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_066[][10]={
            {"          "},
            {"  ######  "},
            {"  #     # "},
            {"  ######  "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  ######  "},
            {"          "},
            {"          "}};

        static const char asc_067[][10]={
            {"          "},
            {"   #####  "},
            {"  #     # "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  #     # "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_068[][10]={
            {"          "},
            {"  ######  "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  ######  "},
            {"          "},
            {"          "}};

        static const char asc_069[][10]={
            {"          "},
            {"   ###### "},
            {"  #       "},
            {"  #####   "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"   ###### "},
            {"          "},
            {"          "}};

        static const char asc_070[][10]={
            {"          "},
            {"   ###### "},
            {"  #       "},
            {"  #####   "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"          "},
            {"          "}};

        static const char asc_071[][10]={
            {"          "},
            {"   #####  "},
            {"  #       "},
            {"  #  #### "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_072[][10]={
            {"          "},
            {"  #     # "},
            {"  #     # "},
            {"  ####### "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_073[][10]={
            {"          "},
            {"    ###   "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"    ###   "},
            {"          "},
            {"          "}};

        static const char asc_074[][10]={
            {"          "},
            {"        # "},
            {"        # "},
            {"        # "},
            {"        # "},
            {"  #     # "},
            {"  #     # "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_075[][10]={
            {"          "},
            {"  #   #   "},
            {"  #  #    "},
            {"  ###     "},
            {"  #  #    "},
            {"  #   #   "},
            {"  #    #  "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_076[][10]={
            {"          "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  ####### "},
            {"          "},
            {"          "}};

        static const char asc_077[][10]={
            {"          "},
            {"  #     # "},
            {"  ##   ## "},
            {"  # # # # "},
            {"  #  #  # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_078[][10]={
            {"          "},
            {"  #     # "},
            {"  ##    # "},
            {"  # #   # "},
            {"  #  #  # "},
            {"  #   # # "},
            {"  #    ## "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_079[][10]={
            {"          "},
            {"   #####  "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_080[][10]={
            {"          "},
            {"  ######  "},
            {"  #     # "},
            {"  ######  "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"          "},
            {"          "}};

        static const char asc_081[][10]={
            {"          "},
            {"   #####  "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #   # # "},
            {"  #    #  "},
            {"   #### # "},
            {"          "},
            {"          "}};

        static const char asc_082[][10]={
            {"          "},
            {"  ######  "},
            {"  #     # "},
            {"  ######  "},
            {"  #  #    "},
            {"  #   #   "},
            {"  #    #  "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_083[][10]={
            {"          "},
            {"   #####  "},
            {"  #       "},
            {"   ####   "},
            {"       #  "},
            {"        # "},
            {"  #     # "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_084[][10]={
            {"          "},
            {"  ####### "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"          "},
            {"          "}};

        static const char asc_085[][10]={
            {"          "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_086[][10]={
            {"          "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"  #     # "},
            {"   #   #  "},
            {"    # #   "},
            {"     #    "},
            {"          "},
            {"          "}};

        static const char asc_087[][10]={
            {"          "},
            {"  #     # "},
            {"  #  #  # "},
            {"  #  #  # "},
            {"  #  #  # "},
            {"  #  #  # "},
            {"  #  #  # "},
            {"   ## ##  "},
            {"          "},
            {"          "}};

        static const char asc_088[][10]={
            {"          "},
            {"  #     # "},
            {"   #   #  "},
            {"    # #   "},
            {"     #    "},
            {"    # #   "},
            {"   #   #  "},
            {"  #     # "},
            {"          "},
            {"          "}};

        static const char asc_089[][10]={
            {"          "},
            {"  #     # "},
            {"   #   #  "},
            {"    # #   "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"          "},
            {"          "}};

        static const char asc_090[][10]={
            {"          "},
            {"  ####### "},
            {"       #  "},
            {"      #   "},
            {"     #    "},
            {"    #     "},
            {"   #      "},
            {"  ####### "},
            {"          "},
            {"          "}};

        static const char asc_091[][10]={
            {"          "},
            {"   ###    "},
            {"   #      "},
            {"   #      "},
            {"   #      "},
            {"   #      "},
            {"   #      "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_092[][10]={
            {"          "},
            {" #        "},
            {"  #       "},
            {"   #      "},
            {"    #     "},
            {"     #    "},
            {"      #   "},
            {"       #  "},
            {"          "},
            {"          "}};

        static const char asc_093[][10]={
            {"          "},
            {"   ###    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"     #    "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_094[][10]={
            {"          "},
            {"    #     "},
            {"   # #    "},
            {"  #   #   "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_095[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"  ######  "},
            {"          "},
            {"          "}};

        static const char asc_096[][10]={
            {"          "},
            {"    #     "},
            {"     #    "},
            {"      #   "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        static const char asc_097[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ####   "},
            {"       #  "},
            {"   #####  "},
            {"  #    #  "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_098[][10]={
            {"          "},
            {"  #       "},
            {"  #       "},
            {"  # ###   "},
            {"  ##   #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #####   "},
            {"          "},
            {"          "}};

        static const char asc_099[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ####   "},
            {"  #       "},
            {"  #       "},
            {"  #    #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_100[][10]={
            {"          "},
            {"       #  "},
            {"       #  "},
            {"   ### #  "},
            {"  #   ##  "},
            {"  #    #  "},
            {"  #    #  "},
            {"   #####  "},
            {"          "},
            {"          "}};

        static const char asc_101[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"  #####   "},
            {"  #       "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_102[][10]={
            {"          "},
            {"     ###  "},
            {"    #     "},
            {"  ######  "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"  ##      "}};

        static const char asc_103[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"   #####  "},
            {"       #  "},
            {"  #####   "}};

        static const char asc_104[][10]={
            {"          "},
            {"  #       "},
            {"  #       "},
            {"  # ###   "},
            {"  ##   #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"          "},
            {"          "}};

        static const char asc_105[][10]={
            {"          "},
            {"    #     "},
            {"          "},
            {"   ##     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_106[][10]={
            {"          "},
            {"      #   "},
            {"          "},
            {"      #   "},
            {"     ##   "},
            {"    # #   "},
            {"      #   "},
            {"      #   "},
            {"  #   #   "},
            {"   ###    "}};

        static const char asc_107[][10]={
            {"          "},
            {"   #      "},
            {"   #   #  "},
            {"   #  #   "},
            {"   ###    "},
            {"   # #    "},
            {"   #  #   "},
            {"   #   #  "},
            {"          "},
            {"          "}};

        static const char asc_108[][10]={
            {"          "},
            {"   ##     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_109[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #    #  "},
            {"  ##  ##  "},
            {"  # ## #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"          "},
            {"          "}};

        static const char asc_110[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  # ###   "},
            {"  ##   #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"          "},
            {"          "}};

        static const char asc_111[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_112[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #####   "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #####   "},
            {"  #       "},
            {"  #       "}};

        static const char asc_113[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ### #  "},
            {"  #   ##  "},
            {"  #    #  "},
            {"  #    #  "},
            {"   #####  "},
            {"       #  "},
            {"       #  "}};

        static const char asc_114[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  # ##    "},
            {"  ##  #   "},
            {"  #       "},
            {"  #       "},
            {"  #       "},
            {"          "},
            {"          "}};

        static const char asc_115[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   ####   "},
            {"  #       "},
            {"   ####   "},
            {"       #  "},
            {"   ####   "},
            {"          "},
            {"          "}};

        static const char asc_116[][10]={
            {"          "},
            {"   #      "},
            {"   #      "},
            {"  ###     "},
            {"   #      "},
            {"   #      "},
            {"   #  #   "},
            {"    ##    "},
            {"          "},
            {"          "}};

        static const char asc_117[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #   ##  "},
            {"   ### #  "},
            {"          "},
            {"          "}};

        static const char asc_118[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #     # "},
            {"  #     # "},
            {"   #   #  "},
            {"    # #   "},
            {"     #    "},
            {"          "},
            {"          "}};

        static const char asc_119[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #     # "},
            {"  #     # "},
            {"  #  #  # "},
            {"  # # # # "},
            {"   #   #  "},
            {"          "},
            {"          "}};

        static const char asc_120[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"   #   #  "},
            {"    # #   "},
            {"     #    "},
            {"    # #   "},
            {"   #   #  "},
            {"          "},
            {"          "}};

        static const char asc_121[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #    #  "},
            {"  #   ##  "},
            {"   ### #  "},
            {"       #  "},
            {"   ####   "}};

        static const char asc_122[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  #####   "},
            {"     #    "},
            {"    #     "},
            {"   #      "},
            {"  #####   "},
            {"          "},
            {"          "}};

        static const char asc_123[][10]={
            {"          "},
            {"   ###    "},
            {"   #      "},
            {"   #      "},
            {"  #       "},
            {"   #      "},
            {"   #      "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_124[][10]={
            {"          "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"    #     "},
            {"          "},
            {"          "}};

        static const char asc_125[][10]={
            {"          "},
            {"   ###    "},
            {"     #    "},
            {"     #    "},
            {"      #   "},
            {"     #    "},
            {"     #    "},
            {"   ###    "},
            {"          "},
            {"          "}};

        static const char asc_126[][10]={
            {"          "},
            {"          "},
            {"          "},
            {"  ###  #  "},
            {"  #  ###  "},
            {"          "},
            {"          "},
            {"          "},
            {"          "},
            {"          "}};

        mat[0] = &(asc_000[0][0]);
        mat[1] = &(asc_001[0][0]);
        mat[2] = &(asc_002[0][0]);
        mat[3] = &(asc_003[0][0]);
        mat[4] = &(asc_004[0][0]);
        mat[5] = &(asc_005[0][0]);
        mat[6] = &(asc_006[0][0]);
        mat[7] = &(asc_007[0][0]);
        mat[8] = &(asc_008[0][0]);
        mat[9] = &(asc_009[0][0]);
        mat[10] = &(asc_010[0][0]);
        mat[11] = &(asc_011[0][0]);
        mat[12] = &(asc_012[0][0]);
        mat[13] = &(asc_013[0][0]);
        mat[14] = &(asc_014[0][0]);
        mat[15] = &(asc_015[0][0]);
        mat[16] = &(asc_016[0][0]);
        mat[17] = &(asc_017[0][0]);
        mat[18] = &(asc_018[0][0]);
        mat[19] = &(asc_019[0][0]);
        mat[20] = &(asc_020[0][0]);
        mat[21] = &(asc_021[0][0]);
        mat[22] = &(asc_022[0][0]);
        mat[23] = &(asc_023[0][0]);
        mat[24] = &(asc_024[0][0]);
        mat[25] = &(asc_025[0][0]);
        mat[26] = &(asc_026[0][0]);
        mat[27] = &(asc_027[0][0]);
        mat[28] = &(asc_028[0][0]);
        mat[29] = &(asc_029[0][0]);
        mat[30] = &(asc_030[0][0]);
        mat[31] = &(asc_031[0][0]);
        mat[32] = &(asc_032[0][0]);
        mat[33] = &(asc_033[0][0]);
        mat[34] = &(asc_034[0][0]);
        mat[35] = &(asc_035[0][0]);
        mat[36] = &(asc_036[0][0]);
        mat[37] = &(asc_037[0][0]);
        mat[38] = &(asc_038[0][0]);
        mat[39] = &(asc_039[0][0]);
        mat[40] = &(asc_040[0][0]);
        mat[41] = &(asc_041[0][0]);
        mat[42] = &(asc_042[0][0]);
        mat[43] = &(asc_043[0][0]);
        mat[44] = &(asc_044[0][0]);
        mat[45] = &(asc_045[0][0]);
        mat[46] = &(asc_046[0][0]);
        mat[47] = &(asc_047[0][0]);
        mat[48] = &(asc_048[0][0]);
        mat[49] = &(asc_049[0][0]);
        mat[50] = &(asc_050[0][0]);
        mat[51] = &(asc_051[0][0]);
        mat[52] = &(asc_052[0][0]);
        mat[53] = &(asc_053[0][0]);
        mat[54] = &(asc_054[0][0]);
        mat[55] = &(asc_055[0][0]);
        mat[56] = &(asc_056[0][0]);
        mat[57] = &(asc_057[0][0]);
        mat[58] = &(asc_058[0][0]);
        mat[59] = &(asc_059[0][0]);
        mat[60] = &(asc_060[0][0]);
        mat[61] = &(asc_061[0][0]);
        mat[62] = &(asc_062[0][0]);
        mat[63] = &(asc_063[0][0]);
        mat[64] = &(asc_064[0][0]);
        mat[65] = &(asc_065[0][0]);
        mat[66] = &(asc_066[0][0]);
        mat[67] = &(asc_067[0][0]);
        mat[68] = &(asc_068[0][0]);
        mat[69] = &(asc_069[0][0]);
        mat[70] = &(asc_070[0][0]);
        mat[71] = &(asc_071[0][0]);
        mat[72] = &(asc_072[0][0]);
        mat[73] = &(asc_073[0][0]);
        mat[74] = &(asc_074[0][0]);
        mat[75] = &(asc_075[0][0]);
        mat[76] = &(asc_076[0][0]);
        mat[77] = &(asc_077[0][0]);
        mat[78] = &(asc_078[0][0]);
        mat[79] = &(asc_079[0][0]);
        mat[80] = &(asc_080[0][0]);
        mat[81] = &(asc_081[0][0]);
        mat[82] = &(asc_082[0][0]);
        mat[83] = &(asc_083[0][0]);
        mat[84] = &(asc_084[0][0]);
        mat[85] = &(asc_085[0][0]);
        mat[86] = &(asc_086[0][0]);
        mat[87] = &(asc_087[0][0]);
        mat[88] = &(asc_088[0][0]);
        mat[89] = &(asc_089[0][0]);
        mat[90] = &(asc_090[0][0]);
        mat[91] = &(asc_091[0][0]);
        mat[92] = &(asc_092[0][0]);
        mat[93] = &(asc_093[0][0]);
        mat[94] = &(asc_094[0][0]);
        mat[95] = &(asc_095[0][0]);
        mat[96] = &(asc_096[0][0]);
        mat[97] = &(asc_097[0][0]);
        mat[98] = &(asc_098[0][0]);
        mat[99] = &(asc_099[0][0]);
        mat[100] = &(asc_100[0][0]);
        mat[101] = &(asc_101[0][0]);
        mat[102] = &(asc_102[0][0]);
        mat[103] = &(asc_103[0][0]);
        mat[104] = &(asc_104[0][0]);
        mat[105] = &(asc_105[0][0]);
        mat[106] = &(asc_106[0][0]);
        mat[107] = &(asc_107[0][0]);
        mat[108] = &(asc_108[0][0]);
        mat[109] = &(asc_109[0][0]);
        mat[110] = &(asc_110[0][0]);
        mat[111] = &(asc_111[0][0]);
        mat[112] = &(asc_112[0][0]);
        mat[113] = &(asc_113[0][0]);
        mat[114] = &(asc_114[0][0]);
        mat[115] = &(asc_115[0][0]);
        mat[116] = &(asc_116[0][0]);
        mat[117] = &(asc_117[0][0]);
        mat[118] = &(asc_118[0][0]);
        mat[119] = &(asc_119[0][0]);
        mat[120] = &(asc_120[0][0]);
        mat[121] = &(asc_121[0][0]);
        mat[122] = &(asc_122[0][0]);
        mat[123] = &(asc_123[0][0]);
        mat[124] = &(asc_124[0][0]);
        mat[125] = &(asc_125[0][0]);
        mat[126] = &(asc_126[0][0]);
    }
    return mat[code];
}
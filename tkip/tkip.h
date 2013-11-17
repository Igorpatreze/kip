/*
 * [Autor]
 * David Sena
 * sena.ufc@gmail.com
 *
 */

#ifndef TKIP_H
#define TKIP_H

/* Muda a cor da letra
 * r,g,b,y,c,m,k,w para cores claras
 * R,G,B,Y,C,M,K,W para cores escuras */
void tk_color(char color);

/* Limpa o fundo */
void tk_clear();

/* Escreve na posicao x,y o texto usando a sintaxe de printf
 * ex:  k_write(10,5,"oi");
 * ex:  k_write(12,6,"%d %c", idade, sexo); */
void tk_write(int x, int y, const char *format, ...);

/* Se houver alguma tecla no teclado ele retorna a tecla,
 * caso contrário, retorna 0  */
int tk_peek(void);

/* Trava e so retorna quando o usuario digitar uma tecla */
int tk_wait(void);

/* Faz o programa dormir por mseg, em milesegundos */
void tk_sleep(int msec);

/* Retorna um número aleatorio */
int  tkm_rand();

/* Toca um mp3 se tiver o programa mpg123 instalado */
void tk_mp3_play(char *path);

/* Interrompe um mp3 que esteja tocando */
void tk_mp3_stop(char *path);

/* Retorna o vetor com as 16 cores */
const char * tk_info_colors();
#endif

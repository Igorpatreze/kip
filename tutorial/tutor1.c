/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) David Sena, 2013
 */

/* Ola, o objetivo desse codigo eh ensina-lo a usar algumas funcoes
 * graficas para podermos desenvolver alguma logica de jogos.
 * Os comentarios nao terao acentos. E algumas acentuacoes serao
 * feitas com h.
 */

/* Para compilar esse codigo voce precisa instalar a biblioteca grafica
 * para c chamada kfup. No ubuntu basta executar a linha abaixo no terminal

 wget https://raw.github.com/senapk/dfx/master/dfx_install_v2.sh;sh dfx_install_v2.sh;

 * Se voce nao esta no ubuntu, acesse o site: https://github.com/senapk/dfx
 * e leia as instrucoes.
 *
 * Esse tutorial eh interativo, quando for solicitado, pare e execute as
 * instrucoes ou nao conseguira prosseguir.
 *
 * Pra compilar esse codigo, a maneira mais facil eh abrir o terminal onde
 * este codigo se encontra, e digitar

 gccx tutor1.c -o tutor1

 * Se estiver utilizando o codeblocks, crie um projeto e faça o seguinte:
 *
    Ir em:
    Settings, Compiler, Linker
    Adicionar o path para os dois arquivos:
    /usr/local/lib/libkfup.a
    /usr/lib/libX11.so

 */


// incluindo a biblioteca
#include <kfup.h> //esse arquivo se encontra em /usr/local/include/dfx.h

int main(){

    /* Para ter uma tela grafica usamos a abstracao de canvas, que significa
     * em ingles uma tela de desenho. Atraves da funcao canvas_open nos ini-
     * ciamos a janela grafica. Neste exemplo sao 800 pixels de largura, 600
     * de altura e o nome Minha Janela
     */

    canvas_open(800,600,"Minha Janela");
    event_get();
    /*
     * A segunda abstracao que vamos necessitar eh a abstracao de event, que re-
     * presenta um evento de mouse ou de teclado. A funcao event_get() vai
     * bloquear a execucao do codigo ate que alguma tecla seja pressionada
     * ou algum botao do mouse clicado. Sem ele, a janela aparece, mas ime-
     * diatamente some, por isso nao esqueça de colocá-lo.
     *
     * Acao 1: Execute o codigo e veja a janela.*/


    /* Tarefa 2:
     * Vamos escrever algo na nossa janela. A terceira abstracao eh a de pen,
     * pen significa pincel ou caneta. Sera com esses metodos que faremos as
     * primeiras escritas na nossa tela. Com a funcao pen_write() voce pode
     * escrever utilizando a mesma sintaxe do printf, usando variaveis, etc.
     * Vamos escrever Ola Mundo. Descomente o Alvo2. Comente o event_get()
     * do exemplo passado e descomente o alvo dois.*/

    //Alvo 2 - INICIO
    /*
    pen_write("Ola mundo \nVoltei pro inicio \n");
    pen_write("Dez dividido por 3 eh %.2f", (double)10/3);
    event_get();
    */
    //Alvo 2 - FIM

    /* Tarefa 3:
     * Vamos aprender mais alguns metodos sobre pen. pen_move(int x, int y)
     * movimenta o pincel para o bloco x, y. Normalmente em telas graficas,
     * o x e o y sao 0 na quina superior esquerda. x cresce para direita e y
     * cresce para baixo. pen_move faz o pincel andar em blocos, algo pare-
     * cido com o terminal que voce esta acostumado. O codigo abaixo move o
     * pincel para x=3 e y =10, como se fosse a linha 10 coluna 3, e coloca
     * o caractere x com pen_write(). Descomente e execute. Depois tente
     * alterar o codigo para se mover para outros lugares. */

    /*Alvo 3 - INICIO*/
    /*
    pen_move(3,10);
    pen_write("x");
    event_get();
    */
    //Alvo 3 - FIM

    /* Tarefa 4:
     * O path da biblioteca grafica eh
     * usr/local/include/kfup.h . Se der uma olhada vai achar todas as funcoes
     * basicas que estamos usando.
     *
     * Jah vimos a funcao canvas_open que cria a tela.
     * A funcao canvas_clear limpa a tela. Nosso objetivo eh fazer o x
     * atravessar a tela andando. Vamos criar um laco que altere os valores de
     * x e a cada interacao vamos limpar a tela, mover o cursor, pintar o
     * x e esperar uma tecla, se quiser pode comentar os alvos 1, 2 e 3 */

    /*Alvo 4 - INICIO*/
    /*
    for(int i = 0;i<10;i++){//como o dfx compila usando a versao c de 1999, voce
        canvas_clear();     //pode instanciar o i dentro do for
        pen_move(i,10);
        pen_write("x");
        event_get();
    }
    */
    //Alvo 4 - FIM

    /* Tarefa 5:
     * Para facilitar a nossa vida, voce tambem tem uma funcao de sleep embutida
     * na abstracao de util. Se digitar util_msleep( int mseg ), voce tem uma fun-
     * cao que para o codigo por tantos milessegundos.
     * Descomente o codigo abaixo e execute.
     *
     * Nele, limpamos a tela, plotamos o x no lugar dele, forcamos que essa informa-
     * cao apareca na tela antes do sleep com canvas_update e damos o sleep.
     *
     * Canvas_update eh automaticamente executado em todo event_get(). Como o codigo
     * abaixo nao efetua bloqueio com event_get, entao o canvas_update eh necessario.
     */
    /*
    for(int i = 0;i<10;i++){//como o dfx compila usando a versao c de 1999, voce
        canvas_clear();     //pode instanciar o i dentro do for
        pen_move(i,12);
        pen_write("y");
        canvas_update();
        util_msleep(500);
    }
    */

    /* Tarefa 6:
     * O zoom default eh de 2, isso significa que cada bloco tem 20 pixels de altura
     * e 20 de largura, o zoom determina o tamanho da letra, a ampliacao dos desenhos,
     * e a forma como pen_move salta na tela. pen_move(3,4) com o zoom default
     * significa dizer: pule para o pixel x = 3*20=60, y = 4*20 = 80. Eh possivel
     * alterar o zoom a qualquer momento com as funcoes de font. font_zoom( int fator),
     * muda o fator default de 2 para qualquer que deseje. Faca o seguinte,
     * antes do alvo 4 coloque font_zoom(5), ou font_zoom(1) e veja o que acontece.
     * Se voce fez isso, percebeu que o x ficou maior, como tambem ficou mais
     * la no fundo da tela. Isso eh porque agora cada bloco tem 50 pixeis. Quando voce
     * faz um pen_moveb(1,10) vai para posicao x=50, y=500*/

    /* Tarefa 7:
     * Continuando. Comente os alvos anteriores. Nossa meta agora eh escrever textos
     * coloridos e com tamanhos diferentes. Com font voce tem opcao de mudar a cor
     * de risco com font_color, a cor de clear  com font_clear_color, o zoom com
     * font_zoom, alem de retirar o monoespacado para deixar o texto mais armonioso.
     * As cores podem ser colocadas usando as enumeracoes do dfx.h, que seguem o padrao
     * color_GREEN para verde escuro ou color_green para verde claro. Temos as cores,
     * white, black, green, red, blue, cyan, magenta. Descomente o alvo 7. Leia o
     * codigo e perceba o que esta acontecendo. Ao final que tal tentar escrever algumas
     * frase coloridas na tela.
     *
     * Descomente o Alvo 7. Execute.
     */

    //Alvo 7 -INICIO
    /*
    font_zoom(2);//mudando o zoom para 2
    pen_move(3,3);//movendo para o bloco 3,3
    font_clear_color(color_white);//mudando a cor de clear para branco
    canvas_clear();//fazendo o clear de branco
    font_color(color_BLUE);//mudando a cor do pincel para azul
    pen_write("O ceu eh azul e as nuvens brancas\n");//escrevendo em azul
    font_mono_on();//numa font monoespacada toda letra ocupa o mesmo espaco
    pen_write("O ceu eh azul e as nuvens brancas\n");//escrevendo em azul
    font_mono_off();//desabilitando mono
    font_color(color_RED);//mudando o pincel para vermelho
    font_zoom_xy(3,4);//colocando o zoom em x =3 e em y =4, letras mais estiradas
    pen_write("Grande vermelho\n");
    font_zoom(1);
    font_color(color_BLACK);
    pen_write("Leia-me se for capaz\n");//escrevendo em azul
    event_get();
    */
    //Alvo 7 -FIM

    /* Tarefa 8:
     * Para iniciar, comente o alvo 7. Que tal uma animacao mais suave agora.
     * Voce ja viu a funcao pen_move, que move em blocos. Pois bem, pen_pix
     * move em pixeis.
     * Voce conheceu canvas_open e canvas_clear. Para atualizar a tela dentro de
     * um laco sem interrupcoes de evento como event_get() voce precisa dar um
     * comando de canvas_update(), isso forca o desenho a ser desenhado antes de
     * dormir.
     * Vamos fazer o '@' cair usando a funcao pen_pix para um movimento
     * mais suave, canvas_update() para repintar a tela em cada interacao,
     * util_msleep() para dar um sleep no loop.
     *
     * O bomberman tem uma posicao em y e uma velocidade em y.
     * A cada laco essa velocidade aumenta.
     * Se o py passar da posicao 580, 600 - 20(tamanho da letra)
     * eu inverto a velocidade fazendo a letra imediatamente mover-se
     * pra cima.
     *
     * A cada interacao verificamos se alguma tecla ou clique foi pressionada
     * com a funcao event_is_waiting(). Se alguma tiver sido, entao
     * saimos do codigo
     *
     * Descomente o alvo 8. Execute.
     */

    //Alvo 8 - INICIO
    /*
    float py = 0; //representa a posicao do bomberman
    float vy = 0; //representa a velocidade vertical do bomberman
    font_zoom(2);
    pen_pix(400,py); //movendo para o topo da tela no meio

    while(1){
        canvas_clear();
        vy=vy+0.4;//aumentando a velocidade para baixo
        py = py + vy; //atualizando a posicao atraves da velocidade

        pen_pix(400, py);//movendo o pincel para posicao que vou desenha o bomberman
        pen_write("@");
        canvas_update();//forcando a tela a redesenhar antes de dar o sleep
        util_msleep(50);
        if(py>580){//o bomberman tem 20 pixeis de altura, se os pes dele tocam o fundo
            py=580;//que eh 600, eh porque a cabeca estah ou passou dos 580. Se isso
            vy=-vy;//acontecer eu forco a posicao a ser 580 e inverto a velocidade
        }
        if(event_is_waiting())//funcao nao bloqueante, avisa se teve algum evento
            break;//sai do while
    }
    */
    //Alvo 8 - FIM

    /* Tarefa 9:
     * Legal o bomberman pulando né. Que tal destrui-lo agora? A funcao event_is_waiting()
     * retorna 1 se foi uma tecla foi pressionada ou um botao do mouse clicado
     * Se algum desses eventos acontecer, ele pode ser obtido atraves
     * de event_get(). Comente o codigo do Alvo 8, vamos reproduzi-lo abaixo com algumas
     * modificacoes.
     *
     * Vou usar uma variavel char sym para definir o simbolo do boneco que inicia em 'b'
     * Vou passar essa variavel como parametro para imprimir o boneco.
     *
     * Vamos fazer uma verificacao de evento. Se for um evento de teclado, vamos pegar essa tecla
     * e colocar como o novo simbolo do boneco.
     *
     * Se for o botao esquerdo do mouse, vamos teleportar o bomberman para a posicao do clique.
     * Se for o botao do meio, vamos paralisa-lo. Se for o direito, invertemos a velocidade.
     * Se rodar a bolinha do mouse pra frente, dobramos a velocidade.
     * Se for pra tras, diminuimos a velocidade.
     *
     * Descomente o Alvo 9. Execute.
     */


    //Alvo 9 - INICIO
    float px = 400;
    float py = 0; //representa a posicao do boneco.
    float vy = 0; //representa a velocidade vertical do boneco.
    char sym = 'b';//o simbolo do boneco
    font_zoom(2);
    pen_pix(px,py); //movendo para a posicao px, py

    while(1){
        canvas_clear();
        vy=vy+0.3;//aumentando a velocidade para baixo
        py = py + vy; //atualizando a posicao atraves da velocidade

        pen_pix(px, py);//movendo o pincel para posicao que vou desenha o boneco.
        pen_write("%c",sym);
        canvas_update();//mandando a tela a redesenhar antes de dar o sleep
        util_msleep(50);
        if(py>580){//o bomberman tem 20 pixeis de altura. Se os pes dele tocam o fundo
            py=580;//que eh 600, eh porque a cabeca estah ou passou dos 580. Se isso
            vy=-vy;//acontecer eu forco a posicao a ser 580 e inverto a velocidade
        }
        if(event_is_waiting()){
            char c = event_get();//representa o evento
            if(c > 32)
                sym = c;

            if (c == click_LEFT){ //vou teleportar a letra
                px = event_get_pos_x();//alterando as variaveis que determinam a posicao da letra
                py = event_get_pos_y();
            }
            if(c == click_MIDDLE)//ou c==2, vou paraliza-lo, zerando a velocidade
                vy = 0;
            if(c == click_RIGHT)//ou c ==3, vou faze-lo ricochetear seja subindo ou descendo
                vy = -vy;
            if(c == click_UP)//ou c ==4, vou duplicar a velocidade
                vy = 2*vy;
            if(c == click_DOWN)//ou c ==5, vou reduzir a velocidade
                vy = vy/2;
        }

    }
    //Alvo 9 - FIM


    return 0;
}



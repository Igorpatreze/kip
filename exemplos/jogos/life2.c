#include <kip.h>
#include <stdio.h>

//#define ALTURA 34
#define ALTURA 70
//#define LARGURA 68
#define LARGURA 130
#define VIVA 1
#define MORTA 0

float delay = 0;

char celula[] = "\
######### \
######### \
######### \
######### \
######### \
######### \
######### \
######### \
######### \
          ";

char play[] = "\
          \
rrRrrrrrr \
rrRRrrrrr \
rrRRRrrrr \
rrRRRRrrr \
rrRRRRRrr \
rrRRRRrrr \
rrRRRrrrr \
rrRRrrrrr \
rrRrrrrrr ";

char next[] = "\
          \
rrrrrrrrr \
rrrrrrrrr \
rRrrRrrRr \
rRRrRRrRr \
rRRRRRRRr \
rRRrRRrRr \
rRrrRrrRr \
rrrrrrrrr \
rrrrrrrrr ";

char pause[] = "\
          \
rrrrrrrrr \
rRRRrRRRr \
rRRRrRRRr \
rRRRrRRRr \
rRRRrRRRr \
rRRRrRRRr \
rRRRrRRRr \
rRRRrRRRr \
rrrrrrrrr ";

char clean[] = "\
                    \
rrrrrrrrrrrrrrrrrrr \
rrrrrrrrrrrrrrrrrrr \
rrRRRRrRrrrrRRrrRrr \
rrRrrrrRrrrrRrRrRrr \
rrRrrrrRrrrrRrRrRrr \
rrRrrrrRrrrrRrRrRrr \
rrRRRRrRRRRrRrrRRrr \
rrrrrrrrrrrrrrrrrrr \
rrrrrrrrrrrrrrrrrrr ";

char um[] = "\
          \
rrrrrrrrr \
rrrrrrrrr \
rrrRRrrrr \
rrRrRrrrr \
rrrrRrrrr \
rrrrRrrrr \
rrrrRrrrr \
rrrrrrrrr \
rrrrrrrrr ";

char dois[] = "\
          \
rrrrrrrrr \
rrrrrrrrr \
rrrRRRrrr \
rrrrrRrrr \
rrrRRRrrr \
rrrRrrrrr \
rrrRRRrrr \
rrrrrrrrr \
rrrrrrrrr ";

char tres[] ="\
          \
rrrrrrrrr \
rrrrrrrrr \
rrrRRRrrr \
rrrrrRrrr \
rrrRRRrrr \
rrrrrRrrr \
rrrRRRrrr \
rrrrrrrrr \
rrrrrrrrr ";

char quatro[] = "\
          \
rrrrrrrrr \
rrrrrrrrr \
rrrRrRrrr \
rrrRrRrrr \
rrrRRRrrr \
rrrrrRrrr \
rrrrrRrrr \
rrrrrrrrr \
rrrrrrrrr ";

char cinco[] = "\
          \
rrrrrrrrr \
rrrrrrrrr \
rrrRRRrrr \
rrrRrrrrr \
rrrRRRrrr \
rrrrrRrrr \
rrrRRRrrr \
rrrrrrrrr \
rrrrrrrrr ";

char seis[] = "\
          \
rrrrrrrrr \
rrrrrrrrr \
rrrRRRrrr \
rrrRrrrrr \
rrrRRRrrr \
rrrRrRrrr \
rrrRRRrrr \
rrrrrrrrr \
rrrrrrrrr ";

int matriz[LARGURA][ALTURA];
int automatico = 0;
int played = 1;

void gerar_Tela();
void mostrar_Celula(int x, int y, int estado);
void mostrar_Matriz(int mat[LARGURA][ALTURA]);
void inicializar_Matriz(int mat[LARGURA][ALTURA]);
void verificar_Matriz(int mat[LARGURA][ALTURA]);
void verificar_Peca(int mat[LARGURA][ALTURA], int mat2[LARGURA][ALTURA], int i,  int j);
void atualiza_Matriz(int mat[LARGURA][ALTURA], int mat_2[LARGURA][ALTURA]);
void atualiza_Matriz_2(int vizinhos, int mat_2[LARGURA][ALTURA], int i, int j);
int pegar_Evento();
void carregar_Exemplos_Basicos(int mat[LARGURA][ALTURA]);
void carregar_Pulsar(int mat[LARGURA][ALTURA]);
void carregar_Diehard(int mat[LARGURA][ALTURA]);
void carregar_Acorn(int mat[LARGURA][ALTURA]);
void carregar_GliderGun(int mat[LARGURA][ALTURA]);
void carregar_GG(int mat[LARGURA][ALTURA]);
void mostrarBotoes();

int main(){
	gerar_Tela();
	inicializar_Matriz(matriz);
	k_clear('K');
	mostrar_Matriz(matriz);

	while(1) {
		if(automatico){
			verificar_Matriz(matriz);
			mostrar_Matriz(matriz);
			pegar_Evento();
		} else {
			if(pegar_Evento(matriz))
			mostrar_Matriz(matriz);
		}
		mostrarBotoes();
		k_sleep(delay);
	}
	return 0;

}

int pegar_Evento(){
    char c = k_peek();
    if(c) {
        if(c == CLICK_LEFT) {
            int x = k_xpos();
            int y = k_ypos();
            //printf("X = %d\t Y = %d\n", x, y);
            if(y >= ALTURA) {
                if(x == 0) {
                    played = (played+1) % 2;
                    if(played == 1) automatico = 0;
                    else automatico = 1;
                } else if(x == 2) {
                    verificar_Matriz(matriz);
                } else if(x == 4 || x == 5) {
                    inicializar_Matriz(matriz);
                } else if(x == 7) {
                    carregar_Exemplos_Basicos(matriz);
                } else if(x == 8) {
                    carregar_Pulsar(matriz);
                } else if(x == 9) {
                    carregar_Diehard(matriz);
                } else if(x == 10) {
                    carregar_Acorn(matriz);
                } else if(x == 11) {
                    carregar_GliderGun(matriz);
                } else if(x == 12) {
                    carregar_GG(matriz);
                } else if(x == 14) {
                    delay /= 2;
                } else if(x == 15) {
                    delay += 10;
                }
            } else matriz[x][y] = (matriz[x][y] + 1) % 2;
        } else if(c == KEY_ENTER) {
            verificar_Matriz(matriz);
        } else if(c == ' ') {
            automatico = (automatico+1) % 2;
            played = (played+1) % 2;
        } else if(c == 'c') {
            inicializar_Matriz(matriz);
        } else if(c == '1') {
            carregar_Exemplos_Basicos(matriz);
        } else if(c == '2') {
            carregar_Pulsar(matriz);
        } else if(c == '3') {
            carregar_Diehard(matriz);
        } else if(c == '4') {
            carregar_Acorn(matriz);
        } else if(c == '5') {
            carregar_GliderGun(matriz);
        } else if(c == '6') {
            carregar_GG(matriz);
        }
        return 1;
    }
    return 0;
}

void carregar_GG(int mat[LARGURA][ALTURA]){
	inicializar_Matriz(matriz);
	mat[13][2] = VIVA;
	mat[12][3] = VIVA;
	mat[13][3] = VIVA;
	mat[12][4] = VIVA;
	mat[11][5] = VIVA;
	mat[11][6] = VIVA;
	mat[11][4] = VIVA;
	mat[12][5] = VIVA;
	mat[12][6] = VIVA;
	mat[10][5] = VIVA;
	mat[12][7] = VIVA;
	mat[13][7] = VIVA;
	mat[13][8] = VIVA;
	mat[18][4] = VIVA;
	mat[17][4] = VIVA;
	mat[17][5] = VIVA;
	mat[18][5] = VIVA;
	mat[18][6] = VIVA;
	mat[17][6] = VIVA;
	mat[20][3] = VIVA;
	mat[21][4] = VIVA;
	mat[22][5] = VIVA;
	mat[24][5] = VIVA;
	mat[24][6] = VIVA;
	mat[23][4] = VIVA;
	mat[23][3] = VIVA;
	mat[23][2] = VIVA;
	mat[22][1] = VIVA;
	mat[21][2] = VIVA;
	mat[24][1] = VIVA;
	mat[24][0] = VIVA;
	mat[35][2] = VIVA;
	mat[36][2] = VIVA;
	mat[36][3] = VIVA;
	mat[35][3] = VIVA;
	mat[2][4] = VIVA;
	mat[1][4] = VIVA;
	mat[1][5] = VIVA;
	mat[2][5] = VIVA;
	//glider1
	mat[25][9] = VIVA;
	mat[25][11] = VIVA;
	mat[26][10] = VIVA;
	mat[26][11] = VIVA;
	mat[24][11] = VIVA;
	//glider2
	mat[31][18] = VIVA;
	mat[32][19] = VIVA;
	mat[33][19] = VIVA;
	mat[33][18] = VIVA;
	mat[33][17] = VIVA;

	mat[33][25] = VIVA;
	mat[34][25] = VIVA;
	mat[34][26] = VIVA;
	mat[32][26] = VIVA;
	mat[32][27] = VIVA;
	mat[32][28] = VIVA;
	mat[31][28] = VIVA;
	mat[37][24] = VIVA;
	mat[38][24] = VIVA;
	mat[38][23] = VIVA;
	mat[37][23] = VIVA;
	mat[37][22] = VIVA;
	mat[38][22] = VIVA;
	mat[39][21] = VIVA;
	mat[40][20] = VIVA;
	mat[41][21] = VIVA;
	mat[39][25] = VIVA;
	mat[40][26] = VIVA;
	mat[41][25] = VIVA;
	mat[42][22] = VIVA;
	mat[42][23] = VIVA;
	mat[42][24] = VIVA;
	mat[52][22] = VIVA;
	mat[53][22] = VIVA;
	mat[53][23] = VIVA;
	mat[52][23] = VIVA;
}

void carregar_Diehard(int mat[LARGURA][ALTURA]){
	inicializar_Matriz(matriz);
	mat[31][17] = VIVA;
	mat[32][17] = VIVA;
	mat[32][18] = VIVA;
	mat[36][18] = VIVA;
	mat[37][18] = VIVA;
	mat[38][18] = VIVA;
	mat[37][16] = VIVA;
}

void carregar_Acorn(int mat[LARGURA][ALTURA]){
	inicializar_Matriz(matriz);
	mat[50][17] = VIVA;
	mat[51][17] = VIVA;
	mat[51][15] = VIVA;
	mat[53][16] = VIVA;
	mat[54][17] = VIVA;
	mat[55][17] = VIVA;
	mat[56][17] = VIVA;
}

void carregar_Pulsar(int mat[LARGURA][ALTURA]){
	inicializar_Matriz(matriz);
	mat[30][16] = VIVA;
	mat[29][16] = VIVA;
	mat[28][16] = VIVA;
	mat[31][13] = VIVA;
	mat[31][14] = VIVA;
	mat[31][15] = VIVA;
	mat[30][18] = VIVA;
	mat[29][18] = VIVA;
	mat[28][18] = VIVA;
	mat[31][19] = VIVA;
	mat[31][21] = VIVA;
	mat[31][20] = VIVA;
	mat[33][15] = VIVA;
	mat[33][14] = VIVA;
	mat[33][13] = VIVA;
	mat[34][16] = VIVA;
	mat[35][16] = VIVA;
	mat[36][16] = VIVA;
	mat[34][18] = VIVA;
	mat[35][18] = VIVA;
	mat[36][18] = VIVA;
	mat[33][19] = VIVA;
	mat[33][20] = VIVA;
	mat[33][21] = VIVA;
	mat[34][11] = VIVA;
	mat[35][11] = VIVA;
	mat[36][11] = VIVA;
	mat[30][11] = VIVA;
	mat[29][11] = VIVA;
	mat[28][11] = VIVA;
	mat[26][15] = VIVA;
	mat[26][14] = VIVA;
	mat[26][13] = VIVA;
	mat[26][19] = VIVA;
	mat[26][20] = VIVA;
	mat[26][21] = VIVA;
	mat[29][23] = VIVA;
	mat[30][23] = VIVA;
	mat[28][23] = VIVA;
	mat[34][23] = VIVA;
	mat[36][23] = VIVA;
	mat[35][23] = VIVA;
	mat[38][19] = VIVA;
	mat[38][20] = VIVA;
	mat[38][21] = VIVA;
	mat[38][15] = VIVA;
	mat[38][14] = VIVA;
	mat[38][13] = VIVA;
}

void carregar_GliderGun(int mat[LARGURA][ALTURA]){
	inicializar_Matriz(matriz);
	mat[32][17] = VIVA;
	mat[31][17] = VIVA;
	mat[31][16] = VIVA;
	mat[31][18] = VIVA;
	mat[30][19] = VIVA;
	mat[30][15] = VIVA;
	mat[29][17] = VIVA;
	mat[28][14] = VIVA;
	mat[27][14] = VIVA;
	mat[28][20] = VIVA;
	mat[27][20] = VIVA;
	mat[26][19] = VIVA;
	mat[26][15] = VIVA;
	mat[25][16] = VIVA;
	mat[25][17] = VIVA;
	mat[25][18] = VIVA;
	mat[16][17] = VIVA;
	mat[16][16] = VIVA;
	mat[15][16] = VIVA;
	mat[15][17] = VIVA;
	mat[35][16] = VIVA;
	mat[36][16] = VIVA;
	mat[35][15] = VIVA;
	mat[36][15] = VIVA;
	mat[35][14] = VIVA;
	mat[36][14] = VIVA;
	mat[37][13] = VIVA;
	mat[37][17] = VIVA;
	mat[39][13] = VIVA;
	mat[39][12] = VIVA;
	mat[39][17] = VIVA;
	mat[39][18] = VIVA;
	mat[49][14] = VIVA;
	mat[50][14] = VIVA;
	mat[50][15] = VIVA;
	mat[49][15] = VIVA;
}

void carregar_Exemplos_Basicos(int mat[LARGURA][ALTURA]){
	inicializar_Matriz(mat);
	// Bloco
	mat[6][4] = VIVA;
	mat[7][4] = VIVA;
	mat[6][5] = VIVA;
	mat[7][5] = VIVA;
	// Bote
	mat[17][4] = VIVA;
	mat[17][5] = VIVA;
	mat[18][5] = VIVA;
	mat[18][3] = VIVA;
	mat[19][4] = VIVA;
	// Blinker
	mat[34][4] = VIVA;
	mat[35][4] = VIVA;
	mat[36][4] = VIVA;
	// Sapo
	mat[46][4] = VIVA;
	mat[47][4] = VIVA;
	mat[48][4] = VIVA;
	mat[45][5] = VIVA;
	mat[46][5] = VIVA;
	mat[47][5] = VIVA;
	// Beacon
	mat[56][3] = VIVA;
	mat[56][4] = VIVA;
	mat[57][3] = VIVA;
	mat[59][6] = VIVA;
	mat[59][5] = VIVA;
	mat[58][6] = VIVA;
	// Glider
	mat[7][20] = VIVA;
	mat[8][20] = VIVA;
	mat[9][20] = VIVA;
	mat[9][19] = VIVA;
	mat[8][18] = VIVA;
	// Lightweight Spaceship
	mat[30][20] = VIVA;
	mat[31][20] = VIVA;
	mat[32][20] = VIVA;
	mat[33][18] = VIVA;
	mat[33][19] = VIVA;
	mat[33][20] = VIVA;
	mat[29][19] = VIVA;
	mat[29][17] = VIVA;
	mat[32][17] = VIVA;
}

void verificar_Matriz(int mat[LARGURA][ALTURA]){
	int mat2[LARGURA][ALTURA];
	//printf("Verificando\n");

	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			mat2[i][j] = mat[i][j];

	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			verificar_Peca(mat, mat2, i, j);

	atualiza_Matriz(mat, mat2);
}

void atualiza_Matriz(int mat[LARGURA][ALTURA], int mat2[LARGURA][ALTURA]){
	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			mat[i][j] = mat2[i][j];
}

void atualiza_Matriz_2(int vizinhos, int mat2[LARGURA][ALTURA], int i, int j){
	if(vizinhos < 2 || vizinhos > 3)
		mat2[i][j] = MORTA;
	if(vizinhos == 3)
		mat2[i][j] = VIVA;
}

void verificar_Peca(int mat[LARGURA][ALTURA], int mat2[LARGURA][ALTURA], int i,  int j){
	int vizinhos = 0;

	for(int x = i-1; x <= i+1; x++)
		for(int y = j-1; y <= j+1; y++) {
			if(x == i && y == j) continue;
			if(x < 0 || y < 0) continue;
			if(x >= LARGURA || y >= ALTURA) continue;
			if(mat[x][y] == VIVA) vizinhos++;
		}
	atualiza_Matriz_2(vizinhos, mat2, i, j);
}

void inicializar_Matriz(int mat[LARGURA][ALTURA]){
	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			mat[i][j] = MORTA;
}

void mostrar_Matriz(int mat[LARGURA][ALTURA]){
	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			mostrar_Celula(i, j, mat[i][j]);
	//k_flush();
}

void mostrar_Celula(int x, int y, int estado) {
	if(estado == VIVA) k_set_color('b');
	else k_set_color('W');
    k_draw(x,y, celula, 10,10);
}

void gerar_Tela(){
	k_open(LARGURA*20, ALTURA*20+20, "Jogo Da Vida" );
    k_set_block(10);
    k_set_zoom(1,1);
	k_clear('K');
	//k_flush();
}

void mostrarBotoes() {
	if(played)
        k_draw(0, ALTURA, play, 10,10);
	else
        k_draw(0, ALTURA, pause, 10,10);

    k_draw(2,ALTURA, next, 10,10);
    k_draw(4,ALTURA,clean, 10,20);

    k_draw(7,ALTURA,um , 10,10);
    k_draw(8,ALTURA,dois, 10,10);
    k_draw(9,ALTURA,tres, 10,10);
    k_draw(10,ALTURA,quatro, 10,10);
    k_draw(11,ALTURA,cinco, 10,10);
    k_draw(12,ALTURA,seis, 10,10);
    k_write(14,ALTURA,"+");
    k_write(15,ALTURA,"-");
}

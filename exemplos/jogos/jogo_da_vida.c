#include <kip.h>
#include <stdio.h>

#define ALTURA 34
#define LARGURA 68
#define VIVA 1
#define MORTA 0

char celula[] = "\
          \
 #########\
 #########\
 #########\
 #########\
 #########\
 #########\
 #########\
 #########\
 #########";

char play[] = "\
          \
 rrRrrrrrr\
 rrRRrrrrr\
 rrRRRrrrr\
 rrRRRRrrr\
 rrRRRRRrr\
 rrRRRRrrr\
 rrRRRrrrr\
 rrRRrrrrr\
 rrRrrrrrr";

char next[] = "\
          \
 rrrrrrrrr\
 rrrrrrrrr\
 rRrrRrrRr\
 rRRrRRrRr\
 rRRRRRRRr\
 rRRrRRrRr\
 rRrrRrrRr\
 rrrrrrrrr\
 rrrrrrrrr";

char pause[] = "\
          \
 rrrrrrrrr\
 rRRRrRRRr\
 rRRRrRRRr\
 rRRRrRRRr\
 rRRRrRRRr\
 rRRRrRRRr\
 rRRRrRRRr\
 rRRRrRRRr\
 rrrrrrrrr";

int matriz[LARGURA][ALTURA];
int automatico = 0;
int played = 1;

void gerar_Tela();
void mostrar_Celula(int x, int y, int estado);
void mostrar_Matriz(int mat[LARGURA][ALTURA]);
void preencher_Matriz(int mat[LARGURA][ALTURA]);
void verificar_Matriz(int mat[LARGURA][ALTURA]);
void verificar_Peca(int mat[LARGURA][ALTURA], int mat2[LARGURA][ALTURA], int i,  int j);
void atualiza_Matriz(int mat[LARGURA][ALTURA], int mat_2[LARGURA][ALTURA]);
void atualiza_Matriz_2(int vizinhos, int mat_2[LARGURA][ALTURA], int i, int j);
int  pegar_Evento();
void mostrarBotoes();

int main(){
	gerar_Tela();
	preencher_Matriz(matriz);
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
		k_sleep(100);
	}
	return 0;
	
}

int pegar_Evento(){
	char c = k_peek();//olha o buffer sem bloquear pra pegar um evento, retorna 0 se não houver evento
	if(c != 0) {//se houve um evento
		if(c == CLICK_LEFT) {
			int x = k_xpos();//pega qual bloco foi clicado em x e em y
			int y = k_ypos();
			printf("X = %d\t Y = %d\n", x, y);
			if(y >= ALTURA) {
				if(x == 0) { //>= 0 && x < 20
					played = (played+1) % 2;
					if(played == 1) automatico = 0;
					else automatico = 1;
				} else if(x == 2) verificar_Matriz(matriz);
			} else matriz[x][y] = (matriz[x][y] + 1) % 2;	
		}
		else if(c == KEY_ENTER) {
			verificar_Matriz(matriz);
		}
		else if(c == ' ') {
			automatico = (automatico+1) % 2;
			played = (played+1) % 2;
		}
		return 1;
	}
	return 0;
}

void verificar_Matriz(int mat[LARGURA][ALTURA]){
	int mat2[LARGURA][ALTURA];
	printf("Verificando\n");
	
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

void preencher_Matriz(int mat[LARGURA][ALTURA]){
	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			mat[i][j] = MORTA;
}

void mostrar_Matriz(int mat[LARGURA][ALTURA]){
	for(int i = 0; i < LARGURA; i++)
		for(int j = 0; j < ALTURA; j++)
			mostrar_Celula(i, j, mat[i][j]);
	k_flush();//atualiza a tela
}

void mostrar_Celula(int x, int y, int estado) {
	if(estado == VIVA) k_set_color('R');
	else k_set_color('W');
	k_draw(x,y,celula,10,10); 
}

void gerar_Tela(){
	k_open(LARGURA*20, ALTURA*20+20, "Jogo Da Vida" );
	k_clear('K');
	k_flush();
}

void mostrarBotoes() {
	if(played)
		k_draw(0,ALTURA, play, 10,10);
	else
		k_draw(0,ALTURA, pause, 10,10);
	k_draw(2,ALTURA,next, 10,10);
}

#include <stdlib.h>
#include <stdio.h>

#define DIM 10

void criaMapa(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM]);
void mostraMapa(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM]);
void inicializaMapa(int mapaA[DIM][DIM], int mapaB[DIM][DIM]);
void jogar(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM]);
void mostraDica(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM], int i, int j, int jogador);

int main(){
	int mapaA[DIM][DIM], mapaB[DIM][DIM], copiaA[DIM][DIM], copiaB[DIM][DIM];
	int i, j;

	criaMapa(mapaA, mapaB, copiaA, copiaB);
	inicializaMapa(mapaA, mapaB);
	mostraMapa(mapaA, mapaB, copiaA, copiaB);
	jogar(mapaA, mapaB, copiaA, copiaB);

	return 0;
}

/*Função que gerencia as jogadas e é executada até obter um vencedor*/
void jogar(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM]){
	int i, j, jogador = 1;
	int pontoA = (DIM/5) * 1 + (DIM/2) * 3 + (DIM/2) * 5, pontoB = (DIM/5) * 1 + (DIM/2) * 3 + (DIM/2) * 5;
	int pontoTotal = (DIM/5) * 1 + (DIM/2) * 3 + (DIM/2) * 5;
	int ultimaAx = 0, ultimaAy = 0, ultimaBx = 0, ultimaBy = 0;

	/*Alterna entre os jogadores até ter um vencedor*/
	do{
		if(jogador == 1){
			printf("Jogador 1. Você já acertou %d alvos.\n", pontoTotal - pontoA);
			if(ultimaAx != 0 || ultimaAy != 0){
				printf("Sua última jogada foi: %d e %d.\n", ultimaAx, ultimaAy);
			}
			printf("Digite a posição que quer atacar: ");
			scanf("%d%d", &i, &j);
			while(i < 0 || i >= DIM || j < 0 || j >= DIM){
				printf("Digite a posição entre 0 e %d\n", DIM);
				scanf("%d%d", &i, &j);
			}
			while(copiaB[i][j] == -1 || copiaB[i][j] == -2){
				printf("Digite outra posição. Já jogou neste ponto!\n");
				scanf("%d%d", &i, &j);
			}
			if(mapaB[i][j] == 2 || mapaB[i][j] == 3 || mapaB[i][j] == 4){
				copiaB[i][j] = -1;
				pontoA--;
			}else
			if(mapaB[i][j] == 0){
				copiaB[i][j] = -2;
			}
			mostraMapa(mapaA, mapaB, copiaA, copiaB);
			mostraDica(mapaA, mapaB, copiaA, copiaB, i, j, jogador);
			ultimaAx = i;
			ultimaAy = j;
			jogador = 2;
		}
		if(jogador == 2){
			printf("Jogador 2. Você já acertou %d alvos.\n", pontoTotal - pontoB);
			if(ultimaBx != 0 || ultimaBy != 0){
				printf("Sua última jogada foi: %d e %d.\n", ultimaBx, ultimaBy);
			}
			printf("Digite a posição que quer atacar: ");
			scanf("%d%d", &i, &j);
			while(i < 0 || i >= DIM || j < 0 || j >= DIM){
				printf("Digite a posição entre 0 e %d\n", DIM);
				scanf("%d%d", &i, &j);
			}			
			while(copiaA[i][j] == -1 || copiaA[i][j] == -2){
				printf("Digite outra posição. Já jogou neste ponto!\n");
				scanf("%d%d", &i, &j);
			}
			if(mapaA[i][j] == 2 || mapaA[i][j] == 3 || mapaA[i][j] == 4){
				copiaA[i][j] = -1;
				pontoB--;
			}else
			if(mapaA[i][j] == 0){
				copiaA[i][j] = -2;
			}
			mostraMapa(mapaA, mapaB, copiaA, copiaB);
			mostraDica(mapaA, mapaB, copiaA, copiaB, i, j, jogador);
			ultimaBx = i;
			ultimaBy = j;
			jogador = 1;
		}
	}while(pontoA > 0 && pontoB > 0);
	if(pontoA == 0){
		printf("Vencedor foi o jogador A.\n");
	}else{
		printf("Vencedor foi o jogador B.\n");
	}
}

/*Mostra dicas de quantos alvos ainda restam na linha e na columa*/
void mostraDica(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM], int x, int y, int jogador){
	int i = 0, j = 0, pescador = 0, submarino = 0, portaAviao = 0;
	/*Verifica a linha*/
	printf("***************************************\n");
	printf("            Mapa dos pontos            \n");
	printf("***************************************\n");
	if(jogador == 1){
		while(j < DIM){
			if(mapaB[x][j] == 2 && copiaB[x][j] == 0){
				pescador++;
			}
			if(mapaB[x][j] == 3 && copiaB[x][j] == 0){
				submarino++;
			}			
			if(mapaB[x][j] == 4 && copiaB[x][j] == 0){
				portaAviao++;
			}			
			j++;
		}
		printf("   Nesta linha tem %d pescador.\n", pescador);
		printf("   Nesta linha tem %d submarino.\n", submarino);
		printf("   Nesta linha tem %d portaAviao.\n", portaAviao);
	}
	if(jogador == 2){
		while(j < DIM){
			if(mapaA[x][j] == 2 && copiaA[x][j] == 0){
				pescador++;
			}
			if(mapaA[x][j] == 3 && copiaA[x][j] == 0){
				submarino++;
			}
			if(mapaA[x][j] == 4 && copiaA[x][j] == 0){
				portaAviao++;
			}
			j++;
		}
		printf("   Nesta linha tem %d pescador.\n", pescador);
		printf("   Nesta linha tem %d submarino.\n", submarino);
		printf("   Nesta linha tem %d portaAviao.\n", portaAviao);
	}

	pescador = 0;
	submarino = 0;
	portaAviao = 0;
	/*Verifica a coluna*/
	if(jogador == 1){
		while(i < DIM){
			if(mapaB[i][y] == 2 && copiaB[i][y] == 0){
				pescador++;
			}
			if(mapaB[i][y] == 3 && copiaB[i][y] == 0){
				submarino++;
			}
			if(mapaB[i][y] == 4 && copiaB[i][y] == 0){
				portaAviao++;
			}
			i++;
		}
		printf("   Nesta coluna tem %d pescador.\n", pescador);
		printf("   Nesta coluna tem %d submarino.\n", submarino);
		printf("   Nesta coluna tem %d portaAviao.\n", portaAviao);
	}
	if(jogador == 2){
		while(i < DIM){
			if(mapaA[i][y] == 2 && copiaA[i][y] == 0){
				pescador++;
			}
			if(mapaA[i][y] == 3 && copiaA[i][y] == 0){
				submarino++;
			}
			if(mapaA[i][y] == 4 && copiaA[i][y] == 0){
				portaAviao++;
			}
			i++;
		}
		printf("   Nesta coluna tem %d pescador.\n", pescador);
		printf("   Nesta coluna tem %d submarino.\n", submarino);
		printf("   Nesta coluna tem %d portaAviao.\n", portaAviao);
	}
	printf("***************************************\n\n\n\n\n\n");
}

void criaMapa(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM]){
	int i, j;
	for(i = 0; i < DIM; ++i){
		for(j = 0; j < DIM; ++j){
			mapaA[i][j] = 0;
			mapaB[i][j] = 0;
			copiaA[i][j] = 0;
			copiaB[i][j] = 0;
		}
	}
}

void mostraMapa(int mapaA[DIM][DIM], int mapaB[DIM][DIM], int copiaA[DIM][DIM], int copiaB[DIM][DIM]){
	int i, j, espaco;
	printf("\n\n\n");

/*	for(i = 0; i < DIM; ++i){
		for(j = 0; j < DIM; ++j){
			printf("%d ", mapaA[i][j]);
		}
		printf("  ");
		for(j = 0; j < DIM; ++j){
			printf("%d ", mapaB[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/

	for(i = 0; i < DIM; ++i){
		if(i == 0){
			for(espaco = 0; espaco < DIM / 2; ++espaco){
				printf(" ");
			}
			printf(" Mapa A");
			for(espaco = 0; espaco < DIM * 1.5; ++espaco){
				printf(" ");
			}
			printf("Mapa B");
			printf("\n");
		}
		for(j = 0; j < DIM; ++j){
			if(copiaA[i][j] == 0){
				printf("0 ");
			}
			if(copiaA[i][j] == -1){
				printf("* ");
			}
			if(copiaA[i][j] == -2){
				printf("~ ");
			}
		}
		printf("  ");
		for(j = 0; j < DIM; ++j){
			if(copiaB[i][j] == 0){
				printf("0 ");
			}
			if(copiaB[i][j] == -1){
				printf("* ");
			}
			if(copiaB[i][j] == -2){
				printf("~ ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

/*Inicializa a posição dos alvos no mapa*/
void inicializaMapa(int mapaA[DIM][DIM], int mapaB[DIM][DIM]){
	int i, j;
	int orientacao;
	srand((unsigned)time(NULL));
	int pescadorA = DIM / 5, pescadorB = DIM / 5;
	int SubmarinoA =  DIM / 2, SubmarinoB =  DIM / 2;
	int portaAviaoA = DIM / 2, portaAviaoB = DIM / 2;

	/*Pescador[1][1]*/
	do{
		i = rand()%DIM;
		j = rand()%DIM;
		if(mapaA[i][j] == 0){
			mapaA[i][j] = 2;
			pescadorA--;		
		}
	}while(pescadorA > 0);

	do{
		i = rand()%DIM;
		j = rand()%DIM;
		if(mapaB[i][j] == 0){
			mapaB[i][j] = 2;
			pescadorB--;		
		}
	}while(pescadorB > 0);

	/*Submarino[1][3]*/
	do{
		i = rand()%DIM;
		j = rand()%DIM;
		orientacao = rand()%2;
		/*Vertical*/
		if(orientacao == 0 && j < DIM - 2){
			if(mapaA[i][j] == 0 && mapaA[i][j+1] == 0 && mapaA[i][j+2] == 0){
				mapaA[i][j] = 3;
				mapaA[i][j+1] = 3;
				mapaA[i][j+2] = 3;
				SubmarinoA--;		
			}

		}
		/*Horizontal*/
		if(orientacao == 1 && i < DIM - 2){
			if(mapaA[i][j] == 0 && mapaA[i+1][j] == 0 && mapaA[i+2][j] == 0){
				mapaA[i][j] = 3;
				mapaA[i+1][j] = 3;
				mapaA[i+2][j] = 3;
				SubmarinoA--;		
			}
		}
	}while(SubmarinoA > 0);

	do{
		i = rand()%DIM;
		j = rand()%DIM;
		orientacao = rand()%2;
		/*Vertical*/
		if(orientacao == 0 && j < DIM - 2){
			if(mapaB[i][j] == 0 && mapaB[i][j+1] == 0 && mapaB[i][j+2] == 0){
				mapaB[i][j] = 3;
				mapaB[i][j+1] = 3;
				mapaB[i][j+2] = 3;
				SubmarinoB--;
			}
		}
		/*Horizontal*/
		if(orientacao == 1 && i < DIM - 2){
			if(mapaB[i][j] == 0 && mapaB[i+1][j] == 0 && mapaB[i+2][j] == 0){
				mapaB[i][j] = 3;
				mapaB[i+1][j] = 3;
				mapaB[i+2][j] = 3;
				SubmarinoB--;
			}
		}
	}while(SubmarinoB > 0);

	/*PortaAviao[1][5]*/
	do{
		i = rand()%DIM;
		j = rand()%DIM;
		orientacao = rand()%2;
		/*Vertical*/
		if(orientacao == 0 && j < DIM - 4){
			if(mapaA[i][j] == 0 && mapaA[i][j+1] == 0 && mapaA[i][j+2] == 0 && mapaA[i][j+3] == 0 && mapaA[i][j+4] == 0){
				mapaA[i][j] = 4;
				mapaA[i][j+1] = 4;
				mapaA[i][j+2] = 4;
				mapaA[i][j+3] = 4;
				mapaA[i][j+4] = 4;
				portaAviaoA--;		
			}

		}
		/*Horizontal*/
		if(orientacao == 1 && i < DIM - 4){
			if(mapaA[i][j] == 0 && mapaA[i+1][j] == 0 && mapaA[i+2][j] == 0 && mapaA[i+3][j] == 0 && mapaA[i+4][j] == 0){
				mapaA[i][j] = 4;
				mapaA[i+1][j] = 4;
				mapaA[i+2][j] = 4;
				mapaA[i+3][j] = 4;
				mapaA[i+4][j] = 4;
				portaAviaoA--;		
			}
		}
	}while(portaAviaoA > 0);

	do{
		i = rand()%DIM;
		j = rand()%DIM;
		orientacao = rand()%2;
		/*Vertical*/
		if(orientacao == 0 && j < DIM - 4){
			if(mapaB[i][j] == 0 && mapaB[i][j+1] == 0 && mapaB[i][j+2] == 0 && mapaB[i][j+3] == 0 && mapaB[i][j+4] == 0){
				mapaB[i][j] = 4;
				mapaB[i][j+1] = 4;
				mapaB[i][j+2] = 4;
				mapaB[i][j+3] = 4;
				mapaB[i][j+4] = 4;
				portaAviaoB--;
			}
		}
		/*Horizontal*/
		if(orientacao == 1 && i < DIM - 4){
			if(mapaB[i][j] == 0 && mapaB[i+1][j] == 0 && mapaB[i+2][j] == 0 && mapaB[i+3][j] == 0 && mapaB[i+4][j] == 0){
				mapaB[i][j] = 4;
				mapaB[i+1][j] = 4;
				mapaB[i+2][j] = 4;
				mapaB[i+3][j] = 4;
				mapaB[i+4][j] = 4;
				portaAviaoB--;
			}
		}
	}while(portaAviaoB > 0);
}
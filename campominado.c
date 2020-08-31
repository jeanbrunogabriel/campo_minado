
#include <stdio.h>
#include <stdlib.h>

/* O código deste campo minado consiste na criação de uma matriz quadrad de 2x2 a 10x10 cuja função é armazenar um tabuleiro.
 *
 * As casas ocultas tem valor superior a 10 quando não têm bombas, e em -1 quando há uma bomba. Para revelar a casa é feito o resto da multiplicação por 10 - % 10.  
 *
 *
 * Os significado dos valores são - onde X é valor da casa:
 *
 * X = 10 - Casa zerada. Ou não tem nenhuma bomba adjacente e ainda está oculta ou ainda não foi inicializada - Ver chamada da função zera_campo()na função main().
 *
 * 10 < X - Casa adjacente a pelo menos 1 bomba e ainda oculta, por isso seu valor é maior do que 10.
 *
 * X = 0 - Casa sem nenhuma bomba adjacente e revelado pelo jogador direta ou indiretamente - Ver função revela_campo()
 *
 * 0 < X < 10 - Casa adjacente a pelo menos 1 bomba e já revelada pelo jogador direta ou indiretamente - Ver função revela_campo()
 *
 * */

int print_campo(int tamanho, int tabuleiro[tamanho][tamanho]){
	/* "Confere" é o retorno desta função booleana.
	 * 
	 * Esta variável booleana se, e somente se, 
	 * permancer em 1 ao final desta função faz com que o jogador
	 * ganhe a partida.
	 * 
	 * Caso seu valor seja posteriormente determinado em 0,
	 * significa que ainda há casas a serem descobertas.*/
	int confere = 1;
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){

			/*Após o resto da divisão por 10 ser feito em jogada() ou revela_campo(), naturalmente é revelado pela condição que segue 
			 * */
			if(tabuleiro[i][j] < 10 && tabuleiro[i][j] != -1){
				printf("%d\t", tabuleiro[i][j]);
			}else if(tabuleiro[i][j] == -1){
				//As bombas nunca podem ser reveladas, caso o sejam a saída encontra-se já na função jogada(). 
				printf("*\t");
			}
			else{
				/* Caso esta condição seja satisfeita,
				 * Confere passa para 0, pois há campos a serem revelados.
				 * O jogo continua*/
				confere = 0;
				printf("*\t");
			}

		}
		printf("\n");
	}
	return confere;

}

// Enumera as casas adjacentes a bombas, confere a existência das 8. Portanto, priva-se de comentários.
void enumera_campo(int tamanho, int x, int y, int tabuleiro[tamanho][tamanho]){
	if(x-1 >= 0){
		if (tabuleiro[x-1][y] != -1) {
				tabuleiro[x-1][y] += 1;
		}
		if(y-1 >= 0 && tabuleiro[x-1][y-1] != -1){
			tabuleiro[x-1][y-1] += 1;
		}
		if(y+1 < tamanho && tabuleiro[x-1][y+1] != -1){
			tabuleiro[x-1][y+1] += 1;
		}
	}
	if(x+1 < tamanho){
		if(tabuleiro[x+1][y] != -1){
			tabuleiro[x+1][y] += 1;
		}
		if (y+1 < tamanho && tabuleiro[x+1][y+1] != -1){
			tabuleiro[x+1][y+1] += 1;
		}
		if (y-1 >=0 && tabuleiro[x+1][y-1] != -1){
			tabuleiro[x+1][y-1] += 1;
		}
	}
	if (y-1 >=0 && tabuleiro[x][y-1] != -1){
		tabuleiro[x][y-1] += 1;
	}
	if (y+1 < tamanho && tabuleiro[x][y+1] != -1){
		tabuleiro[x][y+1] += 1;
	}

}

void zera_campo(int tamanho, int tabuleiro[tamanho][tamanho]){
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			tabuleiro[i][j] = 10;
		}
	}
}

/*Revela o campo adjacente a casas que não são vizinhas a bombas. Caso alguma casa revelada também não tenha bombas adjacentes, o campo e novamente revelado pela mesma função. 
 * 
 * A conferência se estende pelos 8 campos. Comentários não são mais necessários*/
void revela_campo(int tamanho, int tabuleiro[tamanho][tamanho], int x, int y){
	if(x-1 >= 0 && tabuleiro[x-1][y] != 0){
		tabuleiro[x-1][y] %= 10;

		if(tabuleiro[x-1][y] == 0){
			revela_campo(tamanho,tabuleiro, x-1, y);
		}

		if(y+1 < tamanho && tabuleiro[x-1][y+1] != 0){
			tabuleiro[x-1][y+1] %= 10;
			if (tabuleiro[x-1][y+1] == 0) {
				revela_campo(tamanho, tabuleiro, x-1, y+1);
			}
		}
		if(y-1 >= 0 && tabuleiro[x-1][y-1] != 0){
				tabuleiro[x-1][y-1] %= 10;
				if (tabuleiro[x-1][y-1] == 0) {
					revela_campo(tamanho, tabuleiro, x-1, y-1);
				}
		}
	}

	if(x+1 < tamanho && tabuleiro[x+1][y] != 0){
		tabuleiro[x+1][y] %= 10;
		if(tabuleiro[x+1][y] == 0){
			revela_campo(tamanho,tabuleiro, x+1, y);
		}

		if(y+1 < tamanho && tabuleiro[x][y+1] != 0){
			tabuleiro[x+1][y+1] %= 10;
			if (tabuleiro[x+1][y+1] == 0) {
				revela_campo(tamanho, tabuleiro, x+1, y+1);
			}
		}
		if(y-1 >= 0 && tabuleiro[x+1][y-1] != 0){
				tabuleiro[x+1][y-1] %= 10;
				if (tabuleiro[x+1][y-1] == 0) {
					revela_campo(tamanho, tabuleiro, x+1, y-1);
				}
		}
	}

	if(y-1 >=0 && tabuleiro[x][y-1] != 0){
		tabuleiro[x][y-1] %= 10;
		if (tabuleiro[x][y-1] == 0) {
			revela_campo(tamanho, tabuleiro, x, y-1);
		}
	}
	if (y+1 < tamanho && tabuleiro[x][y+1] != 0) {
		tabuleiro[x][y+1] %= 10;
		if (tabuleiro[x][y+1] == 0) {
			revela_campo(tamanho, tabuleiro, x, y+1);
		}
	}
}

void jogada(int tamanho, int tabuleiro[tamanho][tamanho], int x, int y){
	if (tabuleiro[x][y] == -1){

		// Se o jogador selecionou uma bomba, logo o jogo é terminado
		printf("\n\n*******************KABUM**********************\n\n");
		exit(1);
	}else if(tabuleiro[x][y] > 0){
		/*N° do campo é revelado com o resto da divisão por 10
		 * - Ver função zera_campo() que determina o valor em
		 *   N° de bombas adjacentes + 10*/ 
		tabuleiro[x][y] %= 10;
		if (tabuleiro[x][y] == 0){
			/*Caso não haja bombas adjacentes
			 * Todas as casas adjacentes são reveladas
			 * em cascata. */ 
			revela_campo(tamanho,tabuleiro,x,y);
		}
	}
}

int main()
{
    int tamanho; // tamanho da matriz
    while(1) {
        printf("Insira o tamanho do campo: ");
        scanf("%d", &tamanho);
        fflush(stdin);

	// A matriz pode ser de [2][2] = 4  até [10][10] = 100 
        if(tamanho >= 2 && tamanho <= 10){
            break; 
        }
        printf("O tamanho mínimo do tabuleiro é 2x2 e o máximo 10x10");
    }

    /* Matriz inteira na qual cada campo revelado significa o n°
     * de bombas adjascentes sendo -1 uma bomba: */
    int tabuleiro[tamanho][tamanho];

    /* Os campos não revelados tem o seu n° de bombas adjascentes somados de 10, portanto a função abaixo determina os valores em 10, pois nenhum há de ser revelado ao início*/

    zera_campo(tamanho, tabuleiro);
    
    

    int bombas = tamanho + 1; 
    
    
    for (int i = 0; i < bombas; i++){
        //coordenadas aleatórias para as bombas com a função rand()
        int x, y;
	while (1){
		x = rand() % tamanho;
        	y = rand() % tamanho;
		
		//condição p/ não repetição de bombas na mesma casa
		if (tabuleiro[x][y] != -1){
			break;
		}
	}

	//print de desenvolvimento p/ conferência do código: 
	printf("x: %d, y: %d\n", x+1, y+1);
	
	//Como supracitado, o valor para bombas é -1 
  	tabuleiro [x][y] = -1;
	
	//enumera as casas adjacentes às bombas
	enumera_campo(tamanho, x, y, tabuleiro);
 
    }

    //Início de jogo
    int x, y;

    //Revela o campo inicial, todas as casas ocultas 
    print_campo(tamanho, tabuleiro);

    /*O jogo não termina até que o jogador faça descubra todas as casas
     *  ou até que exploda */
    while (1){
        printf ("Digite a coordenada X: ");
        scanf("%d", &x);
        printf("Digite a coordenada Y: ");
        scanf("%d", &y);
	
	//Confirma a validade das coordenadas
        if(x > tamanho || y > tamanho || x < 1 || y < 1){
            printf ("coordenadas incongruentes");
        }else {

		/* Primeiramente, computa a jogada
		 * Revela o campo a ser mostrado
		 * Reproduz na tela as alterações no campo
		 * */
		jogada(tamanho, tabuleiro, x-1, y-1);
	}
	/*Ver comentário inicial da função booleana print_campo()
	 * 
	 * Caso seu retorno seja true (1), logo o jogador venceu*/

	if (print_campo(tamanho, tabuleiro)){
		printf("Ganhou!!");
		return 0;
	}
    }
    return 0;
}

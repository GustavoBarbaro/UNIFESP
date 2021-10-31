#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <math.h>

#define Max_buffer 100
#define Max_threads 100

int buffer [Max_buffer] = {0};

typedef struct parametros {
	int Numero;
	int vet[Max_buffer];
} param;

param parametro[Max_threads];


sem_t mutex;


void preenche_buffer (int valor){

	int i;

	for (i = 0; i < Max_buffer; i++){
		if (buffer[i] == 0){
			buffer[i] = valor; //salva o valor no buffer
			break;
		}
	}
}



void *perfect_num (void * args){

	int i;

	param t_parametro = *(param *) args;

	for (i = 1; i <= Max_buffer; i++){
		if (t_parametro.vet[i] == 0){
			break;
		}
		else{
			if ((t_parametro.Numero%t_parametro.vet[i]) == 0){ //divisao inteira - acessar regiao critica

				sem_wait(&mutex); //acesssando a regiao critica

				preenche_buffer(t_parametro.vet[i]);

				sem_post(&mutex); //saindo da regiao critica
			}
		}
	}
	pthread_exit(NULL);
}





int main(int argc, char **argv) {

	int N; //numero a ser verificado
	int P; //quantidade de threads 
	int i, passo, cont, j;
	cont = 1;

	sem_init(&mutex, 0, 1);

	// ----- INPUTS ---- //

	printf("Número a ser verificado : ");
	scanf("%d", &N);
	
	printf("Número de threads: ");
	scanf("%d", &P);

	int mat[N][P];

	for (i=0;i<N;i++){
		for(j=0;j<P;j++){
			mat[i][j]=0; //inicializa com 0
		}
	}
	// ------------------ //

	// --- Inicializando as threads --- //

	pthread_t threads[P];
	
	passo = floor((N-1)/P);

	for (i = 1; i <= N - 1; i++){
		
		for (j = 0; j < P; j++){ //preenchendo a matriz
			mat[i][j] = cont;
			cont++;
		}

		if ((cont - 1) == (N - 1)){
			break;
		}

		//nao conseguiu preencher tudo
		if (i == passo){
			j = 0;
			i++;
			while ((cont - 1) != (N-1)){
				mat[i][j] = cont;
				cont++;
				j++;
			}
			break;
		}
	}
	
	for (i = 0; i < P; i ++){ //aqui vai criar as threads

		parametro[i].Numero = N;

		for (j = 1; j <= N-1; j++){
			if (mat[j][i] != 0){
				parametro[i].vet[j] = mat[j][i];
			}
		}

		pthread_create (&threads[i], NULL, perfect_num, &parametro[i]);
	}


	for (i = 0; i < P; i ++){ //aqui vai organizar as threads
		pthread_join (threads[i], NULL);
	}


	// ----- verificação final de numero perfeito -----

	int contador = 0;

	for (i = 0; i < Max_buffer; i++){
		contador = contador + buffer[i];
	}

	if (contador == N){
		printf("Número Perfeito!\n");
	}
	else{
		printf("Número não perfeito!\n");
	}

	return 0;
}
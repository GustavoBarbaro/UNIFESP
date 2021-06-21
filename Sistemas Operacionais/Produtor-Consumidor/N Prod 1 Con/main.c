#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10 //tamanho maximo do buffer
#define N_Prod 5 //maximo de produtores

int buffer[N]; //buffer

sem_t mutex;
sem_t empty;
sem_t full;


int produz(void){
	int resp;

	resp = rand()%100 + 1; //gera numeros de 1 a 100

	return resp;
}

void inicializa_buffer_zerado (){
	int i;
	for (i = 0; i < N; i++){
		buffer[i]=0;
	}
}

int insere_buffer (int valor){
	int i, posicao;

	for (i = 0; i < N; i++){
		if (buffer[i] == 0){ //lugar vazio pode inserir
			buffer[i] = valor;
			posicao = i;
			break;
		}
	}
	return posicao;
}


int remove_buffer (void){
	int i, item;

	for (i = 0; i < N; i++){
		if (buffer[i] != 0){ //lugar com conteudo
			item = buffer[i];
			buffer[i] = 0; //retirado do buffer
			break;
		}
	}
	return item;
}


int identifica_posicao (void){
	int i, posicao;

	for (i = 0; i < N; i++){
		if (buffer[i] != 0){ //lugar com conteudo
			posicao = i;
			break;
		}
	}
	return posicao;	
}


void *produtor (void *args){

	int item, posicao;

	while (1){
		item = produz();
		sem_wait(&empty);
		sem_wait(&mutex); //entrando na regiao critica
		
		//coloca novo item no buffer
		//e retorna o lugar onde inseriu
		posicao = insere_buffer (item);
		printf("Prod: buffer[%d] = %d\n", posicao, buffer[posicao]);
		fflush(stdout);

		sem_post(&mutex); //saindo da regiao critica
		sem_post(&full);
	}
	//talvez colocar um pthread_exit
	pthread_exit (NULL);
}


void *consumidor (void *args){

	int item, posicao;

	while(1){
		sleep (1);
		sem_wait(&full);
		sem_wait(&mutex); //entrando na regiao critica

		//tira item do buffer
		//e retorna o lugar daonde tirou
		posicao = identifica_posicao();
		item = remove_buffer();

		sem_post(&mutex); //saindo da regiao critica
		sem_post(&empty);
		printf("Cons: %d = buffer[%d]\n", item, posicao);
		fflush(stdout);
	}
	pthread_exit (NULL);
}


int main(int argc, char **argv) {

	pthread_t tp[N_Prod], tc;
	int i;

	inicializa_buffer_zerado();

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);

	// ------  CRIAÇÃO DAS THREADS ------  //
	for(i = 0; i < N_Prod; i++){
		pthread_create(&tp[i], NULL, produtor, NULL);
	}	

	pthread_create(&tc, NULL, consumidor, NULL);
	// ------  ------------------- ------  //

	// ------  JOIN DAS THREADS ------  //

	for(i = 0; i < N_Prod; i++){
		pthread_join(tp[i], NULL);
	}

	pthread_join(tc, NULL);


	return 0;
}
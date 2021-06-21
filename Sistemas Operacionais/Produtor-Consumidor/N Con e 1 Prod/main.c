#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 10 //tamanho maximo do buffer
#define N_Cons 5 //maxino de consumidores

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

	pthread_t tp, tc[N_Cons];
	int i;

	inicializa_buffer_zerado();

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);
	
	pthread_create(&tp, NULL, produtor, NULL);

	for(i = 0; i < N_Cons; i++){
		pthread_create(&tc[i], NULL, consumidor, NULL);
	}

	pthread_join(tp, NULL);

	for(i = 0; i < N_Cons; i++){
		pthread_join(tc[i], NULL);
	}


	return 0;
}
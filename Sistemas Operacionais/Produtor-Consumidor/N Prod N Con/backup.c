#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 10
int buffer[N];
//sem_t count; // 0: Itens disponiveis p/ consumo no buffer
sem_t count; // N: posicoes vazias no buffer p/ producao
sem_t mutex;

int w=0;
int r=0;

int produz(void){
	return rand()%100;
}

void *produtor(void *args){
	int item;
	while (1) {
		item = produz();
		sem_wait(&count);
		sem_wait(&mutex);
		buffer[w] = item;
		printf("Prod: buffer[%d] = %d\n",w, buffer[w]);
		fflush(stdout);
		w = (w+1)%N; //buffer circular de 0 a N-1
		sem_post(&mutex);
	}
	pthread_exit(NULL);
}

void *consumidor(void *args){
	int item, cval;
	while(1) {
		sem_wait(&mutex);
		item = buffer[r];
		printf("Cons: %d = buffer[%d]\n", item, r);
		fflush(stdout);
		r = (r+1)%N; //buffer circular de 0 a N-1
		sem_post(&mutex);
		sem_getvalue(&count, &cval);
		if (cval < N) sem_post(&count);
	}
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	pthread_t tp, tc;
	sem_init(&count, 0, N);
	sem_init(&mutex, 0, 1);
	
	pthread_create(&tp, NULL, produtor, NULL);
	pthread_create(&tc, NULL, consumidor, NULL);
	pthread_join(tp, NULL);
	pthread_join(tc, NULL);
	return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>


#define men_max 5
#define woman_max 5


sem_t men_mutex, woman_mutex, bath_mutex;

int womenCount = 0;
int menCount = 0;

void homem_quer_entrar (void){
	sleep(1);
	sem_wait(&men_mutex); //entrando na regiao critica
	menCount++;
	if(menCount == 1){ //primeiro homem a entrar
		sem_wait(&bath_mutex);
	}
	
	printf("Man %d using bathroom!\n", menCount);
	fflush(stdout);
	sem_post(&men_mutex); //saindo da regiao critica
}


void homem_sair (void){
	
	sem_wait(&men_mutex); //entrando na regiao critica
	menCount--;
	if (menCount == 0){ //ultimo homem a sair
		sem_post(&bath_mutex);
	}
	printf ("Man %d leave bathroom!\n", menCount+1);
	fflush(stdout);
	sem_post(&men_mutex); // saindo da regiao critica
	
}


void mulher_quer_entrar (void){
	sleep(1);
	sem_wait(&woman_mutex); //entrando na regiao critica
	womenCount++;
	if(womenCount == 1){ //primeira mulher a entrar
		sem_wait(&bath_mutex);
	}
	printf("Woman %d using bathroom!\n", womenCount);
	fflush(stdout);
	sem_post(&woman_mutex); //saindo da regiao critica

	
}


void mulher_sair (void){
	
	sem_wait(&woman_mutex); //entrando na regiao critica
	womenCount--;
	if (womenCount == 0){ //ultima mulher a sair
		sem_post(&bath_mutex);
	}
	printf ("Woman %d leave bathroom!\n", womenCount+1);
	fflush(stdout);
	sem_post(&woman_mutex); // saindo da regiao critica
}


void *homem (void *args){
	while(1){
		homem_quer_entrar();
        usleep(rand()%100); //usa o banheiro
		homem_sair();
	}
	pthread_exit(NULL);
}

void *mulher (void *args){
	while(1){
		mulher_quer_entrar();
        usleep(rand()%100); //usa o banheiro
		mulher_sair();
	}
	pthread_exit(NULL);
}



int main(int argc, char **argv) {

	pthread_t men[men_max], woman[woman_max];
	int i;

	sem_init(&men_mutex, 0, 1);
	sem_init(&woman_mutex, 0, 1);
	sem_init(&bath_mutex, 0, 1);


	// ------  CRIAÇÃO DAS THREADS ------  //
	for (i = 0; i < men_max; i++){
		pthread_create (&men[i], NULL, homem, NULL);
	}

	for (i = 0; i < woman_max; i++){
		pthread_create (&woman[i], NULL, mulher, NULL);
	}

	// ------  ------------------- ------  //

	// ------  JOIN DAS THREADS ------  //
	for (i = 0; i < men_max; i++){
		pthread_join(men[i], NULL);
	}
	for (i = 0; i < woman_max; i++){
		pthread_join(woman[i], NULL);
	}


	return 0;
}
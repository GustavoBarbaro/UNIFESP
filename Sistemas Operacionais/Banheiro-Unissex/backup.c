#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MEN_SIZE 5
#define WOMEN_SIZE 5

int womenCount = 0;
int menCount = 0;
sem_t mutexMale, mutexFemale, accessMutex;
pthread_t men[MEN_SIZE], women[WOMEN_SIZE];

void * womenRoutine(void * arg)
{
	while(1)
	{
		int * aux = arg;
		int id = * aux;
		usleep(500000);
		
		sem_wait(&mutexFemale);
		womenCount++; // aumenta quantidade de mulheres
		if(womenCount == 1)
			sem_wait(&accessMutex);
		sem_post(&mutexFemale);
		
		printf("Mulher %d usando banheiro\n", id);
			
		sem_wait(&mutexFemale);
		womenCount--;
		if(womenCount == 0)
			sem_post(&accessMutex); // sai do banheiro (diminui quantidade de mulheres)
		
		//printf("womenCount: %d\n", womenCount);	
		sem_post(&mutexFemale);
	}
}

void * menRoutine(void * arg)
{
	while(1)
	{
		int * aux = arg;
		int id = * aux;
		
		usleep(500000);
		
		//fprintf(stderr, "mulher: %d\n\n", id);
		
		sem_wait(&mutexMale);
		++menCount; // aumenta quantidade de mulheres
		if(menCount == 1)
			sem_wait(&accessMutex);
		sem_post(&mutexMale);
		
		printf("Homem %d usando banheiro\n", id);
			
		sem_wait(&mutexMale);
		menCount--;
		if(menCount == 0)
			sem_post(&accessMutex); // sai do banheiro (diminui quantidade de mulheres)
		sem_post(&mutexMale);
		//printf("menCount: %d\n", menCount);
	}
}
int main(void)
{
	int i;
	sem_init(&mutexMale, 0, 1);
	sem_init(&mutexFemale, 0, 1);
	sem_init(&accessMutex, 0, 1);

	for(i = 0; i < MEN_SIZE; i++)
		pthread_create(&men[i], NULL, menRoutine, &i);
		
	for(i = 0; i < WOMEN_SIZE; i++)
		pthread_create(&women[i], NULL, womenRoutine, &i);
		
	for(i = 0; i < MEN_SIZE; i++)
		pthread_join(men[i], NULL);
		
	for(i = 0; i < WOMEN_SIZE; i++)
		pthread_join(women[i], NULL);
		
	
}


/*
void * womenRoutine(void * arg)
{
	while(1)
	{
		int * aux = arg;
		int id = * aux;
		fprintf(stderr, "mulher: %d\n\n", id);
		sem_wait(&mutexFemale);
		++womenCount; // aumenta quantidade de mulheres
		if(womenCount == 1)
			sem_wait(&accessMutex);
		sem_wait(&mutexFemale);
		//printf("Mulher %d usando banheiro\n", id);
		sem_post(&mutexFemale);
		--womenCount;
		if(womenCount == 0)
			sem_post(&accessMutex); // sai do banheiro (diminui quantidade de mulheres)
		sem_post(&mutexFemale);
	}
}

void * menRoutine(void * arg)
{
	while(1)
	{
		int * aux = arg;
		int id = * aux;
		fprintf(stderr, "homem: %d\n\n", id);
		sem_wait(&mutexMale);
		menCount++; // aumenta quantidade de mulheres
		if(menCount == 1)
			sem_wait(&accessMutex);
		sem_wait(&mutexMale);
		printf("Homem %d usando banheiro\n", id);
		sem_post(&mutexFemale);
		--womenCount;
		if(womenCount == 0)
			sem_post(&accessMutex); // sai do banheiro (diminui quant	
		sem_post(&mutexMale);
	}
}
*/

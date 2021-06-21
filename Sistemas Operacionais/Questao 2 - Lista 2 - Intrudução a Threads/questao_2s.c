#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid) {
/* Esta funcao imprime o identificador do thread e sai. */
	printf("Ola mundo. Boas vindas do thread %d\n", *(int *)tid);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
/* O programa principal cria 10 threads e sai. */

	pthread_t threads[NUMBER_OF_THREADS];
	int status, i, uids[NUMBER_OF_THREADS];
 	
	for(i=0; i < NUMBER_OF_THREADS; i++) {
		printf("Metodo Main. Criando thread %d\n", i);
		uids[i] = i;
		status = pthread_create(&threads[i], NULL, print_hello_world, (void*)&uids[i]);
		if (status != 0) {
			printf("Oops. pthread_create returned error code %d\n", status);
			exit(-1);
		}
		pthread_join(threads[i], NULL);
	}
	exit(NULL);
}

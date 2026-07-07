#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

long long shared_counter = 0;

pthread_mutex_t counter_mutex;

void *increment_counter(void *arg){
	int i; //incrementos
	long num_interations = *((long *)arg); //Número de conteos
	for(i = 0; i< num_interations;i++){//Comienza el conteo y la zona crítica
		pthread_mutex_lock(&counter_mutex);
		shared_counter++;
		pthread_mutex_unlock(&counter_mutex);
	}
	return NULL;
}

int main(){
	pthread_t thread1, thread2; //Hilos
	long iterations_per_thread = 1000000; //Número de incrementos por hilo
	
	shared_counter = 0; //Inicializa a 0 el contadod
	pthread_mutex_init(&counter_mutex, NULL);//Inicia el mutex
	/*Creación de los hilos que van a contar*/
	pthread_create(&thread1, NULL, increment_counter, &iterations_per_thread);
	
	pthread_create(&thread2, NULL, increment_counter, &iterations_per_thread);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("Valor esperado %ld\n",2*iterations_per_thread);
	printf("Valor final: %lld\n",shared_counter);

	pthread_mutex_destroy(&counter_mutex);
	return 0;
	}

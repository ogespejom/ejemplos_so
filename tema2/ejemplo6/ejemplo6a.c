#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

long long shared_counter = 0;

void *increment_counter(void *arg){
	int i; //incrementos
	long num_interations = *((long *)arg); //Número de conteos
	for(i = 0; i< num_interations;i++){//Comienza el conteo y la zona crítica
		shared_counter++;
		}
		return NULL;
}

int main(){
	pthread_t thread1, thread2; //Hilos
	long iterations_per_thread = 1000000; //Número de incrementos por hilo
	
	shared_counter = 0; //Inicializa a 0 el contadod
	/*Creación de los hilos que van a contar*/
	pthread_create(&thread1, NULL, increment_counter, &iterations_per_thread);
	pthread_create(&thread2, NULL, increment_counter, &iterations_per_thread);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	printf("Valor esperado %ld\n",2*iterations_per_thread);
	printf("Valor final: %lld\n",shared_counter);
	return 0;
	}

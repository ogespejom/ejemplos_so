#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

long contador;

void* cuenta(void*){
	while(1) contador++;
}

int main(){
	pthread_t id_h;
	int ret_h;
	void *arg=NULL;

	contador = 0;

	ret_h = pthread_create(&id_h, NULL, &cuenta, arg);
	if(ret_h){
		printf("ERROR");
		exit(1);
	}
	printf("El hilo se encuentra funcionando en segundo plano...");
	sleep(5);
	getchar();
	printf("El contador llegó hasta: %ld\n", contador);
	exit(0);	
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int global = 10;

void* hilo(void *arg){
	global = 100;
	printf("Variable después del hilo desde el hilo\n");
	printf("Global: %d\n",global);
	getchar();
	return 0;
}

int main(){
	pthread_t id_h;
	int ret_h;
	void *arg=NULL;
	
	printf("Variables antes del hilo\n");
	printf("Global: %d\n",global);
	ret_h = pthread_create(&id_h,NULL,&hilo,arg);
	if(ret_h){
		printf("¡Error en la creación del hilo!\n");
		return -1;
	}
	pthread_join(id_h,NULL);
	printf("Variables después del hilo desde el padre\n");
	printf("Global: %d\n",global);
	getchar();
	return 0;
}

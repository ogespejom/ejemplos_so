#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Ejemplo3 Sistemas Operativos
Mostrar el comportamiento de la memoria en subprocesos
*/

int variable_global = 10;

int main(){
	pid_t pid;
	int variable_local = 20;
	int *ptr = (int*)malloc(sizeof(int));
	*ptr = 30;
	printf("Variables antes del fork: Global: %d, Local: %d, Puntero: %d\n",variable_global, variable_local,*ptr);

	pid = fork();
	switch (pid){
		case -1:
			printf("¡Error!\n");
			free(ptr);
			return -1;
			break;
		case 0:
			printf("Hijo con PID: %d con padre PPID: %d \n",getpid(), getppid());
			variable_global = 100;
			variable_local = 200;
			*ptr = 300;
			printf("Las variables del hijo son:\n");
			printf("Gobal: %d, Local: %d, ptr: %d\n", variable_global, variable_local, *ptr);
			getchar();
			free(ptr);
			break;
		default:
			wait(NULL);
			printf("Estas son las variables después del fork\n");
			printf("Global: %d, Local: %d, ptr: %d",variable_global, variable_local, *ptr);
			getchar();
			free(ptr);
			return 0;
	}
}


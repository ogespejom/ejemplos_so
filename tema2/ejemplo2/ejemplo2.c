#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
/*
Ejemplo 2 sistemas operativos
Creación de subprocesos
*/

int main(){
	pid_t pid;
	pid = fork();
	
	if (pid<0){
		printf("¡Error en la creación de un proceso!\n");
		return -1;
	} else if (pid==0){
		printf("Este el el proceso hijo con PID: %d con padre con PPID: %d\n",getpid(),getppid());
		getchar();
	} else {
		printf("Este es el proceso padre con PID: %d\n", getpid());
		wait(NULL); //Quitar para probar la secuencia de procesos
	}
}

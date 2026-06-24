#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
Ejemplo 1 de Sistemas operativos
Observar la creación de un proceso y los datos que guarda el sistema operativo
*/

int main(){
	printf("Este es un proceso con número: %d",getpid());
	getchar();
}

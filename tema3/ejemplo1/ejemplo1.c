#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Iniciando proceso de carga del procesador (PID %d)...\n", getpid());
	long long x=0;
	while(1){
		x=x+1;
	}
	return 0;
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("iniciando proceso...\n");
    raise(SIGTERM);
    printf("Saliendo del proceso\n");
    exit(0);
}
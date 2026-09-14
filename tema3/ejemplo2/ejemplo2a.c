#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    signal(SIGTERM,SIG_IGN);
    printf("iniciando proceso...\n");
    raise(SIGTERM);
    printf("Saliendo del proceso\n");
    exit(0);
}

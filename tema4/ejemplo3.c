#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int sig){
    printf("Fallo de página! (SEGV)\n");
    exit(1);
}

int main(){
    signal(SIGSEGV, handler);
    int *ptr = NULL;
    *ptr = 42;
    return 0;
}
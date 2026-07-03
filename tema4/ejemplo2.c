#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global;

int main(){
    int stack;
    int *heap = malloc(sizeof(int));

    printf("Código:  %p\n", main);
    printf("Datos: %p\n", &global);
    printf("Pila: %p\n", &stack);
    printf("Montón: %p\n", heap);
    getchar();
    free(heap);
    return 0;
}
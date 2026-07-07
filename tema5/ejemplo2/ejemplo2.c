#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int arg, char *argv[]){

    struct dirent *archivo;
    DIR *dir;
    if (arg != 2){
        printf("Uso: %s <directorio>\n", argv[0]);
        return 1;
    }
    dir = opendir(argv[1]);
    while ((archivo = readdir(dir)) != NULL){
        printf("%s\n", archivo->d_name);
    }
    return 0;
}
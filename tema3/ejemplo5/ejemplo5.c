#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    //Creación de los descriptores de archivo
    int fd[2];
    pid_t pidC;
    //Preparación del buffer para enviar información
    char buf[10];
    int num_ch;
    //Cración de la tubería
    pipe(fd);
    //Inicio del hijo
    pidC = fork();

    switch (pidC)
    {
        case 0:
            close(fd[0]); //Como el hijo escribe cierra la lectura
            write(fd[1], "Hola\0",6); //Envía 5 caracteres
            close(fd[1]); //Se cierra la escritura para evitar memorias abiertas
            exit(0);
            break;
        case -1:
            printf("¡Error!\n");
            exit(-1);
            break;
        default: //El padre recibe la información
            close(fd[1]);// El padre cierra la lectura
            num_ch = read(fd[0], buf, sizeof(buf)); //El padre lee el buffer
            close(fd[0]); //Cierra la lectura para evitar memorias abiertas
            printf("Se han leído %d Bytes con el mensaje: %s\n", num_ch,buf);
            exit(0);
            break;
    }
}
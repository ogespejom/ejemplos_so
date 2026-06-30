#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
    int fd; //descriptor de archivo
    char buf[] = "Mensaje 1..."; //Mensaje a enviar
    mkfifo("/tmp/mi_fifo",0666); //Creación del archivo temporal
    fd = open("/tmp/mi_fifo",O_WRONLY); //Se abre el archivo como solo escritura

    write(fd,buf,sizeof(buf)); //Se escribe la información
    close(fd); //se cierra el archivo
    return 0;

}
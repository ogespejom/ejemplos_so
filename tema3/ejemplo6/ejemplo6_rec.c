#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
    int fd; //descriptor de archivo
    char buf[1024]; //Buffer para recibir el archivo

    fd = open("/tmp/mi_fifo",O_RDONLY); //Se abre el archivo como solo lectura
    int nb = read(fd, buf, sizeof(buf));
    close(fd); //se cierra el archivo
    printf("Recibido el mensaje, bytes %d Texto: %s \n", nb, buf);
    return 0;

}
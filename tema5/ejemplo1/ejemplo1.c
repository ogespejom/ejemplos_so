#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
 
void mostrar_atributos(const char *ruta) {
    struct stat info;
    if (stat(ruta, &info) == -1) {
        perror("stat");
        return;
    }
    printf("\nAtributos de '%s':\n", ruta);
    printf("- Inodo: %ld\n", (long)info.st_ino);
    printf("- Permisos: %o\n", info.st_mode & 0777);
    printf("- Tamano: %ld bytes\n", (long)info.st_size);
    printf("- Ultimo acceso: %s", ctime(&info.st_atime));
    printf("- Ultima modificacion: %s", ctime(&info.st_mtime));
}
 
int main(void) {
    const char *ruta = "mi_archivo_c.txt";
 
    /* Crear archivo si no existe, en modo solo escritura */
    int fd = open(ruta, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) { perror("open"); return 1; }
    printf("Archivo creado/abierto. Descriptor: %d\n", fd);
 
    write(fd, "Datos escritos desde C\n", 23);
    close(fd);
    printf("Archivo cerrado.\n");
 
    mostrar_atributos(ruta);
 
    /* Reabrir en modo lectura */
    fd = open(ruta, O_RDONLY);
    char buffer[100] = {0};
    read(fd, buffer, sizeof(buffer) - 1);
    printf("\nContenido leido: %s", buffer);
    close(fd);
    getchar();
    return 0;
}

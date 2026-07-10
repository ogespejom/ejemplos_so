#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set rfds;
    struct timeval tv;
    int retval;

    // Limpiamos el conjunto de descriptores y añadimos la entrada estándar (0 = teclado)
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    // Configuramos el temporizador para 5 segundos
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    printf("El proceso solicita datos de E/S. El SO lo pondrá a dormir (Blocked)...\n");
    printf("Tienes 5 segundos para escribir algo y generar una interrupción de hardware.\n\n");

    // select() cede el control del CPU al SO hasta que el teclado envíe datos
    retval = select(1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("Error en select()");
    } else if (retval) {
        printf("¡Interrupción de hardware recibida! El SO despertó este proceso.\n");
    } else {
        printf("Tiempo agotado. El teclado no envió interrupciones y el CPU se usó en otros procesos.\n");
    }

    return 0;
}
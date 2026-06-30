#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

static volatile int keep_running = 1;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Manejador de SIGALRM (seguro con write)
void handlerAlarm(int sig) {
    const char *msg = "¡Alarma!\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    _exit(0);
}

// Hilo que actualiza la cuenta regresiva en la primera línea
void* countdown_thread(void* arg) {
    for (int i = 5; i > 0 && keep_running; --i) {
        pthread_mutex_lock(&mutex);

        printf("\033[s");           // Guardar posición actual (segunda línea)
        printf("\033[1;1H");        // Ir a la primera línea
        printf("Alarma en: %2d segundos   ", i);
        printf("\033[u");           // Restaurar posición (vuelve a la segunda línea)
        fflush(stdout);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main(void) {
    char *entrada = malloc(10 * sizeof(char));
    if (entrada == NULL) {
        perror("malloc");
        return 1;
    }

    signal(SIGALRM, handlerAlarm);

    // ----- LIMPIAR LA CONSOLA AL INICIAR -----
    printf("\033[2J\033[H");   // Borra toda la pantalla y mueve cursor a (1,1)
    fflush(stdout);
    // -----------------------------------------

    // Mostrar el prompt en la segunda línea (con salto de línea)
    printf("\nIntroduzca algo (máximo 9 caracteres):\n");
    fflush(stdout);

    // Crear el hilo de cuenta regresiva
    pthread_t tid;
    if (pthread_create(&tid, NULL, countdown_thread, NULL) != 0) {
        perror("pthread_create");
        free(entrada);
        return 1;
    }

    // Activar la alarma (5 segundos)
    alarm(5);

    // Leer la entrada del usuario (el cursor está al inicio de la segunda línea)
    if (scanf("%9s", entrada) == 1) {
        keep_running = 0;
        pthread_join(tid, NULL);

        printf("\nEntrada del usuario: %s\n", entrada);
        fflush(stdout);
    } else {
        keep_running = 0;
        pthread_join(tid, NULL);
    }

    free(entrada);
    return 0;
}
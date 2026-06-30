#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/* * 1. MANEJADOR DE LA SEÑAL (RECEPTOR)
 * Al usar SA_SIGINFO, la función manejadora recibe 3 parámetros.
 * El segundo parámetro (siginfo_t) contiene la información enviada.
 */
void manejador_con_datos(int sig, siginfo_t *info, void *contexto) {
    printf("\n[Hijo] ¡Señal recibida!\n");
    printf("[Hijo] Número de señal: %d\n", sig);
    
    // Accedemos al valor que fue enviado usando info->si_value.sival_int
    printf("[Hijo] ** Información recibida: %d **\n", info->si_value.sival_int);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    } 
    
    else if (pid == 0) {
        /* ---------------------------------------------------
         * CÓDIGO DEL PROCESO HIJO (RECEPTOR)
         * --------------------------------------------------- */
        struct sigaction sa;
        
        // Asignamos nuestra función manejadora especial
        sa.sa_sigaction = manejador_con_datos;
        
        // Vaciamos la máscara de señales bloqueadas
        sigemptyset(&sa.sa_mask);
        
        // ¡CRÍTICO! SA_SIGINFO le dice al kernel que queremos recibir 
        // la estructura siginfo_t con los datos extra.
        sa.sa_flags = SA_SIGINFO;

        // Registramos el manejador para la señal SIGUSR1
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("Error en sigaction");
            exit(EXIT_FAILURE);
        }

        printf("[Hijo] Esperando señal del padre con PID %d...\n", getpid());
        
        // pause() suspende el proceso hasta que llegue una señal
        pause(); 
        
        printf("[Hijo] Terminando ejecución tras procesar la señal.\n");
        exit(EXIT_SUCCESS);
    } 
    
    else {
        /* ---------------------------------------------------
         * CÓDIGO DEL PROCESO PADRE (EMISOR)
         * --------------------------------------------------- */
        // Damos un segundo para asegurarnos de que el hijo haya configurado sigaction
        sleep(1); 
        
        // Preparamos los datos a enviar usando la unión sigval
        union sigval valor_a_enviar;
        valor_a_enviar.sival_int = 404; // Nuestro "mensaje" numérico
        
        printf("[Padre] Enviando señal SIGUSR1 al hijo (PID: %d)...\n", pid);
        printf("[Padre] Adjuntando el dato: %d\n", valor_a_enviar.sival_int);
        
        // Usamos sigqueue en lugar de kill para poder adjuntar el valor
        if (sigqueue(pid, SIGUSR1, valor_a_enviar) == -1) {
            perror("Error en sigqueue");
            exit(EXIT_FAILURE);
        }

        // Esperamos a que el hijo termine para que no quede zombie
        wait(NULL);
        printf("\n[Padre] El hijo ha terminado. Finalizando padre.\n");
    }

    return 0;
}
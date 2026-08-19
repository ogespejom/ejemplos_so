#include <sys/syscall.h>

int main() {
    char msg[] = "Hola\n";
    // Llamada directa al kernel, sin pasar por glibc
    long ret;
    __asm__ volatile (
        "mov $1, %%rax\n"         // 1 = sys_write
        "mov $1, %%rdi\n"         // 1 = stdout
        "mov %1, %%rsi\n"         // puntero al mensaje
        "mov $5, %%rdx\n"         // longitud
        "syscall\n"               // ¡Salto directo al Ring 0!
        "mov %%rax, %0\n"         // guardar resultado
        : "=r"(ret) 
        : "r"(msg)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
}

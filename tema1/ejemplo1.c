#include <unistd.h>

int main() {
    char mensaje[] = "Hola Mundo\n";
    // write(fd=1, buf=mensaje, count=11)
    write(1, mensaje, 11); 
    return 0;
}
/* Para observar los llamados: objdump -d ./ejemplo0 | grep -A 20 "<write@plt>:" */
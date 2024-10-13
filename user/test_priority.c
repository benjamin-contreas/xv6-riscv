#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    for(int i = 0; i < 20; i++) {
        if (fork() == 0) {
            printf("Ejecutando proceso %d\n", i);
            sleep(10);
            exit(0);
        } else {
            wait(0);  // Esperar a que el hijo termine antes de continuar
        }
    }

    exit(0);
}
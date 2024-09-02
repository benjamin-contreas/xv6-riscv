#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Solo se acepta 1 argumento en la consola de comandos.\n");
        exit(1);
    }

    int n= atoi(argv[1]);
    int ancestor_pid = getancestor(n);

    if (ancestor_pid == -1) {
        printf("El ancestro %d no existe.\n", n);
    }
    else {
        printf("PID del ancestro %d: %d\n", n, ancestor_pid);
    }

    exit(0);
}
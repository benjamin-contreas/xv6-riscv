#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main() {
    int fd;
    char *filename = "testfile";
    char *message = "Este es un archivo de prueba.\n";
    char *message2 = "Este es el mensaje final del archivo.\n";
    char buffer[128];
    int n;

    // Crear archivo
    fd = open(filename, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf("Error al crear el archivo\n");
        exit(1);
    }

    // Escribir algo en el archivo
    if (write(fd, message, strlen(message)) != strlen(message)) {
        printf("Error al escribir en el archivo\n");
        close(fd);
        exit(1);
    }
    printf("Escritura exitosa\n");
    close(fd);

    // Cambiar permisos
    if (chmod(filename, 1) < 0) {
        printf("Error al cambiar permisos\n");
        exit(1);
    }

    // Intentar abrir para escritura
    fd = open(filename, O_WRONLY);
    if (fd >= 0) {
        printf("Error: se pudo abrir para escritura sin permiso\n");
        exit(1);
    } else {
        printf("Correcto: no se puede abrir para escritura sin permiso\n");
    }
    close(fd);

    // Cambiar permisos a perm = 3
    if (chmod(filename, 3) < 0) {
        printf("Error al cambiar permisos\n");
        exit(1);
    }

    // Escribir nuevamente algo en el archivo
    fd = open(filename, O_WRONLY);
    if (write(fd, message2, strlen(message2)) != strlen(message2)) {
        printf("Error al escribir en el archivo\n");
        close(fd);
        exit(1);
    }
    printf("Escritura final exitosa\n");
    close(fd);
    

    // Leer contenido del archivo
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Error al abrir el archivo para lectura\n");
        exit(1);
    }
    printf("Contenido del archivo:\n");
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, n); // Escribir en stdout
    }

    if (n < 0) {
        printf("Error al leer el archivo\n");
    }
    close(fd);

    // Cambiar permisos a perm = 5 inmutable
    if (chmod(filename, 5) < 0) {
        printf("Error al cambiar permisos\n");
        exit(1);
    }

    // Intentar abrir para escritura
    fd = open(filename, O_WRONLY);
    if (fd >= 0) {
        printf("Error: se pudo abrir para escritura sin permiso\n");
        close(fd);
        exit(1);
    } else {
        printf("Correcto: no se puede abrir para escritura sin permiso\n");
    }
    close(fd);

    // Cambiar permisos a perm = 3, deberia fallar porque es inmutable
    if (chmod(filename, 3) > 0) {
        printf("Error: Se cambio el permiso de un archivo inmutable\n");
        exit(1);
    }
    else {
      printf("Correcto: no se puede cambiar el permiso de un archivo inmutable\n");
    }
    
    exit(0);
}

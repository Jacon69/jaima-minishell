#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line;
    int fd = open("prom.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    while (1) {
        // Mostrar el prompt y leer una línea de entrada
        line = readline("prom> ");
        if (!line) {
            break; // EOF, probablemente Ctrl+D
        }

        // Añadir la línea al historial
        add_history(line);

        // Si la línea es "exit", salir del bucle
        if (strcmp(line, "exit") == 0) {
            free(line);
            break;
        }

        // Escribir la línea en el archivo y añadir un salto de línea
        if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1) {
            perror("Error al escribir en el archivo");
            free(line);
            break;
        }

        // Liberar la memoria de la línea
        free(line);
    }

    close(fd);
    return 0;
}
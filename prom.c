#include "environment.h"


void ft_ejecutar(char *line, t_list  **env)
{
    char **args;
 //   int i;

    args = ft_split(line, ' ');
    if (!args)
        return;
    if (ft_strcmp(args[0], "env") == 0)
    {
        ft_lstiter(*env, print_string); //##PRUEBA## Imprime la lista de variables de entorno
    }
    else if (ft_strcmp(args[0], "export") == 0)
    {
        ft_add_v_env(args[1], env);  //ft_export(args);
    }
    else if (ft_strcmp(args[0], "unset") == 0)
    {
        ft_del_v_env(args[1], env);  //Crear un ft_unset
    }
}

void prom(t_list  **env) 
{
    char *line;
    int fd = open("prom.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("No se pudo abrir el archivo");
        return;
    }

    while (1) {
        // Mostrar el prompt y leer una línea de entrada
        line = readline("prom> "); //hace Malloc
        if (!line)
            break; // EOF, probablemente Ctrl+D Ctrl+c
        if (ft_strlen(line) > 0) // Añadir la línea al historial
            add_history(line);
        // Escribir la línea en el archivo y añadir un salto de línea
        if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1)    
        {
            perror("Error al escribir en el archivo");
            free(line);
            break;
        }
         
        if (ft_strcmp(line, "exit") == 0) // Si la línea es "exit", salir del bucle
        {
            free(line);
            break;
        }
        ft_ejecutar(line, env); //PAra pruebas en esta función pongo los comando que quiero probar

        // Aquí es donde de se tiene que procesar la linea introducida
        free(line); // Liberar la memoria de la línea
    }

    
    close(fd);
}

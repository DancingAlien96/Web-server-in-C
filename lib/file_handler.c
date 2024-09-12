#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_file_contents(const char *url, char **content, int *http_code) {
    // Inicializar contenido como NULL
    *content = NULL;
    FILE *file;
    char path[256];

    // Construye la ruta completa del archivo
    if (strcmp(url, "/") == 0) {
        snprintf(path, sizeof(path), "%s/index.html", HTML_ROOT);
    } else {
        snprintf(path, sizeof(path), "%s%s", HTML_ROOT, url);
    }

    // Intenta abrir el archivo
    file = fopen(path, "r");
    if (file == NULL) {
        *http_code = 404;
        return -1;  // Devuelve error si no se puede abrir el archivo
    }

    // Lee el archivo en el buffer
    char buffer[1024];
    size_t read_size;
    size_t total_size = 0;

    while ((read_size = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        *content = realloc(*content, total_size + read_size + 1);
        if (*content == NULL) {
            *http_code = 500;  // Error de memoria
            fclose(file);
            return -1;
        }
        memcpy(*content + total_size, buffer, read_size);
        total_size += read_size;
    }
    (*content)[total_size] = '\0';  // Asegurar terminador NULL

    *http_code = 200;
    fclose(file);
    return 0;
}

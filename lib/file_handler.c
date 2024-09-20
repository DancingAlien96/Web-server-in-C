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
    file = fopen(path, "rb");
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


const char* get_mime_type(const char* url) {
    if (strstr(url, ".html") != NULL) {
        return "text/html";
    } else if (strstr(url, ".css") != NULL) {
        return "text/css";
    } else if (strstr(url, ".js") != NULL) {
        return "application/javascript";
    } else if (strstr(url, ".png") != NULL) {
        return "image/png";
    } else if (strstr(url, ".jpg") != NULL || strstr(url, ".jpeg") != NULL) {
        return "image/jpeg";
    } else if (strstr(url, ".gif") != NULL) {
        return "image/gif";
    } else {
        return "application/octet-stream";  // Tipo de contenido por defecto
    }
}
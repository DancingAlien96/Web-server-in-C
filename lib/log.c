
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void log_event(const char *message) {
    FILE *file;
    char filepath[256];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[100];
    
    strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S]", t);
    printf("%s Evento: %s\n", time_str, message);

    strftime(filepath, sizeof(filepath), LOG_DIR "%Y-%m-%d.log", t);
    file = fopen(filepath, "a");
    if (file == NULL) {
        perror("Error al abrir el archivo de log de eventos");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s Evento: %s\n", time_str, message);
    fclose(file);
}

void log_error(const char *message) {
    FILE *file;
    char filepath[256];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[100];

    strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S]", t);
    fprintf(stderr, "%s Error: %s\n", time_str, message);

    strftime(filepath, sizeof(filepath), LOG_DIR "%Y-%m-%d-errors.log", t);
    file = fopen(filepath, "a");
    if (file == NULL) {
        perror("Error al abrir el archivo de log de errores");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s Error: %s\n", time_str, message);
    fclose(file);
}

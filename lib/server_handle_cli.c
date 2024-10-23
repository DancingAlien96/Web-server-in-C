#include "server_handle_cli.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>  
#include "file_handler.h"    
#include "http_status_codes.h" 
#include <time.h>  // Para srand() y rand()

void srv_handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received < 0) {
        log_error("Error al recibir datos del cliente");
        return;
    }

    buffer[bytes_received] = '\0';

    http_req req;
    parse_request(buffer, &req);

    // Redirigir si la solicitud es a la raíz "/"
    if (strcmp(req.url, "/") == 0) {
        srand(time(NULL));  // Inicializar generador de números aleatorios
        int random_site = rand() % 3 + 1;  // Generar un número aleatorio entre 1 y 3
        char redirect_url[256];

        // Asignar la URL de redirección según el número aleatorio
        if (random_site == 1) {
            strcpy(redirect_url, "/sitio1/index.html");
        } else if (random_site == 2) {
            strcpy(redirect_url, "/sitio2/index.html");
        } else {
            strcpy(redirect_url, "/sitio3/index.html");
        }

        // Construir la respuesta HTTP de redirección (302 Found)
        char response[512];
        snprintf(response, sizeof(response),
                 "HTTP/1.1 302 Found\r\n"
                 "Location: %s\r\n"
                 "Content-Length: 0\r\n"
                 "Connection: close\r\n\r\n",
                 redirect_url);

        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;  // Finaliza el manejo de esta conexión
    }

    int http_code;
    char *content = NULL;

    // Obtener el contenido del archivo solicitado
    get_file_contents(req.url, &content, &http_code);

    // Obtener el tipo MIME del archivo solicitado
    const char *content_type = get_mime_type(req.url);

    // Registrar en los logs el archivo que se está sirviendo
    if (http_code == 200) {
        char log_msg[512];
        snprintf(log_msg, sizeof(log_msg), "Sirviendo archivo: %s", req.url);
        log_event(log_msg);
    } else {
        char log_msg[512];
        snprintf(log_msg, sizeof(log_msg), "Error al servir: %s (Código: %d)", req.url, http_code);
        log_error(log_msg);
    }

    // Enviar la respuesta HTTP
    http_response(client_socket, http_code, content_type, content);

    if (content != NULL) {
        free(content);
    }
}

void parse_request(const char *request, http_req *req) {
    sscanf(request, "%s %s", req->method, req->url);
}

void http_response(int client_socket, int http_code, const char *content_type, const char *body) {
    char response[BUFFER_SIZE]; 
    const char *status_message = get_status_message(http_code);
    int content_length = strlen(body);

    snprintf(response, sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Server: SimpleCServer\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        http_code, status_message, content_type, content_length, body);

    send(client_socket, response, strlen(response), 0);
}

#include "server_handle_cli.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void srv_handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received < 0) {
        log_error("Error al recibir datos del cliente");
        return;
    }

    buffer[bytes_received] = '\0';  // Asegurar que el buffer termine en NULL

    http_req req;
    parse_request(buffer, &req);

    if (strcmp(req.method, "GET") == 0) {
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        getpeername(client_socket, (struct sockaddr*)&addr, &addr_len);

        char log_msg[512];
        snprintf(log_msg, sizeof(log_msg), 
                 "El cliente %s:%d solicita %s con el método %s",
                 inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), req.url, req.method);
        log_event(log_msg);
    } else {
        log_error("Método no soportado. Solo se permite GET.");
    }
}

void parse_request(const char *request, http_req *req) {
    sscanf(request, "%s %s", req->method, req->url);
}

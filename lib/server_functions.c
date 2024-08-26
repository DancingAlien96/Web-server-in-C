#include "server_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int srv_init(int port) {
    int server_fd;
    struct sockaddr_in address;

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección y puerto del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Vincular el socket con el puerto
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        exit(EXIT_FAILURE);
    }

    // Poner el socket en modo pasivo (escuchando)
    if (listen(server_fd, 3) < 0) {
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d\n", port);
    return server_fd;
}

int srv_accept_client(int server_fd) {
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Aceptar una nueva conexión
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Error en accept");
        exit(EXIT_FAILURE);
    }

    printf("Nueva conexión desde %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    return new_socket;
}

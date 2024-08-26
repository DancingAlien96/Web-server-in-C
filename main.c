#include "lib/server_functions.h"

#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;

    // Inicializar el servidor
    server_fd = srv_init(PORT);

    while (1) {
        // Aceptar nuevas conexiones
        new_socket = srv_accept_client(server_fd);
        // Aquí podrías manejar la conexión, pero por ahora solo aceptamos y notificamos
    }

    return 0;
}

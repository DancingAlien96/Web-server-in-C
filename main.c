#include "lib/server_functions.h"
#include "lib/log.h"
#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;

    // Inicializar el servidor
    log_event("Iniciando el servidor...");
    server_fd = srv_init(PORT);

    while (1) {
      
       new_socket = srv_accept_client(server_fd);
        
    }

    return 0;
}

#include "lib/server_functions.h"
#include "lib/server_handle_cli.h"
#include "lib/log.h"
#include <unistd.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
   

    // Inicializar el servidor
    log_event("Iniciando el servidor...");
    int server_fd = srv_init(PORT);

    while (1) {
      
     int client_socket = srv_accept_client(server_fd);
        srv_handle_client(client_socket);
        close(client_socket);
        
    }

    return 0;
}

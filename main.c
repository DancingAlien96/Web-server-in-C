#include "lib/server_functions.h"
#include "lib/server_handle_cli.h"
#include "lib/log.h"
#include "lib/queue.h"  // Cola que necesitas implementar
#include <pthread.h>    // Para usar hilos POSIX
#include <unistd.h>     // Para close()
#define PORT 8000
#define THREAD_POOL_SIZE 10

// Declaración global del pool de hilos y la cola de conexiones
pthread_t thread_pool[THREAD_POOL_SIZE];
queue_t connection_queue;

// Función para manejar las conexiones desde la cola
void* handle_multithread(void *arg) {
    while (1) {
        int client_socket = dequeue(&connection_queue);  // Sacar una conexión de la cola
        if (client_socket >= 0) {
            srv_handle_client(client_socket);  // Manejar la solicitud del cliente
            close(client_socket);  // Cerrar la conexión
        }
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    // Inicializar el servidor
    log_event("Iniciando el servidor...");
    int server_fd = srv_init(PORT);

    // Inicializar la cola de conexiones
    init_queue(&connection_queue);

    // Crear el pool de hilos
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, handle_multithread, NULL);
    }

    // Loop principal para aceptar conexiones
    while (1) {
        int client_socket = srv_accept_client(server_fd);
        if (client_socket >= 0) {
            enqueue(&connection_queue, client_socket);  // Poner la conexión en la cola
        } else {
            log_error("Error al aceptar la conexión.");
        }
    }

    return 0;
}

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void init_queue(queue_t *queue) {
    queue->front = NULL;
    queue->rear = NULL;
    pthread_mutex_init(&queue->lock, NULL);    // Inicializa el mutex
    pthread_cond_init(&queue->cond, NULL);     // Inicializa la variable de condición
}

void enqueue(queue_t *queue, int connfd) {
    node_t *new_node = malloc(sizeof(node_t)); // Crear un nuevo nodo
    new_node->connfd = connfd;
    new_node->next = NULL;

    pthread_mutex_lock(&queue->lock);  // Bloquea la cola

    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    pthread_cond_signal(&queue->cond);  // Despierta los hilos en espera
    pthread_mutex_unlock(&queue->lock); // Desbloquea la cola
}

int dequeue(queue_t *queue) {
    pthread_mutex_lock(&queue->lock);  // Bloquea la cola

    while (queue->front == NULL) {
        // Si la cola está vacía, espera hasta que haya una conexión
        pthread_cond_wait(&queue->cond, &queue->lock);
    }

    node_t *temp = queue->front;
    int connfd = temp->connfd;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;  // Si la cola queda vacía, rear también debe ser NULL
    }

    free(temp);  // Libera el nodo
    pthread_mutex_unlock(&queue->lock); // Desbloquea la cola
    return connfd;
}

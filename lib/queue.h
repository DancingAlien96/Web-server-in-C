#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>  // Para mutex y variables de condición

typedef struct node {
    int connfd;
    struct node *next;
} node_t;

typedef struct {
    node_t *front;
    node_t *rear;
    pthread_mutex_t lock;  // Mutex para sincronizar el acceso a la cola
    pthread_cond_t cond;   // Variable de condición para manejar la espera de conexiones
} queue_t;

void init_queue(queue_t *queue);
void enqueue(queue_t *queue, int connfd);
int dequeue(queue_t *queue);

#endif

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

int srv_init(int port);
int srv_accept_client(int server_fd);

#endif

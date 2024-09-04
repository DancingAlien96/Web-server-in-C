#ifndef SERVER_HANDLE_CLI_H
#define SERVER_HANDLE_CLI_H

#define BUFFER_SIZE 4096

typedef struct {
    char method[8];
    char url[256];
} http_req;

void srv_handle_client(int client_socket);
void parse_request(const char *request, http_req *req);

#endif

#ifndef HTTP_STATUS_CODES_H
#define HTTP_STATUS_CODES_H

typedef struct {
    int code;
    const char *description;
} HttpStatus;

extern const HttpStatus http_statuses[];

const char* get_status_message(int code);


#endif

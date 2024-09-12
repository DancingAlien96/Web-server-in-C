#include "http_status_codes.h"

const HttpStatus http_statuses[] = {
    {200, "OK"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {500, "Internal Server Error"}
};

const char* get_status_message(int code) {
    for (int i = 0; i < sizeof(http_statuses) / sizeof(HttpStatus); i++) {
        if (http_statuses[i].code == code) {
            return http_statuses[i].description;
        }
    }
    return "Unknown Status";
}

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#define HTML_ROOT "./html"

int get_file_contents(const char *url, char **content, int *http_code);

#endif

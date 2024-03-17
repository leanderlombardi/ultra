#ifndef ULTRAHTTP_H
#define ULTRAHTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUF_SIZE 1024
#define MAX_REDIRECTS 5

#define HOSTNAME_RESOLVE_ERROR_MSG "Error: Unable to resolve hostname\n"
#define SOCKET_OPEN_ERROR_MSG "Error: Couldn't open socket\n"
#define CONNECT_SERVER_ERROR_MSG "Error: Couldn't connect to server\n"
#define WRITE_SOCKET_ERROR_MSG "Error: Couldn't write to socket\n"
#define HTTP_REQ_ERROR_MSG "Error: HTTP request failed with status code %d\n"
#define REDIRECT_ERROR_MSG "Error: Too many redirects\n"
#define ERROR_OPEN_FILE_MSG "Error: Couldn't open file\n"

typedef enum  {
  HTTP_OK = 200,
  HTTP_MOVED_PERMANENTLY = 301,
  HTTP_FOUND = 302,
  HTTP_BAD_REQUEST = 400,
  HTTP_NOT_FOUND = 404,
  HTTP_INTERNAL_SERVER_ERROR = 500,
} HttpStatusCode;

int http_get(const char *, const char *);

#endif // ULTRAHTTP_H

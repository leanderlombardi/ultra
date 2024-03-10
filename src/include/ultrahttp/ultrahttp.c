#include "ultrahttp.h"

int http_get(const char *url, const char *filename) {
  int sockfd;
  struct sockaddr_in server_addr;
  struct hostent *server;
  char buffer[BUF_SIZE];
  int redirects = 0;

  char hostname[100];
  char path[200];
  sscanf(url, "http://%99[^/]/%199s", hostname, path);

  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr, (char *)HOSTNAME_RESOLVE_ERROR_MSG);
    return -1;
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr, (char *)SOCKET_OPEN_ERROR_MSG);
    return -1;
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr, server->h_length);
  server_addr.sin_port = htons(80);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    fprintf(stderr, (char *)CONNECT_SERVER_ERROR_MSG);
    return -1;
  }

  sprintf(buffer, "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, hostname);
  if (write(sockfd, buffer, strlen(buffer)) < 0) {
    fprintf(stderr, (char *)WRITE_SOCKET_ERROR_MSG);
    return -1;
  }

  int http_status = -1;
  while (1) {
    int bytes_recieved = read(sockfd, buffer, BUF_SIZE);
    if (bytes_recieved <= 0) {
      break;
    }

    buffer[bytes_recieved] = '\0';

    if (http_status == -1 && sscanf(buffer, "HTTP/1.1 %d", &http_status) == 0) {
      if (http_status != HTTP_OK && http_status != HTTP_MOVED_PERMANENTLY && http_status != HTTP_FOUND) {
        fprintf(stderr, (char *)HTTP_REQ_ERROR_MSG, http_status);
        close(sockfd);
        return -1;
      }
    }

    if (http_status == HTTP_MOVED_PERMANENTLY || http_status == HTTP_FOUND) {
      char *location = strstr(buffer, "Location: ");
      if (location != NULL) {
        sscanf(location, "Location: %s", buffer);
        close(sockfd);
        if (++redirects > MAX_REDIRECTS) {
          fprintf(stderr, (char *)REDIRECT_ERROR_MSG);
          return -1;
        }

        return http_get(buffer, filename);
      }
    }

    if (http_status == HTTP_OK) {
      FILE *file = fopen(filename, "wb");
      if (file == NULL) {
        fprintf(stderr, (char *)ERROR_OPEN_FILE_MSG);
        close(sockfd);
        return -1;
      }

      fwrite(buffer, 1, bytes_recieved, file);
      fclose(file);
    }
  }

  close(sockfd);

  return 0;
}

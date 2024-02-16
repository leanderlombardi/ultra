#include "include/download.h"
#include "include/basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define PACKAGE_URL_PREFIX "https://github.com/ultrapack/" // Git-based until I get enough donations for repo.ultrapack.org

size_t writef_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (quietlevel == 3) printf("%s%sULTRA%s%s Constructing 'writef_data' function...\n", CYAN, BLUE, CYAN, NORMAL);
  return fwrite(ptr, size, nmemb, stream);
}

int download_package(int onlydownload, int nodependencies, int quietlevel) {
  CURL *curl;
  CURLcode res;
  FILE *fp;
  char url[1000];

  // Construct URL
  snprintf(url, sizeof(url), "%s%s", PACKAGE_URL_PREFIX, package_name);

  // Init curl
  curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "Failed to initialize curl\n");
    exit(1);
  }

  fp = fopen(package_name, "wb");
  if (!fp) {
    fprintf(stderr, "Failed to open temporary file for writing\n");
    curl_easy_cleanup(curl);
    exit(1);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

:wa
:!poweroff
  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    if (quietlevel != 0) fprintf(stderr, "%sError: Failed to download '%s'\n", RED, curl_easy_strerror(res));
    fclose(fp);
    curl_easy_cleanup(curl);
    exit(1);
  }

  fclose(fp);
  curl_easy_cleanup(curl);

  printf("'%s' downloaded successfully.\n", package_name);

  return 0;
}


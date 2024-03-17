#include "download.h"
#include "../package/package.h"
#include <string.h>

void download_package(char *package_name) {
  Package *pkg;

  for (int i = 0; i < 1024; i++) {
    if (strcmp(packages[i].name, package_name) == 0) {

    }
  }
}

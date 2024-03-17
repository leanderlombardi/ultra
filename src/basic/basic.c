#include "basic.h"
#include <unistd.h>

int file_exists(char *path) {
  return access(path, F_OK) == 0;
}

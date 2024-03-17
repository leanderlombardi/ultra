#include "packagelist.h"
#include "../basic/basic.h"
#include "../ultrahttp/ultrahttp.h"
#include <stdio.h>
#include <stdlib.h>

void make_packagelist() {
  if (file_exists(PACKAGELIST_PATH)) {}
  else {
    FILE *package_list = fopen(PACKAGELIST_PATH, "w");
    if (package_list == NULL) {
      fprintf(stderr, "%sError%s: Couldn't open package list file\n", RED, NORMAL);
      fclose(package_list);
      exit(1);
    }

    fclose(package_list);

    http_get("http://raw.githubusercontent.com/leanderlombardi/ultra/pkglist", PACKAGELIST_PATH);
  }
}

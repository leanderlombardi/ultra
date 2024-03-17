#include "package.h"
#include "../packagelist/packagelist.h"
#include <string.h>
#include <stdlib.h>
#include "../basic/basic.h"
#include <stdio.h>

typedef struct Package {
  char *name;
  char *link;
} Package;

Package *packages[1024];

void make_packages() {
  make_packagelist();

  FILE *f = fopen(PACKAGELIST_PATH, "rb");
  if (f == NULL) {
    fclose(f);
    fprintf(stderr, "%sError:%s Couldn't open package list\n", RED, NORMAL);
    exit(1);
  }

  char *fcont = (char *)malloc(1048576 * sizeof(char));
  char *bufn = (char *)malloc(1024 * sizeof(char));

  char *names[1024];
  char *links[1024];

  fscanf(f, "%1023s", bufn);

  int j = 0;
  for (int i = 0; i < strlen(fcont); i++) {
    if (fcont[i] == ':') {
      names[j] = bufn;
      bufn = "";
      packages[j]->name = names[j];
      sprintf(links[j], "https://raw.githubusercontent.com/leanderlombardi/%s/blob/main/installscript.sh", names[j]);
      packages[j]->link = links[j];
      j++;
    } else {
      bufn[i] = fcont[i];
      continue;
    }
  }
}

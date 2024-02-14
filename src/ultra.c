#include <stdio.h>        // printf(char *format, ...);
#include <stdlib.h>       // exit(int code);
#include <string.h>       // strcmp(const char *s1, const char *s2);

void print_usage() {
  printf("Usage of ultra package manager:\n\n");
  printf("\tultra h ........................... Print this message and exit\n");
  printf("\tultra i [options] <package(s)> .... Installs given package(s)\n");
  printf("\tultra r [options] <package(s)> .... Removes given package(s)\n\n");
  printf("\tultra l ........................... Reloads package database\n");
  printf("\tultra u ........................... Upgrades ultra package manager\n");
  printf("Options:\n");
  printf("\t-v, --verbose ..................... Prints verbose output\n");
  printf("\t--only-download ................... Only downloads package [only for installation]\n");
  printf("\t-f, --from-file ................... Installs .utr package [only for installation]\n");
  printf("\t--no-dependencies ................. Doesn't install needed dependencies\n");
  printf("\t-q, --quiet ....................... Doesn't print anything besides errors\n");
  printf("\t--shut-the-fuck-up ................ Doesn't print anything\n");
}

int onlydownload = 0;
int nodependencies = 0;
int quietlevel = 2;

void install_packages(int argc, char **argv, int onlydownload, int nodependencies, int quietlevel) { // quietlevels: 0 = shut the fuck up, 1 = quiet, 2 = normal, 3 = verbose
    // Implementation will be added later
}

void remove_packages(int argc, char **argv, int quietlevel) {
    // Implementation will be added later
}

void reload_database(int quietlevel) {
    // Implementation will be added later
}

void upgrade_manager(int quietlevel) {
    // Implementation will be added later
}

int main(int argc, char **argv) {
  if (argc < 2) {
    print_usage();
    return 0;
  }

  int i;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "h") == 0) {
      print_usage();
      return 0;
    } else if (strcmp(argv[i], "i") == 0) {
      install_packages(argc - i - 1, argv + i + 1, onlydownload, nodependencies, quietlevel);
      return 0;
    } else if (strcmp(argv[i], "r") == 0) {
      remove_packages(argc - i - 1, argv + i + 1, quietlevel);
      return 0;
    } else if (strcmp(argv[i], "l") == 0) {
      reload_database(quietlevel);
      return 0;
    } else if (strcmp(argv[i], "u") == 0) {
      upgrade_manager(quietlevel);
      return 0;
    } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
      // Handle verbose option
    } else if (strcmp(argv[i], "--only-download") == 0) {
      // Handle only-download option
    } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--from-file") == 0) {
      // Handle from-file option
    } else if (strcmp(argv[i], "--no-dependencies") == 0) {
      // Handle no-dependencies option
    } else if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0) {
      // Handle quiet option
    } else if (strcmp(argv[i], "--shut-the-fuck-up") == 0) {
      // Handle shut-the-fuck-up option
    } else {
      printf("Invalid command or option: %s\n", argv[i]);
      print_usage();
      return 1;
    }
  }

  return 0;
}


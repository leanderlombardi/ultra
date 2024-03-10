#ifndef ULTRAZIP_H
#define ULTRAZIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define CHUNK_SIZE 16384

int extract_zip(const char *, const char *);

#endif // ULTRAZIP_H

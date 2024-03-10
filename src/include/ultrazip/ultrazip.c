#include "ultrazip.h"

int extract_zip(const char *zip_filename, const char *output_dir) {
  gzFile zip_file = gzopen(zip_filename, "rb");
  if (zip_file == NULL) {
    fprintf(stderr, "Error: Unable to extract zip file\n");
    return -1;
  }

  char out_filename[256];
  int ret;
  unsigned char buffer[CHUNK_SIZE];

  while (1) {
    ret = gzread(zip_file, buffer, sizeof(buffer));
    if (ret < 0) {
      fprintf(stderr, "Error: Unable to read from zip file\n");
      gzclose(zip_file);
      return -1;
    }

    if (ret == 0) break;

    sprintf(out_filename, "%s/%s", output_dir, buffer);
    FILE *outfile = fopen(out_filename, "wb");
    if (outfile == NULL) {
      fprintf(stderr, "Error: Unable to create output file\n");
      gzclose(zip_file);
      return -1;
    }

    fwrite(buffer, 1, ret, outfile);
    fclose(outfile);
  }

  gzclose(zip_file);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "utils.h"

char * load_file(char * path)
{
  long size;
  FILE * fd;
  char * buffer;

  // open file
  if (!(fd = fopen(path, "r"))) crash("open file");

  // read size
  if (fseek(fd, 0, SEEK_END) == -1) crash("seek to end");
  size = ftell(fd);
  if (fseek(fd, 0, SEEK_SET) == -1) crash("seek to start");

  // allocate memory
  if (!(buffer = (char *)malloc(size))) crash("malloc");

  // read info buffer
  if (fread(buffer, 1, (size_t)size, fd) != size) crash("fread");

  if (fclose(fd) == -1) crash("fclose");

  return(buffer);
}

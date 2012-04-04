#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOURCE "fixtures/sample.s"

void crash(char * message);
void debug(char * message);
void load_file(char * buffer, char * path);

int main(int argc, const char ** argv)
{
  debug("main");

  char * source;

  load_file(source, SOURCE);
  free(source);

  exit(0);
}

void crash(char * message)
{
  printf("!! Failed: %s !!\n", message);
  exit(EXIT_FAILURE);
}

void debug(char * message)
{
  printf("== %s ==\n", message);
}

void load_file(char * buffer, char * path)
{
  debug("load_file");

  long size;
  FILE * fd;

  // open file
  if (!(fd = fopen(path, "r"))) crash("open file");

  // read size
  if (fseek(fd, 0, SEEK_END) == -1) crash("seek to end");
  size = ftell(fd);
  if (fseek(fd, 0, SEEK_SET) == -1) crash("seek to start");

  // allocate memory
  if (!(buffer = (char *)malloc(sizeof(char) * size))) crash("malloc");

  // read info buffer
  if (fread(buffer, 1, (size_t)size, fd) != size) crash("fread");

  if (fclose(fd) == -1) crash("fclose");
}

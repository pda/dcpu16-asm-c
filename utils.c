#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void crash(char * message, char * file, int line)
{
  fprintf(stderr, "CRASH at %s:%d: %s\n", file, line, message);
  exit(EXIT_FAILURE);
}

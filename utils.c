#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void crash(char * message)
{
  printf("!! Failed: %s !!\n", message);
  exit(EXIT_FAILURE);
}

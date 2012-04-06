#include <stdlib.h>

#include "file.h"
#include "parser.h"

#define SOURCE_PATH "fixtures/sample.s"

int main(int argc, const char ** argv)
{
  char * source = load_file(SOURCE_PATH);
  parse(source);
  free(source);

  exit(EXIT_SUCCESS);
}

#include <stdlib.h>

#include "file.h"
#include "parser.h"

#define SOURCE_PATH "fixtures/sample.s"

int main(int argc, const char ** argv)
{
  char * source;
  parse_result_t * pr;

  source = load_file(SOURCE_PATH);
  pr = parse(source);
  free(source);

  for (int i = 0; i < pr->statement_count; i++)
    print_statement(&pr->statements[i]);

  exit(EXIT_SUCCESS);
}

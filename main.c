#include <stdlib.h>

#include "file.h"
#include "parser.h"

#define SOURCE_PATH "fixtures/sample.s"

int main(int argc, const char ** argv)
{
  char * source;
  parse_result_t * pr;
  statement_t * s;
  statement_t ** sp_reader;

  source = load_file(SOURCE_PATH);
  pr = parse(source);
  free(source);

  sp_reader = pr->statements;
  while ((s = *sp_reader++))
    print_statement(s);

  exit(EXIT_SUCCESS);
}

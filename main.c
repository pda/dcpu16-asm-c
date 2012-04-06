#include <stdlib.h>

#include "file.h"
#include "lexeme.h"
#include "lexer.h"
#include "utils.h"

#define SOURCE_PATH "fixtures/sample.s"

int main(int argc, const char ** argv)
{
  char * source = load_file(SOURCE_PATH);
  char * lexable = source;

  for (int i = 0; i < 200; i ++)
  {
    lexeme_t * lx = (lexeme_t *)malloc(sizeof(lexeme_t));
    if (!read_lexeme(lx, &lexable)) break;
    print_lexeme(lx);
    free_lexeme(lx);
  }

  free(source);

  exit(0);
}

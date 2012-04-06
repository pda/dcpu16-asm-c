#include <stdlib.h>

#include "file.h"
#include "token.h"
#include "lexer.h"
#include "utils.h"

#define SOURCE_PATH "fixtures/sample.s"

int main(int argc, const char ** argv)
{
  char * source = load_file(SOURCE_PATH);
  char * lexable = source;

  for (int i = 0; i < 200; i ++)
  {
    token_t * t = (token_t *)malloc(sizeof(token_t));
    if (!read_token(t, &lexable)) break;
    print_token(t);
    free_token(t);
  }

  free(source);

  exit(0);
}

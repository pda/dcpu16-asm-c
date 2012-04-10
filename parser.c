#include <stdlib.h>

#include "lexer.h"
#include "token.h"

#include "parser.h"

void parse(char * source)
{
  char * lexable = source;
  token_t * t;

  while (1)
  {
    t = read_token(&lexable);
    if (!t) break;
    print_token(t);
    free_token(t);
  }
}

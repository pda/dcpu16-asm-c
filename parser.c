#include <stdlib.h>

#include "lexer.h"
#include "token.h"

#include "parser.h"

void parse(char * source)
{
  char * lexable = source;

  while (1)
  {
    token_t * t = (token_t *)malloc(sizeof(token_t));
    if (!read_token(t, &lexable)) break;
    print_token(t);
    free_token(t);
  }
}

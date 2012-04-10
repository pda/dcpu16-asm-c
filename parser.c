#include <stdlib.h>

#include "lexer.h"
#include "token.h"

#include "parser.h"

void parse(char * source)
{
  lexer_state state;
  token_t * t;

  lexer_init(&state, source);

  while (1)
  {
    t = read_token(&state);
    if (!t) break;
    print_token(t);
    free_token(t);
  }
}

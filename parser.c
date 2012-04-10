#include <stdlib.h>

#include "lexer.h"
#include "token.h"

#include "parser.h"

void parse(char * source)
{
  lexer_state state;
  lexer_init(&state, source);

  token_t * t;

  print_token(next_token(&state));
  peek_token(&state, 3);
  peek_token(&state, 2);

  while ((t = next_token(&state)))
    print_token(t);

  // TODO: free() the tokens!
  // including the state->token_buffer

  return;
}

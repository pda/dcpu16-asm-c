#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#define TOKEN_BUFFER_SIZE 4

#include "token.h"

typedef struct token_list {
  token_t * token;
  struct token_list * next;
} token_list;

typedef struct {
  char * ptr;
  token_list * token_buffer;
  int ahead;
} lexer_state;

/**
 * Read the next token from the source code buffer.
 * Returns null pointer when finished.
 */
token_t * read_token(lexer_state *);

/**
 * The next token, possibly from the read-ahead buffer.
 * Returns null pointer when finished.
 */
token_t * next_token(lexer_state *);

/**
 * Peek at an upcoming token.
 * Returns null pointer if no token.
 */
token_t * peek_token(lexer_state *, int offset);

/**
 * Initialize the lexer_state for the source code buffer.
 */
void lexer_init(lexer_state *, char * source);

#endif

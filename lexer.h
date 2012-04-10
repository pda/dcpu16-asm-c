#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include "token.h"

typedef struct {
  char * ptr;
} lexer_state;

/**
 * Read the next token from the buffer.
 * Returns null pointer when finished.
 */
token_t * read_token(lexer_state *);

/**
 * Initialize the lexer_state for the source code buffer.
 */
void lexer_init(lexer_state *, char * source);

#endif

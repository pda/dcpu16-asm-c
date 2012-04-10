#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include "token.h"

/**
 * Read the next token from the buffer.
 * Returns null pointer when finished.
 */
token_t * read_token(char **);

#endif

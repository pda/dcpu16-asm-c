#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include "token.h"

/**
 * Read the next token from the buffer.
 * Returns 1 on success, 0 at end of buffer.
 */
int read_token(token_t *, char **);

#endif

#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include "lexeme.h"

/**
 * Read the next lexeme from the buffer.
 * Returns 1 on success, 0 at end of buffer.
 */
int read_lexeme(lexeme_t *, char **);

#endif

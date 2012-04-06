#ifndef INCLUDED_LEXEME_H
#define INCLUDED_LEXEME_H

// ----------------------------------------
// Types.

enum lexeme_types {
  LX_COMMENT,
  LX_NAME,
  LX_NUMBER,
  LX_BRACKET_L,
  LX_BRACKET_R,
  LX_COMMA,
  LX_LABEL,
  LX_PLUS
};

typedef struct {
  enum lexeme_types type;
  int size;
  char * value;
} lexeme_t;

// ----------------------------------------
// Functions.

/**
 * Prints a representation of the lexeme to STDOUT.
 */
void print_lexeme(lexeme_t *);

/**
 * Releases memory allocated to the lexeme.
 */
void free_lexeme(lexeme_t *);

#endif

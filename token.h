#ifndef INCLUDED_TOKEN_H
#define INCLUDED_TOKEN_H

// ----------------------------------------
// Types.

enum token_types {
  T_COMMENT,
  T_NEWLINE,
  T_NAME,
  T_INT_DEC,
  T_INT_HEX,
  T_BRACKET_L,
  T_BRACKET_R,
  T_COMMA,
  T_LABEL,
  T_PLUS
};

typedef struct {
  enum token_types type;
  int size;
  char * value;
} token_t;

// ----------------------------------------
// Functions.

/**
 * Prints a representation of the token to STDOUT.
 */
void print_token(token_t *);

/**
 * Releases memory allocated to the token.
 */
void free_token(token_t *);

/**
 * The name of the token type, e.g. "INT_HEX".
 */
const char * token_type_name(token_t *);

#endif

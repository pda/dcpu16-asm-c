#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#include "token.h"

void print_token(token_t * t)
{
  char label[32];
  snprintf(label, 32, "%s[%u]", token_type_name(t), t->size);
  printf("%12s %s\n", label, t->value);
}

void free_token(token_t * t)
{
  free(t->value);
  free(t);
}

const char * token_type_name(token_t * t)
{
  const char * names[] = {
    "COMMENT",
    "NAME",
    "INT_DEC",
    "INT_HEX",
    "BRACKET_L",
    "BRACKET_R",
    "COMMA",
    "LABEL",
    "PLUS"
  };

  return names[t->type];
}

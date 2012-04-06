#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#include "lexeme.h"

void print_lexeme(lexeme_t * l)
{
  debug("print_lexeme");
  printf("[t:%u s:%03u]    %s\n", l->type, l->size, l->value);
}

void free_lexeme(lexeme_t * l)
{
  free(l->value);
  free(l);
}

const char * lexeme_type_name(lexeme_t * l)
{
  const char * names[] = {
    "COMMENT",
    "NAME",
    "NUMBER",
    "BRACKET_L",
    "BRACKET_R",
    "COMMA",
    "LABEL",
    "PLUS"
  };

  return names[l->type];
}

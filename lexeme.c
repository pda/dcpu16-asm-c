#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#include "lexeme.h"

void print_lexeme(lexeme_t * l)
{
  char label[32];
  snprintf(label, 32, "%s[%u]", lexeme_type_name(l), l->size);
  printf("%12s %s\n", label, l->value);
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
    "INT_DEC",
    "INT_HEX",
    "BRACKET_L",
    "BRACKET_R",
    "COMMA",
    "LABEL",
    "PLUS"
  };

  return names[l->type];
}

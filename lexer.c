#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#include "lexer.h"

int read_lexeme(lexeme_t * l, char ** source)
{
  int type, value_size;
  char * base = *source;
  char * ptr;
  char c;

  // Ignore leading whitespace.
  while ((c = *base) && (c == ' ' || c == '\n')) base++;
  ptr = base;

  if (c == ';')
  {
    for (ptr++; c != '\n'; c = *(++ptr));
    value_size = ptr - base;
    type = LX_COMMENT;
  }
  else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
  {
    for (; (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); c = (*(++ptr)));
    value_size = ptr - base;
    type = LX_NAME;
  }
  else if (c == ':')
  {
    for (c = *(++ptr); (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); c = (*(++ptr)));
    value_size = ptr - base;
    type = LX_LABEL;
  }
  else if (c >= '0' && c <= '9')
  {
    for (; (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == 'x'; c = (*(++ptr)));
    value_size = ptr - base;
    type = LX_NUMBER;
  }
  else if (c == '[' || c == ']')
  {
    ptr++;
    value_size = 1;
    type = c == '[' ? LX_BRACKET_L : LX_BRACKET_R;
  }
  else if (c == ',')
  {
    ptr++;
    value_size = 1;
    type = LX_COMMA;
  }
  else if (c == '+')
  {
    ptr++;
    value_size = 1;
    type = LX_PLUS;
  }
  else if (c == 0)
  {
    return 0;
  }
  else
  {
    printf("c: '%c' (0x%02x)\n", c, (int)c);
    crash("unhandled lexeme");
  }

  l->type = type;
  l->size = value_size;
  l->value = (char *)malloc(value_size + 1);
  strlcpy(l->value, base, value_size + 1);
  *source = ptr;

  return 1;
}

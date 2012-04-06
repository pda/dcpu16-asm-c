#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#include "lexer.h"

int is_name_char(char);
int is_digit_char(char);
int is_hex_char(char);

int read_token(token_t * t, char ** source)
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
    type = T_COMMENT;
  }
  else if (is_name_char(c))
  {
    for (; is_name_char(c); c = (*(++ptr)));
    type = T_NAME;
  }
  else if (c == ':')
  {
    for (c = *(++ptr); is_name_char(c); c = (*(++ptr)));
    type = T_LABEL;
  }
  else if (is_digit_char(c))
  {
    if (*(base + 1) == 'x') // look-ahead
    {
      for (; is_hex_char(c); c = (*(++ptr)));
      type = T_INT_HEX;
    }
    else
    {
      for (; is_digit_char(c); c = (*(++ptr)));
      type = T_INT_DEC;
    }
  }
  else if (c == '[' || c == ']')
  {
    ptr++;
    type = c == '[' ? T_BRACKET_L : T_BRACKET_R;
  }
  else if (c == ',')
  {
    ptr++;
    type = T_COMMA;
  }
  else if (c == '+')
  {
    ptr++;
    type = T_PLUS;
  }
  else if (c == 0)
  {
    return 0;
  }
  else
  {
    printf("c: '%c' (0x%02x)\n", c, (int)c);
    crash("unhandled token");
  }

  t->type = type;
  t->size = value_size = ptr - base;
  t->value = (char *)malloc(value_size + 1);
  strlcpy(t->value, base, value_size + 1);
  *source = ptr;

  return 1;
}

int is_name_char(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit_char(char c)
{
  return c >= '0' && c <= '9';
}

int is_hex_char(char c)
{
  return is_digit_char(c) || (c >= 'a' && c <= 'f') || c == 'x';
}

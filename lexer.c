#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#include "lexer.h"

int is_name_char(char);
int is_digit_char(char);
int is_hex_char(char);

token_t * read_token(lexer_state * state)
{
  token_t * t;
  int type, value_size;
  char * left = state->ptr;
  char * right;
  char c;

  // Ignore spaces.
  while ((c = *left) && (c == ' ')) left++;
  right = left;

  if (c == ';')
  {
    while (c != '\n') c = *(++right);
    type = T_COMMENT;
  }
  else if (c == '\n')
  {
    right++;
    type = T_NEWLINE;
  }
  else if (is_name_char(c))
  {
    while (is_name_char(c)) c = *(++right);
    type = T_NAME;
  }
  else if (c == ':')
  {
    c = *(right++);
    while (is_name_char(c)) c = *(++right);
    type = T_LABEL;
  }
  else if (is_digit_char(c))
  {
    if (*(left + 1) == 'x') // look-ahead
    {
      while (is_hex_char(c)) c = *(++right);
      type = T_INT_HEX;
    }
    else
    {
      while (is_digit_char(c)) c = *(++right);
      type = T_INT_DEC;
    }
  }
  else if (c == '[' || c == ']')
  {
    right++;
    type = c == '[' ? T_BRACKET_L : T_BRACKET_R;
  }
  else if (c == ',')
  {
    right++;
    type = T_COMMA;
  }
  else if (c == '+')
  {
    right++;
    type = T_PLUS;
  }
  else if (c == 0)
  {
    return NULL;
  }
  else
  {
    printf("c: '%c' (0x%02x)\n", c, (int)c);
    crash("unhandled token");
  }

  t = (token_t *)malloc(sizeof(token_t));
  t->type = type;
  t->size = value_size = right - left;
  t->value = (char *)malloc(value_size + 1);
  strlcpy(t->value, left, value_size + 1);

  state->ptr = right;

  return t;
}

void lexer_init(lexer_state * state, char * source)
{
  state->ptr = source;
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

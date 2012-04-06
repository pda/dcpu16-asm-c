#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file.h"
#include "lexeme.h"
#include "utils.h"

#define SOURCE_PATH "fixtures/sample.s"
#undef DEBUG

// ----------------------------------------
// Function headers.

int read_lexeme(lexeme_t *, char **);

// ----------------------------------------
// Main.

int main(int argc, const char ** argv)
{
  debug("main");

  char * source = load_file(SOURCE_PATH);
  char * lexable = source;

  for (int i = 0; i < 200; i ++)
  {
    lexeme_t * lx = (lexeme_t *)malloc(sizeof(lexeme_t));
    if (!read_lexeme(lx, &lexable)) break;
    print_lexeme(lx);
    free_lexeme(lx);
  }

  free(source);

  debug("finished");
  exit(0);
}

// ----------------------------------------
// Functions.

int read_lexeme(lexeme_t * l, char ** source)
{
  debug("read_lexeme");

  int type, value_size;
  char * base = *source;
  char * ptr;
  char c;

  // Ignore leading whitespace.
  while ((c = *base) && (c == ' ' || c == '\n')) base++;
  ptr = base;

  if (c == ';')
  {
    debug("lexing comment");
    for (ptr++; c != '\n'; c = *(++ptr));
    value_size = ptr - base;
    type = LX_COMMENT;
  }
  else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
  {
    debug("lexing name");
    for (; (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); c = (*(++ptr)));
    value_size = ptr - base;
    type = LX_NAME;
  }
  else if (c == ':')
  {
    debug("lexing label");
    for (c = *(++ptr); (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); c = (*(++ptr)));
    value_size = ptr - base;
    type = LX_LABEL;
  }
  else if (c >= '0' && c <= '9')
  {
    debug("lexing number");
    for (; (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == 'x'; c = (*(++ptr)));
    value_size = ptr - base;
    type = LX_NUMBER;
  }
  else if (c == '[' || c == ']')
  {
    debug("lexing bracket");
    ptr++;
    value_size = 1;
    type = c == '[' ? LX_BRACKET_L : LX_BRACKET_R;
  }
  else if (c == ',')
  {
    debug("lexing comma");
    ptr++;
    value_size = 1;
    type = LX_COMMA;
  }
  else if (c == '+')
  {
    debug("lexing plus");
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

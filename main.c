#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

#define SOURCE_PATH "fixtures/sample.s"
#undef DEBUG

// ----------------------------------------
// Types.

enum lexeme_types {
  LX_COMMENT,
  LX_INSTRUCTION,
  LX_NUMBER,
  LX_BRACKET_OPEN,
  LX_BRACKET_CLOSE,
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
// Function headers.

char * load_file(char * path);

void print_lexeme(lexeme_t *);
int read_lexeme(lexeme_t *, char **);
void free_lexeme(lexeme_t *);

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

char * load_file(char * path)
{
  debug("load_file");

  long size;
  FILE * fd;
  char * buffer;

  // open file
  if (!(fd = fopen(path, "r"))) crash("open file");

  // read size
  if (fseek(fd, 0, SEEK_END) == -1) crash("seek to end");
  size = ftell(fd);
  if (fseek(fd, 0, SEEK_SET) == -1) crash("seek to start");

  // allocate memory
  if (!(buffer = (char *)malloc(size))) crash("malloc");

  // read info buffer
  if (fread(buffer, 1, (size_t)size, fd) != size) crash("fread");

  if (fclose(fd) == -1) crash("fclose");
  return(buffer);
}

void print_lexeme(lexeme_t * l)
{
  debug("print_lexeme");
  printf("[t:%u s:%03u]    %s\n", l->type, l->size, l->value);
}

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
    type = LX_INSTRUCTION;
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
    type = c == '[' ? LX_BRACKET_OPEN : LX_BRACKET_CLOSE;
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

void free_lexeme(lexeme_t * l)
{
  free(l->value);
  free(l);
}

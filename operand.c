#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "utils.h"

#include "operand.h"

static const char * operand_type_name(operand_t *);

void operand_init(operand_t * o)
{
  o->type = 0;
  o->reg = 0;
  o->next_word = 0;
  o->label = 0;
}

void operand_free(operand_t * o)
{
  free(o->label);
}

char * operand_to_s(operand_t * o)
{
  char * s = (char *)malloc(32);
  if (!s) CRASH("malloc operand_to_s");

  if (o->type == O_NULL)
    *s = 0;

  else if (o->type == O_REG)
    snprintf(s, 32, "%c", "ABCXYZIJ"[o->reg]);

  else if (o->type == O_NW)
    snprintf(s, 32, "0x%04X", o->next_word);

  else if (o->type == O_INDIRECT_NW)
    snprintf(s, 32, "[0x%04X]", o->next_word);

  else if (o->type == O_LITERAL && o->label)
    snprintf(s, 32, "%s", o->label);

  else if (o->type == O_INDIRECT_REG)
    snprintf(s, 32, "[%c]", "ABCXYZIJ"[o->reg]);

  else if (o->type == O_INDIRECT_NW_OFFSET)
    snprintf(s, 32, "[0x%04X+%c]", o->next_word, "ABCXYZIJ"[o->reg]);

  else if (o->type >= O_POP && o->type <= O_O)
    snprintf(s, 32, "%s", operand_type_name(o));

  else
    snprintf(s, 32,
      "t:0x%02X %s",
      o->type,
      o->label ? o->label : ""
    );

  return s;
}

static const char * operand_type_name(operand_t * o)
{
  enum operand_type t = o->type;
  if (t == 0x00) return "REG";
  if (t == 0x08) return "INDIRECT_REG";
  if (t == 0x10) return "INDIRECT_NW_OFFSET";
  if (t == 0x18) return "POP";
  if (t == 0x19) return "PEEK";
  if (t == 0x1A) return "PUSH";
  if (t == 0x1B) return "SP";
  if (t == 0x1C) return "PC";
  if (t == 0x1D) return "O";
  if (t == 0x1E) return "INDIRECT_NW";
  if (t == 0x1F) return "NW";
  if (t == 0x20) return "LITERAL";
  if (t == 0xDEAD) return "NULL";
  CRASH("Invalid type for operand_type_name");
  return (char *)0;
}

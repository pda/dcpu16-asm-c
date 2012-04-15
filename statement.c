#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "utils.h"

#include "statement.h"

statement_t * statement_new()
{
  statement_t * s = (statement_t *)malloc(sizeof(statement_t));
  if (!s) CRASH("malloc statement_t");

  s->label = 0;
  s->mnemonic[0] = 0;
  s->operand[0] = 0;
  s->operand[1] = 0;

  return s;
}

void statement_free(statement_t * s)
{
  free(s->label);
  free(s->operand[0]);
  free(s->operand[1]);
  free(s);
}

void print_statement(statement_t * s)
{
  const char * label = s->label ? s->label : "";
  char o[2][32];
  char * writer;

  bzero(o[0], 32);
  bzero(o[1], 32);

  writer = stpncpy(o[0], s->operand[0], 30);
  if (s->operand[1]) *(writer++) = ',';

  if (s->operand[1])
    stpncpy(o[1], s->operand[1], 31);

  printf(
    "%-16s %-3s  %-12s %-12s ; 0x%02X\n",
    label,
    s->mnemonic,
    o[0],
    o[1],
    s->opcode
  );
}

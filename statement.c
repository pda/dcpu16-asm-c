#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "utils.h"

#include "assembler.h"
#include "operand.h"
#include "statement.h"

void statement_init(statement_t * s)
{
  s->label = 0;
  s->mnemonic[0] = 0;
  s->opcode = 0;
  operand_init(&s->operand[0]);
  operand_init(&s->operand[1]);
}

void statement_free_members(statement_t * s)
{
  free(s->label);
  operand_free(&s->operand[0]);
  operand_free(&s->operand[1]);
}

void print_statement(statement_t * s)
{
  const char * label = s->label ? s->label : "";

  char * o[2];

  for (int i = 0; i < 2; i++)
    o[i] = operand_to_s(&s->operand[i]);

  instruction_t instruction;
  statement_assemble(s, &instruction);

  printf(
    "%-10s %-3s %-10s %-10s ;",
    label,
    s->mnemonic,
    o[0],
    o[1]
  );

  for (int i = 0; i < instruction.word_count; i++)
    printf(" %04x", instruction.word[i]);

  printf("\n");

  for (int i = 0; i < 2; i++)
    free(o[i]);
}

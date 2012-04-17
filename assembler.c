#include <stdio.h>
#include <strings.h>

#include "assembler.h"
#include "utils.h"

static void statement_assemble_operand(operand_t *, instruction_t *, int index);

void statement_assemble(statement_t * s, instruction_t * instruction)
{
  instruction->word[0] = s->opcode;
  instruction->word_count = 1;

  if (s->opcode == 0x0)
  {
    if (s->operand[1].type != O_NULL)
      CRASH("Non-basic opcode must have single operand.");

    switch (s->opcode_non_basic)
    {
      case OP_JSR:
        instruction->word[0] = 0;
        instruction->word[0] |= OP_JSR << OPCODE_WIDTH;
        statement_assemble_operand(&s->operand[0], instruction, 1);
        break;
      default:
        CRASH("Unhandled non-basic opcode");
    }
  }
  else
  {
    for (int i = 0; i < 2; i++)
      statement_assemble_operand(&s->operand[i], instruction, i);
  }
}

static void statement_assemble_operand(operand_t * o, instruction_t * instruction, int index)
{
  int shift = OPCODE_WIDTH + (index * OPERAND_WIDTH);

  switch (o->type)
  {
    case O_REG:
    case O_INDIRECT_REG:
      instruction->word[0] |= (o->type + o->reg) << shift;
      break;
    case O_INDIRECT_NW_OFFSET:
      instruction->word[0] |= (0x10 + o->reg) << shift;
      instruction->word[instruction->word_count] = o->next_word;
      instruction->word_count++;
      break;
    case O_NW:
    case O_INDIRECT_NW:
      if (o->next_word <= OPERAND_LITERAL_MAX && !o->label)
      {
        instruction->word[0] |= (o->next_word + OPERAND_LITERAL_OFFSET) << shift;
      }
      else
      {
        instruction->word[0] |= o->type << shift;
        instruction->word[instruction->word_count] = o->next_word;
        instruction->word_count++;
      }
      break;
    case O_POP:
    case O_PEEK:
    case O_PUSH:
    case O_SP:
    case O_PC:
    case O_O:
      instruction->word[0] |= o->type << shift;
      break;
    default:
      fprintf(stderr, "operand_to_s: %s\n", operand_to_s(o));
      fprintf(stderr, "operand type: %u 0x%02X\n", o->type, o->type);
      CRASH("unhandled operand type");
      break;
  }
}

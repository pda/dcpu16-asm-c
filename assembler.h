#ifndef INCLUDED_ASSEMBLER_H
#define INCLUDED_ASSEMBLER_H

#include <stdint.h>

#include "parser.h"
#include "statement.h"

/**
 * An assembled binary CPU instruction.
 */
typedef struct {
  int word_count; // 1..3
  uint16_t word[3];
} instruction_t;

typedef struct {
  long int length;
  uint16_t * code;
} program_t;

/**
 * Assemble the parse result into binary CPU instructions.
 */
program_t * assemble(parse_result_t *);

/**
 * Assembles the given statement_t into the instruction_t.
 */
void statement_assemble(statement_t *, instruction_t *);

#endif

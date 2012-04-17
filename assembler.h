#ifndef INCLUDED_ASSEMBLER_H
#define INCLUDED_ASSEMBLER_H

#include <stdint.h>

#include "statement.h"

/**
 * An assembled binary CPU instruction.
 */
typedef struct {
  int word_count;
  uint16_t word[3];
} instruction_t;


/**
 * Assembles the given statement_t into the instruction_t.
 */
void statement_assemble(statement_t *, instruction_t *);

#endif

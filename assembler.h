#ifndef INCLUDED_ASSEMBLER_H
#define INCLUDED_ASSEMBLER_H

#include <stdint.h>

#include "label_table.h"
#include "parser.h"
#include "statement.h"

/**
 * An assembled binary CPU instruction.
 */
typedef struct {
  int word_count; // 1..3
  uint16_t word[3];
} instruction_t;

/**
 * A stream of assembled CPU instructions.
 */
typedef struct {
  long int length;
  uint16_t * code;
} program_t;

typedef struct {
  label_table_t label_defs;
  label_table_t label_refs;
  program_t * program;
  uint16_t * next_word;
} assembler_state_t;

/**
 * Assemble the parse result into binary CPU instructions.
 */
program_t * assemble(parse_result_t *);

#endif

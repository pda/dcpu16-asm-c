#ifndef INCLUDED_STATEMENT_H
#define INCLUDED_STATEMENT_H

#include <stdint.h>

#include "operand.h"

typedef struct {
  char * label;
  char mnemonic[4];
  uint8_t opcode;
  operand_t operand[2];
} statement_t;

/**
 * Initialize an already allocated statement_t.
 */
void statement_init(statement_t *);

/**
 * Free memory for statement_t and its members.
 */
void statement_free_members(statement_t *);

/**
 * Dump a representation of the statement.
 */
void print_statement(statement_t *);

#endif

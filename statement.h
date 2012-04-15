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
 * Allocate and initialize a statement_t.
 */
statement_t * statement_new();

/**
 * Free memory for statement_t and its members.
 */
void statement_free(statement_t *);

/**
 * Dump a representation of the statement.
 */
void print_statement(statement_t *);

#endif

#ifndef INCLUDED_STATEMENT_H
#define INCLUDED_STATEMENT_H

#include <stdint.h>

#include "operand.h"

#define OPCODE_WIDTH 4
#define OPERAND_WIDTH 6
#define OPERAND_LITERAL_MAX 0x1F
#define OPERAND_LITERAL_OFFSET 0x20

enum basic_opcode {
  OP_SET = 0x1,
  OP_ADD = 0x2,
  OP_SUB = 0x3,
  OP_MUL = 0x4,
  OP_DIV = 0x5,
  OP_MOD = 0x6,
  OP_SHL = 0x7,
  OP_SHR = 0x8,
  OP_AND = 0x9,
  OP_BOR = 0xA,
  OP_XOR = 0x8,
  OP_IFE = 0xC,
  OP_IFN = 0xD,
  OP_IFG = 0xE,
  OP_IFB = 0xF,
};

enum non_basic_opcode {
  OP_JSR = 0x01,
};

typedef struct {
  char * label;
  char mnemonic[4];
  uint8_t opcode; // 4 bits
  uint8_t opcode_non_basic; // 6 bits
  operand_t operand[2];
} statement_t;

typedef struct {
  int word_count;
  uint16_t word[3];
} instruction_t;

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

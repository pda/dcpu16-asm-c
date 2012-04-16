#ifndef INCLUDED_OPERAND_H
#define INCLUDED_OPERAND_H

#include <stdint.h>

enum operand_type {
  O_REG = 0x00,
  O_INDIRECT_REG = 0x08,
  O_INDIRECT_NW_OFFSET = 0x10,
  O_POP = 0x18,
  O_PEEK = 0x19,
  O_PUSH = 0x1A,
  O_SP = 0x1B,
  O_PC = 0x1C,
  O_O = 0x1D,
  O_INDIRECT_NW = 0x1E,
  O_NW = 0x1F,
  O_LITERAL = 0x20,

  O_NULL = 0xDEAD,
};

// General purpose registers.
enum operand_register_value {
  REG_A,
  REG_B,
  REG_C,
  REG_X,
  REG_Y,
  REG_Z,
  REG_I,
  REG_J,
};

// Special registers.
enum operand_special_register {
  SREG_PC,
  SREG_SP,
  SREG_O,
};

typedef struct {
  enum operand_type type;
  enum operand_register_value reg;
  uint16_t next_word;
  char * label;
} operand_t;

/**
 * Initialize an already allocated operand_t.
 */
void operand_init(operand_t *);

/**
 * Releases memory allocated to operand and its members.
 */
void operand_free(operand_t *);

/**
 * Return a string representation of the operand.
 * Must be released with free() by the caller.
 */
char * operand_to_s(operand_t *);

/**
 * Sets the register (as enum operand_register_value) for the register name.
 */
void operand_set_reg_by_name(operand_t *, char *);

#endif

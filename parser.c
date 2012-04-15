#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "token.h"
#include "utils.h"

#include "parser.h"

typedef struct {
  char * label;
  char mnemonic[4];
  uint8_t opcode;
  char * operand[2];
} statement_t;

statement_t * parse_statement(lexer_state *);
statement_t * statement_new();
void statement_free(statement_t *);
void parse_discard_empty_lines(lexer_state *);
void parse_label(lexer_state *, statement_t *);
void parse_mnemonic(lexer_state *, statement_t *);
void parse_operands(lexer_state *, statement_t *);
void parse_operand(lexer_state *, statement_t *, int index);
uint8_t parser_opcode_for_mnemonic(char *);
void print_statement(statement_t *);

void parse(char * source)
{
  lexer_state state;
  lexer_init(&state, source);

  statement_t * s;

  while ((s = parse_statement(&state)))
  {
    print_statement(s);
    statement_free(s);
  }
}

statement_t * parse_statement(lexer_state * state)
{
  token_t * t;
  statement_t * s = statement_new();

  parse_discard_empty_lines(state);

  t = peek_token(state, 1);
  if (!t) return 0;

  if (t->type == T_LABEL)
    parse_label(state, s);

  parse_mnemonic(state, s);

  parse_operands(state, s);

  if (peek_token(state, 1)->type == T_COMMENT)
    next_token(state);

  if (next_token(state)->type != T_NEWLINE)
    CRASH("expected T_NEWLINE");

  return s;
}

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

void parse_discard_empty_lines(lexer_state * state)
{
  token_t * t;
  while ((t = peek_token(state, 1)) && (t->type == T_COMMENT || t->type == T_NEWLINE))
    next_token(state);
}

void parse_label(lexer_state * state, statement_t * s)
{
  token_t * t = next_token(state);
  s->label = (char *)malloc(t->size);
  if (!s->label) CRASH("malloc label");
  memcpy(s->label, t->value, t->size);
}

void parse_mnemonic(lexer_state * state, statement_t * s)
{
  token_t * t = next_token(state);
  if (t->type != T_NAME) { print_token(t); CRASH("expected T_NAME"); }
  memcpy(s->mnemonic, t->value, 4);
  s->opcode = parser_opcode_for_mnemonic(s->mnemonic);
}

void parse_operands(lexer_state * state, statement_t * s)
{
  parse_operand(state, s, 0);
  if (next_token(state)->type == T_COMMA)
    parse_operand(state, s, 1);
}

void parse_operand(lexer_state * state, statement_t * s, int index)
{
  token_t * t;
  t = next_token(state);

  switch (t->type)
  {
    case T_BRACKET_L:
      s->operand[index] = (char *)malloc(6); // TODO: free()
      if (!s->operand[index]) CRASH("malloc operand[index]");
      memcpy(s->operand[index], "[???]", 6);
      while (next_token(state)->type != T_BRACKET_R);
      break;
    case T_NAME:
    case T_INT_HEX:
    case T_INT_DEC:
      s->operand[index] = (char *)malloc(t->size); // TODO: free()
      if (!s->operand[index]) CRASH("malloc operand[index]");
      memcpy(s->operand[index], t->value, t->size);
      break;
    default:
      print_token(t);
      CRASH("parse_operand");
      break;
  }
}

uint8_t parser_opcode_for_mnemonic(char * m)
{
  // basic opcodes
  if (strcmp(m, "SET") == 0) return 0x1;
  if (strcmp(m, "ADD") == 0) return 0x2;
  if (strcmp(m, "SUB") == 0) return 0x3;
  if (strcmp(m, "MUL") == 0) return 0x4;
  if (strcmp(m, "DIV") == 0) return 0x5;
  if (strcmp(m, "MOD") == 0) return 0x6;
  if (strcmp(m, "SHL") == 0) return 0x7;
  if (strcmp(m, "SHR") == 0) return 0x8;
  if (strcmp(m, "AND") == 0) return 0x9;
  if (strcmp(m, "BOR") == 0) return 0xA;
  if (strcmp(m, "XOR") == 0) return 0xB;
  if (strcmp(m, "IFE") == 0) return 0xC;
  if (strcmp(m, "IFN") == 0) return 0xD;
  if (strcmp(m, "IFG") == 0) return 0xE;
  if (strcmp(m, "IFB") == 0) return 0xF;
  if (strcmp(m, "IFB") == 0) return 0xF;

  // non-basic opcodes
  if (strcmp(m, "JSR") == 0) return 0x10;

  puts(m); CRASH("parser_opcode_for_mnemonic");
  return -1;
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
